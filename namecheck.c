/*

	Definition of functions used to determine whether
	specified string of chars is correct (in ascii code).

	Author: Kacper Sołtysiak

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree.h"
#include "namecheck.h"


static inline bool checkCorrectAsciiChar(char targetChar)
{
	return ((unsigned char) targetChar > 32);
}

static inline bool iterateInString(char * targetString, int iterationLimit)
{
	bool stringIterationResult = true;
	for(int i = 0; i < iterationLimit; i++)
	{
		stringIterationResult = stringIterationResult && checkCorrectAsciiChar(targetString[i]);
	}
	return stringIterationResult;
}

static inline bool checkNonNullString(char * targetString)
{
	int stringLength = strlen(targetString);
	bool correctString = iterateInString(targetString, stringLength);
	return correctString;
}

static inline bool checkCorrectAsciiString(char * targetString)
{
	if(targetString != NULL)
	{
		return checkNonNullString(targetString);
	}
	else
	{
		return true;
	}
}

bool checkCorrectNames(char * targetForest, char * targetTree, char * targetAnimal)
{
	bool testOfForest = checkCorrectAsciiString(targetForest);
	bool testOfTree = checkCorrectAsciiString(targetTree);
	bool testOfAnimal = checkCorrectAsciiString(targetAnimal);
	return (testOfForest && testOfTree && testOfAnimal);
}