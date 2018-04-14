# Postfix-Converter
A program that reads a file containing in-fix math operations, and prints the same operations in post-fix.

This is an explanation of post-fix operations.
http://www.cs.man.ac.uk/~pjj/cs212/fix.html

The program reads a file that contains in-fix operations using undefined variables, in the following format:

A + B ;
C * ( D + E ) ;
F * ( G + H * I ) + J ;
( K + L ) / ( M - N ) ;
( ( O + P ) * ( Q - R ) + S ) / (T + U ) .

The ; tells the program to go to a new line and the . tells it that it has reached the end of the file.

The program prints it into a format like that following:

Infix: A + B ;

Postfix: A B +

Infix: C * ( D + E ) ;

Postfix: C D E + *

Infix: F * ( G + G * I ) + J ;

Postfix F G H I * + * J +
