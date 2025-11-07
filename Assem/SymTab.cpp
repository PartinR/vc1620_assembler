//
//  Implementation of the symbol table class.  This is the format I want for commenting functions.
//

#include "stdafx.h"
#include "SymTab.h"

void SymbolTable::AddSymbol( const string &a_symbol, int a_loc )
{
    // If the symbol is already in the symbol table, record it as multiply defined.
    map<string, int>::iterator st = m_symbolTable.find(a_symbol);

    if(st != m_symbolTable.end()) 
    {
        st->second = multiplyDefinedSymbol;
        return;
    }

    // Record a the location in the symbol table.
    m_symbolTable[a_symbol] = a_loc;
}

bool SymbolTable::LookupSymbol( const string& a_symbol, int& a_loc )
{
    auto it = m_symbolTable.find(a_symbol);

    if (it != m_symbolTable.end())
    {
        a_loc = it->second;
        return true;
    }
    else
    {
        return false;
    }
}

void SymbolTable::DisplaySymbolTable()
{
    cout << "Symbol Table:" << endl;
    cout << "Symbol#\t" << " Symbol\t" << " Location" << endl;

    int sym_count = 0;

    for (const auto& entry : m_symbolTable)
    {
        cout << sym_count++ << "\t";
        cout << entry.first << "\t";

        if (entry.second == multiplyDefinedSymbol)
        {
            cout << "Multiply Defined" << endl;
        }
        else
        {
            cout << " " << entry.second << endl;
        }
    }
}