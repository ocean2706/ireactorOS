#Specifications and ideas

##Project layout
There will be blod

##Specs and ideas layout
This folder will keep some of the docs until will be merged on the src specific folder
specs folder contain specs. ideas folder contain ideas ;)


## Arch
At first we will focus on x86/amd64 arch. Next will be ARM (yes we will support ARM devices !!! )
Also there will be a low level virtual machine implementation in order to abstract some system calls for "incorporated device"
in order to make the system mobile-ready !

##Chapters x86

1. IReactor Boot Loader
  

2. IReactor SYS Calls

3. IReactor Underline Layers Call
  1. Linux Binary Compatibility
  2. FreeBsd Binary Compatibility (bsd-binary compatibility)
  3. Win32 Binary Compatibility (heavly   based on ReactOS and Wine work )
  4. BeOS/Haiku Binary Compatibility (based on haiku right now ) - future goal if requested
  
4. IReactor installer
5. Core video calls and compatibility. Native 2D/3D accelerator for core video
6. IReactor Shell and shell scripting
7. IReactor Design  compared with
 1. Chromium OS (http://www.chromium.org/chromium-os/chromiumos-design-docs)
 2. Android (most covering diff on linux kernel allowing android devices to have special functions as thethering )
 3. Windows 10 on tablets (actualy also a comparison Android vs Windows 10 )
8. IReactor vs OsDEV
9. Core VM - HAL and other 
