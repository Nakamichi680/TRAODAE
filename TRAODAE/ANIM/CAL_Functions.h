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


#pragma once
#include "Classes.h"


// Restituisce la Y della curva di Bezier, prendendo in ingresso la X (tempo) ed i parametri a, b, c, d
float APB_BezierIDX (float x, float a, float b, float c, float d);

// Combina due layers di animazioni
void APB_Combine_AnimLayers (AnimationCurveNode *dest, AnimationCurveNode addend);

// Disabilita tutte le scalature
void APB_Disable_Scaling (vector < vector <AnimationCurveNode> > &Ani_curvenode);

// Restituisce una curva di animazione con un valore fisso
AnimationCurveData APB_Fill_AnimationCurveData (float value, unsigned int nFrames);

// Riempie i vettori vuoti delle rotazioni con valori di default
void APB_Fill_rotQuaternion (AnimationCurveNode *Ani_curvenode, unsigned int nFrames);

// Restituisce gli slopes della spline cubica di Hermite passante per 4 punti (due arbitrari, uno iniziale ed uno finale)
void APB_HermiteFindBC (float X1,float Y1, float X2, float Y2, float a, float d, float *b, float *c);

// Lettura rotazioni 2 (salva ogni frame, perdendo i valori statici e le curve di Bezier)
vector <float> CAL_Get_Rquat_Keyframes_2 (ifstream &calfile, unsigned int nFrames, float correction_factor);

// Lettura traslazioni, rotazioni e scalature
AnimationCurveData CAL_Get_TRS_Keyframes (ifstream &calfile, unsigned int nFrames, float correction_factor);

// Lettura traslazioni, rotazioni e scalature 2 (salva ogni frame, perdendo i valori statici e le curve di Bezier)
AnimationCurveData CAL_Get_TRS_Keyframes_2 (ifstream &calfile, unsigned int nFrames, float correction_factor);

// Lettura file CAL
void CAL_Read (ifstream &calfile, vector <Animation_info> &Ani_header, vector < vector <AnimationCurveNode> > &Ani_curvenode, bool Export_POS);