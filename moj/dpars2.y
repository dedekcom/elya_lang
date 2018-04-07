%{
 #include <stdio.h>
 #include <string.h>
 #include "lex.yy.c"
 //#define YYDEBUG 1
 
 FILE *fin;
 #define ILELOCAL		100
 #define ILESTACK	100
 #define IDNAME		128
 int idlocal=0;		// licznik zmiennych lokalnych
 int ktorylocal=0;
 int looplocal=0;	// licznik zmiennych lokalnych petli
 int idstack=0;
 char sav[ILESTACK][IDNAME],	// do zapamietywania
 	local[ILELOCAL][IDNAME];	// tablica zmiennych lokalnych
 char sloc[20];		// obliczona nazwa zmiennej lokalnej
 char sclass[20];		// nazwa typu: class, module, game
 void dderror(char *s1, char *s2)	{ printf("error: %s%s",s1,s2); exit(1);	}
 void addlocal(char *s);
 void addrellocal(char *styp, char *s);
 void addlocarray( char *styp, char *snom, char *sile );
 char *getlocal(char *s);
 void ddpush(char *s)	{ strcpy(sav[idstack],s); idstack++; }
 char sbuild[256], spom[256];
 char sident[IDNAME], sidentr[IDNAME];
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
 char *localname(int pos);
 void stdnew();
 
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
 void cmpandor(char *s);
 void ifpart1();
 void ifpart2();
 void ifpart3();
 void startloop();
 
%}

%union {
    char s[512];
}

%start SPACE
%token KW_CLASS KW_MODULE KW_GAME KW_INT KW_DO KW_WHILE  KW_NEW KW_THIS
%token KW_STRING KW_REAL KW_IF KW_ELSE KW_RETURN  KW_FOR KW_PUBLIC KW_VIRTUAL
%token NM_STRING NM_INT NM_REAL IDENTIFIER IDENTTAB
%token  BH_E BH_NE BH_ANDAND BH_OROR BH_AE BH_PP BH_MM BH_LE BH_PE BH_MNE BH_MLE BH_DE BH_MDE

%left BH_ANDAND BH_OROR
%left BH_E BH_NE BH_AE BH_LE '<' '>'
%left '-' '+'
%left '*' '/'
%left '%'
%left NEG

%%

SPACE: SPACE SPACE1
	|	 SPACE1
;

SPACE1: GLOBALNEW
	|	CLASS
;

BEGINCLASS:	 KW_CLASS	{ ddput("\tclass "); strcpy(sclass,"class"); }
	|	KW_GAME		{ ddput("\tgame "); strcpy(sclass,"game");  }
	|	KW_MODULE		{ ddput("\tmodule "); strcpy(sclass,"module");  }
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

METHODNAME2:	IDENTIFIER	{  ddput3("\tmethod ",$<s>1,"\n"); 	idlocal=0; ktorylocal=0;}
;

METHODNAME:	METHODNAME2
	|	BASETYPE METHODNAME2		{ ddpop(); }	// wyrzucenie niepotrzebnego typu zwracanego
	|	KW_PUBLIC BASETYPE METHODNAME2		{ ddpop(); }	// wyrzucenie niepotrzebnego typu zwracanego
	|	KW_PUBLIC METHODNAME2
	|	KW_VIRTUAL BASETYPE METHODNAME2		{ ddpop(); }	// wyrzucenie niepotrzebnego typu zwracanego
	|	KW_VIRTUAL METHODNAME2
;

METHOD2:	METHODNAME  ARGUMENTS	{int i;	 for(i=ktorylocal;i>0; i--)	
									{ ddput3("\tpop ",localname(i-1),"\n"); }	}
;
METHOD:	METHOD2  METHODBODY	{ ddput("\tend method\n"); }
;

ARGUMENTS:	 '(' ARGUMENTS1 ')'
	|	'(' ')'
;

ARGUMENTS1: 	ARGUMENT
	|	ARGUMENT ',' ARGUMENTS1
;

ARGUMENT:	BASETYPE IDENTIFIER 	{ addrellocal( ddpop(), $<s>2);  }
	|	BASETYPE IDENTIFIER	'[' NM_INT ']' { addlocarray( ddpop(), $<s>2, $<s>4 ); }
;

METHODBODY:	'{'	METHODBODY1	'}'
	|	'{' '}'
;

/*BODY:	'{'	METHODBODY1	'}'
	|	METHODBODY2
	|	'{' '}'
	|	';'
;*/

METHODBODY1:	METHODBODY1 METHODBODY2
	|	METHODBODY2
;

METHODBODY2:	IFEXPR
	|	WHILEEXPR
	|	FOREXPR
	|	EQUATION	';'
	|	CALLMETHOD	';'	
	|	ORDNEW
	|	RETEXPR
	|	LOCALNEW	';'
	|	METHODBODY
;

RETEXPR:	KW_RETURN EXPR ';'	{ ddput("\tret\n");	 }		// wynik na stosie
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
WHILEEXPR:	 STARTWHILE IFBODY		{ poploop(); }		// zdjecie pierwszej etykiety
;

GLOBALNEW1:  KW_NEW BASETYPE IDENTIFIER 	{ ddput3("\tnew ",ddpop(),",");  ddput2($<s>3 , "\n"); ddpush($<s>3); }
;

GLOBALNEW2:  KW_NEW  IDENTIFIER IDENTIFIER	 { ddput3("\tnew ", $<s>2, ",");	ddput2($<s>3,"\n"); }
;

GLOBALNEW:	GLOBALNEW1 ';'	{	ddpop(); }
	|	GLOBALNEW1	ATTRIB	';' {	ddput3("\tpop ",ddpop(),"\n");	}
	|	GLOBALNEW2 ';'
;

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
IFEXPR:	STARTIF1 		{ ifpart3(); }
	|	STARTIF1 KW_ELSE METHODBODY2	{ ifpart3(); }
;

IFBODY1:	'(' EXPR ')'		{ ifpart1(); }
;

IFBODY:  IFBODY1 METHODBODY2	{ ifpart2(); }
;

/*COMPARISON:	COMPARISON1
 	|	COMPARISON BH_ANDAND COMPARISON		{	cmpandor("and"); }
 	|	COMPARISON BH_OROR COMPARISON		{	cmpandor("or"); }
 	|	'('	COMPARISON  ')'  
;

COMPARISON1:	EXPR BH_E EXPR		{ cmp("je"); }
	|	EXPR BH_NE EXPR			{ cmp("jne"); }
	|	EXPR BH_AE EXPR			{ cmp("jae"); }
	|	EXPR BH_LE EXPR			{ cmp("jle"); }
	|	EXPR '<' EXPR				{ cmp("jl"); }
	|	EXPR '>' EXPR				{ cmp("ja"); }
;*/
/* COMPARISON:	EXPR; */

STARTORDNEW:	KW_NEW		{ prepare(); build("\tnew "); pushbuild(); }
;
ORDNEW1:	STARTORDNEW ARGTONEW1 ARGTONEW2 { stdnew(); }  		// teraz dodaje typ,nazwa
;

ORDNEW:	ORDNEW1 ';'
	|		ORDNEW1 ATTRIB ';'	{ ddput3("\tpop ",sident,"\n"); }
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

BASETYPE:	KW_INT		{ ddpush("int"); }
	|	KW_REAL		{ ddpush("real"); }
	|	KW_STRING		{ ddpush("string"); }
;

REFERENCE:	'['	EXPR	']' 	{ ddput("\tpopax\n\tmov $a,[$a]\n\tpsax\n");}
;

EQUATION:	NAMEIDENT ATTRIB	{ ddput3("\tpop ",sident,"\n"); }
	|	ARGEXPR	ATTRIB		{ ddput("\tspop $b\n\tpopax\n\tmov [$b],$a\n"); }
	|	NAMEIDENT	BH_PP		{ ddput3("\tadd ",sident,",1\n");	ddput3("\tpop ",sident,"\n"); }
	|	NAMEIDENT	BH_MM		{ ddput3("\tsub ",sident,",1\n");	ddput3("\tpop ",sident,"\n"); }
	|	NAMEIDENT	BH_PE EXPR	{ qexpr("add", sident); }
	|	NAMEIDENT	BH_MNE EXPR	{ qexpr("sub", sident); }
	|	NAMEIDENT	BH_MLE EXPR	{ qexpr("mul", sident); }
	|	NAMEIDENT	BH_DE EXPR		{ ddput3("\tpopax\n\tdiv ",sident,",$a\n");	ddput3("\tmov ",sident,",$a\n");	}
	|	NAMEIDENT	BH_MDE EXPR	{ ddput3("\tpopax\n\tdiv ",sident,",$a\n");	ddput3("\tmov ",sident,",$d\n");	}
	|	ARGEXPR	BH_PP		{ ddput("\tspop $b\n\tadd [$b],1\n\tpop [$b]\n"); }
	|	ARGEXPR	BH_MM		{ ddput("\tspop $b\n\tsub [$b],1\n\tpop [$b]\n"); }
	|	ARGEXPR	BH_PE EXPR	{ sexpr("add"); }
	|	ARGEXPR	BH_MNE EXPR	{ sexpr("sub"); }
	|	ARGEXPR	BH_MLE EXPR	{ sexpr("mul"); }
	|	ARGEXPR	BH_DE EXPR		{ ddput("\tpopax\n\tspop $b\n\tdiv [$b],$a\n\tmov [$b],$a\n"); }	
	|	ARGEXPR	BH_MDE EXPR	{ ddput("\tpopax\n\tspop $b\n\tdiv [$b],$a\n\tmov [$b],$d\n"); }	
;

/*ANDOREXPR:	BH_ANDAND
	|	BH_OROR
;*/
/*ANDANDEXP:	BH_ANDAND
;
OROREXP:	BH_OROR
;*/
EXPR:	VALUE
	|	EXPR '+' EXPR  	{ expr("add"); }
	|	EXPR '-' EXPR	{ expr("sub"); }
	|	EXPR '*' EXPR	{ expr("mul"); }
	|	EXPR '/' EXPR	{ expr("div"); ddput("\tpsax\n");}
	|	EXPR '%' EXPR	{ expr("div"); ddput("\tpush $d\n"); }	// w dx reszta
	|	EXPR BH_ANDAND EXPR {	cmpandor("and");	}
	|	EXPR BH_OROR EXPR {	cmpandor("or");	}
	/*|	EXPR ANDANDEXP EXPR {	cmpandor("and");	}
	|	EXPR OROREXP EXPR {	cmpandor("or");	}*/
/* 	|	EXPR ANDOREXPR EXPR {	cmpandor("or");	}  */
	|	EXPR BH_E EXPR		{ cmp("je"); }
	|	EXPR BH_NE EXPR	{ cmp("jne"); }
	|	EXPR BH_AE EXPR	{ cmp("jae"); }
	|	EXPR BH_LE EXPR	{ cmp("jle"); }
	|	EXPR '<' EXPR		{ cmp("jl"); }
	|	EXPR '>' EXPR		{ cmp("ja"); }
	|	'-' EXPR	%prec NEG	{ ddput("\tpopax\n\tsub 0,$a\n"); }
	|	'!' EXPR	%prec NEG	{ neg(); }
	|	'(' EXPR ')'
;

EXPR2:	VALUE
	|	EXPR2 '+' EXPR2  	{ expr("add"); }
	|	EXPR2 '-' EXPR2	{ expr("sub"); }
	|	EXPR2 '*' EXPR2	{ expr("mul"); }
	|	EXPR2 '/' EXPR2	{ expr("div"); ddput("\tpsax\n");}
	|	EXPR2 '%' EXPR2	{ expr("div"); ddput("\tpush $d\n"); }	// w dx reszta
	|	'-' EXPR2	%prec NEG	{ ddput("\tpopax\n\tsub 0,$a\n"); }
	|	'(' EXPR2 ')'
;

NUMBER:	NM_INT	{	ddput3("\tpush ",$<s>1,"\n"); }
	|	NM_REAL	{	ddput3("\tpush ",$<s>1,"\n"); }
	|	NM_STRING	{	ddput3("\tpush ",$<s>1,"\n"); }
;

VALUE:	VARIABLE	// nazwa zmiennej znajduje sie na stosie 
	|	NUMBER		// liczba/string znajduje sie na stosie 
	|	CALLMETHOD		
;

CALLMETHOD:	CALLMETH	{ putbuild(); } // wypluj kod wywolania metody a wynik metody jest na stosie
;

CALLMETH:	CALLOBJECT
	|	CALLTHIS
	|	CALLPARENT
;

CALLOBJECTSTART:	IDENTIFIER	{ char *c=getlocal($<s>1); 
									if(c==NULL) build3("\tcall ", $<s>1, ","); 
									else build3("\tcall ",c, ",");  
								pushbuild(); }
	|	ARGEXPR				{ build("\tspop $a\n\tcall [$a],"); 
								pushbuild(); }		// referencja na stosie - najpierw oblicz argumenty
;
CALLOBJECT:	CALLOBJECTSTART '.' CALLTHIS1
;

CALLPARENTSTART:	IDENTIFIER	{ build3("\tclparent ", $<s>1, ","); pushbuild(); }
	|	ARGEXPR				{ build("\tspop $a\n\t clparent [$a],"); 
								pushbuild(); 	}	// referencja na stosie - najpierw oblicz argumenty
;
CALLPARENT:		CALLPARENTSTART ':' ':' CALLTHIS1
;

CALLTHISSTART: KW_THIS		{ build("\tcthis "); pushbuild(); }
;
CALLTHIS:	CALLTHISSTART '.' CALLTHIS1
;
METHODCALLED:	IDENTIFIER	{ popbuild(); build2($<s>1,"\n"); pushbuild(); }
	|	ARGEXPR			{ popbuild(); prebuild("\tspop $d\n"); build("[$d]\n"); 
							pushbuild();}	// zdjecie dzialania przed call i jako metoda [dx]
;
CALLTHIS1:	METHODCALLED ARGSMETH
;

ARGEXPR: '<' EXPR2 '>'	{	ddput("\tpopax\n\tspush $a\n"); }
;

ARGSMETH:	'(' ARGSMETH1 ')'
 	|	'(' ')' 
;

ARGSMETH1:	EXPR
	|	EXPR ',' ARGSMETH1
;

NAMEIDENT:	IDENTIFIER	{	char tmp[256]; strcpy(tmp,$<s>1); char *c=getlocal(tmp); 		// wyznaczenie nazwy zmiennej..
						if (c==NULL) strcpy(sident,tmp);
						else strcpy(sident,c); }
;

NAMEIDENTR:	IDENTIFIER	{	char tmp[256]; strcpy(tmp,$<s>1); char *c=getlocal(tmp); 		// wyznaczenie nazwy zmiennej..
						if (c==NULL) strcpy(sidentr,tmp);
						else strcpy(sidentr,c); }
;

VARIABLE:	NAMEIDENTR	{ ddput3("\tpush ",sidentr,"\n"); }
	|	REFERENCE		// w referencji umieszczenie obiektu na stosie..
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

void cmpandor(char *s)	{
	ddput3("\tpopax\n\tpop $b\n\t", s, " $a,$b\n");
}

void startloop()	{
	ddput2( pushloop(), ":\n" );
}

void ifpart1()	{
	char 	*c2 = pushloop();
	ddput3("\tpopax\n\tcmp $a,0\n\tje ",c2,"\n");
}

void ifpart2()	{
	char *c2 = poploop(), *c1 = lastloop();
	ddput3("\tjmp ",c1,"\n");
	ddput2( c2, ":\n");
}

void ifpart3()	{
	ddput2( poploop(), ":\n" );
}

void cmp(char *s)	{
	char *c1 = pushloop(), *c2 = pushloop();
	ddput3("\tpop $b\n\tpopax\n\tcmp $a,$b\n\t",s," ");
	ddput3( c1,"\n\tpush 0\n\tjmp ", c2);
	ddput3("\n",c1,":\n\tpush 1\n");
	ddput2(c2, ":\n");
	poploop();
	poploop();
}

void neg()	{
	char *c1 = pushloop(), *c2 = pushloop();
	ddput3("\tpopax\n\tcmp $a,0\n\tje ",c1,"\n\tpush 0\n\tjmp ");
	ddput3(c2,"\n",c1);
	ddput3(":\n\tpush 1\n",c2,":\n");
	poploop();
	poploop();
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
	strcpy(local[idlocal],s);
	idlocal++;	
}

void addrellocal(char *styp, char *s)	{
	ddput3("\tlocal",styp," ");  
	addlocal( s );
	ddput2( getlocal( s ) , "\n"); 
	ktorylocal++;
}

void addlocarray( char *styp, char *snom, char *sile )	{
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
	return localname(idlocal-1);
}

char *getlocal(char *s)	{
	int pos = -1;
	int i;
	for(i=0; i<idlocal; i++)	{
		if(strcmp(s,local[i])==0)	{
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

void ddend()	{
	fclose(fin);
}

void ddput(char *s)	{
	fputs(s,fin);
}

void ddput2(char *s1, char *s2)	{
	fputs(s1,fin);	fputs(s2,fin);
}

void ddput3(char *s1, char *s2, char *s3)	{
	fputs(s1,fin);	fputs(s2,fin);	fputs(s3,fin);
}

void stdnew()	{
	strcpy(sident,ddpop()); 		// drugi argument
	char styp[100];
	strcpy(styp, ddpop());	// typ 
	putbuild(); 	// buduje ewentualne popy oraz "new "
	ddput3(styp,",",sident); 
	ddput("\n");
}

int yyerror()
{
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
int main(int argc, char *argv[])
{
//	yydebug=1;
	FILE *fprj;
	int readobj=0;
	char srobj[128], z, srob[128];
	int iposob=0, i, koniec=0;
 	if(argc>1)	{
		if( (fprj=fopen(argv[1],"r"))==NULL)	{
			printf("\nnie otworzylem %s",argv[1]);
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
				printf("\nnie znalazlem ");
				ddstart(NULL);
			}
		}
	} else {
		printf("\nargc = 1 ");
    		ddstart(NULL);
	}
    yyparse();
    ddend();
    return 0;
}

