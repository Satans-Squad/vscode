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

    // Find the closest point to the mean as the center
    double mean_x = accumulate(x.begin(), x.end(), 0.0) / x.size();
    double mean_y = accumulate(y.begin(), y.end(), 0.0) / y.size();

    double min_distance = INFINITY;
    int closest_index = -1;

    for (int i = 0; i < x.size(); i++) {
        double distance = sqrt(pow(x[i] - mean_x, 2) + pow(y[i] - mean_y, 2));
        if (distance < min_distance) {
            min_distance = distance;
            closest_index = i;
        }
    }

    double center_x = x[closest_index];
    double center_y = y[closest_index];

    cout << "Center of cluster is (" << center_x << ", " << center_y << ")" << endl;

    for (int i = 0; i < x.size(); i++) {
        cout << "Distance of point (" << x[i] << ", " << y[i] << ") from the center is " << sqrt(pow(x[i] - center_x, 2) + pow(y[i] - center_y, 2)) << endl;
    }
    
}