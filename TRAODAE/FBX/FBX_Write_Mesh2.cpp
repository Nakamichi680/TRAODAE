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
Scrittura Null, Model, Geometry, Deformer e SubDeformer del gruppo MESH 2
INPUT: vector <MESH2_CLASS> &mesh2, vector < vector < vector <int> > > &MESH2_FACES,
	   vector < vector < vector <unsigned short> > > &MESH2_vINDX, CHR_MESH2_LIST &chr_mesh2_list, vector <matrix4x4> &SKquat
OUTPUT: ofstream &out
------------------------------------------------------------------------------------------------------------------*/

#include "stdafx.h"
#include "Classes.h"
#include "FBX/FBX_Functions.h"


void FBX_Write_Mesh2 (vector <MESH2_CLASS> &mesh2,
                      vector < vector < vector <int> > > &MESH2_FACES,
                      vector < vector < vector <unsigned short> > > &MESH2_vINDX,
                      CHR_MESH2_LIST &chr_mesh2_list,
                      vector <matrix4x4> &SKquat,
                      ofstream &out)
{
    for (unsigned int g = 0; g < chr_mesh2_list.nMeshes2; g++)	// Ogni ciclo è un gruppo MESH 2
        if (mesh2[g].nV != 0)									// Controlla ed eventualmente esclude i gruppi MESH 2 privi di vertici
        {
            /////////////////////// SCRITTURA MESH 2 NULL
            if (mesh2[g].hashed)
                out << "	Model: " << nodeID(16,g) << ", \"Model::MESH2_" << mesh2[g].name << "\", \"Null\" {\n";		// Se il codice hash non è decodificato 
            else
                out << "	Model: " << nodeID(16,g) << ", \"Model::" << mesh2[g].name << "\", \"Null\" {\n";			// Se il codice hash è decodificato
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

            for (unsigned int el = 0; el < mesh2[g].nElements; el++)	// Ogni ciclo scrive un elemento del gruppo MESH 2
                if (MESH2_FACES[g][el].size() > 2)						// Serve ad escludere gli elementi privi di facce
                {
                    /////////////////////// SCRITTURA MODEL
                    if (mesh2[g].hashed)
                        out << "	Model: " << nodeID(17,g,el) << ", \"Model::MESH2_" << mesh2[g].name_lower();		// Se il codice hash non è decodificato 
                    else
                        out << "	Model: " << nodeID(17,g,el) << ", \"Model::" << mesh2[g].name_lower();				// Se il codice hash è decodificato 
                    if (mesh2[g].nElements<2)
                        out << "\", \"Mesh\" {\n";
                    else
                        out << "_part_" << el << "\", \"Mesh\" {\n";
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
                    out << "	Geometry: " << nodeID(18,g,el) << ", \"Geometry::\", \"Mesh\" {\n";
                    out << "		Properties70:  {\n";
                    out << "			P: \"Color\", \"ColorRGB\", \"Color\", \"\",0.725490196078431,0.181372549019608,0.0313725490196078\n";
                    out << "		}\n";
                    // Scrive i vertici
                    out << "		Vertices: *" << MESH2_vINDX[g][el].size() * 3 << " {\n";		// Numero di vertici x 3
                    out << "			a: ";
                    for (unsigned int v = 0; v < MESH2_vINDX[g][el].size(); v++)
                    {
                        out << mesh2[g].X[MESH2_vINDX[g][el][v]] << "," << mesh2[g].Y[MESH2_vINDX[g][el][v]] << "," << mesh2[g].Z[MESH2_vINDX[g][el][v]];
                        if (MESH2_vINDX[g][el].size() - 1 == v) out << "\n";
                        else out << ",\n";
                    }
                    out << "		}\n";
                    // Scrive le facce
                    out << "		PolygonVertexIndex: *" << MESH2_FACES[g][el].size() << " {\n";	// Numero di indici di vertici
                    out << "			a: ";
                    for (unsigned int P = 0; P < MESH2_FACES[g][el].size(); P++)
                    {
                        out << MESH2_FACES[g][el][P];
                        if (MESH2_FACES[g][el].size() - P != 1)
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
                    out << "			Normals: *" << MESH2_vINDX[g][el].size() * 3 << " {\n";		// Numero di normals x 3
                    out << "				a: ";
                    for (unsigned int vn = 0; vn < MESH2_vINDX[g][el].size(); vn++)
                    {
                        out << mesh2[g].Xn[MESH2_vINDX[g][el][vn]] << "," << mesh2[g].Yn[MESH2_vINDX[g][el][vn]] << "," << mesh2[g].Zn[MESH2_vINDX[g][el][vn]];
                        if (MESH2_vINDX[g][el].size() - 1 == vn) out << "\n";
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
                    out << "			Tangents: *" << MESH2_vINDX[g][el].size() * 3 << " {\n";	// Numero di tangents x 3
                    out << "				a: ";
                    for (unsigned int vtg = 0; vtg < MESH2_vINDX[g][el].size(); vtg++)
                    {
                        out << mesh2[g].Xtg[MESH2_vINDX[g][el][vtg]] << "," << mesh2[g].Ytg[MESH2_vINDX[g][el][vtg]] << "," << mesh2[g].Ztg[MESH2_vINDX[g][el][vtg]];
                        if (MESH2_vINDX[g][el].size() - 1 == vtg) out << "\n";
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
                    out << "			Binormals: *" << MESH2_vINDX[g][el].size() * 3 << " {\n";	// Numero di binormals x 3
                    out << "a: ";
                    for (unsigned int vbn = 0; vbn < MESH2_vINDX[g][el].size(); vbn++)
                    {
                        out << mesh2[g].Xbn[MESH2_vINDX[g][el][vbn]] << "," << mesh2[g].Ybn[MESH2_vINDX[g][el][vbn]] << "," << mesh2[g].Zbn[MESH2_vINDX[g][el][vbn]];
                        if (MESH2_vINDX[g][el].size() - 1 == vbn) out << "\n";
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
                    out << "			UV: *" << MESH2_vINDX[g][el].size() * 2 << " {\n";			// Numero di UV x 2
                    out << "a: ";
                    for (unsigned int uv = 0; uv < MESH2_vINDX[g][el].size(); uv++)
                    {
                        out << mesh2[g].U[MESH2_vINDX[g][el][uv]] << "," << mesh2[g].V[MESH2_vINDX[g][el][uv]];
                        if (MESH2_vINDX[g][el].size() - 1 == uv) out << "\n";
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
                    out << "	Deformer: " << nodeID(19,g,el) << ", \"Deformer::\", \"Skin\" {\n";
                    out << "		Version: 101\n";
                    out << "		Link_DeformAcuracy: 50\n";
                    out << "	}\n";

                    /////////////////////// SCRITTURA SUBDEFORMER
                    out << "	Deformer: " << nodeID(20,mesh2[g].Bone,g,el) << ", \"SubDeformer::\", \"Cluster\" {\n";
                    out << "		Version: 100\n";
                    out << "		UserData: \"\", \"\"\n";
                    out << "		Indexes: *" << MESH2_vINDX[g][el].size() << " {\n";
                    out << "			a: ";
                    for (unsigned int I = 0; I < MESH2_vINDX[g][el].size(); I++)						// SCRITTURA INDICI
                    {
                        out << I;
                        if (MESH2_vINDX[g][el].size() - I != 1)
                        {
                            out << ",";
                            if ((I + 1) % 30 == 0 && I != 0)   out << "\n";
                        }
                        else out << "\n";
                    }
                    out << "		}\n";
                    out << "		Weights: *" << MESH2_vINDX[g][el].size() << " {\n";
                    out << "			a: ";
                    for (unsigned int W = 0; W < MESH2_vINDX[g][el].size(); W++)						// SCRITTURA PESI (SEMPRE 1)
                    {
                        out << "1";
                        if (MESH2_vINDX[g][el].size() - W != 1)
                        {
                            out << ",";
                            if ((W + 1) % 30 == 0 && W != 0)   out << "\n";
                        }
                        else out << "\n";
                    }
                    out << "		}\n";
                    int b = mesh2[g].Bone;
                    out << "		Transform: *16 {\n";
                    out << "			a: 1,0,0,0,0,1,0,0,0,0,1,0,";
                    out << SKquat[b].row4[0] * -1 << "," << SKquat[b].row4[1] * -1 << "," << SKquat[b].row4[2] * -1 << "," << SKquat[b].row4[3] << "\n";		// Traslazione
                    out << "		}\n";
                    out << "		TransformLink: *16 {\n";
                    out << "			a: 1,0,0,0,-0,1,0,0,0,-0,1,0,";
                    out << SKquat[b].row4[0] << "," << SKquat[b].row4[1] << "," << SKquat[b].row4[2] << "," << SKquat[b].row4[3] << "\n";						// Traslazione
                    out << "		}\n";
                    out << "	}\n\n";
                }
        }
}