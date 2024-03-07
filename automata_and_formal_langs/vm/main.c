#include "vm.h"
#include "vmparse.tab.h"
#include <stdio.h>
#include <stdlib.h>

extern FILE *yyin;
int need_close = 0;

int yyparse();

void milan_error(char const * msg)
{
        if(need_close)
                fclose(yyin);
        
	fprintf(stderr, msg);
	exit(1);
}

int main(int argc, char **argv)
{
        if(argc < 2) {
                yyin = stdin;
                printf("Reading input from stdin\n");
        }
        else {
                yyin = fopen(argv[1], "rt");
                if(!yyin) {
                        printf("Unable to read %s\n", argv[1]);
                        return 1;
                }
                
                need_close = 1;
                printf("Reading input from %s\n", argv[1]);
        }
        
        if(0 == yyparse()) {
                run();
        }

        if(need_close) {
                fclose(yyin);
        }
                
        return 0;
}
