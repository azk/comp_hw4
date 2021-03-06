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
	NONE
} ScopeType;



struct scope
{
//	scope(){std::cout << "creating\n";}
//	~scope(){std::cout << "destroying\n";}
	ScopeType scopeType;
	VariableSet varSet;
	bool breakEncountered;
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
