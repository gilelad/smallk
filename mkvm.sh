#!/bin/bash

exec qemu-system-x86_64 \
        -cpu qemu32 \
        -boot order=d \
        -cdrom os.iso \
        -net nic -net user,hostname=gentoovm \
        -m 256M \
        -monitor stdio \
        -name "osdev VM" \
        $@
