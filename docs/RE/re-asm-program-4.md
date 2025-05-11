---
layout: default
title: ASM Program 4 [Moving Data Between Registers And Memory]
nav_order: 9
parent: RE
---

# ASM Program 4 [Moving Data Between Registers And Memory]
{: .no_toc }

ASM Chương trình 4 [Di chuyển dữ liệu giữa thanh ghi và bộ nhớ]
{: .fs-6 .fw-300 }

_Nguồn tham khảo: [https://0xinfection.github.io/reversing/](https://0xinfection.github.io/reversing/)_

---

## TABLE OF CONTENTS
{: .no_toc .text-delta }

1. TOC
{:toc}

---

## Programming

Chương trình bên dưới thực hiện sao chép dữ liệu từ thanh ghi `eax` vào biến `memory`.

__moving_data_between_registers_and_memory.asm__

{% capture code %}
{% highlight nasm linenos %}
;moving_data_between_registers_and_memory: mov data between regs and mem

section .data
    memory db 10

section .text                        ;Code Segment
    global _start

_start:                              ;User prompt
    nop                              ;used for debugging purposes

mov_immediate_data_between_registers_and_memory:
    mov eax, 777                     ;mov immediate value 777 to eax
    mov [memory], eax                ;mov eax value into memory value

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
nasm -f elf32 moving_data_between_registers_and_memory.asm
ld -m elf_i386 -o moving_data_between_registers_and_memory moving_data_between_registers_and_memory.o
```

## Debugging

__nop__ (no operation) dùng với mục đích để debug breakpoint. Không quan trọng.

```conf
┌──(root㉿kali)-[~/box]
└─# gdb -q moving_data_between_registers_and_memory
Reading symbols from moving_data_between_registers_and_memory...
(No debugging symbols found in moving_data_between_registers_and_memory)
(gdb) b _start
Breakpoint 1 at 0x8049000
(gdb) run
Starting program: /root/box/moving_data_between_registers_and_memory

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
0x08049001 in mov_immediate_data_between_registers_and_memory ()
(gdb) disassemble /r
Dump of assembler code for function mov_immediate_data_between_registers_and_memory:
=> 0x08049001 <+0>:     b8 09 03 00 00          mov    eax,0x309
   0x08049006 <+5>:     a3 00 a0 04 08          mov    ds:0x804a000,eax
End of assembler dump.
(gdb) stepi
0x08049006 in mov_immediate_data_between_registers_and_memory ()
(gdb) disassemble /r
Dump of assembler code for function mov_immediate_data_between_registers_and_memory:
   0x08049001 <+0>:     b8 09 03 00 00          mov    eax,0x309
=> 0x08049006 <+5>:     a3 00 a0 04 08          mov    ds:0x804a000,eax
End of assembler dump.
(gdb) info registers
eax            0x309               777
ecx            0x0                 0
edx            0x0                 0
ebx            0x0                 0
esp            0xffffd3d0          0xffffd3d0
ebp            0x0                 0x0
esi            0x0                 0
edi            0x0                 0
eip            0x8049006           0x8049006 <mov_immediate_data_between_registers_and_memory+5>
eflags         0x202               [ IF ]
cs             0x23                35
ss             0x2b                43
ds             0x2b                43
es             0x2b                43
fs             0x0                 0
gs             0x0                 0
(gdb) x/xw 0x804a000
0x804a000:      0x0000000a
(gdb) stepi
0x0804900b in exit ()
(gdb) x/xw 0x804a000
0x804a000:      0x00000309
(gdb)
```

## Hacking

Mục tiêu, dùng gdb để thay đổi giá trị của memory.

```conf
(gdb) set {int}0x804a000=1337
(gdb) x/xw 0x804a000
0x804a000:      0x00000539
(gdb) x/dw 0x804a000
0x804a000:      1337
(gdb)
```

