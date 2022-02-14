
	# 99beer_skeleton
    .data

 

	msg1:  .string "bottles of beer on the wall, "
	msg2:  .string "%d "
	msg3:  .string "bottles of beer, take one down, pass it around, "
	msg4:  .string "bottles of beer on the wall.\n"
	

	i:  	.quad 99

        .text
        .global main

main:

    /* for elf-function call compatibility. Do not touch. */

	pushq    %rbp
	movq     %rsp ,%rbp

       /* Program code starts here */
	loop: # program block label. this can now be used as a jump point.

	movq    i, %rsi # read the value from integer i to register %rsi ,rsi is used as parameter for printing
	movq 	$msg2, %rdi
	call printf #print the number
	
	movq    $msg1, %rdi # read the value from string msg2 to register %rdi ,rdi is used as parameter for printing
	call    printf #print the first text
	
	movq    i, %rsi # read the value from integer i to register %rsi ,rsi is used as parameter for printing
	movq	$msg2, %rdi
	call printf #print the number again
	
	movq	$msg3, %rdi
	call printf #print the next text
	
	decq	i # decrease the value of i by one
	movq	i, %rsi
	movq	$msg2, %rdi
	call printf #print the decreased number
	
	movq 	$msg4, %rdi
    	call    printf # print last text
    	
    	
    	
    	cmpq    $94, i # compare i to 94 as 5 first pages had to be printed
    	jne     loop # if comparison not equal, jump to beginning of loop

    	/* Program code ends here */
    	/* for compatibility. Do not touch ... */
    	movq    %rbp, %rsp
    	popq    %rbp
    	ret    $0
