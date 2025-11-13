//
//  Implementation of Emulator class.
//

#include "stdafx.h"
#include "Emulator.h"

bool Emulator::runProgram( )
{
    int loc = 100;
    while(true)
    {            
        long long inst = m_memory[loc];

        int op_code = inst / 10'000'000'000;
        int address1 = (inst / 100'000) % 100'000;
        int address2 = inst / 100'000;
    }
}
