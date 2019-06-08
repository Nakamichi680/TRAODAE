/* Tomb Raider - The Angel of Darkness Animation Exporter
Copyright (c) 2017-2019 Nakamichi680

This file is part of "Tomb Raider - The Angel of Darkness Animation Exporter".

"Tomb Raider - The Angel of Darkness Animation Exporter" is free software: you can redistribute it and/or modify it under the terms of the
GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.

"Tomb Raider - The Angel of Darkness Animation Exporter" is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without
even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with "Tomb Raider - The Angel of Darkness Animation Exporter".
If not, see <http://www.gnu.org/licenses/>.

Copyright (c) Square Enix Ltd. Lara Croft and Tomb Raider are trademarks or registered trademarks of Square Enix Ltd.*/


/*------------------------------------------------------------------------------------------------------------------
Restituisce una curva di animazione con un valore fisso
INPUT: float value, unsigned int nFrames
OUTPUT: AnimationCurveData
------------------------------------------------------------------------------------------------------------------*/

#include "stdafx.h"
#include "Classes.h"


AnimationCurveData APB_Fill_AnimationCurveData (float value, unsigned int nFrames)
{
	AnimationCurveData outdata;
	for (unsigned int f = 0; f <nFrames; f++)
	{
		outdata.KeyTime.push_back((unsigned long long)f * FBXframe1 + FBXframe1);				// Tempo
		outdata.KeyValueFloat.push_back(value);													// Valore frame
		outdata.KeyAttrFlags.push_back(24840);													// Cubic|TangeantAuto|GenericTimeIndependent|GenericClampProgressive
		outdata.KeyAttrDataFloat.push_back(0);													// RightSlope:0
		outdata.KeyAttrDataFloat.push_back(0);													// NextLeftSlope:0
		outdata.KeyAttrDataFloat.push_back(218434821);											// RightWeight:0.333333, NextLeftWeight:0.333333
		outdata.KeyAttrDataFloat.push_back(0);													// RightVelocity:0, NextLeftVelocity:0
	}
	return outdata;
}