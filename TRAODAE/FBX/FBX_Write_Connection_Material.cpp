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
Scrittura Connections dei materiali
INPUT: vector <TextureHeader> &TextureHeader, Material *Materials
OUTPUT: ofstream &out
------------------------------------------------------------------------------------------------------------------*/

#include "stdafx.h"
#include "Classes.h"
#include "FBX/FBX_Functions.h"


void FBX_Write_Connection_Material (vector <TextureHeader> &TextureHeader, Material *Materials, ofstream &out)
{
    int d, b, m;
	m = Materials->Number;
    switch (Materials->Type)
    {
    case(0):	// NONE (con Depth Of Field)
	case(1):	// NONE (senza Depth Of Field)
	case(3):	// NONE (senza Depth Of Field)
        break;

    case(4):	// DIFFUSE (con Depth Of Field)
	case(5):	// DIFFUSE (senza Depth Of Field)
	case(7):	// DIFFUSE (senza Depth Of Field)
        d = Materials->Diffuse;
        if (d < 0)	break;
        out << "	C: \"OP\"," << nodeID(23,d) << "," << nodeID(21,m) << ", \"DiffuseColor\"\n";					// Texture 1, Material
        if (TextureHeader[d].DXT == 3 || TextureHeader[d].DXT == 5)
            out << "	C: \"OP\"," << nodeID(24,d) << "," << nodeID(21,m) << ", \"TransparentColor\"\n";					// Texture 2, Material
        break;

    case(8):	// BUMP (con Depth Of Field)
	case(9):	// BUMP (senza Depth Of Field)
	case(11):	// BUMP (senza Depth Of Field)
        b = Materials->BumpSpec;
        if (b < 0)	break;
        out << "	C: \"OP\"," << nodeID(23,b) << "," << nodeID(21,m) << ", \"Bump\"\n";							// Texture 1, Material
        break;

    case(12):   // DIFFUSE + BUMP (con Depth Of Field)
	case(13):   // DIFFUSE + BUMP (senza Depth Of Field)
	case(15):   // DIFFUSE + BUMP (senza Depth Of Field)
        d = Materials->Diffuse;
        if (d < 0)	break;
        out << "	C: \"OP\"," << nodeID(23,d) << "," << nodeID(21,m) << ", \"DiffuseColor\"\n";					// Texture 1, Material
        if (TextureHeader[d].DXT == 3 || TextureHeader[d].DXT == 5)
            out << "	C: \"OP\"," << nodeID(24,d) << "," << nodeID(21,m) << ", \"TransparentColor\"\n";					// Texture 2, Material
        b = Materials->BumpSpec;
        if (b < 0)	break;
        out << "	C: \"OP\"," << nodeID(23,b) << "," << nodeID(21,m) << ", \"Bump\"\n";							// Texture 1, Material
        break;

    case(36):	// DIFFUSE + SPECULAR (con Depth Of Field)
	case(37):	// DIFFUSE + SPECULAR (senza Depth Of Field)
	case(39):	// DIFFUSE + SPECULAR (senza Depth Of Field)
        d = Materials->Diffuse;
        if (d < 0)	break;
        out << "	C: \"OP\"," << nodeID(23,d) << "," << nodeID(21,m) << ", \"DiffuseColor\"\n";					// Texture 1, Material
        if (TextureHeader[d].DXT == 3 || TextureHeader[d].DXT == 5)
            out << "	C: \"OP\"," << nodeID(24,d) << "," << nodeID(21,m) << ", \"TransparentColor\"\n";					// Texture 2, Material
        b = Materials->BumpSpec;
        if (b < 0)	break;
        out << "	C: \"OP\"," << nodeID(24,b) << "," << nodeID(21,m) << ", \"SpecularColor\"\n";							// Texture 2, Material
        break;

    case(44):	// DIFFUSE + BUMP + SPECULAR (con Depth Of Field)
	case(45):	// DIFFUSE + BUMP + SPECULAR (senza Depth Of Field)
	case(47):	// DIFFUSE + BUMP + SPECULAR (senza Depth Of Field)
        d = Materials->Diffuse;
        if (d < 0)	break;
        out << "	C: \"OP\"," << nodeID(23,d) << "," << nodeID(21,m) << ", \"DiffuseColor\"\n";					// Texture 1, Material
        if (TextureHeader[d].DXT == 3 || TextureHeader[d].DXT == 5)
            out << "	C: \"OP\"," << nodeID(24,d) << "," << nodeID(21,m) << ", \"TransparentColor\"\n";					// Texture 2, Material
        b = Materials->BumpSpec;
        if (b < 0)	break;
        out << "	C: \"OP\"," << nodeID(23,b) << "," << nodeID(21,m) << ", \"Bump\"\n";							// Texture 1, Material
        out << "	C: \"OP\"," << nodeID(24,b) << "," << nodeID(21,m) << ", \"SpecularColor\"\n";							// Texture 2, Material
        break;

    case(68):	// DIFFUSE + ENVELOPE (con Depth Of Field)
	case(69):	// DIFFUSE + ENVELOPE (senza Depth Of Field)
	case(71):	// DIFFUSE + ENVELOPE (senza Depth Of Field)
        d = Materials->Diffuse;
        if (d < 0)	break;
        out << "	C: \"OP\"," << nodeID(23,d) << "," << nodeID(21,m) << ", \"DiffuseColor\"\n";					// Texture 1, Material
        if (TextureHeader[d].DXT == 3 || TextureHeader[d].DXT == 5)
            out << "	C: \"OP\"," << nodeID(24,d) << "," << nodeID(21,m) << ", \"TransparentColor\"\n";					// Texture 2, Material
        b = Materials->BumpSpec;
        if (b < 0)	break;
        out << "	C: \"OP\"," << nodeID(24,b) << "," << nodeID(21,m) << ", \"ReflectionFactor\"\n";						// Texture 2, Material
        break;

    case(76):	// DIFFUSE + ENVELOPE + BUMP (con Depth Of Field)
	case(77):	// DIFFUSE + ENVELOPE + BUMP (senza Depth Of Field)
	case(79):	// DIFFUSE + ENVELOPE + BUMP (senza Depth Of Field)
        d = Materials->Diffuse;
        if (d < 0)	break;
        out << "	C: \"OP\"," << nodeID(23,d) << "," << nodeID(21,m) << ", \"DiffuseColor\"\n";					// Texture 1, Material
        if (TextureHeader[d].DXT == 3 || TextureHeader[d].DXT == 5)
            out << "	C: \"OP\"," << nodeID(24,d) << "," << nodeID(21,m) << ", \"TransparentColor\"\n";					// Texture 2, Material
        b = Materials->BumpSpec;
        if (b < 0)	break;
        out << "	C: \"OP\"," << nodeID(23,b) << "," << nodeID(21,m) << ", \"Bump\"\n";							// Texture 1, Material
        out << "	C: \"OP\"," << nodeID(24,b) << "," << nodeID(21,m) << ", \"ReflectionFactor\"\n";						// Texture 2, Material
        break;

    case(100):  // DIFFUSE + ENVELOPE + SPECULAR (con Depth Of Field)
	case(101):  // DIFFUSE + ENVELOPE + SPECULAR (senza Depth Of Field)
	case(103):  // DIFFUSE + ENVELOPE + SPECULAR (senza Depth Of Field)
        d = Materials->Diffuse;
        if (d < 0)	break;
        out << "	C: \"OP\"," << nodeID(23,d) << "," << nodeID(21,m) << ", \"DiffuseColor\"\n";					// Texture 1, Material
        if (TextureHeader[d].DXT == 3 || TextureHeader[d].DXT == 5)
            out << "	C: \"OP\"," << nodeID(24,d) << "," << nodeID(21,m) << ", \"TransparentColor\"\n";					// Texture 2, Material
        b = Materials->BumpSpec;
        if (b < 0)	break;
        out << "	C: \"OP\"," << nodeID(24,b) << "," << nodeID(21,m) << ", \"ReflectionFactor\"\n";						// Texture 2, Material
        out << "	C: \"OP\"," << nodeID(24,b) << "," << nodeID(21,m) << ", \"SpecularColor\"\n";							// Texture 2, Material
        break;

    case(108):	// DIFFUSE + ENVELOPE + BUMP + SPECULAR (con Depth Of Field)
	case(109):	// DIFFUSE + ENVELOPE + BUMP + SPECULAR (senza Depth Of Field)
	case(111):	// DIFFUSE + ENVELOPE + BUMP + SPECULAR (senza Depth Of Field)
        d = Materials->Diffuse;
        if (d < 0)	break;
        out << "	C: \"OP\"," << nodeID(23,d) << "," << nodeID(21,m) << ", \"DiffuseColor\"\n";					// Texture 1, Material
        if (TextureHeader[d].DXT == 3 || TextureHeader[d].DXT == 5)
            out << "	C: \"OP\"," << nodeID(24,d) << "," << nodeID(21,m) << ", \"TransparentColor\"\n";					// Texture 2, Material
        b = Materials->BumpSpec;
        if (b < 0)	break;
        out << "	C: \"OP\"," << nodeID(23,b) << "," << nodeID(21,m) << ", \"Bump\"\n";							// Texture 1, Material
        out << "	C: \"OP\"," << nodeID(24,b) << "," << nodeID(21,m) << ", \"ReflectionFactor\"\n";						// Texture 2, Material
        out << "	C: \"OP\"," << nodeID(24,b) << "," << nodeID(21,m) << ", \"SpecularColor\"\n";							// Texture 2, Material
        break;

    case(144):  // SKIN (DIFFUSE + BUMP + SPECULAR + AMBIENT) (con Depth Of Field)
	case(145):  // SKIN (DIFFUSE + BUMP + SPECULAR + AMBIENT) (senza Depth Of Field)
	case(147):  // SKIN (DIFFUSE + BUMP + SPECULAR + AMBIENT) (senza Depth Of Field)
        d = Materials->Diffuse;
        if (d < 0)	break;
        out << "	C: \"OP\"," << nodeID(23,d) << "," << nodeID(21,m) << ", \"DiffuseColor\"\n";					// Texture 1, Material
        if (TextureHeader[d].DXT == 3 || TextureHeader[d].DXT == 5)
            out << "	C: \"OP\"," << nodeID(24,d) << "," << nodeID(21,m) << ", \"TransparentColor\"\n";					// Texture 2, Material
        b = Materials->BumpSpec;
        if (b < 0)	break;
        out << "	C: \"OP\"," << nodeID(23,b) << "," << nodeID(21,m) << ", \"Bump\"\n";							// Texture 1, Material
        out << "	C: \"OP\"," << nodeID(24,b) << "," << nodeID(21,m) << ", \"AmbientColor\"\n";							// Texture 2, Material
        out << "	C: \"OP\"," << nodeID(24,b) << "," << nodeID(21,m) << ", \"SpecularColor\"\n";							// Texture 2, Material
        break;

    default:
        d = Materials->Diffuse;
        if (d < 0)	break;
        out << "	C: \"OP\"," << nodeID(23,d) << "," << nodeID(21,m) << ", \"DiffuseColor\"\n";					// Texture 1, Material
        if (TextureHeader[d].DXT == 3 || TextureHeader[d].DXT == 5)
            out << "	C: \"OP\"," << nodeID(24,d) << "," << nodeID(21,m) << ", \"TransparentColor\"\n";					// Texture 2, Material
        break;
    }
}