---
layout: default
title: ASM Program 5 [Indirect Addressing With Registers]
nav_order: 10
parent: RE
---

# ASM Program 5 [Indirect Addressing With Registers]
{: .no_toc }

ASM Chương trình 5 [Địa chỉ gián tiếp với các thanh ghi]
{: .fs-6 .fw-300 }

_Nguồn tham khảo: [https://0xinfection.github.io/reversing/](https://0xinfection.github.io/reversing/)_

---

## TABLE OF CONTENTS
{: .no_toc .text-delta }

1. TOC
{:toc}

---

## Programming

Chương trình bên dưới thực hiện các thao tác truy cập dữ liệu kiểu mảng.

__indirect_addressing_with_registers.asm__

{% capture code %}
{% highlight nasm linenos %}
;indirect_addressing_with_registers: accessing data in mem using pointers

section .data
    constants dd 5, 8, 17, 44, 50, 52, 60, 65, 70, 77, 80

section .text                        ;Code Segment
    global _start

_start:                              ;User prompt
    nop                              ;used for debugging purposes

indirect_addressing_with_registers:
    mov eax, [constants]             ;mov constants mem value into eax
    mov edi, constants               ;mov mem addr into edi
    mov dword[edi+0x4], 25           ;mov immediate value 4 bytes after edi ptr
    mov edi, 1                       ;load 2nd index constants label
    mov ebx, dword[edi*4+constants]  ;mov above value 4 bytes from constants

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
nasm -f elf32 indirect_addressing_with_registers.asm
ld -m elf_i386 -o indirect_addressing_with_registers indirect_addressing_with_registers.o
```

## Debugging

__nop__ (no operation) dùng với mục đích để debug breakpoint. Không quan trọng.

```conf
┌──(root㉿kali)-[~/box]
└─# gdb -q indirect_addressing_with_registers
┌──(root㉿kali)-[~/box]
└─# gdb -q indirect_addressing_with_registers
Reading symbols from indirect_addressing_with_registers...
(No debugging symbols found in indirect_addressing_with_registers)
(gdb) b _start
Breakpoint 1 at 0x8049000
(gdb) run
Starting program: /root/box/indirect_addressing_with_registers

Breakpoint 1, 0x08049000 in _start ()
(gdb) disassemble /r _start,+42
Dump of assembler code from 0x8049000 to 0x804902a:
=> 0x08049000 <_start+0>:       90                      nop
   0x08049001 <indirect_addressing_with_registers+0>:   a1 00 a0 04 08          mov    eax,ds:0x804a000
   0x08049006 <indirect_addressing_with_registers+5>:   bf 00 a0 04 08          mov    edi,0x804a000
   0x0804900b <indirect_addressing_with_registers+10>:  c7 47 04 19 00 00 00    mov    DWORD PTR [edi+0x4],0x19
   0x08049012 <indirect_addressing_with_registers+17>:  bf 01 00 00 00          mov    edi,0x1
   0x08049017 <indirect_addressing_with_registers+22>:  8b 1c bd 00 a0 04 08    mov    ebx,DWORD PTR [edi*4+0x804a000]
   0x0804901e <exit+0>: b8 01 00 00 00          mov    eax,0x1
   0x08049023 <exit+5>: bb 00 00 00 00          mov    ebx,0x0
   0x08049028 <exit+10>:        cd 80                   int    0x80
End of assembler dump.
(gdb) x/12xw 0x804a000
0x804a000:      0x00000005      0x00000008      0x00000011      0x0000002c
0x804a010:      0x00000032      0x00000034      0x0000003c      0x00000041
0x804a020:      0x00000046      0x0000004d      0x00000050      0x00000000
(gdb) x/12dw 0x804a000
0x804a000:      5       8       17      44
0x804a010:      50      52      60      65
0x804a020:      70      77      80      0
```

Thực hiện `stepi` 2 lần, di chuyển mảng `constants` vào `eax` và quan sát. 4 bytes đầu của mảng được sao chép vào thanh ghi `eax`.

```conf
(gdb) stepi
0x08049001 in indirect_addressing_with_registers ()
(gdb) stepi
0x08049006 in indirect_addressing_with_registers ()
(gdb) disassemble /r _start,+42
Dump of assembler code from 0x8049000 to 0x804902a:
   0x08049000 <_start+0>:       90                      nop
   0x08049001 <indirect_addressing_with_registers+0>:   a1 00 a0 04 08          mov    eax,ds:0x804a000
=> 0x08049006 <indirect_addressing_with_registers+5>:   bf 00 a0 04 08          mov    edi,0x804a000
   0x0804900b <indirect_addressing_with_registers+10>:  c7 47 04 19 00 00 00    mov    DWORD PTR [edi+0x4],0x19
   0x08049012 <indirect_addressing_with_registers+17>:  bf 01 00 00 00          mov    edi,0x1
   0x08049017 <indirect_addressing_with_registers+22>:  8b 1c bd 00 a0 04 08    mov    ebx,DWORD PTR [edi*4+0x804a000]
   0x0804901e <exit+0>: b8 01 00 00 00          mov    eax,0x1
   0x08049023 <exit+5>: bb 00 00 00 00          mov    ebx,0x0
   0x08049028 <exit+10>:        cd 80                   int    0x80
End of assembler dump.
(gdb) info registers eax
eax            0x5                 5
```

Thực hiện `stepi` 2 lần, sao chép địa chỉ của mảng `constants` vào thanh ghi `edi`, sau đó thay đổi phần tử thứ 2 của mảng `constants` từ `8` thành `25`.

```conf
(gdb) stepi
0x0804900b in indirect_addressing_with_registers ()
(gdb) stepi
0x08049012 in indirect_addressing_with_registers ()
(gdb) disassemble /r _start,+42
Dump of assembler code from 0x8049000 to 0x804902a:
   0x08049000 <_start+0>:       90                      nop
   0x08049001 <indirect_addressing_with_registers+0>:   a1 00 a0 04 08          mov    eax,ds:0x804a000
   0x08049006 <indirect_addressing_with_registers+5>:   bf 00 a0 04 08          mov    edi,0x804a000
   0x0804900b <indirect_addressing_with_registers+10>:  c7 47 04 19 00 00 00    mov    DWORD PTR [edi+0x4],0x19
=> 0x08049012 <indirect_addressing_with_registers+17>:  bf 01 00 00 00          mov    edi,0x1
   0x08049017 <indirect_addressing_with_registers+22>:  8b 1c bd 00 a0 04 08    mov    ebx,DWORD PTR [edi*4+0x804a000]
   0x0804901e <exit+0>: b8 01 00 00 00          mov    eax,0x1
   0x08049023 <exit+5>: bb 00 00 00 00          mov    ebx,0x0
   0x08049028 <exit+10>:        cd 80                   int    0x80
End of assembler dump.
(gdb) info registers edi
edi            0x804a000           134520832
(gdb) x/12xw 0x804a000
0x804a000:      0x00000005      0x00000019      0x00000011      0x0000002c
0x804a010:      0x00000032      0x00000034      0x0000003c      0x00000041
0x804a020:      0x00000046      0x0000004d      0x00000050      0x00000000
(gdb) x/12dw 0x804a000
0x804a000:      5       25      17      44
0x804a010:      50      52      60      65
0x804a020:      70      77      80      0
```

Thực hiện `stepi` 2 lần, sao chép 4 bytes thứ 2 của mảng `constants` vào thanh ghi `ebx`. Cú pháp `edi*4+constants` nghĩa là truy cập mảng từ phần tử 2 đến 4 bytes tiếp theo, nhớ rằng `mov edi, 1` đã set `edi` thành `1`. Có thể xem tương tự như `constants[1]`.

```conf
(gdb) stepi
0x08049017 in indirect_addressing_with_registers ()
(gdb) stepi
0x0804901e in exit ()
(gdb) disassemble /r _start,+42
Dump of assembler code from 0x8049000 to 0x804902a:
   0x08049000 <_start+0>:       90                      nop
   0x08049001 <indirect_addressing_with_registers+0>:   a1 00 a0 04 08          mov    eax,ds:0x804a000
   0x08049006 <indirect_addressing_with_registers+5>:   bf 00 a0 04 08          mov    edi,0x804a000
   0x0804900b <indirect_addressing_with_registers+10>:  c7 47 04 19 00 00 00    mov    DWORD PTR [edi+0x4],0x19
   0x08049012 <indirect_addressing_with_registers+17>:  bf 01 00 00 00          mov    edi,0x1
   0x08049017 <indirect_addressing_with_registers+22>:  8b 1c bd 00 a0 04 08    mov    ebx,DWORD PTR [edi*4+0x804a000]
=> 0x0804901e <exit+0>: b8 01 00 00 00          mov    eax,0x1
   0x08049023 <exit+5>: bb 00 00 00 00          mov    ebx,0x0
   0x08049028 <exit+10>:        cd 80                   int    0x80
End of assembler dump.
(gdb) x/12xw 0x804a000
0x804a000:      0x00000005      0x00000019      0x00000011      0x0000002c
0x804a010:      0x00000032      0x00000034      0x0000003c      0x00000041
0x804a020:      0x00000046      0x0000004d      0x00000050      0x00000000
(gdb) info registers ebx
ebx            0x19                25
```

## Hacking

Mục tiêu, dùng gdb để thay đổi phần tử thứ 3 trong mảng `constants`.

```conf
(gdb) x/12dw 0x804a000
0x804a000:      5       25      17      44
0x804a010:      50      52      60      65
0x804a020:      70      77      80      0
(gdb) x/1dw 0x804a008
0x804a008:      17
(gdb) set *0x804a008 = 66
(gdb) x/12dw 0x804a000
0x804a000:      5       25      66      44
0x804a010:      50      52      60      65
0x804a020:      70      77      80      0
```

