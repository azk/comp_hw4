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
#include <utility>

#include "output.hpp"

//Debug
#include <iostream>
/*==== Variable related definitions ====*/
typedef enum
{
	NIS_T,
	AGORA_T,
	BOOL_T,
	INT_T,
	ERROR_T
} VarType;


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
typedef std::pair<VariableSet::iterator, bool> VarSetRet;


/*==== End of Variable definitions ====*/

/*==== Scope related definitions =====*/

typedef enum
{
	MAIN_S,
	IF_S,
	ELSE_S,
	WHILE_S,
	CURLY_S,
	NONE
} ScopeType;

struct scope
{
	ScopeType scopeType;
	VariableSet varSet;
	bool breakEncountered;
	bool curlyBraced;
	bool whileCurly;
};

typedef struct scope* Scope;

typedef std::stack<Scope> ScopeStack;

class ScopeGlobal
{
public:
	ScopeGlobal():globalOffset(0),currentScope(NULL){}
	~ScopeGlobal();

	void addScope(ScopeType scopeType)
	{
		Scope newScope = new struct scope();
		newScope->scopeType = scopeType;
		newScope->breakEncountered = newScope->curlyBraced = newScope->whileCurly = false;
		if (currentScope != NULL &&currentScope->scopeType == WHILE_S && scopeType == CURLY_S)
			newScope->whileCurly = true;

		scopeStack.push(newScope);
		currentScope = newScope;
	}

	bool varExistsInCurrentScope(std::string& varName)
	{
		Variable dummy;
		dummy.name = varName;
		VariableSet::iterator res = currentScope->varSet.find(dummy);

		return (res != currentScope->varSet.end());

	}

	bool addVarToCurrentScope(VarType varType, std::string varName)
	{
		Variable newVar;
		newVar.name = varName;
		newVar.type = varType;
		newVar.offset = globalOffset;

		VarSetRet ret = currentScope->varSet.insert(newVar);
		if (ret.second == false)
			return false;

		globalOffset++;
		return true;
	}

	void setCurrentScopeCurly(bool isCurly)
	{
		currentScope->curlyBraced = isCurly;
	}

	bool isCurrentScopeCurlyWhile()
	{
		return (currentScope->whileCurly);
	}

	ScopeType getCurrentScopeType()
	{
		return currentScope->scopeType;
	}

	void dumpCurrentScope()
	{
		int iterations = (currentScope->scopeType == ELSE_S)?2:1;

		for (int i =0 ; i < iterations ; i++)
		{
			if (currentScope->varSet.size() > 0 || currentScope->scopeType == CURLY_S)
			{
				int offsetDelta = currentScope->varSet.size();
				output::endScope();
				for (VariableSet::iterator it  = currentScope->varSet.begin() ; it != currentScope->varSet.end() ; it ++)
				{
					output::printVar(it->name.c_str(),it->offset,typeMap(it->type));
				}
				globalOffset -= offsetDelta;
			}

			scopeStack.pop();
			if (!scopeStack.empty())
				currentScope = scopeStack.top();
			else
				currentScope = NULL;
		}
	}

	Variable getCurrentScopeVarByName(std::string& varName)
	{
		Variable dummy;
		dummy.name = varName;
		return *(currentScope->varSet.find(dummy));
	}

	VarType getCurrentScopeVarType(std::string& varName)
	{
		if (!varExistsInCurrentScope(varName))
			return ERROR_T;

		else
			return getCurrentScopeVarByName(varName).type;
	}
private:
	int globalOffset;
	Scope currentScope;
	ScopeStack scopeStack;

	const char* typeMap(VarType vType)
	{
		if (vType == NIS_T)
			return "NIS";
		if (vType == AGORA_T)
			return "AGORA";
		if (vType == BOOL_T)
			return "bool";
		return "int";
	}
};

/*==== End of Scope definitions ====*/

#endif /* SCOPE_H_ */
