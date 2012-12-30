#ifndef _SHARED_H_
#define _SHARED_H_

#include <stdio.h>

#define MAX_STR_SIZE 1024 // ?????

typedef union
{
    int number;
    char name[MAX_STR_SIZE];
} STYPE;
#define YYSTYPE STYPE

#endif
