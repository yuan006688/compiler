#include <iostream>
#include <string>
#include <stack>
#include <unistd.h>

using namespace std;

int toInte(string str);
int in(char a);
char youxian(char a,char b);
int suan(int m,int n,char c);

int main(int argc, char const *argv[])
{
	string all;
	cin>>all;
	while(all[0] != '#'){
		char next=all[0];
		int first=0;
		int last=0;
		stack<int> opnd;
		stack<char> optr;
		optr.push('#');

		while(next != '#' || optr.top() !='#' ){
			if(0==in(next)){
				for(last=first;0==in(all[last]);last++)
					;
				opnd.push(toInte(all.substr(first,last-first)));
				next=all[last];
				first=last;
			}else{
				switch (youxian(optr.top(),next)){
					case '<':
						optr.push(next);
						first++;
						next=all[first];
						break;
					case '=':
						optr.pop();
						first++;
						next=all[first];
						break;
					case '>':
						int m=opnd.top();
						opnd.pop();
						int n=opnd.top();
						opnd.pop();
						char yun=optr.top();
						optr.pop();
						opnd.push(suan(m,n,yun));
						/*
						if(next == ')'){
							first++;
							next=all[first];
							optr.pop();
							//break;
						}

						//下边这一段是第一次多此一举加进去的，没弄明白程序所导致的
						if(next != '#'){
							optr.push(next);
							first++;
							next=all[first];
						}
						*/
						break;
				}
			}

		}
		cout<<opnd.top()<<'\n';
		cin>>all;
	}
}

int toInte(string str){
	int i=0;
	int sum=0;
	while(i<str.length()){
		sum=sum*10+int(str[i]-'0');
		i++;
	}
	return sum;
}

int in(char a){
	if(
		( a=='+' ) ||
		( a=='-' ) ||
		( a=='*' ) ||
		( a=='/' ) ||
		( a=='(' ) ||
		( a==')' ) ||
		( a=='#' )
	)
		return 1;
	else
		return 0;
}

char youxian(char a,char b){
	char youxianji[7][7]={
		{'>','>','<','<','<','>','>'},
		{'>','>','<','<','<','>','>'},
		{'>','>','>','>','<','>','>'},
		{'>','>','>','>','<','>','>'},
		{'<','<','<','<','<','=',' '},
		{'>','>','>','>',' ','>','>'},
		{'<','<','<','<','<',' ','='}
	};

	int fa,la;
	switch (a){
		case '+':fa=0;break;
		case '-':fa=1;break;
		case '*':fa=2;break;
		case '/':fa=3;break;
		case '(':fa=4;break;
		case ')':fa=5;break;
		case '#':fa=6;break;
	};
	switch (b){
		case '+':la=0;break;
		case '-':la=1;break;
		case '*':la=2;break;
		case '/':la=3;break;
		case '(':la=4;break;
		case ')':la=5;break;
		case '#':la=6;break;
	};
	return youxianji[fa][la];
}

int suan(int m,int n,char c){
	switch (c){
		case '+':return m+n;
		case '-':return n-m;
		case '*':return m*n;
		case '/':return n/m;
	}
	return 0;
}