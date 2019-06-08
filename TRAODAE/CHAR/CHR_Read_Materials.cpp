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
Lettura lista materiali file CHR
INPUT: ifstream &chrfile
OUTPUT: vector <Material> &Materials
------------------------------------------------------------------------------------------------------------------*/

#include "stdafx.h"
#include "CHAR/CHR_Struct.h"
#include "Classes.h"


void CHR_Read_Materials (vector <Material> &Materials, ifstream &chrfile)
{
    CHR_HEADER chr_header;
    CHR_MATERIALS_HEADER chr_materials_header;
    CHR_MATERIALS_LIST chr_materials_list;

    streamoff original_position = chrfile.tellg();	// Memorizza la posizione iniziale del cursore nel file per poterci tornare alla fine della funzione
    chrfile.seekg(4, chrfile.beg);					// Posiziona il cursore di lettura all'inizio del file, con offset di 4 bytes per leggere l'offset del blocco textures
    chrfile.read(reinterpret_cast<char*>(&chr_header.TEXTURE_PTR), sizeof(chr_header.TEXTURE_PTR));
    chrfile.seekg(chr_header.TEXTURE_PTR);
    chrfile.read(reinterpret_cast<char*>(&chr_materials_header.nMaterials), sizeof(chr_materials_header.nMaterials));  // Legge il numero di materiali

    for (unsigned int m = 0; m < chr_materials_header.nMaterials; m++)
    {
        Materials.resize(m+1);
		Materials[m].Number = m;
        chrfile.read(reinterpret_cast<char*>(&Materials[m].Type), sizeof(chr_materials_list.TextureMode));		// Legge il tipo di materiale
        chrfile.seekg(6, ios_base::cur);																		// Salta DoubleSided ed Unknown1
        chrfile.read(reinterpret_cast<char*>(&Materials[m].Diffuse), sizeof(chr_materials_list.DiffuseID));		// Legge l'ID diffuse
        chrfile.read(reinterpret_cast<char*>(&Materials[m].Shadow), sizeof(chr_materials_list.ShadowMapID));	// Legge l'ID shadowmap (inutile nei CHR)
        chrfile.read(reinterpret_cast<char*>(&Materials[m].BumpSpec), sizeof(chr_materials_list.BumpSpecID));	// Legge l'ID del bump mapping e dello specular/envelope
        chrfile.read(reinterpret_cast<char*>(&Materials[m].Fur), sizeof(chr_materials_list.FurID));				// Legge l'ID del fur
    }
    chrfile.seekg(original_position);				// Riporta il cursore di lettura dove si trovava prima di entrare in questa funzione
}