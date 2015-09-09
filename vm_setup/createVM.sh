# parameter
VM_NAME="praktikum"
VM_DIR="vm"
MEM_SIZE=2048
X64=true

if ! lsmod | grep "vboxdrv" &> /dev/null ; then
  echo "The module vboxdrv is not loaded."
  echo "Aborting..."
  exit 1
fi

echo
if ${X64}; then
	echo "Using 64bit environment (with full hardware virtualisation support)"
else
	echo "Using 32bit environment (without hardware virtualisation support)"
fi
echo

# thanks to http://www.perkin.org.uk/posts/create-virtualbox-vm-from-the-command-line.html
# create and register a VirtualBox VM
VBoxManage unregistervm ${VM_NAME}
rm -rf ${VM_DIR}
VBoxManage createvm --name ${VM_NAME} --basefolder "${PWD}/${VM_DIR}" --register 

# create a dynamically allocated virtual disk and attach it to the VMs SATA controller
VBoxManage createhd --filename ${VM_DIR}/${VM_NAME}.vdi --size 10240 # --variant Fixed

VBoxManage storagectl ${VM_NAME} --name "SATA Controller" --add sata
VBoxManage storageattach ${VM_NAME} --storagectl "SATA Controller" --port 0 --device 0 --type hdd --medium "${VM_DIR}/${VM_NAME}.vdi"

# create a IDE controller with a DVD drive
VBoxManage storagectl ${VM_NAME} --name "IDE Controller" --add ide
VBoxManage storageattach ${VM_NAME} --storagectl "IDE Controller" --port 0 --device 0 --type dvddrive --medium emptydrive

# modify
VBoxManage modifyvm ${VM_NAME} --clipboard bidirectional
VBoxManage modifyvm ${VM_NAME} --memory ${MEM_SIZE}
VBoxManage modifyvm ${VM_NAME} --boot1 dvd --boot2 disk
VBoxManage modifyvm ${VM_NAME} --nic1 nat
VBoxManage modifyvm ${VM_NAME} --usb on
VBoxManage modifyvm ${VM_NAME} --vram 12
VBoxManage modifyvm ${VM_NAME} --pae off
VBoxManage modifyvm ${VM_NAME} --rtcuseutc on
if ${X64}; then
	VBoxManage modifyvm ${VM_NAME} --ioapic on
else
	VBoxManage modifyvm ${VM_NAME} --hwvirtex off
fi
VBoxManage modifyvm ${VM_NAME} --nestedpaging off

# attach SK-16FX Board
# thanks to https://antonyjepson.wordpress.com/2012/01/26/quickly-attaching-usb-devices-to-virtualbox-guests-using-vboxmanage/
VBoxManage usbfilter add 0 --target ${VM_NAME} --name "FUJITSU SK-16FX-100PMC V1.1" --vendorid 0x0403 --productid 0x6001
