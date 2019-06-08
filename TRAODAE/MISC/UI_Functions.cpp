/* Tomb Raider - The Angel of Darkness Animation Exporter
Copyright (c) 2017-2018 Nakamichi680

This file is part of "Tomb Raider - The Angel of Darkness Animation Exporter".

"Tomb Raider - The Angel of Darkness Animation Exporter" is free software: you can redistribute it and/or modify it under the terms of the
GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.

"Tomb Raider - The Angel of Darkness Animation Exporter" is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without
even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with "Tomb Raider - The Angel of Darkness Animation Exporter".
If not, see <http://www.gnu.org/licenses/>.

Copyright (c) Square Enix Ltd. Lara Croft and Tomb Raider are trademarks or registered trademarks of Square Enix Ltd.*/


#include "stdafx.h"
#include "MISC/concol.h"
#include "Classes.h"


/*------------------------------------------------------------------------------------------------------------------
Scrive sullo schermo la string "str" centrandola in uno spazio di "lenght" caratteri
INPUT: string str, unsigned int length
OUTPUT:
------------------------------------------------------------------------------------------------------------------*/

void Center_string (string str, unsigned int length)
{
    unsigned int len = str.length();
    unsigned int pos = (int)((length - len) / 2);
    for (unsigned int counter = 0; counter < pos; counter++)
        cout << " ";											// Aggiunge gli spazi prima della scritta
    cout << setw(length - pos) << std::left << str;				// Scrive la stringa ed aggiunge gli spazi successivi
}


/*------------------------------------------------------------------------------------------------------------------
Controlla se un file esiste
INPUT:
OUTPUT:
------------------------------------------------------------------------------------------------------------------*/

bool doesExist (string filename)
{
	ifstream test;
	test.open(filename, std::ios::binary);
    if (test.is_open())
		return true;
	else
		return false;
}


/*------------------------------------------------------------------------------------------------------------------
Accorcia una stringa "str" ad una lunghezza massima di "lenght" caratteri (gli ultimi tre caratteri sono punti di sospensione)
INPUT: string str, unsigned int length
OUTPUT:
------------------------------------------------------------------------------------------------------------------*/

string Resize_string (string str, unsigned int length)
{
    if (str.length() > length)
    {
        str.resize(length - 3);
        str.append("...");
    }
    return str;
}


/*------------------------------------------------------------------------------------------------------------------
Messaggio di errore/errore fatale. 
INPUT: bool FATAL_ERROR, string filename, string message
OUTPUT:
------------------------------------------------------------------------------------------------------------------*/

void UI_Display_Error (bool FATAL_ERROR, string filename, string message)
{
	int user_input;
	string error1, error2, temp, text;
	if (FATAL_ERROR)
	{
		error1 = "FATAL ERROR: ";
		error2 = " Press any key to exit. ";
	}
	else
	{
		error1 = "ERROR: ";
		error2 = " Press any key to continue. ";
	}
	temp = error1;
	temp.append(message);
	unsigned int lenght = temp.size();
	lenght = 83 - lenght;
	filename = Resize_string(filename, lenght);					// Accorcia il nome del file se troppo lungo
	text = error1;
	if (filename.size() > 1)
		text.append("\"");
	text.append(filename);
	if (filename.size() > 1)
		text.append("\"");
	text.append(message);
	cout << red << "\n              ษอออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป\n";
	cout << "              บ                                                                                         บ\n";
	cout << "              บ";
	Center_string(text, 89);
	cout << "บ\n";
	cout << "              บ                                                                                         บ\n";
	cout << "              ศอออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ\n\n\n" << black;
	cout << error2;
	user_input = getch();
	if (user_input == 224 || user_input == 0)
		getch();
	cout << "\n\n";
}


/*------------------------------------------------------------------------------------------------------------------
Errore per mancanza di file di input. Termina il programma
INPUT:
OUTPUT:
------------------------------------------------------------------------------------------------------------------*/

bool UI_Exit_noinput ()
{
	system("cls");
	cout << "TOMB RAIDER - THE ANGEL OF DARKNESS ANIMATION EXPORTER (by Nakamichi680)\n\n";
	cout << "For any question, feel free to contact me on:\n";
	cout << "http://www.aspidetr.com/forum/  or  http://www.tombraiderforums.com/\n\n\n\n";
	cout << "USAGE\n";
	cout << "- Command Prompt:\n";
	cout << "     SYNTAX:   TRAODAE filename\n";
	cout << "               TRAODAE filename.CHR\n";
	cout << "               TRAODAE filename.CAL\n";
	cout << "               TRAODAE filename.TMT\n\n";
	cout << "- File Explorer:\n";
	cout << "     Drag and drop the CHR/CAL/TMT file into TRAODAE.EXE\n\n\n";
	cout << "Press any key to exit\n";
	getch();
	return false;
}


/*------------------------------------------------------------------------------------------------------------------
Cancella lo schermo e scrive la barra del titolo
INPUT:
OUTPUT:
------------------------------------------------------------------------------------------------------------------*/

void UI_Title ()
{
	system("cls");
	cout << " ษอออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป\n";
	cout << " บ                                                                                                                   บ\n";
	cout << " บ" << red << "                              Tomb Raider - The Angel of Darkness Animation Exporter                               " << black << "บ\n";
	cout << " บ" << blue << "                                                  by Nakamichi680                                                  " << black << "บ\n";
	cout << " บ                                                                                                                   บ\n";
	cout << " บ" << dark_green << "  For any question, feel free to contact me on http://www.aspidetr.com/forum/ or http://www.tombraiderforums.com/  " << black << "บ\n";
	cout << " ศอออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ\n";
	cout << dark_purple << "                                                                                                 v. 1.1    2018/03/11\n\n\n" << black;
}


/*------------------------------------------------------------------------------------------------------------------
Scrive un testo (opzionale) e, a seguire, disegna una barra di avanzamento
INPUT: unsigned int Position, unsigned int End, unsigned int BarLength, string PreText = "", int P = 99999, int E = 99999
OUTPUT:
------------------------------------------------------------------------------------------------------------------*/

void UI_ProgressBar (unsigned int Position,							// Posizione attuale della barra
					 unsigned int End,								// Posizione finale della barra
					 unsigned int BarLength,						// Larghezza della barra in caratteri
					 string PreText = "",							// Opzionale: testo da anteporre alla barra sulla stessa riga
					 int P = 99999,									// Opzionale: numero che precede la barra e che indica la posizione attuale (non usato per disegnare la barra)
					 int E = 99999)									// Opzionale: numero che precede la barra e che indica la posizione finale (non usato per disegnare la barra)
{
	if (P == 99999 || E == 99999)
	{
		P = Position;
		E = End;
	}
	stringstream sstream;
	sstream << P + 1 << "/" << E;
	float pos = (float)(Position + 1) / (float)End * (float)BarLength;
	cout << PreText << setw(9) << sstream.str() << "   0 % [";
	for (float i = 0; i <= BarLength; i++)
	{
		if (i <= pos)
			cout << dark_magenta << "þ";		
		else cout << " ";
	}
	cout << black << "] 100 %" << "\r";
	if (Position == End - 1)
		cout << "\n\n";
}


/*------------------------------------------------------------------------------------------------------------------
Mostra il testo della licenza
INPUT:
OUTPUT:
------------------------------------------------------------------------------------------------------------------*/

void UI_ShowLicense ()
{
	int user_input;
	system("mode 119, 52");	
	system("cls");
	cout << red << "\n PAGE 1 OF 11\n" << black;
	cout << "\n                                             GNU GENERAL PUBLIC LICENSE\n";
	cout << "                                              Version 3, 29 June 2007\n\n";
	cout << "  Copyright (C) 2007 Free Software Foundation, Inc. <http://fsf.org/>\n";
	cout << "  Everyone is permitted to copy and distribute verbatim copies of this license document, but changing it is\n";
	cout << " not allowed.\n\n";
	cout << "                                                     Preamble\n\n";
	cout << "  The GNU General Public License is a free, copyleft license for software and other kinds of works.\n\n";
	cout << "  The licenses for most software and other practical works are designed to take away your freedom to share and change\n";
	cout << " the works.  By contrast, the GNU General Public License is intended to guarantee your freedom to share and change all\n";
	cout << " versions of a program--to make sure it remains free software for all its users. We, the Free Software Foundation,\n";
	cout << " use the GNU General Public License for most of our software; it applies also to any other work released this way by\n";
	cout << " its authors. You can apply it to your programs, too.\n\n";
	cout << "  When we speak of free software, we are referring to freedom, not price. Our General Public Licenses are designed to\n";
	cout << " make sure that you have the freedom to distribute copies of free software (and charge for them if you wish), that you\n";
	cout << " receive source code or can get it if you want it, that you can change the software or use pieces of it in new free\n";
	cout << " programs, and that you know you can do these things.\n\n";
	cout << "  To protect your rights, we need to prevent others from denying you these rights or asking you to surrender\n";
	cout << " the rights.\n";
	cout << "  Therefore, you have certain responsibilities if you distribute copies of the software, or if you modify it:\n";
	cout << " responsibilities to respect the freedom of others.\n\n";
	cout << "  For example, if you distribute copies of such a program, whether gratis or for a fee, you must pass on to the\n";
	cout << " recipients the same freedoms that you received. You must make sure that they, too, receive or can get the source\n";
	cout << " code. And you must show them these terms so they know their rights.\n\n";
	cout << "  Developers that use the GNU GPL protect your rights with two steps: (1) assert copyright on the software, and\n";
	cout << " (2) offer you this License giving you legal permission to copy, distribute and/or modify it.\n\n";
	cout << "  For the developers' and authors' protection, the GPL clearly explains that there is no warranty for this free\n";
	cout << " software. For both users' and authors' sake, the GPL requires that modified versions be marked as changed, so that\n";
	cout << " their problems will not be attributed erroneously to authors of previous versions.\n\n";
	cout << "  Some devices are designed to deny users access to install or run modified versions of the software inside them,\n";
	cout << " although the manufacturer can do so. This is fundamentally incompatible with the aim of protecting users' freedom to\n";
	cout << " change the software. The systematic pattern of such abuse occurs in the area of products for individuals to use,\n";
	cout << " which is precisely where it is most unacceptable. Therefore, we have designed this version of the GPL to prohibit the\n";
	cout << " practice for those products. If such problems arise substantially in other domains, we stand ready to extend this\n";
	cout << " provision to those domains in future versions of the GPL, as needed to protect the freedom of users.\n\n\n\n";
	cout << red << " PRESS ANY KEY TO CONTINUE " << black;
	user_input = getch();
	if (user_input == 224 || user_input == 0)
		getch();

	system("cls");
	cout << red << "\n PAGE 2 OF 11\n" << black;
	cout << "\n  Finally, every program is threatened constantly by software patents. States should not allow patents to restrict\n";
	cout << " development and use of software on general-purpose computers, but in those that do, we wish to avoid the special\n";
	cout << " danger that patents applied to a free program could make it effectively proprietary. To prevent this, the GPL assures\n";
	cout << " that patents cannot be used to render the program non-free.\n\n";
	cout << "  The precise terms and conditions for copying, distribution and modification follow.\n\n";
	cout << "                                                TERMS AND CONDITIONS\n\n";
	cout << "  0. Definitions.\n\n";
	cout << "  \"This License\" refers to version 3 of the GNU General Public License.\n\n";
	cout << "  \"Copyright\" also means copyright-like laws that apply to other kinds of works, such as semiconductor masks.\n\n";
	cout << "  \"The Program\" refers to any copyrightable work licensed under this License. Each licensee is addressed as \"you\".\n";
	cout << " \"Licensees\" and \"recipients\" may be individuals or organizations.\n\n";
	cout << "  To \"modify\" a work means to copy from or adapt all or part of the work in a fashion requiring copyright permission,\n";
	cout << " other than the making of an exact copy. The resulting work is called a \"modified version\" of the earlier work or a\n";
	cout << " work \"based on\" the earlier work.\n\n";
	cout << "  A \"covered work\" means either the unmodified Program or a work based on the Program.\n\n";
	cout << "  To \"propagate\" a work means to do anything with it that, without permission, would make you directly or secondarily\n";
	cout << " liable for infringement under applicable copyright law, except executing it on a computer or modifying a private\n";
	cout << " copy. Propagation includes copying, distribution (with or without modification), making available to the public, and\n";
	cout << " in some countries other activities as well.\n\n";
	cout << "  To \"convey\" a work means any kind of propagation that enables other parties to make or receive copies. Mere\n";
	cout << " interaction with a user through a computer network, with no transfer of a copy, is not conveying.\n\n";
	cout << "  An interactive user interface displays \"Appropriate Legal Notices\" to the extent that it includes a convenient and\n";
	cout << " prominently visible feature that (1) displays an appropriate copyright notice, and (2) tells the user that there is\n";
	cout << " no warranty for the work (except to the extent that warranties are provided), that licensees may convey the work\n";
	cout << " under this License, and how to view a copy of this License. If the interface presents a list of user commands or\n";
	cout << " options, such as a menu, a prominent item in the list meets this criterion.\n\n";
	cout << "  1. Source Code.\n\n";
	cout << "  The \"source code\" for a work means the preferred form of the work for making modifications to it. \"Object code\"\n";
	cout << " means any non-source form of a work.\n\n";
	cout << "  A \"Standard Interface\" means an interface that either is an official standard defined by a recognized standards\n";
	cout << " body, or, in the case of interfaces specified for a particular programming language, one that is widely used among\n";
	cout << " developers working in that language.\n\n";
	cout << red << " PRESS ANY KEY TO CONTINUE " << black;
	user_input = getch();
	if (user_input == 224 || user_input == 0)
		getch();

	system("cls");
	cout << red << "\n PAGE 3 OF 11\n" << black;
	cout << "\n  The \"System Libraries\" of an executable work include anything, other than the work as a whole, that (a) is included\n";
	cout << " in the normal form of packaging a Major Component, but which is not part of that Major Component, and (b) serves only\n";
	cout << " to enable use of the work with that Major Component, or to implement a Standard Interface for which an implementation\n";
	cout << " is available to the public in source code form. A \"Major Component\", in this context, means a major essential\n";
	cout << " component (kernel, window system, and so on) of the specific operating system (if any) on which the executable work\n";
	cout << " runs, or a compiler used to produce the work, or an object code interpreter used to run it.\n\n";
	cout << "  The \"Corresponding Source\" for a work in object code form means all the source code needed to generate, install, and\n";
	cout << " (for an executable work) run the object code and to modify the work, including scripts to control those activities.\n";
	cout << " However, it does not include the work's System Libraries, or general-purpose tools or generally available free\n";
	cout << " programs which are used unmodified in performing those activities but which are not part of the work. For example,\n";
	cout << " Corresponding Source includes interface definition files associated with source files for the work, and the source\n";
	cout << " code for shared libraries and dynamically linked subprograms that the work is specifically designed to require, such\n";
	cout << " as by intimate data communication or control flow between those subprograms and other parts of the work.\n\n";
	cout << "  The Corresponding Source need not include anything that users can regenerate automatically from other parts of the\n";
	cout << " Corresponding Source.\n\n";
	cout << "  The Corresponding Source for a work in source code form is that same work.\n\n";
	cout << "  2. Basic Permissions.\n\n";
	cout << "  All rights granted under this License are granted for the term of copyright on the Program, and are irrevocable\n";
	cout << " provided the stated conditions are met. This License explicitly affirms your unlimited permission to run the\n";
	cout << " unmodified Program. The output from running a covered work is covered by this License only if the output, given its\n";
	cout << " content, constitutes a covered work. This License acknowledges your rights of fair use or other equivalent, as\n";
	cout << " provided by copyright law.\n\n";
	cout << "  You may make, run and propagate covered works that you do not convey, without conditions so long as your license\n";
	cout << " otherwise remains in force. You may convey covered works to others for the sole purpose of having them make\n";
	cout << " modifications exclusively for you, or provide you with facilities for running those works, provided that you comply\n";
	cout << " with the terms of this License in conveying all material for which you do not control copyright. Those thus making or\n";
	cout << " running the covered works for you must do so exclusively on your behalf, under your direction and control, on terms\n";
	cout << " that prohibit them from making any copies of your copyrighted material outside their relationship with you.\n\n";
	cout << "  Conveying under any other circumstances is permitted solely under the conditions stated below. Sublicensing is not\n";
	cout << " allowed; section 10 makes it unnecessary.\n\n";
	cout << "  3. Protecting Users' Legal Rights From Anti-Circumvention Law.\n\n";
	cout << "  No covered work shall be deemed part of an effective technological measure under any applicable law fulfilling\n";
	cout << " obligations under article 11 of the WIPO copyright treaty adopted on 20 December 1996, or similar laws prohibiting or\n";
	cout << " restricting circumvention of such measures.\n\n\n\n\n";
	cout << red << " PRESS ANY KEY TO CONTINUE " << black;
	user_input = getch();
	if (user_input == 224 || user_input == 0)
		getch();

	system("cls");
	cout << red << "\n PAGE 4 OF 11\n" << black;
	cout << "\n  When you convey a covered work, you waive any legal power to forbid circumvention of technological measures to the\n";
	cout << " extent such circumvention is effected by exercising rights under this License with respect to the covered work, and\n";
	cout << " you disclaim any intention to limit operation or modification of the work as a means of enforcing, against the work's\n";
	cout << " users, your or third parties' legal rights to forbid circumvention of technological measures.\n\n";
	cout << "  4. Conveying Verbatim Copies.\n\n";
	cout << "  You may convey verbatim copies of the Program's source code as you receive it, in any medium, provided that you\n";
	cout << " conspicuously and appropriately publish on each copy an appropriate copyright notice; keep intact all notices stating\n";
	cout << " that this License and any non-permissive terms added in accord with section 7 apply to the code; keep intact all\n";
	cout << " notices of the absence of any warranty; and give all recipients a copy of this License along with the Program.\n";
	cout << "  You may charge any price or no price for each copy that you convey, and you may offer support or warranty protection\n";
	cout << " for a fee.\n\n";
	cout << "  5. Conveying Modified Source Versions.\n\n";
	cout << "  You may convey a work based on the Program, or the modifications to produce it from the Program, in the form of\n";
	cout << " source code under the terms of section 4, provided that you also meet all of these conditions:\n\n";
	cout << "    a) The work must carry prominent notices stating that you modified it, and giving a relevant date.\n\n";
	cout << "    b) The work must carry prominent notices stating that it is released under this License and any conditions added\n";
	cout << "       under section 7. This requirement modifies the requirement in section 4 to \"keep intact all notices\".\n\n";
	cout << "    c) You must license the entire work, as a whole, under this License to anyone who comes into possession of a copy.\n";
	cout << "       This License will therefore apply, along with any applicable section 7 additional terms, to the whole of the\n";
	cout << "       work, and all its parts, regardless of how they are packaged. This License gives no permission to license the\n";
	cout << "       work in any other way, but it does not invalidate such permission if you have separately received it.\n\n";
	cout << "    d) If the work has interactive user interfaces, each must display Appropriate Legal Notices; however, if the\n";
	cout << "       Program has interactive interfaces that do not display Appropriate Legal Notices, your work need not make them\n";
	cout << "       do so.\n\n";
	cout << "  A compilation of a covered work with other separate and independent works, which are not by their nature extensions\n";
	cout << " of the covered work, and which are not combined with it such as to form a larger program, in or on a volume of a\n";
	cout << " storage or distribution medium, is called an \"aggregate\" if the compilation and its resulting copyright are not used\n";
	cout << " to limit the access or legal rights of the compilation's users beyond what the individual works permit. Inclusion of\n";
	cout << " a covered work in an aggregate does not cause this License to apply to the other parts of the aggregate.\n\n";
	cout << "  6. Conveying Non-Source Forms.\n\n";
	cout << "  You may convey a covered work in object code form under the terms of sections 4 and 5, provided that you also convey\n";
	cout << " the machine-readable Corresponding Source under the terms of this License, in one of these ways:\n\n\n\n\n";
	cout << red << " PRESS ANY KEY TO CONTINUE " << black;
	user_input = getch();
	if (user_input == 224 || user_input == 0)
		getch();

	system("cls");
	cout << red << "\n PAGE 5 OF 11\n" << black;
	cout << "\n    a) Convey the object code in, or embodied in, a physical product (including a physical distribution medium),\n";
	cout << "       accompanied by the Corresponding Source fixed on a durable physical medium customarily used for software\n";
	cout << "       interchange.\n\n";
	cout << "    b) Convey the object code in, or embodied in, a physical product (including a physical distribution medium),\n";
	cout << "       accompanied by a written offer, valid for at least three years and valid for as long as you offer spare parts\n";
	cout << "       or customer support for that product model, to give anyone who possesses the object code either (1) a copy of\n";
	cout << "       the Corresponding Source for all the software in the product that is covered by this License, on a durable\n";
	cout << "       physical medium customarily used for software interchange, for a price no more than your reasonable cost of\n";
	cout << "       physically performing this conveying of source, or (2) access to copy the Corresponding Source from a network\n";
	cout << "       server at no charge.\n\n";
	cout << "    c) Convey individual copies of the object code with a copy of the written offer to provide the Corresponding\n";
	cout << "       Source. This alternative is allowed only occasionally and noncommercially, and only if you received the object\n";
	cout << "       code with such an offer, in accord with subsection 6b.\n\n";
	cout << "    d) Convey the object code by offering access from a designated place (gratis or for a charge), and offer\n";
	cout << "       equivalent access to the Corresponding Source in the same way through the same place at no further charge. You\n";
	cout << "       need not require recipients to copy the Corresponding Source along with the object code. If the place to copy\n";
	cout << "       the object code is a network server, the Corresponding Source may be on a different server (operated by you or\n";
	cout << "       a third party) that supports equivalent copying facilities, provided you maintain clear directions next to the\n";
	cout << "       object code saying where to find the Corresponding Source. Regardless of what server hosts the Corresponding\n";
	cout << "       Source, you remain obligated to ensure that it is available for as long as needed to satisfy these\n";
	cout << "       requirements.\n\n";
	cout << "    e) Convey the object code using peer-to-peer transmission, provided you inform other peers where the object code\n";
	cout << "       and Corresponding Source of the work are being offered to the general public at no charge under subsection 6d.\n\n";
	cout << "  A separable portion of the object code, whose source code is excluded from the Corresponding Source as a System\n";
	cout << " Library, need not be included in conveying the object code work.\n\n";
	cout << "  A \"User Product\" is either (1) a \"consumer product\", which means any tangible personal property which is normally\n";
	cout << " used for personal, family, or household purposes, or (2) anything designed or sold for incorporation into a dwelling.\n";
	cout << " In determining whether a product is a consumer product, doubtful cases shall be resolved in favor of coverage. For a\n";
	cout << " particular product received by a particular user, \"normally used\" refers to a typical or common use of that class of\n";
	cout << " product, regardless of the status of the particular user or of the way in which the particular user actually uses, or\n";
	cout << " expects or is expected to use, the product. A product is a consumer product regardless of whether the product has\n";
	cout << " substantial commercial, industrial or non-consumer uses, unless such uses represent the only significant mode of use\n";
	cout << " of the product.\n\n";
	cout << "  \"Installation Information\" for a User Product means any methods, procedures, authorization keys, or other\n";
	cout << " information required to install and execute modified versions of a covered work in that User Product from a modified\n";
	cout << " version of its Corresponding Source. The information must suffice to ensure that the continued functioning of the\n";
	cout << " modified object code is in no case prevented or interfered with solely because modification has been made.\n\n\n\n";
	cout << red << " PRESS ANY KEY TO CONTINUE " << black;
	user_input = getch();
	if (user_input == 224 || user_input == 0)
		getch();

	system("cls");
	cout << red << "\n PAGE 6 OF 11\n" << black;
	cout << "\n  If you convey an object code work under this section in, or with, or specifically for use in, a User Product, and\n";
	cout << " the conveying occurs as part of a transaction in which the right of possession and use of the User Product is\n";
	cout << " transferred to the recipient in perpetuity or for a fixed term (regardless of how the transaction is characterized),\n";
	cout << " the Corresponding Source conveyed under this section must be accompanied by the Installation Information. But this\n";
	cout << " requirement does not apply if neither you nor any third party retains the ability to install modified object code on\n";
	cout << " the User Product (for example, the work has been installed in ROM).\n\n";
	cout << "  The requirement to provide Installation Information does not include a requirement to continue to provide support\n";
	cout << " service, warranty, or updates for a work that has been modified or installed by the recipient, or for the User\n";
	cout << " Product in which it has been modified or installed. Access to a network may be denied when the modification itself\n";
	cout << " materially and adversely affects the operation of the network or violates the rules and protocols for communication\n";
	cout << " across the network.\n\n";
	cout << "  Corresponding Source conveyed, and Installation Information provided, in accord with this section must be in a\n";
	cout << " format that is publicly documented (and with an implementation available to the public in source code form), and must\n";
	cout << " require no special password or key for unpacking, reading or copying.\n\n";
	cout << "  7. Additional Terms.\n\n";
	cout << "  \"Additional permissions\" are terms that supplement the terms of this License by making exceptions from one or more\n";
	cout << " of its conditions. Additional permissions that are applicable to the entire Program shall be treated as though they\n";
	cout << " were included in this License, to the extent that they are valid under applicable law. If additional permissions\n";
	cout << " apply only to part of the Program, that part may be used separately under those permissions, but the entire Program\n";
	cout << " remains governed by this License without regard to the additional permissions.\n\n";
	cout << "  When you convey a copy of a covered work, you may at your option remove any additional permissions from that copy,\n";
	cout << " or from any part of it. (Additional permissions may be written to require their own removal in certain cases when you\n";
	cout << " modify the work.) You may place additional permissions on material, added by you to a covered work, for which you\n";
	cout << " have or can give appropriate copyright permission.\n\n";
	cout << "  Notwithstanding any other provision of this License, for material you add to a covered work, you may (if authorized\n";
	cout << " by the copyright holders of that material) supplement the terms of this License with terms:\n\n";
	cout << "    a) Disclaiming warranty or limiting liability differently from the terms of sections 15 and 16 of this License; or\n\n";
	cout << "    b) Requiring preservation of specified reasonable legal notices or author attributions in that material or in the\n";
	cout << "       Appropriate Legal Notices displayed by works containing it; or\n\n";
	cout << "    c) Prohibiting misrepresentation of the origin of that material, or requiring that modified versions of such\n";
	cout << "       material be marked in reasonable ways as different from the original version; or\n\n";
	cout << "    d) Limiting the use for publicity purposes of names of licensors or authors of the material; or\n\n";
	cout << "    e) Declining to grant rights under trademark law for use of some trade names, trademarks, or service marks; or\n\n\n\n";
	cout << red << " PRESS ANY KEY TO CONTINUE " << black;
	user_input = getch();
	if (user_input == 224 || user_input == 0)
		getch();

	system("cls");
	cout << red << "\n PAGE 7 OF 11\n" << black;
	cout << "\n    f) Requiring indemnification of licensors and authors of that material by anyone who conveys the material (or\n";
	cout << "       modified versions of it) with contractual assumptions of liability to the recipient, for any liability that\n";
	cout << "       these contractual assumptions directly impose on those licensors and authors.\n\n";
	cout << "  All other non-permissive additional terms are considered \"further restrictions\" within the meaning of section 10.\n";
	cout << " If the Program as you received it, or any part of it, contains a notice stating that it is governed by this License\n";
	cout << " along with a term that is a further restriction, you may remove that term. If a license document contains a further\n";
	cout << " restriction but permits relicensing or conveying under this License, you may add to a covered work material governed\n";
	cout << " by the terms of that license document, provided that the further restriction does not survive such relicensing or\n";
	cout << " conveying.\n\n";
	cout << "  If you add terms to a covered work in accord with this section, you must place, in the relevant source files, a\n";
	cout << " statement of the additional terms that apply to those files, or a notice indicating where to find the applicable\n";
	cout << " terms.\n\n";
	cout << "  Additional terms, permissive or non-permissive, may be stated in the form of a separately written license, or stated\n";
	cout << " as exceptions; the above requirements apply either way.\n\n";
	cout << "  8. Termination.\n\n";
	cout << "  You may not propagate or modify a covered work except as expressly provided under this License. Any attempt\n";
	cout << " otherwise to propagate or modify it is void, and will automatically terminate your rights under this License\n";
	cout << " (including any patent licenses granted under the third paragraph of section 11).\n\n";
	cout << "  However, if you cease all violation of this License, then your license from a particular copyright holder is\n";
	cout << " reinstated (a) provisionally, unless and until the copyright holder explicitly and finally terminates your license,\n";
	cout << " and (b) permanently, if the copyright holder fails to notify you of the violation by some reasonable means prior to\n";
	cout << " 60 days after the cessation.\n\n";
	cout << "  Moreover, your license from a particular copyright holder is reinstated permanently if the copyright holder notifies\n";
	cout << " you of the violation by some reasonable means, this is the first time you have received notice of violation of this\n";
	cout << " License (for any work) from that copyright holder, and you cure the violation prior to 30 days after your receipt of\n";
	cout << " the notice.\n\n";
	cout << "  Termination of your rights under this section does not terminate the licenses of parties who have received copies or\n";
	cout << " rights from you under this License. If your rights have been terminated and not permanentlyreinstated, you do not\n";
	cout << " qualify to receive new licenses for the same material under section 10.\n\n";
	cout << "  9. Acceptance Not Required for Having Copies.\n\n";
	cout << "  You are not required to accept this License in order to receive or run a copy of the Program. Ancillary propagation\n";
	cout << " of a covered work occurring solely as a consequence of using peer-to-peer transmission to receive a copy likewise\n";
	cout << " does not require acceptance. However, nothing other than this License grants you permission to propagate or modify\n";
	cout << " any covered work. These actions infringe copyright if you do not accept this License. Therefore, by modifying or\n";
	cout << " propagating a covered work, you indicate your acceptance of this License to do so.\n\n\n";
	cout << red << " PRESS ANY KEY TO CONTINUE " << black;
	user_input = getch();
	if (user_input == 224 || user_input == 0)
		getch();

	system("cls");
	cout << red << "\n PAGE 8 OF 11\n" << black;
	cout << "\n  10. Automatic Licensing of Downstream Recipients.\n\n";
	cout << "  Each time you convey a covered work, the recipient automatically receives a license from the original licensors, to\n";
	cout << " run, modify and propagate that work, subject to this License. You are not responsible for enforcing compliance by\n";
	cout << " third parties with this License.\n\n";
	cout << "  An \"entity transaction\" is a transaction transferring control of an organization, or substantially all assets of\n";
	cout << " one, or subdividing an organization, or merging organizations. If propagation of a covered work results from an\n";
	cout << " entity transaction, each party to that transaction who receives a copy of the work also receives whatever licenses to\n";
	cout << " the work the party's predecessor in interest had or could give under the previous paragraph, plus a right to\n";
	cout << " possession of the Corresponding Source of the work from the predecessor in interest, if the predecessor has it or can\n";
	cout << " get it with reasonable efforts.\n\n";
	cout << "  You may not impose any further restrictions on the exercise of the rights granted or affirmed under this License.\n";
	cout << " For example, you may not impose a license fee, royalty, or other charge for exercise of rights granted under this\n";
	cout << " License, and you may not initiate litigation (including a cross-claim or counterclaim in a lawsuit) alleging that any\n";
	cout << " patent claim is infringed by making, using, selling, offering for sale, or importing the Program or any portion of it.\n\n";
	cout << "  11. Patents.\n\n";
	cout << "  A \"contributor\" is a copyright holder who authorizes use under this License of the Program or a work on which the\n";
	cout << " Program is based.  The work thus licensed is called the contributor's \"contributor version\".\n\n";
	cout << "  A contributor's \"essential patent claims\" are all patent claims owned or controlled by the contributor, whether\n";
	cout << " already acquired or hereafter acquired, that would be infringed by some manner, permitted by this License, of making,\n";
	cout << " using, or selling its contributor version, but do not include claims that would be infringed only as a consequence of\n";
	cout << " further modification of the contributor version. For purposes of this definition, \"control\" includes the right to\n";
	cout << " grant patent sublicenses in a manner consistent with the requirements of this License.\n\n";
	cout << "  Each contributor grants you a non-exclusive, worldwide, royalty-free patent license under the contributor's\n";
	cout << " essential patent claims, to make, use, sell, offer for sale, import and otherwise run, modify and propagate the\n";
	cout << " contents of its contributor version.\n\n";
	cout << "  In the following three paragraphs, a \"patent license\" is any express agreement or commitment, however denominated,\n";
	cout << " not to enforce a patent (such as an express permission to practice a patent or covenant not to sue for patent\n";
	cout << " infringement). To \"grant\" such a patent license to a party means to make such an agreement or commitment not to\n";
	cout << " enforce a patent against the party.\n\n";
	cout << "  If you convey a covered work, knowingly relying on a patent license, and the Corresponding Source of the work is not\n";
	cout << " available for anyone to copy, free of charge and under the terms of this License, through a publicly available\n";
	cout << " network server or other readily accessible means, then you must either (1) cause the Corresponding Source to be so\n";
	cout << " available, or (2) arrange to deprive yourself of the benefit of the patent license for this particular work, or (3)\n";
	cout << " arrange, in a manner consistent with the requirements of this License, to extend the patent license to downstream\n";
	cout << " recipients. \"Knowingly relying\" means you have actual knowledge that, but for the patent license, your conveying the\n";
	cout << " covered work in a country, or your recipient's use of the covered work in a country, would infringe one or more\n";
	cout << " identifiable patents in that country that you have reason to believe are valid.\n\n";
	cout << red << " PRESS ANY KEY TO CONTINUE " << black;
	user_input = getch();
	if (user_input == 224 || user_input == 0)
		getch();

	system("cls");
	cout << red << "\n PAGE 9 OF 11\n" << black;
	cout << "\n  If, pursuant to or in connection with a single transaction or arrangement, you convey, or propagate by procuring\n";
	cout << " conveyance of, a covered work, and grant a patent license to some of the parties receiving the covered work\n";
	cout << " authorizing them to use, propagate, modify or convey a specific copy of the covered work, then the patent license you\n";
	cout << " grant is automatically extended to all recipients of the covered work and works based on it.\n\n";
	cout << "  A patent license is \"discriminatory\" if it does not include within the scope of its coverage, prohibits the exercise\n";
	cout << " of, or is conditioned on the non-exercise of one or more of the rights that are specifically granted under this\n";
	cout << " License. You may not convey a covered work if you are a party to an arrangement with a third party that is in the\n";
	cout << " business of distributing software, under which you make payment to the third party based on the extent of your\n";
	cout << " activity of conveying the work, and under which the third party grants, to any of the parties who would receive the\n";
	cout << " covered work from you, a discriminatory patent license (a) in connection with copies of the covered work conveyed by\n";
	cout << " you (or copies made from those copies), or (b) primarily for and in connection with specific products or compilations\n";
	cout << " that contain the covered work, unless you entered into that arrangement, or that patent license was granted, prior to\n";
	cout << " 28 March 2007.\n\n";
	cout << "  Nothing in this License shall be construed as excluding or limiting any implied license or other defenses to\n";
	cout << " infringement that may otherwise be available to you under applicable patent law.\n\n";
	cout << "  12. No Surrender of Others' Freedom.\n\n";
	cout << "  If conditions are imposed on you (whether by court order, agreement or otherwise) that contradict the conditions of\n";
	cout << " this License, they do not excuse you from the conditions of this License. If you cannot convey a covered work so as\n";
	cout << " to satisfy simultaneously your obligations under this License and any other pertinent obligations, then as a\n";
	cout << " consequence you may not convey it at all. For example, if you agree to terms that obligate you to collect a royalty\n";
	cout << " for further conveying from those to whom you convey the Program, the only way you could satisfy both those terms and\n";
	cout << " this License would be to refrain entirely from conveying the Program.\n\n";
	cout << "  13. Use with the GNU Affero General Public License.\n\n";
	cout << "  Notwithstanding any other provision of this License, you have permission to link or combine any covered work with a\n";
	cout << " work licensed under version 3 of the GNU Affero General Public License into a single combined work, and to convey the\n";
	cout << " resulting work. The terms of this License will continue to apply to the part which is the covered work, but the\n";
	cout << " special requirements of the GNU Affero General Public License, section 13, concerning interaction through a network\n";
	cout << " will apply to the combination as such.\n\n";
	cout << "  14. Revised Versions of this License.\n\n";
	cout << "  The Free Software Foundation may publish revised and/or new versions of the GNU General Public License from time to\n";
	cout << " time. Such new versions will be similar in spirit to the present version, but may differ in detail to address new\n";
	cout << " problems or concerns.\n\n";
	cout << "  Each version is given a distinguishing version number. If the Program specifies that a certain numbered version of\n";
	cout << " the GNU General Public License \"or any later version\" applies to it, you have the option of following the terms and\n";
	cout << " conditions either of that numbered version or of any later version published by the Free Software Foundation. If the\n";
	cout << " Program does not specify a version number of the GNU General Public License, you may choose any version ever\n";
	cout << " published by the Free Software Foundation.\n\n";
	cout << red << " PRESS ANY KEY TO CONTINUE " << black;
	user_input = getch();
	if (user_input == 224 || user_input == 0)
		getch();

	system("cls");
	cout << red << "\n PAGE 10 OF 11\n" << black;
	cout << "\n  If the Program specifies that a proxy can decide which future versions of the GNU General Public License can be\n";
	cout << " used, that proxy's public statement of acceptance of a version permanently authorizes you to choose that version for\n";
	cout << " the Program.\n\n";
	cout << "  Later license versions may give you additional or different permissions. However, no additional obligations are\n";
	cout << " imposed on any author or copyright holder as a result of your choosing to follow a later version.\n\n";
	cout << "  15. Disclaimer of Warranty.\n\n";
	cout << "  THERE IS NO WARRANTY FOR THE PROGRAM, TO THE EXTENT PERMITTED BY APPLICABLE LAW. EXCEPT WHEN OTHERWISE STATED IN\n";
	cout << " WRITING THE COPYRIGHT HOLDERS AND/OR OTHER PARTIES PROVIDE THE PROGRAM \"AS IS\" WITHOUT WARRANTY OF ANY KIND, EITHER\n";
	cout << " EXPRESSED OR IMPLIED, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A\n";
	cout << " PARTICULAR PURPOSE. THE ENTIRE RISK AS TO THE QUALITY AND PERFORMANCE OF THE PROGRAM IS WITH YOU. SHOULD THE PROGRAM\n";
	cout << " PROVE DEFECTIVE, YOU ASSUME THE COST OF ALL NECESSARY SERVICING, REPAIR OR CORRECTION.\n\n";
	cout << "  16. Limitation of Liability.\n\n";
	cout << "  IN NO EVENT UNLESS REQUIRED BY APPLICABLE LAW OR AGREED TO IN WRITING WILL ANY COPYRIGHT HOLDER, OR ANY OTHER PARTY\n";
	cout << " WHO MODIFIES AND/OR CONVEYS THE PROGRAM AS PERMITTED ABOVE, BE LIABLE TO YOU FOR DAMAGES, INCLUDING ANY GENERAL,\n";
	cout << " SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES ARISING OUT OF THE USE OR INABILITY TO USE THE PROGRAM (INCLUDING BUT\n";
	cout << " NOT LIMITED TO LOSS OF DATA OR DATA BEING RENDERED INACCURATE OR LOSSES SUSTAINED BY YOU OR THIRD PARTIES OR A\n";
	cout << " FAILURE OF THE PROGRAM TO OPERATE WITH ANY OTHER PROGRAMS), EVEN IF SUCH HOLDER OR OTHER PARTY HAS BEEN ADVISED OF\n";
	cout << " THE POSSIBILITY OF SUCH DAMAGES.\n\n";
	cout << "  17. Interpretation of Sections 15 and 16.\n\n";
	cout << "  If the disclaimer of warranty and limitation of liability provided above cannot be given local legal effect\n";
	cout << " according to their terms, reviewing courts shall apply local law that most closely approximates an absolute waiver of\n";
	cout << " all civil liability in connection with the Program, unless a warranty or assumption of liability accompanies a copy\n";
	cout << " of the Program in return for a fee.\n\n";
	cout << "                                              END OF TERMS AND CONDITIONS\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
	cout << red << " PRESS ANY KEY TO CONTINUE " << black;
	user_input = getch();
	if (user_input == 224 || user_input == 0)
		getch();

	system("cls");
	cout << red << "\n PAGE 11 OF 11\n" << black;
	cout << "\n                                     How to Apply These Terms to Your New Programs\n\n";
	cout << "  If you develop a new program, and you want it to be of the greatest possible use to the public, the best way to\n";
	cout << " achieve this is to make it free software which everyone can redistribute and change under these terms.\n\n";
	cout << "  To do so, attach the following notices to the program.  It is safest to attach them to the start of each source file\n";
	cout << " to most effectively state the exclusion of warranty; and each file should have at least the \"copyright\" line and a\n";
	cout << " pointer to where the full notice is found.\n\n";
	cout << "    <one line to give the program's name and a brief idea of what it does.>\n";
	cout << "    Copyright (C) <year>  <name of author>\n\n";
	cout << "    This program is free software: you can redistribute it and/or modify it under the terms\n";
	cout << "    of the GNU General Public License as published by the Free Software Foundation, either\n";
	cout << "    version 3 of the License, or (at your option) any later version.\n\n";
	cout << "    This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;\n";
	cout << "    without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.\n";
	cout << "    See the GNU General Public License for more details.\n\n";
	cout << "    You should have received a copy of the GNU General Public License along with this program.\n";
	cout << "    If not, see <http://www.gnu.org/licenses/>.\n\n";
	cout << " Also add information on how to contact you by electronic and paper mail.\n\n";
	cout << "  If the program does terminal interaction, make it output a short notice like this when it starts in an interactive\n";
	cout << " mode:\n\n";
	cout << "    <program>  Copyright (C) <year>  <name of author>\n";
	cout << "    This program comes with ABSOLUTELY NO WARRANTY; for details type 'show w'.\n";
	cout << "    This is free software, and you are welcome to redistribute it under certain conditions;\n";
	cout << "    type 'show c' for details.\n\n";
	cout << " The hypothetical commands 'show w' and 'show c' should show the appropriate parts of the General Public License.\n";
	cout << " Of course, your program's commands might be different; for a GUI interface, you would use an \"about box\".\n\n";
	cout << "  You should also get your employer (if you work as a programmer) or school, if any, to sign a \"copyright disclaimer\"\n";
	cout << " for the program, if necessary. For more information on this, and how to apply and follow the GNU GPL, see\n";
	cout << " <http://www.gnu.org/licenses/>.\n\n";
	cout << "  The GNU General Public License does not permit incorporating your program into proprietary programs. If your program\n";
	cout << " is a subroutine library, you may consider it more useful to permit linking proprietary applications with the library.\n";
	cout << " If this is what you want to do, use the GNU Lesser General Public License instead of this License. But first, please\n";
	cout << " read <http://www.gnu.org/philosophy/why-not-lgpl.html>.\n\n\n\n";
	cout << red << " PRESS ANY KEY TO RETURN TO MAIN MENU " << black;
	user_input = getch();
	if (user_input == 224 || user_input == 0)
		getch();
	system("mode 119, 40");	
	system("cls");
}