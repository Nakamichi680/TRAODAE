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
Ruota la matrice in ingresso attorno l'asse Z
INPUT: matrix4x4 matrix, float angle (in gradi)
OUTPUT: matrix4x4
------------------------------------------------------------------------------------------------------------------*/

#include "stdafx.h"
#include "Classes.h"
#include "MATH/math_Functions.h"


matrix4x4 mathRotZ (matrix4x4 matrix, float angle)
{
	angle *= 3.141593f / 180;			// Conversione da gradi a radianti
	matrix4x4 rotMatrix;
	rotMatrix.row1[0] = cos(angle);			rotMatrix.row1[1] = sin(angle);			rotMatrix.row1[2] = 0;			rotMatrix.row1[3] = 0;
	rotMatrix.row2[0] = -sin(angle);		rotMatrix.row2[1] = cos(angle);			rotMatrix.row2[2] = 0;			rotMatrix.row2[3] = 0;
	rotMatrix.row3[0] = 0;					rotMatrix.row3[1] = 0;					rotMatrix.row3[2] = 1;			rotMatrix.row3[3] = 0;
	rotMatrix.row4[0] = 0;					rotMatrix.row4[1] = 0;					rotMatrix.row4[2] = 0;			rotMatrix.row4[3] = 1;
	return mathMulMatrices(rotMatrix, matrix);
}