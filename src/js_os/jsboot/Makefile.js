/*
The code is used to create boot loader code from scratch. 
It will run js code in order to build asm source code in one file in order to be compiled as a 
boo

Input code: js
Intermediate code: asm and c code
Depend on js-bootlib - the library for performing low level routines
Output result: uefi/mbr boot code able to load ntldr, freebsd, linux and other os kernels

Inspiration Sources: libreboot,coreboot,grub, lilo, u.a
*/


nodejs makeboot.js
