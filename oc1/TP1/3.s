.data
	array: .word 27, 16, 20, 49, 39, 48, 38, 7, 5, 19
	size:  .word 10

.text
## Load test data
la a0, array # first arg is array start pointer
lw a1, size # second arg is array size

## Based on:
# void insertionSort(int arr[], int n) {
#   int i, key, j;
#   for (i = 1; i < n; i++) {
#     key = arr[i];
#     j = i - 1;
#     while (j >= 0 && arr[j] > key) {
#       arr[j + 1] = arr[j];
#       j = j - 1;
#     }
#     arr[j + 1] = key;
#   }
# }
insertion_sort:
	li t0, 0 # t0 = i = 0
	li t6, 2 # size of int in bytes, 2 in 32bit and 4 in 64bit
	for_begin:
		addi t0, t0, 1 # i++
		bgt t0, a1, for_end # !(i < n)

		mul t2, t6, t0 # index byte offset
		add t3, t2, a0
		lw t1, 0(t3) # t1 = key = arr[i];
		addi t2, t0, -1 # t2 = j = i - 1

		while_begin:
			bltz t2, while_end # !(j >= 0)

			mul t3, t6, t2
			add t4, t3, a0
			lw t3, 0(t4) # t3 = arr[j]

			blt t3, t1, while_end # !(arr[j] > key)

			sw t3, 4(t4) # arr[j + 1] = arr[j];
			addi t2, t2, -1 # j = j - 1;
			j while_begin

		while_end:
		addi t4, t2, 1 # t4 = j + 1
		mul t5, t6, t4
		add t4, t5, a0
		sw t1, 0(t4) # arr[t4] = key;

		j for_begin

	for_end:
		li a0, 0 # return zero, to play nice on my console
		# also, its up to the caller to save the original a0