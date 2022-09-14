#pragma once

#define assert(x) { if (!(x)) { printf("assert(%s) failed on line=%lu file=%s", #x, __LINE__, __FILE__); exit(0); } }
#define fatal_error(x) { printf("[ERR] %s\n", x); exit(0); }