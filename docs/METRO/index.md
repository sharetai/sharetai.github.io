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

_*(Build bằng VMware Pro 17.5.0 (search gg sẽ lấy đc key active) + PNETLab + Modem/SRT/CR1/BRAS (dùng IOL L3) + AGG1 (dùng CSR1000))_

_*(Build trên CPU Ryzen 3200 + RAM 16Gb <= tham khảo cấu hình trước khi build lab (1 con xrv demo sẽ yêu cầu 3Gb ram, 1 con csr sẽ yêu cầu 6Gb ram; có thể bỏ đi 1 mặt, chỉ làm 1 AGG và 1 CT đối với máy chỉ có 8Gb ram; IOL ko yêu cầu ram nhiều))_

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

<!-- <h3>SRT4</h3>
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
``` -->

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

<!-- <h3>AGG2</h3>
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
``` -->

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

<!-- <h3>CT2</h3>
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
``` -->

<h3>RR</h3>
```
enable
conf t
!
no ip domain-lookup
host RR
!
int Loopback0
  ip addr 10.138.0.1 255.255.255.255
int e0/0
  ip addr 10.166.0.6 255.255.255.252
  no shut
int e0/1
  ip addr 10.166.0.13 255.255.255.252
  no shut
int e0/2
  ip addr 10.166.0.10 255.255.255.252
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
no ip domain-lookup
host CTx
!
int Loopback0
  ip addr 10.136.0.13 255.255.255.255
int e0/0
  ip addr 10.166.0.14 255.255.255.252
  no shut
int e0/2
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
no ip domain-lookup
host AGGx
!
int Loopback0
  ip addr 10.134.1.1 255.255.255.255
int e0/2
  ip addr 10.162.0.5 255.255.255.252
  no shut
int e0/0
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
  ip addr 10.162.0.6 255.255.255.252
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

<!-- <h3>SRT4</h3>
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
``` -->

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

<!-- <h3>AGG2</h3>
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
``` -->

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
  router-id 10.136.0.11
  network 10.166.0.1 0.0.0.0 area 0
  network 10.166.0.5 0.0.0.0 area 0
router ospf 2
  router-id 10.136.0.11
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
ip prefix-list LOOPBACK0_CT permit 10.136.0.11/32
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

<!-- <h3>CT2</h3>
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
``` -->

<h3>RR</h3>
```
enable
conf t
!
! ========================================================================
! Khai bao OSPF
! ========================================================================
no router ospf 1
router ospf 1
  router-id 10.138.0.1
  network 10.138.0.1 0.0.0.0 area 0
  network 10.166.0.6 0.0.0.0 area 0
  network 10.166.0.10 0.0.0.0 area 0
  network 10.166.0.13 0.0.0.0 area 0
!
int range e0/0-2
  ip ospf network point-to-point
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
! Khai bao OSPF
! ========================================================================
no router ospf 1
no router ospf 2
router ospf 1
  router-id 10.136.0.13
  network 10.166.0.14 0.0.0.0 area 0
router ospf 2
  router-id 10.136.0.13
  passive-interface Loopback0
  network 10.136.0.13 0.0.0.0 area 0
  network 10.164.0.14 0.0.0.0 area 0
!
int range e0/0-2
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
no router ospf 2
router ospf 2
  router-id 10.134.1.1
  passive-interface Loopback0
  network 10.134.1.1 0.0.0.0 area 0
  network 10.164.0.13 0.0.0.0 area 0
  network 10.162.0.5 0.0.0.0 area 1
!
int range e0/0-2
  ip ospf network point-to-point
!
! ========================================================================
! Khai bao Filtering LSA Type 3 giua Area 0 va Area khac 0
! ========================================================================
no ip prefix-list AREA_0_TO_AREA_N
no ip prefix-list AREA_N_TO_AREA_0
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
no router ospf 2
router ospf 2
  router-id 10.132.1.1
  passive-interface Loopback0
  network 10.132.1.1 0.0.0.0 area 1
  network 10.162.0.6 0.0.0.0 area 1
!
int e0/0
  ip ospf network point-to-point
!
end
write
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
! ========================================================================
! Tat tinh nang go nhan LDP tai hop cuoi (Penultimate Hop) de duy tri 
! gia tri QoS trong nhan LDP dam bao thuc hien QoS toan trinh.
! ========================================================================
mpls ldp explicit-null
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
! ========================================================================
! Tat tinh nang go nhan LDP tai hop cuoi (Penultimate Hop) de duy tri 
! gia tri QoS trong nhan LDP dam bao thuc hien QoS toan trinh.
! ========================================================================
mpls ldp explicit-null
!
end
write
```

<!-- <h3>AGG2</h3>
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
``` -->

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
! ========================================================================
! Tat tinh nang go nhan LDP tai hop cuoi (Penultimate Hop) de duy tri 
! gia tri QoS trong nhan LDP dam bao thuc hien QoS toan trinh.
! ========================================================================
mpls ldp explicit-null
!
end
write
```

<!-- <h3>CT2</h3>
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
``` -->

<h3>RR</h3>
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
int e0/2
  mpls ip
!
! ========================================================================
! Tat tinh nang go nhan LDP tai hop cuoi (Penultimate Hop) de duy tri 
! gia tri QoS trong nhan LDP dam bao thuc hien QoS toan trinh.
! ========================================================================
mpls ldp explicit-null
!
end
write
```

<h3>CTx/AGGx/SRTx</h3>
```
enable
conf t
!
! ========================================================================
! Khai bao MPLS
! ========================================================================
int range e0/0-2
  mpls ip
!
! ========================================================================
! Tat tinh nang go nhan LDP tai hop cuoi (Penultimate Hop) de duy tri 
! gia tri QoS trong nhan LDP dam bao thuc hien QoS toan trinh.
! ========================================================================
mpls ldp explicit-null
!
end
write
```

## BGP

<!-- <h3>SRT1</h3>
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
``` -->

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
    neighbor SRT_TO_AGG send-community both
    neighbor SRT_TO_AGG send-label
    neighbor 10.134.0.1 activate
    neighbor 10.134.0.2 activate
  exit-address-family
  address-family vpnv4
    neighbor SRT_TO_AGG send-community both
    neighbor 10.134.0.1 activate
    neighbor 10.134.0.2 activate
  exit-address-family
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
!
! nhs tren rr chi thay doi nexthop ebgp route, nen de thay doi nexthop cua 
! route duoc quang ba boi rr-client thi dung route-map
route-map NEXT_HOP_SELF permit 10
  set ip next-hop self
!
no router bgp 7552
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
    neighbor AGG_TO_SRT route-reflector-client
    neighbor AGG_TO_SRT send-community both
    neighbor AGG_TO_SRT send-label
    neighbor AGG_TO_SRT route-map NEXT_HOP_SELF out
    neighbor 10.132.0.1 activate
    neighbor 10.132.0.2 activate
    neighbor 10.132.0.3 activate
    neighbor 10.132.0.4 activate
    neighbor 10.132.0.5 activate
    !
    neighbor AGG_TO_CT send-community both
    neighbor AGG_TO_CT send-label
    neighbor AGG_TO_CT route-map NEXT_HOP_SELF out
    neighbor 10.136.0.11 activate
    neighbor 10.136.0.12 activate
  !
  exit-address-family
  !
  address-family vpnv4
  !
    neighbor AGG_TO_SRT route-reflector-client
    neighbor AGG_TO_SRT send-community both
    neighbor AGG_TO_SRT route-map NEXT_HOP_SELF out
    neighbor 10.132.0.3 activate
    !
    neighbor AGG_TO_CT send-community both
    neighbor AGG_TO_CT route-map NEXT_HOP_SELF out
    neighbor 10.136.0.11 activate
    neighbor 10.136.0.12 activate
  !
  exit-address-family
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
!
! nhs tren rr chi thay doi nexthop ebgp route, nen de thay doi nexthop cua 
! route duoc quang ba boi rr-client thi dung route-map
route-map NEXT_HOP_SELF permit 10
  set ip next-hop self
!
no router bgp 7552
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
  neighbor 10.138.0.1 peer-group CT_TO_RR
  !
  address-family ipv4
  !
    neighbor CT_TO_AGG route-reflector-client
    neighbor CT_TO_AGG send-community both
    neighbor CT_TO_AGG send-label
    neighbor CT_TO_AGG route-map NEXT_HOP_SELF out
    neighbor 10.134.0.1 activate
    neighbor 10.134.0.2 activate
    !
    neighbor CT_TO_RR send-community both
    neighbor CT_TO_RR send-label
    neighbor CT_TO_RR route-map NEXT_HOP_SELF out
    neighbor 10.138.0.1 activate
  !
  exit-address-family
  !
  address-family vpnv4
  !
    neighbor CT_TO_AGG route-reflector-client
    neighbor CT_TO_AGG send-community both
    neighbor CT_TO_AGG route-map NEXT_HOP_SELF out
    neighbor 10.134.0.1 activate
    neighbor 10.134.0.2 activate
    !
    neighbor CT_TO_RR send-community both
    neighbor CT_TO_RR route-map NEXT_HOP_SELF out
    neighbor 10.138.0.1 activate
  !
  exit-address-family
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
no router bgp 7552
router bgp 7552
!
  bgp router-id 10.138.0.1
  !
  neighbor RR_TO_CT peer-group
  neighbor RR_TO_CT remote-as 7552
  neighbor RR_TO_CT update-source Loopback0
  neighbor 10.136.0.11 peer-group RR_TO_CT
  neighbor 10.136.0.12 peer-group RR_TO_CT
  neighbor 10.136.0.13 peer-group RR_TO_CT
  !
  address-family ipv4
  !
    neighbor RR_TO_CT route-reflector-client
    neighbor RR_TO_CT send-community both
    neighbor RR_TO_CT send-label
    neighbor 10.136.0.11 activate
    neighbor 10.136.0.12 activate
    neighbor 10.136.0.13 activate
  !
  exit-address-family
  !
  address-family vpnv4
  !
    neighbor RR_TO_CT route-reflector-client
    neighbor RR_TO_CT send-community both
    neighbor 10.136.0.11 activate
    neighbor 10.136.0.12 activate
    neighbor 10.136.0.13 activate
  !
  exit-address-family
!
end
write
```

<!-- <h3>SRT4</h3>
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
``` -->

<h3>SRTx</h3>
```
enable
conf t
!
! ========================================================================
! Khai bao BGP
! ========================================================================
no router bgp 7552
router bgp 7552
  bgp router-id 10.132.1.1
  neighbor SRT_TO_AGG peer-group
  neighbor SRT_TO_AGG remote-as 7552
  neighbor SRT_TO_AGG update-source Loopback0
  neighbor 10.134.1.1 peer-group SRT_TO_AGG
  address-family ipv4
    network 10.132.1.1 mask 255.255.255.255
    neighbor SRT_TO_AGG send-community both
    neighbor SRT_TO_AGG send-label
    neighbor 10.134.1.1 activate
  exit-address-family
  address-family vpnv4
    neighbor SRT_TO_AGG send-community both
    neighbor 10.134.0.1 activate
    neighbor 10.134.1.1 activate
  exit-address-family
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
!
! nhs tren rr chi thay doi nexthop ebgp route, nen de thay doi nexthop cua 
! route duoc quang ba boi rr-client thi dung route-map
route-map NEXT_HOP_SELF permit 10
  set ip next-hop self
!
no router bgp 7552
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
    neighbor AGG_TO_SRT route-reflector-client
    neighbor AGG_TO_SRT send-community both
    neighbor AGG_TO_SRT send-label
    neighbor AGG_TO_SRT route-map NEXT_HOP_SELF out
    neighbor 10.132.1.1 activate
    !
    neighbor AGG_TO_CT send-community both
    neighbor AGG_TO_CT send-label
    neighbor AGG_TO_CT route-map NEXT_HOP_SELF out
    neighbor 10.136.0.13 activate
  !
  exit-address-family
  !
  address-family vpnv4
  !
    neighbor AGG_TO_SRT route-reflector-client
    neighbor AGG_TO_SRT send-community both
    neighbor AGG_TO_SRT route-map NEXT_HOP_SELF out
    neighbor 10.132.1.1 activate
    !
    neighbor AGG_TO_CT send-community both
    neighbor AGG_TO_CT route-map NEXT_HOP_SELF out
    neighbor 10.136.0.13 activate
  !
  exit-address-family
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
!
! nhs tren rr chi thay doi nexthop ebgp route, nen de thay doi nexthop cua 
! route duoc quang ba boi rr-client thi dung route-map
route-map NEXT_HOP_SELF permit 10
  set ip next-hop self
!
no router bgp 7552
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
  neighbor 10.138.0.1 peer-group CT_TO_RR
  !
  address-family ipv4
  !
    neighbor CT_TO_AGG route-reflector-client
    neighbor CT_TO_AGG send-community both
    neighbor CT_TO_AGG send-label
    neighbor CT_TO_AGG route-map NEXT_HOP_SELF out
    neighbor 10.134.1.1 activate
    !
    neighbor CT_TO_RR send-community both
    neighbor CT_TO_RR send-label
    neighbor CT_TO_RR route-map NEXT_HOP_SELF out
    neighbor 10.138.0.1 activate
  !
  exit-address-family
  !
  address-family vpnv4
  !
    neighbor CT_TO_AGG route-reflector-client
    neighbor CT_TO_AGG send-community both
    neighbor CT_TO_AGG route-map NEXT_HOP_SELF out
    neighbor 10.134.1.1 activate
    !
    neighbor CT_TO_RR send-community both
    neighbor CT_TO_RR route-map NEXT_HOP_SELF out
    neighbor 10.138.0.1 activate
  !
  exit-address-family
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
! hidden command to enable rsvp explicit-null
mpls traffic-eng signalling interpret explicit-null verbatim
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
!
! 02. enable MPLS-TE & RSVP under each interested interface
int range e0/1-2
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
! hidden command to enable rsvp explicit-null
mpls traffic-eng signalling interpret explicit-null verbatim
!
end
write
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
! ========================================================================
! Khai bao pseudowire
! ========================================================================
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
! ========================================================================
! Khai bao pseudowire stitching / multi-segment pseudowire
! ========================================================================
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
! ========================================================================
! Khai bao pseudowire
! ========================================================================
interface Ethernet0/3.11
  encapsulation dot1Q 11
  xconnect 10.134.0.1 10003 encapsulation mpls
    backup peer 10.134.0.2 10004
!
interface Ethernet0/3
  no shut
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
! ========================================================================
! Khai bao PPPoE Server
! ========================================================================
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

## L3VPN

<h3>SRT3</h3>
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
interface lo500
  vrf forwarding L3VPN
  ip address 172.16.40.1 255.255.255.0
  no shutdown
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
ip vrf L3VPN
  rd 7552:500
  route-target export 7552:500
  route-target import 7552:500
!
interface lo500
  ip vrf forwarding L3VPN
  ip address 172.16.140.1 255.255.255.0
  no shutdown
!
router bgp 7552
  address-family ipv4 vrf L3VPN
    network 172.16.140.0 mask 255.255.255.0
  exit-address-family
!
end
write
```
