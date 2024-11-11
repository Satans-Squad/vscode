#include<bits/stdc++.h>
using namespace std;

// Function to get support count for an itemset
int getSupport(const set<string>& item, const vector<set<string>>& table) {
    int count = 0;
    for (const auto& transaction : table) {
        if (includes(transaction.begin(), transaction.end(), item.begin(), item.end())) {
            count++;
        }
    }
    return count;
}

// Function to generate candidate itemsets
set<set<string>> generateCandidates(const vector<set<string>>& prevFrequentItemsets, int k) {
    set<set<string>> candidates;
    for (int i = 0; i < prevFrequentItemsets.size(); i++) {
        for (int j = i + 1; j < prevFrequentItemsets.size(); j++) {
            set<string> candidate(prevFrequentItemsets[i]);
            candidate.insert(prevFrequentItemsets[j].begin(), prevFrequentItemsets[j].end());
            if (candidate.size() == k) {
                candidates.insert(candidate);
            }
        }
    }
    return candidates;
}

// Function to run the Apriori algorithm
void apriori(const vector<set<string>>& table, double minSup) {
    int n = table.size();
    int minSupCount = static_cast<int>(minSup * n / 100.0);
    cout << "Minimum support count: " << minSupCount << endl;

    vector<set<string>> frequentItemsets;
    set<set<string>> oneItemFrequentItemsets;

    // Find frequent 1-itemsets
    for (const auto& transaction : table) {
        for (const auto& item : transaction) {
            oneItemFrequentItemsets.insert({item}); // show only single items
        }
    }

    for (const auto& item : oneItemFrequentItemsets) {
        int support = getSupport(item, table);
        if (support >= minSupCount) {
            frequentItemsets.push_back(item);
            cout << "Frequent 1-itemset: {";
            for (const auto& i : item) {
                cout << i << ", ";
            }
            cout << "}, Support count: " << support << endl;
        }
    }

    int k = 2;
    set<set<string>> topThreeItemset;
    while (!oneItemFrequentItemsets.empty()) {
        auto candidates = generateCandidates(frequentItemsets, k);
        vector<set<string>> kItemFrequentItemsets;

        for (const auto& candidate : candidates) {
            int support = getSupport(candidate, table);
            if (support >= minSupCount) {
                kItemFrequentItemsets.push_back(candidate);
                cout << "Frequent " << k << "-itemset: {";
                for (const auto& item : candidate) {
                    cout << item << ", ";
                }
                cout << "}, Support count: " << support << endl;

                if (k == 3 && (topThreeItemset.empty() || support > getSupport(*topThreeItemset.begin(), table))) {
                    topThreeItemset = {candidate};
                }
            }
        }

        frequentItemsets = move(kItemFrequentItemsets);
        oneItemFrequentItemsets = move(candidates);
        k++;
    }

    if (!topThreeItemset.empty()) {
        ofstream output("output.csv");
        for (const auto& item : *topThreeItemset.begin()) {
            output << item << ",";
        }
        output.seekp(-1, ios_base::end);
        output << endl;
        output.close();
        cout << "Top 3 frequent itemset written to output.csv" << endl;
    }
}

int main() {
    string filePath = "Transaction.csv";
    double minSup;
    cout << "Enter minimum support percentage: ";
    cin >> minSup;

    vector<set<string>> table;
    ifstream file(filePath);
    string line;
    getline(file, line); // Skip header

    while (getline(file, line)) {
        set<string> transaction;
        stringstream ss(line);
        string item;
        while (getline(ss, item, ',')) {
            transaction.insert(item);
        }
        table.push_back(transaction);
    }

    apriori(table, minSup);

    return 0;
}