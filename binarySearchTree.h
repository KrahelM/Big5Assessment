#ifndef BINARYSEARCHTREE_H
#define BINARYSEARCHTREE_H

/* File: binarySearchTree.h
 * Author: Matthew Krahel
 * Description: Declares/Implements a BinarySearchTree Template Class
 */

#include "position.h"
#include "big5assessment.h"
#include <algorithm>
#include <iostream>
using namespace std;
// declaration for friend statement below
template<class T> class Position; 
 
const int PREORDER = 1;
const int INORDER = 2;
const int POSTORDER = 3;
 
template<class T>
class BinarySearchTree {
public:
   BinarySearchTree();
   BinarySearchTree( const BinarySearchTree& );
   Node<T>* copyTree(Node<T>*, Node<T>*);
   BinarySearchTree<T>& operator=( const BinarySearchTree<T>& );
   // returns num nodes in tree
   int size() const { return numNodes; } 
   // returns true if tree empty of real nodes
   bool empty() const { return numNodes == 0; } 
   // superroot right pointer always points to real root node
   Position<T> root() const { 
      return Position<T>( superRootPtr->rightPtr ); 
   } 
   void traverseAndPrint( const Position<T>& p, int type ) const;
   void preorderTraverseAndWrite( const Position<T>&, ostream&  ) const;
   int depth( const Position<T>& ) const;
   int height( const Position<T>& ) const; 
   Position<T> begin() const;
   // returns NULL iterator
   Position<T> end() const { return Position<T>( ); } 
   Position<T> find( const T& ) const;
   Position<T> insert( const T& );
   bool erase( const T& );
   bool erase( const Position<T>& );
   virtual ~BinarySearchTree() { deleteUtility(superRootPtr); }
   friend class Position<T>;
private:
	Node<T>* superRootPtr;
   // number real nodes in tree, not including fake super 
   // root and fake ends nodes 
   int numNodes; 
   void preorderTraverseAndPrint( const Position<T>& ) const;
   void inorderTraverseAndPrint( const Position<T>& ) const;
   void postorderTraverseAndPrint( const Position<T>& ) const;
   // finds item in tree starting at position
   Position<T> findUtility( const T& item, const Position<T>& ) const;
   // inserts item into tree
   Position<T> insertUtility( const T& item );
   // deletes all nodes in the tree
   void deleteUtility( Node<T>* );
   // erases just one node from the tree at position p
   Position<T> eraseUtility( const Position<T>& p);
   // insert item data at position p
   void expandExternal( const T& item, Position<T>& p); 
   // remove node above fake leaf node at position p
   Position<T> removeAboveExternal( const Position<T>& p ); 
};

//Default Constructor
template<class T>
BinarySearchTree<T>::BinarySearchTree()
{
	superRootPtr = new Node<T>();
	superRootPtr->rightPtr = new Node<T>();
	superRootPtr->rightPtr->parentPtr = superRootPtr;
	superRootPtr->leftPtr = NULL;
	numNodes = 0;
}

//Copy Constructor
template<class T>
BinarySearchTree<T>::BinarySearchTree(const BinarySearchTree& tree)
{
	numNodes = tree.numNodes;
    superRootPtr = new Node<T>();
    if(tree.empty()){
        superRootPtr.rightPtr = new Node<T>();
        superRootPtr.rightPtr.parentPtr = superRootPtr;
    } else {
        superRootPtr.rightPtr = copyTree(superRootPtr, tree.superRootPtr.rightPtr);
    }
}

/* copyTree utility function that copies one tree to this' tree
 * Parameters
 *    p pointer to parent in this' tree that new node's 
         parentPtr should point to
 *    n pointer to new node in tree to copy from
 * Returns pointer to node just allocated for this' tree or NULL 
 *   (if at the end of a branch) and no new node to copy
 */
template<class T>
Node<T>* BinarySearchTree<T>::copyTree(Node<T>* pPtr, Node<T>* nPtr)
{
	if (nPtr != NULL){
        Node<T> newNode = node(*nPtr);
        newNode.parentPtr = pPtr;
        newNode.leftPtr = copyTree(newNode, nPtr.leftPtr);
        newNode.rightPtr = copyTree(newNode, nPtr.rightPtr);
        return newNode;
    } else {
        return NULL;
    }
}

/* overloaded = operator deletes current object, copies object 2 to current object
 * Parameters: current tree object and second tree object
 * Returns current tree object
 */
 template <class T>
 BinarySearchTree<T>& BinarySearchTree<T>::operator=( const BinarySearchTree<T>& tree){
    deleteUtility(this->superRootPtr);
    numNodes = tree.numNodes;
    superRootPtr = new Node<T>();
    if(tree.empty()){
        superRootPtr.rightPtr = new Node<T>();
        superRootPtr.rightPtr.parentPtr = superRootPtr;
    } else {
        superRootPtr.rightPtr = copyTree(superRootPtr, tree.superRootPtr.rightPtr);
    }
    return *this;
 }

/* depth returns distance from root to node at parameter
 * position
 * Parameter:
 *   p position to compute depth of
 * Returns depth or -1 if position p is superroot
*/
template<class T>
int BinarySearchTree<T>::depth( const Position<T>& p ) const 
{
	if ( p.isSuperRoot()) return -1;
	if ( p.isRoot()) return 0;
	else 
	{
		return 1+depth( p.parent() );
	}
}


/* height returns distance from node at parameter position to
 * lowest leaf
 * Parameter: position to computer height of
*/
template<class T>
int BinarySearchTree<T>::height( const Position<T>& p ) const 
{
	// if leaf
	if ( p.isExternal() ) return 0;
	int h = 0;
	// h = max of 0 and height of left subtree
	h= max( h, height( Position<T>(p.nodePtr->leftPtr) ) ); 
	// h = max of height of left subtree and 
	// height of right subtree
	h = max( h, height( Position<T>( p.nodePtr->rightPtr ) ) );
	return 1 + h; 
}


/* begin: returns position iterator to first node on tree - the leftmost
 */
template<class T>
Position<T> BinarySearchTree<T>::begin() const 
{
	if ( numNodes > 0 ) 
	{
		Position<T> p = root();
		while (p.isInternal()) 
		{
			p = p.left();
		}
		
      return p.parent();
	}

   else return Position<T>( superRootPtr );
}


/* finds a T object in tree
 * Parameters: the object to find
 * Pre-condition: class T has overloaded operator==
 * Returns iterator to object, superroot iterator if tree
 *   is empty, fake leaf postion if not found
 */
template<class T>
Position<T> BinarySearchTree<T>::find( const T& item ) const 
{
	if ( numNodes > 0 )
	{
		Position<T> v = findUtility( item, root());
		return v;
	}

   else return Position<T>(superRootPtr);
}


/* findUtility: recursive utility find function
 * Parameters: 
 *   item to look for
 *   p position to start looking from 
 * Pre-condition: class T has overloaded operator== and 
 *   operator<, tree not empty of real nodes
 * Returns position iterator where found or NULL iterator
 */
template<class T>
Position<T> BinarySearchTree<T>::findUtility( const T& item, const Position<T>& p) const
{
	if(p.isExternal())
	{
		return p;
	}
	else if(p.nodePtr->item == item)
	{
		return p;
	}
	else if(item < p.nodePtr->item)
	{
		return findUtility( item,  p.left());
	}
	else
		return findUtility(item, p.right());

}

/*
 * deleteUtility: a post-order traversal used to
 * delete a node
 * Parameters: a pointer to a node
 */
template<class T>
void BinarySearchTree<T>::deleteUtility( Node<T>* nPtr)
 {
	 if(nPtr != NULL)
	 {
		 deleteUtility(nPtr->leftPtr);
		 deleteUtility(nPtr->rightPtr);
		 delete(nPtr);
	 }
 }
 
 /* expandExternal - inserts item by copying its data to 
 *   position p and setting position's left and right ptrs 
 *   to end nodes
 * Parameters
 *   item to be inserted
 *   p fake end node where item will be inserted
 * Precondition: p is an external node (a fake leaf) and 
 *    class T has overloaded = operator
 */
template <class T>
void BinarySearchTree<T>::expandExternal( const T& item, Position<T>& p)
{
	Node<T>* left = new Node<T>;
	Node<T>* right = new Node<T>;
	p.nodePtr->leftPtr = left;
	p.nodePtr->rightPtr = right;
	left->parentPtr = p.nodePtr;
	right->parentPtr = p.nodePtr;
	p.nodePtr->item = item;
	numNodes++;
}



/* inserts object T in the binary tree
 * Parameter: the object to insert
 * Pre-condition: class T has overloaded operator<
 * Returns iterator to newly inserted object or superRootPtr
 *    if item already in tree
 */
template<class T>
Position<T> BinarySearchTree<T>::insert( const T& item ) {
   // root() = superroot's right ptr 
   Position<T> p = insertUtility( item ); 
   // return iterator to position where new node inserted
   return p; 
}


/* insertUtility: inserts at position for new node
 * Parameters: new node to insert
 * Returns iterator to newly inserted object or to superRoot
 *    fake node if item already in tree
 */
template <class T>
Position<T> BinarySearchTree<T>::insertUtility( const T& item )
{
	Position<T> foundPos = findUtility(item, root());
	
	if(foundPos.isExternal())
	{
		expandExternal(item, foundPos);
		return foundPos;
	}
	else
	{
		return superRootPtr;
	}
}


/* removeAboveExternal: removes internal node just above fake
     leaf node pointed to by p. Decrements number of nodes 
     in tree.
   Parameter 
     p leaf node of real node to delete
 * Returns position iterator to sibling of node removed
 */
template<class T>
Position<T> BinarySearchTree<T>::removeAboveExternal( const Position<T>& p )
{
	Node<T>* w = p.nodePtr;
	Node<T>* v = w->parentPtr;;
	Node<T>* siblingPtr;
	Node<T>* grandparentPtr;
	if(w == v->leftPtr)
	{
		siblingPtr = v->rightPtr;
	}
	else
	{
		siblingPtr = v->leftPtr;
	}
	if(v == superRootPtr->rightPtr)
	{
		superRootPtr->rightPtr = siblingPtr;
		siblingPtr->parentPtr = superRootPtr;
	}
	else
	{
		grandparentPtr = v->parentPtr;
		if(v == v->parentPtr->leftPtr)
		{
			grandparentPtr->leftPtr = siblingPtr;
		}
		else
		{
			grandparentPtr->rightPtr = siblingPtr;
		}
		
		siblingPtr->parentPtr = grandparentPtr;
	}
	
	delete(w);
	delete(v);
	numNodes--;
	return Position<T>( siblingPtr );
}


/* erase removes a node above Position p
 * Precondition position p is a valid position in tree
 * Returns true if successful
 */
template<class T>
bool BinarySearchTree<T>::erase( const Position<T>& p ) {
   // can't remove superroot or fake external node
   if ( !p.isSuperRoot() && !p.isExternal() ) { 
      eraseUtility( p );
      return true;
   }
   else
      return false;
}

/*
 * eraseUtility: determines a leaf node to swap with the node 
 * to delete
 * Parameters: a const reference to a Position
 * Returns: A call to remove above external with
 * Position w as the argument, a position
 */
template<class T>
Position<T> BinarySearchTree<T>::eraseUtility( const Position<T>& p)
{
	Position<T> w;
	Position<T> u;
	if(p.left().isExternal())
	{
		w = p.left();
	}
	else if(p.right().isExternal())
	{
		w = p.right();
	}
	else
	{
		w = p.right();
		do
		{
			w = w.left();
		}while( w.isInternal() );
		
		u = w.parent();
		p.nodePtr->setItem(u.nodePtr->getItem());
	}

	return ( removeAboveExternal(w) );
}

/*
 * preorderTraverseAndPrint:
 * performs a pre-order traversal of the tree and prints
 * data inside of the tree's nodes
 * Parameters: a constant reference to a Position<T> p
 */
template<class T>
void BinarySearchTree<T>::preorderTraverseAndPrint( const Position<T>& p) const
{
	if(p.isInternal())
	{
		cout << p.nodePtr->item;
		preorderTraverseAndPrint( p.nodePtr->leftPtr );
		preorderTraverseAndPrint( p.nodePtr->rightPtr );
	}
}

/*
 * inorderTraverseAndPrint:
 * performs an in-order traversal of the tree
 * and prints data inside the nodes
 * Parameters: a constant reference to a Position<T> p
 */
template<class T>
void BinarySearchTree<T>::inorderTraverseAndPrint( const Position<T>& p) const
{
	if(p.isInternal())
	{
		inorderTraverseAndPrint(p.nodePtr->leftPtr);
		cout << p.nodePtr->item << "  ";
		inorderTraverseAndPrint(p.nodePtr->rightPtr);
	}
}

/*
 * postorderTraverseAndPrint:
 * performs a post-order traversal of the tree
 * and prints the data inside of each node
 * Parameters: a constant reference to a Position<T> p
 */
template<class T>
void BinarySearchTree<T>::postorderTraverseAndPrint( const Position<T>& p) const
{
	if(p.isInternal())
	{
		postorderTraverseAndPrint(p.nodePtr->leftPtr);
		postorderTraverseAndPrint(p.nodePtr->rightPtr);
		cout << p.nodePtr->item << "  ";
	}
}

/*
 * traverseAndPrint: traverses the tree based on which type of traversal
 * is passed (see constant values defined at top of file)
 * Parameters: Constant reference to a Position<T> p and
 * an interger value for type
 */
template<class T>
void BinarySearchTree<T>::traverseAndPrint( const Position<T>& p, int type ) const
{
	if(type == PREORDER)
	{
		preorderTraverseAndPrint(p);
	}
	else if (type == INORDER)
	{
		inorderTraverseAndPrint(p);
	}
	else
	{
		postorderTraverseAndPrint(p);
	}
}

/*
 * Same as the erase function that takes a Position<T> parameter,
 * but this version of the function takes an item as a parameter (type T)
 * Returns: true if successful
 */
template<class T>
bool BinarySearchTree<T>::erase( const T& i)
{
	Position<T> p = findUtility(i, root());
	if ( !p.isSuperRoot() && !p.isExternal() )
	{	
		//Position<T> p = findUtility(i, root());
		eraseUtility(p);
		return true;
	}
	else
		return false;
}


/*
 * preorderTraverseAndWrite:
 * performs a pre-order traversal of the tree and writes to outstream
 * data inside of the tree's nodes
 * Parameters: a constant reference to a Position<T> p and an oustream
 */
template<class T>
void BinarySearchTree<T>::preorderTraverseAndWrite( const Position<T>& p, ostream& outStream) const
{
	if(p.isInternal() && !p.isSuperRoot() )
	{
		p.nodePtr->item.write(outStream);
		preorderTraverseAndWrite( p.nodePtr->leftPtr, outStream );
		preorderTraverseAndWrite( p.nodePtr->rightPtr, outStream );
	}
}



#endif 