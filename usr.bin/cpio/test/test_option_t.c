/*-
 * Copyright (c) 2003-2007 Tim Kientzle
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR(S) ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR(S) BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#include "test.h"
__FBSDID("$FreeBSD$");


DEFINE_TEST(test_option_t)
{
	char *p;
	int r;

	/* List reference archive, make sure the TOC is correct. */
	extract_reference_file("test_option_t.cpio");
	r = systemf("%s -it < test_option_t.cpio >it.out 2>it.err", testprog);
	assertEqualInt(r, 0);
	assertTextFileContents("1 block\n", "it.err");
	extract_reference_file("test_option_t.stdout");
	p = slurpfile(NULL, "test_option_t.stdout");
	assertTextFileContents(p, "it.out");
	free(p);

	/* We accept plain "-t" as a synonym for "-it" */
	r = systemf("%s -t < test_option_t.cpio >t.out 2>t.err", testprog);
	assertEqualInt(r, 0);
	assertTextFileContents("1 block\n", "t.err");
	extract_reference_file("test_option_t.stdout");
	p = slurpfile(NULL, "test_option_t.stdout");
	assertTextFileContents(p, "t.out");
	free(p);

	/* But "-ot" is an error. */
	assert(0 != systemf("%s -ot < test_option_t.cpio >ot.out 2>ot.err",
			    testprog));
	assertEmptyFile("ot.out");

	/* List reference archive verbosely, make sure the TOC is correct. */
	r = systemf("%s -itv < test_option_t.cpio >tv.out 2>tv.err", testprog);
	assertEqualInt(r, 0);
	assertTextFileContents("1 block\n", "tv.err");
	extract_reference_file("test_option_tv.stdout");

	/* This doesn't work because the usernames on different systems
	 * are different and cpio now looks up numeric UIDs on
	 * the local system. */
	/* assertEqualFile("tv.out", "test_option_tv.stdout"); */

	/* List reference archive with numeric IDs, verify TOC is correct. */
	r = systemf("%s -itnv < test_option_t.cpio >itnv.out 2>itnv.err",
		    testprog);
	assertEqualInt(r, 0);
	assertTextFileContents("1 block\n", "itnv.err");
	extract_reference_file("test_option_tnv.stdout");
	/* This does work because numeric IDs come from archive. */
	/* Unfortunately, the timestamp still gets localized, so
	 * we can't just compare against a fixed result. */
	/* TODO: Fix this. */
	/* assertEqualFile("itnv.out", "test_option_tnv.stdout"); */

	/* But "-n" without "-t" is an error. */
	assert(0 != systemf("%s -in < test_option_t.cpio >in.out 2>in.err",
			    testprog));
	assertEmptyFile("in.out");
}
