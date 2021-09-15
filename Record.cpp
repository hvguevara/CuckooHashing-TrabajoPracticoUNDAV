#include "Record.h"
#include "String.h"
#include <iostream>

using namespace UndavRecord;
using namespace UndavString;

struct UndavRecord::Record{
	int fieldCount;
	char** fields;
	int key;
};

void SetFields(Record* newRecord, char* csvRecord);

Record* UndavRecord::Create(char* csvRecord, int keyFieldPosition)
{
	Record* newRecord = new Record;
	newRecord->fieldCount = CountApparitions(csvRecord, ',');
	SetFields(newRecord, csvRecord);
	if(newRecord->fieldCount > keyFieldPosition){
		newRecord->key = keyFieldPosition;
	}else{
		newRecord->key = 0;
	}
	return newRecord;
}

int UndavRecord::GetFieldCount(const Record* record)
{
	return record->fieldCount;
}

const char* UndavRecord::GetFieldValue(const Record* record, int fieldPosition)
{
	if(GetFieldCount(record) > fieldPosition){
		return record->fields[fieldPosition];
	}else{
		return NULL;
	}
}

const char* UndavRecord::GetKey(const Record* record)
{
	return record->fields[record->key];
}

void UndavRecord::Destroy(Record* record)
{
	for(int fieldPosition = 0; fieldPosition < GetFieldCount(record); fieldPosition++)
	{
		delete record->fields[fieldPosition];
	}
	delete record->fields;
	delete record;
}

void SetFields(Record* newRecord, char* csvRecord)
{
	newRecord->fields = new char*[(newRecord->fieldCount)];
	int initialFieldPosition = 0;
	for(int fieldNumber = 0; fieldNumber < newRecord->fieldCount; fieldNumber++)
	{
		int fieldLength = CountUntilToken(csvRecord, initialFieldPosition, ',');
		newRecord->fields[fieldNumber] = CopyUntilLength(&csvRecord[initialFieldPosition], fieldLength);
		initialFieldPosition += (fieldLength + 1);
	}
}

bool UndavRecord::IsLesser(const Record* recordOne, const Record* recordTwo){
	if(IsNumber(GetKey(recordOne)) && IsNumber(GetKey(recordTwo))){
		int keyOne = ConvertToInt(GetKey(recordOne));
		int keyTwo = ConvertToInt(GetKey(recordTwo));
		return keyOne < keyTwo;
	} else {
		return UndavString::IsLesser(GetKey(recordOne), GetKey(recordTwo));
	}
}

bool UndavRecord::IsGreater(const Record* recordOne, const Record* recordTwo){
	if(IsNumber(GetKey(recordOne)) && IsNumber(GetKey(recordTwo))){
		int keyOne = ConvertToInt(GetKey(recordOne));
		int keyTwo = ConvertToInt(GetKey(recordTwo));
		return keyOne > keyTwo;
	} else {
		return UndavString::IsGreater(GetKey(recordOne), GetKey(recordTwo));
	}
}

bool UndavRecord::IsEqual(const Record* recordOne, const Record* recordTwo){
	if(IsNumber(GetKey(recordOne)) && IsNumber(GetKey(recordTwo))){
		int keyOne = ConvertToInt(GetKey(recordOne));
		int keyTwo = ConvertToInt(GetKey(recordTwo));
		return keyOne == keyTwo;
	} else {
		return UndavString::IsEqual(GetKey(recordOne), GetKey(recordTwo));
	}
}
