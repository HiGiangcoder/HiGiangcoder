addi $s2, $zero, 0
addi $s0, $zero, 1

For:

slt $t0, $s1, $s0

bne $t0, $zero, End

add $s2, $s2, $s0

addi $s0, $s0, 1
j For

End: