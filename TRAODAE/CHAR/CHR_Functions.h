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


#pragma once
#include "Classes.h"


// Legge le textures dal file CHR e ne salva le informazioni, le esporta in DDS, le converte in BMP e separa il canale alfa
void CHR_Export_Textures (vector <TextureHeader> &TextureHeader, FBX_COUNT_CLASS *FBX_Count, ifstream &chrfile, IO_CLASS &IO);

// Lettura lista materiali file CHR
void CHR_Read_Materials (vector <Material> &Materials, ifstream &chrfile);

// Legge tutto il gruppo MESH1 (vertici, facce ed elementi)
void CHR_Read_Mesh1 (MESH1_CLASS &mesh1, vector <matrix4x4> &SKquat, ifstream &chrfile);

// Legge un singolo gruppo MESH2 (vertici, facce ed elementi)
void CHR_Read_Mesh2 (MESH2_CLASS *mesh2, vector <matrix4x4> &SKquat, ifstream &chrfile);

// Legge lo scheletro del CHR
void CHR_Read_Skeleton (unsigned int nBONES,
						vector <unsigned int> &Hierarchy,
						vector <string> &Bone_name,
						vector <matrix4x4> &SKquat,
						vector <matrix4x4> &BONESquat,
						vector <int> &Anim_bones,
						ifstream &chrfile);

// Conversione strip gruppo MESH 1 in facce esplicite per file FBX
void Calculate_Faces_Mesh1 (MESH1_CLASS &mesh1, vector < vector <unsigned short> > &MESH1_vINDX, vector < vector <int> > &MESH1_FACES);

// Conversione strip gruppo MESH 2 in facce esplicite per file FBX
void Calculate_Faces_Mesh2 (vector <MESH2_CLASS> &mesh2, vector < vector < vector <unsigned short> > > &MESH2_vINDX, vector < vector < vector <int> > > &MESH2_FACES);