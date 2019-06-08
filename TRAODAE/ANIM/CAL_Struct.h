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


struct CAL_HEADER
{
    uint32_t nAnims;						// Numero di animazioni
    uint32_t Unknown1;                      // Sempre 11000000h
    uint32_t Anim_pointer_list_offset;      // Sempre 18000000h
    uint32_t Unknown2;
    uint32_t Unknown3;
    uint32_t Unknown4;
};


struct CAL_ANIM_POINTER_LIST
{
    uint32_t Anim_header_offset;            // Puntatore all'inizio dell'header dell'animazione
};


struct CAL_ANIM_HEADER
{
    char Name[64];                          // Nome dell'animazione
    uint32_t Anim_raw_header_offset;        // Puntatore all'inizio dei dati raw dell'animazione
    uint32_t Unknown1;			// dovrebbe essere un puntatore
    uint32_t Unknown2;			// dovrebbe essere un puntatore, è QUASI sempre uguale a 002CC22Ch
    uint32_t Unknown3;			// dovrebbe essere un puntatore
    uint32_t Unknown4;			// dovrebbe essere un puntatore
    uint32_t Unknown5;			// dovrebbe essere un puntatore
    uint32_t Unknown6;			// dovrebbe essere un puntatore
    uint32_t Unknown7;
    uint32_t Hashed_name;                   // Hash del nome dell'animazione
    uint32_t Unknown8;
    uint32_t nFrames;                       // Numero di frames dell'animazione
    uint32_t nBones;                        // Numero di pointers presenti all'inizio del gruppo data RAW (sarebbe il numero di Bones)
    uint32_t Unknown10;
    uint32_t Unknown11;
    uint32_t Unknown12;
    uint32_t Unknown13;
    uint32_t Unknown14;
};


struct CAL_ANIM_RAW_HEADER
{
    uint32_t Bones_offset;                  // Offset di CAL_ANIM_RAW_BONES
    uint32_t Transform_type;				// Il tipo di trasformazioni aggiuntive della root bone HIP (root motion)
    uint32_t Pointer;						// Punta ad una lista di pointers di frammenti dell'animazione della root bone HIP (root motion)
};


struct CAL_ANIM_RAW_BONES
{
    uint32_t Transform_type;                // Il tipo di trasformazioni che quella bone avrà
    uint32_t Pointer;                       // Punta alla lista di pointers dei frammenti dell'animazione (il secondo gruppo di pointers)
};


struct CAL_ANIM_RAW_TRANSFORMS
{
    uint32_t Pointer;                       // Puntatore ai dati raw grezzi
};


struct CAL_ANIM_CHUNK_HEADER
{
    uint16_t Keyframe;						// Numero dell'ultimo keyframe nella sequenza
    uint8_t Frame_mode;						// 1 frame-1 valore (2h, Ah) / n frames-1 valore (4h, Ch) / n frames-3 o 4 valori (1h, 9h, curva di Bezier)
    uint8_t Chunk_size;						// Dimensione CAL_ANIM_CHUNK_HEADER + CAL_ANIM_CHUNK_DATA
};


struct CAL_ANIM_CHUNK_DATA
{
    int16_t Data;							// Valore dell'animazione
};