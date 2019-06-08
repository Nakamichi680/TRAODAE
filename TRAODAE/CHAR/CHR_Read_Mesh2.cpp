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
Legge un singolo gruppo MESH2 (vertici, facce ed elementi)
INPUT: vector <matrix4x4> &SKquat, ifstream &chrfile
OUTPUT: MESH2_CLASS *mesh2
------------------------------------------------------------------------------------------------------------------*/

#include "stdafx.h"
#include "CHAR/CHR_Struct.h"
#include "Classes.h"
#include "MISC/hash_Functions.h"
#include "CHAR/Skeleton_Functions.h"


void CHR_Read_Mesh2 (MESH2_CLASS *mesh2, vector <matrix4x4> &SKquat, ifstream &chrfile)
{
    CHR_MESH2_HEADER chr_mesh2_header;
    CHR_MESH2_VERTEX chr_mesh2_vertex;
    CHR_MESH_STRIP_HEADER chr_mesh_strip_header;
    CHR_MESH_STRIP chr_mesh_strip;
    CHR_MESH_ELEMENT_HEADER chr_mesh_element_header;
    CHR_MESH_ELEMENT chr_mesh_element;

    chrfile.read(reinterpret_cast<char*>(&chr_mesh2_header.Unknown1), sizeof(chr_mesh2_header.Unknown1));
    chrfile.read(reinterpret_cast<char*>(&chr_mesh2_header.Unknown2), sizeof(chr_mesh2_header.Unknown2));
    chrfile.read(reinterpret_cast<char*>(&chr_mesh2_header.ID), sizeof(chr_mesh2_header.ID));						// Legge l'ID del gruppo MESH2
    chrfile.read(reinterpret_cast<char*>(&mesh2->Bone), sizeof(chr_mesh2_header.Bone_ref));							// Legge la bone di appartenenza
    chrfile.read(reinterpret_cast<char*>(&chr_mesh2_header.Unknown3), sizeof(chr_mesh2_header.Unknown3));
    chrfile.read(reinterpret_cast<char*>(&mesh2->nV), sizeof(chr_mesh2_header.nVertices));							// Legge il numero di vertici
    
	mesh2->name = GetMeshName(chr_mesh2_header.ID, &mesh2->hashed);
    
	mesh2->X.resize(mesh2->nV);
    mesh2->Y.resize(mesh2->nV);
    mesh2->Z.resize(mesh2->nV);
    mesh2->Xn.resize(mesh2->nV);
    mesh2->Yn.resize(mesh2->nV);
    mesh2->Zn.resize(mesh2->nV);
    mesh2->Xtg.resize(mesh2->nV);
    mesh2->Ytg.resize(mesh2->nV);
    mesh2->Ztg.resize(mesh2->nV);
    mesh2->Xbn.resize(mesh2->nV);
    mesh2->Ybn.resize(mesh2->nV);
    mesh2->Zbn.resize(mesh2->nV);
    mesh2->U.resize(mesh2->nV);
    mesh2->V.resize(mesh2->nV);

    ///////////////////    LETTURA DEI VERTICI DEL BLOCCO MESH 2
    for (unsigned int v = 0; v < mesh2->nV; v++)							// Ogni ciclo fa un vertice
    {
        chrfile.read(reinterpret_cast<char*>(&chr_mesh2_vertex.X), sizeof(chr_mesh2_vertex.X));
        chrfile.read(reinterpret_cast<char*>(&chr_mesh2_vertex.Y), sizeof(chr_mesh2_vertex.Y));
        chrfile.read(reinterpret_cast<char*>(&chr_mesh2_vertex.Z), sizeof(chr_mesh2_vertex.Z));
        chrfile.read(reinterpret_cast<char*>(&chr_mesh2_vertex.Xn), sizeof(chr_mesh2_vertex.Xn));
        chrfile.read(reinterpret_cast<char*>(&chr_mesh2_vertex.Yn), sizeof(chr_mesh2_vertex.Yn));
        chrfile.read(reinterpret_cast<char*>(&chr_mesh2_vertex.Zn), sizeof(chr_mesh2_vertex.Zn));
        chrfile.read(reinterpret_cast<char*>(&chr_mesh2_vertex.Xtg), sizeof(chr_mesh2_vertex.Xtg));
        chrfile.read(reinterpret_cast<char*>(&chr_mesh2_vertex.Ytg), sizeof(chr_mesh2_vertex.Ytg));
        chrfile.read(reinterpret_cast<char*>(&chr_mesh2_vertex.Ztg), sizeof(chr_mesh2_vertex.Ztg));
        chrfile.read(reinterpret_cast<char*>(&chr_mesh2_vertex.Xbn), sizeof(chr_mesh2_vertex.Xbn));
        chrfile.read(reinterpret_cast<char*>(&chr_mesh2_vertex.Ybn), sizeof(chr_mesh2_vertex.Ybn));
        chrfile.read(reinterpret_cast<char*>(&chr_mesh2_vertex.Zbn), sizeof(chr_mesh2_vertex.Zbn));
        chrfile.read(reinterpret_cast<char*>(&chr_mesh2_vertex.U), sizeof(chr_mesh2_vertex.U));						// Legge la coordinata U della texture
        chrfile.read(reinterpret_cast<char*>(&chr_mesh2_vertex.V), sizeof(chr_mesh2_vertex.V));						// Legge la coordinata V della texture
        mesh2->X[v] = chr_mesh2_vertex.X * 0.0625f;
        mesh2->Y[v] = chr_mesh2_vertex.Y * 0.0625f;
        mesh2->Z[v] = chr_mesh2_vertex.Z * 0.0625f;
        mesh2->Xn[v] = chr_mesh2_vertex.Xn * 0.007874016f;
        mesh2->Yn[v] = chr_mesh2_vertex.Yn * 0.007874016f;
        mesh2->Zn[v] = chr_mesh2_vertex.Zn * 0.007874016f;
        mesh2->Xtg[v] = chr_mesh2_vertex.Xtg * 0.007874016f;
        mesh2->Ytg[v] = chr_mesh2_vertex.Ytg * 0.007874016f;
        mesh2->Ztg[v] = chr_mesh2_vertex.Ztg * 0.007874016f;
        mesh2->Xbn[v] = chr_mesh2_vertex.Xbn * 0.007874016f;
        mesh2->Ybn[v] = chr_mesh2_vertex.Ybn * 0.007874016f;
        mesh2->Zbn[v] = chr_mesh2_vertex.Zbn * 0.007874016f;
        mesh2->U[v] = chr_mesh2_vertex.U * 0.00003051850947599f;
        mesh2->V[v] = chr_mesh2_vertex.V * 0.00003051850947599f;

        Skeleton_Vertex_TS(&mesh2->X[v], &mesh2->Y[v], &mesh2->Z[v], SKquat[mesh2->Bone]);			//APPLICAZIONE COORDINATE BONES AI VERTICI
    }

    ///////////////////    LETTURA DEL TRIANGLE STRIP DEL BLOCCO MESH 2
    chrfile.read(reinterpret_cast<char*>(&chr_mesh_strip_header.nIndices), sizeof(chr_mesh_strip_header.nIndices));		// Legge il numero di indici dello strip
    mesh2->arrIndex.resize(chr_mesh_strip_header.nIndices);					// Ridimensionamento del vettore del blocco TRIANGLE STRIP MESH2
    for (unsigned int I = 0; I < chr_mesh_strip_header.nIndices; I++)		// Questo blocco legge lo strip
        chrfile.read(reinterpret_cast<char*>(&mesh2->arrIndex[I]), sizeof(chr_mesh_strip.Index));

    ///////////////////    LETTURA DEGLI ELEMENTI DEL BLOCCO MESH 2
    chrfile.read(reinterpret_cast<char*>(&mesh2->nElements), sizeof(chr_mesh_element_header.nElements));				// Legge il numero di elementi
    mesh2->arrEl_Ind.resize(mesh2->nElements);		// Contiene il numero di indici dell'elemento
    mesh2->arrOffset.resize(mesh2->nElements);		// Contiene l'offset dell'elemento nel triangle strip
    mesh2->arrMat_Ref.resize(mesh2->nElements);		// ID materiale
    mesh2->arrDraw_Mode.resize(mesh2->nElements);	// Draw Mode (4 per facce esplicite o 5 per triangle strip)
    for (unsigned int el = 0; el < mesh2->nElements; el++)
    {
        chrfile.seekg(2, ios_base::cur);
        chrfile.read(reinterpret_cast<char*>(&mesh2->arrEl_Ind[el]), sizeof(chr_mesh_element.nElement_Indices));		// Legge il numero di indici dell'elemento
        chrfile.read(reinterpret_cast<char*>(&mesh2->arrOffset[el]), sizeof(chr_mesh_element.Offset));					// Legge l'offset dell'elemento nello strip
        chrfile.read(reinterpret_cast<char*>(&mesh2->arrMat_Ref[el]), sizeof(chr_mesh_element.Material_Ref));			// Legge l'ID del materiale
        chrfile.seekg(2, ios_base::cur);
        chrfile.read(reinterpret_cast<char*>(&mesh2->arrDraw_Mode[el]), sizeof(chr_mesh_element.Draw_mode));			// Legge il Draw Mode dell'elemento
    }
}