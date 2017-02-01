#ifndef UTILS_H
#define UTILS_H

#include <algorithm>
#include <iostream>
#include <unordered_set>

using namespace std;
bool is_anagram(string original, string word){
    sort(original.begin(), original.end());
    sort(word.begin(), word.end());
    return original==word;
}

void sort_anagram(vector<string> all_correct, string input, vector<string>& top){
    for (string temp : all_correct){
        if(is_anagram(input, temp))
            top.push_back(temp);        
    }
}


void sort_rest(vector<string> all_correct, string input, vector<string>& top){
    for (string temp : all_correct){
        if(top.size()>10)   return;
            if((!is_anagram(temp,input)) && temp.size() == input.size())
                top.push_back(temp);
    }
    for (string temp : all_correct){
        if(top.size()>10)   return;
            if((!is_anagram(temp,input)) && temp.size() < input.size())
                top.push_back(temp);
    }
    for (string temp : all_correct){
        if(top.size()>10)   return;
            if((!is_anagram(temp,input)) && temp.size() > input.size())
                top.push_back(temp);
    }
}

void print(const unordered_set<string>& set) {
    for (auto&x : set) {
        cout << x << endl;
    }
}

#endif
