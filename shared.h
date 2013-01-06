#ifndef _SHARED_H_
#define _SHARED_H_

#include "output.hpp"
#include <string>

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
	VarType type;
	std::string name;
	struct
	{
		std::string name;
		VarType type;
	} expInfo;

} STYPE;


#define YYSTYPE STYPE





#endif
