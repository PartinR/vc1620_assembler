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
        int address2 = inst % 100'000;

        switch (op_code)
        {
            case 1:  // Addition
                m_memory[address1] = m_memory[address1] + m_memory[address2];
                loc++;
                break;

            case 2:  // Subtraction
                m_memory[address1] = m_memory[address1] - m_memory[address2];
                loc++;
                break;

            case 3:  // Multiplication
                m_memory[address1] = m_memory[address1] * m_memory[address2];
                loc++;
                break;

            case 4:  // Division
                if (m_memory[address2] == 0)
                {
                    cerr << "Error: Division by zero" << endl;
                    return false;
                }
                m_memory[address1] = m_memory[address1] / m_memory[address2];
                loc++;
                break;

            case 5:  // Copy
                m_memory[address1] = m_memory[address2];
                loc++;
                break;

            case 6:  // Read
                cout << "? ";
                cin >> m_memory[address1];
                loc++;
                break;

            case 7:  // Write
                cout << m_memory[address1] << endl;
                loc++;
                break;

            case 8:  // Branch
                loc = address1;
                break;

            case 9:  // Branch Minus
                if (m_memory[address1] < 0)
                {
                    loc = address2;
                }
                else
                {
                    loc++;
                }
                break;

            case 10:  // Branch Zero
                if (m_memory[address1] == 0)
                {
                    loc = address2;
                }
                else
                {
                    loc++;
                }
                break;

            case 11:  // Branch Positive
                if (m_memory[address1] > 0)
                {
                    loc = address2;
                }
                else
                {
                    loc++;
                }
                break;

            case 12:  // Halt
                return true;

            default:
                cerr << "Illegal opcode:" << op_code << endl;
                return false;
        }
    }
}
