#ifndef BIG5ASSESSMENT_H
#define BIG5ASSESSMENT_H

/* File: big5Assessment.h
 * Author: Matthew Krahel
 * Description: Declares a Big5Assessment Class
 */

#include "node.h"
#include "position.h"
#include "binarySearchTree.h"
#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <string>

using namespace std;

const int NUM_QUESTIONS = 50;


class Big5Assessment {
public:
    //Constructors
    //Default Constructor
    Big5Assessment();
    //4-arg constructor
    Big5Assessment(string&, string&, int&, int ans[NUM_QUESTIONS]);
    
    //copy constructor
    Big5Assessment(Big5Assessment&);
    
    // destructor
    virtual ~Big5Assessment(){};
    
    //Set/Get functions
    void setLastName (string&);
    void setFirstName (string&);
    void setAge (int&);
    void setAnswer (int&, int&);
    
    string getLastName() const { return lastName;};
    string getFirstName() const { return firstName;};
    int getAge() const { return age;};
    int getAnswer(int& q) const { return answers[q];};

    //Overload Operators
    friend bool operator<( const Big5Assessment&, const Big5Assessment&);
    friend bool operator==( const Big5Assessment&, const Big5Assessment&);
    friend ostream& operator<<( ostream&, Big5Assessment&);
    friend istream& operator>>( istream&, Big5Assessment&);
    
    //Functions
    ostream& write (ostream& );
    istream& read (istream& );
    void printNormalizedTraits ();
    

private:
    string lastName;
    string firstName;
    int age;
    int answers[NUM_QUESTIONS];

};

#endif 