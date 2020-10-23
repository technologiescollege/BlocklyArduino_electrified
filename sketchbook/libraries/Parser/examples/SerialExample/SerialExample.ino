/***************************************************
Copyright (c) 2018 Luis Llamas
(www.luisllamas.es)

Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file except in compliance with the License. You may obtain a copy of the License at http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software distributed under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the License for the specific language governing permissions and limitations under the License
 ****************************************************/
 
#include "ParserLib.h"

Parser parser;

void setup()
{
	Serial.begin(9600);
	while (!Serial) { ; }
	Serial.println("Starting Demo");
	Serial.setTimeout(10);
}

void loop()
{
	if (Serial.available())
	{
		// Try writing some numbers and separators (, . ; # = are valid separators)
		String reader = Serial.readStringUntil('\n');

		if (reader.length() > 0)
		{
			parser.Init(reader);

			parser.DoWhile(
				[]()-> bool { return parser.Search(Parser::IsSeparator); },
				[]() { Serial.println(parser.Read_Int8()); parser.SkipWhile(Parser::IsSeparator); },
				[]() { Serial.println(parser.Read_Int8()); }
			);
			parser.Reset();
		}
	}
}