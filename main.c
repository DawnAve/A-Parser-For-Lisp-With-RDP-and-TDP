#include <stdio.h>
#include <string.h>
#include  <stdbool.h>
#include <stdio.h>
#include "RDP.h"
#include <signal.h>
#include "TDP.h"
int main(void){
    char input[225];
    //Running RDP first
    printf("Running RDP (Recursive Descent Parser) now.\n");
    printf("Enter an input (\"quit\" to quit): ");
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = '\0';
    while(strcmp (input, "quit")!=0){
        signal(SIGSEGV, handle_segfault); //Used to catch errors, and report "not accepted" messages
        if(input[0] != '('){
            parseTree = parseE(input); 
        }else{
            parseTree = parseL(input); 
        }
        

        printf("Result for input \"%s\" is: \n", input);
        if (parseTree == NULL){
            printf("Invalid input, please try again\n");
        }
        printTree(parseTree, 0);

        printf("Enter an input (\"quit\" to quit): ");
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = '\0';
    }
    //Running TDP now 
    printf("Running TDP (Table Driven Parser) now.\n");
    printf("Enter an input (\"quit\" to quit): ");
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = '\0';
    while(strcmp (input, "quit")!=0){
        signal(SIGSEGV, handle_segfault);
        int** table = create_table();
        if(input[0] != '('){
            parseTree = TDP_parseE(table,input); 
        }else{
            parseTree = TDP_parseL(table,input); 
        }
        printf("Result for input \"%s\" is: \n", input);
        if (parseTree == NULL){
            printf("Invalid input, please try again\n");
        }
        printTree(parseTree, 0);

        printf("Enter an input (\"quit\" to quit): ");
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = '\0';
    }
}
