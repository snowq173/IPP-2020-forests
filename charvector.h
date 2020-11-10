/*

	Definition of "charvector" structure and 
	functions used by it.

	Author: Kacper Sołtysiak

*/


#ifndef CHARVECTOR_H
#define CHARVECTOR_H

#include <stdbool.h>

typedef struct charVector charVector;

//definition of charVector structure
struct charVector
{
	char * vectorArray;
	int sizeOfVectorArray;
	int charCount;
};

//function which deletes a specified vector
void disposeOfVector(charVector *);

//function which adds a specified char to the vector
void addCharToVector(charVector *, char);

//function which sets parameters to default (including the array inside of the vector)
void restoreVectorToDefault(charVector *);

//function which creates a new vector, sets its default parameters (as in the definition of the functions); returns a pointer to the created vector
charVector * createNewCharVector(void);

#endif