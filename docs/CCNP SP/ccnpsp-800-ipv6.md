---
layout: default
title: IPv6
nav_order: 800
parent: CCNP SP
---

# Internet Protocol version 6
{: .no_toc }

Giao thức liên mạng thế hệ 6
{: .fs-6 .fw-300 }

---

## TABLE OF CONTENTS
{: .no_toc .text-delta }

1. TOC
{:toc}

---

## Lab

<img src="/docs/CCNP SP/img/ipv6 lab.png" style="max-width: 100%; width: 1200px" />

```
1. Setup topology trên với các Router xRV1,2 R3,4,5,6 thuộc phân vùng Service Provider, sử dụng OSPF area 0.
2. Thực hiện cấu hình MPLS LDP trong phân vùng Service Provider.
3. Các Router R7,8,9,10 đóng vai trò là Router CE sử dụng IPv6 only , setup kịch bản như sau:
   a. Link R7-xRV1 : 2001:abc:117::/64, thuộc VRF global trên xRV1
   b. Link R9-xRV1 : 2002:abc:119::/64, thuộc VRF A trên xRV1
   c. Link R6-R8 : 2001:cba:168::/64, thuộc VRF global trên R8
   d. Link R6-R10 : 2002:cba:106::/64, thuộc VRF A trên R8
4. Cấu hình BGP tại 2 Router xRV1 và R6 sao cho kết nối được các cặp Router R7-R8, R9-R10 IPv6 thông qua hạ 
tầng Service Provider IPv4 only. (R7-R8 sử dụng kết nối 6PE, R9-R10 sử dụng kết nối 6VPE).
```

```
1. Setup topology tren voi cac Router xRV1,2 R3,4,5,6 thuoc phan vung Service Provider, su dung OSPF area 0.  
2. Thuc hien cau hinh MPLS LDP trong phan vung Service Provider.  
3. Cac Router R7,8,9,10 dong vai tro la Router CE su dung IPv6 only, setup kich ban nhu sau:  
   a. Link R7-xRV1 : 2001:abc:117::/64, thuoc VRF global tren xRV1  
   b. Link R9-xRV1 : 2002:abc:119::/64, thuoc VRF A tren xRV1  
   c. Link R6-R8 : 2001:cba:168::/64, thuoc VRF global tren R8  
   d. Link R6-R10 : 2002:cba:106::/64, thuoc VRF A tren R8  
4. Cau hinh BGP tai 2 Router xRV1 va R6 sao cho ket noi duoc cac cap Router R7-R8, R9-R10 IPv6 thong qua ha 
tang Service Provider IPv4 only. (R7-R8 su dung ket noi 6PE, R9-R10 su dung ket noi 6VPE).
```

<h1>1. Setup topology trên với các Router xRV1,2 R3,4,5,6 thuộc phân vùng Service Provider, sử dụng OSPF area 0.</h1>

**xrv1**
```
conf
!
host xrv1
!
int lo0
  ipv4 addr 1.1.1.1/32
!
int g0/0/0/0
  no shut
  ipv4 addr 10.0.12.1/24
!
int g0/0/0/1
  no shut
  ipv4 addr 10.0.13.1/24
!
int g0/0/0/2
  no shut
  ipv4 addr 10.0.14.1/24
!
router ospf 1
  router-id 1.1.1.1
  area 0
    network point-to-point
    interface lo0
      exit
    interface gi0/0/0/0
      exit
    interface gi0/0/0/1
      exit
    interface gi0/0/0/2
      exit
root
!
commit
end
```

**xrv2**
```
conf
!
host xrv1
!
int lo0
  ipv4 addr 2.2.2.2/32
!
int g0/0/0/0
  no shut
  ipv4 addr 10.0.12.2/24
!
int g0/0/0/1
  no shut
  ipv4 addr 10.0.25.2/24
!
router ospf 1
  router-id 2.2.2.2
  area 0
    network point-to-point
    interface lo0
      exit
    interface gi0/0/0/0
      exit
    interface gi0/0/0/1
      exit
    interface gi0/0/0/2
      exit
root
!
commit
end
```