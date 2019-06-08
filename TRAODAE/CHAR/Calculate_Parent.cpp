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
Prende in ingresso una bone e restituisce quella da cui essa dipende
INPUT: int b, vector <unsigned int> Hierarchy
OUTPUT: int
------------------------------------------------------------------------------------------------------------------*/

#include "stdafx.h"


int Calculate_Parent (int b, vector <unsigned int> Hierarchy)
{
    if (b != 0)
    {
		int RootBone = 0;
		int Ignore = 0;
        if (Hierarchy[b] == 0xC0 || Hierarchy[b] == 0xC1 ||	Hierarchy[b] == 0x00 || Hierarchy[b] == 0x28 ||			// Questi valori indicano dipendenza dalla bone superiore
            Hierarchy[b] == 0x01 || Hierarchy[b] == 0x0400 || Hierarchy[b] == 0x0401)
            return (b-1);
        if (Hierarchy[b] == 0x03 || Hierarchy[b] == 0x02)
        {
            for (int i = b - 1; i >= 0; i--)
            {
                if (Hierarchy[i] == 0x02)
                    Ignore++;
                if (Hierarchy[i] == 0x01)
                    Ignore--;
                if (Hierarchy[i] == 0x01 && Ignore <= 0)
                {
                    RootBone = i - 1;
                    i = -1;
                }
            }
            return (RootBone);
        }
        if (Hierarchy[b] == 0x403 || Hierarchy[b] == 0x402)
        {
            for (int i = b - 1; i >= 0; i--)
            {
                if (Hierarchy[i] == 0x402)
                    Ignore++;
                if (Hierarchy[i] == 0x401)
                    Ignore--;
                if (Hierarchy[i] == 0x401 && Ignore <= 0)
                {
                    RootBone = i - 1;
                    i = -1;
                }
            }
            return (RootBone);
        }
        if (Hierarchy[b] == 0xC3 || Hierarchy[b] == 0xC2)
        {
            for (int i = b - 1; i >= 0; i--)
            {
                if (Hierarchy[i] == 0xC2)
                    Ignore++;
                if (Hierarchy[i] == 0xC1)
                    Ignore--;
                if (Hierarchy[i] == 0xC1 && Ignore <= 0)
                {
                    RootBone = i - 1;
                    i = -1;
                }
            }
            return (RootBone);
        }
        if (Hierarchy[b] == 0x2A || Hierarchy[b] == 0x2B)
        {
            for (int i = b - 1; i >= 0; i--)
                if (Hierarchy[i] == 0x01)
                {
                    RootBone = i - 1;
                    i = -1;
                }
            return (RootBone);
        }
        return 0;		// Se non trova niente restituisce HIP (bone 0)
    }
}