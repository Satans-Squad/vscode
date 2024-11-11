#include<bits/stdc++.h>
using namespace std;

class RowData{
    public:
    map<string,string> mp;
};

vector<string> split(const string& str, char delim) {
    vector<string> tokens;
    stringstream ss(str);
    string token;
    while (getline(ss, token, delim)) {
        tokens.push_back(token);
    }
    return tokens;
}


vector<RowData> read(){
    vector<RowData> result;

    ifstream inpFile("./input.csv");

    vector<string> headers;

    string header;

    getline(inpFile,header);

    headers=split(header,',');

    string line;
    while(getline(inpFile,line)){
        vector<string> values=split(line,',');
        RowData d;
        for(int i=0;i<headers.size();i++){
            d.mp[headers[i]]=values[i];
        }
        result.push_back(d);
    }

    return result;
}

double calc_entro(vector<RowData>& d,string target){
    map<string,int> freq;

    for(auto it:d){
        freq[it.mp[target]]++;
    }

    double entropy=0.0;
    double dataSize=static_cast<double>(d.size());

    for(auto it:freq){
        double prob=it.second/dataSize;
        entropy-=prob*log2(prob);
    }

    return entropy;
}

double gain(vector<RowData>& data,string attr,string target){
    map<string,int> freq;

    for(auto it:data){
        freq[it.mp[attr]]++;
    }

    double subsetEntropy=0.0;

    for(auto it:freq){
        vector<RowData> subset;

        for(auto t:data){
            if(t.mp[attr]==it.first){
                subset.push_back(t);
            }
        }

        double prob=(double)subset.size()/data.size();
        subsetEntropy+=prob * calc_entro(subset,target);
    }

    double total_entro=calc_entro(data,target);
    return total_entro-subsetEntropy;
}

map<string,double> infoGain(vector<RowData>& data,string target){

    map<string,double> result;

    for(auto it:data[0].mp){
        if(it.first!=target){
            result[it.first]=gain(data,it.first,target);
        }
    }

    return result;
}

int main(){
    vector<RowData> data=read();

    string target="play";

    map<string,double> result=infoGain(data,target);

    for(auto it:result){
        cout<<it.first<<" "<<it.second<<endl;
    }
}