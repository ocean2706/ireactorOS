ireactorOS
==========

ireactor and superecmascript based full os

#Goals
## 1. Integrate low level win32 and other good api 

### The quest for a better os for desktop and laptop and day to day productivity 
Why ?
The virtualisation is slow and unreliable for desktop/laptop 
The reactos have done good job but it pay tribute to his roots as described on their goals.
The wine project can run some, not all, win32 programs and games but need to be more tightened to the core os.
The linux based and bsd like os-s are from some point of view (as a paradox)  rigid. The current code 

The x86 architecture is here for years, hardware on this platform moving slowly, but we still are find "improvements" to do on code. Improvements not equal to optimisations - we started with 2.6 kernel and now we still face issues with 

Do we need to talk about X ? wayland and mir are moving slowly in order to replace X..... why ? If there is something wrong with X, why not fix-it ?
Do we need to talk about VNC ? RDP is much better protocol !!!!

The win7 api is stable and from a point of view consistent. It will be not changed essential until 2020

There are some win32 app that can`t pe reliable run and there is no fully functional alternative under linux at this time. So we need virtualisation,or wine.

So do we need a fully functional independent Windows 7 Professional like system - until 2020 ?, yes.

Another paradox is that many  android tools run only under win32 os. What a joke !

There already have been some changes and some similar (defunct now ?) projects - for example freebsd had a linux interop api layer (https://www.freebsd.org/doc/handbook/linuxemu.html ). Why not integrate all in one ?

There are already some issues with drivers that will be never be fixed (a large low cost devices don`t work whell with linux/bsd as there is lack of drivers ). Why not use available functional windows drivers ( we already have some time functional ndiswrappers ) ? As we not rule the world of hardware, the choice of reason will be to implement the driver stack model, but nobody force us not to use low level good code. 

#### We are going to desktop 
I love Android, Firefox OS and i expect an x86 computer to behave similar as the power of processing is (?) we suppose better. Why not have wifi display driver incorporated as an option in the os ? Why we don`t have usb thethering on desktop/laptop ?
Don`t you think your old computer can 

An old windows 95 with IE 4 fit in 4GB Hdd ( around 500MB instaled). XP fit in 650MB-1GB. Why we need 10GB of data right now ?
We have enough hdd space right now but "modern". Not the same for linux distro`s but, how do you feel thinking that your 4 years old laptop act slower than a 4 core android tablet or phone ? If there is something wrong in the code, why not fixing ?





### Another reason is the future
We need to look in the future for hardware changes - until 2020 - the next step will be miaturisation but there will be always the need for processing.

As arm devices will have more processing power we can expect a little change from intel domination on desktop and laptops. 
The next step in hardware will be thunderbolt and usb type C devices
The next step is to have new accelerated video boards and full hd games
The next step is have low ssd prices

The next 8k video is near but who need it right now when we don`t have yet fully adopted 4k ?






Chromeos and android os will be merged and also will be merged some portion of firefox os based on his performance (also some firefox os code need to be added here :) Think of nexus usb video, usb thetering and other nice functions android have on it and we love to have them into a desktop computer ! (adb for example ? )

There are also plenty of old devices that need to be able to be run under modern or old hardware - like handheld scanners, pos terminals over serial interfaces, POS devices, etc.

But most of the drivers are already here in the wild !!!!

All you have to do is put it together, even if devos.org told us it is not a good thing to do so.

For the common sense, increased security and independence, we need to run all this under a new flexible, open system

## 2. Js as a language for everything
Ok, not js, better to think at a js-like language.
Js have some little limitations, most of them in ecma or js itself licence.
Some years ago this limits blocked us to use llvm in order to compile js to native code.

We need js as a target language as it is native understood by the browser. In many ways, a browser is just a windows manager and (gnome for example ) already are there implementations of the concepts you can start based on that ideea. It is enough to have something like (near dead) Adobe Flex/Air, windows rt, or lets`s say Titanium for mobile in order to build modern interfaces (modern as in atractive design for UI ) using html to describe the ui hierarchy, js for coding and css for describing the look and feel

The way is already open, and there is no reason not to do it.






