addi $t0, $zero, 0x10010018

lw $t3, 0x10010010

add $t1, $s0, $t3

lw $t2, 4($t0)
add $t1, $t1, $t2

sw $t1, 12($t0)