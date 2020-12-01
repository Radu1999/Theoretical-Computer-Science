#include <bits/stdc++.h>
using namespace std;

int main() {

    ifstream inFile;
    ofstream outFile;
    string filename = "in/test";
    string filenameOut = "out/test";
    int n, k, rank, operation, type;
    for(int i = 1; i <= 20; i++) {
        vector<int> sorted_vector;
        inFile.open(filename + to_string(i) + ".in");
        outFile.open(filenameOut + to_string(i) + ".out");
        inFile >> n;
        for(int j = 0; j < n ; j++) {
            inFile >> rank;
            sorted_vector.push_back(rank);
        }
        sort(sorted_vector.begin(), sorted_vector.end());
        inFile >> k;
        for(int j = 0; j < k; j++) {
            inFile >> operation;
            if(operation == 1) {
                inFile >> rank;
                sorted_vector.insert(lower_bound(sorted_vector.begin(), sorted_vector.end(), rank), rank);
            } else if (operation == 2) {
                inFile >> type;
                if(type == 0) {
                    sorted_vector.erase(sorted_vector.begin());
                } else {
                    sorted_vector.erase(sorted_vector.end() - 1);
                }
            } else if (operation == 3) {
                outFile << sorted_vector[0] << "\n";
            } else {
                outFile << sorted_vector[sorted_vector.size() - 1] << "\n";
            }
        }
        inFile.close();
        outFile.close();

    }
    return 0;
}
