#include<bits/stdc++.h>
using namespace std;

struct Data {
    map<string, string> attrs;
};

vector<Data> readCSV(const string& fileName) {
    vector<Data> data;
    ifstream file(fileName);
    string line;
    
    vector<string> headers;
    if (getline(file, line)) {
        stringstream ss(line);
        string header;
        while (getline(ss, header, ',')) {
            headers.push_back(header);
        }
    }
    
    while (getline(file, line)) {
        Data row;
        stringstream ss(line);
        string value;
        int i = 0;
        while (getline(ss, value, ',')) {
            row.attrs[headers[i]] = value;
            i++;
        }
        data.push_back(row);
    }
    
    return data;
}

// Calculate Gini impurity for a specific subset of data
double calcGiniImpurity(const vector<Data>& subset, const string& target) {
    if (subset.empty()) return 0.0;
    
    map<string, int> classCount;
    for (const auto& item : subset) {
        classCount[item.attrs.at(target)]++;
    }
    
    double gini = 1.0;
    for (const auto& pair : classCount) {
        double prob = static_cast<double>(pair.second) / subset.size();
        gini -= prob * prob;
    }
    
    return gini;
}

// Calculate weighted Gini index for an attribute
double calcWeightedGini(const vector<Data>& data, const string& attr, const string& target) {
    // Group data by attribute values
    map<string, vector<Data>> splits;
    for (const auto& item : data) {
        splits[item.attrs.at(attr)].push_back(item);
    }
    
    // Calculate weighted average of Gini impurities
    double weightedGini = 0.0;
    for (const auto& split : splits) {
        double weight = static_cast<double>(split.second.size()) / data.size();
        double giniImpurity = calcGiniImpurity(split.second, target);
        weightedGini += weight * giniImpurity;
    }
    
    return weightedGini;
}

int main() {
    string fileName = "input.csv";
    vector<Data> data = readCSV(fileName);
    
    cout << "attributes: ";
    bool first = true;
    for (const auto& pair : data[0].attrs) {
        if (!first) cout << ", ";
        cout << pair.first;
        first = false;
    }
    cout << endl;
    
    string target;
    cout << "enter target attribute: ";
    getline(cin, target);
    
    cout << "sample data row: " << endl;
    for (const auto& pair : data[1].attrs) {
        cout << pair.first << ": " << pair.second << ", ";
    }
    cout << endl;
    
    ofstream outFile("output.txt");
    
    // Calculate and output Gini gain for each attribute
    double parentGini = calcGiniImpurity(data, target);
    cout << "Parent Gini Impurity: " << parentGini << endl;
    outFile << "Parent Gini Impurity: " << parentGini << endl;
    
    for (const auto& pair : data[0].attrs) {
        if (pair.first != target) {
            double weightedGini = calcWeightedGini(data, pair.first, target);
            double giniGain = parentGini - weightedGini;
            
            cout << "Attribute: " << pair.first << endl;
            cout << "Weighted Gini: " << weightedGini << endl;
            cout << "Gini Gain: " << giniGain << endl << endl;
            
            outFile << "Attribute: " << pair.first << endl;
            outFile << "Weighted Gini: " << weightedGini << endl;
            outFile << "Gini Gain: " << giniGain << endl << endl;
        }
    }
    
    outFile.close();
    return 0;
}