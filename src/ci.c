#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char *isWord(char *p){
	int i=0;
	if(isalpha(p[i])){
		i++;
		while(isalnum(p[i]) || p[i]=='_' ){
			i++;
		}
		return p+i;
	}
	return (char*)NULL;
}

char *isKnow(char *p){
	int i=0;
	if(p[i]=='/'){
		i++;
		if(p[i]=='/'){
			i++;
			while(p[i] != '\n' && p[i]!='\0' ) {
				i++;
			}
			return p+i;
		}else if(p[i]=='*'){
			i++;
			while( !( (p[i]=='*' && p[i+1]=='/') ) ) {
			    i++;
			}
			return p+i+2;
		}else{
			i++;
		}
	}
	return NULL;
}

void copy(char *a,char *b,int size){
	int i=0;
	for(;i<size;i++)
		b[i]=a[i];
	b[i]='\0';
}

void copy2(char *a,char *b,int size){
	int i=0,j=0;
	for(;i<size;i++){
		if(a[i] != '\n'){
			b[j++]=a[i];
		}else{
			i++;
		}
	}
	b[j]='\0';
}

int isSame(char *a,char *b,int size){
	int i=0;
	for(;i<size;i++){
		if(b[i]!=a[i]){
			return 0;;
		}
	}
	return 1;
}


char *isKeyWord(char *p){
	char *a[]={"auto","double","int",
		"struct","break","else","long","switch",
		"case","enum","returnegister","typedef",
		"char","extern","return","union","const",
		"float","short","unsigned","continue","for",
		"signed","void","default","goto","sizeof",
		"volatile","do","if","while","static","inline"};
	for(int i=0;i<sizeof(a)/8;i++){
		if(isSame(p,*(a+i),strlen(*(a+i))) &&
			(!isalnum(*(p+strlen(*(a+i))))) &&
			*(p+strlen(*(a+i))) != '_'  ){
			return p+strlen(*(a+i));
		}
	}
	return (char *)NULL;
}

char *isOperator(char *p){
	char *a[]={"++","--","+=","-+","*=",
		"/=","/","*","+","-","%=","%","->",">=","<=",">",
		"<","==","!=","=","&&",
		"||","&","|","^"};
	for(int i=0;i<sizeof(a)/8;i++){
		if(isSame(p,*(a+i),strlen(*(a+i)))){
			return p+strlen(*(a+i));
		}
	}
	return (char *)NULL;
}

char *isParten(char *p){
	char ch=*p;
	if( ch=='('||
		ch==')'||
		ch=='{'||
		ch=='}'
		){
		return p+1;
	}
	return NULL;
}

char *isNum(char *p){
	int i=0;
	if(isdigit(p[i])){
		i++;
		if(p[i]=='X' || p[i]=='x'){
			i++;
			while(isxdigit(p[i]))
				i++;
		}else{
			while(isdigit(p[i]))
				i++;
		}
		return p+i;
	}
	return (char *)NULL;
}

char *isString(char *p){
	int i=0;
	if(p[i]=='"'){
		i++;
		int mark=1;
		while(mark) {
			if(p[i]=='\\'){
				i++;
				if( p[i]=='"' ||
					p[i]=='t' ||
					p[i]=='n'
					)
					i++;
			}else if(p[i]=='"'){
				i++;
				mark=0;
			}else{
				i++;
			}
		}
		return p+i;
	}
	return NULL;
}

char *isChar(char *p){
	int i=0;
	if(p[i] == '\''){
		i++;
		if( p[i] !='\\' ){
			i++;
			return p+i;
		}else{
			i++;
			while(p[i++]!='\'') {
			}
			return p+i;
		}
	}
	return NULL;
}

void anylise(char *a,int size){
	char *name[]={"operator","KeyWord","Word",
		"Number","parteen","string","know","char"};
	char *name2[]={	"运算符   ",
					"关键字   ",
					"标示符   ",
					"数字     ",
					"括号     ",
					"字符串   ",
					"注释     ",
					"字符常量 "
				};
	int i=0;
	char *p = a;
	while(i<size) {
		int mark=0;
		if( (p=isKnow(a+i))!=NULL ){
			mark=6;
		}else if((p=isOperator(a+i))!=NULL){
			mark=0;
		}else if((p=isKeyWord(a+i))!=NULL){
			mark=1;
		}else if((p=isWord(a+i))!=NULL){
			mark=2;
		}else if((p=isNum(a+i))!=NULL){
			mark=3;
		}else if((p=isParten(a+i))!=NULL){
			mark=4;
		}else if((p=isString(a+i))!=NULL){
			mark=5;
		}else if((p=isChar(a+i))){
			mark=7;
		}else{
			i++;
			continue;
		}
		//printf("\e[31;1m%20s:\e[32;1m", *(name2+mark));
		printf("%s:", *(name2+mark));

		char b[512];
		for(int i=0;i<512;i++)
			*(b+i)='\0';
		copy2(a+i,b,p-(a+i));
		//b[1+( p-(a+i) )]='\0';
		i=i+(p-(a+i));
		printf("%s\n",b );
	}
}
//ksdfsddddddddddd
struct  of{
	FILE *fp;
	char *p;
};

/*  sakhdaskdasjkdh*/
struct of open(char *p){
	struct  of a;
	a.fp = fopen(p,"r");
	if( a.fp == NULL ){
		printf("open file error\n");
		exit(1);
	}

	a.p = (char *)malloc(1<<15);
	for(int i=0;i< 1<<15;i++)
		*(a.p+i) = '\0';
	if( a.p == NULL ){
		printf("error\n");
	}

	char *ch = a.p;
	while(!feof(a.fp)) {
		*ch++ = fgetc(a.fp);
	}
	*ch = '\0';
	return a;
}

void close(struct of a){
	fclose(a.fp);
	free(a.p);
}

int main(){
	/**
	 *
	 * hello
	 */
	char name[200];
	//printf("file name:");
	//scanf("%s",name);
	struct of a;
	a = open("/home/w/tmp/课程/编译原理/词法分析/ci.c");
	anylise(a.p,strlen(a.p));
	close(a);
}
