/*This file contains the attributes and methods of the Translator class.
The translator is used  to load input and output files, as well as the rules dictionary.*/
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <string>
using namespace std;
// create inclusion guard

    #ifndef TRANSLATOR_H
#define TRANSLATOR_H

class Translator{
        // atributes: Take in a file for input, a file for the list of rules, and a file for output.
private:
    // Scott Comment: I would not use pointers here. You want
    //  File objects for input, rules  and output
    fstream inputFile;  // BRF file
    fstream outputFile; // Formatted HTML / MD file
    fstream ruleFile;   // rules list

public:
    // default constructor
    // Scott version of a constructor using delegated constructors
    Translator(string inputFileName, string outputFileName, string ruleFileName) : inputFile(inputFileName, std::fstream::in | std::fstream::binary), outputFile(outputFileName, std::fstream::out | std::fstream::binary), ruleFile(ruleFileName, std::fstream::out | std::fstream::binary)
    {
        // Other constructor-y things
    }
// function to organize the rules dictionary by finding substrings that start with a specific character and adding them to a vector of strings.
    void findMatches(fstream &rules, vector<string> &matches, char delim, char key)
    {
        string line;
        while (getline(rules, line))
        {
            // find location of the delimiter
            int tempIndex = line.find("|");
            // if the letter after the delimiter's location is the key, add the substring to the vector.
            if (line[tempIndex + 1] == key)
            {      
            line.erase(line.size() - 2, line.size() - 1);
            matches.push_back(line.substr(line.find("|") + 1));
        }
    }
}
void splitString(string &line, map<char, vector<string>> &rules, fstream &ruleFile)
{
    // create a char variable that holds the | delimiter
    char delim = '|';
    // use the find function to locate the delimiter position
    line.find("|");
    // create a char for the key
    char key;
    // create  vector of strings for the value
    vector<string> values;
    // Scott Comments: look at string.find, and string.substr
    key = line[0];
    // add values to the map
    findMatches(ruleFile, values, '|', key);
}

// Function to copy contents of input file to output file, takes input and output files as parameters
void copyInputToOutput(fstream &input, fstream &output)
{
    string str;
    while (input >> str)
    {
        output << str; // copy contents from braille file to text file
        // cout<<str;
    }
}
// function to load translation rules, take in rules file and add each rule to a map of strings
void loadRules(fstream &rules)
{
    // create a map with keys and values being both strings, the keys being the ascii interpretation of the braille characters
    map<char, vector<string>> rulesList;
    // create a string to hold each  word in the rules file
    string line;
    while (getline(rules, line))
    {
        // line= getline(rules, line, '|');
        // I don't know why the line above gives me a conversion error;
        splitString(line, rulesList, rules);
    }
}

// destructor to close input, rules, and output files.
~Translator()
{
    inputFile.close();
    outputFile.close();
    ruleFile.close();
}
// main translator method
string translate(string line, map<char, vector<string>> &rulesList){
    //get a reference for the rulesList at the first character in line.
vector<string> curTrans= rulesList[line[0]];
// the number of characters in a pattern
//int lineConsumed=0;
string output;
for(int i=0; i<curTrans.size(); i++){
if(line.find(curTrans[i], 0))
output=curTrans[i];

}
}

};
#endif