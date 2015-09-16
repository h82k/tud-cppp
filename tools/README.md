# Documentation

## Procedure to Generate an Appliance for the Practical Course on C/C++
1. Create a VM executing `createVM.sh`.
  * Set to 32 bit if Virtualisation is not provided by the target CPU.
2. Download a Linux installation ISO (either 32 bit or 64 bit, depending on the previous choice).
3. Start the VM and install the chosen Linux distribution manually.
4. Install and configure the required tools:
  * If an Arch Linux derivate was chosen: Execute `install.sh` with the future development user inside the VM.
  * Otherwise: Adapt the installation script to the chosen distribution and execute it then.
5. Configure stuff:
  * deactivate automatic updates notification
  * deactivate screen locking
  * Eclipse
   * enable automatic save on build: Window -> Preferences -> General -> Workspace -> Save automatically before build
   * deactivate Semantic Errors: Window -> Preferences -> C/C++ -> Code Analysis -> Syntax and Semantic Errors
   * enable binary parser (Makefile projects): Window -> Preferences -> C/C++ -> New C/C++ Project -> Makefile Projects -> Binary Parsers -> Elf Parser
  * install Qt Creator
  * add symlinks to directories and programs
  * override `~/.gitconfig` with the supplied one
  * add aliases to `~/.bashrc`
   * `alias ll="ls -la"`
   * `alias ..="cd .."`
   * `alias ...="cd ../.."`
6. Clone exercise and lecture git repository and import the projects in Eclipse (and close them).
7. Export the VM as an appliance.

## Create a VM Directory on Multiple Windows Computers
Execute `create_vm_folder_in_pool.cmd` to create a VM directory on a pool computer which can be accessed by every user.

## Baud Rate Problem Inside the VM
By default the VM will search for an SK-FX16 board connected to a USB port using a filter.
Unfortunately, some computers set the baud rate wrongly (most often to the value of 19200) inside the VM.
Additionally, it seems that it is not possible to change it permanently via `stty -F /dev/ttyUSBx 115200` or directly with FLASHly.

Different solutions exist to circumvent this problem:

1. Reconfigure the VM:
  * Disable the USB filter of the SK-FX16 Board.
  * Enable a serial device (port number: COM1, port mode: host device, path: e.g. /dev/ttyUSB0 or COM12 depending on your operating system).
  * The Makefile provided with one of the projects or solutions of day 5 and 6 is able to choose between /dev/ttyUSBx or /dev/ttySx.
2. Try to install the tools on your computer (Linux should be straightforward, Windows requires the alternative Makefile provided in the `Windows` folder)
3. Use the old development environment provided by the ES department (Windows only).
4. Another (future) solution might be to write a new flash tool directly for Linux which sets the correct baud rate.

## In General: How to Use the SK-FX16 Board on Linux
1. Enable a COM port within wine
  * Allow the user to access the serial interface either with `usermod -aG uucp USER` or `usermod -aG dialout USER` depending on your distribution. Do not forget to relogin with the respective user.
  * Link the corresponding USB device to the first COM port in wine using `ln -s /dev/ttyUSBx ~/.wine/dosdevices/com1`. Use `dmesg` to find the proper device number.
2. Required binaries
  * Copy Softune and FLASHly binaries into the wine folder
  * Softune may be downloaded from: http://www.spansion.com/Support/microcontrollers/developmentenvironment/Pages/software-softune-lineup-f2mc-16.aspx
  * FLASHly can be downloaded from: http://www.holgerium.de/elektronik/
3. Confer the Makefiles in the projects or solutions of day 5 and 6 on how to invoke the tools (Hint: The latest Makefiles automatically create a symbolic link to the device!).
