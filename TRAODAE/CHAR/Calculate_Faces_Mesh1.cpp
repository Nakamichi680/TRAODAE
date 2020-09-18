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
Conversione strip gruppo MESH 1 in facce esplicite per file FBX
INPUT: MESH1_CLASS &mesh1
OUTPUT: vector < vector <unsigned short> > &MESH1_vINDX, vector < vector <int> > &MESH1_FACES
------------------------------------------------------------------------------------------------------------------*/

#include "stdafx.h"
#include "Classes.h"


void Calculate_Faces_Mesh1 (MESH1_CLASS &mesh1, vector < vector <unsigned short> > &MESH1_vINDX, vector < vector <int> > &MESH1_FACES)
{
    // Creazione lista di indici ottimizzata (vengono eliminati i salti nella lista indici a causa di vertici inutilizzati, in modo che gli indici diventino progressivi)
    for (unsigned int el = 0; el < mesh1.nElements; el++)				// Ogni ciclo è un elemento
    {
        vector <unsigned short> MESH1_Split_strip;                      // Questo vettore conterrà lo strip del solo elemento el
        for (unsigned int I = 0; I < mesh1.arrEl_Ind[el]; I++)			// Questo "for" legge ogni indice per elemento e lo memorizza in MESH1_Split_strip
            MESH1_Split_strip.push_back(mesh1.arrIndex[mesh1.arrOffset[el]+I]);                 // MESH1_Split_strip[posizione INDX vertice]
        for (unsigned int k = 0; k < MESH1_Split_strip.size(); k++)		// Questo ciclo legge ogni indice di MESH1_Split_strip e, se non presente, lo mette in MESH1_vINDX
            if (find(MESH1_vINDX[el].begin(), MESH1_vINDX[el].end(), MESH1_Split_strip[k]) == MESH1_vINDX[el].end())
                MESH1_vINDX[el].push_back(MESH1_Split_strip[k]);
        for (unsigned int k = 0; k < MESH1_Split_strip.size(); k++)		// Questo ciclo mette dentro MESH1_Split_strip la posizione di quell'indice all'interno di MESH1_vINDX
        {
            vector <unsigned short>::iterator it;                       // Iteratore provvisorio che conterrà la posizione dell'indice trovato dentro MESH1_vINDX
            it = find(MESH1_vINDX[el].begin(), MESH1_vINDX[el].end(), MESH1_Split_strip[k]);	// Cerca la posizione dell'indice dentro MESH1_vINDX
            MESH1_Split_strip[k] = distance(MESH1_vINDX[el].begin(), it);						// Sovrascrive l'indice in MESH1_Split_strip con il riferimento a MESH1_vINDX
        }

        // Creazione lista facce
		if (mesh1.arrDraw_Mode[el] == 5)			// Se il Draw mode è uguale a 5 si tratta di un triangle strip
		{
			if (mesh1.arrOffset[el] % 2 == 0)		// Verifica se il punto d'inizio di ogni frammento dello strip è pari o dispari
			{
				for (int I = 0; I < (mesh1.arrEl_Ind[el] - 2); I++)
					if (MESH1_Split_strip[I] != MESH1_Split_strip[I+1] &&						// Esclude le facce nulle
						MESH1_Split_strip[I] != MESH1_Split_strip[I+2] &&
						MESH1_Split_strip[I+1] != MESH1_Split_strip[I+2])
					{
						if (I % 2 == 0)		// Se pari
						{
							MESH1_FACES[el].push_back(MESH1_Split_strip[I+2]);
							MESH1_FACES[el].push_back(MESH1_Split_strip[I+1]);
							MESH1_FACES[el].push_back(MESH1_Split_strip[I] ^ -1);		// XOR per formato FBX
						}
						else                // Se dispari
						{
							MESH1_FACES[el].push_back(MESH1_Split_strip[I]);
							MESH1_FACES[el].push_back(MESH1_Split_strip[I+1]);
							MESH1_FACES[el].push_back(MESH1_Split_strip[I+2] ^ -1);		// XOR per formato FBX
						}
					}
			}
			else
			{
				for (int I = 0; I < (mesh1.arrEl_Ind[el] - 2); I++)
					if (MESH1_Split_strip[I] != MESH1_Split_strip[I+1] &&						// Esclude le facce nulle
						MESH1_Split_strip[I] != MESH1_Split_strip[I+2] &&
						MESH1_Split_strip[I+1] != MESH1_Split_strip[I+2])
					{
						if (I % 2 == 0)		// Se pari
						{
							MESH1_FACES[el].push_back(MESH1_Split_strip[I]);
							MESH1_FACES[el].push_back(MESH1_Split_strip[I+1]);
							MESH1_FACES[el].push_back(MESH1_Split_strip[I+2] ^ -1);     // XOR per formato FBX
						}
						else                // Se dispari
						{
							MESH1_FACES[el].push_back(MESH1_Split_strip[I+2]);
							MESH1_FACES[el].push_back(MESH1_Split_strip[I+1]);
							MESH1_FACES[el].push_back(MESH1_Split_strip[I] ^ -1);       // XOR per formato FBX
						}
					}
			}
		}
		else										// Se il Draw mode non è 5 si tratta di una lista di facce esplicite
            for (int I = 0; I < mesh1.arrEl_Ind[el];)
            {
                MESH1_FACES[el].push_back(MESH1_Split_strip[I+2]);
                MESH1_FACES[el].push_back(MESH1_Split_strip[I+1]);
                MESH1_FACES[el].push_back(MESH1_Split_strip[I] ^ -1);					// XOR per formato FBX
                I += 3;
            }
    }
}