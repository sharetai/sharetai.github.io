---
layout: default
title: Thanh ghi EIP
nav_order: 3
parent: RE
---

# Extended Instruction Pointer Register
{: .no_toc }

Thanh ghi con trỏ lệnh
{: .fs-6 .fw-300 }

_Nguồn tham khảo: [https://0xinfection.github.io/reversing/](https://0xinfection.github.io/reversing/)_

---


Thanh ghi con trỏ lệnh được gọi là thanh ghi EIP đơn giản là thanh ghi quan trọng nhất sẽ xử lý trong bất kỳ kỹ thuật đảo ngược nào. EIP theo dõi mã lệnh tiếp theo để thực thi. EIP trỏ tới lệnh tiếp theo để thực thi. Nếu thay đổi con trỏ đó để chuyển sang vùng khác trong mã, ta có toàn quyền kiểm soát chương trình đó.

Ví dụ một chương trình Hello World. Điều cần lưu ý ở đây là có một hàm tên là unreachableFunction mà hàm chính không bao giờ gọi. Nếu ta có thể kiểm soát thanh ghi EIP, ta có thể hack chương trình này để thực thi mã đó!

```c
#include <stdio.h>
#include <stdlib.h>

void unreachableFunction()
{
    printf("Pwned!\n");
    exit(0);
}

int main() {
    printf("Hello World!\n");
    return 0;
}
```

`gcc -m32 -ggdb -o eipExample eipExample.c` // Biên dịch chương trình <br>
`./eipExample` // Chạy chương trình

```conf
┌──(root㉿kali)-[~/box]
└─# gcc -m32 -ggdb -o eipExample eipExample.c

┌──(root㉿kali)-[~/box]
└─# ./eipExample
Hello World!
```

`gdb eipExample` // Gỡ lỗi chương trình <br>
`set disassembly-flavor intel` // Chuyển sang cú pháp intel <br>
`break main` // Đặt break point <br>
`run` // Chạy chương trình, nếu gặp break point sẽ dừng <br>
`continue` // Chạy tiếp chương trình <br>
`disassemble` // Tháo rời mã

```conf
(gdb) set disassembly-flavor intel
(gdb) break main
Breakpoint 1 at 0x11e4: file eipExample.c, line 11.
(gdb) run
Starting program: /root/box/eipExample
[Thread debugging using libthread_db enabled]
Using host libthread_db library "/lib/x86_64-linux-gnu/libthread_db.so.1".

Breakpoint 1, main () at eipExample.c:11
11          printf("Hello World!\n");
(gdb) disassemble
Dump of assembler code for function main:
   0x565561cb <+0>:     lea    ecx,[esp+0x4]
   0x565561cf <+4>:     and    esp,0xfffffff0
   0x565561d2 <+7>:     push   DWORD PTR [ecx-0x4]
   0x565561d5 <+10>:    push   ebp
   0x565561d6 <+11>:    mov    ebp,esp
   0x565561d8 <+13>:    push   ebx
   0x565561d9 <+14>:    push   ecx
   0x565561da <+15>:    call   0x56556207 <__x86.get_pc_thunk.ax>
   0x565561df <+20>:    add    eax,0x2e15
=> 0x565561e4 <+25>:    sub    esp,0xc
   0x565561e7 <+28>:    lea    edx,[eax-0x1fe5]
   0x565561ed <+34>:    push   edx
   0x565561ee <+35>:    mov    ebx,eax
   0x565561f0 <+37>:    call   0x56556040 <puts@plt>
   0x565561f5 <+42>:    add    esp,0x10
   0x565561f8 <+45>:    mov    eax,0x0
   0x565561fd <+50>:    lea    esp,[ebp-0x8]
   0x56556200 <+53>:    pop    ecx
   0x56556201 <+54>:    pop    ebx
   0x56556202 <+55>:    pop    ebp
   0x56556203 <+56>:    lea    esp,[ecx-0x4]
   0x56556206 <+59>:    ret
End of assembler dump.
(gdb) continue
Continuing.
Hello World!
[Inferior 1 (process 2499) exited normally]
```

Chạy lại chương trình và kiểm tra xem EIP đang trỏ đến đâu. <br>
`x $eip` // Xem thanh ghi eip <br>
`disassemble unreachableFunction` // Thao gỡ hàm unreachableFunction <br>
`set $eip = 0x5655619d` // Đặt eip thành địa chỉ bắt đầu của hàm unreachableFunction

```conf
(gdb) run
Starting program: /root/box/eipExample
[Thread debugging using libthread_db enabled]
Using host libthread_db library "/lib/x86_64-linux-gnu/libthread_db.so.1".

Breakpoint 1, main () at eipExample.c:11
11          printf("Hello World!\n");
(gdb) x $eip
0x565561e4 <main+25>:   0x8d0cec83
(gdb) disassemble unreachableFunction
Dump of assembler code for function unreachableFunction:
   0x5655619d <+0>:     push   ebp
   0x5655619e <+1>:     mov    ebp,esp
   0x565561a0 <+3>:     push   ebx
   0x565561a1 <+4>:     sub    esp,0x4
   0x565561a4 <+7>:     call   0x565560a0 <__x86.get_pc_thunk.bx>
   0x565561a9 <+12>:    add    ebx,0x2e4b
   0x565561af <+18>:    sub    esp,0xc
   0x565561b2 <+21>:    lea    eax,[ebx-0x1fec]
   0x565561b8 <+27>:    push   eax
   0x565561b9 <+28>:    call   0x56556040 <puts@plt>
   0x565561be <+33>:    add    esp,0x10
   0x565561c1 <+36>:    sub    esp,0xc
   0x565561c4 <+39>:    push   0x0
   0x565561c6 <+41>:    call   0x56556050 <exit@plt>
End of assembler dump.
(gdb) set $eip = 0x5655619d
(gdb) x $eip
0x5655619d <unreachableFunction>:       0x53e58955
(gdb) continue
Continuing.
Pwned!
[Inferior 1 (process 2502) exited normally]
```