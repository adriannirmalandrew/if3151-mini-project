/*
 * Header file that defines the Max Heap data structure
 */
#pragma once

#include <iostream>
#include <vector>
#include <stdexcept>

#include "ticket.h"

class MaxHeap {
private:
    std::vector<Ticket> heap;

    // Return index values relative to i
    int parent(int i) const { return (i - 1) / 2; }
    int left(int i) const { return (2 * i) + 1; }
    int right(int i) const { return (2 * i) + 2; }

    // Moves element up the tree after insertion
    void heapify_up(int i) {
        while (i > 0 && heap[parent(i)].get_score() < heap[i].get_score()) {
            std::swap(heap[i], heap[parent(i)]);
            i = parent(i);
        }
    }

    // Moves element down the tree after extraction
    void heapify_down(int i) {
        int largest = i;
        int l = left(i);
        int r = right(i);

        // Check if left child exists and is larger than the current largest
        if (l < heap.size() && heap[l].get_score() > heap[largest].get_score()) {
            largest = l;
        }
        // Check if right child exists and is larger than the current largest
        if (r < heap.size() && heap[r].get_score() > heap[largest].get_score()) {
            largest = r;
        }
        // If the largest is not the current node, swap and continue sifting down
        if (largest != i) {
            std::swap(heap[i], heap[largest]);
            heapify_down(largest);
        }
    }

public:
    void insert(const Ticket& t) {
        heap.push_back(t); // Add to the end of the vector (last leaf)
        heapify_up(heap.size() - 1); // Bubble up to restore heap property
    }

    const Ticket& get_top() const {
        return heap[0];
    }

    void delete_max() {
        if (heap.empty()) return;

        // Get max element
        Ticket max_ticket = heap[0];
        // Move the last element to the root position
        heap[0] = heap.back();
        heap.pop_back();
        // Push the new root down
        if (!heap.empty()) {
            heapify_down(0);
        }
    }

    bool is_empty() const {
        return heap.empty();
    }

    size_t size() const {
        return heap.size();
    }
};
