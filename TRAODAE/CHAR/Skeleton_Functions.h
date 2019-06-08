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


// Prende in ingresso una bone e restituisce quella da cui essa dipende
int Calculate_Parent (int b, vector <unsigned int> Hierarchy);

// Prende in ingresso una bone e vi applica le coordinate della bone da cui essa dipende
void Calculate_Hierarchy (int b, vector <unsigned int> Hierarchy, vector <matrix4x4> &SKquat);

// Applica le scalature ad una bone. INUTILIZZATO
matrix4x4 Skeleton_Bone_S (matrix4x4 in);

// Applica le trasformazioni dello scheletro alle coordinate dei vertici (funzione originale: "Trans_VS")
void Skeleton_Vertex_TS (float *X, float *Y, float *Z, matrix4x4 SKquat);