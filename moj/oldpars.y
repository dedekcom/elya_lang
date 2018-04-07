%{
 #include <stdio.h>
 #include <string.h>
 #include "lex.yy.c"
 //#define YYDEBUG 1
 
 enum VARTYPE { VT_INT, VT_FLOAT, VT_FUNC, VT_PTL, VT_TAB };
 char vars[5][255][20],loopstack[100][20];
 char linijka[20],variable[20];
 int id[5],vartype,varint,idloop=0,stackloop=0,compare_number=0;
 float varfloat;
 FILE *dane=NULL, *kod=NULL;

 char *NextLoop()	{
	sprintf(linijka,"_loop%d",idloop);
	idloop++;	
	return linijka;
 }
 void PushLoop(char *l)	{
	strcpy(loopstack[stackloop],l);
	stackloop++;
 }
 char *ReadLoop()	{
	return loopstack[stackloop-1];
 }
 char *PopLoop()	{
	stackloop--;
	return loopstack[stackloop];
 }
 
 void CreateIf()	{
	PushLoop(NextLoop());
	PushLoop(NextLoop());
	fprintf(kod,"\t\t;create if\n");
 }
 
 void CreateDoWhile()	{
	PushLoop(NextLoop());
	fprintf(kod,"%s:\t\t;create do while\n",ReadLoop());
	PushLoop(NextLoop());
 }
 
 void Init()	{
	if (dane==NULL)	{
		dane = fopen("dane.asm","w");
		kod = fopen("kod.asm","w");
		fprintf(dane,"\n\tsegment .data\n\n");
		int i=0;
		for (i=0;i<5; i++)
			id[i]=0;
	}
 }
 void Main()	{
 	Init();
	fprintf(kod,"\n\n\n\tsegment .text\n\n\tglobal _start\n\n_start:\n");
 }

 void SetLinia(char *s)	{
	strcpy(linijka, s);
 }
 void SetVar(char *s)	{
	strcpy(variable,s);
 }
 void EndProg()	{
	fprintf(kod, "\n\n\tmov eax, 1              ; sys_exit\n\
\tmov ebx, 0              ; kod wyjscia\n\
\tint 0x80                ; wywolanie\n");
	fclose(dane);
	fclose(kod);
 }

 void FindVar(char *name)	{
	int pom = GetVar(name,VT_INT);
	if (pom!=-1)	{
		sprintf(linijka,"int%d",pom);
		fprintf(kod,"\tmov eax,%s\n\tpush eax\n",linijka);
	} else {
		pom=GetVar(name,VT_FLOAT);
		if (pom==-1)	{
			printf("\nniezadeklarowana zmienna\n");
			exit(1);
		} else {
			sprintf(linijka,"fl%d",pom);
			fprintf(kod,"\tmov eax,%s\n\tpush eax\n",linijka);
		}
	}
 }

 
 int GetVar(char *name,int k)	{
	int i;
	for (i=0;i<id[k]; i++)
		if (strcmp(vars[k][i],name)==0)
			return i;
	return -1;	// nie zadeklarowano zmiennej
 }
 
 char *PopVar(int k)	{
	char *pom= vars[k][id[k]];
	id[k]--;
	return pom;
 }
 
 void DelVar(char *name, int k)	{
 	int pom;
	if ((pom=GetVar(name,k))==-1)	{
		printf("\nnie bylo zadeklarowanego takiego id\n");
		exit(1);
	} else {
	
	}
 }
 
 void AddVar(char *name, int k)	{
 	Init();
 	if (GetVar(name,k)==-1)	{
		strcpy(vars[k][id[k]],name);	
		if (k==VT_INT)
			fprintf(dane,"\n\tdd\tint%d\t?",id[k]);
		if (k==VT_FLOAT)
			fprintf(dane,"\n\tdd\tfl%d\t?",id[k]);
		if (k==VT_TAB)
			fprintf(dane,"\n\tdd\ttab%d\t?",id[k]);
		id[k]++;
	} else {
		printf("\nponowna deklaracja zmiennej\n");
		exit(1);
	}
 }
 void Dzialaj(char *name,char *dzialanie)	{
 	char tmp[10];
	int a = GetVar(name,VT_INT);
	if (a!=-1)	{
		sprintf(tmp,"int%d",GetVar(name,VT_INT));
		fprintf(kod,"\tmov ebx,%s\n\t%s\n\tmov %s,ebx\n",tmp,dzialanie,tmp);
	} else {
		printf("\nniezadeklarowana zmienna\n");
		exit(1);
	}
 }
  void Dzialaj2(char *name,char *dzialanie)	{
 	char tmp[10];
	int a = GetVar(name,VT_FLOAT);
	if (a!=-1)	{
		sprintf(tmp,"fl%d",GetVar(name,VT_FLOAT));
		fprintf(kod,"\tmov ebx,%s\n\t%s\n\tmov %s,ebx\n",tmp,dzialanie,tmp);
	} else {
		printf("\nniezadeklarowana zmienna\n");
		exit(1);
	}
 }


 void Inc(char *name)	{
	Dzialaj(name,"inc ebx");
 }
 void Dec(char *name)	{
	Dzialaj(name,"dec ebx");
 }

 void CallRead()	{
	fprintf(kod,"\tmov eax, 4\n\tmov ebx, 1\n\tint 0x80\t\t;call read\n");
 }
 void Oblicz(char znak)	{
 	fprintf(kod,"\tpop eax\n\tpop edx\n");
	switch(znak)	{
		case'*': fprintf(kod,"\tmul edx\n"); break;
		case'/': fprintf(kod,"\tdiv edx\n");break;
		case'+' : fprintf(kod,"\tadd eax,edx\n"); break;
		case'-' : fprintf(kod,"\tsub eax,edx\n"); break;
		default: break;
	}
	fprintf(kod,"\tpush eax\t\t;wynik na stos\n");
 }
 void Porownaj()	{
	fprintf(kod,"\tpop eax\n\tand eax,ffffffffh\n\tjz %s\n",ReadLoop());/* jesli wynik operacji logicznych jest 0, skacz do petli 2 */
 }

 int licznik=0;
 /* sprawdzenie czy dzialanie spelnia warunek (jesli tak, to push 1) lub jesli nie , to push 0 */
 void Porownaj1(char *skok)	{  	
 	/*PushLoop(NextLoop());	 tymczasowa petla */
	/*char *tmp = PopLoop();*/
	char tmp[20];
	sprintf(tmp,"_tmp%d",licznik);
	licznik++;
	fprintf(kod,"\tpop ebx\n\tpop eax\n\tcmp eax,ebx\n\t%s %s\n\tpush 0\n\%s:\t\t;tmp loop\n\tpush 1\n",skok,tmp,tmp);
 }
 void PorownajEnd()	{
 	char *tmp = PopLoop();	/* nazwa 2 petli */
	fprintf(kod,"\tjmp %s\n%s:\t\t;koniec porownania\n",ReadLoop(),tmp);/* pierwsza petla jeszcze potrzebna */
 }
 void ElseEnd()	{
	fprintf(kod,"%s:\t\t;koniec bloku if lub else (jesli bylo)\n",PopLoop());	/* zdejmujemy pierwsza petle na koniec */
 }
%}

%union {
    char s[255];
}

%start KLASY
%token KW_PRIVATE KW_PUBLIC KW_STATIC KW_VOID KW_CLASS KW_INT KW_DO KW_WHILE ID_ID LIT_LIT NM_INT NM_FLOAT BH_AE BH_PP BH_MM BH_LE 
%token KW_PROTECTED KW_STRING KW_SYSTEM KW_MAIN KW_UNSIGNED KW_FLOAT BH_E BH_NE BH_ANDAND BH_OROR KW_IF KW_ELSE KW_RETURN
%left "=" "-"
%left "+" "*"
%left "/"
%left "(" ")"
%%

KLASY: KLASY KLASA
	| KLASA
;

KLASA: KW_PUBLIC KW_CLASS ID_ID '{' CLASS_BODY '}'
;

CLASS_BODY: CLASS_BODY CLASS_BODY1
	| CLASS_BODY1
;

CLASS_BODY1: DECLARE_METHOD
	| DECLARE_CLASSVARIABLE
	| DECLARE_MAIN
;

DECLARE_MAIN: DECLARE_MAIN1 '(' KW_STRING'['']' ID_ID ')' BODY2 { EndProg();}
;

DECLARE_MAIN1: INHERIT_TYPE KW_STATIC KW_VOID KW_MAIN	{ Main(); }
;

INHERIT_TYPE: KW_PUBLIC
	| KW_PROTECTED
	| KW_PRIVATE
;

DECLARE_METHOD: INHERIT_TYPE TYPE ID_ID ARGUMENTS2 '{' BODY RETURN '}'
		| INHERIT_TYPE TYPE ID_ID ARGUMENTS2 '{' RETURN '}'
		| INHERIT_TYPE KW_VOID ID_ID ARGUMENTS2 BODY2
;

RETURN: KW_RETURN EXPR ';'	
;

ARGUMENTS2: '(' ARGUMENTS ')'
	| '(' KW_VOID ')'
	| '('')'
;

DECLARE_CLASSVARIABLE: INHERIT_TYPE TYPE ID_ID ';'	{ AddVar($<s>3,vartype);} 
;


BODY2: '{' BODY '}'
	| '{' '}'
;

BODY3: BODY2
	| OPERATION ';'
	| FUNC_RET ';'
;

BODY: BODY BODY1
	| BODY1
;

START_DO_WHILE: KW_DO	{ CreateDoWhile(); }
;

DO_WHILE: START_DO_WHILE BODY2 KW_WHILE  COMPARES2  ';' { PorownajEnd(); PopLoop(); fprintf(kod,"\t\t;koniec do while\n\n"); }
;

COMPARES2: '(' COMPARES ')'	{/* warunki do if i do while- wynik porownan zapisany na stosie */ Porownaj();	}
	| '(' NUMBER ')'	{ Porownaj(); /* number jest na stosie */ }
;

START_IF: KW_IF { CreateIf(); }
;

IF_THEN1: START_IF COMPARES2 BODY3	{ PorownajEnd(); }

IF_THEN: IF_THEN1	{ ElseEnd(); }
	| IF_THEN1 KW_ELSE BODY3	{ ElseEnd(); }
;

BODY1: DECLARATION
	| DO_WHILE
	| IF_THEN
	| OPERATION ';'
	| FUNC_RET ';'
;

CALL_IN: KW_SYSTEM '.' ID_ID '.' ID_ID '(' ')' { CallRead(); }
;

DECLARATION: DECLARE_VAR 
	| DECLARE_EXP 
	| DECLARE_TAB
;

DECLARE_TAB: TYPE ID_ID '['']' ';'
	| TYPE ID_ID '[' NM_INT ']' ';'
;

DECLARE_VAR: TYPE ID_ID ';'	{AddVar($<s>2,vartype); }
;

DECLARE_EXP: TYPE ATTRIBUTION ';' { AddVar(variable,vartype); 
					if(vartype==VT_INT)
						Dzialaj(variable,"move ebx,eax"); 
					else if (vartype==VT_FLOAT)	
						Dzialaj2(variable,"move ebx,eax");	
					
				}
;

ATTRIBUTION: ID_ID '=' EXPR	{ /*AddVar($<s>1,vartype); Dzialaj($<s>1,"pop ebx");*/
					if (vartype==VT_INT)	{
						fprintf(kod,"\n\tpop eax\n");
						SetVar($<s>1);						
						/*fprintf(kod,"mov int%d,ebx\n",GetVar($<s>1,VT_INT));*/
					}else if(vartype==VT_FLOAT)	{
						fprintf(kod,"\n\tfstb eax\n");
						SetVar($<s>1);
						/*fprintf(kod,"mov fl%d,ebx\n",GetVar($<s>1,VT_FLOAT));*/
					}
				}
	| ID_TAB '=' EXPR	
;

ID_TAB: ID_ID '[' EXPR ']'
;

OPERATION_DOUBLE: ID_ID BH_PP { Inc($<s>1);}
	| ID_ID BH_MM		{ Dec($<s>1);} 
;

OPERATION: ATTRIBUTION
	| OPERATION_DOUBLE
;

ARGUMENTS: ARGUMENTS ',' TYPE ID_ID { AddVar($<s>4,vartype); }
	| TYPE ID_ID	{ AddVar($<s>2,vartype); }
;

TYPE: KW_UNSIGNED KW_INT { vartype=VT_INT; }
	| KW_FLOAT 	{ vartype=VT_FLOAT; }
	| KW_INT 	{ vartype=VT_INT;  }
;

NUMBER: NM_INT		{ fprintf(kod,"\tpush %s\n",$<s>1); }
	| NM_FLOAT	{ fprintf(kod,"\tfld %s\n",$<s>1);}
;
	
VALUE: NUMBER		 
	| ID_ID		{ FindVar($<s>1); }
	| ID_TAB
;

	
EXPR: EXPR '*' EXPR	{ Oblicz('*');}
	| EXPR '+' EXPR	{ Oblicz('+');}
	| EXPR '-' EXPR { Oblicz('-');}
	| EXPR '/' EXPR { Oblicz('/');}
	| '(' EXPR ')'
	| VALUE
	| FUNC_RET	{ fprintf(kod,"\tpush eax\n"); /*wynik f.systemowej w eax*/}
;

FUNC_RET: CALL_IN
	| ID_ID ARGS1
;	


COMPARES: COMPARES BH_ANDAND COMPARES	{ Porownaj1("je "); /* wszystkie musza byc jedynkami */ }
	| COMPARES BH_OROR COMPARES	{ Porownaj1("jnz "); /* wystarczy ze jeden!=drugiego i na pewno nie ma zera */ }
	| '(' COMPARES ')' 
	| COMPARE
;

EXPR1: EXPR
	| '(' ATTRIBUTION ')' 
;

COMPARE: EXPR1 '<' EXPR1 	{ Porownaj1("jl "); }
	| EXPR1 '>' EXPR1	{ Porownaj1("ja "); }
	| EXPR1 BH_E EXPR1	{ Porownaj1("je "); }
	| EXPR1 BH_NE EXPR1	{ Porownaj1("jne "); }
	| EXPR1 BH_AE EXPR1	{ Porownaj1("jae "); }
	| EXPR1 BH_LE EXPR1	{ Porownaj1("jle "); }
;

ARGS1: '(' ARGS ')'
	| '(' ')'
;

ARGS: ARGS ',' VALUE
	| VALUE
;
	
%%

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

