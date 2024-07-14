---
layout: default
title: ASM Program 6 [CMOV Instructions]
nav_order: 11
parent: RE
---

# ASM Program 6 [CMOV Instructions]
{: .no_toc }

ASM Chương trình 6 [Chỉ dẫn Di chuyển có điều kiện]
{: .fs-6 .fw-300 }

_Nguồn tham khảo: [https://0xinfection.github.io/reversing/](https://0xinfection.github.io/reversing/)_

---

## Table of contents
{: .no_toc .text-delta }

1. TOC
{:toc}

---

## Programming

Chương trình bên dưới thực hiện tìm giá trị nhỏ nhất trong mảng.

__cmov_instructions.asm__

{% capture code %}
{% highlight nasm linenos %}
;cmov_instructions: conditional move instruction

section .data
   result db "The smallest value is "
   lr db ".", 0xa
   constants dd 3, 9, 2, 7

section .bss                           ;Uninitialized data
   answer resb 1
   
section .text                          ;Code Segment
   global _start

_start:                                ;User prompt
   nop                                 ;used for debugging purposes

   mov ebx, [constants]                ;mov array values into ebx
   mov edi, 1                          ;load 2nd index constants label

find_smallest_value:

   mov eax, dword[edi*4+constants]     ;mov above value 4 bytes from constants (like constants[1->3])
   cmp eax, ebx                        ;compare ebx to eax (like eax - ebx without stored)
   cmovb ebx, eax                      ;compare below eax to ebx [Carry Flag = 1]
   inc edi                             ;increment edi to move through array (like i++)
   cmp edi, 4                          ;check where we are in array (like if i<4)
   jne find_smallest_value             ;jne to begining of loop
   add ebx, 0x30                       ;convert int to ascii
   mov [answer], ebx                   ;mov new value of ebx to answer label

   ;print "The smallest value is "
   mov eax, 4                          ;sys_write system call
   mov ebx, 1                          ;stdout
   mov ecx, result                     ;mov result address into ecx
   mov edx, 22                         ;mov 22 bytes (len of result) into edx
   int 80h                             ;call sys_write

   ;print answer
   mov eax, 4                          ;sys_write system call
   mov ebx, 1                          ;stdout
   mov ecx, answer                     ;mov answer address into ecx
   mov edx, 1                          ;mov 1 byte into edx
   int 80h                             ;call sys_write

   ;print ".\n"
   mov eax, 4                          ;sys_write system call
   mov ebx, 1                          ;stdout
   mov ecx, lr                         ;mov lr address into ecx
   mov edx, 2                          ;mov 1 bytes (len of lr) into edx
   int 80h                             ;call sys_write

exit:
   mov eax, 1                          ;sys_exit system call
   mov ebx, 0                          ;exit code 0 successful execution
   int 80h                             ;call sys_exit
{% endhighlight %}
{% endcapture %}
{% include fix_linenos.html code=code %}
{% assign code = nil %}

Biên dịch chương trình:

```
nasm -f elf32 cmov_instructions.asm
ld -m elf_i386 -o cmov_instructions cmov_instructions.o
```

## Debugging

__nop__ (no operation) dùng với mục đích để debug breakpoint. Không quan trọng.

```conf
┌──(root㉿kali)-[~/box]
└─# gdb -q cmov_instructions
Reading symbols from cmov_instructions...
(No debugging symbols found in cmov_instructions)
(gdb) b _start
Breakpoint 1 at 0x8049000
(gdb) run
Starting program: /root/box/cmov_instructions

Breakpoint 1, 0x08049000 in _start ()
(gdb) disassemble /r _start,+116
Dump of assembler code from 0x8049000 to 0x8049074:
=> 0x08049000 <_start+0>:       90                      nop
   0x08049001 <_start+1>:       8b 1d 18 a0 04 08       mov    ebx,DWORD PTR ds:0x804a018
   0x08049007 <_start+7>:       bf 01 00 00 00          mov    edi,0x1
   0x0804900c <find_smallest_value+0>:  8b 04 bd 18 a0 04 08    mov    eax,DWORD PTR [edi*4+0x804a018]
   0x08049013 <find_smallest_value+7>:  39 d8                   cmp    eax,ebx
   0x08049015 <find_smallest_value+9>:  0f 42 d8                cmovb  ebx,eax
   0x08049018 <find_smallest_value+12>: 47                      inc    edi
   0x08049019 <find_smallest_value+13>: 83 ff 04                cmp    edi,0x4
   0x0804901c <find_smallest_value+16>: 75 ee                   jne    0x804900c <find_smallest_value>
   0x0804901e <find_smallest_value+18>: 83 c3 30                add    ebx,0x30
   0x08049021 <find_smallest_value+21>: 89 1d 28 a0 04 08       mov    DWORD PTR ds:0x804a028,ebx
   0x08049027 <find_smallest_value+27>: b8 04 00 00 00          mov    eax,0x4
   0x0804902c <find_smallest_value+32>: bb 01 00 00 00          mov    ebx,0x1
   0x08049031 <find_smallest_value+37>: b9 00 a0 04 08          mov    ecx,0x804a000
   0x08049036 <find_smallest_value+42>: ba 16 00 00 00          mov    edx,0x16
   0x0804903b <find_smallest_value+47>: cd 80                   int    0x80
   0x0804903d <find_smallest_value+49>: b8 04 00 00 00          mov    eax,0x4
   0x08049042 <find_smallest_value+54>: bb 01 00 00 00          mov    ebx,0x1
   0x08049047 <find_smallest_value+59>: b9 28 a0 04 08          mov    ecx,0x804a028
   0x0804904c <find_smallest_value+64>: ba 01 00 00 00          mov    edx,0x1
   0x08049051 <find_smallest_value+69>: cd 80                   int    0x80
   0x08049053 <find_smallest_value+71>: b8 04 00 00 00          mov    eax,0x4
   0x08049058 <find_smallest_value+76>: bb 01 00 00 00          mov    ebx,0x1
   0x0804905d <find_smallest_value+81>: b9 16 a0 04 08          mov    ecx,0x804a016
   0x08049062 <find_smallest_value+86>: ba 02 00 00 00          mov    edx,0x2
   0x08049067 <find_smallest_value+91>: cd 80                   int    0x80
   0x08049069 <exit+0>: b8 01 00 00 00          mov    eax,0x1
   0x0804906e <exit+5>: bb 00 00 00 00          mov    ebx,0x0
   0x08049073 <exit+10>:        cd 80                   int    0x80
End of assembler dump.
```

Đặt breakpoint để skip qua đoạn tìm giá trị nhỏ nhất. Kiểm tra `answer` chứa giá trị `32` thay vì `2` do đã được `+0x30` để chuyển từ kiểu `int` thành `ascii` in ra màn hình.

```conf
(gdb) b *find_smallest_value+27
Breakpoint 2 at 0x8049027
(gdb) continue
Continuing.

Breakpoint 2, 0x08049027 in find_smallest_value ()
(gdb) disassemble /r _start,+116
Dump of assembler code from 0x8049000 to 0x8049074:
   0x08049000 <_start+0>:       90                      nop
   0x08049001 <_start+1>:       8b 1d 18 a0 04 08       mov    ebx,DWORD PTR ds:0x804a018
   0x08049007 <_start+7>:       bf 01 00 00 00          mov    edi,0x1
   0x0804900c <find_smallest_value+0>:  8b 04 bd 18 a0 04 08    mov    eax,DWORD PTR [edi*4+0x804a018]
   0x08049013 <find_smallest_value+7>:  39 d8                   cmp    eax,ebx
   0x08049015 <find_smallest_value+9>:  0f 42 d8                cmovb  ebx,eax
   0x08049018 <find_smallest_value+12>: 47                      inc    edi
   0x08049019 <find_smallest_value+13>: 83 ff 04                cmp    edi,0x4
   0x0804901c <find_smallest_value+16>: 75 ee                   jne    0x804900c <find_smallest_value>
   0x0804901e <find_smallest_value+18>: 83 c3 30                add    ebx,0x30
   0x08049021 <find_smallest_value+21>: 89 1d 28 a0 04 08       mov    DWORD PTR ds:0x804a028,ebx
=> 0x08049027 <find_smallest_value+27>: b8 04 00 00 00          mov    eax,0x4
   0x0804902c <find_smallest_value+32>: bb 01 00 00 00          mov    ebx,0x1
   0x08049031 <find_smallest_value+37>: b9 00 a0 04 08          mov    ecx,0x804a000
   0x08049036 <find_smallest_value+42>: ba 16 00 00 00          mov    edx,0x16
   0x0804903b <find_smallest_value+47>: cd 80                   int    0x80
   0x0804903d <find_smallest_value+49>: b8 04 00 00 00          mov    eax,0x4
   0x08049042 <find_smallest_value+54>: bb 01 00 00 00          mov    ebx,0x1
   0x08049047 <find_smallest_value+59>: b9 28 a0 04 08          mov    ecx,0x804a028
   0x0804904c <find_smallest_value+64>: ba 01 00 00 00          mov    edx,0x1
   0x08049051 <find_smallest_value+69>: cd 80                   int    0x80
   0x08049053 <find_smallest_value+71>: b8 04 00 00 00          mov    eax,0x4
   0x08049058 <find_smallest_value+76>: bb 01 00 00 00          mov    ebx,0x1
   0x0804905d <find_smallest_value+81>: b9 16 a0 04 08          mov    ecx,0x804a016
   0x08049062 <find_smallest_value+86>: ba 02 00 00 00          mov    edx,0x2
   0x08049067 <find_smallest_value+91>: cd 80                   int    0x80
   0x08049069 <exit+0>: b8 01 00 00 00          mov    eax,0x1
   0x0804906e <exit+5>: bb 00 00 00 00          mov    ebx,0x0
   0x08049073 <exit+10>:        cd 80                   int    0x80
End of assembler dump.
(gdb) x/1xw 0x804a028
0x804a028:      0x00000032
(gdb) x/1cw 0x804a028
0x804a028:      50 '2'
```

## Hacking

Mục tiêu, dùng gdb để trỏ `eip` ra gia đoạn sau của hàm `find_smallest_value`, để bỏ qua tìm kiếm giá trị nhỏ nhất.

```conf
┌──(root㉿kali)-[~/box]
└─# gdb -q cmov_instructions
Reading symbols from cmov_instructions...
(No debugging symbols found in cmov_instructions)
(gdb) b *find_smallest_value
Breakpoint 1 at 0x804900c
(gdb) run
Starting program: /root/box/cmov_instructions

Breakpoint 1, 0x0804900c in find_smallest_value ()
(gdb) disassemble /r _start,+114
Dump of assembler code from 0x8049000 to 0x8049072:
   0x08049000 <_start+0>:       90                      nop
   0x08049001 <_start+1>:       8b 1d 18 a0 04 08       mov    ebx,DWORD PTR ds:0x804a018
   0x08049007 <_start+7>:       bf 01 00 00 00          mov    edi,0x1
=> 0x0804900c <find_smallest_value+0>:  8b 04 bd 18 a0 04 08    mov    eax,DWORD PTR [edi*4+0x804a018]
   0x08049013 <find_smallest_value+7>:  39 d8                   cmp    eax,ebx
   0x08049015 <find_smallest_value+9>:  0f 42 d8                cmovb  ebx,eax
   0x08049018 <find_smallest_value+12>: 47                      inc    edi
   0x08049019 <find_smallest_value+13>: 83 ff 04                cmp    edi,0x4
   0x0804901c <find_smallest_value+16>: 75 ee                   jne    0x804900c <find_smallest_value>
   0x0804901e <find_smallest_value+18>: 83 c3 30                add    ebx,0x30
   0x08049021 <find_smallest_value+21>: 89 1d 28 a0 04 08       mov    DWORD PTR ds:0x804a028,ebx
   0x08049027 <find_smallest_value+27>: b8 04 00 00 00          mov    eax,0x4
   0x0804902c <find_smallest_value+32>: bb 01 00 00 00          mov    ebx,0x1
   0x08049031 <find_smallest_value+37>: b9 00 a0 04 08          mov    ecx,0x804a000
   0x08049036 <find_smallest_value+42>: ba 16 00 00 00          mov    edx,0x16
   0x0804903b <find_smallest_value+47>: cd 80                   int    0x80
   0x0804903d <find_smallest_value+49>: b8 04 00 00 00          mov    eax,0x4
   0x08049042 <find_smallest_value+54>: bb 01 00 00 00          mov    ebx,0x1
   0x08049047 <find_smallest_value+59>: b9 28 a0 04 08          mov    ecx,0x804a028
   0x0804904c <find_smallest_value+64>: ba 01 00 00 00          mov    edx,0x1
   0x08049051 <find_smallest_value+69>: cd 80                   int    0x80
   0x08049053 <find_smallest_value+71>: b8 04 00 00 00          mov    eax,0x4
   0x08049058 <find_smallest_value+76>: bb 01 00 00 00          mov    ebx,0x1
   0x0804905d <find_smallest_value+81>: b9 16 a0 04 08          mov    ecx,0x804a016
   0x08049062 <find_smallest_value+86>: ba 02 00 00 00          mov    edx,0x2
   0x08049067 <find_smallest_value+91>: cd 80                   int    0x80
   0x08049069 <exit+0>: b8 01 00 00 00          mov    eax,0x1
   0x0804906e <exit+5>: bb 00 00 00 00          mov    ebx,0x0
End of assembler dump.
(gdb) set $eip=*find_smallest_value+18
(gdb) continue
Continuing.
The smallest value is 3.
[Inferior 1 (process 1344707) exited normally]
```

