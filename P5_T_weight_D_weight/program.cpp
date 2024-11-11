#include<bits/stdc++.h>
using namespace std;

// Calculate total weight percentage
double calculate_total_weight(double a_value, double b_value) {
    if (a_value + b_value == 0) {
        return 0;
    }
    return (a_value / (a_value + b_value)) * 100;
}

// Calculate direct weight percentage
double calculate_direct_weight(double current_value, double total) {
    if (total == 0) {
        return 0;
    }
    return (current_value / total) * 100;
}

// Read data from CSV
bool read_from_csv(const string& filename, 
                   vector<string>& regions, 
                   vector<double>& values_a, 
                   vector<double>& values_b) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Error opening the file " << filename << endl;
        return false;
    }

    string line, region, str_a, str_b;
    
    // Skip header
    getline(file, line);
    
    // Read data
    while (getline(file, line)) {
        stringstream ss(line);
        
        // Read region
        getline(ss, region, ',');
        
        // Read values
        getline(ss, str_a, ',');
        getline(ss, str_b);
        
        regions.push_back(region);
        values_a.push_back(stod(str_a));
        values_b.push_back(stod(str_b));
    }

    file.close();
    return true;
}

// Write results to CSV
bool write_to_csv(const string& filename, 
                  const vector<string>& regions, 
                  const vector<double>& t_wt_a, 
                  const vector<double>& t_wt_b,
                  const vector<double>& d_wt_a, 
                  const vector<double>& d_wt_b) {
    ofstream file(filename);
    if (!file.is_open()) {
        cout << "Error writing to file " << filename << endl;
        return false;
    }

    // Write header
    file << "Region,t_wt_A %,t_wt_B %,d_wt_A %,d_wt_B %" << endl;

    // Write data
    for (size_t i = 0; i < regions.size(); ++i) {
        file << regions[i] << ","
             << fixed << setprecision(2)
             << "\t\t" << t_wt_a[i] << ","
             << "\t" << t_wt_b[i] << ","
             << "\t" << d_wt_a[i] << ","
             << "\t" << d_wt_b[i] << endl;
    }

    file.close();
    return true;
}

int main() {
    string input_filename = "Input.csv";
    vector<string> regions;
    vector<double> values_a, values_b;

    // Read input file
    if (!read_from_csv(input_filename, regions, values_a, values_b)) {
        return 1;
    }

    // Calculate total weights
    vector<double> t_wt_a, t_wt_b;
    for (size_t i = 0; i < values_a.size(); ++i) {
        t_wt_a.push_back(calculate_total_weight(values_a[i], values_b[i]));
        t_wt_b.push_back(calculate_total_weight(values_b[i], values_a[i]));
    }

    // Calculate total sums
    double total_a = accumulate(values_a.begin(), values_a.end(), 0.0);
    double total_b = accumulate(values_b.begin(), values_b.end(), 0.0);

    // Calculate direct weights
    vector<double> d_wt_a, d_wt_b;
    for (const auto& a : values_a) {
        d_wt_a.push_back(calculate_direct_weight(a, total_a));
    }
    for (const auto& b : values_b) {
        d_wt_b.push_back(calculate_direct_weight(b, total_b));
    }

    // Write output file
    string output_filename = "Output.csv";
    if (!write_to_csv(output_filename, regions, t_wt_a, t_wt_b, d_wt_a, d_wt_b)) {
        return 1;
    }

    return 0;
}