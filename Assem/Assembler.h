//
//  Assembler class.  This is a container for all the components
//  that make up the assembler.
//
#pragma once 

#include "SymTab.h"
#include "Instruction.h"
#include "FileAccess.h"
#include "Emulator.h"


class Assembler {

public:

    /// <summary>
    /// Initializes the Assembler class, setting up the necessary components for assembly processing. 
    /// This constructor passes the application's command-line arguments (<paramref name="argc"/> and 
    /// <paramref name="argv"/>) directly to the internal file access component (m_facc) for initialization.
    /// </summary>
    /// <param name="argc">The number of command-line arguments provided to the main program.</param>
    /// <param name="argv">The array of command-line argument strings provided to the main program.</param>
    /// <author>Race Partin</author>
    /// <date>11/05/2025 10:04pm</date>
    Assembler( int argc, char *argv[] );

    ~Assembler( );

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
    void PassI( );

    // Pass II - generate a translation
    void PassII( );

    // Display the symbols in the symbol table.
    void DisplaySymbolTable( ) 
    { 
        m_symtab.DisplaySymbolTable(); 
    }
    
    // Run emulator on the translation.
    void RunProgramInEmulator( );

private:

    FileAccess m_facc;	    // File Access object
    SymbolTable m_symtab;   // Symbol table object
    Instruction m_inst;	    // Instruction object
    Emulator m_emul;        // Emulator object
};