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

int Instruction::LocationNextInstruction(int a_loc)
{
    if (m_type == ST_Comment || m_type == ST_End)
    {
        return a_loc;
    }
}