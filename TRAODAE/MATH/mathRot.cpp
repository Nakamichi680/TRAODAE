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
Ruota le traslazioni attorno i 3 assi XYZ
INPUT: Translation input, matrix4x4 rotMatrix
OUTPUT: Translation
------------------------------------------------------------------------------------------------------------------*/

#include "stdafx.h"
#include "Classes.h"


Translation mathRot (Translation input, matrix4x4 rotMatrix)
{
	Translation output;
	output.xt = rotMatrix.row1[0] * input.xt + rotMatrix.row2[0] * input.yt + rotMatrix.row3[0] * input.zt + rotMatrix.row4[0];
	output.yt = rotMatrix.row1[1] * input.xt + rotMatrix.row2[1] * input.yt + rotMatrix.row3[1] * input.zt + rotMatrix.row4[1];
	output.zt = rotMatrix.row1[2] * input.xt + rotMatrix.row2[2] * input.yt + rotMatrix.row3[2] * input.zt + rotMatrix.row4[2];
	return output;
}