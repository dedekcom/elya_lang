 #include "y.tab.h"
 #include<stdio.h>
 char tab[1000];
 int idtab=0;
 
%X koment literal

%%

[ \t]	;

"//".*	;

"/*"	{		BEGIN koment;	}
	
<koment>"*/"	{	printf("!!Komentarz /* */\n");
			BEGIN INITIAL;		}
<koment>(.|\n)	;

\"	{	idtab=0;
		printf("\n");
		BEGIN literal;	}
<literal>\"	{	tab[idtab]='\0';
			printf("\t\t100\t%s",tab);
			BEGIN INITIAL;
			return LIT_LIT;		}
<literal>.	{	tab[idtab]=yytext[0];
			idtab++;
			printf("%s",yytext);		}
<literal>\n	

"*/"		{	printf("!!Nie otwarto komentarza\t\t12\n");		}

"int"		{	printf("\n%s",yytext); return KW_INT;		}
"float"		{	printf("\n%s",yytext); return KW_FLOAT;		}
"do"		{	printf("\n%s",yytext); return KW_DO;		}
"static"		{	printf("\n%s",yytext); return KW_STATIC;		}
"void"		{	printf("\n%s",yytext); return KW_VOID;		}
"while"		{	printf("\n%s",yytext); return KW_WHILE;		}
"main"		{	printf("\n%s",yytext); return KW_MAIN;		}
"System"	{ 	printf("\n%s",yytext); return KW_SYSTEM;	}
"public"	{	printf("\n%s",yytext); return KW_PUBLIC;	}
"protected"	{	printf("\n%s",yytext); return KW_PROTECTED;	}
"private"	{	printf("\n%s",yytext); return KW_PRIVATE;	}
"String"	{	printf("\n%s",yytext); return KW_STRING;	}
"class"	{	printf("\n%s",yytext); return KW_CLASS; }
"if"	{	printf("\n%s",yytext); return KW_IF; }
"else"	{	printf("\n%s",yytext); return KW_ELSE; }
"return"	{	printf("\n%s",yytext); return KW_RETURN; }


[0-9]+		{	printf("\nint %s",yytext); strcpy(yylval.s,yytext); return NM_INT;}
[0-9]*"."[0-9]+	{	printf("\nfloat %s",yytext); strcpy(yylval.s,yytext); return NM_FLOAT;}

">="	{	printf("\n%s",yytext);return BH_AE;}
"<="	{	printf("\n%s",yytext);return BH_LE;}
"++"	{	printf("\n%s",yytext);return BH_PP;}
"--"	{	printf("\n%s",yytext);return BH_MM;}
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
"["	{	printf("\n%s",yytext);return yytext[0]; }
"]"	{	printf("\n%s",yytext);return yytext[0]; }

[_a-zA-Z][a-zA-Z0-9_]*	{ strcpy(yylval.s,yytext);
			printf("\n%s\t\t400\t\"%s\"",yytext,yytext); return ID_ID;
		}

(.|\n)	;

%%

int yywrap()
{
   if (YYSTATE == literal || YYSTATE==koment)
	printf("\nNiepoprawnie zamkniety plik\n");
	       
    return(1);
}

