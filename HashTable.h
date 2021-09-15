#ifndef HASHTABLE_H_
#define HASHTABLE_H_

#include "Record.h"
using UndavRecord::Record;

namespace UndavHashTable{
	struct HashTable;

	//Precondicion: Ninguna
	//Postcondicion: Devuelve una instancia valida que representa una tabla de hashing que tiene un espacio de direcciones fijo igual a @size
	HashTable* Create(int size = 127);

	//Precondicion: @hashTable es una instancia valida
	//Postcondicion: Si existe @key reemplaza el valor asociado por @value. Si no existe @key y hay espacio disponible agrega @value asociado a la @key.
	//Si no hay espacio disponible no realiza ninguna accion
	void Add(HashTable* hashTable, const char* key, Record* value);

	//Precondicion: @hashTable es una instancia valida
	//Postcondicion: Si existe @key elimina de @hashTable el par key-value
	void Remove(HashTable* hashTable, const char* key);

	//Precondicion: @hashTable es una instancia valida
	//Postcondicion: Si existe @key en @hashTable devuelve el valor asociado. Caso contrario devuelve NULL
	Record* Get(HashTable* hashTable, const char* key);

	//Precondicion: @hashTable es una instancia valida
	//Postcondicion: Si existe @key en @hashTable devuelve true. Caso contrario devuelve false
	bool Contains(HashTable* hashTable, const char* key);

	//Precondicion: @hashTable es una instancia valida
	//Postcondicion: Devuelve la cantidad de pares key-value que hay en @hashTable
	int Length(const HashTable* hashTable);

	//Precondicion: @hashTable es una instancia valida
	//Postcondicion: Devuelve la capacidad de direcciones de @hashTable
	int Size(const HashTable* hashTable);

	//Precondicion: @hashTable es una instancia valida
	//Postcondicion: Libera todos los recursos asociados a @hashTable
	void Destroy(HashTable* hashTable);
}

#endif
