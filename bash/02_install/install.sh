#!/bin/bash

# 1. update soft
# 2. install package

# --- ZMIENNE SPECJALNE ---
# 0 			- Nazwa skryptu
# 1 ... 9 - Nazwy argumentów
# @ 			- Wszystkie argumenty
# ? 			- Zwrócona wartość przez ostatnie polecenie
# $ 			- PID bieżącej powłoki
# # 			- Ilość argumentów
# --------------------------

currentDate=$(date +"%F")
RED="\e[0;31m"
GREEN="\e[0;32m"
BLUE="\e[0;34m"
NC="\e[0m"

function update_pack()
{
 sudo aptitude update |& tee -a log_$currentDate.log &> /dev/null
# sudo apt upgrade -y |& tee -a log_$currentDate.log &> /dev/null
 echo -e "${GREEN}[OK] - Aktualizacja zakończona. Sprawdź rezultat w pliku log_$currentDate.log"

}

function check_install()
{
	if [ $# -eq 0 ]; then		# $# przekazanie parametru
		echo -e "${RED}[ERROR] - Nie podałęś żadnego argumentu!$NC" | tee -a log_$currentDate.log
		exit 1
	fi

	for install in "$@" 		# $@ ilość argumentów w funkcji
	do
		dpkg -s $install &> /dev/null		# -s sprawdza czy dany pakiet jest zainstalowany. Za zmienną install będą kryły się nazwy kolejnych argumentów (programów do zainstalowania
		if [ $? -eq 0 ]; then						# $? zwraca wartość 0 czyli TRUE poprzednij instrukcji. Wartość inna niż zero -> FALSE
			echo -e "${BLUE}[MESSAGE] - Nasz pakiet $install jest już zainstalowany!$NC" | tee -a log_$currentDate.log
		else
			echo -e "Instalacja pakietu $install" | tee -a log_$currentDate.log
			sudo aptitude install -y $install | tee -a log_$currentDate.log &> /dev/null
			if [ $? -eq 0 ]; then
				echo -e "${GREEN}[OK] - Pakiet $install zainstalowany pomyślnie.$NC" | tee -a log_$currentDate.log
			else
				echo -e "${RED}[ERROR] - Pakiet $install nie zainstalwał się. Sprawdź informację w pliku log_$currentDate.log$NC" | tee -a log_$currentDate.log
			fi
		fi
	done
}

function main()
{
	update_pack
	check_install zip mc
}

main
