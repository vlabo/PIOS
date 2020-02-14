# PIOS

A simple OS for the Raspberry PI 3

**Here is a great tutorial:**  
https://github.com/bztsrc/raspi3-tutorial

**And uploading the kernel from UART is possible because of this repository:**  
https://github.com/mrvn/raspbootin

## Dependencies

* clang (Compiler)
* [qemu](https://www.qemu.org/) (VM) - *"if you want to run it in a virtual machine."*
* Raspberry PI 3

## Run

* Compile:  
    `make`
* Run on Qemu:  
    `make run`
* Run on Raspberry pi 3
    - Copy `build/kernel.img` to an sd card with installed rasbian as `kernel8.img`
    - Insert it in the raspberry pi and boot it.

## Upload the kernel over serial

* Compile  
    ```make```
* Copy `build/kernel8.img` to an sd card with installed rasbian as `kernel8.img`. (only the first time)
* Connect your computer to the raspberry pi with [usb-to-serial](https://en.wikipedia.org/wiki/USB_adapter) device.
* Run:  
    ```make upload```  
    *you may need to change the tty port in `uploader/Makefile`.*
* Boot the raspberry pi.
    
