---
layout: default
title: IPv6
nav_order: 23
parent: CCNA
---

# Internet Protocol Version 6
{: .no_toc }

Giao thức Internet phiên bản 6
{: .fs-6 .fw-300 }

---

## Table of contents
{: .no_toc .text-delta }

1. TOC
{:toc}

---

## Tổng quan

### Thiếu hụt IPv4

|          IPv4 |  ->  | IPv6                                                |
| ------------: | :--: | :-------------------------------------------------- |
|       32 bits |  ->  | 128 bits                                            |
| 4,294,967,296 |  ->  | 340,282,366,920,938,463,463,374,607,431,768,211,456 |

Để giải quyết việc thiếu hụt IPv4, 2 phương án: <br>
\- VLSM <br>
\- NAT <br>
\-> Tuy nhiên vẫn thiếu, hiện tại đã cạn kiệt <br>

### IPv6

\- 128-bits địa chỉ <br>
\- Không có địa chỉ broadcast. Thay vào đó là anycast (cho phép trùng địa chỉ ipv6 trên nhiều node mạng, routing sẽ cần đến node gần nhất) <br>
\- Đặt địa chỉ IPv6: static, eui-64, slaac (staless auto address configuration), dhcpv6 <br>
\- Không cần NAT/PAT <br>
\- Hỗ trợ IPSec <br>
\- Header đơn giản hơn <br>
\- Công cụ chuyển giao Dual-stack IPv4/IPv6 <br>

### Biểu diễn IPv6

0010000001000001...0001001100011011 <br>
0010 0000 0100 0001 .... 0001 0011 0001 1011 <br>
  2    0    4    1  ....   1    3    1    B <br>
2041:1234:140F:1122:AB91:564F:875B:131B <br>

### Thu gọn địa chỉ IPv6

\- <u>Một chuỗi các số 0 liên tiếp có thể được lược bỏ, tuy nhiên chỉ được làm điều này một lần.</u> <br>

<p style="display:inline">2041:</p><p style="display:inline;color:red">0000</p><p style="display:inline">:140F:</p><p style="display:inline;color:red">0000:0000:0000</p><p style="display:inline">:875B:131B<br></p>
<p style="display:inline">2041</p><p style="display:inline;color:red">::</p><p style="display:inline">140F:</p><p style="display:inline;color:red">0000:0000:0000</p><p style="display:inline">:875B:131B<br></p>
<p style="display:inline">2041:</p><p style="display:inline;color:red">0000</p><p style="display:inline">:140F</p><p style="display:inline;color:red">::</p><p style="display:inline">875B:131B<br></p>

\- <u>Các số 0 đầu tiên trong 1 octet có thể được lược bỏ.</u> <br>

<p style="display:inline">2001:</p><p style="display:inline;color:red">0000</p><p style="display:inline">:</p><p style="display:inline;color:red">000</p><p style="display:inline">1:</p><p style="display:inline;color:red">0000</p><p style="display:inline">:</p><p style="display:inline;color:red">0000</p><p style="display:inline">:</p><p style="display:inline;color:red">000</p><p style="display:inline">2:</p><p style="display:inline;color:red">000</p><p style="display:inline">3:</p><p style="display:inline;color:red">000</p><p style="display:inline">4<br></p>

<p style="display:inline">2001:</p><p style="display:inline">0</p><p style="display:inline">:</p><p style="display:inline;color:red"></p><p style="display:inline">1:</p><p style="display:inline;color:red"></p><p style="display:inline">:</p><p style="display:inline;color:red"></p><p style="display:inline">2:</p><p style="display:inline;color:red"></p><p style="display:inline">3:</p><p style="display:inline;color:red"></p><p style="display:inline">4<br></p>

### Prefix

<p style="display:inline;color:blue">Prefix</p><p style="display:inline">:</p><p style="display:inline;color:green">Host<br></p>
<p style="display:inline;color:blue">2001:1234:5678:1234</p><p style="display:inline">:</p><p style="display:inline;color:green">5678:ABCD:EF12:1234<br></p>
<p style="display:inline;color:blue">2001:1234:5678:1234</p><p style="display:inline">:</p><p style="display:inline;color:green">0000:0000:0000:0000<br></p>
<p style="display:inline;color:blue">2001:1234:5678:1234::</p><p style="display:inline;color:green">/64<br></p>

### Các loại địa chỉ IPv6

![alt text](/docs/CCNA/img/ipv6-type.png)

### Quy hoạch địa chỉ IPv6

IANA (2000:/3) <br>
RIPE NCC (2001:4000::/23) ARIN (2001:0400::/23)<br>
ISP (2001:41f0::/32) <br>
Customer (2001:41f0:4060::/48) <br>
LAN10 (2001:41f0:4060:10::/64) LAN20 (2001:41f0:4060:20::/64) <br>
trong đó <br>
< \-\-\-\-\-\-\- 48 bit \-\-\-\-\-\-\- >< \-\-\- 16 bit \-\-\- >< \-\-\-\-\- 64 bit \-\-\-\- > <br>
< \-\- 2001:41f0:4060 \-\- >< \-\- Subnet \-\- >< \-\- InterfaceID \-\- > <br>

### Cách đặt địa chỉ IPv6

\- <u>Gán IPv6 tĩnh</u> <br>
```
ipv6 address 2001:1234:A:B::1/64
```
\- <u>Gán IPv6 động theo EUI-64</u> <br>

```
ipv6 address 2001:1234:A:B::/64 eui-64
```

EUI-64 (Extended Unique Identifier) là một phương pháp dùng để tự động định cấu hình phần host của địa chỉ IPv6 dựa vào địa chỉ MAC. <br>
Vấn đề là MAC dài 48 bit còn host thì cần 64 bit. Giải quyết bằng cách chèn thêm cho đủ: <br>
1\. Chia đôi địa chỉ MAC <br>
2\. Chèn "FFFE" vào giữa => đủ 64 bit <br>
3\. Đảo giá trị của bit thứ 7 <br>

![alt text](/docs/CCNA/img/ipv6-eui-64.png)

\- <u>Gán IPv6 động theo SLAAC (StaLess Auto Address Configuration)</u> <br>

```
ipv6 address autoconfig
```

\-- SLAAC giống như một máy chủ "mini-DHCP" cho IPv6. <br>
\-- Các router chạy IPv6 có thể cung cấp phần Prefix & Default Gateway cho các client chạy IPv6. <br>
\-- IPv6 sử dụng NDP (Neighbor Discovery Protocol) và một trong những điều mà giao thức này cung cấp là các gói tin RS và RA giúp thiết bị tự động định cấu hình địa chỉ IPv6. <br>

\* Vấn đề của SLAAC là không thể tự động cấp IP DNS Server. Do đó cần DHCPv6. <br>

\- <u>Dùng DHCPv6</u> <br>

\-- **Stateful** khá giống IPv4. Máy chủ DHCPv6 sẽ gán địa chỉ IPv6 cho tất cả các máy khách và nó sẽ theo dõi các địa chỉ IP này. <br>
\-- **Stateless** hoạt động khác một chút... Máy chủ DHCPv6 không gán địa chỉ IPv6 cho máy khách, mà việc này sẽ được thực hiện thông qua SLAAC. Máy chủ DHCPv6 chỉ gán thông tin mà SLAAC không cấp được, như DNS Server.<br>

## IPv6 Routing

![image](/docs/CCNA/img/ipv6-routing.png)

### IPv6 Static Route

```
R1(config)#ipv6 unicast-routing 
R1(config)#ipv6 route FC00:2::/64 2001::2

R2(config)#ipv6 unicast-routing 
R2(config)#ipv6 route FC00:1::/64 2001::1
```

### IPv6 OSPF Route

* __R1__

```
R1(config)#ipv6 unicast-routing 
R1(config)#ipv6 router ospf 1
R1(config-rtr)#router-id 1.1.1.1

R1(config)#int g0/0
R1(config-if)#ipv6 ospf 1 area 0
R1(config-if)#int g0/1
R1(config-if)#ipv6 ospf 1 area 0
```

* __R1__

```
R2(config)#ipv6 unicast-routing 
R2(config)#ipv6 router ospf 1
R2(config-rtr)#router-id 2.2.2.2

R2(config)#int g0/0
R2(config-if)#ipv6 ospf 1 area 0
R2(config-if)#int g0/1
R2(config-if)#ipv6 ospf 1 area 0
```

## Chia subnet IPv6

2001:DB8::/50 chia 16

```
* Số bit mượn (n): 4
* Subnet mask mới: /54
[ ] dùng biểu diễn nhị phân
2001:0DB8:0000:[00xx xx00 0000 0000]::/54 <- x là bit mượn
* 16 mạng con:
  - 2001:DB8::/54
  - 2001:DB8:0:400::/54
  - 2001:DB8:0:800::/54
  ...
  - 2001:0DB8:0:3C00:/54
```

## Tunneling

__* 6 to 4 tunneling__ - Công nghệ sử dụng cơ sở hạ tầng mạng IPv4 để truyền tải gói tin IPv6, phục vụ cho kết nối IPv6. <br>
__* dual-stack__ - Cho phép IPv4 và IPv6 cùng tồn tại trong cùng một thiết bị mạng. <br>
__* NAT-PT (Network Address Translation-Protocol Translation)__ - Là một dạng của công nghệ NAT, cho phép thiết bị chỉ hỗ trợ IPv6 có thể giao tiếp với thiết bị chỉ hỗ trợ IPv4. <br>
