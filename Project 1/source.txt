/*
Dillon Li - 1642853
Project 1: Tries
*/


#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <math.h>
#include <time.h>

using namespace std;

// Convert alphabet into numbers
int char_to_index(char C)
{
    // Numbers 0 to 9 indices 26-35
    if (isdigit(C))
        return (int)C - 22;
    else if (C == '_')
        return 36;
    else if (C == ' ')
         return 37;
    // Alphabet indices 0-25
    else
        return (int)C - (int)'a';
}

class trieNode {
friend class trie;
private:
    bool isValid;
public:
    string wordpart;
    trieNode *children[37];
    trieNode() 
    {
        for (int i = 0; i <= 37; i++) {
            children[i] = NULL; }
        wordpart = "";
        isValid = false;
    }
};

class trie {
private:
public:
    trieNode root;
    void insert(string s);
    trieNode* search(string s);
    void test_print(trieNode* node);
    void print_leaves(trieNode* node);
};

void trie::test_print(trieNode* node)
{
    cout << "Wordpart is " << node->wordpart << endl;
    system("pause");
    for (int i = 0; i <= 37; i++)
    {
        if (node->children[i] != NULL)
           test_print(node->children[i]);
    }
}

void trie::insert(string s)
{
     
    int length = s.length();
    trieNode* traverse = &root;
    for (int i = 0; i < length; i++)
    {
        // Check if it exists at each level of trie
        int index = char_to_index(s[i]);
        //cout << "Index is " << index << endl;
        if (traverse->children[index] == NULL) // Does not exist
        {
            string sub = s.substr(0, i+1);
            traverse->children[index] = new trieNode;
            traverse->children[index]->wordpart = sub;
            //cout << "Inserted node wordpart is " << traverse->children[index]->wordpart << endl;
        }
        traverse = traverse->children[index]; // next letter 
        //system("pause");
    }
    traverse->isValid = true; 
    //cout << "This is a leaf node\n";
}

trieNode* trie::search(string s)
{
    int length = s.length();
    trieNode* traverse = &root;
    for (int i = 0; i < length; i++)
    {
        int index = char_to_index(s[i]);
        if (traverse->children[index] != NULL)
            traverse = traverse->children[index];
        else 
        {
            return NULL;
        }
        // system("pause");
    }
    return traverse;
}

void trie::print_leaves(trieNode* node)
{
    if (node->isValid)
        cout << node->wordpart << endl;
    for (int i = 0; i <= 37; i++)
    {
        if (node->children[i] != NULL)
            print_leaves(node->children[i]);    
    }
}

main()
{
     trie search_complete;
     
     // Read dictionary into trie
     ifstream infile("Dictionary.txt");
     string line;
     while(getline(infile, line))
     {
         search_complete.insert(line);
         //cout << "Line is: " << line << endl;

         //system("pause");
     }  
     infile.close();
     
     // search_complete.test_print(&search_complete.root);
     
     
     // Take input
     string input;
     cout << "Please type search queries: \n";
     cin >> input; 
     
     trieNode* node;
     node = search_complete.search(input);
     if (node != NULL)
     {
         cout << "Your options are:\n";
         search_complete.print_leaves(node);
     }
     else 
         cout << "There are no results that match your query\n";
     system("pause");
}



