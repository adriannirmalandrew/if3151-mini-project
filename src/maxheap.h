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

    // Helper methods to get indices of parent and children
    int parent(Ticket i) { return (i - 1) / 2; }
    int leftChild(Ticket i) { return (2 * i) + 1; }
    int rightChild(Ticket i) { return (2 * i) + 2; }

    // Bubble up the element to maintain the max-heap property (used after insertion)
    void heapifyUp(Ticket i) {
        while (i > 0 && heap[parent(i)] < heap[i]) {
            std::swap(heap[parent(i)], heap[i]);
            i = parent(i);
        }
    }

    // Bubble down the element to maintain the max-heap property (used after extraction)
    void heapifyDown(Ticket i) {
        int maxIndex = i;
        int left = leftChild(i);
        int right = rightChild(i);
        int size = heap.size();

        if (left < size && heap[left] > heap[maxIndex]) {
            maxIndex = left;
        }

        if (right < size && heap[right] > heap[maxIndex]) {
            maxIndex = right;
        }

        if (i != maxIndex) {
            std::swap(heap[i], heap[maxIndex]);
            heapifyDown(maxIndex);
        }
    }

public:
    // Insert a new key into the max heap
    void insert(Ticket key) {
        heap.push_back(key);
        // heapifyUp(heap.size() - 1);
    }

    // Remove and return the maximum element (root) from the heap
    Ticket extractMax() {
        if (heap.empty()) {
            throw std::out_of_range("Heap is empty");
        }

        Ticket maxVal = heap[0];

        // Move the last element to the root and shrink the vector
        heap[0] = heap.back();
        heap.pop_back();

        if (!heap.empty()) {
            // heapifyDown(0); FIX THIS
        }

        return maxVal;
    }

    // Return the maximum element without removing it
    Ticket getMax() const {
        if (heap.empty()) {
            throw std::out_of_range("Heap is empty");
        }
        return heap[0];
    }

    // Check if the heap is empty
    bool isEmpty() const {
        return heap.empty();
    }

    // Return the current size of the heap
    size_t size() const {
        return heap.size();
    }
};
