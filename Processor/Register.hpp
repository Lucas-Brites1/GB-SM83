#ifndef REGISTER_HPP
#define REGISTER_HPP
#include "../Utils/Type.hpp"

struct Register
{
  private:
    byte value;

  public:
    void write(byte value)
    {
      this->value = value;
    }

    byte read() const
    {
      return this->value;
    }

    Register& operator=(byte value)
    {
      this->value = value;
      return *this;
    }

    operator byte() const
    {
      return this->value;
    }

    Register& operator+=(const Register& other)
    {
      this->value += other; 
      return *this;
    }

    Register& operator+=(byte value)
    {
      this->value += value;
      return *this;
    }
};

#endif
