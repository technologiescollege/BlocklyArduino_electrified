'use strict';

goog.provide('Blockly.Msg.en');

goog.require('Blockly.Msg');

Blockly.Msg.CAT_MICROBIT_ACCEL = 'Accelerometer';
Blockly.Msg.CAT_MICROBIT_BUTTONS = 'Buttons';
Blockly.Msg.CAT_MICROBIT_COMPASS = 'Compass';
Blockly.Msg.CAT_MICROBIT_DISPLAY = 'Display';
Blockly.Msg.CAT_MICROBIT_IMAGE = 'Image';
Blockly.Msg.CAT_MICROBIT_MICROBIT = 'Micro:Bit';
Blockly.Msg.CAT_MICROBIT_MUSIQUE = 'Music';
Blockly.Msg.CAT_MICROBIT_NEOPIXELS = 'Neopixels';
Blockly.Msg.CAT_MICROBIT_PINS = 'Pins';
Blockly.Msg.CAT_MICROBIT_RADIO = 'Radio';
Blockly.Msg.CAT_MICROBIT_SPEECH = 'Speech';
Blockly.Msg.MICROBIT_ACCELEROMETER_GET_X_MESSAGE0 = 'Accelerometer X axis';
Blockly.Msg.MICROBIT_ACCELEROMETER_GET_X_TOOLTIP = 'Get the acceleration measurement in the X axis.';
Blockly.Msg.MICROBIT_ACCELEROMETER_GET_X_HELPURL = 'https://microbit-micropython.readthedocs.io/en/latest/accelerometer.html#microbit.accelerometer.get_x';
Blockly.Msg.MICROBIT_ACCELEROMETER_GET_Y_MESSAGE0 = 'Accelerometer Y axis';
Blockly.Msg.MICROBIT_ACCELEROMETER_GET_Y_TOOLTIP = 'Get the acceleration measurement in the Y axis.';
Blockly.Msg.MICROBIT_ACCELEROMETER_GET_Y_HELPURL = 'https://microbit-micropython.readthedocs.io/en/latest/accelerometer.html#microbit.accelerometer.get_y';
Blockly.Msg.MICROBIT_ACCELEROMETER_GET_Z_MESSAGE0 = 'Accelerometer Z axis';
Blockly.Msg.MICROBIT_ACCELEROMETER_GET_Z_TOOLTIP = 'Get the acceleration measurement in the Z axis.';
Blockly.Msg.MICROBIT_ACCELEROMETER_GET_Z_HELPURL = 'https://microbit-micropython.readthedocs.io/en/latest/accelerometer.html#microbit.accelerometer.get_z';
Blockly.Msg.MICROBIT_ACCELEROMETER_WAS_GESTURE_MESSAGE0 = 'Was gesture %1';
Blockly.Msg.MICROBIT_ACCELEROMETER_WAS_GESTURE_TOOLTIP = 'Return True or False to indicate if the named gesture was active since the last check.';
Blockly.Msg.MICROBIT_ACCELEROMETER_WAS_GESTURE_HELPURL = 'https://microbit-micropython.readthedocs.io/en/latest/accelerometer.html#microbit.accelerometer.was_gesture';
Blockly.Msg.MICROBIT_ACCELEROMETER_IS_GESTURE_MESSAGE0 = 'Is gesture %1';
Blockly.Msg.MICROBIT_ACCELEROMETER_IS_GESTURE_TOOLTIP = 'Return True or False to indicate if the named gesture is currently active.';
Blockly.Msg.MICROBIT_ACCELEROMETER_IS_GESTURE_HELPURL = 'https://microbit-micropython.readthedocs.io/en/latest/accelerometer.html#microbit.accelerometer.is_gesture';
Blockly.Msg.MICROBIT_ACCELEROMETER_GET_GESTURES_MESSAGE0 = 'Get gestures';
Blockly.Msg.MICROBIT_ACCELEROMETER_GET_GESTURES_TOOLTIP = 'Return the gesture history. The most recent gesture is last. Also clears the gesture history.';
Blockly.Msg.MICROBIT_ACCELEROMETER_GET_GESTURES_HELPURL = 'https://microbit-micropython.readthedocs.io/en/latest/accelerometer.html#microbit.accelerometer.get_gestures';
Blockly.Msg.MICROBIT_ACCELEROMETER_CURRENT_GESTURE_MESSAGE0 = 'Current gesture';
Blockly.Msg.MICROBIT_ACCELEROMETER_CURRENT_GESTURE_TOOLTIP = 'Return the name of the current gesture.';
Blockly.Msg.MICROBIT_ACCELEROMETER_CURRENT_GESTURE_HELPURL = 'https://microbit-micropython.readthedocs.io/en/latest/accelerometer.html#microbit.accelerometer.current_gesture';
Blockly.Msg.MICROBIT_BUTTON_IS_PRESSED_MESSAGE0 = 'Button %1 is pressed';
Blockly.Msg.MICROBIT_BUTTON_IS_PRESSED_TOOLTIP = 'Return True if the specified button is pressed. Otherwise, return False.';
Blockly.Msg.MICROBIT_BUTTON_IS_PRESSED_HELPURL = 'https://microbit-micropython.readthedocs.io/en/latest/button.html#Button.is_pressed';
Blockly.Msg.MICROBIT_BUTTON_WAS_PRESSED_MESSAGE0 = 'Button %1 was pressed';
Blockly.Msg.MICROBIT_BUTTON_WAS_PRESSED_TOOLTIP = 'Return True if the specified button was pressed since the device started or the last time this was checked.';
Blockly.Msg.MICROBIT_BUTTON_WAS_PRESSED_HELPURL = 'https://microbit-micropython.readthedocs.io/en/latest/button.html#Button.was_pressed';
Blockly.Msg.MICROBIT_BUTTON_GET_PRESSES_MESSAGE0 = 'Get number of presses for button %1';
Blockly.Msg.MICROBIT_BUTTON_GET_PRESSES_TOOLTIP = 'Return the running total of presses for the specified button, and resets this total to zero.';
Blockly.Msg.MICROBIT_BUTTON_GET_PRESSES_HELPURL = 'https://microbit-micropython.readthedocs.io/en/latest/button.html#Button.get_presses';
Blockly.Msg.MICROBIT_COMPASS_CALIBRATE_HELPURL = 'https://microbit-micropython.readthedocs.io/en/latest/compass.html#microbit.compass.calibrate';
Blockly.Msg.MICROBIT_COMPASS_CALIBRATE_MESSAGE0 = 'Calibrate compass';
Blockly.Msg.MICROBIT_COMPASS_CALIBRATE_TOOLTIP = 'Start the callibration process to improve the accuracy of the compass.';
Blockly.Msg.MICROBIT_COMPASS_IS_CALIBRATED_MESSAGE0 = 'Compass is calibrated?';
Blockly.Msg.MICROBIT_COMPASS_IS_CALIBRATED_TOOLTIP = 'Returns True if the compass is calibrated, otherwise returns False.';
Blockly.Msg.MICROBIT_COMPASS_IS_CALIBRATED_HELPURL = 'https://microbit-micropython.readthedocs.io/en/latest/compass.html#microbit.compass.is_calibrated';
Blockly.Msg.MICROBIT_COMPASS_HEADING_MESSAGE0 = 'Compass heading';
Blockly.Msg.MICROBIT_COMPASS_HEADING_TOOLTIP = 'Return the compass heading as a number between 0 to 360, representing the angle in degrees, clockwise, with north as 0.';
Blockly.Msg.MICROBIT_COMPASS_HEADING_HELPURL = 'https://microbit-micropython.readthedocs.io/en/latest/compass.html#microbit.compass.heading';
Blockly.Msg.MICROBIT_COMPASS_GET_FIELD_STRENGTH_MESSAGE0 = 'Compass field strength';
Blockly.Msg.MICROBIT_COMPASS_GET_FIELD_STRENGTH_TOOLTIP = 'Return a number indicating the magnitude of the magnetic field around the device.';
Blockly.Msg.MICROBIT_COMPASS_GET_FIELD_STRENGTH_HELPURL = 'https://microbit-micropython.readthedocs.io/en/latest/compass.html#microbit.compass.get_field_strength';
Blockly.Msg.MICROBIT_DISPLAY_GET_PIXEL_MESSAGE0 = 'Get brightness at X %1 Y %2';
Blockly.Msg.MICROBIT_DISPLAY_GET_PIXEL_TOOLTIP = 'Get the brightness of the LED at column X and row Y as a number between 0 (off) and 9 (brightest).';
Blockly.Msg.MICROBIT_DISPLAY_GET_PIXEL_HELPURL = 'https://microbit-micropython.readthedocs.io/en/latest/display.html#microbit.display.get_pixel';
Blockly.Msg.MICROBIT_DISPLAY_SET_PIXEL_MESSAGE0 = 'Set pixel at X %1 Y %2 to brightness %3';
Blockly.Msg.MICROBIT_DISPLAY_SET_PIXEL_TOOLTIP = 'Set the brightness of the LED at column X and row Y to a value which has to be a number between 0 (off) and 9 (brightest).';
Blockly.Msg.MICROBIT_DISPLAY_SET_PIXEL_HELPURL = 'https://microbit-micropython.readthedocs.io/en/latest/display.html#microbit.display.set_pixel';
Blockly.Msg.MICROBIT_DISPLAY_CLEAR_HELPURL = 'https://microbit-micropython.readthedocs.io/en/latest/display.html#microbit.display.clear';
Blockly.Msg.MICROBIT_DISPLAY_CLEAR_MESSAGE0 = 'Clear display';
Blockly.Msg.MICROBIT_DISPLAY_CLEAR_TOOLTIP = 'Clear the display - set the brightness of all LEDs to 0 (off).';
Blockly.Msg.MICROBIT_DISPLAY_SHOW_IMAGE_MESSAGE0 = 'Show image %1';
Blockly.Msg.MICROBIT_DISPLAY_SHOW_IMAGE_TOOLTIP = 'Show the referenced image on the display.';
Blockly.Msg.MICROBIT_DISPLAY_SHOW_IMAGE_HELPURL = 'https://microbit-micropython.readthedocs.io/en/latest/display.html#microbit.display.show';
Blockly.Msg.MICROBIT_DISPLAY_SHOW_ANIMATION_MESSAGE0 = 'Animate images %1 with a delay of %2 milliseconds between frames. %3 Wait %4 %5 Loop %6 %7 Clear %8';
Blockly.Msg.MICROBIT_DISPLAY_SHOW_ANIMATION_TOOLTIP = 'Display the list of images as an animation with a certain delay between each frame. Indicate if you need to wait before continuing, continuously loop the animation and clear the display when finished.';
Blockly.Msg.MICROBIT_DISPLAY_SHOW_ANIMATION_HELPURL = 'https://microbit-micropython.readthedocs.io/en/latest/display.html#microbit.display.show';
Blockly.Msg.MICROBIT_DISPLAY_SCROLL_MESSAGE0 = 'Scroll message %1';
Blockly.Msg.MICROBIT_DISPLAY_SCROLL_TOOLTIP = 'Scroll the referenced text across the display.';
Blockly.Msg.MICROBIT_DISPLAY_SCROLL_HELPURL = 'https://microbit-micropython.readthedocs.io/en/latest/display.html#microbit.display.scroll';
Blockly.Msg.MICROBIT_DISPLAY_ON_HELPURL = 'https://microbit-micropython.readthedocs.io/en/latest/display.html#microbit.display.on';
Blockly.Msg.MICROBIT_DISPLAY_ON_MESSAGE0 = 'Turn on display';
Blockly.Msg.MICROBIT_DISPLAY_ON_TOOLTIP = 'Turns on the display.';
Blockly.Msg.MICROBIT_DISPLAY_OFF_HELPURL = 'https://microbit-micropython.readthedocs.io/en/latest/display.html#microbit.display.off';
Blockly.Msg.MICROBIT_DISPLAY_OFF_MESSAGE0 = 'Turn off display';
Blockly.Msg.MICROBIT_DISPLAY_OFF_TOOLTIP = 'Turn off the display.';
Blockly.Msg.MICROBIT_DISPLAY_IS_ON_MESSAGE0 = 'Display is on?';
Blockly.Msg.MICROBIT_DISPLAY_IS_ON_TOOLTIP = 'Return True if the display is on, otherwise return False.';
Blockly.Msg.MICROBIT_DISPLAY_IS_ON_HELPURL = 'https://microbit-micropython.readthedocs.io/en/latest/display.html#microbit.display.is_on';
Blockly.Msg.MICROBIT_IMAGE_BUILTINS_MESSAGE0 = 'Built in image %1';
Blockly.Msg.MICROBIT_IMAGE_BUILTINS_TOOLTIP = 'Specify one of the built-in images.';
Blockly.Msg.MICROBIT_IMAGE_BUILTINS_HELPURL = 'https://microbit-micropython.readthedocs.io/en/latest/image.html#attributes';
Blockly.Msg.MICROBIT_IMAGE_COPY_MESSAGE0 = 'Copy image %1';
Blockly.Msg.MICROBIT_IMAGE_COPY_TOOLTIP = 'Create an exact copy of the referenced image.';
Blockly.Msg.MICROBIT_IMAGE_COPY_HELPURL = 'https://microbit-micropython.readthedocs.io/en/latest/image.html#microbit.Image.copy';
Blockly.Msg.MICROBIT_IMAGE_INVERT_MESSAGE0 = 'Invert image %1';
Blockly.Msg.MICROBIT_IMAGE_INVERT_TOOLTIP = 'Create a new image by inverting the brightness of the pixels in the referenced image.';
Blockly.Msg.MICROBIT_IMAGE_INVERT_HELPURL = 'https://microbit-micropython.readthedocs.io/en/latest/image.html#microbit.Image.invert';
Blockly.Msg.MICROBIT_IMAGE_CREATE_MESSAGE0 = 'Create image %1 %2 %3 %4 %5 %6 %7 %8 %9 %10 %11 %12 %13 %14 %15 %16 %17 %18 %19 %20 %21 %22 %23 %24 %25 %26 %27 %28 %29 %30';
Blockly.Msg.MICROBIT_IMAGE_CREATE_TOOLTIP = 'Create a new image.';
Blockly.Msg.MICROBIT_IMAGE_CREATE_HELPURL = 'https://microbit-micropython.readthedocs.io/en/latest/image.html#microbit.Image';
Blockly.Msg.MICROBIT_MICROBIT_PANIC_MESSAGE0 = 'Panic with status code %1';
Blockly.Msg.MICROBIT_MICROBIT_PANIC_TOOLTIP = 'Enter panic mode to indicate something has gone wrong. Requires a restart. Pass in a number to indicate a status code.';
Blockly.Msg.MICROBIT_MICROBIT_PANIC_HELPURL = 'https://microbit-micropython.readthedocs.io/en/latest/microbit.html#microbit.panic';
Blockly.Msg.MICROBIT_MICROBIT_RESET_HELPURL = 'https://microbit-micropython.readthedocs.io/en/latest/microbit.html#microbit.reset';
Blockly.Msg.MICROBIT_MICROBIT_RESET_MESSAGE0 = 'Reset micro:bit';
Blockly.Msg.MICROBIT_MICROBIT_RESET_TOOLTIP = 'Reset the micro:bit';
Blockly.Msg.MICROBIT_MICROBIT_SLEEP_MESSAGE0 = 'Sleep %1 milliseconds';
Blockly.Msg.MICROBIT_MICROBIT_SLEEP_TOOLTIP = 'Wait for a specified number of milliseconds before the next instruction.';
Blockly.Msg.MICROBIT_MICROBIT_SLEEP_HELPURL = 'https://microbit-micropython.readthedocs.io/en/latest/microbit.html#microbit.sleep';
Blockly.Msg.MICROBIT_MICROBIT_RUNNING_TIME_MESSAGE0 = 'Running time';
Blockly.Msg.MICROBIT_MICROBIT_RUNNING_TIME_TOOLTIP = 'Get the number of milliseconds since the board was switched on or restarted.';
Blockly.Msg.MICROBIT_MICROBIT_RUNNING_TIME_HELPURL = 'https://microbit-micropython.readthedocs.io/en/latest/microbit.html#microbit.running_time';
Blockly.Msg.MICROBIT_MICROBIT_TEMPERATURE_MESSAGE0 = 'Board temperature';
Blockly.Msg.MICROBIT_MICROBIT_TEMPERATURE_TOOLTIP = 'Get the temperature of the micro:bit in degrees Celcius.';
Blockly.Msg.MICROBIT_MICROBIT_TEMPERATURE_HELPURL = 'https://microbit-micropython.readthedocs.io/en/latest/microbit.html#microbit.temperature';
Blockly.Msg.MICROBIT_MUSIC_PLAY_BUILT_IN_MESSAGE0 = 'Play built-in melody %1 %2 Wait %3 %4 Loop %5';
Blockly.Msg.MICROBIT_MUSIC_PLAY_BUILT_IN_TOOLTIP = 'Play one of the built-in melodies. Indicate if you need to wait before continuing or continuously loop the melody.';
Blockly.Msg.MICROBIT_MUSIC_PLAY_BUILT_IN_HELPURL = 'https://microbit-micropython.readthedocs.io/en/latest/music.html#built-in-melodies';
Blockly.Msg.MICROBIT_MUSIC_PITCH_MESSAGE0 = 'Play pitch %1 %2 for  %3 milliseconds';
Blockly.Msg.MICROBIT_MUSIC_PITCH_TOOLTIP = 'Play a pitch at a certain number of cycles per second for a specified number of milliseconds.';
Blockly.Msg.MICROBIT_MUSIC_PITCH_HELPURL = 'https://microbit-micropython.readthedocs.io/en/latest/music.html#music.pitch';
Blockly.Msg.MICROBIT_MUSIC_PLAY_LIST_OF_NOTES_MESSAGE0 = 'Play notes %1 Wait %2 %3 Loop %4';
Blockly.Msg.MICROBIT_MUSIC_PLAY_LIST_OF_NOTES_TOOLTIP = 'Play a list of notes expressed in the special music language. Indicate if you need to wait before continuing or continuously loop the melody.';
Blockly.Msg.MICROBIT_MUSIC_PLAY_LIST_OF_NOTES_HELPURL = 'https://microbit-micropython.readthedocs.io/en/latest/music.html#musical-notation';
Blockly.Msg.MICROBIT_MUSIC_RESET_HELPURL = 'https://microbit-micropython.readthedocs.io/en/latest/music.html#music.reset';
Blockly.Msg.MICROBIT_MUSIC_RESET_MESSAGE0 = 'Reset music';
Blockly.Msg.MICROBIT_MUSIC_RESET_TOOLTIP = 'Reset all music related settings (current tempo, octave and duration) to default values.';
Blockly.Msg.MICROBIT_MUSIC_STOP_HELPURL = 'https://microbit-micropython.readthedocs.io/en/latest/music.html#music.stop';
Blockly.Msg.MICROBIT_MUSIC_STOP_MESSAGE0 = 'Stop music';
Blockly.Msg.MICROBIT_MUSIC_STOP_TOOLTIP = 'Stop all music playback.';
Blockly.Msg.MICROBIT_MUSIC_SET_TEMPO_MESSAGE0 = 'Set tempo with 1 beat the same as %1 ticks, at  %2 beats per minute';
Blockly.Msg.MICROBIT_MUSIC_SET_TEMPO_TOOLTIP = 'Set the speed (tempo) of playback. A certain number of ticks represents a beat. Each beat is to be played a certain number of times a minute (beats per minute or BPM).';
Blockly.Msg.MICROBIT_MUSIC_SET_TEMPO_HELPURL = 'https://microbit-micropython.readthedocs.io/en/latest/music.html#music.set_tempo';
Blockly.Msg.MICROBIT_MUSIC_GET_TEMPO_MESSAGE0 = 'Get current tempo';
Blockly.Msg.MICROBIT_MUSIC_GET_TEMPO_TOOLTIP = 'Gets current tempo information as two numbers: number of ticks per beat, and number of beats per minute (BPM).';
Blockly.Msg.MICROBIT_MUSIC_GET_TEMPO_HELPURL = 'https://microbit-micropython.readthedocs.io/en/latest/music.html#music.get_tempo';
Blockly.Msg.MICROBIT_NEOPIXEL_INITIALISE_MESSAGE0 = 'Initialise %1 neopixel[s] %2 on pin %3';
Blockly.Msg.MICROBIT_NEOPIXEL_INITIALISE_TOOLTIP = 'Make an object to control any attached neopixels. Specify the number of neopixels and the pin to which they are attached.';
Blockly.Msg.MICROBIT_NEOPIXEL_INITIALISE_HELPURL = 'https://microbit-micropython.readthedocs.io/en/latest/neopixel.html#neopixel.NeoPixel';
Blockly.Msg.MICROBIT_NEOPIXEL_CLEAR_MESSAGE0 = 'Clear neopixels on %1';
Blockly.Msg.MICROBIT_NEOPIXEL_CLEAR_TOOLTIP = 'Clear all neopixels controlled by the referenced neopixel object.';
Blockly.Msg.MICROBIT_NEOPIXEL_CLEAR_HELPURL = 'https://microbit-micropython.readthedocs.io/en/latest/neopixel.html#neopixel.NeoPixel.clear';
Blockly.Msg.MICROBIT_NEOPIXEL_SHOW_MESSAGE0 = 'Show neopixels on %1';
Blockly.Msg.MICROBIT_NEOPIXEL_SHOW_TOOLTIP = 'Show / update all the neopixels controlled by the referenced neopixel object.';
Blockly.Msg.MICROBIT_NEOPIXEL_SHOW_HELPURL = 'https://microbit-micropython.readthedocs.io/en/latest/neopixel.html#neopixel.NeoPixel.show';
Blockly.Msg.MICROBIT_NEOPIXEL_SET_MESSAGE0 = 'Using neopixels on %1 set pixel in position %2 with red %3 green %4 blue %5';
Blockly.Msg.MICROBIT_NEOPIXEL_SET_TOOLTIP = 'Use the referenced neopixel object to update the individual neopixel in a specific numbered position with a red, green, blue (RGB) value.';
Blockly.Msg.MICROBIT_NEOPIXEL_SET_HELPURL = 'https://microbit-micropython.readthedocs.io/en/latest/neopixel.html#using-neopixels';
Blockly.Msg.MICROBIT_PIN_TOUCHED_MESSAGE0 = 'Pin %1 is touched?';
Blockly.Msg.MICROBIT_PIN_TOUCHED_TOOLTIP = 'Return True if the referenced pin is touched.';
Blockly.Msg.MICROBIT_PIN_TOUCHED_HELPURL = 'https://microbit-micropython.readthedocs.io/en/latest/pin.html#microbit.MicroBitTouchPin.is_touched';
Blockly.Msg.MICROBIT_PIN_READ_ANALOG_MESSAGE0 = 'Read analog on pin %1';
Blockly.Msg.MICROBIT_PIN_READ_ANALOG_TOOLTIP = 'Read analog value from the referenced pin.';
Blockly.Msg.MICROBIT_PIN_READ_ANALOG_HELPURL = 'https://microbit-micropython.readthedocs.io/en/latest/pin.html#microbit.MicroBitAnalogDigitalPin.read_analog';
Blockly.Msg.MICROBIT_PIN_WRITE_ANALOG_MESSAGE0 = 'Write analog value %1 on pin %2';
Blockly.Msg.MICROBIT_PIN_WRITE_ANALOG_TOOLTIP = 'Write analog value to the referenced pin.';
Blockly.Msg.MICROBIT_PIN_WRITE_ANALOG_HELPURL = 'https://microbit-micropython.readthedocs.io/en/latest/pin.html#microbit.MicroBitAnalogDigitalPin.write_analog';
Blockly.Msg.MICROBIT_PIN_READ_DIGITAL_MESSAGE0 = 'Read digital value on pin %1';
Blockly.Msg.MICROBIT_PIN_READ_DIGITAL_TOOLTIP = 'Read digital value (True or False) from the referenced pin.';
Blockly.Msg.MICROBIT_PIN_READ_DIGITAL_HELPURL = 'https://microbit-micropython.readthedocs.io/en/latest/pin.html#microbit.MicroBitDigitalPin.read_digital';
Blockly.Msg.MICROBIT_PIN_WRITE_DIGITAL_MESSAGE0 = 'Write digital value %1 on pin %2';
Blockly.Msg.MICROBIT_PIN_WRITE_DIGITAL_TOOLTIP = 'Write digital value (True or False) to the referenced pin.';
Blockly.Msg.MICROBIT_PIN_WRITE_DIGITAL_HELPURL = 'https://microbit-micropython.readthedocs.io/en/latest/pin.html#microbit.MicroBitDigitalPin.write_digital';
Blockly.Msg.MICROBIT_RADIO_ON_HELPURL = 'https://microbit-micropython.readthedocs.io/en/latest/radio.html#radio.on';
Blockly.Msg.MICROBIT_RADIO_ON_MESSAGE0 = 'Switch on radio';
Blockly.Msg.MICROBIT_RADIO_ON_TOOLTIP = 'Turn on the radio. This needs to be explicitly called since the radio draws power and takes up memory that you may otherwise need.';
Blockly.Msg.MICROBIT_RADIO_OFF_HELPURL = 'https://microbit-micropython.readthedocs.io/en/latest/radio.html#radio.off';
Blockly.Msg.MICROBIT_RADIO_OFF_MESSAGE0 = 'Switch off radio';
Blockly.Msg.MICROBIT_RADIO_OFF_TOOLTIP = 'Turn off the radio, thus saving power and memory.';
Blockly.Msg.MICROBIT_RADIO_CONFIG_MESSAGE0 = 'Configure radio message length %1 %2 maximum queue length %3 %4 tuned to channel %5 %6 broadcast power %7 %8 data rate %9';
Blockly.Msg.MICROBIT_RADIO_CONFIG_TOOLTIP = 'Configure the radio. The length defines how long an individual message can be. The queue specifies the number of messages that can be stored on the incoming message queue. The channel defines the frequency to which the radio is tuned. The power specifies the strength of the broadcast signal. The data rate indicates the speed at which data is transferred.';
Blockly.Msg.MICROBIT_RADIO_CONFIG_HELPURL = 'https://microbit-micropython.readthedocs.io/en/latest/radio.html#radio.config';
Blockly.Msg.MICROBIT_RADIO_RESET_HELPURL = 'https://microbit-micropython.readthedocs.io/en/latest/radio.html#radio.reset';
Blockly.Msg.MICROBIT_RADIO_RESET_MESSAGE0 = 'Reset radio';
Blockly.Msg.MICROBIT_RADIO_RESET_TOOLTIP = 'Reset the radio to default settings.';
Blockly.Msg.MICROBIT_RADIO_SEND_STRING_MESSAGE0 = 'Send message %1';
Blockly.Msg.MICROBIT_RADIO_SEND_STRING_TOOLTIP = 'Broadcast a text message.';
Blockly.Msg.MICROBIT_RADIO_SEND_STRING_HELPURL = 'https://microbit-micropython.readthedocs.io/en/latest/radio.html#radio.send';
Blockly.Msg.MICROBIT_RADIO_RECEIVE_MESSAGE0 = 'Receive message';
Blockly.Msg.MICROBIT_RADIO_RECEIVE_TOOLTIP = 'Receive a message.';
Blockly.Msg.MICROBIT_RADIO_RECEIVE_HELPURL = 'https://microbit-micropython.readthedocs.io/en/latest/radio.html#radio.receive';
Blockly.Msg.MICROBIT_SPEECH_SAY_MESSAGE0 = 'Say %1';
Blockly.Msg.MICROBIT_SPEECH_SAY_TOOLTIP = 'Attempt to say English input.';
Blockly.Msg.MICROBIT_SPEECH_SAY_HELPURL = 'https://microbit-micropython.readthedocs.io/en/latest/speech.html#speech.say';
Blockly.Msg.MICROBIT_SPEECH_PRONOUNCE_MESSAGE0 = 'Pronounce %1';
Blockly.Msg.MICROBIT_SPEECH_PRONOUNCE_TOOLTIP = 'Precisely pronounce phoneme input.';
Blockly.Msg.MICROBIT_SPEECH_PRONOUNCE_HELPURL = 'https://microbit-micropython.readthedocs.io/en/latest/speech.html#phonemes';
Blockly.Msg.MICROBIT_SPEECH_SING_MESSAGE0 = 'Sing %1';
Blockly.Msg.MICROBIT_SPEECH_SING_TOOLTIP = 'Sing phonemes like a ROBOT.';
Blockly.Msg.MICROBIT_SPEECH_SING_HELPURL = 'https://microbit-micropython.readthedocs.io/en/latest/speech.html#singing';

//adding tooltip & helpurl

