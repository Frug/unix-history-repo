/*
 * Copyright (c) 1994, Paul Richards.
 *
 * All rights reserved.
 *
 * This software may be used, modified, copied, distributed, and
 * sold, in both source and binary form provided that the above
 * copyright and these terms are retained, verbatim, as the first
 * lines of this file.  Under no circumstances is the author
 * responsible for the proper functioning of this software, nor does
 * the author assume any responsibility for damages incurred with
 * its use.
 */

#define BOOT1 "/stand/sdboot"
#define BOOT2 "/stand/bootsd"

/* XXX -- calculate these, this is nasty */
#define DEFFSIZE 1024
#define DEFFRAG 8

int Mb_to_cylbdry(int, struct disklabel *);
void default_disklabel(struct disklabel *, int, int);
int disk_size(struct disklabel *);
