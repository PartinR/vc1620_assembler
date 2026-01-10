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

    /// <summary>
    /// Performs Pass II of the assembly process to display the translation of the program and 
    /// load it into memory for the emulator. This function rewinds and iterates throught the 
    /// source file line by line again in order to display and insert into the emulator memory.
    /// Any Errors from Pass I and Pass II will be thrown here as well.
    /// </summary>
    /// <returns>This function does not return a value (void).</returns>
    /// <author>Race Partin</author>
    /// <date>11/21/2025 9:25pm</date>
    void PassII( );

    /// <summary>
    /// Displays the contents of the assembler's symbol table by forwarding
    /// the request to the internal SymbolTable object.
    /// </summary>
    /// <author>Race Partin</author>
    /// <date>11/12/2025 10:59pm</date>
    void DisplaySymbolTable( ) 
    { 
        m_symtab.DisplaySymbolTable(); 
    }
    
    /// <summary>
    /// This function makes sure that the e_mul object can run the program then proceeds.
    /// </summary>
    /// <returns>This function does not return a value (void).</returns>
    /// <author>Race Partin</author>
    /// <date>11/21/2025 9:25pm</date>
    void RunProgramInEmulator( );

private:

    // --- Helper functions for Pass II Refactoring ---

    /// <summary>
    /// Handles translation and output for Assembler directives (ORG, DS, DC).
    /// </summary>
    /// <param name="a_loc">Current memory location (reference to update).</param>
    /// <param name="a_line">The original source line.</param>
    void HandleAssemblerInstruction(int& a_loc, const string& a_line);

    /// <summary>
    /// Handles translation and encoding for Machine Language instructions.
    /// </summary>
    /// <param name="a_loc">Current memory location (reference to update).</param>
    /// <param name="a_line">The original source line.</param>
    void HandleMachineInstruction(int& a_loc, const string& a_line);

    /// <summary>
    /// Helper to print standard output lines in Pass II.
    /// </summary>
    void PrintTranslation(int a_loc, long long a_contents, const string& a_line);

    FileAccess m_facc;	    // File Access object
    SymbolTable m_symtab;   // Symbol table object
    Instruction m_inst;	    // Instruction object
    Emulator m_emul;        // Emulator object
};