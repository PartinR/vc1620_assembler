//
//  Symbol table class.
//
#pragma once

// This class is our symbol table.
class SymbolTable {

public:

    // Get rid of constructor and destructor later if you don't need them.
    SymbolTable( ) {};
    ~SymbolTable( ) {};
    
    const int multiplyDefinedSymbol = -999;

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
    void AddSymbol( const string &a_symbol, int a_loc );

    // Display the symbol table.
    void DisplaySymbolTable( );

    // Lookup a symbol in the symbol table.
    bool LookupSymbol( const string &a_symbol, int &a_loc );

private:

    // This is the actual symbol table.  The symbol is the key to the map.  The value is the location.
    map<string, int> m_symbolTable;
};