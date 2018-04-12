/* 
 * @copyright (c) 2008, Hedspi, Hanoi University of Technology
 * @author Huu-Duc Nguyen
 * @version 1.0
 */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "semantics.h"
#include "error.h"

extern SymTab* symtab;
extern Token* currentToken;
Object* lookupObject(char *name) {
  // TODO
	Object* object = NULL;
    static Scope* currentScope = NULL;

    // Start searching from current scope if
    // we did not search any time before
    // or a global search has been carried out
        currentScope = symtab->currentScope;

    // else we start from the scope of previous search
    while (currentScope != NULL) {
        object = findObject(currentScope->objList, name);

        // Jump to the outside scope
        currentScope = currentScope->outer;


        // Return the found object
        if (object != NULL)
            return object;
    }

    // Fallback to search in global scope
    object = findObject(symtab->globalObjectList, name);

    return object;
}

void checkFreshIdent(char *name) {
  // TODO
	Object *obj=lookupObject(name);

	if(obj!=NULL){
		error(ERR_DUPLICATE_IDENT, currentToken->lineNo, currentToken->colNo);
	}
}

Object* checkDeclaredIdent(char* name) {
  // TODO
	Object *obj = lookupObject(name);
	if (obj == NULL)
		printf("%s\n", name);
        error(ERR_UNDECLARED_IDENT, currentToken->lineNo, currentToken->colNo);

    return obj;
}

Object* checkDeclaredConstant(char* name) {
  // TODO
	Object *obj=checkDeclaredIdent(name);
	if(obj->kind!=OBJ_CONSTANT){
		error(ERR_UNDECLARED_CONSTANT, currentToken->lineNo, currentToken->colNo);
	}
	return obj;
}

Object* checkDeclaredType(char* name) {
  // TODO
	Object *obj=checkDeclaredIdent(name);
	if(obj->kind!=OBJ_TYPE){
		error(ERR_UNDECLARED_TYPE,currentToken->lineNo, currentToken->colNo);
	}
	return obj;
}

Object* checkDeclaredVariable(char* name) {
  // TODO
	Object *obj=checkDeclaredIdent(name);
	if(obj->kind!=OBJ_VARIABLE){
		error(ERR_UNDECLARED_VARIABLE,currentToken->lineNo, currentToken->colNo);
	}
	return obj;
}

Object* checkDeclaredFunction(char* name) {
  // TODO
	Object *obj=checkDeclaredIdent(name);
	if(obj->kind!=OBJ_FUNCTION){
		error(ERR_UNDECLARED_FUNCTION,currentToken->lineNo, currentToken->colNo);
	}
	return obj;
}

Object* checkDeclaredProcedure(char* name) {
  // TODO
	Object *obj=checkDeclaredIdent(name);
	if(obj->kind!=OBJ_PROCEDURE){
		error(ERR_UNDECLARED_PROCEDURE,currentToken->lineNo, currentToken->colNo);
	}
	return obj;
}

Object* checkDeclaredLValueIdent(char* name) {
  // TODO
	Object *obj=checkDeclaredIdent(name);
	if(obj->kind!=OBJ_VARIABLE){
		error(ERR_UNDECLARED_VARIABLE,currentToken->lineNo, currentToken->colNo);
	}
	return obj;
}

