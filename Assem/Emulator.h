//
//  Emulator class - supports the emulation of VC1620 programs
//
#ifndef _EMULATOR_H  // UNIX way of preventing multiple inclusions.
#define _EMULATOR_H

#include <assert.h>

class Emulator {

public:

    const static int MEMSZ = 100'000;  // The size of the memory of the VC1620.

    /// <summary>
    /// Default constructor for the Emulator class. Initializes the
    /// memory vector to MEMSZ elements, all set to 0
    /// </summary>
    /// <author>Race Partin</author>
    /// <date>11/21/2025 9:29pm</date>
    Emulator( ) 
    {
         m_memory.resize(MEMSZ, 0);
    }

    /// <summary>
    /// Insert a value into a specified location in the VC1620 memory.
    /// </summary>
    /// <param name ="a_location">The memory address where the value is going to be stored.</param>
    /// <param name ="a_contents">The value that is to be contained at a specified location.</param>
    /// <returns>Returns true on a successful memory insertion.</returns>
    /// <author>Race Partin</author>
    /// <date>11/21/2025 9:34pm</date>
    bool insertMemory( int a_location, long long a_contents )
    {
        assert(a_location >= 0 && a_location < MEMSZ); 
        m_memory[a_location] = a_contents;
        return true;
    }
    
    /// <summary>
    /// Executes the program that is stored in VC1620 memory.
    /// </summary>
    /// <returns>Returns true on successful completion of the program.</returns>
    /// <author>Race Partin</author>
    /// <date>11/21/2025 9:35pm</date>
    bool runProgram( );

private:

    vector <long long> m_memory;  // Memory for the VC1620.
};

#endif