#ifndef _SHARED_H_
#define _SHARED_H_

#include <string>

typedef enum
{
	NIS_T,
	AGORA_T,
	BOOL_T,
	INT_T
} VarType;

typedef struct
{
	std::string name;
	VarType type;
} STYPE;


#define YYSTYPE STYPE





#endif
