.data
array: .word 10, 20, 30, 40    # Khai báo m?ng trong .data
.text
main:

add $s0, $s1, $s2 # s0 = s1 + s2

addi $t0, $s0, -5 # t0 = t0 -5

addu $t1, $t2, $t3 # t1 = t2 + t3 (khong dau)

addiu $t4, $zero, 3 # t4 = 0 + 3 (khong dau)

sub $s3, $s4, $s5 # s3 = s4 - s5

subu $t5, $t6, $t7 # t5 = t6 - t7 (khong dau)

and $t8, $t9, $s6 # t8 = t9 and s6 

andi $s7, $s0, 2 # s7 = s0 + 2

or $t9, $t8, $t7 # 

nor $s7, $s6, $s5   

la $s0, array # dua di chi array vao s0
lw $a0, 4($s0) # lay s0[1] (tuc la gia tri 20) vao a0

sw $a0, 8($s0) # luu a0 vao s0[2] (thay gia tri 30 thanh 20)

slt $t0, $s1, $s2 # t0 = (s1 < s2)

slti $t1, $s3, 100 # t1 = (s3 < 100)

sltu $t2, $s4, $s5 # t2 = (s4 < s5) (khong dau)

sltiu $t3, $s6, 4 # t3 = (s6 < 4) (khong dau)