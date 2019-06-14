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


/*------------------------------------------------------------------------------------------------------------------
Legge il file POS contenente le traslazioni dei personaggi durante le cutscenes
INPUT: ifstream &posfile, IO_CLASS IO
OUTPUT: vector <POS_CLASS> &pos
------------------------------------------------------------------------------------------------------------------*/

#include "stdafx.h"
#include "CPOS/POS_Struct.h"
#include "Classes.h"
#include "MISC/UI_Functions.h"


bool POS_Read (ifstream &posfile, vector <POS_CLASS> &pos, IO_CLASS IO)
{
	POS_HEADER pos_header;
	POS_ANIM_HEADER pos_anim_header;
	POS_RAW_DATA pos_raw_data;

	posfile.read(reinterpret_cast<char*>(&pos_header.POS_MAGIC), sizeof(pos_header.POS_MAGIC));						// Legge l'ID del file ("CPOS")

	if (pos_header.POS_MAGIC != 1397706819)			// Se il file non inizia con "CPOS" l'estrazione delle traslazioni termina
	{
		UI_Display_Error(false, IO.POS, " is not a valid POS file. Cutscene translations will not be exported.");
		return false;
	}
	else											// Se il file è valido
	{
		posfile.seekg(4, ios_base::cur);
		posfile.read(reinterpret_cast<char*>(&pos_header.nCHARS), sizeof(pos_header.nCHARS));						// Legge il numero di personaggi
		pos.resize(pos_header.nCHARS);

		// Ogni ciclo legge un layer di traslazioni del personaggio
		for (unsigned int c = 0; c < pos_header.nCHARS; c++)
		{
			posfile.read(reinterpret_cast<char*>(&pos_anim_header.Name_lenght), sizeof(pos_anim_header.Name_lenght));
			posfile.read(reinterpret_cast<char*>(&pos[c].name), pos_anim_header.Name_lenght);
			posfile.read(reinterpret_cast<char*>(&pos_anim_header.Name_hashed), sizeof(pos_anim_header.Name_hashed));
			posfile.read(reinterpret_cast<char*>(&pos[c].Animation_hashed), sizeof(pos_anim_header.Animation_hashed));
			posfile.read(reinterpret_cast<char*>(&pos[c].Blendshape_hashed), sizeof(pos_anim_header.Blendshape_hashed));
			posfile.read(reinterpret_cast<char*>(&pos_anim_header.TMS_Name_lenght), sizeof(pos_anim_header.TMS_Name_lenght));
			posfile.read(reinterpret_cast<char*>(&pos[c].TMS_name), pos_anim_header.TMS_Name_lenght);
			posfile.read(reinterpret_cast<char*>(&pos[c].nFrames), sizeof(pos_anim_header.nFrames));
			pos[c].X_trasl.resize(pos_anim_header.nFrames + 1);
			pos[c].Y_trasl.resize(pos_anim_header.nFrames + 1);
			pos[c].Z_trasl.resize(pos_anim_header.nFrames + 1);
			pos[c].W_trasl.resize(pos_anim_header.nFrames + 1);

			for (unsigned int f = 0; f < pos[c].nFrames + 1; f++)
			{
				posfile.read(reinterpret_cast<char*>(&pos[c].X_trasl[f]), sizeof(pos_raw_data.X_trasl));
				posfile.read(reinterpret_cast<char*>(&pos[c].Y_trasl[f]), sizeof(pos_raw_data.Y_trasl));
				posfile.read(reinterpret_cast<char*>(&pos[c].Z_trasl[f]), sizeof(pos_raw_data.Z_trasl));
				posfile.read(reinterpret_cast<char*>(&pos[c].W_trasl[f]), sizeof(pos_raw_data.W_trasl));
			}
		}
	}
	return true;
}