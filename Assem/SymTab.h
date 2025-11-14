//
//  Symbol table class.
//
#pragma once

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
    /// <date>10/25/2025 01:07pm</date>
    void AddSymbol( const string &a_symbol, int a_loc );

    /// <summary>
    /// Displays the current contents of the internal symbol table to the console (standard output).
    /// The output typically includes the symbol index, the symbol name, and its location.
    /// </summary>
    /// <returns>This function does not return a value (void).</returns>
    /// <author>Race Partin</author>
    /// <date>11/6/2025 10:43pm</date>
    void DisplaySymbolTable( );

    /// <summary>
    /// Looks up a symbol's location in the symbol table.
    /// </summary>
    /// <param name="a_symbol">The name of the symbol to search for.</param>
    /// <param name="a_loc">Receives the location of the symbol if found.</param>
    /// <returns>true if the symbol was found in the table; otherwise, false.</returns>
    /// <author>Race Partin</author>
    /// <date>11/06/2025 10:08pm</date>
    bool LookupSymbol( const string &a_symbol, int &a_loc );

private:

    // This is the actual symbol table.  The symbol is the key to the map.  The value is the location.
    map<string, int> m_symbolTable;
};