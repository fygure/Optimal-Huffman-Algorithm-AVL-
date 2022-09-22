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

// Changeable dataset
    int n = 5;
    vector<char> S = {'c', 'a', 'b', 'e', 'd'};
    vector<int> P = {1, 2, 7, 9, 15};

// To output the huffman encoding
    ofstream outFS("results.txt");

// Initialize and populate AVL tree with P and S data
    AVL Tree;
    for(int i=0; i < P.size(); i++)
        Tree.insert(P[i], S[i]);
    //Tree.display();

    

    



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
         
        /*  
            char x = min of tree, then remove from tree
            char y = min of tree, then remove from tree
            insert node of x + y for key and '$' for symbol
        */
        
        //string append = Huff(n-1, Tree, outFS);
        
        /*
            if both symbols are not '$'
                print(x, ":" + 0 or 1 + append)
                print(y, ":" + 0 or 1 + append)
                return "0";

            if x is '$' and y is not
                print(y, ":" + 0 + append)
                return "0" + append;
            
            if y is '$' and x is not
                print(x, ":" + 1 + append)
                return "1" + append;

            if both symbols are '$'
                return "1";

        */

    }


}