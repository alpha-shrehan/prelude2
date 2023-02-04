#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <assert.h>
#include <stdint.h>
#include <stdbool.h>

#define PL_API
#define PL_ASSERT(X) assert(X)
#define BIT(x, y, z) ((x >> y) & z)