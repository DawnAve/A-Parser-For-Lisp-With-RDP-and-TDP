# A-Parser-For-Lisp-With-RDP-and-TDP
It is a parser for Lisp language, I wrote it based on several syntactic categories. Basically, it will check about solid numbers/lowercase letters, and the use of parentheses. 

To run, use the terminal and go to the file, type in "make", and do "gcc stack.c TDP.c RDP.c main.c -o main", and run by "./main"
TDP stands for table-driven parsing, while RDP stands for recursive descent parsing, notice two Ds mean different things. 

 After typing in inputs, you will see a strangely formatted tree printed, don't be scared.
 Valid input including (,), number digits 0-9, lowercase letters a-z, and combinations like 19, and ab is allowed, but mixings like a3 or 3k is not allowed. 

 I hope you enjoy these seemingly useless weird parsers!  (Easter eggs included!)
