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
 * $Header: /data/gemrb/cvs2svn/gemrb/gemrb/gemrb/plugins/KEYImporter/KeyImp.h,v 1.6 2004/02/24 22:20:40 balrog994 Exp $
 *
 */

#ifndef KEYIMP_H
#define KEYIMP_H

#include <vector>
#include "../Core/ResourceMgr.h"
#include "Dictionary.h"

typedef struct RESEntry {
	char ResRef[8];
	unsigned short Type;
	unsigned long ResLocator;
} RESEntry;

typedef struct BIFEntry {
	char* name;
	unsigned short BIFLocator;
} BIFEntry;

class KeyImp : public ResourceMgr {
private:
	std::vector< BIFEntry> biffiles;
	Dictionary resources;
public:
	KeyImp(void);
	~KeyImp(void);
	bool LoadResFile(const char* resfile);
	DataStream* GetResource(const char* resname, SClass_ID type);
	void* GetFactoryResource(const char* resname, SClass_ID type,
		unsigned char mode = IE_NORMAL);
public:
	void release(void)
	{
		delete this;
	}
};

#endif
