#ifndef UTILS_HPP
#define UTILS_HPP
#include "Type.hpp"

#define ANSI_COLOR_RESET   "\x1b[0m"
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"

void LOG(const char* instruct_type, word addr, byte value);
bool get_bit_state(byte byte_value, short unsigned int index);
#endif
