
#include <iostream>
#include <tuple>
#include <fstream>
#include <unordered_set>
#include <vector>

#define LETTERS  "abcdefghijklmnopqrstuvwxyz"
#define R(i) (get<1>(split[i]))
#define L(i) (get<0>(split[i]))

using namespace std;
unordered_set<string> myset;

void  create_dictionary(unordered_set<string>&  set, ifstream& file) {
    string line;
    try {
        file.open("words.txt");
    }
    catch (ifstream::failure e) {
        cerr << "Exception opening the file" << endl;
    }
    while (getline(file, line))
        set.insert(line);
    file.close();
}

void print(const unordered_set<string>& set) {
    for (auto&x : set) {
        cout << x << endl;
    }
}

unordered_set<string> edits1(string word) {

    int size = word.length();

    string deletes[size + 1];
    string transposes[size + 1];
    tuple<string, string> split [size + 1];
    vector<string> replaces;
    vector<string> inserts;
    unordered_set<string> single_edits;

    for (int i = 0 ; i < size + 1; i++) {
        split[i] = make_tuple(word.substr(0, i), word.substr(i, size));
    }

    for (int i = 0; i < size + 1; i++) {
        string temp = R(i);
        if (temp != "") {
            deletes[i] = L(i) + temp.substr(1, temp.size());
            single_edits.insert(L(i) + temp.substr(1, temp.size()));
        }
    }

    for (int i = 0; i < size + 1; i++) {
        string temp = R(i);
        int length = temp.size();
        if (length > 1) {
            transposes[i] = L(i) + temp[1] + temp[0] + temp.substr(2, length);
            single_edits.insert(L(i) + temp[1] + temp[0] + temp.substr(2, length));
        }
    }

    for (int i = 0; i < size + 1; i++) {
        string left_temp = L(i);
        if (R(i) != "") {
            string right_temp = R(i).substr(1, R(i).size());
            for (char c : LETTERS) {
                if (c != '\0') {
                    replaces.push_back(left_temp + c + right_temp );
                    single_edits.insert(left_temp + c + right_temp );
                }
            }
        }
    }

    for (int i = 0; i < size + 1; i++) {
        string left_temp = L(i);
        string right_temp = R(i);
        for (char c : LETTERS) {
            if (c != '\0') {
                inserts.push_back(left_temp + c + right_temp);
                single_edits.insert(left_temp + c + right_temp);
            }
        }
    }

    return single_edits;
}


vector<string> known(const unordered_set<string>& set){
    vector<string> know;
    for(auto& value : set){
        if (myset.count(value))
            know.push_back(value);
    }
    return know;
}


int main() {
    ifstream myfile;
    
    create_dictionary(myset, myfile);

    string choice;
    cin >> choice;
    unordered_set<string> possibilities = edits1(choice);
    //print(myset);
    vector<string> know = known(possibilities);
    for (int i=0; i<know.size(); i++){
        cout<<know[i]<<endl;
    }

    return 0;
}
