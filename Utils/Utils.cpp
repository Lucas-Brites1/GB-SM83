#include <cstring>
#include <cstdio>
#include "Utils.hpp"

bool get_bit_state(byte byte_value, short unsigned int index)
{
  if (index > 7) return false;

  return (byte_value & (0x01 << index)) ? true : false;
}

void LOG(const char* instruct_type, word addr, byte value)
{
  const char* color = ""; 

  if (strcmp(instruct_type, "WRITE") == 0) {
    color = ANSI_COLOR_YELLOW;  
  } else if (strcmp(instruct_type, "READ") == 0) {
    color = ANSI_COLOR_CYAN;    
  } else if (strcmp(instruct_type, "MBC") == 0) {
    color = ANSI_COLOR_MAGENTA; 
  } else if (strcmp(instruct_type, "ERROR") == 0) {
    color = ANSI_COLOR_RED;     
  }

  printf("%s[%s] Addr: 0x%04X, Value: 0x%02X%s\n", 
          color, 
          instruct_type, 
          addr, 
          value, 
          ANSI_COLOR_RESET
          ); 
}
