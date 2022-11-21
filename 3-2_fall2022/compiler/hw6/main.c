#include <stdio.h>
#include <stdlib.h>
#include "type.h"
extern int syntax_err;
extern A_NODE *root;
void initialize();
void print_ast();

void main(int argc, char *argv[]) { 

	initialize();

	printf("syntax analysis start!\n");
	yyparse();
	
	if (!syntax_err) {
		printf("syntax analysis end (no error)\n");
		print_ast(root); // print.c 내부에 존재
	}
}