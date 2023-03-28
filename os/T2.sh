#!/bin/bash/
#the following command returns the number of arguments
#hint $? will be 0 if there are no errors after any bash command
 
args=$#
if [ $args -lt 2 ]
then
	echo Usage sh T2.sh folder_path link.
	exit
fi
folder_path=$1
link=$2
#create directory according to input
mkdir $folder_path
#If director does not exists, do not try to link the file.
#This avoids reduntant error messages when trying to create the file in a protected directory.
if [ -d "$folder_path" ]; then
	ln -s $folder_path $link
fi


