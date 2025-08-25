## Observations
Here are some observations I made while coding that I am a little confused about:
1. When creating any functions that take in fstream parameters, their implementation works only when I pass in these parameters by reference and consequently change the original function definition. Is there a particular reason for that?
This is because fstream is an interface that allows us to interact with files outside of our code. The thing is: the fstream library is system-dependent. Windows does not allow the modification of multiple files. Therefore you must pass in the fstream file by reference.

2. It seems that using pointers makes working with any functions that have fstream parameters a lot easier. Is this the case?

## Questions
1. Should I have a distructor?

Yes, A distructor is important to avoid any potential errors such as the locking of files by the operating system.

## Plan for translation (written out by Scott)
//New map structure:
map<string,vector<string>> ruleList;
// The key is the first character in the translation
//key= line[0];
// The vector is a list of translations that start with that character
In order to obtain that vector, we will create a function that takes in the rules file and searches each line after the '|' delimiter
void findMatches(fstream&rules, vector<string>&matches, char delim, char key)
while (file-getline)
if(line[locationofdelim+1])
vector.push_back(the_substr);

Assumptions:
* Rule dictionary is already loaded
* InputFile and output are valid and loaded


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
// string Translator::translate(string& line, int& lineConsume)
pseudo code (assuming map to list rule set):
- get a reference to list at first character (`curTrans = &rulesList[line[0]];`)
- iterate through curTrans until you find a complete match (`if( line.find(curTrans[i],0,curTrans[i].length()) != string::npos)`) This is important to just search the amount that is the length of the value in curTrans. If we are looking at | yr| that is not the same as | yrf|
- If you get to the end of the list (`i >= curTrans.length()`) -> this means there is no translation, just pass through
- You could use interators here to make things more general (i.e. it = curTrans.begin(); it++; it.length();)




More questions:
1. Can we talk about the architecture of the Translator methods?
example: For my copyInputToOutput function, do I need to take in the parameter of the file name or should it be the fstream object?
Should I perhaps use a getter function to retrieve the private variables for the fstream objects?


August 25, 2025
1. Problem with "loadRules", the file is passed in by referenece, sso the file is exhausted due to the passout to mult. functs. Use pointer to figure out
2. Importance oof having the "SplitString" function because it will be used in translation.

