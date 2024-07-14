---
layout: default
title: Cách biên dịch chương trình
nav_order: 5
parent: RE
---

# Cách biên dịch chương trình
{: .no_toc }

How To Compile A Program
{: .fs-6 .fw-300 }

_Nguồn tham khảo: [https://0xinfection.github.io/reversing/](https://0xinfection.github.io/reversing/)_

---

Xem lại chương trình C bên dưới và tìm hiểu sâu hơn cách ta biến mã nguồn đó thành một tệp thực thi.

```c
int main() {
    return 0;
}
```

Để biên dịch chương trình này, ta chỉ cần gõ:

```
gcc -m32 -ggdb -fno-pie -o exit exit.c
```

Bước duy nhất này sẽ tạo __exit.o__ là tệp đối tượng nhị phân và __exit__ là tệp thực thi nhị phân.

Nếu ta muốn chuyển đổi mã nguồn C này thành Assembly, ta cần sử dụng trình biên dịch GNU theo cách dưới đây. Hãy bắt đầu bằng cách chạy lệnh dưới đây trong terminal:

```
gcc -S -m32 -masm=intel -fno-pie -O0 exit.c
```

```
┌──(root㉿kali)-[~/box]
└─# gcc --help -v | more
...
  -S                       Compile only; do not assemble or link.

  -m32                        Generate 32bit i386 code.

  -masm=                      Use given assembler dialect.
  Known assembler dialects (for use with the -masm= option):
    att intel

  -O                          Optimize output file
...
```

Key `-S` sẽ tạo mã nguồn AT&T Syntax Assembly tương đương. `-m32` sẽ tạo tệp thực thi 32 bit và `-O0` sẽ cho trình biên dịch biết mức độ tối ưu hóa cần sử dụng khi biên dịch nhị phân. Đó là chữ `O` viết hoa và số `0`. Số `0` trong trường hợp đó có nghĩa là không tối ưu hóa, nghĩa là nó nằm ở tập lệnh dễ đọc nhất của con người. Nếu thay thế `1`, `2` hoặc `3` thì mức độ tối ưu hóa sẽ tăng lên khi giá trị tăng lên.

```conf
┌──(root㉿kali)-[~/box]
└─# cat exit.s
        .file   "exit.c"
        .intel_syntax noprefix
        .text
        .globl  main
        .type   main, @function
main:
.LFB0:
        .cfi_startproc
        push    ebp
        .cfi_def_cfa_offset 8
        .cfi_offset 5, -8
        mov     ebp, esp
        .cfi_def_cfa_register 5
        mov     eax, 0
        pop     ebp
        .cfi_restore 5
        .cfi_def_cfa 4, 4
        ret
        .cfi_endproc
.LFE0:
        .size   main, .-main
        .ident  "GCC: (Debian 13.2.0-4) 13.2.0"
        .section        .note.GNU-stack,"",@progbits
```

Bước này ở trên tạo ra __exit.s__ là mã nguồn Assembly.

Sau đó, ta cần biên dịch mã nguồn Assembly thành một tệp đối tượng nhị phân để tạo ra tệp __exit.o__.

```
gcc -m32 -c exit.s -o exit.o
```

Cuối cùng, ta cần sử dụng một trình liên kết để tạo mã thực thi nhị phân thực tế từ tệp đối tượng nhị phân, mã này sẽ tạo ra một tệp thực thi được gọi là __exit__. 

```
gcc -m32 exit.o -o exit
```

Hãy kiểm tra mã trong trình gỡ lỗi. Hãy khởi động GDB, trình gỡ lỗi GNU.

```conf
┌──(root㉿kali)-[~/box]
└─# gdb -q exit
Reading symbols from exit...
(No debugging symbols found in exit)
(gdb) b main
Breakpoint 1 at 0x1180
(gdb) run
Starting program: /root/box/exit
[Thread debugging using libthread_db enabled]
Using host libthread_db library "/lib/x86_64-linux-gnu/libthread_db.so.1".

Breakpoint 1, 0x56556180 in main ()
(gdb) disas
Dump of assembler code for function main:
   0x5655617d <+0>:     push   ebp
   0x5655617e <+1>:     mov    ebp,esp
=> 0x56556180 <+3>:     mov    eax,0x0
   0x56556185 <+8>:     pop    ebp
   0x56556186 <+9>:     ret
End of assembler dump.
(gdb)
```

Nếu ta muốn tạo một chương trình Assembly thuần túy thực hiện điều tương tự ở trên, ta thực hiện như bên dưới:

```conf
┌──(root㉿kali)-[~/box]
└─# cat exit_asm.s
section .data          ;Data segment
section .bss           ;Uninitialized data
section .text          ;Code Segment
   global _start

_start:                ;User prompt
   ; Exit code
   mov eax, 1          ;sys_exit
   mov ebx, 0          ;display 0 if normal status
   int 80h             ;call sys_exit


┌──(root㉿kali)-[~/box]
└─# nasm -f elf -o exit_asm.o exit_asm.s

┌──(root㉿kali)-[~/box]
└─# ld -m elf_i386 -s -o exit_asm exit_asm.o

┌──(root㉿kali)-[~/box]
└─# ./exit_asm
```
