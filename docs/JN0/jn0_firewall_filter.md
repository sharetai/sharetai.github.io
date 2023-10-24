---
layout: default
title: Firewall Filter
nav_order: 8
parent: JN0
---

# Firewall Filter
{: .no_toc }

Bộ lọc tưởng lửa
{: .fs-6 .fw-300 }

---

## Table of contents
{: .no_toc .text-delta }

1. TOC
{:toc}

---

## Chuẩn bị

![](/docs/JN0/img/6.png)

```
# vMX1
set interfaces lo0 unit 0 family inet address 1.1.1.1/32
set interfaces ge-0/0/0 unit 0 family inet address 10.0.12.1/29
set routing-options static route 2.2.2.2/32 next-hop 10.0.12.2

# vMX2
set interfaces lo0 unit 0 family inet address 2.2.2.2/32
set interfaces ge-0/0/1 unit 0 family inet address 10.0.12.2/29
set routing-options static route 1.1.1.1/32 next-hop 10.0.12.1
set system login user lab class super-user authentication plain-text-password
set system services telnet
```

## Định nghĩa Firewall Filter

```
# vMX1
set firewall family inet filter input-ff term deny-icmp from protocol icmp
set firewall family inet filter input-ff term deny-icmp then reject
set firewall family inet filter input-ff term permit-other then accept
```

## Áp Firewall Filter

```
# vMX1
set interfaces ge-0/0/0 unit 0 family inet filter input input-ff
```

## Kiểm tra

```
# Trước khi áp firewall filter

root@vMX1# run ping rapid 2.2.2.2 source 1.1.1.1
PING 2.2.2.2 (2.2.2.2): 56 data bytes
!!!!!
--- 2.2.2.2 ping statistics ---
5 packets transmitted, 5 packets received, 0% packet loss
round-trip min/avg/max/stddev = 1.292/2.551/5.973/1.736 ms

# Sau khi áp firewall filter

root@vMX1# run ping rapid 2.2.2.2 source 1.1.1.1
PING 2.2.2.2 (2.2.2.2): 56 data bytes
.....
--- 2.2.2.2 ping statistics ---
5 packets transmitted, 0 packets received, 100% packet loss

# Kiểm tra giao thức khác (như Telnet) vẫn hoạt động

root@vMX1# run telnet 2.2.2.2
Trying 2.2.2.2...
Connected to 2.2.2.2.
Escape character is '^]'.

vMX2 (ttyp0)

login:

```

