/***************************************************
Copyright (c) 2018 Luis Llamas
(www.luisllamas.es)

Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file except in compliance with the License. You may obtain a copy of the License at http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software distributed under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the License for the specific language governing permissions and limitations under the License
 ****************************************************/
 
#include "ParserLib.h"

Parser::Parser(size_t default_command_length)
{
}

Parser::Parser(String & buffer, size_t default_command_length)
{
	Init(buffer, DEFAULT_COMMAND_LENGTH);
}

Parser::Parser(byte* buffer, size_t bufferLength, size_t default_command_length)
{
	Init(buffer, bufferLength, DEFAULT_COMMAND_LENGTH);
}

Parser::Parser(char * buffer, size_t bufferLength, size_t default_command_length)
{
	Init(buffer, bufferLength, DEFAULT_COMMAND_LENGTH);
}

void Parser::Init(byte * buffer, size_t bufferLength, size_t default_command_length)
{
	_buffer = buffer;
	_bufferLength = bufferLength;
	DEFAULT_COMMAND_LENGTH = 5;
	CurrentIndex = 0;
}

void Parser::Init(char * buffer, size_t bufferLength, size_t default_command_length)
{
	_buffer = (byte*)buffer;
	_bufferLength = bufferLength;
	DEFAULT_COMMAND_LENGTH = 5;
	CurrentIndex = 0;
}


void Parser::Init(String& buffer, size_t default_command_length)
{
	Init((char*)buffer.c_str(), buffer.length());
}


char * Parser::CurrentItemPointer()
{
	return (char*)_buffer + CurrentIndex;
}

char Parser::CurrentItem()
{
	if (IsBufferOverflow()) return '\0';
	return (char)_buffer[CurrentIndex];
}

void Parser::Reset()
{
	CurrentIndex = 0;
}

inline bool Parser::IsBufferOverflow()
{
	return CurrentIndex >= _bufferLength;
}


// Read methods
bool Parser::Read_Bool(ParserCallbackBool callback)
{
	char rst = CurrentItem();
	if (rst == '1')
	{
		if (callback != nullptr) callback(true);
		return true;
	}
	if (rst == '0')
	{
		if (callback != nullptr) callback(false);
		return false;
	}
	return false;
}

char Parser::Read_Char(ParserCallbackChar callback)
{
	char rst = CurrentItem();
	increaseIndex();
	return rst;
}

byte Parser::Read_Byte(ParserCallbackByte callback)
{
	byte rst = CurrentItem();
	increaseIndex();
	return rst;
}

int8_t Parser::Read_Int8(ParserCallbackInt8 callback)
{
	bool valid = Parser::IsNumeric(CurrentItem());
	if (!valid) return 0;

	int8_t data = readInteger<int8_t>();
	if (callback != nullptr) callback(data);
	return data;
}

int16_t Parser::Read_Int16(ParserCallbackInt16 callback)
{
	bool valid = Parser::IsNumeric(CurrentItem());
	if (!valid) return 0;

	int16_t data = readInteger<int16_t>();
	if (callback != nullptr) callback(data);
	return data;
}

int32_t Parser::Read_Int32(ParserCallbackInt32 callback)
{
	bool valid = Parser::IsNumeric(CurrentItem());
	if (!valid) return 0;

	int32_t data = readInteger<int32_t>();
	if (callback != nullptr) callback(data);
	return data;
}

uint8_t Parser::Read_Uint8(ParserCallbackUint8 callback)
{
	bool valid = Parser::IsDigit(CurrentItem());
	if (!valid) return 0;

	uint8_t data = readUnsignedInteger<uint8_t>();
	if (callback != nullptr) callback(data);
	return data;
}

uint16_t Parser::Read_Uint16(ParserCallbackUint16 callback)
{
	bool valid = Parser::IsDigit(CurrentItem());
	if (!valid) return 0;

	uint16_t data = readUnsignedInteger<uint16_t>();
	if (callback != nullptr) callback(data);
	return data;
}

uint32_t Parser::Read_Uint32(ParserCallbackUint32 callback)
{
	bool valid = Parser::IsDigit(CurrentItem());
	if (!valid) return 0;

	uint32_t data = readUnsignedInteger<uint32_t>();
	if (callback != nullptr) callback(data);
	return data;
}

float Parser::Read_Float(ParserCallbackFloat callback)
{
	bool valid = Parser::IsNumeric(CurrentItem());
	if (!valid) return 0;

	float data = 0;
	int dataReal = 0;
	int dataDecimal = 0;
	int dataPow = 1;
	bool isDecimalStage = false;

	bool isNegative = false;
	if (_buffer[CurrentIndex] == '-')
	{
		isNegative = true;
		CurrentIndex++;
	}


	while (CurrentIndex < _bufferLength)
	{
		char incomingChar = _buffer[CurrentIndex];

		if (incomingChar == '.' || incomingChar == ',')
			isDecimalStage = true;

		else if (incomingChar >= '0' && incomingChar <= '9')
		{
			if (isDecimalStage == false)
				dataReal = (dataReal * 10) + (incomingChar - '0');
			else
			{
				dataDecimal = (dataDecimal * 10) + (incomingChar - '0');
				dataPow *= 10;
			}
		}
		else
			break;

		CurrentIndex++;
	}

	data = (float)dataReal + (float)dataDecimal / dataPow;
	data = isNegative ? -data : data;

	if (callback != nullptr) callback(data);
	return data;
}

float Parser::Read_UnsignedFloat(ParserCallbackFloat callback)
{
	bool valid = Parser::IsNumeric(CurrentItem());
	if (!valid) return 0;

	float data = 0;
	int dataReal = 0;
	int dataDecimal = 0;
	int dataPow = 1;
	bool isDecimalStage = false;

	while (CurrentIndex < _bufferLength)
	{
		char incomingChar = _buffer[CurrentIndex];

		if (incomingChar == '.' || incomingChar == ',')
			isDecimalStage = true;

		else if (incomingChar >= '0' && incomingChar <= '9')
		{
			if (isDecimalStage == false)
				dataReal = (dataReal * 10) + (incomingChar - '0');
			else
			{
				dataDecimal = (dataDecimal * 10) + (incomingChar - '0');
				dataPow *= 10;
			}
		}
		else
			break;

		CurrentIndex++;
	}

	data = (float)dataReal + (float)dataDecimal / dataPow;

	if (callback != nullptr) callback(data);
	return data;
}

size_t Parser::Read_CharArray(char separator, ParserCallbackCharArray callback)
{
	return Read_CharArray(separator, true, callback);

}

size_t Parser::Read_CharArray(ParserCriterion criterion, ParserCallbackCharArray callback)
{
	return Read_CharArray(criterion, true, callback);
}

size_t Parser::Read_CharArray(char separator, bool endIfNotFound, ParserCallbackCharArray callback)
{
	size_t length = 0;
	bool found = false;

	char* start = CurrentItemPointer();
	while (CurrentIndex + length < _bufferLength)
	{
		if (_buffer[CurrentIndex + length] == separator)
		{
			found = true;
			break;
		}
		length++;
	}
	CurrentIndex += length + (found ? 1 : 0);

	if ((endIfNotFound || (!endIfNotFound && found)))
	{
		if (callback != nullptr) callback(start, length);
	}

	return length;
}

size_t Parser::Read_CharArray(ParserCriterion criterion, bool endIfNotFound, ParserCallbackCharArray callback)
{
	size_t length = 0;
	bool found = false;

	char* start = CurrentItemPointer();
	while (CurrentIndex + length < _bufferLength)
	{
		if (criterion(_buffer[CurrentIndex + length]))
		{
			found = true;
			break;
		}
		length++;
	}
	CurrentIndex += length + (found ? 1 : 0);

	if ((endIfNotFound || (!endIfNotFound && found)))
	{
		if (callback != nullptr) callback(start, length);
	}

	return length;
}

String Parser::Read_String(char separator, ParserCallbackString callback)
{
	return Read_String(separator, true, callback);
}

String Parser::Read_String(ParserCriterion criterion, ParserCallbackString callback)
{
	return Read_String(criterion, true, callback);
}

String Parser::Read_String(char separator, bool endIfNotFound, ParserCallbackString callback)
{
	String rst;
	size_t length = 0;
	bool found = false;

	char* start = CurrentItemPointer();
	while (CurrentIndex + length < _bufferLength)
	{
		if (_buffer[CurrentIndex + length] == separator)
		{
			found = true;
			break;
		}
		length++;
	}
	CurrentIndex += length;//+ (found ? 1 : 0);

	if ((endIfNotFound || (!endIfNotFound && found)))
	{
		rst.reserve(length);
		for (size_t i = 0; i < length; i++)
			rst.concat(start[i]);

		if (callback != nullptr) callback(rst);
	}

	return rst;
}

String Parser::Read_String(ParserCriterion criterion, bool endIfNotFound, ParserCallbackString callback)
{
	String rst;
	size_t length = 0;
	bool found = false;

	char* start = CurrentItemPointer();
	while (CurrentIndex + length < _bufferLength)
	{
		if (criterion(_buffer[CurrentIndex + length]))
		{
			found = true;
			break;
		}
		length++;
	}

	CurrentIndex += length;

	if ((endIfNotFound || (!endIfNotFound && found)))
	{
		rst.reserve(length);
		for (size_t i = 0; i < length; i++)
			rst.concat(start[i]);

		if (callback != nullptr) callback(rst);
	}

	return rst;
}


// Compare methods
bool Parser::Compare(char token, ParserCallback callback)
{
	if (CurrentIndex >= _bufferLength) return false;

	bool found = false;
	if (CurrentItem() == token)
	{
		if (callback != nullptr) callback();
		found = true;
	}
	return true;
}

bool Parser::Compare(char token[], ParserCallback callback)
{
	return Compare(token, DEFAULT_COMMAND_LENGTH, callback);
}

bool Parser::Compare(char token[], size_t max_length, ParserCallback callback)
{
	if (CurrentIndex >= _bufferLength) return false;

	bool found = false;
	if (compare((char*)_buffer, token, max_length))
	{

		if (callback != nullptr) callback();
		found = true;
	}
	return found;
}

bool Parser::Compare(String token, ParserCallback callback)
{
	return Compare((char*)token.c_str(), token.length(), callback);
}

bool Parser::Compare(ParserCriterion comparision, ParserCallback callback)
{
	if (CurrentIndex >= _bufferLength) return false;

	bool found = false;
	if (!comparision(CurrentItem()))
	{
		if (callback != nullptr) callback();
		found = true;
	}
	return found;
}

// Search methods
bool Parser::Search(char token, ParserCallback callback)
{
	for (size_t index = CurrentIndex; index < _bufferLength; index++)
	{
		if (_buffer[index] == token)
		{
			if (callback != nullptr) callback();
			return true;
		}
	}
	return false;
}

bool Parser::Search(char token[], ParserCallback callback)
{
	return Search(token, DEFAULT_COMMAND_LENGTH, callback);
}

bool Parser::Search(char token[], size_t max_length, ParserCallback callback)
{
	for (size_t index = CurrentIndex; index < _bufferLength; index++)
	{
		if (compare((char*)_buffer, token, max_length))
		{
			if (callback != nullptr) callback();
			return true;
		}
	}
	return false;
}

bool Parser::Search(String token, ParserCallback callback)
{
	return Search((char*)token.c_str(), token.length(), callback);
}

bool Parser::Search(ParserCriterion comparision, ParserCallback callback)
{
	for (size_t index = CurrentIndex; index < _bufferLength; index++)
	{
		if (comparision(_buffer[index]))
		{
			if (callback != nullptr) callback();
			return true;
		}
	}
	return false;
}


// Loop-if methods
bool Parser::IfCurrentIs(char token, ParserCallback yesCallback, ParserCallback noCallback)
{
	if (CurrentItem() == token)
	{
		if (yesCallback != nullptr) yesCallback();
		return true;
	}
	if (noCallback != nullptr) noCallback();
	return false;
}

bool Parser::IfCurrentIs(ParserCriterion criterion, ParserCallback yesCallback, ParserCallback noCallback)
{
	if (criterion(CurrentItem()))
	{
		if (yesCallback != nullptr) yesCallback();
		return true;
	}
	if (noCallback != nullptr) noCallback();
	return false;
}

bool Parser::IfCurrentIsNot(char token, ParserCallback yesCallback, ParserCallback noCallback)
{
	if (CurrentItem() != token)
	{
		if (yesCallback != nullptr) yesCallback();
		return true;
	}
	if (noCallback != nullptr) noCallback();
	return false;
}

bool Parser::IfCurrentIsNot(ParserCriterion criterion, ParserCallback yesCallback, ParserCallback noCallback)
{
	if (!criterion(CurrentItem()))
	{
		if (yesCallback != nullptr) yesCallback();
		return true;
	}
	if (noCallback != nullptr) noCallback();
	return false;
}

void Parser::DoUntil(ParserCondition condition, ParserCallback callback, ParserCallback finally)
{
	while (!condition())
	{
		if (callback != nullptr) callback();
	}
	if (finally != nullptr) finally();
}

void Parser::DoWhile(ParserCondition condition, ParserCallback callback, ParserCallback finally)
{
	while (condition())
	{
		if (callback != nullptr) callback();
	}
	if (finally != nullptr) finally();
}


// Skip methods
void Parser::Skip(size_t num_items)
{
	CurrentIndex += num_items;

	if (IsBufferOverflow()) CurrentIndex = _bufferLength - 1;

}

void Parser::SkipWhile(char item)
{
	while (!IsBufferOverflow() && CurrentItem() == item)
		CurrentIndex++;

}

void Parser::SkipWhile(ParserCriterion comparision)
{
	while (!IsBufferOverflow() && comparision(CurrentItem()))
		CurrentIndex++;

}

void Parser::SkipUntil(char item)
{
	while (!IsBufferOverflow() && (CurrentItem() != item))
		CurrentIndex++;
}

void Parser::SkipUntil(ParserCriterion comparision)
{
	while (!IsBufferOverflow() && !comparision(CurrentItem()))
		CurrentIndex++;
}


// Jump methods
void Parser::JumpAfter(char item)
{
	size_t index = CurrentIndex;
	while (index < _bufferLength)
	{
		if (_buffer[index] == item)
		{
			CurrentIndex = index;
			increaseIndex();
			return;
		}
		index++;
	}
}

void Parser::JumpAfter(ParserCriterion comparision)
{
	size_t index = CurrentIndex;
	while (index < _bufferLength)
	{
		if (comparision(_buffer[index]))
		{
			CurrentIndex = index;
			increaseIndex();
			return;
		}
		index++;
	}
}

void Parser::JumpTo(char item)
{
	size_t index = CurrentIndex;
	while (index < _bufferLength)
	{
		if (_buffer[index] == item)
		{
			CurrentIndex = index;
			return;
		}
		index++;
	}
}

void Parser::JumpTo(ParserCriterion comparision)
{
	size_t index = CurrentIndex;
	while (index < _bufferLength)
	{
		if (comparision(_buffer[index]))
		{
			CurrentIndex = index;
			return;
		}
		index++;
	}
}



//Static methods
bool Parser::IsPrintable(byte item)
{
	return item >= 32 && item < 129;
}

bool Parser::IsAlfaNumeric(byte item)
{
	return IsLetter(item) || IsDigit(item);
}

bool Parser::IsNotDigit(byte item)
{
	return !IsDigit(item);
}

bool Parser::IsDigit(byte item)
{
	return item >= '0' && item <= '9';
}

bool Parser::IsNumeric(byte item)
{
	return IsDigit(item) || item == '.' || item == ',' || item == '-';
}

bool Parser::IsLetter(byte item)
{
	return IsUpperCaseLetter(item) || IsLowercasaLetter(item);
}

bool Parser::IsNotLetter(byte item)
{
	return !IsLetter(item);
}

bool Parser::IsUpperCaseLetter(byte item)
{
	return item >= 'A' && item <= 'Z';
}

bool Parser::IsLowercasaLetter(byte item)
{
	return item >= 'a' && item <= 'z';
}

bool Parser::IsSeparator(byte item)
{
	return item == '.' || item == ',' || item == ';' || item == ' ' || item == '_' || item == '-' || item == '#' || item == '?' || item == '\0';
}

bool Parser::IsSymbol(byte item)
{
	return IsPrintable(item) && !IsDigit(item) && !IsLetter(item);
}

bool Parser::IsNewLine(byte item)
{
	return item == '\n';
}


bool Parser::IsCarriageReturn(byte item)
{
	return item == '\r';
}

bool Parser::IsSeparatorOrNewLine(byte item)
{
	return IsSeparator(item) || IsNewLine(item);
}


// Private methods
inline void Parser::increaseIndex()
{
	CurrentIndex++;
	if (CurrentIndex >= _bufferLength) CurrentIndex = _bufferLength;
}

inline bool Parser::compare(char * str1, char * str2, size_t n)
{
	bool equals = true;

	size_t newIndex = CurrentIndex;
	for (size_t index = 0; index < n; index++)
	{
		if (newIndex >= _bufferLength)
		{
			equals = false;
			break;
		}

		if (str1[newIndex] != str2[index])
		{
			equals = false;
			break;
		}

		newIndex++;

	}

	if (equals) CurrentIndex = newIndex;
	return equals;
}



