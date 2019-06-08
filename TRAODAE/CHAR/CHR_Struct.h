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


#pragma once


struct CHR_HEADER
{
    uint32_t CHR_MAGIC;
    uint32_t TEXTURE_PTR;
    uint32_t SKELETON_PTR;
    uint32_t UNKNOWN2;
    uint32_t MESH1_PTR;
    uint32_t nBONES;
};


struct CHR_BONE					// SIZE: 448 bytes
{
    uint32_t Hierarchy;
    char Bone_name[64];					// Nome bone in ASCII, 64 bytes
    uint32_t Bone_name_hashed;			// Hash nome bone
    uint32_t NULL1;						// Non fa niente, il gioco lo ignora
    uint32_t NULL2;						// Non fa niente, il gioco lo ignora
    float X_scale;
    float Xy_scale;
    float Xz_scale;
    float Xw_scale;
    float Yx_scale;
    float Y_scale;
    float Yz_scale;
    float Yw_scale;
    float Zx_scale;
    float Zy_scale;
    float Z_scale;
    float Zw_scale;
    float X1_trasl;
    float Y1_trasl;
    float Z1_trasl;
    float W1_trasl;
    float Ragdoll_X;
    float Ragdoll_Xy;
    float Ragdoll_Xz;
    float Ragdoll_Xw;
    float Ragdoll_Yx;
    float Ragdoll_Y;
    float Ragdoll_Yz;
    float Ragdoll_Yw;
    float Ragdoll_Zx;
    float Ragdoll_Zy;
    float Ragdoll_Z;
    float Ragdoll_Zw;
    float X2_trasl;         // DA CONTROLLARE
    float Y2_trasl;         // DA CONTROLLARE
    float Z2_trasl;         // DA CONTROLLARE
    float W2_trasl;         // DA CONTROLLARE
    char Unknown2[128];					// 128 bytes da scoprire
    float Unknown3;         // DA CONTROLLARE
    float Unknown4;         // DA CONTROLLARE
    float Unknown5;         // DA CONTROLLARE
    float Unknown6;         // DA CONTROLLARE
    float Unknown7;         // DA CONTROLLARE
    char Unknown8[92];      // DA CONTROLLARE
};


struct CHR_MESH12_HEADER
{
    uint32_t SizeMESH12;
};


struct CHR_MESH1_HEADER
{
    uint32_t Unknown1;
    uint32_t ID;
    uint32_t nVertices;
};


struct CHR_MESH1_VERTEX
{
    int16_t X1;             // Set vertici 1
    int16_t Y1;             // Set vertici 1
    int16_t Z1;             // Set vertici 1
    int16_t X2;                         // Set vertici 2
    int16_t Y2;                         // Set vertici 2
    int16_t Z2;                         // Set vertici 2
    int8_t X1n;             // Set normals 1
    int8_t Y1n;             // Set normals 1
    int8_t Z1n;             // Set normals 1
    int8_t X2n;                         // Set normals 2
    int8_t Y2n;                         // Set normals 2
    int8_t Z2n;                         // Set normals 2
    int8_t X1tg;            // Set tangents 1
    int8_t Y1tg;            // Set tangents 1
    int8_t Z1tg;            // Set tangents 1
    int8_t X1bn;            // Set binormals 1
    int8_t Y1bn;            // Set binormals 1
    int8_t Z1bn;            // Set binormals 1
    int8_t X2tg;						// Set tangents 2
    int8_t Y2tg;                        // Set tangents 2
    int8_t Z2tg;                        // Set tangents 2
    int8_t X2bn;                        // Set binormals 2
    int8_t Y2bn;                        // Set binormals 2
    int8_t Z2bn;                        // Set binormals 2
    int16_t Weight;            // Peso della prima bone
    uint8_t Bone1;
    uint8_t Bone2;
    int16_t U;
    int16_t V;
};


struct CHR_MESH_STRIP_HEADER
{
    uint32_t nIndices;
};


struct CHR_MESH_STRIP
{
    uint16_t Index;
};


struct CHR_MESH_ELEMENT_HEADER
{
    uint32_t nElements;
};


struct CHR_MESH_ELEMENT
{
    int16_t nElement_Triangles;         // Numero di triangoli. Sempre uguale a numero indici triangle strip dell'elemento - 2
    int16_t nElement_Indices;           // Numero di indici di vertici. Sempre uguale a nElement_Triangles + 2
    int16_t Offset;                     // Il primo è 00000000h, i successivi sono Offset + nElement_Indices dell'elemento precedente
    uint16_t Material_Ref;				// Numero del materiale
    uint16_t Unknown1;                  // Sempre FFFFh ?
    uint16_t Draw_mode;                 // 0000h/0100h vista vertici. 0200h/0300h wireframe senza/con flip poligoni pari? 0400h facce esplicite. 0500h triangle strip
};


struct CHR_MESH2_LIST
{
    uint32_t nMeshes2;					// Numero di mesh di tipo 2
};


struct CHR_MESH2_HEADER
{
    uint32_t Unknown1;					// Sempre 00000000h ?
    uint32_t Unknown2;					// Forse il numero di ripetizioni dell'oggetto
    uint32_t ID;						// Hash del nome dell'oggetto
    uint32_t Bone_ref;					// Numero bone a cui la mesh è collegata
    uint32_t Unknown3;					// Sempre FFFFFFFFh ?
    uint32_t nVertices;
};


struct CHR_MESH2_VERTEX
{
    int16_t X;
    int16_t Y;
    int16_t Z;
    int8_t Xn;
    int8_t Yn;
    int8_t Zn;
    int8_t Xtg;
    int8_t Ytg;
    int8_t Ztg;
    int8_t Xbn;
    int8_t Ybn;
    int8_t Zbn;
    int16_t U;
    int16_t V;
};


struct CHR_MATERIALS_HEADER
{
    uint32_t nMaterials;				// Numero materiali
};


struct CHR_MATERIALS_LIST		// SIZE: 24 bytes
{
    uint16_t TextureMode;               // Tipologia di materiale
    uint16_t DoubleSided;               // Texture a doppia faccia. Inutile nei CHR perchè hanno il backface culling disattivato
    int32_t Unknown1;                   // Sembrerebbe sempre pari a 00000004h, forse indica il numero di slot per textures a seguire
    int32_t DiffuseID;                  // Slot 1: texture principale
    int32_t ShadowMapID;                // Slot 2: shadow map
    int32_t BumpSpecID;                 // Slot 3: bump map e riflessi
    int32_t FurID;                      // Slot 4: texture ARGB usata per fur (principalmente ciuffi di erba)
};


struct CHR_TEXTURES_HEADER
{
    uint32_t nTextures;                 // Numero textures
};


struct CHR_TEXTURES_LIST        // SIZE: 28 bytes
{
    char32_t DXT;                       // DXT1, DXT3, DXT5 o RGBA
    uint32_t ColourBumpShadow;          // 01000000h per shadow map, 02000000h per diffuse map, 04000000h per bump map, 05000000h per fur
    uint32_t Unknown1;                  // Sempre 01000000h
    uint32_t Mips;                      // Numero di mipmaps
    uint32_t Xsize;                     // Dimensione asse X immagine in pixels
    uint32_t Ysize;                     // Dimensione asse Y immagine in pixels
    uint32_t RAWsize;                   // Dimensione texture in bytes
};