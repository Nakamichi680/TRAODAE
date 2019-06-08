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
Scrittura bones
INPUT: CHR_HEADER &chr_header, vector <string> &Bone_name, vector <matrix4x4> &BONESquat
OUTPUT: ofstream &out
------------------------------------------------------------------------------------------------------------------*/

#include "stdafx.h"
#include "Classes.h"
#include "FBX/FBX_Functions.h"


void FBX_Write_Bone (CHR_HEADER &chr_header, vector <string> &Bone_name, vector <matrix4x4> &BONESquat, ofstream &out)
{
    for (unsigned int b = 0; b < chr_header.nBONES; b++)
    {
		/////////////////////// SCRITTURA NODEATTRIBUTE BONE
        out << "	NodeAttribute: " << nodeID(22,b) << ", \"NodeAttribute::\", \"LimbNode\" {\n";
        out << "		Properties70:  {\n";
        out << "			P: \"Size\", \"double\", \"Number\", \"\",200\n";			// Diametro della sfera della bone
        out << "		}\n";
        out << "		TypeFlags: \"Skeleton\"\n";
        out << "	}\n";

		/////////////////////// SCRITTURA BONE CON COORDINATE DI TRASLAZIONE E SCALATURA
        out << "	Model: " << nodeID(15,b) << ", \"Model::" << Bone_name[b] << "\", \"LimbNode\" {\n";
        out << "		Version: 232\n";
        out << "		Properties70:  {\n";
        out << "			P: \"RotationActive\", \"bool\", \"\", \"\",1\n";
        out << "			P: \"InheritType\", \"enum\", \"\", \"\",1\n";
        out << "			P: \"ScalingMax\", \"Vector3D\", \"Vector\", \"\",0,0,0\n";
        out << "			P: \"DefaultAttributeIndex\", \"int\", \"Integer\", \"\",0\n";
        out << "			P: \"Lcl Translation\", \"Lcl Translation\", \"\", \"A\",";
		out << BONESquat[b].row4[0] << "," << BONESquat[b].row4[1] << "," << BONESquat[b].row4[2] << "\n";
        out << "			P: \"Lcl Rotation\", \"Lcl Rotation\", \"\", \"A\",0,0,0\n";
        out << "			P: \"Lcl Scaling\", \"Lcl Scaling\", \"\", \"A\",";
        out << BONESquat[b].row1[0] + BONESquat[b].row2[0] + BONESquat[b].row3[0] << ",";
        out << BONESquat[b].row1[1] + BONESquat[b].row2[1] + BONESquat[b].row3[1] << ",";
        out << BONESquat[b].row1[2] + BONESquat[b].row2[2] + BONESquat[b].row3[2]<< "\n";
        out << "		}\n";
        out << "		Shading: Y\n";
        out << "		Culling: \"CullingOff\"\n";
        out << "	}\n";
    }
}