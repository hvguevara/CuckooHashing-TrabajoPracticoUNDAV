#ifndef STRING_H_
#define STRING_H_

namespace UndavString{

	/*
	* Precondicion: @string es una cadena de caracteres
	* Postcondcion: Crea y devuelve una copia de @string
	*/
	char* CreateCopy(const char* string);

	/*
	* Precondicion: @string es una cadena de caracteres
	* Postcondcion: Devuelve la cantidad de apariciones de @c en @string
	*/
	int CountApparitions(const char* string, char c);


	/*
	* Precondicion: @string es una cadena de caracteres
	* Postcondcion: Devuelve la cantidad de caracteres de @string
	*/
	int CountCharacters(const char* string);

	/*
	* Precondicion: @string es una cadena de caracteres y @givenCharacter es un caracter
	* Postcondcion: Devuelve la cantidad de caracteres de @string desde @initialPosition
	* hasta que encuentre @givenCharacter
	*/
	int CountUntilToken(const char* string, unsigned int initialPosition , char token);

	/*
	* Precondicion: @string es una cadena de caracteres y @length una longitud valida
	* Postcondcion: Devuelve una copia de @string con la longitud solicitada
	*/
	char* CopyUntilLength(const char* string, int length);

	/*
	* Precondicion: @stringOne y @stringTwo son cadenas de caracteres
	* Postcondcion: Devuelve true si @stringOne es menor alfabeticamente que stringTwo. Caso contrario devuelve false
	*/
	bool IsLesser(const char* stringOne, const char* stringTwo);

	/*
	* Precondicion: @stringOne y @stringTwo son cadenas de caracteres
	* Postcondcion: Devuelve true si @stringOne es mayor alfabeticamente que stringTwo. Caso contrario devuelve false
	*/
	bool IsGreater(const char* stringOne, const char* stringTwo);

	/*
	* Precondicion: @stringOne y @stringTwo son cadenas de caracteres
	* Postcondcion: Devuelve true si @stringOne es igual alfabeticamente que stringTwo. Caso contrario devuelve false
	*/
	bool IsEqual(const char* stringOne, const char* stringTwo);

	/*
	* Precondicion: @string es una cadena de caracteres
	* Postcondcion: Devuelve true si @string es un numero. Caso contrario devuelve false
	*/
	bool IsNumber(const char* string);

	/*
	* Precondicion: @string es una cadena de caracteres que representa un numero
	* Postcondcion: Convierte @string a int y lo devuelve
	*/
	int ConvertToInt(const char* string);

	/*
	* Precondicion: @string es una cadena de caracteres
	* Postcondcion: Destruye la copia de @string
	*/
	void DestroyCopy(char* string);
}

#endif
