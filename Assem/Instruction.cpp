#include "stdafx.h"
#include <sstream>
#include "Instruction.h"
#include "Errors.h"

/*
NAME

    RemoveComment - removes comments defined by a semicolon in an assembly line.

SYNOPSIS

    string RemoveComment( string line );
        line        -> The assembly instruction line that may contains a comment.

DESCRIPTION

    This function recieves an assembly instruction line and removes any portion of the line following a
    semicolon (';'). If no semicolon is present, the line is returned unchanged.

RETURNS

    The input line with any comment (text after a semicolon) removed.

AUTHOR

    Race Partin

DATE

    01:04pm 10/25/2025

*/
string Instruction::RemoveComment( string line ) {
    size_t pos = line.find(';');
    if (pos == string::npos)
    {
        return line;
    }
    return line.erase(pos);
}

/*
NAME

    ParseLine - parses line into label, opcode, operand1, and operand2.

SYNOPSIS

    bool ParseLine( const string& line, string& label, string& opcode, string& operand1, string& operand2 );
        line        -> The assembly instruction line to be parsed.
        label       -> Recieves the label portion of the instruction, otherwise empty.
        opcode      -> Recieves the operation code from the instruction line.  
        operand1    -> Receives the first operand following, if present. Set to empty if no operand.
        operand2    -> Receives the second operand following, if present. Set to empty if no operand.
    
DESCRITPION

    This function parses an assembly instruction line into its key components: the label, opcode,
    and up to two operands. If the line begins with a non-whitespace character, it is assigned to 
    the label. Otherwise, the parser skips the label field and extracts the opcode and operands
    sequentially.

RETURNS

    Returns true if the line was parsed and no extra tokens were collected. Returns false
    if an extra token was collected.

AUTHOR

    Race Partin

DATE

    12:50pm 10/25/2025

*/
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