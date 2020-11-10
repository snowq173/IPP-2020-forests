/*
	
	Definitions of functions associated
	with "tree" structure.

	Author: Kacper Sołtysiak

*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "charvector.h"
#include "tree.h"

static void checkCharArrayAllocationError(char * arrayPointer)
{
	if(arrayPointer == NULL)
	{
		exit(1);
	}
}

static void checkTreeMallocError(tree * allocatedTreeNode)
{
	if(allocatedTreeNode == NULL)
	{
		exit(1);
	}
}

static void setNodeKey(tree * targetNode, char * targetKey)
{
	int length = strlen(targetKey);
	char * keyArray = malloc((length + 1) * sizeof(char));
	checkCharArrayAllocationError(keyArray);
	keyArray = strcpy(keyArray, targetKey);
	targetNode -> key = keyArray;
}

static void setDefaultNodeParameters(tree * targetNode, char * targetKey)
{
	setNodeKey(targetNode, targetKey);
	targetNode -> left = NULL;
	targetNode -> right = NULL;
	targetNode -> parent = NULL;
	targetNode -> subTree = NULL;
}

static void clearNodeAttributes(tree * targetNode)
{
	if(targetNode != NULL)
	{
		deleteTree(targetNode -> subTree);
		free(targetNode -> key);
		free(targetNode);
	}
}


tree * createTree(char * givenKey)
{
	tree * newTreeNode = malloc(sizeof(tree));
	checkTreeMallocError(newTreeNode);
	setDefaultNodeParameters(newTreeNode, givenKey);
	return newTreeNode;
}


static inline tree * addToLeft(tree * targetNode, char * targetKey)
{
	tree * leftNode = targetNode -> left;
	if(leftNode != NULL)
	{
		return addKeyToTheTree(&leftNode, targetKey);
	}
	else
	{
		tree * newNode = createTree(targetKey);
		targetNode -> left = newNode;
		newNode -> parent = targetNode;
		return newNode;	
	}
}

static inline tree * addToRight(tree * targetNode, char * targetKey)
{
	tree * rightNode = targetNode -> right;
	if(rightNode != NULL)
	{
		return addKeyToTheTree(&rightNode, targetKey);
	}
	else
	{
		tree * newNode = createTree(targetKey);
		targetNode -> right = newNode;
		newNode -> parent = targetNode;
		return newNode;
	}
}

static inline tree * addToNullNode(tree ** currentNode, char * targetKey)
{
	tree * newNode = createTree(targetKey);
	*currentNode = newNode;
	return *currentNode;
}

static inline tree * addToNonNullNode(tree * currentNode, char * targetKey)
{
	char * currentNodeKey = currentNode -> key;
	int stringComparation = strcmp(currentNodeKey, targetKey);
	if(stringComparation > 0)
	{
		return addToLeft(currentNode, targetKey);
	}
	else if(stringComparation < 0)
	{
		return addToRight(currentNode, targetKey);
	}
	else
	{
		return currentNode;
	}	
}

tree * addKeyToTheTree(tree ** root, char * targetKey)
{
	if(*root != NULL)
	{
		return addToNonNullNode(*root, targetKey);
	}
	else
	{
		return addToNullNode(root, targetKey);
	}
}

void deleteTree(tree * root)
{
	if(root != NULL)
	{
		deleteTree(root -> left);
		deleteTree(root -> right);
		clearNodeAttributes(root);
	}
}

void printKeys(tree * root)
{
	if(root != NULL)
	{
		printKeys(root -> left);
		printf("%s\n", root -> key);
		printKeys(root -> right);
	}
}

static inline tree * findKeyNonNullNode(tree * currentNode, char * targetKey)
{
	int stringComparation = strcmp(currentNode -> key, targetKey);
	if(stringComparation > 0)
	{
		return findKey(currentNode -> left, targetKey);
	}
	else if(stringComparation < 0)
	{
		return findKey(currentNode -> right, targetKey);
	}
	else
	{
		return currentNode;
	}
}

tree * findKey(tree * rootNode, char * targetKey)
{
	if(rootNode != NULL && targetKey != NULL)
	{
		return findKeyNonNullNode(rootNode, targetKey);
	}
	else
	{
		return NULL;
	}
}

bool checkKey(tree * rootNode, char * targetKey)
{
	return (findKey(rootNode, targetKey) != NULL);
}

static tree * treeMinimum(tree * root)
{
	tree * travelNode = root;
	while(travelNode -> left != NULL)
	{
		travelNode = travelNode -> left;
	}
	return travelNode;
}

static void switchNodes(tree ** rootNode, tree * firstNode, tree * secondNode)
{
	if(firstNode -> parent == NULL)
	{
		*rootNode = secondNode;
	}
	else if(firstNode == firstNode -> parent -> left)
	{
		firstNode -> parent -> left = secondNode;
	}
	else
	{
		firstNode -> parent -> right = secondNode;
	}
	if(secondNode != NULL)
	{
		secondNode -> parent = firstNode -> parent;
	}
}


void deleteNode(tree ** rootNode, tree * targetNode)
{
	if(targetNode != NULL)
	{
		if(targetNode -> left == NULL)
		{
			switchNodes(rootNode, targetNode, targetNode -> right);
		}
		else if(targetNode -> right == NULL)
		{
			switchNodes(rootNode, targetNode, targetNode -> left);
		}
		else
		{
			tree * minimumNode = treeMinimum(targetNode -> right);
			if(minimumNode -> parent != targetNode)
			{
				switchNodes(rootNode, minimumNode, minimumNode -> right);
				minimumNode -> right = targetNode -> right;
				minimumNode -> right -> parent = minimumNode;
			}
			switchNodes(rootNode, targetNode, minimumNode);
			minimumNode -> left = targetNode -> left;
			minimumNode -> left -> parent = minimumNode;
		}
		clearNodeAttributes(targetNode);
	}
}