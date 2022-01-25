#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<cstdlib>

using namespace std;

char score2grade(int score){
    if(score >= 80) return 'A';
    if(score >= 70) return 'B';
    if(score >= 60) return 'C';
    if(score >= 50) return 'D';
    else return 'F';
}

string toUpperStr(string x){
    string y = x;
    for(unsigned i = 0; i < x.size();i++) y[i] = toupper(x[i]);
    return y;
}

void importDataFromFile(string a, vector<string> &b, vector<int> &c, vector<char> &d){
    string text;
    char search[] = "%[^:]: %d %d %d";
    ifstream source;
    source.open(a);
    char n[100];
    int x, y, z;
    while(getline(source, text)){
        const char *A = text.c_str();
        sscanf(A, search, n, &x, &y, &z);
        b.push_back(string(n));
        c.push_back(int(x+y+z));
        d.push_back(score2grade(int(x+y+z)));
    }
}

void getCommand(string &a, string &b){
    string text;
    char command[100], key[100];
    char search[] = "%s %[^\n]";
    cout << "Please input your command: ";
    getline(cin, text);
    const char *text2 = text.c_str();
    sscanf(text2, search, command, key);
    a = command;
    b = key;
}

void searchName(vector<string> a, vector<int> b, vector<char> c, string d){
    int n = 0;
    cout <<  "---------------------------------\n";
    for(int m=0; m<int(a.size()); m++){
        if(toUpperStr(a.at(m)).compare(toUpperStr(d)) == 0){
            cout << a.at(m) << "'s score = " << b.at(m) << endl;
            cout << a.at(m) << "'s grade = " << c.at(m) << endl;
        }else n++;
    }
    if(n == 26) cout << "Cannot found." << endl;
    cout <<  "---------------------------------\n";
}

void searchGrade(vector<string> a, vector<int> b, vector<char> c, string d){
    cout <<  "---------------------------------\n";
    for(int i=0; i<int(a.size()); i++){
        if(c.at(i) == d[0]) cout << a.at(i) << " (" << b.at(i) << ")" << endl;
    }
    cout <<  "---------------------------------\n";
}


int main(){
    string filename = "name_score.txt";
    vector<string> names;
    vector<int> scores;
    vector<char> grades; 
    importDataFromFile(filename, names, scores, grades);
    
    do{
        string command, key;
        getCommand(command,key);
        command = toUpperStr(command);
        key = toUpperStr(key);
        if(command == "EXIT") break;
        else if(command == "GRADE") searchGrade(names, scores, grades, key);
        else if(command == "NAME") searchName(names, scores, grades, key);
        else{
            cout << "---------------------------------\n";
            cout << "Invalid command.\n";
            cout << "---------------------------------\n";
        }
    }while(true);
    
    return 0;
}
