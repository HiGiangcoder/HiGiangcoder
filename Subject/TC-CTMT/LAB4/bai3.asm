.data
newline:   .asciiz "\n"

promptArr: .asciiz "nhap n: "
promptIdx: .asciiz "nhap gia tri thu "
promptSpace: .asciiz ": "

.text

    la $a0, promptArr
    li $v0, 4
    syscall
    
    # doc n
    li $v0, 5
    syscall
    add $s2, $v0, $zero # $s2 = n
    
    
    add $t0, $zero, $zero
    
    Loop:
    beq $t0, $s2, Endloop
    
    	la $a0, promptIdx
    	li $v0, 4
    	syscall
    	
    	add $a0, $zero, $t0
    	li $v0, 1
    	syscall
    	
    	la $a0, promptSpace
    	li $v0, 4
    	syscall
    	
    	# nhap a[i]
    	li $v0, 5
    	syscall
    	sll $t1, $t0, 2
    	add $t1, $t1, $s3
    	sw $v0, 0($t1)
    	
    	addi $t0, $t0, 1
    j Loop
    Endloop:
        
                
# so sanh i < j
    slt   $t0, $s0, $s1       # neu i < j thi $t0 = 1, nguoc lai = 0
    beq   $t0, $zero, ELSE    # neu $t0 == 0 (i >= j) thi nhay sang ELSE

    # TH1: i < j  --> A[i] = i
    sll   $t1, $s0, 2         # $t1 = i * 4  (khoang cach byte cho int)
    add   $t1, $t1, $s3       # $t1 = dia chi A + i*4
    sw    $s0, 0($t1)         # luu i vao A[i]
    j     END_IF              # nhay qua phan ELSE

ELSE:
    # TH2: i >= j  --> A[i] = j
    sll   $t1, $s0, 2         # $t1 = i * 4
    add   $t1, $t1, $s3       # $t1 = dia chi A + i*4
    sw    $s1, 0($t1)         # luu j vao A[i]

END_IF:

   