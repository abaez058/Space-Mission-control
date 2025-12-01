Project: Space Mission Control System

Final Programming Assignment – COP 4338 
1. Team Member(s)

* Andrew Baez

2. Panther ID(s)

* 6286900 – Andrew Baez

3. FIU Email(s)

* abaez058@fiu.edu

4. Compilation & Execution Instructions
Compilation

This project uses a standard Makefile.
To compile the program, run:

make


This will generate an executable named:

space_mission

Execution

Run the program with:

./space_mission

If “No rule to make target” occurs

Ensure all .c files listed in the Makefile exist. A typical Makefile for this project should include:

gcc -Wall -Wextra -g -o space_mission main.c mission_control.c


If filenames differ, update them accordingly.

5. Programming Environment

OS: Ubuntu 24.04 LTS (Ocelot server environment)

Compiler: gcc version 11+

Build System: make

Standard Used: C11

The project uses:

Dynamic memory management (malloc, realloc, free)

Struct-based mission and communication tracking

File I/O for mission loading and report saving

Enum-based priority validation

String and timestamp validation
