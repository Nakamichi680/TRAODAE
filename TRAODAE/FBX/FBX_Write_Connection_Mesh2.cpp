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
Scrittura Connections del gruppo MESH 2
INPUT: vector <MESH2_CLASS> &mesh2, vector < vector < vector <int> > > &MESH2_FACES, CHR_MESH2_LIST &chr_mesh2_list
OUTPUT: ofstream &out
------------------------------------------------------------------------------------------------------------------*/

#include "stdafx.h"
#include "Classes.h"
#include "FBX/FBX_Functions.h"


void FBX_Write_Connection_Mesh2 (vector <MESH2_CLASS> &mesh2,
                                 vector < vector < vector <int> > > &MESH2_FACES,
                                 CHR_MESH2_LIST &chr_mesh2_list,
                                 ofstream &out)
{
    for (unsigned int g = 0; g < chr_mesh2_list.nMeshes2; g++)
        if (mesh2[g].nV != 0)										// Controlla che il gruppo abbia almeno un vertice
        {
            out << "	C: \"OO\"," << nodeID(16,g) << "," << nodeID(0) << "\n";											// Null, Root node
            for (unsigned int el = 0; el < mesh2[g].nElements; el++)
                if (MESH2_FACES[g][el].size() > 2)					// Controlla che l'elemento abbia almeno una faccia
                {
                    int m = mesh2[g].arrMat_Ref[el];
                    int b = mesh2[g].Bone;
                    out << "	C: \"OO\"," << nodeID(17,g,el) << "," << nodeID(16,g) << "\n";								// Mesh, Null
                    out << "	C: \"OO\"," << nodeID(21,m) << "," << nodeID(17,g,el) << "\n";								// Material, Mesh
                    out << "	C: \"OO\"," << nodeID(18,g,el) << "," << nodeID(17,g,el) << "\n";							// Geometry, Mesh
                    out << "	C: \"OO\"," << nodeID(19,g,el) << "," << nodeID(18,g,el) << "\n";							// Deformer, Geometry
                    out << "	C: \"OO\"," << nodeID(20,b,g,el) << "," << nodeID(19,g,el) << "\n";							// Subdeformer, Deformer
                    out << "	C: \"OO\"," << nodeID(15,b) << "," << nodeID(20,b,g,el) << "\n";							// Bone, SubDeformer
                }
        }
}