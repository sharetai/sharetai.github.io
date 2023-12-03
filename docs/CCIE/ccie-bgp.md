---
layout: default
title: BGP
nav_order: 20
parent: CCIE
---

# Border Gateway Protocol
{: .no_toc }

Giao thức cổng đường biên
{: .fs-6 .fw-300 }

_Nguồn tham khảo: [http://ccie-in-2-months.blogspot.com/](http://ccie-in-2-months.blogspot.com/p/the-hints-series.html)_

---

## Table of contents
{: .no_toc .text-delta }

1. TOC
{:toc}

---

BGP (Border Gateway Protocol) is defined in [RFC 4271](http://tools.ietf.org/html/rfc4271).

---

Uses TCP port 179.

---

<u>Common Comparisons</u>
 - Prefix Length
 - Highest Local Preference
 - Shortest as-path
 - Lowest Multi-Exit Discriminator (MED)
 - Prefer eBGP over iBGP
 - Lowest IGP metric to the BGP next hop
 - Lowest BGP router-id

---

<u>Topo</u>

\[ Router1 \] e0/0 ------------ e0/1 \[ Router2 \] e0/0 ------------ gi0/0/0/1 \[ Router3 \] gi0/0/0/0 ------------ gi0/0/0/1 \[ Router4 \]

---

## <u>Init</u>

IOS
{: .label .label-blue }

<u>R1</u>
```
conf t

host R1
!
int lo0
 ip addr 1.1.1.1 255.255.255.255
!
int e0/0
 no shut
 ip addr 210.245.12.1 255.255.255.0
!

end
write
```

<u>R2</u>
```
conf t

host R2
!
int lo0
 ip addr 2.2.2.2 255.255.255.255
!
int e0/0
 no shut
 ip addr 10.0.23.2 255.255.255.0
!
int e0/1
 no shut
 ip addr 210.245.12.2 255.255.255.0
!
router ospf 1
 router-id 2.2.2.2
 network 2.2.2.2 0.0.0.0 area 0
 network 10.0.23.2 0.0.0.0 area 0
!

end
write
```

IOS-XR
{: .label .label-green }

<u>R3</u>
```
conf

host R3
!
int lo0
 ipv4 addr 3.3.3.3/32
!
int gi0/0/0/0
 no shut
 ipv4 addr 113.45.34.3/24
!
int gi0/0/0/1
 no shut
 ipv4 addr 10.0.23.3/24
!
router ospf 1
 router-id 3.3.3.3
 area 0
  int lo0
  !
  int gi0/0/0/1
  !
 !
!

commit
end
```

<u>R4</u>
```
conf

host R4
!
int lo0
 ipv4 addr 4.4.4.4/32
!
int gi0/0/0/1
 no shut
 ipv4 addr 113.45.34.4/24
!

commit
end
```

## <u>Configuration</u>

IOS
{: .label .label-blue }

<u>R1</u>
```
conf t

router bgp 1
 bgp router-id 1.1.1.1
 neighbor 210.245.12.2 remote-as 23
!

end
write
```

<u>R2</u>
```
conf t

router bgp 23
 bgp router-id 2.2.2.2
 neighbor 3.3.3.3 remote-as 23
 neighbor 3.3.3.3 update-source lo0
 neighbor 210.245.12.1 remote-as 1
!

end
write
```

IOS-XR
{: .label .label-green }

<u>R3</u>
```
conf

router bgp 23
 bgp router-id 3.3.3.3
 address-family ipv4 unicast
 neighbor 2.2.2.2
  remote-as 23
  address-family ipv4 unicast
  update-source lo0
 !
 neighbor 113.45.34.4
  remote-as 4
  address-family ipv4 unicast
 !
!

commit
end
```

<u>R4</u>
```
conf

router bgp 4
 bgp router-id 4.4.4.4
 address-family ipv4 unicast
 neighbor 113.45.34.3
  remote-as 23
  address-family ipv4 unicast
 !
!

commit
end
```

## <u>Advertisement</u>

IOS
{: .label .label-blue }

<u>R1</u>
```
conf t

router bgp 1
 network 1.1.1.1 mask 255.255.255.255
!

end
write
```

<u>R2</u>
```
conf t

router bgp 23
 neighbor 3.3.3.3 next-hop-self
!

end
write
```

IOS-XR
{: .label .label-green }

<u>R3</u>
```
conf

route-policy pass_all
 pass
 exit
!
router bgp 23
 neighbor 2.2.2.2
  address-family ipv4 unicast
   next-hop-self
  !
 !
 neighbor 113.45.34.4
  address-family ipv4 unicast
   route-policy pass_all in
   route-policy pass_all out
  !
 !
!

commit
end
```

<u>R4</u>
```
conf

route-policy pass_all
 pass
 exit
!
router bgp 4
 address-family ipv4 unicast
  network 4.4.4.4/32
 !
 neighbor 113.45.34.3
  address-family ipv4 unicast
   route-policy pass_all in
   route-policy pass_all out
  !
 !
!

commit
end
```

test

```
R2#show bgp summary
BGP router identifier 2.2.2.2, local AS number 23
BGP table version is 3, main routing table version 3
2 network entries using 288 bytes of memory
2 path entries using 168 bytes of memory
2/2 BGP path/bestpath attribute entries using 320 bytes of memory
2 BGP AS-PATH entries using 48 bytes of memory
0 BGP route-map cache entries using 0 bytes of memory
0 BGP filter-list cache entries using 0 bytes of memory
BGP using 824 total bytes of memory
BGP activity 4/2 prefixes, 4/2 paths, scan interval 60 secs

Neighbor        V           AS MsgRcvd MsgSent   TblVer  InQ OutQ Up/Down  State/PfxRcd
3.3.3.3         4           23      26      26        3    0    0 00:20:33        1
210.245.12.1    4            1      26      27        3    0    0 00:20:37        1
R2#show bgp
BGP table version is 3, local router ID is 2.2.2.2
Status codes: s suppressed, d damped, h history, * valid, > best, i - internal,
              r RIB-failure, S Stale, m multipath, b backup-path, f RT-Filter,
              x best-external, a additional-path, c RIB-compressed,
              t secondary path,
Origin codes: i - IGP, e - EGP, ? - incomplete
RPKI validation codes: V valid, I invalid, N Not found

     Network          Next Hop            Metric LocPrf Weight Path
 *>   1.1.1.1/32       210.245.12.1             0             0 1 i
 *>i  4.4.4.4/32       3.3.3.3                  0    100      0 4 i
R2#show ip route bgp
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

      1.0.0.0/32 is subnetted, 1 subnets
B        1.1.1.1 [20/0] via 210.245.12.1, 00:19:32
      4.0.0.0/32 is subnetted, 1 subnets
B        4.4.4.4 [200/0] via 3.3.3.3, 00:03:02


RP/0/0/CPU0:R3#show bgp summary
Sun Dec  3 14:38:57.677 UTC
BGP router identifier 3.3.3.3, local AS number 23
BGP generic scan interval 60 secs
Non-stop routing is enabled
BGP table state: Active
Table ID: 0xe0000000   RD version: 4
BGP main routing table version 4
BGP NSR Initial initsync version 2 (Reached)
BGP NSR/ISSU Sync-Group versions 0/0
BGP scan interval 60 secs

BGP is operating in STANDALONE mode.


Process       RcvTblVer   bRIB/RIB   LabelVer  ImportVer  SendTblVer  StandbyVer
Speaker               4          4          4          4           4           0

Neighbor        Spk    AS MsgRcvd MsgSent   TblVer  InQ OutQ  Up/Down  St/PfxRcd
2.2.2.2           0    23      82      74        4    0    0 00:20:55          1
113.45.34.4       0     4      57      64        4    0    0 00:20:31          1

RP/0/0/CPU0:R3#show bgp
Sun Dec  3 14:38:59.577 UTC
BGP router identifier 3.3.3.3, local AS number 23
BGP generic scan interval 60 secs
Non-stop routing is enabled
BGP table state: Active
Table ID: 0xe0000000   RD version: 4
BGP main routing table version 4
BGP NSR Initial initsync version 2 (Reached)
BGP NSR/ISSU Sync-Group versions 0/0
BGP scan interval 60 secs

Status codes: s suppressed, d damped, h history, * valid, > best
              i - internal, r RIB-failure, S stale, N Nexthop-discard
Origin codes: i - IGP, e - EGP, ? - incomplete
   Network            Next Hop            Metric LocPrf Weight Path
*>i1.1.1.1/32         2.2.2.2                  0    100      0 1 i
*> 4.4.4.4/32         113.45.34.4              0             0 4 i

Processed 2 prefixes, 2 paths
RP/0/0/CPU0:R3#show route bgp
Sun Dec  3 14:39:03.907 UTC

B    1.1.1.1/32 [200/0] via 2.2.2.2, 00:12:49
B    4.4.4.4/32 [20/0] via 113.45.34.4, 00:06:49


R1#ping 4.4.4.4 source 1.1.1.1
Type escape sequence to abort.
Sending 5, 100-byte ICMP Echos to 4.4.4.4, timeout is 2 seconds:
Packet sent with a source address of 1.1.1.1
!!!!!
Success rate is 100 percent (5/5), round-trip min/avg/max = 3/3/4 ms
```
