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
Moltiplica due matrici
INPUT: matrix4x4 a, matrix4x4 b
OUTPUT: matrix4x4
------------------------------------------------------------------------------------------------------------------*/

#include "stdafx.h"
#include "Classes.h"


matrix4x4 mathMulMatrices (matrix4x4 a, matrix4x4 b)
{
	matrix4x4 out;
	out.row1[0] = a.row1[0] * b.row1[0] + a.row1[1] * b.row2[0] + a.row1[2] * b.row3[0] + a.row1[3] * b.row4[0];
	out.row1[1] = a.row1[0] * b.row1[1] + a.row1[1] * b.row2[1] + a.row1[2] * b.row3[1] + a.row1[3] * b.row4[1];
	out.row1[2] = a.row1[0] * b.row1[2] + a.row1[1] * b.row2[2] + a.row1[2] * b.row3[2] + a.row1[3] * b.row4[2];
	out.row1[3] = a.row1[0] * b.row1[3] + a.row1[1] * b.row2[3] + a.row1[2] * b.row3[3] + a.row1[3] * b.row4[3];
	out.row2[0] = a.row2[0] * b.row1[0] + a.row2[1] * b.row2[0] + a.row2[2] * b.row3[0] + a.row2[3] * b.row4[0];
	out.row2[1] = a.row2[0] * b.row1[1] + a.row2[1] * b.row2[1] + a.row2[2] * b.row3[1] + a.row2[3] * b.row4[1];
	out.row2[2] = a.row2[0] * b.row1[2] + a.row2[1] * b.row2[2] + a.row2[2] * b.row3[2] + a.row2[3] * b.row4[2];
	out.row2[3] = a.row2[0] * b.row1[3] + a.row2[1] * b.row2[3] + a.row2[2] * b.row3[3] + a.row2[3] * b.row4[3];
	out.row3[0] = a.row3[0] * b.row1[0] + a.row3[1] * b.row2[0] + a.row3[2] * b.row3[0] + a.row3[3] * b.row4[0];
	out.row3[1] = a.row3[0] * b.row1[1] + a.row3[1] * b.row2[1] + a.row3[2] * b.row3[1] + a.row3[3] * b.row4[1];
	out.row3[2] = a.row3[0] * b.row1[2] + a.row3[1] * b.row2[2] + a.row3[2] * b.row3[2] + a.row3[3] * b.row4[2];
	out.row3[3] = a.row3[0] * b.row1[3] + a.row3[1] * b.row2[3] + a.row3[2] * b.row3[3] + a.row3[3] * b.row4[3];
	out.row4[0] = a.row4[0] * b.row1[0] + a.row4[1] * b.row2[0] + a.row4[2] * b.row3[0] + a.row4[3] * b.row4[0];
	out.row4[1] = a.row4[0] * b.row1[1] + a.row4[1] * b.row2[1] + a.row4[2] * b.row3[1] + a.row4[3] * b.row4[1];
	out.row4[2] = a.row4[0] * b.row1[2] + a.row4[1] * b.row2[2] + a.row4[2] * b.row3[2] + a.row4[3] * b.row4[2];
	out.row4[3] = a.row4[0] * b.row1[3] + a.row4[1] * b.row2[3] + a.row4[2] * b.row3[3] + a.row4[3] * b.row4[3];
    return out;
}