---
layout: default
title: L3VPN
nav_order: 3.55
has_children: false
---

# Layer 3 Virtual Private Network
{: .no_toc }

Dịch vụ Mạng riêng ảo lớp 3
{: .fs-6 .fw-300 }

---

## TABLE OF CONTENTS
{: .no_toc .text-delta }

1. TOC
{:toc}

---

## Sơ đồ

![](/docs/L3VPN/img/l3vpn.png)

## Cấu hình

## SRT1

```
enable
conf t
!
no ip domain-lookup
host SRT1
!
int Loopback0
  ip addr 10.132.0.1 255.255.255.255
int e0/0
  ip addr 10.162.0.25 255.255.255.252
  no shut
!
! ========================================================================
! Khai bao OSPF
! ========================================================================
router ospf 2
  router-id 10.132.0.1
  passive-interface Loopback0
  network 10.132.0.1 0.0.0.0 area 1
  network 10.162.0.25 0.0.0.0 area 1
!
int e0/0
  ip ospf network point-to-point
  ip ospf cost 100
!
! ========================================================================
! Khai bao BGP
! ========================================================================
ip bgp-community new-format
!
route-map COMMMUNITY_SRT_LOOPBACK0 permit 100
  set community 7552:800
!
router bgp 7552
!
  bgp router-id 10.132.0.1
  neighbor SRT_TO_AGG peer-group
  neighbor SRT_TO_AGG remote-as 7552
  neighbor SRT_TO_AGG update-source Loopback0
  neighbor 10.134.0.1 peer-group SRT_TO_AGG
  !
  address-family ipv4
    network 10.132.0.1 mask 255.255.255.255 route-map COMMMUNITY_SRT_LOOPBACK0
    neighbor SRT_TO_AGG send-community both
    neighbor 10.134.0.1 activate
  !
  address-family vpnv4
    neighbor 10.134.0.1 activate
  !
!
! ========================================================================
! Khai bao L3VPN
! ========================================================================
ip vrf L3VPN
  rd 7552:500
  route-target export 7552:501
  route-target import 7552:502
!
interface lo501
  ip vrf forwarding L3VPN
  ip address 172.16.40.1 255.255.255.0
!
router bgp 7552
  address-family ipv4 vrf L3VPN
    network 172.16.40.0 mask 255.255.255.0
  exit-address-family
!
! ========================================================================
! Khai bao MPLS
! ========================================================================
int range e0/0-3
  mpls ip
!
! ========================================================================
! Tat tinh nang go nhan LDP tai hop cuoi (Penultimate Hop) de duy tri 
! gia tri QoS trong nhan LDP dam bao thuc hien QoS toan trinh.
! ========================================================================
mpls ldp explicit-null
!
! Dung ping/trace mpls
mpls oam
!
end
write
```

## AGG1

```
enable
conf t
!
no ip domain lookup
host AGG1
!
int Loopback0
  ip addr 10.134.0.1 255.255.255.255
int e0/0
  ip addr 10.164.0.13 255.255.255.252
  no shut
int e0/1
  ip addr 10.162.0.26 255.255.255.252
  no shut
!
! ========================================================================
! Khai bao OSPF
! ========================================================================
router ospf 2
  router-id 10.134.0.1
  passive-interface Loopback0
  network 10.134.0.1 0.0.0.0 area 0
!
int e0/0
  ip ospf 2 area 0
  ip ospf network point-to-point
  ip ospf cost 10000
!
int e0/1
  ip ospf 2 area 1
  ip ospf network point-to-point
  ip ospf cost 100
!
! ========================================================================
! Khai bao Filtering LSA Type 3 giua Area 0 va Area khac 0
! ========================================================================
ip prefix-list AREA_0_TO_AREA_N permit 10.134.0.1/32
ip prefix-list AREA_0_TO_AREA_N deny 0.0.0.0/0 le 32
ip prefix-list AREA_N_TO_AREA_0 deny 0.0.0.0/0 le 32
!
router ospf 2
area 0 filter-list prefix AREA_N_TO_AREA_0 in
area 1 filter-list prefix AREA_0_TO_AREA_N in
!
! ========================================================================
! Khai bao BGP
! ========================================================================
ip bgp-community new-format
!
route-map DENY_ALL deny 100
!
router bgp 7552
!
  bgp router-id 10.134.0.1
  !
  neighbor AGG_TO_SRT peer-group
  neighbor AGG_TO_SRT remote-as 7552
  neighbor AGG_TO_SRT update-source Loopback0
  neighbor 10.132.0.1 peer-group AGG_TO_SRT
  !
  neighbor AGG_TO_CT peer-group
  neighbor AGG_TO_CT remote-as 7552
  neighbor AGG_TO_CT update-source Loopback0
  neighbor 10.136.0.11 peer-group AGG_TO_CT
  !
  address-family ipv4
  !
    network 10.134.0.1 mask 255.255.255.255
    !
    neighbor AGG_TO_SRT route-reflector-client
    neighbor AGG_TO_SRT send-community both
    neighbor AGG_TO_SRT next-hop-self all
    neighbor AGG_TO_SRT route-map DENY_ALL out
    neighbor 10.132.0.1 activate
    !
    neighbor AGG_TO_SRT send-community both
    neighbor AGG_TO_SRT next-hop-self all
    neighbor 10.136.0.11 activate
  !
  address-family vpnv4
    neighbor AGG_TO_SRT route-reflector-client
    neighbor AGG_TO_SRT next-hop-self all
    neighbor 10.132.0.1 activate
    !
    neighbor AGG_TO_CT next-hop-self all
    neighbor 10.136.0.11 activate
  !
!
! ========================================================================
! Khai bao MPLS
! ========================================================================
int range e0/0-3
  mpls ip
!
! ========================================================================
! Tat tinh nang go nhan LDP tai hop cuoi (Penultimate Hop) de duy tri 
! gia tri QoS trong nhan LDP dam bao thuc hien QoS toan trinh.
! ========================================================================
mpls ldp explicit-null
!
! Dung ping/trace mpls
mpls oam
!
end
write
```

## CT1

```
enable
conf t
!
no ip domain lookup
host CT1
!
int Loopback0
  ip addr 10.136.0.11 255.255.255.255
int e0/0
  ip addr 10.166.0.5 255.255.255.252
  no shut
int e0/1
  ip addr 10.164.0.14 255.255.255.252
  no shut
!
! ========================================================================
! Khai bao OSPF
! ========================================================================
router ospf 1
  router-id 10.136.0.11
router ospf 2
  router-id 10.136.0.11
  passive-interface Loopback0
  network 10.136.0.11 0.0.0.0 area 0
!
int e0/0
  ip ospf 1 area 0
  ip ospf network point-to-point
  ip ospf cost 2000
!
int e0/1
  ip ospf 2 area 0
  ip ospf network point-to-point
  ip ospf cost 10000
!
! ========================================================================
! Khai bao quang ba Loopback 0 CT vao OSPF Process 1
! ========================================================================
ip prefix-list LOOPBACK0_CT permit 10.136.0.11/32
!
route-map PROCESS_ME_TO_PROCESS_CORE permit 10
  match ip address prefix-list LOOPBACK0_CT
!
router ospf 1
  redistribute ospf 2 metric-type 1 route-map PROCESS_ME_TO_PROCESS_CORE
!
! ========================================================================
! Khai bao BGP
! ========================================================================
ip bgp-community new-format
!
ip community-list standard COMMMUNITY_SRT_LOOPBACK0 permit 7552:800
!
route-map CT_TO_AGG_IPV4 deny 100
  match community COMMMUNITY_SRT_LOOPBACK0
route-map CT_TO_AGG_IPV4 permit 1000
!
router bgp 7552
!
  bgp router-id 10.136.0.11
  !
  neighbor CT_TO_AGG peer-group
  neighbor CT_TO_AGG remote-as 7552
  neighbor CT_TO_AGG update-source Loopback0
  neighbor 10.134.0.1 peer-group CT_TO_AGG
  !
  neighbor CT_TO_RR peer-group
  neighbor CT_TO_RR remote-as 7552
  neighbor CT_TO_RR update-source Loopback0
  neighbor 10.255.0.1 peer-group CT_TO_RR
  !
  address-family ipv4
  !
    network 10.136.0.11 mask 255.255.255.255
    !
    neighbor CT_TO_AGG route-reflector-client
    neighbor CT_TO_AGG send-community both
    neighbor CT_TO_AGG next-hop-self all
    neighbor 10.134.0.1 activate
    !
    neighbor CT_TO_RR send-community both
    neighbor CT_TO_RR next-hop-self all
    neighbor 10.255.0.1 activate
  !
  address-family vpnv4
    neighbor CT_TO_AGG route-reflector-client
    neighbor CT_TO_AGG next-hop-self all
    neighbor 10.134.0.1 activate
    !
    neighbor CT_TO_RR next-hop-self all
    neighbor 10.255.0.1 activate
  !
!
! ========================================================================
! Khai bao MPLS
! ========================================================================
int range e0/0-3
  mpls ip
!
! ========================================================================
! Tat tinh nang go nhan LDP tai hop cuoi (Penultimate Hop) de duy tri 
! gia tri QoS trong nhan LDP dam bao thuc hien QoS toan trinh.
! ========================================================================
mpls ldp explicit-null
!
! Dung ping/trace mpls
mpls oam
!
end
write
```

## CTx

```
enable
conf t
!
no ip domain lookup
host CTx
!
int Loopback0
  ip addr 10.136.0.13 255.255.255.255
int e0/0
  ip addr 10.166.0.14 255.255.255.252
  no shut
int e0/1
  ip addr 10.164.0.14 255.255.255.252
  no shut
!
! ========================================================================
! Khai bao OSPF
! ========================================================================
router ospf 1
  router-id 10.136.0.13
router ospf 2
  router-id 10.136.0.13
  passive-interface Loopback0
  network 10.136.0.13 0.0.0.0 area 0
!
int e0/0
  ip ospf 1 area 0
  ip ospf network point-to-point
!
int e0/1
  ip ospf 2 area 0
  ip ospf network point-to-point
!
! ========================================================================
! Khai bao quang ba Loopback 0 CT vao OSPF Process 1
! ========================================================================
ip prefix-list LOOPBACK0_CT permit 10.136.0.13/32
!
route-map PROCESS_ME_TO_PROCESS_CORE permit 10
  match ip address prefix-list LOOPBACK0_CT
!
router ospf 1
  redistribute ospf 2 route-map PROCESS_ME_TO_PROCESS_CORE
!
! ========================================================================
! Khai bao BGP
! ========================================================================
ip bgp-community new-format
!
ip community-list standard COMMMUNITY_SRT_LOOPBACK0 permit 7552:800
!
route-map CT_TO_AGG_IPV4 deny 100
  match community COMMMUNITY_SRT_LOOPBACK0
route-map CT_TO_AGG_IPV4 permit 1000
!
router bgp 7552
!
  bgp router-id 10.136.0.13
  !
  neighbor CT_TO_AGG peer-group
  neighbor CT_TO_AGG remote-as 7552
  neighbor CT_TO_AGG update-source Loopback0
  neighbor 10.134.1.1 peer-group CT_TO_AGG
  !
  neighbor CT_TO_RR peer-group
  neighbor CT_TO_RR remote-as 7552
  neighbor CT_TO_RR update-source Loopback0
  neighbor 10.255.0.1 peer-group CT_TO_RR
  !
  address-family ipv4
  !
    network 10.136.0.13 mask 255.255.255.255
    !
    neighbor CT_TO_AGG route-reflector-client
    neighbor CT_TO_AGG send-community both
    neighbor CT_TO_AGG next-hop-self all
    neighbor 10.134.1.1 activate
    !
    neighbor CT_TO_RR send-community both
    neighbor CT_TO_RR next-hop-self all
    neighbor 10.255.0.1 activate
  !
  address-family vpnv4
    neighbor CT_TO_AGG route-reflector-client
    neighbor CT_TO_AGG next-hop-self all
    neighbor 10.134.1.1 activate
    !
    neighbor CT_TO_RR next-hop-self all
    neighbor 10.255.0.1 activate
  !
!
! ========================================================================
! Khai bao MPLS
! ========================================================================
int range e0/0-3
  mpls ip
!
! ========================================================================
! Tat tinh nang go nhan LDP tai hop cuoi (Penultimate Hop) de duy tri 
! gia tri QoS trong nhan LDP dam bao thuc hien QoS toan trinh.
! ========================================================================
mpls ldp explicit-null
!
! Dung ping/trace mpls
mpls oam
!
end
write
```

## AGGx

```
enable
conf t
!
no ip domain lookup
host AGGx
!
int Loopback0
  ip addr 10.134.1.1 255.255.255.255
int e0/1
  ip addr 10.162.0.26 255.255.255.252
  no shut
int e0/0
  ip addr 10.164.0.13 255.255.255.252
  no shut
!
! ========================================================================
! Khai bao OSPF
! ========================================================================
router ospf 2
  router-id 10.134.1.1
  passive-interface Loopback0
  network 10.134.1.1 0.0.0.0 area 0
!
int e0/0
  ip ospf 2 area 0
  ip ospf network point-to-point
!
int e0/1
  ip ospf 2 area 1
  ip ospf network point-to-point
!
! ========================================================================
! Khai bao Filtering LSA Type 3 giua Area 0 va Area khac 0
! ========================================================================
ip prefix-list AREA_0_TO_AREA_N permit 10.134.1.1/32
ip prefix-list AREA_0_TO_AREA_N deny 0.0.0.0/0 le 32
ip prefix-list AREA_N_TO_AREA_0 deny 0.0.0.0/0 le 32
!
router ospf 2
area 0 filter-list prefix AREA_N_TO_AREA_0 in
area 1 filter-list prefix AREA_0_TO_AREA_N in
!
! ========================================================================
! Khai bao BGP
! ========================================================================
ip bgp-community new-format
!
route-map DENY_ALL deny 100
!
router bgp 7552
!
  bgp router-id 10.134.1.1
  !
  neighbor AGG_TO_SRT peer-group
  neighbor AGG_TO_SRT remote-as 7552
  neighbor AGG_TO_SRT update-source Loopback0
  neighbor 10.132.1.1 peer-group AGG_TO_SRT
  !
  neighbor AGG_TO_CT peer-group
  neighbor AGG_TO_CT remote-as 7552
  neighbor AGG_TO_CT update-source Loopback0
  neighbor 10.136.0.13 peer-group AGG_TO_CT
  !
  address-family ipv4
  !
    network 10.134.1.1 mask 255.255.255.255
    !
    neighbor AGG_TO_SRT route-reflector-client
    neighbor AGG_TO_SRT send-community both
    neighbor AGG_TO_SRT next-hop-self all
    neighbor AGG_TO_SRT route-map DENY_ALL out
    neighbor 10.132.1.1 activate
    !
    neighbor AGG_TO_CT next-hop-self all
    neighbor AGG_TO_CT send-community both
    neighbor 10.136.0.13 activate
  !
  address-family vpnv4
    neighbor AGG_TO_SRT route-reflector-client
    neighbor AGG_TO_SRT next-hop-self all
    neighbor 10.132.1.1 activate
    !
    neighbor AGG_TO_CT next-hop-self all
    neighbor 10.136.0.13 activate
  !
!
! ========================================================================
! Khai bao MPLS
! ========================================================================
int range e0/0-3
  mpls ip
!
! ========================================================================
! Tat tinh nang go nhan LDP tai hop cuoi (Penultimate Hop) de duy tri 
! gia tri QoS trong nhan LDP dam bao thuc hien QoS toan trinh.
! ========================================================================
mpls ldp explicit-null
!
! Dung ping/trace mpls
mpls oam
!
end
write
```

## SRTx

```
enable
conf t
!
no ip domain-lookup
host SRTx
!
int Loopback0
  ip addr 10.132.1.1 255.255.255.255
int e0/0
  ip addr 10.162.0.25 255.255.255.252
  no shut
!
! ========================================================================
! Khai bao OSPF
! ========================================================================
router ospf 2
  router-id 10.132.1.1
  passive-interface Loopback0
  network 10.132.1.1 0.0.0.0 area 1
  network 10.162.0.25 0.0.0.0 area 1
!
int e0/0
  ip ospf network point-to-point
!
! ========================================================================
! Khai bao BGP
! ========================================================================
ip bgp-community new-format
!
route-map COMMMUNITY_SRT_LOOPBACK0 permit 100
  set community 7552:800
!
router bgp 7552
!
  bgp router-id 10.132.1.1
  neighbor SRT_TO_AGG peer-group
  neighbor SRT_TO_AGG remote-as 7552
  neighbor SRT_TO_AGG update-source Loopback0
  neighbor 10.134.1.1 peer-group SRT_TO_AGG
  !
  address-family ipv4
    network 10.132.1.1 mask 255.255.255.255 route-map COMMMUNITY_SRT_LOOPBACK0
    neighbor SRT_TO_AGG send-community both
    neighbor 10.134.1.1 activate
  !
  address-family vpnv4
    neighbor 10.134.1.1 activate
  !
!
! ========================================================================
! Khai bao L3VPN
! ========================================================================
ip vrf L3VPN
  rd 7552:500
  route-target export 7552:502
  route-target import 7552:501
!
interface lo502
  ip vrf forwarding L3VPN
  ip address 172.16.140.1 255.255.255.0
!
router bgp 7552
  address-family ipv4 vrf L3VPN
    network 172.16.140.0 mask 255.255.255.0
  exit-address-family
!
! ========================================================================
! Khai bao MPLS
! ========================================================================
int range e0/0-3
  mpls ip
!
! ========================================================================
! Tat tinh nang go nhan LDP tai hop cuoi (Penultimate Hop) de duy tri 
! gia tri QoS trong nhan LDP dam bao thuc hien QoS toan trinh.
! ========================================================================
mpls ldp explicit-null
!
! Dung ping/trace mpls
mpls oam
!
end
write
```

## CKV

```
enable
conf t
!
no ip domain-lookup
host CKV
!
int Loopback0
  ip addr 10.136.0.1 255.255.255.255
int e0/0
  ip addr 10.166.0.253 255.255.255.252
  no shut
int e0/1
  ip addr 10.166.0.6 255.255.255.252
  no shut
int e0/3
  ip addr 10.166.0.13 255.255.255.252
  no shut
!
! ========================================================================
! Khai bao OSPF
! ========================================================================
router ospf 1
  router-id 10.136.0.1
  network 0.0.0.0 0.0.0.0 area 0
!
int range e0/0-3
  ip ospf network point-to-point
!
! ========================================================================
! Khai bao MPLS
! ========================================================================
int range e0/0-3
  mpls ip
!
! ========================================================================
! Tat tinh nang go nhan LDP tai hop cuoi (Penultimate Hop) de duy tri 
! gia tri QoS trong nhan LDP dam bao thuc hien QoS toan trinh.
! ========================================================================
mpls ldp explicit-null
!
! Dung ping/trace mpls
mpls oam
!
end
write
```

## RR

```
enable
conf t
!
no ip domain lookup
host RR
!
int Loopback0
  ip addr 10.255.0.1 255.255.255.255
int e0/0
  ip addr 10.166.0.254 255.255.255.252
  no shut
!
! ========================================================================
! Khai bao OSPF
! ========================================================================
router ospf 1
  router-id 10.255.0.1
  passive-interface Loopback0
  network 10.255.0.1 0.0.0.0 area 0
!
int e0/0
  ip ospf 1 area 0
  ip ospf network point-to-point
!
! ========================================================================
! Khai bao BGP
! ========================================================================
ip bgp-community new-format
!
router bgp 7552
!
  bgp router-id 10.255.0.1
  !
  neighbor RR_TO_CT peer-group
  neighbor RR_TO_CT remote-as 7552
  neighbor RR_TO_CT update-source Loopback0
  neighbor 10.136.0.11 peer-group RR_TO_CT
  neighbor 10.136.0.13 peer-group RR_TO_CT
  !
  address-family ipv4
  !
    neighbor RR_TO_CT route-reflector-client
    neighbor RR_TO_CT send-community both
    neighbor 10.136.0.11 activate
    neighbor 10.136.0.13 activate
  !
  address-family vpnv4
  !
    neighbor RR_TO_CT route-reflector-client
    neighbor 10.136.0.11 activate
    neighbor 10.136.0.13 activate
  !
!
! ========================================================================
! Khai bao MPLS
! ========================================================================
int range e0/0-3
  mpls ip
!
! ========================================================================
! Tat tinh nang go nhan LDP tai hop cuoi (Penultimate Hop) de duy tri 
! gia tri QoS trong nhan LDP dam bao thuc hien QoS toan trinh.
! ========================================================================
mpls ldp explicit-null
!
! Dung ping/trace mpls
mpls oam
!
end
write
```
