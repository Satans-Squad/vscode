#include<bits/stdc++.h>
using namespace std;

int getSupport(set<string>& item,vector<set<string>>& table){
    int count=0;

    // check if the item
    for(auto transaction:table){
        if(includes(transaction.begin(),transaction.end(),item.begin(),item.end())){
            count++;
        }
    }

    return count;
}

set<set<string>> generateCandidates(vector<set<string>>& prevFreqItemset,int k){
    set<set<string>> candidatessss;

    for(int i=0;i<prevFreqItemset.size();i++){
        for(int j=i+1;j<prevFreqItemset.size();j++){
            set<string> candidate(prevFreqItemset[i]);
            candidate.insert(prevFreqItemset[j].begin(),prevFreqItemset[j].end());

            if(candidate.size()==k){
                candidatessss.insert(candidate);
            }
        }
    }

    return candidatessss;
}

void apriori(vector<set<string>>& table, double minSup){
    int n=table.size();
    int minSupCount=static_cast<int>(minSup*n/100.0);

    vector<set<string>> freqItemset;
    set<set<string>> oneItemFreqItemset;

    // find frequent itemset for unique items all over the table
    for(auto transaction:table){
        for(auto item:transaction){
            oneItemFreqItemset.insert({item}); //inset as single set as it is set of string
        }
    }

    for(auto item:oneItemFreqItemset){
        int support=getSupport(item,table);

        if(support>=minSup){
            freqItemset.push_back(item);

            cout << "Frequent 1-itemset: {";
            for (const auto& i : item) {
                cout << i << ", ";
            }
            cout << "}, Support count: " << support << endl;
        }
    }

    int k=2;

    set<set<string>> topThreeItemset;

    while(!oneItemFreqItemset.empty()){
        auto candidates=generateCandidates(freqItemset,k);

        vector<set<string>> kItemFrequentItemSet;

        for(auto candidate:candidates){
            int support=getSupport(candidate,table);

            if(support>=minSup){
                kItemFrequentItemSet.push_back(candidate);
                
                cout << "Frequent " << k << "-itemset: {";
                for (const auto& item : candidate) {
                    cout << item << ", ";
                }
                cout << "}, Support count: " << support << endl;

                
            }
        }

        freqItemset=move(kItemFrequentItemSet);
        oneItemFreqItemset=move(candidates);
        k++;

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

int main(){
    string inp="./Transaction.csv";
    double minSup;

    cout<<"Enter min support: "<<endl;
    cin>>minSup;

    //unique items out of every transaction
    vector<set<string>> table; 
    ifstream inpFile(inp);
    string line;
    getline(inpFile,line); //skip the header

    while(getline(inpFile,line)){
        set<string> transaction;

        stringstream ss(line);
        string item;

        while(getline(ss,item,',')){
            transaction.insert(item);
        }

        // insert the unique items per transaction ---- 1
        table.push_back(transaction);
    }

}