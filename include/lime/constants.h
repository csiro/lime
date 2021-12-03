#pragma once

/* Use of this code is is subject to agreement to the
   CSIRO Open Source Software Licence Agreement
   as set out in the file ../../LICENCE.md
*/


#define LIME_EPSILON (1.0e-6)

#if defined(_M_X64) || defined(__amd64__)
#define LIME_BIG_INT (999999999)
#else
#define LIME_BIG_INT (99999999)
#endif
#define LIME_BIG_DOUBLE (1.0e99)
// Alt name for LIME_BUG_INT
#define LIME_MAX LIME_BIG_INT


