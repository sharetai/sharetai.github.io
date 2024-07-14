---
layout: default
title: MPLS
nav_order: 30
parent: CCIE
---

# Multiprotocol Label Switching
{: .no_toc }

Chuyển mạch nhãn đa giao thức
{: .fs-6 .fw-300 }

_Nguồn tham khảo: [http://ccie-in-2-months.blogspot.com/](http://ccie-in-2-months.blogspot.com/p/the-hints-series.html)_

---

## Table of contents
{: .no_toc .text-delta }

1. TOC
{:toc}

---

LDP (Label Distribution Protocol) is defined in [RFC 5036](http://tools.ietf.org/html/rfc5036).<br>
MPLS (Multi-Protocol Label Switching) architecture is defined in [RFC 3031](http://tools.ietf.org/html/rfc3031).<br>
MPLS Label Stack Encoding is defined in [RFC 3032](http://tools.ietf.org/html/rfc3032).

---

<u>Topo</u>

\[ PPPoE client \] e0/0 ------------ e0/1 \[ Switch \] e0/0 ------------ e0/1 \[ PPPoE server \]

---

## BGP FREE CORE

![Alt text](/docs/CCIE/img/bgp-free-core.png)

```conf
# R1
interface Loopback0
 ip address 1.1.1.1 255.255.255.255
!
interface Ethernet0/0
 no shut
 ip address 10.0.12.1 255.255.255.0
!
router bgp 1
 network 1.1.1.1 mask 255.255.255.255
 neighbor 10.0.12.2 remote-as 234
!

# R2
interface Loopback0
 ip address 2.2.2.2 255.255.255.255
!
interface Ethernet0/0
 no shut
 ip address 10.0.23.2 255.255.255.0
 mpls ip
!
interface Ethernet0/1
 no shut
 ip address 10.0.12.2 255.255.255.0
!
router ospf 1
 network 2.2.2.2 0.0.0.0 area 0
 network 10.0.23.2 0.0.0.0 area 0
!
router bgp 234
 neighbor 4.4.4.4 remote-as 234
 neighbor 4.4.4.4 update-source Loopback0
 neighbor 4.4.4.4 next-hop-self
 neighbor 10.0.12.1 remote-as 1
!

# R3
interface Loopback0
 ip address 3.3.3.3 255.255.255.255
!
interface Ethernet0/0
 no shut
 ip address 10.0.34.3 255.255.255.0
 mpls ip
!
interface Ethernet0/1
 no shut
 ip address 10.0.23.3 255.255.255.0
 mpls ip
!
router ospf 1
 network 3.3.3.3 0.0.0.0 area 0
 network 10.0.23.3 0.0.0.0 area 0
 network 10.0.34.3 0.0.0.0 area 0
!

# R4
interface Loopback0
 ip address 4.4.4.4 255.255.255.255
!
interface Ethernet0/0
 no shut
 ip address 10.0.45.4 255.255.255.0
!
interface Ethernet0/1
 no shut
 ip address 10.0.34.4 255.255.255.0
 mpls ip
!
router ospf 1
 network 4.4.4.4 0.0.0.0 area 0
 network 10.0.34.4 0.0.0.0 area 0
!
router bgp 234
 neighbor 2.2.2.2 remote-as 234
 neighbor 2.2.2.2 update-source Loopback0
 neighbor 2.2.2.2 next-hop-self
 neighbor 10.0.45.5 remote-as 5
!

# R5
interface Loopback0
 ip address 5.5.5.5 255.255.255.255
!
interface Ethernet0/1
 no shut
 ip address 10.0.45.5 255.255.255.0
!
router bgp 5
 network 5.5.5.5 mask 255.255.255.255
 neighbor 10.0.45.4 remote-as 234
!
```

## MPLS VPN L3

![Alt text](/docs/CCIE/img/mpls-vpn-l3.png)

### A. Static

__<u>Config</u>__

```conf
# R2
ip vrf A
 rd 234:15
 route-target export 234:1
 route-target import 234:5
!
interface Loopback0
 ip address 2.2.2.2 255.255.255.255
!
interface Ethernet0/0
 no shut
 ip address 10.0.23.2 255.255.255.0
 mpls ip
!
interface Ethernet0/1
 no shut
 ip vrf forwarding A
 ip address 10.0.12.2 255.255.255.0
!
router ospf 1
 network 2.2.2.2 0.0.0.0 area 0
 network 10.0.23.2 0.0.0.0 area 0
!
router bgp 234
 neighbor 4.4.4.4 remote-as 234
 neighbor 4.4.4.4 update-source Loopback0
 !
 address-family vpnv4
  neighbor 4.4.4.4 activate
 !
 address-family ipv4 vrf A
  redistribute static
!
ip route vrf A 1.1.1.1 255.255.255.255 10.0.12.1
!

# R3
interface Loopback0
 ip address 3.3.3.3 255.255.255.255
!
interface Ethernet0/0
 no shut
 ip address 10.0.34.3 255.255.255.0
 mpls ip
!
interface Ethernet0/1
 no shut
 ip address 10.0.23.3 255.255.255.0
 mpls ip
!
router ospf 1
 network 3.3.3.3 0.0.0.0 area 0
 network 10.0.23.3 0.0.0.0 area 0
 network 10.0.34.3 0.0.0.0 area 0
!

# R4
ip vrf A
 rd 234:15
 route-target export 234:5
 route-target import 234:1
!
interface Loopback0
 ip address 4.4.4.4 255.255.255.255
!
interface Ethernet0/0
 no shut
 ip vrf forwarding A
 ip address 10.0.45.4 255.255.255.0
!
interface Ethernet0/1
 no shut
 ip address 10.0.34.4 255.255.255.0
 mpls ip
!
router ospf 1
 network 4.4.4.4 0.0.0.0 area 0
 network 10.0.34.4 0.0.0.0 area 0
!
router bgp 234
 neighbor 2.2.2.2 remote-as 234
 neighbor 2.2.2.2 update-source Loopback0
 !
 address-family vpnv4
  neighbor 2.2.2.2 activate
 !
 address-family ipv4 vrf A
  redistribute static
!
ip route vrf A 5.5.5.5 255.255.255.255 10.0.45.5
!

# R1A
interface Loopback0
 ip address 1.1.1.1 255.255.255.255
!
interface Ethernet0/0
 no shut
 ip address 10.0.12.1 255.255.255.0
!
ip route 5.5.5.5 255.255.255.255 10.0.12.2
!

# R5A
interface Loopback0
 ip address 5.5.5.5 255.255.255.255
!
interface Ethernet0/1
 no shut
 ip address 10.0.45.5 255.255.255.0
!
ip route 1.1.1.1 255.255.255.255 10.0.45.4
!
```

__<u>Verify</u>__

```conf
R2#sh ip route vrf A

Routing Table: A
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
S        1.1.1.1 [1/0] via 10.0.12.1
      5.0.0.0/32 is subnetted, 1 subnets
B        5.5.5.5 [200/0] via 4.4.4.4, 00:11:49
      10.0.0.0/8 is variably subnetted, 2 subnets, 2 masks
C        10.0.12.0/24 is directly connected, Ethernet0/1
L        10.0.12.2/32 is directly connected, Ethernet0/1
R2#sh ip bgp sum
BGP router identifier 2.2.2.2, local AS number 234
BGP table version is 1, main routing table version 1

Neighbor        V           AS MsgRcvd MsgSent   TblVer  InQ OutQ Up/Down  State/PfxRcd
4.4.4.4         4          234      50      68        1    0    0 00:33:02        0
R2#sh ip bgp vpnv4 all
BGP table version is 12, local router ID is 2.2.2.2
Status codes: s suppressed, d damped, h history, * valid, > best, i - internal,
              r RIB-failure, S Stale, m multipath, b backup-path, f RT-Filter,
              x best-external, a additional-path, c RIB-compressed,
Origin codes: i - IGP, e - EGP, ? - incomplete
RPKI validation codes: V valid, I invalid, N Not found

     Network          Next Hop            Metric LocPrf Weight Path
Route Distinguisher: 234:15 (default for vrf A)
 *>  1.1.1.1/32       10.0.12.1                0         32768 ?
 *>i 5.5.5.5/32       4.4.4.4                  0    100      0 ?

R4#sh ip route vrf A

Routing Table: A
Codes: L - local, C - connected, S - static, R - RIP, M - mobile, B - BGP
       D - EIGRP, EX - EIGRP external, O - OSPF, IA - OSPF inter area
       N1 - OSPF NSSA external type 1, N2 - OSPF NSSA external type 2
       E1 - OSPF external type 1, E2 - OSPF external type 2
       i - IS-IS, su - IS-IS summary, L1 - IS-IS level-1, L2 - IS-IS level-2
       ia - IS-IS inter area, * - candidate default, U - per-user static route
       o - ODR, P - periodic downloaded static route, H - NHRP, l - LISP
       a - application route
       + - replicated route, % - next hop override
R2#

Gateway of last resort is not set

      1.0.0.0/32 is subnetted, 1 subnets
B        1.1.1.1 [200/0] via 2.2.2.2, 00:14:41
      5.0.0.0/32 is subnetted, 1 subnets
S        5.5.5.5 [1/0] via 10.0.45.5
      10.0.0.0/8 is variably subnetted, 2 subnets, 2 masks
C        10.0.45.0/24 is directly connected, Ethernet0/0
L        10.0.45.4/32 is directly connected, Ethernet0/0
R4#sh ip bgp sum
BGP router identifier 4.4.4.4, local AS number 234
BGP table version is 1, main routing table version 1

Neighbor        V           AS MsgRcvd MsgSent   TblVer  InQ OutQ Up/Down  State/PfxRcd
2.2.2.2         4          234      68      51        1    0    0 00:33:45        0
R4#sh ip bgp vpnv4 all
BGP table version is 26, local router ID is 4.4.4.4
Status codes: s suppressed, d damped, h history, * valid, > best, i - internal,
              r RIB-failure, S Stale, m multipath, b backup-path, f RT-Filter,
              x best-external, a additional-path, c RIB-compressed,
Origin codes: i - IGP, e - EGP, ? - incomplete
RPKI validation codes: V valid, I invalid, N Not found

     Network          Next Hop            Metric LocPrf Weight Path
Route Distinguisher: 234:15 (default for vrf A)
 *>i 1.1.1.1/32       2.2.2.2                  0    100      0 ?
 *>  5.5.5.5/32       10.0.45.5                0         32768 ?
R4#

R1A#ping 5.5.5.5 source 1.1.1.1
Type escape sequence to abort.
Sending 5, 100-byte ICMP Echos to 5.5.5.5, timeout is 2 seconds:
Packet sent with a source address of 1.1.1.1
!!!!!
Success rate is 100 percent (5/5), round-trip min/avg/max = 1/1/2 ms
R1A#

Type escape sequence to abort.
Sending 5, 100-byte ICMP Echos to 1.1.1.1, timeout is 2 seconds:
Packet sent with a source address of 5.5.5.5
!!!!!
Success rate is 100 percent (5/5), round-trip min/avg/max = 1/1/1 ms
R5A#
```

### B. OSPF

__<u>Config</u>__

```conf
# R2
ip vrf B
 rd 234:150
 route-target export 234:10
 route-target import 234:50
!
interface Loopback0
 ip address 2.2.2.2 255.255.255.255
!
interface Ethernet0/0
 no shut
 ip address 10.0.23.2 255.255.255.0
 mpls ip
!
interface Ethernet0/2
 no shut
 ip vrf forwarding B
 ip address 10.0.12.2 255.255.255.0
!
router ospf 11 vrf B
 redistribute bgp 234 subnets
 network 10.0.12.2 0.0.0.0 area 0
!
router ospf 1
 network 2.2.2.2 0.0.0.0 area 0
 network 10.0.23.2 0.0.0.0 area 0
!
router bgp 234
 bgp log-neighbor-changes
 neighbor 4.4.4.4 remote-as 234
 neighbor 4.4.4.4 update-source Loopback0
 !
 address-family vpnv4
  neighbor 4.4.4.4 activate
 !
 address-family ipv4 vrf B
  redistribute ospf 11
!

# R3
interface Loopback0
 ip address 3.3.3.3 255.255.255.255
!
interface Ethernet0/0
 no shut
 ip address 10.0.34.3 255.255.255.0
 mpls ip
!
interface Ethernet0/1
 no shut
 ip address 10.0.23.3 255.255.255.0
 mpls ip
!
router ospf 1
 network 3.3.3.3 0.0.0.0 area 0
 network 10.0.23.3 0.0.0.0 area 0
 network 10.0.34.3 0.0.0.0 area 0
!

# R4
ip vrf B
 rd 234:150
 route-target export 234:50
 route-target import 234:10
!
interface Loopback0
 ip address 4.4.4.4 255.255.255.255
!
interface Ethernet0/1
 no shut
 ip address 10.0.34.4 255.255.255.0
 mpls ip
!
interface Ethernet0/2
 no shut
 ip vrf forwarding B
 ip address 10.0.45.4 255.255.255.0
!
router ospf 11 vrf B
 redistribute bgp 234 subnets
 network 10.0.45.4 0.0.0.0 area 0
!
router ospf 1
 network 4.4.4.4 0.0.0.0 area 0
 network 10.0.34.4 0.0.0.0 area 0
!
router bgp 234
 bgp log-neighbor-changes
 neighbor 2.2.2.2 remote-as 234
 neighbor 2.2.2.2 update-source Loopback0
 !
 address-family vpnv4
  neighbor 2.2.2.2 activate
 !
 address-family ipv4 vrf B
  redistribute ospf 11
!

# R1B
interface Loopback0
 ip address 1.1.1.1 255.255.255.255
!
interface Ethernet0/0
 no shut
 ip address 10.0.12.1 255.255.255.0
!
router ospf 1
 network 1.1.1.1 0.0.0.0 area 0
 network 10.0.12.1 0.0.0.0 area 0
!

# R5B
interface Loopback0
 ip address 5.5.5.5 255.255.255.255
!
interface Ethernet0/0
 no shut
 ip address 10.0.45.5 255.255.255.0
!
router ospf 1
 network 5.5.5.5 0.0.0.0 area 0
 network 10.0.45.5 0.0.0.0 area 0
!
```

__<u>Verify</u>__

```conf
R2#sh ip bgp sum
BGP router identifier 2.2.2.2, local AS number 234
BGP table version is 1, main routing table version 1

Neighbor        V           AS MsgRcvd MsgSent   TblVer  InQ OutQ Up/Down  State/PfxRcd
4.4.4.4         4          234      61      67        1    0    0 00:45:42        0
R2#sh ip bgp vpnv4 vrf B
BGP table version is 64, local router ID is 2.2.2.2
Status codes: s suppressed, d damped, h history, * valid, > best, i - internal,
              r RIB-failure, S Stale, m multipath, b backup-path, f RT-Filter,
              x best-external, a additional-path, c RIB-compressed,
Origin codes: i - IGP, e - EGP, ? - incomplete
RPKI validation codes: V valid, I invalid, N Not found

     Network          Next Hop            Metric LocPrf Weight Path
Route Distinguisher: 234:150 (default for vrf B)
 *>  1.1.1.1/32       10.0.12.1               11         32768 ?
 *>i 5.5.5.5/32       4.4.4.4                 11    100      0 ?
 *>  10.0.12.0/24     0.0.0.0                  0         32768 ?
 *>i 10.0.45.0/24     4.4.4.4                  0    100      0 ?
R2#

R4#sh ip bgp sum
BGP router identifier 4.4.4.4, local AS number 234
BGP table version is 1, main routing table version 1

Neighbor        V           AS MsgRcvd MsgSent   TblVer  InQ OutQ Up/Down  State/PfxRcd
2.2.2.2         4          234      68      62        1    0    0 00:46:25        0
R4#sh ip bgp vpnv4 vrf B
BGP table version is 87, local router ID is 4.4.4.4
Status codes: s suppressed, d damped, h history, * valid, > best, i - internal,
              r RIB-failure, S Stale, m multipath, b backup-path, f RT-Filter,
              x best-external, a additional-path, c RIB-compressed,
Origin codes: i - IGP, e - EGP, ? - incomplete
RPKI validation codes: V valid, I invalid, N Not found

     Network          Next Hop            Metric LocPrf Weight Path
Route Distinguisher: 234:150 (default for vrf B)
 *>i 1.1.1.1/32       2.2.2.2                 11    100      0 ?
 *>  5.5.5.5/32       10.0.45.5               11         32768 ?
 *>i 10.0.12.0/24     2.2.2.2                  0    100      0 ?
 *>  10.0.45.0/24     0.0.0.0                  0         32768 ?
R4#

R1B#ping 5.5.5.5 source 1.1.1.1
Type escape sequence to abort.
Sending 5, 100-byte ICMP Echos to 5.5.5.5, timeout is 2 seconds:
Packet sent with a source address of 1.1.1.1
!!!!!
Success rate is 100 percent (5/5), round-trip min/avg/max = 1/1/2 ms
R1B#

R5B#ping 1.1.1.1 source 5.5.5.5
Type escape sequence to abort.
Sending 5, 100-byte ICMP Echos to 1.1.1.1, timeout is 2 seconds:
Packet sent with a source address of 5.5.5.5
!!!!!
Success rate is 100 percent (5/5), round-trip min/avg/max = 1/1/1 ms
R5B#
```

### C. BGP

![Alt text](/docs/CCIE/img/mpls-vpn-l3-bgp.png)

__<u>Config</u>__

```conf
# R2
ip vrf C
 rd 234:151
 route-target export 234:11
 route-target import 234:51
!
interface Loopback0
 ip address 2.2.2.2 255.255.255.255
!
interface Ethernet0/0
 no shut
 ip address 10.0.23.2 255.255.255.0
 mpls ip
!
interface Ethernet0/3
 no shut
 ip vrf forwarding C
 ip address 10.0.12.2 255.255.255.0
!
router ospf 1
 network 2.2.2.2 0.0.0.0 area 0
 network 10.0.23.2 0.0.0.0 area 0
!
router bgp 234
 bgp log-neighbor-changes
 neighbor 4.4.4.4 remote-as 234
 neighbor 4.4.4.4 update-source Loopback0
 !
 address-family vpnv4
  neighbor 4.4.4.4 activate
 !
 address-family ipv4 vrf C
  neighbor 10.0.12.1 remote-as 15
  neighbor 10.0.12.1 activate
  neighbor 10.0.12.1 as-override
!

# R3
interface Loopback0
 ip address 3.3.3.3 255.255.255.255
!
interface Ethernet0/0
 no shut
 ip address 10.0.34.3 255.255.255.0
 mpls ip
!
interface Ethernet0/1
 no shut
 ip address 10.0.23.3 255.255.255.0
 mpls ip
!
router ospf 1
 network 3.3.3.3 0.0.0.0 area 0
 network 10.0.23.3 0.0.0.0 area 0
 network 10.0.34.3 0.0.0.0 area 0
!

# R4
ip vrf C
 rd 234:151
 route-target export 234:51
 route-target import 234:11
!
interface Loopback0
 ip address 4.4.4.4 255.255.255.255
!
interface Ethernet0/1
 no shut
 ip address 10.0.34.4 255.255.255.0
 mpls ip
!
interface Ethernet0/3
 no shut
 ip vrf forwarding C
 ip address 10.0.45.4 255.255.255.0
!
router ospf 1
 network 4.4.4.4 0.0.0.0 area 0
 network 10.0.34.4 0.0.0.0 area 0
!
router bgp 234
 bgp log-neighbor-changes
 neighbor 2.2.2.2 remote-as 234
 neighbor 2.2.2.2 update-source Loopback0
 !
 address-family vpnv4
  neighbor 2.2.2.2 activate
 !
 address-family ipv4 vrf C
  neighbor 10.0.45.5 remote-as 15
  neighbor 10.0.45.5 activate
  neighbor 10.0.45.5 as-override
!

# R1C
interface Loopback0
 ip address 1.1.1.1 255.255.255.255
!
interface Ethernet0/0
 ip address 10.0.12.1 255.255.255.0
!
router bgp 15
 bgp log-neighbor-changes
 network 1.1.1.1 mask 255.255.255.255
 neighbor 10.0.12.2 remote-as 234
!

# R5C
interface Loopback0
 ip address 5.5.5.5 255.255.255.255
!
interface Ethernet0/0
 ip address 10.0.45.5 255.255.255.0
!
router bgp 15
 bgp log-neighbor-changes
 network 5.5.5.5 mask 255.255.255.255
 neighbor 10.0.45.4 remote-as 234
!
```

__<u>Verify</u>__

```conf
R2#show bgp vpnv4 unicast vrf C summary
BGP router identifier 2.2.2.2, local AS number 234
BGP table version is 4, main routing table version 4
2 network entries using 304 bytes of memory
2 path entries using 160 bytes of memory
3/2 BGP path/bestpath attribute entries using 456 bytes of memory
1 BGP AS-PATH entries using 24 bytes of memory
2 BGP extended community entries using 48 bytes of memory
0 BGP route-map cache entries using 0 bytes of memory
0 BGP filter-list cache entries using 0 bytes of memory
BGP using 992 total bytes of memory
BGP activity 2/0 prefixes, 2/0 paths, scan interval 60 secs

Neighbor        V           AS MsgRcvd MsgSent   TblVer  InQ OutQ Up/Down  State/PfxRcd
10.0.12.1       4           15      20      21        4    0    0 00:13:49        1
R2#show bgp vpnv4 unicast vrf C
BGP table version is 4, local router ID is 2.2.2.2
Status codes: s suppressed, d damped, h history, * valid, > best, i - internal,
              r RIB-failure, S Stale, m multipath, b backup-path, f RT-Filter,
              x best-external, a additional-path, c RIB-compressed,
Origin codes: i - IGP, e - EGP, ? - incomplete
RPKI validation codes: V valid, I invalid, N Not found

     Network          Next Hop            Metric LocPrf Weight Path
Route Distinguisher: 234:151 (default for vrf C)
 *>  1.1.1.1/32       10.0.12.1                0             0 15 i
 *>i 5.5.5.5/32       4.4.4.4                  0    100      0 15 i
R2#

R4#show bgp vpnv4 unicast vrf C summary
BGP router identifier 4.4.4.4, local AS number 234
BGP table version is 4, main routing table version 4
2 network entries using 304 bytes of memory
2 path entries using 160 bytes of memory
3/2 BGP path/bestpath attribute entries using 456 bytes of memory
1 BGP AS-PATH entries using 24 bytes of memory
2 BGP extended community entries using 48 bytes of memory
0 BGP route-map cache entries using 0 bytes of memory
0 BGP filter-list cache entries using 0 bytes of memory
BGP using 992 total bytes of memory
BGP activity 2/0 prefixes, 2/0 paths, scan interval 60 secs

Neighbor        V           AS MsgRcvd MsgSent   TblVer  InQ OutQ Up/Down  State/PfxRcd
10.0.45.5       4           15      20      21        4    0    0 00:13:38        1
R4#show bgp vpnv4 unicast vrf C
BGP table version is 4, local router ID is 4.4.4.4
Status codes: s suppressed, d damped, h history, * valid, > best, i - internal,
              r RIB-failure, S Stale, m multipath, b backup-path, f RT-Filter,
              x best-external, a additional-path, c RIB-compressed,
Origin codes: i - IGP, e - EGP, ? - incomplete
RPKI validation codes: V valid, I invalid, N Not found

     Network          Next Hop            Metric LocPrf Weight Path
Route Distinguisher: 234:151 (default for vrf C)
 *>i 1.1.1.1/32       2.2.2.2                  0    100      0 15 i
 *>  5.5.5.5/32       10.0.45.5                0             0 15 i
R4#

R1C#ping 5.5.5.5 source 1.1.1.1
Type escape sequence to abort.
Sending 5, 100-byte ICMP Echos to 5.5.5.5, timeout is 2 seconds:
Packet sent with a source address of 1.1.1.1
!!!!!
Success rate is 100 percent (5/5), round-trip min/avg/max = 1/1/2 ms
R1C#

R5C#ping 1.1.1.1 source 5.5.5.5
Type escape sequence to abort.
Sending 5, 100-byte ICMP Echos to 1.1.1.1, timeout is 2 seconds:
Packet sent with a source address of 5.5.5.5
!!!!!
Success rate is 100 percent (5/5), round-trip min/avg/max = 1/1/2 ms
R5C#
```