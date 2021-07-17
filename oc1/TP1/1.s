.text
# Load test data to args
# li a0, 0 # a0 = V
# li a1, 0 # a1 = R
# li a2, 0 # a2 = I

# Program itself
seqz t1, a0
seqz t2, a1
seqz t3, a2
add t0, t1, t2
add t0, t0, t3
li t1, 1
bgt t0, t1, calc_zero # if more than 1 arg is 0 then calc_zero
beq a0, zero, calc_v # if V = 0 then calc_v

# setting our y for #calc_ri
bne a2, zero, move_I
mv t1, a1 # use R as divisor
j calc_ri
move_I: # use I as divisor
	mv t1, a2
	j calc_ri

calc_zero: # return zero
	li t0, 0
	j return

calc_v: # Multiplication: x = R * I
	mul t0, a1, a2 # discards upper 32 bits of 32x32 op, should I care about overflow?
	j return

calc_ri: # Division: x = V / y
	div t0, a0, t1

return: # set return register
	mv a0, t0
