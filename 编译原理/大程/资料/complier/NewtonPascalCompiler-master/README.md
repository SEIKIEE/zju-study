# NewtonPascalCompiler

A Free Pascal Compiler from ZJU Organization.

##Usage

You can compile this project by just using `makefile`:

	make
	
Run: if you use this compiler to compile a pascal source code named `yoursrc. pas`:

* If you don't use `-o`, it will generate a default file named `default.S`:

		./newton-pascal yoursrc.pas 
 
* If you use `-o` to assign your own file name `youroutput`:

		./newton-pascal -o youroutput yoursrc.pas 
 
 or
 
 		./newton-pascal yoursrc.pas -o youroutput 
 