//
//  Implementation of Instruction Class.
// 

#include "stdafx.h"
#include <sstream>
#include "Instruction.h"
#include "Errors.h"

/// <summary>
/// Removes any portion of an assembly instruction line following a semicolon (';'), 
/// which is treated as a comment. If no semicolon is present, the line is returned unchanged.
/// </summary>
/// <param name="line">The assembly instruction line that may contain a comment.</param>
/// <returns>The input line with any comment (text after a semicolon) removed.</returns>
/// <author>Race Partin</author>
/// <date>01:04pm 10/25/2025</date>
string Instruction::RemoveComment( string line ) {
    size_t pos = line.find(';');
    if (pos == string::npos)
    {
        return line;
    }
    return line.erase(pos);
}

/// <summary>
/// Parses an assembly instruction line into its core components: **label**, **opcode**, and up to two **operands**.
/// If the line begins with a non-whitespace character, it is assigned to the label. Otherwise, the parser skips 
/// the label field and extracts the opcode and operands sequentially.
/// </summary>
/// <param name="line">The assembly instruction line to be parsed.</param>
/// <param name="label">Receives the label portion of the instruction, otherwise empty.</param>
/// <param name="opcode">Receives the operation code from the instruction line.</param>
/// <param name="operand1">Receives the first operand following, if present. Set to empty if no operand.</param>
/// <param name="operand2">Receives the second operand following, if present. Set to empty if no operand.</param>
/// <returns>Returns true if the line was successfully parsed with no extra tokens collected, false otherwise.</returns>
/// <author>Race Partin</author>
/// <date>12:50pm 10/25/2025</date>
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
            catch (const invalid_argument& e)
            {
                Errors::RecordError("ds operand is an invalid integer: " + m_Operand1);
                return a_loc + 1;
            }
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