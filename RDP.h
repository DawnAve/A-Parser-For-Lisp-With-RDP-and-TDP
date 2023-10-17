#ifndef _RDP_h
#define _RDP_h
typedef struct NODE *TREE;
struct NODE {
    char label;
    TREE leftmostChild, rightSibling;
};
TREE parseTree; /* holds the result of the parse */
char *nextTerminal; /* current position in input string */
TREE makeNode0(char x);
TREE makeNode1(char x, TREE t);
TREE makeNode2(char x, TREE t1, TREE t2);
TREE makeNode3(char x, TREE t1, TREE t2, TREE t3);
TREE makeNode4(char x, TREE t1, TREE t2, TREE t3, TREE t4); 
void printTree(TREE node, int depth);
TREE Expr(void);
TREE Atom(void);
TREE Word(void);
TREE Number(void);
TREE List(void);
TREE Elements(void);
TREE Rest(void);
TREE WordT(void);
TREE NumberT(void);
TREE Digit(void);
TREE Letter(void);
bool lookahead(char c);
TREE parseE(char* input);
TREE parseL(char* input);
bool match(char c);
void handle_segfault(int sig);
#endif