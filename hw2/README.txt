1) This program is to output "Hello World!". The files are located in src folder.
The steps to create the .out file are listed below:

Creating the .o files:
g++ -c -m64 -Wall -l hello.lis -o hello.o hello.cpp

Create .out file:
g++ -m64 -o hello.out hello.o

Execute:
./hello.out

2)
This program is to ask the user to input 5 numbers (the NumberPublisher file) and output the sum of the unique numbers (NumberListener). The files are located in src folder.
The steps to create the .out file are listed below:

Creating the .o files:
g++ -c -m64 -Wall -l Main.lis -o Main.o Main.cpp
g++ -c -m64 -Wall -l NumberPublisher.lis -o NumberPublisher.o NumberPublisher.cpp
g++ -c -m64 -Wall -l NumberListener.lis -o NumberListener.o NumberListener.cpp

Link and creating the .out file:
g++ -m64 -o main.out NumberListener.o NumberPublisher.o Main.o

Execute:
./main.out
