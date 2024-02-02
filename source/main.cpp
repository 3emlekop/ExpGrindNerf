#include "cube.h"
#include <windows.h>

int __cdecl Creature__CalculateMaxExp(cube::Creature *creature)
{
    int level = creature->level;
    int result = (int)((1 - (1 / ((level - 1) * 0.006 + 1))) * 1000 + 10);
    return result;
}

unsigned int Creature__CalculateMaxExp_ptr = (unsigned int)&Creature__CalculateMaxExp;

unsigned int inlinefix1_jmp_back;
void __declspec(naked) __declspec(noinline) inlinefix1()
{
    __asm
    {
        call [Creature__CalculateMaxExp_ptr]
        jmp[inlinefix1_jmp_back]
    }
}

unsigned int inlinefix2_jmp_back;
void __declspec(naked) __declspec(noinline) inlinefix2()
{
    __asm
    {
        push ecx
        mov ecx, esi
        call [Creature__CalculateMaxExp_ptr]
        pop ecx
        jmp [inlinefix2_jmp_back]
    }
}

unsigned int inlinefix3_jmp_back;
void __declspec(naked) __declspec(noinline) inlinefix3()
{
    __asm
    {
        push ecx
        mov ecx, esi
        call [Creature__CalculateMaxExp_ptr]
        pop ecx
        jmp [inlinefix3_jmp_back]
    }
}

void WriteJMP(BYTE *location, BYTE *newFunction)
{
    DWORD dwOldProtection;
    VirtualProtect(location, 5, PAGE_EXECUTE_READWRITE, &dwOldProtection);
    location[0] = 0xE9; // jmp
    *((DWORD *)(location + 1)) = (DWORD)((unsigned int)newFunction - (unsigned int)location - 5);
    VirtualProtect(location, 5, dwOldProtection, &dwOldProtection);
}

unsigned int base;
extern "C" __declspec(dllexport) bool APIENTRY DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
    switch (fdwReason)
    {
    case DLL_PROCESS_ATTACH:
        base = (unsigned int)GetModuleHandle(NULL);
        WriteJMP((BYTE *)(base + 0x44D60), (BYTE *)(Creature__CalculateMaxExp_ptr));

        inlinefix1_jmp_back = base + 0x47B5E;
        WriteJMP((BYTE *)(base + 0x47B11), (BYTE *)&inlinefix1);

        inlinefix2_jmp_back = base + 0x47BA3;
        WriteJMP((BYTE *)(base + 0x47B7A), (BYTE *)&inlinefix2);

        inlinefix3_jmp_back = base + 0x47C10;
        WriteJMP((BYTE *)(base + 0x47BBF), (BYTE *)&inlinefix3);
    }
    return true;
}
