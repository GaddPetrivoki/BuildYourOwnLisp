#include <stdio.h>
#include <stdlib.h>
#include"mpc.h"

#ifdef _WIN32
#include <string.h>

static char buffer[2048];

char* readline(char* prompt) {
	fputs(prompt, stdout);
	fgets(buffer, 2048, stdin);
	char* cpy = malloc(strlen(buffer)+1);
	strcpy(cpy, buffer);
	cpy[strlen(cpy)-1]= '\0';
	return cpy;
}

void add_history(car* unused) {}

#else
#include <editline/readline.h>
#endif

mpc_parser_t* Operator  = mpc_new("operator");
mpc_parser_t* Expr	= mpc_new("expr");
mpc_parser_t* Gadd	= mpc_new("gadd");

mpc_lang(MPCA_LANG_DEFAULT,
"
\
   number   : /-?[0-9]+/;
\
   operator : '+'|'-'|'*'|'/';
\
   expr     : <number>|'('<operator> <expr>+ ')';
\
   gadd     : /^/ <operator> <expr>+ /$/;
\
",
Number, Operator, Expr, Gadd);



int main(int argc, char** argv){
	puts("Gadd version 0.0.0.0.1");
	puts("Press Ctrl+c to Exit\n");

	while(1){
	char* input = readline("Gadd> ");
	add_history(input);
	printf("No you're a %s\n", input);
	free(input);
	}
mpc_cleanup(4,Number,Operator,Expr,Gadd);
return 0;

}
