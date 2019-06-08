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
Scrittura dati texture
INPUT: IO_CLASS IO, TextureHeader *TextureHeader
OUTPUT: ofstream &out
------------------------------------------------------------------------------------------------------------------*/

#include "stdafx.h"
#include "Classes.h"
#include "FBX/FBX_Functions.h"


void FBX_Write_Texture (IO_CLASS IO, TextureHeader *TextureHeader, ofstream &out)
{
	int t = TextureHeader->Number;					// Numero della texture in corso di scrittura
    int DXT = TextureHeader->DXT;					// BMP = 0, DXT1 = 1, DXT3 = 3, DXT5 = 5 
    int Mode = TextureHeader->ColourBumpShadow;		// Shadowmap = 1, diffusemap = 2, bumpmap = 4, fur = 5

    if (DXT == 1 && Mode == 2)
    {
        out << "	Texture: " << nodeID(23,t) << ", \"Texture::" << IO.chr_name << "_" << t << "_diffuse\", \"\" {\n";
        out << "		Type: \"TextureVideoClip\"\n";
        out << "		Version: 202\n";
        out << "		TextureName: \"Texture::" << IO.chr_name << "_" << t << "_diffuse\"\n";
        out << "		Properties70:  {\n";
        out << "			P: \"UVSet\", \"KString\", \"\", \"\", \"UVChannel_1\"\n";
        out << "			P: \"UseMaterial\", \"bool\", \"\", \"\",1\n";
        out << "		}\n";
        out << "		FileName: \"" << IO.fbx_folder << IO.chr_name << "_" << t << "_diffuse.bmp\"\n";
        out << "		ModelUVTranslation: 0,0\n";
        out << "		ModelUVScaling: 1,1\n";
        out << "		Texture_Alpha_Source: \"None\"\n";
        out << "		Cropping: 0,0,0,0\n";
        out << "	}\n";
    }

    if ((DXT == 3 || DXT == 5) && Mode == 2)
    {
        out << "	Texture: " << nodeID(23,t) << ", \"Texture::" << IO.chr_name << "_" << t << "_diffuse\", \"\" {\n";
        out << "		Type: \"TextureVideoClip\"\n";
        out << "		Version: 202\n";
        out << "		TextureName: \"Texture::" << IO.chr_name << "_" << t << "_diffuse\"\n";
        out << "		Properties70:  {\n";
        out << "			P: \"UVSet\", \"KString\", \"\", \"\", \"UVChannel_1\"\n";
        out << "			P: \"UseMaterial\", \"bool\", \"\", \"\",1\n";
        out << "		}\n";
        out << "		FileName: \"" << IO.fbx_folder << IO.chr_name << "_" << t << "_diffuse.bmp\"\n";
        out << "		ModelUVTranslation: 0,0\n";
        out << "		ModelUVScaling: 1,1\n";
        out << "		Texture_Alpha_Source: \"None\"\n";
        out << "		Cropping: 0,0,0,0\n";
        out << "	}\n";

        out << "	Texture: " << nodeID(24,t) << ", \"Texture::" << IO.chr_name << "_" << t << "_transparency\", \"\" {\n";
        out << "		Type: \"TextureVideoClip\"\n";
        out << "		Version: 202\n";
        out << "		TextureName: \"Texture::" << IO.chr_name << "_" << t << "_transparency\"\n";
        out << "		Properties70:  {\n";
        out << "			P: \"UVSet\", \"KString\", \"\", \"\", \"UVChannel_1\"\n";
        out << "			P: \"UseMaterial\", \"bool\", \"\", \"\",1\n";
        out << "		}\n";
        out << "		FileName: \"" << IO.fbx_folder << IO.chr_name << "_" << t << "_transparency.bmp\"\n";
        out << "		ModelUVTranslation: 0,0\n";
        out << "		ModelUVScaling: 1,1\n";
        out << "		Texture_Alpha_Source: \"None\"\n";
        out << "		Cropping: 0,0,0,0\n";
        out << "	}\n";
    }

    if (DXT == 1 && Mode == 4)
    {
        out << "	Texture: " << nodeID(23,t) << ", \"Texture::" << IO.chr_name << "_" << t << "_bump\", \"\" {\n";
        out << "		Type: \"TextureVideoClip\"\n";
        out << "		Version: 202\n";
        out << "		TextureName: \"Texture::" << IO.chr_name << "_" << t << "_bump\"\n";
        out << "		Properties70:  {\n";
        out << "			P: \"UVSet\", \"KString\", \"\", \"\", \"UVChannel_1\"\n";
        out << "			P: \"UseMaterial\", \"bool\", \"\", \"\",1\n";
        out << "		}\n";
        out << "		FileName: \"" << IO.fbx_folder << IO.chr_name << "_" << t << "_bump.bmp\"\n";
        out << "		ModelUVTranslation: 0,0\n";
        out << "		ModelUVScaling: 1,1\n";
        out << "		Texture_Alpha_Source: \"None\"\n";
        out << "		Cropping: 0,0,0,0\n";
        out << "	}\n";
    }

    if ((DXT == 3 || DXT == 5) && Mode == 4)
    {
        out << "	Texture: " << nodeID(23,t) << ", \"Texture::" << IO.chr_name << "_" << t << "_bump\", \"\" {\n";
        out << "		Type: \"TextureVideoClip\"\n";
        out << "		Version: 202\n";
        out << "		TextureName: \"Texture::" << IO.chr_name << "_" << t << "_bump\"\n";
        out << "		Properties70:  {\n";
        out << "			P: \"UVSet\", \"KString\", \"\", \"\", \"UVChannel_1\"\n";
        out << "			P: \"UseMaterial\", \"bool\", \"\", \"\",1\n";
        out << "		}\n";
        out << "		FileName: \"" << IO.fbx_folder << IO.chr_name << "_" << t << "_bump.bmp\"\n";
        out << "		ModelUVTranslation: 0,0\n";
        out << "		ModelUVScaling: 1,1\n";
        out << "		Texture_Alpha_Source: \"None\"\n";
        out << "		Cropping: 0,0,0,0\n";
        out << "	}\n";

        out << "	Texture: " << nodeID(24,t) << ", \"Texture::" << IO.chr_name << "_" << t << "_envspec\", \"\" {\n";
        out << "		Type: \"TextureVideoClip\"\n";
        out << "		Version: 202\n";
        out << "		TextureName: \"Texture::" << IO.chr_name << "_" << t << "_envspec\"\n";
        out << "		Properties70:  {\n";
        out << "			P: \"UVSet\", \"KString\", \"\", \"\", \"UVChannel_1\"\n";
        out << "			P: \"UseMaterial\", \"bool\", \"\", \"\",1\n";
        out << "		}\n";
        out << "		FileName: \"" << IO.fbx_folder << IO.chr_name << "_" << t << "_envspec.bmp\"\n";
        out << "		ModelUVTranslation: 0,0\n";
        out << "		ModelUVScaling: 1,1\n";
        out << "		Texture_Alpha_Source: \"None\"\n";
        out << "		Cropping: 0,0,0,0\n";
        out << "	}\n";
    }

    if (DXT == 0 && Mode == 5)
    {
        out << "	Texture: " << nodeID(23,t) << ", \"Texture::" << IO.chr_name << "_" << t << "_diffuse\", \"\" {\n";
        out << "		Type: \"TextureVideoClip\"\n";
        out << "		Version: 202\n";
        out << "		TextureName: \"Texture::" << IO.chr_name << "_" << t << "_diffuse\"\n";
        out << "		Properties70:  {\n";
        out << "			P: \"UVSet\", \"KString\", \"\", \"\", \"UVChannel_1\"\n";
        out << "			P: \"UseMaterial\", \"bool\", \"\", \"\",1\n";
        out << "		}\n";
        out << "		FileName: \"" << IO.fbx_folder << IO.chr_name << "_" << t << "_diffuse.bmp\"\n";
        out << "		ModelUVTranslation: 0,0\n";
        out << "		ModelUVScaling: 1,1\n";
        out << "		Texture_Alpha_Source: \"None\"\n";
        out << "		Cropping: 0,0,0,0\n";
        out << "	}\n";

        out << "	Texture: " << nodeID(24,t) << ", \"Texture::" << IO.chr_name << "_" << t << "_fur\", \"\" {\n";
        out << "		Type: \"TextureVideoClip\"\n";
        out << "		Version: 202\n";
        out << "		TextureName: \"Texture::" << IO.chr_name << "_" << t << "_fur\"\n";
        out << "		Properties70:  {\n";
        out << "			P: \"UVSet\", \"KString\", \"\", \"\", \"UVChannel_1\"\n";
        out << "			P: \"UseMaterial\", \"bool\", \"\", \"\",1\n";
        out << "		}\n";
        out << "		FileName: \"" << IO.fbx_folder << IO.chr_name << "_" << t << "_fur.bmp\"\n";
        out << "		ModelUVTranslation: 0,0\n";
        out << "		ModelUVScaling: 1,1\n";
        out << "		Texture_Alpha_Source: \"None\"\n";
        out << "		Cropping: 0,0,0,0\n";
        out << "	}\n";
    }
}