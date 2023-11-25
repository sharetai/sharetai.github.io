---
layout: default
title: NASM
nav_order: 12
parent: RE
---

# Netwide Assembler
{: .no_toc }

Netwide Assembler là một trình biên dịch và dịch ngược cho kiến ​​trúc Intel x86
{: .fs-6 .fw-300 }

_Nguồn tham khảo: [https://www.tutorialspoint.com/assembly_programming/](https://www.tutorialspoint.com/assembly_programming/)_

---

## Table of contents
{: .no_toc .text-delta }

1. TOC
{:toc}

---

Trang này sẽ trình bày ngoài phần code tham khảo từ tutorial, sẽ có thêm phần debug trực tiếp chương trình. Mục đích tạo ra góc nhìn rõ ràng hành vi của các thành phần trong bộ nhớ của một tiến trình đang chạy.

## Bố cục bộ nhớ của một tiến trình

```
 ______________________________ 
|                              | ← low memory
|          text (code)         |
|______________________________|
|                              |
|      data (initialized)      |
|______________________________|
|                              |
|      bss (uninitialized)     |
|______________________________|
|                              |
|             heap             |
|------------------------------|
|              ↓               |
|                              |
|                              | 
|              ↑               |
|------------------------------|
|            stack             |
|______________________________| ← high memory
```

## hello.asm

{% capture code %}
{% highlight nasm linenos %}
section	.text
   global _start  	;must be declared for linker (ld)
	
_start:	            	;tells linker entry point
   mov	edx,len     	;message length
   mov	ecx,msg    	;message to write
   mov	ebx,1    	;file descriptor (stdout)
   mov	eax,4     	;system call number (sys_write)
   int	0x80        	;call kernel
	
   mov	eax,1       	;system call number (sys_exit)
   int	0x80        	;call kernel

section	.data
msg db 'Hello, world!', 0xa  	;string to be printed
len equ $ - msg     		;length of the string
{% endhighlight %}
{% endcapture %}
{% include fix_linenos.html code=code %}
{% assign code = nil %}

Biên dịch chương trình:

```
nasm -f elf32 hello.asm
ld -m elf_i386 -o hello hello.o
```

Dùng __gef__ debug:

```conf
┌──(root㉿kali)-[~/box]
└─# gdb-gef -q hello
Reading symbols from hello...
(No debugging symbols found in hello)
Error while writing index for `/root/box/hello': No debugging symbols
GEF for linux ready, type `gef' to start, `gef config' to configure
89 commands loaded and 5 functions added for GDB 13.2 in 0.01ms using Python engine 3.11
gef➤  start
[+] Breaking at '0x8049000'
[ Legend: Modified register | Code | Heap | Stack | String ]
───────────────────────────────────────────────────────────────────────────────────────────────── registers ────
$eax   : 0x0
$ebx   : 0x0
$ecx   : 0x0
$edx   : 0x0
$esp   : 0xffffd430  →  0x00000001
$ebp   : 0x0
$esi   : 0x0
$edi   : 0x0
$eip   : 0x08049000  →  <_start+0> mov edx, 0xe
$eflags: [zero carry parity adjust sign trap INTERRUPT direction overflow resume virtualx86 identification]
$cs: 0x23 $ss: 0x2b $ds: 0x2b $es: 0x2b $fs: 0x00 $gs: 0x00
───────────────────────────────────────────────────────────────────────────────────────────────────── stack ────
0xffffd430│+0x0000: 0x00000001   ← $esp
0xffffd434│+0x0004: 0xffffd5aa  →  "/root/box/hello"
0xffffd438│+0x0008: 0x00000000
0xffffd43c│+0x000c: 0xffffd5ba  →  0x5353454c
0xffffd440│+0x0010: 0xffffd5cf  →  "POWERSHELL_TELEMETRY_OPTOUT=1"
0xffffd444│+0x0014: 0xffffd5ed  →  "USER=root"
0xffffd448│+0x0018: 0xffffd5f7  →  "LANGUAGE=en_US:en"
0xffffd44c│+0x001c: 0xffffd609  →  "SSH_CLIENT=192.168.181.1 60542 22"
─────────────────────────────────────────────────────────────────────────────────────────────── code:x86:32 ────
    0x8048ffa 0000                                 add    BYTE PTR [eax], al
    0x8048ffc 0000                                 add    BYTE PTR [eax], al
    0x8048ffe 0000                                 add    BYTE PTR [eax], al
 →  0x8049000 ba0e000000          <_start+0>       mov    edx, 0xe
    0x8049005 b900a00408          <_start+5>       mov    ecx, 0x804a000
    0x804900a bb01000000          <_start+10>      mov    ebx, 0x1
    0x804900f b804000000          <_start+15>      mov    eax, 0x4
    0x8049014 cd80                <_start+20>      int    0x80
    0x8049016 b801000000          <_start+22>      mov    eax, 0x1
─────────────────────────────────────────────────────────────────────────────────────────────────── threads ────
[#0] Id 1, Name: "hello", stopped 0x8049000 in _start (), reason: BREAKPOINT
───────────────────────────────────────────────────────────────────────────────────────────────────── trace ────
[#0] 0x8049000 → _start()
────────────────────────────────────────────────────────────────────────────────────────────────────────────────
gef➤  memory watch 0x8049000 64 byte
[+] Adding memwatch to 0x8049000
gef➤  memory watch 0x804a000 64 byte
[+] Adding memwatch to 0x804a000
gef➤  context memory
────────────────────────────────────────────────────────────────────────────────────────── memory:0x8049000 ────
0x08049000 <_start+0000>    ba 0e 00 00 00 b9 00 a0 04 08 bb 01 00 00 00 b8    ................
0x08049010 <_start+0010>    04 00 00 00 cd 80 b8 01 00 00 00 cd 80 00 00 00    ................
0x08049020     00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00    ................
0x08049030     00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00    ................
────────────────────────────────────────────────────────────────────────────────────────── memory:0x804a000 ────
0x0804a000 <msg+0000>    48 65 6c 6c 6f 2c 20 77 6f 72 6c 64 21 0a 00 00    Hello, world!...
0x0804a010     00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00    ................
0x0804a020     01 00 00 00 00 00 00 00 00 00 00 00 04 00 f1 ff    ................
0x0804a030     0b 00 00 00 00 a0 04 08 00 00 00 00 00 00 02 00    ................
────────────────────────────────────────────────────────────────────────────────────────────────────────────────
gef➤  disassemble /r _start,+28
Dump of assembler code from 0x8049000 to 0x804901c:
=> 0x08049000 <_start+0>:       ba 0e 00 00 00          mov    edx,0xe
   0x08049005 <_start+5>:       b9 00 a0 04 08          mov    ecx,0x804a000
   0x0804900a <_start+10>:      bb 01 00 00 00          mov    ebx,0x1
   0x0804900f <_start+15>:      b8 04 00 00 00          mov    eax,0x4
   0x08049014 <_start+20>:      cd 80                   int    0x80
   0x08049016 <_start+22>:      b8 01 00 00 00          mov    eax,0x1
   0x0804901b <_start+27>:      cd 80                   int    0x80
End of assembler dump.
gef➤  x/s 0x0804a000
0x804a000:      "Hello, world!\n"
gef➤  x/4xw 0x0804a000
0x804a000:      0x6c6c6548      0x77202c6f      0x646c726f      0x00000a21
gef➤
```

## 9starts.asm

{% capture code %}
{% highlight nasm linenos %}
section	.text
   global _start	 ;must be declared for linker (gcc)
	
_start:	         ;tell linker entry point
   mov	edx,len  ;message length
   mov	ecx,msg  ;message to write
   mov	ebx,1    ;file descriptor (stdout)
   mov	eax,4    ;system call number (sys_write)
   int	0x80     ;call kernel
	
   mov	edx,9    ;message length
   mov	ecx,s2   ;message to write
   mov	ebx,1    ;file descriptor (stdout)
   mov	eax,4    ;system call number (sys_write)
   int	0x80     ;call kernel
	
   mov	eax,1    ;system call number (sys_exit)
   int	0x80     ;call kernel
	
section	.data
msg db 'Displaying 9 stars',0xa ;a message
len equ $ - msg  ;length of message
s2 times 9 db '*'
{% endhighlight %}
{% endcapture %}
{% include fix_linenos.html code=code %}
{% assign code = nil %}

Biên dịch chương trình:

```
nasm -f elf32 9starts.asm
ld -m elf_i386 -o 9starts 9starts.o
```

Dùng __gef__ debug:

```conf
┌──(root㉿kali)-[~/box]
└─# gdb-gef -q 9starts
Reading symbols from 9starts...
(No debugging symbols found in 9starts)
Error while writing index for `/root/box/9starts': No debugging symbols
GEF for linux ready, type `gef' to start, `gef config' to configure
89 commands loaded and 5 functions added for GDB 13.2 in 0.01ms using Python engine 3.11
gef➤  start
...
gef➤  memory watch 0x8049000 64 byte
[+] Adding memwatch to 0x8049000
gef➤  memory watch 0x804a000 64 byte
[+] Adding memwatch to 0x804a000
gef➤  context memory
────────────────────────────────────────────────────────────────────────────────────────── memory:0x8049000 ────
0x08049000 <_start+0000>    ba 13 00 00 00 b9 00 a0 04 08 bb 01 00 00 00 b8    ................
0x08049010 <_start+0010>    04 00 00 00 cd 80 ba 09 00 00 00 b9 13 a0 04 08    ................
0x08049020 <_start+0020>    bb 01 00 00 00 b8 04 00 00 00 cd 80 b8 01 00 00    ................
0x08049030 <_start+0030>    00 cd 80 00 00 00 00 00 00 00 00 00 00 00 00 00    ................
────────────────────────────────────────────────────────────────────────────────────────── memory:0x804a000 ────
0x0804a000 <msg+0000>    44 69 73 70 6c 61 79 69 6e 67 20 39 20 73 74 61    Displaying 9 sta
0x0804a010 <msg+0010>    72 73 0a 2a 2a 2a 2a 2a 2a 2a 2a 2a 00 00 00 00    rs.*********....
0x0804a020     00 00 00 00 00 00 00 00 00 00 00 00 01 00 00 00    ................
0x0804a030     00 00 00 00 00 00 00 00 04 00 f1 ff 0d 00 00 00    ................
────────────────────────────────────────────────────────────────────────────────────────────────────────────────
gef➤
```

## input.asm

{% capture code %}
{% highlight nasm linenos %}
section .data                           ;Data segment
   userMsg db 'Please enter a number: ' ;Ask the user to enter a number
   lenUserMsg equ $-userMsg             ;The length of the message
   dispMsg db 'You have entered: '
   lenDispMsg equ $-dispMsg                 

section .bss           ;Uninitialized data
   num resb 5
	
section .text          ;Code Segment
   global _start
	
_start:                ;User prompt
   ;Output the message 'Please enter a number: '
   mov eax, 4
   mov ebx, 1
   mov ecx, userMsg
   mov edx, lenUserMsg
   int 80h

   ;Read and store the user input
   mov eax, 3
   mov ebx, 2
   mov ecx, num  
   mov edx, 5          ;5 bytes (numeric, 1 for sign) of that information
   int 80h
	
   ;Output the message 'The entered number is: '
   mov eax, 4
   mov ebx, 1
   mov ecx, dispMsg
   mov edx, lenDispMsg
   int 80h  

   ;Output the number entered
   mov eax, 4
   mov ebx, 1
   mov ecx, num
   mov edx, 5
   int 80h  
    
   ; Exit code
   mov eax, 1
   mov ebx, 0
   int 80h
{% endhighlight %}
{% endcapture %}
{% include fix_linenos.html code=code %}
{% assign code = nil %}

Biên dịch chương trình:

```
nasm -f elf32 input.asm
ld -m elf_i386 -o input input.o
```

Dùng __gef__ debug:

```conf
┌──(root㉿kali)-[~/box]
└─# gdb-gef -q input
Reading symbols from input...
(No debugging symbols found in input)
Error while writing index for `/root/box/input': No debugging symbols
GEF for linux ready, type `gef' to start, `gef config' to configure
89 commands loaded and 5 functions added for GDB 13.2 in 0.01ms using Python engine 3.11
gef➤  start
...
gef➤  disassemble _start,+100
Dump of assembler code from 0x8049000 to 0x8049064:
=> 0x08049000 <_start+0>:       mov    eax,0x4
   0x08049005 <_start+5>:       mov    ebx,0x1
   0x0804900a <_start+10>:      mov    ecx,0x804a000
   0x0804900f <_start+15>:      mov    edx,0x17
   0x08049014 <_start+20>:      int    0x80
   0x08049016 <_start+22>:      mov    eax,0x3
   0x0804901b <_start+27>:      mov    ebx,0x2
   0x08049020 <_start+32>:      mov    ecx,0x804a02c
   0x08049025 <_start+37>:      mov    edx,0x5
   0x0804902a <_start+42>:      int    0x80
   0x0804902c <_start+44>:      mov    eax,0x4
   0x08049031 <_start+49>:      mov    ebx,0x1
   0x08049036 <_start+54>:      mov    ecx,0x804a017
   0x0804903b <_start+59>:      mov    edx,0x12
   0x08049040 <_start+64>:      int    0x80
   0x08049042 <_start+66>:      mov    eax,0x4
   0x08049047 <_start+71>:      mov    ebx,0x1
   0x0804904c <_start+76>:      mov    ecx,0x804a02c
   0x08049051 <_start+81>:      mov    edx,0x5
   0x08049056 <_start+86>:      int    0x80
   0x08049058 <_start+88>:      mov    eax,0x1
   0x0804905d <_start+93>:      mov    ebx,0x0
   0x08049062 <_start+98>:      int    0x80
End of assembler dump.
gef➤  b *_start+44
Breakpoint 1 at 0x804902c
gef➤  memory watch 0x804a000 64 byte
[+] Adding memwatch to 0x804a000
gef➤  context memory
────────────────────────────────────────────────────────────────────────────────────────── memory:0x804a000 ────
0x0804a000 <userMsg+0000>    50 6c 65 61 73 65 20 65 6e 74 65 72 20 61 20 6e    Please enter a n
0x0804a010 <userMsg+0010>    75 6d 62 65 72 3a 20 59 6f 75 20 68 61 76 65 20    umber: You have
0x0804a020 <dispMsg+0009>    65 6e 74 65 72 65 64 3a 20 00 00 00 00 00 00 00    entered: .......
0x0804a030 <num+0004>    00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00    ................
────────────────────────────────────────────────────────────────────────────────────────────────────────────────
gef➤  continue
Continuing.
Please enter a number: 1234

Breakpoint 1, 0x0804902c in _start ()
...
gef➤  context memory
────────────────────────────────────────────────────────────────────────────────────────── memory:0x804a000 ────
0x0804a000 <userMsg+0000>    50 6c 65 61 73 65 20 65 6e 74 65 72 20 61 20 6e    Please enter a n
0x0804a010 <userMsg+0010>    75 6d 62 65 72 3a 20 59 6f 75 20 68 61 76 65 20    umber: You have
0x0804a020 <dispMsg+0009>    65 6e 74 65 72 65 64 3a 20 00 00 00 31 32 33 34    entered: ...1234
0x0804a030 <num+0004>    0a 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00    ................
────────────────────────────────────────────────────────────────────────────────────────────────────────────────
gef➤
```

## mov.asm

{% capture code %}
{% highlight nasm linenos %}
section .data                           ;Data segment
section	.text
   global _start     ;must be declared for linker (ld)
_start:             ;tell linker entry point
	
   ;writing the name 'Zara Ali'
   mov	edx,9       ;message length
   mov	ecx,name    ;message to write
   mov	ebx,1       ;file descriptor (stdout)
   mov	eax,4       ;system call number (sys_write)
   int	0x80        ;call kernel
	
   mov	[name],  dword 'Nuha'    ; Changed the name to Nuha Ali
	
   ;writing the name 'Nuha Ali'
   mov	edx,9       ;message length
   mov	ecx,name    ;message to write
   mov	ebx,1       ;file descriptor (stdout)
   mov	eax,4       ;system call number (sys_write)
   int	0x80        ;call kernel
	
   mov	eax,1       ;system call number (sys_exit)
   int	0x80        ;call kernel

section	.data
name db 'Zara Ali',0xa
{% endhighlight %}
{% endcapture %}
{% include fix_linenos.html code=code %}
{% assign code = nil %}

Biên dịch chương trình:

```
nasm -f elf32 mov.asm
ld -m elf_i386 -o mov mov.o
```

Dùng __gef__ debug:

```conf
┌──(root㉿kali)-[~/box]
└─# gdb-gef -q mov
Reading symbols from mov...
(No debugging symbols found in mov)
Error while writing index for `/root/box/mov': No debugging symbols
GEF for linux ready, type `gef' to start, `gef config' to configure
89 commands loaded and 5 functions added for GDB 13.2 in 0.01ms using Python engine 3.11
gef➤  start
...
gef➤  disassemble _start,+60
Dump of assembler code from 0x8049000 to 0x804903c:
=> 0x08049000 <_start+0>:       mov    edx,0x9
   0x08049005 <_start+5>:       mov    ecx,0x804a000
   0x0804900a <_start+10>:      mov    ebx,0x1
   0x0804900f <_start+15>:      mov    eax,0x4
   0x08049014 <_start+20>:      int    0x80
   0x08049016 <_start+22>:      mov    DWORD PTR ds:0x804a000,0x6168754e
   0x08049020 <_start+32>:      mov    edx,0x9
   0x08049025 <_start+37>:      mov    ecx,0x804a000
   0x0804902a <_start+42>:      mov    ebx,0x1
   0x0804902f <_start+47>:      mov    eax,0x4
   0x08049034 <_start+52>:      int    0x80
   0x08049036 <_start+54>:      mov    eax,0x1
   0x0804903b <_start+59>:      int    0x80
End of assembler dump.
gef➤  b *_start+32
Breakpoint 1 at 0x8049020
gef➤  memory watch 0x804a000 64 byte
[+] Adding memwatch to 0x804a000
gef➤  context memory
────────────────────────────────────────────────────────────────────────────────────────── memory:0x804a000 ────
0x0804a000 <name+0000>    5a 61 72 61 20 41 6c 69 0a 00 00 00 00 00 00 00    Zara Ali........
0x0804a010     00 00 00 00 00 00 00 00 00 00 00 00 01 00 00 00    ................
0x0804a020     00 00 00 00 00 00 00 00 04 00 f1 ff 09 00 00 00    ................
0x0804a030     00 a0 04 08 00 00 00 00 00 00 02 00 13 00 00 00    ................
────────────────────────────────────────────────────────────────────────────────────────────────────────────────
gef➤  continue
Continuing.
Zara Ali

Breakpoint 1, 0x08049020 in _start ()
...
gef➤  context memory
────────────────────────────────────────────────────────────────────────────────────────── memory:0x804a000 ────
0x0804a000 <name+0000>    4e 75 68 61 20 41 6c 69 0a 00 00 00 00 00 00 00    Nuha Ali........
0x0804a010     00 00 00 00 00 00 00 00 00 00 00 00 01 00 00 00    ................
0x0804a020     00 00 00 00 00 00 00 00 04 00 f1 ff 09 00 00 00    ................
0x0804a030     00 a0 04 08 00 00 00 00 00 00 02 00 13 00 00 00    ................
────────────────────────────────────────────────────────────────────────────────────────────────────────────────
gef➤
```

## sum.asm

{% capture code %}
{% highlight nasm linenos %}
SYS_EXIT  equ 1
SYS_READ  equ 3
SYS_WRITE equ 4
STDIN     equ 0
STDOUT    equ 1

segment .data 

   msg1 db "Enter a digit: "
   len1 equ $- msg1 

   msg2 db "Please enter a second digit: "
   len2 equ $- msg2 

   msg3 db "The sum is: "
   len3 equ $- msg3

segment .bss

   num1 resb 2 
   num2 resb 2 
   res resb 1    

section	.text
   global _start    ;must be declared for using gcc
	
_start:             ;tell linker entry point
   mov eax, SYS_WRITE         
   mov ebx, STDOUT         
   mov ecx, msg1         
   mov edx, len1 
   int 0x80                

   mov eax, SYS_READ 
   mov ebx, STDIN  
   mov ecx, num1 
   mov edx, 2
   int 0x80            

   mov eax, SYS_WRITE        
   mov ebx, STDOUT         
   mov ecx, msg2          
   mov edx, len2         
   int 0x80

   mov eax, SYS_READ  
   mov ebx, STDIN  
   mov ecx, num2 
   mov edx, 2
   int 0x80        

   mov eax, SYS_WRITE         
   mov ebx, STDOUT         
   mov ecx, msg3          
   mov edx, len3         
   int 0x80

   ; moving the first number to eax register and second number to ebx
   ; and subtracting ascii '0' to convert it into a decimal number
	
   mov eax, [num1]
   sub eax, '0'
	
   mov ebx, [num2]
   sub ebx, '0'

   ; add eax and ebx
   add eax, ebx
   ; add '0' to to convert the sum from decimal to ASCII
   add eax, '0'

   ; storing the sum in memory location res
   mov [res], eax

   ; print the sum 
   mov eax, SYS_WRITE        
   mov ebx, STDOUT
   mov ecx, res         
   mov edx, 1        
   int 0x80

exit:    
   
   mov eax, SYS_EXIT   
   xor ebx, ebx 
   int 0x80
{% endhighlight %}
{% endcapture %}
{% include fix_linenos.html code=code %}
{% assign code = nil %}

Biên dịch chương trình:

```
nasm -f elf32 sum.asm
ld -m elf_i386 -o sum sum.o
```

Dùng __gef__ debug:

```conf
┌──(root㉿kali)-[~/box]
└─# gdb-gef -q sum
Reading symbols from sum...
(No debugging symbols found in sum)
Error while writing index for `/root/box/sum': No debugging symbols
GEF for linux ready, type `gef' to start, `gef config' to configure
89 commands loaded and 5 functions added for GDB 13.2 in 0.00ms using Python engine 3.11
gef➤  start
...
gef➤  disassemble _start,+168
Dump of assembler code from 0x8049000 to 0x80490a8:
=> 0x08049000 <_start+0>:       mov    eax,0x4
   0x08049005 <_start+5>:       mov    ebx,0x1
   0x0804900a <_start+10>:      mov    ecx,0x804a000
   0x0804900f <_start+15>:      mov    edx,0xf
   0x08049014 <_start+20>:      int    0x80
   0x08049016 <_start+22>:      mov    eax,0x3
   0x0804901b <_start+27>:      mov    ebx,0x0
   0x08049020 <_start+32>:      mov    ecx,0x804a038
   0x08049025 <_start+37>:      mov    edx,0x2
   0x0804902a <_start+42>:      int    0x80
   0x0804902c <_start+44>:      mov    eax,0x4
   0x08049031 <_start+49>:      mov    ebx,0x1
   0x08049036 <_start+54>:      mov    ecx,0x804a00f
   0x0804903b <_start+59>:      mov    edx,0x1d
   0x08049040 <_start+64>:      int    0x80
   0x08049042 <_start+66>:      mov    eax,0x3
   0x08049047 <_start+71>:      mov    ebx,0x0
   0x0804904c <_start+76>:      mov    ecx,0x804a03a
   0x08049051 <_start+81>:      mov    edx,0x2
   0x08049056 <_start+86>:      int    0x80
   0x08049058 <_start+88>:      mov    eax,0x4
   0x0804905d <_start+93>:      mov    ebx,0x1
   0x08049062 <_start+98>:      mov    ecx,0x804a02c
   0x08049067 <_start+103>:     mov    edx,0xc
   0x0804906c <_start+108>:     int    0x80
   0x0804906e <_start+110>:     mov    eax,ds:0x804a038
   0x08049073 <_start+115>:     sub    eax,0x30
   0x08049076 <_start+118>:     mov    ebx,DWORD PTR ds:0x804a03a
   0x0804907c <_start+124>:     sub    ebx,0x30
   0x0804907f <_start+127>:     add    eax,ebx
   0x08049081 <_start+129>:     add    eax,0x30
   0x08049084 <_start+132>:     mov    ds:0x804a03c,eax
   0x08049089 <_start+137>:     mov    eax,0x4
   0x0804908e <_start+142>:     mov    ebx,0x1
   0x08049093 <_start+147>:     mov    ecx,0x804a03c
   0x08049098 <_start+152>:     mov    edx,0x1
   0x0804909d <_start+157>:     int    0x80
   0x0804909f <exit+0>: mov    eax,0x1
   0x080490a4 <exit+5>: xor    ebx,ebx
   0x080490a6 <exit+7>: int    0x80
End of assembler dump.
gef➤  b *_start+44
Breakpoint 1 at 0x804902c
gef➤  b *_start+88
Breakpoint 2 at 0x8049058
gef➤  b *_start+110
Breakpoint 3 at 0x804906e
gef➤  memory watch 0x804a000 80 byte
[+] Adding memwatch to 0x804a000
gef➤  context memory
────────────────────────────────────────────────────────────────────────────────────────── memory:0x804a000 ────
0x0804a000 <msg1+0000>    45 6e 74 65 72 20 61 20 64 69 67 69 74 3a 20 50    Enter a digit: P
0x0804a010 <msg2+0001>    6c 65 61 73 65 20 65 6e 74 65 72 20 61 20 73 65    lease enter a se
0x0804a020 <msg2+0011>    63 6f 6e 64 20 64 69 67 69 74 3a 20 54 68 65 20    cond digit: The
0x0804a030 <msg3+0004>    73 75 6d 20 69 73 3a 20 00 00 00 00 00 00 00 00    sum is: ........
0x0804a040     00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00    ................
────────────────────────────────────────────────────────────────────────────────────────────────────────────────
gef➤  continue
Continuing.
Enter a digit: 2

Breakpoint 1, 0x0804902c in _start ()
...
────────────────────────────────────────────────────────────────────────────────────────── memory:0x804a000 ────
0x0804a000 <msg1+0000>    45 6e 74 65 72 20 61 20 64 69 67 69 74 3a 20 50    Enter a digit: P
0x0804a010 <msg2+0001>    6c 65 61 73 65 20 65 6e 74 65 72 20 61 20 73 65    lease enter a se
0x0804a020 <msg2+0011>    63 6f 6e 64 20 64 69 67 69 74 3a 20 54 68 65 20    cond digit: The
0x0804a030 <msg3+0004>    73 75 6d 20 69 73 3a 20 32 0a 00 00 00 00 00 00    sum is: 2.......
0x0804a040     00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00    ................
────────────────────────────────────────────────────────────────────────────────────────────────────────────────
...
gef➤  continue
Continuing.
Please enter a second digit: 3

Breakpoint 2, 0x08049058 in _start ()
[ Legend: Modified register | Code | Heap | Stack | String ]
...
────────────────────────────────────────────────────────────────────────────────────────── memory:0x804a000 ────
0x0804a000 <msg1+0000>    45 6e 74 65 72 20 61 20 64 69 67 69 74 3a 20 50    Enter a digit: P
0x0804a010 <msg2+0001>    6c 65 61 73 65 20 65 6e 74 65 72 20 61 20 73 65    lease enter a se
0x0804a020 <msg2+0011>    63 6f 6e 64 20 64 69 67 69 74 3a 20 54 68 65 20    cond digit: The
0x0804a030 <msg3+0004>    73 75 6d 20 69 73 3a 20 32 0a 33 0a 00 00 00 00    sum is: 2.3.....
0x0804a040     00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00    ................
────────────────────────────────────────────────────────────────────────────────────────────────────────────────
...
gef➤  continue
Continuing.
The sum is:
Breakpoint 3, 0x0804906e in _start ()
...
gef➤  stepi
0x08049073 in _start ()
[ Legend: Modified register | Code | Heap | Stack | String ]
───────────────────────────────────────────────────────────────────────────────────────────────── registers ────
$eax   : 0xa330a32  ("2\n3\n"?)
$ebx   : 0x1
...
─────────────────────────────────────────────────────────────────────────────────────────────── code:x86:32 ────
    0x8049067 ba0c000000          <_start+103>     mov    edx, 0xc
    0x804906c cd80                <_start+108>     int    0x80
    0x804906e a138a00408          <_start+110>     mov    eax, ds:0x804a038
 →  0x8049073 83e830              <_start+115>     sub    eax, 0x30
    0x8049076 8b1d3aa00408        <_start+118>     mov    ebx, DWORD PTR ds:0x804a03a
    0x804907c 83eb30              <_start+124>     sub    ebx, 0x30
    0x804907f 01d8                <_start+127>     add    eax, ebx
    0x8049081 83c030              <_start+129>     add    eax, 0x30
    0x8049084 a33ca00408          <_start+132>     mov    ds:0x804a03c, eax
────────────────────────────────────────────────────────────────────────────────────────── memory:0x804a000 ────
0x0804a000 <msg1+0000>    45 6e 74 65 72 20 61 20 64 69 67 69 74 3a 20 50    Enter a digit: P
0x0804a010 <msg2+0001>    6c 65 61 73 65 20 65 6e 74 65 72 20 61 20 73 65    lease enter a se
0x0804a020 <msg2+0011>    63 6f 6e 64 20 64 69 67 69 74 3a 20 54 68 65 20    cond digit: The
0x0804a030 <msg3+0004>    73 75 6d 20 69 73 3a 20 32 0a 33 0a 00 00 00 00    sum is: 2.3.....
0x0804a040     00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00    ................
─────────────────────────────────────────────────────────────────────────────────────────────────── threads ────
...
gef➤  stepi
0x08049076 in _start ()
[ Legend: Modified register | Code | Heap | Stack | String ]
───────────────────────────────────────────────────────────────────────────────────────────────── registers ────
$eax   : 0xa330a02
$ebx   : 0x1
...
─────────────────────────────────────────────────────────────────────────────────────────────── code:x86:32 ────
    0x804906c cd80                <_start+108>     int    0x80
    0x804906e a138a00408          <_start+110>     mov    eax, ds:0x804a038
    0x8049073 83e830              <_start+115>     sub    eax, 0x30
 →  0x8049076 8b1d3aa00408        <_start+118>     mov    ebx, DWORD PTR ds:0x804a03a
    0x804907c 83eb30              <_start+124>     sub    ebx, 0x30
    0x804907f 01d8                <_start+127>     add    eax, ebx
    0x8049081 83c030              <_start+129>     add    eax, 0x30
    0x8049084 a33ca00408          <_start+132>     mov    ds:0x804a03c, eax
    0x8049089 b804000000          <_start+137>     mov    eax, 0x4
────────────────────────────────────────────────────────────────────────────────────────── memory:0x804a000 ────
0x0804a000 <msg1+0000>    45 6e 74 65 72 20 61 20 64 69 67 69 74 3a 20 50    Enter a digit: P
0x0804a010 <msg2+0001>    6c 65 61 73 65 20 65 6e 74 65 72 20 61 20 73 65    lease enter a se
0x0804a020 <msg2+0011>    63 6f 6e 64 20 64 69 67 69 74 3a 20 54 68 65 20    cond digit: The
0x0804a030 <msg3+0004>    73 75 6d 20 69 73 3a 20 32 0a 33 0a 00 00 00 00    sum is: 2.3.....
0x0804a040     00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00    ................
...
gef➤  stepi
0x0804907c in _start ()
[ Legend: Modified register | Code | Heap | Stack | String ]
───────────────────────────────────────────────────────────────────────────────────────────────── registers ────
$eax   : 0xa330a02
$ebx   : 0xa33
...
─────────────────────────────────────────────────────────────────────────────────────────────── code:x86:32 ────
    0x804906e a138a00408          <_start+110>     mov    eax, ds:0x804a038
    0x8049073 83e830              <_start+115>     sub    eax, 0x30
    0x8049076 8b1d3aa00408        <_start+118>     mov    ebx, DWORD PTR ds:0x804a03a
 →  0x804907c 83eb30              <_start+124>     sub    ebx, 0x30
    0x804907f 01d8                <_start+127>     add    eax, ebx
    0x8049081 83c030              <_start+129>     add    eax, 0x30
    0x8049084 a33ca00408          <_start+132>     mov    ds:0x804a03c, eax
    0x8049089 b804000000          <_start+137>     mov    eax, 0x4
    0x804908e bb01000000          <_start+142>     mov    ebx, 0x1
────────────────────────────────────────────────────────────────────────────────────────── memory:0x804a000 ────
0x0804a000 <msg1+0000>    45 6e 74 65 72 20 61 20 64 69 67 69 74 3a 20 50    Enter a digit: P
0x0804a010 <msg2+0001>    6c 65 61 73 65 20 65 6e 74 65 72 20 61 20 73 65    lease enter a se
0x0804a020 <msg2+0011>    63 6f 6e 64 20 64 69 67 69 74 3a 20 54 68 65 20    cond digit: The
0x0804a030 <msg3+0004>    73 75 6d 20 69 73 3a 20 32 0a 33 0a 00 00 00 00    sum is: 2.3.....
0x0804a040     00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00    ................
─────────────────────────────────────────────────────────────────────────────────────────────────── threads ────
...
gef➤  stepi
0x0804907f in _start ()
[ Legend: Modified register | Code | Heap | Stack | String ]
───────────────────────────────────────────────────────────────────────────────────────────────── registers ────
$eax   : 0xa330a02
$ebx   : 0xa03
...
─────────────────────────────────────────────────────────────────────────────────────────────── code:x86:32 ────
    0x8049073 83e830              <_start+115>     sub    eax, 0x30
    0x8049076 8b1d3aa00408        <_start+118>     mov    ebx, DWORD PTR ds:0x804a03a
    0x804907c 83eb30              <_start+124>     sub    ebx, 0x30
 →  0x804907f 01d8                <_start+127>     add    eax, ebx
    0x8049081 83c030              <_start+129>     add    eax, 0x30
    0x8049084 a33ca00408          <_start+132>     mov    ds:0x804a03c, eax
    0x8049089 b804000000          <_start+137>     mov    eax, 0x4
    0x804908e bb01000000          <_start+142>     mov    ebx, 0x1
    0x8049093 b93ca00408          <_start+147>     mov    ecx, 0x804a03c
────────────────────────────────────────────────────────────────────────────────────────── memory:0x804a000 ────
0x0804a000 <msg1+0000>    45 6e 74 65 72 20 61 20 64 69 67 69 74 3a 20 50    Enter a digit: P
0x0804a010 <msg2+0001>    6c 65 61 73 65 20 65 6e 74 65 72 20 61 20 73 65    lease enter a se
0x0804a020 <msg2+0011>    63 6f 6e 64 20 64 69 67 69 74 3a 20 54 68 65 20    cond digit: The
0x0804a030 <msg3+0004>    73 75 6d 20 69 73 3a 20 32 0a 33 0a 00 00 00 00    sum is: 2.3.....
0x0804a040     00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00    ................
─────────────────────────────────────────────────────────────────────────────────────────────────── threads ────
...
gef➤  stepi
0x08049081 in _start ()
[ Legend: Modified register | Code | Heap | Stack | String ]
───────────────────────────────────────────────────────────────────────────────────────────────── registers ────
$eax   : 0xa331405
$ebx   : 0xa03
...
─────────────────────────────────────────────────────────────────────────────────────────────── code:x86:32 ────
    0x8049076 8b1d3aa00408        <_start+118>     mov    ebx, DWORD PTR ds:0x804a03a
    0x804907c 83eb30              <_start+124>     sub    ebx, 0x30
    0x804907f 01d8                <_start+127>     add    eax, ebx
 →  0x8049081 83c030              <_start+129>     add    eax, 0x30
    0x8049084 a33ca00408          <_start+132>     mov    ds:0x804a03c, eax
    0x8049089 b804000000          <_start+137>     mov    eax, 0x4
    0x804908e bb01000000          <_start+142>     mov    ebx, 0x1
    0x8049093 b93ca00408          <_start+147>     mov    ecx, 0x804a03c
    0x8049098 ba01000000          <_start+152>     mov    edx, 0x1
────────────────────────────────────────────────────────────────────────────────────────── memory:0x804a000 ────
0x0804a000 <msg1+0000>    45 6e 74 65 72 20 61 20 64 69 67 69 74 3a 20 50    Enter a digit: P
0x0804a010 <msg2+0001>    6c 65 61 73 65 20 65 6e 74 65 72 20 61 20 73 65    lease enter a se
0x0804a020 <msg2+0011>    63 6f 6e 64 20 64 69 67 69 74 3a 20 54 68 65 20    cond digit: The
0x0804a030 <msg3+0004>    73 75 6d 20 69 73 3a 20 32 0a 33 0a 00 00 00 00    sum is: 2.3.....
0x0804a040     00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00    ................
─────────────────────────────────────────────────────────────────────────────────────────────────── threads ────
...
gef➤  stepi
0x08049084 in _start ()
[ Legend: Modified register | Code | Heap | Stack | String ]
───────────────────────────────────────────────────────────────────────────────────────────────── registers ────
$eax   : 0xa331435
$ebx   : 0xa03
...
─────────────────────────────────────────────────────────────────────────────────────────────── code:x86:32 ────
    0x804907c 83eb30              <_start+124>     sub    ebx, 0x30
    0x804907f 01d8                <_start+127>     add    eax, ebx
    0x8049081 83c030              <_start+129>     add    eax, 0x30
 →  0x8049084 a33ca00408          <_start+132>     mov    ds:0x804a03c, eax
    0x8049089 b804000000          <_start+137>     mov    eax, 0x4
    0x804908e bb01000000          <_start+142>     mov    ebx, 0x1
    0x8049093 b93ca00408          <_start+147>     mov    ecx, 0x804a03c
    0x8049098 ba01000000          <_start+152>     mov    edx, 0x1
    0x804909d cd80                <_start+157>     int    0x80
────────────────────────────────────────────────────────────────────────────────────────── memory:0x804a000 ────
0x0804a000 <msg1+0000>    45 6e 74 65 72 20 61 20 64 69 67 69 74 3a 20 50    Enter a digit: P
0x0804a010 <msg2+0001>    6c 65 61 73 65 20 65 6e 74 65 72 20 61 20 73 65    lease enter a se
0x0804a020 <msg2+0011>    63 6f 6e 64 20 64 69 67 69 74 3a 20 54 68 65 20    cond digit: The
0x0804a030 <msg3+0004>    73 75 6d 20 69 73 3a 20 32 0a 33 0a 00 00 00 00    sum is: 2.3.....
0x0804a040     00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00    ................
─────────────────────────────────────────────────────────────────────────────────────────────────── threads ────
...
gef➤  stepi
0x08049089 in _start ()
[ Legend: Modified register | Code | Heap | Stack | String ]
───────────────────────────────────────────────────────────────────────────────────────────────── registers ────
$eax   : 0xa331435
$ebx   : 0xa03
...
─────────────────────────────────────────────────────────────────────────────────────────────── code:x86:32 ────
    0x804907f 01d8                <_start+127>     add    eax, ebx
    0x8049081 83c030              <_start+129>     add    eax, 0x30
    0x8049084 a33ca00408          <_start+132>     mov    ds:0x804a03c, eax
 →  0x8049089 b804000000          <_start+137>     mov    eax, 0x4
    0x804908e bb01000000          <_start+142>     mov    ebx, 0x1
    0x8049093 b93ca00408          <_start+147>     mov    ecx, 0x804a03c
    0x8049098 ba01000000          <_start+152>     mov    edx, 0x1
    0x804909d cd80                <_start+157>     int    0x80
    0x804909f b801000000          <exit+0>         mov    eax, 0x1
────────────────────────────────────────────────────────────────────────────────────────── memory:0x804a000 ────
0x0804a000 <msg1+0000>    45 6e 74 65 72 20 61 20 64 69 67 69 74 3a 20 50    Enter a digit: P
0x0804a010 <msg2+0001>    6c 65 61 73 65 20 65 6e 74 65 72 20 61 20 73 65    lease enter a se
0x0804a020 <msg2+0011>    63 6f 6e 64 20 64 69 67 69 74 3a 20 54 68 65 20    cond digit: The
0x0804a030 <msg3+0004>    73 75 6d 20 69 73 3a 20 32 0a 33 0a 35 14 33 0a    sum is: 2.3.5.3.
0x0804a040     00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00    ................
─────────────────────────────────────────────────────────────────────────────────────────────────── threads ────
...
gef➤  continue
Continuing.
5[Inferior 1 (process 1732025) exited normally]
gef➤
```

