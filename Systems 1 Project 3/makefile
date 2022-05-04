#Jake Kennedy Lab 3 Makefile

#Makefile for lab 1-4.  You need to add you name to this file in the comments
# You will need to add a entry to create your zip file

#change the last dependency for each new lab
all:  tags headers lab3 structProto frictionPercentProto

#this entry has to change for lab 2 - 4
# NEVER compile .c files with this rule - it lacks needed compile time flags
# There is an entry below that turns .c files into .o files

lab3: lab3.o table.o allocation.o movement.o
	gcc -g -o $@ $^ -lncurses -L. -l8ball -llinkedlist -lm 

#this is where you create an entry to build yuour zip file
#it will also update with new labs

lab3.zip:	makefile *.c *.h README_LAB3
	zip lab3.zip makefile *.c *.h README_LAB3

#makes struct prototype file
#TO BE GRADED
structProto: structProto.o
	gcc -ansi -pedantic -g -o $@ $^ -lncurses -L. -l8ball

#makes friction prototype file
#TO BE GRADED
frictionPercentProto: frictionPercentProto.o
	gcc -ansi -pedantic -g -o $@ $^ -lm

#makes static block variable prototype
#TO BE GRADED
staticTester: staticTester.o
	gcc -ansi -pedantic -g -o $@ $^

#makes offtable prototype file
#TO BE GRADED
pocketProto: pocketProto.o
	gcc -ansi -pedantic -g -o $@ $^ 
#this entry stays for C code labs
tags: *.c
	ctags -R .

# this entry stays for C code labs
headers: *.c tags
	headers.sh


# this entry takes care of C files depending on header files
# It has the flags for compiling the c code
# It you don't like makefiles, consider typing the following line a few
# thousand times this semester and reconsider.
# Be sure that this one doesn't get an inserted line break anywhere
%.o:%.c *.h
	gcc -ansi -pedantic -Wimplicit-function-declaration -Wreturn-type -g -c $< -o $@


