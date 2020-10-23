/***************************************************
Copyright (c) 2018 Luis Llamas
(www.luisllamas.es)

Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file except in compliance with the License. You may obtain a copy of the License at http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software distributed under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the License for the specific language governing permissions and limitations under the License
 ****************************************************/
 
// ParserLib.h

#ifndef _PARSERLIB_h
#define _PARSERLIB_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

// Callbacks definitions
typedef void(*ParserCallback)();
typedef void(*ParserCallbackBool)(bool data);
typedef void(*ParserCallbackChar)(char data);
typedef void(*ParserCallbackByte)(byte data);
typedef void(*ParserCallbackUint8)(uint8_t data);
typedef void(*ParserCallbackUint16)(uint16_t data);
typedef void(*ParserCallbackUint32)(uint32_t data);
typedef void(*ParserCallbackInt8)(int8_t data);
typedef void(*ParserCallbackInt16)(int16_t data);
typedef void(*ParserCallbackInt32)(int32_t data);
typedef void(*ParserCallbackFloat)(float data);
typedef void(*ParserCallbackCharArray)(char* data, size_t length);
typedef void(*ParserCallbackString)(String &data);
typedef bool(*ParserCondition)();
typedef bool(*ParserCriterion)(byte data);

class Parser
{
public:
	Parser(size_t default_command_length = 5);
	Parser(String& buffer, size_t default_command_length = 5);
	Parser(byte* buffer, size_t bufferLength, size_t default_command_length = 5);
	Parser(char* buffer, size_t bufferLength, size_t default_command_length = 5);


	void Init(char* buffer, size_t bufferLength, size_t default_command_length = 5);
	void Init(byte* buffer, size_t bufferLength, size_t default_command_length = 5);
	void Init(String& buffer, size_t default_command_length = 5);

	size_t DEFAULT_COMMAND_LENGTH;
	size_t CurrentIndex;
	char* CurrentItemPointer();
	char CurrentItem();
	void Reset();
	inline bool IsBufferOverflow();

	// Read methods
	bool	  Read_Bool(ParserCallbackBool callback = nullptr);
	char     Read_Char(ParserCallbackChar callback = nullptr);
	byte     Read_Byte(ParserCallbackByte callback = nullptr);
	int8_t   Read_Int8(ParserCallbackInt8 callback = nullptr);
	int16_t  Read_Int16(ParserCallbackInt16 callback = nullptr);
	int32_t  Read_Int32(ParserCallbackInt32 callback = nullptr);
	uint8_t  Read_Uint8(ParserCallbackUint8 callback = nullptr);
	uint16_t Read_Uint16(ParserCallbackUint16 callback = nullptr);
	uint32_t Read_Uint32(ParserCallbackUint32 callback = nullptr);

	float Read_Float(ParserCallbackFloat callback = nullptr);
	float Read_UnsignedFloat(ParserCallbackFloat callback = nullptr);

	size_t Read_CharArray(char separator, ParserCallbackCharArray callback = nullptr);
	size_t Read_CharArray(ParserCriterion criterion, ParserCallbackCharArray callback = nullptr);
	size_t Read_CharArray(char separator, bool endIfNotFound, ParserCallbackCharArray callback = nullptr);
	size_t Read_CharArray(ParserCriterion criterion, bool endIfNotFound, ParserCallbackCharArray callback = nullptr);

	String Read_String(char separator, ParserCallbackString callback = nullptr);
	String Read_String(ParserCriterion criterion, ParserCallbackString callback = nullptr);
	String Read_String(char separator, bool endIfNotFound, ParserCallbackString callback = nullptr);
	String Read_String(ParserCriterion criterion, bool endIfNotFound, ParserCallbackString callback = nullptr);


	// Compare methods
	bool Compare(char token, ParserCallback callback = nullptr);
	bool Compare(char token[], ParserCallback callback = nullptr);
	bool Compare(char token[], size_t max_length, ParserCallback callback = nullptr);
	bool Compare(String token, ParserCallback callback = nullptr);
	bool Compare(ParserCriterion comparision, ParserCallback callback = nullptr);

	// Search methods
	bool Search(char token, ParserCallback callback = nullptr);
	bool Search(char token[], ParserCallback callback = nullptr);
	bool Search(char token[], size_t max_length, ParserCallback callback = nullptr);
	bool Search(String token, ParserCallback callback = nullptr);
	bool Search(ParserCriterion criterion, ParserCallback callback = nullptr);

	// Loop-if methods
	bool IfCurrentIs(char token, ParserCallback yesCallback = nullptr, ParserCallback noCallback = nullptr);
	bool IfCurrentIs(ParserCriterion criterion, ParserCallback yesCallback = nullptr, ParserCallback noCallback = nullptr);
	bool IfCurrentIsNot(char token, ParserCallback yesCallback = nullptr, ParserCallback noCallback = nullptr);
	bool IfCurrentIsNot(ParserCriterion criterion, ParserCallback yesCallback = nullptr, ParserCallback noCallback = nullptr);
	void DoUntil(ParserCondition condition, ParserCallback callback = nullptr, ParserCallback finally = nullptr);
	void DoWhile(ParserCondition condition, ParserCallback callback = nullptr, ParserCallback finally = nullptr);

	// Skip methods
	void Skip(size_t num_items);
	void SkipWhile(char item);
	void SkipWhile(ParserCriterion comparision);
	void SkipUntil(char item);
	void SkipUntil(ParserCriterion comparision);

	// Jump methods
	void JumpAfter(char item);
	void JumpAfter(ParserCriterion comparision);
	void JumpTo(char item);
	void JumpTo(ParserCriterion comparision);


	// Comparision static methods
	static bool IsPrintable(byte item);
	static bool IsAlfaNumeric(byte Item);
	static bool IsNotDigit(byte Item);
	static bool IsDigit(byte item);
	static bool IsNumeric(byte item);
	static bool IsLetter(byte item);
	static bool IsNotLetter(byte item);
	static bool IsUpperCaseLetter(byte item);
	static bool IsLowercasaLetter(byte item);
	static bool IsSymbol(byte item);
	static bool IsSeparator(byte item);
	static bool IsNewLine(byte item);
	static bool IsCarriageReturn(byte item);
	static bool IsSeparatorOrNewLine(byte item);

protected:
	byte* _buffer;
	size_t _bufferLength;
	inline void increaseIndex();
	inline bool compare(char* str1, char* str2, size_t n);

	template <class T_int>
	T_int readInteger();

	template <class T_uint>
	T_uint readUnsignedInteger();
};

#endif

template<class T_int>
T_int Parser::readInteger()
{
	T_int rst = 0;

	bool isNegative = false;
	if (_buffer[CurrentIndex] == '-')
	{
		isNegative = true;
		CurrentIndex++;
	}

	while (CurrentIndex < _bufferLength)
	{
		char incomingChar = _buffer[CurrentIndex];
		if (incomingChar >= '0' && incomingChar <= '9')
			rst = (rst * 10) + (incomingChar - '0');

		else
			break;

		CurrentIndex++;
	}
	return isNegative ? -rst : rst;
}

template<class T_uint>
inline T_uint Parser::readUnsignedInteger()
{
	T_uint rst = 0;

	while (CurrentIndex < _bufferLength)
	{
		char incomingChar = _buffer[CurrentIndex];

		if (incomingChar >= '0' && incomingChar <= '9')
			rst = (rst * 10) + (incomingChar - '0');

		else
			break;

		CurrentIndex++;
	}
	return rst;
}
