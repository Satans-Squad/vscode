#include<bits/stdc++.h>

using namespace std;

// Class to store data attributes
class Data {
public:
    map<string, string> attrs;
};

// Function to split string by delimiter
vector<string> split(const string& str, char delim) {
    vector<string> tokens;
    stringstream ss(str);
    string token;
    while (getline(ss, token, delim)) {
        tokens.push_back(token);
    }
    return tokens;
}

// Function to read CSV file
vector<Data> read_csv(const string& file_name) {
    vector<Data> data;
    ifstream file(file_name);
    
    if (!file.is_open()) {
        cout << "Error occurred " << file_name << endl;
        return data;
    }

    string line;
    vector<string> headers;
    
    // Read headers
    if (getline(file, line)) {
        headers = split(line, ',');
    }
    
    // Read data
    while (getline(file, line)) {
        vector<string> values = split(line, ',');
        if (values.size() == headers.size()) {
            Data d;
            for (size_t i = 0; i < headers.size(); i++) {
                d.attrs[headers[i]] = values[i];
            }
            data.push_back(d);
        }
    }
    
    file.close();
    return data;
}

// Calculate entropy
double calc_entropy(const vector<Data>& data, const string& target) {
    map<string, int> freq;
    
    // Calculate frequency
    for (const auto& d : data) {
        freq[d.attrs.at(target)]++;
    }
    
    double entropy = 0.0;
    double data_size = static_cast<double>(data.size());
    
    // Calculate entropy
    for (const auto& f : freq) {
        double prob = f.second / data_size;
        entropy -= prob * log2(prob);
    }
    
    return entropy;
}

// Calculate information gain
double calc_gain(const vector<Data>& data, const string& attr, const string& target) {
    map<string, int> freq;
    
    // Calculate frequency of attribute values
    for (const auto& d : data) {
        freq[d.attrs.at(attr)]++;
    }
    
    double subset_entropy = 0.0;
    double data_size = static_cast<double>(data.size());
    
    // Calculate entropy for each subset
    for (const auto& f : freq) {
        vector<Data> subset;
        for (const auto& d : data) {
            if (d.attrs.at(attr) == f.first) {
                subset.push_back(d);
            }
        }
        double prob = subset.size() / data_size;
        subset_entropy += prob * calc_entropy(subset, target);
    }
    
    double total_entropy = calc_entropy(data, target);
    return total_entropy - subset_entropy;
}

// Calculate gains for all attributes
map<string, double> calculate_all_gains(const vector<Data>& data, const string& target) {
    map<string, double> gains;
    
    // Get all attributes except target
    for (const auto& attr : data[0].attrs) {
        if (attr.first != target) {
            gains[attr.first] = calc_gain(data, attr.first, target);
        }
    }
    
    return gains;
}

int main() {
    string file_name = "input.csv";
    vector<Data> data = read_csv(file_name);
    
    if (data.empty()) {
        cout << "Error" << endl;
        return 1;
    }
    
    string target;
    cout << "Enter the target attribute: ";
    cin >> target;
    
    map<string, double> gains = calculate_all_gains(data, target);
    
    // Sort gains by value
    vector<pair<string, double>> sorted_gains(gains.begin(), gains.end());
    sort(sorted_gains.begin(), sorted_gains.end(),
         [](const auto& a, const auto& b) { return a.second > b.second; });
    
    // Write results to file
    ofstream out_file("Output.txt");
    if (!out_file.is_open()) {
        cout << "Error opening the file" << endl;
        return 1;
    }
    
    out_file << "Info gain for all attributes:\n";
    for (const auto& gain : sorted_gains) {
        out_file << gain.first << ": " << fixed << setprecision(6) << gain.second << "\n";
    }
    
    out_file.close();
    return 0;
}