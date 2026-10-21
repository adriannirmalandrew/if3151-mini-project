/*
 * Header file that defines the Max Heap data structure
 */

#include <iostream>
#include <vector>
#include <stdexcept>

class MaxHeap {
private:
    std::vector<Ticket> heap;

    // Helper methods to get indices of parent and children
    int parent(int i) { return (i - 1) / 2; }
    int leftChild(int i) { return (2 * i) + 1; }
    int rightChild(int i) { return (2 * i) + 2; }

    // Bubble up the element to maintain the max-heap property (used after insertion)
    void heapifyUp(int i) {
        while (i > 0 && heap[parent(i)] < heap[i]) {
            std::swap(heap[parent(i)], heap[i]);
            i = parent(i);
        }
    }

    // Bubble down the element to maintain the max-heap property (used after extraction)
    void heapifyDown(int i) {
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
    void insert(int key) {
        heap.push_back(key);
        heapifyUp(heap.size() - 1);
    }

    // Remove and return the maximum element (root) from the heap
    int extractMax() {
        if (heap.empty()) {
            throw std::out_of_range("Heap is empty");
        }

        int maxVal = heap[0];

        // Move the last element to the root and shrink the vector
        heap[0] = heap.back();
        heap.pop_back();

        if (!heap.empty()) {
            heapifyDown(0);
        }

        return maxVal;
    }

    // Return the maximum element without removing it
    int getMax() const {
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
