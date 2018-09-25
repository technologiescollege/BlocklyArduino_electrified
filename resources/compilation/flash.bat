@echo off
.\tools\avr\bin\avrdude -p%1 -carduino -P%2 -b%3 -D -Uflash:w:.\build\sketch.ino.hex:i