// Code entry point: calls start function

.globl reset
reset:
    jal start
// if start returns, infinite loop
reset_loop:
    j reset_loop


// void spin(int numiters)
.globl spin
spin:
    j spin_cond
spin_loop:
    addi a0, a0, -1
spin_cond:
    bgtz a0, spin_loop
    ret

