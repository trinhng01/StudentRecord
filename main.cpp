// main test driver for BST
// Created by Frank M. Carrano and Tim Henry.
// Modified by Trinh Nguyen

//  CIS 22C-02Y
//  M/W 1:30 - 3:20
//  Professor Delia Gârbacea
//  Trinh Nguyen
//  February 26, 2017
//  Homework #5
//  IDE: Xcode


#include <iostream>
#include <string>
#include <fstream>
#include <stack>
#include <iomanip>
#include "BinarySearchTree.h"
#include "Student.h"
#include "Queue.h"
#include "Stack.h"
using namespace std;

//Function Prototype
void readFile(string filename, BinarySearchTree<Student>&studentList);
string validInput();
int validInput2();
char DFTMenuInput();
void displayNode(Student&student);
void displayMenu();
void ProcessAction(BinarySearchTree<Student>&studentList);
void optionD(BinarySearchTree<Student>&studentList);
void optionI(BinarySearchTree<Student>&studentList);
void optionB(BinarySearchTree<Student>&studentList);
void optionS(BinarySearchTree<Student>&studentList);
void optionM(BinarySearchTree<Student>&studentList);
void optionX(BinarySearchTree<Student>&studentList);
void optionT(BinaryNode<Student>*root, int level);
void optionA();


int main()
{
    string fileName = "gpa.txt";
    BinarySearchTree<Student> studentList;
    readFile(fileName, studentList);
    ProcessAction(studentList);
    return 0;
}

//readFile function reads data from input file and insert them to BST
void readFile(string filename, BinarySearchTree<Student> &studentList)
{
    string tempName = "";
    int tempID;
    double tempGPA;
    
    ifstream inputfile;
    inputfile.open(filename);
    
    if(!inputfile.good())
    {
        cout <<"Error opening file!\n";
        exit(-1);
    }
    
    while (inputfile.good())
    {
        Student data;
        inputfile >> tempID;
        data.setID(tempID);
        
        inputfile.ignore();
        getline(inputfile, tempName, ';');
        data.setName(tempName);
        
        inputfile.ignore();
        inputfile >> tempGPA;
        data.setGPA(tempGPA);
        
        studentList.insert(data);
        inputfile.ignore();
    }
    cout << fixed << setprecision(1);
    inputfile.close();
}

//validInput function validate user input in the main menu
string validInput()
{
    string input;
    getline(cin, input);
    input[0] = toupper(input[0]);
    if (input != "D" && input != "I" && input != "B" && input != "S" && input != "M"
        && input != "X" && input != "T" && input != "A" && input != "H" && input != "E")
    {
        cout << "Please enter a valid option following the menu provided above. ";
        input = validInput();
    }
    return input;
}

//validInput2 function checks for valid input in optionS
int validInput2()
{
    int input;
    cout << "Please enter 4-digit Student ID ==> ";
    cin >> input;
    input = toupper(input);
    if (input <= 0 || input > 9999)
    {
        input = validInput2();
    }
    return input;
}

//DFTMenuInput function validate user input in depth-first traversals menu
char DFTMenuInput()
{
    char option;
    cout << "\tThere are 3 choices:\n";
    cout << "\t\t1. Preorder\n\t\t2. Inorder\n\t\t3. Postorder\nYour choice ==> ";
    cin >> option;
    if (option != '1' && option != '2' && option != '3'){
        option = DFTMenuInput();
    }
    return option;
}

//displayMenu function displays main menu
void displayMenu()
{
    cout << "\n=== === === === === === MENU OF SERVICES === === === === === ===\n"
    "D – Depth-First Traversals: inorder, preorder, postorder\n"
    "I – Iterative Depth-First Traversals: inorder, preorder, postorder\n"
    "B – Tree Breadth-First Traversals: Print by level\n"
    "S – Search by the primary key\n"
    "M – Find the smallest\n"
    "X – Find the largest\n"
    "T – Print the BST as an indented list\n"
    "H – Help – to show the menu, and\n"
    "E – Exit.\n";
    return;
}

//displayNode function display a single node
void displayNode(Student &student)
{
    cout << student.getID() << "\t\t"  << student.getGPA() << "\t\t" << student.getName() << endl;
}

//ProcessAction function process according to user input
void ProcessAction(BinarySearchTree<Student>&studentList)
{
    string option;
    do {
        displayMenu();
        cout << "Your choice ==> ";
        option = validInput();
        if (option == "D") optionD(studentList);
        else if(option == "I") optionI(studentList);
        else if(option == "B") optionB(studentList);
        else if(option == "S") optionS(studentList);
        else if(option == "M") optionM(studentList);
        else if(option == "X") optionX(studentList);
        else if(option == "T")
        {
            BinaryNode<Student> *root = studentList.getRoot();
            int n = 0;
            optionT(root, n);
            cout << endl;
        }
        else if(option == "A") optionA();
        else if(option == "H") displayMenu();
    } while (option!= "E");
}


//optionD function gets user input of DFTMenuInput()
//then display tree in depth first order according to user input
void optionD(BinarySearchTree<Student>& studentList)
{
    char option = DFTMenuInput();
    if (option == '1')
    {
        cout << "Depth-First Traversal - Preorder: \n\n";
        studentList.preOrder(displayNode);
    }
    else if (option == '2')
    {
        cout << "Depth-First Traversal - Inorder: \n\n";
        studentList.inOrder(displayNode);
    }
    else if (option == '3')
    {
        cout << "Depth-First Traversal - Postorder: \n\n";
        studentList.postOrder(displayNode);
    }
    cout << endl;
}


//EXTRA CREDIT
//Iterative depth fist traversal: inorder, preorder, postorder
void optionI(BinarySearchTree<Student>&studentList )
{
    char option = DFTMenuInput();
    if (option == '1') {
        cout << "Depth-First Traversal - Preorder: \n\n";
        BinaryNode<Student>* root = studentList.getRoot();
        Stack<BinaryNode<Student>> s;
        s.push(*root);
        while (!s.isEmpty())
        {
            BinaryNode<Student> node;
            s.pop(node);
            cout << node.getItem().getID() << "\t\t"
            << node.getItem().getGPA() << "\t\t"
            << node.getItem().getName() << "\n";
            BinaryNode<Student>* leftChild = node.getLeftPtr();
            BinaryNode<Student>* rightChild = node.getRightPtr();
            if (leftChild)
                s.push(*leftChild);
            if (rightChild)
                s.push(*rightChild);
        }
        cout << endl;
    }
    else if (option == '2') {
        cout << "Depth-First Traversal - Inorder: \n\n";
        Stack<BinaryNode<Student>*>s;
        BinaryNode<Student>*pWalk = studentList.getRoot();
        bool done = false;
        while (!done)
        {
            if (pWalk)
            {
                s.push(pWalk);
                pWalk = pWalk->getLeftPtr();
            }
            else
            {
                if (!s.isEmpty())
                {
                    s.pop(pWalk);
                    cout << pWalk->getItem().getID() << "\t\t"
                    << pWalk->getItem().getGPA() << "\t\t"
                    << pWalk->getItem().getName()  << "\n";
                    pWalk = pWalk->getRightPtr();
                }
                else
                    done = true;
            }
        }
        cout << endl;
    }
    else if (option == '3') {
        cout << "Depth-First Traversal - Postorder: \n\n";
        BinaryNode<Student>* root = studentList.getRoot();
        Stack<BinaryNode<Student>> s, s2;
        s.push(*root);
        while (!s.isEmpty())
        {
            BinaryNode<Student> node;
            s.pop(node);
            s2.push(node);
            BinaryNode<Student>* leftChild = node.getLeftPtr();
            BinaryNode<Student>* rightChild = node.getRightPtr();
            if (leftChild)
                s.push(*leftChild);
            if (rightChild)
                s.push(*rightChild);
        }
        while (!s2.isEmpty())
        {
            BinaryNode<Student> temp;
            s2.pop(temp);
            cout << temp.getItem().getID() << "\t\t"
            << temp.getItem().getGPA() << "\t\t"
            << temp.getItem().getName() << "\n";
        }
        cout << endl;
    }
}

//optionB function prints tree by level with Breadth-first traversal
void optionB(BinarySearchTree<Student>&studentList)
{
    cout << "Tree Breadth-First Traversals - Print by level:\n\n" ;
    BinaryNode<Student>* root = studentList.getRoot();
    Queue<BinaryNode<Student>> q;
    if (root == nullptr) {
        cout << endl;
        return;
    }
    q.enqueue(*root);
    while (!q.isEmpty()) {
        BinaryNode<Student> n; q.dequeue(n);
        cout << n.getItem().getID() << "\t\t"
        << n.getItem().getGPA() << "\t\t"
        << n.getItem().getName() << endl;
        if (n.getLeftPtr() != nullptr)
            q.enqueue(*n.getLeftPtr());
        if (n.getRightPtr() != nullptr)
            q.enqueue(*n.getRightPtr());
    }
    cout << endl;
}

//optionT function prints tree as an indented list //Preorder: Root-Right-Left
void optionT(BinaryNode<Student>*nodePtr, int level)
{
    if (nodePtr != 0)
    {
        Student item = nodePtr->getItem();
        for (int i = 0; i < level; i++) cout << "\t";
        cout << level + 1 << ". ";
        cout << nodePtr->getItem().getID() << "\t"
        << nodePtr->getItem().getName() << "\t"
        << nodePtr->getItem().getGPA() << endl;
        int newLevel = level + 1;
        optionT(nodePtr->getRightPtr(), newLevel);
        optionT(nodePtr->getLeftPtr(), newLevel);
    }
}

//optionS function searchs by unique key and print out result
void optionS(BinarySearchTree<Student>&studentList)
{
    int input = validInput2();
    Student* entry = new Student;
    Student* result = new Student;
    entry->setID(input);
    bool found = studentList.getEntry(*entry, *result);
    if (found)
    {
        cout << "Student is Found:"  << endl;
        cout << result->getID() << "\t\t"
        << result->getGPA() << "\t\t"
        << result->getName() << endl;
        cout << endl;
    }
    else {
        cout << "Student is Not Found" << endl << endl;
    }
}

//optionM find the smallest node of the tree
void optionM(BinarySearchTree<Student>&studentList)
{
    BinaryNode<Student> *small = studentList.findSmallest();
    cout << small->getItem().getID() << "\t\t" <<
            small->getItem().getGPA() << "\t\t" <<
            small->getItem().getName() << endl;
}

//optionX find the largest node of the tree
void optionX(BinarySearchTree<Student>&studentList)
{
    BinaryNode<Student> *large = studentList.findLargest();
    cout << large->getItem().getID() << "\t\t"
    << large->getItem().getGPA() << "\t\t"
    << large->getItem().getName() << endl;
}

//optionA fucntion - Hidden option: display name of developer
void optionA()
{
    cout << "This program is created by Frank M. Carrano and Tim Henry"
    "and is modified by Trinh Nguyen\n\n";

}
