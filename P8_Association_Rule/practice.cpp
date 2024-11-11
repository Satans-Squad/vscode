#include<bits/stdc++.h>
using namespace std;

vector<set<string>> loadTransactions(){
    vector<set<string>> result;

    ifstream inpfile("./Transaction.csv");
    string line;
    getline(inpfile,line); //skip header

    while(getline(inpfile,line)){
        set<string> transaction;

        string item;
        stringstream ss(line);
        while(getline(ss,item,',')){
            transaction.insert(item);
        }
        result.push_back(transaction);
    }

    return result;
};

int getSupport(set<string>& itemset,vector<set<string>>& table){
    int count=0;

    for(auto it:table){
        bool contains=true;

        for(auto item:itemset){
            if(it.find(item)==it.end()){
                contains=false;
                break;
            }
        }

        if(contains) count++;
    }
    return count;
};

vector<set<string>> getCombinations(set<string>& itemset,int r){
    vector<set<string>> result;

    vector<string> s(itemset.begin(),itemset.end());
    vector<bool> bitmask(itemset.size()-r,0); //{0}
    bitmask.resize(itemset.size(),1); // {0,1,1}

    do{
        set<string> combination;

        for(int i=0;i<s.size();i++){
            if(bitmask[i]) combination.insert(s[i]);
        }

        result.push_back(combination);
    } while (next_permutation(bitmask.begin(),bitmask.end()));

    return result;
}

set<string> setDiff(set<string>& freqset,set<string>& left){
    set<string> diff;

    for(auto item:freqset){
        if(left.find(item)==left.end()){
            diff.insert(item);
        }
    }

    return diff;
}

void associationRule(set<string>& freqItemset,vector<set<string>>& table,double min_confidence){
    // left side, right side, confidence
    vector<tuple<set<string>,set<string>,double>> rules;

    // get support for freqitemset
    int support_count=getSupport(freqItemset,table);

    // iterating over all the elements in the itemset
    for(int i=1;i<freqItemset.size();i++){
        vector<set<string>> combintations=getCombinations(freqItemset,i);

        for(auto left:combintations){
            set<string> right=setDiff(freqItemset,left);

            int left_support=getSupport(left,table);

            if(left_support>0){
                double confidence=(static_cast<double>(support_count)/left_support)*100;

                if(confidence>=min_confidence){
                    rules.push_back(make_tuple(left,right,confidence));
                }
            }
        }
    }


    for(auto rule:rules){
        cout<<"{";
        for(auto item:get<0>(rule)){
            cout<<item<<",";
        }
        cout<<"\b} -> {";

        for(auto item:get<1>(rule)){
            cout<<item<<",";
        }
        cout<<"\b} -> {";

        cout<<"\b}   "<<fixed<<setprecision(2)<<get<2>(rule)<<"%"<<endl;
    } 
    if(rules.empty()){
        cout << "\nNo association rules found with confidence >= " << min_confidence << "%" << endl;
    }

}

set<string> getFreqItemSet(){
    ifstream inpfile("./input.csv");

    set<string> result;

    string line;

    while(getline(inpfile,line,',')){
        result.insert(line);
    }

    return result;
}

int main(){
    double min_confidence;

    cout<<"Enter min confidence:";
    cin>>min_confidence;

    // load the transaction file data
    vector<set<string>> transactions=loadTransactions();

    set<string> freq_itemset=getFreqItemSet();

    associationRule(freq_itemset,transactions,min_confidence);

}