/* Tomb Raider - The Angel of Darkness Animation Exporter
Copyright (c) 2017-2019 Nakamichi680

This file is part of "Tomb Raider - The Angel of Darkness Animation Exporter".

"Tomb Raider - The Angel of Darkness Animation Exporter" is free software: you can redistribute it and/or modify it under the terms of the
GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.

"Tomb Raider - The Angel of Darkness Animation Exporter" is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without
even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with "Tomb Raider - The Angel of Darkness Animation Exporter".
If not, see <http://www.gnu.org/licenses/>.

Copyright (c) Square Enix Ltd. Lara Croft and Tomb Raider are trademarks or registered trademarks of Square Enix Ltd.
Copyright (c) Autodesk, Inc. and/or its licensors. FBX is a registered trademarks or trademarks of Autodesk, Inc. and/or its subsidiaries
and/or affiliates in the USA and other countries.*/


/*------------------------------------------------------------------------------------------------------------------
Imposta i nomi di file e cartelle e ne controlla l'esistenza, chiede cosa esportare, mostra le prime due schermate di avvio
INPUT: char **argv
OUTPUT: IO_CLASS &IO
------------------------------------------------------------------------------------------------------------------*/

#include "stdafx.h"
#include "MISC/concol.h"
#include "Classes.h"
#include "MISC/UI_Functions.h"


bool UI_Startup (char **argv, IO_CLASS &IO)
{
	CONSOLE_FONT_INFOEX cfi;								// Struttura per la gestione della console di Windows
	cfi.cbSize = sizeof cfi;
	cfi.nFont = 0;
	cfi.dwFontSize.X = 8;									// Dimensione caratteri
	cfi.dwFontSize.Y = 14;									// Dimensione caratteri
	cfi.FontFamily = FF_DONTCARE;
	cfi.FontWeight = FW_NORMAL;
	wcscpy(cfi.FaceName, L"Lucida Console");				// Seleziona il carattere Lucida Console (in questo momento non è ancora impostato!!!)
	GetConsoleTitle(IO.Console_OldTitle, MAX_PATH);			// Legge il nome iniziale dalla barra della console. Serve per ripristinarlo quando il programma termina
	SetConsoleTitle(IO.Console_NewTitle);					// Imposta il nome del programma nella barra della console di Windows

	if (argv[1] == NULL)							// Se manca l'input utente il programma mostra un avviso e termina
		return UI_Exit_noinput();

	string input(argv[1]);

	/////////////////////// PREPARAZIONE STRINGHE CARTELLE EXE/CHR/FBX
    if (input.find("\\") == string::npos)			// Se non trova "\" nella stringa in ingresso significa che l'EXE e il CHR/CAL/TMT sono nella stessa cartella
    {
		GetCurrentDirectory(MAX, IO.folder_exe_lpwstr);													/*		C:\Cartella_EXE_CHR						*/
		IO.folder_chr_lpwstr = IO.folder_exe_lpwstr;													/*		C:\Cartella_EXE_CHR						*/
		IO.fbx_folder = CW2A(IO.folder_exe_lpwstr);														/*      C:\Cartella_EXE_CHR						*/	
		if (IO.fbx_folder.back() != '\\')						// Aggiunge "\" se assente alla fine del percorso (i files nel root dell'unità ce l'hanno già)
			IO.fbx_folder.append("\\");																	/*		C:\Cartella_EXE_CHR\					*/
		IO.chr_name = input;																			/*		Nome_personaggio(.CHR/.CAL/.TMT/.POS)	*/
    }
	else											// Se trova "\" allora salva il percorso attuale dell'EXE e ricava da "input" il percorso del CHR/CAL/TMT/POS
	{
		GetModuleFileName(NULL, IO.folder_exe_lpwstr, MAX);												/*		C:\Cartella_EXE\TRAODAE.EXE				*/
		string temp = CW2A(IO.folder_exe_lpwstr);
		temp = temp.substr(0, temp.find_last_of("\\"));													/*      C:\Cartella_EXE	(o C:)					*/
		if (temp.find("\\") == string::npos)					// Aggiunge "\" se non ne trova nemmeno uno (per il root dell'unità)
			temp.append("\\");
		mbstowcs(IO.folder_exe_lpwstr, temp.c_str(), MAX);												/*		C:\Cartella_EXE	(o C:\)					*/
		temp = input.substr(0, input.find_last_of("\\"));												/*      C:\Cartella_CHR (o C:)					*/	
		if (temp.find("\\") == string::npos)					// Aggiunge "\" se non ne trova nemmeno uno (per il root dell'unità)
			temp.append("\\");
		mbstowcs(IO.folder_chr_lpwstr, temp.c_str(), MAX);												/*		C:\Cartella_CHR	(o C:\)					*/
		IO.fbx_folder = input.substr(0, input.find_last_of("\\") + 1);									/*		C:\Cartella_CHR\						*/
		IO.chr_name = input.substr(input.find_last_of("\\") + 1);										/*		Nome_personaggio(.CHR/.CAL/.TMT/.POS)	*/
	}

	/////////////////////// PREPARAZIONE STRINGHE FILES DI INPUT (CHR/CAL/TMT/POS) ED IMPOSTAZIONE PREFERENZE INIZIALI DI ESPORTAZIONE
	transform(IO.chr_name.begin(), IO.chr_name.end(), IO.chr_name.begin(), ::toupper);		// Converte in maiuscolo il nome del file in ingresso
	int ExportMode;		// 0 = Esporta tutto, 1 = Esporta modello/chiedi x altri, 2 = Esporta animazioni/chiedi x altri, 3 = Esporta blend shapes/chiedi x altri

	if (IO.chr_name.size() < 5)			// Se la lunghezza del nome è di 4 o meno caratteri è impossibile che contenga l'estensione che viene, quindi, aggiunta automaticamente
		ExportMode = 0;							// Visto che l'estensione non è specificata verrà esportato tutto il possibile senza chiedere nulla
	else
	{
		unsigned int sz = IO.chr_name.size();
		if (IO.chr_name[sz-4] == '.' && IO.chr_name[sz-3] == 'C' && IO.chr_name[sz-2] == 'H' && IO.chr_name[sz-1] == 'R')						// File in ingresso: CHR
		{
			IO.chr_name = IO.chr_name.substr(0, sz-4);
			ExportMode = 1;						// Il modello in T-Pose verrà esportato automaticamente, blend shapes ed animazioni su richiesta
		}
		else
		{
			if (IO.chr_name[sz-4] == '.' && IO.chr_name[sz-3] == 'C' && IO.chr_name[sz-2] == 'A' && IO.chr_name[sz-1] == 'L')					// File in ingresso: CAL
			{
				IO.chr_name = IO.chr_name.substr(0, sz-4);
				ExportMode = 2;					// Le animazioni verranno esportate automaticamente, blend shapes e modello in T-Pose su richiesta
			}
			else
			{
				if (IO.chr_name[sz-4] == '.' && IO.chr_name[sz-3] == 'T' && IO.chr_name[sz-2] == 'M' && IO.chr_name[sz-1] == 'T')				// File in ingresso: TMT
				{
					IO.chr_name = IO.chr_name.substr(0, sz-4);
					ExportMode = 3;				// I blend shapes verranno esportati automaticamente, animazioni e modello in T-Pose su richiesta
				}
				else
					ExportMode = 0;				// Se non viene trovata un'estensione valida verrà esportato tutto il possibile senza chiedere nulla
			}
		}
	}
	IO.CHR = IO.chr_name;
	IO.CAL = IO.chr_name;
	IO.TMT = IO.chr_name;
	IO.POS = IO.chr_name;
	IO.CHR.append(".CHR");
	IO.CAL.append(".CAL");
	IO.TMT.append(".TMT");
	IO.POS.append(".POS");
	IO.fbx_folder.append(IO.chr_name);																	/*		C:\Cartella_CHR\Nome_personaggio	*/		
	mbstowcs(IO.folder_fbx_lpwstr, IO.fbx_folder.c_str(), MAX);											/*		C:\Cartella_CHR\Nome_personaggio	*/
	IO.fbx_folder.append("\\");																			/*		C:\Cartella_CHR\Nome_personaggio\	*/

	/////////////////////// AVVIO INTERFACCIA GRAFICA UTENTE
	SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);		// Imposta dimensione caratteri e font
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0xf0);				// Imposta il colore di testo e sfondo
	system("chcp 437");															// Imposta il codepage americano
	concolinit();																// Inizializzazione colori testo concol
	bool exit_loop = false;
	int user_input;
	do {
		system("mode 119, 43");													// Imposta la dimensione della finestra
		UI_Title();
		cout << " Welcome to Tomb Raider - The Angel of Darkness Animation Exporter, the all-in-one CHR/CAL/TMT/POS to FBX converter.\n\n";
		cout << " TRAODAE allows you exporting T-Pose, rigged and textured 3D models from CHR files, animations from CAL files, Blend\n";
		cout << " Shapes from TMT files and cutscene character root motion from POS files.\n\n";
		cout << " IMPORTANT NOTICE:\n";
		cout << " CHR file is mandatory: you can export the T-Pose model without CAL, POS and TMT files but you can't export animations\n";
		cout << " or Blend Shapes without their respective CHR. Also, make sure to put all the files in the same folder and with the\n";
		cout << " same name.\n\n\n\n\n";
		cout << " Before continuing you must accept the " << purple << "Terms and Conditions" << black << ":\n\n";
		cout << " \"Tomb Raider - The Angel of Darkness Animation Exporter\" is free software: you can redistribute it and/or modify it\n";
		cout << " under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of\n";
		cout << " the License, or (at your option) any later version.\n\n";
		cout << " To read the full license text of GNU General Public License version 3, press \"L\".\n\n\n\n";
		cout << " Do you accept the Terms and Conditions [Y/N]? ";
		user_input = getch();
		if (user_input == 89 || user_input == 121)								// "Y" = passa alla schermata successiva
			exit_loop = true;
		if (user_input == 78 || user_input == 110)								// "N" = messaggio di saluto e chiusura programma
		{
			system("cls");
			cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n                                                          Bye!\n\n\n\n\n\n\n\n\n\n\n\n\n";
			Sleep(1100);			// Ritardo di 1,1 secondi
			return false;
		}
		if (user_input == 76 || user_input == 108)								// "L" = mostra la licenza
			UI_ShowLicense();
	} while (!exit_loop);
	
	exit_loop = false;
	UI_Title();																	// Resetta la schermata e mostra il titolo del programma

	/////////////////////// CONTROLLO ESISTENZA SU DISCO DEI FILES CHR/CAL/TMT
	SetCurrentDirectory(IO.folder_chr_lpwstr);									// Viene impostata la cartella contenente il CHR
	IO.CHR_exists = doesExist(IO.CHR);
	IO.CAL_exists = doesExist(IO.CAL);
	IO.TMT_exists = doesExist(IO.TMT);
	IO.POS_exists = doesExist(IO.POS);
	if (!IO.CHR_exists)								// Se il file CHR è assente il programma termina
	{
		UI_Display_Error(true, IO.CHR, " not found. Unable to continue.");		// Mostra il messaggio di errore fatale
		return false;
	}
	
	/////////////////////// IMPOSTAZIONE PREFERENZE UTENTE DI ESPORTAZIONE
	switch (ExportMode)
	{
	case(0):										// Esporta tutto il disponibile. ExportMode = 0
		IO.Export_CHR = true;
		if (IO.CAL_exists)
			IO.Export_CAL = true;
		if (IO.TMT_exists)
			IO.Export_TMT = true;
		if (IO.POS_exists && IO.Export_CAL)
			IO.Export_POS = true;
		cout << " The following elements will be exported:\n\n";
		if (IO.Export_CHR)
			cout << " - T-Pose Model\n";
		if (IO.Export_CAL)
			cout << " - Animations\n";
		if (IO.Export_POS)
			cout << " - Cutscene character root motion\n";
		if (IO.Export_TMT)
			cout << " - Blend Shapes\n";
		cout << "\n\n Press any key to continue or Escape to exit.\n";
		user_input = getch();
		if (user_input == 27)
			return false;
		else
		{
			if (user_input == 224 || user_input == 0)
				getch();
			return true;
		}
		break;

	case(1):										// Priorità a CHR, chiedi per CAL, POS e TMT. ExportMode = 1
		IO.Export_CHR = true;
		if (IO.CAL_exists)
			do {
				cout << " Would you like to export animations [Y/N]? ";
				user_input = getch();
				if (user_input == 89 || user_input == 121)
				{
					cout << "Y\n\n";
					IO.Export_CAL = true;
					exit_loop = true;
				}
				if (user_input == 78 || user_input == 110)
				{
					cout << "N\n\n";
					exit_loop = true;
				}
				if (!exit_loop)
					cout << "\r";
			} while (!exit_loop);
		exit_loop = false;
		if (IO.POS_exists && IO.Export_CAL)
			do {
				cout << " Would you like to export cutscene character root motion [Y/N]? ";
				user_input = getch();
				if (user_input == 89 || user_input == 121)
				{
					cout << "Y\n\n";
					IO.Export_POS = true;
					exit_loop = true;
				}
				if (user_input == 78 || user_input == 110)
				{
					cout << "N\n\n";
					exit_loop = true;
				}
				if (!exit_loop)
					cout << "\r";
			} while (!exit_loop);
		exit_loop = false;
		if (IO.TMT_exists)
			do {
				cout << " Would you like to export Blend Shapes [Y/N]? ";
				user_input = getch();
				if (user_input == 89 || user_input == 121)
				{
					cout << "Y\n\n";
					IO.Export_TMT = true;
					exit_loop = true;
				}
				if (user_input == 78 || user_input == 110)
				{
					cout << "N\n\n";
					exit_loop = true;
				}
				if (!exit_loop)
					cout << "\r";
			} while (!exit_loop);
		cout << " The following elements will be exported:\n\n";
		if (IO.Export_CHR)
			cout << " - T-Pose Model\n";
		if (IO.Export_CAL)
			cout << " - Animations\n";
		if (IO.Export_POS)
			cout << " - Cutscene character root motion\n";
		if (IO.Export_TMT)
			cout << " - Blend Shapes\n";
		cout << "\n\n Press any key to continue or Escape to exit.\n";
		user_input = getch();
		if (user_input == 27)
			return false;
		else
		{
			if (user_input == 224 || user_input == 0)
				getch();
			return true;
		}
		break;

	case(2):										// Priorità a CAL, chiedi per CHR, POS e TMT. ExportMode = 2
		IO.Export_CAL = true;
		if (IO.POS_exists)
			do {
				cout << " Would you like to export cutscene character root motion [Y/N]? ";
				user_input = getch();
				if (user_input == 89 || user_input == 121)
				{
					cout << "Y\n\n";
					IO.Export_POS = true;
					exit_loop = true;
				}
				if (user_input == 78 || user_input == 110)
				{
					cout << "N\n\n";
					exit_loop = true;
				}
				if (!exit_loop)
					cout << "\r";
			} while (!exit_loop);
		exit_loop = false;
		do {
			cout << " Would you like to export the T-pose model [Y/N]? ";
			user_input = getch();
			if (user_input == 89 || user_input == 121)
			{
				cout << "Y\n\n";
				IO.Export_CHR = true;
				exit_loop = true;
			}
			if (user_input == 78 || user_input == 110)
			{
				cout << "N\n\n";
				exit_loop = true;
			}
			if (!exit_loop)
				cout << "\r";
		} while (!exit_loop);
		exit_loop = false;
		if (IO.TMT_exists)
			do {
				cout << " Would you like to export Blend Shapes [Y/N]? ";
				user_input = getch();
				if (user_input == 89 || user_input == 121)
				{
					cout << "Y\n\n";
					IO.Export_TMT = true;
					exit_loop = true;
				}
				if (user_input == 78 || user_input == 110)
				{
					cout << "N\n\n";
					exit_loop = true;
				}
				if (!exit_loop)
					cout << "\r";
			} while (!exit_loop);
		cout << " The following elements will be exported:\n\n";
		if (IO.Export_CHR)
			cout << " - T-Pose Model\n";
		if (IO.Export_CAL)
			cout << " - Animations\n";
		if (IO.Export_POS)
			cout << " - Cutscene character root motion\n";
		if (IO.Export_TMT)
			cout << " - Blend Shapes\n";
		cout << "\n\n Press any key to continue or Escape to exit.\n";
		user_input = getch();
		if (user_input == 27)
			return false;
		else
		{
			if (user_input == 224 || user_input == 0)
				getch();
			return true;
		}
		break;

	case(3):										// Priorità a TMT, chiedi per CHR, CAL e POS. ExportMode = 3
		IO.Export_TMT = true;
		do {
			cout << " Would you like to export the T-pose model [Y/N]? ";
			user_input = getch();
			if (user_input == 89 || user_input == 121)
			{
				cout << "Y\n\n";
				IO.Export_CHR = true;
				exit_loop = true;
			}
			if (user_input == 78 || user_input == 110)
			{
				cout << "N\n\n";
				exit_loop = true;
			}
			if (!exit_loop)
				cout << "\r";
		} while (!exit_loop);
		exit_loop = false;
		if (IO.CAL_exists)
			do {
				cout << " Would you like to export animations [Y/N]? ";
				user_input = getch();
				if (user_input == 89 || user_input == 121)
				{
					cout << "Y\n\n";
					IO.Export_CAL = true;
					exit_loop = true;
				}
				if (user_input == 78 || user_input == 110)
				{
					cout << "N\n\n";
					exit_loop = true;
				}
				if (!exit_loop)
					cout << "\r";
			} while (!exit_loop);
		exit_loop = false;
		if (IO.POS_exists && IO.Export_CAL)
			do {
				cout << " Would you like to export cutscene character root motion [Y/N]? ";
				user_input = getch();
				if (user_input == 89 || user_input == 121)
				{
					cout << "Y\n\n";
					IO.Export_POS = true;
					exit_loop = true;
				}
				if (user_input == 78 || user_input == 110)
				{
					cout << "N\n\n";
					exit_loop = true;
				}
				if (!exit_loop)
					cout << "\r";
			} while (!exit_loop);
		cout << " The following elements will be exported:\n\n";
		if (IO.Export_CHR)
			cout << " - T-Pose Model\n";
		if (IO.Export_CAL)
			cout << " - Animations\n";
		if (IO.Export_POS)
			cout << " - Cutscene character root motion\n";
		if (IO.Export_TMT)
			cout << " - Blend Shapes\n";
		cout << "\n\n Press any key to continue or Escape to exit.\n";
		user_input = getch();
		if (user_input == 27)
			return false;
		else
		{
			if (user_input == 224 || user_input == 0)
				getch();
			return true;
		}
	}
}