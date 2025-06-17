#include "CPU.hpp"
#include "../Utils/Utils.hpp"
#include "OPCODE.hpp"
#include <cstdio>

void CPU::turn(bool state)
{
  this->is_running = state;
}

void CPU::init()
{
  if (this->is_initialized) return;

  pc = 0x0100; // Program Counter starts at ROM begins;
  sp = 0xFFFE; // Stack Pointer starts at end of HIGH RAM;
  
  // Register Pairs
  af = 0x01B0; // A = 0x01 & F = 0xB0;
  bc = 0x0013; // B = 0X00 & C = 0x13;
  de = 0x00D8; // D = 0x00 & E = 0xD8;
  hl = 0x014D; // H = 0x01 & L = 0x4D;
        
  // Timers
  this->memory.write(0xFF04, 0x00); // DIV
  this->memory.write(0xFF05, 0x00); // TIMA
  this->memory.write(0xFF06, 0x00); // TMA
  this->memory.write(0xFF07, 0x00); // TAC

  // Sound
  this->memory.write(0xFF10, 0x80); // NR10
  this->memory.write(0xFF11, 0xBF); // NR11
  this->memory.write(0xFF12, 0xF3); // NR12
  this->memory.write(0xFF14, 0xBF); // NR14
  this->memory.write(0xFF16, 0x3F); // NR21
  this->memory.write(0xFF17, 0x00); // NR22
  this->memory.write(0xFF19, 0xBF); // NR24
  this->memory.write(0xFF1A, 0x7F); // NR30
  this->memory.write(0xFF1B, 0xFF); // NR31
  this->memory.write(0xFF1C, 0x9F); // NR32
  this->memory.write(0xFF1E, 0xBF); // NR33
  this->memory.write(0xFF20, 0xFF); // NR41
  this->memory.write(0xFF21, 0x00); // NR42
  this->memory.write(0xFF22, 0x00); // NR43
  this->memory.write(0xFF23, 0xBF); // NR44
  this->memory.write(0xFF24, 0x77); // NR50
  this->memory.write(0xFF25, 0xF3); // NR51
  this->memory.write(0xFF26, 0xF1); // NR52
                                
  // Graphics
  this->memory.write(0xFF40, 0x91); // LCDC (LCD Control) - Scree on
  this->memory.write(0xFF42, 0x00); // SCY (Scroll Y)
  this->memory.write(0xFF43, 0x00); // SCX (Scroll X)
  this->memory.write(0xFF45, 0x00); // LYC (LY Compare)
  this->memory.write(0xFF47, 0xFC); // BGP (BG Palette Data)
  this->memory.write(0xFF48, 0xFF); // OBP0 (Object Palette 0 Data)
  this->memory.write(0xFF49, 0xFF); // OBP1 (Object Palette 1 Data)
  this->memory.write(0xFF4A, 0x00); // WY (Window Y Position)
  this->memory.write(0xFF4B, 0x00); // WX (Window X Position)

  // Switch
  this->memory.write(0xFFFF, 0x00); // IE (Interrupt Enable)
  
  this->is_initialized = true;
}

void CPU::advance_pc(byte steps)
{
  this->pc += steps;
}

bool CPU::get_flag(FlagBit flag_mask) const 
{
  return (f & flag_mask) != 0;
}

void CPU::set_flag(FlagBit flag_mask, bool state)
{
  if (state)
  {
    f |= flag_mask;
  }
  else  
  {
    f &= ~flag_mask;
  }
}

void CPU::execute_cycle()
{
  this->current_opcode = this->memory.read(pc);
  OpcodeInfo info = OpcodeTable[this->current_opcode];
  print_opcode_info(info.name, info.length, info.cycles, info.conditional_cycles);

  switch (this->current_opcode) 
  {
    // 0x0X
    case OpCode::NOP:
      break;
    case OpCode::LD_BC_u16:
       this->bc = this->memory.read_word(pc + 0x0001);
       break;
    case OpCode::LD_mBC_A:
       this->memory.write(this->bc, this->a);
       break;
    case OpCode::INC_B:
       this->b += 0x01;
       break;
    case OpCode::DEC_B:
       this->b -= 0x01;
       break;
    case OpCode::INC_BC:
       this->bc += 0x0001;
       break;
    case OpCode::LD_B_u8:
       this->b = this->memory.read(pc + 0x01);
       break;

  
    // 0x1X
    case OpCode::LD_DE_u16:
       this->de = this->memory.read_word(pc + 0x0001);
       break;
    case OpCode::LD_mDE_A:
       this->memory.write(this->de, this->a);
    case OpCode::INC_DE:
      this->de = this->memory.read_word(this->de) + 0x1;
      break;
    case OpCode::INC_D:
      this->d += 0x01;
      break;
    case OpCode::DEC_D:
      this->d -= 0x01;
      break;
    case OpCode::LD_D_u8:
      this->d = this->memory.read(pc + 0x01);
      break; 

    // 0x2X
    case OpCode::LD_HL_u16:
       this->hl = this->memory.read_word(pc + 0x0001);
       break;
    case OpCode::LD_SP_u16:
       this->sp = this->memory.read_word(pc + 0x0001);
       break;
    case OpCode::LD_H_u8:
       break;
    default:
       break;
  }

  this->current_instruction_clock = info.cycles;
  this->div_counter_cycles   += this->current_instruction_clock;
  this->timer_counter_cycles += this->current_instruction_clock;
  this->clock_cycles_elapsed += this->current_instruction_clock;
    
  CPU::update_timers();

  advance_pc(info.length);
}

void CPU::update_timers()
{
  // DIV
  byte DIV = this->memory.read(0xFF04);
  while (this->div_counter_cycles >= 0x0100) 
  {
    this->memory.write(0xFF04, DIV + 1);
    this->div_counter_cycles -= 0x0100;
  }
  
  // TAC [TIMER CONTROL]
  // : the second bit of TAC represents if timer is active or deactive
  byte TAC = this->memory.read(0xFF07);
  bool timer_enable = get_bit_state(TAC, 0x02);

  if (timer_enable) 
  {
    word timer_cycle_limit = 0x0000;

    switch (TAC & 0x03)
    {
      case 0x00: timer_cycle_limit = 1024; break; // 4096    Hz
      case 0x01: timer_cycle_limit = 16; break  ; // 262.144 Hz
      case 0x02: timer_cycle_limit = 64; break  ; // 65.536  Hz
      case 0x03: timer_cycle_limit = 256; break ; // 16.384  Hz
    }

    while (this->timer_counter_cycles >= timer_cycle_limit)
    {
      this->timer_counter_cycles -= timer_cycle_limit;

      byte TIMA = this->memory.read(0xFF05);
      TIMA++;

      if (TIMA == 0x00) // Timer Overflow 
      {
        TIMA = this->memory.read(0xFF06);
        byte IF = this->memory.read(0xFF0F);
        this->memory.write(0xFF0F, IF | 0x04);
      }

      this->memory.write(0xFF05, TIMA);
    }
  }
}

void CPU::print_flag_state()
{
  printf("Z=%u | N=%u | H=%u | C=%u\n", get_flag(FlagBit::Z), get_flag(FlagBit::N), get_flag(FlagBit::H), get_flag(FlagBit::C));
}

void CPU::print_cpu_state()
{
  printf("PC: 0x%04X, SP: 0x%04X | AF: 0x%04X, BC: 0x%04X, DE: 0x%04X, HL: 0x%04X\n", pc, sp, af, bc, de, hl
      );
  
}

word CPU::get_clock_cycles() 
{
  return this->clock_cycles_elapsed;
}
