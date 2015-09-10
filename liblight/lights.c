/*
 * Copyright (C) 2013 The CyanogenMod Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */


#define LOG_NDEBUG 0
#define LOG_TAG "lights"

#include <cutils/log.h>

#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <pthread.h>

#include <sys/ioctl.h>
#include <sys/types.h>

#include <hardware/lights.h>

#ifndef min
#define min(a,b) ((a)<(b)?(a):(b))
#endif
#ifndef max
#define max(a,b) ((a)<(b)?(b):(a))
#endif

/******************************************************************************/

static pthread_once_t g_init = PTHREAD_ONCE_INIT;
static pthread_mutex_t g_lock = PTHREAD_MUTEX_INITIALIZER;
static struct light_state_t g_notification;
static struct light_state_t g_battery;
static struct light_state_t g_attention;

static int g_led_is_dt = 0;

const char *const LCD_FILE
        = "/sys/class/leds/lcd-backlight/brightness";

const char *const BUTTONS_FILE
        = "/sys/class/leds/button-backlight/brightness";

const char *const RED_LED_FILE
        = "/sys/class/leds/red/brightness";

const char *const GREEN_LED_FILE
        = "/sys/class/leds/green/brightness";

const char *const BLUE_LED_FILE
        = "/sys/class/leds/blue/brightness";

const char *const LED_FREQ_FILE
        = "/sys/class/leds/red/device/grpfreq";

const char *const LED_PWM_FILE
        = "/sys/class/leds/red/device/grppwm";

char const *const LED_BLINK_FILE
        = "/sys/class/leds/red/device/blink";

char const *const LED_DT_RED_BRIGHTNESS
        = "/sys/class/leds/led:rgb_red/brightness";

char const *const LED_DT_GREEN_BRIGHTNESS
        = "/sys/class/leds/led:rgb_green/brightness";

char const *const LED_DT_BLUE_BRIGHTNESS
        = "/sys/class/leds/led:rgb_blue/brightness";

char const *const LED_DT_RAMP_STEP_FILE
        = "/sys/class/leds/led:rgb_red/ramp_step_ms";

char const *const LED_DT_DUTY_FILE
        = "/sys/class/leds/led:rgb_red/duty_pcts";

char const *const LED_DT_BLINK_FILE
        = "/sys/class/leds/led:rgb_red/blink";

// Number of steps to use in the duty array
#define LED_DT_DUTY_STEPS       50

// Brightness ramp up/down time for blinking
#define LED_DT_RAMP_MS          500

/**
 * device methods
 */

void init_globals(void)
{
    // init the mutex
    pthread_mutex_init(&g_lock, NULL);

    /*
     * Determine whether LED is DT based.
     *
     * Traditional LED drivers control blinking via grpfreq/grppwm.
     * DT based LED drivers control blinking via ramp_step_ms/duty_pcts.
     *
     * Thus, if duty_pcts exists, the driver is DT based.
     */
    g_led_is_dt = (access(LED_DT_DUTY_FILE, R_OK) == 0);
}

static int
write_string(const char *path, const char *buffer)
{
    int fd;
    static int already_warned = 0;

    fd = open(path, O_RDWR);
    if (fd >= 0) {
        int bytes = strlen(buffer);
        int amt = write(fd, buffer, bytes);
        close(fd);
        return amt == -1 ? -errno : 0;
    } else {
        if (already_warned == 0) {
            ALOGE("write_string failed to open %s (%s)\n", path, strerror(errno));
            already_warned = 1;
        }
        return -errno;
    }
}

static int
write_int(const char *path, int value)
{
    char buffer[20];
    sprintf(buffer, "%d\n", value);
    return write_string(path, buffer);
}

static int
rgb_to_brightness(const struct light_state_t *state)
{
    int color = state->color & 0x00ffffff;
    return ((77*((color>>16)&0x00ff))
            + (150*((color>>8)&0x00ff)) + (29*(color&0x00ff))) >> 8;
}

static int
is_lit(struct light_state_t const *state)
{
    return state->color & 0x00ffffff;
}

static int
set_speaker_light_locked_drv(struct light_device_t *dev,
        struct light_state_t const *state)
{
    int len;
    int blink, freq, pwm;
    int onMS, offMS;
    unsigned int colorRGB;

    if (state == NULL) {
        write_int(RED_LED_FILE, 0);
        write_int(GREEN_LED_FILE, 0);
        write_int(BLUE_LED_FILE, 0);
        write_int(LED_BLINK_FILE, 0);
        return 0;
    }

    switch (state->flashMode) {
        case LIGHT_FLASH_TIMED:
            onMS = state->flashOnMS;
            offMS = state->flashOffMS;
            break;
        case LIGHT_FLASH_NONE:
        default:
            onMS = 0;
            offMS = 0;
            break;
    }

    colorRGB = state->color;

    if (onMS > 0 && offMS > 0) {
        int totalMS = onMS + offMS;

        // the LED appears to blink about once per second if freq is 20
        // 1000ms / 20 = 50
        freq = totalMS / 50;
        // pwm specifies the ratio of ON versus OFF
        // pwm = 0 -> always off
        // pwm = 255 => always on
        pwm = (onMS * 255) / totalMS;

        // the low 4 bits are ignored, so round up if necessary
        if (pwm > 0 && pwm < 16)
            pwm = 16;

        blink = 1;
    } else {
        blink = 0;
        freq = 0;
        pwm = 0;
    }

    write_int(RED_LED_FILE, (colorRGB >> 16) & 0xFF);
    write_int(GREEN_LED_FILE, (colorRGB >> 8) & 0xFF);
    write_int(BLUE_LED_FILE, colorRGB & 0xFF);

    if (blink) {
        write_int(LED_FREQ_FILE, freq);
        write_int(LED_PWM_FILE, pwm);
    }
    write_int(LED_BLINK_FILE, blink);

    return 0;
}

static int
set_speaker_light_locked_dt(struct light_device_t *dev,
        struct light_state_t const *state)
{
    int len;
    int onMS, offMS;
    unsigned int colorRGB;

    if (state == NULL) {
        write_int(LED_DT_BLINK_FILE, 0);
        write_int(LED_DT_RED_BRIGHTNESS, 0);
        return 0;
    }

    switch (state->flashMode) {
        case LIGHT_FLASH_TIMED:
            onMS = state->flashOnMS;
            offMS = state->flashOffMS;
            break;
        case LIGHT_FLASH_NONE:
        default:
            onMS = 0;
            offMS = 0;
            break;
    }

    colorRGB = state->color;

    if (onMS > 0 && offMS > 0) {
        char dutystr[(3+1)*LED_DT_DUTY_STEPS+1];
        char* p = dutystr;
        int stepMS;
        int n;

        onMS = max(onMS, LED_DT_RAMP_MS);
        offMS = max(offMS, LED_DT_RAMP_MS);
        stepMS = (onMS+offMS)/LED_DT_DUTY_STEPS;

        p += sprintf(p, "0");
        for (n = 1; n < (onMS/stepMS); ++n) {
            p += sprintf(p, ",%d", min((100*n*stepMS)/LED_DT_RAMP_MS, 100));
        }
        for (n = 0; n < LED_DT_DUTY_STEPS-(onMS/stepMS); ++n) {
            p += sprintf(p, ",%d", 100 - min((100*n*stepMS)/LED_DT_RAMP_MS, 100));
        }
        p += sprintf(p, "\n");

        write_int(LED_DT_RAMP_STEP_FILE, stepMS);
        write_string(LED_DT_DUTY_FILE, dutystr);
        write_int(LED_DT_BLINK_FILE, 1);
    }
    else {
        write_int(LED_DT_RED_BRIGHTNESS, colorRGB ? 255 : 0);
    }

    return 0;
}

static int
set_speaker_light_locked(struct light_device_t *dev,
        struct light_state_t const *state)
{
    if (g_led_is_dt)
        return set_speaker_light_locked_dt(dev, state);

    return set_speaker_light_locked_drv(dev, state);
}

static void
handle_speaker_battery_locked(struct light_device_t *dev,
        const struct light_state_t *state)
{
    set_speaker_light_locked(dev, NULL);
    if (is_lit(&g_attention)) {
        set_speaker_light_locked(dev, &g_attention);
    } else if (is_lit(&g_notification)) {
        set_speaker_light_locked(dev, &g_notification);
    } else {
        set_speaker_light_locked(dev, &g_battery);
    }
}

static int
set_light_backlight(struct light_device_t *dev,
        const struct light_state_t *state)
{
    int err = 0;
    int brightness = rgb_to_brightness(state);

    pthread_mutex_lock(&g_lock);

    err = write_int(LCD_FILE, brightness);

    pthread_mutex_unlock(&g_lock);

    return err;
}

static int
set_light_buttons(struct light_device_t *dev,
        const struct light_state_t *state)
{
    int err = 0;
    int brightness = rgb_to_brightness(state);

    pthread_mutex_lock(&g_lock);

    err = write_int(BUTTONS_FILE, brightness);

    pthread_mutex_unlock(&g_lock);

    return err;
}

static int
set_light_notifications(struct light_device_t *dev,
        const struct light_state_t *state)
{
    pthread_mutex_lock(&g_lock);

    g_notification = *state;
    handle_speaker_battery_locked(dev, state);

    pthread_mutex_unlock(&g_lock);

    return 0;
}

static int
set_light_attention(struct light_device_t *dev,
        const struct light_state_t *state)
{
    pthread_mutex_lock(&g_lock);

    g_attention = *state;
    if (state->flashMode == LIGHT_FLASH_HARDWARE) {
        if (g_attention.flashOnMS > 0 && g_attention.flashOffMS == 0) {
            g_attention.flashMode = LIGHT_FLASH_NONE;
        }
    } else if (state->flashMode == LIGHT_FLASH_NONE) {
        g_attention.color = 0;
    }
    handle_speaker_battery_locked(dev, state);

    pthread_mutex_unlock(&g_lock);

    return 0;
}

static int
set_light_battery(struct light_device_t *dev,
        const struct light_state_t *state)
{
    pthread_mutex_lock(&g_lock);

    g_battery = *state;
    handle_speaker_battery_locked(dev, state);

    pthread_mutex_unlock(&g_lock);

    return 0;
}

/** Close the lights device */
static int
close_lights(struct light_device_t *dev)
{
    if (dev) {
        free(dev);
    }
    return 0;
}


/******************************************************************************/

/**
 * module methods
 */

/** Open a new instance of a lights device using name */
static int open_lights(const struct hw_module_t *module, const char *name,
        struct hw_device_t **device)
{
    int (*set_light)(struct light_device_t *dev,
            const struct light_state_t *state);

    if (0 == strcmp(LIGHT_ID_BACKLIGHT, name))
        set_light = set_light_backlight;
    else if (0 == strcmp(LIGHT_ID_BUTTONS, name))
        set_light = set_light_buttons;
    else if (0 == strcmp(LIGHT_ID_NOTIFICATIONS, name))
        set_light = set_light_notifications;
    else if (0 == strcmp(LIGHT_ID_ATTENTION, name))
        set_light = set_light_attention;
    else if (0 == strcmp(LIGHT_ID_BATTERY, name))
        set_light = set_light_battery;
    else
        return -EINVAL;

    pthread_once(&g_init, init_globals);

    struct light_device_t *dev = malloc(sizeof(struct light_device_t));
    memset(dev, 0, sizeof(*dev));

    dev->common.tag = HARDWARE_DEVICE_TAG;
    dev->common.version = 0;
    dev->common.module = (struct hw_module_t*)module;
    dev->common.close = (int (*)(struct hw_device_t*))close_lights;
    dev->set_light = set_light;

    *device = (struct hw_device_t*)dev;
    return 0;
}

static struct hw_module_methods_t lights_module_methods = {
    .open =  open_lights,
};

/*
 * The lights Module
 */
struct hw_module_t HAL_MODULE_INFO_SYM = {
    .tag = HARDWARE_MODULE_TAG,
    .version_major = 1,
    .version_minor = 0,
    .id = LIGHTS_HARDWARE_MODULE_ID,
    .name = "Oppo Lights Module",
    .author = "The CyanogenMod Project",
    .methods = &lights_module_methods,
};
