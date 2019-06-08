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
Conversione strip gruppo MESH 2 in facce esplicite per file FBX
INPUT: vector <MESH2_CLASS> &mesh2
OUTPUT: vector < vector < vector <unsigned short> > > &MESH2_vINDX, vector < vector < vector <int> > > &MESH2_FACES
------------------------------------------------------------------------------------------------------------------*/

#include "stdafx.h"
#include "Classes.h"


void Calculate_Faces_Mesh2 (vector <MESH2_CLASS> &mesh2, vector < vector < vector <unsigned short> > > &MESH2_vINDX, vector < vector < vector <int> > > &MESH2_FACES)
{
    for (unsigned int g = 0; g < mesh2.size(); g++)						// Ogni ciclo è un gruppo di tipo mesh 2
	{
        // Creazione lista di indici ottimizzata (vengono eliminati i salti nella lista indici a causa di vertici inutilizzati, in modo che gli indici diventino progressivi)
        for (unsigned int el = 0; el < mesh2[g].nElements; el++)		// Ogni ciclo è un elemento
        {
            vector <unsigned short> MESH2_Split_strip;                  // Questo vettore conterrà lo strip del solo elemento el
            MESH2_vINDX[g].resize(el+1);                                // Aggiunge uno slot per il nuovo elemento
            MESH2_FACES[g].resize(el+1);                                // Aggiunge uno slot per il nuovo elemento
            for (unsigned int I = 0; I < mesh2[g].arrEl_Ind[el]; I++)	// Questo "for" legge ogni indice per elemento e lo memorizza in MESH2_Split_strip
                MESH2_Split_strip.push_back(mesh2[g].arrIndex[mesh2[g].arrOffset[el]+I]);		// MESH2_Split_strip[posizione INDX vertice]
            for (unsigned int k = 0; k < MESH2_Split_strip.size(); k++)	// Questo ciclo legge ogni indice di MESH2_Split_strip e, se non presente, lo mette in MESH2_vINDX
                if (find(MESH2_vINDX[g][el].begin(), MESH2_vINDX[g][el].end(), MESH2_Split_strip[k]) == MESH2_vINDX[g][el].end())
                    MESH2_vINDX[g][el].push_back(MESH2_Split_strip[k]);
            for (unsigned int k = 0; k < MESH2_Split_strip.size(); k++)	// Questo ciclo mette dentro MESH2_Split_strip la posizione di quell'indice all'interno di MESH2_vINDX
            {
                vector <unsigned short>::iterator it;                   // Iteratore provvisorio che conterrà la posizione dell'indice trovato dentro MESH2_vINDX
                it = find(MESH2_vINDX[g][el].begin(), MESH2_vINDX[g][el].end(), MESH2_Split_strip[k]);	// Cerca la posizione dell'indice dentro MESH2_vINDX
                MESH2_Split_strip[k] = distance(MESH2_vINDX[g][el].begin(), it);                        // Sovrascrive l'indice in MESH2_Split_strip con il riferimento a MESH2_vINDX
            }
            // Creazione lista facce
            if (mesh2[g].arrDraw_Mode[el] == 5)					// Se il Draw mode è uguale a 5 si tratta di un triangle strip
            {
                if (mesh2[g].arrOffset[el] % 2 == 0)			// Verifica se il punto d'inizio di ogni frammento dello strip è pari o dispari
                {
                    for (int I = 0; I < (mesh2[g].arrEl_Ind[el] - 2); I++)
                        if (MESH2_Split_strip[I] != MESH2_Split_strip[I+1] &&
                            MESH2_Split_strip[I] != MESH2_Split_strip[I+2] &&
                            MESH2_Split_strip[I+1] != MESH2_Split_strip[I+2])						// Esclude le facce nulle
                        {
                            if (I % 2 == 0)		// Se pari
                            {
                                MESH2_FACES[g][el].push_back(MESH2_Split_strip[I+2]);
                                MESH2_FACES[g][el].push_back(MESH2_Split_strip[I+1]);
                                MESH2_FACES[g][el].push_back(MESH2_Split_strip[I] ^ -1);	// XOR per formato FBX
                            }
                            else				// Se dispari
                            {
                                MESH2_FACES[g][el].push_back(MESH2_Split_strip[I]);
                                MESH2_FACES[g][el].push_back(MESH2_Split_strip[I+1]);
                                MESH2_FACES[g][el].push_back(MESH2_Split_strip[I+2] ^ -1);	// XOR per formato FBX
                            }
                        }
                }
                else
                {
                    for (int I = 0; I < (mesh2[g].arrEl_Ind[el] - 2); I++)
                        if (MESH2_Split_strip[I] != MESH2_Split_strip[I+1] &&
                            MESH2_Split_strip[I] != MESH2_Split_strip[I+2] &&
                            MESH2_Split_strip[I+1] != MESH2_Split_strip[I+2])						// Esclude le facce nulle
                        {
                            if (I % 2 == 0)		// Se pari
                            {
                                MESH2_FACES[g][el].push_back(MESH2_Split_strip[I]);
                                MESH2_FACES[g][el].push_back(MESH2_Split_strip[I+1]);
                                MESH2_FACES[g][el].push_back(MESH2_Split_strip[I+2] ^ -1);	// XOR per formato FBX
                            }
                            else				// Se dispari
                            {
                                MESH2_FACES[g][el].push_back(MESH2_Split_strip[I+2]);
                                MESH2_FACES[g][el].push_back(MESH2_Split_strip[I+1]);
                                MESH2_FACES[g][el].push_back(MESH2_Split_strip[I] ^ -1);	// XOR per formato FBX
                            }
                        }
                }
            }
            else												// Se il Draw mode non è 5 si tratta di una lista di facce esplicite
                for (int I = 0; I < mesh2[g].arrEl_Ind[el];)
                {
                    MESH2_FACES[g][el].push_back(MESH2_Split_strip[I+2]);
                    MESH2_FACES[g][el].push_back(MESH2_Split_strip[I+1]);
                    MESH2_FACES[g][el].push_back(MESH2_Split_strip[I] ^ -1);				// XOR per formato FBX
                    I += 3;
                }
        }
	}
}