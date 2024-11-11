#include<bits/stdc++.h>
using namespace std;

void findClosestClusters(vector<vector<double>>& distances, int& c1, int& c2) {
    double minDist = numeric_limits<double>::infinity();
    for(int i = 0; i < distances.size(); i++) {
        for(int j = 0; j < distances[i].size(); j++) {
            if(i != j && distances[i][j] < minDist) {
                minDist = distances[i][j];
                c1 = i;
                c2 = j;
            }
        }
    }
}

void printClusters(const vector<vector<int>>& clusters) {
    for(int i = 0; i < clusters.size(); i++) {
        cout << "[";
        for(int j = 0; j < clusters[i].size(); j++) {
            cout << clusters[i][j];
            if(j < clusters[i].size() - 1) cout << ",";
        }
        cout << "]";
    }
    cout <<endl;
}

void singleLinkageClustering(vector<vector<double>>& distances) {
    vector<vector<int>> clusters;
    for(int i = 0; i < distances.size(); i++) {
        clusters.push_back({i});
    }
    
    cout << "initial clusters: ";
    printClusters(clusters);
    
    while(clusters.size() > 1) {
        int c1 = 0, c2 = 0;
        findClosestClusters(distances, c1, c2);
        
        for(int x : clusters[c2]) {
            clusters[c1].push_back(x);
        }
        clusters.erase(clusters.begin() + c2);
        
        for(int i = 0; i < distances.size(); i++) {
            if(i != c1 && i != c2) {
                double minDist = min(distances[c1][i], distances[c2][i]);
                distances[c1][i] = distances[i][c1] = minDist;
            }
        }
        distances.erase(distances.begin() + c2);
        for(auto& row : distances) {
            row.erase(row.begin() + c2);
        }
        
        cout<< c1 << "-" << c2 << ": ";
        printClusters(clusters);
    }
}

int main() {
    int n;
    cout << "enter the number of data points: ";
    cin >> n;
    
    cout << "enter the distance matrix:\n";
    vector<vector<double>> distances(n, vector<double>(n));
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            cin >> distances[i][j];
        }
    }
    
    singleLinkageClustering(distances);
    return 0;
}