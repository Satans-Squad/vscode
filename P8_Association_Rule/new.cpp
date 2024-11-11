#include<bits/stdc++.h>
using namespace std;

unordered_map<string,int> readKthFile(int k,string filename){
    unordered_map<string,int> mp;
    ifstream in(filename);
    string str;
    while(getline(in,str)){
        stringstream ss(str);
        string tmp;
        int t = k;
        string key;
        while(getline(ss,tmp,',') && t!=0){
            t--;
            key += tmp;
            key += ",";
        }
        mp[key] = stoi(tmp);
    }
    
    return mp;
}
int main(){
    double minConf;
    cout << "\nEnter minimum confidence: " << endl;
    cin >> minConf;
    unordered_map<string, int> one_map = readKthFile(1, "one.csv");
    unordered_map<string, int> two_map = readKthFile(2, "two.csv");
    unordered_map<string, int> three_map = readKthFile(3, "three.csv");

    cout << "\n confidence of eligible items: " << endl<<endl;
    int t = 1;
    for(auto i:two_map){
        string str = i.first;
        double x_y = i.second;
        string tmp;
        cout << t++ <<") {" << str << "} : "<<endl;
        
        for(char c:str){
            tmp.push_back(c);
            if(c==','){
                double x = one_map[tmp];
                double c = (x_y / x) * 100;
                cout << "For {" << tmp << "} = " << x_y << "/" << x << "= " << c << "(" << ((c >= minConf) ? "Strong)" : "Weak)") << endl;
                tmp = "";
            }
        }
        cout << endl;
    }
    for(auto i:three_map){
        string str = i.first;
        double x_y = i.second;
        string tmp;
        cout << t++ <<") {" << str << "} : "<<endl;
        for(char c:str){
            tmp.push_back(c);
            if(c==','){
                double x = one_map[tmp];
                double c = (x_y / x) * 100;
                cout << "For {" << tmp << "} = " << x_y << "/" << x << "= " << c << "(" << ((c >= minConf) ? "Strong)" : "Weak)") << endl;
                tmp = "";
            }
        }
        cout << endl;
    }

    return 0;
}