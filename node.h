#ifndef NODE_H
#define NODE_H

/* File: node.h
 * Author: Matthew Krahel
 * Description: Declares/Implements a Node Template Class
 */


#include <stdio.h>
#include <iostream>
#include <cstdlib>

using namespace std;


template<class T> class BinarySearchTree; // declaration for friend statement below
template<class T> class Position; // declaration for friend statement below

template<class T>
class Node {
public:
   Node(); // default constuctor
   // constructor that takes node’s dat
   Node( const T& ); 
   // copy constructor. 
   Node( const Node<T>& );  
   virtual ~Node<T>() {} // destructor
   void setItem( const T& ); 
   T getItem() { return item; } 
   Node<T>& operator=( const Node<T>& );
   friend class BinarySearchTree<T>;
   friend class Position<T>; // Position is an iterator class
private:
   Node<T>* leftPtr;
   Node<T>* rightPtr;
   Node<T>* parentPtr;
   T item;
};

// set item
template<class T>
void Node<T>::setItem(const T& i)
{
	item = i;
}

// default constructor 
template <class T>
Node<T>::Node()
{
	leftPtr = rightPtr = parentPtr = NULL;
}

// constructor that takes date
template <class T>
Node<T>::Node(const T& i)
{
	setItem(i);
}

// Copy constructor 
template <class T>
Node<T>::Node(const Node<T>& n)
{
	leftPtr = rightPtr = parentPtr = "NULL";
	this->item = n->item;
}

//Overloaded operator=
template <class T>
Node<T>& Node<T>::operator=(const Node<T>& n)
{
	leftPtr = rightPtr = parentPtr = "NULL";
	item = n->item;
	return *this;
}

#endif