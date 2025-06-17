#include "MEM.hpp"
#include "../Utils/Type.hpp"
#include "../Utils/Utils.hpp"

byte Memory::read(word addr) const
{
  if (this->logging)
  {
    LOG("READ", addr, this->mem[addr]);
  }

  //if (addr <= MemoryMap::ROM_BANK_N_END) // cartridge.read_byte(offset);
  return this->mem[addr];
};

void Memory::write(word addr, byte value)
{
  if (this->logging)
  {
    LOG("WRITE", addr, value);
  }

  /*
  if (addr >= MemoryMap::CHANGE_ROM_BANK_S &&  addr <= MemoryMap::CHANGE_ROM_BANK_E)
  {
    // change rom bank 
    this->current_rom_bank = value;
    return;
  }

  if (addr <= MemoryMap::ROM_BANK_N_END)
  {
    return;
  }
  */

  this->mem[addr] = value;
};

word Memory::read_word(word addr) const 
{
  byte l_byte = this->read(addr);
  byte h_byte = this->read(addr+1);
  return (static_cast<word>(h_byte) << 8) | l_byte;
}

void Memory::write_word(word addr, word value) 
{
  // 0000 0000 XXXX XXXX
  byte h_byte = (value >> 8);
  byte l_byte = (value & 0xFF);
  this->write(addr, l_byte);
  this->write(addr+1, h_byte);
}
