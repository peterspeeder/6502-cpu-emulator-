//
//  main.cpp
//  cpu
//
//  Created by Peter Kolev on 2023-08-21.
//

#include <iostream>

using Byte = unsigned char;
using Word = unsigned short;
using u32 = unsigned int;

// Memory structure
struct Mem {
    typedef unsigned int u32;
    static constexpr u32 MAX_MEM = 1024 * 64;
    Byte Data[MAX_MEM];
    
    // Initialize memory
    void Initialise() {
        for (u32 i = 0; i < MAX_MEM; ++i) {
            Data[i] = 0;
        }
    }

    // Read a byte from memory
    Byte operator[](u32 Address) const {
        // TODO: Add bounds checking/assertions here
        return Data[Address];
    }
};

// CPU structure
struct CPU {
    Word PC; // Program counter
    Word SP; // Stack counter
    
    Byte A, X, Y; // Registers
    
    // Status flags
    Byte C : 1;
    Byte Z : 1;
    Byte I : 1;
    Byte D : 1;
    Byte B : 1;
    Byte V : 1;
    Byte N : 1;
    
    // Reset the CPU
    void Reset(Mem& memory) {
        PC = 0xFFFC;
        SP = 0x0100;
        C = Z = I = D = B = V = N = 0;
        A = X = Y = 0;
        memory.Initialise();
    }

    // Fetch a byte from memory
    Byte FetchByte(u32& Cycles, Mem& memory) {
        Byte Data = memory[PC];
        PC++;
        Cycles--;
        return Data;
    }

    // Instruction codes
    static constexpr Byte INS_LDA_IN = 0xA;
    
    // Execute instructions
    void Execute(u32 Cycles, Mem& memory) {
        while (Cycles > 0) {
            Byte Ins = FetchByte(Cycles, memory);
            switch (Ins)
            {
            case INS_LDA_IN:
                {
                   Byte value =
                        FetchByte(Cycles, memory);
                    A = value;
                    Z = (A==0);
                    N = (A & 0b10000000) > 0;
                }
                break;
            }    

            // TODO: Implement instruction handling based on 'Ins'
            // For example, you can use a switch statement here.

            // Placeholder for now
            (void)Ins;
        }
    }
};

int main() {
    Mem mem;
    CPU cpu;
    cpu.Reset(mem);
    cpu.Execute(2, mem);
    return 0;
}
