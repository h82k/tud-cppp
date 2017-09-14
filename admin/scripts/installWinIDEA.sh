#!/bin/bash

# This script creates a file with udev rules, which allow 
# user running the script to access all iSystem devices.
# If devices are atatched, when the script is run, they
# have to be detached and reatached to activate the rules.
#
# (c) iSystem AG, 2014-2017
#
# Modified by Sascha Edwin Zander (Sep 2017)
#
# The following steps yield a running WinIDEA instance using Wine.
# Flash and debug support may not work properly currently
# Steps:
# * Install wine and winetricks (both 32bit)
# * Run `winetricks vcrun2013`
# * Unpack *WinIDEA_Driver.zip* so that *~/.wine/drive_c/PortableApps* contains the subfolders *iSYSTEM* and *Cypress*.
# * Copy this script to *~/.wine/drive_c/PortableApps/iSYSTEM/winIDEAOpen9*
# * Execute the copied script and answer both questions with 'yes'
# * Start *winIDEA.exe* (some dependencies may be installed automatically during the first start)
#

UDEV_FILE="/etc/udev/rules.d/isystem-usb.rules"
WINIDEA_DIR=`pwd`
START_FILE="winidea.sh"
WINIDEA_EXE="winIDEA.exe"
USR_BIN_DIR="/usr/local/bin"
SCRIPTNAME="installWinIDEA.sh"

S_OK=0
E_UDEV_RULES_EXIST=1
E_NOT_ROOT=2
E_UDEV_CREATION_FAILED=3
E_NO_EXE=4
E_STARTUP_SCRIPT_CREATION_FAILED=5
E_PERM_OR_USER=6
E_LINK_FAILED=7
E_INVALID_ARG=8

# TODO: deploy script should define <version> above

check_sudo()
{
    if [ "${USER}" != "root" ]; then
        echo >&2 "ERROR: Script must be run as root. Use sudo to run this script."
        exit ${E_NOT_ROOT}
    fi
}


create_udev_rules()
{
    if [ -e "${UDEV_FILE}" ]; then
        echo >&2 "File '${UDEV_FILE}' already exists. Edit it manually if necessary."
        return ${E_UDEV_RULES_EXIST}
    fi

    echo -e "Creating udev rule for iSystem USB devices, file:\n    ${UDEV_FILE}"
    sudo echo "ACTION==\"add\", SUBSYSTEM==\"usb\", ATTR{idVendor}==\"06f9\", OWNER=\"${SUDO_USER}\"" > ${UDEV_FILE}

    if [ ${?} != "0" ]; then
        echo >&2 "ERROR: Unable to create file: ${UDEV_FILE}"
        exit ${E_UDEV_CREATION_FAILED}
    fi

    echo -e "Rules for iSystem USB devices were written to file:\n    ${UDEV_FILE}"
    echo -e "\n!!! Remove and attach iSystem devices to activate the rules.!!!\n"
}


create_startup_script()
{
    if [ ! -e "${WINIDEA_EXE}" ]; then
        echo >&2 "ERROR: Start this script in the directory, where winidea.exe is located."
        exit ${E_NO_EXE}
    fi

    echo -e "#!/bin/bash\n\nexport WINEDLLPATH=${WINIDEA_DIR}\nwine ${WINIDEA_DIR}/${WINIDEA_EXE}" > ${START_FILE}

    if [ ${?} != "0" ]; then
        echo >&2 "ERROR: Unable to create winiDEA startup file: ${START_FILE}"
        exit ${E_STARTUP_SCRIPT_CREATION_FAILED}
    fi

    chmod 744 ${START_FILE}
    chown ${SUDO_USER}:${SUDO_USER} ${START_FILE}

    if [ ${?} != "0" ]; then
        echo >&2 "ERROR: Unable to set permissions of winiDEA startup file: ${START_FILE}"
        exit ${E_PERM_OR_USER}
    fi

    echo "winIDEA start script successfully created!"
}


create_link_to_startup_script()
{
    echo -n "Do you want to create a link to '${START_FILE}' in '${USR_BIN_DIR}'? [Y/n] "
    read answer

    if [ -e "${USR_BIN_DIR}/winidea" ]; then
        rm "${USR_BIN_DIR}/winidea"
    fi
    
    if [ "${answer}" == "y" -o "${answer}" == "Y" -o "${answer}" == "" ]; then
        sudo ln -s "${WINIDEA_DIR}/${START_FILE}" "${USR_BIN_DIR}/winidea"

        if [ ${?} != "0" ]; then
            echo >&2 "ERROR: Unable to create link in ${USR_BIN_DIR} to winIDEA startup file: ${START_FILE}"
            exit ${E_LINK_FAILED}
        fi
    fi
}    


parse_options()
{
    while getopts ":h" OPTION; do
        case "${OPTION}" in
            h)
                print_help
                exit ${S_OK}
                ;;
            *)
                echo >&2
                echo >&2 "${0} - ERROR: Invalid option: '${OPTARG}'"
                print_help
                exit ${E_INVALID_ARG}
                ;;
        esac
    done
}


print_help()
{
    echo ""
    echo "NAME"
    echo "    ${SCRIPTNAME} - installs iSystem winIDEA"
    echo ""
    echo "SYNOPSIS"
    echo "    $SCRIPTNAME [OPTIONS]"
    echo ""
    echo "DESCRIPTION"
    echo "    This script installs winIDEA into the folder where it is started."
    echo "    It performs the following actions:"
    echo "    - downloads winIDEA archive files from iSystem's web page"
    echo "    - unpacks the archive"
    echo "    - creates udev rules for iSystem USB devices if they do not already exist"
    echo "    - creates startup script 'winidea.sh' in the current folder"
    echo "    - prompts for confirmation to create a link in /usr/bin to the startup script"
    echo ""
    echo "    -h"
    echo "        prints this information."
    echo ""
}


main()
{
    check_sudo
    parse_options $@
    create_udev_rules
    create_startup_script
    create_link_to_startup_script
    echo -e "\nInstallation finished.\n"
}


main $@
