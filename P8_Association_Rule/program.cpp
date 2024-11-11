#include <bits/stdc++.h>

using namespace std;

// Function to get all combinations of size r from set s
vector<set<string>> getCombinations(set<string>& s, int r) {
    vector<set<string>> combinations;
    vector<string> v(s.begin(), s.end());
    vector<bool> bitmask(v.size() - r, 0);
    bitmask.resize(v.size(), 1);

    do {
        set<string> combination;
        for (size_t i = 0; i < v.size(); ++i) {
            if (bitmask[i]) combination.insert(v[i]);
        }
        combinations.push_back(combination);
    } while (next_permutation(bitmask.begin(), bitmask.end()));

    return combinations;
}

// Function to calculate support count
int getSupport(const set<string>& item, const vector<set<string>>& table) {
    int count = 0;
    for (const auto& transaction : table) {
        bool isSubset = true;
        for (const auto& i : item) {
            if (transaction.find(i) == transaction.end()) {
                isSubset = false;
                break;
            }
        }
        if (isSubset) count++;
    }
    return count;
}

// Function to get set difference
set<string> setDifference(const set<string>& a, const set<string>& b) {
    set<string> diff;
    for (const auto& item : a) {
        if (b.find(item) == b.end()) {
            diff.insert(item);
        }
    }
    return diff;
}

// Function to load transaction data from CSV
vector<set<string>> loadTransactions(const string& filename) {
    vector<set<string>> table;
    ifstream file(filename);
    string line;
    
    // Skip header
    getline(file, line);
    
    while (getline(file, line)) {
        stringstream ss(line);
        string item;
        set<string> transaction;
        
        while (getline(ss, item, ',')) {
            if (!item.empty()) {
                transaction.insert(item);
            }
        }
        
        if (!transaction.empty()) {
            table.push_back(transaction);
        }
    }
    
    return table;
}

// Main function to generate association rules
void generateAssociationRules(const set<string>& frequent_itemset, 
                            const vector<set<string>>& table, 
                            double min_confidence) {
    vector<tuple<set<string>, set<string>, double>> rules;
    int support_count = getSupport(frequent_itemset, table);
    
    if (support_count == 0) {
        cout << "Error: The provided frequent itemset has a support count of 0" << endl;
        return;
    }
    
    for (int i = 1; i < frequent_itemset.size(); i++) {
        vector<set<string>> combinations = getCombinations(const_cast<set<string>&>(frequent_itemset), i);
        
        for (const auto& antecedent : combinations) {
            set<string> consequent = setDifference(frequent_itemset, antecedent);
            int antecedent_support = getSupport(antecedent, table);
            
            if (antecedent_support > 0) {
                double confidence = (static_cast<double>(support_count) / antecedent_support) * 100;
                
                if (confidence >= min_confidence) {
                    rules.push_back(make_tuple(antecedent, consequent, confidence));
                }
            }
        }
    }
    
    // Print results
    if (!rules.empty()) {
        cout << "\nAssociation rules (minimum confidence: " << min_confidence << "%)" << endl;
        cout << "Format: {IF} -> {THEN}" << endl;
        cout << "Rule                                   Confidence" << endl;
        cout << "--------------------------------------------------" << endl;
        
        for (const auto& rule : rules) {
            cout << "{";
            for (const auto& item : get<0>(rule)) {
                cout << item << ",";
            }
            cout << "\b} -> {";
            
            for (const auto& item : get<1>(rule)) {
                cout << item << ",";
            }
            cout << "\b}   " << fixed << setprecision(2) << get<2>(rule) << "%" << endl;
        }
    } else {
        cout << "\nNo association rules found with confidence >= " << min_confidence << "%" << endl;
    }
}

int main() {
    double min_confidence;
    
    // Get minimum confidence from user
    while (true) {
        cout << "Enter minimum confidence threshold (%): ";
        if (cin >> min_confidence && min_confidence >= 0 && min_confidence <= 100) {
            break;
        }
        cout << "Please enter a value between 0 and 100" << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    
    // Load transaction data
    vector<set<string>> table = loadTransactions("Transaction.csv");
    if (table.empty()) {
        cout << "Error: No transactions loaded" << endl;
        return 1;
    }
    
    // Read frequent itemset from Input.csv
    set<string> frequent_itemset;
    ifstream input_file("Input.csv");
    string item;
    
    while (getline(input_file, item, ',')) {
        if (!item.empty()) {
            frequent_itemset.insert(item);
        }
    }
    
    cout << "\nFrequent itemset: {";
    for (const auto& item : frequent_itemset) {
        cout << item << ",";
    }
    cout << "\b}" << endl;
    
    // Generate and display association rules
    generateAssociationRules(frequent_itemset, table, min_confidence);
    
    return 0;
}