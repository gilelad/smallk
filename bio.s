	global outb					; export outb function

	;; outb - send a byte to an I/O port
	;; stack: [esp + 4] the I/O port
	;;        [esp + 8] the data byte
	;;        [esp]     the return address
outb:
	mov dx, [esp+4]				; load I/O port into $dx
	mov al, [esp+8]				; load data to $al
	out dx, al                  ; send data to I/O port
	ret                         ; return to calling function
