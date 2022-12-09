#ifndef __qLinkedList__
#define __qLinkedList__
#include<stdint.h>
#include<stdlib.h>
struct _qLinkedList;
typedef struct _qLinkedList{
	void*data;
	struct _qLinkedList*next;
}_qLinkedList;
typedef struct qLinkedList{
	_qLinkedList*head,*tail;
	size_t dataSize;
	uint64_t len;
}qLinkedList;
//Init
void qLinkedListF0(qLinkedList*obj, size_t dataSize){
	obj->dataSize=dataSize;
	obj->head=obj->tail=NULL;
	obj->len=0;
}
//Access
void*qLinkedListF1(qLinkedList*obj, uint64_t index){
	if(index>=obj->len)return NULL;
	_qLinkedList*p;
	uint64_t i;
	for(p=obj->head,i=index;i;i--, p=p->next);
	return p->data;
}
//Get length
uint64_t qLinkedListF2(qLinkedList*obj){return obj->len;}
//Insert (Insert, Add)
void*qLinkedListF3(qLinkedList*obj, uint64_t index){
	if(index>obj->len)return NULL;
	uint64_t i;
	_qLinkedList*newObj;
	if(index){
		_qLinkedList*p;
		for(p=obj->head,i=index-1;i;i--, p=p->next);
		newObj=(_qLinkedList*)malloc(sizeof(_qLinkedList));
		newObj->data=malloc(obj->dataSize);
		newObj->next=p->next;
		p->next=newObj;
	}else{
		newObj=(_qLinkedList*)malloc(sizeof(_qLinkedList));
		newObj->data=malloc(obj->dataSize);
		newObj->next=obj->head;
		obj->head=newObj;
	}
	if(index==obj->len)obj->tail=newObj;
	obj->len++;
	return newObj->data;
}
//Insert Back (Add)
void*qLinkedListF4(qLinkedList*obj){
	_qLinkedList*newObj;
	if(obj->len){
		newObj=(_qLinkedList*)malloc(sizeof(_qLinkedList));
		newObj->data=malloc(obj->dataSize);
		newObj->next=NULL;
		obj->tail->next=newObj;
		obj->tail=newObj;
	}else{
		newObj=(_qLinkedList*)malloc(sizeof(_qLinkedList));
		newObj->data=malloc(obj->dataSize);
		newObj->next=NULL;
		obj->head=obj->tail=newObj;
		obj->tail->next=newObj;
	}
	obj->len++;
	return newObj->data;
}
//Remove
uint8_t qLinkedListF5(qLinkedList*obj, uint64_t index){
	if(index>=obj->len)return 0;
	_qLinkedList*target;
	if(index){
		uint64_t i;
		_qLinkedList*p;
		for(p=obj->head,i=index-1;i;i--, p=p->next);
		target=p->next;
		p->next=p->next->next;
		free(target->data);
		free(target);
		if(obj->len==index+1)obj->tail=p;
	}else{
		target=obj->head;
		obj->head=obj->head->next;
		free(target->data);
		free(target);
		if(obj->len==index+1)obj->tail=obj->head;
	}
	obj->len--;
	return 1;
}
//Remove Back
uint8_t qLinkedListF6(qLinkedList*obj){
	return qLinkedListF5(obj, obj->len-1);
}
#endif//__qLinkedList__
