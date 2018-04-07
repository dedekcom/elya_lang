 #include "y.tab.h"
 #include<stdio.h>
 char tab[1000];
 int idtab=0;
 void copychar(char z);

INT	[0-9]+
IDENT	[_a-zA-Z][a-zA-Z0-9_]*
REAL	[0-9]+"."[0-9]+

%X koment literal literalchar

%%

[ \t]	;

"//".*	;

"/*"	{		BEGIN koment;	}
	
<koment>"*/"	{	BEGIN INITIAL;		}
<koment>(.|\n)	;

\"	{	idtab=1;printf("\n"); tab[0]='\"';
		BEGIN literal;	}
<literal>\\	{	tab[idtab]='\\';	idtab++;	BEGIN literalchar;	}
<literalchar>.	{	tab[idtab]=yytext[0];	idtab++;	BEGIN literal;	}
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
"bool"		{	printf("\n%s",yytext); return KW_INT;		}
"real"		{	printf("\n%s",yytext); return KW_REAL;		}
"def"		{	printf("\n%s",yytext); return KW_DEF;		}
"while"		{	printf("\n%s",yytext); return KW_WHILE;		}
"func"		{	printf("\n%s",yytext); return KW_FUNC;		}
"for"		{	printf("\n%s",yytext); return KW_FOR;		}
"string"	{	printf("\n%s",yytext); return KW_STRING;	}
"class"	{	printf("\n%s",yytext); return KW_CLASS; }
"module"	{	printf("\n%s",yytext); return KW_MODULE; }
"game"	{	printf("\n%s",yytext); return KW_GAME; }
"if"	{	printf("\n%s",yytext); return KW_IF; }
"new"	{	printf("\n%s",yytext); return KW_NEW; }
"delete"	{	printf("\n%s",yytext); return KW_DELETE; }
"this"	{	printf("\n%s",yytext); return KW_THIS; }
"else"	{	printf("\n%s",yytext); return KW_ELSE; }
"null"	{	printf("\n%s",yytext); strcpy(yylval.s,"\"null\""); return NM_STRING; }
"return"	{	printf("\n%s",yytext); return KW_RETURN; }
"public"	{	printf("\n%s",yytext); return KW_PUBLIC; }
"virtual"	{	printf("\n%s",yytext); return KW_VIRTUAL; }
"operator"	{	printf("\n%s",yytext); return KW_OPERATOR; }
"match"	{	printf("\n%s",yytext); return KW_MATCH; }

"true"	{	printf("\n%s",yytext); strcpy(yylval.s,"1"); return NM_INT;}
"false"	{	printf("\n%s",yytext); strcpy(yylval.s,"0"); return NM_INT;}

{REAL}	{	printf("\nfloat %s",yytext); strcpy(yylval.s,yytext); return NM_REAL;}
{INT}		{	printf("\nint %s",yytext); strcpy(yylval.s,yytext); return NM_INT;}
\'[a-zA-Z0-9\~\`\!\@\#\$\%\^\&\*\(\)\-\_\+\=\{\[\}\]\|\;\:\,\<\.\>\/\?\ ]\' { copychar(yytext[1]); return NM_INT; }
\'\\[\\\'\"]\' { copychar(yytext[2]); return NM_INT; }

"=>"	{	printf("\n%s",yytext);return OPSET;}
"->"	{	printf("\n%s",yytext);return OPPOINTER;}
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
"::"	{	printf("\n%s",yytext);return BH_CP;}

".+"	{	printf("\n%s",yytext);return OPP;}
".++"	{	printf("\n%s",yytext);return OPPP;}
".--"	{	printf("\n%s",yytext);return OPMM;}
".-"	{	printf("\n%s",yytext);return OPM;}
".*"	{	printf("\n%s",yytext);return OPMU;}
"./"	{	printf("\n%s",yytext);return OPD;}
".%"	{	printf("\n%s",yytext);return OPMO;}
".="	{	printf("\n%s",yytext);return OPE;}
".=="	{	printf("\n%s",yytext);return OPEQ;}
".!="	{	printf("\n%s",yytext);return OPNE;}
".>="	{	printf("\n%s",yytext);return OPAE;}
".<="	{	printf("\n%s",yytext);return OPLE;}
".>"	{	printf("\n%s",yytext);return OPA;}
"..<"	{	printf("\n%s",yytext);return OPL;}

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
"!"	{	printf("\n%s",yytext);return yytext[0]; }
"|"	{	printf("\n%s",yytext);return yytext[0]; }
"&"	{	printf("\n%s",yytext);return yytext[0]; }
"?"	{	printf("\n%s",yytext);return yytext[0]; }
"\\"	{	printf("\n%s",yytext);return yytext[0]; }
"_"	{	printf("\n%s",yytext);return yytext[0]; }

{IDENT}	{ strcpy(yylval.s,yytext);
		printf("\n%s\t\t400\t\"%s\"",yytext,yytext); return IDENTIFIER;
	}

(.|\n)	;

%%

void copychar(char c)	{
	int id = (int)c;
	char tmp[10];
	sprintf(tmp,"%d", id);
	printf("\nchar %s",yytext); 
	strcpy(yylval.s,tmp);
}

int yywrap()
{
   if (YYSTATE == literal || YYSTATE==koment)
	printf("\nNiepoprawnie zamkniety plik\n");
	       
    return(1);
}

