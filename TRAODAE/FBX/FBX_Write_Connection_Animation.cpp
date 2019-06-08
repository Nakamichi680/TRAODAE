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
Scrittura Connections delle animazioni
INPUT: int a, vector <int> &Anim_bones, vector < vector <AnimationCurveNode> > &Ani_curvenode,
OUTPUT: ofstream &out
------------------------------------------------------------------------------------------------------------------*/

#include "stdafx.h"
#include "Classes.h"
#include "FBX/FBX_Functions.h"


void FBX_Write_Connection_Animation (int a,														// Numero animazione selezionata
                                     vector <int> &Anim_bones,									// Indici delle bones (tutte le bones tranne le DYNAMIC)
                                     vector < vector <AnimationCurveNode> > &Ani_curvenode,		// Per il controllo dei flags delle trasformazioni attive
                                     ofstream &out)												// Flusso di output del file FBX
{
    out << "	C: \"OO\"," << nodeID(97,a) << "," << nodeID(98,a) << "\n";													// AnimationLayer, AnimationStack

    for (unsigned int b = 0; b < min(Anim_bones.size(), Ani_curvenode[a].size()); b++)						// Ogni ciclo fa una bone
    {
        if (Ani_curvenode[a][b].tX_flag || Ani_curvenode[a][b].tY_flag || Ani_curvenode[a][b].tZ_flag)		//  Traslazione
        {
            out << "	C: \"OO\"," << nodeID(50,b,a) << "," << nodeID(97,a) << "\n";										// AnimationCurveNode t, AnimationLayer
            out << "	C: \"OP\"," << nodeID(50,b,a) << "," << nodeID(15,Anim_bones[b]) << ", \"Lcl Translation\"\n";		// AnimationCurveNode t, Bone
            if (Ani_curvenode[a][b].tX_flag)
                out << "	C: \"OP\"," << nodeID(51,b,a) << "," << nodeID(50,b,a) << ", \"d|X\"\n";						// AnimationCurve tX, AnimationCurveNode t
            if (Ani_curvenode[a][b].tY_flag)
                out << "	C: \"OP\"," << nodeID(52,b,a) << "," << nodeID(50,b,a) << ", \"d|Y\"\n";						// AnimationCurve tY, AnimationCurveNode t
            if (Ani_curvenode[a][b].tZ_flag)
                out << "	C: \"OP\"," << nodeID(53,b,a) << "," << nodeID(50,b,a) << ", \"d|Z\"\n";						// AnimationCurve tZ, AnimationCurveNode t
        }
        if (Ani_curvenode[a][b].rX_flag || Ani_curvenode[a][b].rY_flag || Ani_curvenode[a][b].rZ_flag)		// Rotazione
        {
            out << "	C: \"OO\"," << nodeID(60,b,a) << "," << nodeID(97,a) << "\n";										// AnimationCurveNode r, AnimationLayer
            out << "	C: \"OP\"," << nodeID(60,b,a) << "," << nodeID(15,Anim_bones[b]) << ", \"Lcl Rotation\"\n";			// AnimationCurveNode r, Bone
            if (Ani_curvenode[a][b].rX_flag)
                out << "	C: \"OP\"," << nodeID(61,b,a) << "," << nodeID(60,b,a) << ", \"d|X\"\n";						// AnimationCurve rX, AnimationCurveNode r
            if (Ani_curvenode[a][b].rY_flag)
                out << "	C: \"OP\"," << nodeID(62,b,a) << "," << nodeID(60,b,a) << ", \"d|Y\"\n";						// AnimationCurve rY, AnimationCurveNode r
            if (Ani_curvenode[a][b].rZ_flag)
                out << "	C: \"OP\"," << nodeID(63,b,a) << "," << nodeID(60,b,a) << ", \"d|Z\"\n";						// AnimationCurve rZ, AnimationCurveNode r
        }
        if (Ani_curvenode[a][b].sX_flag || Ani_curvenode[a][b].sY_flag || Ani_curvenode[a][b].sZ_flag)		// Scalatura
        {
            out << "	C: \"OO\"," << nodeID(70,b,a) << "," << nodeID(97,a) << "\n";										// AnimationCurveNode s, AnimationLayer
            out << "	C: \"OP\"," << nodeID(70,b,a) << "," << nodeID(15,Anim_bones[b]) << ", \"Lcl Scaling\"\n";			// AnimationCurveNode s, Bone
            if (Ani_curvenode[a][b].sX_flag)
                out << "	C: \"OP\"," << nodeID(71,b,a) << "," << nodeID(70,b,a) << ", \"d|X\"\n";						// AnimationCurve sX, AnimationCurveNode s
            if (Ani_curvenode[a][b].sY_flag)
                out << "	C: \"OP\"," << nodeID(72,b,a) << "," << nodeID(70,b,a) << ", \"d|Y\"\n";						// AnimationCurve sY, AnimationCurveNode s
            if (Ani_curvenode[a][b].sZ_flag)
                out << "	C: \"OP\"," << nodeID(73,b,a) << "," << nodeID(70,b,a) << ", \"d|Z\"\n";						// AnimationCurve sZ, AnimationCurveNode s
        }
    }
}