/*

Copyright (c) 2014, Project OSRM contributors
All rights reserved.

Redistribution and use in source and binary forms, with or without modification,
are permitted provided that the following conditions are met:

Redistributions of source code must retain the above copyright notice, this list
of conditions and the following disclaimer.
Redistributions in binary form must reproduce the above copyright notice, this
list of conditions and the following disclaimer in the documentation and/or
other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

*/

#ifndef SEARCH_ENGINE_DATA_HPP
#define SEARCH_ENGINE_DATA_HPP

#include <boost/thread/tss.hpp>

#include "../typedefs.h"
#include "binary_heap.hpp"

struct HeapData
{
    NodeID parent;
    HeapData(NodeID p) : parent(p) {}
};

struct many_to_many_heapdata
{
    NodeID parent;
    unsigned distance;
    many_to_many_heapdata(NodeID p, unsigned d) : parent(p), distance(d) {}
};

struct SearchEngineData
{
    using QueryHeap = BinaryHeap<NodeID, NodeID, int, HeapData, UnorderedMapStorage<NodeID, int>>;
    using SearchEngineHeapPtr = boost::thread_specific_ptr<QueryHeap>;

    static SearchEngineHeapPtr forwardHeap;
    static SearchEngineHeapPtr backwardHeap;
    static SearchEngineHeapPtr forwardHeap2;
    static SearchEngineHeapPtr backwardHeap2;
    static SearchEngineHeapPtr forwardHeap3;
    static SearchEngineHeapPtr backwardHeap3;

    using many_to_many_heap =
        BinaryHeap<NodeID, NodeID, int, many_to_many_heapdata, UnorderedMapStorage<NodeID, int>>;
    using general_m2m_heap_ptr = boost::thread_specific_ptr<many_to_many_heap>;
    static general_m2m_heap_ptr general_m2m_heap;

    void InitializeOrClearFirstThreadLocalStorage(const unsigned number_of_nodes);

    void InitializeOrClearSecondThreadLocalStorage(const unsigned number_of_nodes);

    void InitializeOrClearThirdThreadLocalStorage(const unsigned number_of_nodes);

    void initialize_general_m2m_heap(const unsigned number_of_nodes);
};

#endif // SEARCH_ENGINE_DATA_HPP
