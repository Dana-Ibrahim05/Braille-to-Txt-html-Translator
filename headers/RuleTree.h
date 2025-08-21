#pragma once

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
using namespace std;

//Specification for RuleTree

class RuleNode{
    private: 
        //Collection of children nodes
        vector<RuleNode*> children; //TODO: This could be even more efficient with careful use here (i.e. keeping things in alpha order or a map)
        char nodeChar; // Corresponding character for this node
        string translation; //If this is the last node to match, what should the translation be?

        //Probably just for debugging
        int level; //Which level of the pattern is this node (should be the depth of the tree)

    public:
        //Constructor always needs full arguments
        RuleNode(char newNodeChar, string newTranslation, int newLevel);
        //Make sure you delete all of the children nodes
        ~RuleNode();

        //Basic access
        char getChar(){return nodeChar;};
        string getTranslation(){return translation;}
        int getLevel(){ return level;}

        //This should only be used to update a node that was previously added
        void setTranslation(string trans){ translation = trans; }

        //Adds new child to this node
        void addChild(RuleNode* newChild);

        //Find the correct child based off of searchChar
        // If not found, returns null pointer
        RuleNode* findChild(char searchChar);

        //Debug
        void printNode();


};

class RuleTree{

    private:
        //Root node 
        RuleNode* root;

        // Utility to add something to the root tree
        // pattern is encoded into the tree
        // translation is what results in ending on the new node (i.e. the last node of the translation)
        //TODO: This should probably check to see if there is other nodes that match (i.e. don't duplicate)
        void addNode(string pattern, string translation);

    public: 
        RuleTree(fstream& ruleFile);
        ~RuleTree();

        //Search the tree for the most complete match of the pattern string
        // if matchedString is empty, it means there was nothing found that matches
        // otherwise the matched string is paired with the corresponding translation
        void lookUp(const string& patternString, string& matchedString, string& translation);
};