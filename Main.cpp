
#include <iostream>
#include <tuple>
#include <fstream>
#include <unordered_set>
#include <vector>
#include "utils.cpp"

#define LETTERS  "abcdefghijklmnopqrstuvwxyz"
#define R(i) (get<1>(split[i]))
#define L(i) (get<0>(split[i]))

using namespace std;
//Global Variable
unordered_set<string> myset;

unordered_set<string>  create_dictionary(const char* path) {
    string line;
    ifstream file;
    unordered_set<string> set;
    
    try {
        file.open(path);
    }
    catch (ifstream::failure e) {
        cerr << "Exception opening the file" << endl;
    }
    if (file){
        while (getline(file, line))
            set.insert(line);
        file.close();
    }
    return set;
}

unordered_set<string> edits1(string word) {

    int size = word.length();
    tuple<string, string> split [size + 1];
    unordered_set<string> single_edits;
    
    // Split the string 
    for (int i = 0 ; i < size + 1; i++) {
        split[i] = make_tuple(word.substr(0, i), word.substr(i, size));
    }
    //find all possible strings with just one deletion
    for (int i = 0; i < size + 1; i++) {
        string temp = R(i);
        if (temp != "") {
            single_edits.insert(L(i) + temp.substr(1, temp.size()));
        }
    }
    
    //find all possible strings with one transpose 
    for (int i = 0; i < size + 1; i++) {
        string temp = R(i);
        int length = temp.size();
        if (length > 1) {
            single_edits.insert(L(i) + temp[1] + temp[0] + temp.substr(2, length));
        }
    }
    
    //find all strings with one replaces
    for (int i = 0; i < size + 1; i++) {
        string left_temp = L(i);
        if (R(i) != "") {
            string right_temp = R(i).substr(1, R(i).size());
            for (char c : LETTERS) {
                if (c != '\0') {
                    single_edits.insert(left_temp + c + right_temp );
                }
            }
        }
    }
    
    //find all strings with one insert
    for (int i = 0; i < size + 1; i++) {
        string left_temp = L(i);
        string right_temp = R(i);
        for (char c : LETTERS) {
            if (c != '\0') {
                single_edits.insert(left_temp + c + right_temp);
            }
        }
    }

    return single_edits;
}

unordered_set<string> edits2(string word){
    unordered_set<string> edt1 = edits1(word);
    unordered_set<string> edt2;
    for(string value : edt1){
        unordered_set<string> temp = edits1(value);
        for(string value2 : temp){
            edt2.insert(value2);
        }
        temp.clear();
    }
    return edt2;
}

/**
 * "known" function searches the dictionary and separates out the strings in the set that are present in the dictionary.
 * function parses through the set and sees weather they exist in the dictionary.
 * @param   : unordered_set&
 * @return  : vector<string>
 */
vector<string> known(const unordered_set<string>& set){
    vector<string> know;
    for(auto& value : set){
        if (myset.count(value))
            know.push_back(value);
    }
    return know;
}

int main(int argc, char **argv) {
    
    myset =  create_dictionary("Database/words.txt");
    string choice;
    if(argc <2){
        cout<<"Enter the Choice"<<endl;
        cin >> choice;
    }
    else
        choice = argv[1];
    vector<string>top;
    vector<string> know = known(edits1(choice));
    
    
    sort_anagram(know, choice,top);
    if(top.size()<11)
        sort_rest(know, choice,top);
    if(top.size()<11){
        know.clear();
        know = known(edits2(choice));
        if(top.size()<11)
            sort_rest(know, choice,top);
    }
        
    int i =0;
    for(string& value: top)
        cout<<"tops:"<<++i<<'\t'<<value<<endl;

    return 0;
}
