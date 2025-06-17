#ifndef MEM_HPP
#define MEM_HPP
#include "../Utils/Type.hpp"

namespace MemoryMap 
{
  static constexpr std::size_t MEM_CAPACITY = 0x10000;

              // [ROM]
  constexpr word ROM_BANK_0_START  = 0x0000; // 0 
  constexpr word ROM_BANK_0_END    = 0x3FFF; // 16.383
  constexpr word CHANGE_ROM_BANK_S = 0x2000;
  constexpr word CHANGE_ROM_BANK_E = 0x3FFF;
  constexpr word ROM_BANK_N_START  = 0x4000; // 16.384
  constexpr word ROM_BANK_N_END    = 0x7FFF; // 32.767

             //  [VRAM]
  constexpr word VRAM_START        = 0x8000; // 32.768
  constexpr word VRAM_END          = 0x9FFF; // 40.959
}

class Memory 
{
  private: 
    byte mem[MemoryMap::MEM_CAPACITY]; // 0x0000 -> 0xFFFF | 65.535[bytes] valid addresses (65KiB)
    int  current_rom_bank = 1;
    bool logging = true; 

  public:
    void write(word addr, byte value);
    byte read(word addr) const;

    void write_word(word addr, word value);
    word read_word(word addr) const;
};

#endif // !MEM_HPP
