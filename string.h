/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef STRING_H
#define STRING_H
#include "def.h"
#include <string.h>
#ifdef __cplusplus
extern "C"
{
#endif

/*
  func: StrStartsWith

  Checks if string starts with subString. If you pass NO_GIVEN_LEN for the
  subStringLen parameter we'll calculate the subString length for you,
  otherwise we use what you pass for efficiencies sake.
*/
bool StrStartsWith(char *string, char *subString, isize subStringLen);

/*
  func: SplitLines

  Splits the given string by line and returns an array of the pointers into
  the string. The returned array must be freed after use or you'll leak memory
*/
char **SplitLines(char *req);

/* strcmp and strncmp wrappers */
bool StringEq(const char *str1, const char *str2);
bool SubStringEq(const char *str1, const char *str2, size_t n);

/*
  func:StrCpyAndLen

  a version of strncpy that returns the length of the written string.
*/
size_t StrCpyAndLen(char *restrict dest, const char *restrict src, size_t destBufLen);
#ifdef __cplusplus
}
#endif

#endif
