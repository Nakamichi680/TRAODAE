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
Restituisce il nome (se presente nell'elenco) corrispondente all'hash in ingresso; se non trova nulla restituisce l'hash
INPUT: int h_name, bool *hashed
OUTPUT: string
------------------------------------------------------------------------------------------------------------------*/

#include "stdafx.h"
#include "MISC/hash_Functions.h"


string GetMeshName (int h_name, bool *hashed)
{
    int num_IDs = 179;
    string ID[179];

    // Tutti gli ID legati ai personaggi trovati dentro il file TRAOD_P4.EXE o ricavati con Hash_Reversal
    ID[0] = "HIP";                                  ID[1] = "THORAX";                               ID[2] = "NECK";                                 ID[3] = "THIGH_L";
    ID[4] = "CALF_L";                               ID[5] = "THIGH_R";                              ID[6] = "CALF_R";                               ID[7] = "BICEP";
    ID[8] = "FORARM";                               ID[9] = "ARM1";                                 ID[10] = "ARM8";                                ID[11] = "FOOT_L";
    ID[12] = "FOOT_R";                              ID[13] = "STABBY";                              ID[14] = "CLAWMOUTH";                           ID[15] = "BOAZFLY_CLOTH_H";
    ID[16] = "BOAZFLY_CLOTH_S";                     ID[17] = "BICEP_L";                             ID[18] = "FORARM_L";                            ID[19] = "BICEP_R";
    ID[20] = "FORARM_R";                            ID[21] = "ANKLE_L";                             ID[22] = "ANKLE_R";                             ID[23] = "SPINE_1";
    ID[24] = "HEAD";                                ID[25] = "BELLY_DYNAMIC";                       ID[26] = "KURTIS_CLOTH_H";                      ID[27] = "KURTIS_CLOTH_S";
    ID[28] = "LAB2_CLOTH_H";                        ID[29] = "LAB2_CLOTH_S";                        ID[30] = "COAT_CLOTH_H";                        ID[31] = "COAT_CLOTH_S";
    ID[32] = "SPINE_2";                             ID[33] = "KAREL_JACKET_CLOTH_H";                ID[34] = "KAREL_JACKET_CLOTH_S";                ID[35] = "TENDRILD_CLOTH_H";
    ID[36] = "TENDRILD_CLOTH_S";                    ID[37] = "SPINE";                               ID[38] = "TENDRILA_CLOTH_H";                    ID[39] = "TENDRILA_CLOTH_S";
    ID[40] = "SPINE1";                              ID[41] = "TENDRILB_CLOTH_H";                    ID[42] = "TENDRILB_CLOTH_S";                    ID[43] = "SPINE2";
    ID[44] = "TENDRILC_CLOTH_H";                    ID[45] = "TENDRILC_CLOTH_S";                    ID[46] = "SPINE3";                              ID[47] = "SPINE6";
    ID[48] = "SPINE8";                              ID[49] = "SPINE9";                              ID[50] = "FOREARM_L";                           ID[51] = "FOREARM_R";
    ID[52] = "BODY_CLOTH_H";                        ID[53] = "ROBES_CLOTH_S";                       ID[54] = "TORSO_CLOTH_H";                       ID[55] = "TORSO_CLOTH_S";
    ID[56] = "HOOD";                                ID[57] = "HOOD_CLOTH_H";                        ID[58] = "HOOD_CLOTH_S";                        ID[59] = "SHLDER_L";
    ID[60] = "SHLDER_R";                            ID[61] = "STRAP1_DYNAMIC";                      ID[62] = "STRAP2_DYNAMIC";                      ID[63] = "STRAP3_DYNAMIC";
    ID[64] = "STRAP4_DYNAMIC";                      ID[65] = "STRAP5_DYNAMIC";                      ID[66] = "STRAP6_DYNAMIC";                      ID[67] = "STRAP7_DYNAMIC";
    ID[68] = "STRAP8_DYNAMIC";                      ID[69] = "STRAP9_DYNAMIC";                      ID[70] = "STRAP10_DYNAMIC";                     ID[71] = "STRAP11_DYNAMIC";
    ID[72] = "STRAP12_DYNAMIC";                     ID[73] = "STRAP13_DYNAMIC";                     ID[74] = "STRAP14_DYNAMIC";                     ID[75] = "STRAP15_DYNAMIC";
    ID[76] = "STRAP16_DYNAMIC";                     ID[77] = "SKIRT_CLOTH_H";                       ID[78] = "SKIRT_CLOTH_S";                       ID[79] = "LARA_DENIM_CLOTH_H";
    ID[80] = "LARA_DENIM_CLOTH_S";                  ID[81] = "LARA_FLAK_CLOTH_H";                   ID[82] = "LARA_FLAK_CLOTH_S";                   ID[83] = "LARA_FRINGE_CLOTH_H";
    ID[84] = "LARA_FRINGE_CLOTH_S";                 ID[85] = "PONY1_DYNAMIC";                       ID[86] = "PONY3_DYNAMIC";                       ID[87] = "PONY5_DYNAMIC";
    ID[88] = "PONY7_DYNAMIC";                       ID[89] = "PONY9_DYNAMIC";                       ID[90] = "PONY10_DYNAMIC";                      ID[91] = "JUG_L_DYNAMIC";
    ID[92] = "JUG_R_DYNAMIC";                       ID[93] = "LARA_SILENCER_SCORPION_X_LEFTHOLSTER";ID[94] = "LARA_SIGHT_K2_IMPACTOR_HOLSTER";      ID[95] = "LARA_RESPIRATOR";
    ID[96] = "LARA_SIGHT_DART_SS_HOLSTER";          ID[97] = "LARA_SILENCER_MAGVEGA_HOLSTER";       ID[98] = "LARA_SILENCER_MV9_HOLSTER";           ID[99] = "LARA_SIGHT_MV9_HOLSTER";
    ID[100] = "LARA_DESERT_RANGER_HOLSTER";         ID[101] = "LARA_SIGHT_DESERT_RANGER_HOLSTER";   ID[102] = "LARA_DART_SS_HOLSTER";               ID[103] = "LARA_RIGG09_HOLSTER";
    ID[104] = "LARA_SCORPION_X_HOLSTER";            ID[105] = "LARA_SILENCER_SCORPION_X_HOLSTER";   ID[106] = "GUNHOLSTER_LEFT";                    ID[107] = "SHOTGUN_BACKPACK";
    ID[108] = "LARA_VIPER_SMG_HOLSTER";             ID[109] = "LARA_SIGHT_VIPER_SMG_HOLSTER";       ID[110] = "LARA_MAGVEGA_HOLSTER";               ID[111] = "LARA_MV9_HOLSTER";
    ID[112] = "LARA_SIGHT_MAGVEGA_HOLSTER";         ID[113] = "LARA_GLASSES";                       ID[114] = "LARA_REBREATHER";                    ID[115] = "LARA_DIVINGMASK";
    ID[116] = "LARA_K2_IMPACTOR_HOLSTER";           ID[117] = "GUNHAND_LEFT";                       ID[118] = "LARA_CROWBAR";                       ID[119] = "SHOTGUN";
    ID[120] = "SHOTGUN_PUMP";                       ID[121] = "GUNHAND_RIGHT";                      ID[122] = "LARA_SHARD";                         ID[123] = "LARA_K2_IMPACTOR";
    ID[124] = "LARA_SIGHT_K2_IMPACTOR";             ID[125] = "LARA_RIGG09";                        ID[126] = "LARA_MV10";                          ID[127] = "LARA_SILENCER_MV9";
    ID[128] = "LARA_SIGHT_MV9";                     ID[129] = "LARA_DESERT_RANGER";                 ID[130] = "LARA_SIGHT_DESERT_RANGER";           ID[131] = "LARA_DART_SS";
    ID[132] = "LARA_SIGHT_DART_SS";                 ID[133] = "LARA_SCORPION_X";                    ID[134] = "LARA_SILENCER_SCORPION_X";           ID[135] = "LARA_VIPER_SMG";
    ID[136] = "LARA_SIGHT_VIPER_SMG";               ID[137] = "LARA_MAGVEGA";                       ID[138] = "LARA_SILENCER_MAGVEGA";              ID[139] = "LARA_SIGHT_MAGVEGA";
    ID[140] = "LARA_HAMMER";                        ID[141] = "HARPOON_GUN";                        ID[142] = "HARPOON_GUN_BACKPACK";               ID[143] = "LARA_SCORPION_X_LEFT";
    ID[144] = "LARA_SILENCER_SCORPION_X_LEFT";      ID[145] = "LARA_SCORPION_X_LEFTHOLSTER";        ID[146] = "HIP_CHATKA";                         ID[147] = "GUNHOLSTER_RIGHT";
    ID[148] = "PISTOL_HAND";                        ID[149] = "GLAVE_SPIKE";                        ID[150] = "GLAVE";                              ID[151] = "SHARD";
    ID[152] = "LASER";                              ID[153] = "SIGHTS";                             ID[154] = "SILENCER";                           ID[155] = "LARA_FACE";
    ID[156] = "LARA_EYE_LEFT";                      ID[157] = "LARA_EYE_RIGHT";                     ID[158] = "KURTIS_FACE";                        ID[159] = "BAG";
    ID[160] = "PISTOLGRIP";                         ID[161] = "LEYE";                               ID[162] = "REYE";                               ID[163] = "SKULL";
    ID[164] = "R_EYE";                              ID[165] = "R_EYE1";                             ID[166] = "PCUBE5";                             ID[167] = "PCUBE2";
    ID[168] = "PCUBE6";                             ID[169] = "PCUBE3";                             ID[170] = "PCUBE1";                             ID[171] = "CANISTERA";
    ID[172] = "CANISTERB";                          ID[173] = "PCUBE10";                            ID[174] = "ECK_GLASSES";                        ID[175] = "ECK_FACE";
    ID[176] = "ECK_SHARD1";                         ID[177] = "ECK_SHARD2";                         ID[178] = "KAREL_FACE";
	
    for (int i = 0; i < num_IDs; i++)
        if (GetHashValue(ID[i].c_str()) == h_name)
        {
            *hashed = false;					// Questo bool indica che la stringa non è più un hash ma è stata decodificata
            return ID[i];
        }

    stringstream original_hash;					// Se non trova alcuna corrispondenza restituisce l'hash originale
    original_hash << std::hex << h_name;
    *hashed = true;								// Questo bool indica che la stringa è ancora un hash
    return original_hash.str();
}