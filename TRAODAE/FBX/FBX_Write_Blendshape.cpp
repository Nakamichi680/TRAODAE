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
Scrittura Null, Model, Geometry, Deformer, SubDeformer e BlendShape Geometry del file dei blend shapes
INPUT: TMT_CLASS &tmt, vector <int> &BLENDSHAPE_FACES, vector <matrix4x4> &SKquat
OUTPUT: ofstream &out
------------------------------------------------------------------------------------------------------------------*/

#include "stdafx.h"
#include "Classes.h"
#include "FBX/FBX_Functions.h"


void FBX_Write_Blendshape (TMT_CLASS &tmt,
						   vector <int> &BLENDSHAPE_FACES,
						   vector <matrix4x4> &SKquat,
						   ofstream &out)
{
	unsigned int g = tmt.mesh2_group;			// Gruppo MESH 2 associato al blend shape
	unsigned int b = tmt.mesh2_bone;			// Bone associata al gruppo MESH 2

	/////////////////////// SCRITTURA BLENDSHAPE MESH NORMALE NULL
	out << "	Model: " << nodeID(25,g) << ", \"Model::BLENDSHAPE_" << tmt.name << "\", \"Null\" {\n";
	out << "		Version: 232\n";
	out << "		Properties70:  {\n";
	out << "			P: \"InheritType\", \"enum\", \"\", \"\",1\n";
	out << "			P: \"ScalingMin\", \"Vector3D\", \"Vector\", \"\",1,1,1\n";
	out << "			P: \"DefaultAttributeIndex\", \"int\", \"Integer\", \"\",0\n";
	out << "		}\n";
	out << "		Shading: T\n";
	out << "		Culling: \"CullingOff\"\n";
	out << "	}\n\n";

	/////////////////////// SCRITTURA MODEL MESH NORMALE
	out << "	Model: " << nodeID(26,g) << ", \"Model::BlendShape_" << tmt.name_lower() << "_Master\", \"Mesh\" {\n";
	out << "		Version: 232\n";
	out << "		Properties70:  {\n";
	out << "			P: \"InheritType\", \"enum\", \"\", \"\",1\n";
	out << "			P: \"ScalingMin\", \"Vector3D\", \"Vector\", \"\",1,1,1\n";
	out << "			P: \"DefaultAttributeIndex\", \"int\", \"Integer\", \"\",0\n";
	out << "		}\n";
	out << "		Shading: T\n";
	out << "		Culling: \"CullingOff\"\n";
	out << "	}\n\n";

	/////////////////////// SCRITTURA GEOMETRY MESH NORMALE
	out << "	Geometry: " << nodeID(27,g) << ", \"Geometry::\", \"Mesh\" {\n";
	out << "		Properties70:  {\n";
	out << "			P: \"Color\", \"ColorRGB\", \"Color\", \"\",0.225490196078431,0.881372549019608,0.0313725490196078\n";
	out << "		}\n";
	// Scrive i vertici
	out << "		Vertices: *" << tmt.nV *3 << " {\n";											// Numero di vertici x 3
	out << "			a: ";
	for (unsigned int v = 0; v < tmt.nV; v++)
	{
		out << tmt.X[0][v] << "," << tmt.Y[0][v] << "," << tmt.Z[0][v];
		if (tmt.nV - 1 == v) out << "\n";
		else out << ",\n";
	}
	out << "		}\n";
	// Scrive le facce
	out << "		PolygonVertexIndex: *" << BLENDSHAPE_FACES.size() << " {\n";					// Numero di indici di vertici
	out << "			a: ";
	for (unsigned int P = 0; P < BLENDSHAPE_FACES.size(); P++)
	{
		out << BLENDSHAPE_FACES[P];
		if (BLENDSHAPE_FACES.size() - P != 1)
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
	out << "			Normals: *" << tmt.nV *3 << " {\n";											// Numero di normals x 3
	out << "				a: ";
	for (unsigned int vn = 0; vn < tmt.nV; vn++)
	{
		out << tmt.Xn[0][vn] << "," << tmt.Yn[0][vn] << "," << tmt.Zn[0][vn];
		if (tmt.nV - 1 == vn) out << "\n";
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
	out << "			UV: *" << tmt.nV * 2 << " {\n";												// Numero di UV x 2
	out << "				a: ";
	for (unsigned int uv = 0; uv < tmt.nV; uv++)
	{
		out << tmt.U[0][uv] << "," << tmt.V[0][uv];
		if (tmt.nV - 1 == uv) out << "\n";
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
	out << "				Type: \"LayerElementMaterial\"\n";
	out << "				TypedIndex: 0\n";
	out << "			}\n";
	out << "			LayerElement:  {\n";
	out << "				Type: \"LayerElementUV\"\n";
	out << "				TypedIndex: 0\n";
	out << "			}\n";
	out << "		}\n";
	out << "	}\n\n";

	/////////////////////// SCRITTURA DEFORMER BLENDSHAPE MESH NORMALE
	out << "	Deformer: " << nodeID(28,g) << ", \"Deformer::BlendShape_" << tmt.name << "\", \"BlendShape\" {\n";
	out << "		Version: 100\n";
	out << "	}\n";

	for (unsigned int n = 1; n <= tmt.nBlendshapes; n++)
	{
		/////////////////////// SCRITTURA SUBDEFORMER BLENDSHAPE
		out << "	Deformer: " << nodeID(29,g,n) << ", \"SubDeformer::BlendShape_" << tmt.name_lower() << "." << tmt.name_lower() << "_" << n << "\", \"BlendShapeChannel\" {\n";
		out << "		Version: 100\n";
		out << "		DeformPercent: 0\n";
		out << "		FullWeights: *1 {\n";
		out << "			a: 100\n";
		out << "		}\n";
		out << "	}\n";

		/////////////////////// SCRITTURA GEOMETRY BLENDSHAPE
		out << "	Geometry: " << nodeID(30,g,n) << ", \"Geometry::BlendShape_" << tmt.name_lower() << "_" << n << "\", \"Shape\" {\n";
		out << "		Version: 100\n";
		// Scrittura indici vertici 
		out << "		Indexes: *" << tmt.BLENDSHAPE_vINDX[n].size() << " {\n";					// Numero di vertici differenti da quelli della mesh normale
		out << "			a: ";
		for (unsigned int I = 0; I < tmt.BLENDSHAPE_vINDX[n].size(); I++)
		{
			out << tmt.BLENDSHAPE_vINDX[n][I];
			if (tmt.BLENDSHAPE_vINDX[n].size() - I != 1)
			{
				out << ",";
				if ((I + 1) % 30 == 0 && I != 0)  out << "\n";
			}
			else out << "\n";
		}
		out << "		}\n";
		// Scrittura vertici
		out << "		Vertices: *" << tmt.BLENDSHAPE_vINDX[n].size() * 3 << " {\n";				// Numero di vertici differenti da quelli della mesh normale x 3
		out << "			a: ";
		for (unsigned int v = 0; v < tmt.BLENDSHAPE_vINDX[n].size(); v++)
		{
			out << tmt.X[n][v] << "," << tmt.Y[n][v] << "," << tmt.Z[n][v];
			if (tmt.BLENDSHAPE_vINDX[n].size() - 1 == v) out << "\n";
			else out << ",\n";
		}
		out << "		}\n";
		// Scrittura normals
		out << "		Normals: *" << tmt.BLENDSHAPE_vINDX[n].size() * 3 << " {\n";				// Numero di normals x 3
		out << "			a: ";
		for (unsigned int vn = 0; vn < tmt.BLENDSHAPE_vINDX[n].size(); vn++)
		{
			out << tmt.Xn[n][vn] << "," << tmt.Yn[n][vn] << "," << tmt.Zn[n][vn];
			if (tmt.BLENDSHAPE_vINDX[n].size() - 1 == vn) out << "\n";
			else out << ",\n";
		}
		out << "		}\n";
		// Scrittura UVs
		out << "		UV: *" << tmt.BLENDSHAPE_vINDX[n].size() * 2 << " {\n";						// Numero di UV x 2
		out << "			a: ";
		for (unsigned int uv = 0; uv < tmt.BLENDSHAPE_vINDX[n].size(); uv++)
		{
			out << tmt.U[n][uv] << "," << tmt.V[n][uv];
			if (tmt.BLENDSHAPE_vINDX[n].size() - 1 == uv) out << "\n";
			else out << ",\n";
		}
		out << "		}\n";
		out << "	}\n";
	}

	/////////////////////// SCRITTURA DEFORMER X BONE
    out << "	Deformer: " << nodeID(31,g) << ", \"Deformer::\", \"Skin\" {\n";
    out << "		Version: 101\n";
    out << "		Link_DeformAcuracy: 50\n";
    out << "	}\n";

    /////////////////////// SCRITTURA SUBDEFORMER X BONE
    out << "	Deformer: " << nodeID(32,b,g) << ", \"SubDeformer::\", \"Cluster\" {\n";
    out << "		Version: 100\n";
    out << "		UserData: \"\", \"\"\n";
    out << "		Indexes: *" << tmt.nV << " {\n";
    out << "			a: ";
    for (unsigned int I = 0; I < tmt.nV; I++)														// SCRITTURA INDICI
    {
        out << I;
        if (tmt.nV - I != 1)
        {
            out << ",";
            if ((I + 1) % 30 == 0 && I != 0)   out << "\n";
        }
        else out << "\n";
    }
    out << "		}\n";
    out << "		Weights: *" << tmt.nV << " {\n";
    out << "			a: ";
    for (unsigned int W = 0; W < tmt.nV; W++)														// SCRITTURA PESI (SEMPRE 1)
    {
        out << "1";
        if (tmt.nV - W != 1)
        {
            out << ",";
            if ((W + 1) % 30 == 0 && W != 0)   out << "\n";
        }
        else out << "\n";
    }
    out << "		}\n";
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