//
//  Class to store machine operators.
//
#pragma once

#include "stdafx.h"
#include <unordered_map>

class MachineOps {

public:

    /// <summary>
    /// Getter function for the unorderd map of machine operators.
    /// </summary>
    /// <returns>A static constant reference to the unordered_map</returns>
    /// <author>Race Partin</author>
    /// <date>11/21/2025 9:43pm</date>
    static const unordered_map<string, int>& GetMachineOps( );

private:

    static const unordered_map<string, int> m_MachineOps;
};