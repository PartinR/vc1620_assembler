//
//  Implementation of the Assembler class.
//

#include "stdafx.h"
#include "Assembler.h"
#include "Instruction.h"
#include "Errors.h"

/// <summary>
/// Initializes the Assembler class, setting up the necessary components for assembly processing. 
/// This constructor passes the application's command-line arguments (<paramref name="argc"/> and 
/// <paramref name="argv"/>) directly to the internal file access component (m_facc) for initialization.
/// </summary>
/// <param name="argc">The number of command-line arguments provided to the main program.</param>
/// <param name="argv">The array of command-line argument strings provided to the main program.</param>
/// <author>Race Partin</author>
/// <date>11/05/2025 10:04pm</date>
Assembler::Assembler( int argc, char *argv[] )
: m_facc( argc, argv )
{
    // Nothing else to do here at this point.
}

// Destructor currently does nothing.  You might need to add something as you develope this project.  If not, we can delete it.
Assembler::~Assembler( )
{
}

/// <summary>
/// Performs Pass I of the assembly process to establish the memory location of all labels.
/// This function iterates through the source file line by line, maintaining a location counter 
/// to track the address of the instructions being processed. Its primary role is to 
/// populate the symbol table (m_symtab) by recording every encountered label along with 
/// its calculated location. Lines marked as comments or the final END statement are 
/// used to control the flow of the pass. Missing END statements are allowed in this 
/// pass but will be reported as an error in Pass II.
/// </summary>
/// <returns>This function does not return a value (void).</returns>
/// <author>Race Partin</author>
/// <date>11/05/2025 10:08pm</date>
void Assembler::PassI( ) 
{
    // Tracks the location of the instructions to be generated.
    int loc = 0;

    // Successively process each line of source code.
    for( ; ; )
    {
        // Read the next line from the source file.
        string line; 
        if( ! m_facc.GetNextLine( line ) ) 
        {
            // If there are no more lines, we are missing an end statement.
            // We will let this error be reported by Pass II.
            return;
        }

        // Parse the line and get the instruction type.
        Instruction::InstructionType st =  m_inst.ParseInstruction( line );

        // If this is an end statement, there is nothing left to do in pass I.
        // Pass II will determine if the end is the last statement and report an error if it isn't.
        if( st == Instruction::ST_End ) return;

        // Labels can only be on machine language and assembler language
        // instructions.  So, skip comments.
        if( st == Instruction::ST_Comment )  
        {
        	continue;
	    }

        // If the instruction has a label, record it and its location in the
        // symbol table.
        if( m_inst.isLabel( ) ) 
        {
            m_symtab.AddSymbol( m_inst.GetLabel( ), loc );
        }

        // Compute the location of the next instruction.
        // loc = m_inst.LocationNextInstruction( loc );
    }
}

// TODO: Implement PassII