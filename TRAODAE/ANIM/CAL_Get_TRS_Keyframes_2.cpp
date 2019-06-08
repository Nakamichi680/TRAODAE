/* Tomb Raider - The Angel of Darkness Animation Exporter
Copyright (c) 2017-2019 Nakamichi680

This file is part of "Tomb Raider - The Angel of Darkness Animation Exporter".

"Tomb Raider - The Angel of Darkness Animation Exporter" is free software: you can redistribute it and/or modify it under the terms of the
GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.

"Tomb Raider - The Angel of Darkness Animation Exporter" is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without
even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with "Tomb Raider - The Angel of Darkness Animation Exporter".
If not, see <http://www.gnu.org/licenses/>.

Copyright (c) Square Enix Ltd. Lara Croft and Tomb Raider are trademarks or registered trademarks of Square Enix Ltd.
Copyright (c) Autodesk, Inc. and/or its licensors. FBX is a registered trademarks or trademarks of Autodesk, Inc. and/or its subsidiaries
and/or affiliates in the USA and other countries.*/


/*------------------------------------------------------------------------------------------------------------------
Lettura traslazioni, rotazioni e scalature 2 (salva ogni frame, perdendo i valori statici e le curve di Bezier)
INPUT: ifstream &calfile, unsigned int nFrames, float correction_factor
OUTPUT: AnimationCurveData
------------------------------------------------------------------------------------------------------------------*/

#include "stdafx.h"
#include "ANIM/CAL_Struct.h"
#include "Classes.h"
#include "ANIM/CAL_Functions.h"


AnimationCurveData CAL_Get_TRS_Keyframes_2 (ifstream &calfile,					// File delle animazioni da leggere
										    unsigned int nFrames,				// Durata in frames dell'animazione corrente
										    float correction_factor)
{
	CAL_ANIM_RAW_TRANSFORMS cal_anim_raw_transforms;
	CAL_ANIM_CHUNK_DATA cal_anim_chunk_data;
	AnimationCurveData outdata;
	unsigned short Currentframe = 0;                    // Contatore del frame in via di estrazione
	unsigned short Lastchunkframe = 0;                  // Memorizza il valore dell'ultimo frame di ogni chuck (i primi due bytes dell'header del chunk)
	signed short Lastvalue = 0;                         // Salva l'ultimo signed short estratto, serve per le curve di Bezier con soli 3 valori

	calfile.read(reinterpret_cast<char*>(&cal_anim_raw_transforms.Pointer), sizeof(cal_anim_raw_transforms.Pointer));	// Legge la posizione del primo chunk
	calfile.seekg(cal_anim_raw_transforms.Pointer);																		// Posiziona l'inizio della lettura al primo chunk

    while (Lastchunkframe < (nFrames-1))
    {
        int Frame_mode = 0;
        int Chunk_size = 0;

        //////////////  LETTURA HEADER CHUNK
        calfile.read(reinterpret_cast<char*>(&Lastchunkframe), 2);		// Numero dell'ultimo frame del chunk
        calfile.read(reinterpret_cast<char*>(&Frame_mode), 1);			// 2/10 = 1 solo valore per tutti i frames, 4/12 = n valori per n frames, 1/9 = curva di Bezier
        calfile.read(reinterpret_cast<char*>(&Chunk_size), 1);			// Dimensioni complessive del chunk (4 bytes di header + 2 bytes per ogni dato raw)

        //////////////  LETTURA DATI RAW ANIMAZIONE
        if (Frame_mode == 4 || Frame_mode == 12)        /////////////////////   TANTI KEYFRAMES QUANTI SONO I FRAMES DELL'ANIMAZIONE
        {
            while (Currentframe <= Lastchunkframe)
            {
                calfile.read(reinterpret_cast<char*>(&cal_anim_chunk_data.Data), sizeof(cal_anim_chunk_data.Data));		// Legge il valore del keyframe
                Lastvalue = cal_anim_chunk_data.Data;		// Memorizza l'ultimo valore. Serve per la curva di Bezier con 3 valori

                unsigned short IncrementIfLastChunk = Lastchunkframe;
                if (Currentframe == Lastchunkframe && Lastchunkframe == (nFrames-1))
                    IncrementIfLastChunk++;		// Se è l'ultimo frame dell'ultimo chunk, allora IncrementIfLastChunk viene aumentato di 1 così viene scritto anche l'ultimo frame

                if (Currentframe < IncrementIfLastChunk)	// Scrive tutti i valori tranne quello dell'ultimo frame (scritto dal chunk successivo), a meno che non sia l'ultimo chunk
				{
					outdata.KeyTime.push_back((unsigned long long)Currentframe * FBXframe1 + FBXframe1);		// Tempo
                    outdata.KeyValueFloat.push_back((float)cal_anim_chunk_data.Data * correction_factor);		// Valore frame
					outdata.KeyAttrFlags.push_back(24840);														// Cubic|TangeantAuto|GenericTimeIndependent|GenericClampProgressive
                    outdata.KeyAttrDataFloat.push_back(0);														// RightSlope:0
                    outdata.KeyAttrDataFloat.push_back(0);														// NextLeftSlope:0
                    outdata.KeyAttrDataFloat.push_back(218434821);												// RightWeight:0.333333, NextLeftWeight:0.333333
                    outdata.KeyAttrDataFloat.push_back(0);														// RightVelocity:0, NextLeftVelocity:0
				}
				Currentframe++;
            }
            // Siccome il controllo nel while è "<=", l'ultimo Currentframe++ fa andare il valore un frame in avanti di troppo. Currentframe-- lo riporta al valore corretto
            Currentframe--;
        }

        if (Frame_mode == 2 || Frame_mode == 10)        /////////////////////   UN SINGOLO KEYFRAME CHE RIMANE COSTANTE PER n FRAMES
        {
            calfile.read(reinterpret_cast<char*>(&cal_anim_chunk_data.Data), sizeof(cal_anim_chunk_data.Data));			// Legge il valore del keyframe
            Lastvalue = cal_anim_chunk_data.Data;			// Memorizza l'ultimo valore. Serve per la curva di Bezier con 3 valori
            unsigned short IncrementIfLastChunk = Lastchunkframe;

            while (Currentframe < IncrementIfLastChunk)
            {
				outdata.KeyTime.push_back((unsigned long long)Currentframe * FBXframe1 + FBXframe1);			// Tempo
                outdata.KeyValueFloat.push_back((float)cal_anim_chunk_data.Data * correction_factor);			// Valore frame
				outdata.KeyAttrFlags.push_back(24840);															// Cubic|TangeantAuto|GenericTimeIndependent|GenericClampProgressive
                outdata.KeyAttrDataFloat.push_back(0);															// RightSlope:0
                outdata.KeyAttrDataFloat.push_back(0);															// NextLeftSlope:0
                outdata.KeyAttrDataFloat.push_back(218434821);													// RightWeight:0.333333, NextLeftWeight:0.333333
                outdata.KeyAttrDataFloat.push_back(0);															// RightVelocity:0, NextLeftVelocity:0
				Currentframe++;
                if (Currentframe == Lastchunkframe && Lastchunkframe == (nFrames-1))
                    IncrementIfLastChunk++;		// Se è l'ultimo frame dell'ultimo chunk, allora IncrementIfLastChunk viene aumentato di 1 così viene scritto anche l'ultimo frame
            }
        }

        if (Frame_mode == 1 || Frame_mode == 9)         /////////////////////   CURVA DI BEZIER
        {
            float a, b, c, d;
            if (Chunk_size == 10)	// 3 VALORI
            {
                a = Lastvalue * correction_factor;																		// Legge la "a" dall'ultimo valore del chunk precedente
                calfile.read(reinterpret_cast<char*>(&cal_anim_chunk_data.Data), sizeof(cal_anim_chunk_data.Data));		// Legge la "b"
                b = (float)cal_anim_chunk_data.Data * correction_factor;
                calfile.read(reinterpret_cast<char*>(&cal_anim_chunk_data.Data), sizeof(cal_anim_chunk_data.Data));		// Legge la "c"
                c = (float)cal_anim_chunk_data.Data * correction_factor;
                calfile.read(reinterpret_cast<char*>(&cal_anim_chunk_data.Data), sizeof(cal_anim_chunk_data.Data));		// Legge la "d"
                d = (float)cal_anim_chunk_data.Data * correction_factor;
                Lastvalue = cal_anim_chunk_data.Data;       // Memorizza l'ultimo valore. Serve per la curva di Bezier con 3 valori
            }
            if (Chunk_size == 12)   // 4 VALORI
            {
                calfile.read(reinterpret_cast<char*>(&cal_anim_chunk_data.Data), sizeof(cal_anim_chunk_data.Data));		// Legge la "a"
                a = (float)cal_anim_chunk_data.Data * correction_factor;
                calfile.read(reinterpret_cast<char*>(&cal_anim_chunk_data.Data), sizeof(cal_anim_chunk_data.Data));		// Legge la "b"
                b = (float)cal_anim_chunk_data.Data * correction_factor;
                calfile.read(reinterpret_cast<char*>(&cal_anim_chunk_data.Data), sizeof(cal_anim_chunk_data.Data));		// Legge la "c"
                c = (float)cal_anim_chunk_data.Data * correction_factor;
                calfile.read(reinterpret_cast<char*>(&cal_anim_chunk_data.Data), sizeof(cal_anim_chunk_data.Data));		// Legge la "d"
                d = (float)cal_anim_chunk_data.Data * correction_factor;
                Lastvalue = cal_anim_chunk_data.Data;		// Memorizza l'ultimo valore. Serve per la curva di Bezier con 3 valori
            }
            unsigned short IncrementIfLastChunk = Lastchunkframe;
            unsigned short Begin = Currentframe;					// Frame iniziale della curva di Bezier
            unsigned short Lenght = Lastchunkframe - Begin;         // Durata in frames della curva di Bezier (frame finale - frame iniziale)

			while (Currentframe < IncrementIfLastChunk)
            {
                float x, y;
                x = ((float)Currentframe - (float)Begin) / (float)Lenght;		// Calcolo del tempo (0-1)
                y = APB_BezierIDX(x, a, b, c, d);								// Applicazione equazione curva di Bezier e calcolo del valore al tempo x
                outdata.KeyTime.push_back((unsigned long long)Currentframe * FBXframe1 + FBXframe1);			// Tempo
                outdata.KeyValueFloat.push_back(y);																// Valore frame
				outdata.KeyAttrFlags.push_back(24840);															// Cubic|TangeantAuto|GenericTimeIndependent|GenericClampProgressive
                outdata.KeyAttrDataFloat.push_back(0);															// RightSlope:0
                outdata.KeyAttrDataFloat.push_back(0);															// NextLeftSlope:0
                outdata.KeyAttrDataFloat.push_back(218434821);													// RightWeight:0.333333, NextLeftWeight:0.333333
                outdata.KeyAttrDataFloat.push_back(0);															// RightVelocity:0, NextLeftVelocity:0
				Currentframe++;
				if (Currentframe == Lastchunkframe && Lastchunkframe == (nFrames-1))
					IncrementIfLastChunk++;		// Se è l'ultimo frame dell'ultimo chunk, allora IncrementIfLastChunk viene aumentato di 1 così viene scritto anche l'ultimo frame
            }
        }
    }
	return outdata;
}