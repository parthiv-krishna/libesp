// Code entry point: calls start function

.globl reset
reset:
    jal start
// if start returns, infinite loop
reset_loop:
    j reset_loop

