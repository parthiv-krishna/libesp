# Code entry point: calls start function

.globl _reset
_reset:
    jal start

# if start returns, infinite loop
loop:
    j loop
