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
Lettura file CAL
INPUT: ifstream &calfile, bool Export_POS
OUTPUT: vector <Animation_info> &Ani_header, vector < vector <AnimationCurveNode> > &Ani_curvenode
------------------------------------------------------------------------------------------------------------------*/

#include "stdafx.h"
#include "ANIM/CAL_Struct.h"
#include "Classes.h"
#include "MISC/UI_Functions.h"
#include "MATH/math_Functions.h"
#include "ANIM/CAL_Functions.h"


void CAL_Read (ifstream &calfile, vector <Animation_info> &Ani_header, vector < vector <AnimationCurveNode> > &Ani_curvenode, bool Export_POS)
{
    CAL_HEADER cal_header;
    CAL_ANIM_POINTER_LIST cal_anim_pointer_list;
    CAL_ANIM_HEADER cal_anim_header;
    CAL_ANIM_RAW_HEADER cal_anim_raw_header;
    CAL_ANIM_RAW_BONES cal_anim_raw_bones;
	int user_input;
	bool Export_RootMotion, exit_loop = false;

	cout << endl;
	do {
		cout << " Would you like to export root motion [Y/N]? ";
		user_input = getch();
		if (user_input == 89 || user_input == 121)
		{
			cout << "Y\n\n\n";
			Export_RootMotion = true;										// Esporta il root motion per tutte le animazioni
			exit_loop = true;
		}
		if (user_input == 78 || user_input == 110)
		{
			cout << "N\n\n\n";
			Export_RootMotion = false;
			exit_loop = true;
		}
		if (!exit_loop)
			cout << "\r";
	} while (!exit_loop);

    calfile.read(reinterpret_cast<char*>(&cal_header.nAnims), sizeof(cal_header.nAnims));		// Numero di animazioni
    calfile.seekg(4, ios_base::cur);
    calfile.read(reinterpret_cast<char*>(&cal_header.Anim_pointer_list_offset), sizeof(cal_header.Anim_pointer_list_offset));
    calfile.seekg(cal_header.Anim_pointer_list_offset);		// Posiziona l'indice di lettura all'inizio del gruppo offsets degli header delle animazioni

    Ani_header.resize(cal_header.nAnims);					// Ridimensiona il vettore in base al numero di animazioni da accogliere
    Ani_curvenode.resize(cal_header.nAnims);				// Ridimensiona il vettore in base al numero di animazioni da accogliere

    for (unsigned int a = 0; a < cal_header.nAnims; a++)	// LETTURA OFFSETS HEADER ANIMAZIONI
        calfile.read(reinterpret_cast<char*>(&Ani_header[a].Pointer_h), sizeof(cal_anim_pointer_list.Anim_header_offset));

	for (unsigned int a = 0; a < cal_header.nAnims; a++)	// LETTURA HEADER ANIMAZIONI
    {
		AnimationCurveNode Root;								// Classe contenente tutte le informazioni sul root motion dell'animazione
		int reading_offset = 0;
		UI_ProgressBar(a, cal_header.nAnims, 45, " Reading animations...                         ");
        calfile.seekg(Ani_header[a].Pointer_h);
        calfile.read(reinterpret_cast<char*>(&Ani_header[a].name), sizeof(cal_anim_header.Name));							// Nome animazione
        calfile.read(reinterpret_cast<char*>(&Ani_header[a].Pointer_r), sizeof(cal_anim_header.Anim_raw_header_offset));	// Offset dati raw
        calfile.seekg(28, ios_base::cur);
		calfile.read(reinterpret_cast<char*>(&Ani_header[a].Name_hashed), sizeof(cal_anim_header.Name_hashed));				// Hash del nome dell'animazione
        calfile.seekg(4, ios_base::cur);
		calfile.read(reinterpret_cast<char*>(&Ani_header[a].nFrames), sizeof(cal_anim_header.nFrames));						// Numero di frames dell'animazione
        calfile.read(reinterpret_cast<char*>(&Ani_header[a].nBones), sizeof(cal_anim_header.nBones));						// Numero di bones controllate dall'animazione
        Ani_curvenode[a].resize(Ani_header[a].nBones);		// Ridimensiona il vettore in base al numero di bones da accogliere
        calfile.seekg(Ani_header[a].Pointer_r);
        calfile.read(reinterpret_cast<char*>(&cal_anim_raw_header.Bones_offset), sizeof(cal_anim_raw_header.Bones_offset));
		calfile.read(reinterpret_cast<char*>(&cal_anim_raw_header.Transform_type), sizeof(cal_anim_raw_header.Transform_type));
		calfile.read(reinterpret_cast<char*>(&cal_anim_raw_header.Pointer), sizeof(cal_anim_raw_header.Pointer));

		///////////////////    LETTURA KEYFRAMES ROOT MOTION
		if (Export_RootMotion)
		{
			if (cal_anim_raw_header.Transform_type & 1)			// traslazione X
			{
				Root.tX_flag = true;
				calfile.seekg(cal_anim_raw_header.Pointer + reading_offset);
				Root.tX = CAL_Get_TRS_Keyframes_2(calfile, Ani_header[a].nFrames, 0.03125f);
				reading_offset += 4;
			}
			if (cal_anim_raw_header.Transform_type & 2)			// traslazione Y
			{
				Root.tY_flag = true;
				calfile.seekg(cal_anim_raw_header.Pointer + reading_offset);
				Root.tY = CAL_Get_TRS_Keyframes_2(calfile, Ani_header[a].nFrames, 0.03125f);
				reading_offset += 4;
			}
			if (cal_anim_raw_header.Transform_type & 4)			// traslazione Z
			{
				Root.tZ_flag = true;
				calfile.seekg(cal_anim_raw_header.Pointer + reading_offset);
				Root.tZ = CAL_Get_TRS_Keyframes_2(calfile, Ani_header[a].nFrames, 0.03125f);
				reading_offset += 4;
			}
			if (cal_anim_raw_header.Transform_type & 0x20)		// rotazione Z (a differenza delle rotazioni dello scheletro, non è un quaternione ma già un angolo euleriano)
			{
				Root.rZ_flag = true;
				calfile.seekg(cal_anim_raw_header.Pointer + reading_offset);
				Root.rZ = CAL_Get_TRS_Keyframes_2(calfile, Ani_header[a].nFrames, 0.001953125f);
				reading_offset += 4;
			}
		}

        for (unsigned int b = 0; b < Ani_header[a].nBones; b++)
        {
            calfile.seekg(cal_anim_raw_header.Bones_offset + 8 * b);	// Posiziona ad ogni ciclo il punto di lettura al Transform_type della bone b (salta 8 bytes per bone)
            calfile.read(reinterpret_cast<char*>(&cal_anim_raw_bones.Transform_type), sizeof(cal_anim_raw_bones.Transform_type));	// Legge il Transform_type
            calfile.read(reinterpret_cast<char*>(&cal_anim_raw_bones.Pointer), sizeof(cal_anim_raw_bones.Pointer));					// Legge il pointer del primo chunk
            reading_offset = 0;

			///////////////////    LETTURA KEYFRAMES SCHELETRO
            if (cal_anim_raw_bones.Transform_type & 1)			// traslazione X
            {
                Ani_curvenode[a][b].tX_flag = true;
                calfile.seekg(cal_anim_raw_bones.Pointer + reading_offset);
				if ((b == 0 && Export_RootMotion && (Root.tX_flag || Root.rZ_flag)) || (b == 0 && Export_POS))
					Ani_curvenode[a][b].tX = CAL_Get_TRS_Keyframes_2(calfile, Ani_header[a].nFrames, 0.25f);
				else
					Ani_curvenode[a][b].tX = CAL_Get_TRS_Keyframes(calfile, Ani_header[a].nFrames, 0.25f);
                reading_offset += 4;
            }
            if (cal_anim_raw_bones.Transform_type & 2)          // traslazione Y
            {
                Ani_curvenode[a][b].tY_flag = true;
                calfile.seekg(cal_anim_raw_bones.Pointer + reading_offset);
				if ((b == 0 && Export_RootMotion && (Root.tY_flag || Root.rZ_flag)) || (b == 0 && Export_POS))
					Ani_curvenode[a][b].tY = CAL_Get_TRS_Keyframes_2(calfile, Ani_header[a].nFrames, 0.25f);
				else
					Ani_curvenode[a][b].tY = CAL_Get_TRS_Keyframes(calfile, Ani_header[a].nFrames, 0.25f);
                reading_offset += 4;
            }
            if (cal_anim_raw_bones.Transform_type & 4)          // traslazione Z
            {
                Ani_curvenode[a][b].tZ_flag = true;
                calfile.seekg(cal_anim_raw_bones.Pointer + reading_offset);
                if ((b == 0 && Export_RootMotion && Root.tZ_flag) || (b == 0 && Export_POS))
					Ani_curvenode[a][b].tZ = CAL_Get_TRS_Keyframes_2(calfile, Ani_header[a].nFrames, 0.25f);
				else
					Ani_curvenode[a][b].tZ = CAL_Get_TRS_Keyframes(calfile, Ani_header[a].nFrames, 0.25f);
                reading_offset += 4;
            }
            if (cal_anim_raw_bones.Transform_type & 8)          // coordinata X del quaternione delle rotazioni
            {
                Ani_curvenode[a][b].rX_flag = true;
                calfile.seekg(cal_anim_raw_bones.Pointer + reading_offset);
				Ani_curvenode[a][b].rotQuatX = CAL_Get_Rquat_Keyframes_2(calfile, Ani_header[a].nFrames, 0.00006103888f);
                reading_offset += 4;
            }
            if (cal_anim_raw_bones.Transform_type & 0x10)       // coordinata Y del quaternione delle rotazioni
            {
                Ani_curvenode[a][b].rY_flag = true;
                calfile.seekg(cal_anim_raw_bones.Pointer + reading_offset);
                Ani_curvenode[a][b].rotQuatY = CAL_Get_Rquat_Keyframes_2(calfile, Ani_header[a].nFrames, 0.00006103888f);
                reading_offset += 4;
            }
            if (cal_anim_raw_bones.Transform_type & 0x20)       // coordinata Z del quaternione delle rotazioni
            {
                Ani_curvenode[a][b].rZ_flag = true;
                calfile.seekg(cal_anim_raw_bones.Pointer + reading_offset);
                Ani_curvenode[a][b].rotQuatZ = CAL_Get_Rquat_Keyframes_2(calfile, Ani_header[a].nFrames, 0.00006103888f);
                reading_offset += 4;
            }
            if (cal_anim_raw_bones.Transform_type & 0x40)       // scalatura X
            {
                Ani_curvenode[a][b].sX_flag = true;
                calfile.seekg(cal_anim_raw_bones.Pointer + reading_offset);
				Ani_curvenode[a][b].sX = CAL_Get_TRS_Keyframes(calfile, Ani_header[a].nFrames, 0.003921569f);
                reading_offset += 4;
            }
            if (cal_anim_raw_bones.Transform_type & 0x80)       // scalatura Y
            {
                Ani_curvenode[a][b].sY_flag = true;
                calfile.seekg(cal_anim_raw_bones.Pointer + reading_offset);
				Ani_curvenode[a][b].sY = CAL_Get_TRS_Keyframes(calfile, Ani_header[a].nFrames, 0.003921569f);
                reading_offset += 4;
            }
            if (cal_anim_raw_bones.Transform_type & 0x100)      // scalatura Z
            {
                Ani_curvenode[a][b].sZ_flag = true;
                calfile.seekg(cal_anim_raw_bones.Pointer + reading_offset);
				Ani_curvenode[a][b].sZ = CAL_Get_TRS_Keyframes(calfile, Ani_header[a].nFrames, 0.003921569f);
                reading_offset += 4;
            }
            if (cal_anim_raw_bones.Transform_type & 0x200)      // coordinata W del quaternione delle rotazioni
            {
                calfile.seekg(cal_anim_raw_bones.Pointer + reading_offset);
				Ani_curvenode[a][b].rotQuatW = CAL_Get_Rquat_Keyframes_2(calfile, Ani_header[a].nFrames, 0.00006103888f);
            }

			APB_Fill_rotQuaternion(&Ani_curvenode[a][b], Ani_header[a].nFrames);	// Inserisce valori di default nei vettori vuoti del quaternione delle rotazioni

			///////////////////    PREPARAZIONE ROTAZIONI
            if (Ani_curvenode[a][b].rX_flag)										// Serve ad impedire che vengano lette bones prive di rotazioni
                for (unsigned int f = 0; f < Ani_header[a].nFrames; f++)			// Ogni ciclo elabora un frame dell'animazione di rotazione
                {
                    Quaternion RotQuaternion;
                    RotQuaternion.x = Ani_curvenode[a][b].rotQuatX[f];
                    RotQuaternion.y = Ani_curvenode[a][b].rotQuatY[f];
                    RotQuaternion.z = Ani_curvenode[a][b].rotQuatZ[f];
                    RotQuaternion.w = Ani_curvenode[a][b].rotQuatW[f];
                    mathQuatNormalise(&RotQuaternion);								// Il quaternione delle rotazioni viene normalizzato
                    matrix4x4 RotMatrix = mathQuatToMatrix(RotQuaternion);			// Il quaternione viene convertito in matrice
                    EulerRotation RotAngles = mathMatrixToEuler(RotMatrix);			// La matrice viene trasformata in angoli di rotazione euleriani
                    mathRadToDeg(&RotAngles);										// Gli angoli euleriani vengono convertiti da radianti a gradi
                    // Scrittura rotazione X
                    Ani_curvenode[a][b].rX.KeyTime.push_back((unsigned long long)f * FBXframe1 + FBXframe1);	// Tempo
                    Ani_curvenode[a][b].rX.KeyValueFloat.push_back(RotAngles.x);                                // Valore frame
                    Ani_curvenode[a][b].rX.KeyAttrFlags.push_back(24840);                                       // Cubic|TangeantAuto|GenericTimeIndependent|GenericClampProgressive
                    Ani_curvenode[a][b].rX.KeyAttrDataFloat.push_back(0);                                       // RightSlope:0
                    Ani_curvenode[a][b].rX.KeyAttrDataFloat.push_back(0);                                       // NextLeftSlope:0
                    Ani_curvenode[a][b].rX.KeyAttrDataFloat.push_back(218434821);                               // RightWeight:0.333333, NextLeftWeight:0.333333
                    Ani_curvenode[a][b].rX.KeyAttrDataFloat.push_back(0);                                       // RightVelocity:0, NextLeftVelocity:0
                    // Scrittura rotazione Y
                    Ani_curvenode[a][b].rY.KeyTime.push_back((unsigned long long)f * FBXframe1 + FBXframe1);    // Tempo
                    Ani_curvenode[a][b].rY.KeyValueFloat.push_back(RotAngles.y);                                // Valore frame
                    Ani_curvenode[a][b].rY.KeyAttrFlags.push_back(24840);                                       // Cubic|TangeantAuto|GenericTimeIndependent|GenericClampProgressive
                    Ani_curvenode[a][b].rY.KeyAttrDataFloat.push_back(0);                                       // RightSlope:0
                    Ani_curvenode[a][b].rY.KeyAttrDataFloat.push_back(0);                                       // NextLeftSlope:0
                    Ani_curvenode[a][b].rY.KeyAttrDataFloat.push_back(218434821);                               // RightWeight:0.333333, NextLeftWeight:0.333333
                    Ani_curvenode[a][b].rY.KeyAttrDataFloat.push_back(0);                                       // RightVelocity:0, NextLeftVelocity:0
                    // Scrittura rotazione Z
                    Ani_curvenode[a][b].rZ.KeyTime.push_back((unsigned long long)f * FBXframe1 + FBXframe1);    // Tempo
                    Ani_curvenode[a][b].rZ.KeyValueFloat.push_back(RotAngles.z);                                // Valore frame
                    Ani_curvenode[a][b].rZ.KeyAttrFlags.push_back(24840);                                       // Cubic|TangeantAuto|GenericTimeIndependent|GenericClampProgressive
                    Ani_curvenode[a][b].rZ.KeyAttrDataFloat.push_back(0);                                       // RightSlope:0
                    Ani_curvenode[a][b].rZ.KeyAttrDataFloat.push_back(0);                                       // NextLeftSlope:0
                    Ani_curvenode[a][b].rZ.KeyAttrDataFloat.push_back(218434821);                               // RightWeight:0.333333, NextLeftWeight:0.333333
                    Ani_curvenode[a][b].rZ.KeyAttrDataFloat.push_back(0);                                       // RightVelocity:0, NextLeftVelocity:0
                }

			///////////////////		APPLICAZIONE ROOT MOTION A BONE HIP
			if (b == 0 && Export_RootMotion)
			{
				if (Root.rZ_flag)		// Se il root motion include la rotazione Z è necessario ruotare le traslazioni del root motion e della bone HIP dello scheletro
				{
					matrix4x4 UnitMatrix;												// Matrice identità
					UnitMatrix.row1[0] = 1;		UnitMatrix.row1[1] = 0;		UnitMatrix.row1[2] = 0;		UnitMatrix.row1[3] = 0;
					UnitMatrix.row2[0] = 0;		UnitMatrix.row2[1] = 1;		UnitMatrix.row2[2] = 0;		UnitMatrix.row2[3] = 0;
					UnitMatrix.row3[0] = 0;		UnitMatrix.row3[1] = 0;		UnitMatrix.row3[2] = 1;		UnitMatrix.row3[3] = 0;
					UnitMatrix.row4[0] = 0;		UnitMatrix.row4[1] = 0;		UnitMatrix.row4[2] = 0;		UnitMatrix.row4[3] = 1;

					Root.rZ.KeyValueFloat.insert(Root.rZ.KeyValueFloat.begin(), 0);		// Aggiunge 0 come valore di partenza della rotazione
					Root.rZ.KeyValueFloat.pop_back();									// Elimina l'ultimo frame per ristabilire la corretta durata dell'animazione
					for (unsigned int f = 1; f < Root.rZ.KeyValueFloat.size(); f++)		// Somma ad ogni rotazione quella del frame precedente (i singoli valori sono incrementi)
						Root.rZ.KeyValueFloat[f] += Root.rZ.KeyValueFloat[f-1];

					if (Root.tX_flag || Root.tY_flag)									// Corregge le traslazioni del root motion
					{
						if (!Root.tX_flag)												// Crea gli slot, se assenti, per i nuovi valori di traslazione
							Root.tX = APB_Fill_AnimationCurveData(0, Root.rZ.KeyValueFloat.size());
						if (!Root.tY_flag)												// Crea gli slot, se assenti, per i nuovi valori di traslazione
							Root.tY = APB_Fill_AnimationCurveData(0, Root.rZ.KeyValueFloat.size());
						Root.tX_flag = true;
						Root.tY_flag = true;
						for (unsigned int f = 0; f < Root.rZ.KeyValueFloat.size(); f++)
						{
							Translation oldRoot, newRoot;
							oldRoot.xt = Root.tX.KeyValueFloat[f];			oldRoot.yt = Root.tY.KeyValueFloat[f];			oldRoot.zt = 0;
							newRoot = mathRot(oldRoot, mathRotZ(UnitMatrix, Root.rZ.KeyValueFloat[f]));
							Root.tX.KeyValueFloat[f] = newRoot.xt;		Root.tY.KeyValueFloat[f] = newRoot.yt;
						}
					}

					if (Ani_curvenode[a][b].tX_flag || Ani_curvenode[a][b].tY_flag)		// Corregge le traslazioni della bone HIP dello scheletro
					{
						if (!Ani_curvenode[a][b].tX_flag)								// Crea gli slot, se assenti, per i nuovi valori di traslazione
							Ani_curvenode[a][b].tX = APB_Fill_AnimationCurveData(0, Root.rZ.KeyValueFloat.size());
						if (!Ani_curvenode[a][b].tY_flag)								// Crea gli slot, se assenti, per i nuovi valori di traslazione			
							Ani_curvenode[a][b].tY = APB_Fill_AnimationCurveData(0, Root.rZ.KeyValueFloat.size());
						Ani_curvenode[a][b].tX_flag = true;
						Ani_curvenode[a][b].tY_flag = true;
						for (unsigned int f = 0; f < Root.rZ.KeyValueFloat.size(); f++)
						{
							Translation oldHip, newHip;
							oldHip.xt = Ani_curvenode[a][b].tX.KeyValueFloat[f];		oldHip.yt = Ani_curvenode[a][b].tY.KeyValueFloat[f];		oldHip.zt = 0;
							newHip = mathRot(oldHip, mathRotZ(UnitMatrix, Root.rZ.KeyValueFloat[f]));
							Ani_curvenode[a][b].tX.KeyValueFloat[f] = newHip.xt;		Ani_curvenode[a][b].tY.KeyValueFloat[f] = newHip.yt;
						}
					}
				}

				// Questo pezzo aggiunge al valore di ogni keyframe il valore del precedente. Questo perchè le traslazioni sono salvate per incrementi e non per valori assoluti
				if (Root.tX_flag)
				{
					Root.tX.KeyValueFloat.insert(Root.tX.KeyValueFloat.begin(), 0);		// Aggiunge 0 come valore di partenza della traslazione
					Root.tX.KeyValueFloat.pop_back();									// Elimina l'ultimo frame per ristabilire la corretta durata dell'animazione
					for (unsigned int f = 1; f < Root.tX.KeyValueFloat.size(); f++)		// Somma ad ogni traslazione quella del frame precedente (i singoli valori sono incrementi)
						Root.tX.KeyValueFloat[f] += Root.tX.KeyValueFloat[f-1];
				}
				if (Root.tY_flag)
				{
					Root.tY.KeyValueFloat.insert(Root.tY.KeyValueFloat.begin(), 0);		// Aggiunge 0 come valore di partenza della traslazione
					Root.tY.KeyValueFloat.pop_back();									// Elimina l'ultimo frame per ristabilire la corretta durata dell'animazione
					for (unsigned int f = 1; f < Root.tY.KeyValueFloat.size(); f++)		// Somma ad ogni traslazione quella del frame precedente (i singoli valori sono incrementi)
						Root.tY.KeyValueFloat[f] += Root.tY.KeyValueFloat[f-1];
				}
				if (Root.tZ_flag)
				{
					Root.tZ.KeyValueFloat.insert(Root.tZ.KeyValueFloat.begin(), 0);		// Aggiunge 0 come valore di partenza della traslazione
					Root.tZ.KeyValueFloat.pop_back();									// Elimina l'ultimo frame per ristabilire la corretta durata dell'animazione
					for (unsigned int f = 1; f < Root.tZ.KeyValueFloat.size(); f++)		// Somma ad ogni traslazione quella del frame precedente (i singoli valori sono incrementi)
						Root.tZ.KeyValueFloat[f] += Root.tZ.KeyValueFloat[f-1];
				}
				APB_Combine_AnimLayers(&Ani_curvenode[a][b], Root);						// Aggiunge alla bone HIP il Root Motion
			}
        }
    }

	exit_loop = false;
	cout << endl;
	do {
		cout << " Scalings may give unpredictable results in some 3D softwares/game engines. Would you like to disable them [Y/N]? ";
		user_input = getch();
		if (user_input == 89 || user_input == 121)
		{
			cout << "Y\n\n\n";
			APB_Disable_Scaling(Ani_curvenode);										// Disabilitazione scalature
			exit_loop = true;
		}
		if (user_input == 78 || user_input == 110)
		{
			cout << "N\n\n\n";
			exit_loop = true;
		}
		if (!exit_loop)
			cout << "\r";
	} while (!exit_loop);
}