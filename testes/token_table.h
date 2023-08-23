#ifndef TOKEN_TABLE_H
#define TOKEN_TABLE_H

#define TOKEN_TABLE_INITIAL_SIZE 100

void initializeTokenTable();
void addToken(const int token_category, const int attribute);
void printFirst10Entries();

#endif