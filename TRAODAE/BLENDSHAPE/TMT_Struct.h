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


struct TMT_HEADER
{
	uint32_t TMT_MAGIC;						// Sempre "MPHB"
	uint8_t TMT_DATA_lenght;				// Dimensione in bytes del blocco TMT_DATA di ogni blendshape. Sempre 20h (32 bytes)
	uint16_t nVertices_null;				// Numero dei vertici dei blendshapes. NON UTILIZZARE QUESTO
	uint8_t Unknown1;
	uint32_t Hash1;							// Probabilmente è un hash utilizzato durante la lettura del file
	uint32_t Linked_mesh_hash;				// L'hash della mesh a cui il blendshape fa riferimento (ad esempio LARA_FACE)
	uint32_t nBlendshapes;					// Numero di blendshapes (sempre 7), esclusa la mesh di riferimento (in totale sono 8)
	uint32_t nVertices;						// Numero dei vertici dei blendshapes
	uint32_t Unknown2;						// Sempre 18000000h
	uint32_t Unknown3;						// Sempre 00000000h
};


struct TMT_DATA
{
	float X;								// Valore reale se è la mesh di riferimento, differenza rispetto alla mesh di riferimento se è un blendshape
	float Y;								// Valore reale se è la mesh di riferimento, differenza rispetto alla mesh di riferimento se è un blendshape
	float Z;								// Valore reale se è la mesh di riferimento, differenza rispetto alla mesh di riferimento se è un blendshape
	float Xn;								// Valore reale se è la mesh di riferimento, differenza rispetto alla mesh di riferimento se è un blendshape
	float Yn;								// Valore reale se è la mesh di riferimento, differenza rispetto alla mesh di riferimento se è un blendshape
	float Zn;								// Valore reale se è la mesh di riferimento, differenza rispetto alla mesh di riferimento se è un blendshape
	float U;								// Sempre valore reale
	float V;								// Sempre valore reale
};