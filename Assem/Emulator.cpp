#include "stdafx.h"
#include "Emulator.h"

bool Emulator::runProgram( )

{
    int loc = 100;
    while(true)
    {            
        long long inst = m_memory[loc];
        int op_code = (int) (inst / 10'000'000'000LL);
    }
}
