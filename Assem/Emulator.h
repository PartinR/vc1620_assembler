//
//  Emulator class - supports the emulation of VC1620 programs
//
#ifndef _EMULATOR_H      // UNIX way of preventing multiple inclusions.
#define _EMULATOR_H

#include <assert.h>

class Emulator {

public:

    const static int MEMSZ = 100'000;	// The size of the memory of the VC1620.
    Emulator() 
    {
         m_memory.resize(MEMSZ, 0);
    }
    // Records instructions and data into simulated memory.
    bool insertMemory( int a_location, long long a_contents )
    {
        assert(a_location >= 0 && a_location < MEMSZ); 
        m_memory[a_location] = a_contents;
    }
    
    // Runs the program recorded in memory.
    bool runProgram( );

private:

    vector <long long> m_memory;  	// Memory for the VC1620
};

#endif