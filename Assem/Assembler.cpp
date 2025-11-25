//
//  Implementation of the Assembler class.
//

#include "stdafx.h"
#include "Assembler.h"
#include "Instruction.h"
#include "MachineOps.h"
#include "Emulator.h"
#include "Errors.h"

Assembler::Assembler( int argc, char *argv[] )
: m_facc( argc, argv )
{
    // Nothing else to do here at this point.
}

// Destructor currently does nothing.
Assembler::~Assembler( )
{
}

void Assembler::PassI( ) 
{
    int loc = 0;

    for (; ;)
    {
        string line; 
        if (!m_facc.GetNextLine(line)) 
        {
            // If there are no more lines, we are missing an end statement.
            return;
        }

        // Parse the line and get the instruction type.
        Instruction::InstructionType st =  m_inst.ParseInstruction(line);

        // If this is an end statement, there is nothing left to do in PassI.
        if (st == Instruction::ST_End) return;

        // Skip comments
        if (st == Instruction::ST_Comment)  
        {
        	continue;
	    }

        // If the instruction has a label, record it and its location in the symbol table.
        if (m_inst.isLabel()) 
        {
            m_symtab.AddSymbol(m_inst.GetLabel(), loc);
        }

        loc = m_inst.LocationNextInstruction( loc );
    }
}

void Assembler::PassII( )
{
    // Rewind and reset location.
    int loc = 0;
    m_facc.rewind();

    cout << "\nTranslation of Program:" << endl;
    cout << "Location\t" << "Contents\t" << "Original Statement" << endl;

    for (; ;)
    {
        string line;
        if (!m_facc.GetNextLine(line))
        {
            break;
        }

        Instruction::InstructionType st = m_inst.ParseInstruction(line);

        if (st == Instruction::ST_Comment)
        {
            cout << "\t\t\t\t" << line << endl;
            continue;
        }

        if (st == Instruction::ST_End)
        {
            cout << "\t\t\t" << line << endl;
            return;
        }

        if (st == Instruction::ST_AssemblerInstr)
        {
            if (m_inst.GetOpCode() == "org")
            {
                cout << loc;

                try
                {
                    // Convert operand1 into int.
                    loc = stoi(m_inst.GetOperand1());
                }
                catch (...)
                {
                    Errors::RecordError("Invalid ORG value: " + m_inst.GetOperand1());
                }

                cout << "\t\t\t\t" << line << endl;
                continue;
            }

            if (m_inst.GetOpCode() == "ds")
            {
                int count = 0;

                try
                {
                    // Convert operand1 into int.
                    count = stoi(m_inst.GetOperand1());
                }
                catch (...)
                {
                    Errors::RecordError("Invalid DS value: " + m_inst.GetOperand1());
                }

                cout << loc << "\t\t\t\t" << line << endl;
                loc += count;
                continue;
            }

            if (m_inst.GetOpCode() == "dc")
            {
                long long value = 0;

                try
                {
                    // Convert operand1 into long long.
                    value = stoll(m_inst.GetOperand1());
                }
                catch (...)
                {
                    Errors::RecordError("Invalid DS value: " + m_inst.GetOperand1());
                }

                // Load into emulator memory.
                m_emul.insertMemory(loc, value);

                cout << loc << "\t\t" << setw(12) << setfill('0') << value << "\t" << line << endl;
                loc++;
                continue;
            }
        }

        if (st == Instruction::ST_MachineLanguage)
        {
            long long contents = 0;
            int opcode_value = 0;
            int operand1_addr = 0;
            int operand2_addr = 0;

            // Lambda expression: removes commas inside of operand
            auto cleanOperand = [](string op) {
                op.erase(remove(op.begin(), op.end(), ','), op.end());
                return op;
            };

            try
            {
                // Get corresponding machine op and address of operands' 1 and 2.
                opcode_value = MachineOps::GetMachineOps().at(m_inst.GetOpCode());

                // Get operand1 location.
                if (!m_inst.GetOperand1().empty()) 
                {
                    // Remove commas from operand1.
                    string op1 = cleanOperand(m_inst.GetOperand1());

                    if (!m_symtab.LookupSymbol(op1, operand1_addr))
                    {
                        try
                        {
                            operand1_addr = stoi(op1);
                        }
                        catch (...)
                        {
                            Errors::RecordError("Undefined operand1: " + op1);
                        }
                    }
                }

                // Get operand2 location.
                if (!m_inst.GetOperand2().empty())
                {
                    // Remove commas from operand2.
                    string op2 = cleanOperand(m_inst.GetOperand2());

                    if (!m_symtab.LookupSymbol(op2, operand2_addr))
                    {
                        try
                        {
                            operand2_addr = stoi(op2);
                        }
                        catch (...)
                        {
                            Errors::RecordError("Undefined operand1: " + op2);
                        }
                    }
                }
            }
            catch (...)
            {
                Errors::RecordError("Error assembling instruction: " + line);
            }

            // Encode machine instruction.
            contents = opcode_value * 10'000'000'000 + operand1_addr * 100'000 + operand2_addr;

            // Load into emulator memory.
            m_emul.insertMemory(loc, contents);

            cout << loc << "\t\t" << setw(12) << setfill('0') << contents << "\t" << line << endl;
            loc++;
        }
    }
    Errors::DisplayErrors();
}

void Assembler::RunProgramInEmulator( )
{
    cout << "\nResults from emulating program:" << endl;

    if (!m_emul.runProgram())
    {
        cout << "Emulator has encountered an error." << endl;
        return;
    }

    cout << "End of emulation" << endl;
}