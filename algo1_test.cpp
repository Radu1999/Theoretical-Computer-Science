#include "algo1.cpp"

int main() {

    int n, rank, k;
    std::cin >> n;
    std::vector<int> ranks;

    for(int i = 0; i < n; i++) {
        std::cin >> rank;
        ranks.push_back(rank);
    }
    MinMaxHeap<int> heap;
    heap.buildMinMaxHeap(ranks);

    std::cin >> k;
    int operation, type;
    for(int i = 0; i < k; i++) {
        std::cin >> operation;
        if(operation == 1) {
            std::cin >> rank;
            heap.insert(rank);
        } else if(operation == 2) {
            std::cin >> type;
            type ? heap.deleteMax() : heap.deleteMin();
        } else if(operation == 3){
            std::cout << heap.getMin() << "\n";
        } else {
            std::cout << heap.getMax() << "\n";
        }
    }
    return 0;
}
