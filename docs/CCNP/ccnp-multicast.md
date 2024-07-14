---
layout: default
title: Multicast
nav_order: 100
parent: CCNP
---

# Multicast
{: .no_toc }

Truyền thông Multicast
{: .fs-6 .fw-300 }

---

## Table of contents
{: .no_toc .text-delta }

1. TOC
{:toc}

---

![Alt text](/docs/CCNP/img/multicast-0.png)

## OSPF

* R1
```conf
interface Loopback0
 ip address 1.1.1.1 255.255.255.255
!
interface Ethernet0/0
 ip address 10.0.12.1 255.255.255.0
 ip ospf network point-to-point
 ip ospf 1 area 0
!
interface Ethernet0/1
 ip address 10.0.13.1 255.255.255.0
 ip ospf network point-to-point
 ip ospf 1 area 0
!
router ospf 1
 router-id 1.1.1.1
 network 1.1.1.1 0.0.0.0 area 0
!
```

* R2
```conf
interface Loopback0
 ip address 2.2.2.2 255.255.255.255
!
interface Ethernet0/0
 ip address 10.0.23.2 255.255.255.0
 ip ospf network point-to-point
 ip ospf 1 area 0
!
interface Ethernet0/1
 ip address 10.0.12.2 255.255.255.0
 ip ospf network point-to-point
 ip ospf 1 area 0
!
router ospf 1
 router-id 2.2.2.2
 network 2.2.2.2 0.0.0.0 area 0
!
```

* R3
```conf
interface Loopback0
 ip address 3.3.3.3 255.255.255.255
!
interface Ethernet0/0
 ip address 10.0.13.3 255.255.255.0
 ip ospf network point-to-point
 ip ospf 1 area 0
!
interface Ethernet0/1
 ip address 10.0.23.3 255.255.255.0
 ip ospf network point-to-point
 ip ospf 1 area 0
!
interface Ethernet0/2
 ip address 10.0.34.3 255.255.255.0
 ip ospf network point-to-point
 ip ospf 1 area 0
!
router ospf 1
 router-id 3.3.3.3
 network 3.3.3.3 0.0.0.0 area 0
!
```

* R4
```conf
interface Loopback0
 ip address 4.4.4.4 255.255.255.255
!
interface Ethernet0/0
 ip address 10.0.34.4 255.255.255.0
 ip ospf network point-to-point
 ip ospf 1 area 0
!
interface Ethernet0/1
 ip address 192.168.1.1 255.255.255.0
 ip ospf network point-to-point
 ip ospf 1 area 0
!
router ospf 1
 router-id 4.4.4.4
 network 4.4.4.4 0.0.0.0 area 0
!
```

Verify

```conf
R1#sh ip ospf nei

Neighbor ID     Pri   State           Dead Time   Address         Interface
3.3.3.3           0   FULL/  -        00:00:36    10.0.13.3       Ethernet0/1
2.2.2.2           0   FULL/  -        00:00:31    10.0.12.2       Ethernet0/0
R1#sh ip route ospf
Codes: L - local, C - connected, S - static, R - RIP, M - mobile, B - BGP
       D - EIGRP, EX - EIGRP external, O - OSPF, IA - OSPF inter area
       N1 - OSPF NSSA external type 1, N2 - OSPF NSSA external type 2
       E1 - OSPF external type 1, E2 - OSPF external type 2
       i - IS-IS, su - IS-IS summary, L1 - IS-IS level-1, L2 - IS-IS level-2
       ia - IS-IS inter area, * - candidate default, U - per-user static route
       o - ODR, P - periodic downloaded static route, H - NHRP, l - LISP
       a - application route
       + - replicated route, % - next hop override, p - overrides from PfR

Gateway of last resort is not set

      2.0.0.0/32 is subnetted, 1 subnets
O        2.2.2.2 [110/11] via 10.0.12.2, 00:37:59, Ethernet0/0
      3.0.0.0/32 is subnetted, 1 subnets
O        3.3.3.3 [110/11] via 10.0.13.3, 00:37:59, Ethernet0/1
      4.0.0.0/32 is subnetted, 1 subnets
O        4.4.4.4 [110/21] via 10.0.13.3, 00:12:08, Ethernet0/1
      10.0.0.0/8 is variably subnetted, 7 subnets, 2 masks
O        10.0.23.0/24 [110/20] via 10.0.13.3, 00:37:59, Ethernet0/1
                      [110/20] via 10.0.12.2, 00:37:59, Ethernet0/0
O        10.0.34.0/24 [110/20] via 10.0.13.3, 00:37:59, Ethernet0/1
O        10.0.40.0/24 [110/30] via 10.0.13.3, 00:06:09, Ethernet0/1
R1#ping 4.4.4.4
Type escape sequence to abort.
Sending 5, 100-byte ICMP Echos to 4.4.4.4, timeout is 2 seconds:
!!!!!
Success rate is 100 percent (5/5), round-trip min/avg/max = 1/1/1 ms
R1#
```

## PIM Sparse-mode

* R1/2
```conf
interface Ethernet0/0
 ip pim sparse-mode
!
interface Ethernet0/1
 ip pim sparse-mode
!
```

* R3
```conf
interface Ethernet0/0
 ip pim sparse-mode
!
interface Ethernet0/1
 ip pim sparse-mode
!
interface Ethernet0/2
 ip pim sparse-mode
!
```

* R4
```conf
interface Ethernet0/0
 ip pim sparse-mode
!
interface Ethernet0/1
 ip pim sparse-mode
!
```

## IGMP join-group

* R4
```conf
interface Ethernet0/1
 ip igmp join-group 224.6.6.6
!
```

## PIM Static RP

![Alt text](/docs/CCNP/img/multicast-1.png)

* R1/2/3/4
```conf
en
conf t
ip pim rp-address 2.2.2.2
end
```

Verify

```conf
R4#show ip igmp groups
IGMP Connected Group Membership
Group Address    Interface                Uptime    Expires   Last Reporter   Group Accounted
224.6.6.6        Ethernet0/1              00:37:53  00:02:54  10.0.40.4
224.0.1.40       Ethernet0/0              00:37:53  00:02:50  10.0.34.4
R4#

R1#show ip mroute
IP Multicast Routing Table
Flags: D - Dense, S - Sparse, B - Bidir Group, s - SSM Group, C - Connected,
       L - Local, P - Pruned, R - RP-bit set, F - Register flag,
       T - SPT-bit set, J - Join SPT, M - MSDP created entry, E - Extranet,
       X - Proxy Join Timer Running, A - Candidate for MSDP Advertisement,
       U - URD, I - Received Source Specific Host Report,
       Z - Multicast Tunnel, z - MDT-data group sender,
       Y - Joined MDT-data group, y - Sending to MDT-data group,
       G - Received BGP C-Mroute, g - Sent BGP C-Mroute,
       N - Received BGP Shared-Tree Prune, n - BGP C-Mroute suppressed,
       Q - Received BGP S-A Route, q - Sent BGP S-A Route,
       V - RD & Vector, v - Vector, p - PIM Joins on route,
       x - VxLAN group
Outgoing interface flags: H - Hardware switched, A - Assert winner, p - PIM Join
 Timers: Uptime/Expires
 Interface state: Interface, Next-Hop or VCD, State/Mode

(*, 224.6.6.6), 00:01:53/stopped, RP 3.3.3.3, flags: SP
  Incoming interface: Ethernet0/1, RPF nbr 10.0.13.3
  Outgoing interface list: Null

(10.0.12.1, 224.6.6.6), 00:01:53/00:01:26, flags: PT
  Incoming interface: Ethernet0/0, RPF nbr 0.0.0.0
  Outgoing interface list: Null

(10.0.13.1, 224.6.6.6), 00:01:53/00:01:26, flags: PT
  Incoming interface: Ethernet0/1, RPF nbr 0.0.0.0
  Outgoing interface list: Null

(*, 224.0.1.40), 00:58:27/00:02:43, RP 3.3.3.3, flags: SJPL
  Incoming interface: Ethernet0/1, RPF nbr 10.0.13.3
  Outgoing interface list: Null

R1#show ip pim rp mapping
PIM Group-to-RP Mappings

Group(s): 224.0.0.0/4, Static
    RP: 3.3.3.3 (?)
R1#ping 224.6.6.6
Type escape sequence to abort.
Sending 1, 100-byte ICMP Echos to 224.6.6.6, timeout is 2 seconds:

Reply to request 0 from 10.0.40.4, 1 ms
Reply to request 0 from 10.0.40.4, 1 ms
R1#ping 224.6.6.6
Type escape sequence to abort.
Sending 1, 100-byte ICMP Echos to 224.6.6.6, timeout is 2 seconds:

Reply to request 0 from 10.0.40.4, 1 ms
Reply to request 0 from 10.0.40.4, 6 ms
R1#
```

## PIM Auto RP

![Alt text](/docs/CCNP/img/multicast-2.png)

* R1 (RP candidate - Ứng viên sẽ làm RP)
```conf
en
conf t
ip pim send-rp-announce lo0 scope 5
end
```

* R2 (Mapping Agent)
```conf
en
conf t
ip pim send-rp-discovery lo0 scope 5
end
```

* R3 (RP candidate - Ứng viên sẽ làm RP)
```conf
en
conf t
ip pim send-rp-announce lo0 scope 5
ip pim autorp listener
end
```

Verify

```conf
R1#show ip pim rp mapping
PIM Group-to-RP Mappings
This system is an RP (Auto-RP)

Group(s) 224.0.0.0/4
  RP 3.3.3.3 (?), v2v1
    Info source: 2.2.2.2 (?), elected via Auto-RP
         Uptime: 00:02:48, expires: 00:02:06
R1#ping 224.6.6.6
Type escape sequence to abort.
Sending 1, 100-byte ICMP Echos to 224.6.6.6, timeout is 2 seconds:

Reply to request 0 from 10.0.40.4, 2 ms
Reply to request 0 from 10.0.40.4, 2 ms
Reply to request 0 from 10.0.40.4, 2 ms
R1#

R2#show ip pim rp mapping
PIM Group-to-RP Mappings
This system is an RP-mapping agent (Loopback0)

Group(s) 224.0.0.0/4
  RP 3.3.3.3 (?), v2v1
    Info source: 3.3.3.3 (?), elected via Auto-RP
         Uptime: 00:02:55, expires: 00:02:01
  RP 1.1.1.1 (?), v2v1
    Info source: 1.1.1.1 (?), via Auto-RP
         Uptime: 00:02:35, expires: 00:02:24
R2#
```

## PIM BSR

![Alt text](/docs/CCNP/img/multicast-3.png)

* R1 (RP candidate - Ứng viên sẽ làm RP)
```conf
en
conf t
ip pim rp-candidate lo0
end
```

* R2 (BSR - Thiết bị sẽ chọn RP)
```conf
en
conf t
ip pim bsr-candidate lo0
end
```

* R3 (RP candidate - Ứng viên sẽ làm RP)
```conf
en
conf t
ip pim rp-candidate lo0
end
```

Verify

```conf
R1#show ip pim bsr-router
PIMv2 Bootstrap information
  BSR address: 2.2.2.2 (?)
  Uptime:      00:04:29, BSR Priority: 0, Hash mask length: 0
  Expires:     00:01:43
  Candidate RP: 1.1.1.1(Loopback0)
    Holdtime 150 seconds
    Advertisement interval 60 seconds
    Next advertisement in 00:00:32
R1#show ip pim rp-hash 224.6.6.6
  RP 3.3.3.3 (?), v2
    Info source: 2.2.2.2 (?), via bootstrap, priority 0, holdtime 150
         Uptime: 00:04:39, expires: 00:01:47
  PIMv2 Hash Value (mask 0.0.0.0)
    RP 3.3.3.3, via bootstrap, priority 0, hash value 450145259
    RP 1.1.1.1, via bootstrap, priority 0, hash value 332477713
R1#show ip pim rp mapping
PIM Group-to-RP Mappings
This system is a candidate RP (v2)

Group(s) 224.0.0.0/4
  RP 3.3.3.3 (?), v2
    Info source: 2.2.2.2 (?), via bootstrap, priority 0, holdtime 150
         Uptime: 00:04:49, expires: 00:01:38
  RP 1.1.1.1 (?), v2
    Info source: 2.2.2.2 (?), via bootstrap, priority 0, holdtime 150
         Uptime: 00:04:49, expires: 00:01:41
R1#ping 224.6.6.6
Type escape sequence to abort.
Sending 1, 100-byte ICMP Echos to 224.6.6.6, timeout is 2 seconds:

Reply to request 0 from 10.0.40.4, 2 ms
Reply to request 0 from 10.0.40.4, 30 ms
Reply to request 0 from 10.0.40.4, 30 ms
R1#
```


