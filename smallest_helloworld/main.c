__declspec(dllimport) void* __stdcall GetStdHandle(unsigned long nStdHandle);
__declspec(dllimport) int __stdcall WriteFile(void* hFile, const void* lpBuffer, unsigned long nNumberOfBytesToWrite, unsigned long* lpNumberOfBytesWritten, void* lpOverlapped);
__declspec(dllimport) void __stdcall ExitProcess(unsigned int uExitCode);
void __stdcall mainCRTStartup(void) {
    void* hStdout = GetStdHandle((unsigned long)-11);
    const char msg[] = "Hello, world!";
    unsigned long written;
    WriteFile(hStdout, msg, 13, &written, 0);
    ExitProcess(0);
}
