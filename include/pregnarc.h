/****************************************************************************\
 *                                 PregNARC                                 *
 *                                                                          *
 *                    Copyright © 2020 Alexander Nicholi                    *
 *                Released under Mozilla Public License 2.0.                *
\****************************************************************************/

#ifndef INC_API__PREGNARC_H
#define INC_API__PREGNARC_H

#include <uni/types/int.h>

enum
{
	NARC_ERR_NONE = 0,
	NARC_ERR_BADINFILE,
	NARC_ERR_BADINDIR,
	NARC_ERR_BADHEADID,
	NARC_ERR_BADBOM,
	NARC_ERR_BADVER,
	NARC_ERR_BADHEADSZ,
	NARC_ERR_BADCHUNKCT,
	NARC_ERR_BADFATID,
	NARC_ERR_BADFATRESERVED,
	NARC_ERR_BADFNTID,
	NARC_ERR_BADFNTENTRYID,
	NARC_ERR_BADFIMGID,
	NARC_ERR_BADOUTFILE,
	NARC_ERR_TOOMANYFILES
};

struct narc_header
{
	u32 id;
	u16 bom, ver;
	u32 filesz;
	u16 chunksz, chunkct;
};

struct narc_fat
{
	u32 id, chunksz;
	u16 filect, reserved;
};

struct narc_fatentry
{
	u32 start, end;
};

struct narc_fnt
{
	u32 id, chunksz;
};

struct narc_fntentry
{
	u32 offs;
	u16 first_fid, util;
};

struct narc_fileimg
{
	u32 id, chunksz;
};

int narc_pack( const char*, const char* );
int narc_unpack( const char*, const char* );

#endif /* INC_API__PREGNARC_H */
