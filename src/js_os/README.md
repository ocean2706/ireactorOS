#IReactor OS
As we believe it is enough mature, the js can be used in order to generate coresponding codes for both os and 
We have two directions of using js for developing - light and dark

The light side is to split some boot code, lib and other core parts in order to ease manipulation of asm/c code that provide low level
boot routine - as in boot loader and core kernel - it is enough to have nodejs installed and run Makefile.js for each project

The dark side is go to the rabbit hole and direct control the kernel, functions, scripting, booting using/from js code - this mean 
interpret and execute js code inside bootloader kernel 

Here is repository of both above code.

Please feel free to contribute
