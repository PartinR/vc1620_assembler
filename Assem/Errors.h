//
//  Class to manage error reporting. Note: all members are static so we can access them anywhere.
//  What other choices do we have to accomplish the same thing?
//
#ifndef _ERRORS_H
#define _ERRORS_H

#include <string>
#include <vector>

class Errors {

public:
    
    /// <summary>
    /// Initializes or resets the error reporting system by clearing all previously recorded error messages
    /// (stored in m_ErrorMsgs).
    /// </summary>
    /// <returns>This function does not return a value (void).</returns>
    /// <author>Race Partin</author>
    /// <date>11/06/2025 8:18pm</date>
    static void InitErrorReporting()
    {
        m_ErrorMsgs.clear();
    }

    /// <summary>
    /// Records a specific error message (<paramref name="a_emsg"/>) into the internal collection 
    /// of errors (m_ErrorMsgs).
    /// </summary>
    /// <param name="a_emsg">The descriptive error message to be recorded.</param>
    /// <returns>This function does not return a value (void).</returns>
    /// <author>Race Partin</author>
    /// <date>11/06/2025 8:20pm</date>
    static void RecordError( string a_emsg )
    {
        m_ErrorMsgs.push_back(a_emsg);
    }

    /// <summary>
    /// Displays all recorded error messages to the console standard error stream (cerr).
    /// </summary>
    /// <returns>This function does not return a value (void).</returns>
    /// <author>Race Partin</author>
    /// <date>11/06/2025 8:22pm</date>
    static void DisplayErrors()
    {
        for (string& em : m_ErrorMsgs)
        {
            cerr << em << endl;
        }
    }

private:

    static vector<string> m_ErrorMsgs;  // This must be declared in the .cpp file.  Why?
    									// There is an alternative: make this an inline variable.
    									// This is a newer feature.  We will talk ablout it in class.
};
#endif