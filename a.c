#include<stdio.h>
#include<stdint.h>

#include"qLinkedList.h"
#include"qLinkedTree.h"
#include"qStack.h"

#define bin_chuckSize 7
uint8_t binAt(qLinkedList*obj, size_t idx){
	return (idx%bin_chuckSize)[(int8_t*)qLinkedListF1(obj, idx/bin_chuckSize)];
}
uint32_t utf8ToCodepoint(qLinkedList*str, size_t*begin){
	size_t b=*begin;
	uint8_t c=binAt(str, b), t;
	uint32_t a=0;
	for(t=0x80;c&t;t>>=1);
	switch(t){
		case 0x80:t=0;a=c;		break;
		case 0x20:t=1;a=c&0x1f;	break;
		case 0x10:t=2;a=c&0x0f;	break;
		case 0x08:t=3;a=c&0x07;	break;
		case 0x04:t=4;a=c&0x03;	break;
		case 0x02:t=5;a=c&0x01;	break;
		default:{//0x40 0x01
			*begin+=1;
			return 0xFFFD;
		}
	}
	*begin+=t+1;
	for(c=0;c<t;c++)a=a<<6|binAt(str,b+c+1)&0x3f;
	return a;
}

qLinkedList source;
size_t sourceLength=0;

qLinkedTree parseTree;
qStack parseTreeStack;

typedef struct s0{uint16_t type; uint64_t data;}s0;

uint64_t makeParseTree(){
	static size_t readPoint=0;
	static uint32_t c;
	c=utf8ToCodepoint(&source, &readPoint);
	printf("%c",c);
	printf("q : %p %d\n",*(qLinkedTree**)qStackF2(&parseTreeStack), ((s0*)qLinkedTreeF4(*(qLinkedTree**)qStackF2(&parseTreeStack)))->type);
	/*
	if(parseTreeStack.count==1){
		((s0*)qLinkedTreeF4(qLinkedTreeF1(*(qLinkedTree**)qStackF2(&parseTreeStack), sizeof(s0))))->type=0x10;
		((s0*)qLinkedTreeF4(qLinkedTreeF1(*(qLinkedTree**)qStackF2(&parseTreeStack), sizeof(s0))))->type=0x20;
		((s0*)qLinkedTreeF4(qLinkedTreeF2(*(qLinkedTree**)qStackF2(&parseTreeStack), 1)))->data=1;
		((s0*)qLinkedTreeF4(qLinkedTreeF1(
			qLinkedTreeF2(*(qLinkedTree**)qStackF2(&parseTreeStack), 1), sizeof(s0)
		)))->type=0x10;
		((s0*)qLinkedTreeF4(qLinkedTreeF2(
			qLinkedTreeF2(*(qLinkedTree**)qStackF2(&parseTreeStack), 1), 0
		)))->data=0;
		((s0*)qLinkedTreeF4(qLinkedTreeF1(*(qLinkedTree**)qStackF2(&parseTreeStack), sizeof(s0))))->type=0x10;
		((s0*)qLinkedTreeF4(qLinkedTreeF2(*(qLinkedTree**)qStackF2(&parseTreeStack), 0)))->data=;
//		qLinkedTreeF1(*(qLinkedTree**)qStackF2(&parseTreeStack), 8);
//		*qLinkedTreeF1(*(qLinkedTree**)qStackF2(&parseTreeStack), 8)->data=;
	}
	switch((*(s0*)qLinkedTreeF4(*(qLinkedTree**)qStackF2(&parseTreeStack))).type){
		case 0:{//Root
			if(c==0x03BB){
			}
			break;
		}
	}
//	printf("%d",*(uint64_t)qLinkedTreeF4(qStackF2(&parseTreeStack)));
	*/
	switch(c){
		case 'U':{
			((s0*)qLinkedTreeF4(*(qLinkedTree**)qStackF2(&parseTreeStack)))->type=0;
			((s0*)qLinkedTreeF4(*(qLinkedTree**)qStackF2(&parseTreeStack)))->data=0;
			break;
		}
		case '1':{
			((s0*)qLinkedTreeF4(*(qLinkedTree**)qStackF2(&parseTreeStack)))->type=0;
			((s0*)qLinkedTreeF4(*(qLinkedTree**)qStackF2(&parseTreeStack)))->data=1;
			break;
		}
		case '+':{
			((s0*)qLinkedTreeF4(*(qLinkedTree**)qStackF2(&parseTreeStack)))->type=1;

			*(qLinkedTree**)qStackF1(&parseTreeStack)
				=qLinkedTreeF1(*(qLinkedTree**)qStackF2(&parseTreeStack),sizeof(s0));
			makeParseTree();
			qStackF3(&parseTreeStack);

			*(qLinkedTree**)qStackF1(&parseTreeStack)
				=qLinkedTreeF1(*(qLinkedTree**)qStackF2(&parseTreeStack),sizeof(s0));
			makeParseTree();
			qStackF3(&parseTreeStack);
			break;
		}
		case '*':{
			((s0*)qLinkedTreeF4(*(qLinkedTree**)qStackF2(&parseTreeStack)))->type=2;

			*(qLinkedTree**)qStackF1(&parseTreeStack)
				=qLinkedTreeF1(*(qLinkedTree**)qStackF2(&parseTreeStack),sizeof(s0));
			makeParseTree();
			qStackF3(&parseTreeStack);

			*(qLinkedTree**)qStackF1(&parseTreeStack)
				=qLinkedTreeF1(*(qLinkedTree**)qStackF2(&parseTreeStack),sizeof(s0));
			makeParseTree();
			qStackF3(&parseTreeStack);
			break;
		}
		case '@':{
			((s0*)qLinkedTreeF4(*(qLinkedTree**)qStackF2(&parseTreeStack)))->type=3;
			
			*(qLinkedTree**)qStackF1(&parseTreeStack)
				=qLinkedTreeF1(*(qLinkedTree**)qStackF2(&parseTreeStack),sizeof(s0));
			makeParseTree();
			qStackF3(&parseTreeStack);
			break;
		}
		case '!':{
			((s0*)qLinkedTreeF4(*(qLinkedTree**)qStackF2(&parseTreeStack)))->type=4;
			
			*(qLinkedTree**)qStackF1(&parseTreeStack)
				=qLinkedTreeF1(*(qLinkedTree**)qStackF2(&parseTreeStack),sizeof(s0));
			makeParseTree();
			qStackF3(&parseTreeStack);
			break;
		}
		case '?':{
			((s0*)qLinkedTreeF4(*(qLinkedTree**)qStackF2(&parseTreeStack)))->type=5;

			*(qLinkedTree**)qStackF1(&parseTreeStack)
				=qLinkedTreeF1(*(qLinkedTree**)qStackF2(&parseTreeStack),sizeof(s0));
			makeParseTree();
			qStackF3(&parseTreeStack);

			*(qLinkedTree**)qStackF1(&parseTreeStack)
				=qLinkedTreeF1(*(qLinkedTree**)qStackF2(&parseTreeStack),sizeof(s0));
			makeParseTree();
			qStackF3(&parseTreeStack);
			break;
		}
		case '<':{
			((s0*)qLinkedTreeF4(*(qLinkedTree**)qStackF2(&parseTreeStack)))->type=6;
			
			*(qLinkedTree**)qStackF1(&parseTreeStack)
				=qLinkedTreeF1(*(qLinkedTree**)qStackF2(&parseTreeStack),sizeof(s0));
			makeParseTree();
			qStackF3(&parseTreeStack);
			break;
		}
		case '>':{
			((s0*)qLinkedTreeF4(*(qLinkedTree**)qStackF2(&parseTreeStack)))->type=7;
			
			*(qLinkedTree**)qStackF1(&parseTreeStack)
				=qLinkedTreeF1(*(qLinkedTree**)qStackF2(&parseTreeStack),sizeof(s0));
			makeParseTree();
			qStackF3(&parseTreeStack);
			break;
		}
		case '$':{
			((s0*)qLinkedTreeF4(*(qLinkedTree**)qStackF2(&parseTreeStack)))->type=8;

			*(qLinkedTree**)qStackF1(&parseTreeStack)
				=qLinkedTreeF1(*(qLinkedTree**)qStackF2(&parseTreeStack),sizeof(s0));
			makeParseTree();
			qStackF3(&parseTreeStack);

			*(qLinkedTree**)qStackF1(&parseTreeStack)
				=qLinkedTreeF1(*(qLinkedTree**)qStackF2(&parseTreeStack),sizeof(s0));
			makeParseTree();
			qStackF3(&parseTreeStack);
			break;
		}
	}
	printf(" q : %p %d\n",*(qLinkedTree**)qStackF2(&parseTreeStack), ((s0*)qLinkedTreeF4(*(qLinkedTree**)qStackF2(&parseTreeStack)))->type);
}

uint64_t memory[1024];
uint64_t runParseTree(){
	uint64_t a;
	switch(((s0*)qLinkedTreeF4(*(qLinkedTree**)qStackF2(&parseTreeStack)))->type){
		case 0:{
			return ((s0*)qLinkedTreeF4(*(qLinkedTree**)qStackF2(&parseTreeStack)))->data;
		}
		case 1:{
			*(qLinkedTree**)qStackF1(&parseTreeStack)
				=qLinkedTreeF2(*(qLinkedTree**)qStackF2(&parseTreeStack),0);
			a=runParseTree();
			qStackF3(&parseTreeStack);

			*(qLinkedTree**)qStackF1(&parseTreeStack)
				=qLinkedTreeF2(*(qLinkedTree**)qStackF2(&parseTreeStack),1);
			a+=runParseTree();
			qStackF3(&parseTreeStack);
			return a;
		}
		case 2:{
			*(qLinkedTree**)qStackF1(&parseTreeStack)
				=qLinkedTreeF2(*(qLinkedTree**)qStackF2(&parseTreeStack),0);
			a=runParseTree();
			qStackF3(&parseTreeStack);

			*(qLinkedTree**)qStackF1(&parseTreeStack)
				=qLinkedTreeF2(*(qLinkedTree**)qStackF2(&parseTreeStack),1);
			a*=runParseTree();
			qStackF3(&parseTreeStack);
			return a;
		}
		case 3:{
			*(qLinkedTree**)qStackF1(&parseTreeStack)
				=qLinkedTreeF2(*(qLinkedTree**)qStackF2(&parseTreeStack),0);
			a=runParseTree();
			qStackF3(&parseTreeStack);
			return a[memory];
		}
		case 4:{
			do{
				*(qLinkedTree**)qStackF1(&parseTreeStack)
					=qLinkedTreeF2(*(qLinkedTree**)qStackF2(&parseTreeStack),0);
				a=runParseTree();
				qStackF3(&parseTreeStack);
			}while(a);
			return a;
		}
		case 5:{
			uint64_t b;
			*(qLinkedTree**)qStackF1(&parseTreeStack)
				=qLinkedTreeF2(*(qLinkedTree**)qStackF2(&parseTreeStack),0);
			a=runParseTree();
			qStackF3(&parseTreeStack);

			*(qLinkedTree**)qStackF1(&parseTreeStack)
				=qLinkedTreeF2(*(qLinkedTree**)qStackF2(&parseTreeStack),1);
			b=runParseTree();
			qStackF3(&parseTreeStack);
			return a!=b;
		}
		case 6:{
			*(qLinkedTree**)qStackF1(&parseTreeStack)
				=qLinkedTreeF2(*(qLinkedTree**)qStackF2(&parseTreeStack),0);
			a=runParseTree();
			qStackF3(&parseTreeStack);
			a[memory]=getchar();
			return a[memory];
		}
		case 7:{
			*(qLinkedTree**)qStackF1(&parseTreeStack)
				=qLinkedTreeF2(*(qLinkedTree**)qStackF2(&parseTreeStack),0);
			a=runParseTree();
			qStackF3(&parseTreeStack);
			putchar(a);
			return a;
		}
		case 8:{
			*(qLinkedTree**)qStackF1(&parseTreeStack)
				=qLinkedTreeF2(*(qLinkedTree**)qStackF2(&parseTreeStack),0);
			a=runParseTree();
			qStackF3(&parseTreeStack);

			*(qLinkedTree**)qStackF1(&parseTreeStack)
				=qLinkedTreeF2(*(qLinkedTree**)qStackF2(&parseTreeStack),1);
			runParseTree()[memory]=a;
			qStackF3(&parseTreeStack);
			return a;
		}
	}
}

int main(int argc, char**argv){
	printf("%d\n",feof(stdin));
	if(argc<2)return 0;
	if(argc>1)puts(argv[1]);
	
	//Init buffer for source read 
	qLinkedListF0(&source, bin_chuckSize);

	{//Read source
		size_t r;
		FILE*sourceFile=fopen(argv[1],"rb");
		while((r=fread(qLinkedListF4(&source),1,bin_chuckSize,sourceFile))==bin_chuckSize)sourceLength+=r;
		sourceLength+=r;
		fclose(sourceFile);
	}
	printf("%d\n",sourceLength);
	int i;
//	uint64_t c=0;
//	for(c=0;c<sourceLength;){
//		printf("%04X ",utf8ToCodepoint(&source, &c));
//	}

	qLinkedTreeF0(&parseTree,sizeof(s0));
//	qLinkedTreeF0(&memory,8);
//	(*(s0*)qLinkedTreeF4(&parseTree)).type=0;

	qStackF0(&parseTreeStack, sizeof(qLinkedTree*), 16);
	*(qLinkedList**)qStackF1(&parseTreeStack)=&parseTree;
	printf("%p\n",&parseTree);
	

	printf("o : %p %d\n",*(qLinkedTree**)qStackF2(&parseTreeStack), ((s0*)qLinkedTreeF4(*(qLinkedTree**)qStackF2(&parseTreeStack)))->type);
	makeParseTree();
	puts("");
	printf("o : %p %d\n",*(qLinkedTree**)qStackF2(&parseTreeStack), ((s0*)qLinkedTreeF4(*(qLinkedTree**)qStackF2(&parseTreeStack)))->type);
	printf("%d",runParseTree());

}
/*	qStack q;
	qStackF0(&q, 5, 7);
//	printf("%lu", q.data.dataSize);
//	void*a=malloc(48);
	void* p=qStackF1(&q);
	*(int*)p=0;
	printf("%p\n",p);
	
	for(i=1;i<16;i++){
		p=qStackF1(&q);
		*(int*)p=i;
		printf("%d %p %p\n",i,p, qStackF2(&q));
	}
	for(i=1;i<16;i++){
		printf("%d ",*(int*)qStackF2(&q));
		p=qStackF3(&q);
		printf("%d %d %p\n",i,p, qStackF2(&q));
	}
	p=qStackF3(&q);
	printf("%d %d %p\n",i,p, qStackF2(&q));
*/
/*	qLinkedList q;
	qLinkedListF0(&q, 4);
	printf("%p\n",qLinkedListF1(&q, 0));
	*(int*)qLinkedListF4(&q)=5;
	*(int*)qLinkedListF3(&q, 0)=1;
	*(int*)qLinkedListF3(&q, 0)=2;
	*(int*)qLinkedListF3(&q, 1)=3;
	*(int*)qLinkedListF4(&q)=4;
	printf("%p\n",qLinkedListF1(&q, 0));
	uint64_t i;
	for(i=0;i<qLinkedListF2(&q);i++)printf("%d ",*(int*)qLinkedListF1(&q, i));puts("");
	printf("%d\n",qLinkedListF6(&q));
	for(i=0;i<qLinkedListF2(&q);i++)printf("%d ",*(int*)qLinkedListF1(&q, i));puts("");
	printf("%d\n",qLinkedListF5(&q, 0));
	printf("%d\n",qLinkedListF5(&q, 3));
	printf("%d\n",qLinkedListF5(&q, 0));
	printf("%d\n",qLinkedListF5(&q, 0));
	printf("%d\n",qLinkedListF5(&q, 0));
	printf("%d\n",qLinkedListF5(&q, 0));
	printf("%d\n",qLinkedListF5(&q, 0));
	printf("%d\n",qLinkedListF6(&q));
//	*(int*)qLinkedListF4(&q)=6;
	for(i=0;i<qLinkedListF2(&q);i++)printf("%d ",*(int*)qLinkedListF1(&q, i));puts("");
*/

