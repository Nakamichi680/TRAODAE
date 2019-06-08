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
Scrittura Null, Model, Geometry, Deformer e SubDeformer del gruppo MESH 1
INPUT: MESH1_CLASS &mesh1, vector < vector <int> > &MESH1_FACES, vector < vector <unsigned short> > &MESH1_vINDX,
	   CHR_HEADER &chr_header, vector <matrix4x4> &SKquat
OUTPUT: ofstream &out
------------------------------------------------------------------------------------------------------------------*/

#include "stdafx.h"
#include "Classes.h"
#include "FBX/FBX_Functions.h"


void FBX_Write_Mesh1 (MESH1_CLASS &mesh1,
                      vector < vector <int> > &MESH1_FACES,
                      vector < vector <unsigned short> > &MESH1_vINDX,
                      CHR_HEADER &chr_header,
                      vector <matrix4x4> &SKquat,
                      ofstream &out)
{
    /////////////////////// SCRITTURA BODY NULL
    out << "	Model: " << nodeID(99) << ", \"Model::Body_" << mesh1.name << "\", \"Null\" {\n";
    out << "		Version: 232\n";
    out << "		Properties70:  {\n";
    out << "			P: \"InheritType\", \"enum\", \"\", \"\",1\n";
    out << "			P: \"ScalingMin\", \"Vector3D\", \"Vector\", \"\",1,1,1\n";
    out << "			P: \"DefaultAttributeIndex\", \"int\", \"Integer\", \"\",0\n";
    out << "			P: \"Lcl Translation\", \"Lcl Translation\", \"\", \"A+\",0,0,0\n";
    out << "		}\n";
    out << "		MultiLayer: 0\n";
    out << "		MultiTake: 1\n";
    out << "		Shading: T\n";
    out << "		Culling: \"CullingOff\"\n";
    out << "	}\n\n";

    for (unsigned int el = 0; el < mesh1.nElements; el++)		// Ogni ciclo scrive un elemento del gruppo MESH 1
        if (MESH1_FACES[el].size() > 2)							// Controlla che l'elemento del gruppo MESH 1 abbia almeno una faccia
        {
            /////////////////////// SCRITTURA MODEL BODY_PART
            out << "	Model: " << nodeID(11,el) << ", \"Model::Body_part_" << el << "\", \"Mesh\" {\n";
            out << "		Version: 232\n";
            out << "		Properties70:  {\n";
            out << "			P: \"RotationActive\", \"bool\", \"\", \"\",1\n";
            out << "			P: \"InheritType\", \"enum\", \"\", \"\",1\n";
            out << "			P: \"ScalingMin\", \"Vector3D\", \"Vector\", \"\",1,1,1\n";
            out << "			P: \"DefaultAttributeIndex\", \"int\", \"Integer\", \"\",0\n";
            out << "			P: \"Lcl Translation\", \"Lcl Translation\", \"\", \"A+\",0,0,0\n";
            out << "		}\n";
            out << "		MultiLayer: 0\n";
            out << "		MultiTake: 1\n";
            out << "		Shading: T\n";
            out << "		Culling: \"CullingOff\"\n";
            out << "	}\n\n";

            /////////////////////// SCRITTURA GEOMETRY
            out << "	Geometry: " << nodeID(12,el) << ", \"Geometry::\", \"Mesh\" {\n";
            out << "		Properties70:  {\n";
            out << "			P: \"Color\", \"ColorRGB\", \"Color\", \"\",0.525490196078431,0.431372549019608,0.0313725490196078\n";
            out << "		}\n";
            // Scrive i vertici
            out << "		Vertices: *" << MESH1_vINDX[el].size() * 3 << " {\n";					// Numero di vertici x 3
            out << "			a: ";
            for (unsigned int v = 0; v < MESH1_vINDX[el].size(); v++)
            {
                out << mesh1.X[MESH1_vINDX[el][v]] << "," << mesh1.Y[MESH1_vINDX[el][v]] << "," << mesh1.Z[MESH1_vINDX[el][v]];
                if (MESH1_vINDX[el].size() - 1 == v) out << "\n";
                else out << ",\n";
            }
            out << "		}\n";
            // Scrive le facce
            out << "		PolygonVertexIndex: *" << MESH1_FACES[el].size() << " {\n";				// Numero di indici di vertici
            out << "			a: ";
            for (unsigned int P = 0; P < MESH1_FACES[el].size(); P++)
            {
                out << MESH1_FACES[el][P];
                if (MESH1_FACES[el].size() - P != 1)
				{
                    out << ",";
                    if ((P + 1) % 30 == 0 && P != 0)  out << "\n";
				}
                else out << "\n";
            }
            out << "		}\n";
            // Scrive i normals
            out << "		GeometryVersion: 124\n";
            out << "		LayerElementNormal: 0 {\n";
            out << "			Version: 101\n";
            out << "			Name: \"\"\n";
            out << "			MappingInformationType: \"ByVertice\"\n";
            out << "			ReferenceInformationType: \"Direct\"\n";
            out << "			Normals: *" << MESH1_vINDX[el].size() * 3 << " {\n";				// Numero di normals x 3
            out << "				a: ";
            for (unsigned int vn = 0; vn < MESH1_vINDX[el].size(); vn++)
            {
                out << mesh1.Xn[MESH1_vINDX[el][vn]] << "," << mesh1.Yn[MESH1_vINDX[el][vn]] << "," << mesh1.Zn[MESH1_vINDX[el][vn]];
                if (MESH1_vINDX[el].size() - 1 == vn) out << "\n";
                else out << ",\n";
            }
            out << "			}\n";
            out << "		}\n";
            // Scrive i tangents
            out << "		LayerElementTangent: 0 {\n";
            out << "			Version: 101\n";
            out << "			Name: \"UVChannel_1\"\n";
            out << "			MappingInformationType: \"ByVertice\"\n";
            out << "			ReferenceInformationType: \"Direct\"\n";
            out << "			Tangents: *" << MESH1_vINDX[el].size() * 3 << " {\n";				// Numero di tangents x 3
            out << "				a: ";
            for (unsigned int vtg = 0; vtg < MESH1_vINDX[el].size(); vtg++)
            {
                out << mesh1.Xtg[MESH1_vINDX[el][vtg]] << "," << mesh1.Ytg[MESH1_vINDX[el][vtg]] << "," << mesh1.Ztg[MESH1_vINDX[el][vtg]];
                if (MESH1_vINDX[el].size() - 1 == vtg) out << "\n";
                else out << ",\n";
            }
            out << "			}\n";
            out << "		}\n";
            // Scrive i binormals
            out << "		LayerElementBinormal: 0 {\n";
            out << "			Version: 101\n";
            out << "			Name: \"UVChannel_1\"\n";
            out << "			MappingInformationType: \"ByVertice\"\n";
            out << "			ReferenceInformationType: \"Direct\"\n";
            out << "			Binormals: *" << MESH1_vINDX[el].size() * 3 << " {\n";				// Numero di binormals x 3
            out << "				a: ";
            for (unsigned int vbn = 0; vbn < MESH1_vINDX[el].size(); vbn++)
            {
                out << mesh1.Xbn[MESH1_vINDX[el][vbn]] << "," << mesh1.Ybn[MESH1_vINDX[el][vbn]] << "," << mesh1.Zbn[MESH1_vINDX[el][vbn]];
                if (MESH1_vINDX[el].size() - 1 == vbn) out << "\n";
                else out << ",\n";
            }
            out << "			}\n";
            out << "		}\n";
            // Scrive gli UVs
            out << "		LayerElementUV: 0 {\n";
            out << "			Version: 101\n";
            out << "			Name: \"UVChannel_1\"\n";
            out << "			MappingInformationType: \"ByVertice\"\n";
            out << "			ReferenceInformationType: \"Direct\"\n";
            out << "			UV: *" << MESH1_vINDX[el].size() * 2 << " {\n";						// Numero di UV x 2
            out << "				a: ";
            for (unsigned int uv = 0; uv < MESH1_vINDX[el].size(); uv++)
            {
                out << mesh1.U[MESH1_vINDX[el][uv]] << "," << mesh1.V[MESH1_vINDX[el][uv]];
                if (MESH1_vINDX[el].size() - 1 == uv) out << "\n";
                else out << ",\n";
            }
            out << "			}\n";
            out << "		}\n";
            out << "		LayerElementMaterial: 0 {\n";
            out << "			Version: 101\n";
            out << "			Name: \"\"\n";
            out << "			MappingInformationType: \"AllSame\"\n";
            out << "			ReferenceInformationType: \"IndexToDirect\"\n";
            out << "			Materials: *1 {\n";
            out << "				a: 0\n";
            out << "			}\n";
            out << "		}\n";
            out << "		Layer: 0 {\n";
            out << "			Version: 100\n";
            out << "			LayerElement:  {\n";
            out << "				Type: \"LayerElementNormal\"\n";
            out << "				TypedIndex: 0\n";
            out << "			}\n";
            out << "			LayerElement:  {\n";
            out << "				Type: \"LayerElementBinormal\"\n";
            out << "				TypedIndex: 0\n";
            out << "			}\n";
            out << "			LayerElement:  {\n";
            out << "				Type: \"LayerElementTangent\"\n";
            out << "				TypedIndex: 0\n";
            out << "			}\n";
            out << "			LayerElement:  {\n";
            out << "				Type: \"LayerElementMaterial\"\n";
            out << "				TypedIndex: 0\n";
            out << "			}\n";
            out << "			LayerElement:  {\n";
            out << "				Type: \"LayerElementUV\"\n";
            out << "				TypedIndex: 0\n";
            out << "			}\n";
            out << "		}\n";
            out << "	}\n\n";

            /////////////////////// SCRITTURA DEFORMER
            out << "	Deformer: " << nodeID(13,el) << ", \"Deformer::\", \"Skin\" {\n";
            out << "		Version: 101\n";
            out << "		Link_DeformAcuracy: 50\n";
            out << "	}\n\n";

            /////////////////////// SCRITTURA SUBDEFORMER
            for (unsigned int b = 0; b < chr_header.nBONES; b++)	// Questo ciclo controlla se ogni bone è presente nell'elemento ed eventualmente scrive il Subdeformer
                for (unsigned int check_v = 0; check_v < MESH1_vINDX[el].size(); check_v++)
                    if (mesh1.Bone1[MESH1_vINDX[el][check_v]] == b || mesh1.Bone2[MESH1_vINDX[el][check_v]] == b)				// Se la bone viene trovata
                    {
                        check_v = MESH1_vINDX[el].size() + 1;		// Serve ad impedire che venga controllata la stessa bone più volte interrompendo il ciclo for a monte
                        int nIndexes = 0;
                        for (unsigned int count_v = 0; count_v < MESH1_vINDX[el].size(); count_v++)			// Conta il numero di vertici associati alla bone trovata
                            if (mesh1.Bone1[MESH1_vINDX[el][count_v]] == b || mesh1.Bone2[MESH1_vINDX[el][count_v]] == b)
                                nIndexes++;
                        out << "	Deformer: " << nodeID(14,b,el) << ", \"SubDeformer::\", \"Cluster\" {\n";
                        out << "		Version: 100\n";
                        out << "		UserData: \"\", \"\"\n";
                        out << "		Indexes: *" << nIndexes << " {\n";
                        out << "			a: ";
                        int comma_newline = 0;
                        for (unsigned int count_v = 0; count_v < MESH1_vINDX[el].size(); count_v++)		// SCRITTURA INDICI
                            if (mesh1.Bone1[MESH1_vINDX[el][count_v]] == b || mesh1.Bone2[MESH1_vINDX[el][count_v]] == b)
                            {
                                if (comma_newline == 0)
                                    out << count_v;
                                else
                                    if (comma_newline % 30 == 0)			// Se vero, va capo ogni 30 numeri inseriti
                                        out << ",\n" << count_v;
                                    else
                                        out << "," << count_v;
                                comma_newline++;
                            }
                        out << "\n";
                        out << "		}\n";
                        out << "		Weights: *" << nIndexes << " {\n";
                        out << "			a: ";
                        comma_newline = 0;
                        for (unsigned int count_v = 0; count_v < MESH1_vINDX[el].size(); count_v++)		// SCRITTURA PESI
                        {
                            if (mesh1.Bone1[MESH1_vINDX[el][count_v]] == b && mesh1.Bone2[MESH1_vINDX[el][count_v]] == b)	// Se il vertice è associato ad un'unica bone scrive W1
                            {
                                if (comma_newline == 0)
                                    out << mesh1.W1[MESH1_vINDX[el][count_v]];
                                else
                                    if (comma_newline % 30 == 0)			// Se vero, va capo ogni 30 numeri inseriti
                                        out << ",\n" << mesh1.W1[MESH1_vINDX[el][count_v]];
                                    else
                                        out << "," << mesh1.W1[MESH1_vINDX[el][count_v]];
                                comma_newline++;
                            }
                            else
                                if (mesh1.Bone1[MESH1_vINDX[el][count_v]] == b)                                             // Se il vertice è associato alla bone numero 1 scrive W1
                                {
                                    if (comma_newline == 0)
                                        out << mesh1.W1[MESH1_vINDX[el][count_v]];
                                    else
                                        if (comma_newline % 30 == 0)		// Se vero, va capo ogni 30 numeri inseriti
                                            out << ",\n" << mesh1.W1[MESH1_vINDX[el][count_v]];
                                        else
                                            out << "," << mesh1.W1[MESH1_vINDX[el][count_v]];
                                    comma_newline++;
                                }
                                else
                                    if (mesh1.Bone2[MESH1_vINDX[el][count_v]] == b)                                         // Se il vertice è associato alla bone numero 2 scrive W2
                                    {
                                        if (comma_newline == 0)
                                            out << mesh1.W2[MESH1_vINDX[el][count_v]];
                                        else
                                            if (comma_newline % 30 == 0)	// Se vero, va capo ogni 30 numeri inseriti
                                                out << ",\n" << mesh1.W2[MESH1_vINDX[el][count_v]];
                                            else
                                                out << "," << mesh1.W2[MESH1_vINDX[el][count_v]];
                                        comma_newline++;
                                    }
                        }
                        out << "\n";
                        out << "		}\n";
                        out << "		Transform: *16 {\n";
                        out << "			a: 1,0,0,0,0,1,0,0,0,0,1,0,";
                        out << SKquat[b].row4[0] * -1 << "," << SKquat[b].row4[1] * -1 << "," << SKquat[b].row4[2] * -1 << "," << SKquat[b].row4[3] << "\n";	// Traslazione
                        out << "		}\n";
                        out << "		TransformLink: *16 {\n";
                        out << "			a: 1,0,0,0,-0,1,0,0,0,-0,1,0,";
                        out << SKquat[b].row4[0] << "," << SKquat[b].row4[1] << "," << SKquat[b].row4[2] << "," << SKquat[b].row4[3] << "\n";					// Traslazione
                        out << "		}\n";
                        out << " 	}\n\n";
                    }
        }
}