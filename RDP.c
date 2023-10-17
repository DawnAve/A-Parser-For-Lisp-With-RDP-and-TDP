/* -*- compile-command: "gcc -o focs_11_27_gf -std=c99 -Wall -Werror focs_11_27_gf.c"; -*-
 *
 * focs_11_27_gf.c
 *
 * George Ferguson's adaptation of the code from FOCS Fig. 11.27 for
 * parsing strings of balanced parentheses.
 *
 * Changes from the code in focs_11_27.c:
 * - Define and use functions lookahead and match rather than direct
 *   string manipulation in the parsing function
 *   - These use type bool, so include stdbool.h
 * - Write parsing function B MECHANICALLY based on the productions, as seen
 *   in class.
 * - Define and use function parse to check that the entire was consumed
 *   after the parsing function returns successfully
 * - Define a stub for printing the parse tree, but you will need to write
 *   this yourself
 *   - This uses printf, so include stdio.h
 */
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <ctype.h>
#include <signal.h>

#define FAILED NULL

typedef struct NODE *TREE;
struct NODE {
    char label;
    TREE leftmostChild, rightSibling;
};

TREE makeNode0(char x);
TREE makeNode1(char x, TREE t);
TREE makeNode2(char x, TREE t1, TREE t2);
TREE makeNode3(char x, TREE t1, TREE t2, TREE t3);
TREE makeNode4(char x, TREE t1, TREE t2, TREE t3, TREE t4); TREE B(void);

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

TREE parseTree; /* holds the result of the parse */
char *nextTerminal; /* current position in input string */

void handle_segfault(int sig) {
    printf("Input not accpeted\n");
    exit(1);
}
/**
 * Returns true if the current input symbol is the given char, otherwise false.
 */
bool lookahead(char c) {
    return *nextTerminal == c;
}

/**
 * If the current input symbol is the given char, advance to the next
 * character of the input and return true, otherwise leave it and return false.
 */
bool match(char c) {
    if (lookahead(c)) {
	nextTerminal += 1;
	return true;
    } else {
	return false;
    }
}

/**
 * Attempt to parse the given string as a string of balanced parentheses.
 * If the parse succeeds, return the parse tree, else return FAILED (NULL).
 */




TREE makeNode0(char x)
{
    TREE root;
    root = (TREE) malloc(sizeof(struct NODE));
    root->label = x;
    root->leftmostChild = NULL;
    root->rightSibling = NULL;
    return root;
}

TREE makeNode1(char x, TREE t)
{
    TREE root;
    root = makeNode0(x);
    root->leftmostChild = t;
    return root;
}
TREE makeNode2(char x, TREE t1, TREE t2)
{
    TREE root;
    root = makeNode1(x, t1);
    t1->rightSibling = t2;
    return root;
}
TREE makeNode3(char x, TREE t1, TREE t2, TREE t3)
{
    TREE root;
    root = makeNode1(x, t1);
    t1->rightSibling = t2;
    t2->rightSibling = t3;
    return root;
}
TREE makeNode4(char x, TREE t1, TREE t2, TREE t3, TREE t4)
{
    TREE root;
    root = makeNode1(x, t1);
    t1->rightSibling = t2;
    t2->rightSibling = t3;
    t3->rightSibling = t4;
    return root;
}
void printTree(TREE node, int depth) {
    if (node == NULL){
        return;
    }
    for (int i = 0; i < depth; i++) {
        printf("  ");
    }
    printf("%c\n", node->label);
    if (node->leftmostChild != NULL) {
        printTree(node->leftmostChild, depth + 1);
    }
    if (node->rightSibling != NULL) {
        printTree(node->rightSibling, depth);
    }
}

TREE List(void) {
    //printf("List visited\n");
    //printf("%s\n",nextTerminal);
    /*if (!lookahead('(')) {
	    TREE atom = Atom();
        if (atom != NULL){
            return atom;
        }else{
            return NULL;
        }
    }else{*/
    if (!match('(')) return NULL;
    TREE elements = Elements();
    if (elements == NULL ){
        //printf("element null");
        return NULL;
    }
    if (!match(')')) return NULL;
        
    return makeNode3('L', makeNode0('('),elements, makeNode0(')'));
    
}

TREE Expr(void) {
    //printf("EXPR visited\n");
    //printf("%s\n",nextTerminal);
    if (!lookahead('(')){
        TREE atom =Atom();
        if (atom != NULL) {
            return makeNode1('E', atom);
    }
    }else{
        TREE list =List();
        if (list != NULL) {
            return makeNode1('E', list);
        }
    }
    return NULL;
}

TREE Atom(void) {
    //printf("ATOM visited\n");
    //printf("%s\n",nextTerminal);
    TREE word = Word();
    if (word != NULL) {
        return makeNode1('A',word);
    }
    TREE number = Number();
    if (number != NULL) {
        return makeNode1('A',number);
    }
    return NULL;
}

TREE Word(void) {
    TREE letter = Letter();
    if (letter == NULL) return NULL;
    
    TREE wordT = WordT();
    return makeNode2('N', letter, wordT);
}
TREE Letter(void){
    if (!islower(*nextTerminal)) {
        return NULL;
    }else{
        //printf("construcsion achieved");
        TREE temp = makeNode0(*nextTerminal);
        nextTerminal +=1;
        return makeNode1('l',temp);
    }
}
TREE WordT(void) {
    //printf("WordT visited\n");
    TREE word = Word();
    if (word == NULL){
        //printf("WordT e added\n");
        return makeNode1('w', makeNode0('*'));
    }
    return makeNode1('w',word);
    
}

TREE Number(void) {
    //printf("Number visited\n");
    //printf("%s\n",nextTerminal);
    TREE digit = Digit();
    if (digit == NULL) return NULL;
    
    TREE numberT = NumberT();
    return makeNode2('N', digit, numberT);
}
TREE Digit(void){
    //printf("Digit visited\n");
    //printf("%s\n",nextTerminal);
    if (!isdigit(*nextTerminal)) {
        return NULL;
    }else{
        TREE temp = makeNode0(*nextTerminal);
        nextTerminal +=1;
        return makeNode1('D',temp);
    }
}
TREE NumberT(void) {
    //printf("NumberT visited\n");
    //printf("%s\n",nextTerminal);
    TREE number = Number();

    if (number == NULL) return makeNode1('n',makeNode0('*'));
    return makeNode1('n', number);
    
}

TREE Elements(void) {
    //printf("Elements visited\n");
    //printf("%s\n",nextTerminal);
    TREE expr = Expr();
    
    if (expr == NULL) {
        //printf("e added");
        return makeNode1('E', makeNode0('*'));  // epsilon
    }
    TREE rest = Rest();
    //printf("%s\n",nextTerminal);
    /*if (lookahead(' ')){
        return NULL;
    }*/

    /*if (rest == NULL || expr == NULL) {
        //printf("Elements e added\n");
        return makeNode1('e', makeNode0('*'));  // epsilon
    }*/
    return makeNode2('e', expr, rest);
}

TREE Rest(void) {
    //printf("Rest visited\n");
    //printf("%s\n",nextTerminal);
    if(lookahead(' ')){
        
    }
    if (!match(' ')  ) {
        return NULL; 
    }
    //printf("Break-one\n");
    TREE expr = Expr();
    //printf("Break-two\n");

    TREE rest = Rest();
    if (expr == NULL && rest == NULL){
        //printf("Rest e added\n");
        return makeNode0('*');
    }
    TREE space = makeNode0('-');
    return makeNode3('R', space, expr, rest);
}


TREE parseE(char* input) {
    nextTerminal = input;
    char blank = '\0';
    if(*nextTerminal == blank){
        //printf("get in successfully\n");
        return makeNode0('*');
    }
    TREE parseTree = Expr();
    if (parseTree != NULL && lookahead('\0')) {
        return parseTree;
    } else {
        return NULL;
    }
}
TREE parseL(char* input) {
    nextTerminal = input;
    TREE parseTree = List();
    if (parseTree != NULL && lookahead('\0')) {
        return parseTree;
    } else {
        return NULL;
    }
}
/*int main(void)
{
    signal(SIGSEGV, handle_segfault);
    parseTree = parse("(defun f (x y) ((times (plus x y) (plus x y))))");
    if (parseTree == NULL){
        printf("Not accpeted\n");
    }
    printTree(parseTree, 0);
}*/

