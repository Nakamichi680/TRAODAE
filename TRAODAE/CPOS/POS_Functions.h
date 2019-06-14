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


// Legge il file CPOS (contiene le informazioni di traslazione dei personaggi durante le cutscenes)
bool POS_Read (ifstream &posfile, vector <POS_CLASS> &pos, IO_CLASS IO);

// Chiede quale POS applicare al layer di animazioni ed effettua l'operazione
void POS_ApplyTransToAnimLayer (vector <POS_CLASS> &pos, vector <Animation_info> &Ani_header, vector < vector <AnimationCurveNode> > &Ani_curvenode);