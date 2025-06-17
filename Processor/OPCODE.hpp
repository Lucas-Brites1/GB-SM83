#ifndef OPCODE_HPP
#define OPCODE_HPP
#include "../Utils/Type.hpp"

struct OpcodeInfo
{
  const char*               name;
  byte                    length;
  byte                    cycles;
  byte        conditional_cycles;
};

extern OpcodeInfo OpcodeTable[0x100]; // 256 opcodes
void   init_opcode_table();
void   print_opcode_info(const char* opcode_desc, byte len, byte clock_cycle, byte clock_cycle_conditional);

enum OpCode
{
    NOP           = 0x00, // "NOP"
    LD_BC_u16     = 0x01, // "LD BC, u16"
    LD_mBC_A      = 0x02, // "LD (BC), A"
    INC_BC        = 0x03, // "INC BC"
    INC_B         = 0x04, // "INC B"
    DEC_B         = 0x05, // "DEC B"
    LD_B_u8       = 0x06, // "LD B, u8"

    LD_DE_u16     = 0x11, // "LD DE, u16"
    LD_mDE_A      = 0x12, // "LD (DE), A"
    INC_DE        = 0x13, // "INC DE"
    INC_D         = 0x14, // "INC D"
    DEC_D         = 0x15, // "DEC D"
    LD_D_u8       = 0x16, // "LD D, u8"
    
    JR_NZ_i8      = 0x20, // "JR NZ, i8"
    LD_HL_u16     = 0x21, // "LD HL, u16"
    LD_mHLinc_A   = 0x22, // "LD (HL+), A"
    INC_HL        = 0x23, // "INC HL"
    INC_H         = 0x24, // "INC H"
    DEC_H         = 0x25, // "DEC H"
    LD_H_u8       = 0x26, // "LD H, u8"

    JR_NC_i8      = 0x30, // "JR NC, i8"
    LD_SP_u16     = 0x31, // "LD SP, u16"
    LD_mHLdec_A   = 0x32, // "LD (HL-), A"
    INC_SP        = 0x33, // "INC SP"
    INC_mHL       = 0x34, // "INC (HL)"
    DEC_mHL       = 0x35, // "DEC (HL)"
    LD_mHL_u8     = 0x36  // "LD (HL), u8"
};

#endif // !OPCODE_HPP
