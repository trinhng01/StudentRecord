// Node for a binary tree
// Created by Frank M. Carrano and Tim Henry.
// Modified by Trinh Nguyen

//  Trinh Nguyen
//  February 26, 2017
//  Homework #4
//  IDE: Xcode

#ifndef _BINARY_NODE
#define _BINARY_NODE

template<class ItemType>
class BinaryNode
{   
private:
	ItemType              item;         // Data portion
	BinaryNode<ItemType>* leftPtr;		// Pointer to left child
	BinaryNode<ItemType>* rightPtr;		// Pointer to right child

public:
	//Constructors
	BinaryNode() { leftPtr = 0; rightPtr = 0; }
	BinaryNode(const ItemType & anItem) { item = anItem; leftPtr = 0; rightPtr = 0; }
	BinaryNode(const ItemType & anItem, 
		       BinaryNode<ItemType>* left, 
			   BinaryNode<ItemType>* right) {item = anItem; leftPtr = left; rightPtr = right;}
	
    //Accessors
	void setItem(const ItemType & anItem) {item = anItem;}
	void setLeftPtr(BinaryNode<ItemType>* left) {leftPtr = left;}
    void setRightPtr(BinaryNode<ItemType>* right) {rightPtr = right;}
	
    //Mutators
	ItemType getItem()	 {return item;}
	BinaryNode<ItemType>* getLeftPtr() const  {return leftPtr;}
	BinaryNode<ItemType>* getRightPtr() const {return rightPtr;}
	BinaryNode<ItemType> & operator=(BinaryNode<ItemType> & sourceNode)
	{
		if (this == &sourceNode) return *this;
		item = sourceNode.getItem();
		if (sourceNode.getLeftPtr())
		{
			leftPtr = new BinaryNode<ItemType>;
			leftPtr = sourceNode.getLeftPtr();
		}
		else leftPtr = nullptr;
		if (sourceNode.getRightPtr())
		{
			rightPtr = new BinaryNode<ItemType>;
			rightPtr = sourceNode.getRightPtr();
		}
		else rightPtr = nullptr;

		return *this;
	}

	bool isLeaf() const {return (leftPtr == 0 && rightPtr == 0);}
}; 

#endif 
