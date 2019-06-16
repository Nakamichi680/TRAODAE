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


#pragma once


string nodeID (unsigned int node_type, unsigned int value1, unsigned int value2, unsigned int value3);


class IO_CLASS {
public:
	TCHAR Console_OldTitle[MAX_PATH];
	LPCWSTR Console_NewTitle = L"Tomb Raider - The Angel of Darkness Animation Exporter  (by Nakamichi680)";
	LPWSTR folder_exe_lpwstr = new TCHAR[MAX];			// Cartella in cui si trova il programma
	LPWSTR folder_chr_lpwstr = new TCHAR[MAX];			// Cartella in cui si trovano i file CHR/CAL/TMT/POS
	LPWSTR folder_fbx_lpwstr = new TCHAR[MAX];			// Cartella in cui verranno creati i file FBX e le textures
	LPWSTR folder_ani_lpwstr () {
		LPWSTR temp_lpwstr = new TCHAR[MAX];
		string temp = fbx_folder;
		temp.append(chr_name);
		temp.append("_ANIMATIONS");
		mbstowcs(temp_lpwstr, temp.c_str(), MAX);
		return temp_lpwstr;
	};
	string filename_FBX_CAL (char animation_name[64]) {
		string temp = animation_name;
		temp.append(".FBX");
		return temp;
	};
	string filename_FBX_CHR () {
		string temp = chr_name;
		temp.append(".FBX");
		return temp;
	};
	string filename_FBX_TMT () {
		string temp = chr_name;
		temp.append("_BLENDSHAPES.FBX");
		return temp;
	};
	string fbx_folder;
	string chr_name;
	string CHR;											// Stringa contenente il nome del file CHR con estensione
	string CAL;											// Stringa contenente il nome del file CAL con estensione
	string TMT;											// Stringa contenente il nome del file TMT con estensione
	string POS;											// Stringa contenente il nome del file POS con estensione
	bool CHR_exists = false;
	bool CAL_exists = false;
	bool TMT_exists = false;
	bool POS_exists = false;
	bool Export_CHR = false;
	bool Export_CAL = false;
	bool Export_TMT = false;
	bool Export_POS = false;
};


class Quaternion {
public:		float x;	float y;	float z;	float w; };


class EulerRotation{
public:		float x;	float y;	float z; };


class Translation{
public:		float xt;	float yt;	float zt; };


class matrix4x4 {
public:		float row1[4];		float row2[4];		float row3[4];		float row4[4]; };


class TextureHeader {
public:
	unsigned int Number;								// Numero della texture
    int DXT;											// 0 = ARGB, 1 = DXT1, 3 = DXT3, 5 = DXT5
    int ColourBumpShadow;								// 1 = shadow map, 2 = colour map, 4 = bump map, 5 = fur
};


class Material {
public:
	unsigned int Number;								// Numero del materiale
    short Type;											// Tipologia materiale (None, diffuse, bump, specular, ecc.)
    short DoubleSide;
    int Diffuse;										// ID texture slot 1
    int Shadow;											// ID texture slot 2
    int BumpSpec;										// ID texture slot 3
    int Fur;											// ID texture slot 4
};


class Animation_info {
public:
    char name[64];										// Il nome dell'animazione
	unsigned int Name_hashed;							// Hash del nome dell'animazione
    unsigned int Pointer_h;								// Dove inizia l'header dell'animazione
    unsigned int Pointer_r;								// Dove inizia il blocco dati dell'animazione
    unsigned int nBones;								// Numero di bones
    unsigned int nFrames;								// Durata in frames dell'animazione
};


class AnimationCurveData {
public:
    vector <unsigned long long> KeyTime;				// Contiene i tempi
    vector <float> KeyValueFloat;						// Contiene i valori per ogni KeyTime
    vector <int> KeyAttrFlags;							// Contiene la tipologia di ogni keyframe
    vector <int> KeyAttrDataFloat;						// Contiene i valori delle derivate dei keyframes
};


class AnimationCurveNode {
public:
    bool tX_flag = false;								// True se presente la traslazione lungo la coordinata X
    bool tY_flag = false;								// True se presente la traslazione lungo la coordinata Y
    bool tZ_flag = false;								// True se presente la traslazione lungo la coordinata Z
    bool rX_flag = false;								// True se presente la rotazione lungo la coordinata X
    bool rY_flag = false;								// True se presente la rotazione lungo la coordinata Y
    bool rZ_flag = false;								// True se presente la rotazione lungo la coordinata Z
    bool sX_flag = false;								// True se presente la scalatura lungo la coordinata X
    bool sY_flag = false;								// True se presente la scalatura lungo la coordinata Y
    bool sZ_flag = false;								// True se presente la scalatura lungo la coordinata Z
    // Classi contenenti i valori definitivi per il file FBX
    AnimationCurveData tX;
    AnimationCurveData tY;
    AnimationCurveData tZ;
    AnimationCurveData rX;
    AnimationCurveData rY;
    AnimationCurveData rZ;
    AnimationCurveData sX;
    AnimationCurveData sY;
    AnimationCurveData sZ;
    // Vettori temporanei contenenti le informazioni di rotazione estratte dal file CAL
    vector <float> rotQuatX;
    vector <float> rotQuatY;
    vector <float> rotQuatZ;
    vector <float> rotQuatW;
    string Text (int a, int b, float Xtrasl, float Ytrasl, float Ztrasl) {			// Questa funzione prepara l'animationcurvenode
        stringstream temp;
        if (tX_flag || tY_flag || tZ_flag)
        {
            temp << "	AnimationCurveNode: " << nodeID(50,b,a,0) << ", \"AnimCurveNode::T\", \"\" {\n";
            temp << "		Properties70:  {\n";
            temp << "			P: \"d|X\", \"Number\", \"\", \"A\"," << Xtrasl << "\n";
            temp << "			P: \"d|Y\", \"Number\", \"\", \"A\"," << Ytrasl << "\n";
            temp << "			P: \"d|Z\", \"Number\", \"\", \"A\"," << Ztrasl << "\n";
            temp << "		}\n";
            temp << "	}\n";
        }
        if (rX_flag || rY_flag || rZ_flag)
        {
            temp << "	AnimationCurveNode: " << nodeID(60,b,a,0) << ", \"AnimCurveNode::R\", \"\" {\n";
            temp << "		Properties70:  {\n";
            temp << "			P: \"d|X\", \"Number\", \"\", \"A\",0\n";
            temp << "			P: \"d|Y\", \"Number\", \"\", \"A\",0\n";
            temp << "			P: \"d|Z\", \"Number\", \"\", \"A\",0\n";
            temp << "		}\n";
            temp << "	}\n";
        }
        if (sX_flag || sY_flag || sZ_flag)
        {
            temp << "	AnimationCurveNode: " << nodeID(70,b,a,0) << ", \"AnimCurveNode::S\", \"\" {\n";
            temp << "		Properties70:  {\n";
            temp << "			P: \"d|X\", \"Number\", \"\", \"A\",1\n";
            temp << "			P: \"d|Y\", \"Number\", \"\", \"A\",1\n";
            temp << "			P: \"d|Z\", \"Number\", \"\", \"A\",1\n";
            temp << "		}\n";
            temp << "	}\n";
        }
        return temp.str();
    };
};


class MESH1_CLASS {
public:
    string name;										// Nome originale (hash) o ricavato da Get_mesh_name (usato per Null)
    bool hashed;										// True se "name" è un hash
    unsigned int nElements;								// Il numero di elementi del gruppo MESH1
    vector <float> X;
    vector <float> Y;
    vector <float> Z;
    vector <float> Xn;
    vector <float> Yn;
    vector <float> Zn;
    vector <float> Xtg;
    vector <float> Ytg;
    vector <float> Ztg;
    vector <float> Xbn;
    vector <float> Ybn;
    vector <float> Zbn;
    vector <float> U;
    vector <float> V;
    vector <float> W1;
    vector <float> W2;
    vector <uint8_t> Bone1;
    vector <uint8_t> Bone2;
    vector <unsigned short> arrIndex;					// Contiene lo strip
    vector <unsigned short> arrEl_Ind;					// Contiene il numero di indici dell'elemento
    vector <unsigned short> arrOffset;					// Contiene l'offset dell'elemento nel triangle strip
    vector <unsigned short> arrMat_Ref;					// ID materiale
    vector <unsigned short> arrDraw_Mode;				// Draw mode (4 o 5)
    string name_lower () {								// Restituisce lo stesso nome di "name" ma in minuscolo (usato per Mesh)
        string out = name;
        transform(out.begin(), out.end(), out.begin(), ::tolower);
        return out;
    };
};


class MESH2_CLASS {
public:
    string name;										// Nome originale (hash) o ricavato da Get_mesh_name (usato per Null)
    bool hashed;										// True se "name" è un hash
    int Bone;											// La bone a cui è associato il gruppo MESH2
    unsigned int nV;									// Il numero di vertici del gruppo MESH2
    unsigned int nElements;								// Il numero di elementi del gruppo MESH2
    vector <float> X;
    vector <float> Y;
    vector <float> Z;
    vector <float> Xn;
    vector <float> Yn;
    vector <float> Zn;
    vector <float> Xtg;
    vector <float> Ytg;
    vector <float> Ztg;
    vector <float> Xbn;
    vector <float> Ybn;
    vector <float> Zbn;
    vector <float> U;
    vector <float> V;
    vector <unsigned short> arrIndex;					// Contiene lo strip
    vector <unsigned short> arrEl_Ind;					// Contiene il numero di indici dell'elemento
    vector <unsigned short> arrOffset;					// Contiene l'offset dell'elemento nel triangle strip
    vector <unsigned short> arrMat_Ref;					// ID materiale
    vector <unsigned short> arrDraw_Mode;				// Draw mode (4 o 5)
    string name_lower () {								// Restituisce lo stesso nome di "name" ma in minuscolo (usato per Mesh)
        string out = name;
        transform(out.begin(), out.end(), out.begin(), ::tolower);
        return out;
    };
};


class TMT_CLASS {
public:
	string name;										// Nome originale (hash) o ricavato da Get_mesh_name (usato per Null)
	bool hashed;										// True se "name" è un hash
	unsigned int nBlendshapes = 0;						// Numero di blendshapes presenti (a cui va aggiunto 1 per la mesh normale)
	unsigned int nV;									// Numero di vertici del blendshape
	unsigned int mesh2_group;							// Indice del gruppo MESH 2 a cui il blendshape è associato
	unsigned int mesh2_bone;							// Indice della bone dello scheletro associata al blendshape
	Material TMT_Material;								// Il materiale del TMT è forzato a "Diffuse" (4)
	vector < vector <int> > BLENDSHAPE_vINDX;			// Contiene gli indici dei vertici diversi dalla mesh normale di ogni blendshape (per file FBX)		
	vector < vector <float> > X;
	vector < vector <float> > Y;
	vector < vector <float> > Z;
	vector < vector <float> > Xn;
	vector < vector <float> > Yn;
	vector < vector <float> > Zn;
	vector < vector <float> > U;
	vector < vector <float> > V;
	string name_lower () {								// Restituisce lo stesso nome di "name" ma in minuscolo (usato per Mesh)
		string out = name;
		transform(out.begin(), out.end(), out.begin(), ::tolower);
		return out;
	};
};


class POS_CLASS {
public:
	unsigned int Animation_hashed;
	unsigned int Blendshape_hashed;
	unsigned int nFrames = 0;
	AnimationCurveNode Cutscene_Root_Motion;
};


class FBX_COUNT_CLASS {
public:
    int AnimationStack = 0;
    int AnimationLayer = 0;
    int AnimationCurveNode = 0;
    int AnimationCurve = 0;
    int Model = 0;
    int Geometry = 0;
    int Material = 0;
    int Texture = 0;
    int NodeAttribute = 0;
    int Pose = 0;
    int BindPose = 0;
    int Deformer = 0;
};