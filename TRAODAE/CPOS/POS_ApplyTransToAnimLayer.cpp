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
Combina il layer di traslazioni del file POS con la bone HIP del file delle animazioni
INPUT: vector <POS_CLASS> &pos, vector <Animation_info> &Ani_header, vector < vector <AnimationCurveNode> > &Ani_curvenode
OUTPUT: vector < vector <AnimationCurveNode> > &Ani_curvenode
------------------------------------------------------------------------------------------------------------------*/

#include "stdafx.h"
#include "Classes.h"
#include "MISC/UI_Functions.h"
#include "ANIM/CAL_Functions.h"


void POS_ApplyTransToAnimLayer (vector <POS_CLASS> &pos, vector <Animation_info> &Ani_header, vector < vector <AnimationCurveNode> > &Ani_curvenode)
{
	class Matches {									// Questa classe conterrà tutte le corrispondenze trovate
	public:
		vector <unsigned int> POS_number;
		vector <unsigned int> CAL_number;
	};

	Matches Animations_found;

	// Ricerca corrispondenza hash tra animazione nel file CAL e traslazioni nel file POS
	for (unsigned int a = 0; a < Ani_header.size(); a++)
	{
		for (unsigned int p = 0; p < pos.size(); p++)
			if (pos[p].Animation_hashed == Ani_header[a].Name_hashed)
			{
				Animations_found.POS_number.push_back(p);
				Animations_found.CAL_number.push_back(a);
			}
	}

	if (Animations_found.POS_number.size() == 0)
		UI_Display_Error(false, "", "POS - CAL comparison error: no matching animation found.");

	// Somma le animazioni del file POS a quelle corrispondenti del file CAL
	for (unsigned int i = 0; i < Animations_found.POS_number.size(); i++)
	{
		UI_ProgressBar(i, Animations_found.POS_number.size(), 45, " Applying cutscene character root motion...    ");
		APB_Combine_AnimLayers(&Ani_curvenode[Animations_found.CAL_number[i]][0], pos[Animations_found.POS_number[i]].Cutscene_Root_Motion);
	}
}