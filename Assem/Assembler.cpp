//
//  Implementation of the Assembler class.
//

#include "stdafx.h"
#include "Assembler.h"
#include "Instruction.h"
#include "Errors.h"

Assembler::Assembler( int argc, char *argv[] )
: m_facc( argc, argv )
{
    // Nothing else to do here at this point.
}

// Destructor currently does nothing.  You might need to add something as you develope this project.  If not, we can delete it.
Assembler::~Assembler( )
{
}

void Assembler::PassI( ) 
{
    // Tracks the location of the instructions to be generated.
    int loc = 0;

    // Successively process each line of source code.
    for (; ;)
    {
        // Read the next line from the source file.
        string line; 
        if (!m_facc.GetNextLine(line)) 
        {
            // If there are no more lines, we are missing an end statement.
            // We will let this error be reported by Pass II.
            return;
        }

        // Parse the line and get the instruction type.
        Instruction::InstructionType st =  m_inst.ParseInstruction(line);

        // If this is an end statement, there is nothing left to do in pass I.
        // Pass II will determine if the end is the last statement and report an error if it isn't.
        if (st == Instruction::ST_End) return;

        // Labels can only be on machine language and assembler language
        // instructions.  So, skip comments.
        if (st == Instruction::ST_Comment)  
        {
        	continue;
	    }

        // If the instruction has a label, record it and its location in the
        // symbol table.
        if (m_inst.isLabel()) 
        {
            m_symtab.AddSymbol(m_inst.GetLabel(), loc);
        }

        // Compute the location of the next instruction.
        loc = m_inst.LocationNextInstruction( loc );
    }
}

// TODO: Implement PassII
void Assembler::PassII( )
{
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
        }

        if (st == Instruction::ST_AssemblerInstr)
        {
            if (m_inst.GetOpCode() == "org")
            {
                cout << loc;

                try
                {
                    // Convert operand1 into int
                    loc = stoi(m_inst.GetOperand1());
                }
                catch (...)
                {
                    Errors::RecordError("Invalid ORG value: " + m_inst.GetOperand1());
                }
                
                cout << "\t\t\t" << line << endl;
                continue;
            }

            if (m_inst.GetOpCode() == "ds")
            {
                int count = 0;

                try
                {
                    // Convert operand1 into int
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
                    // Convert operand1 into long long
                    value = stoll(m_inst.GetOperand1());
                }
                catch (...)
                {
                    Errors::RecordError("Invalid DS value: " + m_inst.GetOperand1());

                }

                // Load into emulator memory
                m_emul.insertMemory(loc, value);

                cout << loc << "\t\t" << setw(12) << setfill('0') << value << "\t" << line << endl;
                loc++;
                continue;
            }
        }
    }
}

//TODO: Implement RunProgramInEmulator
void Assembler::RunProgramInEmulator( )
{

}