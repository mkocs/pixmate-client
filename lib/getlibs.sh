#!bin/bash

git clone https://github.com/mkocs/QHotkey
mv QHotkey/QHotkey QHotkey1
rm -rf QHotkey
mv QHotkey1 QHotkey
echo "done!"
