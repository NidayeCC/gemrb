/* GemRB - Infinity Engine Emulator
 * Copyright (C) 2003 The GemRB Project
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 *
 * $Header: /data/gemrb/cvs2svn/gemrb/gemrb/gemrb/plugins/Core/Font.cpp,v 1.28 2004/02/24 22:20:36 balrog994 Exp $
 *
 */

#include "../../includes/win32def.h"
#include "Font.h"
#include "Interface.h"

extern Interface* core;
unsigned long lastX = 0;

#define PARAGRAPH_START_X 5;

inline size_t mystrlen(const char* string)
{
	if (!string) {
		return ( size_t ) 0;
	}
	const char* tmp = string;
	size_t count = 0;
	while (*tmp != 0) {
		if (( ( unsigned char ) * tmp ) >= 0xf0) {
			tmp += 3;
			count += 3;
		}
		count++;
		tmp++;
	}
	return count;
}

Font::Font(int w, int h, void* palette, bool cK, int index)
{
	lastX = 0;
	count = 0;
	void* pixels = malloc( w* h );
	sprBuffer = core->GetVideoDriver()->CreateSprite8( w, h, 8, pixels,
											palette, cK, index );
	this->palette = core->GetVideoDriver()->GetPalette( sprBuffer );
	maxHeight = h;
}

Font::~Font(void)
{
	free( palette );
	core->GetVideoDriver()->FreeSprite( sprBuffer );
	/*
	Since we assume that the font was loaded from a factory Object,
	we don't need to free the sprites, those will be freed directly
	by the Factory Object destructor.
	*/
	/*
	std::vector<Sprite2D*>::iterator m;
	for(; chars.size() != 0; ) {
	m = chars.begin();
		core->GetVideoDriver()->FreeSprite((*m));
		chars.erase(m);
	}
	*/
}

void Font::AddChar(void* spr, int w, int h, short xPos, short yPos)
{
	if (!spr) {
		size[count].x = 0;
		size[count].y = 0;
		size[count].w = 0;
		size[count].h = 0;
		this->xPos[count] = 0;
		this->yPos[count] = 0;
		count++;
		return;
	}
	unsigned char * startPtr = ( unsigned char * ) sprBuffer->pixels;
	unsigned char * currPtr;
	unsigned char * srcPtr = ( unsigned char * ) spr;
	for (int y = 0; y < h; y++) {
		currPtr = startPtr + ( y * sprBuffer->Width ) + lastX;
		memcpy( currPtr, srcPtr, w );
		srcPtr += w;
	}
	size[count].x = lastX;
	size[count].y = 0;
	size[count].w = w;
	size[count].h = h;
	this->xPos[count] = xPos;
	this->yPos[count] = yPos;
	count++;
	lastX += w;
	/*if(count == 0) {
		palette = core->GetVideoDriver()->GetPalette(spr);
	}
	if(maxHeight < spr->YPos)
		maxHeight = spr->YPos;
	//chars.push_back(spr);	
	chars[count++] = spr;*/
}

bool written = false;

void Font::PrintFromLine(int startrow, Region rgn, unsigned char* string,
	Color* hicolor, unsigned char Alignment, bool anchor, Font* initials,
	Color* initcolor, Sprite2D* cursor, int curpos)
{
	Color* pal = NULL, * ipal = NULL;
	unsigned long psx = PARAGRAPH_START_X;
	pal = hicolor;
	if (ipal != NULL) {
		ipal = initcolor;
	} else {
		ipal = pal;
	}
	if (!pal) {
		pal = palette;
	}
	/*for(int i = 0; i < 255; i++) {
		core->GetVideoDriver()->SetPalette(chars[i], pal);
	}*/
	core->GetVideoDriver()->SetPalette( sprBuffer, pal );
	Video* video = core->GetVideoDriver();
	size_t len = strlen( ( char* ) string );
	char* tmp = ( char* ) malloc( len + 1 );
	memcpy( tmp, ( char * ) string, len + 1 );
	SetupString( tmp, rgn.w );
	int ystep = 0;
	if (Alignment & IE_FONT_SINGLE_LINE) {
		for (size_t i = 0; i < len; i++) {
			if (tmp[i] != 0)
				if (ystep < yPos[( unsigned char ) tmp[i] - 1])//chars[(unsigned char)tmp[i]-1]->YPos)
					ystep = yPos[( unsigned char ) tmp[i] - 1];//chars[(unsigned char)tmp[i]-1]->YPos;
		}
	} else {
		ystep = size[1].h;
	}//chars[1]->Height;
	int x = psx, y = ystep;
	if (Alignment & IE_FONT_ALIGN_CENTER) {
		int w = CalcStringWidth( tmp );
		x = ( rgn.w / 2 ) - ( w / 2 );
	} else if (Alignment & IE_FONT_ALIGN_RIGHT) {
		int w = CalcStringWidth( tmp );
		x = ( rgn.w - w );
	}
	if (Alignment & IE_FONT_ALIGN_MIDDLE) {
		int h = 0;
		for (size_t i = 0; i <= len; i++) {
			if (( tmp[i] == 0 ) || ( tmp[i] == '\n' ))
				h++;
		}
		h = h * ystep;
		y += ( rgn.h / 2 ) - ( h / 2 );
	}
	int row = 0;
	for (size_t i = 0; i < len; i++) {
		if (( ( unsigned char ) tmp[i] ) == '[') {
			i++;
			char tag[256];
			int k = 0;
			for (k = 0; k < 256; k++) {
				if (tmp[i] == ']') {
					tag[k] = 0;
					break;
				}
				tag[k] = tmp[i++];
			}
			if (strnicmp( tag, "color=", 6 ) == 0) {
				unsigned int r,g,b;
				if (sscanf( tag, "color=%02X%02X%02X", &r, &g, &b ) != 3)
					continue;
				Color c = {r,g, b, 0}, back = {0, 0, 0, 0};
				Color* newPal = core->GetVideoDriver()->CreatePalette( c,
															back );
				core->GetVideoDriver()->SetPalette( sprBuffer, newPal );
				free( newPal );
			} else {
				if (stricmp( tag, "/color" ) == 0) {
					core->GetVideoDriver()->SetPalette( sprBuffer, pal );
				} else {
					if (stricmp( "p", tag ) == 0) {
						psx = x;
					} else {
						if (stricmp( "/p", tag ) == 0) {
							psx = PARAGRAPH_START_X;
						}
					}
				}
			}
			continue;
		}
		if (row < startrow) {
			if (tmp[i] == 0) {
				row++;
			}
			continue;
		}
		if (( tmp[i] == 0 ) || ( tmp[i] == '\n' )) {
			y += ystep;
			x = psx;
			if (Alignment & IE_FONT_ALIGN_CENTER) {
				int w = CalcStringWidth( &tmp[i + 1] );
				x = ( rgn.w / 2 ) - ( w / 2 );
			} else if (Alignment & IE_FONT_ALIGN_RIGHT) {
				int w = CalcStringWidth( &tmp[i + 1] );
				x = ( rgn.w - w );
			}
			continue;
		}
		unsigned char currChar = ( unsigned char ) tmp[i] - 1;
		x += xPos[currChar];//spr->XPos;
		video->BlitSpriteRegion( sprBuffer, size[currChar],
				x + rgn.x - xPos[currChar], y + rgn.y - yPos[currChar], true,
				&rgn );
		if (cursor && ( curpos == i ))
			video->BlitSprite( cursor, x - xPos[currChar] + rgn.x, y + rgn.y,
					true, &rgn );
		x += size[currChar].w - xPos[currChar];
	}
	if (cursor && ( curpos == len )) {
		video->BlitSprite( cursor, x - xPos[tmp[len] - 1] + rgn.x, y + rgn.y,
				true, &rgn );
	}
	free( tmp );
}

void Font::Print(Region rgn, unsigned char* string, Color* hicolor,
	unsigned char Alignment, bool anchor, Font* initials, Color* initcolor,
	Sprite2D* cursor, int curpos)
{
	Color* pal = NULL, * ipal = NULL;
	unsigned long psx = PARAGRAPH_START_X;
	pal = hicolor;
	if (ipal != NULL) {
		ipal = initcolor;
	} else {
		ipal = pal;
	}
	if (!pal) {
		pal = palette;
	}
	//for(int i = 0; i < 255; i++) {
	//	core->GetVideoDriver()->SetPalette(chars[i], pal);
	//}
	core->GetVideoDriver()->SetPalette( sprBuffer, pal );
	Video* video = core->GetVideoDriver();
	size_t len = strlen( ( char* ) string );
	char* tmp = ( char* ) malloc( len + 1 );
	memcpy( tmp, ( char * ) string, len + 1 );
	SetupString( tmp, rgn.w );
	int ystep = 0;
	if (Alignment & IE_FONT_SINGLE_LINE) {
		for (size_t i = 0; i < len; i++) {
			if (tmp[i] != 0)
				if (ystep < yPos[( unsigned char ) tmp[i] - 1])//chars[(unsigned char)tmp[i]-1]->YPos)
					ystep = yPos[( unsigned char ) tmp[i] - 1];//chars[(unsigned char)tmp[i]-1]->YPos;
		}
	} else {
		ystep = size[1].h;
	}//chars[1]->Height;
	int x = psx, y = ystep;
	if (Alignment & IE_FONT_ALIGN_CENTER) {
		int w = CalcStringWidth( tmp );
		x = ( rgn.w / 2 ) - ( w / 2 );
	} else if (Alignment & IE_FONT_ALIGN_RIGHT) {
		int w = CalcStringWidth( tmp );
		x = ( rgn.w - w );
	}
	if (Alignment & IE_FONT_ALIGN_MIDDLE) {
		int h = 0;
		for (size_t i = 0; i <= len; i++) {
			if (tmp[i] == 0)
				h++;
		}
		h = h * ystep;
		y += ( rgn.h / 2 ) - ( h / 2 );
	} else if (Alignment & IE_FONT_ALIGN_TOP) {
		y += 5;
	}
	for (size_t i = 0; i < len; i++) {
		if (( ( unsigned char ) tmp[i] ) == '[') {
			i++;
			char tag[256];
			for (int k = 0; k < 256; k++) {
				if (tmp[i] == ']') {
					tag[k] = 0;
					break;
				}
				tag[k] = tmp[i++];
			}
			if (strnicmp( tag, "color=", 6 ) == 0) {
				unsigned int r,g,b;
				if (sscanf( tag, "color=%02X%02X%02X", &r, &g, &b ) != 3)
					continue;
				Color c = {r,g, b, 0}, back = {0, 0, 0, 0};
				Color* newPal = core->GetVideoDriver()->CreatePalette( c,
															back );
				core->GetVideoDriver()->SetPalette( sprBuffer, newPal );
				free( newPal );
			} else {
				if (stricmp( tag, "/color" ) == 0) {
					core->GetVideoDriver()->SetPalette( sprBuffer, pal );
				} else {
					if (stricmp( "p", tag ) == 0) {
						psx = x;
					} else {
						if (stricmp( "/p", tag ) == 0) {
							psx = PARAGRAPH_START_X;
						}
					}
				}
			}
			continue;
		}
		if (tmp[i] == 0) {
			y += ystep;
			x = psx;
			if (Alignment & IE_FONT_ALIGN_CENTER) {
				int w = CalcStringWidth( &tmp[i + 1] );
				x = ( rgn.w / 2 ) - ( w / 2 );
			} else if (Alignment & IE_FONT_ALIGN_RIGHT) {
				int w = CalcStringWidth( &tmp[i + 1] );
				x = ( rgn.w - w );
			}
			continue;
		}
		unsigned char currChar = ( unsigned char ) tmp[i] - 1;
		x += xPos[currChar];//spr->XPos;
		video->BlitSpriteRegion( sprBuffer, size[currChar],
				x + rgn.x - xPos[currChar], y + rgn.y - yPos[currChar],
				anchor, &rgn );
		if (cursor && ( curpos == i ))
			video->BlitSprite( cursor, x - xPos[currChar] + rgn.x, y + rgn.y,
					anchor, &rgn );
		x += size[currChar].w - xPos[currChar];//spr->Width-spr->XPos;
	}
	if (cursor && ( curpos == len )) {
		video->BlitSprite( cursor, x - xPos[tmp[len] - 1] + rgn.x, y + rgn.y,
				anchor, &rgn );
	}
	free( tmp );
}

int Font::CalcStringWidth(char* string)
{
	size_t ret = 0, len = strlen( string );
	for (size_t i = 0; i < len; i++) {
		if (( ( unsigned char ) string[i] ) == '[') {
			i++;
			char tag[256];
			int k = 0;
			for (k = 0; k < 256; k++) {
				if (string[i] == ']') {
					tag[k] = 0;
					break;
				}
				tag[k] = string[i++];
			}
			continue;
		}
		ret += size[( unsigned char ) string[i] - 1].w;//chars[(unsigned char)string[i]-1]->Width;
	}
	return ( int ) ret;
}

void Font::SetupString(char* string, int width)
{
	size_t len = strlen( string );
	unsigned long psx = PARAGRAPH_START_X;
	int lastpos = 0;
	int x = psx, wx = 0;
	bool endword = false;
	for (size_t pos = 0; pos < len; pos++) {
		if (x + wx > width) {
			if (!endword && ( x == psx ))
				lastpos = ( int ) pos;
			string[lastpos] = 0;
			x = psx;
		}
		if (string[pos] == 0) {
			continue;
		}
		endword = false;
		if (string[pos] == '\r')
			string[pos] = ' ';
		if (string[pos] == '\n') {
			string[pos] = 0;
			x = psx;
			wx = 0;
			lastpos = ( int ) pos;
			endword = true;
			continue;
		}
		if (( ( unsigned char ) string[pos] ) == '[') {
			pos++;
			char tag[256];
			int k = 0;
			for (k = 0; k < 256; k++) {
				if (string[pos] == ']') {
					tag[k] = 0;
					break;
				}
				tag[k] = string[pos++];
			}
			if (stricmp( "p", tag ) == 0) {
				psx = x;
			} else {
				if (stricmp( "/p", tag ) == 0) {
					psx = PARAGRAPH_START_X;
				}
			}
			continue;
		}
		wx += size[( unsigned char ) string[pos] - 1].w;//chars[((unsigned char)string[pos])-1]->Width;
		if (( string[pos] == ' ' ) || ( string[pos] == '-' )) {
			x += wx;
			wx = 0;
			lastpos = ( int ) pos;
			endword = true;
		}
	}
}

void* Font::GetPalette()
{
	return palette;
}
