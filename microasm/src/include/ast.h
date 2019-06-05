#ifndef AST_H
#define AST_H

#include "token.h"
#include "memory.h"

typedef struct Condition {
    Token name;
    Token value;
} Condition;

typedef struct Line {
    Condition* conditions;
    int conditionCount;
    int conditionCapacity;
    Token* bits;
    int bitCount;
    int bitCapacity;
    Token condition1Equals;
} Line;

typedef struct Header {
    Token* bits;
    int bitCount;
    int bitCapacity;
} Header;

typedef struct Microcode {
    Header head;
    Arena arena;
} Microcode;

void InitMicrocode(Microcode* mcode);

void PrintMicrocode(Microcode* mcode);

void FreeMicrocode(Microcode* mcode);

#endif