# HINT: VirtualBox requires modprobe vboxdrv on Arch Linux

# parameter
VM="cpp"
VM_DIR="vm"
MEM_SIZE=1024
# TODO replace this with stable on release (25. April)
ISO="debian-jessie-DI-rc3-amd64-netinst.iso"

# TODO check integrity of ISO

# thanks to http://www.perkin.org.uk/posts/create-virtualbox-vm-from-the-command-line.html
# create and register a VirtualBox VM
#VBoxManage unregistervm ${VM}
rm -rf ${VM_DIR}
VBoxManage createvm --name ${VM} --basefolder "${PWD}/${VM_DIR}" --register 

# create a dynamically allocated virtual disk and attach it to the VMs SATA controller
VBoxManage createhd --filename ${VM_DIR}/${VM}.vdi --size 10240

VBoxManage storagectl ${VM} --name "SATA Controller" --add sata
VBoxManage storageattach ${VM} --storagectl "SATA Controller" --port 0 --device 0 --type hdd --medium "${VM_DIR}/${VM}.vdi"

# create a IDE controller with a DVD drive and insert the ISO
VBoxManage storagectl ${VM} --name "IDE Controller" --add ide
VBoxManage storageattach ${VM} --storagectl "IDE Controller" --port 0 --device 0 --type dvddrive --medium ${ISO}

# modify
VBoxManage modifyvm ${VM} --memory ${MEM_SIZE}
VBoxManage modifyvm ${VM} --boot1 dvd --boot2 disk
VBoxManage modifyvm ${VM} --nic1 nat
VBoxManage modifyvm ${VM} --usb on
VBoxManage modifyvm ${VM} --vram 12

# configure
#VBoxHeadless -s ${VM} -v off
# eject ISO
#VBoxManage storageattach ${VM} --storagectl "IDE Controller" --port 0 --device 0 --type dvddrive --medium none
