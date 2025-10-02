.data
array1: .word 5, 6, 7, 8, 1, 2, 3, 9, 10, 4
size1:  .word 10

array2: .byte 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16
size2:  .word 16

array3: .space 8       # Cap phat 8 byte, chua khoi gia tri
size3:  .word 8

# Chuoi de in newline va in prompt
newline:   .asciiz "\n"

promptArr: .asciiz "nhap mang (1-3): "
promptIdx: .asciiz "nhap chi so: "

.text
.globl main

main:
    # 1) In ra toan bo cac phan tu cua array1
    la   $t0, size1
    lw   $t2, 0($t0)     # $t2 = size1 = 10

    li   $t1, 0          # $t1 = i = 0
    la   $t3, array1     # $t3 = base address cua array1

print_array1_loop:
    beq  $t1, $t2, done_print_array1
    # Tinh address = base + i*4
    sll  $t4, $t1, 2     # $t4 = i << 2
    add  $t5, $t3, $t4   # $t5 = &array1[i] (pseudo code)
    lw   $t6, 0($t5)     # $t6 = array1[i]

    # In gia tri ($t6) ra man hinh
    add $a0, $t6, $zero
    li   $v0, 1 # ma "print integer"
    syscall

    # In mot dau space
    li   $a0, 32         # ASCII code = 32 = ' '
    li   $v0, 11 # print ki tu ASCII ra man hinh
    syscall

    addi $t1, $t1, 1     # i++
    j    print_array1_loop

done_print_array1: # ket thuc vong lap

    # In newline
    la   $a0, newline
    li   $v0, 4
    syscall

    # 2) In ra toan bo cac phan tu cua array2
    la   $t0, size2
    lw   $t2, 0($t0)     # $t2 = size2 = 16

    li   $t1, 0
    la   $t3, array2

print_array2_loop:
    beq  $t1, $t2, done_print_array2
    # Address = base + i
    add  $t5, $t3, $t1   # $t5 = &array2[i]
    lbu  $t6, 0($t5)     # $t6 = array2[i] # lenh co ban, load 1 byte (8 bit)

    # In $t6
    add $a0, $t6, $zero
    li   $v0, 1
    syscall

    # In space
    li   $a0, 32
    li   $v0, 11
    syscall

    addi $t1, $t1, 1
    j    print_array2_loop

done_print_array2:
    # In newline
    la   $a0, newline
    li   $v0, 4 # print string
    syscall

    # -----------------------------------------------------------------------   
    # 3) Tinh array3[i] = array2[i] + array2[size2-1-i]
    la   $t0, size2
    lw   $t2, 0($t0)     # $t2 = size2 = 16
    la   $t0, size3
    lw   $t3, 0($t0)     # $t3 = size3 = 8

    li   $t1, 0
    la   $t4, array2
    la   $t6, array3

compute_array3_loop:
    beq  $t1, $t3, done_compute_array3

    # Lay array2[i]
    add  $t7, $t4, $t1   # $t7 = &array2[i]
    lbu  $t5, 0($t7)     # $t5 = array2[i]

    # Tinh j = size2 - 1 - i
    addi $t8, $t2, -1   # t8 = size2 - 1
    sub  $t8, $t8, $t1 # t8 = (size2-1) - i

    # Lay array2[j]
    add  $t8, $t8, $t4 # $t8 = &array2[j]
    lbu  $t7, 0($t8)   # $t7 = array2[j]

    # Cong
    add  $t5, $t5, $t7
    # Luu vao array3[i]
    add  $t7, $t6, $t1  # $t7 = &array3[i]
    sb   $t5, 0($t7)   # ghi 1 byte

    addi $t1, $t1, 1
    j    compute_array3_loop

done_compute_array3:
    # (Khong in array3 ra, vi de khong yeu cau)



    # 4) Cho nguoi dung nhap: so mang (1-3) va chi so, roi in phan tu tuong ung (khong co thong bao loi)
    # In prompt “Enter array number (1-3): ”
    la   $a0, promptArr
    li   $v0, 4
    syscall

    # Doc so mang vao $t0
    li   $v0, 5 # read integer
    syscall
    add $t0, $v0, $zero          # $t0 = array_number

    # In prompt “Enter index: ”
    la   $a0, promptIdx
    li   $v0, 4
    syscall

    # Doc index vao $t1
    li $v0, 5 # read integer
    syscall
    add $t1, $v0, $zero          # $t1 = index

    # So sanh va xu ly tung mang (neu khac 1,2,3 ? exit)
    li   $t2, 1
    beq  $t0, $t2, handle_array1
    li   $t2, 2
    beq  $t0, $t2, handle_array2
    li   $t2, 3
    beq  $t0, $t2, handle_array3

    # Neu t0 ? 1,2,3 thi nhay thang ra exit
    j    exit_program

handle_array1:
    # Tinh dia chi array1[index]
    # (gia su index hop le 0 <= index < size1)
    sll  $t3, $t1, 2       # $t3 = index << 2
    la   $t4, array1       # $t4 = base array1
    add  $t5, $t4, $t3     # $t5 = &array1[index]
    lw   $t6, 0($t5)       # $t6 = array1[index]
    j    print_result

handle_array2:
    la   $t4, array2       # $t4 = base array2
    add  $t5, $t4, $t1     # $t5 = &array2[index]
    lbu  $t6, 0($t5)       # $t6 = array2[index]
    j    print_result

handle_array3:
    la   $t4, array3       # $t4 = base array3
    add  $t5, $t4, $t1     # $t5 = &array3[index]
    lbu  $t6, 0($t5)       # $t6 = array3[index]
    j    print_result

print_result:
    # In ket qua ($t6) roi newline
    add $a0, $t6, $zero
    li   $v0, 1 #  print integer
    syscall

    la   $a0, newline
    li   $v0, 4 # print string
    syscall

exit_program:
    li   $v0, 10
    syscall