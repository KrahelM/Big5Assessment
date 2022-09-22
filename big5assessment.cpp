/* File: big5Assessment.cpp
 * Author: Matthew Krahel
 * Description: Implements a Big5Assessment Class
 */
 
#include "big5assessment.h"
#include "node.h"
#include "position.h"
#include "binarySearchTree.h"
#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <string>
#include <iomanip>
#include <string.h>

using namespace std;

/*
 * Default Constructor
 */
Big5Assessment::Big5Assessment(){
    lastName = "";
    firstName = "";
    age = 0;
    answers[0] = 0;
}

/*
 * 4-arg constructor
 *  parameters:
 *      last  last name
 *      first  first name
 *      a  age
 *      b[]  array of answers
 */
Big5Assessment::Big5Assessment(string& last, string& first, int& a, int b[NUM_QUESTIONS]){
    lastName = last;
    firstName = first;
    age = a;
    for(int i = 0; i < NUM_QUESTIONS; i++){
        answers[i] = b[i];
    }
}

/* copy constructor
 */
Big5Assessment::Big5Assessment(Big5Assessment& b){
    lastName = b.lastName;
    firstName = b.firstName;
    age = b.age;
    for(int i = 0; i < NUM_QUESTIONS; i++){
        answers[i] = b.answers[i];
    }
}




/* setLastName sets last name
 * Parameter last name string
 * Returns: nothing
 */
void Big5Assessment::setLastName (string& last){
    lastName = last;
}

/* setFirstName sets first name
 * Parameter first name string
 * Returns: nothing
 */
void Big5Assessment::setFirstName (string& first){
    firstName = first;
}

/* setAge sets age
 * Parameter age int
 * Returns: nothing
 */
void Big5Assessment::setAge (int& a){
    age = a;
}

/* setAnswer sets a single answer
 * Parameter answer int and question number int
 * Returns: nothing
 */
void Big5Assessment::setAnswer (int& a, int& q){
    answers[q] = a;
}

/* operator< returns true if one Big5Assessment b1 < Big5Assessment b2 (if one last name < another)
 * Parameters two Big5Assessments
 * Returns true if b1 last name < b2 last name
 */
bool operator<( const Big5Assessment& b1, const Big5Assessment& b2){
    string tempString1;
    string tempString2;
    
    //Make the keys lowercase (case insensitive test)
    tempString1 = (b1.getLastName() + " " + b1.getFirstName());
    for( int i = 0; i < (tempString1.length()); i++){
        tempString1[i] = tolower(tempString1[i]);
    }
    tempString2 = (b2.getLastName() + " " + b2.getFirstName());
    for( int i = 0; i < (tempString2.length()); i++){
        tempString2[i] = tolower(tempString2[i]);
    }
    
    if( tempString1 < tempString2){
        return (true);
    } else {
        return (false);
    }
}

/* overloaded == operator returns true if Big5Assessments full names are equal
 * Parameters: two Big5Assessments to compare
 * Returns true if Big5Assessments full names are equal
 */
bool operator==( const Big5Assessment& b1, const Big5Assessment& b2){
    string tempString1;
    string tempString2;
    
    //Make the keys lowercase (case insensitive test)
    tempString1 = (b1.getFirstName() + b1.getLastName());
    for( int i = 0; i < (tempString1.length()); i++){
        tempString1[i] = tolower(tempString1[i]);
    }
    tempString2 = (b2.getFirstName() + b2.getLastName());
    for( int i = 0; i < (tempString2.length()); i++){
        tempString2[i] = tolower(tempString2[i]);
    }
    

    if( tempString1 == tempString2){
        return (true);
    } else {
        return (false);
    }
}

/* operator<< overloaded for Big5Assessment object
 * Parameters:
 *    outStream the output stream
 *    b the Big5Assessment
 * Returns the output stream
 */
ostream& operator<<( ostream& outStream, Big5Assessment& b) {
    

    cout << b.getFirstName() << " " << b.getLastName() << " " << b.getAge() << endl << "\t";
    for (int i = 0; i < NUM_QUESTIONS; i++){
        cout << b.getAnswer(i) << " ";
    }
    cout << endl;
    

    return outStream;
}

/* operator>> overloaded for Big5Assessment object
 * Parameters:
 *    inStream the input stream
 *    b the Big5Assessment
 * Returns the input stream
 */
istream& operator>>( istream& in, Big5Assessment& b){
    string tempString;
    string tempString2;
    int lengthOfVar;
    int tempInt;
    
    getline(in, tempString);
    //Get Name from string
    lengthOfVar = tempString.find(' ');
    tempString2 = tempString.substr(0, lengthOfVar);
    b.setFirstName(tempString2);
    tempString.erase(0, (lengthOfVar + 1));
    
    
    lengthOfVar = tempString.find(' ');
    tempString2 = tempString.substr(0, lengthOfVar);
    b.setLastName(tempString2);
    tempString.erase(0, (lengthOfVar + 1));
    
    tempInt = std::stoi(tempString);
    b.setAge(tempInt);
    tempString.erase(0, (lengthOfVar + 1));
    
    getline(in, tempString);
    
    for(int i = 0; i < NUM_QUESTIONS; i++){
        tempInt = tempString.front();
        tempInt = (tempInt - 48);
        b.setAnswer(tempInt, i);
        tempString.erase(0,2);
    }


    return in;
};

/* write will write the Big5Assessment to the outstream
 * Parameters:
 *    outStream the output stream
 *    b the Big5Assessment
 * Returns the output stream
 */
ostream& Big5Assessment::write (ostream& out){
    struct big5struct {
        char lastName[51], firstName[51];
        int age;
        int answers[NUM_QUESTIONS];
    } big5AsC;
    
    //adjust from C++ string to C string
    strcpy(big5AsC.lastName, lastName.c_str());
    strcpy(big5AsC.firstName, firstName.c_str());
    big5AsC.age = age;
    for(int i = 0; i < NUM_QUESTIONS; i++){
        big5AsC.answers[i] = answers[i];
    }
    
    //write to file
    out.write( (char*)&big5AsC, sizeof(big5struct));
    
    
    return out;
};

/* read will read the Big5Assessment to the outstream
 * Parameters:
 *    iStream the input stream
 *    b the Big5Assessment
 * Returns the input stream
 */
istream& Big5Assessment::read (istream& in){
    struct big5struct {
        char lastName[51], firstName[51];
        int age;
        int answers[NUM_QUESTIONS];
    } big5AsC;
    
    //Read from file
    in.read( (char*)&big5AsC, sizeof(big5struct));
    
    //adjust from C string to C++ string
    lastName = big5AsC.lastName;
    firstName = big5AsC.firstName;
    age = big5AsC.age;
    for(int i = 0; i < NUM_QUESTIONS; i++){
        answers[i] = big5AsC.answers[i];
    }
    
    return in;
};

/* printNormalizedTraits will calculate the normalized traits and print 
 * them to the output stream
 * Parameters:
 *    the Big5Assessment
 * Returns nothing
 */
void Big5Assessment::printNormalizedTraits (){
    double e, a, c, n, o = 0;
    string lastName;
    string firstName;
    int age;
    int tempInt;
    
    lastName = this->getLastName();
    firstName = this->getFirstName();
    age = this->getAge();
                    
    //Calculate totals
    tempInt = 0;
    e = 20 + this->getAnswer(tempInt); //Q1
    tempInt = tempInt + 5;
    e = e - this->getAnswer(tempInt); //Q6
    tempInt = tempInt + 5;
    e = e + this->getAnswer(tempInt); //Q11
    tempInt = tempInt + 5;
    e = e - this->getAnswer(tempInt); //Q16
    tempInt = tempInt + 5;
    e = e + this->getAnswer(tempInt); //Q21
    tempInt = tempInt + 5;
    e = e - this->getAnswer(tempInt); //Q26
    tempInt = tempInt + 5;
    e = e + this->getAnswer(tempInt); //Q31
    tempInt = tempInt + 5;
    e = e - this->getAnswer(tempInt); //Q36
    tempInt = tempInt + 5;
    e = e + this->getAnswer(tempInt); //Q41
    tempInt = tempInt + 5;
    e = e - this->getAnswer(tempInt); //Q46
    
    tempInt = 1;
    a = 14 - this->getAnswer(tempInt); //Q2
    tempInt = tempInt + 5;
    a = a + this->getAnswer(tempInt); //Q7
    tempInt = tempInt + 5;
    a = a - this->getAnswer(tempInt); //Q12
    tempInt = tempInt + 5;
    a = a + this->getAnswer(tempInt); //Q17
    tempInt = tempInt + 5;
    a = a - this->getAnswer(tempInt); //Q22
    tempInt = tempInt + 5;
    a = a + this->getAnswer(tempInt); //Q27
    tempInt = tempInt + 5;
    a = a - this->getAnswer(tempInt); //Q32
    tempInt = tempInt + 5;
    a = a + this->getAnswer(tempInt); //Q37
    tempInt = tempInt + 5;
    a = a + this->getAnswer(tempInt); //Q42
    tempInt = tempInt + 5;
    a = a + this->getAnswer(tempInt); //Q47
                    
    tempInt = 2;
    c = 14 + this->getAnswer(tempInt); //Q3
    tempInt = tempInt + 5;
    c = c - this->getAnswer(tempInt); //Q8
    tempInt = tempInt + 5;
    c = c + this->getAnswer(tempInt); //Q13
    tempInt = tempInt + 5;
    c = c - this->getAnswer(tempInt); //Q18
    tempInt = tempInt + 5;
    c = c + this->getAnswer(tempInt); //Q23
    tempInt = tempInt + 5;
    c = c - this->getAnswer(tempInt); //Q28
    tempInt = tempInt + 5;
    c = c + this->getAnswer(tempInt); //Q33
    tempInt = tempInt + 5;
    c = c - this->getAnswer(tempInt); //Q38
    tempInt = tempInt + 5;
    c = c + this->getAnswer(tempInt); //Q43
    tempInt = tempInt + 5;
    c = c + this->getAnswer(tempInt); //Q48                    

    tempInt = 3;
    n = 38 - this->getAnswer(tempInt); //Q4
    tempInt = tempInt + 5;
    n = n + this->getAnswer(tempInt); //Q9
    tempInt = tempInt + 5;
    n = n - this->getAnswer(tempInt); //Q14
    tempInt = tempInt + 5;
    n = n + this->getAnswer(tempInt); //Q19
    tempInt = tempInt + 5;
    n = n - this->getAnswer(tempInt); //Q24
    tempInt = tempInt + 5;
    n = n - this->getAnswer(tempInt); //Q29
    tempInt = tempInt + 5;
    n = n - this->getAnswer(tempInt); //Q34
    tempInt = tempInt + 5;
    n = n - this->getAnswer(tempInt); //Q39
    tempInt = tempInt + 5;
    n = n - this->getAnswer(tempInt); //Q44
    tempInt = tempInt + 5;
    n = n - this->getAnswer(tempInt); //Q49                   
                    
    tempInt = 4;
    o = 8 + this->getAnswer(tempInt); //Q5
    tempInt = tempInt + 5;
    o = o - this->getAnswer(tempInt); //Q10
    tempInt = tempInt + 5;
    o = o + this->getAnswer(tempInt); //Q15
    tempInt = tempInt + 5;
    o = o - this->getAnswer(tempInt); //Q20
    tempInt = tempInt + 5;
    o = o + this->getAnswer(tempInt); //Q25
    tempInt = tempInt + 5;
    o = o - this->getAnswer(tempInt); //Q30
    tempInt = tempInt + 5;
    o = o + this->getAnswer(tempInt); //Q35
    tempInt = tempInt + 5;
    o = o + this->getAnswer(tempInt); //Q40
    tempInt = tempInt + 5;
    o = o + this->getAnswer(tempInt); //Q45
    tempInt = tempInt + 5;
    o = o + this->getAnswer(tempInt); //Q50
                    
                    
    //normalize to scale of 1-5
    e = (e + 10) / 10;
    a = (a + 10) / 10;
    c = (c + 10) / 10;
    n = (n + 10) / 10;
    o = (o + 10) / 10;
    
    //Print report
    cout << "Last Name       First Name       Age   E   A   C   N   O \n";
    cout << "-------------------------------------------------------- \n";
    cout << setw(16) << left << lastName;
    cout << setw(16) << left << firstName;
    cout << setw(4) << right << age;
    cout << setprecision(1) << fixed << setw(4) << right << e;
    cout << setprecision(1) << fixed << setw(4) << right << a;
    cout << setprecision(1) << fixed << setw(4) << right << c;
    cout << setprecision(1) << fixed << setw(4) << right << n;
    cout << setprecision(1) << fixed << setw(4) << right << o;
}