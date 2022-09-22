#ifndef POSITION_H
#define POSITION_H

/* File: position.h
 * Author: Matthew Krahel
 * Description: Declares/Implements a Position Template Class
 */

#include "node.h"
#include "big5assessment.h"

template<class T> class BinarySearchTree; // declaration for friend statement below
 
template<class T> 
class Position {
public:   
	Node<T>& operator*() { return *nodePtr; }
	Position parent() const { 
      return Position<T>( this->nodePtr->parentPtr ); } 
	Position left() const { 
      return Position<T>( nodePtr->leftPtr ); }
	Position right() const { 
      return Position<T>( nodePtr->rightPtr ); }
    bool isRoot( ) const {
      // does this iterator point to real root?
      return this->nodePtr->parentPtr->parentPtr == NULL; } 
	bool isSuperRoot() const{ 
      // does this iterator point to fake superroot?
      return this->nodePtr->parentPtr == NULL; } 
	bool isExternal() const { 
		// is it a fake end node?
      return this->nodePtr->leftPtr == NULL && 
      this->nodePtr->rightPtr == NULL; }
	bool isInternal() const { return !(isExternal() ); }
	bool operator==( const Position& p ) { 
      return this->nodePtr == p.nodePtr; }
	Position& operator=(Position<T> p){
		this->nodePtr = p.nodePtr;
			return *this;
	}
	bool operator!=(Position<T> p){
		return (!(*this == p));
	}
	Position& operator++( ); // inorder traversal
	T getItem() { return nodePtr->item; }
	friend class BinarySearchTree<T>;
	
   
private:
	// only friends like BST can create positions from its nodes
	Position(): nodePtr(NULL) { }
	Position( Node<T>* );
	Node<T>* nodePtr;
};

/*
 * 1-arg constructor
 * Parameters: A pointer to a Node<T> n
 */
template<class T>
Position<T>::Position( Node<T>* n)
{
	nodePtr = n;
}

/*
 * operator++
 * Iterates through the tree
 * in-order traversal
 */
template<class T>
Position<T>& Position<T>::operator++()
{
	Position<T> w = this->right();
	if(w.isInternal())
	{
		do
		{
			*this = w.nodePtr;
			w = w.left();

		}while(w.isInternal());
	}
	else
	{
		w = this->parent();

		while(w.nodePtr != "NULL" && *this == w.right())
		{
			*this = w;
			w = w.parent();
		}

		*this = w;
	}

	return *this;
}

#endif