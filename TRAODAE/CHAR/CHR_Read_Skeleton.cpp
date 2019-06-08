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
Legge lo scheletro del CHR
INPUT: int nBONES, ifstream &chrfile
OUTPUT: vector <unsigned int> &Hierarchy, vector <string> &Bone_name, vector <matrix4x4> &SKquat,
		vector <matrix4x4> &BONESquat, vector <int> &Anim_bones
------------------------------------------------------------------------------------------------------------------*/

#include "stdafx.h"
#include "CHAR/CHR_Struct.h"
#include "Classes.h"
#include "CHAR/Skeleton_Functions.h"


void CHR_Read_Skeleton (unsigned int nBONES,					// Numero di bones dello scheletro
                        vector <unsigned int> &Hierarchy,       // Vettore contenente i valori di gerarchia di tutte le bones
                        vector <string> &Bone_name,             // Nomi delle bones (verranno scritti nel file FBX)
                        vector <matrix4x4> &SKquat,             // Valori di traslazione e scalatura (non usati) di ogni bone da applicare ai vertici ed al SubDeformer
                        vector <matrix4x4> &BONESquat,          // Valori di traslazione e scalatura di ogni bone da applicare allo scheletro
                        vector <int> &Anim_bones,               // Contiene gli indici delle bones non DYNAMIC
                        ifstream &chrfile)                      // Lo stream contenente il file CHR
{
    CHR_BONE chr_bone;
    char temp_name[64];
    //char TXT[MAX];
	//strcpy(TXT, charname);
    //strcat(TXT, ".TXT");
    ofstream companion, debug;
    //companion.open(TXT);                    // File necessario per il CHR importer
    debug.open("TRAODAE_DEBUG.TXT");        // File con informazioni sulla gerarchia delle bones
    //companion << "----------  TRAOD Animation Exporter by Nakamichi680  -----------" << endl << endl;
    //companion << "DO NOT MODIFY THIS FILE!" << endl << endl;
    //companion << charname << " " << nBONES << endl;*/

    for (unsigned int b = 0; b < nBONES; b++)				// Questo ciclo legge ogni bone e ne applica le trasformazioni mano a mano
    {
        chrfile.read(reinterpret_cast<char*>(&Hierarchy[b]), sizeof(chr_bone.Hierarchy));
        chrfile.read(temp_name, 64);
        chrfile.seekg(12, ios_base::cur);
        chrfile.read(reinterpret_cast<char*>(&SKquat[b].row1[0]), sizeof(chr_bone.X_scale));
        chrfile.read(reinterpret_cast<char*>(&SKquat[b].row1[1]), sizeof(chr_bone.Xy_scale));
        chrfile.read(reinterpret_cast<char*>(&SKquat[b].row1[2]), sizeof(chr_bone.Xz_scale));
        chrfile.read(reinterpret_cast<char*>(&SKquat[b].row1[3]), sizeof(chr_bone.Xw_scale));
        chrfile.read(reinterpret_cast<char*>(&SKquat[b].row2[0]), sizeof(chr_bone.Yx_scale));
        chrfile.read(reinterpret_cast<char*>(&SKquat[b].row2[1]), sizeof(chr_bone.Y_scale));
        chrfile.read(reinterpret_cast<char*>(&SKquat[b].row2[2]), sizeof(chr_bone.Yz_scale));
        chrfile.read(reinterpret_cast<char*>(&SKquat[b].row2[3]), sizeof(chr_bone.Yw_scale));
        chrfile.read(reinterpret_cast<char*>(&SKquat[b].row3[0]), sizeof(chr_bone.Zx_scale));
        chrfile.read(reinterpret_cast<char*>(&SKquat[b].row3[1]), sizeof(chr_bone.Zy_scale));
        chrfile.read(reinterpret_cast<char*>(&SKquat[b].row3[2]), sizeof(chr_bone.Z_scale));
        chrfile.read(reinterpret_cast<char*>(&SKquat[b].row3[3]), sizeof(chr_bone.Zw_scale));
        chrfile.read(reinterpret_cast<char*>(&SKquat[b].row4[0]), sizeof(chr_bone.X1_trasl));
        chrfile.read(reinterpret_cast<char*>(&SKquat[b].row4[1]), sizeof(chr_bone.Y1_trasl));
        chrfile.read(reinterpret_cast<char*>(&SKquat[b].row4[2]), sizeof(chr_bone.Z1_trasl));
        chrfile.read(reinterpret_cast<char*>(&SKquat[b].row4[3]), sizeof(chr_bone.W1_trasl));
        chrfile.read(reinterpret_cast<char*>(&chr_bone.Ragdoll_X), sizeof(chr_bone.Ragdoll_X));
        chrfile.read(reinterpret_cast<char*>(&chr_bone.Ragdoll_Xy), sizeof(chr_bone.Ragdoll_Xy));
        chrfile.read(reinterpret_cast<char*>(&chr_bone.Ragdoll_Xz), sizeof(chr_bone.Ragdoll_Xz));
        chrfile.read(reinterpret_cast<char*>(&chr_bone.Ragdoll_Xw), sizeof(chr_bone.Ragdoll_Xw));
        chrfile.read(reinterpret_cast<char*>(&chr_bone.Ragdoll_Yx), sizeof(chr_bone.Ragdoll_Yx));
        chrfile.read(reinterpret_cast<char*>(&chr_bone.Ragdoll_Y), sizeof(chr_bone.Ragdoll_Y));
        chrfile.read(reinterpret_cast<char*>(&chr_bone.Ragdoll_Yz), sizeof(chr_bone.Ragdoll_Yz));
        chrfile.read(reinterpret_cast<char*>(&chr_bone.Ragdoll_Yw), sizeof(chr_bone.Ragdoll_Yw));
        chrfile.read(reinterpret_cast<char*>(&chr_bone.Ragdoll_Zx), sizeof(chr_bone.Ragdoll_Zx));
        chrfile.read(reinterpret_cast<char*>(&chr_bone.Ragdoll_Zy), sizeof(chr_bone.Ragdoll_Zy));
        chrfile.read(reinterpret_cast<char*>(&chr_bone.Ragdoll_Z), sizeof(chr_bone.Ragdoll_Z));
        chrfile.read(reinterpret_cast<char*>(&chr_bone.Ragdoll_Zw), sizeof(chr_bone.Ragdoll_Zw));
        chrfile.read(reinterpret_cast<char*>(&chr_bone.X2_trasl), sizeof(chr_bone.X2_trasl));
        chrfile.read(reinterpret_cast<char*>(&chr_bone.Y2_trasl), sizeof(chr_bone.Y2_trasl));
        chrfile.read(reinterpret_cast<char*>(&chr_bone.Z2_trasl), sizeof(chr_bone.Z2_trasl));
        chrfile.read(reinterpret_cast<char*>(&chr_bone.W2_trasl), sizeof(chr_bone.W2_trasl));
        chrfile.seekg(128, ios_base::cur);
        chrfile.read(reinterpret_cast<char*>(&chr_bone.Unknown3), sizeof(chr_bone.Unknown3));
        chrfile.read(reinterpret_cast<char*>(&chr_bone.Unknown4), sizeof(chr_bone.Unknown4));
        chrfile.read(reinterpret_cast<char*>(&chr_bone.Unknown5), sizeof(chr_bone.Unknown5));
        chrfile.read(reinterpret_cast<char*>(&chr_bone.Unknown6), sizeof(chr_bone.Unknown6));
        chrfile.read(reinterpret_cast<char*>(&chr_bone.Unknown7), sizeof(chr_bone.Unknown7));
        chrfile.seekg(92, ios_base::cur);
        Bone_name[b] = temp_name;
        BONESquat[b] = SKquat[b];

        ///////////////////////////////////     Questa parte serve per scrivere le FBX connections delle animazioni     /////////////////////////////////
        string DYNAMIC("DYNAMIC"), temp;
        size_t pos = 0;
        temp = Bone_name[b];
        if ((pos = temp.find(DYNAMIC)) == std::string::npos)			// Scarta le bones che contengono "DYNAMIC" nel nome
            Anim_bones.push_back(b);
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        // Le scalature per i vertici vengono bloccate a 1-1-1 perchè vengono ereditate dallo scheletro. Le traslazioni, invece, restano e vengono applicate ai vertici
        SKquat[b].row1[0] = 1;      SKquat[b].row1[1] = 0;      SKquat[b].row1[2] = 0;      SKquat[b].row1[3] = 0;
        SKquat[b].row2[0] = 0;      SKquat[b].row2[1] = 1;      SKquat[b].row2[2] = 0;      SKquat[b].row2[3] = 0;
        SKquat[b].row3[0] = 0;      SKquat[b].row3[1] = 0;      SKquat[b].row3[2] = 1;      SKquat[b].row3[3] = 0;
        Calculate_Hierarchy(b, Hierarchy, SKquat);

        /*companion << hex << Hierarchy[b] << dec << " " << Bone_name[b] << " ";
        companion << chr_bone.Ragdoll_X << " " << chr_bone.Ragdoll_Xy << " " << chr_bone.Ragdoll_Xz << " " << chr_bone.Ragdoll_Xw << " ";
        companion << chr_bone.Ragdoll_Yx << " " << chr_bone.Ragdoll_Y << " " << chr_bone.Ragdoll_Yz << " " << chr_bone.Ragdoll_Yw << " ";
        companion << chr_bone.Ragdoll_Zx << " " << chr_bone.Ragdoll_Zy << " " << chr_bone.Ragdoll_Z << " " << chr_bone.Ragdoll_Zw << " ";
        companion << chr_bone.X2_trasl << " " << chr_bone.Y2_trasl << " " << chr_bone.Z2_trasl << " " << chr_bone.W2_trasl << " ";
        companion << chr_bone.Unknown3 << " " << chr_bone.Unknown4 << " " << chr_bone.Unknown5 << " " << chr_bone.Unknown6 << " " << chr_bone.Unknown7 << endl;*/
        debug << "Codice gerarchia bone: " << setw(5) << std::hex << Hierarchy[b] << "     Nome bone: " << Bone_name[b] << endl;
    }
    //companion.close();
    debug.close();
}