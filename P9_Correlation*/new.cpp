#include<bits/stdc++.h>
using namespace std;

double findMean(vector<double> v,int n){
    return (double)accumulate(v.begin(), v.end(),0.0) / (double)n;
}

double findCovariance(vector<double>& a,vector<double>& b,double mean_a,double mean_b,int n){
    vector<double> cv;
    for (int i = 0; i < n;i++){
        double temp = (a[i] - mean_a) * (b[i] - mean_b);
        cv.push_back(temp);
    }
    return findMean(cv, n);
}

double findSD(vector<double>& v,double mean,int n){
    double sd = 0;
    for(double i:v){
        sd += (pow(i - mean, 2)) / n-1;
    }
    return sqrt(sd);
}

double findCorrelation(vector<double>& a,vector<double>& b,int n){
    double mean_a = findMean(a, n);
    double mean_b = findMean(b, n);
    double cv = findCovariance(a, b, mean_a, mean_b, n);
    double sd_a = findSD(a, mean_a, n);
    double sd_b = findSD(b, mean_b, n);
    return (cv / (sd_a * sd_b));
}

int main(){
    ifstream in ("input.csv");
    string str;
    getline(in, str);
    stringstream ss(str);
    string attr1, attr2;
    getline(ss,attr1,',');
    getline(ss,attr2,',');
    vector<double> a, b;
    while(getline(in,str)){
        stringstream ss1(str);
        string t1,t2;
        getline(ss1,t1,',');
        getline(ss1,t2,',');
        a.push_back(stod(t1));
        b.push_back(stod(t2));
    }

    double ans = findCorrelation(a, b,a.size());
    
    string label = "No";

    if(ans>0)
        label = "Positive";
    else if(ans<0)
        label = "Negative";
    cout << "Correlation between " << attr1 << " & " << attr2 << " = " << ans << " (" << label << " Correlation)" << endl;
    return 0;
}