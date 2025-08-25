////////////////////////////////////////////////////////////////////////////////
// program title: Braille to text translation//
////////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <fstream>
#include<vector>
#include <string>
#include <map>
#include "Translator.h"
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
    // initialize a translator object
    Translator initial("22672v01.brf", "translated Content.txt", "rules.txt");
    
    return 0;
}