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
Legge le textures dal file CHR e ne salva le informazioni, le esporta in DDS, le converte in BMP e separa il canale alfa
INPUT: ifstream &chrfile, IO_CLASS IO
OUTPUT: vector <TextureHeader> &TextureHeader, FBX_COUNT_CLASS *FBX_Count
------------------------------------------------------------------------------------------------------------------*/

#include "stdafx.h"
#include "MISC/concol.h"
#include "CHAR/CHR_Struct.h"
#include "Classes.h"
#include "MISC/UI_Functions.h"


void CHR_Export_Textures (vector <TextureHeader> &TextureHeader, FBX_COUNT_CLASS *FBX_Count, ifstream &chrfile, IO_CLASS &IO)
{
    CHR_HEADER chr_header;
    CHR_MATERIALS_HEADER chr_materials_header;
    CHR_TEXTURES_HEADER chr_textures_header;
    CHR_TEXTURES_LIST chr_textures_list;

	///////////////////    CONTROLLO PRESENZA FILES DI DDS2BMP
	SetCurrentDirectory(IO.folder_exe_lpwstr);		// Imposta la cartella di lettura per controllare se ci sono i files
	string text = " not found. ";
	if (IO.Export_CHR && !IO.Export_TMT)
		text.append("T-Pose model will not be exported.");
	if (!IO.Export_CHR && IO.Export_TMT)
		text.append("Blend Shapes will not be exported.");
	if (IO.Export_CHR && IO.Export_TMT)
		text.append("T-Pose model and Blend Shapes will not be exported.");
	ifstream TestIfExists("dds2bmp.exe", std::ios::binary);		// Controlla che dds2bmp.exe sia presente
    if (!TestIfExists.is_open())
	{
		UI_Display_Error(false, "dds2bmp.exe", text);
		IO.Export_CHR = false;
		IO.Export_TMT = false;
		SetCurrentDirectory(IO.folder_chr_lpwstr);
        return;
	}
    TestIfExists.close();
    TestIfExists.open("FreeImage.dll", std::ios::binary);		// Controlla che FreeImage.dll sia presente
    if (!TestIfExists.is_open())
	{
        UI_Display_Error(false, "FreeImage.dll", text);
		IO.Export_CHR = false;
		IO.Export_TMT = false;
		SetCurrentDirectory(IO.folder_chr_lpwstr);
        return;
	}
    TestIfExists.close();
	SetCurrentDirectory(IO.folder_fbx_lpwstr);		// Imposta la cartella dell'FBX per esportare i DDS

	///////////////////    INIZIO LETTURA CHR
    streamoff original_position = chrfile.tellg();	// Memorizza la posizione iniziale del cursore nel file per poterci tornare alla fine della funzione
    chrfile.seekg(4, chrfile.beg);					// Posiziona il cursore di lettura all'inizio del file, con offset di 4 bytes per leggere l'offset del blocco textures
    chrfile.read(reinterpret_cast<char*>(&chr_header.TEXTURE_PTR), sizeof(chr_header.TEXTURE_PTR));
    chrfile.seekg(chr_header.TEXTURE_PTR);
    chrfile.read(reinterpret_cast<char*>(&chr_materials_header.nMaterials), sizeof(chr_materials_header.nMaterials));	// Legge il numero di materiali (serve per poterli saltare)
    chrfile.seekg(chr_materials_header.nMaterials * 24, chrfile.cur);													// Salta il blocco materiali
    chrfile.read(reinterpret_cast<char*>(&chr_textures_header.nTextures), sizeof(chr_textures_header.nTextures));		// Legge il numero di textures

    TextureHeader.resize(chr_textures_header.nTextures);

    for (unsigned int T = 0; T < chr_textures_header.nTextures; T++)
	{
		UI_ProgressBar(T, chr_textures_header.nTextures, 45, " Exporting textures...                         ");

		int DXT, ColourBumpShadow;
        chrfile.read(reinterpret_cast<char*>(&DXT), sizeof(chr_textures_list.DXT));									// DXT1, DXT3, DXT5 o RGBA
        chrfile.read(reinterpret_cast<char*>(&ColourBumpShadow), sizeof(chr_textures_list.ColourBumpShadow));		// 1 = shadow map, 2 = colour map, 4 = bump map, 5 = fur
        chrfile.seekg(4, ios_base::cur);																			// Salta Unknown1
        chrfile.read(reinterpret_cast<char*>(&chr_textures_list.Mips), sizeof(chr_textures_list.Mips));				// MIPS
        chrfile.read(reinterpret_cast<char*>(&chr_textures_list.Xsize), sizeof(chr_textures_list.Xsize));			// Dimensioni texture asse X
        chrfile.read(reinterpret_cast<char*>(&chr_textures_list.Ysize), sizeof(chr_textures_list.Ysize));			// Dimensioni texture asse Y
        chrfile.read(reinterpret_cast<char*>(&chr_textures_list.RAWsize), sizeof(chr_textures_list.RAWsize));		// Dimensioni texture in bytes

		TextureHeader[T].Number = T;
        TextureHeader[T].ColourBumpShadow = ColourBumpShadow;
        if (DXT == 827611204)				// DXT1
            TextureHeader[T].DXT = 1;
        if (DXT == 861165636)				// DXT3
            TextureHeader[T].DXT = 3;
        if (DXT == 894720068)				// DXT5
            TextureHeader[T].DXT = 5;
        if (DXT == 21)						// ARGB
            TextureHeader[T].DXT = 0;

        if (DXT == 827611204 || DXT == 861165636 || DXT == 894720068)				// ESPORTAZIONE E CONVERSIONE TEXTURE DDS
        {
			///////////////////    ESPORTAZIONE DDS
            stringstream INCREMENT_NAME, OUTFILE;
            INCREMENT_NAME << IO.chr_name << "_" << T << ".dds";
            string FILENAME = INCREMENT_NAME.str();					// Il nome della texture
            ofstream dds, bmpdiffuse, bmptransparency, bmpbump, bmpenvspec;
            dds.open(FILENAME.c_str(), ofstream::binary);
            dds << char(0x44) << char(0x44) << char(0x53) << char(0x20) << char(0x7c) << char(0x00);
			dds << char(0x00) << char(0x00) << char(0x07) << char(0x10) << char(0x0a) << char(0x00);
            dds.write(reinterpret_cast<const char*>(&chr_textures_list.Xsize), 4);		// DIMENSIONI DEI LATI DELLE TEXTURE
            dds.write(reinterpret_cast<const char*>(&chr_textures_list.Ysize), 4);		// DIMENSIONI DEI LATI DELLE TEXTURE
            for (int h = 0; h < 8; h++)
                dds << char(0x00);
            dds.write(reinterpret_cast<const char*>(&chr_textures_list.Mips), 4);		// MIPMAPS
            for (int h = 0; h < 44; h++)
                dds << char(0x00);
            dds << char(0x20) << char(0x00) << char(0x00) << char(0x00) << char(0x04) << char(0x00) << char(0x00) << char(0x00);
            dds.write(reinterpret_cast<const char*>(&DXT), 4);							// DXT1/DXT3/DXT5
            for (int h = 0; h < 20; h++)
                dds << char(0x00);
            dds << char(0x08) << char(0x10) << char(0x40);
            for (int h = 0; h < 17; h++)
                dds << char(0x00);
            char* buffer = new char[chr_textures_list.RAWsize];							// Buffer di lettura
            chrfile.read(buffer, chr_textures_list.RAWsize);                            // Legge i dati raw della texture e li mette nel buffer
            dds.write(buffer, chr_textures_list.RAWsize);                               // Copia il buffer nel file di destinazione
            delete[] buffer;
            dds.close();

			///////////////////    CONVERSIONE DDS IN BMP
			SetCurrentDirectory(IO.folder_exe_lpwstr);
            char cmdstring[MAX] = "dds2bmp -q --flip-vertical -i \"";
			strcat(cmdstring, IO.fbx_folder.c_str());
            strcat(cmdstring, FILENAME.c_str());
			strcat(cmdstring, "\"");					// Nome e percorso del file vengono racchiusi tra virgolette per prevenire bug nel caso in cui contengano spazi
            system(cmdstring);							// Questa stringa fa partire il programma che converte in BMP il file DDS
			SetCurrentDirectory(IO.folder_fbx_lpwstr);

			///////////////////    CREAZIONE FILE DI OUTPUT FINALI
            INCREMENT_NAME.str("");						// Pulizia stringstream
            INCREMENT_NAME.clear();						// Pulizia stringstream
            INCREMENT_NAME << IO.chr_name << "_" << T << ".bmp";

            if (DXT == 827611204 && ColourBumpShadow == 2)							// TEXTURE DXT1, DIFFUSE COLOR. ENTRA 1 BMP, ESCE 1 BMP
            {
                OUTFILE << IO.chr_name << "_" << T << "_diffuse.bmp";
                FILENAME = OUTFILE.str();
                bmpdiffuse.open(FILENAME.c_str(), ofstream::binary);		// Prepara il nuovo file BMP
                FILENAME = INCREMENT_NAME.str();
                ifstream bmpread(FILENAME.c_str(), std::ios::binary);       // Apre il file BMP convertito
                bmpread.seekg(0, bmpread.end);
                int filesize = bmpread.tellg();
                bmpread.seekg(0, bmpread.beg);
                char* buffer = new char[filesize];
                bmpread.read(buffer, filesize);
                bmpdiffuse.write(buffer, filesize);
                delete[] buffer;
                bmpdiffuse.close();
                bmpread.close();
                remove(FILENAME.c_str());
                FBX_Count->Texture++;
            }
            if (DXT == 827611204 && ColourBumpShadow == 4)							// TEXTURE DXT1, BUMP MAP. ENTRA 1 BMP, ESCE 1 BMP
            {
                OUTFILE << IO.chr_name << "_" << T << "_bump.bmp";
                FILENAME = OUTFILE.str();
                bmpbump.open(FILENAME.c_str(), ofstream::binary);           // Prepara il nuovo file BMP
                FILENAME = INCREMENT_NAME.str();
                ifstream bmpread(FILENAME.c_str(), std::ios::binary);       // Apre il file BMP convertito
                bmpread.seekg(0, bmpread.end);
                int filesize = bmpread.tellg();
                bmpread.seekg(0, bmpread.beg);
                char* buffer = new char[filesize];
                bmpread.read(buffer, filesize);
                bmpbump.write(buffer, filesize);
                delete[] buffer;
                bmpbump.close();
                bmpread.close();
                remove(FILENAME.c_str());
                FBX_Count->Texture++;
            }
            if ((DXT == 861165636 || DXT == 894720068) && ColourBumpShadow == 2)	// TEXTURE DXT3/DXT5, DIFFUSE COLOR + TRANSPARENCY. ENTRA 1 BMP, ESCONO 2 BMP
            {
                OUTFILE << IO.chr_name << "_" << T << "_diffuse.bmp";
                FILENAME = OUTFILE.str();
                bmpdiffuse.open(FILENAME.c_str(), ofstream::binary);        // Prepara il nuovo file BMP 1/2
                OUTFILE.str("");
                OUTFILE.clear();
                OUTFILE << IO.chr_name << "_" << T << "_transparency.bmp";
                FILENAME = OUTFILE.str();
                bmptransparency.open(FILENAME.c_str(), ofstream::binary);   // Prepara il nuovo file BMP 2/2
                FILENAME = INCREMENT_NAME.str();
                ifstream bmpread(FILENAME.c_str(), std::ios::binary);		// Apre il file BMP convertito

                bmpdiffuse << char(0x42) << char(0x4d);                     // Intestazione BMP 1/2 (DIFFUSE)
                int BMP_size(chr_textures_list.Xsize * chr_textures_list.Ysize * 3 + 54);	// X*Y*3 (numero pixels*24 bpp/8=dimensione in bytes)+54 (bytes header)
                int BMP_raw_size(chr_textures_list.Xsize * chr_textures_list.Ysize * 3);
                bmpdiffuse.write(reinterpret_cast<const char*>(&BMP_size), 4);						// Dimensione file BMP
                bmpdiffuse << char(0x00) << char(0x00) << char(0x00) << char(0x00) << char(0x36) << char(0x00);
				bmpdiffuse << char(0x00) << char(0x00) << char(0x28) << char(0x00) << char(0x00) << char(0x00);
                bmpdiffuse.write(reinterpret_cast<const char*>(&chr_textures_list.Xsize), 4);		// DIMENSIONI DEI LATI DELLE TEXTURE
                bmpdiffuse.write(reinterpret_cast<const char*>(&chr_textures_list.Ysize), 4);		// DIMENSIONI DEI LATI DELLE TEXTURE
                bmpdiffuse << char(0x01) << char(0x00) << char(0x18) << char(0x00) << char(0x00) << char(0x00) << char(0x00) << char(0x00);
                bmpdiffuse.write(reinterpret_cast<const char*>(&BMP_raw_size), 4);					// Dimensioni dati RAW texture
                for (int h = 0; h < 16; h++)
                    bmpdiffuse << char(0x00);

                bmptransparency << char(0x42) << char(0x4d);                // Intestazione BMP 2/2 (TRANSPARENCY)
                BMP_size = chr_textures_list.Xsize * chr_textures_list.Ysize + 54 + 1024;	// X*Y (numero pixels*8 bpp/8=dimensione in bytes)+54+1024 (bytes header e indici colori)
                BMP_raw_size = chr_textures_list.Xsize * chr_textures_list.Ysize;
                bmptransparency.write(reinterpret_cast<const char*>(&BMP_size), 4);					// Dimensione file BMP
                bmptransparency << char(0x00) << char(0x00) << char(0x00) << char(0x00) << char(0x36) << char(0x04);
				bmptransparency << char(0x00) << char(0x00) << char(0x28) << char(0x00) << char(0x00) << char(0x00);
                bmptransparency.write(reinterpret_cast<const char*>(&chr_textures_list.Xsize), 4);	// DIMENSIONI DEI LATI DELLE TEXTURE
                bmptransparency.write(reinterpret_cast<const char*>(&chr_textures_list.Ysize), 4);	// DIMENSIONI DEI LATI DELLE TEXTURE
                bmptransparency << char(0x01) << char(0x00) << char(0x08) << char(0x00) << char(0x00) << char(0x00) << char(0x00) << char(0x00);
                bmptransparency.write(reinterpret_cast<const char*>(&BMP_raw_size), 4);				// Dimensioni dati RAW texture
                for (int h = 0; h < 16; h++)
                    bmptransparency << char(0x00);
                for (int h = 0; h < 256; h++)			// Questo ciclo scrive l'indice colori del BMP monocromatico
                {
                    bmptransparency.write(reinterpret_cast<const char*>(&h), 1);
                    bmptransparency.write(reinterpret_cast<const char*>(&h), 1);
                    bmptransparency.write(reinterpret_cast<const char*>(&h), 1);
                    bmptransparency << char(0x00);
                }
                bmpread.seekg(54, bmpread.beg);
                char* buffer1 = new char[3];
                char* buffer2 = new char[1];
                for (unsigned int b = 0; b < chr_textures_list.Xsize*chr_textures_list.Ysize; b++)		// Scrittura dati RAW di entrambe le textures
                {
                    bmpread.read(buffer1, 3);
                    bmpread.read(buffer2, 1);
                    bmpdiffuse.write(buffer1, 3);
                    bmptransparency.write(buffer2, 1);
                }
                delete[] buffer1;
                delete[] buffer2;
                bmpdiffuse.close();
                bmptransparency.close();
                bmpread.close();
                remove(FILENAME.c_str());
                FBX_Count->Texture += 2;
            }
            if ((DXT == 861165636 || DXT == 894720068) && ColourBumpShadow == 4)	// TEXTURE DXT3/DXT5, BUMP MAP + ENVSPEC. ENTRA 1 BMP, ESCONO 2 BMP
            {
                OUTFILE << IO.chr_name << "_" << T << "_bump.bmp";
                FILENAME = OUTFILE.str();
                bmpbump.open(FILENAME.c_str(), ofstream::binary);           // Prepara il nuovo file BMP 1/2
                OUTFILE.str("");
                OUTFILE.clear();
                OUTFILE << IO.chr_name << "_" << T << "_envspec.bmp";
                FILENAME = OUTFILE.str();
                bmpenvspec.open(FILENAME.c_str(), ofstream::binary);        // Prepara il nuovo file BMP 2/2
                FILENAME = INCREMENT_NAME.str();
                ifstream bmpread(FILENAME.c_str(), std::ios::binary);       // Apre il file BMP convertito

                bmpbump << char(0x42) << char(0x4d);						// Intestazione BMP 1/2 (BUMP MAP)
                int BMP_size(chr_textures_list.Xsize * chr_textures_list.Ysize * 3 + 54);	// X*Y*3 (numero pixels*24 bpp/8=dimensione in bytes)+54 (bytes header)
                int BMP_raw_size(chr_textures_list.Xsize * chr_textures_list.Ysize * 3);
                bmpbump.write(reinterpret_cast<const char*>(&BMP_size), 4);							// Dimensione file BMP
                bmpbump << char(0x00) << char(0x00) << char(0x00) << char(0x00) << char(0x36) << char(0x00);
				bmpbump << char(0x00) << char(0x00) << char(0x28) << char(0x00) << char(0x00) << char(0x00);
                bmpbump.write(reinterpret_cast<const char*>(&chr_textures_list.Xsize), 4);			// DIMENSIONI DEI LATI DELLE TEXTURE
                bmpbump.write(reinterpret_cast<const char*>(&chr_textures_list.Ysize), 4);			// DIMENSIONI DEI LATI DELLE TEXTURE
                bmpbump << char(0x01) << char(0x00) << char(0x18) << char(0x00) << char(0x00) << char(0x00) << char(0x00) << char(0x00);
                bmpbump.write(reinterpret_cast<const char*>(&BMP_raw_size), 4);						// Dimensioni dati RAW texture
                for (int h = 0; h < 16; h++)
                    bmpbump << char(0x00);

                bmpenvspec << char(0x42) << char(0x4d);						// Intestazione BMP 2/2 (ENVSPEC)
                BMP_size = chr_textures_list.Xsize * chr_textures_list.Ysize + 54 + 1024;	// X*Y (numero pixels*8 bpp/8=dimensione in bytes)+54+1024 (bytes header e indici colori)
                BMP_raw_size = chr_textures_list.Xsize * chr_textures_list.Ysize;
                bmpenvspec.write(reinterpret_cast<const char*>(&BMP_size), 4);						// Dimensione file BMP
                bmpenvspec << char(0x00) << char(0x00) << char(0x00) << char(0x00) << char(0x36) << char(0x04);
				bmpenvspec << char(0x00) << char(0x00) << char(0x28) << char(0x00) << char(0x00) << char(0x00);
                bmpenvspec.write(reinterpret_cast<const char*>(&chr_textures_list.Xsize), 4);		// DIMENSIONI DEI LATI DELLE TEXTURE
                bmpenvspec.write(reinterpret_cast<const char*>(&chr_textures_list.Ysize), 4);		// DIMENSIONI DEI LATI DELLE TEXTURE
                bmpenvspec << char(0x01) << char(0x00) << char(0x08) << char(0x00) << char(0x00) << char(0x00) << char(0x00) << char(0x00);
                bmpenvspec.write(reinterpret_cast<const char*>(&BMP_raw_size), 4);					// Dimensioni dati RAW texture
                for (int h = 0; h < 16; h++)
                    bmpenvspec << char(0x00);
                for (int h = 0; h < 256; h++)			// Questo ciclo scrive l'indice colori del BMP monocromatico
                {
                    bmpenvspec.write(reinterpret_cast<const char*>(&h), 1);
                    bmpenvspec.write(reinterpret_cast<const char*>(&h), 1);
                    bmpenvspec.write(reinterpret_cast<const char*>(&h), 1);
                    bmpenvspec << char(0x00);
                }
                bmpread.seekg(54, bmpread.beg);
                char* buffer1 = new char[3];
                char* buffer2 = new char[1];
                for (unsigned int b = 0; b < chr_textures_list.Xsize*chr_textures_list.Ysize; b++)		// Scrittura dati RAW di entrambe le textures
                {
                    bmpread.read(buffer1, 3);
                    bmpread.read(buffer2, 1);
                    bmpbump.write(buffer1, 3);
                    bmpenvspec.write(buffer2, 1);
                }
                delete[] buffer1;
                delete[] buffer2;
                bmpbump.close();
                bmpenvspec.close();
                bmpread.close();
                remove(FILENAME.c_str());
                FBX_Count->Texture += 2;
            }
        }

        else
            if (DXT == 21)															// ESPORTAZIONE E CONVERSIONE TEXTURE BMP
            {  
                stringstream INCREMENT_NAME, OUTFILE;
                INCREMENT_NAME << IO.chr_name << "_" << T << ".bmp";
                string FILENAME = INCREMENT_NAME.str();				// Il nome della texture
                ofstream bmp, bmpdiffuse, bmpfur;
                bmp.open(FILENAME.c_str(), ofstream::binary);
                bmp << char(0x42) << char(0x4d);					// Intestazione BMP
                int BMP_size(chr_textures_list.RAWsize + 54);
                bmp.write(reinterpret_cast<const char*>(&BMP_size), 4);								// Dimensione file BMP
                bmp << char(0x00) << char(0x00) << char(0x00) << char(0x00) << char(0x36) << char(0x00);
				bmp << char(0x00) << char(0x00) << char(0x28) << char(0x00) << char(0x00) << char(0x00);
                bmp.write(reinterpret_cast<const char*>(&chr_textures_list.Xsize), 4);				// DIMENSIONI DEI LATI DELLE TEXTURE
                bmp.write(reinterpret_cast<const char*>(&chr_textures_list.Ysize), 4);				// DIMENSIONI DEI LATI DELLE TEXTURE
                bmp << char(0x01) << char(0x00) << char(0x20) << char(0x00) << char(0x00) << char(0x00) << char(0x00) << char(0x00);
                bmp.write(reinterpret_cast<const char*>(&chr_textures_list.RAWsize), 4);			// Dimensioni dati RAW texture
                for (int h = 0; h < 16; h++)
                    bmp << char(0x00);
                char* buffer = new char[chr_textures_list.RAWsize];									// Buffer di lettura
                chrfile.read(buffer, chr_textures_list.RAWsize);									// Legge i dati raw della texture e li mette nel buffer
                bmp.write(buffer, chr_textures_list.RAWsize);										// Copia il buffer nel file di destinazione
                delete[] buffer;
                bmp.close();

                if (DXT == 21 && ColourBumpShadow == 5)								// TEXTURE ARGB, DIFFUSE COLOR + FUR. ENTRA 1 BMP, ESCONO 2 BMP
                {
                    ifstream bmpread(FILENAME.c_str(), std::ios::binary);	// Apre il file BMP convertito
                    OUTFILE << IO.chr_name << "_" << T << "_diffuse.bmp";
                    FILENAME = OUTFILE.str();
                    bmpdiffuse.open(FILENAME.c_str(), ofstream::binary);	// Prepara il nuovo file BMP 1/2
                    OUTFILE.str("");
                    OUTFILE.clear();
                    OUTFILE << IO.chr_name << "_" << T << "_fur.bmp";
                    FILENAME = OUTFILE.str();
                    bmpfur.open(FILENAME.c_str(), ofstream::binary);		// Prepara il nuovo file BMP 2/2

                    bmpdiffuse << char(0x42) << char(0x4d);					// Intestazione BMP 1/2 (DIFFUSE)
                    BMP_size = chr_textures_list.Xsize * chr_textures_list.Ysize * 3 + 54;	// X*Y*3 (numero pixels*24 bpp/8=dimensione in bytes)+54 (bytes header)
                    int BMP_raw_size(chr_textures_list.Xsize * chr_textures_list.Ysize * 3);
                    bmpdiffuse.write(reinterpret_cast<const char*>(&BMP_size), 4);					// Dimensione file BMP
                    bmpdiffuse << char(0x00) << char(0x00) << char(0x00) << char(0x00) << char(0x36) << char(0x00);
					bmpdiffuse << char(0x00) << char(0x00) << char(0x28) << char(0x00) << char(0x00) << char(0x00);
                    bmpdiffuse.write(reinterpret_cast<const char*>(&chr_textures_list.Xsize), 4);	// DIMENSIONI DEI LATI DELLE TEXTURE
                    bmpdiffuse.write(reinterpret_cast<const char*>(&chr_textures_list.Ysize), 4);	// DIMENSIONI DEI LATI DELLE TEXTURE
                    bmpdiffuse << char(0x01) << char(0x00) << char(0x18) << char(0x00) << char(0x00) << char(0x00) << char(0x00) << char(0x00);
                    bmpdiffuse.write(reinterpret_cast<const char*>(&BMP_raw_size), 4);				// Dimensioni dati RAW texture
                    for (int h = 0; h < 16; h++)
                        bmpdiffuse << char(0x00);

                    bmpfur << char(0x42) << char(0x4d);						// Intestazione BMP 2/2 (FUR)
                    BMP_size = chr_textures_list.Xsize * chr_textures_list.Ysize + 54 + 1024;// X*Y (numero pixels*8 bpp/8=dimensione in bytes)+54+1024 (bytes header e indici colori)
                    BMP_raw_size = chr_textures_list.Xsize * chr_textures_list.Ysize;
                    bmpfur.write(reinterpret_cast<const char*>(&BMP_size), 4);						// Dimensione file BMP
                    bmpfur << char(0x00) << char(0x00) << char(0x00) << char(0x00) << char(0x36) << char(0x04);
					bmpfur << char(0x00) << char(0x00) << char(0x28) << char(0x00) << char(0x00) << char(0x00);
                    bmpfur.write(reinterpret_cast<const char*>(&chr_textures_list.Xsize), 4);		// DIMENSIONI DEI LATI DELLE TEXTURE
                    bmpfur.write(reinterpret_cast<const char*>(&chr_textures_list.Ysize), 4);		// DIMENSIONI DEI LATI DELLE TEXTURE
                    bmpfur << char(0x01) << char(0x00) << char(0x08) << char(0x00) << char(0x00) << char(0x00) << char(0x00) << char(0x00);
                    bmpfur.write(reinterpret_cast<const char*>(&BMP_raw_size), 4);					// Dimensioni dati RAW texture
                    for (int h = 0; h < 16; h++)
                        bmpfur << char(0x00);
                    for (int h = 0; h < 256; h++)		// Questo ciclo scrive l'indice colori del BMP monocromatico
                    {
                        bmpfur.write(reinterpret_cast<const char*>(&h), 1);
                        bmpfur.write(reinterpret_cast<const char*>(&h), 1);
                        bmpfur.write(reinterpret_cast<const char*>(&h), 1);
                        bmpfur << char(0x00);
                    }
                    bmpread.seekg(54, bmpread.beg);
                    char* buffer1 = new char[3];
                    char* buffer2 = new char[1];
                    for (unsigned int b = 0; b < chr_textures_list.Xsize*chr_textures_list.Ysize; b++)	// Scrittura dati RAW di entrambe le textures
                    {
                        bmpread.read(buffer1, 3);
                        bmpread.read(buffer2, 1);
                        bmpdiffuse.write(buffer1, 3);
                        bmpfur.write(buffer2, 1);
                    }
                    delete[] buffer1;
                    delete[] buffer2;
                    bmpdiffuse.close();
                    bmpfur.close();
                    bmpread.close();
                    FBX_Count->Texture += 2;
                }
            }
            else
                chrfile.seekg(chr_textures_list.RAWsize, ios_base::cur);		// Se il tipo di texture è sconosciuto passa alla texture successiva
	}
	SetCurrentDirectory(IO.folder_chr_lpwstr);
	SetConsoleTitle(IO.Console_NewTitle);			// Imposta il nome del programma nella barra della console di Windows
    chrfile.seekg(original_position);				// Riporta il cursore di lettura dove si trovava prima di entrare in questa funzione
}