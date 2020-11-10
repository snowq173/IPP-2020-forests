/*

	Main code file, including main function, 
	input reading and processing each line of input.

	Author: Kacper Sołtysiak

*/


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "charvector.h"
#include "tree.h"
#include "operations.h"
#include "namecheck.h"

bool readNewInputLine(charVector * inputVector, bool * endOfFile)
{
	int inputChar = '0';
	inputChar = getchar();
	while(inputChar != '\n' && inputChar != EOF)
	{
		addCharToVector(inputVector, (char) inputChar);
		inputChar = getchar();
	}
	addCharToVector(inputVector, '\0');
	if(inputChar == EOF)
    {
	    *endOfFile = true;
    }
    return(inputChar == '\n');
}

static void detectOperationAndExecuteIt(char * targetCommand, char * targetForest, char * targetTree, char * targetAnimal, tree ** forestsRoot)
{
	if(strcmp(targetCommand, "ADD") == 0)
	{
		executeAddOperation(forestsRoot, targetForest, targetTree, targetAnimal);
	}
	else if(strcmp(targetCommand, "CHECK") == 0)
	{
		executeCheckOperation(*forestsRoot, targetForest, targetTree, targetAnimal);
	}
	else if(strcmp(targetCommand, "DEL") == 0)
	{
		executeDelOperation(forestsRoot, targetForest, targetTree, targetAnimal);
	}
	else if(strcmp(targetCommand, "PRINT") == 0)
	{
		executePrintOperation(*forestsRoot, targetForest, targetTree, targetAnimal);
	}
	else
	{
		printError();
	}
}

void processInputLine(charVector * inputVector, tree ** forestsRoot, bool checkNewLineEnding)
{
	char * inputLineArray = inputVector -> vectorArray;

	if(inputLineArray[0] == '#')
	{
		return;
	}

	char inputSeparatorsArray[] = " \t\v\f\r";
	char * targetCommand = strtok(inputLineArray, inputSeparatorsArray);
	char * targetForest = strtok(NULL, inputSeparatorsArray);
	char * targetTree = strtok(NULL, inputSeparatorsArray);
	char * targetAnimal = strtok(NULL, inputSeparatorsArray);
	char * extraArgument = strtok(NULL, inputSeparatorsArray);

	if(!checkCorrectNames(targetForest, targetTree, targetAnimal))
	{
		printError();
		return;
	}

	if(targetCommand != NULL && !checkNewLineEnding)
	{
		printError();
		return;
	}

	if(extraArgument != NULL)
	{
		printError();
		return;
	}

	if(targetCommand == NULL)
    {
	    return;
    }

    detectOperationAndExecuteIt(targetCommand, targetForest, targetTree, targetAnimal, forestsRoot);
}

int main(void)
{
	tree * forestsRoot = NULL;
	charVector * inputArray = createNewCharVector();
	bool endOfFile = false;
	while(!endOfFile)
	{
		bool checkNewLineEnding = readNewInputLine(inputArray, &endOfFile);
		processInputLine(inputArray, &forestsRoot, checkNewLineEnding);
		restoreVectorToDefault(inputArray);
	}
	deleteTree(forestsRoot);
	disposeOfVector(inputArray);
	return 0;
}