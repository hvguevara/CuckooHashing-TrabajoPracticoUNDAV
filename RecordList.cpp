#include <iostream>
#include "RecordList.h"
#include "Record.h"
#include "String.h"
using UndavRecord::Record;
using UndavRecord::IsLesser;

struct Node{
	Record* item;
	Node* next;
};

struct UndavRecordList::RecordList{
	Node* first;
	Node* last;
	int length;
};

struct UndavRecordList::Iterator::RecordIterator{
	Node* node;
};

//Precondicion: @list es una instancia valida
//Postcondicion: devuelve TRUE si @list se encuentra vacia, de lo contrario FALSE.
bool IsEmpty(UndavRecordList::RecordList* list);

//Precondicion: @item es un Record valido, y @Next es un Node valido
//Postcondicion: Devuelve una instancia valida de Node, que contiene a @item y esta enlazado con @next
Node* CreateNode(Record* item, Node* next);

//Precondicion: @a y @b tienen que ser nodos que representen cada uno dos mitades contiguas de una misma lista, donde ambos terminen en NULL
//Postcondicion: ordena los elementos de @a y @b en un nuevo primer nodo de la lista, el cual retornara
Node* Merge(Node* a, Node* b);

//Precondicion: @firstNode representa el primer nodo de una lista
//Postcondicion: divide la lista en dos y ordena sus respectivas partes en un mismo primer nodo
Node* MergeSort(Node* firstNode);

UndavRecordList::RecordList* UndavRecordList::Create(){
	RecordList*  newList = new RecordList;
	newList->first = newList->last = NULL;
	newList->length = 0;
	return newList;
}

Node* CreateNode(Record* item, Node* next)
{
	Node* newNode = new Node;
	newNode->item  = item;
	newNode->next = next;
	return newNode;
}

void UndavRecordList::Add(RecordList* list, Record* item){
	Node* newNode = CreateNode(item, NULL);
	if(IsEmpty(list))
	{
		list->first = newNode;
	}
	else
	{
		list->last->next = newNode;
	}
	list->last = newNode;
	list->length++;
}

bool IsEmpty(UndavRecordList::RecordList* list)
{
	return list->first == NULL;
}

int UndavRecordList::Length(const RecordList* list){
	return list->length;
}

Node* Merge(Node* a, Node* b){
	Node newFirst;
	Node* c = &newFirst;
	while(a != NULL && b != NULL){
		if(IsLesser(a->item, b->item)){
			c->next = a;
			c = a;
			a = a->next;
		} else {
			c->next = b;
			c = b;
			b = b->next;
		}
	}
	c->next = (a == NULL) ? b : a;
	return newFirst.next;
}

Node* MergeSort(Node* firstNode){
	Node* a;
	Node* b;
	if(firstNode == NULL || firstNode->next == NULL) return firstNode;
	a = firstNode;
	b = firstNode->next;
	while(b != NULL && b->next != NULL){
		firstNode = firstNode->next;
		b = b->next->next;
	}
	b = firstNode->next;
	firstNode->next = NULL;
	return Merge(MergeSort(a), MergeSort(b));
}

void UndavRecordList::Sort(RecordList* list){
	list->first = MergeSort(list->first);
	Node* iterator = list->first;
	while(iterator!=NULL)
	{
		if(iterator->next == NULL){
		  list->last = iterator;
		}
		iterator = iterator->next;
	}
}

void UndavRecordList::Reverse(RecordList* list){
	Node* iterator = list->first;
	list->last = iterator;
	Node* nextIterator;
	Node* newFirst = NULL;
	while(iterator != NULL){
		nextIterator = iterator->next;
		iterator->next = newFirst;
		newFirst = iterator;
		iterator = nextIterator;
	}
	list->first = newFirst;
}

UndavRecordList::Iterator::RecordIterator* UndavRecordList::Iterator::Begin(RecordList* list){
	RecordIterator* newIterator = new RecordIterator;
	newIterator->node = list->first;
	return newIterator;
}

bool UndavRecordList::Iterator::IsEnd(const RecordIterator* iterator){
	return (iterator->node == NULL);
}

void UndavRecordList::Iterator::Next(RecordIterator* iterator){
	if(!IsEnd(iterator)) iterator->node = iterator->node->next;
}

Record* UndavRecordList::Iterator::GetItem(RecordIterator* iterator){
	if(!IsEnd(iterator)) return iterator->node->item;
	else return NULL;
}

void UndavRecordList::Iterator::Destroy(RecordIterator* iterator){
	delete[] iterator;
}

void UndavRecordList::Destroy(RecordList* list){
	Node* iterator = list->first;
	while(iterator != NULL){
		Node* auxiliar = iterator;
		iterator = iterator->next;
		delete auxiliar;
	}
	delete[] list;
}
