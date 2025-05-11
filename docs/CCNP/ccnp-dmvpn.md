---
layout: default
title: DMVPN
nav_order: 100
parent: CCNP
---

# Dynamic Multipoint Virtual Private Network
{: .no_toc }

Mạng riêng ảo đa điểm động
{: .fs-6 .fw-300 }

---

## TABLE OF CONTENTS
{: .no_toc .text-delta }

1. TOC
{:toc}

---

![Alt text](/docs/CCNP/img/dmvpn-01.png)

![Alt text](/docs/CCNP/img/dmvpn.png)

## Tunnel

* R1-Hub
```conf
enable
conf t
!
host R1-Hub
!
no ip domain-lookup
!
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
end
```

* R2-Spoke (Single Command NHRP Configuration)
```conf
enable
conf t
!
host R2-Spoke
!
no ip domain-lookup
!
interface Ethernet0/0
 no shut
 ip address 200.0.123.2 255.255.255.0
!
interface Tunnel123
 ip address 10.0.123.2 255.255.255.0
 ip nhrp network-id 1
 ip nhrp nhs 10.0.123.1 nbma 200.0.123.1 multicast
 tunnel source Ethernet0/0
 tunnel destination 200.0.123.1
 tunnel mode gre ip
!
end
```

* R3-Spoke (Multi-Command NHRP Configuration)
```conf
enable
conf t
!
host R3-Spoke
!
no ip domain-lookup
!
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
end
```

Verify

```conf
R1-Hub#show dmvpn
Legend: Attrb --> S - Static, D - Dynamic, I - Incomplete
        N - NATed, L - Local, X - No Socket
        T1 - Route Installed, T2 - Nexthop-override
        C - CTS Capable, I2 - Temporary
        # Ent --> Number of NHRP entries with same NBMA peer
        NHS Status: E --> Expecting Replies, R --> Responding, W --> Waiting
        UpDn Time --> Up or Down Time for a Tunnel
==========================================================================

Interface: Tunnel123, IPv4 NHRP Details
Type:Hub, NHRP Peers:2,

 # Ent  Peer NBMA Addr Peer Tunnel Add State  UpDn Tm Attrb
 ----- --------------- --------------- ----- -------- -----
     1 200.0.123.2          10.0.123.2    UP 00:01:29     D
     1 200.0.123.3          10.0.123.3    UP 00:01:17     D

R1-Hub#show ip nhrp
10.0.123.2/32 via 10.0.123.2
   Tunnel123 created 00:01:42, expire 00:08:17
   Type: dynamic, Flags: registered nhop
   NBMA address: 200.0.123.2
10.0.123.3/32 via 10.0.123.3
   Tunnel123 created 00:01:30, expire 00:08:29
   Type: dynamic, Flags: registered nhop
   NBMA address: 200.0.123.3

R2-Spoke#show dmvpn
Legend: Attrb --> S - Static, D - Dynamic, I - Incomplete
        N - NATed, L - Local, X - No Socket
        T1 - Route Installed, T2 - Nexthop-override
        C - CTS Capable, I2 - Temporary
        # Ent --> Number of NHRP entries with same NBMA peer
        NHS Status: E --> Expecting Replies, R --> Responding, W --> Waiting
        UpDn Time --> Up or Down Time for a Tunnel
==========================================================================

Interface: Tunnel123, IPv4 NHRP Details
Type:Spoke, NHRP Peers:1,

 # Ent  Peer NBMA Addr Peer Tunnel Add State  UpDn Tm Attrb
 ----- --------------- --------------- ----- -------- -----
     1 200.0.123.1          10.0.123.1    UP 00:01:33     S

R2-Spoke#show ip nhrp
10.0.123.1/32 via 10.0.123.1
   Tunnel123 created 00:01:56, never expire
   Type: static, Flags:
   NBMA address: 200.0.123.1

R2-Spoke#ping 10.0.123.3
Type escape sequence to abort.
Sending 5, 100-byte ICMP Echos to 10.0.123.3, timeout is 2 seconds:
!!!!!
Success rate is 100 percent (5/5), round-trip min/avg/max = 1/1/1 ms
R2-Spoke#traceroute 10.0.123.3 probe 1
Type escape sequence to abort.
Tracing the route to 10.0.123.3
VRF info: (vrf in name/id, vrf out name/id)
  1 10.0.123.1 4 msec
  2 10.0.123.3 2 msec
```

* IPSEC

```
enable
conf t
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
end
```


<!-- ## OSPF

![Alt text](/docs/CCNP/img/dmvpn-02.png)

* R1-Hub
```conf
enable
conf t
interface Loopback0
 ip address 1.1.1.1 255.255.255.255
 ip ospf 1 area 0
!
interface Tunnel123
 ip ospf network broadcast
 ip ospf 1 area 0
!
router ospf 1
 router-id 1.1.1.1
!
end
```

* R2-Spoke
```conf
enable
conf t
interface Loopback0
 ip address 2.2.2.2 255.255.255.255
 ip ospf 1 area 0
!
interface Tunnel123
 ip ospf network broadcast
 ip ospf priority 0
 ip ospf 1 area 0
!
router ospf 1
 router-id 2.2.2.2
!
end
```

* R3-Spoke
```conf
enable
conf t
interface Loopback0
 ip address 3.3.3.3 255.255.255.255
 ip ospf 1 area 0
!
interface Tunnel123
 ip ospf network broadcast
 ip ospf priority 0
 ip ospf 1 area 0
!
router ospf 1
 router-id 3.3.3.3
!
end
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
``` -->


## NHRP redirect and shortcut


<!-- * R1-Hub
```conf
enable
conf t
interface Tunnel123
 ip ospf network point-to-multipoint
 ip nhrp redirect
 tunnel mode gre multipoint
end
```

* R2/3-Spoke
```conf
enable
conf t
interface Tunnel123
 ip ospf network point-to-multipoint
 ip nhrp shortcut
 no tunnel destination
 tunnel mode gre multipoint
end
``` -->


* R1-Hub
```conf
enable
conf t
interface Tunnel123
 ip nhrp redirect
 tunnel mode gre multipoint
end
```

* R2/3-Spoke
```conf
enable
conf t
interface Tunnel123
 ip nhrp shortcut
 no tunnel destination
 tunnel mode gre multipoint
end
```

Verify

```conf
R2-Spoke#traceroute 10.0.123.3 probe 1
Type escape sequence to abort.
Tracing the route to 10.0.123.3
VRF info: (vrf in name/id, vrf out name/id)
  1 10.0.123.1 5 msec
  2 10.0.123.3 5 msec
R2-Spoke#traceroute 10.0.123.3 probe 1
Type escape sequence to abort.
Tracing the route to 10.0.123.3
VRF info: (vrf in name/id, vrf out name/id)
  1 10.0.123.1 1 msec
  2 10.0.123.3 1 msec
R2-Spoke#traceroute 10.0.123.3 probe 1
Type escape sequence to abort.
Tracing the route to 10.0.123.3
VRF info: (vrf in name/id, vrf out name/id)
  1 10.0.123.3 5 msec
R2-Spoke#traceroute 10.0.123.3 probe 1
Type escape sequence to abort.
Tracing the route to 10.0.123.3
VRF info: (vrf in name/id, vrf out name/id)
  1 10.0.123.3 1 msec
R2-Spoke#traceroute 10.0.123.3 probe 1
Type escape sequence to abort.
Tracing the route to 10.0.123.3
VRF info: (vrf in name/id, vrf out name/id)
  1 10.0.123.3 1 msec
```


<!-- ## NHRP registration no-unique

NHRP up phiên sẽ gán cứng ip tunnel map vs ip public. NHRP redirect and shortcut dùng trường hợp modem đk với nhà mạng là ip động có thể bị thay đổi khi reset phiên pppoe, có thể làm down phiên NHRP. Giải quyết bằng cách cấu hình _NHRP registration no-unique_ (tuy nhiên với HUB thì yêu cầu ip static).

* R2/3-Spoke
```conf
enable
conf t
interface Tunnel123
 ip nhrp registration no-unique
end
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
``` -->

