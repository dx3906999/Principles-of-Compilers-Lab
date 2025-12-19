parser grammar SafeCParser;
options { tokenVocab = SafeCLexer; }

compUnit: (decl | funcDef)+ EOF;

decl: constDecl | varDecl;

funcDef: Void Identifier LeftParen RightParen block;

constDecl: Const bType constDef (Comma constDef)* SemiColon;

constDef: Identifier Assign exp | array Assign LeftBrace exp (Comma exp)* RightBrace;

varDecl: bType varDef (Comma varDef)* SemiColon;

bType: Int;

varDef: Identifier | array | Identifier Assign exp | array Assign LeftBrace exp (Comma exp)* RightBrace;

array: obcArray | unobcArray;

obcArray: Obc unobcArray;

unobcArray: Identifier LeftBracket (exp)? RightBracket;

block: LeftBrace blockItem* RightBrace; 

blockItem: decl | stmt;

stmt: block
    | lval Assign exp SemiColon
    | Identifier LeftParen RightParen SemiColon
    | exp? SemiColon
    | While LeftParen cond RightParen stmt
    | If LeftParen cond RightParen stmt (Else stmt)?
    ;

cond: LeftParen cond RightParen
    | exp (Equal | NonEqual | Less | Greater | LessEqual | GreaterEqual) exp
    ;

lval: Identifier | Identifier LeftBracket exp RightBracket;

number: IntConst;

exp:  LeftParen exp RightParen
    | (Plus | Minus) exp
    | exp (Multiply | Divide | Modulo) exp
    | exp (Plus | Minus) exp
    | lval
    | number
    ;