# About
The assignments hosted here are a result of my individual study following the COMP4300 C++ Game Development course lectures hosted at https://www.youtube.com/playlist?list=PL_xRyXins848nDj2v-TJYahzvs-XW9sVV made available and taught by Dave Churchill - http://www.cs.mun.ca/~dchurchill/ - associate professor at the Department of Computer Science of the Memorial University of Newfoundland. I'm not officially enrolled in the course.

# Library Requirements
The assignments are all based on the SFML library.

# Compilation
The compilation process might vary between assignments, but generally it follows these steps:
- compile the cpp files into .o files
- g++ -std=c++17 -c main.cpp
- link the object files and the library
- g++ -std=c++17 main.o -o game -lsfml-graphics -lsfml-window -lsfml-system
