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
Scrittura materiale
INPUT: Material *Materials, unsigned int *Nlambert, unsigned int *Nphong
OUTPUT: unsigned int *Nlambert, unsigned int *Nphong, ofstream &out
------------------------------------------------------------------------------------------------------------------*/

#include "stdafx.h"
#include "Classes.h"
#include "FBX/FBX_Functions.h"


void FBX_Write_Material (Material *Materials, unsigned int *Nlambert, unsigned int *Nphong, ofstream &out)
{
	int m = Materials->Number;						// Numero del materiale in corso di scrittura
    switch (Materials->Type)
    {
    case(0):	// NONE (con Depth Of Field)
	case(1):	// NONE (senza Depth Of Field)
	case(3):	// NONE (senza Depth Of Field)
        out << "	Material: " << nodeID(21,m) << ", \"Material::Mt" << m+1 << "_none_lambert" << *Nlambert << "\", \"\" {\n";
        out << "		Version: 102\n";
        out << "		ShadingModel: \"lambert\"\n";
        out << "		MultiLayer: 0\n";
        out << "		Properties70:  {\n";
		out << "			P: \"AmbientColor\", \"ColorRGB\", \"Color\", \"\",0,0,0\n";
		out << "			P: \"DiffuseColor\", \"ColorRGB\", \"Color\", \"\",0.5,0.5,0.5\n";
		out << "			P: \"TransparencyFactor\", \"double\", \"Number\", \"\",1\n";
		out << "			P: \"Emissive\", \"Vector3D\", \"Vector\", \"\",0,0,0\n";
		out << "			P: \"Ambient\", \"Vector3D\", \"Vector\", \"\",0,0,0\n";
		out << "			P: \"Diffuse\", \"Vector3D\", \"Vector\", \"\",0.5,0.5,0.5\n";
		out << "			P: \"Opacity\", \"double\", \"Number\", \"\",1\n";
        out << "		}\n";
        out << "	}\n";
        (*Nlambert)++;
        break;

    case(4):	// DIFFUSE (con Depth Of Field)
	case(5):	// DIFFUSE (senza Depth Of Field)
	case(7):	// DIFFUSE (senza Depth Of Field)
        out << "	Material: " << nodeID(21,m) << ", \"Material::Mt" << m+1 << "_diffuse_lambert" << *Nlambert << "\", \"\" {\n";
        out << "		Version: 102\n";
        out << "		ShadingModel: \"lambert\"\n";
        out << "		MultiLayer: 0\n";
        out << "		Properties70:  {\n";
		out << "			P: \"AmbientColor\", \"ColorRGB\", \"Color\", \"\",0,0,0\n";
		out << "			P: \"DiffuseColor\", \"ColorRGB\", \"Color\", \"\",1,1,1\n";
		out << "			P: \"TransparencyFactor\", \"double\", \"Number\", \"\",1\n";
		out << "			P: \"Emissive\", \"Vector3D\", \"Vector\", \"\",0,0,0\n";
		out << "			P: \"Ambient\", \"Vector3D\", \"Vector\", \"\",0,0,0\n";
		out << "			P: \"Diffuse\", \"Vector3D\", \"Vector\", \"\",1,1,1\n";
		out << "			P: \"Opacity\", \"double\", \"Number\", \"\",1\n";
        out << "		}\n";
        out << "	}\n";
        (*Nlambert)++;
        break;

    case(8):	// BUMP (con Depth Of Field)
	case(9):	// BUMP (senza Depth Of Field)
	case(11):	// BUMP (senza Depth Of Field)
        out << "	Material: " << nodeID(21,m) << ", \"Material::Mt" << m+1 << "_bump_lambert" << *Nlambert << "\", \"\" {\n";
        out << "		Version: 102\n";
        out << "		ShadingModel: \"lambert\"\n";
        out << "		MultiLayer: 0\n";
        out << "		Properties70:  {\n";
		out << "			P: \"AmbientColor\", \"ColorRGB\", \"Color\", \"\",0,0,0\n";
		out << "			P: \"DiffuseColor\", \"ColorRGB\", \"Color\", \"\",0.5,0.5,0.5\n";
		out << "			P: \"BumpFactor\", \"double\", \"Number\", \"\",0.150000005960464\n";
		out << "			P: \"TransparencyFactor\", \"double\", \"Number\", \"\",1\n";
		out << "			P: \"Emissive\", \"Vector3D\", \"Vector\", \"\",0,0,0\n";
		out << "			P: \"Ambient\", \"Vector3D\", \"Vector\", \"\",0,0,0\n";
		out << "			P: \"Diffuse\", \"Vector3D\", \"Vector\", \"\",0.5,0.5,0.5\n";
		out << "			P: \"Opacity\", \"double\", \"Number\", \"\",1\n";
        out << "		}\n";
        out << "	}\n";
        (*Nlambert)++;
        break;

    case(12):   // DIFFUSE + BUMP (con Depth Of Field)
	case(13):   // DIFFUSE + BUMP (senza Depth Of Field)
	case(15):   // DIFFUSE + BUMP (senza Depth Of Field)
        out << "	Material: " << nodeID(21,m) << ", \"Material::Mt" << m+1 << "_diffusebump_lambert" << *Nlambert << "\", \"\" {\n";
        out << "		Version: 102\n";
        out << "		ShadingModel: \"lambert\"\n";
        out << "		MultiLayer: 0\n";
        out << "		Properties70:  {\n";
		out << "			P: \"AmbientColor\", \"ColorRGB\", \"Color\", \"\",0,0,0\n";
		out << "			P: \"DiffuseColor\", \"ColorRGB\", \"Color\", \"\",1,1,1\n";
		out << "			P: \"BumpFactor\", \"double\", \"Number\", \"\",0.150000005960464\n";
		out << "			P: \"TransparencyFactor\", \"double\", \"Number\", \"\",1\n";
		out << "			P: \"Emissive\", \"Vector3D\", \"Vector\", \"\",0,0,0\n";
		out << "			P: \"Ambient\", \"Vector3D\", \"Vector\", \"\",0,0,0\n";
		out << "			P: \"Diffuse\", \"Vector3D\", \"Vector\", \"\",1,1,1\n";
		out << "			P: \"Opacity\", \"double\", \"Number\", \"\",1\n";
        out << "		}\n";
        out << "	}\n";
        (*Nlambert)++;
        break;

    case(36):	// DIFFUSE + SPECULAR (con Depth Of Field)
	case(37):	// DIFFUSE + SPECULAR (senza Depth Of Field)
	case(39):	// DIFFUSE + SPECULAR (senza Depth Of Field)
        out << "	Material: " << nodeID(21,m) << ", \"Material::Mt" << m+1 << "_diffusespec_phong" << *Nphong << "\", \"\" {\n";
        out << "		Version: 102\n";
        out << "		ShadingModel: \"phong\"\n";
        out << "		MultiLayer: 0\n";
        out << "		Properties70:  {\n";
		out << "			P: \"AmbientColor\", \"ColorRGB\", \"Color\", \"\",0,0,0\n";
		out << "			P: \"DiffuseColor\", \"ColorRGB\", \"Color\", \"\",1,1,1\n";
		out << "			P: \"TransparencyFactor\", \"double\", \"Number\", \"\",1\n";
		out << "			P: \"SpecularColor\", \"ColorRGB\", \"Color\", \"\",0.5,0.5,0.5\n";
		out << "			P: \"ShininessExponent\", \"double\", \"Number\", \"\",100\n";
		out << "			P: \"ReflectionFactor\", \"double\", \"Number\", \"\",0\n";
		out << "			P: \"Emissive\", \"Vector3D\", \"Vector\", \"\",0,0,0\n";
		out << "			P: \"Ambient\", \"Vector3D\", \"Vector\", \"\",0,0,0\n";
		out << "			P: \"Diffuse\", \"Vector3D\", \"Vector\", \"\",1,1,1\n";
		out << "			P: \"Specular\", \"Vector3D\", \"Vector\", \"\",0.5,0.5,0.5\n";
		out << "			P: \"Shininess\", \"double\", \"Number\", \"\",100\n";
		out << "			P: \"Opacity\", \"double\", \"Number\", \"\",1\n";
		out << "			P: \"Reflectivity\", \"double\", \"Number\", \"\",0\n";
		out << "		}\n";
        out << "	}\n";
        (*Nphong)++;
        break;

    case(44):	// DIFFUSE + BUMP + SPECULAR (con Depth Of Field)
	case(45):	// DIFFUSE + BUMP + SPECULAR (senza Depth Of Field)
	case(47):	// DIFFUSE + BUMP + SPECULAR (senza Depth Of Field)
        out << "	Material: " << nodeID(21,m) << ", \"Material::Mt" << m+1 << "_diffusebumpspec_phong" << *Nphong << "\", \"\" {\n";
        out << "		Version: 102\n";
        out << "		ShadingModel: \"phong\"\n";
        out << "		MultiLayer: 0\n";
        out << "		Properties70:  {\n";
		out << "			P: \"AmbientColor\", \"ColorRGB\", \"Color\", \"\",0,0,0\n";
		out << "			P: \"DiffuseColor\", \"ColorRGB\", \"Color\", \"\",1,1,1\n";
		out << "			P: \"BumpFactor\", \"double\", \"Number\", \"\",0.150000005960464\n";
		out << "			P: \"TransparencyFactor\", \"double\", \"Number\", \"\",1\n";
		out << "			P: \"SpecularColor\", \"ColorRGB\", \"Color\", \"\",0.5,0.5,0.5\n";
		out << "			P: \"ShininessExponent\", \"double\", \"Number\", \"\",100\n";
		out << "			P: \"ReflectionFactor\", \"double\", \"Number\", \"\",0\n";
		out << "			P: \"Emissive\", \"Vector3D\", \"Vector\", \"\",0,0,0\n";
		out << "			P: \"Ambient\", \"Vector3D\", \"Vector\", \"\",0,0,0\n";
		out << "			P: \"Diffuse\", \"Vector3D\", \"Vector\", \"\",1,1,1\n";
		out << "			P: \"Specular\", \"Vector3D\", \"Vector\", \"\",0.5,0.5,0.5\n";
		out << "			P: \"Shininess\", \"double\", \"Number\", \"\",100\n";
		out << "			P: \"Opacity\", \"double\", \"Number\", \"\",1\n";
		out << "			P: \"Reflectivity\", \"double\", \"Number\", \"\",0\n";
		out << "		}\n";
        out << "	}\n";
        (*Nphong)++;
        break;

    case(68):	// DIFFUSE + ENVELOPE (con Depth Of Field)
	case(69):	// DIFFUSE + ENVELOPE (senza Depth Of Field)
	case(71):	// DIFFUSE + ENVELOPE (senza Depth Of Field)
        out << "	Material: " << nodeID(21,m) << ", \"Material::Mt" << m+1 << "_diffuseenv_phong" << *Nphong << "\", \"\" {\n";
        out << "		Version: 102\n";
        out << "		ShadingModel: \"phong\"\n";
        out << "		MultiLayer: 0\n";
        out << "		Properties70:  {\n";
		out << "			P: \"AmbientColor\", \"ColorRGB\", \"Color\", \"\",0,0,0\n";
		out << "			P: \"DiffuseColor\", \"ColorRGB\", \"Color\", \"\",1,1,1\n";
		out << "			P: \"TransparencyFactor\", \"double\", \"Number\", \"\",1\n";
		out << "			P: \"SpecularColor\", \"ColorRGB\", \"Color\", \"\",1,1,1\n";
		out << "			P: \"ShininessExponent\", \"double\", \"Number\", \"\",100\n";
		out << "			P: \"ReflectionFactor\", \"double\", \"Number\", \"\",0.5\n";
		out << "			P: \"Emissive\", \"Vector3D\", \"Vector\", \"\",0,0,0\n";
		out << "			P: \"Ambient\", \"Vector3D\", \"Vector\", \"\",0,0,0\n";
		out << "			P: \"Diffuse\", \"Vector3D\", \"Vector\", \"\",1,1,1\n";
		out << "			P: \"Specular\", \"Vector3D\", \"Vector\", \"\",1,1,1\n";
		out << "			P: \"Shininess\", \"double\", \"Number\", \"\",100\n";
		out << "			P: \"Opacity\", \"double\", \"Number\", \"\",1\n";
		out << "			P: \"Reflectivity\", \"double\", \"Number\", \"\",0\n";
		out << "		}\n";
        out << "	}\n";
        (*Nphong)++;
        break;

    case(76):	// DIFFUSE + ENVELOPE + BUMP (con Depth Of Field)
	case(77):	// DIFFUSE + ENVELOPE + BUMP (senza Depth Of Field)
	case(79):	// DIFFUSE + ENVELOPE + BUMP (senza Depth Of Field)
        out << "	Material: " << nodeID(21,m) << ", \"Material::Mt" << m+1 << "_diffuseenvbump_phong" << *Nphong << "\", \"\" {\n";
        out << "		Version: 102\n";
        out << "		ShadingModel: \"phong\"\n";
        out << "		MultiLayer: 0\n";
        out << "		Properties70:  {\n";
		out << "			P: \"AmbientColor\", \"ColorRGB\", \"Color\", \"\",0,0,0\n";
		out << "			P: \"DiffuseColor\", \"ColorRGB\", \"Color\", \"\",1,1,1\n";
		out << "			P: \"BumpFactor\", \"double\", \"Number\", \"\",0.150000005960464\n";
		out << "			P: \"TransparencyFactor\", \"double\", \"Number\", \"\",1\n";
		out << "			P: \"SpecularColor\", \"ColorRGB\", \"Color\", \"\",1,1,1\n";
		out << "			P: \"ShininessExponent\", \"double\", \"Number\", \"\",100\n";
		out << "			P: \"ReflectionFactor\", \"double\", \"Number\", \"\",0.5\n";
		out << "			P: \"Emissive\", \"Vector3D\", \"Vector\", \"\",0,0,0\n";
		out << "			P: \"Ambient\", \"Vector3D\", \"Vector\", \"\",0,0,0\n";
		out << "			P: \"Diffuse\", \"Vector3D\", \"Vector\", \"\",1,1,1\n";
		out << "			P: \"Specular\", \"Vector3D\", \"Vector\", \"\",1,1,1\n";
		out << "			P: \"Shininess\", \"double\", \"Number\", \"\",100\n";
		out << "			P: \"Opacity\", \"double\", \"Number\", \"\",1\n";
		out << "			P: \"Reflectivity\", \"double\", \"Number\", \"\",0\n";
		out << "		}\n";
        out << "	}\n";
        (*Nphong)++;
        break;

    case(100):  // DIFFUSE + ENVELOPE + SPECULAR (con Depth Of Field)
	case(101):  // DIFFUSE + ENVELOPE + SPECULAR (senza Depth Of Field)
	case(103):  // DIFFUSE + ENVELOPE + SPECULAR (senza Depth Of Field)
        out << "	Material: " << nodeID(21,m) << ", \"Material::Mt" << m+1 << "_diffuseenvspec_phong" << *Nphong << "\", \"\" {\n";
        out << "		Version: 102\n";
        out << "		ShadingModel: \"phong\"\n";
        out << "		MultiLayer: 0\n";
        out << "		Properties70:  {\n";
		out << "			P: \"AmbientColor\", \"ColorRGB\", \"Color\", \"\",0,0,0\n";
		out << "			P: \"DiffuseColor\", \"ColorRGB\", \"Color\", \"\",1,1,1\n";
		out << "			P: \"TransparencyFactor\", \"double\", \"Number\", \"\",1\n";
		out << "			P: \"SpecularColor\", \"ColorRGB\", \"Color\", \"\",0.5,0.5,0.5\n";
		out << "			P: \"ReflectionFactor\", \"double\", \"Number\", \"\",0.5\n";
		out << "			P: \"Emissive\", \"Vector3D\", \"Vector\", \"\",0,0,0\n";
		out << "			P: \"Ambient\", \"Vector3D\", \"Vector\", \"\",0,0,0\n";
		out << "			P: \"Diffuse\", \"Vector3D\", \"Vector\", \"\",1,1,1\n";
		out << "			P: \"Specular\", \"Vector3D\", \"Vector\", \"\",0.5,0.5,0.5\n";
		out << "			P: \"Shininess\", \"double\", \"Number\", \"\",20\n";
		out << "			P: \"Opacity\", \"double\", \"Number\", \"\",1\n";
		out << "			P: \"Reflectivity\", \"double\", \"Number\", \"\",0\n";
		out << "		}\n";
        out << "	}\n";
        (*Nphong)++;
        break;

	case(108):	// DIFFUSE + ENVELOPE + BUMP + SPECULAR (con Depth Of Field)
	case(109):	// DIFFUSE + ENVELOPE + BUMP + SPECULAR (senza Depth Of Field)
	case(111):	// DIFFUSE + ENVELOPE + BUMP + SPECULAR (senza Depth Of Field)
        out << "	Material: " << nodeID(21,m) << ", \"Material::Mt" << m+1 << "_diffuseenvbumpspec_phong" << *Nphong << "\", \"\" {\n";
        out << "		Version: 102\n";
        out << "		ShadingModel: \"phong\"\n";
        out << "		MultiLayer: 0\n";
        out << "		Properties70:  {\n";
		out << "			P: \"AmbientColor\", \"ColorRGB\", \"Color\", \"\",0,0,0\n";
		out << "			P: \"DiffuseColor\", \"ColorRGB\", \"Color\", \"\",1,1,1\n";
		out << "			P: \"BumpFactor\", \"double\", \"Number\", \"\",0.150000005960464\n";
		out << "			P: \"TransparencyFactor\", \"double\", \"Number\", \"\",1\n";
		out << "			P: \"SpecularColor\", \"ColorRGB\", \"Color\", \"\",0.5,0.5,0.5\n";
		out << "			P: \"ReflectionFactor\", \"double\", \"Number\", \"\",0.5\n";
		out << "			P: \"Emissive\", \"Vector3D\", \"Vector\", \"\",0,0,0\n";
		out << "			P: \"Ambient\", \"Vector3D\", \"Vector\", \"\",0,0,0\n";
		out << "			P: \"Diffuse\", \"Vector3D\", \"Vector\", \"\",1,1,1\n";
		out << "			P: \"Specular\", \"Vector3D\", \"Vector\", \"\",0.5,0.5,0.5\n";
		out << "			P: \"Shininess\", \"double\", \"Number\", \"\",20\n";
		out << "			P: \"Opacity\", \"double\", \"Number\", \"\",1\n";
		out << "			P: \"Reflectivity\", \"double\", \"Number\", \"\",0\n";
		out << "		}\n";
        out << "	}\n";
        (*Nphong)++;
        break;

    case(144):  // SKIN (DIFFUSE + BUMP + SPECULAR + AMBIENT) (con Depth Of Field)
	case(145):  // SKIN (DIFFUSE + BUMP + SPECULAR + AMBIENT) (senza Depth Of Field)
	case(147):  // SKIN (DIFFUSE + BUMP + SPECULAR + AMBIENT) (senza Depth Of Field)
        out << "	Material: " << nodeID(21,m) << ", \"Material::Mt" << m+1 << "_skin_phong" << *Nphong << "\", \"\" {\n";
        out << "		Version: 102\n";
        out << "		ShadingModel: \"phong\"\n";
        out << "		MultiLayer: 0\n";
        out << "		Properties70:  {\n";
		out << "			P: \"AmbientColor\", \"ColorRGB\", \"Color\", \"\",0.5,0.5,0.5\n";
		out << "			P: \"DiffuseColor\", \"ColorRGB\", \"Color\", \"\",1,1,1\n";
		out << "			P: \"BumpFactor\", \"double\", \"Number\", \"\",0.150000005960464\n";
		out << "			P: \"TransparencyFactor\", \"double\", \"Number\", \"\",1\n";
		out << "			P: \"SpecularColor\", \"ColorRGB\", \"Color\", \"\",0.5,0.5,0.5\n";
		out << "			P: \"ShininessExponent\", \"double\", \"Number\", \"\",100\n";
		out << "			P: \"ReflectionFactor\", \"double\", \"Number\", \"\",0\n";
		out << "			P: \"Emissive\", \"Vector3D\", \"Vector\", \"\",0,0,0\n";
		out << "			P: \"Ambient\", \"Vector3D\", \"Vector\", \"\",0.5,0.5,0.5\n";
		out << "			P: \"Diffuse\", \"Vector3D\", \"Vector\", \"\",1,1,1\n";
		out << "			P: \"Specular\", \"Vector3D\", \"Vector\", \"\",0.5,0.5,0.5\n";
		out << "			P: \"Shininess\", \"double\", \"Number\", \"\",100\n";
		out << "			P: \"Opacity\", \"double\", \"Number\", \"\",1\n";
		out << "			P: \"Reflectivity\", \"double\", \"Number\", \"\",0\n";
		out << "		}\n";
        out << "	}\n";
        (*Nphong)++;
        break;

    default:
        if (Materials[m].Diffuse < 0)       // Se manca il diffuse scrive NONE (case=0)
        {
            out << "	Material: " << nodeID(21,m) << ", \"Material::Mt" << m+1 << "_unknown_" << Materials[m].Type << "_lambert" << *Nlambert << "\", \"\" {\n";
            out << "		Version: 102\n";
            out << "		ShadingModel: \"lambert\"\n";
            out << "		MultiLayer: 0\n";
            out << "		Properties70:  {\n";
            out << "			P: \"AmbientColor\", \"ColorRGB\", \"Color\", \"\",0,0,0\n";
            out << "			P: \"DiffuseColor\", \"ColorRGB\", \"Color\", \"\",0.5,0.5,0.5\n";
			out << "			P: \"TransparencyFactor\", \"double\", \"Number\", \"\",1\n";
            out << "			P: \"Emissive\", \"Vector3D\", \"Vector\", \"\",0,0,0\n";
            out << "			P: \"Ambient\", \"Vector3D\", \"Vector\", \"\",0,0,0\n";
            out << "			P: \"Diffuse\", \"Vector3D\", \"Vector\", \"\",0.5,0.5,0.5\n";
            out << "			P: \"Opacity\", \"double\", \"Number\", \"\",1\n";
            out << "		}\n";
            out << "	}\n";
            (*Nlambert)++;
        }
        else                                // Altrimenti, se il diffuse è presente, tratta il materiale come se fosse solo DIFFUSE
        {
            out << "	Material: " << nodeID(21,m) << ", \"Material::Mt" << m+1 << "_unknown_" << Materials[m].Type << "_lambert" << *Nlambert << "\", \"\" {\n";
            out << "		Version: 102\n";
            out << "		ShadingModel: \"lambert\"\n";
            out << "		MultiLayer: 0\n";
            out << "		Properties70:  {\n";
            out << "			P: \"AmbientColor\", \"ColorRGB\", \"Color\", \"\",0,0,0\n";
            out << "			P: \"DiffuseColor\", \"ColorRGB\", \"Color\", \"\",1,1,1\n";
            out << "			P: \"TransparencyFactor\", \"double\", \"Number\", \"\",1\n";
            out << "			P: \"Emissive\", \"Vector3D\", \"Vector\", \"\",0,0,0\n";
            out << "			P: \"Ambient\", \"Vector3D\", \"Vector\", \"\",0,0,0\n";
            out << "			P: \"Diffuse\", \"Vector3D\", \"Vector\", \"\",1,1,1\n";
            out << "			P: \"Opacity\", \"double\", \"Number\", \"\",1\n";
            out << "		}\n";
            out << "	}\n";
            (*Nlambert)++;
        }
        break;
    }
}