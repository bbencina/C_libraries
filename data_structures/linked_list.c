/* C library for:
 * -linked list [DONE],
 * -double-linked list [DONE],
 * -circular linked list [DONE],
 * -circular double-linked list [DONE].
 *
 * Status: [COMPILED]
 *
 * Written by Benjamin Benčina.
 *
 * Written as a general purpose library of the linked list data structure.
 *
 * NOTES:
 * -Having problems separating this file into a header file (.h) and
 *	an implementation file (.c). Naming it either one compiles and works
 *	fine, but separating them generates a pageful of errors.
 */

#ifndef LINKEDLISTLIBRARY_H
#define LINKEDLISTLIBRARY_H

#include <stdlib.h>

/* STRUCTURES */

typedef struct LinkedListElement_{
	int data;
	struct LinkedListElement_ *next;
} LinkedListElement;

typedef struct DoubleLinkedListElement_{
	int data;
	struct DoubleLinkedListElement_ * prev, * next;
} DoubleLinkedListElement;

typedef struct LinkedList_{
	int size;
	struct LinkedListElement_ * first, * last, * current;
} LinkedList;

typedef struct DoubleLinkedList_{
	int size;
	struct DoubleLinkedListElement_ * first, * last, * current;
} DoubleLinkedList;

typedef struct CircularLinkedList_{
	int size;
	struct LinkedListElement_ * current;
} CircularLinkedList;

typedef struct CircularDoubleLinkedList_{
	int size;
	struct DoubleLinkedListElement_ * current;
} CircularDoubleLinkedList;

/* FUNCTION PROTOTYPES */

LinkedList * LinkedListCreate();
void LinkedListInit (LinkedList *);
int LinkedListInsertAfter (LinkedList *, LinkedListElement *, int);
int LinkedListPopNext (LinkedList *, LinkedListElement *);
int LinkedListAddFirst (LinkedList *, int);
int LinkedListAddLast (LinkedList *, int);
int LinkedListExistsNext (LinkedList *);
LinkedListElement * LinkedListNext (LinkedList *);
int LinkedListContainsValue (LinkedList *, int);
int LinkedListReset (LinkedList *);
int LinkedListClear (LinkedList *);
int LinkedListDelete (LinkedList *);

DoubleLinkedList * DoubleLinkedListCreate();
void DoubleLinkedListInit (DoubleLinkedList *);
int DoubleLinkedListInsertAfter (DoubleLinkedList *, DoubleLinkedListElement *, int);
int DoubleLinkedListInsertBefore(DoubleLinkedList *, DoubleLinkedListElement *, int);
int DoubleLinkedListPopNext (DoubleLinkedList *, DoubleLinkedListElement *);
int DoubleLinkedListPopPrev (DoubleLinkedList *, DoubleLinkedListElement *);
int DoubleLinkedListPopCurrent (DoubleLinkedList *);
int DoubleLinkedListAddFirst (DoubleLinkedList *, int);
int DoubleLinkedListAddLast (DoubleLinkedList *, int);
int DoubleLinkedListExistsNext (DoubleLinkedList *);
int DoubleLinkedListExistsPrev (DoubleLinkedList *);
DoubleLinkedListElement * DoubleLinkedListNext (DoubleLinkedList *);
DoubleLinkedListElement * DoubleLinkedListPrev (DoubleLinkedList *);
int DoubleLinkedListContainsValue (DoubleLinkedList *, int);
int DoubleLinkedListResetToFirst (DoubleLinkedList *);
int DoubleLinkedListResetToLast (DoubleLinkedList *);
int DoubleLinkedListClear (DoubleLinkedList *);
int DoubleLinkedListDelete (DoubleLinkedList *);

CircularLinkedList * CircularLinkedListCreate();
void CircularLinkedListInit (CircularLinkedList *);
int CircularLinkedListInsertAfter (CircularLinkedList *, LinkedListElement *, int);
int CircularLinkedListPopNext (CircularLinkedList *, LinkedListElement *);
LinkedListElement * CircularLinkedListNext (CircularLinkedList *);
int CircularLinkedListContainsValue (CircularLinkedList *, int);
int CircularLinkedListClear (CircularLinkedList *);
int CircularLinkedListDelete (CircularLinkedList *);

CircularDoubleLinkedList * CircularDoubleLinkedListCreate();
void CircularDoubleLinkedListInit (CircularDoubleLinkedList *);
int CircularDoubleLinkedListInsertAfter (CircularDoubleLinkedList *, DoubleLinkedListElement *, int);
int CircularDoubleLinkedListInsertBefore(CircularDoubleLinkedList *, DoubleLinkedListElement *, int);
int CircularDoubleLinkedListPopNext (CircularDoubleLinkedList *, DoubleLinkedListElement *);
int CircularDoubleLinkedListPopPrev (CircularDoubleLinkedList *, DoubleLinkedListElement *);
int CircularDoubleLinkedListPopCurrent (CircularDoubleLinkedList *);
DoubleLinkedListElement * CircularDoubleLinkedListNext (CircularDoubleLinkedList *);
DoubleLinkedListElement * CircularDoubleLinkedListPrev (CircularDoubleLinkedList *);
int CircularDoubleLinkedListContainsValue (CircularDoubleLinkedList *, int);
int CircularDoubleLinkedListClear (CircularDoubleLinkedList *);
int CircularDoubleLinkedListDelete (CircularDoubleLinkedList *);


/* FUNCTION IMPLEMENTATIONS */

LinkedList * LinkedListCreate(){
	LinkedList * list;
	list = (LinkedList *) malloc(sizeof(LinkedList));
	return list;
}

void LinkedListInit (LinkedList * list){
	list->size = 0;
	list->first = NULL;
	list->last = NULL;
	list->current = NULL;

}

int LinkedListInsertAfter (LinkedList * list,LinkedListElement * prev, int data) {
	LinkedListElement * newElement;
	newElement = (LinkedListElement *) malloc(sizeof(LinkedListElement));
	newElement->data = data;
	if (prev == NULL) {
		newElement->next = list->first;
		list->first = newElement;
		list->size++;
		return 1;
	} else {
		newElement->next = prev->next;
		if (prev == list->last) {
			list->last = newElement;
		}
		prev->next = newElement;
		list->size++;
		return 1;
	}
	return 0;
}

int LinkedListPopNext (LinkedList * list, LinkedListElement * prev) {
	if (list->size == 0) {
		return 0;
	}
	LinkedListElement * ptr;
	ptr = prev->next;
	prev->next = (prev->next)->next;
	list->size--;
	int d = ptr->data;
	free(ptr);
	return d;
}

int LinkedListAddFirst (LinkedList * list, int data){
	LinkedListElement * newElement;
	newElement = (LinkedListElement *) malloc(sizeof(LinkedListElement));
	newElement->data = data;
	newElement->next = list->first;
	list->first = newElement;
	list->size++;
	return 1;
}

int LinkedListAddLast (LinkedList * list, int data){
	LinkedListElement * newElement;
	newElement = (LinkedListElement *) malloc(sizeof(LinkedListElement));
	newElement->data = data;
	newElement->next = NULL;
	if (list->size == 0){
		list->first = newElement;
		list->size++;
		return 1;
	}
	list->last = newElement;
	list->size++;
	return 1;
}

int LinkedListExistsNext (LinkedList * list){
	if (list->size == 0){
		return 0;
	}
	if (list->current != list->last) {
		return 1;
	}
	return 0;
}

LinkedListElement * LinkedListNext (LinkedList * list) {
	return ((list->current)->next);
}

int LinkedListContainsValue (LinkedList * list, int val) {
	if (list->size == 0){
		return 0;
	}
	list->current = list->first;
	if ((list->current)->data == val){
		return 1;
	}
	while (LinkedListExistsNext(list)){
		list->current = LinkedListNext(list);
		if ((list->current)->data == val) {
			return 1;
		}
	}
	return 0;
}

int LinkedListReset (LinkedList * list){
	list->current = list->first;
	return 1;
}

int LinkedListClear (LinkedList * list){
	if (list->size == 0) {
		return 1;
	}
	LinkedListReset(list);
	while(LinkedListExistsNext(list)){
		LinkedListElement * temp = list->current;
		list->current = LinkedListNext(list);
		free(temp);
	}
	free(list->last);
	list->size = 0;
	return 1;
}

int LinkedListDelete (LinkedList * list){
	LinkedListClear(list);
	free(list);
	return 1;
}

DoubleLinkedList * DoubleLinkedListCreate() {
	DoubleLinkedList * dlist;
	dlist = (DoubleLinkedList *) malloc(sizeof(DoubleLinkedList));
	return dlist;
}

void DoubleLinkedListInit (DoubleLinkedList * dlist) {
	dlist->size = 0;
	dlist->first = NULL;
	dlist->last = NULL;
	dlist->current = NULL;
}
int DoubleLinkedListInsertAfter (DoubleLinkedList * dlist, DoubleLinkedListElement * previous, int data) {
	DoubleLinkedListElement * newElement;
	newElement = (DoubleLinkedListElement *) malloc(sizeof(DoubleLinkedListElement));
	newElement->data = data;
	if (previous == NULL) {
		newElement->next = dlist->first;
		(dlist->first)->prev = newElement;
		newElement->prev = NULL;
		dlist->first = newElement;
		dlist->size++;
		return 1;
	} else {
		newElement->next = previous->next;
		newElement->prev = previous;
		if (previous == dlist->last) {
			dlist->last = newElement;
		}
		(previous->next)->prev = newElement;
		previous->next = newElement;
		dlist->size++;
		return 1;
	}
	return 0;
}
int DoubleLinkedListInsertBefore(DoubleLinkedList * dlist, DoubleLinkedListElement * nextel, int data) {
	DoubleLinkedListElement * newElement;
	newElement = (DoubleLinkedListElement *) malloc(sizeof(DoubleLinkedListElement));
	newElement->data = data;
	if (nextel == NULL) {
		newElement->prev = dlist->last;
		(dlist->last)->next = newElement;
		newElement->next = NULL;
		dlist->last = newElement;
		dlist->size++;
		return 1;
	} else {
		newElement->next = nextel;
		newElement->prev = nextel->prev;
		if (nextel == dlist->first) {
			dlist->first = newElement;
		}
		(nextel->prev)->next = newElement;
		nextel->prev = newElement;
		dlist->size++;
		return 1;
	}
	return 0;
}

int DoubleLinkedListPopNext (DoubleLinkedList * dlist, DoubleLinkedListElement * previous) {
	if (dlist->size == 0) {
		return 0;
	}
	DoubleLinkedListElement * ptr;
	ptr = previous->next;
	int d = ptr->data;
	dlist->size--;
	previous->next = ptr->next;
	(ptr->next)->prev = previous;
	free(ptr);
	return d;
}

int DoubleLinkedListPopPrev (DoubleLinkedList * dlist, DoubleLinkedListElement * nextel) {
	if (dlist->size == 0) {
		return 0;
	}
	DoubleLinkedListElement * ptr;
	ptr = nextel->prev;
	int d = ptr->data;
	dlist->size--;
	nextel->prev = ptr->prev;
	(ptr->prev)->next = nextel;
	free(ptr);
	return d;
}

int DoubleLinkedListPopCurrent (DoubleLinkedList * dlist) {
	int d = (dlist->current)->data;
	if (dlist->current == dlist->first){
		dlist->first = (dlist->current)->next;
	}
	if (dlist->current == dlist->last){
		dlist->current = (dlist->current)->prev;
	}
	DoubleLinkedListElement * ptr = dlist->current;
	if ((dlist->current)->next != NULL) {
		dlist->current = (dlist->current)->next;
	} else if ((dlist->current)->prev != NULL) {
		dlist->current = (dlist->current)->prev;
	} else {
		dlist->current = NULL;
	}
	dlist->size++;
	free(ptr);
	return d;
}

int DoubleLinkedListAddFirst (DoubleLinkedList * dlist, int data) {
	DoubleLinkedListElement * newElement;
	newElement->data = data;
	newElement->prev = NULL;
	newElement->next = dlist->first;
	if (dlist->size != 0){
		(dlist->first)->prev = newElement;
	}
	dlist->first = newElement;
	if (dlist->size == 0){
		dlist->last = newElement;
	}
	dlist->size++;
	return 1;
}

int DoubleLinkedListAddLast (DoubleLinkedList * dlist, int data) {
	DoubleLinkedListElement * newElement;
	newElement->data = data;
	newElement->next = NULL;
	newElement->prev = dlist->last;
	if (dlist->size != 0){
		(dlist->last)->next = newElement;
	}
	dlist->last = newElement;
	if (dlist->size == 0){
		dlist->first = newElement;
	}
	dlist->size++;
	return 1;
}

int DoubleLinkedListExistsNext (DoubleLinkedList * dlist){
	if (dlist->size == 0){
		return 0;
	}
	if (dlist->current != dlist->last) {
		return 1;
	}
	return 0;
}

int DoubleLinkedListExistsPrev (DoubleLinkedList * dlist) {
	if (dlist->size == 0){
		return 0;
	}
	if (dlist->current != dlist->first) {
		return 1;
	}
	return 0;
}

DoubleLinkedListElement * DoubleLinkedListNext (DoubleLinkedList * dlist) {
	return ((dlist->current)->next);
}

DoubleLinkedListElement * DoubleLinkedListPrev (DoubleLinkedList * dlist) {
	return ((dlist->current)->prev);
}

int DoubleLinkedListContainsValue (DoubleLinkedList * dlist, int val) {
	if (dlist->size == 0){
		return 0;
	}
	dlist->current = dlist->first;
	if ((dlist->current)->data == val){
		return 1;
	}
	while (DoubleLinkedListExistsNext(dlist)){
		dlist->current = DoubleLinkedListNext(dlist);
		if ((dlist->current)->data == val) {
			return 1;
		}
	}
	return 0;
}

int DoubleLinkedListResetToFirst (DoubleLinkedList * dlist) {
	dlist->current = dlist->first;
	return 1;
}

int DoubleLinkedListResetToLast (DoubleLinkedList * dlist) {
	dlist->current = dlist->last;
	return 1;
}

int DoubleLinkedListClear (DoubleLinkedList * dlist) {
	if (dlist->size == 0) {
		return 1;
	}
	DoubleLinkedListResetToFirst(dlist);
	while (DoubleLinkedListExistsNext(dlist)){
		DoubleLinkedListElement * temp = dlist->current;
		dlist->current = DoubleLinkedListNext(dlist);
		free(temp);
	}
	free(dlist->last);
	dlist->size = 0;
	return 1;
}

int DoubleLinkedListDelete (DoubleLinkedList * dlist) {
	DoubleLinkedListClear(dlist);
	free(dlist);
	return 1;
}

CircularLinkedList * CircularLinkedListCreate() {
	CircularLinkedList * clist;
	clist = (CircularLinkedList *) malloc(sizeof(CircularLinkedList));
	return clist;
}

void CircularLinkedListInit (CircularLinkedList * clist) {
	clist->size = 0;
	clist->current = NULL;
}

int CircularLinkedListInsertAfter (CircularLinkedList * clist, LinkedListElement * prev, int data) {
	LinkedListElement * newElement;
	newElement->data = data;

	if (clist->size == 0) {
		newElement->next = newElement;
		clist->size++;
		clist->current = newElement;
		return 1;
	}
	newElement->next = prev->next;
	prev->next = newElement;
	clist->size++;
	return 1;
}

int CircularLinkedListPopNext (CircularLinkedList * clist, LinkedListElement * prev) {
	if (clist->size == 0) {
		return 0;
	}
	LinkedListElement * ptr;
	ptr = prev->next;
	prev->next = (prev->next)->next;
	clist->size--;
	int d = ptr->data;
	free(ptr);
	return d;
}

LinkedListElement * CircularLinkedListNext (CircularLinkedList * clist) {
	return (clist->current)->next;
}

int CircularLinkedListContainsValue (CircularLinkedList * clist, int val) {
	if (clist->size == 0) {
		return 0;
	}
	LinkedListElement * temp = clist->current;
	if ((clist->current)->data == val) {
		return 1;
	}
	if (clist->size > 1){
		clist->current = CircularLinkedListNext(clist);
		while (temp != clist->current) {
			if ((clist->current)->data == val) {
				return 1;
			}
		}
	}
	return 0;
}

int CircularLinkedListClear (CircularLinkedList * clist) {
	while ((clist->current)->next != clist->current) {
		CircularLinkedListPopNext(clist, clist->current);
	}
	free(clist->current);
	clist->size = 0;
	return 1;
}

int CircularLinkedListDelete (CircularLinkedList * clist) {
	CircularLinkedListClear(clist);
	free(clist);
	return 1;
}

CircularDoubleLinkedList * CircularDoubleLinkedListCreate() {
	CircularDoubleLinkedList * cdlist;
	cdlist = (CircularDoubleLinkedList *) malloc(sizeof(CircularDoubleLinkedList));
	return cdlist;
}

void CircularDoubleLinkedListInit (CircularDoubleLinkedList *cdlist) {
	cdlist->size = 0;
	cdlist->current = NULL;
}

int CircularDoubleLinkedListInsertAfter (CircularDoubleLinkedList * cdlist, DoubleLinkedListElement * previous, int data) {
	DoubleLinkedListElement * newElement;
	newElement->data = data;

	if (cdlist->size == 0) {
		newElement->next = newElement;
		newElement->prev = newElement;
		cdlist->size++;
		cdlist->current = newElement;
		return 1;
	}
	newElement->next = previous->next;
	(previous->next)->prev = newElement;
	previous->next = newElement;
	cdlist->size++;
	return 1;
}

int CircularDoubleLinkedListInsertBefore(CircularDoubleLinkedList * cdlist, DoubleLinkedListElement * nextel, int data) {
	DoubleLinkedListElement * newElement;
	newElement->data = data;

	if (cdlist->size == 0) {
		newElement->next = newElement;
		newElement->prev = newElement;
		cdlist->size++;
		cdlist->current = newElement;
		return 1;
	}
	newElement->prev = nextel->prev;
	(nextel->prev)->next = newElement;
	nextel->prev = newElement;
	cdlist->size++;
	return 1;
}

int CircularDoubleLinkedListPopNext (CircularDoubleLinkedList * cdlist, DoubleLinkedListElement * previous) {
	if (cdlist->size == 0) {
		return 0;
	}
	DoubleLinkedListElement * ptr;
	ptr = previous->next;
	previous->next = (previous->next)->next;
	(previous->next)->prev = previous;
	cdlist->size--;
	int d = ptr->data;
	free(ptr);
	return d;
}

int CircularDoubleLinkedListPopPrev (CircularDoubleLinkedList * cdlist, DoubleLinkedListElement * nextel) {
	if (cdlist->size == 0) {
		return 0;
	}
	DoubleLinkedListElement * ptr;
	ptr = nextel->prev;
	nextel->prev = (nextel->prev)->prev;
	(nextel->prev)->next = nextel;
	cdlist->size--;
	int d = ptr->data;
	free(ptr);
	return d;
}

int CircularDoubleLinkedListPopCurrent (CircularDoubleLinkedList * cdlist) {
	if (cdlist->size == 0) {
		return 0;
	} else if (cdlist->size == 1) {
		int d = (cdlist->current)->data;
		free(cdlist->current);
		return d;
	}
	int d = (cdlist->current)->data;
	((cdlist->current)->prev)->next = (cdlist->current)->next;
	((cdlist->current)->next)->prev = (cdlist->current)->prev;
	free(cdlist->current);
	return d;
}

DoubleLinkedListElement * CircularDoubleLinkedListNext (CircularDoubleLinkedList * cdlist) {
	return (cdlist->current)->next;
}

DoubleLinkedListElement * CircularDoubleLinkedListPrev (CircularDoubleLinkedList * cdlist) {
	return (cdlist->current)->prev;
}

int CircularDoubleLinkedListContainsValue (CircularDoubleLinkedList * cdlist, int val) {
	if (cdlist->size == 0) {
		return 0;
	}
	DoubleLinkedListElement * temp = cdlist->current;
	if ((cdlist->current)->data == val) {
		return 1;
	}
	if (cdlist->size > 1){
		cdlist->current = CircularDoubleLinkedListNext(cdlist);
		while (temp != cdlist->current) {
			if ((cdlist->current)->data == val) {
				return 1;
			}
		}
	}
	return 0;
}

int CircularDoubleLinkedListClear (CircularDoubleLinkedList * cdlist) {
	while ((cdlist->current)->next != cdlist->current) {
		CircularDoubleLinkedListPopNext(cdlist, cdlist->current);
	}
	free(cdlist->current);
	cdlist->size = 0;
	return 1;
}

int CircularDoubleLinkedListDelete (CircularDoubleLinkedList * cdlist) {
	CircularDoubleLinkedListClear(cdlist);
	free(cdlist);
	return 1;
}


#endif
