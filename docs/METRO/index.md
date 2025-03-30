---
layout: default
title: METRO
nav_order: 3.2
has_children: false
---

# METRO
{: .no_toc }

METRO
{: .fs-6 .fw-300 }

---

## Table of contents
{: .no_toc .text-delta }

1. TOC
{:toc}

---

![alt text](/docs/METRO/img/metro.png)

_*(Build bằng VMware Pro 17.5.0 (search gg sẽ lấy đc key active) + PNETLab + Modem/SRT/BRAS/CKV/PE dùng IOL L3 + AGG/CT/RR dùng CSR1000)_

_*(Build trên CPU Ryzen 3200 + RAM 32Gb <= tham khảo cấu hình trước khi build lab (1 con xrv demo sẽ yêu cầu 3Gb ram, 1 con csr sẽ yêu cầu 6Gb ram; IOL ko yêu cầu ram nhiều))_

_*(Build HSI thì yêu cầu AGG là CSR1000 để chạy VFI/VPLS, CT có thể dùng IOL L3, máy 8Gb sẽ ok)_

_*(Build L3VPN thì AGG/CT/RR có thể dùng IOL L3, máy 4Gb sẽ ok)_

_*(Build L2VPN thì yêu cầu AGG/CT/RR là CSR1000 để chạy bgp address-family l2vpn vpls, máy 32Gb sẽ ok)_

## IP ADDRESS

<h3>SRT1</h3>
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
int e0/1
  ip addr 10.162.0.22 255.255.255.252
  no shut
!
end
write
```

<h3>SRT2</h3>
```
enable
conf t
!
no ip domain-lookup
host SRT2
!
int Loopback0
  ip addr 10.132.0.2 255.255.255.255
int e0/0
  ip addr 10.162.0.21 255.255.255.252
  no shut
int e0/1
  ip addr 10.162.0.18 255.255.255.252
  no shut
!
end
write
```

<h3>SRT3</h3>
```
enable
conf t
!
no ip domain-lookup
host SRT3
!
int Loopback0
  ip addr 10.132.0.3 255.255.255.255
int e0/0
  ip addr 10.162.0.17 255.255.255.252
  no shut
int e0/1
  ip addr 10.162.0.14 255.255.255.252
  no shut
!
end
write
```

<h3>AGG1</h3>
```
enable
conf t
!
no ip domain lookup
host AGG1
!
int Loopback0
  ip addr 10.134.0.1 255.255.255.255
int gi1
  ip addr 10.164.0.13 255.255.255.252
  no shut
int gi2
  ip addr 10.164.0.10 255.255.255.252
  no shut
int gi2.11
  encapsulation dot1Q 11
  ip addr 10.162.0.1 255.255.255.252
  no shut
int gi3
  ip addr 10.162.0.26 255.255.255.252
  no shut
!
end
write
```

<h3>CT1</h3>
```
enable
conf t
!
no ip domain lookup
host CT1
!
int Loopback0
  ip addr 10.136.0.11 255.255.255.255
int gi1
  ip addr 10.166.0.5 255.255.255.252
  no shut
int gi2
  ip addr 10.166.0.1 255.255.255.252
  no shut
int gi2.200
  encapsulation dot1Q 200
  ip addr 10.164.0.1 255.255.255.252
  no shut
int gi3
  ip addr 10.164.0.14 255.255.255.252
  no shut
!
end
write
```

<h3>CTx</h3>
```
enable
conf t
!
no ip domain lookup
host CTx
!
int Loopback0
  ip addr 10.136.0.13 255.255.255.255
int gi1
  ip addr 10.166.0.14 255.255.255.252
  no shut
int gi3
  ip addr 10.164.0.14 255.255.255.252
  no shut
!
end
write
```

<h3>AGGx</h3>

```
enable
conf t
!
no ip domain lookup
host AGGx
!
int Loopback0
  ip addr 10.134.1.1 255.255.255.255
int gi3
  ip addr 10.162.0.26 255.255.255.252
  no shut
int gi1
  ip addr 10.164.0.13 255.255.255.252
  no shut
!
end
write
```

<h3>SRTx</h3>

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
end
write
```

<h3>CKV</h3>
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
int e0/2
  ip addr 10.166.0.10 255.255.255.252
  no shut
int e0/3
  ip addr 10.166.0.13 255.255.255.252
  no shut
int e1/0
  ip addr 10.166.0.17 255.255.255.252
  no shut
int e1/1
  ip addr 10.166.0.21 255.255.255.252
  no shut
int e1/2
  ip addr 10.166.0.25 255.255.255.252
  no shut
!
end
write
```

<h3>RR</h3>
```
enable
conf t
!
no ip domain lookup
host RR
!
int Loopback0
  ip addr 10.255.0.1 255.255.255.255
int gi1
  ip addr 10.166.0.254 255.255.255.252
  no shut
!
end
write
```

<h3>PE</h3>
```
enable
conf t
!
no ip domain-lookup
host PE
!
int Loopback0
  ip addr 10.136.0.5 255.255.255.255
int e0/0
  ip addr 10.166.0.22 255.255.255.252
  no shut
!
end
write
```

<h3>IGW</h3>
```
enable
conf t
!
no ip domain-lookup
host IGW
!
int Loopback0
  ip addr 10.136.0.26 255.255.255.255
int e0/0
  ip addr 10.166.0.26 255.255.255.252
  no shut
int e0/1
  ip addr 8.8.8.1 255.255.255.0
  no shut
!
end
write
```

## OSPF

<h3>SRT1</h3>
```
enable
conf t
!
! ========================================================================
! Khai bao OSPF
! ========================================================================
router ospf 2
  router-id 10.132.0.1
  passive-interface Loopback0
  network 10.132.0.1 0.0.0.0 area 1
  network 10.162.0.25 0.0.0.0 area 1
  network 10.162.0.22 0.0.0.0 area 1
!
int e0/0
  ip ospf network point-to-point
  ip ospf cost 100
int e0/1
  ip ospf network point-to-point
  ip ospf cost 100
!
end
write
```

<h3>SRT2</h3>
```
enable
conf t
!
! ========================================================================
! Khai bao OSPF
! ========================================================================
router ospf 2
  router-id 10.132.0.2
  passive-interface Loopback0
  network 10.132.0.2 0.0.0.0 area 1
  network 10.162.0.21 0.0.0.0 area 1
  network 10.162.0.18 0.0.0.0 area 1
!
int e0/0
  ip ospf network point-to-point
  ip ospf cost 100
int e0/1
  ip ospf network point-to-point
  ip ospf cost 100
!
end
write
```

<h3>SRT3</h3>
```
enable
conf t
!
! ========================================================================
! Khai bao OSPF
! ========================================================================
router ospf 2
  router-id 10.132.0.3
  passive-interface Loopback0
  network 10.132.0.3 0.0.0.0 area 1
  network 10.162.0.17 0.0.0.0 area 1
  network 10.162.0.14 0.0.0.0 area 1
!
int e0/0
  ip ospf network point-to-point
  ip ospf cost 100
int e0/1
  ip ospf network point-to-point
  ip ospf cost 100
!
end
write
```

<h3>AGG1</h3>
```
enable
conf t
!
! ========================================================================
! Khai bao OSPF
! ========================================================================
router ospf 2
  router-id 10.134.0.1
  passive-interface Loopback0
  network 10.134.0.1 0.0.0.0 area 0
!
int gi1
  ip ospf 2 area 0
  ip ospf network point-to-point
  ip ospf cost 10000
int gi2
  ip ospf 2 area 0
  ip ospf network point-to-point
  ip ospf cost 2000
int gi2.11
  ip ospf 2 area 1
  ip ospf network point-to-point
  ip ospf cost 10
int gi3
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
end
write
```

<!-- ```
conf t
!
! ========================================================================
! Khai bao OSPF
! ========================================================================
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
! ========================================================================
! Khai bao Filtering LSA Type 3 giua Area 0 va Area khac 0
! ========================================================================
route-policy AREA_0_TO_AREA_N
  ! Chi cho phep loopback0 cua AGG quang ba vao area srt
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
commit
end
``` -->

<h3>CT1</h3>
```
enable
conf t
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
int gi1
  ip ospf 1 area 0
  ip ospf network point-to-point
  ip ospf cost 2000
int gi2
  ip ospf 1 area 0
  ip ospf network point-to-point
  ip ospf cost 600
int gi2.11
  ip ospf 2 area 0
  ip ospf network point-to-point
  ip ospf cost 500
int gi3
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
end
write
```
<!--<h3>CT1</h3>
```
conf t
!
! ========================================================================
! Khai bao OSPF
! ========================================================================
router ospf 1
  router-id 10.136.0.11
  area 0
    int gi0/0/0/0
      network point-to-point
      cost 2000
    int gi0/0/0/1
      network point-to-point
      cost 600
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
    exit
  exit
exit
!
! ========================================================================
! Khai bao quang ba Loopback 0 CT vao OSPF Process 1
! ========================================================================
route-policy LOOPBACK0_CT
  if destination in (10.136.0.11/32) then
    done
  endif
end-policy
router ospf 1
  redistribute ospf 2 metric-type 1 route-policy LOOPBACK0_CT
!
commit
end
``` -->

<!-- <h3>CT2</h3>
```
conf t
!
! ========================================================================
! Khai bao OSPF
! ========================================================================
router ospf 1
  router-id 10.136.0.12
  area 0
    int gi0/0/0/0
      network point-to-point
      cost 2000
    int gi0/0/0/1
      network point-to-point
      cost 600
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
    exit
  exit
exit
!
! ========================================================================
! Khai bao quang ba Loopback 0 CT vao OSPF Process 1
! ========================================================================
interface Loopback1000
  ipv4 address 255.255.255.255 255.255.255.255
route-policy LOOPBACK0_CT
  if destination in (10.136.0.12/32) then
    done
  endif
end-policy
router ospf 1
  summary-in enable
  redistribute ospf 2 lsa-type summary route-policy LOOPBACK0_CT
  area 1000
    interface Loopback1000
    passive enable
!
commit
end
``` -->

<h3>CTx</h3>
```
enable
conf t
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
int range gi1
  ip ospf 1 area 0
  ip ospf network point-to-point
!
int range gi3
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
end
write
```

<h3>AGGx</h3>
```
enable
conf t
!
! ========================================================================
! Khai bao OSPF
! ========================================================================
router ospf 2
  router-id 10.134.1.1
  passive-interface Loopback0
  network 10.134.1.1 0.0.0.0 area 0
!
int range gi1
  ip ospf 2 area 0
  ip ospf network point-to-point
!
int range gi3
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
end
write
```

<h3>SRTx</h3>
```
enable
conf t
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
end
write
```

<h3>CKV</h3>
```
enable
conf t
!
! ========================================================================
! Khai bao OSPF
! ========================================================================
router ospf 1
  router-id 10.136.0.1
  network 0.0.0.0 0.0.0.0 area 0
!
int range e0/0-3,e1/0-3
  ip ospf network point-to-point
!
end
write
```

<h3>RR</h3>
```
enable
conf t
!
! ========================================================================
! Khai bao OSPF
! ========================================================================
router ospf 1
  router-id 10.255.0.1
  passive-interface Loopback0
  network 10.255.0.1 0.0.0.0 area 0
!
int gi1
  ip ospf 1 area 0
  ip ospf network point-to-point
!
end
write
```

<h3>PE</h3>
```
enable
conf t
!
! ========================================================================
! Khai bao OSPF
! ========================================================================
router ospf 1
  router-id 10.136.0.5
  passive-interface Loopback0
  network 10.136.0.5 0.0.0.0 area 0
!
int e0/0
  ip ospf 1 area 0
  ip ospf network point-to-point
!
end
write
```

<h3>IGW</h3>
```
enable
conf t
!
! ========================================================================
! Khai bao OSPF
! ========================================================================
router ospf 1
  router-id 10.136.0.26
  passive-interface Loopback0
  network 10.136.0.26 0.0.0.0 area 0
!
int e0/0
  ip ospf 1 area 0
  ip ospf network point-to-point
!
end
write
```

## MPLS

<h3>SRT1/SRT2/SRT3/SRT4/SRT5/SRTx</h3>
```
enable
conf t
!
! ========================================================================
! Khai bao MPLS
! ========================================================================
int e0/0
  mpls ip
int e0/1
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

<h3>AGG1/AGGx</h3>
```
enable
conf t
!
! ========================================================================
! Khai bao MPLS
! ========================================================================
int gi1
  mpls ip
int gi2
  mpls ip
int gi2.11
  mpls ip
int gi3
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

<h3>CT1/CTx</h3>
```
enable
conf t
!
! ========================================================================
! Khai bao MPLS
! ========================================================================
int gi1
  mpls ip
int gi2
  mpls ip
int gi2.200
  mpls ip
int gi3
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

<h3>CKV</h3>
```
enable
conf t
!
! ========================================================================
! Khai bao MPLS
! ========================================================================
int range e0/0-3,e1/0-3
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

<h3>RR</h3>
```
enable
conf t
!
! ========================================================================
! Khai bao MPLS
! ========================================================================
int gi1
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

<h3>PE/IGW</h3>
```
enable
conf t
!
! ========================================================================
! Khai bao MPLS
! ========================================================================
int e0/0
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

## BGP

<h3>SRT1</h3>
```
enable
conf t
!
! ========================================================================
! Khai bao BGP
! ========================================================================
router bgp 7552
  neighbor SRT_TO_AGG peer-group
  neighbor SRT_TO_AGG remote-as 7552
  neighbor SRT_TO_AGG update-source Loopback0
  neighbor 10.134.0.1 peer-group SRT_TO_AGG
  neighbor 10.134.0.2 peer-group SRT_TO_AGG
  !
  address-family ipv4
    network 10.132.0.1 mask 255.255.255.255
    neighbor SRT_TO_AGG send-community both
    neighbor SRT_TO_AGG send-label
    neighbor 10.134.0.1 activate
    neighbor 10.134.0.2 activate
  !
  address-family vpnv4
    neighbor SRT_TO_AGG send-community both
    neighbor 10.134.0.1 activate
    neighbor 10.134.0.2 activate
  !
  address-family rtfilter unicast
    neighbor SRT_TO_AGG send-community both
    neighbor 10.134.0.1 activate
    neighbor 10.134.0.2 activate
  !
!
end
write
```

<h3>SRT2</h3>
```
enable
conf t
!
! ========================================================================
! Khai bao BGP
! ========================================================================
router bgp 7552
  neighbor SRT_TO_AGG peer-group
  neighbor SRT_TO_AGG remote-as 7552
  neighbor SRT_TO_AGG update-source Loopback0
  neighbor 10.134.0.1 peer-group SRT_TO_AGG
  neighbor 10.134.0.2 peer-group SRT_TO_AGG
  !
  address-family ipv4
    network 10.132.0.2 mask 255.255.255.255
    neighbor SRT_TO_AGG send-community both
    neighbor SRT_TO_AGG send-label
    neighbor 10.134.0.1 activate
    neighbor 10.134.0.2 activate
  !
  address-family vpnv4
    neighbor SRT_TO_AGG send-community both
    neighbor 10.134.0.1 activate
    neighbor 10.134.0.2 activate
  !
  address-family rtfilter unicast
    neighbor SRT_TO_AGG send-community both
    neighbor 10.134.0.1 activate
    neighbor 10.134.0.2 activate
  !
!
end
write
```

<h3>SRT3</h3>
```
enable
conf t
!
! ========================================================================
! Khai bao BGP
! ========================================================================
router bgp 7552
  bgp router-id 10.132.0.3
  neighbor SRT_TO_AGG peer-group
  neighbor SRT_TO_AGG remote-as 7552
  neighbor SRT_TO_AGG update-source Loopback0
  neighbor 10.134.0.1 peer-group SRT_TO_AGG
  neighbor 10.134.0.2 peer-group SRT_TO_AGG
  !
  address-family ipv4
    network 10.132.0.3 mask 255.255.255.255
    neighbor SRT_TO_AGG send-community both
    neighbor SRT_TO_AGG send-label
    neighbor 10.134.0.1 activate
    neighbor 10.134.0.2 activate
  !
  address-family vpnv4
    neighbor SRT_TO_AGG send-community both
    neighbor 10.134.0.1 activate
    neighbor 10.134.0.2 activate
  !
  address-family rtfilter unicast
    neighbor SRT_TO_AGG send-community both
    neighbor 10.134.0.1 activate
    neighbor 10.134.0.2 activate
  !
!
end
write
```

<h3>AGG1</h3>
```
enable
conf t
!
! ========================================================================
! Khai bao BGP
! ========================================================================
router bgp 7552
!
  bgp router-id 10.134.0.1
  !
  neighbor AGG_TO_SRT peer-group
  neighbor AGG_TO_SRT remote-as 7552
  neighbor AGG_TO_SRT update-source Loopback0
  neighbor 10.132.0.1 peer-group AGG_TO_SRT
  neighbor 10.132.0.2 peer-group AGG_TO_SRT
  neighbor 10.132.0.3 peer-group AGG_TO_SRT
  neighbor 10.132.0.4 peer-group AGG_TO_SRT
  neighbor 10.132.0.5 peer-group AGG_TO_SRT
  !
  neighbor AGG_TO_CT peer-group
  neighbor AGG_TO_CT remote-as 7552
  neighbor AGG_TO_CT update-source Loopback0
  neighbor 10.136.0.11 peer-group AGG_TO_CT
  neighbor 10.136.0.12 peer-group AGG_TO_CT
  !
  address-family ipv4
  !
    network 10.134.0.1 mask 255.255.255.255
    !
    neighbor AGG_TO_SRT route-reflector-client
    neighbor AGG_TO_SRT send-community both
    neighbor AGG_TO_SRT send-label
    neighbor AGG_TO_SRT next-hop-self all
    neighbor 10.132.0.1 activate
    neighbor 10.132.0.2 activate
    neighbor 10.132.0.3 activate
    neighbor 10.132.0.4 activate
    neighbor 10.132.0.5 activate
    !
    neighbor AGG_TO_CT send-community both
    neighbor AGG_TO_CT send-label
    neighbor AGG_TO_CT next-hop-self all
    neighbor 10.136.0.11 activate
    neighbor 10.136.0.12 activate
  !
  address-family vpnv4
  !
    neighbor AGG_TO_SRT route-reflector-client
    neighbor AGG_TO_SRT send-community both
    neighbor AGG_TO_SRT next-hop-self all
    neighbor 10.132.0.1 activate
    neighbor 10.132.0.2 activate
    neighbor 10.132.0.3 activate
    neighbor 10.132.0.4 activate
    neighbor 10.132.0.5 activate
    !
    neighbor AGG_TO_CT send-community both
    neighbor AGG_TO_CT next-hop-self all
    neighbor 10.136.0.11 activate
    neighbor 10.136.0.12 activate
  !
  address-family l2vpn vpls
  !
    neighbor AGG_TO_CT send-community both
    neighbor 10.136.0.11 activate
    neighbor 10.136.0.12 activate
  !
  address-family rtfilter unicast
  !
    neighbor AGG_TO_SRT route-reflector-client
    neighbor AGG_TO_SRT send-community both
    neighbor 10.132.0.1 activate
    neighbor 10.132.0.2 activate
    neighbor 10.132.0.3 activate
    neighbor 10.132.0.4 activate
    neighbor 10.132.0.5 activate
  !
!
end
write
```

<h3>CT1</h3>
```
enable
conf t
!
! ========================================================================
! Khai bao BGP
! ========================================================================
router bgp 7552
!
  bgp router-id 10.136.0.11
  !
  neighbor CT_TO_AGG peer-group
  neighbor CT_TO_AGG remote-as 7552
  neighbor CT_TO_AGG update-source Loopback0
  neighbor 10.134.0.1 peer-group CT_TO_AGG
  neighbor 10.134.0.2 peer-group CT_TO_AGG
  !
  neighbor CT_TO_RR peer-group
  neighbor CT_TO_RR remote-as 7552
  neighbor CT_TO_RR update-source Loopback0
  neighbor 10.255.0.1 peer-group CT_TO_RR
  !
  address-family ipv4
  !
    neighbor CT_TO_AGG route-reflector-client
    neighbor CT_TO_AGG send-community both
    neighbor CT_TO_AGG send-label
    neighbor CT_TO_AGG next-hop-self all
    neighbor 10.134.0.1 activate
    neighbor 10.134.0.2 activate
    !
    neighbor CT_TO_RR send-community both
    neighbor CT_TO_RR send-label
    neighbor CT_TO_RR next-hop-self all
    neighbor 10.255.0.1 activate
  !
  address-family vpnv4
  !
    neighbor CT_TO_AGG route-reflector-client
    neighbor CT_TO_AGG send-community both
    neighbor 10.134.0.1 activate
    neighbor 10.134.0.2 activate
    !
    neighbor CT_TO_RR send-community both
    neighbor 10.255.0.1 activate
  !
  address-family l2vpn vpls
  !
    neighbor CT_TO_AGG route-reflector-client
    neighbor CT_TO_AGG send-community both
    neighbor 10.134.0.1 activate
    neighbor 10.134.0.2 activate
    !
    neighbor CT_TO_RR send-community both
    neighbor 10.255.0.1 activate
  !
!
end
write
```

<!--<h3>AGG1</h3>
```
conf t
!
! ========================================================================
! Khai bao BGP
! ========================================================================
router bgp 7552
  bgp router-id 10.134.0.1
  ! Cho phep tat ca attribute BGP thay doi tren RR
  ibgp policy out enforce-modifications
  address-family ipv4 unicast
    network 10.134.0.1/32
  neighbor-group AGG_TO_SRT
    remote-as 7552
    update-source Loopback0
    address-family ipv4 unicast route-reflector-client
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
```-->

<!--<h3>CT1</h3>
```
conf t
!
! ========================================================================
! Khai bao BGP
! ========================================================================
router bgp 7552
  bgp router-id 10.136.0.11
  ! Cho phep tat ca attribute BGP thay doi tren RR
  ibgp policy out enforce-modifications
  address-family ipv4 unicast
    network 10.136.0.11/32
  neighbor-group CT_TO_AGG
    remote-as 7552
    update-source Loopback0
    address-family ipv4 unicast route-reflector-client
    address-family ipv4 unicast next-hop-self
  neighbor-group CT_TO_RR
    remote-as 7552
    update-source Loopback0
    address-family ipv4 unicast
    address-family ipv4 unicast next-hop-self
  neighbor 10.134.0.1
    use neighbor-group CT_TO_AGG
  neighbor 10.134.0.2
    use neighbor-group CT_TO_AGG
  neighbor 10.255.0.1
    use neighbor-group CT_TO_RR
!
commit
end
```-->

<h3>SRTx</h3>
```
enable
conf t
!
! ========================================================================
! Khai bao BGP
! ========================================================================
router bgp 7552
!
  bgp router-id 10.132.1.1
  neighbor SRT_TO_AGG peer-group
  neighbor SRT_TO_AGG remote-as 7552
  neighbor SRT_TO_AGG update-source Loopback0
  neighbor 10.134.1.1 peer-group SRT_TO_AGG
  !
  address-family ipv4
    network 10.132.1.1 mask 255.255.255.255
    neighbor SRT_TO_AGG send-community both
    neighbor SRT_TO_AGG send-label
    neighbor 10.134.1.1 activate
  !
  address-family vpnv4
    neighbor SRT_TO_AGG send-community both
    neighbor 10.134.1.1 activate
  !
!
end
write
```

<h3>AGGx</h3>
```
enable
conf t
!
! ========================================================================
! Khai bao BGP
! ========================================================================
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
    neighbor AGG_TO_SRT send-label
    neighbor AGG_TO_SRT next-hop-self all
    neighbor 10.132.1.1 activate
    !
    neighbor AGG_TO_CT send-community both
    neighbor AGG_TO_CT send-label
    neighbor AGG_TO_CT next-hop-self all
    neighbor 10.136.0.13 activate
  !
  address-family vpnv4
  !
    neighbor AGG_TO_SRT route-reflector-client
    neighbor AGG_TO_SRT send-community both
    neighbor AGG_TO_SRT next-hop-self all
    neighbor 10.132.1.1 activate
    !
    neighbor AGG_TO_CT send-community both
    neighbor AGG_TO_CT next-hop-self all
    neighbor 10.136.0.13 activate
  !
  address-family l2vpn vpls
  !
    neighbor AGG_TO_CT send-community both
    neighbor 10.136.0.13 activate
  !
!
end
write
```

<h3>CTx</h3>
```
enable
conf t
!
! ========================================================================
! Khai bao BGP
! ========================================================================
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
    neighbor CT_TO_AGG route-reflector-client
    neighbor CT_TO_AGG send-community both
    neighbor CT_TO_AGG send-label
    neighbor CT_TO_AGG next-hop-self all
    neighbor 10.134.1.1 activate
    !
    neighbor CT_TO_RR send-community both
    neighbor CT_TO_RR send-label
    neighbor CT_TO_RR next-hop-self all
    neighbor 10.255.0.1 activate
  !
  address-family vpnv4
  !
    neighbor CT_TO_AGG route-reflector-client
    neighbor CT_TO_AGG send-community both
    neighbor 10.134.1.1 activate
    !
    neighbor CT_TO_RR send-community both
    neighbor 10.255.0.1 activate
  !
  address-family l2vpn vpls
  !
    neighbor CT_TO_AGG route-reflector-client
    neighbor CT_TO_AGG send-community both
    neighbor 10.134.1.1 activate
    !
    neighbor CT_TO_RR send-community both
    neighbor 10.255.0.1 activate
  !
!
end
write
```

<h3>RR</h3>
```
enable
conf t
!
! ========================================================================
! Khai bao BGP
! ========================================================================
router bgp 7552
!
  bgp router-id 10.255.0.1
  !
  neighbor RR_TO_CT peer-group
  neighbor RR_TO_CT remote-as 7552
  neighbor RR_TO_CT update-source Loopback0
  neighbor 10.136.0.11 peer-group RR_TO_CT
  neighbor 10.136.0.12 peer-group RR_TO_CT
  neighbor 10.136.0.13 peer-group RR_TO_CT
  neighbor 10.136.0.14 peer-group RR_TO_CT
  neighbor 10.136.0.5 peer-group RR_TO_CT
  neighbor 10.136.0.26 peer-group RR_TO_CT
  !
  address-family ipv4
  !
    neighbor RR_TO_CT route-reflector-client
    neighbor RR_TO_CT send-community both
    neighbor RR_TO_CT send-label
    neighbor 10.136.0.11 activate
    neighbor 10.136.0.12 activate
    neighbor 10.136.0.13 activate
    neighbor 10.136.0.14 activate
    neighbor 10.136.0.5 activate
    neighbor 10.136.0.26 activate
  !
  address-family vpnv4
  !
    neighbor RR_TO_CT route-reflector-client
    neighbor RR_TO_CT send-community both
    neighbor 10.136.0.11 activate
    neighbor 10.136.0.12 activate
    neighbor 10.136.0.13 activate
    neighbor 10.136.0.14 activate
  !
  address-family l2vpn vpls
  !
    neighbor RR_TO_CT route-reflector-client
    neighbor RR_TO_CT send-community both
    neighbor 10.136.0.11 activate
    neighbor 10.136.0.12 activate
    neighbor 10.136.0.13 activate
    neighbor 10.136.0.14 activate
  !
!
end
write
```

<h3>PE</h3>
```
enable
conf t
!
! ========================================================================
! Khai bao BGP
! ========================================================================
router bgp 7552
!
  bgp router-id 10.136.0.5
  !
  neighbor CT_TO_RR peer-group
  neighbor CT_TO_RR remote-as 7552
  neighbor CT_TO_RR update-source Loopback0
  neighbor 10.255.0.1 peer-group CT_TO_RR
  !
  address-family ipv4
  !
    network 10.136.0.5 mask 255.255.255.255
    !
    neighbor CT_TO_RR send-community both
    neighbor CT_TO_RR send-label
    neighbor CT_TO_RR next-hop-self all
    neighbor 10.255.0.1 activate
  !
!
end
write
```

<h3>IGW</h3>
```
enable
conf t
!
! ========================================================================
! Khai bao BGP
! ========================================================================
router bgp 7552
!
  bgp router-id 10.136.0.26
  !
  neighbor CT_TO_RR peer-group
  neighbor CT_TO_RR remote-as 7552
  neighbor CT_TO_RR update-source Loopback0
  neighbor 10.255.0.1 peer-group CT_TO_RR
  !
  address-family ipv4
  !
    network 10.136.0.26 mask 255.255.255.255
    !
    neighbor CT_TO_RR send-community both
    neighbor CT_TO_RR send-label
    neighbor CT_TO_RR next-hop-self all
    neighbor 10.255.0.1 activate
  !
!
end
write
```

## RSVP

<h3>AGG1</h3>
```
enable
conf t
!
! ========================================================================
! Khai bao RSVP AGG to CT
! ========================================================================
!
! 01. enable MPLS-TE globally
mpls traffic-eng tunnels
! Tat tinh nang go nhan RSVP 
mpls traffic-eng signalling advertise explicit-null
!
! 02. enable MPLS-TE & RSVP under each interested interface
int range Gi1-2
  mpls traffic-eng tunnels
  ip rsvp bandwidth
!
! 03. enable MPLS-TE extensions under the IGP
router ospf 2
  mpls traffic-eng area 0
  mpls traffic-eng router-id lo0
!
! 04. create the MPLS-TE tunnel
interface Tunnel1
  ip unnumbered Loopback0
  tunnel mode mpls traffic-eng
  tunnel destination 10.136.0.11
  ! Cho phep MPLS-TE tunnel tham gia vao qua trinh tinh toan OSPF
  tunnel mpls traffic-eng autoroute announce
  tunnel mpls traffic-eng path-option 1 explicit name AGG1_TO_CT1
  tunnel mpls traffic-eng path-option protect 1 explicit name AGG1_TO_CT1_BK
!
ip explicit-path name AGG1_TO_CT1
  index 1 next-address 10.164.0.14
!
ip explicit-path name AGG1_TO_CT1_BK enable
  index 1 next-address 10.164.0.9
  index 2 next-address 10.164.0.5
  index 3 next-address 10.164.0.1
!
end
write
```

<h3>CT1</h3>
```
enable
conf t
!
! ========================================================================
! Khai bao RSVP CT to AGG
! ========================================================================
!
! 01. enable MPLS-TE globally
mpls traffic-eng tunnels
! Tat tinh nang go nhan RSVP 
mpls traffic-eng signalling advertise explicit-null
!
! 02. enable MPLS-TE & RSVP under each interested interface
int range gi2-3
  mpls traffic-eng tunnels
  ip rsvp bandwidth
!
! 03. enable MPLS-TE extensions under the IGP
router ospf 2
  mpls traffic-eng area 0
  mpls traffic-eng router-id lo0
!
! 04. create the MPLS-TE tunnel
interface Tunnel1
  ip unnumbered Loopback0
  tunnel mode mpls traffic-eng
  tunnel destination 10.134.0.1
  ! Cho phep MPLS-TE tunnel tham gia vao qua trinh tinh toan OSPF
  tunnel mpls traffic-eng autoroute announce
  tunnel mpls traffic-eng path-option 1 explicit name CT1_TO_AGG1
  tunnel mpls traffic-eng path-option protect 1 explicit name CT1_TO_AGG1_BK
!
ip explicit-path name CT1_TO_AGG1
  index 1 next-address 10.164.0.13
!
ip explicit-path name CT1_TO_AGG1_BK
  index 1 next-address 10.164.0.2
  index 2 next-address 10.164.0.6
  index 3 next-address 10.164.0.10
!
end
write
```

<h3>CTx</h3>
```
enable
conf t
!
! ========================================================================
! Khai bao RSVP CT to AGG
! ========================================================================
!
! 01. enable MPLS-TE globally
mpls traffic-eng tunnels
! Tat tinh nang go nhan RSVP 
mpls traffic-eng signalling advertise explicit-null
!
! 02. enable MPLS-TE & RSVP under each interested interface
int range gi2-3
  mpls traffic-eng tunnels
  ip rsvp bandwidth
!
! 03. enable MPLS-TE extensions under the IGP
router ospf 2
  mpls traffic-eng area 0
  mpls traffic-eng router-id lo0
!
! 04. create the MPLS-TE tunnel
interface Tunnel1
  ip unnumbered Loopback0
  tunnel mode mpls traffic-eng
  tunnel destination 10.134.1.1
  ! Cho phep MPLS-TE tunnel tham gia vao qua trinh tinh toan OSPF
  tunnel mpls traffic-eng autoroute announce
  tunnel mpls traffic-eng path-option 1 explicit name CT1_TO_AGG1
  tunnel mpls traffic-eng path-option protect 1 explicit name CT1_TO_AGG1_BK
!
ip explicit-path name CT1_TO_AGG1
  index 1 next-address 10.164.0.13
!
ip explicit-path name CT1_TO_AGG1_BK
  index 1 next-address 10.164.0.2
  index 2 next-address 10.164.0.6
  index 3 next-address 10.164.0.10
!
end
write
```

<h3>AGGx</h3>
```
enable
conf t
!
! ========================================================================
! Khai bao RSVP AGG to CT
! ========================================================================
!
! 01. enable MPLS-TE globally
mpls traffic-eng tunnels
! Tat tinh nang go nhan RSVP 
mpls traffic-eng signalling advertise explicit-null
!
! 02. enable MPLS-TE & RSVP under each interested interface
int range Gi1-2
  mpls traffic-eng tunnels
  ip rsvp bandwidth
!
! 03. enable MPLS-TE extensions under the IGP
router ospf 2
  mpls traffic-eng area 0
  mpls traffic-eng router-id lo0
!
! 04. create the MPLS-TE tunnel
interface Tunnel1
  ip unnumbered Loopback0
  tunnel mode mpls traffic-eng
  tunnel destination 10.136.0.13
  ! Cho phep MPLS-TE tunnel tham gia vao qua trinh tinh toan OSPF
  tunnel mpls traffic-eng autoroute announce
  tunnel mpls traffic-eng path-option 1 explicit name AGG1_TO_CT1
  tunnel mpls traffic-eng path-option protect 1 explicit name AGG1_TO_CT1_BK
!
ip explicit-path name AGG1_TO_CT1
  index 1 next-address 10.164.0.14
!
ip explicit-path name AGG1_TO_CT1_BK enable
  index 1 next-address 10.164.0.9
  index 2 next-address 10.164.0.5
  index 3 next-address 10.164.0.1
!
end
write
```

## HSI

<h3>VPC</h3>
```
ip dhcp
save
```

<h3>8.8.8.8</h3>
```
ip 8.8.8.8/24 8.8.8.1
save
```

<h3>IGW</h3>
```
enable
conf t
!
router bgp 7552
  address-family ipv4
    network 8.8.8.0 mask 255.255.255.0
!
end
write
```

<h3>Modem</h3>
```
enable
conf t
!
hostname Modem
!
! ========================================================================
! Khai bao PPPoeE Client
! ========================================================================
interface Ethernet0/0
  no shutdown
  no ip address
  pppoe enable
  pppoe-client dial-pool-number 1
!
interface Dialer0
  mtu 1492
  ip address negotiated
  encapsulation ppp
  dialer pool 1
  ppp chap hostname ftth_u1
  ppp chap password 123
!
! ========================================================================
! Khai bao DHCP Server
! ========================================================================
int e0/1
  no shut
  ip addr 192.168.1.1 255.255.255.0
!
service dhcp
!
ip dhcp pool 1
  network 192.168.1.0 255.255.255.0
  default-router 192.168.1.1
!
! ========================================================================
! Khai bao NAT
! ========================================================================
access-list 1 permit any
  ip nat inside source list 1 int Dialer0 overload
int Dialer0
  ip nat outside
int e0/1
  ip nat inside
!
! ========================================================================
! Khai bao Default Route
! ========================================================================
ip route 0.0.0.0 0.0.0.0 Dialer0
!
end
write
```

<h3>SRT3</h3>
```
enable
conf t
!
! ========================================================================
! Khai bao pseudowire
! ========================================================================
interface Ethernet0/2.35
  encapsulation dot1Q 35
  xconnect 10.134.0.1 10001 encapsulation mpls
    backup peer 10.134.0.2 10002
!
end
write
```

<h3>AGG1</h3>
```
enable
conf t
!
! ========================================================================
! Khai bao VPLS
! ========================================================================
l2vpn vfi context HSI
  vpn id 100
  member 10.134.0.2 10005 encapsulation mpls
bridge-domain 100
  member vfi HSI
  member 10.132.0.3 10001 encapsulation mpls
  member 10.136.0.11 10003 encapsulation mpls
!
end
write
```

<h3>CT1</h3>
```
enable
conf t
!
! ========================================================================
! Khai bao pseudowire
! ========================================================================
interface gi4.11
  encapsulation dot1Q 11
  xconnect 10.134.0.1 10003 encapsulation mpls
    backup peer 10.134.0.2 10004
!
interface gi4
  no shut
!
! ========================================================================
! Khai bao OSPF 4050 giua CT-BRAS
! ========================================================================
interface gi4.4050
  encapsulation dot1Q 4050
  ip addr 10.40.0.1 255.255.255.252
  ip ospf 4050 area 4050
  ip ospf network point-to-point
!
router ospf 4050
  area 4050 nssa default-information-originate metric-type 1 no-summary
!
! ========================================================================
! Khai bao default route tro PE
! ========================================================================
!
ip route 0.0.0.0 0.0.0.0 10.136.0.5
!
route-map CT_01_PUB_BRAS
  match tag 4050
!
router bgp 7552
  address-family ipv4 unicast
    redistribute ospf 4050 metric 0 route-map CT_01_PUB_BRAS
!
end
write
```

<h3>BRAS</h3>
```
enable
conf t
!
no ip domain-lookup
!
hostname BRAS
!
int Loopback0
  ip addr 10.137.0.1 255.255.255.255
!
! ========================================================================
! Khai bao PPPoE Server
! ========================================================================
username ftth_u1 password 123
!
bba-group pppoe NHATNGHE
 virtual-template 1
!
int Loopback1
  ip addr 10.137.32.1 255.255.255.255
!
interface Ethernet0/0
 no shutdown
!
interface Ethernet0/0.11
 encapsulation dot1Q 11
 no ip address
 pppoe enable group NHATNGHE
!
interface Virtual-Template1
 mtu 1492
 ip unnumbered lo1
 peer default ip address pool NN_DHCP
 ppp authentication chap callin
!
ip local pool NN_DHCP 210.245.0.1 210.245.0.255
!
! ========================================================================
! Khai bao OSPF 4050 giua CT-BRAS
! ========================================================================
ip prefix-list POOL-BRAS permit 210.245.0.0/24
!
ip route 210.245.0.0 255.255.255.0 null 0
!
route-map EXPORT-POOL-BRAS-TO-OSPF permit 10
 match ip address POOL-BRAS
 set tag 4050
!
interface e0/0.4050
  encapsulation dot1Q 4050
  ip addr 10.40.0.2 255.255.255.252
  ip ospf 4050 area 4050
  ip ospf network point-to-point
!
router ospf 4050
  area 4050 nssa
  redistribute static subnets metric-type 1 route-map EXPORT-POOL-BRAS-TO-OSPF
!
end
write
```

## L3VPN

<h3>SRT3</h3>
```
enable
conf t
!
! ========================================================================
! Khai bao L3VPN
! ========================================================================
ip vrf L3VPN
  rd 7552:500
  route-target export 7552:500
  route-target import 7552:500
!
interface e0/2.1000
  ip vrf forwarding L3VPN
  encapsulation dot1Q 1000
  ip address 172.16.40.1 255.255.255.0
!
router bgp 7552
  address-family ipv4 vrf L3VPN
    network 172.16.40.0 mask 255.255.255.0
  exit-address-family
!
end
write
```

<h3>SRTx</h3>
```
enable
conf t
!
! ========================================================================
! Khai bao L3VPN
! ========================================================================
vrf definition L3VPN
  rd 7552:500
  route-target export 7552:500
  route-target import 7552:500
  address-family ipv4 unicast
!
interface e0/2.1000
  vrf forwarding L3VPN
  encapsulation dot1Q 1000
  ip address 172.16.140.1 255.255.255.0
!
router bgp 7552
  address-family ipv4 vrf L3VPN
    network 172.16.140.0 mask 255.255.255.0
  exit-address-family
!
end
write
```

## L2VPN

<h3>SRT3</h3>
```
enable
conf t
!
! ========================================================================
! Khai bao pseudowire
! ========================================================================
interface e0/2.3500
  encapsulation dot1Q 3500
  xconnect 10.134.0.1 20001 encapsulation mpls
    backup peer 10.134.0.2 20003
!
end
write
```

<h3>SRTx</h3>
```
enable
conf t
!
! ========================================================================
! Khai bao pseudowire
! ========================================================================
interface e0/2.3500
  encapsulation dot1Q 3500
  xconnect 10.134.1.1 20002 encapsulation mpls
!
end
write
```

<h3>AGG1</h3>
```
enable
conf t
!
! ========================================================================
! Khai bao VPLS
! ========================================================================
l2vpn vfi context L2VPN
  vpn id 200
  autodiscovery bgp signaling ldp
bridge-domain 200
  member vfi L2VPN
  member 10.132.0.3 20001 encapsulation mpls
!
end
write
```

<h3>AGGx</h3>
```
enable
conf t
!
! ========================================================================
! Khai bao VPLS
! ========================================================================
l2vpn vfi context L2VPN
  vpn id 200
  autodiscovery bgp signaling ldp
bridge-domain 200
  member vfi L2VPN
  member 10.132.1.1 20002 encapsulation mpls
!
end
write
```

## L2VPN_TDM

<h3>SRT3</h3>
```
enable
conf t
!
! ========================================================================
! Khai bao pseudowire
! ========================================================================
interface e0/2.3600
  encapsulation dot1Q 3600
  xconnect 10.134.0.1 333 encapsulation mpls
    backup peer 10.134.0.2 334
!
end
write
```

<h3>AGG1</h3>
```
enable
conf t
!
! ========================================================================
! Khai bao pseudowire stitching [MS-PW (multi-segment pseudowire)]
! ========================================================================
l2vpn xconnect context L2VPN_TDM
  member 10.132.0.3 333 encapsulation mpls
  member 10.134.1.1 333 encapsulation mpls
!
end
write
```

<h3>AGGx</h3>
```
enable
conf t
!
! ========================================================================
! Khai bao pseudowire stitching [MS-PW (multi-segment pseudowire)]
! ========================================================================
l2vpn xconnect context L2VPN_TDM
  member 10.134.0.1 333 encapsulation mpls
  member 10.132.1.1 333 encapsulation mpls
!
end
write
```

<h3>SRTx</h3>
```
enable
conf t
!
! ========================================================================
! Khai bao pseudowire
! ========================================================================
interface e0/2.3600
  encapsulation dot1Q 3600
  xconnect 10.134.1.1 333 encapsulation mpls
!
end
write
```

## 2G

<h3>SRT3</h3>
```
enable
conf t
!
! ========================================================================
! Khai bao pseudowire
! ========================================================================
interface e0/2.2000
  encapsulation dot1Q 2000
  xconnect 10.136.0.5 10010 encapsulation mpls
    backup peer 10.136.0.6 10011
!
end
write
```

<h3>PE</h3>
```
enable
conf t
!
! ========================================================================
! Khai bao pseudowire
! ========================================================================
interface e0/1.2000
  encapsulation dot1Q 2000
  xconnect 10.132.0.3 10010 encapsulation mpls
!
end
write
```

## DTH

<h3>SRT3</h3>
```
enable
conf t
!
! ========================================================================
! Khai bao giao dien dau noi voi DTH
! ========================================================================
int e0/2.3889
  encapsulation dot1Q 3889
  ip address 172.16.108.1 255.255.255.252
!
! ========================================================================
! Khai bao giao thuc PIM SM tren giao dien dau noi
! ========================================================================
ip multicast-routing
!
int range e0/0-1,e0/2.3889
  ip pim sparse-mode
!
! ========================================================================
! Quang ba route DTH vao OSPF
! ========================================================================
route-map DTH permit 10
  match interface e0/2.3889
  set tag 1001
!
router ospf 2
  no redistribute connected
  redistribute connected subnets route-map DTH
!
end
write
```

<h3>SRT2/SRT1</h3>
```
enable
conf t
!
! ========================================================================
! Khai bao giao thuc PIM SM tren giao dien dau noi
! ========================================================================
ip multicast-routing
!
int range e0/0-1
  ip pim sparse-mode
!
end
write
```

<h3>AGG*/CT*</h3>
```
enable
conf t
!
! ========================================================================
! Khai bao giao thuc PIM SM tren giao dien dau noi
! ========================================================================
ip multicast-routing distributed
!
int range gi1-3
  ip pim sparse-mode
!
end
write
```

<h3>CT1</h3>
```
enable
conf t
!
! ========================================================================
! Quang ba route DTH cho PE
! ========================================================================
route-map PROCESS_ME_TO_PROCESS_CORE permit 20
  match tag 1001
!
router ospf 1
  redistribute ospf 2 route-map PROCESS_ME_TO_PROCESS_CORE
!
end
write
```

<h3>CKV</h3>
```
enable
conf t
!
! ========================================================================
! Khai bao giao thuc PIM SM tren giao dien dau noi
! ========================================================================
ip multicast-routing
!
int range e0/1-2,e1/1
  ip pim sparse-mode
!
end
write
```

<h3>PE</h3>
```
enable
conf t
!
! ========================================================================
! Khai bao giao dien dau noi voi SN Server
! ========================================================================
int e0/1.1090
  encapsulation dot1Q 1090
  ip address 172.16.8.1 255.255.255.252
  ip igmp version 3
!
! ========================================================================
! Khai bao giao thuc PIM SM tren giao dien dau noi
! ========================================================================
ip multicast-routing
!
int range e0/0,e0/1.1090
  ip pim sparse-mode
!
! ========================================================================
! Khai bao giao thuc PIM SSM
! ========================================================================
no ip igmp ssm-map query dns
ip igmp ssm-map enable
ip access-list standard SSM_RANGE_239.2.0.0_0.0.255.255
  permit 239.2.0.0 0.0.255.255
ip pim ssm range SSM_RANGE_239.2.0.0_0.0.255.255
ip igmp ssm-map static SSM_RANGE_239.2.0.0_0.0.255.255 172.16.108.2
!
end
write
```

<h3>DTH</h3>
```
enable
conf t
!
no ip domain-lookup
!
host DTH
!
int e0/0
  no shut
  ip address 172.16.108.2 255.255.255.252
!
end
write
```

<h3>SN Server</h3>
```
enable
conf t
!
no ip domain-lookup
!
host SNServer
!
int e0/0
  no shut
  ip address 172.16.8.2 255.255.255.252
  ip igmp join-group 239.2.2.2 source 172.16.108.2
!
ip route 172.16.108.0 255.255.255.252 172.16.8.1
!
end
write
```

## BTV

<h3>SRT3</h3>
```
enable
conf t
!
! ========================================================================
! Khai bao ip dau noi voi kh
! ========================================================================
int e0/2.3888
  encapsulation dot1Q 3888
  ip unnumbered Loopback0
  ip pim passive
  ip igmp version 3
!
no ip igmp ssm-map query dns
ip igmp ssm-map enable
ip access-list standard SSM_RANGE_239.1.0.0_0.0.255.255
  permit 239.1.0.0 0.0.255.255
ip pim ssm range SSM_RANGE_239.1.0.0_0.0.255.255
ip igmp ssm-map static SSM_RANGE_239.1.0.0_0.0.255.255 172.16.7.2
!
end
write
```

<h3>SRT2/SRT1</h3>
```
enable
conf t
!
! ========================================================================
! Khai bao giao thuc PIM SM tren giao dien dau noi
! ========================================================================
ip multicast-routing
!
int range e0/0-1
  ip pim sparse-mode
!
end
write
```

<h3>AGG*/CT*</h3>
```
enable
conf t
!
! ========================================================================
! Khai bao giao thuc PIM SM tren giao dien dau noi
! ========================================================================
ip multicast-routing distributed
!
int range gi1-3
  ip pim sparse-mode
!
end
write
```

<h3>CT1</h3>
```
enable
conf t
!
! ========================================================================
! Quang ba route BTV cho SRT
! ========================================================================
route-map PROCESS_CORE_TO_PROCESS_ME permit 20
  match tag 1000
!
router ospf 2
  redistribute ospf 1 route-map PROCESS_CORE_TO_PROCESS_ME
!
end
write
```

<h3>CKV</h3>
```
enable
conf t
!
! ========================================================================
! Khai bao giao thuc PIM SM tren giao dien dau noi
! ========================================================================
ip multicast-routing
!
int range e0/1-2,e1/1
  ip pim sparse-mode
!
end
write
```

<h3>PE</h3>
```
enable
conf t
!
! ========================================================================
! Khai bao ip dau noi voi SN Server
! ========================================================================
int e0/1.1080
  encapsulation dot1Q 1080
  ip address 172.16.7.1 255.255.255.252
!
! ========================================================================
! Khai bao giao thuc PIM SM tren giao dien dau noi
! ========================================================================
ip multicast-routing
!
int range e0/0,e0/1.1080
  ip pim sparse-mode
!
! ========================================================================
! Quang ba dia chi ip nguon multicast vao OSPF
! ========================================================================
ip prefix-list BTV permit 172.16.7.0/30
!
route-map BTV permit 10
  match ip address prefix-list BTV
  set tag 1000
!
router ospf 1
  redistribute connected route-map BTV
!
end
write
```

<h3>SN Server</h3>
```
enable
conf t
!
no ip domain-lookup
!
host SNServer
!
int e0/1
  no shut
  ip address 172.16.7.2 255.255.255.252
!
end
write
```

<h3>Tivi</h3>
```
enable
conf t
!
no ip domain-lookup
!
host Tivi
!
int e0/0
  no shut
  ip address 10.10.10.10 255.255.255.0
  ip igmp join-group 239.1.1.1 source 172.16.7.2
!
end
write
```
