/****************************************************************************\
 *                                 PregNARC                                 *
 *                                                                          *
 *                    Copyright © 2020 Alexander Nicholi                    *
 *                Released under Mozilla Public License 2.0.                *
\****************************************************************************/

#include "narc.h"

#include <dirent.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <uni/arr.h>
#include <uni/memory.h>
#include <unistd.h>

#define ASSERT_RETVAL(cnd, ret) do{if(cnd){}else{return (ret);}}while(0)

int narc_pack( const char* fpath, const char* dpath )
{
	FILE* file;
	DIR* dir;
	struct dirent* entry;
	struct uni_arr* fatentries;
	struct narc_fat fat;
	char pathtmp[1024];
	unsigned dirct = 1;

	file = fopen( fpath, "rb" );
	ASSERT_RETVAL( file != NULL, NARC_ERR_BADINFILE );
	dir = opendir(dpath);
	ASSERT_RETVAL( dir != NULL, NARC_ERR_BADINDIR );

	fatentries = uni_arr_init( sizeof( struct narc_fatentry ) );

	while((entry = readdir(dir)) != NULL)
	{
		if (entry->d_type == DT_DIR)
		{
			if(uni_strequ(entry->d_name, ".") || strcmp(entry->d_name, ".."))
			{
				continue;
			}

			dirct++;

			continue;
		}

		{
			struct narc_fatentry fatentry = { 0, 0 };
			ptri arrsz = uni_arr_getsz( fatentries );

			if(arrsz > 1)
			{
				struct rangep range = { arrsz - 1, arrsz };
				struct narc_fatentry* madeentry = uni_arr_mkslice( fatentries, range );
				struct stat st;

				stat(entry->d_name, &st );

				/* align the start to the nearest 32-bit word boundary */
				fatentry.start = ((madeentry->end >> 2) << 2) == madeentry->end ?
					madeentry->end : ((madeentry->end >> 2) << 2) + 4;
				fatentry.end = fatentry.start + st.st_size;
			}
		}
	}

	closedir(dir);

	{
		const ptri fatentryct = uni_arr_getsz( fatentries );

		ASSERT_RETVAL( fatentryct <= U16_MAX, NARC_ERR_TOOMANYFILES );

		fat.id = 0x46415442;
		fat.chunksz = (u32)(sizeof(struct narc_fat) +
			(sizeof(struct narc_fatentry) * fatentryct ));
		fat.filect = (u16)fatentryct;
		fat.reserved = 0;
	}

	/* TODO: deal with FNT entries, create header, serialise, write to file */

	return 0;
}

int narc_unpack( const char* fpath, const char* dpath )
{
	/* TODO: implement narc_unpack() */
	return 0;
}
