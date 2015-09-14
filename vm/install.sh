#
# This script installs the software required in the practical course on C/C++ on an Arch Linux derivate with preinstalled sudo.
#

# script parameter
PREFIX="${HOME}/tools"	# the directory that will contain the Wine prefix ('drive_c' etc) (adjust your Makefile accordingly!)
SOFTUNE="./Softune"		# the directory containing the Softune utility (should contain 'bin' and 'lib')
						# Softune can be downloaded here: http://www.spansion.com/Support/microcontrollers/developmentenvironment/Pages/software-softune-lineup-f2mc-16.aspx
FLASHLY="./FLASHly"		# the directory containing FLASHly (should contain 'FLASHly.exe')
						# FLASHly can be downloaded here: http://www.holgerium.de/elektronik/
GROUP="uucp"			# the system group that is allowed to use the serial port (uucp or dialout, depending on the Linux distribution)

# allow the current user to use serial devices and install required packages
echo "enabling access to serial devices (requires root password)"
sudo usermod -aG ${GROUP} $(whoami)
echo "installing packages (requires root password)"
sudo pacman -S --needed git clang gcc make gdb doxygen wine lib32-ncurses eclipse-cpp

# create a Wine prefix and wait for the wineserver to terminate (wineboot will run in the background!)
export WINEPREFIX=${PREFIX}
wineboot -i
echo "waiting for the wineserver to terminate ..."
wineserver -d -w

# disable Wine MIME types aka remove 'open with ...' with Wine programs
read -p "Do you want to remove all Wine MIME types? [y/N]" -r
if [[ $REPLY =~ ^[Yy]$ ]]
then
	echo "removing WINE MIME types ..."
	rm -f ~/.local/share/mime/packages/x-wine*
	rm -f ~/.local/share/applications/wine-extension*
	rm -f ~/.local/share/icons/hicolor/*/*/application-x-wine-extension*
	rm -f ~/.local/share/mime/application/x-wine-extension*
fi

# copy Softune and FLASHly files to the prefix
cp -r -L ${SOFTUNE} ${PREFIX}/drive_c
cp -r -L ${FLASHLY} ${PREFIX}/drive_c

echo "Renew your session to allow access to serial devices"
