# Librería Arduino Parser
La librería Arduino Parser implementa funciones para interpretar de forma sencilla la información contenida en un char Array o en un String. Dispone de funciones para leer números, subcadenas, buscar un caracter, así como varias funciones para desplazarse o buscar a lo largo del buffer.

Está diseñado para trabajar con un array recibido por un medio de comunicación (por ejemplo, puerto serie), pero el Parser no realiza la recepción ni modifica los datos. De esta forma es posible emplearlo con cualquier char array, independientemente de su origen.

Arduino Parser está diseñado para trabajar junto con la librería AsyncSerial, que realiza la recepción de datos por puerto de serie de forma no bloqueante.

Más información https://www.luisllamas.es/libreria-arduino-parser/

## Instrucciones de uso
La librería Arduino Parser trabaja sobre un buffer de char array, que es proporcionado externamente al objeto. El Parser no recibe, ni modifica en ningún momento el buffer, por lo que es seguro usarlo en cualquier array.

El buffer y su longitud se reciben en el constructor del Parser. No obstante, es posible cambiarlo en cualquier momento con las funciones 'Init().

Parser proporciona funciones para realizar la lectura de datos (bool, char, números, strings). Estas funciones devuelven el objeto leido y avanzan el cursor al elemento actual 'CurrentIndex las posiciones oportunas, si la lectura ha tenido éxito.

Por otro lado, todas las funciones de lectura admiten una función de callback, que dispara si la lectura la lectura ha tenido éxito. Es posible emplear funciones lambda (pero no obligatorio) para conseguir un código más compacto.

Esta forma de uso es algo más avanzada, pero permite discriminar si la lectura ha sido realmente válida (por ejemplo, leer un entero devuelve 0, aunque no haya tenido éxito, mientras que la función de callback sólo dispara si la lectura es realmente correcta).

Por otro lado, tenemos las funciones 'Compare(...) que comparan el punto actual del buffer con un String. Estas funciones son útiles, por ejemplo, para discriminar el comando recibido en un puerto de serie. Las funciones 'Compare(...) necesitan las longitud de la cadena comparada. Si, por diseño, la mayoría de vuestros comandos tienen la misma longitud podéis usar el atributo DEFAULT_COMMAND_LENGTH y no proporcionarlo en aquellos 'Compare(...) que tengan esa longitud.

Por su parte, las funciones 'Search(...) buscan en el resto del buffer en búsqueda de un char. Podemos usarlas, por ejemplo, para dividir un array separado por comas con un número variable de elementos.

Las funciones 'IfCurrentIs(...), 'IfCurrentIsNot(...), 'DoUntil(...) y 'DoWhile(...) permiten implementar de forma sencilla condicionales y bucles sobre el buffer.

Adicionalmente tenemos las funciones de desplazamiento en el buffer 'Skip(...), 'SkipWhile(...), 'SkipUntil(...), 'JumpAfter(...), 'JumpTo(...).

Finalmente, tenemos una serie de funciones estáticas que comparan un char, y están diseñadas para proporcionarse a cualquiera de los métodos anteriores. Así, por ejemplo, es posible avanzar en el buffer hasta que se encuentre un dígito o desplazarse mientras se encuentre un separador.

Unidas todas estas funciones nos dan un gran potencial para interpretar casi cualquier trama que tengáis como comunicación en vuestro proyecto. Consultar los ejemplos para ver algunas combinaciones posibles. (Hay ejemplos con/sin funciones de callback y con/sin funciones lambda).

### Constructor
El objeto Arduino Parser se instancia a través de uno de sus constructores
```c++
Parser(size_t default_command_length = 5); //Vacio
Parser(String& buffer, size_t default_command_length = 5); //Desde String
Parser(char* buffer, size_t bufferLength, size_t default_command_length = 5); //Desde char array
Parser(byte* buffer, size_t bufferLength, size_t default_command_length = 5); //Desde byte array
```

Pero podemos cambiar el buffer usando las funciones 'Init(...)
```c++
void Init(char* buffer, size_t bufferLength, size_t default_command_length = 5);
void Init(byte* buffer, size_t bufferLength, size_t default_command_length = 5);
void Init(String& buffer, size_t default_command_length = 5);
```


### Uso de Arduino Parser
Para realizar la interpretación de lectura del buffer tenemos las funciones 'Read_(...) que devuelven el valor leído, y avanzan el cursor si la lectura ha tenido éxito. Adicionalmente admiten una función de callback que recibe como parámetro el valor leído, y dispara únicamente si la lectura ha sido correcta.
```c++
bool	 Read_Bool(ParserCallbackBool callback = nullptr);
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
```

Las funciones de lectura de cadenas de texto necesitan un separador válido para finalizar la lectura. Igualmente, admiten una función de callback que dispara si la lectura ha tenido éxito.
Por otro lado, el parámetro opcional 'endIfNotFound indica si, en caso de no encontrar el separador, se considera válida la cadena hasta el final del buffer. Por defecto es 'true ya que es útil, por ejemplo, para dividir cadenas cadenas separadas por coma (donde el último dato no tiene coma al final)
```c++
size_t Read_CharArray(char separator, ParserCallbackCharArray callback = nullptr);
size_t Read_CharArray(ParserCriterion criterion, ParserCallbackCharArray callback = nullptr);
size_t Read_CharArray(char separator, bool endIfNotFound, ParserCallbackCharArray callback = nullptr);
size_t Read_CharArray(ParserCriterion criterion, bool endIfNotFound, ParserCallbackCharArray callback = nullptr);

String Read_String(char separator, ParserCallbackString callback = nullptr);
String Read_String(ParserCriterion criterion, ParserCallbackString callback = nullptr);
String Read_String(char separator, bool endIfNotFound, ParserCallbackString callback = nullptr);
String Read_String(ParserCriterion criterion, bool endIfNotFound, ParserCallbackString callback = nullptr);
```

Los métodos 'Compare(...) son unos de los principales del Parser, y permiten comparar la posición actual del buffer con una cadena de texto. Es necesario proporcional la longitud de la cadena comparada. En caso de obviarse se empleará el campo DEFAULT_COMMAND_LENGTH, que es útil si la mayoría de los comandos comparados tienen la misma longitud.
```c++
// Compare methods
bool Compare(char token, ParserCallback callback = nullptr);
bool Compare(char token[], ParserCallback callback = nullptr);
bool Compare(char token[], size_t max_length, ParserCallback callback = nullptr);
bool Compare(String token, ParserCallback callback = nullptr);
bool Compare(ParserCriterion comparision, ParserCallback callback = nullptr);
```

Las funciones 'Search(...) buscan una cadena de texto en el resto del buffer, y devuelven si se ha encontrado o no la ocurrencia. No modifican la posición actual en el buffer, si no que sirven para determinar si tenemos que realizar un tipo de lectura u otra.
```c++
// Search methods
bool Search(char token, ParserCallback callback = nullptr);
bool Search(char token[], ParserCallback callback = nullptr);
bool Search(char token[], size_t max_length, ParserCallback callback = nullptr);
bool Search(String token, ParserCallback callback = nullptr);
bool Search(ParserCriterion criterion, ParserCallback callback = nullptr);
```

Las funciones de Loop e Ifs permiten realizar una acción en el buffer en función de una condición. En la mayoría de casos los emplearemos junto con las funciones de 'Search(...), pero cualquier otra condición es posible.
```c++
// Loop-if methods
bool IfCurrentIs(char token, ParserCallback yesCallback = nullptr, ParserCallback noCallback = nullptr);
bool IfCurrentIs(ParserCriterion criterion, ParserCallback yesCallback = nullptr, ParserCallback noCallback = nullptr);
bool IfCurrentIsNot(char token, ParserCallback yesCallback = nullptr, ParserCallback noCallback = nullptr);
bool IfCurrentIsNot(ParserCriterion criterion, ParserCallback yesCallback = nullptr, ParserCallback noCallback = nullptr);
void DoUntil(ParserCondition condition, ParserCallback callback = nullptr, ParserCallback finally = nullptr);
void DoWhile(ParserCondition condition, ParserCallback callback = nullptr, ParserCallback finally = nullptr);
```

Los métodos 'Skip(...) permiten ignorar ciertos elementos del buffer y avanzar el cursor.
```c++
// Skip methods
void Skip(size_t num_items);  //avanza N elementos
void SkipWhile(char item);	  //avanza mientras se cumple la condición
void SkipWhile(ParserCriterion comparision);
void SkipUntil(char item); 	  //avanza hasta que se cumple la condición
void SkipUntil(ParserCriterion comparision);
```

Los métodos 'Jump(...) permiten avanzar hasta que se cumpla una condición en el buffer.
```c++
// Jump methods
void JumpAfter(char item);		//salta después del elemento que cumple la condición
void JumpAfter(ParserCriterion comparision);
void JumpTo(char item);			//salta al elemento que cumple la condición
void JumpTo(ParserCriterion comparision);
```

Las funciones estáticas de comparación permiten agrupar conjuntos de caracteres. Se emplean en todas las funciones anteriores, para conseguir condiciones más complejas que únicamente comparar con un caracter.
```c++
// Comparision static methods
static bool IsPrintable(byte item);		  // Caracter Ascii valido
static bool IsDigit(byte item);			  // '0' - '9'
static bool IsNotDigit(byte Item);		  // No es dígito
static bool IsNumeric(byte item);		  // Dígito o ',' o '.' o '-'
static bool IsLowercasaLetter(byte item); // 'a' - 'z'
static bool IsUpperCaseLetter(byte item); // 'A' - 'Z'
static bool IsLetter(byte item);		  // Letra minúscula o mayúscula
static bool IsNotLetter(byte item);		  // No es letra
static bool IsAlfaNumeric(byte Item);	  // Número o letra
static bool IsSeparator(byte item);		  // '.' ',' ';' '_' '-' '=' '#' '?'
static bool IsSymbol(byte item);		  // Printable no alfanumérico
static bool IsNewLine(byte item);		  // '\n'
static bool IsNewLine(byte item);		  // '\r'
static bool IsSeparatorOrNewLine(byte item); // Separador o '\n'
```

## Ejemplos
La librería Parser incluye los siguientes ejemplos para ilustrar su uso.

* Simple: Ejemplo sencillo que muestra el uso de algunas funciones.
```c++
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
```

* CommandRecieve: Muestra un uso sencillo para recibir órdenes y comandos, con y sin funciones lambda.
```c++
#include "ParserLib.h"

char demo[] = "CMD2";
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
	parser.Compare("CMD1", 4, []() { Serial.println("Command1 Recieved"); });
	parser.Compare("CMD2", 4, []() { Command(2); });
	parser.Compare("CMD3", 4, Command3);

	parser.Reset();
	delay(2500);
}

void Command3()
{
	Command(3);
}

void Command(int num)
{
	Serial.print("Command");
	Serial.print(num);
	Serial.println(" recieved");
}
```

* Led: Muestra un posible uso para interpretar una trama que enciende o apaga un Led recibiendo 'ON' o 'OFF'.
```c++
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
```

* Servo: Muestra un posible uso para interpretar una trama que movería un servo a un ángulo.
```c++
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
```

* SerialExample: Muestra un uso posible junto con recepción por puesto Serie. (la recepción es mejorable, pero es un ejemplo sencillo).
```c++
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
```

* CommaSeparated: Muestra un posible uso para interpretar números separados por comas, usando y sin usar success callbacks.
```c++
#include "ParserLib.h"

char demo[] = "12,13,14";
int demoLength = strlen(demo);

Parser parser((byte*)demo, demoLength);

void setup()
{
	Serial.begin(9600);
	while (!Serial) { ; }
	Serial.println("Starting Demo");
	Serial.setTimeout(2);

}

void loop()
{
	Serial.println("--- Demo loop ---");

	// Example without using success Callback
	Serial.println("  - Example 1 -");
	parser.DoWhile(
		[]()-> bool { return parser.Search(','); },
		[]() { Serial.println(parser.Read_Uint16()); parser.SkipWhile(','); },
		[]() { Serial.println(parser.Read_Uint16()); }
	);

	parser.Reset();
	// Example using success Callback
	Serial.println(" - Example 2 -");
	parser.DoWhile(
		[]()-> bool { return parser.Search(','); },
		[]() { parser.Read_Uint16([](uint16_t data) {Serial.println(data); parser.SkipWhile(','); }); },
		[]() { parser.Read_Uint16([](uint16_t data) {Serial.println(data); }); }
	);

	parser.Reset();
	delay(2500);
}
```

* SplitText: Muestra un posible ejemplo para dividir un texto por diferentes tipos de separador.
```c++
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
				[](String& data) { Serial.print("Recieved:"); 
						   Serial.println(data); }); 
						   parser.SkipWhile(Parser::IsSeparator); },
		//Finally
		[]() { parser.Read_String(Parser::IsSeparator,
				[](String& data) { Serial.print("Finally:"); 
						   Serial.println(data); }); }
	);

	parser.Reset();
	delay(2500);
}
```
