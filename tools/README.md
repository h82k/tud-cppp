# tud-cpp-private

## Installation Procedure
1. Create a VM executing createVM.sh
  * set to 32 bit if Virtualisation is not provided by the target CPU
2. Download a Linux installation ISO (either 32 bit or 64 bit, depending on the previous choice)
3. Start the VM and install the chosen Linux distribution
4. Execute install.sh with the future development user inside the VM to install and configure the required tools
  * set GROUP to either `uucp` or `dialout` depending on the chosen Linux distribution
5. Configure stuff (e.g. deactivate automatic updates notification and screen locking)
6. Clone exercise git repository and import the projects in Eclipse (and close them)
7. Fix Baudrate: stty -F /dev/ttyUSB0 9600 (or 115200)

## How to Use the SK-FX16 Board on Linux
* Enable a COM port within wine
  * Allow the user to access the serial interface either with `usermod -aG uucp USER` or `usermod -aG dialout USER` depending on your distribution. Do not forget to relogin with the respective user.
  * Link the corresponding USB device to the first COM port in wine using `ln -s /dev/ttyUSBX ~/.wine/dosdevices/com1`. Use `dmesg` to find the proper device number.
* Required binaries
  * Copy Softune and FLASHly binaries into the wine folder
  * Softune may be downloaded from: http://www.spansion.com/Support/microcontrollers/developmentenvironment/Pages/software-softune-lineup-f2mc-16.aspx
  * FLASHly can be downloaded from: http://www.holgerium.de/elektronik/
* Test: Execute the Makefile

## TODO
* write a script to create an appliance

## Legal
For educational use only.
