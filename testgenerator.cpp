#include <bits/stdc++.h>
using namespace std;

int main() {
    string fileName = "test";
    ofstream file;
    int n, k, op;
    for(int i = 1; i <= 20; i++) {
        string newFile = fileName + to_string(i) + ".in";
        file.open(newFile);
        n = rand() + 1000;
        file << n << "\n";
        for(int j = 0; j < n; j++) {
            file << rand() << " ";
        }
        file << "\n";
        k = rand();
        file << k << "\n";
        for(int j = 0; j < k; j++) {
            op = rand() % 4 + 1;
            file << op;
            if(op == 1) {
                file << " " << rand() << "\n";
            } else if(op == 2) {
                file << " " << rand() % 2 << "\n";
            } else {
                file << "\n";
            }
        }
        file.close();

    }
    return 0;
}
