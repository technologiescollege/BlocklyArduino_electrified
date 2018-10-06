@echo off
.\tools\avr\bin\avrdude -C .\tools\avr\bin\avrdude.conf -p %1 -c %2 -P %3 -b %4 -D -U flash:w:.\build\sketch.ino.hex:i