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
Combina due layers di animazioni
INPUT: AnimationCurveNode *dest, AnimationCurveNode addend
OUTPUT: AnimationCurveNode *dest
------------------------------------------------------------------------------------------------------------------*/

#include "stdafx.h"
#include "Classes.h"
#include "MATH/math_Functions.h"


void APB_Combine_AnimLayers (AnimationCurveNode *dest, AnimationCurveNode addend)
{
	if (addend.tX_flag)																	// Traslazione X
	{
		if (dest->tX_flag)
			for (unsigned int f = 0; f < dest->tX.KeyValueFloat.size(); f++)
				dest->tX.KeyValueFloat[f] += addend.tX.KeyValueFloat[f];
		else
		{
			dest->tX = addend.tX;
			dest->tX_flag = true;
		}
	}
	if (addend.tY_flag)																	// Traslazione Y
	{
		if (dest->tY_flag)
			for (unsigned int f = 0; f < dest->tY.KeyValueFloat.size(); f++)
				dest->tY.KeyValueFloat[f] += addend.tY.KeyValueFloat[f];
		else
		{
			dest->tY = addend.tY;
			dest->tY_flag = true;
		}
	}
	if (addend.tZ_flag)																	// Traslazione Z
	{
		if (dest->tZ_flag)
			for (unsigned int f = 0; f < dest->tZ.KeyValueFloat.size(); f++)
				dest->tZ.KeyValueFloat[f] += addend.tZ.KeyValueFloat[f];
		else
		{
			dest->tZ = addend.tZ;
			dest->tZ_flag = true;
		}
	}
	if (addend.rX_flag)																	// Rotazione X
	{
		if (dest->rX_flag)
			for (unsigned int f = 0; f < dest->rX.KeyValueFloat.size(); f++)
			{
				dest->rX.KeyValueFloat[f] += addend.rX.KeyValueFloat[f];
				mathWrapAngle180(&dest->rX.KeyValueFloat[f]);
			}
		else
		{
			dest->rX = addend.rX;
			dest->rX_flag = true;
		}
	}
	if (addend.rY_flag)																	// Rotazione Y
	{
		if (dest->rY_flag)
			for (unsigned int f = 0; f < dest->rY.KeyValueFloat.size(); f++)
			{
				dest->rY.KeyValueFloat[f] += addend.rY.KeyValueFloat[f];
				mathWrapAngle180(&dest->rY.KeyValueFloat[f]);
			}
		else
		{
			dest->rY = addend.rY;
			dest->rY_flag = true;
		}
	}
	if (addend.rZ_flag)																	// Rotazione Z
	{
		if (dest->rZ_flag)
			for (unsigned int f = 0; f < dest->rZ.KeyValueFloat.size(); f++)
			{
				dest->rZ.KeyValueFloat[f] += addend.rZ.KeyValueFloat[f];
				mathWrapAngle180(&dest->rZ.KeyValueFloat[f]);
			}
		else
		{
			dest->rZ = addend.rZ;
			dest->rZ_flag = true;
		}
	}
	if (addend.sX_flag)																	// Scalatura X
	{
		if (dest->sX_flag)
			for (unsigned int f = 0; f < dest->sX.KeyValueFloat.size(); f++)
				dest->sX.KeyValueFloat[f] *= addend.sX.KeyValueFloat[f];
		else
		{
			dest->sX = addend.sX;
			dest->sX_flag = true;
		}
	}
	if (addend.sY_flag)																	// Scalatura Y
	{
		if (dest->sY_flag)
			for (unsigned int f = 0; f < dest->sY.KeyValueFloat.size(); f++)
				dest->sY.KeyValueFloat[f] *= addend.sY.KeyValueFloat[f];
		else
		{
			dest->sY = addend.sY;
			dest->sY_flag = true;
		}
	}
	if (addend.sZ_flag)																	// Scalatura Z
	{
		if (dest->sZ_flag)
			for (unsigned int f = 0; f < dest->sZ.KeyValueFloat.size(); f++)
				dest->sZ.KeyValueFloat[f] *= addend.sZ.KeyValueFloat[f];
		else
		{
			dest->sZ = addend.sZ;
			dest->sZ_flag = true;
		}
	}
}