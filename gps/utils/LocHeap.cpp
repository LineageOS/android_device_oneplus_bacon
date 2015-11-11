/* Copyright (c) 2015, The Linux Foundation. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above
 *       copyright notice, this list of conditions and the following
 *       disclaimer in the documentation and/or other materials provided
 *       with the distribution.
 *     * Neither the name of The Linux Foundation, nor the names of its
 *       contributors may be used to endorse or promote products derived
 *       from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED "AS IS" AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS
 * BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
 * BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
 * OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN
 * IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */
#include <LocHeap.h>

class LocHeapNode {
    friend class LocHeap;

    // size of of the subtree, excluding self, 1 if no subtree
    int mSize;
    LocHeapNode* mLeft;
    LocHeapNode* mRight;
    LocRankable* mData;
public:
    inline LocHeapNode(LocRankable& data) :
        mSize(1), mLeft(NULL), mRight(NULL), mData(&data) {}
    ~LocHeapNode();

    // this only swaps the data of the two nodes, so no
    // detach / re-attached is necessary
    void swap(LocHeapNode& node);

    LocRankable* detachData();

    // push a node into the tree stucture, keeping sorted by rank
    void push(LocHeapNode& node);

    // pop the head node out of the tree stucture. keeping sorted by rank
    static LocHeapNode* pop(LocHeapNode*& top);

    // remove a specific node from the tree
    // returns the pointer to the node removed, which would be either the
    //         same as input (if successfully removed); or NULL (if failed).
    static LocHeapNode* remove(LocHeapNode*& top, LocRankable& data);

    // convenience method to compare data ranking
    inline bool outRanks(LocHeapNode& node) { return mData->outRanks(*node.mData); }
    inline bool outRanks(LocRankable& data) { return mData->outRanks(data); }

    // checks if mSize is correct, AND this node is the highest ranking
    // of the entire subtree
    bool checkNodes();

    inline int getSize() { return mSize; }
};

inline
LocHeapNode::~LocHeapNode() {
    if (mLeft) {
        delete mLeft;
        mLeft = NULL;
    }
    if (mRight) {
        delete mRight;
        mRight = NULL;
    }
    if (mData) {
        mData = NULL;
    }
}

inline
void LocHeapNode::swap(LocHeapNode& node) {
    LocRankable* tmpData = node.mData;
    node.mData = mData;
    mData = tmpData;
}

inline
LocRankable* LocHeapNode::detachData()  {
    LocRankable* data = mData;
    mData = NULL;
    return data;
}

// push keeps the tree sorted by rank, it also tries to balance the
// tree by adding the new node to the smaller of the subtrees.
// The pointer to the tree and internal links never change. If the
// mData of tree top ranks lower than that of the incoming node,
// mData will be swapped with that of the incoming node to ensure
// ranking, no restructuring the container nodes.
void LocHeapNode::push(LocHeapNode& node) {
    // ensure the current node ranks higher than in the incoming one
    if (node.outRanks(*this)) {
        swap(node);
    }

    // now drop the new node (ensured lower than *this) into a subtree
    if (NULL == mLeft) {
        mLeft = &node;
    } else if (NULL == mRight) {
        mRight = &node;
    } else if (mLeft->mSize <= mRight->mSize) {
        mLeft->push(node);
    } else {
        mRight->push(node);
    }
    mSize++;
}

// pop keeps the tree sorted by rank, but it does not try to balance
// the tree. It recursively swaps with the higher ranked top of the
// subtrees.
// The return is a popped out node from leaf level, that has the data
// swapped all the way down from the top. The pinter to the tree and
// internal links will not be changed or restructured, except for the
// node that is popped out.
// If the return pointer == this, this the last node in the tree.
LocHeapNode* LocHeapNode::pop(LocHeapNode*& top) {
    // we know the top has the highest ranking at this point, else
    // the tree is broken. This top will be popped out.  But we need
    // a node from the left or right child, whichever ranks higher,
    // to replace the current top. This then will need to be done
    // recursively to the leaf level. So we swap the mData of the
    // current top node all the way down to the leaf level.
    LocHeapNode* poppedNode = top;
    // top is losing a node in its subtree
    top->mSize--;
    if (top->mLeft || top->mRight) {
        // if mLeft is NULL, mRight for sure is NOT NULL, take that;
        // else if mRight is NULL, mLeft for sure is NOT, take that;
        // else we take the address of whatever has higher ranking mData
        LocHeapNode*& subTop = (NULL == top->mLeft) ? top->mRight :
            ((NULL == top->mRight) ? top->mLeft :
             (top->mLeft->outRanks(*(top->mRight)) ? top->mLeft : top->mRight));
        // swap mData, the tree top gets updated with the new data.
        top->swap(*subTop);
        // pop out from the subtree
        poppedNode = pop(subTop);
    } else {
        // if the top has only single node
        // detach the poppedNode from the tree
        // subTop is the reference of ether mLeft or mRight
        // NOT a local stack pointer. so it MUST be NULL'ed here.
        top = NULL;
    }

    return poppedNode;
}

// navigating through the tree and find the node that hass the input
// data. Since this is a heap, we do recursive linear search.
// returns the pointer to the node removed, which would be either the
//         same as input (if successfully removed); or NULL (if failed).
LocHeapNode* LocHeapNode::remove(LocHeapNode*& top, LocRankable& data) {
    LocHeapNode* removedNode = NULL;
    // this is the node, by address
    if (&data == (LocRankable*)(top->mData)) {
        // pop this node out
        removedNode = pop(top);
    } else if (!data.outRanks(*top->mData)) {
        // subtrees might have this node
        if (top->mLeft) {
            removedNode = remove(top->mLeft, data);
        }
        // if we did not find in mLeft, and mRight is not empty
        if (!removedNode && top->mRight) {
            removedNode = remove(top->mRight, data);
        }

        // top lost a node in its subtree
        if (removedNode) {
            top->mSize--;
        }
    }

    return removedNode;
}

// checks if mSize is correct, AND this node is the highest ranking
// of the entire subtree
bool LocHeapNode::checkNodes() {
    // size of the current subtree
    int totalSize = mSize;
    if (mLeft) {
        // check the consistency of left subtree
        if (mLeft->outRanks(*this) || !mLeft->checkNodes()) {
            return false;
        }
        // subtract the size of left subtree (with subtree head)
        totalSize -= mLeft->mSize;
    }

    if (mRight) {
        // check the consistency of right subtree
        if (mRight->outRanks(*this) || !mRight->checkNodes()) {
            return false;
        }
        // subtract the size of right subtree (with subtree head)
        totalSize -= mRight->mSize;
    }

    // for the tree nodes to consistent, totalSize must be 1 now
    return totalSize == 1;
}

LocHeap::~LocHeap() {
    if (mTree) {
        delete mTree;
    }
}

void LocHeap::push(LocRankable& node) {
    LocHeapNode* heapNode = new LocHeapNode(node);
    if (!mTree) {
        mTree = heapNode;
    } else {
        mTree->push(*heapNode);
    }
}

LocRankable* LocHeap::peek() {
    LocRankable* top = NULL;
    if (mTree) {
        top = mTree->mData;
    }
    return top;
}

LocRankable* LocHeap::pop() {
    LocRankable* locNode = NULL;
    if (mTree) {
        // mTree may become NULL after this call
        LocHeapNode* heapNode = LocHeapNode::pop(mTree);
        locNode = heapNode->detachData();
        delete heapNode;
    }
    return locNode;
}

LocRankable* LocHeap::remove(LocRankable& rankable) {
    LocRankable* locNode = NULL;
    if (mTree) {
        // mTree may become NULL after this call
        LocHeapNode* heapNode = LocHeapNode::remove(mTree, rankable);
        if (heapNode) {
            locNode = heapNode->detachData();
            delete heapNode;
        }
    }
    return locNode;
}

#ifdef __LOC_UNIT_TEST__
bool LocHeap::checkTree() {
    return ((NULL == mTree) || mTree->checkNodes());
}
uint32_t LocHeap::getTreeSize() {
    return (NULL == mTree) ? 0 : mTree->getSize();
}
#endif

#ifdef __LOC_DEBUG__

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

class LocHeapDebug : public LocHeap {
public:
    bool checkTree() {
        return ((NULL == mTree) || mTree->checkNodes());
    }

    uint32_t getTreeSize() {
        return (NULL == mTree) ? 0 : (mTree->getSize());
    }
};

class LocHeapDebugData : public LocRankable {
    const int mID;
public:
    LocHeapDebugData(int id) : mID(id) {}
    inline virtual int ranks(LocRankable& rankable) {
        LocHeapDebugData* testData = dynamic_cast<LocHeapDebugData*>(&rankable);
        return testData->mID - mID;
    }
};

// For Linux command line testing:
// compilation: g++ -D__LOC_HOST_DEBUG__ -D__LOC_DEBUG__ -g -I. -I../../../../vendor/qcom/proprietary/gps-internal/unit-tests/fakes_for_host -I../../../../system/core/include LocHeap.cpp
// test: valgrind --leak-check=full ./a.out 100
int main(int argc, char** argv) {
    srand(time(NULL));
    int tries = atoi(argv[1]);
    int checks = tries >> 3;
    LocHeapDebug heap;
    int treeSize = 0;

    for (int i = 0; i < tries; i++) {
        if (i % checks == 0 && !heap.checkTree()) {
            printf("tree check failed before %dth op\n", i);
        }
        int r = rand();

        if (r & 1) {
            LocHeapDebugData* data = new LocHeapDebugData(r >> 1);
            heap.push(dynamic_cast<LocRankable&>(*data));
            treeSize++;
        } else {
            LocRankable* rankable = heap.pop();
            if (rankable) {
                delete rankable;
            }
            treeSize ? treeSize-- : 0;
        }

        printf("%s: %d == %d\n", (r&1)?"push":"pop", treeSize, heap.getTreeSize());
        if (treeSize != heap.getTreeSize()) {
            printf("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
            tries = i+1;
            break;
        }
    }

    if (!heap.checkTree()) {
        printf("!!!!!!!!!!tree check failed at the end after %d ops!!!!!!!\n", tries);
    } else {
        printf("success!\n");
    }

    for (LocRankable* data = heap.pop(); NULL != data; data = heap.pop()) {
        delete data;
    }

    return 0;
}

#endif
