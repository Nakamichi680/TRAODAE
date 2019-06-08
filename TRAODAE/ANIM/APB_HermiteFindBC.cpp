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
Restituisce gli slopes della spline cubica di Hermite passante per 4 punti (due arbitrari, uno iniziale ed uno finale)
INPUT: float X1,float Y1, float X2, float Y2, float a, float d
OUTPUT: float *b, float *c
------------------------------------------------------------------------------------------------------------------*/

#include "stdafx.h"


void APB_HermiteFindBC (float X1,float Y1, float X2, float Y2, float a, float d, float *b, float *c)
{
    *b = -(pow(X2, 3) * ((a - d) * pow(X1, 2) + Y1 - a) - pow(X2, 2) * ((a - d) * pow(X1, 3) + Y1 - a) - pow(X1, 2) * (X1 - 1) * (Y2 - a)) / (X2 * (X2 - 1) *
		(X2 - X1) * X1 * (X1 - 1));
    *c = -(pow(X2, 3) * ((a - d) * pow(X1, 2) - 2 * (a - d) * X1 - Y1 + a) - pow(X2, 2) * ((a - d) * pow(X1, 3) - 3 * (a - d) * X1 - 2 * (Y1 - a)) + X2 * (2 *
		(a - d) * pow(X1, 3) - 3 * (a - d) * pow(X1, 2) - Y1 + a) + X1 * (pow(X1, 2) - 2 * X1 + 1) * (Y2 - a)) / (X2 * (X2 - 1) * (X2 - X1) * X1 * (X1 - 1));
}