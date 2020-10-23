/***************************************************
Copyright (c) 2018 Luis Llamas
(www.luisllamas.es)

Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file except in compliance with the License. You may obtain a copy of the License at http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software distributed under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the License for the specific language governing permissions and limitations under the License
 ****************************************************/
 
#include "ParserLib.h"

char demo[] = "AA-BB#CC;DD";
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

	// Example without using success Callback
	Serial.println(" - Example 1 -");
	parser.DoWhile(
		// Condition
		[]()-> bool { return parser.Search(Parser::IsSeparator); },
		// Callback
		[]() { Serial.print("Recieved:");
			   Serial.println(parser.Read_String(Parser::IsSeparator)); 
			   parser.SkipWhile(Parser::IsSeparator); },
		//Finally
		[]() { Serial.print("Finally:"); 
			   Serial.println(parser.Read_String(Parser::IsSeparator)); }
	);

	parser.Reset();
	// Example using success Callback
	Serial.println(" - Example 2 -");
	parser.DoWhile(
		// Condition
		[]()-> bool { return parser.Search(Parser::IsSeparator); },
		// Callback
		[]() { parser.Read_String(Parser::IsSeparator, 
				[](String& data) {	Serial.print("Recieved:"); 
									Serial.println(data); }); 
									parser.SkipWhile(Parser::IsSeparator); },
		//Finally
		[]() { parser.Read_String(Parser::IsSeparator,
				[](String& data) {	Serial.print("Finally:"); 
									Serial.println(data); }); }
	);

	parser.Reset();
	delay(2500);
}