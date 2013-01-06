/*
 * scope.h
 *
 *  Created on: Jan 6, 2013
 *      Author: azk
 */

#ifndef SCOPE_H_
#define SCOPE_H_

#include <stack>
#include <set>
#include <string>

//Debug
#include <iostream>

#include "shared.h"

/*==== Variable related definitions ====*/

typedef struct
{
	std::string name;
	VarType type;
	int offset;
} Variable;

struct VarComp
{
	bool operator() (const Variable& var1, const Variable& var2)
	{
		if (var1.name.compare(var2.name) >= 0)
			return false;
		return true;
	}
};

typedef std::set<Variable,VarComp> VariableSet;

/*==== End of Variable definitions ====*/

/*==== Scope related definitions =====*/

typedef enum
{
	MAIN_S,
	IF_S,
	ELSE_S,
	WHILE_S,
	NONE
} ScopeType;



struct scope
{
	ScopeType scopeType;
	VariableSet varSet;

	bool curlyBraced;
};

typedef struct scope* Scope;

typedef std::stack<Scope> ScopeStack;

class ScopeGlobal
{
public:
	ScopeStack scopeStack;
	ScopeGlobal(){}
	~ScopeGlobal();

	void addVar(VarType varType, std::string varName)
	{
		std::cout << "Got: " << varName << " " << (int)varType << std::endl;
	}
};

/*==== End of Scope definitions ====*/

#endif /* SCOPE_H_ */
