//
//  Implementation of Instruction class.
// 

#include "stdafx.h"
#include <sstream>
#include "MachineOps.h"
#include "Instruction.h"
#include "Errors.h"
#include "Emulator.h"

// Helper check for label validity
bool isValidLabel( const string& label ) 
{
    if (label.empty()) return false;

    // Labels must start with a letter
    return isalpha(label[0]);
}

string Instruction::RemoveComment( string line ) 
{
    size_t pos = line.find(';');
    if (pos == string::npos)
    {
        return line;
    }

    return line.erase(pos);
}

bool Instruction::ParseLine( const string& line, string& label, string& opcode, string& operand1, string& operand2 )
{
    istringstream ins(line);
    label = opcode = operand1 = operand2 = "";

    if (line.empty()) return true;

    // Check if the line starts with a label (no whitespace at start).
    if (line[0] != ' ' && line[0] != '\t')
    {
        ins >> label;
    }

    ins >> opcode >> operand1 >> operand2;

    // Robust check for extra operands
    string extra;
    ins >> extra;

    // If 'extra' is not empty, we have garbage at the end of the line
    return extra.empty();
}

Instruction::InstructionType Instruction::ParseInstruction( string a_line )
{
    // Make a local copy to preserve original casing for error messages if needed, 
    // but parsing generally needs case insensitivity for opcodes.
    string parseLine = RemoveComment(a_line);

    // Identify comments/blank lines.
    if (parseLine.find_first_not_of(" \t\n\r") == string::npos)
    {
        m_type = ST_Comment;
        return m_type;
    }

    // Handle parse errors (like extra operands).
    if (!ParseLine(parseLine, m_Label, m_OpCode, m_Operand1, m_Operand2))
    {
        Errors::RecordError("Syntax Error (Extra operand): " + a_line);
        m_type = ST_Error;
        return m_type;
    }

    // Validate Label Format
    if (!m_Label.empty() && !isValidLabel(m_Label)) 
    {
        Errors::RecordError("Syntax Error (Invalid Label Format): " + m_Label);
        m_type = ST_Error;
        return m_type;
    }

    // Convert OpCode to lower case for consistency
    for (auto& c : m_OpCode) c = tolower(c);

    if (m_OpCode == "end")
    {
        m_type = ST_End;
        return m_type;
    }

    // Check Machine Ops
    if (MachineOps::GetMachineOps().find(m_OpCode) != MachineOps::GetMachineOps().end())
    {
        m_type = ST_MachineLanguage;
        return m_type;
    }

    // Check Assembler Ops
    if (m_OpCode == "org" || m_OpCode == "dc" || m_OpCode == "ds")
    {
        m_type = ST_AssemblerInstr;
        return m_type;
    }

    // If we are here, the opcode is unknown.
    Errors::RecordError("Illegal Opcode: " + m_OpCode);
    m_type = ST_Error;
    return m_type;
}

int Instruction::LocationNextInstruction( int a_loc )
{
    if (m_type == ST_Comment || m_type == ST_End)
    {
        return a_loc;
    }

    if (m_type == ST_AssemblerInstr)
    {
        if (m_OpCode == "org")
        {
            try 
            {
                int loc = stoi(m_Operand1);

                // Check if ORG is out of memory bounds
                if (loc < 0 || loc >= Emulator::MEMSZ)
                {
                    Errors::RecordError("ORG operand out of memory bounds: " + m_Operand1);
                    return a_loc;
                }
                return loc;
            }
            catch (...)
            {
                return a_loc;
            }
        }

        if (m_OpCode == "ds")
        {
            try
            {
                int storage_size = stoi(m_Operand1);
                
                // Prevent overflow wrapping
                if (a_loc + storage_size > Emulator::MEMSZ)
                {
                    Errors::RecordError("DS operand causes memory overflow.");
                    return a_loc;
                }
                return a_loc + storage_size;
            }
            catch (...)
            {
                return a_loc;
            }
        }

        if (m_OpCode == "dc")
        {
            return a_loc + 1;
        }
    }

    // For machine language instructions, simply increment by 1.
    return a_loc + 1;
}