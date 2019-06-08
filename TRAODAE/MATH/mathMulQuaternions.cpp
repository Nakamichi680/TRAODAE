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
Moltiplica due quaternioni
INPUT: Quaternion a, Quaternion b
OUTPUT: Quaternion
------------------------------------------------------------------------------------------------------------------*/

#include "stdafx.h"
#include "Classes.h"


Quaternion mathMulQuaternions (Quaternion a, Quaternion b)
{
	Quaternion c;
	c.x = b.w * a.x + b.x * a.w - b.y * a.z + b.z * a.y;
	c.y = b.w * a.y + b.x * a.z + b.y * a.w - b.z * a.x;
	c.z = b.w * a.z - b.x * a.y + b.y * a.x + b.z * a.w;
	c.w = b.w * a.w - b.x * a.x - b.y * a.y - b.z * a.z;
	return c;
}