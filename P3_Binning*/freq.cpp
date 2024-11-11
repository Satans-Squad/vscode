#include<bits/stdc++.h>
using namespace std;

vector<vector<double>> equal_width_binning(vector<double> v,int n){
    int no_bins;
    cout << "\n Enter number of bins: " << endl;
    cin >> no_bins;
    double mini = *min_element(v.begin(), v.end());
    double maxi = *max_element(v.begin(), v.end());
    double w = (maxi - mini) / no_bins;
    vector<vector<double>> ans;
    int j = 0;
    for (int i = 0; i < no_bins;i++){
        vector<double> temp;
        double bin_min = mini + i * w;
        double bin_max = mini + (i+1) * w;
        while(j < n){
            if(i==no_bins-1){
                if(v[j]<=bin_max && v[j]>=bin_min){
                    temp.push_back(v[j]);
                }
                else
                    break;
            }
            else{
                if(v[j]<bin_max && v[j]>=bin_min){
                    temp.push_back(v[j]);
                }
                else
                    break;
            }
            j++;
        }
        ans.push_back(temp);
    }
    return ans;
}

vector<vector<double>> equal_freq_binning(vector<double> v,int n){
    int bin_size;
    cout << "\n Enter size of bin: " << endl;
    cin >> bin_size;
    vector<vector<double>> ans;
    for (int i = 0; i < n;i++){
        vector<double> temp;
        int j = i;
        for (j = i; j < min((i + bin_size),n);j++){
            temp.push_back(v[j]);
        }
        i = j - 1;
        ans.push_back(temp);
    }
    return ans;
}

int main(){
    ifstream in("input.csv");
    string temp;
    int f = 0;
    in>>temp;
    vector<double> v;
    while(in){
        if(f==0){
            f = 1;
        }
        else{
            v.push_back(stod(temp));
        }
        in >> temp;
    }
    int ch;
    cout << "\n Binning: \n1.By equal width\n2.By equal frequency" << endl;
    cout << "Enter your choice: " << endl;
    cin >> ch;
    vector<vector<double>> ans;
    sort(v.begin(), v.end());
    if(ch==1){
        ans = equal_width_binning(v, v.size());
    }
    else if(ch==2){
        ans = equal_freq_binning(v, v.size());
    }
    else{
        cout << "Wrong choice" << endl;
    }
    for (int i = 0; i < ans.size();i++)
    {
        cout << "Bin " << i + 1 << " : [";
        for(double j:ans[i]){
            cout << j << ", ";
        }
        cout << "]\n";
    }
    return 0;
}