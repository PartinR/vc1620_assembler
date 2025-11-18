//
//  Implementation of MachineOps class.
//

#include "stdafx.h"
#include "MachineOps.h"
#include <unordered_map>

const unordered_map<string, int> MachineOps::m_MachineOps = {
    {"add", 1}, {"sub", 2}, {"mult", 3},
    {"div", 4}, {"copy", 5}, {"read", 7},
    {"write", 8}, {"b", 9}, {"bm", 10},
    {"bz", 11}, {"bp", 12}, {"halt", 13}
};

const unordered_map<string, int>& MachineOps::GetMachineOps( )
{
    return m_MachineOps;
}