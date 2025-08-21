////////////////////////////////////////////////////////////////////////////////
// program title: Braille to text translation//
////////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include "Translator.h"
using namespace std;
// function definition for splitting a string into 2 parts based on a delimiter: the | in the "Rules.txt" file. It adds the first part as the key and the second part as the valuein a map
void splitString(string &line, map<string, string> &rules)
{
    // create a char variable that holds the | delimiter
    char delim = '|';
    // iterate over the string  until delimiter is found.
    // create 2 strings: one for the key and one for the value
    string key, value;
    // initialize a counter variable to keep track of the iteration
    int counter = 0;

    //Scott Comments: look at string.find, and string.substr
    while (line[counter] != delim)
    {
        // if the character at line[counter]is a delimiter, then the key the contains all the letters before the delimiter and the value contains all the characters after it.
        counter++;
        if (line[counter] == delim)
        {
            key = line.substr(0, counter);
            value = line.substr(counter + 1, line.size() - 1);
            //value = line.substr(counter + 1); //Option 1 (uses string::npos i.e. end of string)
            //value = line.substr(counter + 1, line.size() - counter - 1); // Option 2 (directly specifies the length, but it is the length of string - where the counter is) You may need an extra -1
        }
    }
    // add values to the map
    rules[key] = value;
}
// function to load translation rules, take in rules file and add each rule to a map of strings
void loadRules(fstream &rules)
{
    // open the rules file
    rules.open("Rules.txt");
    // create a map with keys and values being both strings, the keys being the ascii interpretation of the braille characters
    map<string, string> rulesList;
    // create a string to hold each  word in the rules file
    string line;
    while (getline(rules, line))
    {
        // line= getline(rules, line, '|');
        // I don't know why the line above gives me a conversion error;
        splitString(line, rulesList);
    }
}

// int checkOpenStatus(fstream file){
// if(!file.is_open()){
//     cout<<"Failed to open file."<<endl;
//     return 1;
// }
// else
// return 0;
// }
int main()
{
    fstream rulesFile;
    loadRules(rulesFile); // load the rules from the rules file
    // initialize a translator object
    fstream *brailleFile, *textFile;
    Translator initial(brailleFile, textFile);
    initial.openFiles("ASCII Braille.brf", "translated Content.txt", brailleFile, textFile);
    initial.copyInputToOutput(brailleFile, textFile);
    return 0;
}