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
Applica le trasformazioni dello scheletro alle coordinate dei vertici (funzione originale: "Trans_VS")
INPUT: float *X, float *Y, float *Z, matrix4x4 SKquat
OUTPUT: float *X, float *Y, float *Z
------------------------------------------------------------------------------------------------------------------*/

#include "stdafx.h"
#include "Classes.h"


void Skeleton_Vertex_TS (float *X, float *Y, float *Z, matrix4x4 SKquat)
{
	float Xtemp,Ytemp,Ztemp;
	Xtemp = *X;
	Ytemp = *Y;
	Ztemp = *Z;
	*X = Xtemp*SKquat.row1[0]+Ytemp*SKquat.row2[0]+Ztemp*SKquat.row3[0]+SKquat.row4[0];
	*Y = Xtemp*SKquat.row1[1]+Ytemp*SKquat.row2[1]+Ztemp*SKquat.row3[1]+SKquat.row4[1];
	*Z = Xtemp*SKquat.row1[2]+Ytemp*SKquat.row2[2]+Ztemp*SKquat.row3[2]+SKquat.row4[2];
}