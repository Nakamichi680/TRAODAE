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
Scrittura AnimationStack, AnimationLayer, AnimationCurveNode ed AnimationCurve
INPUT: int a, vector <Animation_info> &Ani_header, vector <int> &Anim_bones,
	   vector < vector <AnimationCurveNode> > &Ani_curvenode, vector <matrix4x4> &BONESquat
OUTPUT: ofstream &out
------------------------------------------------------------------------------------------------------------------*/

#include "stdafx.h"
#include "Classes.h"
#include "FBX/FBX_Functions.h"


void FBX_Write_Animation (int a,														// Numero animazione selezionata
						  vector <Animation_info> &Ani_header,							// Contiene informazioni generali sull'animazione corrente
						  vector <int> &Anim_bones,										// Indici delle bones (tutte le bones tranne le DYNAMIC)
						  vector < vector <AnimationCurveNode> > &Ani_curvenode,		// Classe contenente i dati da scrivere
						  vector <matrix4x4> &BONESquat,								// Valori di scalatura e traslazione provenienti dal CHR
						  ofstream &out)												// Flusso di output del file FBX
{
	/////////////////////// SCRITTURA ANIMATIONSTACK
	unsigned long long temp = Ani_header[a].nFrames * FBXframe1;
    out << "	AnimationStack: " << nodeID(98,a) << ", \"AnimStack::" << Ani_header[a].name << "\", \"\" {\n";
	out << "		Properties70:  {\n";
	out << "			P: \"LocalStart\", \"KTime\", \"Time\", \"\"," << FBXframe1 << endl;
	out << "			P: \"LocalStop\", \"KTime\", \"Time\", \"\"," << temp << endl;
	out << "			P: \"ReferenceStart\", \"KTime\", \"Time\", \"\"," << FBXframe1 << endl;
	out << "			P: \"ReferenceStop\", \"KTime\", \"Time\", \"\"," << temp << endl;
	out << "		}\n";
	out << "	}\n";

	/////////////////////// SCRITTURA ANIMATIONLAYER
	out << "	AnimationLayer: " << nodeID(97,a) << ", \"AnimLayer::BaseLayer\", \"\" {\n";
	out << "	}\n";

	for (unsigned int b = 0; b < min(Anim_bones.size(), Ani_curvenode[a].size()); b++)			// Ogni ciclo fa una bone
	{
		/////////////////////// SCRITTURA ANIMATIONCURVENODE
		out << Ani_curvenode[a][b].Text(a, b, BONESquat[Anim_bones[b]].row4[0], BONESquat[Anim_bones[b]].row4[1], BONESquat[Anim_bones[b]].row4[2]);

		/////////////////////// SCRITTURA ANIMATIONCURVE
		// Traslazioni
		if (Ani_curvenode[a][b].tX_flag)
			FBX_Write_AnimCurve_Subroutine(a, b, 51, BONESquat[Anim_bones[b]].row4[0], &Ani_curvenode[a][b], out);
		if (Ani_curvenode[a][b].tY_flag)
			FBX_Write_AnimCurve_Subroutine(a, b, 52, BONESquat[Anim_bones[b]].row4[1], &Ani_curvenode[a][b], out);
		if (Ani_curvenode[a][b].tZ_flag)
			FBX_Write_AnimCurve_Subroutine(a, b, 53, BONESquat[Anim_bones[b]].row4[2], &Ani_curvenode[a][b], out);
		// Rotazioni
		if (Ani_curvenode[a][b].rX_flag)
			FBX_Write_AnimCurve_Subroutine(a, b, 61, 0, &Ani_curvenode[a][b], out);
		if (Ani_curvenode[a][b].rY_flag)
			FBX_Write_AnimCurve_Subroutine(a, b, 62, 0, &Ani_curvenode[a][b], out);
		if (Ani_curvenode[a][b].rZ_flag)
			FBX_Write_AnimCurve_Subroutine(a, b, 63, 0, &Ani_curvenode[a][b], out);
		// Scalature
		if (Ani_curvenode[a][b].sX_flag)
			FBX_Write_AnimCurve_Subroutine(a, b, 71, 0, &Ani_curvenode[a][b], out);
		if (Ani_curvenode[a][b].sY_flag)
			FBX_Write_AnimCurve_Subroutine(a, b, 72, 0, &Ani_curvenode[a][b], out);
		if (Ani_curvenode[a][b].sZ_flag)
			FBX_Write_AnimCurve_Subroutine(a, b, 73, 0, &Ani_curvenode[a][b], out);
	}
}