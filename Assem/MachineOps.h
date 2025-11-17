//
//  Class to store machine operators.
//
#pragma once

#include "stdafx.h"
#include <unordered_map>

class MachineOps {

public:

    MachineOps( ) { };

    static const unordered_map<string, int>& GetOpcode( );

private:

    static const unordered_map<string, int> m_opcode;
};