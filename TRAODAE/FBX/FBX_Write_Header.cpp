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
Scrittura Header
INPUT: 
OUTPUT: ofstream &out
------------------------------------------------------------------------------------------------------------------*/

#include "stdafx.h"


void FBX_Write_Header (ofstream &out)
{
    out << "; FBX 7.1.0 project file\n";
    out << "; Copyright (C) 1997-2010 Autodesk Inc. and/or its licensors.\n";
    out << "; All rights reserved.\n";
    out << "; ----------------------------------------------------\n\n";
    out << "FBXHeaderExtension:  {\n";
    out << "	FBXHeaderVersion: 1003\n";
    out << "	FBXVersion: 7500\n";
    out << "	Creator: \"FBX SDK/FBX Plugins version 2011.3.1\"\n";
    out << "	SceneInfo: \"SceneInfo::GlobalInfo\", \"UserData\" {\n";
    out << "		Type: \"UserData\"\n";
    out << "		Version: 100\n";
    out << "		MetaData:  {\n";
    out << "			Version: 100\n";
    out << "			Title: \"\"\n";
    out << "			Subject: \"\"\n";
    out << "			Author: \"\"\n";
    out << "			Keywords: \"\"\n";
    out << "			Revision: \"\"\n";
    out << "			Comment: \"\"\n";
    out << "		}\n";
    out << "	}\n";
    out << "}\n";
    out << "GlobalSettings:  {\n";
    out << "	Version: 1000\n";
    out << "	Properties70:  {\n";
    out << "		P: \"UpAxis\", \"int\", \"Integer\", \"\",2\n";
    out << "		P: \"UpAxisSign\", \"int\", \"Integer\", \"\",1\n";
    out << "		P: \"FrontAxis\", \"int\", \"Integer\", \"\",1\n";
    out << "		P: \"FrontAxisSign\", \"int\", \"Integer\", \"\",-1\n";
    out << "		P: \"CoordAxis\", \"int\", \"Integer\", \"\",0\n";
    out << "		P: \"CoordAxisSign\", \"int\", \"Integer\", \"\",1\n";
    out << "		P: \"OriginalUpAxis\", \"int\", \"Integer\", \"\",2\n";
    out << "		P: \"OriginalUpAxisSign\", \"int\", \"Integer\", \"\",1\n";
    out << "		P: \"UnitScaleFactor\", \"double\", \"Number\", \"\",1\n";
    out << "		P: \"OriginalUnitScaleFactor\", \"double\", \"Number\", \"\",1\n";
    out << "		P: \"AmbientColor\", \"ColorRGB\", \"Color\", \"\",0,0,0\n";
    out << "		P: \"DefaultCamera\", \"KString\", \"\", \"\", \"Producer Perspective\"\n";
    out << "		P: \"TimeMode\", \"enum\", \"\", \"\",6\n";
    out << "		P: \"TimeSpanStart\", \"KTime\", \"Time\", \"\",0\n";
    out << "		P: \"TimeSpanStop\", \"KTime\", \"Time\", \"\",15395386000000\n";
    out << "	}\n";
    out << "}\n\n";
}