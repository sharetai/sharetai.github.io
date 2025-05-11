---
layout: default
title: Cài đặt cấu hình qua dây Octal
nav_order: 9
parent: CCNA (old)
---

# Cài đặt cấu hình qua dây Octal
{: .no_toc }

Cấu hình qua dây Octal khi không thể nối dây console và không có ip để telnet
{: .fs-6 .fw-300 }

---

**Mô hình**

![image](/docs/CCNA (old)/img/octal_cable_config_1.png)

Trên router cần gắn thêm module HWIC-8A

![image](/docs/CCNA (old)/img/octal_cable_config_2.png)

**Cấu hình telnet cho Router0**

```
Router>enable
Router#conf t
Router(config)#int Gi0/0
Router(config-if)#ip address 192.168.1.101 255.255.255.0
Router(config-if)#no shutdown
Router(config)#enable secret 456
Router(config)#username admin secret 123
Router(config)#line vty 0 4
Router(config-line)#login local
```

**Cấu hình cho các cổng Octal**

Từ cấu hình trên có thể đứng trên PC telnet đến Router0 để cấu hình cho các cổng Octal:

```
C:\>telnet 192.168.1.101
Router>enable
Router#conf t
Router(config)#line 0/0/0 0/0/7
Router(config-line)#transport input telnet
Router(config-line)#login local
```

**Kiểm tra**

Đến đây ta có thể telnet đến các Router được nối dây octal thông qua port (2000+Line)

Để xem Line dùng lệnh:

```
Router#sh line 
   Tty Line Typ     Tx/Rx    A Roty AccO AccI   Uses   Noise  Overruns   Int
*    0    0 CTY              -    -    -    -      0       0     0/0       -
     1    1 AUX   9600/9600  -    -    -    -      0       0     0/0       -
 0/0/0    3 TTY   9600/9600  -    -    -    -      0       0     0/0       -
 0/0/1    4 TTY   9600/9600  -    -    -    -      0       0     0/0       -
 0/0/2    5 TTY   9600/9600  -    -    -    -      0       0     0/0       -
 0/0/3    6 TTY   9600/9600  -    -    -    -      0       0     0/0       -
 0/0/4    7 TTY   9600/9600  -    -    -    -      0       0     0/0       -
 0/0/5    8 TTY   9600/9600  -    -    -    -      0       0     0/0       -
 0/0/6    9 TTY   9600/9600  -    -    -    -      0       0     0/0       -
 0/0/7   10 TTY   9600/9600  -    -    -    -      0       0     0/0       -
*  388  388 VTY              -    -    -    -      2       0     0/0       -
   389  389 VTY              -    -    -    -      0       0     0/0       -
   390  390 VTY              -    -    -    -      0       0     0/0       -
   391  391 VTY              -    -    -    -      0       0     0/0       -
   392  392 VTY              -    -    -    -      0       0     0/0       -
Line(s) not in async mode -or- with no hardware support:
11-387
```

Để telnet đến line 3 ta dùng port 2003:

```
C:\>telnet 192.168.1.101 2003
```

Line tty chỉ cho phép 1 phiên, nên để đóng phiên dùng lệnh sau:

```
Router#clear line tty 3
```
