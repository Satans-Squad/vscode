#include<bits/stdc++.h>
using namespace std;

int main(){
    vector<double> x,y;

    ifstream inpfile("./input.csv");

    string line;
    while(getline(inpfile,line)){
        string f,s;
        stringstream ss(line);
        getline(ss,f,',');
        getline(ss,s);

        x.push_back(stod(f));
        y.push_back(stod(s));
    }

    double center_x=0.0;
    double center_y=0.0;

    center_x=accumulate(x.begin(),x.end(),0.0)/x.size();
    center_y=accumulate(y.begin(),y.end(),0.0)/y.size();

    cout<<"center of cluster is ("<<center_x<<","<<center_y<<")"<<endl;

    for(int i=0;i<x.size();i++){
        cout<<"Distance of point ( "<<x[i]<<" , "<<y[i]<<" ) from the center is "<<sqrt(pow(x[i] - center_x, 2) + pow(y[i] - center_y, 2))<<endl;
    }
    
}