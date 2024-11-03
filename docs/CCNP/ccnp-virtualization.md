---
layout: default
title: Virtualization
nav_order: 120
parent: CCNP
---

# Virtualization
{: .no_toc }

Ảo hóa
{: .fs-6 .fw-300 }

---

## Table of contents
{: .no_toc .text-delta }

1. TOC
{:toc}

---

## Cisco VRF Virtual Routing and Forwarding
<br>
Với Switch ta có kỹ thuật VLAN chia switch thành nhiều switch nhỏ. Với Router ta có kỹ thuật VRF chia router thành nhiều router nhỏ với các bảng định tuyến khác nhau.

![alt text](/docs/CCNP/img/vrf.avif)

Configuration

```
enable
conf t
!
! Create a VRF instance for our Customer A. Remember that the VRF name is case-sensitive.
vrf definition Cust-A
! Initialize the address family.
address-family ipv4
!
! Associate interfaces with VRF instance.
interface e0/1
no shut
vrf forwarding Cust-A
! Configure the IPv4 address on the interface.
ip address 192.168.1.1 255.255.255.0
!
! Repeat the same process for Customer B
vrf definition Cust-B
address-family ipv4
!
interface e0/2
no shut
vrf forwarding Cust-B
ip address 192.168.1.1 255.255.255.0
!
end
```

Verify

```
Router#sh ip route
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

Router#sh ip route vrf Cust-A

Routing Table: Cust-A
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

      192.168.1.0/24 is variably subnetted, 2 subnets, 2 masks
C        192.168.1.0/24 is directly connected, Ethernet0/1
L        192.168.1.1/32 is directly connected, Ethernet0/1
Router#sh ip route vrf Cust-B

Routing Table: Cust-B
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

      192.168.1.0/24 is variably subnetted, 2 subnets, 2 masks
C        192.168.1.0/24 is directly connected, Ethernet0/2
L        192.168.1.1/32 is directly connected, Ethernet0/2
Router#
```

