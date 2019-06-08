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
Scrittura Object definitions
INPUT: FBX_COUNT_CLASS FBX_Count
OUTPUT: ofstream &out
------------------------------------------------------------------------------------------------------------------*/

#include "stdafx.h"
#include "Classes.h"


void FBX_Write_Object_definitions (FBX_COUNT_CLASS FBX_Count, ofstream &out)
{
    out << "; Object definitions\n";
    out << ";------------------------------------------------------------------\n\n";
    out << "Definitions:  {\n";
    if (FBX_Count.AnimationStack > 0)   {
        out << "	ObjectType: \"AnimationStack\" {\n";
        out << "		Count: " << FBX_Count.AnimationStack << "\n";
        out << "	}\n";   }
    if (FBX_Count.AnimationLayer > 0)   {
        out << "	ObjectType: \"AnimationLayer\" {\n";
        out << "		Count: " << FBX_Count.AnimationLayer << "\n";
        out << "	}\n";   }
    if (FBX_Count.AnimationCurveNode > 0)   {
        out << "	ObjectType: \"AnimationCurveNode\" {\n";
        out << "		Count: " << FBX_Count.AnimationCurveNode << "\n";
        out << "	}\n";   }
    if (FBX_Count.AnimationCurve > 0)   {
        out << "	ObjectType: \"AnimationCurve\" {\n";
        out << "		Count: " << FBX_Count.AnimationCurve << "\n";
        out << "	}\n";   }
    if (FBX_Count.Model > 0)    {
        out << "	ObjectType: \"Model\" {\n";
        out << "		Count: " << FBX_Count.Model << "\n";
        out << "	}\n";   }
    if (FBX_Count.Geometry > 0) {
        out << "	ObjectType: \"Geometry\" {\n";
        out << "		Count: " << FBX_Count.Geometry << "\n";
        out << "	}\n";   }
    if (FBX_Count.Material > 0) {
        out << "	ObjectType: \"Material\" {\n";
        out << "		Count: " << FBX_Count.Material << "\n";
        out << "	}\n";   }
    if (FBX_Count.Texture > 0)  {
        out << "	ObjectType: \"Texture\" {\n";
        out << "		Count: " << FBX_Count.Texture << "\n";
        out << "	}\n";   }
    if (FBX_Count.NodeAttribute > 0)    {
        out << "	ObjectType: \"NodeAttribute\" {\n";
        out << "		Count: " << FBX_Count.NodeAttribute << "\n";
        out << "	}\n";   }
    if (FBX_Count.Pose > 0) {
        out << "	ObjectType: \"Pose\" {\n";
        out << "		Count: " << FBX_Count.Pose << "\n";
        out << "	}\n";   }
    if (FBX_Count.Deformer > 0) {
        out << "	ObjectType: \"Deformer\" {\n";
        out << "		Count: " << FBX_Count.Deformer << "\n";
        out << "	}\n";   }
    out << "}\n";
}