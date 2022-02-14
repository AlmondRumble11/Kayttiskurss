   # one_to_ten.s

    .data

        # declare variables string "msg" and integer "i" and set their

        # initial values

       msg1:     .string "Countdown:\n"

    msg2:  .string "%d\n"

    i:    .quad 10

        .text

        .global main

main:

    /* for elf-function call compatibility. Do not touch. */

    pushq     %rbp

       movq     %rsp ,%rbp

       /* Program code starts here */

       movq    $msg1, %rdi

       call    printf

loop: # program block label. this can now be used as a jump point.

    movq    i, %rsi # read the value from integer i to register %rsi ,rsi is used as parameter for printing

    movq     $msg2, %rdi # read the value from string msg2 to register %rdi ,rdi is used as parameter for printing

    call     printf # call the printf function with %rsi and %rdi as parameters

    decq     i # decrease the value of i by one

    cmpq     $0, i # compare i to 0

    jne     loop # if comparison not equal, jump to beginning of loop

    /* Program code ends here */

    /* for compatibility. Do not touch ... */

    movq    %rbp, %rsp

    popq    %rbp

    ret    $0
