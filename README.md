### STM32 16-Display x 16-Encoder MIDI Controller

Firmware for composite USB device with MIDI & Serial interface running on STM32F446 MCU. Device has 16 rotary encoder & 16 TFT LCD displays (160x80px).

##### MIDI Interface

On every encoder event device sends MIDI commands to the connected USB host. Easiest way to check MIDI commands is using MidiView app.

<img src="media/midiview.png" style="zoom:30%; float: left;"/>

##### Display Elements

Each of 16 displays has channel, name, value and bar elements.

<img src="media/display.png" style="zoom:20%; float: left;"/>

##### Serial Interface

Device supports a set of commands to setup interface fields through serial port. Each command is an ASCII-string with '\n' terminator. 

| Command                  | Parameters                                                   |
| ------------------------ | ------------------------------------------------------------ |
| `/set/value/{x}/{y}`     | {x} - display id<br />{y} - value                            |
| `/set/level/{x}/{y}`     | {x} - display id<br />{y} - bar level                        |
| `/set/channel/{x}/{y}`   | {x} - display id<br />{y} - channel                          |
| `/set/name/{x}/{y}`      | {x} - display id<br />{y} - name                             |
| `/set/color/{x}/{y}/{z}` | {x} - display id<br />{y} - color element: "bg", "text", "border", "bar"<br />{z} - RGB color in hex, e.g. - "ff0000" - red, "ffffff" - white, etc. |

##### Interface example

<img src="media/interface.jpg" style="zoom:10%; float: left;"/>

##### Board Bringup

<img src="media/board_raw.jpg" style="zoom:7.5%;" />		<img src="media/board_bringup.jpeg" alt="board_bringup" style="zoom:7%;" />

##### TODO 

- MIDI channel configuration

##### 
