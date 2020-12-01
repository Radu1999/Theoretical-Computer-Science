//
// Created by Radu on 11/30/2020.
//

#ifndef ALGO1_H
#define ALGO1_H
#include <bits/stdc++.h>

using idx = std::size_t;

template <typename T>
class MinMaxHeap
{
public:
    //  see whether the heap is empty
    bool isEmpty() const noexcept;
    //  insert an element to the heap
    void insert(T) noexcept;
    //  return the minimum element in the heap
    T getMin() const;
    //  return the maximum element in the heap
    T getMax() const;
    //  delete the minimum element in the heap
    void deleteMin();
    //  delete the maximum element in the heap
    void deleteMax();
    //  return the size of the heap
    size_t size() const noexcept;
    //  check the invariant of a min-max heap
    bool checkInvariant() const noexcept;
    void buildMinMaxHeap(std::vector<T> v);

private:
    //  represent the min-max heap
    std::vector<T> heap;

    //  see whether the given index is at max level
    static bool isMaxLevel(idx);
    //  return the index of the parent
    static idx parent(idx);
    //  return the index of the grandparent
    static idx grandparent(idx);
    //  return the index of the right child
    static idx right(idx);
    //  return the index of the left child
    static idx left(idx);

    //  bubble up the element at min level
    void bubbleMin(idx);
    //  bubble up the element at max level
    void bubbleMax(idx);

    //  percolate down the element at min level
    void percolateMin(idx);
    //  percolate down the element at max level
    void percolateMax(idx);
    //  return the minimum child of a position
    idx getMinDescendant(idx) const;
    //  return the maximum child of a position
    idx getMaxDescendant(idx) const;
    //  return the minimum grandchild of a position
    idx getMinGrandChild(idx) const;
    //  return the maximum grandchild of a position
    idx getMaxGrandChild(idx) const;
};


#endif //UNTITLED_ALGO1_H
