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
Generatore ID per nodi del file FBX. Scrive il tipo di nodo (prime due cifre) e fa il padding degi numeri a seguire
INPUT: unsigned int node_type, unsigned int value1, unsigned int value2, unsigned int value3
OUTPUT: string
------------------------------------------------------------------------------------------------------------------*/

#include "stdafx.h"


string nodeID (unsigned int node_type, unsigned int value1 = 0, unsigned int value2 = 0, unsigned int value3 = 0)
{
	ostringstream out;
	switch (node_type)			// La tipologia di nodo (Null, Geometry, Material, Deformer, Texture, ecc.)
	{
	case(0):		// Root node
		out << node_type;
		break;
	case(17):		// CHR Mesh 2 Mesh
	case(18):		// CHR Mesh 2 Geometry
	case(19):		// CHR Mesh 2 Deformer
		out << node_type << setfill('0') << setw(3) << value1 << setw(4) << value2;
		break;
	case(20):		//CHR Mesh 2 Subdeformer
		out << node_type << setfill('0') << setw(2) << value1 << setw(3) << value2 << setw(4) << value3;
		break;
	case(99):		// CHR Mesh 1 Body_null
	case(80):		// CHR Pose
		out << node_type << "0000000000";
		break;
	case(15):		// CHR Bone
	case(22):		// CHR Bone nodeattribute
		out << node_type << setfill('0') << setw(2) << value1;
		break;
	case(16):		// CHR Mesh 2 Null
	case(21):		// CHR Material
	case(25):		// TMT Blendshape 0 Null
	case(26):		// TMT Blendshape 0 Mesh
	case(27):		// TMT Blendshape 0 Geometry
	case(28):		// TMT Blendshape 0 Deformer
	case(31):		// TMT Deformer
		out << node_type << setfill('0') << setw(3) << value1;
		break;
	case(32):		// TMT Subdeformer
		out << node_type << setfill('0') << setw(2) << value1 << setw(3) << value2;
	case(29):		// TMT Blendshape Subdeformer
	case(30):		// TMT Blendshape Geometry
		out << node_type << setfill('0') << setw(3) << value1 << setw(2) << value2;
		break;
	case(11):		// CHR Mesh 1 Mesh
	case(12):		// CHR Mesh 1 Geometry
	case(13):		// CHR Mesh 1 Deformer
	case(23):		// CHR Texture diffuse/bump
	case(24):		// CHR Texture diffuse_alpha/specular/reflection
	case(98):		// CHR AnimationStack
	case(97):		// CHR AnimationLayer
		out << node_type << setfill('0') << setw(4) << value1;
		break;
	case(14):		// CHR Mesh 1 Subdeformer
	case(50):		// CHR AnimationCurveNode Translation
	case(51):		// CHR AnimationCurve Translation X
	case(52):		// CHR AnimationCurve Translation Y
	case(53):		// CHR AnimationCurve Translation Z
	case(60):		// CHR AnimationCurveNode Rotation
	case(61):		// CHR AnimationCurve Rotation X
	case(62):		// CHR AnimationCurve Rotation Y
	case(63):		// CHR AnimationCurve Rotation Z
	case(70):		// CHR AnimationCurveNode Scaling
	case(71):		// CHR AnimationCurve Scaling X
	case(72):		// CHR AnimationCurve Scaling Y
	case(73):		// CHR AnimationCurve Scaling Z
		out << node_type << setfill('0') << setw(2) << value1 << setw(4) << value2;
		break;
	}
	return out.str();
}