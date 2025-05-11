---
layout: default
title: ASM Program 2 [Moving Data Between Registers]
nav_order: 7
parent: RE
---

# ASM Program 2 [Moving Data Between Registers]
{: .no_toc }

ASM Chương trình 2 [Di chuyển dữ liệu giữa các thanh ghi]
{: .fs-6 .fw-300 }

_Nguồn tham khảo: [https://0xinfection.github.io/reversing/](https://0xinfection.github.io/reversing/)_

---

## TABLE OF CONTENTS
{: .no_toc .text-delta }

1. TOC
{:toc}

---

## Programming

Chương trình bên dưới thực hiện sao chép dữ liệu từ thanh ghi `edx` sang thanh ghi `eax`.

__moving_data_between_registers.asm__

{% capture code %}
{% highlight nasm linenos %}
;moving_data_between_registers: mov data between registers

section .data                        ;Data segment
section .text                        ;Code Segment
    global _start

_start:                              ;User prompt
    nop                              ;used for debugging purposes
    mov edx, 22

mov_data_between_registers:
    mov eax, edx                     ;mov the value in EDX into EAX

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
nasm -f elf32 moving_data_between_registers.asm
ld -m elf_i386 -o moving_data_between_registers moving_data_between_registers.o
```

## Debugging

__nop__ (no operation) dùng với mục đích để debug breakpoint. Không quan trọng.

```conf
┌──(root㉿kali)-[~/box]
└─# gdb -q moving_data_between_registers
Reading symbols from moving_data_between_registers...
(No debugging symbols found in moving_data_between_registers)
(gdb) b _start
Breakpoint 1 at 0x8049000
(gdb) run
Starting program: /root/box/moving_data_between_registers

Breakpoint 1, 0x08049000 in _start ()
(gdb) disassemble /r
Dump of assembler code for function _start:
=> 0x08049000 <+0>:     90                      nop
   0x08049001 <+1>:     ba 16 00 00 00          mov    edx,0x16
End of assembler dump.
(gdb) stepi
0x08049001 in _start ()
(gdb) stepi
0x08049006 in mov_data_between_registers ()
(gdb) disassemble /r
Dump of assembler code for function mov_data_between_registers:
=> 0x08049006 <+0>:     89 d0                   mov    eax,edx
End of assembler dump.
(gdb) info registers
eax            0x0                 0
ecx            0x0                 0
edx            0x16                22
ebx            0x0                 0
esp            0xffffd3f0          0xffffd3f0
ebp            0x0                 0x0
esi            0x0                 0
edi            0x0                 0
eip            0x8049006           0x8049006 <mov_data_between_registers>
eflags         0x202               [ IF ]
cs             0x23                35
ss             0x2b                43
ds             0x2b                43
es             0x2b                43
fs             0x0                 0
gs             0x0                 0
(gdb) stepi
0x08049008 in exit ()
(gdb) disassemble /r
Dump of assembler code for function exit:
=> 0x08049008 <+0>:     b8 01 00 00 00          mov    eax,0x1
   0x0804900d <+5>:     bb 00 00 00 00          mov    ebx,0x0
   0x08049012 <+10>:    cd 80                   int    0x80
End of assembler dump.
(gdb) info registers
eax            0x16                22
ecx            0x0                 0
edx            0x16                22
ebx            0x0                 0
esp            0xffffd3f0          0xffffd3f0
ebp            0x0                 0x0
esi            0x0                 0
edi            0x0                 0
eip            0x8049008           0x8049008 <exit>
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

Mục tiêu, dùng gdb để thay đổi giá trị của thanh ghi `edx` trước khi sao chép qua `eax`.

```conf
(gdb) disassemble /r
Dump of assembler code for function _start:
=> 0x08049000 <+0>:     90                      nop
   0x08049001 <+1>:     ba 16 00 00 00          mov    edx,0x16
End of assembler dump.
(gdb) stepi
0x08049001 in _start ()
(gdb) stepi
0x08049006 in mov_data_between_registers ()
(gdb) disassemble /r
Dump of assembler code for function mov_data_between_registers:
=> 0x08049006 <+0>:     89 d0                   mov    eax,edx
End of assembler dump.
(gdb) info registers
eax            0x0                 0
ecx            0x0                 0
edx            0x16                22
ebx            0x0                 0
esp            0xffffd3f0          0xffffd3f0
ebp            0x0                 0x0
esi            0x0                 0
edi            0x0                 0
eip            0x8049006           0x8049006 <mov_data_between_registers>
eflags         0x202               [ IF ]
cs             0x23                35
ss             0x2b                43
ds             0x2b                43
es             0x2b                43
fs             0x0                 0
gs             0x0                 0
(gdb) set $edx=25
(gdb) stepi
0x08049008 in exit ()
(gdb) disassemble /r
Dump of assembler code for function exit:
=> 0x08049008 <+0>:     b8 01 00 00 00          mov    eax,0x1
   0x0804900d <+5>:     bb 00 00 00 00          mov    ebx,0x0
   0x08049012 <+10>:    cd 80                   int    0x80
End of assembler dump.
(gdb) info registers
eax            0x19                25
ecx            0x0                 0
edx            0x19                25
ebx            0x0                 0
esp            0xffffd3f0          0xffffd3f0
ebp            0x0                 0x0
esi            0x0                 0
edi            0x0                 0
eip            0x8049008           0x8049008 <exit>
eflags         0x202               [ IF ]
cs             0x23                35
ss             0x2b                43
ds             0x2b                43
es             0x2b                43
fs             0x0                 0
gs             0x0                 0
(gdb)
```

