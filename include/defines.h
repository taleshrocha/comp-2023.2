#ifndef DEFINES_H
#define DEFINES_H

// TOKENS
#define CONST 1
#define ID 2
#define ATTRIB 3  // Atribuicao
#define SEMICOLON 4
#define OR 5
#define AND 6
#define NEQ 7
#define EQ 8
#define LESS 9
#define GREATER 10
#define LEQ 11
#define GEQ 12
#define NOT 13
#define PLUS 14
#define MINUS 15
#define MULTIPLY 16
#define DIVIDE 17
#define MOD 18
#define LPAR 19  // (
#define RPAR 20  // )
#define V_INT 21
#define V_REAL 22
#define V_BOOL 23
#define V_CHAR 24
#define V_STRING 25
#define DOT 26
#define LBRA 27  // Left bracket [
#define RBRA 28  // right bracket ]
#define TYPE 29
#define T_BOOL 30
#define T_INT 31
#define T_REAL 32
#define T_CHAR 33
#define ARRAY 34
#define OF 35
#define RECORD 36
#define END 37
#define INTERVAL 38  // Corresponds to '..'
#define COMMA 39
#define COLON 40
#define PROCEDURE 41
#define FUNCTION 42
#define VAR 43
#define _BEGIN 44
#define FOR 45
#define TO 46
#define STEP 47
#define LOOP 48
#define EXIT 49
#define WHEN 50
#define CONTINUE 51
#define BREAK 52
#define IF 53
#define THEN 54
#define ELSE 55
#define RETURN 56

// NON-TERMINALS

#define Prog 100
#define Decl 101
#define Consts 102
#define Exp 103
#define Exp_ 104
#define Terms 105
#define Terms_ 106
#define Comps 107
#define Comps_ 108
#define Factor 109
#define AriOp 110
#define AriOp_ 111
#define AriOp2 112
#define AriOp2_ 113
#define Parenthesis 114
#define UnaryExp 115
#define SimpleExp 116
#define NumExp 117
#define AcessMemAddr 118
#define AcessMemAddr_ 119
#define Types 120
#define TypeDec 121
#define Interval 122
#define Interval_ 123
#define Fields 124
#define SubProg 125
#define ProcedureDecl 126
#define FunctionDecl 127
#define Parameters 128
#define ParametersAux 129
#define ParametersAux_ 130
#define Vars 131
#define CmdBlock 132
#define Cmds 133
#define Cmds_ 134
#define CmdAux 135
#define CmdAux_ 136
#define CmdConditional 137
#define CmdConditionalEnd 138
#define CmdReturn 139
#define CmdReturnExp 140
#define Args 141
#define ArgsAux 142
#define ArgsAux_ 143

#define EndOfInput 0

#endif  // DEFINES_H