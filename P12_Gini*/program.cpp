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

// Calculate simple Gini index for any attribute
double calcGini(const vector<Data>& data, const string& attr) {
    map<string, int> freq;
    double gini = 1.0;
    
    for (const auto& item : data) {
        string value = item.attrs.at(attr);
        freq[value]++;
    }
    
    for (const auto& pair : freq) {
        double prob = static_cast<double>(pair.second) / data.size();
        gini -= prob * prob;
    }
    
    return gini;
}

void printAttributeValues(const vector<Data>& data) {
    cout << "\nDataset values:" << endl;
    for (const auto& pair : data[0].attrs) {
        cout << pair.first << ": ";
        set<string> uniqueValues;
        for (const auto& row : data) {
            uniqueValues.insert(row.attrs.at(pair.first));
        }
        for (const auto& value : uniqueValues) {
            cout << value << " ";
        }
        cout << endl;
    }
    cout << endl;
}

int main() {
    string fileName = "input.csv";
    vector<Data> data = readCSV(fileName);
    
    cout << "Attributes: ";
    bool first = true;
    for (const auto& pair : data[0].attrs) {
        if (!first) cout << ", ";
        cout << pair.first;
        first = false;
    }
    cout << endl;
    
    printAttributeValues(data);
    
    string target;
    cout << "Enter target attribute: ";
    getline(cin, target);
    
    // Calculate parent Gini index once
    double parentGini = calcGini(data, target);
    cout << "\nParent Gini Index: " << parentGini << endl << endl;
    
    ofstream outFile("output.txt");
    outFile << "Parent Gini Index: " << parentGini << endl;
    
    // Track best splitting attribute
    string bestAttr;
    double bestGain = -1;
    
    for (const auto& pair : data[0].attrs) {
        if (pair.first != target) {
            double attrGini = calcGini(data, pair.first);
            double gain = parentGini - attrGini;
            
            cout << "Attribute: " << pair.first << endl;
            cout << "Gini Index: " << attrGini << endl;
            cout << "Gini Gain: " << gain << endl << endl;
            
            outFile << "Attribute: " << pair.first << endl;
            outFile << "Gini Index: " << attrGini << endl;
            outFile << "Gini Gain: " << gain << endl << endl;
            
            if (gain > bestGain) {
                bestGain = gain;
                bestAttr = pair.first;
            }
        }
    }
    
    cout << "\nBest splitting attribute: " << bestAttr << " (Gain = " << bestGain << ")" << endl;
    outFile << "\nBest splitting attribute: " << bestAttr << " (Gain = " << bestGain << ")" << endl;
    
    outFile.close();
    return 0;
}