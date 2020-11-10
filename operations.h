/*

	Declarations of functions which execute the operations
	specified in the task, includes two additional functions
	which print "OK" and "ERROR" messages to stdout and stderr,
	respectively.

	Author: Kacper Sołtysiak

*/


#ifndef OPERATIONS_H
#define OPERATIONS_H

void printError(void);

void printOK(void);

void executeAddOperation(tree **, char *, char *, char *);

void executeCheckOperation(tree *, char *, char *, char *);

void executeDelOperation(tree **, char *, char *, char *);

void executePrintOperation(tree *, char *, char *, char *);

#endif