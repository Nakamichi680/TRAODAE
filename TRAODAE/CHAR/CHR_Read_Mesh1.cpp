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
Legge tutto il gruppo MESH1 (vertici, facce ed elementi)
INPUT: vector <matrix4x4> &SKquat, ifstream &chrfile
OUTPUT: MESH1_CLASS &mesh1
------------------------------------------------------------------------------------------------------------------*/

#include "stdafx.h"
#include "CHAR/CHR_Struct.h"
#include "Classes.h"
#include "MISC/hash_Functions.h"
#include "CHAR/Skeleton_Functions.h"


void CHR_Read_Mesh1 (MESH1_CLASS &mesh1, vector <matrix4x4> &SKquat, ifstream &chrfile)
{
    CHR_MESH1_HEADER chr_mesh1_header;
    CHR_MESH1_VERTEX chr_mesh1_vertex;
    CHR_MESH_STRIP_HEADER chr_mesh_strip_header;
    CHR_MESH_STRIP chr_mesh_strip;
    CHR_MESH_ELEMENT_HEADER chr_mesh_element_header;
    CHR_MESH_ELEMENT chr_mesh_element;

    chrfile.seekg(8, ios_base::cur);					// Salta i primi 8 bytes dell'header dei vertici del gruppo MESH 1
    chrfile.read(reinterpret_cast<char*>(&chr_mesh1_header.ID), sizeof(chr_mesh1_header.ID));						// Legge l'ID del gruppo MESH1
    chrfile.read(reinterpret_cast<char*>(&chr_mesh1_header.nVertices), sizeof(chr_mesh1_header.nVertices));			// Legge il numero di vertici
   
	mesh1.name = GetMeshName(chr_mesh1_header.ID, &mesh1.hashed);
    
	mesh1.X.resize(chr_mesh1_header.nVertices);
    mesh1.Y.resize(chr_mesh1_header.nVertices);
    mesh1.Z.resize(chr_mesh1_header.nVertices);
    mesh1.Xn.resize(chr_mesh1_header.nVertices);
    mesh1.Yn.resize(chr_mesh1_header.nVertices);
    mesh1.Zn.resize(chr_mesh1_header.nVertices);
    mesh1.Xtg.resize(chr_mesh1_header.nVertices);
    mesh1.Ytg.resize(chr_mesh1_header.nVertices);
    mesh1.Ztg.resize(chr_mesh1_header.nVertices);
    mesh1.Xbn.resize(chr_mesh1_header.nVertices);
    mesh1.Ybn.resize(chr_mesh1_header.nVertices);
    mesh1.Zbn.resize(chr_mesh1_header.nVertices);
    mesh1.U.resize(chr_mesh1_header.nVertices);
    mesh1.V.resize(chr_mesh1_header.nVertices);
    mesh1.W1.resize(chr_mesh1_header.nVertices);
    mesh1.W2.resize(chr_mesh1_header.nVertices);
    mesh1.Bone1.resize(chr_mesh1_header.nVertices);
    mesh1.Bone2.resize(chr_mesh1_header.nVertices);

    ///////////////////    LETTURA DEI VERTICI DEL BLOCCO MESH 1
    for (unsigned int v = 0; v < chr_mesh1_header.nVertices; v++)			// Ogni ciclo fa un vertice
    {
        float X1, Y1, Z1, X2, Y2, Z2, X1n, Y1n, Z1n, X2n, Y2n, Z2n, X1tg, Y1tg, Z1tg, X1bn, Y1bn, Z1bn, X2tg, Y2tg, Z2tg, X2bn, Y2bn, Z2bn;
        chrfile.read(reinterpret_cast<char*>(&chr_mesh1_vertex.X1), sizeof(chr_mesh1_vertex.X1));
        chrfile.read(reinterpret_cast<char*>(&chr_mesh1_vertex.Y1), sizeof(chr_mesh1_vertex.Y1));
        chrfile.read(reinterpret_cast<char*>(&chr_mesh1_vertex.Z1), sizeof(chr_mesh1_vertex.Z1));
        chrfile.read(reinterpret_cast<char*>(&chr_mesh1_vertex.X2), sizeof(chr_mesh1_vertex.X2));
        chrfile.read(reinterpret_cast<char*>(&chr_mesh1_vertex.Y2), sizeof(chr_mesh1_vertex.Y2));
        chrfile.read(reinterpret_cast<char*>(&chr_mesh1_vertex.Z2), sizeof(chr_mesh1_vertex.Z2));
        chrfile.read(reinterpret_cast<char*>(&chr_mesh1_vertex.X1n), sizeof(chr_mesh1_vertex.X1n));
        chrfile.read(reinterpret_cast<char*>(&chr_mesh1_vertex.Y1n), sizeof(chr_mesh1_vertex.Y1n));
        chrfile.read(reinterpret_cast<char*>(&chr_mesh1_vertex.Z1n), sizeof(chr_mesh1_vertex.Z1n));
        chrfile.read(reinterpret_cast<char*>(&chr_mesh1_vertex.X2n), sizeof(chr_mesh1_vertex.X2n));
        chrfile.read(reinterpret_cast<char*>(&chr_mesh1_vertex.Y2n), sizeof(chr_mesh1_vertex.Y2n));
        chrfile.read(reinterpret_cast<char*>(&chr_mesh1_vertex.Z2n), sizeof(chr_mesh1_vertex.Z2n));
        chrfile.read(reinterpret_cast<char*>(&chr_mesh1_vertex.X1tg), sizeof(chr_mesh1_vertex.X1tg));
        chrfile.read(reinterpret_cast<char*>(&chr_mesh1_vertex.Y1tg), sizeof(chr_mesh1_vertex.Y1tg));
        chrfile.read(reinterpret_cast<char*>(&chr_mesh1_vertex.Z1tg), sizeof(chr_mesh1_vertex.Z1tg));
        chrfile.read(reinterpret_cast<char*>(&chr_mesh1_vertex.X1bn), sizeof(chr_mesh1_vertex.X1bn));
        chrfile.read(reinterpret_cast<char*>(&chr_mesh1_vertex.Y1bn), sizeof(chr_mesh1_vertex.Y1bn));
        chrfile.read(reinterpret_cast<char*>(&chr_mesh1_vertex.Z1bn), sizeof(chr_mesh1_vertex.Z1bn));
        chrfile.read(reinterpret_cast<char*>(&chr_mesh1_vertex.X2tg), sizeof(chr_mesh1_vertex.X2tg));
        chrfile.read(reinterpret_cast<char*>(&chr_mesh1_vertex.Y2tg), sizeof(chr_mesh1_vertex.Y2tg));
        chrfile.read(reinterpret_cast<char*>(&chr_mesh1_vertex.Z2tg), sizeof(chr_mesh1_vertex.Z2tg));
        chrfile.read(reinterpret_cast<char*>(&chr_mesh1_vertex.X2bn), sizeof(chr_mesh1_vertex.X2bn));
        chrfile.read(reinterpret_cast<char*>(&chr_mesh1_vertex.Y2bn), sizeof(chr_mesh1_vertex.Y2bn));
        chrfile.read(reinterpret_cast<char*>(&chr_mesh1_vertex.Z2bn), sizeof(chr_mesh1_vertex.Z2bn));
        chrfile.read(reinterpret_cast<char*>(&chr_mesh1_vertex.Weight), sizeof(chr_mesh1_vertex.Weight));			// Legge il peso delle bones
        chrfile.read(reinterpret_cast<char*>(&mesh1.Bone1[v]), sizeof(chr_mesh1_vertex.Bone1));						// Legge l'indice della bone 1
        chrfile.read(reinterpret_cast<char*>(&mesh1.Bone2[v]), sizeof(chr_mesh1_vertex.Bone2));						// Legge l'indice della bone 2
        chrfile.read(reinterpret_cast<char*>(&chr_mesh1_vertex.U), sizeof(chr_mesh1_vertex.U));						// Legge la coordinata U della texture
        chrfile.read(reinterpret_cast<char*>(&chr_mesh1_vertex.V), sizeof(chr_mesh1_vertex.V));						// Legge la coordinata V della texture

        X1 = chr_mesh1_vertex.X1 * 0.0625f;					Y1 = chr_mesh1_vertex.Y1 * 0.0625f;					Z1 = chr_mesh1_vertex.Z1 * 0.0625f;
        X2 = chr_mesh1_vertex.X2 * 0.0625f;                 Y2 = chr_mesh1_vertex.Y2 * 0.0625f;                 Z2 = chr_mesh1_vertex.Z2 * 0.0625f;
        X1n = chr_mesh1_vertex.X1n * 0.007874016f;          Y1n = chr_mesh1_vertex.Y1n * 0.007874016f;          Z1n = chr_mesh1_vertex.Z1n * 0.007874016f;
        X2n = chr_mesh1_vertex.X2n * 0.007874016f;          Y2n = chr_mesh1_vertex.Y2n * 0.007874016f;          Z2n = chr_mesh1_vertex.Z2n * 0.007874016f;
        X1tg = chr_mesh1_vertex.X1tg * 0.007874016f;        Y1tg = chr_mesh1_vertex.Y1tg * 0.007874016f;        Z1tg = chr_mesh1_vertex.Z1tg * 0.007874016f;
        X1bn = chr_mesh1_vertex.X1bn * 0.007874016f;        Y1bn = chr_mesh1_vertex.Y1bn * 0.007874016f;        Z1bn = chr_mesh1_vertex.Z1bn * 0.007874016f;
        X2tg = chr_mesh1_vertex.X2tg * 0.007874016f;        Y2tg = chr_mesh1_vertex.Y2tg * 0.007874016f;        Z2tg = chr_mesh1_vertex.Z2tg * 0.007874016f;
        X2bn = chr_mesh1_vertex.X2bn * 0.007874016f;        Y2bn = chr_mesh1_vertex.Y2bn * 0.007874016f;        Z2bn = chr_mesh1_vertex.Z2bn * 0.007874016f;

        mesh1.W1[v] = chr_mesh1_vertex.Weight;
        mesh1.W1[v] = mesh1.W1[v] / 32767;			// Normalizza il peso 1
        mesh1.W2[v] = 1 - mesh1.W1[v];              // Ricava il peso 2
        mesh1.U[v] = chr_mesh1_vertex.U * 0.00003051850947599f;					mesh1.V[v] = chr_mesh1_vertex.V * 0.00003051850947599f;

        Skeleton_Vertex_TS(&X1, &Y1, &Z1, SKquat[mesh1.Bone1[v]]);			// APPLICAZIONE COORDINATE BONES AL SET 1 DI VERTICI
        Skeleton_Vertex_TS(&X2, &Y2, &Z2, SKquat[mesh1.Bone2[v]]);			// APPLICAZIONE COORDINATE BONES AL SET 2 DI VERTICI

        ///////////////////////////////// CALCOLO MEDIA PONDERATA SET 1/2 VERTICI IN BASE AI PESI W1 E W2. I DUE VERTICI DIVENTANO UNO SOLO
        mesh1.X[v] = X1 * mesh1.W1[v] + X2 * mesh1.W2[v];           mesh1.Y[v] = Y1 * mesh1.W1[v] + Y2 * mesh1.W2[v];           mesh1.Z[v] = Z1 * mesh1.W1[v] + Z2 * mesh1.W2[v];
        mesh1.Xn[v] = X1n * mesh1.W1[v] + X2n * mesh1.W2[v];        mesh1.Yn[v] = Y1n * mesh1.W1[v] + Y2n * mesh1.W2[v];        mesh1.Zn[v] = Z1n * mesh1.W1[v] + Z2n * mesh1.W2[v];
        mesh1.Xtg[v] = X1tg * mesh1.W1[v] + X2tg * mesh1.W2[v];		mesh1.Ytg[v] = Y1tg * mesh1.W1[v] + Y2tg * mesh1.W2[v];     mesh1.Ztg[v] = Z1tg * mesh1.W1[v] + Z2tg * mesh1.W2[v];
        mesh1.Xbn[v] = X1bn * mesh1.W1[v] + X2bn * mesh1.W2[v];     mesh1.Ybn[v] = Y1bn * mesh1.W1[v] + Y2bn * mesh1.W2[v];     mesh1.Zbn[v] = Z1bn * mesh1.W1[v] + Z2bn * mesh1.W2[v];
    }

    ///////////////////    LETTURA DEL TRIANGLE STRIP DEL BLOCCO MESH 1
    chrfile.read(reinterpret_cast<char*>(&chr_mesh_strip_header.nIndices), sizeof(chr_mesh_strip_header.nIndices));		// Legge il numero di indici dello strip
    mesh1.arrIndex.resize(chr_mesh_strip_header.nIndices);					// Ridimensionamento del vettore del blocco TRIANGLE STRIP MESH1
    for (unsigned int I = 0; I < chr_mesh_strip_header.nIndices; I++)		// Questo blocco legge lo strip
        chrfile.read(reinterpret_cast<char*>(&mesh1.arrIndex[I]), sizeof(chr_mesh_strip.Index));

    ///////////////////    LETTURA DEGLI ELEMENTI DEL BLOCCO MESH 1
    chrfile.read(reinterpret_cast<char*>(&mesh1.nElements), sizeof(chr_mesh_element_header.nElements));					// Legge il numero di elementi
    mesh1.arrEl_Ind.resize(mesh1.nElements);		// Contiene il numero di indici dell'elemento
    mesh1.arrOffset.resize(mesh1.nElements);        // Contiene l'offset dell'elemento nel triangle strip
    mesh1.arrMat_Ref.resize(mesh1.nElements);       // ID materiale
    mesh1.arrDraw_Mode.resize(mesh1.nElements);		// Draw Mode (4 per facce esplicite, 5 per triangle strip). ATTENZIONE: SUPPORTO PER FACCE ESPLICITE NON ANCORA IMPLEMENTATO!!!
    for (unsigned int el = 0; el < mesh1.nElements; el++)
    {
        chrfile.seekg(2, ios_base::cur);
        chrfile.read(reinterpret_cast<char*>(&mesh1.arrEl_Ind[el]), sizeof(chr_mesh_element.nElement_Indices));			// Legge il numero di indici dell'elemento
        chrfile.read(reinterpret_cast<char*>(&mesh1.arrOffset[el]), sizeof(chr_mesh_element.Offset));					// Legge l'offset dell'elemento nello strip
        chrfile.read(reinterpret_cast<char*>(&mesh1.arrMat_Ref[el]), sizeof(chr_mesh_element.Material_Ref));			// Legge l'ID del materiale
        chrfile.seekg(2, ios_base::cur);
        chrfile.read(reinterpret_cast<char*>(&mesh1.arrDraw_Mode[el]), sizeof(chr_mesh_element.Draw_mode));				// Legge il Draw Mode dell'elemento
    }
}