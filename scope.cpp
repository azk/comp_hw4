/*
 * scope.cpp
 *
 *  Created on: Jan 6, 2013
 *      Author: azk
 */

#include "scope.h"

ScopeGlobal* globals;

ScopeGlobal::~ScopeGlobal()
{
	while (!scopeStack.empty())
		scopeStack.pop();
}


