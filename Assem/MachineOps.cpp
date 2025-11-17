//
//  Implementation of MachineOps class.
//

#include "stdafx.h"
#include <unordered_map>
#include "MachineOps.h"

MachineOps::MachineOps( )
{
    // declare the opcodes
    m_opcode = {
        {"add", 1}, {"sub", 2}, {"mult", 3},
        {"div", 4}, {"copy", 5}, {"read", 7},
        {"write", 8}, {"b", 9}, {"bm", 10},
        {"bz", 11}, {"bp", 12}, {"halt", 13}
    };
}

const unordered_map<string, int>& MachineOps::GetOpcode( ) const
{
    return m_opcode;
}