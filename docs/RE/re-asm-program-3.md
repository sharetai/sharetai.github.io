---
layout: default
title: ASM Program 3 [Moving Data Between Memory And Registers]
nav_order: 8
parent: RE
---

# ASM Program 3 [Moving Data Between Memory And Registers]
{: .no_toc }

ASM Chương trình 3 [Di chuyển dữ liệu giữa bộ nhớ và thanh ghi]
{: .fs-6 .fw-300 }

_Nguồn tham khảo: [https://0xinfection.github.io/reversing/](https://0xinfection.github.io/reversing/)_

---

## Table of contents
{: .no_toc .text-delta }

1. TOC
{:toc}

---

## Programming

Chương trình bên dưới thực hiện sao chép dữ liệu từ biến `memory` vào thanh ghi `ecx`.

__moving_data_between_memory_and_registers.asm__

{% capture code %}
{% highlight nasm linenos %}
;moving_data_between_memory_and_registers: mov data between mem and regs

section .data
    memory db 10

section .text                        ;Code Segment
    global _start

_start:                              ;User prompt
    nop                              ;used for debugging purposes

mov_immediate_data_between_memory_and_registers:
    mov ecx, [memory]                ;mov constant value into ECX register

exit:
    mov eax, 1                       ;sys_exit system call
    mov ebx, 0                       ;exit code 0 successful execution
    int 80h                          ;call sys_exit
{% endhighlight %}
{% endcapture %}
{% include fix_linenos.html code=code %}
{% assign code = nil %}

Biên dịch chương trình:

```
nasm -f elf32 moving_data_between_memory_and_registers.asm
ld -m elf_i386 -o moving_data_between_memory_and_registers moving_data_between_memory_and_registers.o
```

## Debugging

__nop__ (no operation) dùng với mục đích để debug breakpoint. Không quan trọng.

```conf
┌──(root㉿kali)-[~/box]
└─# gdb -q moving_data_between_memory_and_registers
Reading symbols from moving_data_between_memory_and_registers...
(No debugging symbols found in moving_data_between_memory_and_registers)
(gdb) b _start
Breakpoint 1 at 0x8049000
(gdb) run
Starting program: /root/box/moving_data_between_memory_and_registers

Breakpoint 1, 0x08049000 in _start ()
(gdb) info registers
eax            0x0                 0
ecx            0x0                 0
edx            0x0                 0
ebx            0x0                 0
esp            0xffffd3d0          0xffffd3d0
ebp            0x0                 0x0
esi            0x0                 0
edi            0x0                 0
eip            0x8049000           0x8049000 <_start>
eflags         0x202               [ IF ]
cs             0x23                35
ss             0x2b                43
ds             0x2b                43
es             0x2b                43
fs             0x0                 0
gs             0x0                 0
(gdb) disassemble /r
Dump of assembler code for function _start:
=> 0x08049000 <+0>:     90                      nop
End of assembler dump.
(gdb) stepi
0x08049001 in mov_immediate_data_between_memory_and_registers ()
(gdb) disassemble /r
Dump of assembler code for function mov_immediate_data_between_memory_and_registers:
=> 0x08049001 <+0>:     8b 0d 00 a0 04 08       mov    ecx,DWORD PTR ds:0x804a000
End of assembler dump.
(gdb) stepi
0x08049007 in exit ()
(gdb) x/4xb 0x804a000
0x804a000:      0x0a    0x00    0x00    0x00
(gdb) info registers
eax            0x0                 0
ecx            0xa                 10
edx            0x0                 0
ebx            0x0                 0
esp            0xffffd3d0          0xffffd3d0
ebp            0x0                 0x0
esi            0x0                 0
edi            0x0                 0
eip            0x8049007           0x8049007 <exit>
eflags         0x202               [ IF ]
cs             0x23                35
ss             0x2b                43
ds             0x2b                43
es             0x2b                43
fs             0x0                 0
gs             0x0                 0
(gdb)
```

## Hacking

Mục tiêu, dùng gdb để thay đổi giá trị của thanh ghi `ecx`.

```conf
(gdb) info registers
eax            0x0                 0
ecx            0xa                 10
edx            0x0                 0
ebx            0x0                 0
esp            0xffffd3d0          0xffffd3d0
ebp            0x0                 0x0
esi            0x0                 0
edi            0x0                 0
eip            0x8049007           0x8049007 <exit>
eflags         0x202               [ IF ]
cs             0x23                35
ss             0x2b                43
ds             0x2b                43
es             0x2b                43
fs             0x0                 0
gs             0x0                 0
(gdb) set $ecx=1337
(gdb) info registers
eax            0x0                 0
ecx            0x539               1337
edx            0x0                 0
ebx            0x0                 0
esp            0xffffd3d0          0xffffd3d0
ebp            0x0                 0x0
esi            0x0                 0
edi            0x0                 0
eip            0x8049007           0x8049007 <exit>
eflags         0x202               [ IF ]
cs             0x23                35
ss             0x2b                43
ds             0x2b                43
es             0x2b                43
fs             0x0                 0
gs             0x0                 0
(gdb)
```

