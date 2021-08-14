.data # should be rodata, but venus doesn't recognize that
	TRUE:
		.word 1
	FALSE:
		.word 0

.text

li a0, 8

primo:
	li  t0, 1
	ble a0, t0, .return_false # if a0 <= 1 then return false

	li t0, 2 # t0 = 2
	.for_2_to_n: # t0 = index
		bge  t0, a0, .for_exit # if we reach index >= a0 then .return_true
		rem  t1, a0, t0 # a0 % index
		beqz t1, .return_false # if remainder is zero then return false
		addi t2, t0, 1 # t0 += 1
		mv   t0, t2 # t0 = t2
		j    .for_2_to_n
	.for_exit:

	j .return_true

	.return_true:
		lw a0, TRUE
		ret

	.return_false: # set return reg to false
		lw a0, FALSE
		ret
