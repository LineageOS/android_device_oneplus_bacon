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
#ifndef __LOC_HEAP__
#define __LOC_HEAP__

#include <stddef.h>
#include <string.h>

// abstract class to be implemented by client to provide a rankable class
class LocRankable {
public:
    virtual inline ~LocRankable() {}

    // method to rank objects of such type for sorting purposes.
    // The pointer of the input node would be stored in the heap.
    // >0 if ranks higher than the input;
    // ==0 if equally ranks with the input;
    // <0 if ranks lower than the input
    virtual int ranks(LocRankable& rankable) = 0;

    // convenient method to rank objects of such type for sorting purposes.
    inline bool outRanks(LocRankable& rankable) { return ranks(rankable) > 0; }
};

// opaque class to provide service implementation.
class LocHeapNode;

// a heap whose left and right children are not sorted. It is sorted only vertically,
// i.e. parent always ranks higher than children, if they exist. Ranking algorithm is
// implemented in Rankable. The reason that there is no sort between children is to
// help beter balance the tree with lower cost. When a node is pushed to the tree,
// it is guaranteed that the subtree that is smaller gets to have the new node.
class LocHeap {
protected:
    LocHeapNode* mTree;
public:
    inline LocHeap() : mTree(NULL) {}
    ~LocHeap();

    // push keeps the tree sorted by rank, it also tries to balance the
    // tree by adding the new node to the smaller of the subtrees.
    // node is reference to an obj that is managed by client, that client
    //      creates and destroyes. The destroy should happen after the
    //      node is popped out from the heap.
    void push(LocRankable& node);

    // Peeks the node data on tree top, which has currently the highest ranking
    // There is no change the tree structure with this operation
    // Returns NULL if the tree is empty, otherwise pointer to the node data of
    //         the tree top.
    LocRankable* peek();

    // pop keeps the tree sorted by rank, but it does not try to balance
    // the tree.
    // Return - pointer to the node popped out, or NULL if heap is already empty
    LocRankable* pop();

    // navigating through the tree and find the node that ranks the same
    // as the input data, then remove it from the tree. Rank is implemented
    // by rankable obj.
    // returns the pointer to the node removed; or NULL (if failed).
    LocRankable* remove(LocRankable& rankable);

#ifdef __LOC_UNIT_TEST__
    bool checkTree();
    uint32_t getTreeSize();
#endif
};

#endif //__LOC_HEAP__
