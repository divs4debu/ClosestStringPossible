 
#include <iostream>
#include <fstream>
#include <unordered_set>
using namespace std;

int main(){
    ifstream myfile;
    unordered_set<string> myset;
    long int count = 0;
    string line;
    myfile.open("words.txt");
    if(myfile.is_open()){
        while(getline(myfile,line)){
            //cout<<line<<endl;
            myset.insert(line);
            count++;
        }
        cout<<"Words present are : "<<count<<endl;
        myfile.close();
    }
    

    
    for (auto&x : myset){
        cout<<x<<endl;
    }
    
    cout<<myset.size()<<endl;

    return 0;
}
