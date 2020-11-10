/*

	Definition of "tree" structure and declarations
	of functions that are associated with this
	structure.

	Author: Kacper Sołtysiak

*/

#ifndef TREE_H
#define TREE_H

#include "charvector.h"

typedef struct tree tree;

//definition of tree structure
struct tree
{
	char * key;
	tree * left;
	tree * right;
	tree * parent;
	tree * subTree;
};

//function which deletes tree
void deleteTree(tree *);

//function which prints keys stored in the nodes of a tree (in lexicographical order)
void printKeys(tree *);

//function which deletes a specified node from the tree
void deleteNode(tree **, tree *);

//function which creates a new tree instance; returns a pointer to the created instance
tree * createTree(char *);

//function which searches the tree for a specified key stored in the char array; returns NULL if such key is not stored in the tree
tree * findKey(tree *, char *);

//function which adds specified key to the tree
tree * addKeyToTheTree(tree **, char *);

//function which checks whether specified key is in the tree; returns true if such key exists in the tree, false else
bool checkKey(tree *, char *);
#endif