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


#pragma once
#include "Classes.h"
#include "CHAR/CHR_Struct.h"


// Scrittura AnimationStack, AnimationLayer, AnimationCurveNode ed AnimationCurve
void FBX_Write_Animation (int a,
						  vector <Animation_info> &Ani_header,
						  vector <int> &Anim_bones,
						  vector < vector <AnimationCurveNode> > &Ani_curvenode,
						  vector <matrix4x4> &BONESquat,
						  ofstream &out);

// Scrittura AnimationCurve
void FBX_Write_AnimCurve_Subroutine (int a, int b, short RSTaxis, float CHRtrasl, AnimationCurveNode *Ani_curvenode, ofstream &out);

// Scrittura BindPose
void FBX_Write_BindPose (FBX_COUNT_CLASS FBX_Count,
						 MESH1_CLASS &mesh1,
						 vector <MESH2_CLASS> &mesh2,
						 vector < vector <int> > &MESH1_FACES,
						 vector < vector < vector <int> > > &MESH2_FACES,
						 CHR_HEADER &chr_header,
						 CHR_MESH2_LIST &chr_mesh2_list,
						 vector <matrix4x4> &SKquat,
						 ofstream &out);

// Scrittura BindPose del blend shape
void FBX_Write_BindPose_Blendshape (FBX_COUNT_CLASS FBX_Count, CHR_HEADER &chr_header, TMT_CLASS &tmt, vector <matrix4x4> &SKquat, ofstream &out);

// Scrittura Null, Model, Geometry, Deformer, SubDeformer e BlendShape Geometry del file dei blend shapes
void FBX_Write_Blendshape (TMT_CLASS &tmt, vector <int> &BLENDSHAPE_FACES, vector <matrix4x4> &SKquat, ofstream &out);

// Scrittura bones
void FBX_Write_Bone (CHR_HEADER &chr_header, vector <string> &Bone_name, vector <matrix4x4> &BONESquat, ofstream &out);

// Scrittura Connections delle animazioni
void FBX_Write_Connection_Animation (int a, vector <int> &Anim_bones, vector < vector <AnimationCurveNode> > &Ani_curvenode, ofstream &out);

// Scrittura Connections del blendshape
void FBX_Write_Connection_Blendshape (TMT_CLASS &tmt, ofstream &out);

// Scrittura Connections delle bones
void FBX_Write_Connection_Bone (vector <unsigned int> &Hierarchy, CHR_HEADER &chr_header, ofstream &out);

// Scrittura Connections dei materiali
void FBX_Write_Connection_Material (vector <TextureHeader> &TextureHeader, Material *Materials, ofstream &out);

// Scrittura Connections del gruppo MESH 1
void FBX_Write_Connection_Mesh1 (MESH1_CLASS &mesh1,
								 vector < vector <int> > &MESH1_FACES,
								 vector < vector <unsigned short> > &MESH1_vINDX,
								 CHR_HEADER &chr_header,
								 ofstream &out);

// Scrittura Connections del gruppo MESH 2
void FBX_Write_Connection_Mesh2 (vector <MESH2_CLASS> &mesh2,
								 vector < vector < vector <int> > > &MESH2_FACES,
								 CHR_MESH2_LIST &chr_mesh2_list,
								 ofstream &out);

// Scrittura Header
void FBX_Write_Header (ofstream &out);

// Scrittura materiale
void FBX_Write_Material (Material *Materials, unsigned int *Nlambert, unsigned int *Nphong, ofstream &out);

// Scrittura Null, Model, Geometry, Deformer e SubDeformer del gruppo MESH 1
void FBX_Write_Mesh1 (MESH1_CLASS &mesh1,
					  vector < vector <int> > &MESH1_FACES,
					  vector < vector <unsigned short> > &MESH1_vINDX,
					  CHR_HEADER &chr_header,
					  vector <matrix4x4> &SKquat,
					  ofstream &out);

// Scrittura Null, Model, Geometry, Deformer e SubDeformer del gruppo MESH 2
void FBX_Write_Mesh2 (vector <MESH2_CLASS> &mesh2,
					  vector < vector < vector <int> > > &MESH2_FACES,
					  vector < vector < vector <unsigned short> > > &MESH2_vINDX,
					  CHR_MESH2_LIST &chr_mesh2_list,
					  vector <matrix4x4> &SKquat,
					  ofstream &out);

// Scrittura Object definitions
void FBX_Write_Object_definitions (FBX_COUNT_CLASS FBX_Count, ofstream &out);

// Scrittura dati texture
void FBX_Write_Texture (IO_CLASS IO, TextureHeader *TextureHeader, ofstream &out);

// Generatore ID per nodi del file FBX. Scrive il tipo di nodo (prime due cifre) e fa il padding degi numeri a seguire
string nodeID (unsigned int node_type, unsigned int value1 = 0, unsigned int value2 = 0, unsigned int value3 = 0);