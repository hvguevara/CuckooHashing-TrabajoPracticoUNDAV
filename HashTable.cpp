#include <iostream>
#include "HashTable.h"
#include "Graph.h"
#include "UniversalHashing.h"
#include "Record.h"
#include "String.h"
using namespace UndavGraph;
using UndavUniversalHashing::UniversalHashing;
using UndavUniversalHashing::Hash;
using UndavRecord::Record;
using UndavString::IsEqual;
using UndavString::CreateCopy;
using UndavString::DestroyCopy;

struct UndavHashTable::HashTable{
	Record** values;
	char** keys;
	int size;
	int length;
	Graph* graph;
	UniversalHashing* firstUniversalHashing;
	UniversalHashing* secondUniversalHashing;
};

//Precondicion: @hashTable y @key son instancias validas
//Postcondicion: Calcula y devuelve el primer indice de hash de la key
int GetFirstHashIndex(UndavHashTable::HashTable* hashTable, const char* key);

//Precondicion: @hashTable y @key son instancias validas
//Postcondicion: Calcula y devuelve el segundo indice de hash de la key
int GetSecondHashIndex(UndavHashTable::HashTable* hashTable, const char* key);

//Precondicion: @hashTable y @key son instancias validas
//Postcondicion: Si @key existe en @hashTable devuelve su indice, si no devuelve -1
int GetKeyIndex(UndavHashTable::HashTable* hashTable, const char* key);

//Precondicion: @hashTable, @key y @value son instancias validas
//Postcondicion: Si @key existe en @hashTable reemplaza su valor. Si no existe y encuentra una posicion vacia,
//inserta el par "key-value" a la tabla. Si encuentra una posicion en la que hay otra key, reinserta esa key
//en su posicion alternativa e inserta nuestra @key en la posicion que quedo vacante, siempre y cuando haya espacio
void Insert(UndavHashTable::HashTable* hashTable, char* key, Record* value, int wrongIndex);

int GetFirstHashIndex(UndavHashTable::HashTable* hashTable, const char* key){
	return Hash(hashTable->firstUniversalHashing, key, (Size(hashTable) + 1)/2);
}

int GetSecondHashIndex(UndavHashTable::HashTable* hashTable, const char* key){
	return (Size(hashTable) + 1)/2 + Hash(hashTable->secondUniversalHashing, key, Size(hashTable)/2);
}

int GetKeyIndex(UndavHashTable::HashTable* hashTable, const char* key){
	int firstHashIndex = GetFirstHashIndex(hashTable, key);
	int secondHashIndex = GetSecondHashIndex(hashTable, key);
	if(IsEqual(hashTable->keys[firstHashIndex], key)) return firstHashIndex;
	else if(IsEqual(hashTable->keys[secondHashIndex], key)) return secondHashIndex;
	else return -1;
}

void Insert(UndavHashTable::HashTable* hashTable, char* key, Record* value, int wrongIndex){
	int index;
	int firstHashIndex = GetFirstHashIndex(hashTable, key);
	int secondHashIndex = GetSecondHashIndex(hashTable, key);
	if(IsEqual(hashTable->keys[firstHashIndex], key)) hashTable->values[firstHashIndex] = value;
	else if(IsEqual(hashTable->keys[secondHashIndex], key)) hashTable->values[secondHashIndex] = value;
	else if(hashTable->length < hashTable->size) {
		if(hashTable->keys[firstHashIndex] == NULL || hashTable->keys[secondHashIndex] == NULL){
			index = (hashTable->keys[firstHashIndex] == NULL) ? firstHashIndex : secondHashIndex;
			hashTable->keys[index] = key;
			hashTable->values[index] = value;
			hashTable->length++;
		} else {
			index = (wrongIndex == firstHashIndex) ? secondHashIndex : firstHashIndex;
			char* reinsertionKey = hashTable->keys[index];
			Record* reinsertionValue = hashTable->values[index];
			hashTable->keys[index] = key;
			hashTable->values[index] = value;
			Insert(hashTable, reinsertionKey, reinsertionValue, index);
		}
	}
}

UndavHashTable::HashTable* UndavHashTable::Create(int size){
	HashTable* newHashTable = new HashTable;
	newHashTable->length = 0;
	newHashTable->keys = new char*[size];
	newHashTable->values = new Record*[size];
	for(int index = 0; index < size; index++){
		newHashTable->keys[index] = NULL;
		newHashTable->values[index] = NULL;
	}
	newHashTable->size = size;
	newHashTable->graph = CreateDirectedGraph(size);
	newHashTable->firstUniversalHashing = UndavUniversalHashing::Create();
	newHashTable->secondUniversalHashing = UndavUniversalHashing::Create();
	return newHashTable;
}

void UndavHashTable::Add(HashTable* hashTable, const char* key, Record* value){
	int firstHashIndex = GetFirstHashIndex(hashTable, key);
	int secondHashIndex = GetSecondHashIndex(hashTable, key);
	if(!AreAdjacent(hashTable->graph, firstHashIndex, secondHashIndex))
		Connect(hashTable->graph, firstHashIndex, secondHashIndex);
	Insert(hashTable, CreateCopy(key), value, secondHashIndex);
}

void UndavHashTable::Remove(HashTable* hashTable, const char* key){
	int index = GetKeyIndex(hashTable, key);
	if(index != -1)
	{
		int firstHashIndex = GetFirstHashIndex(hashTable, key);
		int secondHashIndex = GetSecondHashIndex(hashTable, key);
		DestroyCopy(hashTable->keys[index]);
		hashTable->keys[index] = NULL;
		hashTable->values[index] = NULL;
		hashTable->length--;
		Disconnect(hashTable->graph, firstHashIndex, secondHashIndex);
	}
}

Record* UndavHashTable::Get(HashTable* hashTable, const char* key){
	int index = GetKeyIndex(hashTable, key);
	return (index != -1) ? hashTable->values[index] : NULL;
}

bool UndavHashTable::Contains(HashTable* hashTable, const char* key){
	int index = GetKeyIndex(hashTable, key);
	return (index != -1) ? true : false;
}

int UndavHashTable::Length(const HashTable* hashTable){
	return hashTable->length;
}

int UndavHashTable::Size(const HashTable* hashTable){
	return hashTable->size;
}

void UndavHashTable::Destroy(HashTable* hashTable){
	for(int index = 0; index < Size(hashTable) && Length(hashTable) != 0; index++){
		if(hashTable->keys[index] != NULL){
			DestroyCopy(hashTable->keys[index]);
			hashTable->length--;
		}
	}
	delete hashTable->keys;
	delete hashTable->values;
	DestroyGraph(hashTable->graph);
	UndavUniversalHashing::Destroy(hashTable->firstUniversalHashing);
	UndavUniversalHashing::Destroy(hashTable->secondUniversalHashing);
	delete hashTable;
}
