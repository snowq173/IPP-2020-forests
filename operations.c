/*

	Definitions of functions which execute operations
	specified in the task, includes some additional functions
	which handle minor parts of the operations.
	
	Author: Kacper Sołtysiak

*/


#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "tree.h"
#include "operations.h"

void printError()
{
	fprintf(stderr, "ERROR\n");
}

void printOK()
{
	fprintf(stdout, "OK\n");
}

static inline bool isMetaChar(char * targetChar)
{
	return(strcmp(targetChar, "*") == 0);
}

static void recursiveAddExecution(tree ** forestRoot, char * targetTree, char * targetAnimal)
{
	if(targetTree != NULL)
	{
		tree * treeNode = addKeyToTheTree(forestRoot, targetTree);
		recursiveAddExecution(&(treeNode -> subTree), targetAnimal, NULL);
	}
}

void executeAddOperation(tree ** forestsRoot, char * targetForest, char * targetTree, char * targetAnimal)
{
	if(targetForest == NULL)
	{
		printError();
	}
	else
	{
		tree * forestNode = addKeyToTheTree(forestsRoot, targetForest);
		recursiveAddExecution(&(forestNode -> subTree), targetTree, targetAnimal);
		printOK();
	}
}

static inline void answerCheckQuery(bool checkResult)
{
	if(checkResult)
	{
		fprintf(stdout, "YES\n");
	}
	else
	{
		fprintf(stdout, "NO\n");
	}
}

static bool wrongCheckOperationInput(char * targetForest, char * targetTree, char * targetAnimal)
{
	if(targetForest == NULL)
	{
		return true;
	}
	else if(targetAnimal != NULL && isMetaChar(targetAnimal))
	{
		return true;
	}
	else if(targetForest != NULL && isMetaChar(targetForest) && targetTree == NULL)
	{
		return true;
	}
	else if(targetTree != NULL && isMetaChar(targetTree) && targetAnimal == NULL)
	{
		return true;
	}
	else
	{
		return false;
	}
}

static bool checkAnimal(tree * treeNode, char * targetAnimal)
{
	if(targetAnimal != NULL && treeNode != NULL)
	{
		tree * animalNode = findKey(treeNode -> subTree, targetAnimal);
		return (animalNode != NULL);
	}
	return (treeNode != NULL);
}

static bool checkTree(tree * forestNode, char * targetTree, char * targetAnimal)
{
	if(targetTree != NULL && forestNode != NULL)
	{
		tree * treeNode = findKey(forestNode -> subTree, targetTree);
		return checkAnimal(treeNode, targetAnimal);
	}
	return (forestNode != NULL);
}

static bool checkOneTreeInForest(tree * forestsRoot, char * targetForest, char * targetTree, char * targetAnimal)
{
	tree * forestNode = findKey(forestsRoot, targetForest);
	return checkTree(forestNode, targetTree, targetAnimal);
}

static bool searchAllTreesInForestAndAnimalsInEachTree(tree * treesRootNode, char * targetKey)
{
	if(treesRootNode != NULL)
	{
		bool fromLeftNode = searchAllTreesInForestAndAnimalsInEachTree(treesRootNode -> left, targetKey);
		bool fromRightNode = searchAllTreesInForestAndAnimalsInEachTree(treesRootNode -> right, targetKey);
		bool fromCurrentNode = checkKey(treesRootNode -> subTree, targetKey);
		bool searchResult = fromLeftNode || fromCurrentNode || fromRightNode;
		return searchResult;
	}
	else
	{
		return false;
	}
}

static bool checkWholeForest(tree * forestsRoot, char * targetForest, char * targetAnimal)
{
	tree * forestNode = findKey(forestsRoot, targetForest);
	if(forestNode != NULL)
	{
		return searchAllTreesInForestAndAnimalsInEachTree(forestNode -> subTree, targetAnimal);
	}
	else
	{
		return false;
	}
}

static bool checkAllForestsSpecifiedTree(tree * forestsRoot, char * targetTree, char * targetAnimal)
{
	if(forestsRoot != NULL)
	{
		bool fromLeft = checkAllForestsSpecifiedTree(forestsRoot -> left, targetTree, targetAnimal);
		bool fromRight = checkAllForestsSpecifiedTree(forestsRoot -> right, targetTree, targetAnimal);
		bool fromRoot = checkTree(forestsRoot, targetTree, targetAnimal);
		return (fromLeft || fromRight || fromRoot);
	}
	else
	{
		return false;
	}
}

static bool checkEachForestAndEachTree(tree * forestsRoot, char * targetForest, char * targetAnimal)
{
	if(forestsRoot != NULL)
	{
		bool fromLeft = checkEachForestAndEachTree(forestsRoot -> left, targetForest, targetAnimal);
		bool fromRight = checkEachForestAndEachTree(forestsRoot -> right, targetForest, targetAnimal);
		bool fromCurrentNode = searchAllTreesInForestAndAnimalsInEachTree(forestsRoot -> subTree, targetAnimal);
		return (fromLeft || fromCurrentNode || fromRight);
	}
	else
	{
		return false;
	}
}



static void nonMetaCharForest(tree * forestsRoot, char * targetForest, char * targetTree, char * targetAnimal)
{
	if(targetTree != NULL && isMetaChar(targetTree))
	{
		answerCheckQuery(checkWholeForest(forestsRoot, targetForest, targetAnimal));
	}
	else
	{
		answerCheckQuery(checkOneTreeInForest(forestsRoot, targetForest, targetTree, targetAnimal));
	}
}


static void metaCharForest(tree * forestsRoot, char * targetForest, char * targetTree, char * targetAnimal)
{
	if(isMetaChar(targetTree))
	{
		answerCheckQuery(checkEachForestAndEachTree(forestsRoot, targetForest, targetAnimal));
	}
	else
	{
		answerCheckQuery(checkAllForestsSpecifiedTree(forestsRoot, targetTree, targetAnimal));
	}
}

void executeCheckOperation(tree * forestsRoot, char * targetForest, char * targetTree, char * targetAnimal)
{
	if(wrongCheckOperationInput(targetForest, targetTree, targetAnimal))
	{
		printError();
		return;
	}
	if(isMetaChar(targetForest))
	{
		metaCharForest(forestsRoot, targetForest, targetTree, targetAnimal);
	}
	else
	{
		nonMetaCharForest(forestsRoot, targetForest, targetTree, targetAnimal);
	}
}


static inline void clearEverything(tree ** forestsRoot)
{
	deleteTree(*forestsRoot);
	*forestsRoot = NULL;
}

static void deleteFromAnimalsLayer(tree ** treeRoot, char * targetAnimal)
{
	tree * animalNode = findKey(*treeRoot, targetAnimal);
	deleteNode(treeRoot, animalNode);
}

static void deleteFromTreesLayer(tree ** forestRoot, char * targetTree, char * targetAnimal)
{
	tree * treeNode = findKey(*forestRoot, targetTree);
	if(targetAnimal != NULL && treeNode != NULL)
	{
		deleteFromAnimalsLayer(&(treeNode -> subTree), targetAnimal);
	}
	else
	{
		deleteNode(forestRoot, treeNode);
	}
}

static void deleteFromForestsLayer(tree ** forestsRoot, char * targetForest, char * targetTree, char * targetAnimal)
{
	tree * forestNode = findKey(*forestsRoot, targetForest);
	if(targetTree != NULL && forestNode != NULL)
	{
		deleteFromTreesLayer(&(forestNode -> subTree), targetTree, targetAnimal);
	}
	else
	{
		deleteNode(forestsRoot, forestNode);
	}
}


void executeDelOperation(tree ** forestsRoot, char * targetForest, char * targetTree, char * targetAnimal)
{
	if(targetForest != NULL)
	{
		deleteFromForestsLayer(forestsRoot, targetForest, targetTree, targetAnimal);
		printOK();
	}
	else
	{
		clearEverything(forestsRoot);
		printOK();
	}
}

void executePrintOperation(tree * forestsRoot, char * targetForest, char * targetTree, char * targetAnimal)
{
	if(targetAnimal != NULL)
	{
		printError();
		return;
	}
	tree * forestNode = findKey(forestsRoot, targetForest);
	if(targetForest != NULL && forestNode != NULL)
	{
		executePrintOperation(forestNode -> subTree, targetTree, targetAnimal, NULL);
	}
	else if(targetForest == NULL)
	{
		printKeys(forestsRoot);
	}
}