---
layout: default
title: BGP
nav_order: 11
parent: JN0
---

# Border Gateway Protocol
{: .no_toc }

Giao thức định tuyến ở cổng biên
{: .fs-6 .fw-300 }

---

## Table of contents
{: .no_toc .text-delta }

1. TOC
{:toc}

---

## Notes

Bảng thuộc tính BGP (Thường dùng)

| Name             | Type                     |
|:-----------------|:-------------------------|
| Nexthop          | Well-known mandatory     |
| Local Preference | Well-known discretionary |
| AS Path          | Well-known mandatory     |
| Origin           | Well-known mandatory     |
| Community        | Optional transitive      |

## Chuẩn bị

![](/docs/JN0/img/9.png)

```
# R1

set interfaces ge-0/0/0 unit 0 family inet address 10.0.12.1/29
set interfaces ge-0/0/1 unit 0 family inet address 10.0.13.1/29
set interfaces lo0 unit 0 family inet address 1.1.1.1/32
set protocols ospf area 0.0.0.0 interface lo0.0
set protocols ospf area 0.0.0.0 interface ge-0/0/0.0

# R2

set interfaces ge-0/0/0 unit 0 family inet address 10.0.24.2/29
set interfaces ge-0/0/1 unit 0 family inet address 10.0.12.2/29
set interfaces lo0 unit 0 family inet address 2.2.2.2/32
set protocols ospf area 0.0.0.0 interface lo0.0
set protocols ospf area 0.0.0.0 interface ge-0/0/1.0

# ISP-A

set interfaces ge-0/0/0 unit 0 family inet address 10.0.13.3/29
set interfaces lo0 unit 0 family inet address 3.3.3.3/32

# ISP-B

set interfaces ge-0/0/1 unit 0 family inet address 10.0.24.4/29
set interfaces lo0 unit 0 family inet address 4.4.4.4/32
```

## Cấu hình BGP

```
# R1

set routing-options autonomous-system 65503
set protocols bgp group int-65503 type internal
set protocols bgp group int-65503 local-address 1.1.1.1
set protocols bgp group int-65503 neighbor 2.2.2.2
set protocols bgp group ext-65501 type external
set protocols bgp group ext-65501 peer-as 65501
set protocols bgp group ext-65501 neighbor 10.0.13.3

# R2

set routing-options autonomous-system 65503
set protocols bgp group int-65503 type internal
set protocols bgp group int-65503 local-address 2.2.2.2
set protocols bgp group int-65503 neighbor 1.1.1.1
set protocols bgp group ext-65502 type external
set protocols bgp group ext-65502 peer-as 65502
set protocols bgp group ext-65502 neighbor 10.0.24.4

# ISP-A

set routing-options autonomous-system 65501
set protocols bgp group ext-65503 type external
set protocols bgp group ext-65503 peer-as 65503
set protocols bgp group ext-65503 neighbor 10.0.13.1

# ISP-B

set routing-options autonomous-system 65502
set protocols bgp group ext-65503 type external
set protocols bgp group ext-65503 peer-as 65503
set protocols bgp group ext-65503 neighbor 10.0.24.2
```

## Cấu hình next-hop-self

```
# R1

set policy-options policy-statement next-hop-self-policy term alter-next-hop then next-hop self
set protocols bgp group int-65503 export next-hop-self-policy
```

## Cấu hình quảng bá prefix

```
# R1

set policy-options policy-statement adv-prefix term match-prefix from route-filter 2.2.2.2/32 exact
set policy-options policy-statement adv-prefix term match-prefix then accept
set protocols bgp group ext-65501 export adv-prefix

# ISP-A

set policy-options policy-statement adv-prefix term match-prefix from route-filter 3.3.3.3/32 exact
set policy-options policy-statement adv-prefix term match-prefix then accept
set protocols bgp group ext-65503 export adv-prefix
```

## Kiểm tra

* Kiểm tra bgp peer

```
root@R1> show bgp summary
Groups: 2 Peers: 2 Down peers: 0
Table          Tot Paths  Act Paths Suppressed    History Damp State    Pending
inet.0
                       1          1          0          0          0          0
Peer                     AS      InPkt     OutPkt    OutQ   Flaps Last Up/Dwn State|#Active/Received/Accepted/Damped...
2.2.2.2               65503         24         43       0       0       17:58 0/0/0/0              0/0/0/0
10.0.13.3             65501         33         46       0       0       19:04 1/1/1/0              0/0/0/0

root@R2> show bgp summary
Groups: 2 Peers: 2 Down peers: 0
Table          Tot Paths  Act Paths Suppressed    History Damp State    Pending
inet.0
                       1          1          0          0          0          0
Peer                     AS      InPkt     OutPkt    OutQ   Flaps Last Up/Dwn State|#Active/Received/Accepted/Damped...
1.1.1.1               65503         42         24       0       0        9:41 1/1/1/0              0/0/0/0
10.0.24.4             65502         49         26       0       0       10:17 0/0/0/0              0/0/0/0

root@ISP-A> show bgp summary
Groups: 1 Peers: 1 Down peers: 0
Table          Tot Paths  Act Paths Suppressed    History Damp State    Pending
inet.0
                       1          1          0          0          0          0
Peer                     AS      InPkt     OutPkt    OutQ   Flaps Last Up/Dwn State|#Active/Received/Accepted/Damped...
10.0.13.1             65503         46         34       0       0       14:01 1/1/1/0              0/0/0/0

root@ISP-B> show bgp summary
Groups: 1 Peers: 1 Down peers: 0
Table          Tot Paths  Act Paths Suppressed    History Damp State    Pending
inet.0
                       1          1          0          0          0          0
Peer                     AS      InPkt     OutPkt    OutQ   Flaps Last Up/Dwn State|#Active/Received/Accepted/Damped...
10.0.24.2             65503         26         50       0       0       21:06 1/1/1/0              0/0/0/0
```

* Kiểm tra route bgp

```
root@R2> show route protocol bgp

inet.0: 8 destinations, 8 routes (8 active, 0 holddown, 0 hidden)
+ = Active Route, - = Last Active, * = Both

3.3.3.3/32         *[BGP/170] 00:06:54, localpref 100, from 1.1.1.1
                      AS path: 65501 I, validation-state: unverified
                    > to 10.0.12.1 via ge-0/0/1.0

root@ISP-A> show route protocol bgp

inet.0: 4 destinations, 4 routes (4 active, 0 holddown, 0 hidden)
+ = Active Route, - = Last Active, * = Both

2.2.2.2/32         *[BGP/170] 00:09:53, MED 1, localpref 100
                      AS path: 65503 I, validation-state: unverified
                    > to 10.0.13.1 via ge-0/0/0.0
```

* Kiểm tra ping

```
root@R2> ping rapid 3.3.3.3 source 2.2.2.2
PING 3.3.3.3 (3.3.3.3): 56 data bytes
!!!!!
--- 3.3.3.3 ping statistics ---
5 packets transmitted, 5 packets received, 0% packet loss
round-trip min/avg/max/stddev = 0.938/1.166/1.373/0.165 ms

root@ISP-A> ping rapid 2.2.2.2 source 3.3.3.3
PING 2.2.2.2 (2.2.2.2): 56 data bytes
!!!!!
--- 2.2.2.2 ping statistics ---
5 packets transmitted, 5 packets received, 0% packet loss
round-trip min/avg/max/stddev = 1.291/1.902/3.744/0.930 ms
```