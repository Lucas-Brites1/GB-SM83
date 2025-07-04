#include "OPCODE.hpp"
#include <cstdio>

OpcodeInfo OpcodeTable[0x100];

void init_opcode_table()
{
  for (word idx = 0x000; idx < 0x100; idx++)
  {
    OpcodeTable[idx] = { "INVALID", 0x00, 0x00, 0x00 };
  }

  // CONTROL INSTRUCTIONS
  OpcodeTable[0x00] = { "NOP", 0x01, 0x04, 0x04          };
  OpcodeTable[0x20] = { "JR NZ, i8", 0x02, 0x08, 0x0C    };
  OpcodeTable[0x30] = { "JR NC, i8", 0x02, 0x08, 0x0C    };

  // x16 / LSM
  OpcodeTable[0x01] = { "LD BC, u16", 0x03, 0x0C, 0x00   };
  OpcodeTable[0x11] = { "LD DE, u16", 0x03, 0x0C, 0x00   };
  OpcodeTable[0x21] = { "LD HL, u16", 0x03, 0x0C, 0x00   };
  OpcodeTable[0x31] = { "LD SP, u16", 0x03, 0x0C, 0x00   };

  // x8 / LSM
  OpcodeTable[0x02] = { "LD (BC), A", 0x01, 0x08, 0x00   };
  OpcodeTable[0x12] = { "LD (DE), A", 0x01, 0x08, 0x00   };
  OpcodeTable[0x22] = { "LD (HL+), A", 0x01, 0x08, 0x00  };
  OpcodeTable[0x32] = { "LD (HL-), A", 0x01, 0x08, 0x00  };

  OpcodeTable[0x06] = { "LD B, u8", 0x02, 0x08, 0x00     };
  OpcodeTable[0x16] = { "LD D, u8", 0x02, 0x08, 0x00     };
  OpcodeTable[0x26] = { "LD H, u8", 0x02, 0x08, 0x00     };
  OpcodeTable[0x36] = { "LD (HL), u8", 0x02, 0x0C, 0x00  };
 
  // x16 / ALU
  OpcodeTable[0x03] = { "INC BC", 0x01, 0x08, 0x00       };
  OpcodeTable[0x13] = { "INC DE", 0x01, 0x08, 0x00       };
  OpcodeTable[0x23] = { "INC HL", 0x01, 0x08, 0x00       };
  OpcodeTable[0x33] = { "INC SP", 0x01, 0x08, 0x00       };

  // x8 / ALU
  OpcodeTable[0x04] = { "INC B", 0x01, 0x04, 0x00        };
  OpcodeTable[0x14] = { "INC D", 0x01, 0x04, 0x00        };
  OpcodeTable[0x24] = { "INC H", 0x01, 0x04, 0x00        };
  OpcodeTable[0x34] = { "INC (HL)", 0x01, 0x0C, 0x00     };

  OpcodeTable[0x05] = { "DEC B", 0x01, 0x04, 0x00        };
  OpcodeTable[0x15] = { "DEC D", 0x01, 0x04, 0x00        };
  OpcodeTable[0x25] = { "DEC H", 0x01, 0x04, 0x00        };
  OpcodeTable[0x35] = { "DEC (HL)", 0x01, 0x0C, 0x00     }; 
}

void print_opcode_info(const char* opcode_desc, byte len, byte clock_cycle, byte clock_cycle_conditional)
{
  printf("\n[  OPCODE  |  LENGTH  |  TIMING  |  CONDITIONAL TIMING  ]\n");
  printf("[  %s  |  %u  |  %u  |  %u  ]\n", opcode_desc, len, clock_cycle, clock_cycle_conditional);
}
