    /*This file contains the attributes and methods of the Translator class.
The translator is used  to load input and output files.*/
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

// create inclusion guard

#ifndef TRANSLATOR_H
#define TRANSLATOR_H
class Translator
{
    // atributes: Take in a file for input and a file for output.
private:
    //Scott Comment: I would not use pointers here. You want 
    // input and output files
    fstream *input;
    fstream *output;

    // File objects for input and output
    fstream inputFile; //BRF file
    fstream outputFile; //Formatted HTML / MD file
    fstream ruleFile;

public:
    // default constructor
    Translator()
    {
        *input = nullptr;
        *output = nullptr;
    }
    Translator(fstream *inputFile, fstream *outputFile)
    {
        input = inputFile;
        output = outputFile;
    }

    //Scott version of a constructor using delegated constructors
    Translator(string inputFileName, string outputFileName, string ruleFileName): inputFile(inputFileName, std::fstream::in | std::fstream::binary), outputFile(outputFileName, std::fstream::out | std::fstream::binary), ruleFile(ruleFileName, std::fstream::out | std::fstream::binary){
        //Other constructor-y things
    } 

    // function to open both input and output files
    void openFiles(string inputFileName, string outputFileName, fstream *inputFile, fstream *outputFile)
    {
        outputFile->open(outputFileName);
        inputFile->open(outputFileName);
    }
    // Function to copy contents of input file to output file, takes input and output files as parameters
    void copyInputToOutput(fstream *input, fstream *output)
    {
        string str;
        while (*input >> str)
        {
            *input >> str;  // read each word from the input file.
            *output << str; // copy contents from braille file to text file
            // cout<<str;
        }
    }
    // close input and output files.
    void closeFiles(fstream *input, fstream*output){
        input->close();// closes input file
        output->close();// closes output file.
    }
};

// end inclusion guard
#endif