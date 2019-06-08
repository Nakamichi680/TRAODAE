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
Lettura traslazioni, rotazioni e scalature
INPUT: ifstream &calfile, unsigned int nFrames, float correction_factor
OUTPUT: AnimationCurveData
------------------------------------------------------------------------------------------------------------------*/

#include "stdafx.h"
#include "ANIM/CAL_Struct.h"
#include "Classes.h"
#include "ANIM/CAL_Functions.h"


AnimationCurveData CAL_Get_TRS_Keyframes (ifstream &calfile,					// File delle animazioni da leggere
										  unsigned int nFrames,					// Durata in frames dell'animazione corrente
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
        calfile.read(reinterpret_cast<char*>(&Lastchunkframe), 2);     // Numero dell'ultimo frame del chunk
        calfile.read(reinterpret_cast<char*>(&Frame_mode), 1);         // 2/10 = 1 solo valore per tutti i frames, 4/12 = n valori per n frames, 1/9 = curva di Bezier
        calfile.read(reinterpret_cast<char*>(&Chunk_size), 1);         // Dimensioni complessive del chunk (4 bytes di header + 2 bytes per ogni dato raw)

        //////////////  LETTURA DATI RAW ANIMAZIONE
        if (Frame_mode == 4 || Frame_mode == 12)        /////////////////////   TANTI KEYFRAMES QUANTI SONO I FRAMES DELL'ANIMAZIONE
        {
            while (Currentframe <= Lastchunkframe)
            {
                calfile.read(reinterpret_cast<char*>(&cal_anim_chunk_data.Data), sizeof(cal_anim_chunk_data.Data));		// Legge il valore del keyframe
                Lastvalue = cal_anim_chunk_data.Data;		// Memorizza l'ultimo valore. Serve per la curva di Bezier con 3 valori

                unsigned short IncrementIfLastChunk = Lastchunkframe;
                if (Currentframe == Lastchunkframe && Lastchunkframe == (nFrames-1))
                    IncrementIfLastChunk++;     // Se è l'ultimo frame dell'ultimo chunk, allora IncrementIfLastChunk viene aumentato di 1 così viene scritto anche l'ultimo frame

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
            outdata.KeyTime.push_back((unsigned long long)Currentframe * FBXframe1 + FBXframe1);				// Tempo
            outdata.KeyValueFloat.push_back((float)cal_anim_chunk_data.Data * correction_factor);				// Valore frame
            outdata.KeyAttrFlags.push_back(2);																	// Constant|ConstantStandard
            outdata.KeyAttrDataFloat.push_back(0);																// RightSlope:0
            outdata.KeyAttrDataFloat.push_back(0);																// NextLeftSlope:0
            outdata.KeyAttrDataFloat.push_back(218434821);														// RightWeight:0.333333, NextLeftWeight:0.333333
            outdata.KeyAttrDataFloat.push_back(0);																// RightVelocity:0, NextLeftVelocity:0
            Currentframe = Lastchunkframe;
        }

        if (Frame_mode == 1 || Frame_mode == 9)         /////////////////////   CURVA DI BEZIER
        {
            float a, b, c, d, Hermite_b, Hermite_c;
            if (Chunk_size == 10)   // 3 VALORI
            {
                a = Lastvalue * correction_factor;																		// Legge la "a" dall'ultimo valore del chunk precedente
                calfile.read(reinterpret_cast<char*>(&cal_anim_chunk_data.Data), sizeof(cal_anim_chunk_data.Data));		// Legge la "b"
                b = (float)cal_anim_chunk_data.Data * correction_factor;
                calfile.read(reinterpret_cast<char*>(&cal_anim_chunk_data.Data), sizeof(cal_anim_chunk_data.Data));		// Legge la "c"
                c = (float)cal_anim_chunk_data.Data * correction_factor;
                calfile.read(reinterpret_cast<char*>(&cal_anim_chunk_data.Data), sizeof(cal_anim_chunk_data.Data));		// Legge la "d"
                d = (float)cal_anim_chunk_data.Data * correction_factor;
                Lastvalue = cal_anim_chunk_data.Data;		// Memorizza l'ultimo valore. Serve per la curva di Bezier con 3 valori
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
            float X1 = 0.3f;         float X2 = 0.7f;		// Due valori di x arbitrari necessari per trovare due punti della curva di Bezier
            float Y1 = APB_BezierIDX(X1, a, b, c, d);
            float Y2 = APB_BezierIDX(X2, a, b, c, d);
            APB_HermiteFindBC(X1, Y1, X2, Y2, a, d, &Hermite_b, &Hermite_c);	// INPUT: 2 punti + valori iniziale/finale, OUTPUT: slopes della spline cubica di Hermite
            Hermite_b *= 2;     // CORREZIONE PER FBX
            Hermite_c *= 2;     // CORREZIONE PER FBX
            int FBX_b, FBX_c;
            memcpy(&FBX_b, &Hermite_b, 4);		// Legge il float come Hex e ne interpreta i 4 bytes come se fossero quelli di un intero (non converte da float ad int!!)
            memcpy(&FBX_c, &Hermite_c, 4);		// Legge il float come Hex e ne interpreta i 4 bytes come se fossero quelli di un intero (non converte da float ad int!!)
			outdata.KeyTime.push_back((unsigned long long)Currentframe * FBXframe1 + FBXframe1);				// Tempo
            outdata.KeyValueFloat.push_back(a);																	// Valore frame
            outdata.KeyAttrFlags.push_back(3080);																// Cubic|TangeantUser|GenericBreak
            outdata.KeyAttrDataFloat.push_back(FBX_b);															// RightSlope: Custom
            outdata.KeyAttrDataFloat.push_back(FBX_c);															// NextLeftSlope: Custom
            outdata.KeyAttrDataFloat.push_back(218434821);														// RightWeight:0.333333, NextLeftWeight:0.333333
            outdata.KeyAttrDataFloat.push_back(0);																// RightVelocity:0, NextLeftVelocity:0
			Currentframe = Lastchunkframe;

            if (Lastchunkframe == (nFrames-1))		// Se è l'ultimo chunk, allora scrive anche l'ultimo valore (d) della curva
			{
				outdata.KeyTime.push_back((unsigned long long)Currentframe * FBXframe1 + FBXframe1);			// Tempo
                outdata.KeyValueFloat.push_back(d);																// Valore frame
                outdata.KeyAttrFlags.push_back(1028);															// Linear
                outdata.KeyAttrDataFloat.push_back(0);															// RightSlope:0
                outdata.KeyAttrDataFloat.push_back(0);															// NextLeftSlope:0
                outdata.KeyAttrDataFloat.push_back(218434821);													// RightWeight:0.333333, NextLeftWeight:0.333333
                outdata.KeyAttrDataFloat.push_back(0);															// RightVelocity:0, NextLeftVelocity:0
			}
        }
    }
	return outdata;
}