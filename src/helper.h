/**
 *  This file is part of SoftGREd
 *
 *    SoftGREd is free software: you can redistribute it and/or modify it under the terms
 *  of the GNU Lesse General Public License as published by the Free Software Foundation, either
 *  version 3 of the License, or (at your option) any later version.
 *
 *  SoftGREd is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
 *  without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *  See the GNU Lesse General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesse General Public License
 *  along with SoftGREd.
 *  If not, see <http://www.gnu.org/licenses/>.
 *
 *  Copyright (C) 2014, Jorge Pereira <jpereiran@gmail.com>
 */

#ifndef HELPER_H_
#define HELPER_H_

#include "general.h"
#include "softgred_config.h"

void
helper_print_payload (const u_char *payload,
                      size_t len);

void
helper_print_hex2ascii (const u_char *payload,
                        size_t len,
                        int offset);

int helper_system(bool verbose,
                  const char *format, 
                  ...);

void helper_enable_high_priority();

void helper_enable_coredump();

void helper_print_stacktrace();

void helper_lock();

void helper_unlock();

#endif /*HELPER_H_*/

