#include "CsvParser.h"
#include "RecordList.h"
#include "Record.h"
#include "String.h"

using UndavRecordList::RecordList;
using UndavRecordList::Create;
using UndavRecordList::Add;
using UndavRecord::Record;
using UndavRecord::Create;
using namespace UndavString;


RecordList* UndavCsvParser::GetRecords(const char* csvFileContent, int keyFieldPosition){
	int recordsCount = CountApparitions(csvFileContent, '\n');
	RecordList* newRecordList = Create();
	int initialRecordPosition = 0;
	for(int recordNumber = 0; recordNumber < recordsCount; recordNumber++)
	{
		int recordLength = CountUntilToken(csvFileContent, initialRecordPosition , '\n');
		char* newRecord = CopyUntilLength(&csvFileContent[initialRecordPosition], recordLength);
		Add(newRecordList, Create(newRecord, keyFieldPosition));
		delete newRecord;
		initialRecordPosition += (recordLength + 1);
	}
	return newRecordList;
};
