/*
this is a draft of jsgrub cfg file in order to allow a bootloader to load entries
we need to embbed js parser inside grub and this can be a problem.
the bootloader must be aware of efi32 and able to load x64kernel
*/
{
globalsettings:{
root:"hd(0,0)",
modules:["module1","module2","module3","module4"]
},
entries:[
{name:"Linux", kernelPath:"{{root}}/linux", kernelParams:["a=b","c=d","d=f","test"], initrdPath:"",initrdParams:["","",""]}
{ name:"Linux1", kernelPath:"linux1", kernelParams:["a=b","c=d","d=f","test"], initrdPath:"",initrdParams:["","",""] }

]


}
