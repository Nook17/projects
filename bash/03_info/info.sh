#!/bin/bash

currentDate=$(date +"%F")
RED="\e[0;31m"
GREEN="\e[0;32m"
BROWN="\e[0;33m"
BLUE="\e[0;34m"
PURPLE="\e[0;35m"
CYAN="\e[0;36m"
NC="\e[0m"

function mysystem_info()
{
	if [ $# -eq 0 ]; then
		echo -e "${PURPLE}[INFO] - Nie podałeś żadnych argumentów.$NC"
	fi

}

function main()
{
	mysystem_info
}

main
