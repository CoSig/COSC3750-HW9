####################
# Makefile
# Author: Cole Sigmon
# Date: April 25, 2023
#
# COSC 3750, Homework 9
#
# This is a make file for wyshell.
# Implemented with a clean method.
####################

CC = gcc
CFLAGS = -Wall -ggdb
RM = /bin/rm -f

.PHONY: wyshell clean

wyshell: wyshell.c
	${CC} ${CFLAGS} wyshell.c wyscanner.c -o wyshell

clean:
	${RM} wyshell
