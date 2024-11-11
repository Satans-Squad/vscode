#include<bits/stdc++.h>
using namespace std;
class DataSet{
    public:
        unordered_map<string, string> mp;
        DataSet() {};
};
void classify(vector<DataSet>& data,vector<string>& instances,string target){
    int n = data.size();
    pair<double, double> p_target;
    unordered_map<string, int> freq;
    for(DataSet d:data){
        for(auto i:d.mp){
            if(i.first==target){
                freq[i.second]++;
            }
        }
    }
    p_target.first=((double)freq["Yes"]/n);
    p_target.second=((double)freq["No"]/n);
    double p_yes = 1, p_no = 1;
    for(string str:instances){
        unordered_map<string, int> mp1;
        for(DataSet d:data){
            for(auto i:d.mp){
                if(i.second==str){
                    mp1[d.mp[target]]++;
                }
            }
        }
        p_yes *= ((double)mp1["Yes"]/freq["Yes"]);
        p_no *= ((double)mp1["No"]/freq["No"]);
    }
    p_yes *= p_target.first;
    p_no *= p_target.second;
    cout << "\nP(YES)= " << p_yes<<endl;
    cout << "\nP(NO)= " << p_no<<endl;
    cout << "New Instance(";
    for(string str:instances){
        cout << str << ",";
    }
    cout << ")= " << ((p_yes > p_no) ? "Yes" : "No");
}
int main(){
    ifstream in("input.csv");
    string line;
    getline(in, line);
    vector<string> header;
    stringstream ss(line);
    string temp;
    while(getline(ss,temp,',')){
        header.push_back(temp);
    }
    vector<DataSet> data;
    while(getline(in,line)){
        DataSet d;
        stringstream ss1(line);
        string temp;
        vector<string> v;
        while(getline(ss1,temp,',')){
            v.push_back(temp);
        }
        for (int i = 0; i < header.size();i++){
            d.mp[header[i]] = v[i];
        }
        data.push_back(d);
    }
    string target=header.back();
    header.pop_back();
    cout << "\nEnter no. of instances: " << endl;
    int n;
    cin >> n;
    cout << "\nEnter instances: " << endl;
    vector<string> instances;
    for (int i = 0; i < n;i++){
        string attr;
        cin >> attr;
        instances.push_back(attr);
    }
    classify(data, instances, target);
    return 0;
}