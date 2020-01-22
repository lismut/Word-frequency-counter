#include<map>
#include<vector>
#include<utility>
#include<algorithm>
#include <iostream>
#include <fstream>
#include <ios>

using std::string;
using std::cout;
using std::cin;
using std::endl;
using std::ofstream;
using std::ifstream;
using std::vector;

typedef std::pair<int, string> TPairs;
typedef std::map<string, int> TDictMap;

void help()
{
    cout << "Usage:" << endl;
    cout << "   frequen [input_file] [output_file]" << endl;
}

void incorrectArgs()
{
    cout << "Incorrect format of command line arguments." << endl;
    help();
}

bool checkOutputFile(const char* fileName)
{
    string symbol = " ";
    bool result = true;
    ifstream test(fileName, std::ios::in);
    if (test.is_open()) {
        while (symbol != "y" && symbol != "n" && symbol != "Y" && symbol != "N") {
            cout << "File " << fileName << " already exists, do you want to replace it? [y/n]";
            cin >> symbol;
        }
        if (symbol == "n" || symbol == "N") {
            cout << "Try another filename" << endl;
            result = false;
        }
    }
    return result;
}

void failedOpen(const string& name)
{
    cout << "Could not open file " << name << endl;
    help();
}

void parseFile (ifstream& inpFile, TDictMap& dict)
{
    while(!inpFile.eof()) {
        string word;
        while (inpFile && !isalpha(inpFile.peek())) {
            inpFile.get();
        }
        while (inpFile && isalpha(inpFile.peek())) {
            word.push_back(tolower(inpFile.get()));
        }
        if(!word.empty()) {
            dict[word]++;
        }
    }
}

int main(int argc, char* argv[])
{
    if (argc != 3) {
        incorrectArgs();
        return 1;
    }
    if (!checkOutputFile(argv[2])) {
        return 1;
    }
    ifstream inpFile(argv[1]);
    ofstream outFile(argv[2]);
    if (!inpFile.is_open() || !outFile.is_open()) {
        string name = (inpFile.is_open()) ? argv[2] : argv[1];
        failedOpen(name);
        return 1;
    }
    TDictMap dict;
    parseFile(inpFile, dict);
    vector< TPairs > result;
    for (auto& one : dict) {
        result.push_back(TPairs(one.second, one.first));
    }
    sort(result.begin(), result.end(), [](const TPairs& left, const TPairs& right) {
            if (left.first != right.first) {
                return left.first > right.first;
            } else {
                return right.second > left.second;
            }
         });
    for (auto& one : result) {
        outFile << one.first << " " << one.second << endl;
    }
}
