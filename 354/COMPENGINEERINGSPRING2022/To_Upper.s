	.file	"To_Upper.s"
	.text
	.globl	To_Upper
	.type	To_Upper, @function

/* **********************
    Name: Casey Waddell
    Wisc ID Number: 9082630956
    Wisc Email: ctwaddell@wisc.edu
************************ */


To_Upper:

# C version
/* **********************
    Write the equivalent C code to this function here (in the comment block)
void ToUpper(char* str)
{
    while(*str != '\0')
    {
        if(*str >= 97 && *str <= 122)
        {
            *str -= 32;
        }
        str++;   
    }
    return;
}
************************ */


# Memory Layout
/* ************************ 
    Make a table showing the stack frame for your function (in the comment block)
    The first column should have a memory address (e.g. 8(%rsp))
    The second column should be the name of the C variable used above
    Update the example below with your variables and memory addresses
        -8(%rbp) |  char* str
************************ */


# Prologue
pushq %rbp #push base pointer
movq %rsp, %rbp #establish current stack frame
movq %rdi, -8(%rbp) #move pointer address into -8(%rbp)
movq %rdi, %rax #move pointer into rax

# This code prints the letter 'a' (ascii value 97)
# Use this for debugging
# Comment out when finished - your function should not print anything
# Note putchar overwrites all caller saved registers including argument registers
#movl	$97, %eax
#movl	%eax, %edi
#call	putchar@PLT

# Body of function
LOOPTOP: #The top of the loop
movq $0, %r9 #move immediate 0 into %r9
cmp %rax, %r9 #compare the address of rax with 0
jz END #if address of r9 is 0, it means char* == NULL, so end the program
movb (%rax), %r8b #move value of pointer into r8b
movq $0, %r9 #move 0 into r9
cmp %r8, %r9 #compare 0 to the value in rax 
jz END #if the result is 0, it means the value in %rax is zero aka null terminator
movq $97, %r9 #move 97 into r9
cmp %r8, %r9 #compare 97 from the value of pointer 
jle CHECK #if the result is 0 or positive, it could be in the range
jmp INCREMENT #if the result is negative, increment pointer

CHECK: #checks if character is upper case
movq $122, %r9 #move pointer value into rax
cmp %r8, %r9 #compare 122 from the value of the pointer
jge CONDITION #if pointer - 122 is less than or equal to 0, it is a lowercase letter
jmp INCREMENT #else increment pointer

CONDITION: #since character is upper case, does arithmetic to lower it
movq $32, %r9 #move 32 into the r9 register
movb (%rax), %r11b #move value of pointer into r11b (for testing purposes)
sub %r9, (%rax) #subtract 32 from the value pointer points to
movb (%rax), %r10b #move value of pointer into r10b (for testing purposes)
jmp INCREMENT #increment pointer

INCREMENT: #increments character pointer to next character
inc %rax #since rdi is a char pointer, just increment its address by 1
jmp LOOPTOP #return to top of loop

# Epilogue
END: #cleanup before ret
movq %rbp, %rsp #deestablish current stack frame
popq %rbp #pop the base pointer 
ret #end of function
