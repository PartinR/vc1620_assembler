//
//  Implementation of the Assembler class.
//

#include "stdafx.h"
#include "Assembler.h"
#include "Instruction.h"
#include "MachineOps.h"
#include "Emulator.h"
#include "Errors.h"

Assembler::Assembler( int argc, char *argv[] )
: m_facc( argc, argv )
{
}

// Destructor currently does nothing.
Assembler::~Assembler( )
{
}

void Assembler::PassI( ) 
{
    int loc = 0;

    for (; ;)
    {
        string line; 
        if (!m_facc.GetNextLine(line)) 
        {
            // If there are no more lines, we are missing an end statement.
            return;
        }

        // Parse the line and get the instruction type.
        Instruction::InstructionType st =  m_inst.ParseInstruction(line);

        if (st == Instruction::ST_End) return;

        // Use standard logic for comments or errors, just move on
        if (st == Instruction::ST_Comment)  
        {
        	continue;
	    }

        // Record label if present
        if (m_inst.isLabel()) 
        {
            m_symtab.AddSymbol(m_inst.GetLabel(), loc);
        }

        loc = m_inst.LocationNextInstruction( loc );
    }
}

void Assembler::PassII( )
{
    m_facc.rewind(); // Reset file to start
    int loc = 0;     // Reset location counter

    cout << "\nTranslation of Program:" << endl;
    cout << left << setw(10) << "Location" << setw(15) << "Contents" << "Original Statement" << endl;

    for (; ;)
    {
        string line;
        if (!m_facc.GetNextLine(line))
        {
            break;
        }

        Instruction::InstructionType st = m_inst.ParseInstruction(line);

        if (st == Instruction::ST_Comment)
        {
            cout << "\t\t\t" << line << endl;
            continue;
        }

        // Explicitly handle errors caught during parsing (like illegal opcodes)
        if (st == Instruction::ST_Error)
        {
            cout << "\t\t\t " << line << " ?? ERROR" << endl;
            // Note: Errors are already recorded in Instruction::ParseInstruction
            continue;
        }

        if (st == Instruction::ST_End)
        {
            cout << "\t\t\t" << line << endl;
            return;
        }

        // Delegate to helpers based on type to keep this function clean
        if (st == Instruction::ST_AssemblerInstr)
        {
            HandleAssemblerInstruction(loc, line);
        }
        else if (st == Instruction::ST_MachineLanguage)
        {
            HandleMachineInstruction(loc, line);
        }
    }

    cout << endl;
    Errors::DisplayErrors();
}

void Assembler::HandleAssemblerInstruction( int& a_loc, const string& a_line )
{
    string opcode = m_inst.GetOpCode();

    if (opcode == "org")
    {
        try
        {
            a_loc = stoi(m_inst.GetOperand1());
            cout << left << setw(4) << a_loc << "\t\t     " << a_line << endl;
        }
        catch (...)
        {
            Errors::RecordError("Invalid ORG value: " + m_inst.GetOperand1());
            cout << "????" << "\t\t     " << a_line << endl;
        }
    }
    else if (opcode == "ds")
    {
        try
        {
            int count = stoi(m_inst.GetOperand1());
            cout << left << setw(4) << a_loc << "\t\t     " << a_line << endl;

            // Check for memory overflow
            if (a_loc + count > Emulator::MEMSZ) {
                Errors::RecordError("Error: DS causes memory overflow at loc " + to_string(a_loc));
            }
            else {
                a_loc += count;
            }
        }
        catch (...)
        {
            Errors::RecordError("Invalid DS value: " + m_inst.GetOperand1());
        }
    }
    else if (opcode == "dc")
    {
        try
        {
            long long value = stoll(m_inst.GetOperand1());
            m_emul.insertMemory(a_loc, value);
            PrintTranslation(a_loc, value, a_line);
            a_loc++;
        }
        catch (...)
        {
            Errors::RecordError("Invalid DC value: " + m_inst.GetOperand1());
            cout << "????" << "\t\t     " << a_line << endl;
        }
    }
}

void Assembler::HandleMachineInstruction( int& a_loc, const string& a_line )
{
    int opcode_value = 0;
    int operand1_addr = 0;
    int operand2_addr = 0;

    try
    {
        // Safe lookup for opcode (though ParseInstruction already validated it)
        auto ops = MachineOps::GetMachineOps();

        if (ops.find(m_inst.GetOpCode()) == ops.end()) 
        {
            Errors::RecordError("Illegal Opcode during translation: " + m_inst.GetOpCode());
            return;
        }

        opcode_value = ops.at(m_inst.GetOpCode());

        // Helper lambda to clean and resolve operands
        auto resolveOperand = [&](string op) -> int {
            if (op.empty()) return 0;

            // Remove commas
            op.erase(remove(op.begin(), op.end(), ','), op.end());

            int addr = 0;
            if (m_symtab.LookupSymbol(op, addr))
            {
                if (addr == SymbolTable::multiplyDefinedSymbol) {
                    Errors::RecordError("Symbol is multiply defined: " + op);
                    return 0; // Return 0 to prevent crash, error recorded
                }

                return addr;
            }

            // If not a symbol, try to parse as number
            try 
            {
                return stoi(op);
            }
            catch (...) 
            {
                Errors::RecordError("Undefined symbol or invalid address: " + op);
                return 0;
            }
        };

        operand1_addr = resolveOperand(m_inst.GetOperand1());
        operand2_addr = resolveOperand(m_inst.GetOperand2());
    }
    catch (...)
    {
        Errors::RecordError("Unexpected error assembling instruction: " + a_line);
    }

    // Encode contents: opcode(2) + addr1(5) + addr2(5)
    long long contents = (long long)opcode_value * 10000000000LL +
        (long long)operand1_addr * 100000LL +
        (long long)operand2_addr;

    m_emul.insertMemory(a_loc, contents);
    PrintTranslation(a_loc, contents, a_line);
    a_loc++;
}

void Assembler::PrintTranslation( int a_loc, long long a_contents, const string& a_line )
{
    cout << left << setw(5) << a_loc << "\t"
        << right << setfill('0') << setw(12) << a_contents << setfill(' ')
        << "   " << a_line << endl;
}

void Assembler::RunProgramInEmulator( )
{
    cout << "\nResults from emulating program:" << endl;

    if (!m_emul.runProgram())
    {
        cout << "Emulator has encountered an error." << endl;
        return;
    }

    cout << "End of emulation" << endl;
}