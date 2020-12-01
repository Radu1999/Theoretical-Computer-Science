#include "algo2.h"

int main() {
    RBTree rbTree;
    int n, k, rank;
    ofstream f;
    cin >> n;
    for(int i = 0; i < n; i++) {
        cin >> rank;
        rbTree.insert(rank);
    }
    cin >> k;
    int operation, type;
    for(int i = 0; i < k; i++) {
        cin >> operation;
        if(operation == 1) {
            cin >> rank;
            rbTree.insert(rank);
        } else if(operation == 2) {
            cin >> type;
            if(type == 0) {
               rbTree.deleteMin();
            } else {
               rbTree.deleteMax();
            }
        } else if(operation == 3) {
            cout << rbTree.getMin() << "\n";
        } else if(operation == 4) {
            cout << rbTree.getMax() << "\n";
        }
    }
    return 0;
}
