/* Tomb Raider - The Angel of Darkness Animation Exporter
Copyright (c) 2017-2019 Nakamichi680

This file is part of "Tomb Raider - The Angel of Darkness Animation Exporter".

"Tomb Raider - The Angel of Darkness Animation Exporter" is free software: you can redistribute it and/or modify it under the terms of the
GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.

"Tomb Raider - The Angel of Darkness Animation Exporter" is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without
even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with "Tomb Raider - The Angel of Darkness Animation Exporter".
If not, see <http://www.gnu.org/licenses/>.

Copyright (c) Square Enix Ltd. Lara Croft and Tomb Raider are trademarks or registered trademarks of Square Enix Ltd.
Copyright (c) Autodesk, Inc. and/or its licensors. FBX is a registered trademarks or trademarks of Autodesk, Inc. and/or its subsidiaries
and/or affiliates in the USA and other countries.*/


/*------------------------------------------------------------------------------------------------------------------
Conversione strip del gruppo MESH 2 associato al blendshape in facce esplicite, senza mantenere la suddivisione in elementi
INPUT: TMT_CLASS &tmt, vector <MESH2_CLASS> &mesh2
OUTPUT: vector <int> &BLENDSHAPE_FACES
------------------------------------------------------------------------------------------------------------------*/

#include "stdafx.h"
#include "Classes.h"


void Calculate_Faces_Blendshape (TMT_CLASS &tmt, vector <MESH2_CLASS> &mesh2, vector <int> &BLENDSHAPE_FACES)
{
	unsigned int g = tmt.mesh2_group;
	for (unsigned int el = 0; el < mesh2[g].nElements; el++)			// Ogni ciclo è un elemento
	{
		if (mesh2[g].arrDraw_Mode[el] == 5)						// Se il Draw mode è uguale a 5 si tratta di un triangle strip
		{
			if (mesh2[g].arrOffset[el] % 2 == 0)				// Verifica se il punto d'inizio di ogni frammento dello strip è pari o dispari
			{
				for (int I = mesh2[g].arrOffset[el]; I < (mesh2[g].arrEl_Ind[el] + mesh2[g].arrOffset[el] - 2); I++)
					if (mesh2[g].arrIndex[I] != mesh2[g].arrIndex[I+1] &&
						mesh2[g].arrIndex[I] != mesh2[g].arrIndex[I+2] &&
						mesh2[g].arrIndex[I+1] != mesh2[g].arrIndex[I+2])							// Esclude le facce nulle
					{
						if (I % 2 == 0)			// Se pari
						{
							BLENDSHAPE_FACES.push_back(mesh2[g].arrIndex[I+2]);
							BLENDSHAPE_FACES.push_back(mesh2[g].arrIndex[I+1]);
							BLENDSHAPE_FACES.push_back(mesh2[g].arrIndex[I] ^ -1);			// XOR per formato FBX
						}
						else					// Se dispari
						{
							BLENDSHAPE_FACES.push_back(mesh2[g].arrIndex[I]);
							BLENDSHAPE_FACES.push_back(mesh2[g].arrIndex[I+1]);
							BLENDSHAPE_FACES.push_back(mesh2[g].arrIndex[I+2] ^ -1);		// XOR per formato FBX
						}
					}
			}
			else
			{
				for (int I = 0; I < (mesh2[g].arrEl_Ind[el] - 2); I++)
					if (mesh2[g].arrIndex[I] != mesh2[g].arrIndex[I+1] &&
						mesh2[g].arrIndex[I] != mesh2[g].arrIndex[I+2] &&
						mesh2[g].arrIndex[I+1] != mesh2[g].arrIndex[I+2])							// Esclude le facce nulle
					{
						if (I % 2 == 0)			// Se pari
						{
							BLENDSHAPE_FACES.push_back(mesh2[g].arrIndex[I]);
							BLENDSHAPE_FACES.push_back(mesh2[g].arrIndex[I+1]);
							BLENDSHAPE_FACES.push_back(mesh2[g].arrIndex[I+2] ^ -1);		// XOR per formato FBX
						}
						else					// Se dispari
						{
							BLENDSHAPE_FACES.push_back(mesh2[g].arrIndex[I+2]);
							BLENDSHAPE_FACES.push_back(mesh2[g].arrIndex[I+1]);
							BLENDSHAPE_FACES.push_back(mesh2[g].arrIndex[I] ^ -1);			// XOR per formato FBX
						}
					}
			}
		}
		else													// Se il Draw mode non è 5 si tratta di una lista di facce esplicite
			for (int I = mesh2[g].arrOffset[el]; I < (mesh2[g].arrEl_Ind[el] + mesh2[g].arrOffset[el]);)
			{
				BLENDSHAPE_FACES.push_back(mesh2[g].arrIndex[I+2]);
				BLENDSHAPE_FACES.push_back(mesh2[g].arrIndex[I+1]);
				BLENDSHAPE_FACES.push_back(mesh2[g].arrIndex[I] ^ -1);						// XOR per formato FBX
				I += 3;
			}
	}
}