const char* table[][] = {
    {"S", null, "Prog $", null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, "Prog $", null, null, null, null, null, null, null, null, null, null, null, "Prog $", "Prog $", "Prog $", "Prog $", null, null, null, null, null, null, null, null, null, null, null, null},
    
    {"Prog", null, "Decl CmdBlock", null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, "Decl CmdBlock", null, null, null, null, null, null, null, null, null, null, null, "Decl CmdBlock", "Decl CmdBlock", "Decl CmdBlock", "Decl CmdBlock", null, null, null, null, null, null, null, null, null, null, null, null},
    
    {"Decl", null, "Consts Types SubProg Vars", null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, "Consts Types SubProg Vars", null, null, null, null, null, null, null, null, null, null, null, "Consts Types SubProg Vars", "Consts Types SubProg Vars", "Consts Types SubProg Vars", "Consts Types SubProg Vars", null, null, null, null, null, null, null, null, null, null, null, null},
    
    {"Consts", null, "const Id := Exp ; Consts", null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, "ε", null, null, null, null, null, null, null, null, null, null, null, "ε", "ε", "ε", "ε", null, null, null, null, null, null, null, null, null, null, null, null},
    
    {"Exp", null, null, "Terms Exp_", null, null, null, null, null, null, null, null, null, null, "Terms Exp_", "Terms Exp_", "Terms Exp_", null, null, null, "Terms Exp_", null, "Terms Exp_", "Terms Exp_", "Terms Exp_", "Terms Exp_", "Terms Exp_", null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null},
    
    {"Exp_", null, null, null, null, "ε", "|| Terms Exp_", null, null, null, null, null, null, null, null, null, null, null, null, null, null, "ε", null, null, null, null, null, null, null, "ε", null, null, null, null, null, null, null, null, "ε", "ε", "ε", null, null, null, null, "ε", null, "ε", "ε", null, null, null, null, null, null, "ε", null, null},
    
    {"Terms", null, null, "Comps Terms_", null, null, null, null, null, null, null, null, null, null, "Comps Terms_", "Comps Terms_", "Comps Terms_", null, null, null, "Comps Terms_", null, "Comps Terms_", "Comps Terms_", "Comps Terms_", "Comps Terms_", "Comps Terms_", null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null},
    
    {"Terms_", null, null, null, null, "ε", "ε", "&& Comps Terms_", null, null, null, null, null, null, null, null, null, null, null, null, null, "ε", null, null, null, null, null, null, null, "ε", null, null, null, null, null, null, null, null, "ε", "ε", "ε", null, null, null, null, "ε", null, "ε", "ε", null, null, null, null, null, null, "ε", null, null},
    
    {"Comps", null, null, "Factor Comps_", null, null, null, null, null, null, null, null, null, null, "Factor Comps_", "Factor Comps_", "Factor Comps_", null, null, null, "Factor Comps_", null, "Factor Comps_", "Factor Comps_", "Factor Comps_", "Factor Comps_", "Factor Comps_", null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null},
    
    {"Comps_", null, null, null, null, "ε", "ε", "ε", "!= Factor", "== Factor", "< Factor", "> Factor", "<= Factor", ">= Factor", null, null, null, null, null, null, null, "ε", null, null, null, null, null, null, null, "ε", null, null, null, null, null, null, null, null, "ε", "ε", "ε", null, null, null, null, "ε", null, "ε", "ε", null, null, null, null, null, null, "ε", null, null},
    
    {"Factor", null, null, "AriOp", null, null, null, null, null, null, null, null, null, null, "! AriOp", "AriOp", "AriOp", null, null, null, "AriOp", null, "AriOp", "AriOp", "AriOp", "AriOp", "AriOp", null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null},
    
    {"AriOp", null, null, "AriOp2 AriOp_", null, null, null, null, null, null, null, null, null, null, null, "AriOp2 AriOp_", "AriOp2 AriOp_", null, null, null, "AriOp2 AriOp_", null, "AriOp2 AriOp_", "AriOp2 AriOp_", "AriOp2 AriOp_", "AriOp2 AriOp_", "AriOp2 AriOp_", null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null},
    
    {"AriOp_", null, null, null, null, "ε", "ε", "ε", "ε", "ε", "ε", "ε", "ε", "ε", null, "+ AriOp2 AriOp_", "- AriOp2 AriOp_", null, null, null, null, "ε", null, null, null, null, null, null, null, "ε", null, null, null, null, null, null, null, null, "ε", "ε", "ε", null, null, null, null, "ε", null, "ε", "ε", null, null, null, null, null, null, "ε", null, null},
    
    {"AriOp2", null, null, "Parenthesis AriOp2_", null, null, null, null, null, null, null, null, null, null, null, "Parenthesis AriOp2_", "Parenthesis AriOp2_", null, null, null, "Parenthesis AriOp2_", null, "Parenthesis AriOp2_", "Parenthesis AriOp2_", "Parenthesis AriOp2_", "Parenthesis AriOp2_", "Parenthesis AriOp2_", null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null},
    
    {"AriOp2_", null, null, null, null, "ε", "ε", "ε", "ε", "ε", "ε", "ε", "ε", "ε", null, "ε", "ε", "* Parenthesis AriOp2_", "/ Parenthesis AriOp2_", "% Parenthesis AriOp2_", null, "ε", null, null, null, null, null, null, null, "ε", null, null, null, null, null, null, null, null, "ε", "ε", "ε", null, null, null, null, "ε", null, "ε", "ε", null, null, null, null, null, null, "ε", null, null},
    
    {"Parenthesis", null, null, "UnaryExp", null, null, null, null, null, null, null, null, null, null, null, "UnaryExp", "UnaryExp", null, null, null, "( Exp )", null, "UnaryExp", "UnaryExp", "UnaryExp", "UnaryExp", "UnaryExp", null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null},
    
    {"UnaryExp", null, null, "SimpleExp", null, null, null, null, null, null, null, null, null, null, null, "+ UnaryExp", "- UnaryExp", null, null, null, null, null, "SimpleExp", "SimpleExp", "SimpleExp", "SimpleExp", "SimpleExp", null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null},
    
    {"SimpleExp", null, null, "AcessMemAddr", null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, "NumExp", "NumExp", "NumExp", "NumExp", "NumExp", null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null},
    
    {"NumExp", null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, "V_INT", "V_REAL", "V_BOOL", "V_CHAR", "V_STRING", null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null},
    
    {"AcessMemAddr", null, null, "Id AcessMemAddr_", null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null},
    
    {"AcessMemAddr_", null, null, null, "ε", "ε", "ε", "ε", "ε", "ε", "ε", "ε", "ε", "ε", null, "ε", "ε", "ε", "ε", "ε", "( Args ) AcessMemAddr_", "ε", null, null, null, null, null, ". Id AcessMemAddr_", "[ Exp ] AcessMemAddr_", "ε", null, null, null, null, null, null, null, null, "ε", "ε", "ε", null, null, null, null, "ε", null, "ε", "ε", null, null, null, null, null, null, "ε", null, null},
    
    {"Types", null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, "type Id := TypeDec ; Types", null, null, null, null, null, null, null, null, null, null, null, "ε", "ε", "ε", "ε", null, null, null, null, null, null, null, null, null, null, null, null},
    
    {"TypeDec", null, null, "Id", null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, "bool", "int", "real", "char", "array [ Interval ] of TypeDec", null, "record Fields end", null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null},
    
    {"Interval", null, null, "Exp .. Exp Interval_", null, null, null, null, null, null, null, null, null, null, "Exp .. Exp Interval_", "Exp .. Exp Interval_", "Exp .. Exp Interval_", null, null, null, "Exp .. Exp Interval_", null, "Exp .. Exp Interval_", "Exp .. Exp Interval_", "Exp .. Exp Interval_", "Exp .. Exp Interval_", "Exp .. Exp Interval_", null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null},
    
    {"Interval_", null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, "ε", null, null, null, null, null, null, null, null, null, null, ", Interval", null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null},
    
    {"Fields", null, null, "Id : TypeDec ; Fields", null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, "ε", null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null},
    
    {"SubProg", null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, "ProcedureDecl SubProg", "FunctionDecl SubProg", "ε", "ε", null, null, null, null, null, null, null, null, null, null, null, null},
    
    {"ProcedureDecl", null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, "procedure Id ( Parameters ) CmdBlock ;", null, null, null, null, null, null, null, null, null, null, null, null, null, null, null},
    
    {"FunctionDecl", null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, "function Id ( Parameters ) : TypeDec CmdBlock ;", null, null, null, null, null, null, null, null, null, null, null, null, null, null},
    
    {"Parameters", null, null, "ParametersAux", null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, "ε", null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null},
    
    {"ParametersAux", null, null, "Id : TypeDec ParametersAux_", null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null},
    
    {"ParametersAux_", null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, "ε", null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, ", ParametersAux", null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null},
    
    {"Vars", null, null, "ε", null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, "var Id : TypeDec ; Vars", "ε", "ε", null, null, "ε", "ε", null, "ε", "ε", "ε", null, null, "ε"},
    
    {"CmdBlock", null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, "begin Vars Cmds end", null, null, null, null, null, null, null, null, null, null, null, null},
    
    {"Cmds", null, null, "CmdAux Cmds_", null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, "CmdAux Cmds_", "CmdAux Cmds_", null, null, "CmdAux Cmds_", "CmdAux Cmds_", null, "CmdAux Cmds_", "CmdAux Cmds_", "CmdAux Cmds_", null, null, "CmdAux Cmds_"},
    
    {"Cmds_", null, null, null, null, "; Cmds", null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, "ε", null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null},
    
    {"CmdAux", null, null, "AcessMemAddr CmdAux_", null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, "CmdBlock", "for Id := Exp to Exp step Exp CmdBlock", null, null, "loop Vars Cmds end", "exit when Exp", null, "continue", "break", "CmdConditional", null, null, "CmdReturn"},
    
    {"CmdAux_", null, null, null, ":= Exp", "ε", null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, "ε", null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null},
    
    {"CmdConditional", null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, "if Exp then CmdBlock CmdConditionalEnd", null, null, null},
    
    {"CmdConditionalEnd", null, null, null, null, "ε", null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, "ε", null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, "else CmdBlock", null},
    
    {"CmdReturn", null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, "return CmdReturnExp"},
    
    {"CmdReturnExp", null, null, "Exp", null, "ε", null, null, null, null, null, null, null, null, "Exp", "Exp", "Exp", null, null, null, "Exp", null, "Exp", "Exp", "Exp", "Exp", "Exp", null, null, null, null, null, null, null, null, null, null, null, "ε", null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null},
    
    {"Args", null, null, "ArgsAux", null, null, null, null, null, null, null, null, null, null, "ArgsAux", "ArgsAux", "ArgsAux", null, null, null, "ArgsAux", "ε", "ArgsAux", "ArgsAux", "ArgsAux", "ArgsAux", "ArgsAux", null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null},
    
    {"ArgsAux", null, null, "Exp ArgsAux_", null, null, null, null, null, null, null, null, null, null, "Exp ArgsAux_", "Exp ArgsAux_", "Exp ArgsAux_", null, null, null, "Exp ArgsAux_", null, "Exp ArgsAux_", "Exp ArgsAux_", "Exp ArgsAux_", "Exp ArgsAux_", "Exp ArgsAux_", null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null},
    
    {"ArgsAux_", null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, "ε", null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, ", ArgsAux", null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null},
};


