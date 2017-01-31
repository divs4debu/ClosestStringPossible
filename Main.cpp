 
#include <iostream>
#include <tuple>
#include <fstream>
#include <unordered_set>
#define LETTERS = "abcdefghijklmnopqrstuvwxyz"
using namespace std;

void  create_dictionary(unordered_set<string>&  set, ifstream& file){
    string line;
    try{
        file.open("words.txt");
    }
    catch(ifstream::failure e){
        cerr<<"Exception opening the file"<<endl;
    }
    while(getline(file, line))
        set.insert(line);
    file.close();
}

void print(const unordered_set<string>& set){
    for (auto&x : set){
        cout<<x<<endl;
    }
}

void edits1(string word){
    int size = word.length();
    tuple<string,string> split [size+1];
    for (int i =0 ; i< size+1;i++){
        split[i] = make_tuple(word.substr(0,i), word.substr(i,size));
    }
    for (int i=0; i< size;i++){
        cout<<get<0>(split[i])<<"\t"<<get<1>(split[i])<<endl;
    }

}


int main(){
    ifstream myfile;
    unordered_set<string> myset;
    create_dictionary(myset, myfile);    
    //print(myset);
    edits1("hello");
    
    return 0;
}
