#include "String.h"
#include <cstring>
#include <stdlib.h>

void Copy(const char* origin, char* destination)
{
	while(*destination++ = *origin++);
}

char* UndavString::CreateCopy(const char* string)
{
	int size = CountCharacters(string) + 1;
	char* auxiliary = new char[size];
	Copy(string, auxiliary);
	return auxiliary;
}

int UndavString::CountApparitions(const char* string, char c)
{
	int amount = 1;
	for(; *string != '\0'; string++)
	{
		if(*string == c)
		{
			amount++;
		}
	}
	return amount;
}


int UndavString::CountCharacters(const char* string)
{
	int charactersCount = 0;
	while(*string != '\0')
	{
		charactersCount++;
		string++;
	}
	return charactersCount;
}

void UndavString::DestroyCopy(char* string)
{
	delete &string;
}

int UndavString::CountUntilToken(const char* string, unsigned int initialPosition , char token)
{
	int fragmentLenghtCount = 0;
	while(string[initialPosition] != token && string[initialPosition] != '\0')
	{
		fragmentLenghtCount++;
		initialPosition++;
	}
	return fragmentLenghtCount;
}

char* UndavString::CopyUntilLength(const char* string, int length)
{
	char* newString = new char[length + 1];
	for(int index = 0; index < length; index++){
		newString[index] = *string++;
	}
	newString[length] = '\0';
	return newString;
}

bool UndavString::IsNumber(const char* string){
	int size = UndavString::CountCharacters(string);
	bool isNumber = true;
	for(int index = 0; index < size && isNumber; index++){
		isNumber = ((string[index]>='0') && (string[index]<='9'));
	}
	return isNumber;
}

int UndavString::ConvertToInt(const char* string){
	return atoi(string);
}

enum CompareResult {LESSER, GREATER, EQUAL};

CompareResult CompareSizes(const char* stringOne, const char* stringTwo){
	int sizeOne = UndavString::CountCharacters(stringOne);
	int sizeTwo = UndavString::CountCharacters(stringTwo);
	if (sizeOne < sizeTwo) return LESSER;
	else if (sizeOne > sizeTwo) return GREATER;
	else return EQUAL;
}

CompareResult CompareStrings(const char* stringOne, const char* stringTwo){
	int stringCompare = strcmp(stringOne, stringTwo);
	if(stringCompare == 0) return EQUAL;
	else if (stringCompare < 0) return LESSER;
	else return GREATER;
}

bool UndavString::IsLesser(const char* stringOne, const char* stringTwo){
	return (stringOne != NULL && stringTwo != NULL) ? CompareStrings(stringOne, stringTwo) == LESSER : false;
}

bool UndavString::IsGreater(const char* stringOne, const char* stringTwo){
	return (stringOne != NULL && stringTwo != NULL) ? CompareStrings(stringOne, stringTwo) == GREATER : false;
}

bool UndavString::IsEqual(const char* stringOne, const char* stringTwo){
	return (stringOne != NULL && stringTwo != NULL) ? CompareStrings(stringOne, stringTwo) == EQUAL : false;
}
