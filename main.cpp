/*
    Max Chaltisios
    1808500
    9/21/2022
    Assignment 1 Question 7
    Dr. Leiss

    This program is the implementation of my design of the algorithm
    to get the huffman encoding in O(nlog(base2)n) time complexity.
*/



// Includes
//=======================================================================//
#include <iostream>
#include <vector>
#include <fstream>
#include <map>
#include "AVL.h"

// Functions
//=======================================================================//
string Huff(int n, AVL &Tree, ofstream &outFS);

// Driver Code
//=======================================================================//
int main()
{

// Changeable dataset (CHANGE ONLY HAPPENS HERE)
    int n = 4;
    vector<char> S = {'a', 'b', 'c', 'd'};
    vector<int> P = {7, 9, 11, 12};

// To output the huffman encoding
    ofstream outFS("results.txt");

// Initialize and populate AVL tree with P and S data
    AVL Tree;
    for(int i=0; i < P.size(); i++)
        Tree.insert(P[i], S[i]);

// Run algorithm
    string swag = Huff(n, Tree, outFS);

    outFS.close();
    return 0;
}

//=======================================================================//
//Define Functions
string Huff(int n, AVL &Tree, ofstream &outFS)
{
    // Base Case
    if (n == 1)
    {
        return "";
    }
    // Recursive Case
    else if (n >= 2)
    {
        // Remove first min
        node* temp = Tree.getMinNode();
        char x = temp->symbol;
        int min1 = temp->key;
        Tree.remove(min1);

        // Remove second min
        temp = Tree.getMinNode();
        char y = temp->symbol;
        int min2 = temp->key;
        Tree.remove(min2);

        // Add sum back as a node into tree with dummy symbol '$'
        Tree.insert(min1 + min2, '$');

        // Used to keep track of path as a string of 0s and/or 1s
        string append = Huff(n-1, Tree, outFS);
        
        if (x != '$' && y != '$')
        {
            outFS << x << ": 1" + append << endl;
            outFS << y << ": 0" + append << endl;
            return "0";
        }
        else if (x == '$' && y != '$')
        {
            outFS << y << ": 0" + append << endl;
            return "0" + append;
        }
        else if (y == '$' && x != '$')
        {
            outFS << x << ": 1" + append << endl;
            return "1" + append;
        }
        else if (x == '$' && y == '$')
        {
            return "1";
        }
    }

}