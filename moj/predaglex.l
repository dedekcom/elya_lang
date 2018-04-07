 #include "y.tab.h"
 #include<stdio.h>
 char tab[1000];
 int idtab=0;

INT	[0-9]+
IDENT	[_a-zA-Z][a-zA-Z0-9_]*	
REAL	[0-9]+"."[0-9]+

%X koment literal

%%

[ \t]	;

"//".*	;

"/*"	{		BEGIN koment;	}
	
<koment>"*/"	{	BEGIN INITIAL;		}
<koment>(.|\n)	;

\"	{	idtab=1;printf("\n"); tab[0]='\"';
		BEGIN literal;	}
<literal>\"	{	tab[idtab]='\"'; idtab++;
			tab[idtab]='\0';
			printf("\t\t100\t%s",tab);
			strcpy(yylval.s,tab);
			BEGIN INITIAL;
			return NM_STRING;		}
<literal>.	{	tab[idtab]=yytext[0];
			idtab++;
			printf("%s",yytext);		}
<literal>\n	

"*/"		{	printf("!!Nie otwarto komentarza\t\t12\n");					exit(1); 
		}
"int"		{	printf("\n%s",yytext); return KW_INT;		}
"real"		{	printf("\n%s",yytext); return KW_REAL;		}
"while"		{	printf("\n%s",yytext); return KW_WHILE;		}
"for"		{	printf("\n%s",yytext); return KW_FOR;		}
"string"	{	printf("\n%s",yytext); return KW_STRING;	}
"class"	{	printf("\n%s",yytext); return KW_CLASS; }
"module"	{	printf("\n%s",yytext); return KW_MODULE; }
"game"	{	printf("\n%s",yytext); return KW_GAME; }
"if"	{	printf("\n%s",yytext); return KW_IF; }
"new"	{	printf("\n%s",yytext); return KW_NEW; }
"this"	{	printf("\n%s",yytext); return KW_THIS; }
"else"	{	printf("\n%s",yytext); return KW_ELSE; }
"return"	{	printf("\n%s",yytext); return KW_RETURN; }

{REAL}	{	printf("\nfloat %s",yytext); strcpy(yylval.s,yytext); return NM_REAL;}
{INT}		{	printf("\nint %s",yytext); strcpy(yylval.s,yytext); return NM_INT;}

">="	{	printf("\n%s",yytext);return BH_AE;}
"<="	{	printf("\n%s",yytext);return BH_LE;}
"++"	{	printf("\n%s",yytext);return BH_PP;}
"--"	{	printf("\n%s",yytext);return BH_MM;}
"+="	{	printf("\n%s",yytext);return BH_PE;}
"-="	{	printf("\n%s",yytext);return BH_MNE;}
"*="	{	printf("\n%s",yytext);return BH_MLE;}
"/="	{	printf("\n%s",yytext);return BH_DE;}
"%="	{	printf("\n%s",yytext);return BH_MDE;}
"=="	{	printf("\n%s",yytext);return BH_E;}
"&&"	{	printf("\n%s",yytext);return BH_ANDAND;}
"||"	{	printf("\n%s",yytext);return BH_OROR;}
"!="	{	printf("\n%s",yytext);return BH_NE;}
"."	{	printf("\n%s",yytext);return yytext[0]; }
","	{	printf("\n%s",yytext);return yytext[0]; }
"+"	{	printf("\n%s",yytext);return yytext[0]; }
"-"	{	printf("\n%s",yytext);return yytext[0]; }
"#"	{	printf("\n%s",yytext);return yytext[0]; }
"<"	{	printf("\n%s",yytext);return yytext[0]; }
">"	{	printf("\n%s",yytext);return yytext[0]; }
";"	{	printf("\n%s",yytext);return yytext[0]; }
":"	{	printf("\n%s",yytext);return yytext[0]; }
"'"	{	printf("\n%s",yytext);return yytext[0]; }
"{"	{	printf("\n%s",yytext);return yytext[0]; }
"}"	{	printf("\n%s",yytext);return yytext[0]; }
"="	{	printf("\n%s",yytext);return yytext[0]; }
"("	{	printf("\n%s",yytext);return yytext[0]; }
")"	{	printf("\n%s",yytext);return yytext[0]; }
"*"	{	printf("\n%s",yytext);return yytext[0]; }
"/"	{	printf("\n%s",yytext);return yytext[0]; }
"%"	{	printf("\n%s",yytext);return yytext[0]; }
"["	{	printf("\n%s",yytext);return yytext[0]; }
"]"	{	printf("\n%s",yytext);return yytext[0]; }

{IDENT}	{ strcpy(yylval.s,yytext);
		printf("\n%s\t\t400\t\"%s\"",yytext,yytext); return IDENTIFIER;
	}

(.|\n)	;

%%

int yywrap()
{
   if (YYSTATE == literal || YYSTATE==koment)
	printf("\nNiepoprawnie zamkniety plik\n");
	       
    return(1);
}

