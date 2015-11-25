/*
 * Copyright (c) 2009, 2010, 2013
 * Phillip Lougher <phillip@squashfs.org.uk>
 * Copyright (c) 2015
 * Dmitry Janushkevich <gauri@tut.by>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2,
 * or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 *
 * lzma_zlib_wrapper.c
 *
 * Support for LZMA1 compression using LZMA or ZLIB, whichever is better.
 */

#include <LzmaLib.h>
#include <zlib.h>

#include "squashfs_fs.h"
#include "compressor.h"

#define LZMA_HEADER_SIZE	(LZMA_PROPS_SIZE + 8)

extern int lzma_compress(void *strm, void *dest, void *src, int size, int block_size,
		int *error);

extern int lzma_uncompress(void *dest, void *src, int size, int outsize,
	int *error);


static int zlib_compress(void *strm, void *dest, void *src, int size, int block_size,
		int *error)
{
	/* XXX: Not implemented currently. */
	*error = -42;
	return -1;
}

static int zlib_uncompress(void *dest, void *src, int size, int outsize,
	int *error)
{
	int res;
	unsigned long bytes = outsize;

	res = uncompress(dest, &bytes, src, size);

	if(res == Z_OK)
		return (int) bytes;
	else {
		*error = res;
		return -1;
	}
}


static int lzma_zlib_compress(void *strm, void *dest, void *src, int size, int block_size,
		int *error)
{
	/* XXX: Not implemented currently. */
	*error = -42;
	return -1;
}

static int lzma_zlib_uncompress(void *dest, void *src, int size, int outsize,
	int *error)
{
	unsigned char *s = src;

	if(s[0] == 0x5D)
		return lzma_uncompress(dest, src, size, outsize, error);
	else
		return zlib_uncompress(dest, src, size, outsize, error);
}


struct compressor lzma_zlib_comp_ops = {
	.init = NULL,
	.compress = lzma_zlib_compress,
	.uncompress = lzma_zlib_uncompress,
	.options = NULL,
	.usage = NULL,
	.id = LZMA_ZLIB_COMPRESSION,
	.name = "lzma+zlib",
	.supported = 1
};

