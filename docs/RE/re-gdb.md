---
layout: default
title: GDB
nav_order: 4
parent: RE
---

# GNU Debugger
{: .no_toc }

Trình gỡ lỗi GNU
{: .fs-6 .fw-300 }

_Nguồn tham khảo: [https://0xinfection.github.io/reversing/](https://0xinfection.github.io/reversing/)_

---

## TABLE OF CONTENTS
{: .no_toc .text-delta }

1. TOC
{:toc}

---

## Cài đặt GDB

```
apt uppdate
apt install gdb -y
apt install gcc-multilib g++-multilib -y
```

Getting Started

```
┌──(root㉿kali)-[~/box]
└─# gdb
GNU gdb (Debian 13.2-1) 13.2
Copyright (C) 2023 Free Software Foundation, Inc.
License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>
This is free software: you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.
Type "show copying" and "show warranty" for details.
This GDB was configured as "x86_64-linux-gnu".
Type "show configuration" for configuration details.
For bug reporting instructions, please see:
<https://www.gnu.org/software/gdb/bugs/>.
Find the GDB manual and other documentation resources online at:
    <http://www.gnu.org/software/gdb/documentation/>.

For help, type "help".
Type "apropos word" to search for commands related to "word".
(gdb)
```

## Cài đặt GDB dashboard

```
wget -P ~ https://git.io/.gdbinit
pip install pygments
```

__Use personal configuration files__

~/.gdbinit.d/init
```
set disassembly-flavor intel
dashboard registers -style column-major True
dashboard assembly -style opcodes True
```

## Pwndbg + Peda + GEF — All in One

__Pwndbg__
```
git clone https://github.com/pwndbg/pwndbg ~/tools/pwndbg
cd ~/tools/pwndbg
./setup.sh
echo "source ~/tools/pwndbg/gdbinit.py" > ~/.gdbinit_pwndbg
```

__Peda__
```
git clone https://github.com/longld/peda ~/tools/peda
echo "source ~/tools/peda/peda.py" >> ~/.gdbinit_peda
```

__GEF__
```
wget -O ~/.gdbinit-gef.py -q https://raw.githubusercontent.com/hugsy/gef/main/gef.py
echo "source ~/.gdbinit-gef.py" >> ~/.gdbinit_gef
```

__~/.gdbinit__
```
echo -n "" > ~/.gdbinit
cat >> ~/.gdbinit

set disassembly-flavor intel

define init-pwndbg
source ~/.gdbinit_pwndbg
end
document init-pwndbg
Initializes PwnDBG
end

define init-peda
source ~/.gdbinit_peda
end
document init-peda
Initializes the PEDA (Python Exploit Development Assistant for GDB) framework
end

define init-gef
source ~/.gdbinit_gef
end
document init-gef
Initializes GEF (GDB Enhanced Features)
end
```

__/usr/bin/gdb-pwndbg__
```
cat >> /usr/bin/gdb-pwndbg
#!/bin/sh
exec gdb -q -ex init-pwndbg "$@"
```

__/usr/bin/gdb-peda__
```
cat >> /usr/bin/gdb-peda
#!/bin/sh
exec gdb -q -ex init-peda "$@"
```

__/usr/bin/gdb-gef__
```
cat >> /usr/bin/gdb-gef
#!/bin/sh
exec gdb -q -ex init-gef "$@"
```

__Add execute permission__
```
chmod +x /usr/bin/gdb-*
```

Getting Started
```
# gdb-pwndbg
pwndbg>

# gdb-peda
gdb-peda$

# gdb-gef
gef➤
```

## Cài đặt gdbgui

```
pip install gdbgui
```

Getting Started
```
gdbgui -r 0.0.0.0
```

