#include<bits/stdc++.h>

using namespace std;

double calculate_mean(vector<double>& values) {
    double sum = 0.0;
    for (double value : values) {
        sum += value;
    }
    return sum / values.size();
}

double calculate_stddev(vector<double>& values, double mean) {
    double sum_squared_diff = 0.0;
    for (double value : values) {
        double diff = value - mean;
        sum_squared_diff += diff * diff;
    }
    return sqrt(sum_squared_diff / (values.size() - 1));
}

vector<double> calculate_zscore(vector<double>& values) {
    double mean = calculate_mean(values);
    double std_dev = calculate_stddev(values, mean);
    
    std::vector<double> z_scores;
    for (double value : values) {
        z_scores.push_back((value - mean) / std_dev);
    }
    return z_scores;
}

int main() {
    std::vector<int> ids;
    std::vector<double> values;
    
    std::ifstream infile("../../dataset.csv");
    if (!infile.is_open()) {
        std::cerr << "Error opening input file!" << std::endl;
        return 1;
    }
    
    std::string header;
    std::getline(infile, header);
    
    std::string line;
    while (std::getline(infile, line)) {
        stringstream ss(line);
        string id_str, value_str;
        
        getline(ss, id_str, ',');
        getline(ss, value_str, ',');
        
        try {
            ids.push_back(std::stoi(id_str));
            values.push_back(std::stod(value_str));
        } catch (const std::exception& e) {
            std::cerr << "Error parsing line: " << line << std::endl;
            continue;
        }
    }
    
    infile.close();
    
    std::vector<double> normalized = calculate_zscore(values);
    
    std::ofstream outfile("output.csv");
    outfile << "ID,Original,Normalized\n";
    
    for (size_t i = 0; i < values.size(); i++) {
        outfile << ids[i] << "," << values[i] << "," << normalized[i] << "\n";
    }
    
    outfile.close();        
    return 0;
}