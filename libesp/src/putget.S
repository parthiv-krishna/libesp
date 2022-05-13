// Assembly helpers to avoid compiler optimization

// void put32_asm(uint32_t addr, uint32_t val);
.globl put32_asm
put32_asm:
    sw a1, 0(a0)
    ret


// uint32_t get32_asm(uint32_t addr);
.globl get32_asm
get32_asm:
    lw a0, 0(a0)
    ret