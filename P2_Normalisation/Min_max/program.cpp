#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

double normalize(double x, double from_min, double from_max, double to_min, double to_max) {
    return ((x - from_min) / (from_max - from_min) * (to_max - to_min)) + to_min;
}

int main() {
    string input_file = "../../dataset.csv";
    string output_file = "output.csv";
    
    // Open input file
    ifstream file(input_file);
    if (!file.is_open()) {
        cout << "Error opening input file" << endl;
        return 1;
    }
    
    // Skip header
    string header;
    getline(file, header);
    
    // Read values
    vector<int> ids;
    vector<double> values;
    string line;
    while (getline(file, line)) {
        int id;
        double value;
        sscanf(line.c_str(), "%d,%lf", &id, &value);
        ids.push_back(id);
        values.push_back(value);
    }
    
    // Find min and max
    double min_val = values[0];
    double max_val = values[0];
    for (double v : values) {
        if (v < min_val) min_val = v;
        if (v > max_val) max_val = v;
    }
    
    // Get normalization range
    cout << "enter min-max value: ";
    double norm_min, norm_max;
    cin >> norm_min >> norm_max;
    
    // Open output file
    ofstream outfile(output_file);
    if (!outfile.is_open()) {
        cout << "Error opening output file" << endl;
        return 1;
    }
    
    // Write data
    outfile << "ID,Original,Normalized\n";
    for (int i = 0; i < values.size(); i++) {
        double normalized = normalize(values[i], min_val, max_val, norm_min, norm_max);
        outfile << ids[i] << "," << values[i] << "," << normalized << "\n";
    }
    
    cout << "Results written to " << output_file << endl;
    return 0;
}