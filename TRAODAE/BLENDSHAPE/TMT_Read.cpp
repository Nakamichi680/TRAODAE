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
Legge il file dei blend shapes (vertici, normals, UVs)
INPUT: ifstream &tmtfile, vector <MESH2_CLASS> &mesh2, vector <matrix4x4> &SKquat, vector <Material> &Materials, IO_CLASS IO
OUTPUT: TMT_CLASS &tmt
------------------------------------------------------------------------------------------------------------------*/

#include "stdafx.h"
#include "MISC/concol.h"
#include "BLENDSHAPE/TMT_Struct.h"
#include "Classes.h"
#include "MISC/hash_Functions.h"
#include "CHAR/Skeleton_Functions.h"
#include "MISC/UI_Functions.h"


bool TMT_Read(ifstream &tmtfile, TMT_CLASS &tmt, vector <MESH2_CLASS> &mesh2, vector <matrix4x4> &SKquat, vector <Material> &Materials, IO_CLASS IO)
{
	TMT_HEADER tmt_header;
	TMT_DATA tmt_data;

	tmtfile.read(reinterpret_cast<char*>(&tmt_header.TMT_MAGIC), sizeof(tmt_header.TMT_MAGIC));						// Legge l'ID del file ("MPHB")

	if (tmt_header.TMT_MAGIC != 1112035405)			// Se il file non inizia con "MPHB" l'estrazione dei blend shapes termina
	{
		UI_Display_Error(false, IO.TMT, " is not a valid TMT file. Blend Shapes will not be exported.");
		return false;
	}
	else											// Se il file è valido
	{
		tmtfile.seekg(8, ios_base::cur);
		tmtfile.read(reinterpret_cast<char*>(&tmt_header.Linked_mesh_hash), sizeof(tmt_header.Linked_mesh_hash));	// Legge l'hash della mesh associata
		tmtfile.read(reinterpret_cast<char*>(&tmt.nBlendshapes), sizeof(tmt_header.nBlendshapes));					// Legge il numero di blendshapes
		tmtfile.read(reinterpret_cast<char*>(&tmt.nV), sizeof(tmt_header.nVertices));								// Legge il numero di vertici
		tmtfile.seekg(8, ios_base::cur);

		tmt.name = GetMeshName(tmt_header.Linked_mesh_hash, &tmt.hashed);
		
		// Ricerca gruppo 2 associato al blendshape
		for (unsigned int g = 0; g < mesh2.size(); g++)
			if (mesh2[g].name == tmt.name)			// Se trova un gruppo MESH 2 con nome uguale
			{
				if (mesh2[g].nV != tmt.nV)			// Se il numero di vertici non combacia l'estrazione dei blend shapes termina
				{
					UI_Display_Error(false, "", "CHR/TMT vertex count mismatch. Blend Shapes will not be exported.");
					return false;
				}
				tmt.mesh2_group = g;
				tmt.mesh2_bone = mesh2[g].Bone;
				// Ricerca dell'elemento con più facce. Il materiale verrà preso da questo elemento
				int material_ref = distance(mesh2[g].arrEl_Ind.begin(), max_element(mesh2[g].arrEl_Ind.begin(), mesh2[g].arrEl_Ind.end()));
				tmt.TMT_Material.Number = material_ref;
				tmt.TMT_Material.Type = 4;											// La tipologia di materiale è forzata a "Diffuse" (4)
				tmt.TMT_Material.Diffuse = Materials[material_ref].Diffuse;
			}
		// Ridimensionamento vettori 
		tmt.BLENDSHAPE_vINDX.resize(tmt.nBlendshapes+1);
		tmt.X.resize(tmt.nBlendshapes + 1);
		tmt.Y.resize(tmt.nBlendshapes + 1);
		tmt.Z.resize(tmt.nBlendshapes + 1);
		tmt.Xn.resize(tmt.nBlendshapes + 1);
		tmt.Yn.resize(tmt.nBlendshapes + 1);
		tmt.Zn.resize(tmt.nBlendshapes + 1);
		tmt.U.resize(tmt.nBlendshapes + 1);
		tmt.V.resize(tmt.nBlendshapes + 1);

		// Lettura dati
		for (unsigned int v = 0; v < tmt.nV; v++)
		{
			int P = -1;
			if (v == tmt.nV - 1)
				P = 0;
			if (v % 8 == 0 || v == tmt.nV - 1)			// Disegna la barra ogni 8 vertici (per velocizzare il processo)
				UI_ProgressBar(v, tmt.nV, 45, " Reading Blend Shapes...                       ", P, 1);

			for (unsigned int n = 0; n <= tmt.nBlendshapes; n++)
			{
				tmtfile.read(reinterpret_cast<char*>(&tmt_data.X), sizeof(tmt_data.X));								// Lettura X
				tmtfile.read(reinterpret_cast<char*>(&tmt_data.Y), sizeof(tmt_data.Y));								// Lettura Y
				tmtfile.read(reinterpret_cast<char*>(&tmt_data.Z), sizeof(tmt_data.Z));								// Lettura Z
				tmtfile.read(reinterpret_cast<char*>(&tmt_data.Xn), sizeof(tmt_data.Xn));							// Lettura normal X
				tmtfile.read(reinterpret_cast<char*>(&tmt_data.Yn), sizeof(tmt_data.Yn));							// Lettura normal Y
				tmtfile.read(reinterpret_cast<char*>(&tmt_data.Zn), sizeof(tmt_data.Zn));							// Lettura normal Z
				tmtfile.read(reinterpret_cast<char*>(&tmt_data.U), sizeof(tmt_data.U));								// Lettura coordinata U texture
				tmtfile.read(reinterpret_cast<char*>(&tmt_data.V), sizeof(tmt_data.V));								// Lettura coordinata V texture
				
				if (n == 0)		// Se il blendshape è il numero 0 (mesh normale) vengono copiati tutti i valori
				{
					tmt.X[n].push_back(tmt_data.X);				tmt.Y[n].push_back(tmt_data.Y);				tmt.Z[n].push_back(tmt_data.Z);
					tmt.Xn[n].push_back(tmt_data.Xn);			tmt.Yn[n].push_back(tmt_data.Yn);			tmt.Zn[n].push_back(tmt_data.Zn);
					tmt.U[n].push_back(tmt_data.U);				tmt.V[n].push_back(tmt_data.V);

					Skeleton_Vertex_TS(&tmt.X[n][v], &tmt.Y[n][v], &tmt.Z[n][v], SKquat[tmt.mesh2_bone]);			//APPLICAZIONE COORDINATE BONES AI VERTICI
				}
				else			// Se si tratta di un blendshape vero e proprio vengono copiati tutti i valori solo se almeno uno di essi differisce dalla mesh normale
					if (tmt_data.X != 0 || tmt_data.Y != 0 || tmt_data.Z != 0 ||
						tmt_data.Xn != 0 || tmt_data.Yn != 0 || tmt_data.Zn != 0 ||
						tmt_data.U != tmt.U[0][v] || tmt_data.V != tmt.V[0][v])
					{
						tmt.BLENDSHAPE_vINDX[n].push_back(v);
						tmt.X[n].push_back(tmt_data.X);				tmt.Y[n].push_back(tmt_data.Y);				tmt.Z[n].push_back(tmt_data.Z);
						tmt.Xn[n].push_back(tmt_data.Xn);			tmt.Yn[n].push_back(tmt_data.Yn);			tmt.Zn[n].push_back(tmt_data.Zn);
						tmt.U[n].push_back(tmt_data.U);				tmt.V[n].push_back(tmt_data.V);
					}
			}
		}
	}
	return true;
}