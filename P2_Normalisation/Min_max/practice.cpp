#include<bits/stdc++.h>
using namespace std;

double noramlize(double val,double min,double max,double newmax,double newmin){
    return ((val-min)/(max-min)*(newmax-newmin))+(newmin);
}

int main(){
    string inp="../../dataset.csv";
    string out="./output.csv";

    ifstream inpfile(inp);

    if(!inpfile.is_open()){
        return 1;
    }

    // skip the header
    string line;
    getline(inpfile,line);

    vector<int> ids;
    vector<double> values;

    while(getline(inpfile,line)){
        int id;
        double val;

        sscanf(line.c_str(),"%d,%lf",&id,&val);

        ids.push_back(id);
        values.push_back(val);
    }

    double min_val = values[0];
    double max_val = values[0];
    for (double v : values) {
        if (v < min_val) min_val = v;
        if (v > max_val) max_val = v;
    }
    
    cout << "enter min-max value: ";
    double norm_min, norm_max;
    cin >> norm_min >> norm_max;

    ofstream outfile(out);

    if(!outfile.is_open()) return 1;

    outfile<<"ID,orginal,noramalized"<<endl;

    for(int i=0;i<values.size();i++){
        outfile<<ids[i]<<" "<<values[i]<<" "<<noramlize(values[i],min_val,max_val,norm_max,norm_min)<<endl;
    }
    
}