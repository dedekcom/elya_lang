%{
 #include <stdio.h>
 #include <string.h>
 #include <stdlib.h>
 #include "lex.yy.c"
  #define YYDEBUG 1
 
 FILE *fin;
 int idkod = -1;
 int ilambdas = -1;
 void preparevars();
 #define ILEKOD	100
 char *skod[ILEKOD];
 int ilekod[ILEKOD], ilimkod[ILEKOD], ikodprev[ILEKOD];
 char *beginkod();
 void endkod();
 void printkod();
 char sclassname[256], scallmethod[256];
 #define ILELOCAL	100
 #define ILESTACK	100
 #define IDNAME		128
 #define ILEATTR		100
 int ioptimized = 1;
 int idlocal[ILEKOD];		// licznik zmiennych lokalnych
 int ktorylocal[ILEKOD];
 void zerujlocals();
 int iloctab=0;
 int idstack=0;
 int ilecalls = 0;	// ilosc elementow do (x,y,z..) = ...
 void printlocals();
 char sav[ILESTACK][IDNAME],	// do zapamietywania
 	local[ILELOCAL][IDNAME][ILEKOD],	// tablica zmiennych lokalnych
 	sattr[ILEATTR][IDNAME];
 char sloc[20];		// obliczona nazwa zmiennej lokalnej
 char sclass[20];		// nazwa typu: class, module, game
 void dderror(char *s1, char *s2)	{ printf("error: %s%s",s1,s2); exit(1);	}
 void addlocal(char *s);
 void addrellocal(char *styp, char *s);
 void addlocarray( char *styp, char *snom, char *sile );
 char *getlocal(char *s);
 void ddpush(char *s)	{ strcpy(sav[idstack],s); idstack++; }
 char sbuild[2048], spom[2048];
 char sident[IDNAME][ILEKOD], sidentr[IDNAME][ILEKOD];
 void prepare()	{ strcpy(sbuild,""); }
 void prebuild(char *s)	{ strcpy(spom,sbuild);  strcpy(sbuild,s);  strcat(sbuild,spom); }
 void build(char *s)	{ strcat(sbuild,s); }
 void build2(char *s1, char *s2)	{ build(s1); build(s2); }
 void build3(char *s1, char *s2, char *s3) { build2(s1,s2); build(s3); }
 void pushbuild()	{ ddpush(sbuild); prepare(); }
 char *ddpop()	{ idstack--; if(idstack>=0) return sav[idstack]; else dderror("idstack<","0");  }
 void popbuild()	{ strcpy(sbuild,ddpop()); } 
 void ddstart(char *filename);
 void ddend();
 void ddput(char *s);
 void ddput2(char *s1, char *s2); 
 void ddput3(char *s1, char *s2, char *s3); 
 void putbuild()	{ ddput(ddpop()); } 
 void expr(char *s)	{ ddput3("\tpop $b\n\tpopax\n\t",s," $a,$b\n"); }
 void qexpr(char *sinstr, char *svar);		// quick expression
 void sexpr(char *sinstr);				// slow expression
 char *lastlocal();
 int ilastlocal=0;
 char *localname(int pos);
 void stdnew();
 void qifexp1();
 void qifexp2();
 void qifexp3();
 void argexpr();
 void calloper(char *c);
 
 void insertattr(char *c);
 void putattr();
 
 int loopc=0;		// licznik petli (do budowy)
 int lstack=-1;	// pobor petli 
 char *pushloop();
 char *poploop();
 char *lastloop();
 char *getloop(int id);
 #define ILELOOPS	10000
 char sloop[ILELOOPS][10];
 void cmp(char *s);
 void neg();
 void checkand();
 void checkor();
 void endandor();
 void ifpart1();
 void ifpart2();
 void ifpart3();
 void startloop();
 
 void matchbody();
 void endclass();
%}

%union {
    char s[1024];
}

%start SPACE
%token KW_CLASS KW_MODULE KW_GAME KW_INT KW_DEF KW_DO KW_WHILE  KW_NEW KW_THIS KW_DELETE
%token KW_STRING KW_REAL KW_IF KW_ELSE KW_RETURN  KW_FOR KW_PUBLIC KW_VIRTUAL KW_MATCH
%token NM_STRING NM_INT NM_REAL IDENTIFIER IDENTTAB KW_FUNC 
%token  BH_E BH_NE BH_ANDAND BH_OROR BH_AE BH_PP BH_MM BH_LE BH_PE BH_MNE BH_MLE BH_DE BH_MDE BH_CP
%token KW_OPERATOR OPP OPM OPMU OPD OPMO OPE OPEQ OPNE OPAE OPLE OPA OPL OPSET OPPOINTER
%token OPPP OPMM

/* %left '?' ':' */
%left BH_ANDAND BH_OROR
%left BH_E BH_NE BH_AE BH_LE '<' '>' OPEQ OPNE OPAE OPLE OPL OPA
%left '&' '|'
%left '-' '+' OPP OPM
%left '*' '/' OPMU OPD
%left '%' OPMO
%left NEG
%left OPPOINTER

%%

SPACE: SPACE SPACE1
	|	 SPACE1
;

SPACE1: 	CLASS
	|	KW_PUBLIC METHOD
	|	METHODBODY2
;

BEGINCLASS:	 KW_CLASS	{ ddput("\tclass "); strcpy(sclass,"class"); preparevars();}
	|	KW_GAME			{ ddput("\tgame "); strcpy(sclass,"game"); preparevars(); }
	|	KW_MODULE		{ ddput("\tmodule "); strcpy(sclass,"module"); preparevars(); }
;

CLASS:	BEGINCLASS CLASSES CLASSBODY 	{ endclass(); }
;

CLASSNAME:	IDENTIFIER	{ ddput2($<s>1, "\n"); strcpy(sclassname, $<s>1); }
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

METHODNAME2:	IDENTIFIER	{  ddput3("\tmethod ",$<s>1,"\n"); 	zerujlocals(); }
	|	IDENTIFIER '='	{  ddput3("\tmethod ",$<s>1,"=\n"); 	zerujlocals(); }
	|	KW_OPERATOR '+'	{  ddput("\tmethod operator+\n");		zerujlocals(); }
	|	KW_OPERATOR '-'		{  ddput("\tmethod operator-\n");		zerujlocals(); }
	|	KW_OPERATOR '*'	{  ddput("\tmethod operator*\n");		zerujlocals(); }
	|	KW_OPERATOR '/'		{  ddput("\tmethod operator/\n");		zerujlocals(); }
	|	KW_OPERATOR '%'	{  ddput("\tmethod operator%\n");		zerujlocals(); }
	|	KW_OPERATOR '='	{  ddput("\tmethod operator=\n");		zerujlocals(); }
	|	KW_OPERATOR BH_E	{  ddput("\tmethod operator==\n");		zerujlocals(); }
	|	KW_OPERATOR BH_NE	{  ddput("\tmethod operator!=\n");		zerujlocals(); }
	|	KW_OPERATOR '<'	{  ddput("\tmethod operator<\n");		zerujlocals(); }
	|	KW_OPERATOR '>'	{  ddput("\tmethod operator>\n");		zerujlocals(); }
	|	KW_OPERATOR BH_LE	{  ddput("\tmethod operator<=\n");		zerujlocals(); }
	|	KW_OPERATOR BH_AE	{  ddput("\tmethod operator>=\n");		zerujlocals(); }
	|	KW_OPERATOR BH_PP	{  ddput("\tmethod operator++\n");		zerujlocals(); }
	|	KW_OPERATOR BH_MM	{  ddput("\tmethod operator--\n");		zerujlocals(); }
;

METHODNAME:	METHODNAME2
	|	BASETYPE METHODNAME2		{ ddpop(); }	// wyrzucenie niepotrzebnego typu zwracanego
	|	KW_PUBLIC BASETYPE METHODNAME2		{ ddpop(); }	// wyrzucenie niepotrzebnego typu zwracanego
	|	KW_PUBLIC METHODNAME2
	|	KW_VIRTUAL BASETYPE METHODNAME2		{ ddpop(); }	// wyrzucenie niepotrzebnego typu zwracanego
	|	KW_VIRTUAL METHODNAME2
;

METHOD2:	METHODNAME  ARGUMENTS	{	printlocals();	}
;
METHOD:	METHOD2  METHODBODY	{ ddput("\tend method\n"); printkod(); }
;

ARGUMENTS:	 '(' ARGUMENTS1 ')'
	|	'(' ')'
;

ARGUMENTS1: 	ARGUMENT
	|	ARGUMENT ',' ARGUMENTS1
;

ARGUMENT:	BASETYPE IDENTIFIER 	{ iloctab=0; addrellocal( ddpop(), $<s>2);  }
	|	BASETYPE IDENTIFIER	'[' NM_INT ']' { addlocarray( ddpop(), $<s>2, $<s>4 ); }
;

METHODBODY:	'{'	METHODBODY1	'}'
	|	'{' '}'
	|	';'
;

METHODBODY1:	METHODBODY1 METHODBODY2
	|	METHODBODY2
;

METHODBODY2:	IFEXPR
	|	WHILEEXPR
	|	FOREXPR
	|	EQUATION	';'
	|	EXPR ';'
	|	ORDNEW
	|	ORDDELETE ';'
	|	RETEXPR
	|	LOCALNEW	';'
	|	METHODBODY
	|	MATCH
;

MATCHSTART:	KW_MATCH '(' EXPR ')' '{'	{	ddput("\tspushs\n"); pushloop(); /*petla fin*/	}
;

MATCHBODY3: EXPR OPSET	{		ddput3("\tcmpst\n\tjne ",pushloop(),"\n\tspop $a\n"); }
;
MATCHBODY2:	MATCHBODY3 MATCHEXPR2	{ ddput3("\tjmp ",getloop(-1),"\n"); ddput2(poploop(),":\n"); }
;
MATCHBODY:	MATCHBODY2 MATCHBODY
	|	MATCHBODY2
;
MATCHEXPR2:	METHODBODY2
;
MATCHEND2:	'?' OPSET		{	ddput("\tspop $a\n");	}
;
MATCHEND1:	MATCHEND2 MATCHEXPR2
;
MATCHEND:	MATCHEND1 '}'	{ ddput2(poploop(),":\n");	}
;

MATCH:	MATCHSTART MATCHBODY MATCHEND
;

RETEXPR:	KW_RETURN ARGSMETH1 ';'	{ ddput("\tret\n");	 }		// wynik(i) na stosie
	|	KW_RETURN ';'			{ ddput("\tret\n"); }
;

FOREXPR:	KW_FOR EQFOR1 CMPFOR EQFOR2 METHODBODY2	{ ddput3("\tjmp ", poploop(), "\n");
								ddput2( poploop(), ":\n"); poploop();	}
;

EQFOR1:		EQFOR1A	{ startloop(); }
;
EQFOR1A:	'(' EQUATION 
	|	'(' 
	|	'(' LOCALNEW	
;

CMPFOR:	CMPFOR1	{	ifpart1(); char *c3=pushloop(), *c4=pushloop(); 
							ddput3("\tjmp ", c4, "\n"); ddput2(c3,":\n"); }
;
CMPFOR1:	';' EXPR 		
	|	';'		{ ddput("\tpush 1\n");	}		// automatycznie warunek spelniony
;
EQFOR2:		';' EQFOR2A	{ ddput3("\tjmp ",getloop(-3),"\n");  ddput2( poploop(), ":\n"); }
;
EQFOR2A:		EQUATION ')'	
	|	')'
;

STARTWHILE:	KW_WHILE	{ startloop();	}
;
WHILEEXPR:	 STARTWHILE IFBODY		{ ifpart2(); poploop(); }		// zdjecie pierwszej etykiety
;

/*GLOBALNEW1:  KW_NEW BASETYPE IDENTIFIER 	{ ddput3("\tnew ",ddpop(),",");  ddput2($<s>3 , "\n"); ddpush($<s>3); }
;

GLOBALNEW2:  KW_NEW  IDENTIFIER IDENTIFIER	 { ddput3("\tnew ", $<s>2, ",");	ddput2($<s>3,"\n"); }
;

GLOBALNEW:	GLOBALNEW1 ';'	{	ddpop(); }
	|	GLOBALNEW1	ATTRIB	';' {	ddput3("\tpop ",ddpop(),"\n");	}
	|	GLOBALNEW2 ';'
;*/

LOCALNEW1:	ARGUMENT
	|	ARGUMENT ATTRIB	{ ddput3("\tpop ",lastlocal(),"\n"); }
;

LOCALNEW:  LOCALNEW1
	|	LOCALNEW1 ',' LOCALNEW
;

ATTRIB:	'=' EXPR
;

STARTIF:	KW_IF	{	pushloop();	}		// zdjecie etykiety w ifpart3()
;
STARTIF1:		STARTIF IFBODY
;
IFEXPR:	STARTIF1 		{ ifpart3(); poploop();  }
	|	STARTIF1 IFELS METHODBODY2	{ ifpart3(); }
;
IFELS:	KW_ELSE	{ ifpart2(); }
;
IFBODY1:	'(' EXPR ')'		{ ifpart1(); }
;

IFBODY:  IFBODY1 METHODBODY2	/*{ ifpart2(); }*/
;

STARTORDNEW:	KW_NEW		{ prepare(); build("\tnew "); pushbuild(); }
;

ORDNEW2:	STARTORDNEW ARGTONEW1 ARGTONEW2
;
ORDNEW1:	ORDNEW2 { stdnew(); }  		// teraz dodaje typ,nazwa
;

ORDNEW:	ORDNEW1 ';'
	|	ORDNEW2 ARGSMETH ';'	{ stdnew(); }
	|	ORDNEW1 ATTRIB ';'		{ ddput3("\tpop ",sident[idkod+1],"\n"); }
	|	ORDNEW1 OPE EXPR ';'		{ ddput3("\tcall ",sident[idkod+1],",operator=\n");}
	|	ORDNEW1 '{' { ddpush( beginkod() );	} METHODBODY1 '}' ';' { endkod(); ddput3("\tcall ",sident[idkod+1],","); 
			ddput2(ddpop(),"\n"); }
	|	ORDNEW2 ARGSMETH '{' { stdnew(); ddpush( beginkod() ); }  ARGUMENTS { printlocals(); } METHODBODY1 '}' ';'
		{ endkod(); ddput3("\tcall ",sident[idkod+1],",");	ddput2(ddpop(),"\n"); }
;

ORDDELETE:		KW_DELETE IDENTIFIER	{	ddput3("\tdelete ",$<s>2,"\n");	}
	|	KW_DELETE ARGEXPR			{	ddput("\tspop $d\n\tdelete [$d]\n");	}
;

ARGTONEW2:	ARGEXPR	{ 	char tmp[100]; strcpy(tmp,ddpop()); popbuild(); 
								prebuild("\tspop $e\n"); pushbuild();  ddpush(tmp);  // najpierw new, potem argument
								ddpush("[$e]");  }
	|	IDENTIFIER		{ ddpush($<s>1); }
;

ARGTONEW1:	ARGEXPR	{ popbuild(); prebuild("\tspop $d\n"); pushbuild(); ddpush("[$d]");  }
	|	IDENTIFIER		{ ddpush($<s>1); }
	|	BASETYPE
;

BASETYPE:	KW_INT		{ ddpush("int");	}
	|	KW_REAL		{ ddpush("real");	}
	|	KW_STRING		{ ddpush("string");	}
	|	KW_DEF			{ ddpush("def");	}
;

REFERENCE:	'['	EXPR	']' 	{ ddput("\tpopax\n\tmov $a,[$a]\n\tpsax\n");}
;

EQUATION:	NAMEIDENT ATTRIB	{ ddput3("\tpop ",sident[idkod+1],"\n"); }
	|	ARGEXPR	ATTRIB		{ ddput("\tspop $b\n\tpopax\n\tmov [$b],$a\n"); }
	|	NAMEIDENT	BH_PP		{ ddput3("\tadd ",sident[idkod+1],",1\n");	ddput3("\tpop ",sident[idkod+1],"\n"); }
	|	NAMEIDENT	BH_MM		{ ddput3("\tsub ",sident[idkod+1],",1\n");	ddput3("\tpop ",sident[idkod+1],"\n"); }
	|	NAMEIDENT	BH_PE EXPR	{ qexpr("add", sident[idkod+1]); }
	|	NAMEIDENT	BH_MNE EXPR	{ qexpr("sub", sident[idkod+1]); }
	|	NAMEIDENT	BH_MLE EXPR	{ qexpr("mul", sident[idkod+1]); }
	|	NAMEIDENT	BH_DE EXPR		{ ddput3("\tpopax\n\tdiv ",sident[idkod+1],",$a\n");	ddput3("\tmov ",sident[idkod+1],",$a\n");	}
	|	NAMEIDENT	BH_MDE EXPR	{ ddput3("\tpopax\n\tdiv ",sident[idkod+1],",$a\n");	ddput3("\tmov ",sident[idkod+1],",$d\n");	}
	|	ARGEXPR	BH_PP		{ ddput("\tspop $b\n\tadd [$b],1\n\tpop [$b]\n"); }
	|	ARGEXPR	BH_MM		{ ddput("\tspop $b\n\tsub [$b],1\n\tpop [$b]\n"); }
	|	ARGEXPR	BH_PE EXPR	{ sexpr("add"); }
	|	ARGEXPR	BH_MNE EXPR	{ sexpr("sub"); }
	|	ARGEXPR	BH_MLE EXPR	{ sexpr("mul"); }
	|	ARGEXPR	BH_DE EXPR		{ ddput("\tpopax\n\tspop $b\n\tdiv [$b],$a\n\tmov [$b],$a\n"); }
	|	ARGEXPR	BH_MDE EXPR	{ ddput("\tpopax\n\tspop $b\n\tdiv [$b],$a\n\tmov [$b],$d\n"); }
	|	'|' LARGS '|'	'=' ARGSMETH1	{ putattr(); }
	|	ARGEXPR OPE EXPR	{ddput("\tspop $a\n\tcall [$a],operator=\n");}
	|	NAMEIDENT OPE EXPR	{ddput3("\tcall ",sident[idkod+1],",operator=\n");}
	|	ARGEXPR OPPP	{	ddput("\tspop $a\n\tcall [$a],operator++\n");}
	|	NAMEIDENT OPPP	{ddput3("\tcall ",sident[idkod+1],",operator++\n");}
	|	ARGEXPR OPMM	{	ddput("\tspop $a\n\tcall [$a],operator--\n");}
	|	NAMEIDENT OPMM	{ddput3("\tcall ",sident[idkod+1],",operator--\n");}
	|	'_' '=' EXPR	{	ddput("\tpopax\n");	}
	|	KW_THIS OPE EXPR { ddput("\tcthis operator=\n");	}
	|	KW_THIS OPPP { ddput("\tcthis operator++\n");	}
	|	KW_THIS OPMM { ddput("\tcthis operator--\n");	}
;

OREXP:		EXPRANDOR2  BH_OROR	{	checkor();		}
;
ANDEXP:	EXPRANDOR2  BH_ANDAND	{	checkand();	}
;
STARTOREXP:	EXPRANDOR2  BH_OROR	{	pushloop();pushloop();	checkor();		}
;
STARTANDEXP:	EXPRANDOR2  BH_ANDAND	{	pushloop();pushloop();	checkand();	}
;
EXPRANDOR2:	'!' '(' EXPRANDOR ')'	{	neg();	}
	|	'(' EXPRANDOR ')'
	|	EXPR1
;
QIFEXP1:	'?'	{	qifexp1();	}
;
QIFEXP2:	':'	{	qifexp2();	}
;
QIFEXPR:	EXPRANDOR3 QIFEXP1 EXPR QIFEXP2 EXPR	{	qifexp3();	} 
/* 	|	'(' QIFEXPR ')' */
;
EXPRANDOR3:		EXPRANDOR
	|	EXPRANDOR2
;
EXPR:	EXPRANDOR3
	|	QIFEXPR
;
EXPRANDOR:	STARTOREXP EXPRTOANDOR	{	endandor();	}
	|	STARTANDEXP EXPRTOANDOR	{	endandor();	}
;
EXPRTOANDOR:	EXPRANDOR2 
	|	EXPR3
;
EXPR3:	ANDEXP EXPRTOANDOR
	|	OREXP EXPRTOANDOR
;

EXPR1:	VALUE
	|	EXPR1 '+' EXPR1  	{ expr("add"); }
	|	EXPR1 '-' EXPR1	{ expr("sub"); }
	|	EXPR1 '*' EXPR1	{ expr("mul"); }
	|	EXPR1 '/' EXPR1	{ expr("div"); ddput("\tpsax\n");}
	|	EXPR1 '%' EXPR1	{ expr("div"); ddput("\tpush $d\n"); }	// w dx reszta
	|	EXPR1 '&' EXPR1	{ expr("and");	}
	|	EXPR1 '|' EXPR1	{ expr("or");	}
	|	EXPR1 BH_E EXPR1		{ cmp("je"); }
	|	EXPR1 BH_NE EXPR1	{ cmp("jne"); }
	|	EXPR1 BH_AE EXPR1	{ cmp("jae"); }
	|	EXPR1 BH_LE EXPR1	{ cmp("jle"); }
	|	EXPR1 '<' EXPR1		{ cmp("jl"); }
	|	EXPR1 '>' EXPR1		{ cmp("ja"); }
	|	'-' EXPR1	%prec NEG	{ ddput("\tpopax\n\tsub 0,$a\n"); }
	|	'!' EXPR1	%prec NEG	{ neg(); }
	|	'(' EXPR1 ')'
	|	'(' QIFEXPR ')'
	|	EXPR1 OPP EXPR1	{calloper("+");}
	|	EXPR1 OPM EXPR1	{calloper("-");}
	|	EXPR1 OPMU EXPR1	{calloper("*");}
	|	EXPR1 OPD EXPR1	{calloper("/");}
	|	EXPR1 OPMO EXPR1	{calloper("%");}
	|	EXPR1 OPEQ EXPR1	{calloper("==");}
	|	EXPR1 OPNE EXPR1	{calloper("!=");}
	|	EXPR1 OPAE EXPR1	{calloper(">=");}
	|	EXPR1 OPLE EXPR1	{calloper("<=");}
	|	EXPR1 OPA EXPR1	{calloper(">");}
	|	EXPR1 OPL EXPR1	{calloper("<");}
	|	STARTCALLEXPR IDENTIFIER ARGSMETH	{	ddput3("\tspop $a\n\tcall $a,",$<s>2,"\n");	}
	|	STARTCALLEXPR IDENTIFIER {	ddput3("\tspop $a\n\tcall $a,",$<s>2,"\n");	}
;

STARTCALLEXPR:	EXPR1 OPPOINTER	{	ddput("\tspushs\n");	}
;
STARTCALLEXPR2:	EXPR2 OPPOINTER	{	ddput("\tspushs\n");	}
;

EXPR2:	VALUE
	|	EXPR2 '+' EXPR2  	{ expr("add"); }
	|	EXPR2 '-' EXPR2	{ expr("sub"); }
	|	EXPR2 '*' EXPR2	{ expr("mul"); }
	|	EXPR2 '/' EXPR2	{ expr("div"); ddput("\tpsax\n");}
	|	EXPR2 '%' EXPR2	{ expr("div"); ddput("\tpush $d\n"); }	// w dx reszta
	|	EXPR2 '&' EXPR2	{ expr("and");	}
	|	EXPR2 '|' EXPR2	{ expr("or");	}
	|	'-' EXPR2	%prec NEG	{ ddput("\tpopax\n\tsub 0,$a\n"); }
	|	'(' EXPR2 ')'
	|	STARTCALLEXPR2 IDENTIFIER ARGSMETH	{	ddput3("\tspop $a\n\tcall $a,",$<s>2,"\n");	}
	|	STARTCALLEXPR2 IDENTIFIER	{	ddput3("\tspop $a\n\tcall $a,",$<s>2,"\n");	}
;

NUMBER:	NM_INT	{	ddput3("\tpush ",$<s>1,"\n"); }
	|	NM_REAL	{	ddput3("\tpush ",$<s>1,"\n"); }
	|	NM_STRING	{	ddput3("\tpush ",$<s>1,"\n"); }
;

VALUE:	VARIABLE	// nazwa zmiennej znajduje sie na stosie 
	|	NUMBER		// liczba/string znajduje sie na stosie 
	|	CALLMETHOD
	|	'_'		// sciagaj ze stosu
;

CALLMETHOD:	CALLMETH	{ putbuild(); } // wypluj kod wywolania metody a wynik metody jest na stosie
;

CALLMETH:	CALLOBJECT
	|	CALLTHIS
	|	CALLPARENT
;

CALLAMBDASTART:	'{'	{	popbuild(); build2(beginkod(),"\n"); pushbuild(); }
;
CALLAMBDASTART2:	CALLAMBDASTART ARGUMENTS	{	printlocals();	}
;
CALLAMBDASTART3:	'{'	{	popbuild(); build2(beginkod(),"\"\n"); pushbuild(); }
;
CALLAMBDASTART4:	CALLAMBDASTART3 ARGUMENTS	{	printlocals();	}
;
CALLOBJECTSTART:	IDENTIFIER	{ char *c=getlocal($<s>1); 
									if(c==NULL) build3("\tcall ", $<s>1, ","); 
									else build3("\tcall ",c, ",");  
								pushbuild(); }
	|	ARGEXPR				{ build("\tspop $a\n\tcall [$a],"); 
								pushbuild(); }		// referencja na stosie - najpierw oblicz argumenty
;
CALLFUNCSTART:	KW_FUNC	{	build("\tpush \"");	pushbuild();	}
;
CALLOBJECT:	CALLOBJECTSTART '.' CALLTHIS1
	|	CALLOBJECTSTART CALLAMBDASTART METHODBODY1 '}'		{	endkod();	}
	|	CALLOBJECTSTART ARGSMETH CALLAMBDASTART2 METHODBODY1 '}'	{	endkod();	 }
	|	CALLFUNCSTART  CALLAMBDASTART3 METHODBODY1 '}'	{	endkod();	}
	|	CALLFUNCSTART  CALLAMBDASTART4 METHODBODY1 '}'	{	endkod();	}
;

CALLPARENTSTART:	IDENTIFIER	{ build3("\tclparent ", $<s>1, ","); pushbuild(); }
	|	ARGEXPR				{ build("\tspop $a\n\t clparent [$a],"); 
								pushbuild(); 	}	// referencja na stosie - najpierw oblicz argumenty
;
CALLPARENT:		CALLPARENTSTART BH_CP CALLTHIS1
;

CALLTHISSTART: KW_THIS		{ build("\tcthis "); pushbuild(); }
;
CALLTHIS:	CALLTHISSTART '.' CALLTHIS1
	|	'.' { build("\tcthis "); pushbuild(); } CALLTHIS1
;
METHODCALLED:	IDENTIFIER	{ popbuild(); build2($<s>1,"\n"); pushbuild(); }
	|	IDENTIFIER '='	{ popbuild(); build2($<s>1,"=\n"); pushbuild(); }
	|	ARGEXPR			{ popbuild(); prebuild("\tspop $d\n"); build("[$d]\n"); 
							pushbuild();}	// zdjecie dzialania przed call i jako metoda [dx]
	|	ARGEXPR '='			{ popbuild(); prebuild("\tspop $d\n\tadd $d,\"=\"\n"); build("[$d]\n"); 
							pushbuild();}	// zdjecie dzialania przed call i jako metoda [dx]
;
CALLTHIS1:	METHODCALLED ARGSMETH
	|	METHODCALLED
;

ARGEXPR: '<' EXPR2 '>'	{	argexpr();	 }
	|	'\\' EXPR '\\'	{	argexpr();	}
;

LARG:	REFERENCE		{	insertattr(NULL);	}
	|	NAMEIDENT		{	insertattr(sident[idkod+1]);	}
	|	ORDNEW1		{	insertattr(sident[idkod+1]);	}
	|	ARGUMENT		{	int i; for( i=iloctab;i>0;i--) insertattr( localname(ktorylocal[idkod+1]-i) );	}
	|	'_'	{	insertattr("_");	}
;
LARGS:	LARG ',' LARGS
	|	LARG
;

ARGSMETH:	'(' ARGSMETH1 ')'
 	|	'(' ')' 
;

ARGSMETH1:	EXPR
	|	EXPR ',' ARGSMETH1
;

NAMEIDENT:	IDENTIFIER	{	char tmp[256]; strcpy(tmp,$<s>1); char *c=getlocal(tmp); 		// wyznaczenie nazwy zmiennej..
						if (c==NULL) strcpy(sident[idkod+1],tmp);
						else strcpy(sident[idkod+1],c); }
;

NAMEIDENTR:	IDENTIFIER	{	char tmp[256]; strcpy(tmp,$<s>1); char *c=getlocal(tmp); 		// wyznaczenie nazwy zmiennej..
						if (c==NULL) strcpy(sidentr[idkod+1],tmp);
						else strcpy(sidentr[idkod+1],c); }
;

VARIABLE:	NAMEIDENTR	{ ddput3("\tpush ",sidentr[idkod+1],"\n"); }
	|	REFERENCE		// w referencji umieszczenie obiektu na stosie..
	|	KW_THIS	{	ddput("\tcthis getname\n");	} 
;

%%

void sexpr(char *s)	{
	ddput3("\tpopax\n\tspop $b\n\t",s," [$b],$a\n\tpop [$b]\n");
}

void qexpr(char *sinstr, char *svar)	{
	ddput3("\tpopax\n\t",sinstr," ");
	ddput3( svar, ",$a\n\tpop ",svar);
	ddput("\n");
}

void checkand()	{
	if( ioptimized==0 )	{
		ddput3("\tpopax\n\tcmp $a,0\n\tje ",getloop(-1),"\n");
	} else {
		ddput3("\tcmp0\n\tje ",getloop(-1),"\n");
	}
}

void checkor()	{
	if( ioptimized==0 )	{
		ddput3("\tpopax\n\tcmp $a,0\n\tjne ",lastloop(),"\n");
	} else {
		ddput3("\tcmp0\n\tjne ",lastloop(),"\n");
	}
}

void endandor()	{
	char *c1=getloop(-1);
	char *c2=lastloop();
	char *c3=pushloop();
	ddput3("\tjmp ",c3,"\n");		// jmp next
	ddput3(c1,":\n\tpush 0\n\tjmp ",c3);	// endand: push 0 jmp next
	ddput3("\n",c2,":\n\tpush 1\n");	// endor: push1
	ddput2(c3,":\n");
	poploop();		// out next:
	poploop();		// out endor:
	poploop();		// out endand
}

void startloop()	{
	ddput2( pushloop(), ":\n" );
}

void ifpart1()	{
	char *c2 = pushloop();
	if( ioptimized==0 )	{
		ddput3("\tpopax\n\tcmp $a,0\n\tje ",c2,"\n");
	} else {
		ddput3("\tcmp0\n\tje ",c2,"\n");
	}
}

void ifpart2()	{
	char *c2 = poploop();
	char *c1 = lastloop();
	ddput3("\tjmp ",c1,"\n");
	ddput2( c2, ":\n");
}

void ifpart3()	{
	ddput2( poploop(), ":\n" );
}

void cmp(char *s)	{
	if( ioptimized==0 )	{
		char *c1 = pushloop(), *c2 = pushloop();
		ddput3("\tpop $b\n\tpopax\n\tcmp $a,$b\n\t",s," ");
		ddput3( c1,"\n\tpush 0\n\tjmp ", c2);
		ddput3("\n",c1,":\n\tpush 1\n");
		ddput2(c2, ":\n");
		poploop();
		poploop();
	} else {
		ddput3("\tcmp",s,"\n");
	}
}

void neg()	{
	if( ioptimized==0 )	{
		char *c1 = pushloop(), *c2 = pushloop();
		ddput3("\tpopax\n\tcmp $a,0\n\tje ",c1,"\n\tpush 0\n\tjmp ");
		ddput3(c2,"\n",c1);
		ddput3(":\n\tpush 1\n",c2,":\n");
		poploop();
		poploop();
	} else {
		ddput("\tneg\n");
	}
}

void preparevars()	{
	ilambdas=-1;
	int i;
	if( idkod!=-1 )	{
		printf("\n idkod!=-1! %d\n", idkod );
		exit(1);
	}
	for( i=0; i<ILEKOD;i++)	{
		if( skod[i] != NULL )	{
			printf("\nskod!=NULL");
			free(skod[i]);
			skod[i]=NULL;
		}
		idlocal[i] = 0;
		ktorylocal[i]=0;
		ikodprev[i] = 0;
		ilimkod[i] = 0;
		ilekod[i] = 0;
	}
	strcpy( sclassname, "global" );
}

void printlocals()	{
	int i;
	for(i=ktorylocal[idkod+1];i>0; i--)	{
		ddput3("\tpop ",localname(i-1),"\n");
	}
}

char *pushloop()	{
	lstack++;
	loopc++;	
	char tmp[10], *c;
	c = sloop[lstack];
	strcpy(c,"l");
	sprintf(tmp,"%d",loopc);
	strcat(c,tmp);
	return lastloop();
}

char *poploop()	{
	if(lstack<0)	{
		dderror("stack pointer ","<0");
	}
	lstack--;
	return sloop[lstack+1];
}

char *getloop(int id)	{
	if(id>0)	{
		dderror("getloop id ",">0");
	}
	if(lstack+id<0)	{
		dderror("loop stack pointer ","<0");
	}
	return sloop[lstack+id];
}

char *lastloop()	{
	if(lstack<0)	{
		dderror("loop stack pointer ","<0");
	}
	return sloop[lstack];
}

char *localname(int pos)	{
	strcpy(sloc,"$");
	char tmp[20];
	sprintf(tmp,"%d",pos+1);
	strcat(sloc,tmp);
	return sloc;
}

void addlocal(char *s)	{
	int ile = idlocal[idkod+1], i, found=-1;
	for( i=0; i<ile; i++)	{
		if( strcmp(local[i][idkod+1], s)==0 )
			found=i;
	}
	if( found>=0 )	{
		ilastlocal=found;
	} else {
		strcpy(local[ile][idkod+1],s);
		ilastlocal = ile;
		idlocal[idkod+1]++;
	}
}

void addrellocal(char *styp, char *s)	{
	ddput3("\tlocal",styp," ");  
	addlocal( s );
	ddput2( getlocal( s ) , "\n"); 
	ktorylocal[idkod+1]++;
	iloctab++;
}

void addlocarray( char *styp, char *snom, char *sile )	{
	iloctab = 0;
	int ile = atoi( sile );
	if(ile<=0)	{
		dderror("array size ","< 0");
	}
	int i;
	char s1[20], s2[64];
	for(i =0; i<ile; i++)	{
		strcpy( s2, snom );
		sprintf(s1,"%d",i);
		strcat(s2,s1);
		addrellocal( styp, s2 );
	}
}

char *lastlocal()	{
	//return localname(idlocal[idkod+1]-1);
	return localname( ilastlocal );
}

char *getlocal(char *s)	{
	int pos = -1;
	int i;
	for(i=0; i<idlocal[idkod+1]; i++)	{
		if(strcmp(s,local[i][idkod+1])==0)	{
			pos=i;
		}
	}
	if(pos==-1)	{
		return NULL;
	} else {
		return localname(pos);
	}
}

void ddstart(char *filename)	{
	prepare();		// string build
	if(filename==NULL)	{
		fin = fopen("ddag.odd","w");
	} else fin = fopen(filename,"w");
	if(fin==NULL)	{
		printf("nieudane stworzenie pliku!");
		exit(1);
	}
	ddput("; Dominik Dagiel   ix 2005\n\n");
}

void ddend()	{	fclose(fin);}
void ddput2(char *s1, char *s2)	{	ddput(s1);	ddput(s2);}
void ddput3(char *s1, char *s2, char *s3)	{	ddput(s1);	ddput(s2);	ddput(s3);}
void ddput(char *s)	{
	if( idkod>=0 )	{
		int id = 0;
		if( skod[idkod]==NULL )	{
			skod[idkod] = (char*)malloc( ilimkod[idkod]*sizeof(char));
		}
		while(s[id]!='\0')	{
			if( ilekod[idkod] >= ilimkod[idkod]-1 )	{
				ilimkod[idkod] *= 2;
				char *c = (char*)malloc( ilimkod[idkod]*sizeof(char));
				skod[idkod][ ilekod[idkod] ] = '\0';
				strcpy( c, skod[idkod] );
				free( skod[idkod] );
				skod[idkod] = c;
			}
			skod[idkod][ ilekod[idkod] ] = s[id];
			ilekod[idkod]++;
			id++;
		}
	} else {
		fputs(s,fin);
	}
}
char *beginkod()	{
	char snr[16];
	ilambdas++;
	sprintf(snr, "%d", ilambdas);
	
	ikodprev[ilambdas] = idkod;
	idkod = ilambdas;
	
	skod[idkod] = NULL;
	ilimkod[idkod] = 1024;
	ilekod[idkod] = 0;
	idlocal[idkod+1] = 0;
	ktorylocal[idkod+1]=0;
	
	strcpy(scallmethod, sclassname);
	strcat(scallmethod, snr );
	return scallmethod;
}
void endkod()	{
	idkod = ikodprev[idkod];
}
void printkod()	{
	int i;
	char snr[16], s[256];
	if( idkod!=-1 )	{
		printf("\n idkod!=-1! %d\n", idkod );
		exit(1);
	}
	for(i=0; i<=ilambdas; i++)	{
		if( skod[i]!=NULL )	{
			strcpy(s, sclassname );
			sprintf(snr, "%d", i);
			strcat(s, snr );
			ddput3("\tmethod ", s, "\n");
			printf("\n ilekod, ilambdas : %d, %d\n",ilekod[i], ilambdas ); 
			skod[i][ ilekod[i] ] = '\0';
			ddput( skod[i] );
			free( skod[i] );
			skod[i] = NULL;
			ilekod[i] = 0;
			ddput("\tend method\n");
		}
	}
}

void zerujlocals()	{
	idlocal[idkod+1]=0;
	ktorylocal[idkod+1]=0;
}

void stdnew()	{
	strcpy(sident[idkod+1],ddpop()); 		// drugi argument
	char styp[100];
	strcpy(styp, ddpop());	// typ 
	putbuild(); 	// buduje ewentualne popy oraz "new "
	ddput3(styp,",",sident[idkod+1]); 
	ddput("\n");
}

void qifexp1()	{
	char *c1 = pushloop();
	char *c2 = pushloop();
	ddput3("\tcmp0\n\tje ",c2,"\n");
}
void qifexp2()	{
	char *c2 = poploop();
	char *c1 = lastloop();
	ddput3("\tjmp ",c1,"\n");
	ddput2(c2,":\n");
}
void qifexp3()	{	ddput2(poploop(),":\n");}

void argexpr()	{
	if(ioptimized==0) {
		ddput("\tpopax\n\tspush $a\n");
	} else {
		ddput("\tspushs\n");
	}
}

int yyerror()	{
    printf( "Syntax Error\n");
    exit( 1 );
}

int clears(char *s)	{
	int i, j=0;
	char z;
	for(i=0; s[i]!='\0'; i++)	{
		z = s[i];
		if( (z>='a'&&z<='z')||(z>='A'&&z<='Z')||(z>='0'&&z<='9')||
			z=='/' || z=='.' || z=='_' || z==':')	{
			s[j]=z;
			j++;
		}
	}
	s[j]='\0';
	return j;
}

void putattr()	{
	while(ilecalls>0) {
		if( sattr[ilecalls-1][0]=='\0' )	{
			ddput("\tspop $b\n\tpopax\n\tmov [$b],$a\n");
		} else if( strcmp(sattr[ilecalls-1],"_")==0 ) {
			ddput("\tpopax\n");
		} else {
			ddput3("\tpop ",sattr[ilecalls-1],"\n");
		}
		ilecalls--;
	}
}

void matchbody()	{
	ddput3("\tcmpst\n\tjne ",pushloop(),"\n");
}

void insertattr(char *c)	{
	if( c==NULL )	{
		ddput("\tspushs\n");
		sattr[ilecalls][0]='\0';
	} else {
		strcpy( sattr[ilecalls], c );
	}
	ilecalls++;
}

void calloper(char *c)	{
	ddput3("\tpopax\n\tpop $b\n\tpsax\n\tcall [$b],operator",c,"\n");
}

void endclass()	{
	ddput3("\tend ",sclass,"\n\n");
	if( idkod>-1 )	{
		printf("\nerror! idkod>0! %d\n", idkod);
		exit(1); 
	}
}

int main(int argc, char *argv[])
{
	//yydebug=0;
	FILE *fprj;
	int readobj=0;
	char srobj[128], z, srob[128];
	int iposob=0, i, koniec=0, idarg=1;
	
	strcpy(sclassname, "global");
	for( i=0; i<ILEKOD;i++)	{
		skod[i]=NULL;
		ktorylocal[i]=0;
		idlocal[i]=0;
		ikodprev[i] = 0;
	}
	
	ioptimized = 1;		// std poziom optymalizacji
	
	while(idarg<argc)	{
		if( strcmp( argv[idarg], "-O" )==0 )	{
			if( idarg+1<argc )	{
				ioptimized = atoi( argv[idarg+1] );
				idarg+=2;
			} else {
				printf("\nnot added argument to \"-O\"");
				return 1;
			}
		} else {
			if( (fprj=fopen(argv[idarg],"r"))==NULL)	{
				printf("\nunable to open %s",argv[1]);
				ddstart(NULL);
			} else {
				while( fgets(srobj,128,fprj)!=NULL && !koniec)	{
					if(clears(srobj))	{
						if(!strcmp(srobj,"out:"))	{
							readobj=1;
						} else if(readobj)	{
							printf("\nsrobj = %s", srobj);
							strcpy(srob,srobj);
							koniec = 1;
							readobj=0;
						}
					}
				}
				fclose(fprj);
				if(koniec)	{
					ddstart(srob);
				} else {
					printf("\nout not precisied");
					ddstart(NULL);
				}
			}
			idarg++;
		}
	}
	if( !koniec )	{
		printf("\nnot given output ");
		ddstart(NULL);
	}
    yyparse();
    ddend();
    return 0;
}

