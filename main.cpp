/* File: main.cpp
 * Author: Matthew Krahel
 * Description: Opens a binary file of Big 5 Assessments, places them in a 
 * binary search tree, gives user a menu to choose from to add an assessment,
 * remove an assessment, report an assessment, or print a preorder of the tree,
 * afterwards it will save the tree to the binary file and exit
 */

#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <string>
#include <iomanip>
#include "big5assessment.h"
#include "node.h"
#include "position.h"
#include "binarySearchTree.h"

using namespace std;

int main(int argc, char **argv)
{
    string fileName = "assessment.bin";
    ifstream in;
    ofstream out;
    BinarySearchTree<Big5Assessment> tree;
    Big5Assessment big5;
    Big5Assessment big5two;
    Big5Assessment big5three;
    char menuChoice = '0';
    char tempChar;
    string lastName;
    string firstName;
    int age;
    int tempInt;
    
    
    //open binary file
    in.open( fileName, ios::in | ios::binary);
    ////in.open( "Big5Assessments.txt");
    
    //Test if file opened
    if ( !in.fail() ) {
        
        //Test if file is empty
        in.get(tempChar);
        if(!in.eof()){
            in.putback(tempChar);
            ////cout << "good file open";
            
            in.get(tempChar);
            while(!in.eof()){
                in.putback(tempChar);
                ////in >> big5;
                big5.read(in);
                
                ////cout << big5.getFirstName() << big5.getLastName() << big5.getAge() << endl;
                tree.insert(big5);
                in.get(tempChar);
            }
            
        } else { //File is empty
            
        }
    } else{ //File not loaded
        
        
    }
    
    in.close();
    
    //Print Menu
    while (menuChoice != '5'){
        cout << endl;
        cout << "1 Add assessment" << endl;
        cout << "2 Remove assessment" << endl;
        cout << "3 Report assessment" << endl;
        cout << "4 Pre-order print" << endl;
        cout << "5 Exit and save" << endl;
        cout << "Option: ";
        cin >> menuChoice;
        cout << endl;
        
        switch(menuChoice) {
            case '1' : {//add assessment
                cout << endl << "Add Assessment" << endl; 
                cout << "Last Name: ";
                cin >> lastName;
                cout << endl << "First Name: ";
                cin >> firstName;
                cout << endl;
                
                big5two.setFirstName(firstName);
                big5two.setLastName(lastName);
                
                //Check if assessment already there
                Position<Big5Assessment> p = tree.find(big5two);
                if ( p.isInternal() && !tree.empty()) { 
                    cout << firstName << " " << lastName << " already has an assessment." << endl;
                } else{
                    cout << "Age: ";
                    cin >> age;
                    big5two.setAge(age);
                    cout << endl << "50 question answers: ";
                    for(int i = 0; i < NUM_QUESTIONS; i++){
                        cin >> tempInt;
                        big5two.setAnswer(tempInt, i);
                        cout << " ";
                    }
                    tree.insert(big5two);
                    cout << firstName << " " << lastName << " has been added." << endl;
                }
                
                
                break;
            }
            case '2' :{//remove assessment
                cout << endl << "Remove Assessment" << endl; 
                cout << "Last Name: ";
                cin >> lastName;
                cout << endl << "First Name: ";
                cin >> firstName;
                cout << endl;
                
                big5two.setFirstName(firstName);
                big5two.setLastName(lastName);
                
                //Check if assessment already there
                Position<Big5Assessment> p = tree.find(big5two);
                if ( p.isExternal() || tree.empty()) { 
                    cout << firstName << " " << lastName << " does not have an assessment." << endl;
                } else {
                    big5two = (*p).getItem();
                    cout << "Removed: ";
                    cout << big5two;
                    
                    tree.erase(big5two);
                }
                break;
            }
            case '3' :{ //Report assessment
                cout << endl << "Report Assessment" << endl; 
                cout << "Last Name: ";
                cin >> lastName;
                cout << endl << "First Name: ";
                cin >> firstName;
                cout << endl;
                
                big5two.setFirstName(firstName);
                big5two.setLastName(lastName);
                
                //Check if assessment already there
                Position<Big5Assessment> p = tree.find(big5two);
                if ( p.isExternal() || tree.empty()) { 
                    cout << firstName << " " << lastName << " does not have an assessment." << endl;
                } else { //print assessment report
                    big5two = (*p).getItem();
                    big5two.printNormalizedTraits();
                }

                break;
                
            }
            case '4' :{ //Pre-Order Print
                tree.traverseAndPrint( tree.root(), PREORDER);
                break;
            }
            case '5' :{ //Exit Program
                break;
            }
            default :
                cout << "Incorrect Menu Choice Please Input Correct Option" << endl;
        }
        
    }
    
    
    
    //Output tree to binary file
    out.open(fileName, ios::out | ios::binary);
    
    tree.preorderTraverseAndWrite( tree.root(), out);
    
    out.close();
    
	
	return 0;
}
