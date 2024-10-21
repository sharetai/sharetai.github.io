---
layout: default
title: Bridge Virtual Interface
nav_order: 80
parent: CCNP
---

# Bridge Virtual Interface
{: .no_toc }

Giao diện cầu nối ảo
{: .fs-6 .fw-300 }

---

## Table of contents
{: .no_toc .text-delta }

1. TOC
{:toc}

---

## Transparent Bridge (like Switch)
<br>

![alt text](/docs/CCNP/img/bvi-transparent-bridge.png)

* R1
```
! Enter config mode
enable
conf t
!
!
! Off routing
no ip routing
! On IEEE 802.1 spanning tree protocol
bridge 1 protocol ieee
!
!
! Assign port to bridge group
int range e0/1-2
no shut
no ip addr
bridge-group 1
!
!
end
```

* Verify

```
R1#show bridge

Total of 300 station blocks, 298 free
Codes: P - permanent, S - self

Bridge Group 1:

    Address       Action   Interface       Age   RX count   TX count
aabb.cc00.2000   forward   Ethernet0/1       0          5          5
aabb.cc00.3000   forward   Ethernet0/2       0          5          4
R1#

R2#ping
*Oct 19 14:30:09.068: %SYS-5-CONFIG_I: Configured from console by console
R2#ping 10.0.123.3
Type escape sequence to abort.
Sending 5, 100-byte ICMP Echos to 10.0.123.3, timeout is 2 seconds:
!!!!!
Success rate is 100 percent (5/5), round-trip min/avg/max = 1/1/1 ms
R2#
```

<br>

## CRB - Concurrent Routing and Bridging
<br>

![alt text](/docs/CCNP/img/bvi-crb.png)

* R1
```
! Enter config mode
enable
conf t
!
!
! Set mode CRB
bridge crb
! On IEEE 802.1 spanning tree protocol
bridge 1 protocol ieee
!
!
! Assign port to bridge group
int range e0/1-2
no shut
no ip addr
bridge-group 1
!
!
int e0/3
no shut
ip addr 10.0.14.1 255.255.255.0
!
!
end
```

* Verify

```
R1#show bridge

Total of 300 station blocks, 298 free
Codes: P - permanent, S - self

Bridge Group 1:

    Address       Action   Interface       Age   RX count   TX count
aabb.cc00.2000   forward   Ethernet0/1       0          5          5
aabb.cc00.3000   forward   Ethernet0/2       0          5          4
R1#

R2#ping
*Oct 19 14:30:09.068: %SYS-5-CONFIG_I: Configured from console by console
R2#ping 10.0.123.3
Type escape sequence to abort.
Sending 5, 100-byte ICMP Echos to 10.0.123.3, timeout is 2 seconds:
!!!!!
Success rate is 100 percent (5/5), round-trip min/avg/max = 1/1/1 ms
R2#

R4#ping 10.0.14.1
Type escape sequence to abort.
Sending 5, 100-byte ICMP Echos to 10.0.14.1, timeout is 2 seconds:
!!!!!
Success rate is 100 percent (5/5), round-trip min/avg/max = 1/1/1 ms
R4#
```

<br>

## IRB - Integrated Routing and Bridging
<br>

![alt text](/docs/CCNP/img/bvi-irb.png)

* R1
```
! Enter config mode
enable
conf t
!
!
! Set mode IRB
bridge irb
! On IEEE 802.1 spanning tree protocol
bridge 1 protocol ieee
! On route ip
bridge 1 route ip
!
!
! Assign port to bridge group
int range e0/1-2
no shut
no ip addr
bridge-group 1
!
!
int bvi 1
no shut
ip addr 10.0.123.1 255.255.255.0
!
!
int e0/3
no shut
ip addr 10.0.14.1 255.255.255.0
!
!
end
```

* Verify

```
R1#show bridge

Total of 300 station blocks, 298 free
Codes: P - permanent, S - self

Bridge Group 1:

    Address       Action   Interface       Age   RX count   TX count
aabb.cc00.2000   forward   Ethernet0/1       0         35         25
aabb.cc00.3000   forward   Ethernet0/2       0         19         14
R1#show ip int bri
Interface                  IP-Address      OK? Method Status                Protocol
Ethernet0/0                unassigned      YES manual administratively down down
Ethernet0/1                unassigned      YES manual up                    up
Ethernet0/2                unassigned      YES manual up                    up
Ethernet0/3                10.0.14.1       YES manual up                    up
BVI1                       10.0.123.1      YES manual up                    up
R1#

R2#ping 10.0.123.3
Type escape sequence to abort.
Sending 5, 100-byte ICMP Echos to 10.0.123.3, timeout is 2 seconds:
!!!!!
Success rate is 100 percent (5/5), round-trip min/avg/max = 1/1/1 ms
R2#ping 10.0.123.1
Type escape sequence to abort.
Sending 5, 100-byte ICMP Echos to 10.0.123.1, timeout is 2 seconds:
!!!!!
Success rate is 100 percent (5/5), round-trip min/avg/max = 1/1/1 ms
R2#ping 10.0.14.4
Type escape sequence to abort.
Sending 5, 100-byte ICMP Echos to 10.0.14.4, timeout is 2 seconds:
!!!!!
Success rate is 100 percent (5/5), round-trip min/avg/max = 1/1/1 ms
R2#
```

<br>
