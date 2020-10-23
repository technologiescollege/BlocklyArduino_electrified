/***************************************************
Copyright (c) 2018 Luis Llamas
(www.luisllamas.es)

Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file except in compliance with the License. You may obtain a copy of the License at http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software distributed under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the License for the specific language governing permissions and limitations under the License
 ****************************************************/
 
#include "ParserLib.h"

char demo[] = "AA-123#CC;;;276.56__-,;#__abcd-16";
int demoLength = strlen(demo);

Parser parser((byte*)demo, demoLength);

void setup()
{
	Serial.begin(9600);
	while (!Serial) { ; }
	Serial.println("Starting Demo");
}

void loop()
{
	Serial.println("--- Demo loop ---");

	// Demo Prints AA 123 CC 276.56 -16

	Serial.println(parser.Read_String('-')); 	// Read string until '-' (AA)
	parser.Skip(1); //Ignore '-'

	Serial.println(parser.Read_Int16()); // Read INT16 (123)
	parser.Skip('#'); //Ignore '#'

	Serial.println(parser.Read_String(';')); // Read string until ; (CC)
	parser.SkipWhile(';');   // Ignore ;;;

	Serial.println(parser.Read_Float());  //Read Float (276.56)
	parser.SkipWhile(Parser::IsSeparator);   // Ignore separators __-,;#__

	parser.JumpTo(Parser::IsNumeric);  //Jump to next number (ignore abcd)
	Serial.println(parser.Read_Int32());  //Read Int32 (-16)

	parser.Reset();
	delay(2500);
}
