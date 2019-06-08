/* Tomb Raider - The Angel of Darkness Animation Exporter
Copyright (c) 2017-2019 Nakamichi680

This file is part of "Tomb Raider - The Angel of Darkness Animation Exporter".

"Tomb Raider - The Angel of Darkness Animation Exporter" is free software: you can redistribute it and/or modify it under the terms of the
GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.

"Tomb Raider - The Angel of Darkness Animation Exporter" is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without
even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with "Tomb Raider - The Angel of Darkness Animation Exporter".
If not, see <http://www.gnu.org/licenses/>.

Copyright (c) Square Enix Ltd. Lara Croft and Tomb Raider are trademarks or registered trademarks of Square Enix Ltd.*/


#pragma once
#include "Classes.h"


// Imposta i nomi di file e cartelle e ne controlla l'esistenza, chiede cosa esportare, mostra le prime due schermate di avvio
bool UI_Startup (char **prova, IO_CLASS &IO);

// Scrive sullo schermo la string "str" centrandola in uno spazio di "lenght" caratteri
void Center_string (string str, unsigned int length);

// Controlla se un file esiste
bool doesExist (string filename);

// Accorcia una stringa "str" ad una lunghezza massima di "lenght" caratteri (gli ultimi tre caratteri sono punti di sospensione)
string Resize_string (string str, unsigned int length);

// Messaggio di errore/errore fatale. 
void UI_Display_Error (bool FATAL_ERROR, string filename, string message);

// Errore per mancanza di file di input. Termina il programma
bool UI_Exit_noinput ();

// Cancella lo schermo e scrive la barra del titolo
void UI_Title ();

// Scrive un testo (opzionale) e, a seguire, disegna una barra di avanzamento
void UI_ProgressBar (unsigned int Position, unsigned int End, unsigned int BarLength, string PreText = "", int P = 99999, int E = 99999);

// Mostra il testo della licenza
void UI_ShowLicense ();