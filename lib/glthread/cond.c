/* Condition variables for multithreading.
   Copyright (C) 2008-2019 Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, see <https://www.gnu.org/licenses/>.  */

/* Written by Yoann Vandoorselaere <yoann@prelude-ids.org>, 2008,
   and Bruno Haible <bruno@clisp.org>, 2008.  */

#include <config.h>

#define _GLTHREAD_COND_INLINE _GL_EXTERN_INLINE
#include "glthread/cond.h"

/* ========================================================================= */

#if USE_PTH_THREADS

/* -------------------------- gl_cond_t datatype -------------------------- */

int
glthread_cond_timedwait_multithreaded (gl_cond_t *cond,
                                       gl_lock_t *lock,
                                       struct timespec *abstime)
{
  int ret, status;
  pth_event_t ev;

  ev = pth_event (PTH_EVENT_TIME, pth_time (abstime->tv_sec, abstime->tv_nsec / 1000));
  ret = pth_cond_await (cond, lock, ev);

  status = pth_event_status (ev);
  pth_event_free (ev, PTH_FREE_THIS);

  if (status == PTH_STATUS_OCCURRED)
    return ETIMEDOUT;

  return ret;
}

#endif

/* ========================================================================= */

#if USE_WINDOWS_THREADS

#endif

/* ========================================================================= */
