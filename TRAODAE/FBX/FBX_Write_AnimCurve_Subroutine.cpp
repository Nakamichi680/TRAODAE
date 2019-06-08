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
Scrittura AnimationCurve
INPUT: int a, int b, short RSTaxis, float CHRtrasl, AnimationCurveNode *Ani_curvenode,
OUTPUT: ofstream &out
------------------------------------------------------------------------------------------------------------------*/

#include "stdafx.h"
#include "Classes.h"
#include "FBX/FBX_Functions.h"


void FBX_Write_AnimCurve_Subroutine (int a,												// Numero animazione selezionata
									 int b,												// Bone
									 short RSTaxis,										// Traslazione XYZ = 51/52/53, rotazione XYZ = 61/62/63, scalatura XYZ = 71/72/73
									 float CHRtrasl,									// Valore di traslazione proveniente dallo scheletro del CHR
									 AnimationCurveNode *Ani_curvenode,					// Classe contenente i dati da scrivere
									 ofstream &out)										// Flusso di output del file FBX
{
	AnimationCurveData temp;
	if (RSTaxis == 51)						// Traslazione X
		temp = Ani_curvenode->tX;
	if (RSTaxis == 52)						// Traslazione Y
		temp = Ani_curvenode->tY;
	if (RSTaxis == 53)						// Traslazione Z
		temp = Ani_curvenode->tZ;
	if (RSTaxis == 61)						// Rotazione X
		temp = Ani_curvenode->rX;
	if (RSTaxis == 62)						// Rotazione Y
		temp = Ani_curvenode->rY;
	if (RSTaxis == 63)						// Rotazione Z
		temp = Ani_curvenode->rZ;
	if (RSTaxis == 71)						// Scalatura X
		temp = Ani_curvenode->sX;
	if (RSTaxis == 72)						// Scalatura Y
		temp = Ani_curvenode->sY;
	if (RSTaxis == 73)						// Scalatura Z
		temp = Ani_curvenode->sZ;

	out << "	AnimationCurve: " << nodeID(RSTaxis,b,a) << ", \"AnimCurve::\", \"\" {\n";
	out << "		Default: 0\n";
	out << "		KeyVer: 4008\n";
	out << "		KeyTime: *" << temp.KeyTime.size() << " {\n";
	out << "			a: ";
	for (unsigned int k = 0; k < temp.KeyTime.size(); k++)
    {
        out << temp.KeyTime[k];
        if (temp.KeyTime.size() - k != 1)
		{
            out << ",";
            if ((k + 1) % 18 == 0 && k != 0)  out << "\n";
		}
        else out << "\n";
    }
	out << "		}\n";
	out << "		KeyValueFloat: *" << temp.KeyValueFloat.size()  << " {\n";
	out << "			a: ";
	for (unsigned int k = 0; k < temp.KeyValueFloat.size(); k++)
	{
		out << temp.KeyValueFloat[k] + CHRtrasl;
		if (temp.KeyValueFloat.size() - k != 1)
		{
			out << ",";
			if ((k + 1) % 26 == 0 && k != 0)  out << "\n";
		}
		else out << "\n";
	}
	out << "		}\n";
	out << "		KeyAttrFlags: *" << temp.KeyAttrFlags.size()  << " {\n";
	out << "			a: ";
    for (unsigned int k = 0; k < temp.KeyAttrFlags.size(); k++)
    {
        out << temp.KeyAttrFlags[k];
        if (temp.KeyAttrFlags.size() - k != 1)
		{
            out << ",";
            if ((k + 1) % 38 == 0 && k != 0)  out << "\n";
		}
        else out << "\n";
    }
	out << "		}\n";
	out << "		KeyAttrDataFloat: *" << temp.KeyAttrDataFloat.size()  << " {\n";
	out << "			a: ";
    for (unsigned int k = 0; k < temp.KeyAttrDataFloat.size(); k++)
    {
        out << temp.KeyAttrDataFloat[k];
        if (temp.KeyAttrDataFloat.size() - k != 1)
		{
            out << ",";
            if ((k + 1) % 31 == 0 && k != 0)  out << "\n";
		}
        else out << "\n";
    }
	out << "		}\n";
	out << "		KeyAttrRefCount: *" << temp.KeyAttrFlags.size()  << " {\n";
	out << "		a: ";
    for (unsigned int k = 0; k < temp.KeyAttrFlags.size(); k++)
    {
        out << 1;
        if (temp.KeyAttrFlags.size() - k != 1)
		{
            out << ",";
            if ((k + 1) % 100 == 0 && k != 0)  out << "\n";
		}
        else out << "\n";
    }
    out << "		}\n";
    out << "	}\n";
}