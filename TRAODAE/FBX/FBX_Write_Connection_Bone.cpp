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
Scrittura Connections delle bones
INPUT: vector <unsigned int> &Hierarchy, CHR_HEADER &chr_header
OUTPUT: ofstream &out
------------------------------------------------------------------------------------------------------------------*/

#include "stdafx.h"
#include "CHAR/Skeleton_Functions.h"
#include "FBX/FBX_Functions.h"


void FBX_Write_Connection_Bone (vector <unsigned int> &Hierarchy, CHR_HEADER &chr_header, ofstream &out)
{
    for (unsigned int b = 0; b < chr_header.nBONES; b++)
    {
        int p = Calculate_Parent(b, Hierarchy);		// Questa funzione restituisce la bone di livello superiore di "b"
        if (b == 0)
            out << "    C: \"OO\",1500,0\n";																				// Bone 0, Root node
        else
            out << "    C: \"OO\"," << nodeID(15,b) << "," << nodeID(15,p) << "\n";											// Bone, Parent bone
        out << "    C: \"OO\"," << nodeID(22,b) << "," << nodeID(15,b) << "\n";												// Nodeattribute, Bone
    }
}