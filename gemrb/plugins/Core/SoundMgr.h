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
 * $Header: /data/gemrb/cvs2svn/gemrb/gemrb/gemrb/plugins/Core/SoundMgr.h,v 1.15 2004/08/21 04:53:56 divide Exp $
 *
 */

#ifndef SOUNDMGR_H
#define SOUNDMGR_H

#include <vector>
#include <string>
#include "Plugin.h"
#include "../../includes/globals.h"

class Ambient;

#define GEM_SND_RELATIVE 1
#define GEM_SND_SPEECH   IE_STR_SPEECH // 4
#define GEM_SND_VOL_MUSIC    1
#define GEM_SND_VOL_AMBIENTS 2

#ifdef WIN32

#ifdef GEM_BUILD_DLL
#define GEM_EXPORT __declspec(dllexport)
#else
#define GEM_EXPORT __declspec(dllimport)
#endif

#else
#define GEM_EXPORT
#endif

class GEM_EXPORT SoundMgr : public Plugin {
public:
	SoundMgr(void);
	virtual ~SoundMgr(void);
	virtual bool Init(void) = 0;
	virtual unsigned long Play(const char* ResRef, int XPos = 0, int YPos = 0, unsigned long flags = GEM_SND_RELATIVE) = 0;
	virtual unsigned long StreamFile(const char* filename) = 0;
	virtual bool Stop() = 0;
	virtual bool Play() = 0;
	virtual void ResetMusics() = 0;
	virtual void UpdateViewportPos(int XPos, int YPos) = 0;
	// update volumes (possibly on-the-fly)
	virtual void UpdateVolume( unsigned long = GEM_SND_VOL_MUSIC | GEM_SND_VOL_AMBIENTS ) {}
	class AmbientMgr {
	public:
		AmbientMgr() {}
		virtual ~AmbientMgr() { reset(); }
		virtual void reset() { ambients = std::vector<Ambient *> (); }
		virtual void setAmbients(const std::vector<Ambient *> &a) { reset(); ambients = a; activate(); }
		virtual void activate(const std::string &name);
		virtual void activate() { active = true; } // hard play ;-)
		virtual void deactivate(const std::string &name);
		virtual void deactivate() { active = false; } // hard stop
		virtual bool isActive(const std::string &name) const;
	protected:
		std::vector<Ambient *> ambients;
		bool active;
	};
	virtual AmbientMgr *GetAmbientMgr() { return ambim; }
protected:
	AmbientMgr *ambim;
};

#endif
