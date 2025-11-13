//
//  Implementation of Instruction Class.
// 

#include "stdafx.h"
#include <sstream>
#include "Instruction.h"
#include "Errors.h"

string Instruction::RemoveComment( string line ) {
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

    string extra;

    if (line[0] != ' ' && line[0] != '\t')
    {
        ins >> label;
    }
    ins >> opcode >> operand1 >> operand2 >> extra;

    return extra == "";
}

Instruction::InstructionType Instruction::ParseInstruction(string a_line)
{
    a_line = RemoveComment(a_line);

    // Removed comments become whitespace
    // So label whitespace as ST_Comment
    if (a_line.find_first_not_of("\t\n\r") == string::npos)
    {
        m_type = ST_Comment;
        return m_type;
    }

    if (!ParseLine(a_line, m_Label, m_OpCode, m_Operand1, m_Operand2))
    {
        Errors::RecordError("Failed to parse instruction: " + a_line);
    }

    // Convert all m_OpCode(s) to lower
    for (auto& c : m_OpCode)
    {
        c = tolower(c);
    }

    if (m_OpCode == "end")
    {
        m_type = ST_End;
        return m_type;
    }

    // Create vector of all potential m_opCodes
    static const vector<string> machineOps = {"add", "subtract", "mult", "div", "copy", "read", "write", "b", "bm", "bz", "bp", "halt"};

    if (find(machineOps.begin(), machineOps.end(), m_OpCode) != machineOps.end())
    {
        m_type = ST_MachineLanguage;
        return m_type;
    }

    if (m_OpCode == "org" || m_OpCode == "dc" || m_OpCode == "ds")
    {
        m_type = ST_AssemblerInstr;
        return m_type;
    }

}

int Instruction::LocationNextInstruction(int a_loc)
{
    if (m_type == ST_Comment || m_type == ST_End)
    {
        return a_loc;
    }

    if (m_type == ST_AssemblerInstr)
    {
        if (m_OpCode == "org")
        {
            return a_loc;
        }

        if (m_OpCode == "ds")
        {
            int storage_size = 0;

            try
            {
                storage_size = stoi(m_Operand1);
            }
            // Catch if unable to convert to int
            catch (const invalid_argument& e)
            {
                Errors::RecordError("ds operand is an invalid integer: " + m_Operand1);
                return a_loc + 1;
            }
            // Catch if integer is too large
            catch (const out_of_range& e)
            {
                Errors::RecordError("ds operand is too large: " + m_Operand1);
                return a_loc + 1;
            }

            return a_loc + storage_size;
        }

        if (m_OpCode == "dc")
        {
            return a_loc + 1;
        }
    }

    if (m_type == ST_MachineLanguage)
    {
        return a_loc + 1;
    }

    return a_loc;
}