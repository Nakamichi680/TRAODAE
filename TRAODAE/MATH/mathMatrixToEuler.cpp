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
Restituisce gli angoli euleriani partendo da una matrice
INPUT: matrix4x4 matrix
OUTPUT: EulerRotation
------------------------------------------------------------------------------------------------------------------*/

#include "stdafx.h"
#include "Classes.h"


EulerRotation mathMatrixToEuler (matrix4x4 matrix)
{
    EulerRotation output;
    output.x = atan2(matrix.row2[2], matrix.row3[2]);
    float temp = sqrt(pow(matrix.row1[0], 2) + pow(matrix.row1[1], 2));
    output.y = atan2(-matrix.row1[2], temp);
    output.z = atan2(matrix.row1[1], matrix.row1[0]);
    return output;
}