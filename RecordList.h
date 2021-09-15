#ifndef RECORDLIST_H_
#define RECORDLIST_H_

#include "Record.h"
using UndavRecord::Record;

namespace UndavRecordList{
	struct RecordList;

	//Precondicion: Ninguna
	//Postcondicion: Devuelve una instancia valida que representa una lista de items de tipo Record que esta vacia
	RecordList* Create();

	//Precondicion: @list es una instancia valida
	//Postcondicion: Agrega @item a @list
	void Add(RecordList* list, Record* item);

	//Precondicion: @list es una instancia valida
	//Postcondicion: Devuelve la cantidad de items de @list
	int Length(const RecordList* list);

	//Precondicion: @list es una instancia valida
	//Postcondicion: Ordena @list utilizando la clave de registro UndavRecord::GetKey utilizando un metodo de ordenamiento estable
	void Sort(RecordList* list);

	//Precondicion: @list es una instancia valida
	//Postcondicion: modifica @list dejando de reversa todos los items de @list
	void Reverse(RecordList* list);

	namespace Iterator{
		struct RecordIterator;

		//Precondicion: @list es una instancia valida
		//Postcondicion: Devuelve una instancia valida de RecordIterator que apunta al primer nodo de @list
		RecordIterator* Begin(RecordList* list);

		//Precondicion: @iterator es una instancia valida
		//Postcondicion: Si @iterator apunta al final de la lista devuelve true, caso contrario devuelve false
		bool IsEnd(const RecordIterator* iterator);

		//Precondicion: @iterator es una instancia valida
		//Postcondicion: Avanza, siempre que pueda, @iterator al siguiente nodo de la lista
		void Next(RecordIterator* iterator);

		//Precondicion: @iterator es una instancia valida
		//Postcondicion: Devuelve el item al que apunta @iterator. Si @iterator apunta al final de la lista devuelve NULL
		Record* GetItem(RecordIterator* iterator);

		//Precondicion: @iterator es una instancia valida
		//Postcondicion: Libera todos los recursos asociados a @iterator
		void Destroy(RecordIterator* iterator);
	}

	//Precondicion: @list es una instancia valida
	//Postcondicion: Libera todos los recursos asociados a @list
	void Destroy(RecordList* list);
}

#endif
