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
Scrittura Connections del blendshape
INPUT: TMT_CLASS &tmt
OUTPUT: ofstream &out
------------------------------------------------------------------------------------------------------------------*/

#include "stdafx.h"
#include "Classes.h"
#include "FBX/FBX_Functions.h"


void FBX_Write_Connection_Blendshape (TMT_CLASS &tmt, ofstream &out)
{
	unsigned int m = tmt.TMT_Material.Number;
	unsigned int g = tmt.mesh2_group;
	unsigned int b = tmt.mesh2_bone;

	out << "	C: \"OO\"," << nodeID(25,g) << "," << nodeID(0) << "\n";											// Null 0, Root node
	out << "	C: \"OO\"," << nodeID(26,g) << "," << nodeID(25,g) << "\n";											// Mesh 0, Null 0
	out << "	C: \"OO\"," << nodeID(21,m) << "," << nodeID(26,g) << "\n";											// Material, Mesh 0
	out << "	C: \"OO\"," << nodeID(27,g) << "," << nodeID(26,g) << "\n";											// Geometry 0, Mesh 0
	out << "	C: \"OO\"," << nodeID(31,g) << "," << nodeID(27,g) << "\n";											// Deformer bone, Geometry 0
    out << "	C: \"OO\"," << nodeID(32,b,g) << "," << nodeID(31,g) << "\n";										// Subdeformer bone, Deformer bone
    out << "	C: \"OO\"," << nodeID(15,b) << "," << nodeID(32,b,g) << "\n";										// Bone, Subdeformer bone
	out << "	C: \"OO\"," << nodeID(28,g) << "," << nodeID(27,g) << "\n";											// Deformer 0, Geometry 0

    for (unsigned int n = 1; n <= tmt.nBlendshapes; n++)
    {
        out << "	C: \"OO\"," << nodeID(29,g,n) << "," << nodeID(28,g) << "\n";									// Subdeformer, Deformer 0
		out << "	C: \"OO\"," << nodeID(30,g,n) << "," << nodeID(29,g,n) << "\n";									// Geometry, Subdeformer
    }
}