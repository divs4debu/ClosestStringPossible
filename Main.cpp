 
#include <iostream>
#include <tuple>
#include <fstream>
#include <unordered_set>

#define LETTERS = "abcdefghijklmnopqrstuvwxyz"
#define R(i) (get<1>(split[i]))
#define L(i) (get<0>(split[i]))

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
    
    string deletes[size+1];
    string transposes[size+1];
    tuple<string,string> split [size+1];
    string replaces[size+1];
    
    for (int i =0 ; i< size+1;i++){
        split[i] = make_tuple(word.substr(0,i), word.substr(i,size));
    }
    
    for (int i = 0; i< size+1; i++){
        string temp = R(i);
        if(temp != ""){
            deletes[i] = L(i) + temp.substr(1,temp.size());
        }
    }
    
    for (int i =0; i< size+1;i++){
        string temp = R(i);
        int length = temp.size();
        if(length>1)
            transposes[i] = L(i) + temp[1]+temp[0]+temp.substr(2,length); 
    }
    
    
    for (int i=0; i< size+1;i++){
        cout<<transposes[i]<<endl;
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
