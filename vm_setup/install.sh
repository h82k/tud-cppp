#
# This script serves for setting up a Wine environment in which the flash tool FLASHly may run.
#
# IMPORTANT 1: If you modify PREFIX, your Makefile has to be adjusted accordingly.
# IMPORTANT 2: After adding your user to the group, logout and login again!
#

# parameter
PREFIX="${HOME}/tools"  # this directory will contain the Wine file system (drive_c etc)
SOFTUNE="./Softune"     # The folder containing the Softune utility (should contain 'bin' and 'lib')
                        # Softune can be downloaded here: http://www.spansion.com/Support/microcontrollers/developmentenvironment/Pages/software-softune-lineup-f2mc-16.aspx
FLASHLY="./FLASHly"     # The folder containing FLASHly (should contain 'FLASHly.exe')
                        # FLASHly can be downloaded here: http://www.holgerium.de/elektronik/
GROUP="uucp"            # The system group that may use the serial port. 'uucp' for Arch Linux/Antergos, 'dialout' for Debian/Ubuntu

# allow the current user to use serial devices
echo "enabling access to serial devices (requires root password)"
sudo usermod -aG ${GROUP} $(whoami)
echo "installing packages (requires root password)"
sudo pacman -S --needed git clang eclipse-cpp wine lib32-ncurses    # for Arch Linux/Antergos
#sudo apt-get install git clang eclipse-cdt wine                    # for Debian/Ubuntu

# create a wine prefix and wait for the wineserver to terminate
export WINEPREFIX=${PREFIX}
wineboot -i
echo "waiting for the wineserver to terminate ..."
wineserver -d -w
#while pidof wineserver > /dev/null 2>&1; do sleep 0.1; done

# disable wine MIME types aka remove open with ... with wine programs
#rm -f ~/.local/share/mime/packages/x-wine*
#rm -f ~/.local/share/applications/wine-extension*
#rm -f ~/.local/share/icons/hicolor/*/*/application-x-wine-extension*
#rm -f ~/.local/share/mime/application/x-wine-extension*

# copy Softune and FLASHly files to the prefix
cp -r ${SOFTUNE} ${PREFIX}/drive_c
cp -r ${FLASHLY} ${PREFIX}/drive_c

# link the first and second usb device (/dev/ttyUSB0 and /dev/ttyUSB0) to com1 and com2
ln -sf /dev/ttyUSB0 ${PREFIX}/dosdevices/com1
ln -sf /dev/ttyUSB1 ${PREFIX}/dosdevices/com2

echo "Renew your session to allow access to serial devices"
