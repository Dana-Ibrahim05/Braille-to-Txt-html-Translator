# Planning Document
This document is where we can put our planning for this project. It also includes pseudocode and steps.
## Step 1: File IO basics
This step is the foundation of the program. We build the basic file IO system that allows the program to copy the contents of the braille file into a text file. IMplented as follows:

1. Create 2 file objects: one for the input (braille) and another for writing to the text file.
2. open the braille file.
3. use a string to store each word.
4. write each string to the new file
## step 2 (A): translating contractions.
There are over 150 contractions in braille, some of them being one-cell symbols and other being 2 (or more) letter combinations.
We therefore must create rules to allow the program to  translate these contractions.
I have thought of various tools to do this and used this resource to generate ideas:
[GeeksforGeeks] (https://www.geeksforgeeks.org/cpp/switch-vs-else/)
After our meeting on 08/14/2025, we discussed the following plan to translate our text:
1. write a file that includes all the translation rules. This file will include all the braille fcharacter combos and, delimited by the |or ~ character, followed by their translation.
example:
\ | ou
This file has been created. It will continue to be revised while testing occurs and we find any missing rules.

2. Load the rules file and copy all its elements into a map of "pairs". suggestion:a map of strings, but iterating over a map can be difficult.
3. Create a translator object (using classes), The translator object will load the input file and keep track of the input file's changes
4. Test using a test file. Note: use toupper (letter) if needed (i.e. because vS Code displays brf files as upper case)

### Plan for Translator (meeting on 08/21/2025)
Today, we discussed various important aspects about the translator object.
1. Translator Class Architecture:
* Using fstream objects instead of pointers.
* Using deligate 
    Translator(string inputFileName, string outputFileName): inputFile(inputFileName, 
    * We discussed the importance of opening fstream objects in both binary and input (using the bitwise | operator)
    * The Rules object should be part of the translator and thus, the function should be moved from main to the class header file.
    2. Translating mechanism
    * We discussed 3 options:
    (a) broot-forcing the translation process.
    (b) using a map of string keys and vector values. This is similar to an alphabetical sorting.
    example: all the rules that start with a "^" symbol.
    (c) Using a tree to split the cases.
    We also discussed the efficiency of each one, determining that the most efficient option would be option c.
    I chose to do option b because it was clearer to me.
    3. Miscellaneous:
    * in the "splitString" function, we discussed using the "find" method to find the delimiter instead of having an extra layer to the algorithm (the while-loop).
    * We also discussed that when using "substr" and not include a second parameter, the system automatically splits the string to the end of the string.
    

## Step 2 (B): Translating math formulas
This step is similar to the previous, except that some of the symbols in contractions and the symbols in math overlap, and therefore we must create another set of rules to allow this translation to occur without causing any mistranslation of math content into text and vice versa.

## Step 3: Formatting
It would be very helpful to have a converted file that has some element of formatting, particularly headings. Headings assist in navigation and significantly speed it up. These can be used to mark slide numbers, as well as section titltes.
