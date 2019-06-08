TOMB RAIDER: THE ANGEL OF DARKNESS ANIMATION EXPORTER (by Nakamichi680)

For any question, feel free to contact me on: http://www.aspidetr.com/forum/ or http://www.tombraiderforums.com/


Version: 1.1
Release date: 2018/03/11
Changelog:
- Added animations root motion support
- Improvements in some materials


LICENSE AND DISCLAIMER
This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public
License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any
later version.
This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied
warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.
You can find a copy of the GNU General Public License inside "GNU General Public License v3.txt".


INTRODUCTION
Welcome to the Tomb Raider – The Angel of Darkness Animation Exporter.

This program is designed to export rigged and textured 3D models, animations and blend shapes from CHR, CAL and TMT files.

Before examining how to use the tool, a brief summary of game files structure is required.

A GMX file is an uncompressed archive containing many files, each of which has a specific role. Three of these files
are used to draw and move characters inside the game:
	1) CHR: it contains the skeleton, the rigged mesh and the textures. The mesh is usually stored in T-Pose
	        (for humanoid characters) or in a relaxed pose (for non-humanoid NPCs like dogs, bats, etc). 
		CHR files can be used standalone to produce wonderful, though static, 3D models of a character.
		However, keep in mind that there are two types of CHR files: the former, beforehand described, applies
		to all animate characters while the latter, used for inanimate objects, has a different structure
		and can't be exported by TRAODAE.
	2) CAL: it contains animations. Since it stores only raw transforms and lacks a skeleton, it can’t be converted
		without its respective CHR. Quaternions are used for rotation transforms. TRAODAE will automatically
		convert those quaternions to more user-friendly Euler rotations.
	3) TMT: it contains blend shapes. Blend shapes are used to give expressiveness to characters during cutscenes
		and in-game cutscenes by altering the mesh of the face. TMT files doesn't contain any information on
		polygons, just vertex coordinates: this means that they can't be used without their respective CHR.

HOW TO USE
1) Put the files you'd like to export in one folder (it doesn’t necessarily have to be the same of TRAODAE.EXE)
2) Make sure that all the files you'd like to export have the same name (they have to differ in extension only)
3) Run TRAODAE. You can do this in two ways:
	- From Windows File Explorer: drag and drop one of the files you'd like to convert into TRAODAE.EXE. The
	  program will export the selected file and will ask if you want to export the others too.

	- From Command Prompt: type “TRAODAE [filename]”. If you omit the extension the program will search for
	  CHR/CAL/TMT files and will export everything it finds without asking. If you specify the extension the
	  program will export the selected file and will ask if you want to export the others too.


KNOWN BUGS
- Some characters' skeleton could have wrong bone hierarchy
- Some materials have not yet been implemented. Unknown materials are exported as standard Lambert with diffuse channel only.