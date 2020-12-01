//
// Created by Radu on 11/30/2020.
//
#include "algo1.h"

template <typename T>
bool MinMaxHeap<T>::isEmpty() const noexcept
{
    return heap.empty();
}

template <typename T>
void MinMaxHeap<T>::insert(T newValue) noexcept
{
    heap.push_back(newValue);
    if (isMaxLevel(heap.size() - 1))
        bubbleMax(heap.size() - 1);
    else bubbleMin(heap.size() - 1);
}

template <typename T>
T MinMaxHeap<T>::getMin() const
{
    if (isEmpty())
        throw("Heap is empty!");
    return heap[0];
}

template <typename T>
T MinMaxHeap<T>::getMax() const
{
    if (isEmpty())
        throw("Heap is empty!");

    if (heap.size() >= 3)
        return (heap[1] >= heap[2]) ? heap[1] : heap[2];
    else if (heap.size() == 2)
        return heap[1];
    else
        return heap[0];
}

template <typename T>
void MinMaxHeap<T>::deleteMin()
{
    if (isEmpty())
        throw("Heap is empty!");

    heap[0] = heap[heap.size() - 1];
    heap.pop_back();
    if (!isEmpty())
        percolateMin(0);
}

template <typename T>
void MinMaxHeap<T>::deleteMax()
{
    if (isEmpty())
        throw("Heap is empty!");

    idx maxIndex;

    if (heap.size() >= 3)
        maxIndex = (heap[1] >= heap[2]) ? 1 : 2;
    else if (heap.size() == 2)
        maxIndex = 1;
    else
        maxIndex = 0;

    heap[maxIndex] = heap[heap.size() - 1];
    heap.pop_back();
    if (maxIndex < heap.size())
        percolateMax(maxIndex);
}

template <typename T>
size_t MinMaxHeap<T>::size() const noexcept
{
    return heap.size();
}

template <typename T>
bool MinMaxHeap<T>::isMaxLevel(idx i)
{
    if ((int)log2(i + 1) % 2 == 0)
        return false;
    else
        return true;
}

template <typename T>
idx MinMaxHeap<T>::parent(idx i)
{
    return (i - 1) / 2;
}

template <typename T>
idx MinMaxHeap<T>::grandparent(idx i)
{
    return parent(parent(i));
}

template <typename T>
idx MinMaxHeap<T>::left(idx i)
{
    return 2 * i + 1;
}

template <typename T>
idx MinMaxHeap<T>::right(idx i)
{
    return 2 * i + 2;
}

template <typename T>
void MinMaxHeap<T>::bubbleMin(idx i)
{
    if (i == 0) return;

    idx par_i = parent(i);

    if (heap[i] < heap[par_i]) {
        while (i != 0) {
            if (heap[i] < heap[grandparent(i)])
                std::swap(heap[i], heap[grandparent(i)]);
            i = grandparent(i);
        }
    }

    if (heap[i] > heap[par_i]) {
        std::swap(heap[i], heap[par_i]);
        i = parent(i);
        while (i != 1 && i != 2) {
            if (heap[i] >= heap[grandparent(i)])
                std::swap(heap[i], heap[grandparent(i)]);
            i = grandparent(i);
        }
    }

    /****Recursive Version****/
    /*
    if (i == 0) return;

    idx par_i = parent(i);
    if (heap[i] > heap[par_i]) {
        std::swap(heap[i], heap[par_i]);
        bubbleMax(par_i);
    }
    else {
        if (i > 2) {
            if (heap[i] < heap[grandp_i]) {
                std::swap(heap[i], heap[grandp_i]);
                bubbleMin(grandp_i);
            }
        }
    }
    */
}

template <typename T>
void MinMaxHeap<T>::bubbleMax(idx i)
{
    if (i == 1 || i == 2) {
        if (heap[i] < heap[0])
            std::swap(heap[i], heap[0]);
        return;
    }

    idx par_i = parent(i);

    if (heap[i] > heap[par_i]) {
        while (i != 1 && i != 2) {
            if (heap[i] > heap[grandparent(i)])
                std::swap(heap[i], heap[grandparent(i)]);
            i = grandparent(i);
        }
    }

    if (heap[i] < heap[par_i]) {
        std::swap(heap[i], heap[par_i]);
        i = parent(i);
        while (i != 0) {
            if (heap[i] < heap[grandparent(i)])
                std::swap(heap[i], heap[grandparent(i)]);
            i = grandparent(i);
        }
    }

    /****Recursive Version****/
    /*
    idx par_i = parent(i);
    if (heap[i] < heap[par_i]) {
        std::swap(heap[i], heap[par_i]);
        bubbleMin(par_i);
    }
    else {
        if (i > 2) {
            idx grandp_i = grandparent(i);
            if (heap[i] > heap[grandp_i]) {
                std::swap(heap[i], heap[grandp_i]);
                bubbleMax(grandp_i);
            }
        }
    }
    */
}

template <typename T>
void MinMaxHeap<T>::percolateMin(idx i)
{
    if (left(i) < heap.size()) {
        idx minDescendant = getMinDescendant(i);

        if (heap[i] > heap[minDescendant])
            std::swap(heap[i], heap[minDescendant]);
        if (minDescendant >= left(left(i))) {
            if (heap[minDescendant] > heap[parent(minDescendant)])
                std::swap(heap[minDescendant], heap[parent(minDescendant)]);
            percolateMin(minDescendant);
        }

    }
}

template <typename T>
void MinMaxHeap<T>::percolateMax(idx i)
{
    if (left(i) < heap.size()) {
        idx maxDescendant = getMaxDescendant(i);

        if (heap[i] < heap[maxDescendant])
            std::swap(heap[i], heap[maxDescendant]);
        if (maxDescendant >= left(left(i))){
            if (heap[maxDescendant] < heap[parent(maxDescendant)])
                std::swap(heap[maxDescendant], heap[parent(maxDescendant)]);
            percolateMax(maxDescendant);
        }
    }

}

template <typename T>
idx MinMaxHeap<T>::getMinDescendant(idx i) const
{
    idx minchild;

    if (right(i) < heap.size())
        minchild = (heap[left(i)] <= heap[right(i)]) ? left(i) : right(i);
    else
        minchild = left(i);

    if (left(left(i)) < heap.size()) {
        if (heap[minchild] >= heap[getMinGrandChild(i)]) return getMinGrandChild(i);
        return minchild;
    }
    else {
        return minchild;
    }
}

template <typename T>
idx MinMaxHeap<T>::getMaxDescendant(idx i) const
{
    idx maxchild;

    if (right(i) < heap.size())
        maxchild = (heap[left(i)] >= heap[right(i)]) ? left(i) : right(i);
    else
        maxchild = left(i);

    if (left(left(i)) < heap.size()) {
        if (heap[maxchild] <= heap[getMaxGrandChild(i)]) return getMaxGrandChild(i);
        return maxchild;
    }
    else {
        return maxchild;
    }
}

template <typename T>
idx MinMaxHeap<T>::getMinGrandChild(idx i) const
{
    idx leftGrandChild = left(left(i));
    idx rightGrandChild = right(right(i));
    idx min = leftGrandChild;

    for (idx j = leftGrandChild + 1; j < heap.size() && j <= rightGrandChild; ++j)
        if (heap[j] < heap[min])
            min = j;
    return min;
}

template <typename T>
idx MinMaxHeap<T>::getMaxGrandChild(idx i) const
{
    idx leftGrandChild = left(left(i));
    idx rightGrandChild = right(right(i));
    idx max = leftGrandChild;

    for (idx j = leftGrandChild + 1; j < heap.size() && j <= rightGrandChild; ++j)
        if (heap[j] > heap[max])
            max = j;
    return max;
}

template <typename T>
bool MinMaxHeap<T>::checkInvariant() const noexcept
{
    bool flag = true;

    for (int i = 0; left(i) < heap.size(); ++i) {
        if (isMaxLevel(i)) {
            if (heap[i] >= heap[getMaxDescendant(i)])
                flag = flag && true;
            else flag = flag && false;
        }
        else {
            if(heap[i] <= heap[getMinDescendant(i)])
                flag = flag && true;
            else flag = flag && false;
        }
    }
    return flag;
}

template<typename T>
void MinMaxHeap<T>::buildMinMaxHeap(std::vector<T> v) {
    heap = v;
    for(int i = heap.size() / 2; i >= 0; i--) {
        if(isMaxLevel(i)) {
            percolateMax(i);
        } else {
            percolateMin(i);
        }
    }

}

