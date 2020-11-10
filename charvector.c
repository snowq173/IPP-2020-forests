/*

	Definitions of functions used by the structure charvector.

	Author: Kacper Sołtysiak

*/



#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "charvector.h"

#define defaultSizeOfIdentifierArray 30

static void checkCharVectorAllocationError(charVector * vectorPointer)
{
	if(vectorPointer == NULL)
	{
		exit(1);
	}
}

static void checkCharArrayAllocationError(char * arrayPointer)
{
	if(arrayPointer == NULL)
	{
		exit(1);
	}
}

static void setDefaultParameters(charVector * createdVector)
{
	createdVector -> vectorArray = malloc(defaultSizeOfIdentifierArray * sizeof(char));
	checkCharArrayAllocationError(createdVector -> vectorArray);
	createdVector -> sizeOfVectorArray = defaultSizeOfIdentifierArray;
	createdVector -> charCount = 0;
}


charVector * createNewCharVector(void)
{
	charVector * createdVector = malloc(sizeof(charVector));
	checkCharVectorAllocationError(createdVector);
	setDefaultParameters(createdVector);
	return createdVector;
}

void restoreVectorToDefault(charVector * targetVector)
{
	if(targetVector != NULL)
	{
		free(targetVector -> vectorArray);
		targetVector -> vectorArray = malloc(defaultSizeOfIdentifierArray * sizeof(char));
		checkCharArrayAllocationError(targetVector -> vectorArray);
		targetVector -> sizeOfVectorArray = defaultSizeOfIdentifierArray;
		targetVector -> charCount = 0;
	}
}

static void checkNecessityOfResizing(charVector * targetVector)
{
	int arrayLength = targetVector -> sizeOfVectorArray;
	int filledCount = targetVector -> charCount;
	if(filledCount > arrayLength - 2)
	{
		targetVector -> vectorArray = realloc(targetVector -> vectorArray, 2 * arrayLength * sizeof(char));
		checkCharArrayAllocationError(targetVector -> vectorArray);
		targetVector -> sizeOfVectorArray = 2 * arrayLength;
	}
}

static void insertChar(charVector * targetVector, char targetChar)
{
	int filledFieldsCount = targetVector -> charCount;
	char * targetVectorArray = targetVector -> vectorArray;
	targetVectorArray[filledFieldsCount] = targetChar;
	targetVector -> charCount = filledFieldsCount + 1;
}

void addCharToVector(charVector * targetVector, char targetChar)
{
	if(targetVector != NULL)
	{
		checkNecessityOfResizing(targetVector);
		insertChar(targetVector, targetChar);
	}
}

void disposeOfVector(charVector * targetVector)
{
	if(targetVector != NULL)
	{
		char * disposeArrayPointer = targetVector -> vectorArray;
		free(disposeArrayPointer);
		free(targetVector);
	}
}