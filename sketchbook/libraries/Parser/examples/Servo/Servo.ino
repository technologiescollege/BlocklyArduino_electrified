/***************************************************
Copyright (c) 2018 Luis Llamas
(www.luisllamas.es)

Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file except in compliance with the License. You may obtain a copy of the License at http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software distributed under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the License for the specific language governing permissions and limitations under the License
 ****************************************************/
 
#include "ParserLib.h"

char demo[] = "SERVO12_185.67";
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
	parser.Compare("SERVO", 5,
		[]() { 	Serial.print("Recieved SERVO N:");
				uint8_t servo = parser.Read_Uint8();
				Serial.print(servo);
				parser.SkipWhile(Parser::IsSeparator);
				Serial.print(" Angle:");
				Serial.println(parser.Read_Float());
	});

	parser.Reset();
	delay(2500);
}