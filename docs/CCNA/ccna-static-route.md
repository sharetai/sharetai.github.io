---
layout: default
title: Static Route
nav_order: 11
parent: CCNA
---

# Static Route
{: .no_toc }

Cấu hình định tuyến tĩnh cho Router
{: .fs-6 .fw-300 }

---

## Table of contents
{: .no_toc .text-delta }

1. TOC
{:toc}

---

{: .highlight-title }
> Note
>
> Bản chất của thiết bị mạng là __FORWARDING__.

{: .important-title }
> Summary
>
> Static routing is __manually__ __configuring__ the __routing table__.

Định tuyến là thiết lập đường đi cho các gói tin dữ liệu đến được mạng đích. Mỗi router sử dụng một Bảng định tuyến để thực hiện công việc này, khi định tuyến tĩnh việc thiết lập bảng định tuyến sẽ làm thủ công.

{: .note-title }
> Syntax
>
> Router(config)#__ip route__ {_ip-prefix_ \| _ip-addr ip-mask_} {_next-hop_ \| _interface next-hop_} [_pref_]

__<u>Init</u>__

* __R1__
```
en
conf t
no ip domain-lookup
host R1
int gi0/0
ip addr 10.0.12.1 255.255.255.0
no shut
int gi1/0
ip addr 10.0.120.1 255.255.255.0
no shut
int gi2/0
ip addr 192.168.1.1 255.255.255.0
no shut
int gi3/0
ip addr 192.168.100.1 255.255.255.0
no shut
end
```

* __R2__
```
en
conf t
no ip domain-lookup
host R2
int gi0/0
ip addr 10.0.12.2 255.255.255.0
no shut
int gi1/0
ip addr 10.0.120.2 255.255.255.0
no shut
int gi2/0
ip addr 192.168.4.1 255.255.255.0
no shut
int gi3/0
ip addr 192.168.5.1 255.255.255.0
no shut
int gi4/0
ip addr 192.168.6.1 255.255.255.0
no shut
int gi5/0
ip addr 192.168.7.1 255.255.255.0
no shut
int gi6/0
ip addr 192.168.200.1 255.255.255.0
no shut
end
```

## Network route

![alt text](/docs/CCNA/img/static_route_1.png)

* __R1__
```
ip route 192.168.4.0 255.255.255.0 10.0.12.2
```

* __R2__
```
ip route 192.168.1.0 255.255.255.0 10.0.12.1
```

__Verify__

```
R1#sh ip route static 
S    192.168.4.0/24 [1/0] via 10.0.12.2

R1#sh ip route 192.168.4.0 255.255.255.0
Routing entry for 192.168.4.0/24
Known via "static", distance 1, metric 0
  Routing Descriptor Blocks:
  * 10.0.12.2
      Route metric is 0, traffic share count is 1

R1#
```

## Summary Route

![alt text](/docs/CCNA/img/static_route_2.png)

* __R1__
```
no ip route 192.168.4.0 255.255.255.0 10.0.12.2
ip route 192.168.4.0 255.255.252.0 10.0.12.2
```

__Verify__

```
R1#sh ip route static 
S    192.168.4.0/22 [1/0] via 10.0.12.2

R1#sh ip route 192.168.4.0
Routing entry for 192.168.4.0/22
Known via "static", distance 1, metric 0
  Routing Descriptor Blocks:
  * 10.0.12.2
      Route metric is 0, traffic share count is 1

R1#
```

## Host Route

![alt text](/docs/CCNA/img/static_route_3.png)

* __R1__
```
ip route 192.168.200.2 255.255.255.255 10.0.12.2
```

* __R2__
```
ip route 192.168.100.2 255.255.255.255 10.0.12.1
```

__Verify__

```
R1#sh ip route static
S    192.168.4.0/22 [1/0] via 10.0.12.2
     192.168.200.0/32 is subnetted, 1 subnets
S       192.168.200.2 [1/0] via 10.0.12.2

R1#sh ip route 192.168.200.2 255.255.255.255
Routing entry for 192.168.200.2/32
Known via "static", distance 1, metric 0
  Routing Descriptor Blocks:
  * 10.0.12.2
      Route metric is 0, traffic share count is 1

R1#
```

## Default route

* __R1__
```
no ip route 192.168.4.0 255.255.252.0 10.0.12.2
no ip route 192.168.200.2 255.255.255.255 10.0.12.2
ip route 0.0.0.0 0.0.0.0 10.0.12.2
```

* __R2__
```
no ip route 192.168.1.0 255.255.255.0 10.0.12.1
no ip route 192.168.100.2 255.255.255.255 10.0.12.1
ip route 0.0.0.0 0.0.0.0 10.0.12.1
```

__Verify__

```
R1#sh ip route
Codes: C - connected, S - static, I - IGRP, R - RIP, M - mobile, B - BGP
       D - EIGRP, EX - EIGRP external, O - OSPF, IA - OSPF inter area
       N1 - OSPF NSSA external type 1, N2 - OSPF NSSA external type 2
       E1 - OSPF external type 1, E2 - OSPF external type 2, E - EGP
       i - IS-IS, L1 - IS-IS level-1, L2 - IS-IS level-2, ia - IS-IS inter area
       * - candidate default, U - per-user static route, o - ODR
       P - periodic downloaded static route

Gateway of last resort is 10.0.12.2 to network 0.0.0.0

     10.0.0.0/24 is subnetted, 1 subnets
C       10.0.12.0 is directly connected, GigabitEthernet0/0
C    192.168.1.0/24 is directly connected, GigabitEthernet2/0
C    192.168.100.0/24 is directly connected, GigabitEthernet3/0
S*   0.0.0.0/0 [1/0] via 10.0.12.2

R1#
```

## Load Balancing

![alt text](/docs/CCNA/img/static_route_4.png)

* __R1__
```
ip route 0.0.0.0 0.0.0.0 10.0.12.2
ip route 0.0.0.0 0.0.0.0 10.0.120.2
```

* __R2__
```
ip route 0.0.0.0 0.0.0.0 10.0.12.1
ip route 0.0.0.0 0.0.0.0 10.0.120.1
```

__Verify__

```
R1#sh ip route
Codes: C - connected, S - static, I - IGRP, R - RIP, M - mobile, B - BGP
       D - EIGRP, EX - EIGRP external, O - OSPF, IA - OSPF inter area
       N1 - OSPF NSSA external type 1, N2 - OSPF NSSA external type 2
       E1 - OSPF external type 1, E2 - OSPF external type 2, E - EGP
       i - IS-IS, L1 - IS-IS level-1, L2 - IS-IS level-2, ia - IS-IS inter area
       * - candidate default, U - per-user static route, o - ODR
       P - periodic downloaded static route

Gateway of last resort is 10.0.12.2 to network 0.0.0.0

     10.0.0.0/24 is subnetted, 2 subnets
C       10.0.12.0 is directly connected, GigabitEthernet0/0
C       10.0.120.0 is directly connected, GigabitEthernet1/0
C    192.168.1.0/24 is directly connected, GigabitEthernet2/0
C    192.168.100.0/24 is directly connected, GigabitEthernet3/0
S*   0.0.0.0/0 [1/0] via 10.0.12.2
               [1/0] via 10.0.120.2

R1#
```

## Floating Static Route

* __R1__
```
ip route 0.0.0.0 0.0.0.0 10.0.12.2
ip route 0.0.0.0 0.0.0.0 10.0.120.2 5
ip route 192.168.200.2 255.255.255.255 10.0.120.2
```

* __R2__
```
ip route 0.0.0.0 0.0.0.0 10.0.12.1
ip route 0.0.0.0 0.0.0.0 10.0.120.1 5
ip route 192.168.100.2 255.255.255.255 10.0.120.1
```

__Verify__

```
R1(config)#do sh ip route static
     192.168.200.0/32 is subnetted, 1 subnets
S       192.168.200.2 [1/0] via 10.0.120.2
S*   0.0.0.0/0 [1/0] via 10.0.12.2

R1(config)#int gi0/0
R1(config-if)#shut

R1(config-if)#
%LINK-5-CHANGED: Interface GigabitEthernet0/0, changed state to administratively down

%LINEPROTO-5-UPDOWN: Line protocol on Interface GigabitEthernet0/0, changed state to down

R1(config-if)#do sh ip route static
     192.168.200.0/32 is subnetted, 1 subnets
S       192.168.200.2 [1/0] via 10.0.120.2
S*   0.0.0.0/0 [5/0] via 10.0.120.2

R1(config-if)#
```
