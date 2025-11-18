//
//  Class to store machine operators.
//
#pragma once

#include "stdafx.h"
#include <unordered_map>

class MachineOps {

public:

    static const unordered_map<string, int>& GetMachineOps( );

private:

    static const unordered_map<string, int> m_MachineOps;
};