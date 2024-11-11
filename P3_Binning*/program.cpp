#include<bits/stdc++.h>
using namespace std;

vector<int> readCSV(const string& file_name) {
    vector<int> data;
    ifstream file(file_name);
    if (file.is_open()) {
        string line;
        getline(file, line); // Skip header
        while (getline(file, line)) {
            data.push_back(stoi(line));
        }
        file.close();
    } else {
        cout << "Error opening the file " << file_name << endl;
    }
    return data;
}

void writeToFile(const string& file_name, const vector<int>& median_binned, const vector<double>& mean_binned, const vector<int>& boundaries_binned) {
    ofstream file(file_name);
    if (file.is_open()) {
        file << "Boundaries binning: " << endl;
        for (int boundary : boundaries_binned) {
            file << boundary << endl;
        }
        file << endl << "Mean binning: " << endl;
        for (double mean : mean_binned) {
            file << mean << endl;
        }
        file << endl << "Median binning: " << endl;
        for (int median : median_binned) {
            file << median << endl;
        }
        file.close();
    } else {
        cout << "Error occurred while writing to " << file_name << endl;
    }
}

vector<pair<int, int>> getBinRanges(const vector<int>& data, int num_bins) {
    if (data.empty() || num_bins <= 0) {
        return {};
    }

    int min_val = *min_element(data.begin(), data.end());
    int max_val = *max_element(data.begin(), data.end());
    double bin_width = static_cast<double>(max_val - min_val) / num_bins;
    vector<pair<int, int>> ranges;

    for (int i = 0; i < num_bins; ++i) {
        int start = static_cast<int>(min_val + i * bin_width);
        int end = static_cast<int>(min_val + (i + 1) * bin_width);
        ranges.emplace_back(start, end);
    }

    return ranges;
}

vector<vector<int>> assignToBins(const vector<int>& data, const vector<pair<int, int>>& ranges) {
    vector<vector<int>> bins(ranges.size());

    for (int value : data) {
        for (size_t i = 0; i < ranges.size(); ++i) {
            if (i == ranges.size() - 1 && ranges[i].first <= value && value <= ranges[i].second) {
                bins[i].push_back(value);
                break;
            } else if (ranges[i].first <= value && value < ranges[i].second) {
                bins[i].push_back(value);
                break;
            }
        }
    }

    return bins;
}

vector<int> binningByMedian(const vector<int>& data, int num_bins) {
    if (num_bins <= 0) {
        return data;
    }

    vector<pair<int, int>> ranges = getBinRanges(data, num_bins);
    vector<vector<int>> bins = assignToBins(data, ranges);
    vector<int> binned_data;

    for (const auto& bin_values : bins) {
        if (!bin_values.empty()) {
            sort(bin_values.begin(), bin_values.end());
            int median = bin_values[bin_values.size() / 2];
            binned_data.insert(binned_data.end(), bin_values.size(), median);
        }
    }

    return binned_data;
}

vector<double> binningByMean(const vector<int>& data, int num_bins) {
    if (num_bins <= 0) {
        return vector<double>(data.begin(), data.end());
    }

    vector<pair<int, int>> ranges = getBinRanges(data, num_bins);
    vector<vector<int>> bins = assignToBins(data, ranges);
    vector<double> binned_data;

    for (const auto& bin_values : bins) {
        if (!bin_values.empty()) {
            double mean = accumulate(bin_values.begin(), bin_values.end(), 0.0) / bin_values.size();
            binned_data.insert(binned_data.end(), bin_values.size(), mean);
        }
    }

    return binned_data;
}

vector<int> binningByBoundaries(const vector<int>& data, int num_bins) {
    if (num_bins <= 0) {
        return data;
    }

    vector<pair<int, int>> ranges = getBinRanges(data, num_bins);
    vector<vector<int>> bins = assignToBins(data, ranges);
    vector<int> binned_data;

    for (const auto& bin_values : bins) {
        if (!bin_values.empty()) {
            int min_val = *min_element(bin_values.begin(), bin_values.end());
            int max_val = *max_element(bin_values.begin(), bin_values.end());
            for (int value : bin_values) {
                binned_data.push_back(abs(value - min_val) < abs(value - max_val) ? min_val : max_val);
            }
        }
    }

    return binned_data;
}

int main() {
    string file_name = "input.csv";
    string output_file = "output.csv";
    int num_bins;
    cout << "Enter the number of bins: ";
    cin >> num_bins;

    vector<int> data = readCSV(file_name);
    if (data.empty()) {
        cout << "Error reading file" << endl;
        return 1;
    }

    vector<int> median_binned = binningByMedian(data, num_bins);
    vector<double> mean_binned = binningByMean(data, num_bins);
    vector<int> boundaries_binned = binningByBoundaries(data, num_bins);
    writeToFile(output_file, median_binned, mean_binned, boundaries_binned);

    return 0;
}