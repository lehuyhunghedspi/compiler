/* 
 * @copyright (c) 2008, Hedspi, Hanoi University of Technology
 * @author Huu-Duc Nguyen
 * @version 1.0
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "symtab.h"

void freeObject(Object* obj);
void freeScope(Scope* scope);
void freeObjectList(ObjectNode *objList);
void freeReferenceList(ObjectNode *objList);

SymTab* symtab;
Type* intType;
Type* charType;
Type* floatType;

/******************* Type utilities ******************************/

Type* makeIntType(void) {
  Type* type = (Type*) malloc(sizeof(Type));
  type->typeClass = TP_INT;
  return type;
}

Type* makeCharType(void) {
  Type* type = (Type*) malloc(sizeof(Type));
  type->typeClass = TP_CHAR;
  return type;
}

Type* makeArrayType(int arraySize, Type* elementType) {
  Type* type = (Type*) malloc(sizeof(Type));
  type->typeClass = TP_ARRAY;
  type->arraySize = arraySize;
  type->elementType = elementType;
  return type;
}

Type* makeFloatType(void) {
  Type* type = (Type*) malloc(sizeof(Type));
  type->typeClass = TP_FLOAT;
  return type;
}


Type* duplicateType(Type* type) {
  // TODO
	 Type* type2 = (Type*) malloc(sizeof(Type));
 	type2->typeClass= type->typeClass;
 	type2->arraySize=type->arraySize;
 	type2->elementType=type->elementType;
 	return type2;

}

int compareType(Type* type1, Type* type2) {
  // TODO
  if (type1->typeClass == type2->typeClass) {
        if (type1->typeClass == TP_ARRAY) {
            if (!(type1->arraySize == type2->arraySize
                    && compareType(type1->elementType, type2->elementType)))
                return 0;
        }
        return 1;
    }

    return 0;
}

void freeType(Type* type) {
  // TODO
  if(type->typeClass==TP_ARRAY){
    freeType(type->elementType);
  }
  free(type);
}

/******************* Constant utility ******************************/

ConstantValue* makeIntConstant(int i) {
  // TODO
	ConstantValue *constantValue=(ConstantValue*)malloc(sizeof(ConstantValue));
	constantValue->type=TP_INT;
	constantValue->intValue=i;
	return constantValue;

}

ConstantValue* makeCharConstant(char ch) {
  // TODO
	ConstantValue *constantValue=(ConstantValue*)malloc(sizeof(ConstantValue));
	constantValue->type=TP_CHAR;
	constantValue->charValue=ch;
	return constantValue;
}

ConstantValue* makeFloatConstant(float f) {
  // TODO
  printf("%f\n",f );
  ConstantValue *constantValue=(ConstantValue*)malloc(sizeof(ConstantValue));
  constantValue->type=TP_FLOAT;
  constantValue->floatValue=f;
  return constantValue;
}

ConstantValue* duplicateConstantValue(ConstantValue* v) {
  // TODO
	ConstantValue *constantValue2=(ConstantValue*)malloc(sizeof(ConstantValue));
	constantValue2->type=v->type;
	if(v->type==TP_CHAR){
	constantValue2->charValue=v->charValue;	
	}
	else if(v->type==TP_INT){
		constantValue2->intValue=v->intValue;
	}
  else {
    constantValue2->floatValue=v->floatValue;
  }
	return constantValue2;
}

/******************* Object utilities ******************************/

Scope* createScope(Object* owner, Scope* outer) {
  Scope* scope = (Scope*) malloc(sizeof(Scope));
  scope->objList = NULL;
  scope->owner = owner;
  scope->outer = outer;
  return scope;
}

Object* createProgramObject(char *programName) {
  Object* program = (Object*) malloc(sizeof(Object));
  strcpy(program->name, programName);
  program->kind = OBJ_PROGRAM;
  program->progAttrs = (ProgramAttributes*) malloc(sizeof(ProgramAttributes));
  program->progAttrs->scope = createScope(program,NULL);
  symtab->program = program;

  return program;
}

Object* createConstantObject(char *name) {
  // TODO
	Object * object=(Object *)malloc(sizeof(Object));
	strcpy(object->name,name);
	object->kind=OBJ_CONSTANT;
	object->constAttrs=(ConstantAttributes *)malloc(sizeof(ConstantAttributes));
	object->constAttrs->value=NULL;
  return object;
}

Object* createTypeObject(char *name) {
  // TODO
	Object * object=(Object *)malloc(sizeof(Object));
	strcpy(object->name,name);
	object->kind = OBJ_TYPE;
  object->typeAttrs = (TypeAttributes*) malloc(sizeof(TypeAttributes));
  object->typeAttrs->actualType = NULL;
	return object;
}

Object* createVariableObject(char *name) {
  // TODO
	Object * object=(Object *)malloc(sizeof(Object));
	strcpy(object->name,name);
	object->kind=OBJ_VARIABLE;
	object->varAttrs=(VariableAttributes *)malloc(sizeof(VariableAttributes));
  object->varAttrs->type=NULL;
  object->varAttrs->scope = symtab->currentScope;

	return object;
}

Object* createFunctionObject(char *name) {
  // TODO
	Object * object=(Object *)malloc(sizeof(Object));
	strcpy(object->name,name);
	object->kind=OBJ_FUNCTION;
	object->funcAttrs=(FunctionAttributes *)malloc(sizeof(FunctionAttributes));

    object->funcAttrs->paramList = NULL;
    object->funcAttrs->returnType = NULL;
    object->funcAttrs->scope = createScope(object, symtab->currentScope);
	return object;
}

Object* createProcedureObject(char *name) {
  // TODO
	Object * object=(Object *)malloc(sizeof(Object));
	strcpy(object->name,name);
	object->kind=OBJ_PROCEDURE;
	object->procAttrs=(ProcedureAttributes *)malloc(sizeof(ProcedureAttributes));
   object->procAttrs->paramList = NULL;
    object->procAttrs->scope = createScope(object, symtab->currentScope);
	return object;

}

Object* createParameterObject(char *name, enum ParamKind kind, Object* owner) {
  // TODO
	Object * object=(Object *)malloc(sizeof(Object));
	strcpy(object->name,name);
	object->kind=OBJ_PARAMETER;
	object->paramAttrs=(ParameterAttributes *)malloc(sizeof(ParameterAttributes));
   object->paramAttrs->function = owner;
    object->paramAttrs->kind = kind;
    object->paramAttrs->type = NULL; 
	return object;
}

void freeObject(Object* obj) {
  // TODO
  if(obj !=NULL){
    switch(obj->kind)
    {
      case   OBJ_CONSTANT:  
      if(obj->constAttrs!=NULL){
         free(obj->constAttrs->value);
        free(obj->constAttrs);
      }
       
      break;
      case OBJ_VARIABLE: 
      if(obj->varAttrs!=NULL){

      freeType(obj->varAttrs->type);
      freeScope(obj->varAttrs->scope);
        free(obj->varAttrs);
      }
      break;
      case OBJ_TYPE :
      if(obj->typeAttrs!=NULL){

        freeType(obj->typeAttrs->actualType);
        free(obj->typeAttrs);
      }
      break;
      case OBJ_FUNCTION:

        if(obj->funcAttrs!=NULL){

                freeObjectList(obj->funcAttrs->paramList);
                freeType(obj->funcAttrs->returnType);
                freeScope(obj->funcAttrs->scope);
                free(obj->funcAttrs);
        }
      break;
      case OBJ_PROCEDURE:

        if(obj->funcAttrs!=NULL){

                freeObjectList(obj->funcAttrs->paramList);
                freeType(obj->funcAttrs->returnType);
                freeScope(obj->funcAttrs->scope);
                free(obj->funcAttrs);
        }
      break;
      case OBJ_PARAMETER:break;
      case OBJ_PROGRAM:break;
    }
    free(obj);
  }
}

void freeScope(Scope* scope) {
  // TODO
      if (scope != NULL) {
        freeObjectList(scope->objList);
        free(scope);
        scope = NULL;
    }
}

void freeObjectList(ObjectNode *objList) {
  // TODO
   if (objList != NULL) {
        freeObject(objList->object);
        freeObjectList(objList->next);
        objList = NULL;
    }
}

void freeReferenceList(ObjectNode *objList) {
  // TODO
  if (objList != NULL) {
        freeObject(objList->object);
        freeReferenceList(objList->next);
        objList = NULL;
    }
}

void addObject(ObjectNode **objList, Object* obj) {
  ObjectNode* node = (ObjectNode*) malloc(sizeof(ObjectNode));
  node->object = obj;
  node->next = NULL;
  if ((*objList) == NULL) 
    *objList = node;
  else {
    ObjectNode *n = *objList;
    while (n->next != NULL) 
      n = n->next;
    n->next = node;
  }
}

Object* findObject(ObjectNode *objList, char *name) {
  // TODO

   ObjectNode * currentNode = objList;
  while(currentNode != NULL) {
      if (strcmp(currentNode->object->name, name) == 0) {
           return currentNode->object;
      }
      currentNode = currentNode->next;
  }

  return NULL;

}

/******************* others ******************************/

void initSymTab(void) {
  Object* obj;
  Object* param;

  symtab = (SymTab*) malloc(sizeof(SymTab));
  symtab->globalObjectList = NULL;
  
  obj = createFunctionObject("READC");
  obj->funcAttrs->returnType = makeCharType();
  addObject(&(symtab->globalObjectList), obj);

  obj = createFunctionObject("READI");
  obj->funcAttrs->returnType = makeIntType();
  addObject(&(symtab->globalObjectList), obj);

  obj = createFunctionObject("READF");
  obj->funcAttrs->returnType = makeFloatType();
  addObject(&(symtab->globalObjectList), obj);

  obj = createProcedureObject("WRITEI");
  param = createParameterObject("i", PARAM_VALUE, obj);
  param->paramAttrs->type = makeIntType();
  addObject(&(obj->procAttrs->paramList),param);
  addObject(&(symtab->globalObjectList), obj);

  obj = createProcedureObject("WRITEC");
  param = createParameterObject("ch", PARAM_VALUE, obj);
  param->paramAttrs->type = makeCharType();
  addObject(&(obj->procAttrs->paramList),param);
  addObject(&(symtab->globalObjectList), obj);

  obj = createProcedureObject("WRITEF");
  param = createParameterObject("ch", PARAM_VALUE, obj);
  param->paramAttrs->type = makeFloatType();
  addObject(&(obj->procAttrs->paramList),param);
  addObject(&(symtab->globalObjectList), obj);

  obj = createProcedureObject("WRITELN");
  addObject(&(symtab->globalObjectList), obj);

  intType = makeIntType();
  charType = makeCharType();
  floatType = makeFloatType();
}

void cleanSymTab(void) {
  freeObject(symtab->program);
  freeObjectList(symtab->globalObjectList);
  free(symtab);
  freeType(intType);
  freeType(charType);
}

void enterBlock(Scope* scope) {
  symtab->currentScope = scope;
}

void exitBlock(void) {
  symtab->currentScope = symtab->currentScope->outer;
}

void declareObject(Object* obj) {
  if (obj->kind == OBJ_PARAMETER) {
    Object* owner = symtab->currentScope->owner;
    switch (owner->kind) {
    case OBJ_FUNCTION:
      addObject(&(owner->funcAttrs->paramList), obj);
      break;
    case OBJ_PROCEDURE:
      addObject(&(owner->procAttrs->paramList), obj);
      break;
    default:
      break;
    }
  }
 
  addObject(&(symtab->currentScope->objList), obj);
}


