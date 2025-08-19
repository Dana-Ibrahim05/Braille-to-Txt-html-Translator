////////////////////////////////////////////////////////////////////////////////
// program title: Braille to text translation//
////////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <fstream>
#include <string>
#include<map>
using namespace std;
// function definition for splitting a string into 2 parts based on a delimiter: the | in the "Rules.txt" file. It adds the first part as the key and the second part as the valuein a map
void splitString(string &line, map<string, string> &rules){
//create a char variable that holds the | delimiter
char delim='|';
//iterate over the string  until delimiter is found.
//create 2 strings: one for the key and one for the value
string key, value;
//initialize a counter variable to keep track of the iteration
int counter=0;
while(line[counter]!=delim){
// if the character at line[counter]is a delimiter, then the key the contains all the letters before the delimiter and the value contains all the characters after it.
if(line[counter]==delim){
key=line.substr(0, counter-1);
value= line.substr(counter+1, line.size()-1);
}
    counter++;
}
// add values to the map
rules[key]= value;
}
// function to load translation rules, take in rules file and add each rule to a map of strings
void loadRules(fstream rules){
    // open the rules file
    rules.open("Rules.txt");
// create a map with keys and values being both strings, the keys being the ascii interpretation of the braille characters
map <string, string> rulesList;
// create a string to hold each  word in the rules files before the delimiter
string line;
while(getline(rules, line)){
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

    // create an fstream object to open the braille file
    fstream brailleFile;
    // open the braille file
    brailleFile.open("22672v01.brf");
    if(!brailleFile.is_open()){
    cout<<"Failed to open file."<<endl;
        return 1;}
    // create another fstream object to hold contents of the braille file.
    fstream textFile("translated Content.txt");
    if(!brailleFile.is_open()){
    cout<<"Failed to open file."<<endl;
        return 1;}
    
    // read in braille file contents
    // create string to hold each word
    string str;
    while (brailleFile>>str)
    {
        brailleFile >> str; // read each word from the braille file.
        textFile << str;    // copy contents from braille file to text file
        cout<<str;
    }
    // close braille file
    brailleFile.close();
    // close text file
    textFile.close();
}


