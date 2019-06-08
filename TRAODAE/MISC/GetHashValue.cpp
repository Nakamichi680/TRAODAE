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
Restituisce l'hash della stringa in ingresso
INPUT: const char *String
OUTPUT: int
------------------------------------------------------------------------------------------------------------------*/

#include "stdafx.h"


int GetHashValue(const char *String)
{
	const char *v1, *i;
	int Hash, j;
	int v2 = 0;
	v1 = String;
	for (i = String; *i; v2++)
		i++;
	Hash = v2;
	for (j = (v2 >> 6) + 1; v2 > 0; v1++)
	{
		Hash ^= (Hash >> 2) + 32 * Hash + *v1;
		v2 -= j;
	}
	return Hash;
}