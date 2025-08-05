////////////////////////////////////////////////////////////////////////////////
// program title: Braille to text translation//
////////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <fstream>
#include <string>
using namespace std;
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


