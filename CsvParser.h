#ifndef CSVPARSER_H_
#define CSVPARSER_H_

//#include "Record.h"
//using UndavRecord::Record;

#include "RecordList.h"
using UndavRecordList::RecordList;

namespace UndavCsvParser {

	/*
	* Precondicion: @csvFileContent es una cadena de caracteres en formato csv donde el separador de registros es \n y el separador de campos es ,
	* @keyFieldPosition es un numero de campo valido
	* Postcondicion: Devuelve una lista con los registros de @csvFileContent
	*/
	RecordList* GetRecords(const char* csvFileContent, int keyFieldPosition = 0);
}

#endif
