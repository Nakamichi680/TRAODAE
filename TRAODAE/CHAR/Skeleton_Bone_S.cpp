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
Applica le scalature ad una bone. INUTILIZZATO
INPUT: matrix4x4 in
OUTPUT: matrix4x4
------------------------------------------------------------------------------------------------------------------*/

#include "stdafx.h"
#include "Classes.h"


matrix4x4 Skeleton_Bone_S (matrix4x4 in)
{
	matrix4x4 out;
	out.row4[0] = in.row4[0]*in.row1[0]+in.row4[1]*in.row2[0]+in.row4[2]*in.row3[0];
	out.row4[1] = in.row4[0]*in.row1[1]+in.row4[1]*in.row2[1]+in.row4[2]*in.row3[1];
	out.row4[2] = in.row4[0]*in.row1[2]+in.row4[1]*in.row2[2]+in.row4[2]*in.row3[2];
	out.row4[3] = in.row4[0]*in.row1[3]+in.row4[1]*in.row2[3]+in.row4[2]*in.row3[3];
    return out;
}