#define STD_OUTPUT_HANDLE ((unsigned long)-11)
typedef unsigned int DWORD;
typedef int BOOL;
typedef void* HANDLE;

__declspec(dllimport) HANDLE __stdcall GetStdHandle(DWORD nStdHandle);
__declspec(dllimport) BOOL __stdcall WriteConsoleA(
    HANDLE hConsoleOutput,
    const void* lpBuffer,
    DWORD nNumberOfCharsToWrite,
    DWORD* lpNumberOfCharsWritten,
    void* lpReserved
);
__declspec(dllimport) void __stdcall ExitProcess(unsigned int uExitCode);


int main(void)
{
    HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
    WriteConsoleA(output, "Hello, world!", 13, 0, 0);

    return 0;
}

void mainCRTStartup()
{
    int result = main();
    ExitProcess(result);
}

//cl /O1 helloworld.c /link kernel32.lib user32.lib