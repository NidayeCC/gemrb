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
 * $Header: /data/gemrb/cvs2svn/gemrb/gemrb/gemrb/plugins/ACMImporter/decoder.cpp,v 1.3 2004/02/24 22:20:37 balrog994 Exp $
 *
 */

//#include "stdafx.h"

#include <stdlib.h>
#include "decoder.h"

int CSubbandDecoder::init_decoder()
{
	int memory_size = ( levels == 0 ) ? 0 : ( 3 * ( block_size >> 1 ) - 2 );
	if (memory_size) {
		memory_buffer = ( long * ) calloc( memory_size, sizeof( long ) );
		if (!memory_buffer)
			return 0;
	}
	return 1;
}
void CSubbandDecoder::decode_data(long* buffer, int blocks)
{
	if (!levels) {
		return;
	} // no levels - no work

	long* buff_ptr = buffer, * mem_ptr = memory_buffer;
	int sb_size = block_size >> 1; // current subband size

	blocks <<= 1;
	sub_4d3fcc( ( short * ) mem_ptr, buff_ptr, sb_size, blocks );
	mem_ptr += sb_size;

	for (int i = 0; i < blocks; i++)
		buff_ptr[i * sb_size]++;

	sb_size >>= 1;
	blocks <<= 1;

	while (sb_size != 0) {
		sub_4d420c( mem_ptr, buff_ptr, sb_size, blocks );
		mem_ptr += sb_size << 1;
		sb_size >>= 1;
		blocks <<= 1;
	}
}
void CSubbandDecoder::sub_4d3fcc(short* memory, long* buffer, int sb_size,
	int blocks)
{
	long row_0, row_1, row_2, row_3, db_0, db_1;
	int i;
	int sb_size_2 = sb_size * 2, sb_size_3 = sb_size * 3;
	if (blocks == 2) {
		for (i = 0; i < sb_size; i++) {
			row_0 = buffer[0];
			row_1 = buffer[sb_size];
			buffer[0] = buffer[0] + memory[0] + 2 * memory[1];
			buffer[sb_size] = 2 * row_0 - memory[1] - buffer[sb_size];
			memory[0] = ( short ) row_0;
			memory[1] = ( short ) row_1;

			memory += 2;
			buffer++;
		}
	} else if (blocks == 4) {
		for (i = 0; i < sb_size; i++) {
			row_0 = buffer[0];
			row_1 = buffer[sb_size];
			row_2 = buffer[sb_size_2];
			row_3 = buffer[sb_size_3];

			buffer[0] = memory[0] + 2 * memory[1] + row_0;
			buffer[sb_size] = -memory[1] + 2 * row_0 - row_1;
			buffer[sb_size_2] = row_0 + 2 * row_1 + row_2;
			buffer[sb_size_3] = -row_1 + 2 * row_2 - row_3;

			memory[0] = ( short ) row_2;
			memory[1] = ( short ) row_3;

			memory += 2;
			buffer++;
		}
	} else {
		for (i = 0; i < sb_size; i++) {
			long* buff_ptr = buffer;
			if (( blocks >> 1 ) & 1 != 0) {
				row_0 = buff_ptr[0];
				row_1 = buff_ptr[sb_size];

				buff_ptr[0] = memory[0] + 2 * memory[1] + row_0;
				buff_ptr[sb_size] = -memory[1] + 2 * row_0 - row_1;
				buff_ptr += sb_size_2;

				db_0 = row_0;
				db_1 = row_1;
			} else {
				db_0 = memory[0];
				db_1 = memory[1];
			}

			for (int j = 0; j < blocks >> 2; j++) {
				row_0 = buff_ptr[0];  buff_ptr[0] = db_0 + 2 * db_1 + row_0;  buff_ptr += sb_size;
				row_1 = buff_ptr[0];  buff_ptr[0] = -db_1 + 2 * row_0 - row_1;  buff_ptr += sb_size;
				row_2 = buff_ptr[0];  buff_ptr[0] = row_0 + 2 * row_1 + row_2;  buff_ptr += sb_size;
				row_3 = buff_ptr[0];  buff_ptr[0] = -row_1 + 2 * row_2 -
					row_3;  buff_ptr += sb_size;

				db_0 = row_2;
				db_1 = row_3;
			}
			memory[0] = ( short ) row_2;
			memory[1] = ( short ) row_3;
			memory += 2;
			buffer++;
		}
	}
}
void CSubbandDecoder::sub_4d420c(long* memory, long* buffer, int sb_size,
	int blocks)
{
	long row_0, row_1, row_2, row_3, db_0, db_1;
	int i;
	int sb_size_2 = sb_size * 2, sb_size_3 = sb_size * 3;
	if (blocks == 4) {
		for (i = 0; i < sb_size; i++) {
			row_0 = buffer[0];
			row_1 = buffer[sb_size];
			row_2 = buffer[sb_size_2];
			row_3 = buffer[sb_size_3];

			buffer[0] = memory[0] + 2 * memory[1] + row_0;
			buffer[sb_size] = -memory[1] + 2 * row_0 - row_1;
			buffer[sb_size_2] = row_0 + 2 * row_1 + row_2;
			buffer[sb_size_3] = -row_1 + 2 * row_2 - row_3;

			memory[0] = row_2;
			memory[1] = row_3;

			memory += 2;
			buffer++;
		}
	} else {
		for (i = 0; i < sb_size; i++) {
			long* buff_ptr = buffer;
			db_0 = memory[0]; db_1 = memory[1];
			for (int j = 0; j < blocks >> 2; j++) {
				row_0 = buff_ptr[0];  buff_ptr[0] = db_0 + 2 * db_1 + row_0;  buff_ptr += sb_size;
				row_1 = buff_ptr[0];  buff_ptr[0] = -db_1 + 2 * row_0 - row_1;  buff_ptr += sb_size;
				row_2 = buff_ptr[0];  buff_ptr[0] = row_0 + 2 * row_1 + row_2;  buff_ptr += sb_size;
				row_3 = buff_ptr[0];  buff_ptr[0] = -row_1 + 2 * row_2 -
					row_3;  buff_ptr += sb_size;

				db_0 = row_2;
				db_1 = row_3;
			}
			memory[0] = row_2;
			memory[1] = row_3;

			memory += 2;
			buffer++;
		}
	}
}
