#include<bits/stdc++.h>
using namespace std;

vector<double> getData(){
    vector<double> result;

    ifstream inpfile("./input.csv");
    string line;

    getline(inpfile,line);

    while(getline(inpfile,line)){
        double val;
        val=stod(line);
        result.push_back(val);
    }

    return result;
};

double getMedian(int n,vector<double>& data){

    // for(auto it:data){
    //     cout<<it<<" ";
    // }
    // cout<<endl;
    // cout<<n<<endl;
    // cout<<data[n/2]<<endl;
    // cout<<data[n/2-1]<<endl;
    // cout<<data[n/2+1]<<endl;
    return n%2?(double)(data[n/2-1]):(((double)(data[n/2-1])+(data[n/2]))/2.0);
}

void boxPlot(vector<double>& data){
    sort(data.begin(),data.end());

    int n=data.size();

    double min_ele=data[0];
    double max_ele=data[n-1];

    double median=getMedian(n,data);

    int q1_index=int(n*0.25);
    int q3_index=int(n*0.75);

    double Q1=data[q1_index];
    double Q3=data[q3_index];

    double IQR=Q3-Q1;

    double lower_bound=Q1-1.5*IQR;
    double upper_bound=Q3+1.5*IQR;

    auto outliers=[&](){
        vector<double> outliers;

        for(auto it:data){
            if(it<lower_bound || it>upper_bound){
                outliers.push_back(it);
            }
        }  

        return outliers;
    };

    vector<double> outliersData=outliers();


    cout<<"Lower Bound: "<<lower_bound<<endl;
    cout<<"Q1: "<<Q1<<endl;
    cout<<"Median: "<<median<<endl;
    cout<<"Q3: "<<Q3<<endl;
    cout<<"Upper Bound: "<<upper_bound<<endl;
    cout<<"IQR: "<<IQR<<endl;
    cout<<"Outliers: "<<endl;

    for(auto it:outliersData){
        cout<<it<<" ";
    }
    cout<<endl;
}

int main(){
    vector<double> data=getData();

   boxPlot(data);
}