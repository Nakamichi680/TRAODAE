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
Converte il quaternione in matrice
INPUT: Quaternion quat
OUTPUT: matrix4x4
------------------------------------------------------------------------------------------------------------------*/

#include "stdafx.h"
#include "Classes.h"


matrix4x4 mathQuatToMatrix (Quaternion quat)
{
    matrix4x4 output;
    output.row1[0] = 1 - (2 * pow(quat.y, 2) + 2 * pow(quat.z, 2));
    output.row1[1] = 2 * quat.z * quat.w + 2 * quat.x * quat.y;
    output.row1[2] = 2 * quat.x * quat.z - 2 * quat.y * quat.w;
    output.row1[3] = 0;
    output.row2[0] = 2 * quat.x * quat.y - 2 * quat.z * quat.w;
    output.row2[1] = 1 - (2 * pow(quat.z, 2) + 2 * pow(quat.x, 2));
    output.row2[2] = 2 * quat.x * quat.w + 2 * quat.y * quat.z;
    output.row2[3] = 0;
    output.row3[0] = 2 * quat.y * quat.w + 2 * quat.x * quat.z;
    output.row3[1] = 2 * quat.y * quat.z - 2 * quat.x * quat.w;
    output.row3[2] = 1 - (2 * pow(quat.x, 2) + 2 * pow(quat.y, 2));
    output.row3[3] = 0;
    output.row4[0] = 0;
    output.row4[1] = 0;
    output.row4[2] = 0;
    output.row4[3] = 1;
    return output;
}