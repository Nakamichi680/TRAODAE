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
Scrittura BindPose
INPUT: FBX_COUNT_CLASS FBX_Count, MESH1_CLASS &mesh1, vector <MESH2_CLASS> &mesh2, vector < vector <int> > &MESH1_FACES,
	   vector < vector < vector <int> > > &MESH2_FACES, CHR_HEADER &chr_header, CHR_MESH2_LIST &chr_mesh2_list, vector <matrix4x4> &SKquat
OUTPUT: ofstream &out
------------------------------------------------------------------------------------------------------------------*/

#include "stdafx.h"

#include "Classes.h"
#include "FBX/FBX_Functions.h"


void FBX_Write_BindPose (FBX_COUNT_CLASS FBX_Count,										// Per il conteggio dei bindpose
                         MESH1_CLASS &mesh1,											// Per leggere il numero di elementi del gruppo mesh 1
                         vector <MESH2_CLASS> &mesh2,									// Per leggere il numero di elementi del gruppo mesh 2
                         vector < vector <int> > &MESH1_FACES,							// Per controllare il numero di facce dell'elemento
                         vector < vector < vector <int> > > &MESH2_FACES,				// Per controllare il numero di facce dell'elemento
                         CHR_HEADER &chr_header,										// Per leggere il numero di bones
                         CHR_MESH2_LIST &chr_mesh2_list,								// Per leggere il numero di gruppi del blocco mesh 2
                         vector <matrix4x4> &SKquat,									// Coordinate di traslazione dello scheletro
                         ofstream &out)
{
    out << "	Pose: " << nodeID(80) << ", \"Pose::T_POSE\", \"BindPose\" {\n";			// Intestazione
    out << "		Type: \"BindPose\"\n";
    out << "		Version: 100\n";
    out << "		NbPoseNodes: " << FBX_Count.BindPose << "\n";
    for (unsigned int b = 0; b < chr_header.nBONES; b++)									// Bind_pose bones
    {
        out << "		PoseNode:  {\n";
        out << "			Node: " << nodeID(15,b) << "\n";
        out << "			Matrix: *16 {\n";
        out << "				a: 1,0,0,0,0,1,0,0,0,0,1,0," << SKquat[b].row4[0] << "," << SKquat[b].row4[1] << "," << SKquat[b].row4[2] << "," << SKquat[b].row4[3] << "\n";
        out << "			}\n";
        out << "		}\n";
    }
    for (unsigned int el = 0; el < mesh1.nElements; el++)									// Bind_pose elementi gruppo mesh 1
        if (MESH1_FACES[el].size() > 2)				// Controlla che l'elemento abbia almeno una faccia
        {
            out << "		PoseNode:  {\n";
            out << "			Node: " << nodeID(11,el) << "\n";
            out << "			Matrix: *16 {\n";
            out << "				a: 1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1\n";
            out << "			}\n";
            out << "		}\n";
        }
    for (unsigned int g = 0; g < chr_mesh2_list.nMeshes2; g++)								// Bind_pose elementi gruppo mesh 2
        for (unsigned int el = 0; el < mesh2[g].nElements; el++)
            if (MESH2_FACES[g][el].size() > 2)		// Controlla che l'elemento abbia almeno una faccia
            {
                out << "		PoseNode:  {\n";
                out << "			Node: " << nodeID(17,g,el) << "\n";
                out << "			Matrix: *16 {\n";
                out << "				a: 1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1\n";
                out << "			}\n";
                out << "		}\n";
            }
    out << "	}\n";
}