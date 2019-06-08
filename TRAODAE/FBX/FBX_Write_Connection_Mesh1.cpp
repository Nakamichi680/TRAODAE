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
Scrittura Connections del gruppo MESH 1
INPUT: MESH1_CLASS &mesh1, vector < vector <int> > &MESH1_FACES, vector < vector <unsigned short> > &MESH1_vINDX, CHR_HEADER &chr_header
OUTPUT: ofstream &out
------------------------------------------------------------------------------------------------------------------*/

#include "stdafx.h"
#include "Classes.h"
#include "FBX/FBX_Functions.h"


void FBX_Write_Connection_Mesh1 (MESH1_CLASS &mesh1,
                                 vector < vector <int> > &MESH1_FACES,
                                 vector < vector <unsigned short> > &MESH1_vINDX,
                                 CHR_HEADER &chr_header,
                                 ofstream &out)
{
    out << "	C: \"OO\"," << nodeID(99) << "," << nodeID(0) << "\n";														// Null, Root node
    for (unsigned int el = 0; el < mesh1.nElements; el++)
        if (MESH1_FACES[el].size() > 2)								// Controlla che l'elemento abbia almeno una faccia
        {
            int m = mesh1.arrMat_Ref[el];
            out << "	C: \"OO\"," << nodeID(11,el) << "," << nodeID(99) << "\n";											// Mesh, Null
            out << "	C: \"OO\"," << nodeID(21,m) << "," << nodeID(11,el) << "\n";										// Material, Mesh
            out << "	C: \"OO\"," << nodeID(12,el) << "," << nodeID(11,el) << "\n";										// Geometry, Mesh
            out << "	C: \"OO\"," << nodeID(13,el) << "," << nodeID(12,el) << "\n";										// Deformer, Geometry

            for (unsigned int b = 0; b < chr_header.nBONES; b++)	// Questo ciclo controlla se ogni bone è presente nell'elemento
                for (unsigned int check_v = 0; check_v < MESH1_vINDX[el].size(); check_v++)
                    if (mesh1.Bone1[MESH1_vINDX[el][check_v]] == b || mesh1.Bone2[MESH1_vINDX[el][check_v]] == b)	// Se la bone viene trovata
                    {
                        check_v = MESH1_vINDX[el].size() + 1;		// Serve ad impedire che venga controllata la stessa bone più volte interrompendo il ciclo for a monte
                        out << "	C: \"OO\"," << nodeID(14,b,el) << "," << nodeID(13,el) << "\n";							// Subdeformer, Deformer
                        out << "	C: \"OO\"," << nodeID(15,b) << "," << nodeID(14,b,el) <<"\n";							// Bone, Subdeformer
                    }
        }
}