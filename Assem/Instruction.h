//
//  Class to parse and provide information about instructions.
//
#pragma once

#include "Errors.h"

class Instruction {

public:

    Instruction( ) { };
    ~Instruction( ) { };

    // Codes to indicate the type of instruction we are processing.  Why is this inside the
    // class?  We should make this an enum class.  We will do this during a lecture.
    enum InstructionType {
        ST_MachineLanguage, 	// A machine language instruction.
        ST_AssemblerInstr,      // Assembler Language instruction.
        ST_Comment,             // Comment or blank line
        ST_End                  // end instruction.
    };

    /// <summary>
    /// Parses a raw assembly instruction line into its core components after first removing 
    /// any trailing comments defined by a semicolon.
    /// This function calls RemoveComment to clean the input line and then attempts to parse the 
    /// result into the internal instruction fields (label, opcode, operands). If the parsing operation
    /// fails, an error is recorded using the Errors::RecordError utility.
    /// </summary>
    /// <param name="a_line">The raw assembly line, potentially containing comments and instruction data.</param>
    /// <returns>An InstructionType value, currently defaulting to ST_Comment.</returns>
    /// <author>Race Partin</author>
    /// <date>11/05/2025 9:43pm</date>
    InstructionType ParseInstruction ( string a_line );

    /// <summary>
    /// Computes and returns the location of the instruction immediately following the current one.
    /// This function is used to advance the location counter based on the instruction type. 
    /// It must be called after the instruction has been successfully parsed.
    /// </summary>
    /// <param name="a_loc">The current memory address (Location Counter) before the current instruction is processed.</param>
    /// <returns>The calculated location counter value for the instruction immediately following the current one.</returns>
    /// <author>Race Partin</author>
    /// <date>10/25/2025 10:29pm</date>
    int LocationNextInstruction( int a_loc );

    // To access the label
    inline string &GetLabel( ) 
    {
        return m_Label;
    };

    // To determine if a label is blank.
    inline bool isLabel( ) 
    {
        return ! m_Label.empty();
    };


private:

    /// <summary>
    /// Removes any portion of an assembly instruction line following a semicolon (';'), 
    /// which is treated as a comment. If no semicolon is present, the line is returned unchanged.
    /// </summary>
    /// <param name="line">The assembly instruction line that may contain a comment.</param>
    /// <returns>The input line with any comment (text after a semicolon) removed.</returns>
    /// <author>Race Partin</author>
    /// <date>10/25/2025 01:04pm</date>
    string RemoveComment( string line );

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
    /// <date>10/25/2025 12:50pm</date>
    bool ParseLine( const string& line, string& label, string& opcode, string& operand1, string &operand2 );

    // The elemements of a instruction
    string m_Label;        // The label.
    string m_OpCode;       // The symbolic op code.
    string m_Operand1;      // The operands. 
    string m_Operand2; 

    string m_instruction;  // The original instruction.

    // Derived values.
    int m_NumOpCode;       // The numerical value of the op code for machine language equivalents.
    InstructionType m_type;// The type of instruction.

    bool m_IsNumericOperand;// == true if the operand is numeric.
    int m_Operan1Value;   // The value of the operand if it is numeric.
};