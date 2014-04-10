/*
 * Copyright (C) 2012 Mark Hills <mark@xwax.org>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * version 2, as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License version 2 for more details.
 *
 * You should have received a copy of the GNU General Public License
 * version 2 along with this program; if not, write to the Free
 * Software Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 *
 */

#include <sched.h>
#include <stdio.h>

#include "sched.h"

#define REALTIME_PRIORITY 80

int go_realtime(void)
{
	int max_pri;
	struct sched_param sp;

	if (sched_getparam(0, &sp)) {
		perror("sched_getparam");
		return -1;
	}

	max_pri = sched_get_priority_max(SCHED_FIFO);
	sp.sched_priority = REALTIME_PRIORITY;

	if (sp.sched_priority > max_pri) {
		fprintf(stderr, "Invalid priority (maximum %d)\n", max_pri);
		return -1;
	}

	if (sched_setscheduler(0, SCHED_FIFO, &sp)) {
		perror("sched_setscheduler");
		return -1;
	}

	return 0;
}
