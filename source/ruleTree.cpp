#include "RuleTree.h"

RuleNode::RuleNode(char newNodeChar, string newTranslation, int newLevel):
    nodeChar(newNodeChar),
    translation(newTranslation),
    level(newLevel)
{
    //children should be default constructed (empty vector of children)
}

RuleNode::~RuleNode(){
    for(int i = 0; i < children.size(); i++){
        delete children[i];
    }
}

void RuleNode::addChild(RuleNode* newChild){
    //Add this new child to the vector of children
    children.push_back(newChild);
}

RuleNode* RuleNode::findChild(char searchChar){
    //For this node, see if any of the children have the corresponding nodeChar
    for(int i = 0; i < children.size(); i++){ //iterate though the children
        if(children[i]->getChar() == searchChar){
            //Found the correct node!
            return children[i];
        }
    }

    return nullptr; //TODO: make sure this is working
}


RuleTree::RuleTree(fstream& ruleFile){
    if(ruleFile.fail() || !ruleFile.is_open()){
        //TODO: This is not quite working
        cout << "RuleTree file IO error. Stopping constructor!" << endl;
        return;
    }

    //Go through the whole rule list, fill the rule tree!

    //SetUp Root node
    root = new RuleNode(static_cast<char>(0),"ROOT NODE ERROR",0);
    //                                    ^ Null character, should not ever be checked

    int nodeCount = 0;

    //Go through the list of rules, add each one
    string curLine;
    while( getline(ruleFile,curLine) ){
        if(curLine.find('\r') != string::npos){//Remove return if present
            curLine.erase(curLine.find('\r'));
        }

        string pattern(curLine.substr(0, curLine.find("|"))); //From the first element to one before the delim
        string translation(curLine.substr( curLine.find("|")+1 )); //From one after the delim to the end of the string
        //cout << "Adding |" << curLine << "| parsed to: |" << pattern <<"|,|" << translation <<"|" << endl;
        
        addNode(pattern, translation);
        nodeCount++;
    }

    cout << "Done Adding elements to the RuleTree! Added " << nodeCount << " rules." << endl;
    ruleFile.close();
}

RuleTree::~RuleTree(){
    delete root; // Should call the destructors for all of the nodes in children
}

void RuleTree::addNode(string pattern, string translation){
    RuleNode* curNode = root;
    RuleNode* nextNode = nullptr;
    
    //parse through the pattern, when done make a new node!
    for(int i = 0; i < pattern.length(); i++){
        char curChar = pattern[i];

        //cout << "Looking for |" << curChar << "|" << endl;
        //First check to see if there is a valid node
        nextNode = curNode->findChild(curChar);

        // If nextNode is valid, step into it
        // note: all of the resulting divergence sets up nextNode appropriately
        if(nextNode != nullptr){
            //cout << "Stepping into |" << nextNode->getChar() << "|" << endl;
            //curNode = nextNode; //Update to the next one (don't need to do this, do it at the end)
        } else {
        // If there is not, add respective nodes
            //Deal with the last char in the pattern
            if(i >= pattern.length()-1){
                //It is possible this is the end (i.e. there are no more children to process)
                //    -> nextNode should have the translation
                //cout << "Adding end node!" << endl;
                nextNode = new RuleNode(curChar,translation,i);
                curNode->addChild(nextNode);
                return; //We should be done at this point
            } else {
                //If this is not the end, we need to keep adding nodes 
                //cout << "Adding intermediate node!" << endl;
                nextNode = new RuleNode(curChar,"<EMPTY TRANSLATION ERROR>",i);
                curNode->addChild(nextNode);
                //Keep going!
            }
        }

        curNode = nextNode; //Update which node we are in
    }

    //If we get to this point it means:
    //    we have stepped through all of the nodes, but have not added an end node
    // This means the current node was added previously (because of a longer chain)
    // The current node should have a bad translation entry, so we need to update it
    //cout << "Shorter pattern added! Replacing |" << curNode->getTranslation() << "| with |" << translation << "|" << endl;
    if(curNode->getTranslation() != "<EMPTY TRANSLATION ERROR>"){
        cout << "Duplicate pattern found! Might be an issue. Current pattern: |"<< pattern <<"| replacing |" << curNode->getTranslation() << "| with |" << translation << "|" << endl;
    }

    curNode->setTranslation(translation);
}

void RuleTree::lookUp(const string& patternString, string& matchedString, string& translation){
    cout << "In lookUp" << endl;
    RuleNode* curNode = root;
    RuleNode* nextNode = nullptr;

    //parse through the pattern, looking for positive match / first non-match
    for(int i = 0; i < patternString.length(); i++){
        char curChar = patternString[i];

        cout << "Looking for |" << curChar << "|" << endl;
        //First check to see if there is a valid node
        nextNode = curNode->findChild(curChar);

        if(nextNode != nullptr){
            //Valid node, keep going!
            cout << "Found node with char: |" << curChar << "|" << endl;
            curNode = nextNode;
        } else {
            if(curNode != root){ //Make sure we have made it to a valid child node
                //Probably not an error! This is the end of the matched pattern
                //curNode should be the end of the translation pattern
                cout << "End of look up! Translation: |" << curNode->getTranslation() << "|" << endl;
                translation = curNode->getTranslation();
                matchedString = patternString.substr(0,i);
                //TODO: Deal with trailing spaces? Maybe we do this outside of this method      
                return;
            } else {
                //I think this means there is no translation for this character
                cout << "End of loopUp, no nodes found (i.e. still in root) " << endl;
                matchedString = "";
                translation = "<RootNode ERROR>";
                return;
            }
        }
    }

    // TODO: Deal with trailing stuff
    cout << "Got to the end of lookup! Probably means we are at the end of the line" << endl;
}
