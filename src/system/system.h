/*
    This file is part of Elixir, an open-source cross platform physically
    based renderer.

    Copyright (c) 2019 Samuel Van Allen - All rights reserved.

    Elixir is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

#define EXR_ENABLE_LOGGING
#define EXR_ENABLE_ERRORS
#define EXR_ENABLE_ASSERTS

// The order of the following includes matter!
#include <algorithm>
#include <math.h>
#include <memory>
#include <vector>
#include <stdexcept>

#include "system/config.h"
#include "system/error.h"
#include "system/utils.h"
#include "system/types.h"
#include "system/threading/parallel.h"
#include "system/profiling/profiler.h"
#include "system/memory/memoryarena.h"

