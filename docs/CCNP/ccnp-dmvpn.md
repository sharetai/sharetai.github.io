---
layout: default
title: DMVPN
nav_order: 1
parent: CCNP
---

# Dynamic Multipoint Virtual Private Network
{: .no_toc }

Mạng riêng ảo đa điểm động
{: .fs-6 .fw-300 }

---

## Table of contents
{: .no_toc .text-delta }

1. TOC
{:toc}

---

![Alt text](/docs/CCNP/img/dmvpn.png)

## Tunnel

* R1 (HUB)
```conf
interface Ethernet0/0
 no shut
 ip address 200.0.123.1 255.255.255.0
!
interface Tunnel123
 ip address 10.0.123.1 255.255.255.0
 ip nhrp map multicast dynamic
 ip nhrp network-id 1
 tunnel source Ethernet0/0
 tunnel mode gre multipoint
!
```

* R2 (Spoke)
```conf
interface Ethernet0/0
 no shut
 ip address 200.0.123.2 255.255.255.0
!
interface Tunnel123
 ip address 10.0.123.2 255.255.255.0
 ip nhrp map 10.0.123.1 200.0.123.1
 ip nhrp map multicast 200.0.123.1
 ip nhrp network-id 1
 ip nhrp nhs 10.0.123.1
 tunnel source Ethernet0/0
 tunnel destination 200.0.123.1
 tunnel mode gre ip
!
```

* R3 (Spoke)
```conf
interface Ethernet0/0
 no shut
 ip address 200.0.123.3 255.255.255.0
!
interface Tunnel123
 ip address 10.0.123.3 255.255.255.0
 ip nhrp map 10.0.123.1 200.0.123.1
 ip nhrp map multicast 200.0.123.1
 ip nhrp network-id 1
 ip nhrp nhs 10.0.123.1
 tunnel source Ethernet0/0
 tunnel destination 200.0.123.1
 tunnel mode gre ip
!
```

Verify
```conf
R1#show ip nhrp
10.0.123.2/32 via 10.0.123.2
   Tunnel123 created 00:08:27, expire 01:51:32
   Type: dynamic, Flags: unique registered used nhop
   NBMA address: 200.0.123.2
10.0.123.3/32 via 10.0.123.3
   Tunnel123 created 00:06:16, expire 01:53:43
   Type: dynamic, Flags: unique registered used nhop
   NBMA address: 200.0.123.3
R1#show ip nhrp brief
   Target             Via            NBMA           Mode   Intfc   Claimed
       10.0.123.2/32 10.0.123.2      200.0.123.2     dynamic  Tu123   <   >
       10.0.123.3/32 10.0.123.3      200.0.123.3     dynamic  Tu123   <   >
R1#show dmvpn
Legend: Attrb --> S - Static, D - Dynamic, I - Incomplete
        N - NATed, L - Local, X - No Socket
        # Ent --> Number of NHRP entries with same NBMA peer
        NHS Status: E --> Expecting Replies, R --> Responding, W --> Waiting
        UpDn Time --> Up or Down Time for a Tunnel
==========================================================================

Interface: Tunnel123, IPv4 NHRP Details
Type:Hub, NHRP Peers:2,

 # Ent  Peer NBMA Addr Peer Tunnel Add State  UpDn Tm Attrb
 ----- --------------- --------------- ----- -------- -----
     1 200.0.123.2          10.0.123.2    UP 00:09:58     D
     1 200.0.123.3          10.0.123.3    UP 00:07:47     D

R1#

R2#ping 10.0.123.3
Type escape sequence to abort.
Sending 5, 100-byte ICMP Echos to 10.0.123.3, timeout is 2 seconds:
!!!!!
Success rate is 100 percent (5/5), round-trip min/avg/max = 1/1/2 ms
R2#traceroute 10.0.123.3
Type escape sequence to abort.
Tracing the route to 10.0.123.3
VRF info: (vrf in name/id, vrf out name/id)
  1 10.0.123.1 1 msec 2 msec 1 msec     <-- Lưu lượng sẽ chạy lên hub trước
  2 10.0.123.3 1 msec *  6 msec
R2#
```

* IPSEC

```
crypto isakmp policy 10
 encr aes
 hash md5
 authentication pre-share
 group 5
crypto isakmp key cisco address 0.0.0.0
crypto ipsec transform-set MyTS esp-aes esp-sha-hmac
crypto ipsec profile MyP
 set transform-set MyTS

interface Tunnel123
tunnel protection ipsec profile MyP
```


## OSPF

* R1 (HUB)
```conf
interface Tunnel123
 ip ospf network broadcast
 ip ospf 1 area 0
!
router ospf 1
 network 1.1.1.1 0.0.0.0 area 0
!
```

* R2 (Spoke)
```conf
interface Tunnel123
 ip ospf network broadcast
 ip ospf priority 0
 ip ospf 1 area 0
!
router ospf 1
 network 2.2.2.2 0.0.0.0 area 0
!
```

* R3 (Spoke)
```conf
interface Tunnel123
 ip ospf network broadcast
 ip ospf priority 0
 ip ospf 1 area 0
!
router ospf 1
 network 3.3.3.3 0.0.0.0 area 0
!
```

Verify

```conf
R1#sh ip ospf neighbor

Neighbor ID     Pri   State           Dead Time   Address         Interface
2.2.2.2           0   FULL/DROTHER    00:00:38    10.0.123.2      Tunnel123
3.3.3.3           0   FULL/DROTHER    00:00:35    10.0.123.3      Tunnel123
R1#sh ip route ospf
Codes: L - local, C - connected, S - static, R - RIP, M - mobile, B - BGP
       D - EIGRP, EX - EIGRP external, O - OSPF, IA - OSPF inter area
       N1 - OSPF NSSA external type 1, N2 - OSPF NSSA external type 2
       E1 - OSPF external type 1, E2 - OSPF external type 2
       i - IS-IS, su - IS-IS summary, L1 - IS-IS level-1, L2 - IS-IS level-2
       ia - IS-IS inter area, * - candidate default, U - per-user static route
       o - ODR, P - periodic downloaded static route, H - NHRP, l - LISP
       a - application route
       + - replicated route, % - next hop override

Gateway of last resort is not set

      2.0.0.0/32 is subnetted, 1 subnets
O        2.2.2.2 [110/1001] via 10.0.123.2, 00:52:02, Tunnel123
      3.0.0.0/32 is subnetted, 1 subnets
O        3.3.3.3 [110/1001] via 10.0.123.3, 00:51:52, Tunnel123
R1#

R2#sh ip route ospf
Codes: L - local, C - connected, S - static, R - RIP, M - mobile, B - BGP
       D - EIGRP, EX - EIGRP external, O - OSPF, IA - OSPF inter area
       N1 - OSPF NSSA external type 1, N2 - OSPF NSSA external type 2
       E1 - OSPF external type 1, E2 - OSPF external type 2
       i - IS-IS, su - IS-IS summary, L1 - IS-IS level-1, L2 - IS-IS level-2
       ia - IS-IS inter area, * - candidate default, U - per-user static route
       o - ODR, P - periodic downloaded static route, H - NHRP, l - LISP
       a - application route
       + - replicated route, % - next hop override

Gateway of last resort is not set

      1.0.0.0/32 is subnetted, 1 subnets
O        1.1.1.1 [110/1001] via 10.0.123.1, 00:07:31, Tunnel123
      3.0.0.0/32 is subnetted, 1 subnets
O        3.3.3.3 [110/1001] via 10.0.123.3, 00:00:10, Tunnel123

R2#traceroute 3.3.3.3 source 2.2.2.2    <-- KQ 1 hop
```


## NHRP redirect and shortcut


* R1 (HUB)
```conf
interface Tunnel123
 ip ospf network point-to-multipoint
```

* R2 (Spoke)
```conf
interface Tunnel123
 ip ospf network point-to-multipoint
```

* R3 (Spoke)
```conf
interface Tunnel123
 ip ospf network point-to-multipoint
```

Verify

```conf
R2#traceroute 3.3.3.3 source 2.2.2.2    <-- KQ 1 hop
```


## NHRP registration no-unique

NHRP up phiên sẽ gán cứng ip tunnel map vs ip public. NHRP redirect and shortcut dùng trường hợp modem đk với nhà mạng là ip động có thể bị thay đổi khi reset phiên pppoe, có thể làm down phiên NHRP.

* R2 (Spoke)
```conf
interface Tunnel123
 ip nhrp registration no-unique
```

* R3 (Spoke)
```conf
interface Tunnel123
 ip nhrp registration no-unique
```

Verify

```conf
R1#sh ip nhrp
10.0.123.2/32 via 10.0.123.2
   Tunnel123 created 00:24:50, expire 01:59:38
   Type: dynamic, Flags: registered used nhop   <-- Ko còn "unique registered used nhop"
   NBMA address: 200.0.123.2
10.0.123.3/32 via 10.0.123.3
   Tunnel123 created 00:24:52, expire 01:59:48
   Type: dynamic, Flags: registered used nhop   <-- Ko còn "unique registered used nhop"
   NBMA address: 200.0.123.3
```

