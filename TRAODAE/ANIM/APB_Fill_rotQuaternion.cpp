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
Riempie i vettori vuoti delle rotazioni con valori di default
INPUT: AnimationCurveNode *Ani_curvenode, unsigned int nFrames
OUTPUT: AnimationCurveNode *Ani_curvenode
------------------------------------------------------------------------------------------------------------------*/

#include "stdafx.h"
#include "Classes.h"


void APB_Fill_rotQuaternion (AnimationCurveNode *Ani_curvenode, unsigned int nFrames)
{
    if (Ani_curvenode->rX_flag || Ani_curvenode->rY_flag || Ani_curvenode->rZ_flag)		// Se è presente almeno una rotazione
    {
        if (Ani_curvenode->rotQuatX.size() == 0)			// Riempie di 0 il vettore della X
        {
            for (unsigned int i = 0; i < nFrames; i++)
                Ani_curvenode->rotQuatX.push_back(0);
            Ani_curvenode->rX_flag = true;
        }
        if (Ani_curvenode->rotQuatY.size() == 0)            // Riempie di 0 il vettore della Y
        {
            for (unsigned int i = 0; i < nFrames; i++)
                Ani_curvenode->rotQuatY.push_back(0);
            Ani_curvenode->rY_flag = true;
        }
        if (Ani_curvenode->rotQuatZ.size() == 0)            // Riempie di 0 il vettore della Z
        {
            for (unsigned int i = 0; i < nFrames; i++)
                Ani_curvenode->rotQuatZ.push_back(0);
            Ani_curvenode->rZ_flag = true;
        }
        if (Ani_curvenode->rotQuatW.size() == 0)            // Riempie di 1 il vettore della W
            for (unsigned int i = 0; i < nFrames; i++)
                Ani_curvenode->rotQuatW.push_back(1);
    }
}