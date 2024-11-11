#include<bits/stdc++.h>
using namespace std;

pair<double, double> linearRegression(vector<double>& x, vector<double>& y) {
    int n = x.size();

    double mean_x = accumulate(x.begin(), x.end(), 0.0) / n;
    double mean_y = accumulate(y.begin(), y.end(), 0.0) / n;

    double numerator = 0, denominator = 0;
    for (int i = 0; i < n; i++) {
        numerator += (x[i] - mean_x) * (y[i] - mean_y);
        denominator += (x[i] - mean_x) * (x[i] - mean_x);
    }

    double slope = numerator / denominator;
    double intercept = mean_y - slope * mean_x;

    return {slope, intercept};
}

int main() {
    cout << "enter number of points: ";
    int n;
    cin >> n;
    
    vector<double> x(n), y(n);
    cout << "enter x and y values:\n";
    for(int i = 0; i < n; i++) {
        cin >> x[i] >> y[i];
    }
    
    auto [slope, intercept] = linearRegression(x, y);
    
    cout << "\ny = " << slope << "x + " << intercept << endl;
    cout << "\nresult:\n";
    for(int i = 0; i < n; i++) {
        double predicted = slope * x[i] + intercept;
        cout << "x=" << x[i] << ": predicted y=" << predicted << ", actual y=" << y[i] << endl;
    }
    return 0;
}