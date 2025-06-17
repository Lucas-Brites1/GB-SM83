#ifndef CPU_HPP
#define CPU_HPP
#include "../Utils/Type.hpp"
#include "../Memory/MEM.hpp"
#include "OPCODE.hpp"

constexpr bool ON  = true;
constexpr bool OFF = false;

class CPU
{
  private:
    union {
      word af;  // Accumulator & Flags
      struct {
        byte f;
        byte a;
      };
    };

    union {
      word hl; // Address Pointer
      struct {
        byte l;
        byte h;// H High mem reference | L Low mem reference
      };
    };

    union {
      word bc; // Secondary Addr Pointer
      struct {
        byte c;
        byte b;// B,C loops counter
      };
    };

    union {
      word de; 
      struct {
        byte e;
        byte d;// D - Destiny address | E - Extends D
      };
    };

    word pc;
    word sp;

    bool is_initialized = false;
    bool is_running     = true;

    word timer_counter_cycles        = 0x0000;
    word div_counter_cycles          = 0x0000;
    word clock_cycles_elapsed        = 0x0000;
    
    byte current_opcode              = 0x00;
    byte current_instruction_length  = 0x00;
    byte current_instruction_clock   = 0x00;

    enum FlagBit : byte
    {
      Z = (1 << 7),
      N = (1 << 6),
      H = (1 << 5),
      C = (1 << 4),
    };

    bool get_flag(FlagBit flag_mask) const;
    void set_flag(FlagBit flag_mask, bool state);
    void advance_pc(byte steps = 1);
    void update_timers();

  public:
    CPU() { init_opcode_table(); };
    Memory memory = {};
    void turn(bool state);
    void init();
    void execute_cycle();

    void print_cpu_state();
    void print_flag_state();
    word get_clock_cycles();
};

#endif
