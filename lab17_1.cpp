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

void importDataFromFile(string fname, vector<string> &name, vector<int> &sc, vector<char> &G){
    ifstream source;
    source.open(fname.c_str());
    string textline;
    while(getline(source,textline)){
        const char * text = textline.c_str();
        char format[] = "%[^:]: %d %d %d";
        char scanname[100];
        int a,b,c;
        sscanf(text,format,scanname,&a,&b,&c);
        name.push_back(scanname);
        int sum = a+b+c;
        sc.push_back(sum);
        char kodINW = score2grade(sum);
        G.push_back(kodINW);
    }
}

void getCommand(string &command, string &key){
   cout << "Please input your command: ";
   string input1;
    getline(cin,input1);
    char format[] = "%s %[^:]";
    char cm[100],ke[100];
    sscanf(input1.c_str(),format,cm,ke);
    command = cm;
    key = ke;
}
void searchName(vector<string> name, vector<int> sc, vector<char> G,string key){
    cout<<"---------------------------------"<<endl;
    int count =0;
    for(unsigned int i = 0;i<name.size();i++){
        if(key == toUpperStr(name[i])){
            cout << name[i]<<"'s score = "<< sc[i]<<endl<<name[i]<<"'s grade = "<<G[i]<<endl;
            count++;
        }
    }
    if(count == 0)
    cout<<"Cannot found."<<endl;
    cout<<"---------------------------------"<<endl;
}

void searchGrade(vector<string> name, vector<int> sc, vector<char> G,string key){
    cout<<"---------------------------------\n";
    int count = 0;
    char kek = key[0];
    for(unsigned int i = 0;i<name.size();i++){
        if(kek == (G[i])){
            cout<<name[i]<<" ("<<sc[i]<<")"<<endl;
            count++;
        }
    }
    if (count == 0)
     cout<<"Cannot found";
    cout<<"---------------------------------"<<endl;
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
