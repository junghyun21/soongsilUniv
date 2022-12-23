#include <stdio.h>
#include <stdlib.h>
#include "type.h"

extern int syntax_err;
extern int semantic_err;
extern A_NODE *root;

void initialize();
void semantic_analysis();

void print_ast();
void print_sem_ast();

void main(int argc, char *argv[]) { 

	initialize();

	printf("syntax analysis start!\n");
	yyparse();
	
	if (syntax_err)
		exit(1);
	
	printf("syntax analysis end (no error)\n");
	print_ast(root); // 호출하지 않으면 타입이 이상하게 찍히거나 안찍힘

	printf("\nstart semantic analysis\n");
	semantic_analysis(root);

	if (semantic_err)
		exit(1);

	printf("semantic analysis end (no error)\n");
	print_sem_ast(root);

	exit(0);
}