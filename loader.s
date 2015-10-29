	global loader

	MAGIC_NUMBER equ 0x1BADB002 ; magic number constant
	FLAGS equ 0x0               ; multiboot flags
	CHECKSUM equ -MAGIC_NUMBER  ; (MAGIC_NUMBER + FLAGS + CHECKSUM = 0)

	KERNEL_STACK_SIZE equ 4096  ; kernel stack size in bytes

	section .bss
	align 4
kernel_stack:
	resb KERNEL_STACK_SIZE      ; reserve memory for kernel stack

	section .text
	align 4
	dd MAGIC_NUMBER             ; write MAGIC_NUMBER to machine code
	dd FLAGS                    ; the flags
	dd CHECKSUM                 ; and the checksum

loader:
	mov esp, kernel_stack + KERNEL_STACK_SIZE ; initialize the stack pointer to
	                                          ; top of stack area

	extern kmain				; the C kernel entrypoint
	call kmain
