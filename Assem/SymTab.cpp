//
//  Implementation of the symbol table class.  This is the format I want for commenting functions.
//

#include "stdafx.h"
#include "SymTab.h"

/// <summary>
/// Adds a new symbol along with its associated location to the internal symbol table.
/// This function will place the symbol <paramref name="a_symbol"/> and its location 
/// <paramref name="a_loc"/> into the symbol table for future reference.
/// </summary>
/// <param name="a_symbol">The name of the symbol to be added to the symbol table.</param>
/// <param name="a_loc">The location to be associated with the symbol.</param>
/// <returns>This function does not return a value (void).</returns>
/// <author>Race Partin</author>
/// <date>01:07pm 10/25/2025</date>
void SymbolTable::AddSymbol( const string &a_symbol, int a_loc )
{
    // If the symbol is already in the symbol table, record it as multiply defined.
    map<string, int>::iterator st = m_symbolTable.find( a_symbol );
    if( st != m_symbolTable.end() ) {

        st->second = multiplyDefinedSymbol;
        return;
    }
    // Record a the location in the symbol table.
    m_symbolTable[a_symbol] = a_loc;
}