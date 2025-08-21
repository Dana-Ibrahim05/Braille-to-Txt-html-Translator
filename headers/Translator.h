/*This file contains the attributes and methods of the Translator class.
The translator is used  to load input and output files.*/
#include <iostream>
#include <fstream>
#include <string>
#include "RuleTree.h"
using namespace std;

// create inclusion guard

#ifndef TRANSLATOR_H
#define TRANSLATOR_H
class Translator
{
    // atributes: Take in a file for input and a file for output.
    private:
    // File objects for input and output
    fstream inputFile;  // BRF file
    fstream outputFile; // Formatted HTML / MD file
    fstream ruleFile; //File that holds all of the rules

    RuleTree rTree; // Rule tree that is populated from ruleFile

    public:
    // Scott version of a constructor using delegated constructors
    Translator(string inputFileName, string outputFileName, string ruleFileName) :
        inputFile(inputFileName, std::fstream::in | std::fstream::binary),
        outputFile(outputFileName, std::fstream::out | std::fstream::binary),
        ruleFile(ruleFileName, std::fstream::in | std::fstream::binary),
        rTree(ruleFile)
    {
        //Verify everything opened
        if(! (inputFile.is_open() && !inputFile.fail()) ){
            cout << "Something went wrong with input file! |" << inputFileName << "|" << endl;
        }
        if(! (outputFile.is_open() && !outputFile.fail()) ){
            cout << "Something went wrong with output file! |" << outputFileName << "|" << endl;
        }

        // Other constructor-y things
        cout << "Done setting up the translator!" << endl << endl;
    }

    // Main translation method
    // Input: line - current working space, the first character is the 'next to be translated' character
    //               the character may or may not be the first in a longer chain of characters that influence the translation
    //        lineConsume - the number of characters that were used from line to form the translation.
    // Output: a string that will need to be appended to the growing translation, i.e. what the input character(s) get translated to
    //        example: if line is |,LOS ,ANGELES :ILE %E 0 9 HI<|
    //                 the pattern match will be |,L|
    //                 lineConsume will be 2, for the two characters used
    //                 return value will be |L| (capital L)
    //        Alt example: if the line is | X ) BLACK4 ,I WI% 6GEE-|
    //                 the pattern match will be | X |
    //                 lineConsume will be 3, for the three character used (TODO: this may be wrong, it may need to be 2 and keep the last space for the next translation)
    //                 return value will be | it |
    string translate(string& line, int& lineConsume){
        string matched;
        string translated;

        //Perform the look up
        rTree.lookUp(line,matched,translated);

        if(matched != ""){
            lineConsume = matched.length();
            return translated;
        } else {
            cout << "ERORR IN TRANSLATE!" << endl;
            lineConsume = -1;
            return "";
        }
    }

};

// end inclusion guard
#endif