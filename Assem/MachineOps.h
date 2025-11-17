//
//  Class to store machine operators.
//
#pragma once

#include "stdafx.h"
#include <unordered_map>

class MachineOps {

public:

    MachineOps( ) { };

    /// <summary>
    /// Get a constant reference to the opcode.
    /// </summary>
    /// <returns>Returns constant reference to the unordered_map storing opcodes.</returns>
    /// <author>Race Partin</author>
    /// <date>11/16/2025 9:28pm</date.
    const unordered_map<string, int>& GetOpcode( ) const;

private:

    unordered_map<string, int> m_opcode;
};