%{
 #include <stdio.h>
 #include <string.h>
 #include "lex.yy.c"
 #define YYDEBUG 1
 
 int iopen=0;
 FILE *fin;
 #define ILELOCAL		100
 #define ILESTACK	100
 int idlocal=0;		// licznik zmiennych lokalnych
 int looplocal=0;	// licznik zmiennych lokalnych petli
 int idstack=0;
 char sav[ILESTACK][50],	// do zapamietywania
 	local[ILELOCAL][50];	// tablica zmiennych lokalnych
 char sloc[20];		// obliczona nazwa zmiennej lokalnej
 char sclass[20];		// nazwa typu: class,, module, game
 void dderror(char *s1, char *s2)	{ printf("error: %s%s",s1,s2); exit(1);	}
 void addlocal(char *s);
 char *getlocal(char *s);
 void ddpush(char *s)	{ strcpy(sav[idstack],s); idstack++; }
 char sbuild[256], spom[256];
 void prepare()	{ strcpy(sbuild,""); }
 void prebuild(char *s)	{ strcpy(spom,sbuild);  strcpy(sbuild,s);  strcat(sbuild,spom); }
 void build(char *s)	{ strcat(sbuild,s); }
 void build2(char *s1, char *s2)	{ build(s1); build(s2); }
 void build3(char *s1, char *s2, char *s3) { build2(s1,s2); build(s3); }
 void pushbuild()	{ ddpush(sbuild); prepare(); };
 char *ddpop()	{ idstack--; if(idstack>=0) return sav[idstack]; else dderror("idstack<","0");  }
 void ddstart();
 void ddend();
 void ddput(char *s);
 void ddput2(char *s1, char *s2); 
 void ddput3(char *s1, char *s2, char *s3); 
 
%}

%union {
    char s[255];
}

%start SPACE
%token KW_CLASS KW_MODULE KW_GAME KW_INT KW_DO KW_WHILE  KW_NEW KW_THIS
%token KW_STRING KW_REAL KW_IF KW_ELSE KW_RETURN  KW_FOR
%token NM_STRING NM_INT NM_REAL IDENTIFIER IDENTTAB
%token  BH_E BH_NE BH_ANDAND BH_OROR BH_AE BH_PP BH_MM BH_LE 
%left '-' '+'
%left '*' '/'
%left BH_ANDAND BH_OROR

%%

SPACE: SPACE SPACE1
	|	 SPACE1
;

SPACE1: GLOBALNEW
	|	CLASS
;

BEGINCLASS:	 KW_CLASS	{ ddstart(); ddput("\tclass "); strcpy(sclass,"class"); }
	|	KW_GAME		{ ddstart(); ddput("\tgame "); strcpy(sclass,"game");  }
	|	KW_MODULE		{ ddstart(); ddput("\tmodule "); strcpy(sclass,"module");  }
;

CLASS:	BEGINCLASS CLASSES CLASSBODY 	{ ddput3("\tend ",sclass,"\n\n"); }
;

CLASSNAME:	IDENTIFIER	{ ddput2($<s>1, "\n"); }
;

CLASSES:	CLASSNAME
	|	CLASSNAME ':' INHERIT_LIST
;

PARENTNAME:	IDENTIFIER	{ ddput3("\tparent ", $<s>1,"\n"); }
;

INHERIT_LIST:  PARENTNAME ',' INHERIT_LIST
	|	PARENTNAME
;

CLASSBODY:	'{'	CLASSBODY1 '}'
	|	'{'	'}'
;

CLASSBODY1:	CLASSBODY1 METHOD
	|	METHOD
;

METHODNAME:	IDENTIFIER	{ ddput3("\tmethod ",$<s>1,"\n"); 	idlocal=0; }
;
METHOD:	METHODNAME  ARGUMENTS  METHODBODY	{ ddput("\tend method\n"); }
;

ARGUMENTS:	 '(' ARGUMENTS1 ')'
	|	'(' ')'
;

ARGUMENTS1: 	ARGUMENT
	|	ARGUMENT ',' ARGUMENTS1
;

ARGUMENT:	BASETYPE IDENTIFIER 	{ ddput3("\tlocal ",ddpop(),",");  addlocal($<s>2);  ddput2( getlocal($<s>2) , "\n"); }
;

METHODBODY:	'{'	METHODBODY1	'}'
	|	'{' '}'
;

METHODBODY1:	METHODBODY1 METHODBODY2
	|	METHODBODY2
;

METHODBODY2:	IFEXPR
	|	WHILEEXPR
	|	FOREXPR
	|	EQUATION	';'
	|	CALLMETH	';'
	|	ORDNEW
	|	LOCALNEW	';'
;

FOREXPR:	KW_FOR EQFOR1 CMPFOR EQFOR2 METHODBODY
;

EQFOR1:	'(' EQUATION ';'
	|	'(' ';'
	|	'(' LOCALNEW	';'
;

CMPFOR:	COMPARISON ';'
	|	';'
;

EQFOR2:		EQUATION ')'
	|	')'
;

STARTWHILE:	KW_WHILE
;
WHILEEXPR:	 STARTWHILE IFBODY
;

GLOBALNEW:  KW_NEW BASETYPE IDENTIFIER ';'	{ ddstart(); ddput3("\tnew ",sav[0],",");  ddput2($<s>3 , "\n"); }
	|	KW_NEW  IDENTIFIER IDENTIFIER	 ';'		{ ddstart(); ddput3("\tnew ", $<s>2, ",");	ddput2($<s>3,"\n"); }
;

LOCALNEW:	ARGUMENT
	|	ARGUMENT ATTRIB
;

ATTRIB:	'=' EXPR
;

STARTIF:	KW_IF
;
IFEXPR:	STARTIF IFBODY
	|	STARTIF IFBODY KW_ELSE METHODBODY
	|	STARTIF IFBODY KW_ELSE IFEXPR
;

IFBODY: 	'(' COMPARISON ')' METHODBODY
;

COMPARISON:	COMPARISON1
 	|	COMPARISON BH_ANDAND COMPARISON
  	|	COMPARISON BH_OROR COMPARISON
 	|	'('	COMPARISON  ')'  
;

COMPARISON1:	EXPR BH_E EXPR
	|	EXPR BH_NE EXPR
	|	EXPR BH_AE EXPR
	|	EXPR BH_LE EXPR
	|	EXPR '<' EXPR
	|	EXPR '>' EXPR
;

ORDNEW:	KW_NEW ARGTONEW ARGTONEW ';'
 	|	KW_NEW ARGTONEW IDENTTAB ';' 
;

ARGTONEW:	VARIABLE
	|	BASETYPE
;

BASETYPE:	KW_INT		{ ddpush("int"); }
	|	KW_REAL		{ ddpush("real"); }
	|	KW_STRING		{ ddpush("string"); }
;

REFERENCE:	'['	EXPR	']' 	{ ddput("\tpopax\n");  ddput("\tmov ax,[ax]\n"); ddput("\tpsax\n");}
;

EQUATION:	VARIABLE ATTRIB
;

EXPR:	VALUE
  	|	EXPR '+' EXPR  
	|	EXPR '-' EXPR
	|	EXPR '*' EXPR
	|	EXPR '/' EXPR
	|	'(' EXPR ')'
;

NUMBER:	NM_INT	{	ddput3("\tpush ",$<s>1,"\n"); }
	|	NM_REAL	{	ddput3("\tpush ",$<s>1,"\n"); }
	|	NM_STRING	{	ddput3("\tpush ",$<s>1,"\n"); }
;

VALUE:	VARIABLE	// nazwa zmiennej znajduje sie na stosie 
	|	NUMBER		// liczba/string znajduje sie na stosie
	|	CALLMETH	// wynik metody na stosie
;

CALLMETH:	CALLOBJECT
	|	CALLTHIS
	|	CALLPARENT
;

CALLOBJECTSTART:	IDENTIFIER	{ build3("\tcall ", $<s>1, ","); }
	|	REFERENCE				{ build("\tpopax\n\t call [ax],"); }		// referencja na stosie - najpierw oblicz argumenty
;
CALLOBJECT:	CALLOBJECTSTART '.' CALLTHIS1
;

CALLPARENTSTART:	IDENTIFIER	{ build3("\tclparent ", $<s>1, ","); }
	|	REFERENCE				{ build("\tpopax\n\t clparent [ax],"); }	// referencja na stosie - najpierw oblicz argumenty
;
CALLPARENT:		CALLPARENTSTART ':' ':' CALLTHIS1
;

CALLTHISSTART: KW_THIS		{ build("\tclthis "); }
;
CALLTHIS:	CALLTHISSTART '.' CALLTHIS1
;
METHODNAME:	IDENTIFIER	{ build2($<s>1,"\n"); pushbuild(); }
	|	REFERENCE			{ prebuild("\tpop dx\n"); build("[dx]\n"); }	// zdjecie referencji przed call i jako metoda [dx]
;
CALLTHIS1:	METHODNAME ARGSMETH
;

ARGSMETH:	'(' ARGSMETH1 ')'
 	|	'(' ')' 
;

ARGSMETH1:	EXPR
	|	EXPR ',' ARGSMETH1
;

VARIABLE:	IDENTIFIER
	|	REFERENCE
;

%%

void addlocal(char *s)	{
	strcpy(local[idlocal],s);
	idlocal++;	
}

char *getlocal(char *s)	{
	int pos = -1;
	int i;
	for(i=0; i<idlocal; i++)	{
		if(strcmp(local[i],s)==0)	{
			pos=i;
		}
	}
	if(pos==-1)	{
		dderror("no such local variable ",s);
	}
	strcpy(sloc,"$");
	char tmp[20];
	sprintf(tmp,"%d",pos+1);
	strcat(sloc,tmp);
	return sloc;
}

void ddstart()	{
	if(iopen==0)	{
		prepare();		// string build
		iopen=1;
		fin = fopen("ddag.odd","w");
		if(fin==NULL)	{
			printf("nieudane stworzenie pliku!");
			exit(1);
		}
	}
}

void ddend()	{
	fclose(fin);
}

void ddput(char *s)	{
	fputs(s,fin);
}

void ddput2(char *s1, char *s2)	{
	fputs(s1,fin);
	fputs(s2,fin);
}

void ddput3(char *s1, char *s2, char *s3)	{
	fputs(s1,fin);
	fputs(s2,fin);
	fputs(s3,fin);
}

int yyerror()
{
    printf( "Syntax Error\n");
    exit( 1 );
}


int main()
{
//	yydebug=1;
    yyparse();
    return 0;
}

