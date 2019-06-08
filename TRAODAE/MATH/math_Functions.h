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


#pragma once
#include "Classes.h"


// Restituisce gli angoli euleriani partendo da una matrice
EulerRotation mathMatrixToEuler (matrix4x4 matrix);

// Moltiplica due matrici
matrix4x4 mathMulMatrices (matrix4x4 a, matrix4x4 b);

// Moltiplica due quaternioni
Quaternion mathMulQuaternions (Quaternion a, Quaternion b);

// Normalizza il quaternione
void mathQuatNormalise (Quaternion *quat);

// Converte il quaternione in matrice
matrix4x4 mathQuatToMatrix (Quaternion quat);

// Converti i radianti in gradi
void mathRadToDeg (EulerRotation *rad);

// Ruota le traslazioni attorno i 3 assi XYZ
Translation mathRot (Translation input, matrix4x4 rotMatrix);

// Ruota la matrice in ingresso attorno l'asse X. INUTILIZZATO
matrix4x4 mathRotX (matrix4x4 matrix, float angle);

// Ruota la matrice in ingresso attorno l'asse Y. INUTILIZZATO
matrix4x4 mathRotY (matrix4x4 matrix, float angle);

// Ruota la matrice in ingresso attorno l'asse Z
matrix4x4 mathRotZ (matrix4x4 matrix, float angle);

// Blocca l'angolo euleriano nel range -180/+180 gradi
void mathWrapAngle180 (float *angle);