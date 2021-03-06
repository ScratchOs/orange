#ifndef TOKEN_H
#define TOKEN_H

#include <stdbool.h>
#include <stdint.h>

#define FOREACH_TOKEN(x) \
    x(LEFT_PAREN) x(RIGHT_PAREN) \
    x(LEFT_BRACE) x(RIGHT_BRACE) \
    x(COMMA) x(DOT) x(COLON) x(NUMBER) \
    x(SEMICOLON) x(BINARY) x(EQUAL) \
    x(IDENTIFIER) x(OPCODE) x(HEADER) \
    x(INCLUDE) x(TYPE) x(STRING) \
    x(ENUM) x(BITGROUP) x(DOLLAR) \
    x(ERROR) x(EOF) x(NULL)

#define ENUM_TOKEN(x) TOKEN_##x,
#define ADD_TOKEN(x) +1

typedef enum MicrocodeTokenType {
    FOREACH_TOKEN(ENUM_TOKEN)
} MicrocodeTokenType;

const char* TokenNames[FOREACH_TOKEN(ADD_TOKEN)];

#undef ENUM_TOKEN
#undef ADD_TOKEN

typedef struct SourceRange {
    const char* filename;
    const char* tokenStart;
    const char* sourceStart;
    int length;
    int line;
    int column;
} SourceRange;

typedef union TokenData {
    const char* string;
    unsigned int value;
} TokenData;

// type and source location of a token
typedef struct Token {
    MicrocodeTokenType type;
    SourceRange range;
    TokenData data;
} Token;

// output the representation of a token to stdout
void TokenPrint(Token* token);

Token createStrToken(const char* str);
Token* createStrTokenPtr(const char* str);
Token* createUIntTokenPtr(unsigned int num);

uint32_t tokenHash(void* value);
bool tokenCmp(void* a, void* b);
const char* tokenAllocName(Token* tok);

#endif
