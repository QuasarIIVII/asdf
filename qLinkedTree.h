#ifndef __qLinkedTree__
#define __qLinkedTree__
#include"qLinkedList.h"
typedef struct qLinkedTree{
	size_t dataSize;
	struct qLinkedTree*parent;
	qLinkedList child;
	void*data;
}qLinkedTree;
//Init root (Set as root)
void qLinkedTreeF0(qLinkedTree*obj, size_t dataSize){
	obj->parent=NULL;
	obj->dataSize=dataSize;

	obj->data = obj->dataSize ? malloc(obj->dataSize) : NULL;
	qLinkedListF0(&obj->child, sizeof(qLinkedTree));
}
//Add Child
qLinkedTree*qLinkedTreeF1(qLinkedTree*obj, size_t dataSize){
	qLinkedTree*p;
	p=(qLinkedTree*)qLinkedListF4(&obj->child);
	p->dataSize=dataSize;
	p->data = p->dataSize ? malloc(p->dataSize) : NULL;
	p->parent=obj;
	qLinkedListF0(&p->child, sizeof(qLinkedTree));
	return p;
}
//Access Child Node
qLinkedTree*qLinkedTreeF2(qLinkedTree*obj, size_t index){
	return qLinkedListF1(&obj->child,index);
}
//Access Parent Node
qLinkedTree*qLinkedTreeF3(qLinkedTree*obj){return obj->parent;}
//Access Data
void*qLinkedTreeF4(qLinkedTree*obj){return obj->data;}
#endif//__qLinkedTree__
