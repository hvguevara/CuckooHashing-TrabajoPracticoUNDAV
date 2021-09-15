#include <iostream>
#include "HashTable.h"
#include "CsvParser.h"
#include "Record.h"
#include "RecordList.h"

using std::cout;
using std::endl;
using UndavRecordList::RecordList;
using UndavHashTable::HashTable;
using namespace UndavRecordList::Iterator;
using namespace UndavCsvParser;
using namespace UndavRecord;

void ExecuteRecordListDemo(UndavRecordList::RecordList* records);
void ExecuteHashTableDemo(UndavRecordList::RecordList* records);
void Show(UndavRecordList::RecordList* records);
void Show(const Record* record);
void AddRecords(HashTable *symbolTable, UndavRecordList::RecordList *records);
void Show(HashTable *symbolTable, char keys[][3], int count);
void DestroyItems(UndavRecordList::RecordList* records);
/*
CountApparitions correcion, miente porque inicia en 1.

No hacer descomposición funcional cuando no es necesario

Buscar NaturalMerge - Ordenamiento , esta en Bottom UP
bensh up

optimizacion del mergeSort

en record utilizar una funcion Compare en IsLesser etc

leer:
-Refactoring -> Fowler: extract method
-Introduction to algorithms
-Donals Knuth- the art of computer programming
 */
int main()
{
	char* csvFileContent = "8,Espada\n9,Espada\n1,Espada\n2,Espada\n4,Espada\n10,Espada\n11,Espada\n12,Espada\n3,Espada\n5,Espada\n8,Espada\n9,Espada\n1,Espada\n2,Espada\n4,Espada\n10,Espada\n11,Espada\n12,Espada\n3,Espada\n5,Espada";
	//char* csvFileContent = "Argentina,AR\nEcuador,EC\nBrasil,BR\nBolivia,BO\nChile,CH\nColombia,CO\nPeru,PE\nParaguay,PA\nUruguay,UR\nVenezuela,VE";
	UndavRecordList::RecordList* records = GetRecords(csvFileContent);
	ExecuteRecordListDemo(records);
	ExecuteHashTableDemo(records);
	DestroyItems(records);
	Destroy(records);
    return 0;
}

void AddRecords(HashTable *symbolTable, UndavRecordList::RecordList *records) {
	RecordIterator *iterator = Begin(records);
	while (!IsEnd(iterator)) {
		Record *item = GetItem(iterator);
		UndavHashTable::Add(symbolTable, GetKey(item), item);
		Next(iterator);
	}
	Destroy(iterator);
}

void ExecuteHashTableDemo(UndavRecordList::RecordList* records){
	cout<<"Demo de Hash Table:"<<endl;
	cout<<"Cargando todas las cartas en la tabla de hashing...";
	HashTable* symbolTable = UndavHashTable::Create();
	AddRecords(symbolTable, records);
	char m[20][3] = {"1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12", "13", "14", "15", "16", "17", "18","19", "20"};
	//char m[13][13] = {"Argentina", "Uruguay", "Bolivia", "Brasil", "Chile", "Colombia", "Ecuador", "Paraguay", "Peru", "Venezuela", "Papua", "Grecia", "Germania"};
	//char m[13][13] = {"AR", "UR", "BO", "BR", "CH", "CO", "EC", "PA", "PE", "VE", "PP", "GR", "GE"};
	//UndavHashTable::Remove(symbolTable, "10");
	Show(symbolTable, m, 20);
	Destroy(symbolTable);
}

void ExecuteRecordListDemo(UndavRecordList::RecordList* records){
	cout<<"Demo de record List:"<<endl;
	Show(records);
	cout<<endl;
	cout<<"Lista ordenada:"<<endl;
	Sort(records);
	Show(records);
	cout<<endl;
	cout<<"Lista inversa:"<<endl;
	Reverse(records);
	Show(records);
	cout<<endl;
}

void Show(HashTable *symbolTable, char keys[][3], int count){
	cout<<"Cantidad de elementos de la tabla de hashing: "<<UndavHashTable::Length(symbolTable)<<endl;
	for(int i=0; i<count; ++i){
		Record* record = UndavHashTable::Get(symbolTable, keys[i]);
		cout<<keys[i]<<" -> ";
		if(record == NULL){
			cout<<"NULL";
		}else{
			Show(record);
		}
		cout<<endl;
	}
}

void Show(UndavRecordList::RecordList* records){
	RecordIterator* iterator = Begin(records);
	while(!IsEnd(iterator)){
		Record* item = GetItem(iterator);
		Show(item);
		cout<<"->";
		Next(iterator);
	}
	cout<<"NULL";
	Destroy(iterator);
}

void Show(const Record* record) {
    if (GetFieldCount(record) > 0) {
        cout << GetFieldValue(record, 0);
        for (int recordNumber = 1; recordNumber < GetFieldCount(record);++recordNumber) {
            cout << "," << GetFieldValue(record, recordNumber);
        }
    }
}

void DestroyItems(UndavRecordList::RecordList* records){
	RecordIterator* iterator = Begin(records);
	while(!IsEnd(iterator)){
		Record* item = GetItem(iterator);
		Destroy(item);
		Next(iterator);
	}
	Destroy(iterator);
}
