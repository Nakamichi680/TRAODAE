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
Scrittura BindPose del blend shape
INPUT: FBX_COUNT_CLASS FBX_Count, CHR_HEADER &chr_header, TMT_CLASS &tmt, vector <matrix4x4> &SKquat
OUTPUT: ofstream &out
------------------------------------------------------------------------------------------------------------------*/

#include "stdafx.h"
#include "Classes.h"
#include "FBX/FBX_Functions.h"


void FBX_Write_BindPose_Blendshape (FBX_COUNT_CLASS FBX_Count,							// Per il conteggio dei bindpose
									CHR_HEADER &chr_header,								// Per leggere il numero di bones
									TMT_CLASS &tmt,
									vector <matrix4x4> &SKquat,							// Coordinate di traslazione dello scheletro
									ofstream &out)
{
	unsigned int g = tmt.mesh2_group;			// Gruppo MESH 2 associato al blend shape

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
    out << "		PoseNode:  {\n";														// Bind_pose mesh blend shape 0
    out << "			Node: " << nodeID(26,g) << "\n";
    out << "			Matrix: *16 {\n";
    out << "				a: 1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1\n";
    out << "			}\n";
    out << "		}\n";
    out << "	}\n";
}