/* GemRB - Infinity Engine Emulator
 * Copyright (C) 2003 The GemRB Project
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 *
 * $Header: /data/gemrb/cvs2svn/gemrb/gemrb/gemrb/plugins/ZLibMgr/ZLibManager.h,v 1.5 2004/02/24 22:20:35 balrog994 Exp $
 *
 */

#ifndef ZLIBMANAGER_H
#define ZLIBMANAGER_H

#include "../Core/Compressor.h"

class ZLibManager : public Compressor {
public:
	ZLibManager(void);
	~ZLibManager(void);
	// ZLib Decompression Routine
	int Decompress(FILE* dest, DataStream* source);
public:
	void release(void)
	{
		delete this;
	}
};

#endif
