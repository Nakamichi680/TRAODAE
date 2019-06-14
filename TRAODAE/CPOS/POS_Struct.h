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


struct POS_HEADER
{
    uint32_t POS_MAGIC;				// "CPOS"
    uint32_t FILESIZE;				// Dimensione del file POS
    uint32_t nCHARS;				// Numero di animazioni di personaggi contenute nel file POS
};


struct POS_ANIM_HEADER
{
    uint32_t Name_lenght;			// Lunghezza in byte della stringa del nome
	string Name;					// Nome del personaggio del blocco dati
	uint32_t Name_hashed;			// Hash del nome
	uint32_t Animation_hashed;		// Hash del nome dell'animazione collegata (dal file CAL)
	uint32_t Blendshape_hashed;		// Hash del nome del blendshape collegato (dal file TMS)
    uint32_t TMS_Name_lenght;		// Lunghezza in byte della stringa del nome del file TMS
	string TMS_Name;				// Nome del file TMS
	uint32_t nFrames;				// Numero di frames - 1 dell'animazione
};


struct POS_RAW_DATA
{
	float X_trasl;
	float Y_trasl;
	float Z_trasl;
	float W_trasl;
};