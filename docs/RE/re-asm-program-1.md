---
layout: default
title: ASM Program 1 [Moving Immediate Data]
nav_order: 6
parent: RE
---

# ASM Program 1 [Moving Immediate Data]
{: .no_toc }

ASM Chương trình 1 [Di chuyển dữ liệu tức thời]
{: .fs-6 .fw-300 }

_Nguồn tham khảo: [https://0xinfection.github.io/reversing/](https://0xinfection.github.io/reversing/)_

---

## TABLE OF CONTENTS
{: .no_toc .text-delta }

1. TOC
{:toc}

---

Ta sẽ tạo các chương trình lắp ráp 32 bit vì hầu hết phần mềm độc hại được viết ở chế độ 32 bit nhằm tấn công số lượng hệ thống tối đa có thể. Hãy nhớ rằng mặc dù hầu hết chúng ta TẤT CẢ đều có hệ điều hành 64 bit nhưng các chương trình 32 bit vẫn có thể chạy trên chúng.

Mỗi chương trình hợp ngữ được chia thành ba phần:

1) __Data Section__: Phần này được sử dụng để khai báo dữ liệu hoặc hằng số khởi tạo vì dữ liệu này không bao giờ thay đổi khi chạy. Ta có thể khai báo các giá trị không đổi, kích thước bộ đệm, tên tệp, v.v.

2) __BSS Section__: Phần này được sử dụng để khai báo dữ liệu hoặc biến chưa được khởi tạo.

3) __Text Section__: Phần này được sử dụng cho các phần mã thực tế vì nó bắt đầu bằng `global _start` để cho kernel biết nơi bắt đầu thực thi.

## Programming

Chương trình đầu tiên sẽ trình bày cách di chuyển dữ liệu tức thời vào một thanh ghi và dữ liệu tức thời vào bộ nhớ.

__moving_immediate_data.asm__

{% capture code %}
{% highlight nasm linenos %}
;moving_immediate_data: mov immediate data between registers & memory

section .data                        ;Data segment
section .bss                         ;Uninitialized data
    buffer resb 1
section .text                        ;Code Segment
    global _start

_start:                              ;User prompt
    nop                              ;used for debugging purposes

moving_immediate_data_to_register:
    mov eax, 100                     ;mov 100 into the EAX register
    mov byte[buffer], 0x50           ;mov 0x50 into buffer memory location

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
nasm -f elf32 moving_immediate_data.asm
ld -m elf_i386 -o moving_immediate_data moving_immediate_data.o
```

## Debugging

__nop__ (no operation) dùng với mục đích để debug breakpoint. Không quan trọng.

```conf
┌──(root㉿kali)-[~/box]
└─# gdb -q moving_immediate_data
Reading symbols from moving_immediate_data...
(No debugging symbols found in moving_immediate_data)
(gdb) break _start
Breakpoint 1 at 0x8049000
(gdb) run
Starting program: /root/box/moving_immediate_data

Breakpoint 1, 0x08049000 in _start ()
(gdb) disassemble /r
Dump of assembler code for function _start:
=> 0x08049000 <+0>:     90                      nop
End of assembler dump.
(gdb)
```

Thực hiện đưa `100` vào thanh ghi `eax`, quan sát trạng thái thanh ghi.

```conf
(gdb) stepi
0x08049001 in moving_immediate_data_to_register ()
(gdb) disassemble /r
Dump of assembler code for function moving_immediate_data_to_register:
=> 0x08049001 <+0>:     b8 64 00 00 00          mov    eax,0x64
   0x08049006 <+5>:     c6 05 00 a0 04 08 50    mov    BYTE PTR ds:0x804a000,0x50
End of assembler dump.
(gdb) info registers
eax            0x0                 0
ecx            0x0                 0
edx            0x0                 0
ebx            0x0                 0
esp            0xffffd400          0xffffd400
ebp            0x0                 0x0
esi            0x0                 0
edi            0x0                 0
eip            0x8049001           0x8049001 <moving_immediate_data_to_register>
eflags         0x202               [ IF ]
cs             0x23                35
ss             0x2b                43
ds             0x2b                43
es             0x2b                43
fs             0x0                 0
gs             0x0                 0
(gdb) stepi
0x08049006 in moving_immediate_data_to_register ()
(gdb) disassemble /r
Dump of assembler code for function moving_immediate_data_to_register:
   0x08049001 <+0>:     b8 64 00 00 00          mov    eax,0x64
=> 0x08049006 <+5>:     c6 05 00 a0 04 08 50    mov    BYTE PTR ds:0x804a000,0x50
End of assembler dump.
(gdb) info registers
eax            0x64                100
ecx            0x0                 0
edx            0x0                 0
ebx            0x0                 0
esp            0xffffd400          0xffffd400
ebp            0x0                 0x0
esi            0x0                 0
edi            0x0                 0
eip            0x8049006           0x8049006 <moving_immediate_data_to_register+5>
eflags         0x202               [ IF ]
cs             0x23                35
ss             0x2b                43
ds             0x2b                43
es             0x2b                43
fs             0x0                 0
gs             0x0                 0
(gdb)
```

Thực hiện đưa `0x50` vào `buffer`. Đối với dữ liệu non-register, dùng "x" command để xem.

```conf
(gdb) disassemble /r
Dump of assembler code for function moving_immediate_data_to_register:
   0x08049001 <+0>:     b8 64 00 00 00          mov    eax,0x64
=> 0x08049006 <+5>:     c6 05 00 a0 04 08 50    mov    BYTE PTR ds:0x804a000,0x50
End of assembler dump.
(gdb) stepi
0x0804900d in exit ()
(gdb) disassemble /r
Dump of assembler code for function exit:
=> 0x0804900d <+0>:     b8 01 00 00 00          mov    eax,0x1
   0x08049012 <+5>:     bb 00 00 00 00          mov    ebx,0x0
   0x08049017 <+10>:    cd 80                   int    0x80
End of assembler dump.
(gdb) x/1w 0x804a000
0x804a000:      0x00000050
(gdb) x/4b 0x804a000
0x804a000:      0x50    0x00    0x00    0x00
(gdb)
```

## Hacking

Mục tiêu, dùng gdb để thay đổi giá trị của thanh ghi eax.

```conf
(gdb) set $eax=120
(gdb) info registers
eax            0x78                120
ecx            0x0                 0
edx            0x0                 0
ebx            0x0                 0
esp            0xffffd400          0xffffd400
ebp            0x0                 0x0
esi            0x0                 0
edi            0x0                 0
eip            0x8049006           0x8049006 <moving_immediate_data_to_register+5>
eflags         0x202               [ IF ]
cs             0x23                35
ss             0x2b                43
ds             0x2b                43
es             0x2b                43
fs             0x0                 0
gs             0x0                 0
(gdb)
```

