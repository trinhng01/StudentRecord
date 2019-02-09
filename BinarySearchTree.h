// Binary Search Tree ADT
// Created by Frank M. Carrano and Tim Henry.
// Modified by Trinh Nguyen
//  Trinh Nguyen
//  February 26, 2017
//  Homework #4
//  IDE: Xcode


 
#ifndef _BINARY_SEARCH_TREE
#define _BINARY_SEARCH_TREE

#include "BinaryTree.h"

template<class ItemType>
class BinarySearchTree : public BinaryTree<ItemType>
{   
private:
	// internal insert node: insert newNode in nodePtr subtree
	void _insert(BinaryNode<ItemType> & nodePtr, BinaryNode<ItemType> &newNode);
   
	// internal remove node: locate and delete target node under nodePtr subtree
	BinaryNode<ItemType>* _remove(BinaryNode<ItemType>* nodePtr, const ItemType target, bool & success);
   
	// delete target node from tree, called by internal remove node
	BinaryNode<ItemType>* deleteNode(BinaryNode<ItemType>* targetNodePtr);
   
	// remove the leftmost node in the left subtree of nodePtr
	BinaryNode<ItemType>* removeLeftmostNode(BinaryNode<ItemType>* nodePtr, ItemType & successor);
   
	// search for target node
	BinaryNode<ItemType>* findNode(BinaryNode<ItemType>* treePtr, const ItemType & target) const;
    
    //find most right in tree
    BinaryNode<ItemType>* _findLargest(BinaryNode<ItemType>* rootPtr);
    
    //find most left in tree
    BinaryNode<ItemType>* _findSmallest(BinaryNode<ItemType>* rootPtr);
   
public:  
	// insert a node at the correct location
    bool insert(const ItemType & newEntry);
	// remove a node if found
	bool remove(const ItemType & anEntry);
	// find a target node
	bool getEntry(const ItemType & target, ItemType & returnedItem) const;
    // find largest
    BinaryNode<ItemType>* findLargest();
    // find smallest
    BinaryNode<ItemType>* findSmallest();

};


///////////////////////// public function definitions ///////////////////////////

//PUBLIC INSERT FUNCTION
template<class ItemType>
bool BinarySearchTree<ItemType>::insert(const ItemType & newEntry)
{
	if (this->rootPtr == nullptr) {
		this->rootPtr = new BinaryNode<ItemType>(newEntry);
		this->count++;
	}
	else {
		BinaryNode<ItemType>* nodePtr = new BinaryNode<ItemType>(newEntry);
		_insert(*this->rootPtr, *nodePtr);
	}
	return true;
}  

//PUBLIC REMOVE FUNCTION
template<class ItemType>
bool BinarySearchTree<ItemType>::remove(const ItemType & target)
{
	bool isSuccessful = false;
	this->rootPtr = _remove(this->rootPtr, target, isSuccessful);
	return isSuccessful; 
}  

//PUBLIC SEARCH FUNCTION
template<class ItemType>
bool BinarySearchTree<ItemType>::getEntry(const ItemType& anEntry, ItemType & returnedItem) const
{
	BinaryNode<ItemType>* newNodePtr = new BinaryNode<ItemType>(anEntry);
	newNodePtr = findNode(this->rootPtr, anEntry);
	if (newNodePtr)
	{
		returnedItem = newNodePtr->getItem();
		return true;
	}
	else return false;
}  

//PUBLIC FIND LARGEST FUNCTION
template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::findLargest()
{
    BinaryNode<ItemType>* Largest = _findLargest(this->rootPtr);
    return Largest;
}

//PUBLIC FIND SMALLEST FUNCTION
template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::findSmallest()
{
    BinaryNode<ItemType>* Smallest = _findSmallest(this->rootPtr);
    return Smallest;
}

//////////////////////////// private functions ////////////////////////////////////////////

//PRIVATE INSERT FUNCTION
template<class ItemType>
void BinarySearchTree<ItemType>::_insert(BinaryNode<ItemType> & node,
                                                          BinaryNode<ItemType> & newNode)
{
	if (newNode.getItem() < node.getItem())
	{
		if (node.getLeftPtr() != nullptr)
		{
			_insert(*node.getLeftPtr(), newNode);
		}
		else // until its left child is null
		{
			node.setLeftPtr(&newNode);
			this->count++;
		}
	}
	else if (newNode.getItem() > node.getItem() || newNode.getItem() == node.getItem())
	{
		if (node.getRightPtr() != nullptr)
		{
			_insert(*node.getRightPtr(), newNode);
		}
		else
		{
			node.setRightPtr(&newNode);
			this->count++;
		}
	}
}  

//PRIVATE REMOVE FUNCTION
template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::_remove(BinaryNode<ItemType>* nodePtr,
                                                          const ItemType target,
                                                          bool & success)

{
	if (nodePtr == 0)                   
	{
		success = false;
		return 0;
	}
	if (nodePtr->getItem() > target)		 
		nodePtr->setLeftPtr(_remove(nodePtr->getLeftPtr(), target, success));
	else if (nodePtr->getItem() < target)	 
		nodePtr->setRightPtr(_remove(nodePtr->getRightPtr(), target, success));
	else		
	{
		nodePtr = deleteNode(nodePtr);
		this->count--;
		success = true;
	}      
	return nodePtr;   
}  

//PRIVATE DELETE NODE FUNCTION
template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::deleteNode(BinaryNode<ItemType>* nodePtr)
{
	if (nodePtr->isLeaf())				
	{
		delete nodePtr;
		nodePtr = 0;
		return nodePtr;
	}
	else if (nodePtr->getLeftPtr() == 0)  
	{
		BinaryNode<ItemType>* nodeToConnectPtr = nodePtr->getRightPtr();
		delete nodePtr;
		nodePtr = 0;
		return nodeToConnectPtr;
	}
	else if (nodePtr->getRightPtr() == 0) 
	{
		BinaryNode<ItemType>* nodeToConnectPtr = nodePtr->getLeftPtr();
		delete nodePtr;
		nodePtr = 0;
		return nodeToConnectPtr;      
	}
	else                                  
	{
		ItemType newNodeValue;
		nodePtr->setRightPtr(removeLeftmostNode(nodePtr->getRightPtr(), newNodeValue));
		nodePtr->setItem(newNodeValue);
		return nodePtr;
	}  
}  

//PRIVATE REMOVE LEFTMOST NODE FUNCTION
template<class ItemType> 
BinaryNode<ItemType>* BinarySearchTree<ItemType>::removeLeftmostNode(BinaryNode<ItemType>* nodePtr,
                                                                     ItemType & successor)
{
	if (nodePtr->getLeftPtr() == 0)
	{
		successor = nodePtr->getItem();
		return deleteNode(nodePtr);
	}
	else 
	{
		nodePtr->setLeftPtr(removeLeftmostNode(nodePtr->getLeftPtr(), successor));
		return nodePtr;
	}       
}

//PRIVATE FIND NODE FUNCTION
template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::findNode(BinaryNode<ItemType>* root,
                                                           const ItemType & target) const 
{
	if (root != nullptr)
	{
		if (root->getItem() == target) return root;
		if (root->getItem() < target) return findNode(root->getRightPtr(), target);
		else return findNode(root->getLeftPtr(), target);
	}
	else return nullptr;
}

//PRIVATE FIND SMALLEST NODE FUNCTION
template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::_findSmallest(BinaryNode<ItemType>* rootPtr)
{
    BinaryNode<ItemType>* smallest;
    if (rootPtr->getLeftPtr() != NULL)
    {
        smallest = _findSmallest(rootPtr->getLeftPtr());
        return smallest;
    }
    else
        return rootPtr;
}

//PRIVATE FIND LARGEST NODE FUNCTION
template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::_findLargest(BinaryNode<ItemType>* rootPtr)
{
    BinaryNode<ItemType>* largest;
    if (rootPtr->getRightPtr() != NULL)
    {
        largest = _findLargest(rootPtr->getRightPtr());
        return largest;
    }
    else
        return rootPtr;
}


#endif
