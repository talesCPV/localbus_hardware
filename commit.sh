#!/bin/bash
# Upload files to Github - git@github.com:talesCPV/localbus_hardware
.git

read -p "Are you sure to commit localbus_hardware to GitHub ? (Y/n)" -n 1 -r
echo    # (optional) move to a new line
if [[ $REPLY =~ ^[Yy]$ ]]
then

    #git config --global --add safe.directory /opt/lampp/htdocs/localbus_hardware



    git init

    git add esp32/
    git add libs/

    git add commit.sh
    
    git commit -m "by_script"

    git branch -M main
    git remote add origin git@github.com:talesCPV/localbus_hardware.git
    git remote set-url origin git@github.com:talesCPV/localbus_hardware.git

    git push -u -f origin main

fi