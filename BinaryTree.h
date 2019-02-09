// Binary tree abstract base class
// Created by Frank M. Carrano and Tim Henry.
// Modified by Trinh Nguyen
//  Trinh Nguyen
//  February 26, 2017
//  Homework #4
//  IDE: Xcode


#ifndef _BINARY_TREE
#define _BINARY_TREE
#include "BinaryNode.h"

template<class ItemType>
class BinaryTree
{
protected:
    BinaryNode<ItemType>* rootPtr;		// ptr to root node
    int count;							// number of nodes in tree
public:
    // "admin" functions
    BinaryTree() {
        rootPtr = 0; count = 0;
    }
    virtual ~BinaryTree() { }
    BinaryTree & operator = (const BinaryTree & sourceTree);
    BinaryTree(const BinaryTree<ItemType> & tree) {
        count = tree.count;
        if (tree.rootPtr)
        {
            rootPtr = new BinaryNode<ItemType>;
            rootPtr = tree.rootPtr;
        }
    }
    
    //Common functions for all binary trees
    bool isEmpty() const { return count == 0; }
    int size() const { return count; }
    void clear() { destroyTree(rootPtr); rootPtr = 0; count = 0; }
    void preOrder(void visit(ItemType &)) const { _preorder(visit, rootPtr); }
    void inOrder(void visit(ItemType &)) const { _inorder(visit, rootPtr); }
    void postOrder(void visit(ItemType &)) const { _postorder(visit, rootPtr); }
    
    //Abstract functions to be implemented by derived class
    virtual bool insert(const ItemType & newData) = 0;
    //virtual bool remove(const ItemType & data) = 0;
    virtual bool getEntry(const ItemType & anEntry, ItemType & returnedItem) const = 0;
    
    //Mutators
    BinaryNode<ItemType>* getRoot() { return rootPtr; }
    int getCount() { return count; }

    
private:
    // delete all nodes from the tree
    void destroyTree(BinaryNode<ItemType>* nodePtr);
    
    // internal traverse
    void _preorder(void visit(ItemType & ), BinaryNode<ItemType>* nodePtr) const;
    void _inorder(void visit(ItemType & ), BinaryNode<ItemType>* nodePtr) const;
    void _postorder(void visit(ItemType & ), BinaryNode<ItemType>* nodePtr) const;
    
};

//////////////////////////////////////////////////////////////////////////


template<class ItemType>
void BinaryTree<ItemType>::destroyTree(BinaryNode<ItemType>* nodePtr)
{
    BinaryNode<ItemType>* ptr = nodePtr;
    if (ptr == nullptr) return;
    if (ptr->getLeftPtr() != nullptr) destroyTree(ptr->getLeftPtr());
    if (ptr->getRightPtr() != nullptr) destroyTree(ptr->getRightPtr());
    delete ptr;
}

template<class ItemType>
void BinaryTree<ItemType>::_preorder(void visit(ItemType & ), BinaryNode<ItemType>* nodePtr) const
{
    if (nodePtr != 0)
    {
        ItemType item = nodePtr->getItem();
        visit(item);
        _preorder(visit, nodePtr->getRightPtr());
        _preorder(visit, nodePtr->getLeftPtr());
    }
}

template<class ItemType>
void BinaryTree<ItemType>::_inorder(void visit(ItemType & ), BinaryNode<ItemType>* nodePtr) const
{
    if (nodePtr != nullptr)
    {
        ItemType item = nodePtr->getItem();
        if (nodePtr->getLeftPtr() != nullptr)
        {
            _inorder(visit, nodePtr->getLeftPtr());
        }
        visit(item);
        if (nodePtr->getRightPtr() != nullptr)
        {
            _inorder(visit, nodePtr->getRightPtr());
        }
    }
}

template<class ItemType>
void BinaryTree<ItemType>::_postorder(void visit(ItemType & ), BinaryNode<ItemType>* nodePtr) const
{
    if (nodePtr != 0)
    {
        ItemType item = nodePtr->getItem();
        _postorder(visit, nodePtr->getLeftPtr());
        _postorder(visit, nodePtr->getRightPtr());
        visit(item);
    }
}

template<class ItemType>
BinaryTree<ItemType> & BinaryTree<ItemType>::operator=(const BinaryTree<ItemType> & sourceTree)
{
    if ((this = &sourceTree)) return *this;
    count = sourceTree.count;
    if (sourceTree.rootPtr)
    {
        rootPtr = new BinaryNode<ItemType>;
        rootPtr = sourceTree.rootPtr;
    }
    else rootPtr = nullptr;
    
    return *this;
}
#endif
