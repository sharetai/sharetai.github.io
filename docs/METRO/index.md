---
layout: default
title: METRO
nav_order: 3.2
has_children: true
---

# METRO
{: .no_toc }

Cisco Certified Network Associate
{: .fs-6 .fw-300 }

```plaintext
enable
conf t
no ip domain-lookup
ip routing
host SRT1
int Loopback0
ip addr 10.132.0.1 255.255.255.255
int e0/0
no sw
ip addr 10.162.0.6 255.255.255.252
ip ospf network point-to-point
ip ospf cost 100
int e0/1
no sw
ip addr 10.162.0.9 255.255.255.252
ip ospf network point-to-point
ip ospf cost 100
!
router ospf 2
router-id 10.132.0.1
passive-interface Loopback0
network 10.132.0.1 0.0.0.0 area 1
network 10.162.0.6 0.0.0.0 area 1
network 10.162.0.9 0.0.0.0 area 1
!
router bgp 7552
bgp router-id 10.132.0.1
neighbor SRT_TO_AGG peer-group
neighbor SRT_TO_AGG remote-as 7552
neighbor SRT_TO_AGG update-source Loopback0
neighbor 10.134.0.1 peer-group SRT_TO_AGG
neighbor 10.134.0.2 peer-group SRT_TO_AGG
address-family ipv4
 network 10.132.0.1 mask 255.255.255.255
 neighbor 10.134.0.1 activate
 neighbor 10.134.0.2 activate
exit-address-family
!
!
end

enable
conf t
no ip domain-lookup
ip routing
host SRT2
int Loopback0
ip addr 10.132.0.2 255.255.255.255
int e0/0
no sw
ip addr 10.162.0.10 255.255.255.252
ip ospf network point-to-point
ip ospf cost 100
int e0/1
no sw
ip addr 10.162.0.13 255.255.255.252
ip ospf network point-to-point
ip ospf cost 100
!
router ospf 2
router-id 10.132.0.2
passive-interface Loopback0
network 10.132.0.2 0.0.0.0 area 1
network 10.162.0.10 0.0.0.0 area 1
network 10.162.0.13 0.0.0.0 area 1
!
router bgp 7552
bgp router-id 10.132.0.2
neighbor SRT_TO_AGG peer-group
neighbor SRT_TO_AGG remote-as 7552
neighbor SRT_TO_AGG update-source Loopback0
neighbor 10.134.0.1 peer-group SRT_TO_AGG
neighbor 10.134.0.2 peer-group SRT_TO_AGG
address-family ipv4
 network 10.132.0.2 mask 255.255.255.255
 neighbor 10.134.0.1 activate
 neighbor 10.134.0.2 activate
exit-address-family
!
end

enable
conf t
no ip domain-lookup
ip routing
host SRT3
int Loopback0
ip addr 10.132.0.3 255.255.255.255
int e0/0
no sw
ip addr 10.162.0.14 255.255.255.252
ip ospf network point-to-point
ip ospf cost 100
int e0/1
no sw
ip addr 10.162.0.17 255.255.255.252
ip ospf network point-to-point
ip ospf cost 100
!
router ospf 2
router-id 10.132.0.3
passive-interface Loopback0
network 10.132.0.3 0.0.0.0 area 1
network 10.162.0.14 0.0.0.0 area 1
network 10.162.0.17 0.0.0.0 area 1
!
router bgp 7552
bgp router-id 10.132.0.3
neighbor SRT_TO_AGG peer-group
neighbor SRT_TO_AGG remote-as 7552
neighbor SRT_TO_AGG update-source Loopback0
neighbor 10.134.0.1 peer-group SRT_TO_AGG
neighbor 10.134.0.2 peer-group SRT_TO_AGG
address-family ipv4
 network 10.132.0.3 mask 255.255.255.255
 neighbor 10.134.0.1 activate
 neighbor 10.134.0.2 activate
exit-address-family
!
end

enable
conf t
no ip domain-lookup
ip routing
host SRT4
int Loopback0
ip addr 10.132.0.4 255.255.255.255
int e0/0
no sw
ip addr 10.162.0.18 255.255.255.252
ip ospf network point-to-point
ip ospf cost 100
int e0/1
no sw
ip addr 10.162.0.21 255.255.255.252
ip ospf network point-to-point
ip ospf cost 100
!
router ospf 2
router-id 10.132.0.4
passive-interface Loopback0
network 10.132.0.4 0.0.0.0 area 1
network 10.162.0.18 0.0.0.0 area 1
network 10.162.0.21 0.0.0.0 area 1
!
router bgp 7552
bgp router-id 10.132.0.4
neighbor SRT_TO_AGG peer-group
neighbor SRT_TO_AGG remote-as 7552
neighbor SRT_TO_AGG update-source Loopback0
neighbor 10.134.0.1 peer-group SRT_TO_AGG
neighbor 10.134.0.2 peer-group SRT_TO_AGG
address-family ipv4
 network 10.132.0.4 mask 255.255.255.255
 neighbor 10.134.0.1 activate
 neighbor 10.134.0.2 activate
exit-address-family
!
end

enable
conf t
no ip domain-lookup
ip routing
host SRT5
int Loopback0
ip addr 10.132.0.5 255.255.255.255
int e0/0
no sw
ip addr 10.162.0.22 255.255.255.252
ip ospf network point-to-point
ip ospf cost 100
int e0/1
no sw
ip addr 10.162.0.25 255.255.255.252
ip ospf network point-to-point
ip ospf cost 100
!
router ospf 2
router-id 10.132.0.5
passive-interface Loopback0
network 10.132.0.5 0.0.0.0 area 1
network 10.162.0.22 0.0.0.0 area 1
network 10.162.0.25 0.0.0.0 area 1
!
router bgp 7552
bgp router-id 10.132.0.5
neighbor SRT_TO_AGG peer-group
neighbor SRT_TO_AGG remote-as 7552
neighbor SRT_TO_AGG update-source Loopback0
neighbor 10.134.0.1 peer-group SRT_TO_AGG
neighbor 10.134.0.2 peer-group SRT_TO_AGG
address-family ipv4
 network 10.132.0.5 mask 255.255.255.255
 neighbor 10.134.0.1 activate
 neighbor 10.134.0.2 activate
exit-address-family
!
end

conf t
!
no ip domain-lookup
host AGG1
!
int Loopback0
ip addr 10.134.0.1 255.255.255.255
int gi0/0/0/1.11
encapsulation dot1Q 11
ip addr 10.162.0.1 255.255.255.252
no shut
int gi0/0/0/2
ip addr 10.162.0.5 255.255.255.252
no shut
int gi0/0/0/0
ip addr 10.164.0.13 255.255.255.252
no shut
int gi0/0/0/1
ip addr 10.164.0.10 255.255.255.252
no shut
!
router ospf 2
router-id 10.134.0.1
area 0
 int Loopback0
  passive enable
 int gi0/0/0/0
  network point-to-point
  cost 10000
 int gi0/0/0/1
  network point-to-point
  cost 2000
area 1
 int gi0/0/0/1.11
  network point-to-point
  cost 10
 int gi0/0/0/2
  network point-to-point
  cost 100
!
route-policy AREA_0_TO_AREA_N
 if destination in (10.134.0.1) then
  pass
 else
  drop
 endif
end-policy
route-policy AREA_N_TO_AREA_0
 drop
end-policy
!
router ospf 2
 area 0
  route-policy AREA_N_TO_AREA_0 in
 area 1
  route-policy AREA_0_TO_AREA_N in
!
router bgp 7552
bgp router-id 10.134.0.1
address-family ipv4 unicast
neighbor-group AGG_TO_SRT
 remote-as 7552
 update-source Loopback0
 address-family ipv4 unicast route-reflector-client
 address-family ipv4 unicast next-hop-self
neighbor-group AGG_TO_CT
 remote-as 7552
 update-source Loopback0
 address-family ipv4 unicast
 address-family ipv4 unicast next-hop-self
neighbor 10.132.0.1
 use neighbor-group AGG_TO_SRT
neighbor 10.132.0.2
 use neighbor-group AGG_TO_SRT
neighbor 10.132.0.3
 use neighbor-group AGG_TO_SRT
neighbor 10.132.0.4
 use neighbor-group AGG_TO_SRT
neighbor 10.132.0.5
 use neighbor-group AGG_TO_SRT
neighbor 10.136.0.11
 use neighbor-group AGG_TO_CT
neighbor 10.136.0.12
 use neighbor-group AGG_TO_CT
!
commit
end

conf t
!
no ip domain-lookup
host AGG2
!
int Loopback0
ip addr 10.134.0.2 255.255.255.255
int gi0/0/0/1.11
encapsulation dot1Q 11
ip addr 10.162.0.2 255.255.255.252
no shut
int gi0/0/0/2
ip addr 10.162.0.26 255.255.255.252
no shut
int gi0/0/0/0
ip addr 10.164.0.6 255.255.255.252
no shut
int gi0/0/0/1
ip addr 10.164.0.9 255.255.255.252
no shut
!
router ospf 2
router-id 10.134.0.2
no area 0
area 0
 int Loopback0
  passive enable
 int gi0/0/0/0
  network point-to-point
  cost 10000
 int gi0/0/0/1
  network point-to-point
  cost 2000
area 1
 int gi0/0/0/1.11
  network point-to-point
  cost 10
 int gi0/0/0/2
  network point-to-point
  cost 100
!
route-policy AREA_0_TO_AREA_N
 if destination in (10.134.0.2) then
  pass
 else
  drop
 endif
end-policy
route-policy AREA_N_TO_AREA_0
 drop
end-policy
!
router ospf 2
 area 0
  route-policy AREA_N_TO_AREA_0 in
 area 1
  route-policy AREA_0_TO_AREA_N in
!
router bgp 7552
bgp router-id 10.134.0.2
address-family ipv4 unicast
neighbor-group AGG_TO_SRT
 remote-as 7552
 update-source Loopback0
 address-family ipv4 unicast route-reflector-client
 address-family ipv4 unicast next-hop-self
neighbor-group AGG_TO_CT
 remote-as 7552
 update-source Loopback0
 address-family ipv4 unicast
 address-family ipv4 unicast next-hop-self
neighbor 10.132.0.1
 use neighbor-group AGG_TO_SRT
neighbor 10.132.0.2
 use neighbor-group AGG_TO_SRT
neighbor 10.132.0.3
 use neighbor-group AGG_TO_SRT
neighbor 10.132.0.4
 use neighbor-group AGG_TO_SRT
neighbor 10.132.0.5
 use neighbor-group AGG_TO_SRT
neighbor 10.136.0.11
 use neighbor-group AGG_TO_CT
neighbor 10.136.0.12
 use neighbor-group AGG_TO_CT
!
commit
end

conf t
no ip domain-lookup
host CT1
int Loopback0
ip addr 10.136.0.11 255.255.255.255
no int gi0/0/0/1 shut
int gi0/0/0/1.200
encapsulation dot1Q 200
ip addr 10.164.0.1 255.255.255.252
no shut
int gi0/0/0/2
ip addr 10.164.0.14 255.255.255.252
no shut
!
router ospf 2
router-id 10.136.0.11
area 0
 int Loopback0
  passive enable
 int gi0/0/0/1.200
  network point-to-point
  cost 500
 int gi0/0/0/2
  network point-to-point
  cost 10000
!
router bgp 7552
bgp router-id 10.136.0.11
address-family ipv4 unicast
neighbor-group CT_TO_AGG
 remote-as 7552
 update-source Loopback0
 address-family ipv4 unicast route-reflector-client
 address-family ipv4 unicast next-hop-self
neighbor 10.134.0.1
 use neighbor-group CT_TO_AGG
neighbor 10.134.0.2
 use neighbor-group CT_TO_AGG
!
commit
end

conf t
no ip domain-lookup
host CT2
int Loopback0
ip addr 10.136.0.12 255.255.255.255
no int gi0/0/0/1 shut
int gi0/0/0/1.200
encapsulation dot1Q 200
ip addr 10.164.0.2 255.255.255.252
no shut
int gi0/0/0/2
ip addr 10.164.0.5 255.255.255.252
no shut
!
router ospf 2
router-id 10.136.0.12
area 0
 int Loopback0
  passive enable
 int gi0/0/0/1.200
  network point-to-point
  cost 500
 int gi0/0/0/2
  network point-to-point
  cost 10000
!
router bgp 7552
bgp router-id 10.136.0.12
address-family ipv4 unicast
neighbor-group CT_TO_AGG
 remote-as 7552
 update-source Loopback0
 address-family ipv4 unicast route-reflector-client
 address-family ipv4 unicast next-hop-self
neighbor 10.134.0.1
 use neighbor-group CT_TO_AGG
neighbor 10.134.0.2
 use neighbor-group CT_TO_AGG
!
commit
end
```
