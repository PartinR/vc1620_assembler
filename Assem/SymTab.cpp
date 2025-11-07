//
//  Implementation of the symbol table class.  This is the format I want for commenting functions.
//

#include "stdafx.h"
#include "SymTab.h"

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