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
Restituisce la Y della curva di Bezier, prendendo in ingresso la X (tempo) ed i parametri a, b, c, d
INPUT: float x, float a, float b, float c, float d
OUTPUT: float
------------------------------------------------------------------------------------------------------------------*/

#include "stdafx.h"


float APB_BezierIDX (float x, float a, float b, float c, float d)
{
    return (pow(x, 3) * (-a + 3 * b - 3 * c + d) + pow(x, 2) * (3 * a - 6 * b + 3 * c) + x * (-3 * a + 3 * b) + a);
}