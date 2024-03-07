%{
#include "vmparse.tab.h"
#include <stdlib.h>

#ifndef __GNUC__
#define YY_NO_UNISTD_H
#endif
%}

%option noyywrap

WHITESPACE      [ \t]+
EOL             \n
INT             -?[0-9]+
COMMENT		;[^\n]*\n

%%

{EOL}           
{COMMENT}
{WHITESPACE}
{INT}           { yylval = atoi(yytext); return T_INT; }

:               { return T_COLON;    }

SET             { return T_SET;      }
STOP            { return T_STOP;     }
LOAD            { return T_LOAD;     }
STORE           { return T_STORE;    }
BLOAD           { return T_BLOAD;    }
BSTORE          { return T_BSTORE;   }
PUSH            { return T_PUSH;     }
POP             { return T_POP;      }
DUP             { return T_DUP;      }
INVERT          { return T_INVERT;   }
ADD             { return T_ADD;      }
SUB             { return T_SUB;      }
MULT            { return T_MULT;     }
DIV             { return T_DIV;      }
COMPARE         { return T_COMPARE;  }
JUMP            { return T_JUMP;     }
JUMP_YES        { return T_JUMP_YES; }
JUMP_NO         { return T_JUMP_NO;  }
INPUT           { return T_INPUT;    }
PRINT           { return T_PRINT;    }
NOP             { return T_NOP;      }

<<EOF>>         { yyterminate();     }

%%

