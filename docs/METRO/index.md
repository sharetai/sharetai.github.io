---
layout: default
title: METRO
nav_order: 3.2
has_children: true
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

_*(Build bằng VMware Pro 17.5.0 (search gg sẽ lấy đc key active) + PNETLab + SRT (dùng IOL L2) + AGG/CT (dùng xrv-9k-demo))_

_*(Build trên CPU Ryzen 3200 + RAM 16Gb <= tham khảo cấu hình trước khi build lab (1 con xrv sẽ yêu cầu 3Gb ram, có thể bỏ đi 1 mặt, chỉ làm 1 AGG và 1 CT đối với máy chỉ có 8Gb ram; IOL ko yêu cầu ram nhiều))_

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
  ip addr 10.162.0.6 255.255.255.252
  no shut
int e0/1
  ip addr 10.162.0.9 255.255.255.252
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
  ip addr 10.162.0.10 255.255.255.252
  no shut
int e0/1
  ip addr 10.162.0.13 255.255.255.252
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
  ip addr 10.162.0.14 255.255.255.252
  no shut
int e0/1
  ip addr 10.162.0.17 255.255.255.252
  no shut
!
end
write
```

<h3>SRT4</h3>
```
enable
conf t
!
no ip domain-lookup
host SRT4
!
int Loopback0
  ip addr 10.132.0.4 255.255.255.255
int e0/0
  ip addr 10.162.0.18 255.255.255.252
  no shut
int e0/1
  ip addr 10.162.0.21 255.255.255.252
  no shut
!
end
write
```

<h3>SRT5</h3>
```
enable
conf t
!
no ip domain-lookup
host SRT5
!
int Loopback0
  ip addr 10.132.0.5 255.255.255.255
int e0/0
  ip addr 10.162.0.22 255.255.255.252
  no shut
int e0/1
  ip addr 10.162.0.25 255.255.255.252
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
  ip addr 10.162.0.5 255.255.255.252
  no shut
!
end
write
```

<!-- ```
conf t
!
no ip domain-lookup
host AGG1
!
int Loopback0
  ip addr 10.134.0.1 255.255.255.255
int gi0/0/0/0
  ip addr 10.164.0.13 255.255.255.252
  no shut
int gi0/0/0/1
  ip addr 10.164.0.10 255.255.255.252
  no shut
int gi0/0/0/1.11
  encapsulation dot1Q 11
  ip addr 10.162.0.1 255.255.255.252
  no shut
int gi0/0/0/2
  ip addr 10.162.0.5 255.255.255.252
  no shut
!
commit
end
``` -->

<h3>AGG2</h3>
```
conf t
!
no ip domain-lookup
host AGG2
!
int Loopback0
  ip addr 10.134.0.2 255.255.255.255
int gi0/0/0/0
  ip addr 10.164.0.6 255.255.255.252
  no shut
int gi0/0/0/1
  ip addr 10.164.0.9 255.255.255.252
  no shut
int gi0/0/0/1.11
  encapsulation dot1Q 11
  ip addr 10.162.0.2 255.255.255.252
  no shut
int gi0/0/0/2
  ip addr 10.162.0.26 255.255.255.252
  no shut
!
commit
end
```

<h3>CT1</h3>
```
enable
conf t
!
no ip domain-lookup
host CT1
!
int Loopback0
  ip addr 10.136.0.11 255.255.255.255
int e0/0
  ip addr 10.166.0.5 255.255.255.252
  no shut
int e0/1
  ip addr 10.166.0.1 255.255.255.252
  no shut
int e0/1.200
  encapsulation dot1Q 200
  ip addr 10.164.0.1 255.255.255.252
  no shut
int e0/2
  ip addr 10.164.0.14 255.255.255.252
  no shut
!
end
write
```
<!-- ```
conf t
!
no ip domain-lookup
host CT1
!
int Loopback0
  ip addr 10.136.0.11 255.255.255.255
int gi0/0/0/0
  ip addr 10.166.0.5 255.255.255.252
  no shut
int gi0/0/0/1
  ip addr 10.166.0.1 255.255.255.252
  no shut
int gi0/0/0/1.200
  encapsulation dot1Q 200
  ip addr 10.164.0.1 255.255.255.252
  no shut
int gi0/0/0/2
  ip addr 10.164.0.14 255.255.255.252
  no shut
!
commit
end
``` -->

<h3>CT2</h3>
```
conf t
!
no ip domain-lookup
host CT2
!
int Loopback0
  ip addr 10.136.0.12 255.255.255.255
int gi0/0/0/0
  ip addr 10.166.0.9 255.255.255.252
  no shut
int gi0/0/0/1
  ip addr 10.166.0.2 255.255.255.252
  no shut
int gi0/0/0/1.200
  encapsulation dot1Q 200
  ip addr 10.164.0.2 255.255.255.252
  no shut
int gi0/0/0/2
  ip addr 10.164.0.5 255.255.255.252
  no shut
!
commit
end
```

<h3>RR</h3>
```
conf t
!
no ip domain-lookup
host RR
!
int Loopback0
  ip addr 10.138.0.1 255.255.255.255
int gi0/0/0/0
  ip addr 10.166.0.6 255.255.255.252
  no shut
int gi0/0/0/1
  ip addr 10.166.0.13 255.255.255.252
  no shut
int gi0/0/0/2
  ip addr 10.166.0.10 255.255.255.252
  no shut
!
commit
end
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
no router ospf 2
router ospf 2
  router-id 10.132.0.1
  passive-interface Loopback0
  network 10.132.0.1 0.0.0.0 area 1
  network 10.162.0.6 0.0.0.0 area 1
  network 10.162.0.9 0.0.0.0 area 1
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
no router ospf 2
router ospf 2
  router-id 10.132.0.2
  passive-interface Loopback0
  network 10.132.0.2 0.0.0.0 area 1
  network 10.162.0.10 0.0.0.0 area 1
  network 10.162.0.13 0.0.0.0 area 1
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
no router ospf 2
router ospf 2
  router-id 10.132.0.3
  passive-interface Loopback0
  network 10.132.0.3 0.0.0.0 area 1
  network 10.162.0.14 0.0.0.0 area 1
  network 10.162.0.17 0.0.0.0 area 1
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

<h3>SRT4</h3>
```
enable
conf t
!
! ========================================================================
! Khai bao OSPF
! ========================================================================
no router ospf 2
router ospf 2
  router-id 10.132.0.4
  passive-interface Loopback0
  network 10.132.0.4 0.0.0.0 area 1
  network 10.162.0.18 0.0.0.0 area 1
  network 10.162.0.21 0.0.0.0 area 1
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

<h3>SRT5</h3>
```
enable
conf t
!
! ========================================================================
! Khai bao OSPF
! ========================================================================
no router ospf 2
router ospf 2
  router-id 10.132.0.5
  passive-interface Loopback0
  network 10.132.0.5 0.0.0.0 area 1
  network 10.162.0.22 0.0.0.0 area 1
  network 10.162.0.25 0.0.0.0 area 1
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
no router ospf 2
router ospf 2
  router-id 10.134.0.1
  passive-interface Loopback0
  network 10.134.0.1 0.0.0.0 area 0
  network 10.164.0.10 0.0.0.0 area 0
  network 10.164.0.13 0.0.0.0 area 0
  network 10.162.0.1 0.0.0.0 area 1
  network 10.162.0.5 0.0.0.0 area 1
!
int gi1
  ip ospf network point-to-point
  ip ospf cost 10000
int gi2
  ip ospf network point-to-point
  ip ospf cost 2000
int gi2.11
  ip ospf network point-to-point
  ip ospf cost 10
int gi3
  ip ospf network point-to-point
  ip ospf cost 100
!
! ========================================================================
! Khai bao Filtering LSA Type 3 giua Area 0 va Area khac 0
! ========================================================================
no ip prefix-list AREA_0_TO_AREA_N
no ip prefix-list AREA_N_TO_AREA_0
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
no router ospf 2
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

<h3>AGG2</h3>
```
conf t
!
! ========================================================================
! Khai bao OSPF
! ========================================================================
no router ospf 2
router ospf 2
  router-id 10.134.0.2
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
commit
end
```

<h3>CT1</h3>
```
enable
conf t
!
! ========================================================================
! Khai bao OSPF
! ========================================================================
no router ospf 1
no router ospf 2
router ospf 1
  router-id 10.134.0.1
  network 10.166.0.1 0.0.0.0 area 0
  network 10.166.0.5 0.0.0.0 area 0
router ospf 2
  router-id 10.134.0.1
  passive-interface Loopback0
  network 10.136.0.11 0.0.0.0 area 0
  network 10.164.0.1 0.0.0.0 area 0
  network 10.164.0.14 0.0.0.0 area 0
!
int e0/0
  ip ospf network point-to-point
  ip ospf cost 2000
int e0/1
  ip ospf network point-to-point
  ip ospf cost 600
int e0/1.11
  ip ospf network point-to-point
  ip ospf cost 500
int e0/2
  ip ospf network point-to-point
  ip ospf cost 10000
!
! ========================================================================
! Khai bao quang ba Loopback 0 CT vao OSPF Process 1
! ========================================================================
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
no router ospf 1
no router ospf 2
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
interface Loopback1000
  ipv4 address 255.255.255.255 255.255.255.255
route-policy LOOPBACK0_CT
  if destination in (10.136.0.11/32) then
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

<h3>CT2</h3>
```
conf t
!
! ========================================================================
! Khai bao OSPF
! ========================================================================
no router ospf 1
no router ospf 2
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
route-policy LOOPBACK0_CT
  if destination in (10.136.0.12/32) then
    done
  endif
end-policy
router ospf 1
  redistribute ospf 2 metric-type 1 route-policy LOOPBACK0_CT
!
commit
end
```

<h3>RR</h3>
```
conf t
!
! ========================================================================
! Khai bao OSPF
! ========================================================================
no router ospf 1
router ospf 1
router-id 10.138.0.1
area 0
  int Loopback0
    passive enable
  int gi0/0/0/0
    network point-to-point
  int gi0/0/0/1
    network point-to-point
  int gi0/0/0/2
    network point-to-point
!
commit
end
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
no router bgp 7552
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
no router bgp 7552
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
no router bgp 7552
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
write
```

<h3>SRT4</h3>
```
enable
conf t
!
! ========================================================================
! Khai bao BGP
! ========================================================================
no router bgp 7552
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
write
```

<h3>SRT5</h3>
```
enable
conf t
!
! ========================================================================
! Khai bao BGP
! ========================================================================
no router bgp 7552
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
write
```

<h3>AGG1</h3>
```
conf t
!
! ========================================================================
! Khai bao BGP
! ========================================================================
no router bgp 7552
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
```

<h3>AGG2</h3>
```
conf t
!
! ========================================================================
! Khai bao BGP
! ========================================================================
no router bgp 7552
router bgp 7552
  bgp router-id 10.134.0.2
  ! Cho phep tat ca attribute BGP thay doi tren RR
  ibgp policy out enforce-modifications
  address-family ipv4 unicast
    network 10.134.0.2/32
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
```

<h3>CT1</h3>
```
conf t
!
! ========================================================================
! Khai bao BGP
! ========================================================================
no router bgp 7552
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
  neighbor 10.138.0.1
    use neighbor-group CT_TO_RR
!
commit
end
```

<h3>CT2</h3>
```
conf t
!
! ========================================================================
! Khai bao BGP
! ========================================================================
no router bgp 7552
router bgp 7552
  bgp router-id 10.136.0.12
  ! Cho phep tat ca attribute BGP thay doi tren RR
  ibgp policy out enforce-modifications
  address-family ipv4 unicast
    network 10.136.0.12/32
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
  neighbor 10.138.0.1
    use neighbor-group CT_TO_RR
!
commit
end
```

<h3>RR</h3>
```
conf t
!
! ========================================================================
! Khai bao BGP
! ========================================================================
no router bgp 7552
router bgp 7552
bgp router-id 10.138.0.1
  address-family ipv4 unicast
  neighbor-group RR_TO_CT
    remote-as 7552
    update-source Loopback0
    address-family ipv4 unicast route-reflector-client
  neighbor 10.136.0.11
    use neighbor-group RR_TO_CT
  neighbor 10.136.0.12
    use neighbor-group RR_TO_CT
  neighbor 10.136.0.13
    use neighbor-group RR_TO_CT
!
commit
end
```

## MPLS

<h3>SRT[12345]</h3>
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
end
write
```

<h3>AGG1</h3>
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
end
write
```

<h3>AGG2</h3>
```
conf t
!
! ========================================================================
! Khai bao MPLS
! ========================================================================
mpls ldp
  int gi0/0/0/0
  int gi0/0/0/1
  int gi0/0/0/1.11
  int gi0/0/0/2
!
commit
end
```

<h3>CT1</h3>
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
int e0/1.200
  mpls ip
int e0/2
  mpls ip
!
end
write
```

<h3>CT2</h3>
```
conf t
!
! ========================================================================
! Khai bao MPLS
! ========================================================================
mpls ldp
  int gi0/0/0/0
  int gi0/0/0/1
  int gi0/0/0/1.200
  int gi0/0/0/2
!
commit
end
```

<h3>RR</h3>
```
conf t
!
! ========================================================================
! Khai bao MPLS
! ========================================================================
mpls ldp
  int gi0/0/0/0
  int gi0/0/0/1
  int gi0/0/0/2
!
commit
end
```

## HSI

<h3>VPC</h3>
```
ip dhcp
```

<h3>Modem</h3>
```
enable
conf t
!
hostname Modem
!
! ========================================================================
! Khai bao PPPoeE
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
ip route 0.0.0.0 0.0.0.0 210.245.0.1
!
end
write
```

<h3>SRT3</h3>
```
enable
conf t
!
interface Ethernet0/2
  no shutdown
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
l2vpn xconnect context HSI
 member 10.132.0.3 10001 encapsulation mpls
 member 10.136.0.11 10003 encapsulation mpls
!
end
write
```
<!-- ```
conf t
!
! ========================================================================
! Khai bao HSI
! ========================================================================
l2vpn
 pw-class HSI
  encapsulation mpls
  !
 !
 bridge group HSI
  bridge-domain HSI
   neighbor 10.132.0.3 pw-id 10001
    pw-class HSI
    split-horizon group
   !
   neighbor 10.136.0.11 pw-id 10003
    pw-class HSI
   !
   vfi HSI
    neighbor 10.134.0.2 pw-id 10007
    !
   !
  !
 !
!
commit
end
``` -->

<h3>CT1</h3>
```
enable
conf t
!
interface Ethernet0/3
  no shut
!
interface Ethernet0/3.11
  encapsulation dot1Q 11
  xconnect 10.134.0.1 10003 encapsulation mpls
    backup peer 10.134.0.2 10004
!
end
write
```
<!-- ```
conf t
!
! ========================================================================
! Khai bao HSI
! ========================================================================
no int Gi0/0/0/3 shut
int Gi0/0/0/3.11 l2transport
  mtu 1514
  encapsulation dot1q 11
no l2vpn
l2vpn
  pw-class HSI
    encapsulation mpls
  xconnect group HSI
    p2p HSI
      interface GigabitEthernet0/0/0/3.11
      neighbor ipv4 10.134.0.1 pw-id 10003
        pw-class HSI
        backup neighbor 10.134.0.2 pw-id 10004
          pw-class HSI
commit
end
``` -->

<h3>BRAS</h3>
```
enable
conf t
!
hostname BRAS
!
username ftth_u1 password 123
!
bba-group pppoe NHATNGHE
 virtual-template 1
!
interface Virtual-Template1
 mtu 1492
 ip unnumbered Ethernet0/0
 peer default ip address pool NN_DHCP
 ppp authentication chap callin
!
interface Ethernet0/0
 no shutdown
!
interface Ethernet0/0.11
 encapsulation dot1Q 11
 pppoe enable group NHATNGHE
!
interface Ethernet0/0
 no shutdown
 ip address 210.245.0.1 255.255.255.0
!
ip local pool NN_DHCP 210.245.0.2 210.245.0.254
!
end
write
```

<!-- ## backup

<h3>SRT1</h3>

```
enable
conf t
no ip domain-lookup
host SRT1
int Loopback0
ip addr 10.132.0.1 255.255.255.255
int e0/0
ip addr 10.162.0.6 255.255.255.252
ip ospf network point-to-point
ip ospf cost 100
int e0/1
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
int e0/0
 mpls ip
int e0/1
 mpls ip
!
end
write
```

<h3>SRT2</h3>

```
enable
conf t
no ip domain-lookup
host SRT2
int Loopback0
ip addr 10.132.0.2 255.255.255.255
int e0/0
ip addr 10.162.0.10 255.255.255.252
ip ospf network point-to-point
ip ospf cost 100
int e0/1
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
int e0/0
 mpls ip
int e0/1
 mpls ip
!
end
write
```

<h3>SRT3</h3>

```
enable
conf t
no ip domain-lookup
host SRT3
int Loopback0
ip addr 10.132.0.3 255.255.255.255
int e0/0
ip addr 10.162.0.14 255.255.255.252
ip ospf network point-to-point
ip ospf cost 100
no shut
int e0/1
ip addr 10.162.0.17 255.255.255.252
ip ospf network point-to-point
ip ospf cost 100
no shut
!
router ospf 2
router-id 10.132.0.3
passive-interface Loopback0
network 10.132.0.3 0.0.0.0 area 1
network 10.162.0.14 0.0.0.0 area 1
network 10.162.0.17 0.0.0.0 area 1
!
exit
no router bgp 7552
router bgp 7552
bgp router-id 10.132.0.3
neighbor SRT_TO_AGG peer-group
neighbor SRT_TO_AGG remote-as 7552
neighbor SRT_TO_AGG update-source Loopback0
neighbor SRT_TO_AGG send-label
neighbor 10.134.0.1 peer-group SRT_TO_AGG
neighbor 10.134.0.2 peer-group SRT_TO_AGG
network 10.132.0.3 mask 255.255.255.255
!
int e0/0
 mpls ip
int e0/1
 mpls ip
!
int e0/2
 xconnect 10.134.0.1 1001 encapsulation mpls
  backup peer 10.134.0.2 1002
 no shut
end
```

<h3>SRT4</h3>

```
enable
conf t
no ip domain-lookup
host SRT4
int Loopback0
ip addr 10.132.0.4 255.255.255.255
int e0/0
ip addr 10.162.0.18 255.255.255.252
ip ospf network point-to-point
ip ospf cost 100
int e0/1
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
int e0/0
 mpls ip
int e0/1
 mpls ip
!
end
write
```

<h3>SRT5</h3>

```
enable
conf t
no ip domain-lookup
host SRT5
int Loopback0
ip addr 10.132.0.5 255.255.255.255
int e0/0
ip addr 10.162.0.22 255.255.255.252
ip ospf network point-to-point
ip ospf cost 100
int e0/1
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
int e0/0
 mpls ip
int e0/1
 mpls ip
!
end
write
```

<h3>AGG1</h3>

```
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
exit
exit
no router bgp 7552
router bgp 7552
bgp router-id 10.134.0.1
ibgp policy out enforce-modifications
address-family ipv4 unicast
 network 10.134.0.1/32
 allocate-label all
neighbor-group AGG_TO_SRT
 remote-as 7552
 update-source Loopback0
 address-family ipv4 labeled-unicast route-reflector-client
neighbor-group AGG_TO_CT
 remote-as 7552
 update-source Loopback0
 address-family ipv4 labeled-unicast
 address-family ipv4 labeled-unicast next-hop-self
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
mpls ldp
 int gi0/0/0/0
 int gi0/0/0/1
 int gi0/0/0/1.11
 int gi0/0/0/2
!
l2vpn
 pw-class l2vpn
  encapsulation mpls
 bridge group L2VPN
  bridge-domain L2VPN
   neighbor 10.132.0.3 pw-id 1001
    pw-class l2vpn
   vfi L2VPN
    vpn-id 400
    autodiscovery bgp
    rd 7552:400
    route-target 7552:400
    signaling-protocol ldp
    vpls-id 7552:400
!
commit
end
```

<h3>AGG2</h3>

```
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
ibgp policy out enforce-modifications
address-family ipv4 unicast
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
mpls ldp
 int gi0/0/0/0
 int gi0/0/0/1
 int gi0/0/0/1.11
 int gi0/0/0/2
!
commit
end
```

<h3>CT1</h3>

```
conf t
no ip domain-lookup
host CT1
int Loopback0
ip addr 10.136.0.11 255.255.255.255
int gi0/0/0/0
ip addr 10.166.0.1 255.255.255.252
no shut
no int gi0/0/0/1 shut
int gi0/0/0/1.200
encapsulation dot1Q 200
ip addr 10.164.0.1 255.255.255.252
no shut
int gi0/0/0/2
ip addr 10.164.0.14 255.255.255.252
no shut
!
no router ospf 1
router ospf 1
router-id 10.136.0.11
area 0
 int gi0/0/0/0
  network point-to-point
exit
exit
exit
no router ospf 2
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
exit
exit
exit
interface Loopback1000
 ipv4 address 255.255.255.255 255.255.255.255
route-policy LOOPBACK0_CT
 if destination in (10.136.0.11/32) then
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
exit
exit
exit
no router bgp 7552
router bgp 7552
bgp router-id 10.136.0.11
ibgp policy out enforce-modifications
address-family ipv4 unicast
 network 10.136.0.11/32
 allocate-label all
neighbor-group CT_TO_AGG
 remote-as 7552
 update-source Loopback0
 address-family ipv4 labeled-unicast route-reflector-client
 address-family ipv4 labeled-unicast next-hop-self
neighbor-group CT_TO_RR
 remote-as 7552
 update-source Loopback0
 address-family ipv4 labeled-unicast
 address-family ipv4 labeled-unicast next-hop-self
neighbor 10.134.0.1
 use neighbor-group CT_TO_AGG
neighbor 10.134.0.2
 use neighbor-group CT_TO_AGG
neighbor 10.138.0.1
 use neighbor-group CT_TO_RR
!
mpls ldp
 int gi0/0/0/0
 int gi0/0/0/1.200
 int gi0/0/0/2
!
commit
end
```

<h3>CT2</h3>

```
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
neighbor 10.134.0.1
 use neighbor-group CT_TO_AGG
neighbor 10.134.0.2
 use neighbor-group CT_TO_AGG
!
mpls ldp
 int gi0/0/0/1.200
 int gi0/0/0/2
!
commit
end
```

<h3>RR</h3>

```
conf t
no ip domain-lookup
host RR
int Loopback0
ip addr 10.138.0.1 255.255.255.255
int gi0/0/0/0
ip addr 10.166.0.2 255.255.255.252
no shut
int gi0/0/0/1
ip addr 10.166.0.5 255.255.255.252
no shut
!
router ospf 1
router-id 10.138.0.1
area 0
 int Loopback0
  passive enable
 int gi0/0/0/0
  network point-to-point
 int gi0/0/0/1
  network point-to-point
!
exit
exit
exit
no router bgp 7552
router bgp 7552
bgp router-id 10.138.0.1
address-family ipv4 unicast
 allocate-label all
neighbor-group RR_TO_CT
 remote-as 7552
 update-source Loopback0
 address-family ipv4 labeled-unicast route-reflector-client
neighbor 10.136.0.11
 use neighbor-group RR_TO_CT
neighbor 10.136.0.13
 use neighbor-group RR_TO_CT
!
mpls ldp
 int gi0/0/0/0
 int gi0/0/0/1
!
commit
end
```

<h3>CTremote</h3>

```
conf t
no ip domain-lookup
host CTremote
int Loopback0
ip addr 10.136.0.13 255.255.255.255
int gi0/0/0/0
ip addr 10.166.0.6 255.255.255.252
no shut
int gi0/0/0/2
ip addr 10.164.0.14 255.255.255.252
no shut
!
no router ospf 1
router ospf 1
router-id 10.136.0.13
area 0
 int gi0/0/0/0
  network point-to-point
exit
exit
exit
no router ospf 2
router ospf 2
router-id 10.136.0.13
area 0
 int Loopback0
  passive enable
 int gi0/0/0/2
  network point-to-point
  cost 10000
!
exit
exit
exit
interface Loopback1000
 ipv4 address 255.255.255.255 255.255.255.255
route-policy LOOPBACK0_CT
 if destination in (10.136.0.13/32) then
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
exit
exit
exit
no router bgp 7552
router bgp 7552
bgp router-id 10.136.0.13
ibgp policy out enforce-modifications
address-family ipv4 unicast
 network 10.136.0.13/32
 allocate-label all
neighbor-group CT_TO_AGG
 remote-as 7552
 update-source Loopback0
 address-family ipv4 labeled-unicast route-reflector-client
 address-family ipv4 labeled-unicast next-hop-self
neighbor-group CT_TO_RR
 remote-as 7552
 update-source Loopback0
 address-family ipv4 labeled-unicast
 address-family ipv4 labeled-unicast next-hop-self
neighbor 10.134.1.1
 use neighbor-group CT_TO_AGG
neighbor 10.138.0.1
 use neighbor-group CT_TO_RR
!
mpls ldp
 int gi0/0/0/0
 int gi0/0/0/2
!
commit
end
```

<h3>AGGremote</h3>

```
conf t
!
no ip domain-lookup
host AGGremote
!
int Loopback0
ip addr 10.134.1.1 255.255.255.255
int gi0/0/0/2
ip addr 10.162.0.5 255.255.255.252
no shut
int gi0/0/0/0
ip addr 10.164.0.13 255.255.255.252
no shut
!
no router ospf 2
router ospf 2
router-id 10.134.1.1
area 0
 int Loopback0
  passive enable
 int gi0/0/0/0
  network point-to-point
  cost 10000
area 1
 int gi0/0/0/2
  network point-to-point
  cost 100
!
route-policy AREA_0_TO_AREA_N
 if destination in (10.134.1.1) then
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
exit
exit
no router bgp 7552
router bgp 7552
bgp router-id 10.134.1.1
ibgp policy out enforce-modifications
address-family ipv4 unicast
 network 10.134.1.1/32
 allocate-label all
neighbor-group AGG_TO_SRT
 remote-as 7552
 update-source Loopback0
 address-family ipv4 labeled-unicast route-reflector-client
neighbor-group AGG_TO_CT
 remote-as 7552
 update-source Loopback0
 address-family ipv4 labeled-unicast
 address-family ipv4 labeled-unicast next-hop-self
neighbor 10.132.1.1
 use neighbor-group AGG_TO_SRT
neighbor 10.136.0.13
 use neighbor-group AGG_TO_CT
!
mpls ldp
 int gi0/0/0/0
 int gi0/0/0/2
!
l2vpn
 pw-class l2vpn
  encapsulation mpls
 bridge group L2VPN
  bridge-domain L2VPN
   neighbor 10.132.1.1 pw-id 1001
    pw-class l2vpn
   vfi L2VPN
    vpn-id 400
    autodiscovery bgp
    rd 7552:400
    route-target 7552:400
    signaling-protocol ldp
    vpls-id 7552:400
!
commit
end
```

<h3>SRTremote</h3>

```
enable
conf t
no ip domain-lookup
host SRTremote
int Loopback0
ip addr 10.132.1.1 255.255.255.255
int e0/0
ip addr 10.162.0.6 255.255.255.252
ip ospf network point-to-point
ip ospf cost 100
no shut
!
router ospf 2
router-id 10.132.1.1
passive-interface Loopback0
network 0.0.0.0 0.0.0.0 area 1
!
exit
no router bgp 7552
router bgp 7552
bgp router-id 10.132.1.1
neighbor SRT_TO_AGG peer-group
neighbor SRT_TO_AGG remote-as 7552
neighbor SRT_TO_AGG update-source Loopback0
neighbor SRT_TO_AGG send-label
neighbor 10.134.1.1 peer-group SRT_TO_AGG
neighbor 10.134.1.2 peer-group SRT_TO_AGG
network 10.132.1.1 mask 255.255.255.255
!
int e0/0
 mpls ip
!
int e0/2
 xconnect 10.134.1.1 1001 encapsulation mpls
  backup peer 10.134.1.2 1002
 no shut
end
``` -->
