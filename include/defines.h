// TOKENS
#define ID 1
#define CONST 2
#define T_INT 3
#define T_REAL 4
#define T_CHAR 5
#define T_BOOL 6

#define V_INT 7
#define V_CHAR 8
#define V_BOOL 9
#define V_REAL 10
#define V_STRING 11

#define EQ 12
#define LEQ 13
#define GEQ 14
#define GREATER 15
#define LESS 16
#define NEQ 17

#define PLUS 18
#define MINUS 19
#define DIVIDE 20
#define MULTIPLY 21
#define MOD 22


#define LOOP 23
#define IF 24
#define ELSE 25
#define _BEGIN 26
#define END 27

#define AND 28
#define NOT 29
#define OR 30

#define TYPE 31
#define ARRAY 32
#define EXIT 33
#define WHEN 34
#define TO 35
#define STEP 36
#define THEN 37
#define ATTRIB 38 //Atribuicao


#define FUNCTION 39
#define PROCEDURE 40
#define RETURN 41
#define BREAK 42
#define CONTINUE 43
#define RECORD 44
#define OF 45
#define VAR 46

#define LPAR 47 // (
#define RPAR 48 // )
#define LBRA 49 //Left bracket [
#define RBRA 50 //right bracket ]

#define DOT 51
#define COMMA 52
#define SEMICOLON 53
#define COLON 54

#define FOR 55
#define INTERVAL 56 //Corresponds to '..'

// NON-TERMINALS

#define Prog 100
#define Decl 101
#define Consts 102
#define Exp 104
#define Exp_ 105
#define Terms 106
#define Terms_ 107
#define Comps 108
#define Comps_ 109
#define Factor 110
#define AriOp 111
#define AriOp_ 112
#define AriOp2 113
#define AriOp2_ 114
#define Parenthesis 115 
#define UnaryExp 116
#define SimpleExp 117
#define NumExp 118
#define AcessMemAddr 119
#define AcessMemAddr_ 120
#define Types 121
#define TypeDec 122
#define Interval 123
#define Interval_ 124
#define Fields 125
#define SubProg 126
#define ProcedureDecl 127 
#define FunctionDecl 128
#define Parameters 129
#define ParametersAux 130
#define ParametersAux_ 131
#define Vars 132
#define CmdBlock 133 
#define Cmds 134
#define Cmds_ 135
#define CmdAux 136
#define CmdAux_ 137
#define CmdConditional 138 
#define CmdConditionalEnd 139
#define CmdReturn 140
#define CmdReturnExp 141
#define Args 142
#define ArgsAux 144
#define ArgsAux_ 145

#define EndOfInput 0