/***************************************************
Copyright (c) 2018 Luis Llamas
(www.luisllamas.es)

Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file except in compliance with the License. You may obtain a copy of the License at http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software distributed under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the License for the specific language governing permissions and limitations under the License
 ****************************************************/
 
#include "ParserLib.h"

char demo[] = "LED#1-ON";
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
	parser.Compare("LED", 3,
		[]() { 	Serial.print("Recieved LED N:");
				parser.SkipWhile(Parser::IsSeparator);
				Serial.print(parser.Read_Uint8());
				parser.SkipWhile(Parser::IsSeparator);
				parser.Compare("ON", 2, []() {Serial.println(" Action: TURN_ON"); });
				parser.Compare("OFF", 3, []() {Serial.println(" ACTION: TURN_OFF"); });
	});

	parser.Reset();
	delay(2500);
}