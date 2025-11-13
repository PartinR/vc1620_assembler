//
//  File access to source file.
//
#ifndef _FILEACCESS_H  // This is the way that multiple inclusions are defended against often used in UNIX
#define _FILEACCESS_H  // We use pragmas in Visual Studio and g++.  See other include files

#include <fstream>
#include <stdlib.h>
#include <string>

class FileAccess {

public:

    /// <summary>
    /// Initializes the FileAccess object and opens the source file for reading.
    /// </summary>
    /// <param name="argc">The number of command-line arguments passed to the program.</param>
    /// <param name="argv">The array of command-line arguments; expects argv[1] to be the file name</param>
    /// <author>Race Partin</author>
    /// <date>11/12/2025 9:51pm</date.
    FileAccess( int argc, char* argv[] );

    /// <summary>
    /// Destructor for the FileAccess Class. Closes the source file upon object destruction.
    /// </summary>
    /// <author>Race Partin</author>
    /// <date>11/12/2025 10:45pm</date>
    ~FileAccess( );

    /// <summary>
    /// Retrieves the next line from the source file.
    /// </summary>
    /// <param name="a_line">Reference to a string where the retrieved line will be stored.</param>
    /// <returns>Returns true if line was successfully read, false if eof was reached</returns>
    bool GetNextLine( string &a_line );

    /// <summary>
    /// Resets the file pointer to the beginning of the source file.
    /// </summary>
    /// <author>Race Partin</author>
    /// <date>11/12/2025 10:49pm</date>
    void rewind( );

private:

    ifstream m_sfile;		// Source file object.
};
#endif