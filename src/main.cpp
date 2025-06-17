#include "Processor/CPU.hpp"
#include <cstdio>

int main(void)
{
    CPU cpu;
    cpu.init();
    cpu.turn(ON);

    // ===== Teste de Programa simples =====
    // 0x0100: LD BC,0xABCD
    // 0x0103: LD DE,0x1234
    // 0x0106: NOP

    cpu.memory.write(0x0100, 0x01);  // OP_LD_BC_word
    cpu.memory.write(0x0101, 0xCD);
    cpu.memory.write(0x0102, 0xAB);

    cpu.memory.write(0x0103, 0x11);  // OP_LD_DE_word
    cpu.memory.write(0x0104, 0x34);
    cpu.memory.write(0x0105, 0x12);

    cpu.memory.write(0x0106, 0x00);  // OP_NOP
    cpu.memory.write(0x0107, 0x02);  // OP_LD_(BC)_A
    cpu.memory.write(0x0108, 0x03);  // INC_BC
    cpu.memory.write(0x0109, 0x04);  // INC_B

    printf("\n===== INICIANDO TESTE DE CPU =====\n");

    for (int i = 0; i < 6; ++i)
    {
        printf("\n>>> Step %d: Antes da execução\n", i + 1);
        cpu.print_cpu_state();

        cpu.execute_cycle();

        printf(">>> Step %d: Depois da execução\n", i + 1);
        cpu.print_cpu_state();

        printf(">>> Clock cycles acumulados: %d\n", cpu.get_clock_cycles());
        printf("-------------------------------------------\n");
    }

    printf("\n===== ESTADO FINAL DOS REGISTRADORES =====\n");
    cpu.print_cpu_state();

    printf("\n===== Valor final do DIV (Timer) =====\n");
    printf("DIV Register (0xFF04): 0x%02X\n", cpu.memory.read(0xFF04));

    return 0;
}

