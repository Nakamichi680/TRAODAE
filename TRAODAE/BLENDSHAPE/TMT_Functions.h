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


// Legge il file dei blend shapes (vertici, normals, UVs)
bool TMT_Read(ifstream &tmtfile, TMT_CLASS &tmt, vector <MESH2_CLASS> &mesh2, vector <matrix4x4> &SKquat, vector <Material> &Materials, IO_CLASS IO);

// Conversione strip del gruppo MESH 2 associato al blendshape in facce esplicite, senza mantenere la suddivisione in elementi
void Calculate_Faces_Blendshape (TMT_CLASS &tmt,vector <MESH2_CLASS> &mesh2,vector <int> &BLENDSHAPE_FACES);