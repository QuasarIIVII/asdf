#ifndef __qStack__
#define __qStack__
#include"qLinkedList.h"
typedef struct qStack{
	size_t chunkLen, count, dataSize, maxCount;
	qLinkedList data;
}qStack;
//Init
void qStackF0(qStack*obj, size_t dataSize, size_t chunkLen){
	qLinkedListF0(&obj->data, dataSize*chunkLen);
	obj->chunkLen=chunkLen;
	obj->dataSize=dataSize;
	obj->count=obj->maxCount=0;
}
//Push
void*qStackF1(qStack*obj){
	if(obj->maxCount==obj->count){
		puts("Alloc");
		qLinkedListF4(&obj->data);
		obj->maxCount+=obj->chunkLen;
		printf("%lu\n",obj->maxCount);
	}
	return &((obj->count++)%obj->chunkLen*obj->dataSize)[(int8_t*)qLinkedListF1(&obj->data, (obj->count)/obj->chunkLen)];
//	qLinkedListF1()
}
//Peek
void*qStackF2(qStack*obj){
	if(obj->count)return &((obj->count-1)%obj->chunkLen*obj->dataSize)[(int8_t*)qLinkedListF1(&obj->data, (obj->count-1)/obj->chunkLen)];
	else return NULL;
}
//Pop
uint8_t qStackF3(qStack*obj){
	if(!obj->count)return 0;
	obj->count--;
	if(obj->count==obj->maxCount-obj->chunkLen){
		puts("Free");
		qLinkedListF6(&obj->data);
		obj->maxCount-=obj->chunkLen;
		printf("%lu\n",obj->maxCount);
	}
	return 1;
}
#endif//__qStack__
