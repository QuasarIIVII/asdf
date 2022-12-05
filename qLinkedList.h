#ifndef __qLinkedList__
#define __qLinkedList__
struct _qLinkedList{
	void*data;
	_qLinkedList*next;
}
struct qLinkedList{
	_qLinkedList*head;
	size_t dataSize;
}
#endif//__qLinkedList__
