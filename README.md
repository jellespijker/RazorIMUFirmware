# Installation

For those of you that use the Arduino IDE, rename RazorIMUFirmware.cpp -> RazorIMUFirmware.ino. When the program is build via CMAKE, add the content of boards.txt to the boards.txt file in your Arduino SDK.

# Usage

Connect via 115200 baud.
  
The following commands can be send to the board.  
 - \#f -> request single frame
 - \#0 -> disable continuous stream
 - \#1 -> enable continous stream
 - \#b -> request data as byte stream 36 bytes data (Accel X,Y,Z / Magn X,Y,Z / Gyro X,Y,Z) + 1 byte LRC (XOR) as checksum. Each message consist of a total of 37 bytes.
 - \#t -> request sensor readings as text string, three lines total.
 - \#u<char> set the update frequency between ~4 till 50 Hz, by sending a char value with the correspondending value.