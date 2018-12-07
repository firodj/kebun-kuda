#include <cstdio>
#include <cinttypes>
#include <unicorn/unicorn.h>

void hook_mem(uc_engine *uc, uc_mem_type type,
    uint64_t address, int size, int64_t value, void *user_data)
{
    uint64_t rip;
    uc_reg_read(uc, UC_X86_REG_RIP, &rip);
    printf("%p %s %p %d\n", rip, (type == UC_MEM_WRITE) ? "write" : type == UC_MEM_READ ? "read " : " unknown", address, size);
}

int main(int argc, char **argv)
{
    const uint8_t code[] = {
        "\x48\x8b\x00"  //  mov         rax,qword ptr [rax]  
        "\x48\x89\x01"  //   mov         qword ptr [rcx],rax  
        "\xcc"
    };

    uc_engine *uc;
    uc_open(UC_ARCH_X86, UC_MODE_64, &uc);
    uc_mem_map(uc, 0, 0x10000, UC_PROT_ALL);
    uc_mem_write(uc, 0, code, sizeof(code) - 1);

    uc_hook hh;
    uc_hook_add(uc, &hh, UC_HOOK_MEM_READ | UC_HOOK_MEM_WRITE, (void*)hook_mem, nullptr, 1, 0);

    const uint64_t addr = 0x2fff;
    uc_reg_write(uc, UC_X86_REG_RAX, &addr);
    uc_reg_write(uc, UC_X86_REG_RCX, &addr);
    uc_emu_start(uc, 0, sizeof(code) - 1, 0, 2);

    return 0;
}

