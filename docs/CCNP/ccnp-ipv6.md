---
layout: default
title: IPv6
nav_order: 50
parent: CCNP
---

# Internet Protocol version 6
{: .no_toc }

Giao thức liên mạng thế hệ 6
{: .fs-6 .fw-300 }

---

## Table of contents
{: .no_toc .text-delta }

1. TOC
{:toc}

---


## Cấu hình định tuyến trên IPv6
<br>

![alt text](/docs/CCNP/img/ipv6-routing.png)

__<u>Init</u>__

* __R1__
```
en
conf t
no ip domain-lookup
host R1
int lo0
ipv6 address 2001::1/64
int e0/0
ipv6 address 2012::1/64
no shut
end
```

* __R2__
```
en
conf t
no ip domain-lookup
host R2
int lo0
ipv6 address 2002::2/64
int e0/1
ipv6 address 2012::2/64
no shut
int e0/0
ipv6 address 2023::2/64
no shut
end
```

* __R3__
```
en
conf t
no ip domain-lookup
host R3
int lo0
ipv6 address 2003::3/64
int e0/1
ipv6 address 2023::3/64
no shut
int e0/0
ipv6 address 2034::3/64
no shut
end
```

* __R4__
```
en
conf t
no ip domain-lookup
host R4
int lo0
ipv6 address 2004::4/64
int e0/1
ipv6 address 2034::4/64
no shut
int e0/0
ipv6 address 2045::4/64
no shut
end
```

* __R5__
```
en
conf t
no ip domain-lookup
host R5
int lo0
ipv6 address 2005::5/64
int e0/1
ipv6 address 2045::5/64
no shut
int e0/0
ipv6 address 2056::5/64
no shut
end
```

* __R6__
```
en
conf t
no ip domain-lookup
host R6
int lo0
ipv6 address 2006::6/64
int e0/1
ipv6 address 2056::6/64
no shut
end
```

__<u>Static</u>__

* __R1__
```
en
conf t
ipv6 unicast-routing
ipv6 route 2002::2/64 2012::2
end
```

* __R2__
```
en
conf t
ipv6 unicast-routing
ipv6 route 2001::1/64 2012::1
end
```

* __Verify__

```
R1#sh ipv6 route static
IPv6 Routing Table - default - 6 entries
Codes: C - Connected, L - Local, S - Static, U - Per-user Static route
       B - BGP, HA - Home Agent, MR - Mobile Router, R - RIP
       H - NHRP, I1 - ISIS L1, I2 - ISIS L2, IA - ISIS interarea
       IS - ISIS summary, D - EIGRP, EX - EIGRP external, NM - NEMO
       ND - ND Default, NDp - ND Prefix, DCE - Destination, NDr - Redirect
       RL - RPL, O - OSPF Intra, OI - OSPF Inter, OE1 - OSPF ext 1
       OE2 - OSPF ext 2, ON1 - OSPF NSSA ext 1, ON2 - OSPF NSSA ext 2
       la - LISP alt, lr - LISP site-registrations, ld - LISP dyn-eid
       lA - LISP away, a - Application
S   2002::/64 [1/0]
     via 2012::2
R1#ping 2002::2
Type escape sequence to abort.
Sending 5, 100-byte ICMP Echos to 2002::2, timeout is 2 seconds:
!!!!!
Success rate is 100 percent (5/5), round-trip min/avg/max = 4/4/5 ms
R1#
```

__<u>RIPng</u>__

* __R2__
```
en
conf t
ipv6 unicast-routing
ipv6 router rip R2
int lo0
ipv6 rip R2 enable
int e0/0
ipv6 rip R2 enable
end
```

* __R3__
```
en
conf t
ipv6 unicast-routing
ipv6 router rip R3
int lo0
ipv6 rip R3 enable
int e0/1
ipv6 rip R3 enable
end
```

* __Verify__

```
R2#sh ipv6 protocols | sec rip
IPv6 Routing Protocol is "rip R2"
  Interfaces:
    Ethernet0/0
    Loopback0
  Redistribution:
    None
R2#sh ipv6 rip database
RIP process "R2", local RIB
 2003::/64, metric 2, installed
     Ethernet0/0/FE80::A8BB:CCFF:FE00:3010, expires in 156 secs
 2023::/64, metric 2
     Ethernet0/0/FE80::A8BB:CCFF:FE00:3010, expires in 156 secs
R2#sh ipv6 route rip
IPv6 Routing Table - default - 9 entries
Codes: C - Connected, L - Local, S - Static, U - Per-user Static route
       B - BGP, HA - Home Agent, MR - Mobile Router, R - RIP
       H - NHRP, I1 - ISIS L1, I2 - ISIS L2, IA - ISIS interarea
       IS - ISIS summary, D - EIGRP, EX - EIGRP external, NM - NEMO
       ND - ND Default, NDp - ND Prefix, DCE - Destination, NDr - Redirect
       RL - RPL, O - OSPF Intra, OI - OSPF Inter, OE1 - OSPF ext 1
       OE2 - OSPF ext 2, ON1 - OSPF NSSA ext 1, ON2 - OSPF NSSA ext 2
       la - LISP alt, lr - LISP site-registrations, ld - LISP dyn-eid
       lA - LISP away, a - Application
R   2003::/64 [120/2]
     via FE80::A8BB:CCFF:FE00:3010, Ethernet0/0
R2#ping ipv6 2003::3
Type escape sequence to abort.
Sending 5, 100-byte ICMP Echos to 2003::3, timeout is 2 seconds:
!!!!!
Success rate is 100 percent (5/5), round-trip min/avg/max = 1/4/19 ms
R2#
```

__<u>EIGRP</u>__

* __R3__
```
en
conf t
ipv6 unicast-routing
ipv6 router eigrp 34
eigrp router-id 3.3.3.3
int lo0
ipv6 eigrp 34
int e0/0
ipv6 eigrp 34
end
```

* __R4__
```
en
conf t
ipv6 unicast-routing
ipv6 router eigrp 34
eigrp router-id 4.4.4.4
int lo0
ipv6 eigrp 34
int e0/1
ipv6 eigrp 34
end
```

* __Verify__

```
R3#sh ipv6 protocols
IPv6 Routing Protocol is "connected"
IPv6 Routing Protocol is "application"
IPv6 Routing Protocol is "ND"
IPv6 Routing Protocol is "rip R3"
  Interfaces:
    Ethernet0/1
    Loopback0
  Redistribution:
    None
IPv6 Routing Protocol is "eigrp 34"
EIGRP-IPv6 Protocol for AS(34)
  Metric weight K1=1, K2=0, K3=1, K4=0, K5=0
  Soft SIA disabled
  NSF-aware route hold timer is 240
  Router-ID: 3.3.3.3
  Topology : 0 (base)
    Active Timer: 3 min
    Distance: internal 90 external 170
    Maximum path: 16
    Maximum hopcount 100
    Maximum metric variance 1

  Interfaces:
    Ethernet0/0
    Loopback0
  Redistribution:
    None
R3#sh ipv6 eigrp interfaces
EIGRP-IPv6 Interfaces for AS(34)
                              Xmit Queue   PeerQ        Mean   Pacing Time   Multicast    Pending
Interface              Peers  Un/Reliable  Un/Reliable  SRTT   Un/Reliable   Flow Timer   Routes
Et0/0                    1        0/0       0/0           9       0/2           50           0
Lo0                      0        0/0       0/0           0       0/0            0           0
R3#sh ipv6 eigrp neighbors
EIGRP-IPv6 Neighbors for AS(34)
H   Address                 Interface              Hold Uptime   SRTT   RTO  Q  Seq
                                                   (sec)         (ms)       Cnt Num
0   Link-local address:     Et0/0                    14 00:03:05    9   100  0  3
    FE80::A8BB:CCFF:FE00:4010
R3#sh ipv6 eigrp topology
EIGRP-IPv6 Topology Table for AS(34)/ID(3.3.3.3)
Codes: P - Passive, A - Active, U - Update, Q - Query, R - Reply,
       r - reply Status, s - sia Status

P 2004::/64, 1 successors, FD is 409600
        via FE80::A8BB:CCFF:FE00:4010 (409600/128256), Ethernet0/0
P 2003::/64, 1 successors, FD is 128256
        via Connected, Loopback0
P 2034::/64, 1 successors, FD is 281600
        via Connected, Ethernet0/0

R3#sh ipv6 route eigrp
IPv6 Routing Table - default - 9 entries
Codes: C - Connected, L - Local, S - Static, U - Per-user Static route
       B - BGP, HA - Home Agent, MR - Mobile Router, R - RIP
       H - NHRP, I1 - ISIS L1, I2 - ISIS L2, IA - ISIS interarea
       IS - ISIS summary, D - EIGRP, EX - EIGRP external, NM - NEMO
       ND - ND Default, NDp - ND Prefix, DCE - Destination, NDr - Redirect
       RL - RPL, O - OSPF Intra, OI - OSPF Inter, OE1 - OSPF ext 1
       OE2 - OSPF ext 2, ON1 - OSPF NSSA ext 1, ON2 - OSPF NSSA ext 2
       la - LISP alt, lr - LISP site-registrations, ld - LISP dyn-eid
       lA - LISP away, a - Application
D   2004::/64 [90/409600]
     via FE80::A8BB:CCFF:FE00:4010, Ethernet0/0
R3#ping 2004::4
Type escape sequence to abort.
Sending 5, 100-byte ICMP Echos to 2004::4, timeout is 2 seconds:
!!!!!
Success rate is 100 percent (5/5), round-trip min/avg/max = 1/4/19 ms
R3#
```

__<u>OSPFv3</u>__

* __R4__
```
en
conf t
ipv6 unicast-routing
ipv6 router ospf 4
router-id 4.4.4.4
int lo0
ipv6 ospf 4 area 0
ipv6 ospf network point-to-point
int e0/0
ipv6 ospf 4 area 0
ipv6 ospf network point-to-point
end
```

* __R5__
```
en
conf t
ipv6 unicast-routing
ipv6 router ospf 5
router-id 5.5.5.5
int lo0
ipv6 ospf 5 area 0
ipv6 ospf network point-to-point
int e0/1
ipv6 ospf 5 area 0
ipv6 ospf network point-to-point
end
```

* __Verify__

```
R4#sh ipv6 protocols | sec ospf
IPv6 Routing Protocol is "ospf 4"
  Router ID 4.4.4.4
  Number of areas: 1 normal, 0 stub, 0 nssa
  Interfaces (Area 0):
    Loopback0
    Ethernet0/0
  Redistribution:
    None
R4#sh ipv6 ospf interface brief
Interface    PID   Area            Intf ID    Cost  State Nbrs F/C
Lo0          4     0               10         1     P2P   0/0
Et0/0        4     0               3          10    P2P   1/1
R4#sh ipv6 ospf neighbor

            OSPFv3 Router with ID (4.4.4.4) (Process ID 4)

Neighbor ID     Pri   State           Dead Time   Interface ID    Interface
5.5.5.5           0   FULL/  -        00:00:37    4               Ethernet0/0
R4#sh ipv6 route ospf
IPv6 Routing Table - default - 9 entries
Codes: C - Connected, L - Local, S - Static, U - Per-user Static route
       B - BGP, HA - Home Agent, MR - Mobile Router, R - RIP
       H - NHRP, I1 - ISIS L1, I2 - ISIS L2, IA - ISIS interarea
       IS - ISIS summary, D - EIGRP, EX - EIGRP external, NM - NEMO
       ND - ND Default, NDp - ND Prefix, DCE - Destination, NDr - Redirect
       RL - RPL, O - OSPF Intra, OI - OSPF Inter, OE1 - OSPF ext 1
       OE2 - OSPF ext 2, ON1 - OSPF NSSA ext 1, ON2 - OSPF NSSA ext 2
       la - LISP alt, lr - LISP site-registrations, ld - LISP dyn-eid
       lA - LISP away, a - Application
O   2005::/64 [110/11]
     via FE80::A8BB:CCFF:FE00:5010, Ethernet0/0
R4#ping 2005::5
Type escape sequence to abort.
Sending 5, 100-byte ICMP Echos to 2005::5, timeout is 2 seconds:
!!!!!
Success rate is 100 percent (5/5), round-trip min/avg/max = 1/6/18 ms
R4#
```

__<u>BGP</u>__

* __R5__
```
en
conf t
ipv6 unicast-routing
router bgp 56
bgp router-id 5.5.5.5
neighbor 2056::6 remote-as 56
address-family ipv6 unicast
neighbor 2056::6 activate
end
```

* __R6__
```
en
conf t
ipv6 unicast-routing
router bgp 56
bgp router-id 6.6.6.6
neighbor 2056::5 remote-as 56
address-family ipv6 unicast
neighbor 2056::5 activate
network 2006::/64
end
```

* __Verify__

```
R5#sh ipv6 protocols | sec bgp
IPv6 Routing Protocol is "bgp 56"
  IGP synchronization is disabled
  Redistribution:
    None
  Neighbor(s):
    Address                    FiltIn FiltOut Weight RoutemapIn RoutemapOut
    2056::6
  Distance:
R5#sh bgp ipv6 unicast summary
BGP router identifier 5.5.5.5, local AS number 56
BGP table version is 2, main routing table version 2
1 network entries using 168 bytes of memory
1 path entries using 108 bytes of memory
1/1 BGP path/bestpath attribute entries using 160 bytes of memory
0 BGP route-map cache entries using 0 bytes of memory
0 BGP filter-list cache entries using 0 bytes of memory
BGP using 436 total bytes of memory
BGP activity 1/0 prefixes, 1/0 paths, scan interval 60 secs

Neighbor        V           AS MsgRcvd MsgSent   TblVer  InQ OutQ Up/Down  State/PfxRcd
2056::6         4           56      12      12        2    0    0 00:07:53        1
R5#sh bgp ipv6 unicast
BGP table version is 2, local router ID is 5.5.5.5
Status codes: s suppressed, d damped, h history, * valid, > best, i - internal,
              r RIB-failure, S Stale, m multipath, b backup-path, f RT-Filter,
              x best-external, a additional-path, c RIB-compressed,
              t secondary path,
Origin codes: i - IGP, e - EGP, ? - incomplete
RPKI validation codes: V valid, I invalid, N Not found

     Network          Next Hop            Metric LocPrf Weight Path
 *>i  2006::/64        2056::6                  0    100      0 i
R5#sh ipv6 route bgp
IPv6 Routing Table - default - 9 entries
Codes: C - Connected, L - Local, S - Static, U - Per-user Static route
       B - BGP, HA - Home Agent, MR - Mobile Router, R - RIP
       H - NHRP, I1 - ISIS L1, I2 - ISIS L2, IA - ISIS interarea
       IS - ISIS summary, D - EIGRP, EX - EIGRP external, NM - NEMO
       ND - ND Default, NDp - ND Prefix, DCE - Destination, NDr - Redirect
       RL - RPL, O - OSPF Intra, OI - OSPF Inter, OE1 - OSPF ext 1
       OE2 - OSPF ext 2, ON1 - OSPF NSSA ext 1, ON2 - OSPF NSSA ext 2
       la - LISP alt, lr - LISP site-registrations, ld - LISP dyn-eid
       lA - LISP away, a - Application
B   2006::/64 [200/0]
     via 2056::6
R5#ping 2006::6
Type escape sequence to abort.
Sending 5, 100-byte ICMP Echos to 2006::6, timeout is 2 seconds:
!!!!!
Success rate is 100 percent (5/5), round-trip min/avg/max = 1/1/1 ms
R5#
```

__<u>Redistribute Staic to RIPng</u>__

* __R1__
```
en
conf t
ipv6 route ::/0 2012::2
end
```

* __R2__
```
en
conf t
ipv6 router rip R2
redistribute static
end
```

* __Verify__

```
R3#sh ipv6 route rip
IPv6 Routing Table - default - 10 entries
Codes: C - Connected, L - Local, S - Static, U - Per-user Static route
       B - BGP, HA - Home Agent, MR - Mobile Router, R - RIP
       H - NHRP, I1 - ISIS L1, I2 - ISIS L2, IA - ISIS interarea
       IS - ISIS summary, D - EIGRP, EX - EIGRP external, NM - NEMO
       ND - ND Default, NDp - ND Prefix, DCE - Destination, NDr - Redirect
       RL - RPL, O - OSPF Intra, OI - OSPF Inter, OE1 - OSPF ext 1
       OE2 - OSPF ext 2, ON1 - OSPF NSSA ext 1, ON2 - OSPF NSSA ext 2
       la - LISP alt, lr - LISP site-registrations, ld - LISP dyn-eid
       lA - LISP away, a - Application
R   2001::/64 [120/2]
     via FE80::A8BB:CCFF:FE00:2000, Ethernet0/1
R   2002::/64 [120/2]
     via FE80::A8BB:CCFF:FE00:2000, Ethernet0/1
R3#ping 2001::1 source 2003::3
Type escape sequence to abort.
Sending 5, 100-byte ICMP Echos to 2001::1, timeout is 2 seconds:
Packet sent with a source address of 2003::3
!!!!!
Success rate is 100 percent (5/5), round-trip min/avg/max = 1/1/1 ms
R3#
```

__<u>Redistribute EIGRP to RIPng</u>__

* __R3__
```
en
conf t
ipv6 router rip R3
redistribute eigrp 34 metric 1
end
```

* __Verify__

```
R2#sh ipv6 route rip
IPv6 Routing Table - default - 10 entries
Codes: C - Connected, L - Local, S - Static, U - Per-user Static route
       B - BGP, HA - Home Agent, MR - Mobile Router, R - RIP
       H - NHRP, I1 - ISIS L1, I2 - ISIS L2, IA - ISIS interarea
       IS - ISIS summary, D - EIGRP, EX - EIGRP external, NM - NEMO
       ND - ND Default, NDp - ND Prefix, DCE - Destination, NDr - Redirect
       RL - RPL, O - OSPF Intra, OI - OSPF Inter, OE1 - OSPF ext 1
       OE2 - OSPF ext 2, ON1 - OSPF NSSA ext 1, ON2 - OSPF NSSA ext 2
       la - LISP alt, lr - LISP site-registrations, ld - LISP dyn-eid
       lA - LISP away, a - Application
R   2003::/64 [120/2]
     via FE80::A8BB:CCFF:FE00:3010, Ethernet0/0
R   2004::/64 [120/2]
     via FE80::A8BB:CCFF:FE00:3010, Ethernet0/0
R2#
```

__<u>Redistribute RIPng to EIGRP</u>__

* __R3__
```
en
conf t
ipv6 router eigrp 34
redistribute rip R3 metric 1 0 1 1 1
end
```

* __Verify__

```
R4#sh ipv6 route eigrp
IPv6 Routing Table - default - 11 entries
Codes: C - Connected, L - Local, S - Static, U - Per-user Static route
       B - BGP, HA - Home Agent, MR - Mobile Router, R - RIP
       H - NHRP, I1 - ISIS L1, I2 - ISIS L2, IA - ISIS interarea
       IS - ISIS summary, D - EIGRP, EX - EIGRP external, NM - NEMO
       ND - ND Default, NDp - ND Prefix, DCE - Destination, NDr - Redirect
       RL - RPL, O - OSPF Intra, OI - OSPF Inter, OE1 - OSPF ext 1
       OE2 - OSPF ext 2, ON1 - OSPF NSSA ext 1, ON2 - OSPF NSSA ext 2
       la - LISP alt, lr - LISP site-registrations, ld - LISP dyn-eid
       lA - LISP away, a - Application
EX  2001::/64 [170/2560025600]
     via FE80::A8BB:CCFF:FE00:3000, Ethernet0/1
EX  2002::/64 [170/2560025600]
     via FE80::A8BB:CCFF:FE00:3000, Ethernet0/1
D   2003::/64 [90/409600]
     via FE80::A8BB:CCFF:FE00:3000, Ethernet0/1
R4#ping 2001::1 source 2004::4
Type escape sequence to abort.
Sending 5, 100-byte ICMP Echos to 2001::1, timeout is 2 seconds:
Packet sent with a source address of 2004::4
!!!!!
Success rate is 100 percent (5/5), round-trip min/avg/max = 1/1/1 ms
R4#
```

__<u>Redistribute OSPFv3 to EIGRP</u>__

* __R4__
```
en
conf t
ipv6 router eigrp 34
redistribute ospf 4 metric 1 0 1 1 1
end
```

* __Verify__

```
R3#sh ipv6 route eigrp
IPv6 Routing Table - default - 11 entries
Codes: C - Connected, L - Local, S - Static, U - Per-user Static route
       B - BGP, HA - Home Agent, MR - Mobile Router, R - RIP
       H - NHRP, I1 - ISIS L1, I2 - ISIS L2, IA - ISIS interarea
       IS - ISIS summary, D - EIGRP, EX - EIGRP external, NM - NEMO
       ND - ND Default, NDp - ND Prefix, DCE - Destination, NDr - Redirect
       RL - RPL, O - OSPF Intra, OI - OSPF Inter, OE1 - OSPF ext 1
       OE2 - OSPF ext 2, ON1 - OSPF NSSA ext 1, ON2 - OSPF NSSA ext 2
       la - LISP alt, lr - LISP site-registrations, ld - LISP dyn-eid
       lA - LISP away, a - Application
D   2004::/64 [90/409600]
     via FE80::A8BB:CCFF:FE00:4010, Ethernet0/0
EX  2005::/64 [170/2560025600]
     via FE80::A8BB:CCFF:FE00:4010, Ethernet0/0
R3#
```

__<u>Redistribute EIGRP to OSPFv3</u>__

* __R4__
```
en
conf t
ipv6 router ospf 4
redistribute eigrp 34
end
```

* __Verify__

```
R5#sh ipv6 route ospf
IPv6 Routing Table - default - 12 entries
Codes: C - Connected, L - Local, S - Static, U - Per-user Static route
       B - BGP, HA - Home Agent, MR - Mobile Router, R - RIP
       H - NHRP, I1 - ISIS L1, I2 - ISIS L2, IA - ISIS interarea
       IS - ISIS summary, D - EIGRP, EX - EIGRP external, NM - NEMO
       ND - ND Default, NDp - ND Prefix, DCE - Destination, NDr - Redirect
       RL - RPL, O - OSPF Intra, OI - OSPF Inter, OE1 - OSPF ext 1
       OE2 - OSPF ext 2, ON1 - OSPF NSSA ext 1, ON2 - OSPF NSSA ext 2
       la - LISP alt, lr - LISP site-registrations, ld - LISP dyn-eid
       lA - LISP away, a - Application
OE2 2001::/64 [110/20]
     via FE80::A8BB:CCFF:FE00:4000, Ethernet0/1
OE2 2002::/64 [110/20]
     via FE80::A8BB:CCFF:FE00:4000, Ethernet0/1
OE2 2003::/64 [110/20]
     via FE80::A8BB:CCFF:FE00:4000, Ethernet0/1
O   2004::/64 [110/11]
     via FE80::A8BB:CCFF:FE00:4000, Ethernet0/1
R5#ping 2001::1 source 2005::5
Type escape sequence to abort.
Sending 5, 100-byte ICMP Echos to 2001::1, timeout is 2 seconds:
Packet sent with a source address of 2005::5
!!!!!
Success rate is 100 percent (5/5), round-trip min/avg/max = 1/1/1 ms
R5#
```

__<u>Redistribute BGP to OSPFv3</u>__

* __R5 (mặc định ebgp có thể redistribute bằng lệnh `redistribute bgp`, tuy nhiên với ibgp thì cần bổ sung câu lệnh `bgp redistribute-internal`)__
```
en
conf t
ipv6 router ospf 5
redistribute bgp 56
router bgp 56
address-family ipv6 unicast
bgp redistribute-internal
end
```

* __Verify__

```
R4#sh ipv6 route ospf
IPv6 Routing Table - default - 12 entries
Codes: C - Connected, L - Local, S - Static, U - Per-user Static route
       B - BGP, HA - Home Agent, MR - Mobile Router, R - RIP
       H - NHRP, I1 - ISIS L1, I2 - ISIS L2, IA - ISIS interarea
       IS - ISIS summary, D - EIGRP, EX - EIGRP external, NM - NEMO
       ND - ND Default, NDp - ND Prefix, DCE - Destination, NDr - Redirect
       RL - RPL, O - OSPF Intra, OI - OSPF Inter, OE1 - OSPF ext 1
       OE2 - OSPF ext 2, ON1 - OSPF NSSA ext 1, ON2 - OSPF NSSA ext 2
       la - LISP alt, lr - LISP site-registrations, ld - LISP dyn-eid
       lA - LISP away, a - Application
O   2005::/64 [110/11]
     via FE80::A8BB:CCFF:FE00:5010, Ethernet0/0
OE2 2006::/64 [110/1]
     via FE80::A8BB:CCFF:FE00:5010, Ethernet0/0
R4#
```

__<u>Redistribute OSPFv3 to BGP</u>__

* __R5__
```
en
conf t
router bgp 56
address-family ipv6 unicast
redistribute ospf 5 match internal external include-connected
end
```

* __Verify__

```
R6#sh bgp ipv6 unicast
BGP table version is 8, local router ID is 6.6.6.6
Status codes: s suppressed, d damped, h history, * valid, > best, i - internal,
              r RIB-failure, S Stale, m multipath, b backup-path, f RT-Filter,
              x best-external, a additional-path, c RIB-compressed,
              t secondary path,
Origin codes: i - IGP, e - EGP, ? - incomplete
RPKI validation codes: V valid, I invalid, N Not found

     Network          Next Hop            Metric LocPrf Weight Path
 *>i  2001::/64        2056::5                 20    100      0 ?
 *>i  2002::/64        2056::5                 20    100      0 ?
 *>i  2003::/64        2056::5                 20    100      0 ?
 *>i  2004::/64        2056::5                 11    100      0 ?
 *>i  2005::/64        2056::5                  0    100      0 ?
 *>   2006::/64        ::                       0         32768 i
 *>i  2045::/64        2056::5                  0    100      0 ?
R6#sh ipv6 route bgp
IPv6 Routing Table - default - 11 entries
Codes: C - Connected, L - Local, S - Static, U - Per-user Static route
       B - BGP, HA - Home Agent, MR - Mobile Router, R - RIP
       H - NHRP, I1 - ISIS L1, I2 - ISIS L2, IA - ISIS interarea
       IS - ISIS summary, D - EIGRP, EX - EIGRP external, NM - NEMO
       ND - ND Default, NDp - ND Prefix, DCE - Destination, NDr - Redirect
       RL - RPL, O - OSPF Intra, OI - OSPF Inter, OE1 - OSPF ext 1
       OE2 - OSPF ext 2, ON1 - OSPF NSSA ext 1, ON2 - OSPF NSSA ext 2
       la - LISP alt, lr - LISP site-registrations, ld - LISP dyn-eid
       lA - LISP away, a - Application
B   2001::/64 [200/20]
     via 2056::5
B   2002::/64 [200/20]
     via 2056::5
B   2003::/64 [200/20]
     via 2056::5
B   2004::/64 [200/11]
     via 2056::5
B   2005::/64 [200/0]
     via 2056::5
B   2045::/64 [200/0]
     via 2056::5
R6#ping 2001::1 source 2006::6
Type escape sequence to abort.
Sending 5, 100-byte ICMP Echos to 2001::1, timeout is 2 seconds:
Packet sent with a source address of 2006::6
!!!!!
Success rate is 100 percent (5/5), round-trip min/avg/max = 1/1/2 ms
R6#
```

<br>
