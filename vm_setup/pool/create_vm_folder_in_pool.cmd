REM This script creates the folder for the VMs on the pool machines

mkdir C:\VM

REM Assign appropriate rights to the group 'Benutzer'
icacls C:\VM /grant Benutzer:(CI)(OI)(M)
