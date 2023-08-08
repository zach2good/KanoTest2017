# Desktop Applications Developer Test for Kano Computing

### Main Program
Built using
 - Windows 10 x64
 - Qt Creator
 - Qt 5.7.1
 - MSCV2015 x64 (tested) or GCC 6.4 (Via mingw, tested)
 - JSON for Modern C++ (https://github.com/nlohmann/json)
 
Build
 - qmake KanoTest.pro -spec win32-g++

### Test Program
Built using 
 - Windows 10 x64
 - Cygwin 2.9.0
 - GCC 6.4
 - Catch2 (https://github.com/catchorg/Catch2)
 - JSON for Modern C++ (https://github.com/nlohmann/json)
 
Build
 - g++ -std=c++0x lib/test.cpp -o test && ./test --durations yes


### Build Testing
Test program works
Main program builds with 2 different compilers
 
### Loading Testing 
Copy/Pasting the input from the supplied pdf didn't result in valid JSON, edited the inputs to make them valid
Single file (valid)
Single file (invalid)
Multiple files (all valid)
Multiple files (none valid)
Multiple files (mixed)
Cancelling out of the FileSelect dialog is safe

### Logic Testing
Program rejects incorrect inputs with red styling, leaving the input available
Input works with either return or clicking the submit button
Program accepts correct input, turning the input field green, locking the input field and button
Once locked the button and field can't be messed with

### Performance Testing
Performance of 100~ items in menu is fine
Memory usage stable after 10 minutes of usage, no major rises or falls
CPU usage minimal (<1% constant)

### Misc Testing
Exiting the program from the menu cross button works safely
Exiting the program from the quit button works safely
Force closing the program doesn't cause a crash

### Portability
The program doesn't use any Windows specific code and compiles with GCC, so it should theoretically compile
for linux and macOS
