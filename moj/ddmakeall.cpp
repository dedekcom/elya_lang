#include <iostream.h>
#include <stdio.h>
#include <string.h>

int ddreadline(char *sout, char *sline)	{
	if(sline==NULL || sout==NULL) return 0;
	int i=0, j=0;
	char z;
	while(sline[i]!='\0')	{
		z = sline[i];
		if((z>='a'&&z<='z')||(z>='A'&&z<='Z')||(z>='0'&&z<='9'&&i>0)||(z=='_')
				||(z==':')||(z=='/')||(z=='.')) {
			sout[j] = z;
			j++;
		}
		i++;
	}
	sout[j]='\0';
	if(j>0)	return 1;
	else return 0;
}

int main(int argc, char *argv[])	{
	if(argc<=1)	{
		cout<<endl<<"give project file";
		exit(1);
	}
	char sfileprj[100];
	strcpy(sfileprj,argv[1]);

	FILE *fin;
	if( (fin=fopen(sfileprj,"r"))==NULL) {
		cout<<endl<<"can't open file with project: "<<sfileprj;
		exit(1);
	}
	
	char spath[256], sline[256], sout[256], sfileout[256],ssrc[256][128];
	int ilesrc=0;
	int readpath=0;
	int readsrc=0;
	int readall=0;
	int dalej=1;
	while(fgets(sline,256,fin)!=NULL && dalej)	{
		if(ddreadline(sout,sline))	{
			if(!strcmp(sout,"path:"))	{
				readpath=1;	
			}else if (!strcmp(sout,"src:"))	{
				readsrc=1;
			}else if (!strcmp(sout,"all:"))	{
				readall=1; readsrc=0;
			}else if (!strcmp(sout,"out:"))	{
				dalej=0;
			}else if(readpath)	{
				strcpy(spath,sout);
				readpath=0;
			}else if(readsrc)	{
				strcpy(ssrc[ilesrc],spath);
				strcat(ssrc[ilesrc],sout);
				ilesrc++;
			}else if(readall)	{
				strcpy(sfileout,spath);
				strcat(sfileout,sout);
				readall=0;
				dalej=0;
			}
		}
	}
	
	fclose(fin);
	FILE *fout;
	if((fout = fopen(sfileout,"w"))==NULL)	{
		cout<<endl<<"can't create file : "<<sfileout;
		exit(1);
	}
	char z;
	for(int i=0; i<ilesrc; i++)	{
		//cout<<endl<<"otwieram : " <<ssrc[i];
		if((fin=fopen(ssrc[i],"r"))!=NULL)	{
			z=fgetc(fin);
			while(z!=EOF) { 	
				fputc(z,fout);
				z = fgetc(fin);
			}
			fputc('\n',fout);
			fclose(fin);
		}
	}

	fclose(fout);
	cout<<sfileout;
	
	return 0;
}

