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


#include "stdafx.h"
#include "MISC/concol.h"
#include "MISC/UI_Functions.h"
#include "Classes.h"
#include "CHAR/CHR_Struct.h"
#include "ANIM/CAL_Functions.h"
#include "CHAR/CHR_Functions.h"
#include "BLENDSHAPE/TMT_Functions.h"
#include "CPOS/POS_Functions.h"
#include "FBX/FBX_Functions.h"


int main(int argc, char **argv)
{
	IO_CLASS IO;
	CHR_HEADER chr_header;
	CHR_MESH2_LIST chr_mesh2_list;
	FBX_COUNT_CLASS CAL_FBX_Count, TMT_FBX_Count, CHR_FBX_Count;		// Contatori per i nodi dei file FBX 
	ifstream chrfile, calfile, tmtfile, posfile;						// Stream di lettura dei file CHR/CAL/TMT/POS
	ofstream out;														// Stream di output per i file FBX
	unsigned int Nlambert, Nphong;										// Contatori del numero di materiali Lambert e Phong che vengono progressivamente scritti

	if (!UI_Startup(argv, IO))			// Se c'è qualsiasi errore in fase di avvio il programma termina
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x07);							// Ripristina i colori originali della console
		SetConsoleTitle(IO.Console_OldTitle);													// Ripristina il vecchio nome della barra della console
		system("cls");
		return 0;
	}

	chrfile.open(IO.CHR, std::ios::binary);														// Apre il file CHR

    if (!chrfile.is_open())				// Se il file CHR è assente il programma termina (secondo controllo, il primo avviene in UI_Startup.cpp)
    {
		UI_Display_Error(true, IO.CHR, " not found. Unable to continue.");						// Mostra il messaggio di errore fatale
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x07);							// Ripristina i colori originali della console
		SetConsoleTitle(IO.Console_OldTitle);													// Ripristina il vecchio nome della barra della console
		system("cls");
		return 0;
	}

	chrfile.read(reinterpret_cast<char*>(&chr_header.CHR_MAGIC), sizeof(chr_header.CHR_MAGIC));	// Legge l'ID del file

	if (chr_header.CHR_MAGIC != 0)		// Se il file CHR non è valido il programma termina
	{
		UI_Display_Error(true, IO.CHR, " is not a valid CHR file. Unable to continue.");		// Mostra il messaggio di errore fatale
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x07);							// Ripristina i colori originali della console
		SetConsoleTitle(IO.Console_OldTitle);													// Ripristina il vecchio nome della barra della console
		system("cls");
		return 0;
	}

	UI_Title();																					// Pulisce lo schermo e disegna l'intestazione del programma
	CreateDirectory(IO.folder_fbx_lpwstr, NULL);												// Crea la directory "...\nome_chr" che conterrà i file di output

	/////////////////////////////////////////////////////////         INIZIO LETTURA FILE CHR          /////////////////////////////////////////////////////////
    UI_ProgressBar(0, 100, 45, " Reading CHR file...                           ", -1, 1);
	
	// LETTURA HEADER FILE CHR
    chrfile.read(reinterpret_cast<char*>(&chr_header.TEXTURE_PTR), sizeof(chr_header.TEXTURE_PTR));
    chrfile.read(reinterpret_cast<char*>(&chr_header.SKELETON_PTR), sizeof(chr_header.SKELETON_PTR));
    chrfile.seekg(4, ios_base::cur);
    chrfile.read(reinterpret_cast<char*>(&chr_header.MESH1_PTR), sizeof(chr_header.MESH1_PTR));
    chrfile.read(reinterpret_cast<char*>(&chr_header.nBONES), sizeof(chr_header.nBONES));
	UI_ProgressBar(9, 100, 45, " Reading CHR file...                           ", -1, 1);

    // LETTURA SCHELETRO E CALCOLO TRASFORMAZIONI BONES
    vector <unsigned int> Hierarchy(chr_header.nBONES);							// Vettore contenente i valori di gerarchia di tutte le bones
    vector <string> Bone_name(chr_header.nBONES);								// Nomi delle bones (vengono scritti nel file FBX)
    vector <matrix4x4> SKquat(chr_header.nBONES), BONESquat(chr_header.nBONES);	// Valori di traslazione e scalatura di ogni bone
    vector <int> Anim_bones;													// Contiene gli indici delle bones non DYNAMIC
    chrfile.seekg(chr_header.SKELETON_PTR);																// Posiziona la lettura all'inizio del gruppo SKELETON
    CHR_Read_Skeleton(chr_header.nBONES, Hierarchy, Bone_name, SKquat, BONESquat, Anim_bones, chrfile);
	UI_ProgressBar(34, 100, 45, " Reading CHR file...                           ", -1, 1);

    // LETTURA BLOCCO MESH 1
    MESH1_CLASS mesh1;															// Classe contenente tutte le informazioni su nome, vertici, facce ed elementi del gruppo mesh 1
    chrfile.seekg(chr_header.MESH1_PTR);																// Salta il blocco dello scheletro
    CHR_Read_Mesh1(mesh1, SKquat, chrfile);
	UI_ProgressBar(64, 100, 45, " Reading CHR file...                           ", -1, 1);

    // LETTURA BLOCCO MESH 2
    chrfile.read(reinterpret_cast<char*>(&chr_mesh2_list.nMeshes2), sizeof(chr_mesh2_list.nMeshes2));	// Legge il numero di gruppi mesh di tipo 2
    vector <MESH2_CLASS> mesh2(chr_mesh2_list.nMeshes2);						// Classe contenente tutte le informazioni su nome, vertici, facce ed elementi del gruppo mesh 2
    for (unsigned int g = 0; g < chr_mesh2_list.nMeshes2; g++)											// "g" è il contatore dei gruppi MESH2
        CHR_Read_Mesh2(&mesh2[g], SKquat, chrfile);
	UI_ProgressBar(89, 100, 45, " Reading CHR file...                           ", -1, 1);

    // LETTURA MATERIALI
    vector <Material> Materials;
    CHR_Read_Materials(Materials, chrfile);
	UI_ProgressBar(99, 100, 45, " Reading CHR file...                           ", 0, 1);

    // ESPORTAZIONE TEXTURES
    vector <TextureHeader> TextureHeader;
	if (IO.Export_CHR || IO.Export_TMT)		// Le texture vengono esportate solo se è stata selezionata l'esportazione dei blend shapes e/o del modello in T-Pose
		CHR_Export_Textures(TextureHeader, &CHR_FBX_Count, chrfile, IO);

    chrfile.close();
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


    /////////////////////////////////////////////////////////      INIZIO LETTURA FILE ANIMAZIONI      /////////////////////////////////////////////////////////
	vector <Animation_info> Ani_header;
	vector < vector <AnimationCurveNode> > Ani_curvenode;
	if (IO.Export_CAL)																			// Controlla se l'esportazione delle animazioni è stata selezionata
	{
		calfile.open(IO.CAL, std::ios::binary);													// Apre il file CAL
		if (calfile.is_open())
		{
			CAL_Read(calfile, Ani_header, Ani_curvenode);
			calfile.close();
		}
		else
		{
			UI_Display_Error(false, IO.CAL, " not found. Animations will not be exported.");	// Mostra il messaggio di errore se manca il file
			IO.Export_CAL = false;																// Se il file CAL è assente le animazioni non vengono esportate
		}
	}
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/////////////////////////////////////////////////////////      INIZIO LETTURA FILE BLENDSHAPES      ////////////////////////////////////////////////////////
	TMT_CLASS tmt;
	if (IO.Export_TMT)																			// Controlla se l'esportazione dei blend shapes è stata selezionata
	{
		tmtfile.open(IO.TMT, std::ios::binary);													// Apre il file TMT
		if (tmtfile.is_open())
		{
			IO.Export_TMT = TMT_Read(tmtfile, tmt, mesh2, SKquat, Materials, IO);				// Se c'è qualche errore durante la lettura la funzione ritorna falso
			tmtfile.close();
		}
		else
		{
			UI_Display_Error(false, IO.TMT, " not found. Blend Shapes will not be exported.");	// Mostra il messaggio di errore se manca il file	
			IO.Export_TMT = false;																// Se il file TMT è assente i blend shapes non vengono esportati
		}
	}
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	SetCurrentDirectory(IO.folder_fbx_lpwstr);													// Imposta la cartella di output degli FBX

	//////////////////////////////////////////////////////////      ESPORTAZIONE FBX BLEND SHAPES      /////////////////////////////////////////////////////////
	if (IO.Export_TMT)
	{
		UI_ProgressBar(0, 100, 45, " Writing Blend Shapes...                       ", -1, 1);

		// CREAZIONE LISTA FACCE
		vector <int> BLENDSHAPE_FACES;
		Calculate_Faces_Blendshape(tmt, mesh2, BLENDSHAPE_FACES);
		UI_ProgressBar(9, 100, 45, " Writing Blend Shapes...                       ", -1, 1);

		// PREPARAZIONE FBX_COUNT ED INIZIALIZZAZIONE CONTATORI MATERIALI LAMBERT E PHONG
		TMT_FBX_Count.Model = 2 + chr_header.nBONES;							// TMT Blend shape 0 Null + TMT Blend shape 0 Mesh + numero di bones
		TMT_FBX_Count.NodeAttribute = chr_header.nBONES;
		TMT_FBX_Count.Geometry = tmt.nBlendshapes + 1;							// Viene aggiunto 1 per la mesh normale
		TMT_FBX_Count.Deformer = tmt.nBlendshapes + 3;							// Subdeformers blend shapes + deformer blend shapes + subdeformer bone skin + deformer bone skin
		TMT_FBX_Count.Material = 1;
        TMT_FBX_Count.Pose = 1;
		TMT_FBX_Count.BindPose = chr_header.nBONES + 1;
		if (TextureHeader[tmt.TMT_Material.Diffuse].DXT == 1)					// Se la texture DDS è DXT1 il BMP è singolo
			TMT_FBX_Count.Texture = 1;
		else																	// Se la texture DDS non è DXT1 allora bisogna considerare anche il BMP del canale alpha
			TMT_FBX_Count.Texture = 2;
		Nlambert = 0;
		Nphong = 0;

		UI_ProgressBar(14, 100, 45, " Writing Blend Shapes...                       ", -1, 1);

		// SCRITTURA FILE FBX BLEND SHAPES
		out.open(IO.filename_FBX_TMT());
		FBX_Write_Header(out);
		FBX_Write_Object_definitions(TMT_FBX_Count, out);
		out << "; Object properties\n";
		out << ";------------------------------------------------------------------\n\n";
		out << "Objects:  {\n";
		FBX_Write_Blendshape(tmt, BLENDSHAPE_FACES, SKquat, out);																// Blend shapes + mesh normale
		UI_ProgressBar(69, 100, 45, " Writing Blend Shapes...                       ", -1, 1);
		FBX_Write_Material(&tmt.TMT_Material, &Nlambert, &Nphong, out);															// Materiali
		FBX_Write_Bone(chr_header, Bone_name, BONESquat, out);																	// Bones
		FBX_Write_BindPose_Blendshape(TMT_FBX_Count, chr_header, tmt, SKquat, out);												// Bind pose blend shape
		FBX_Write_Texture(IO, &TextureHeader[tmt.TMT_Material.Diffuse], out);													// Textures
		out << "}\n\n";
		out << "; Object connections\n";
		out << ";------------------------------------------------------------------\n\n";
		out << "Connections:  {\n\n";
		FBX_Write_Connection_Blendshape(tmt, out);																				// Connections blend shapes + mesh normale
		FBX_Write_Connection_Bone(Hierarchy, chr_header, out);																	// Connections bones
		FBX_Write_Connection_Material(TextureHeader, &tmt.TMT_Material, out);													// Connections materiali + textures
		out << "}";
		out.close();
		UI_ProgressBar(99, 100, 45, " Writing Blend Shapes...                       ", 0, 1);
	}
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	///////////////////////////////////////////////////////////      ESPORTAZIONE FBX ANIMAZIONI      //////////////////////////////////////////////////////////
	if (IO.Export_CAL)
	{
		// CREAZIONE DIRECTORY PER LE ANIMAZIONI
		CreateDirectory(IO.folder_ani_lpwstr(), NULL);												// Crea la directory "...\nome_chr\nome_chr_ANIMATIONS"
        SetCurrentDirectory(IO.folder_ani_lpwstr());												// Imposta "...\nome_chr\nome_chr_ANIMATIONS" come cartella di lavoro

		for (unsigned int a = 0; a < Ani_header.size(); a++)										// Ogni ciclo esporta una animazione
        {
			UI_ProgressBar(a, Ani_header.size(), 45, " Writing animations...                         ");

			// PREPARAZIONE FBX_COUNT
			CAL_FBX_Count.AnimationCurveNode = 0;													// Resetta questo valore ad ogni ciclo
			CAL_FBX_Count.AnimationCurve = 0;														// Resetta questo valore ad ogni ciclo
            for (unsigned int b = 0; b < min(Anim_bones.size(), Ani_curvenode[a].size()); b++)		// Conta gli AnimationCurveNode e gli AnimationCurve
            {
                if (Ani_curvenode[a][b].tX_flag || Ani_curvenode[a][b].tY_flag || Ani_curvenode[a][b].tZ_flag)      // Controlla che ci sia almeno una traslazione
                    CAL_FBX_Count.AnimationCurveNode++;
                if (Ani_curvenode[a][b].rX_flag || Ani_curvenode[a][b].rY_flag || Ani_curvenode[a][b].rZ_flag)      // Controlla che ci sia almeno una rotazione
                    CAL_FBX_Count.AnimationCurveNode++;
                if (Ani_curvenode[a][b].sX_flag || Ani_curvenode[a][b].sY_flag || Ani_curvenode[a][b].sZ_flag)      // Controlla che ci sia almeno una scalatura
                    CAL_FBX_Count.AnimationCurveNode++;
                if (Ani_curvenode[a][b].tX_flag)    CAL_FBX_Count.AnimationCurve++;
                if (Ani_curvenode[a][b].tY_flag)    CAL_FBX_Count.AnimationCurve++;
                if (Ani_curvenode[a][b].tZ_flag)    CAL_FBX_Count.AnimationCurve++;
                if (Ani_curvenode[a][b].rX_flag)    CAL_FBX_Count.AnimationCurve++;
                if (Ani_curvenode[a][b].rY_flag)    CAL_FBX_Count.AnimationCurve++;
                if (Ani_curvenode[a][b].rZ_flag)    CAL_FBX_Count.AnimationCurve++;
                if (Ani_curvenode[a][b].sX_flag)    CAL_FBX_Count.AnimationCurve++;
                if (Ani_curvenode[a][b].sY_flag)    CAL_FBX_Count.AnimationCurve++;
                if (Ani_curvenode[a][b].sZ_flag)    CAL_FBX_Count.AnimationCurve++;
            }
			CAL_FBX_Count.AnimationStack = 1;
			CAL_FBX_Count.AnimationLayer = 1;
			CAL_FBX_Count.Model = chr_header.nBONES;
			CAL_FBX_Count.NodeAttribute = chr_header.nBONES;

			// SCRITTURA FILE FBX ANIMAZIONI
            out.open(IO.filename_FBX_CAL(Ani_header[a].name));
            FBX_Write_Header(out);
            FBX_Write_Object_definitions(CAL_FBX_Count, out);
            out << "; Object properties\n";
            out << ";------------------------------------------------------------------\n\n";
            out << "Objects:  {\n";
            FBX_Write_Bone(chr_header, Bone_name, BONESquat, out);																// Bones
			FBX_Write_Animation(a, Ani_header, Anim_bones, Ani_curvenode, BONESquat, out);										// Animazioni
            out << "}\n\n";
            out << "; Object connections\n";
            out << ";------------------------------------------------------------------\n\n";
            out << "Connections:  {\n\n";
            FBX_Write_Connection_Bone(Hierarchy, chr_header, out);																// Connections bones
            FBX_Write_Connection_Animation(a, Anim_bones, Ani_curvenode, out);													// Connections animazioni
            out << "}";
            out.close();
        }
		SetCurrentDirectory(IO.folder_fbx_lpwstr);												// Reimposta l'originale cartella di lavoro
	}
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	///////////////////////////////////////////////////////////      ESPORTAZIONE FBX CHR T-POSE      //////////////////////////////////////////////////////////
	if (IO.Export_CHR)
	{
		UI_ProgressBar(0, 100, 45, " Writing T-Pose model...                       ", -1, 1);

		// CREAZIONE LISTA FACCE GRUPPO MESH 1: CREAZIONE DEL VETTORE CONTENENTE TUTTE LE FACCE(1) DI TUTTI GLI ELEMENTI(2) (MATRICE 2D)
		vector < vector <unsigned short> > MESH1_vINDX(mesh1.nElements);                    // Contiene gli indici dei vertici realmente presenti nello strip dell'elemento
		vector < vector <int> > MESH1_FACES(mesh1.nElements);                               // VETTORE 2D "ELEMENTI" x "FACCE"
		Calculate_Faces_Mesh1(mesh1, MESH1_vINDX, MESH1_FACES);
		UI_ProgressBar(9, 100, 45, " Writing T-Pose model...                       ", -1, 1);

		// CREAZIONE LISTA FACCE GRUPPO MESH 2: CREAZIONE DEL VETTORE CONTENENTE TUTTE LE FACCE(1) DI TUTTI GLI ELEMENTI(2) DI TUTTI I GRUPPI(3) (MATRICE 3D)
		vector < vector < vector <unsigned short> > > MESH2_vINDX(chr_mesh2_list.nMeshes2); // Contiene gli indici dei vertici realmente presenti nello strip dell'elemento
		vector < vector < vector <int> > > MESH2_FACES(chr_mesh2_list.nMeshes2);            // VETTORE 3D "GRUPPI" x "ELEMENTI" x "FACCE"
		Calculate_Faces_Mesh2(mesh2, MESH2_vINDX, MESH2_FACES);
		UI_ProgressBar(19, 100, 45, " Writing T-Pose model...                       ", -1, 1);

		// PREPARAZIONE FBX_COUNT ED INIZIALIZZAZIONE CONTATORI MATERIALI LAMBERT E PHONG
		int nMesh1Elements = 0;
        int nMesh1SubDeformers = 0;
        for (unsigned int el = 0; el < mesh1.nElements; el++)
            if (MESH1_FACES[el].size() > 2)														// Controlla che l'elemento del gruppo MESH 1 abbia almeno una faccia
            {
                nMesh1Elements++;
                for (unsigned int b = 0; b < chr_header.nBONES; b++)							// Questo ciclo controlla se ogni bone è presente nell'elemento
                    for (unsigned int check_v = 0; check_v < MESH1_vINDX[el].size(); check_v++)
                        if (mesh1.Bone1[MESH1_vINDX[el][check_v]] == b || mesh1.Bone2[MESH1_vINDX[el][check_v]] == b)	// Se la bone viene trovata viene aggiunto un SubDeformer
                        {
                            check_v = MESH1_vINDX[el].size() + 1;				// Impedisce che venga controllata la stessa bone più volte interrompendo il ciclo for a monte
                            nMesh1SubDeformers++;
                        }
            }
        int nMesh2 = 0;
        int nMesh2Elements = 0;
        for (unsigned int g = 0; g < chr_mesh2_list.nMeshes2; g++)
            if (mesh2[g].nV != 0)																// Controlla che il gruppo MESH 2 non sia privo di vertici, quindi nullo
            {
                nMesh2++;
                for (unsigned int el = 0; el < mesh2[g].nElements; el++)
                    if (MESH2_FACES[g][el].size() > 2)											// Controlla che l'elemento del gruppo MESH 2 abbia almeno una faccia
                        nMesh2Elements++;
            }
        CHR_FBX_Count.Model = chr_header.nBONES + nMesh1Elements + nMesh2Elements + nMesh2 + 1;	// Viene aggiunto 1 perchè è la radice BODY delle parti del corpo del gruppo MESH 1
        CHR_FBX_Count.Geometry = nMesh1Elements + nMesh2Elements;
        CHR_FBX_Count.Material = Materials.size();
		CHR_FBX_Count.NodeAttribute = chr_header.nBONES;
        CHR_FBX_Count.Pose = 1;
		CHR_FBX_Count.BindPose = chr_header.nBONES + nMesh1Elements + nMesh2Elements;
		CHR_FBX_Count.Deformer = CHR_FBX_Count.Geometry + nMesh1SubDeformers + nMesh2Elements;
		Nlambert = 0;
		Nphong = 0;

		UI_ProgressBar(29, 100, 45, " Writing T-Pose model...                       ", -1, 1);

		// SCRITTURA FILE FBX CHR T-POSE
		out.open(IO.filename_FBX_CHR());
        FBX_Write_Header(out);
        FBX_Write_Object_definitions(CHR_FBX_Count, out);
        out << "; Object properties\n";
        out << ";------------------------------------------------------------------\n\n";
        out << "Objects:  {\n";
        FBX_Write_Mesh1(mesh1, MESH1_FACES, MESH1_vINDX, chr_header, SKquat, out);												// Blocco mesh 1
		UI_ProgressBar(59, 100, 45, " Writing T-Pose model...                       ", -1, 1);
        FBX_Write_Mesh2(mesh2, MESH2_FACES, MESH2_vINDX, chr_mesh2_list, SKquat, out);											// Blocco mesh 2
		UI_ProgressBar(84, 100, 45, " Writing T-Pose model...                       ", -1, 1);
        FBX_Write_Bone(chr_header, Bone_name, BONESquat, out);																	// Bones
        FBX_Write_BindPose(CHR_FBX_Count, mesh1, mesh2, MESH1_FACES, MESH2_FACES, chr_header, chr_mesh2_list, SKquat, out);		// Bind pose
		for (unsigned int m = 0; m < Materials.size(); m++)
			FBX_Write_Material(&Materials[m], &Nlambert, &Nphong, out);															// Materiali
		for (unsigned int t = 0; t < TextureHeader.size(); t++)
			FBX_Write_Texture(IO, &TextureHeader[t], out);																		// Textures
        out << "}\n\n";
        out << "; Object connections\n";
        out << ";------------------------------------------------------------------\n\n";
        out << "Connections:  {\n\n";
        FBX_Write_Connection_Mesh1(mesh1, MESH1_FACES, MESH1_vINDX, chr_header, out);											// Connections blocco mesh 1
        FBX_Write_Connection_Mesh2(mesh2, MESH2_FACES, chr_mesh2_list, out);													// Connections blocco mesh 2
        FBX_Write_Connection_Bone(Hierarchy, chr_header, out);																	// Connections bones
        for (unsigned int m = 0; m < Materials.size(); m++)
			FBX_Write_Connection_Material(TextureHeader, &Materials[m], out);													// Connections materiali + textures
        out << "}";
        out.close();
		UI_ProgressBar(99, 100, 45, " Writing T-Pose model...                       ", 0, 1);
	}
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	cout << purple << "\n\n Operation completed! Press any key to exit. ";
	getch();
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x07);			// Ripristina i colori originali della console
	SetConsoleTitle(IO.Console_OldTitle);									// Ripristina il vecchio nome della barra della console
	system("cls");
	return 0;
}