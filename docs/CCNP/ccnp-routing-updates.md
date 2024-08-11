---
layout: default
title: Routing Updates
nav_order: 30
parent: CCNP
---

# Routing Updates
{: .no_toc }

Manipulating Routing Updates - Thao túng cập nhật định tuyến
{: .fs-6 .fw-300 }

---

## Table of contents
{: .no_toc .text-delta }

1. TOC
{:toc}

---

## Route Redistribution (Phân phối lại tuyến đường)

### Default Seed Metrics
<br>
![Alt text](/docs/CCNP/img/default-seed-metric.png)

![Alt text](/docs/CCNP/img/route-redistribution-1.png)

* R1
```conf
en
conf t
no ip domain-lookup
host R1
int e0/0
ip add 192.168.12.1 255.255.255.0
no shut
int lo1
ip add 172.30.1.1 255.255.255.0
int lo2
ip add 172.30.2.1 255.255.255.0
router rip
version 2
net 0.0.0.0
no auto-summary
end
```

* R2
```conf
en
conf t
no ip domain-lookup
host R2
int e0/0
ip add 192.168.23.2 255.255.255.0
ip ospf 1 area 0
ip ospf network point-to-point
no shut
int e0/1
ip add 192.168.12.2 255.255.255.0
no shut
router rip
version 2
net 192.168.12.0
no auto-summary
end
```

* R3
```conf
en
conf t
no ip domain-lookup
host R3
int e0/1
ip add 192.168.23.3 255.255.255.0
ip ospf 1 area 0
ip ospf network point-to-point
no shut
int lo1
ip add 172.16.1.3 255.255.255.0
ip ospf 1 area 0
ip ospf network point-to-point
int lo2
ip add 172.16.2.3 255.255.255.0
ip ospf 1 area 0
ip ospf network point-to-point
end
```

* Verify

```conf
R1#sh ip route rip
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

R1#

R2#sh ip route
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

      172.16.0.0/24 is subnetted, 2 subnets
O        172.16.1.0 [110/11] via 192.168.23.3, 00:06:34, Ethernet0/0
O        172.16.2.0 [110/11] via 192.168.23.3, 00:06:34, Ethernet0/0
      172.30.0.0/24 is subnetted, 2 subnets
R        172.30.1.0 [120/1] via 192.168.12.1, 00:00:06, Ethernet0/1
R        172.30.2.0 [120/1] via 192.168.12.1, 00:00:06, Ethernet0/1
      192.168.12.0/24 is variably subnetted, 2 subnets, 2 masks
C        192.168.12.0/24 is directly connected, Ethernet0/1
L        192.168.12.2/32 is directly connected, Ethernet0/1
      192.168.23.0/24 is variably subnetted, 2 subnets, 2 masks
C        192.168.23.0/24 is directly connected, Ethernet0/0
L        192.168.23.2/32 is directly connected, Ethernet0/0
R2#

R3#sh ip route ospf
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

R3#
```
<br>

### Redistribution OSPF into RIP
<br>
* R2 (manual seed metric)
```conf
en
conf t
router rip
redistribute ospf 1 metric 5
no default-metric
end
```

* Verify

```conf
R1#sh ip route rip
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

      172.16.0.0/24 is subnetted, 2 subnets
R        172.16.1.0 [120/5] via 192.168.12.2, 00:00:16, Ethernet0/0
R        172.16.2.0 [120/5] via 192.168.12.2, 00:00:16, Ethernet0/0
R     192.168.23.0/24 [120/5] via 192.168.12.2, 00:00:16, Ethernet0/0
R1#
```

* R2 (manual default seed metric)
```conf
en
conf t
router rip
no redistribute ospf 1
redistribute ospf 1
default-metric 10
end
```

* Verify

```conf
R1#sh ip route rip
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

      172.16.0.0/24 is subnetted, 2 subnets
R        172.16.1.0 [120/10] via 192.168.12.2, 00:00:02, Ethernet0/0
R        172.16.2.0 [120/10] via 192.168.12.2, 00:00:02, Ethernet0/0
R     192.168.23.0/24 [120/10] via 192.168.12.2, 00:00:02, Ethernet0/0
R1#
```
<br>

### Redistribution OSPF into RIP using Route-map + ACL
<br>
* R2
```conf
en
conf t
access-list 1 permit 172.16.1.0 0.0.0.255
access-list 2 permit 172.16.2.0 0.0.0.255
route-map OSPF-into-RIP permit 10
match ip address 1
set metric 1
route-map OSPF-into-RIP permit 20
match ip address 2
set metric 5
route-map OSPF-into-RIP permit 30
set metric 10
router rip
redistribute ospf 1 route-map OSPF-into-RIP
end
```

* Verify

```conf
R1#sh ip route rip
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

      172.16.0.0/24 is subnetted, 2 subnets
R        172.16.1.0 [120/1] via 192.168.12.2, 00:00:02, Ethernet0/0
R        172.16.2.0 [120/5] via 192.168.12.2, 00:00:02, Ethernet0/0
R     192.168.23.0/24 [120/10] via 192.168.12.2, 00:00:02, Ethernet0/0
R1#
```
<br>

### Redistribution OSPF into RIP using Route-map + Prefix-list
<br>
* R2
```conf
en
conf t
ip prefix-list NET2 permit 172.16.2.0/24
route-map OSPF-into-RIP permit 20
no match ip address
match ip address prefix-list NET2
router rip
redistribute ospf 1 route-map OSPF-into-RIP
end
```

* Verify

```conf
R1#sh ip route rip
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

      172.16.0.0/24 is subnetted, 2 subnets
R        172.16.1.0 [120/1] via 192.168.12.2, 00:00:14, Ethernet0/0
R        172.16.2.0 [120/5] via 192.168.12.2, 00:00:14, Ethernet0/0
R     192.168.23.0/24 [120/10] via 192.168.12.2, 00:00:14, Ethernet0/0
R1#
```

* R3
```conf
en
conf t
int lo2
ip address 172.16.2.3 255.255.255.192
end
```

* Verify

```conf
R1#sh ip route rip
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

      172.16.0.0/16 is variably subnetted, 2 subnets, 2 masks
R        172.16.1.0/24 [120/1] via 192.168.12.2, 00:00:22, Ethernet0/0
R        172.16.2.0/26 [120/10] via 192.168.12.2, 00:00:22, Ethernet0/0
R     192.168.23.0/24 [120/10] via 192.168.12.2, 00:00:22, Ethernet0/0
R1#
```

<br>

__Danh sách Tiền tố (Prefix Lists): 'ge' và 'le' được sử dụng như thế nào?__

Danh sách tiền tố (prefix-lists) khớp các tiền tố mạng. Ví dụ, prefix-list này khớp chính xác mạng 192.168.0.0/24:

```conf
ip prefix-list SIMPLE-LIST permit 192.168.0.0/24
```

Nhưng nếu muốn khớp tất cả các mạng /24 trong 192.168.0.0/16 thì sao?

Có thể làm như sau:

```conf
ip prefix-list SIMPLE-LIST permit 192.168.0.0/24
ip prefix-list SIMPLE-LIST permit 192.168.1.0/24
...
ip prefix-list SIMPLE-LIST permit 192.168.254.0/24
```

Tuy nhiên, điều đó sẽ đòi hỏi hơn 200 mục trong danh sách. May mắn thay, có một cách dễ dàng hơn.

Đây là cách sử dụng 'le' và 'ge'. 'le' là ít hơn (LESS-THAN) và 'ge' là lớn hơn (GREATER-THAN).

Chúng được sử dụng để khớp chiều dài của netmask. Hãy xem ví dụ này:

```conf
ip prefix-list SHORT-LIST permit 192.168.0.0/16 ge 24
```

Đầu tiên, trong ví dụ này, cần cố gắng khớp các mạng trong mạng 192.168.0.0/16.

Ví dụ, mạng 192.168.123.0/24 nằm trong mạng 192.168.0.0/16.

Phần 'ge 24' quan tâm đến việc khớp các mạng này chỉ khi netmask của chúng có độ dài là 24 bits hoặc lớn hơn.

Dưới đây là một số ví dụ:<br>
192.168.10.0/24 - Sẽ khớp<br>
192.168.20.4/30 - Cũng sẽ khớp (netmask dài hơn 24 bits)<br>
192.168.128.0/22 - Sẽ KHÔNG khớp (netmask chỉ có 22 bits)<br>
10.0.0.0/24 - Sẽ KHÔNG khớp (nó không nằm trong mạng 192.168.0.0/16)<br>

Có thể đảo ngược logic và sử dụng 'le 24'. Điều đó có nghĩa là netmask phải ít hơn hoặc bằng 24 bits mới khớp.

Nếu chỉ muốn khớp các mạng /24? Cần kết hợp hai toán tử này. Ví dụ:


```conf
ip prefix-list MASK-24 permit 192.168.0.0/16 ge 24 le 24
```

Cách này chỉ cần một dòng, điều mà ví dụ ban đầu sẽ mất hơn 200 dòng để hoàn thành.

<br>

### Redistribution OSPF into RIP using Route-map + Prefix-list (set tag)
<br>
2 vấn đề cần lưu ý khi phân phối routes từ trên 2 điểm: <br>
\- suboptimal (không tối ưu, không phải đường đi tốt nhất) <br>
\- loop (vòng lặp) <br>
<br>
#### Routing loop in redistribution
<br>
* R1
```conf
en
conf t
int e0/1
ip add 192.168.15.1 255.255.255.0
no shut
int e0/3
ip add 192.168.14.1 255.255.255.0
no shut
end
```

* R3
```conf
en
conf t
int e0/3
ip add 192.168.34.3 255.255.255.0
ip ospf 1 area 0
ip ospf network point-to-point
no shut
end
```

* R4
```conf
en
conf t
no ip domain-lookup
host R4
int e0/3
ip add 192.168.34.4 255.255.255.0
ip ospf 1 area 0
ip ospf network point-to-point
no shut
int e0/2
ip add 192.168.14.4 255.255.255.0
no shut
router rip
version 2
net 192.168.14.0
no auto-summary
end
```

* R5
```conf
en
conf t
no ip domain-lookup
host R5
int lo0
ip add 5.5.5.5 255.255.255.255
int e0/1
ip add 192.168.15.5 255.255.255.0
no shut
router rip
version 2
network 192.168.15.0
no auto-summary
redistribute connected metric 9
end
```

* Verify

```conf
R1#sh ip route rip
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

      5.0.0.0/32 is subnetted, 1 subnets
R        5.5.5.5 [120/9] via 192.168.15.5, 00:00:04, Ethernet0/1
      172.16.0.0/24 is subnetted, 2 subnets
R        172.16.1.0 [120/1] via 192.168.12.2, 00:00:02, Ethernet0/0
R        172.16.2.0 [120/5] via 192.168.12.2, 00:00:02, Ethernet0/0
R     192.168.23.0/24 [120/10] via 192.168.12.2, 00:00:02, Ethernet0/0
R     192.168.34.0/24 [120/10] via 192.168.12.2, 00:00:02, Ethernet0/0
R1#ping 5.5.5.5
Type escape sequence to abort.
Sending 5, 100-byte ICMP Echos to 5.5.5.5, timeout is 2 seconds:
!!!!!
Success rate is 100 percent (5/5), round-trip min/avg/max = 1/1/1 ms
R1#traceroute 5.5.5.5
Type escape sequence to abort.
Tracing the route to 5.5.5.5
VRF info: (vrf in name/id, vrf out name/id)
  1 192.168.15.5 0 msec *  1 msec
R1#

R2#sh ip route rip
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

      5.0.0.0/32 is subnetted, 1 subnets
R        5.5.5.5 [120/10] via 192.168.12.1, 00:00:26, Ethernet0/1
      172.30.0.0/24 is subnetted, 2 subnets
R        172.30.1.0 [120/1] via 192.168.12.1, 00:00:26, Ethernet0/1
R        172.30.2.0 [120/1] via 192.168.12.1, 00:00:26, Ethernet0/1
R     192.168.14.0/24 [120/1] via 192.168.12.1, 00:00:26, Ethernet0/1
R     192.168.15.0/24 [120/1] via 192.168.12.1, 00:00:26, Ethernet0/1
R2#sh ip route ospf
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

      172.16.0.0/24 is subnetted, 2 subnets
O        172.16.1.0 [110/11] via 192.168.23.3, 1d23h, Ethernet0/0
O        172.16.2.0 [110/11] via 192.168.23.3, 1d23h, Ethernet0/0
O     192.168.34.0/24 [110/20] via 192.168.23.3, 1d23h, Ethernet0/0
R2#

R4#sh ip route rip
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

      5.0.0.0/32 is subnetted, 1 subnets
R        5.5.5.5 [120/10] via 192.168.14.1, 00:00:17, Ethernet0/2
      172.30.0.0/24 is subnetted, 2 subnets
R        172.30.1.0 [120/1] via 192.168.14.1, 00:00:17, Ethernet0/2
R        172.30.2.0 [120/1] via 192.168.14.1, 00:00:17, Ethernet0/2
R     192.168.12.0/24 [120/1] via 192.168.14.1, 00:00:17, Ethernet0/2
R     192.168.15.0/24 [120/1] via 192.168.14.1, 00:00:17, Ethernet0/2
R4#sh ip route ospf
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

      172.16.0.0/24 is subnetted, 2 subnets
O        172.16.1.0 [110/11] via 192.168.34.3, 00:08:27, Ethernet0/3
O        172.16.2.0 [110/11] via 192.168.34.3, 00:08:27, Ethernet0/3
O     192.168.23.0/24 [110/20] via 192.168.34.3, 00:08:27, Ethernet0/3
R4#
```

* R2
```conf
en
conf t
router ospf 1
redistribute rip subnets
end
```

* Verify

```conf
R4#sh ip route rip
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

R4#sh ip route ospf
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

      5.0.0.0/32 is subnetted, 1 subnets
O E2     5.5.5.5 [110/20] via 192.168.34.3, 00:00:42, Ethernet0/3
      172.16.0.0/24 is subnetted, 2 subnets
O        172.16.1.0 [110/11] via 192.168.34.3, 00:09:44, Ethernet0/3
O        172.16.2.0 [110/11] via 192.168.34.3, 00:09:44, Ethernet0/3
      172.30.0.0/24 is subnetted, 2 subnets
O E2     172.30.1.0 [110/20] via 192.168.34.3, 00:00:42, Ethernet0/3
O E2     172.30.2.0 [110/20] via 192.168.34.3, 00:00:42, Ethernet0/3
O E2  192.168.12.0/24 [110/20] via 192.168.34.3, 00:00:42, Ethernet0/3
O E2  192.168.15.0/24 [110/20] via 192.168.34.3, 00:00:42, Ethernet0/3
O     192.168.23.0/24 [110/20] via 192.168.34.3, 00:09:44, Ethernet0/3
R4#
```

* R4
```
en
conf t
router rip
redistribute ospf 1 metric 8
end
```

* Verify

```conf
R2#sh ip route rip
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

      5.0.0.0/32 is subnetted, 1 subnets
R        5.5.5.5 [120/9] via 192.168.12.1, 00:00:16, Ethernet0/1
      172.30.0.0/24 is subnetted, 2 subnets
R        172.30.1.0 [120/1] via 192.168.12.1, 00:00:16, Ethernet0/1
R        172.30.2.0 [120/1] via 192.168.12.1, 00:00:16, Ethernet0/1
R     192.168.14.0/24 [120/1] via 192.168.12.1, 00:00:16, Ethernet0/1
R     192.168.15.0/24 [120/1] via 192.168.12.1, 00:00:16, Ethernet0/1
R2#

R1#sh ip route rip
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

      5.0.0.0/32 is subnetted, 1 subnets
R        5.5.5.5 [120/8] via 192.168.14.4, 00:00:01, Ethernet0/3
      172.16.0.0/24 is subnetted, 2 subnets
R        172.16.1.0 [120/1] via 192.168.12.2, 00:00:28, Ethernet0/0
R        172.16.2.0 [120/5] via 192.168.12.2, 00:00:28, Ethernet0/0
R     192.168.23.0/24 [120/8] via 192.168.14.4, 00:00:01, Ethernet0/3
R     192.168.34.0/24 [120/8] via 192.168.14.4, 00:00:01, Ethernet0/3
R1#ping 5.5.5.5
Type escape sequence to abort.
Sending 5, 100-byte ICMP Echos to 5.5.5.5, timeout is 2 seconds:
.....
Success rate is 0 percent (0/5)
R1#traceroute 5.5.5.5
Type escape sequence to abort.
Tracing the route to 5.5.5.5
VRF info: (vrf in name/id, vrf out name/id)
  1 192.168.14.4 1 msec 0 msec 1 msec
  2 192.168.34.3 1 msec 1 msec 0 msec
  3 192.168.23.2 0 msec 1 msec 1 msec
  4 192.168.12.1 0 msec 1 msec 0 msec
  5 192.168.14.4 1 msec 1 msec 1 msec
  6 192.168.34.3 1 msec 1 msec 1 msec
  7 192.168.23.2 0 msec 0 msec 0 msec
  8 192.168.12.1 1 msec 1 msec 1 msec
  9 192.168.14.4 1 msec 2 msec 1 msec
 10 192.168.34.3 1 msec 1 msec 1 msec
 11 192.168.23.2 2 msec 1 msec 1 msec
 12 192.168.12.1 1 msec 1 msec 1 msec
 13 192.168.14.4 2 msec 1 msec 1 msec
 14 192.168.34.3 1 msec 3 msec 2 msec
 15 192.168.23.2 1 msec 2 msec 1 msec
 16 192.168.12.1 1 msec 2 msec 2 msec
 17 192.168.14.4 1 msec 2 msec 2 msec
 18 192.168.34.3 2 msec 2 msec 2 msec
 19 192.168.23.2 2 msec 2 msec 3 msec
 20 192.168.12.1 2 msec 2 msec 2 msec
 21 192.168.14.4 2 msec 2 msec 4 msec
 22 192.168.34.3 3 msec 2 msec 3 msec
 23 192.168.23.2 2 msec 2 msec 3 msec
 24 192.168.12.1 3 msec 2 msec 2 msec
 25 192.168.14.4 2 msec 2 msec 4 msec
 26 192.168.34.3 3 msec 2 msec 3 msec
 27 192.168.23.2 3 msec 3 msec 4 msec
 28 192.168.12.1 3 msec 3 msec 4 msec
 29 192.168.14.4 3 msec 3 msec 3 msec
 30 192.168.34.3 2 msec 3 msec 3 msec
```

Mô tả:<br>
\- Ban đầu R1 học được mạng 5.5.5.5 thông qua RIP với metric là 9 (R5 cấu hình quảng bá mạng kết nối trực tiếp vào miền RIP với metric 9)<br>
\- R1 chuyển tiếp mạng 5.5.5.5 học được đến R2 và R4 với metric là 10. Cả R2 và R4 đều xem R1 là nexthop của mạng 5.5.5.5<br>
\- R2 cấu hình phân phối lại các route học được từ miền RIP đi vào miền OSPF, do đó R2 sẽ phân phối lại mạng 5.5.5.5 đến R4<br>
\- R4 có 2 nguồn thông tin về mạng 5.5.5.5, 1 từ RIP và 2 từ OSPF. Do OSPF AD 110 < RIP AD 120, nên R4 xem OSPF là tin cậy hơn và thay thế toàn bộ routes từ RIP thay bằng OSPF external<br>
\- R4 cấu hình phân phối lại các route học được từ miền OSPF đi vào miền RIP với metric là 8<br>
\- R1 có 2 nguồn thông tin về mạng 5.5.5.5, 1 từ R5 với metric 9 và 2 từ R4 với metric 8. R1 chọn R4 là nexthop của mạng 5.5.5.5<br>
\- Routing loop xảy ra: R1->(5.5.5.5)->R4->R2->R1

<br>

#### Route tagging
<br>
* R2
```conf
en
conf t
route-map into-OSPF deny 10
 match tag 100
route-map into-OSPF permit 20
 set tag 200
router ospf 1
redistribute rip subnets route-map into-OSPF
end
```

* R4
```conf
en
conf t
route-map into-RIP deny 10
 match tag 200
route-map into-RIP permit 20
 set tag 100
router rip
redistribute ospf 1 metric 8 route-map into-RIP
end
```

* Verify

```conf
R4#sh ip route 5.5.5.5
Routing entry for 5.5.5.5/32
  Known via "ospf 1", distance 110, metric 20
  Tag 200, type extern 2, forward metric 20
  Redistributing via rip
  Last update from 192.168.34.3 on Ethernet0/3, 00:05:42 ago
  Routing Descriptor Blocks:
  * 192.168.34.3, from 192.168.23.2, 00:05:42 ago, via Ethernet0/3
      Route metric is 20, traffic share count is 1
      Route tag 200
R4#

R1#sh ip route rip
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

      5.0.0.0/32 is subnetted, 1 subnets
R        5.5.5.5 [120/9] via 192.168.15.5, 00:00:10, Ethernet0/1
      172.16.0.0/24 is subnetted, 2 subnets
R        172.16.1.0 [120/1] via 192.168.12.2, 00:00:09, Ethernet0/0
R        172.16.2.0 [120/5] via 192.168.12.2, 00:00:09, Ethernet0/0
R     192.168.23.0/24 [120/8] via 192.168.14.4, 00:00:25, Ethernet0/3
R     192.168.34.0/24 [120/8] via 192.168.14.4, 00:00:25, Ethernet0/3
R1#ping 5.5.5.5
Type escape sequence to abort.
Sending 5, 100-byte ICMP Echos to 5.5.5.5, timeout is 2 seconds:
!!!!!
Success rate is 100 percent (5/5), round-trip min/avg/max = 1/1/1 ms
R1#traceroute 5.5.5.5
Type escape sequence to abort.
Tracing the route to 5.5.5.5
VRF info: (vrf in name/id, vrf out name/id)
  1 192.168.15.5 1 msec *  1 msec
R1#
```
<br>

### Redistribution using Distribute-list
<br>
![Alt text](/docs/CCNP/img/route-redistribution-2.png)

* R1
```conf
en
conf t
no ip domain-lookup
host R1
int e0/2
ip add 10.0.12.1 255.255.255.0
no shut
int e0/3
ip add 10.0.13.1 255.255.255.0
no shut
int lo1
ip add 1.1.1.1 255.255.255.255
int lo2
ip add 2.2.2.2 255.255.255.255
int lo3
ip add 3.3.3.3 255.255.255.255
int lo4
ip add 4.4.4.4 255.255.255.255
router rip
version 2
net 0.0.0.0
no auto-summary
end
```

* R2
```conf
en
conf t
no ip domain-lookup
host R2
int e0/2
ip add 10.0.12.2 255.255.255.0
no shut
int e0/0
ip add 10.0.234.2 255.255.255.0
no shut
router rip
version 2
net 0.0.0.0
no auto-summary
end
```

* R3
```conf
en
conf t
no ip domain-lookup
host R3
int e0/3
ip add 10.0.13.3 255.255.255.0
no shut
int e0/0
ip add 10.0.234.3 255.255.255.0
no shut
router rip
version 2
net 0.0.0.0
no auto-summary
end
```

* R4
```conf
en
conf t
no ip domain-lookup
host R4
int e0/0
ip add 10.0.234.4 255.255.255.0
no shut
router rip
version 2
net 0.0.0.0
no auto-summary
end
```

* Verify

```conf
R2#sh ip route rip
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
R        1.1.1.1 [120/1] via 10.0.12.1, 00:00:15, Ethernet0/2
      2.0.0.0/32 is subnetted, 1 subnets
R        2.2.2.2 [120/1] via 10.0.12.1, 00:00:15, Ethernet0/2
      3.0.0.0/32 is subnetted, 1 subnets
R        3.3.3.3 [120/1] via 10.0.12.1, 00:00:05, Ethernet0/2
      4.0.0.0/32 is subnetted, 1 subnets
R        4.4.4.4 [120/1] via 10.0.12.1, 00:00:05, Ethernet0/2
      10.0.0.0/8 is variably subnetted, 5 subnets, 2 masks
R        10.0.13.0/24 [120/1] via 10.0.234.3, 00:00:07, Ethernet0/0
                      [120/1] via 10.0.12.1, 00:00:15, Ethernet0/2
R2#

R3#sh ip route rip
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
R        1.1.1.1 [120/1] via 10.0.13.1, 00:00:08, Ethernet0/3
      2.0.0.0/32 is subnetted, 1 subnets
R        2.2.2.2 [120/1] via 10.0.13.1, 00:00:08, Ethernet0/3
      3.0.0.0/32 is subnetted, 1 subnets
R        3.3.3.3 [120/1] via 10.0.13.1, 00:00:08, Ethernet0/3
      4.0.0.0/32 is subnetted, 1 subnets
R        4.4.4.4 [120/1] via 10.0.13.1, 00:00:08, Ethernet0/3
      10.0.0.0/8 is variably subnetted, 5 subnets, 2 masks
R        10.0.12.0/24 [120/1] via 10.0.234.2, 00:00:22, Ethernet0/0
                      [120/1] via 10.0.13.1, 00:00:08, Ethernet0/3
R3#

R4#sh ip route rip
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
R        1.1.1.1 [120/2] via 10.0.234.3, 00:00:09, Ethernet0/0
                 [120/2] via 10.0.234.2, 00:00:10, Ethernet0/0
      2.0.0.0/32 is subnetted, 1 subnets
R        2.2.2.2 [120/2] via 10.0.234.3, 00:00:09, Ethernet0/0
                 [120/2] via 10.0.234.2, 00:00:10, Ethernet0/0
      3.0.0.0/32 is subnetted, 1 subnets
R        3.3.3.3 [120/2] via 10.0.234.3, 00:00:09, Ethernet0/0
                 [120/2] via 10.0.234.2, 00:00:10, Ethernet0/0
      4.0.0.0/32 is subnetted, 1 subnets
R        4.4.4.4 [120/2] via 10.0.234.3, 00:00:09, Ethernet0/0
                 [120/2] via 10.0.234.2, 00:00:10, Ethernet0/0
      10.0.0.0/8 is variably subnetted, 4 subnets, 2 masks
R        10.0.12.0/24 [120/1] via 10.0.234.2, 00:00:10, Ethernet0/0
R        10.0.13.0/24 [120/1] via 10.0.234.3, 00:00:09, Ethernet0/0
R4#
```

* R2 (cấu hình Distribute-list + ACL không nhận mạng 10.0.13.0/24)
```conf
en
conf t
ip access-list standard DENY13
deny 10.0.13.0 0.0.0.255
permit any
router rip
distribute-list DENY13 in
end
```

```conf
R2#sh ip route rip
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
R        1.1.1.1 [120/1] via 10.0.12.1, 00:00:09, Ethernet0/2
      2.0.0.0/32 is subnetted, 1 subnets
R        2.2.2.2 [120/1] via 10.0.12.1, 00:00:09, Ethernet0/2
      3.0.0.0/32 is subnetted, 1 subnets
R        3.3.3.3 [120/1] via 10.0.12.1, 00:00:09, Ethernet0/2
      4.0.0.0/32 is subnetted, 1 subnets
R        4.4.4.4 [120/1] via 10.0.12.1, 00:00:09, Ethernet0/2
R2#
```

* R3 (cấu hình Distribute-list + Prefix-list không nhận mạng 10.0.12.0/24)
```conf
en
conf t
ip prefix-list DENY12 deny 10.0.12.0/24
ip prefix-list DENY12 permit 0.0.0.0/0 le 32
router rip
distribute-list prefix DENY12 in e0/0
distribute-list prefix DENY12 in e0/3
end
```

```conf
R3#sh ip route rip
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
R        1.1.1.1 [120/2] via 10.0.234.2, 00:00:04, Ethernet0/0
      2.0.0.0/32 is subnetted, 1 subnets
R        2.2.2.2 [120/2] via 10.0.234.2, 00:00:04, Ethernet0/0
      3.0.0.0/32 is subnetted, 1 subnets
R        3.3.3.3 [120/2] via 10.0.234.2, 00:00:04, Ethernet0/0
      4.0.0.0/32 is subnetted, 1 subnets
R        4.4.4.4 [120/2] via 10.0.234.2, 00:00:04, Ethernet0/0
R3#
```

* R1 (cấu hình Distribute-list + ACL + Prefix-list chỉ quảng bá 2.2.2.2/32 và 4.4.4.4/32 cho R2, chỉ quảng bá 3.3.3.3/32 và 4.4.4.4/32 cho R3)
```conf
en
conf t
ip access-list extended 124
5 permit ip any host 2.2.2.2
10 permit ip any host 4.4.4.4
100 deny ip any any
ip prefix-list PERMIT34 seq 5 permit 3.3.3.3/32
ip prefix-list PERMIT34 seq 10 permit 4.4.4.4/32
ip prefix-list PERMIT34 seq 100 deny 0.0.0.0/0 le 32
router rip
distribute-list 124 out e0/2
distribute-list prefix PERMIT34 out e0/3
end
```

```conf
R2#sh ip route rip
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

      2.0.0.0/32 is subnetted, 1 subnets
R        2.2.2.2 [120/1] via 10.0.12.1, 00:00:06, Ethernet0/2
      3.0.0.0/32 is subnetted, 1 subnets
R        3.3.3.3 [120/2] via 10.0.234.3, 00:00:10, Ethernet0/0
      4.0.0.0/32 is subnetted, 1 subnets
R        4.4.4.4 [120/1] via 10.0.12.1, 00:00:06, Ethernet0/2
R2#

R3#sh ip route rip
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

      2.0.0.0/32 is subnetted, 1 subnets
R        2.2.2.2 [120/2] via 10.0.234.2, 00:00:05, Ethernet0/0
      3.0.0.0/32 is subnetted, 1 subnets
R        3.3.3.3 [120/1] via 10.0.13.1, 00:00:23, Ethernet0/3
      4.0.0.0/32 is subnetted, 1 subnets
R        4.4.4.4 [120/1] via 10.0.13.1, 00:00:23, Ethernet0/3
R3#

R4#sh ip route rip
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

      2.0.0.0/32 is subnetted, 1 subnets
R        2.2.2.2 [120/2] via 10.0.234.2, 00:00:14, Ethernet0/0
      3.0.0.0/32 is subnetted, 1 subnets
R        3.3.3.3 [120/2] via 10.0.234.3, 00:00:12, Ethernet0/0
      4.0.0.0/32 is subnetted, 1 subnets
R        4.4.4.4 [120/2] via 10.0.234.3, 00:00:12, Ethernet0/0
                 [120/2] via 10.0.234.2, 00:00:14, Ethernet0/0
      10.0.0.0/8 is variably subnetted, 4 subnets, 2 masks
R        10.0.12.0/24 [120/1] via 10.0.234.2, 00:00:14, Ethernet0/0
R        10.0.13.0/24 [120/1] via 10.0.234.3, 00:00:12, Ethernet0/0
R4#
```

* R4 (cấu hình Distribute-list + ACL chỉ nhận 4.4.4.4/32 từ R2)
```conf
en
conf t
ip access-list extended 124
5 permit ip host 10.0.234.2 host 4.4.4.4
10 deny ip any host 4.4.4.4
100 permit ip any any
router rip
distribute-list 124 in
end
```

```conf
R4#sh ip route rip
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

      2.0.0.0/32 is subnetted, 1 subnets
R        2.2.2.2 [120/2] via 10.0.234.2, 00:00:06, Ethernet0/0
      3.0.0.0/32 is subnetted, 1 subnets
R        3.3.3.3 [120/2] via 10.0.234.3, 00:00:00, Ethernet0/0
      4.0.0.0/32 is subnetted, 1 subnets
R        4.4.4.4 [120/2] via 10.0.234.2, 00:00:06, Ethernet0/0
      10.0.0.0/8 is variably subnetted, 4 subnets, 2 masks
R        10.0.12.0/24 [120/1] via 10.0.234.2, 00:00:06, Ethernet0/0
R        10.0.13.0/24 [120/1] via 10.0.234.3, 00:00:00, Ethernet0/0
R4#
```

![Alt text](/docs/CCNP/img/route-redistribution-3.png)

* R1
```conf
en
conf t
no ip domain-lookup
host R1
int lo0
ip add 1.1.1.1 255.255.255.255
ip ospf 123 area 123
int e0/0
ip add 10.0.12.1 255.255.255.0
ip ospf 123 area 123
ip ospf network point-to-point
no shut
end
```

* R2
```conf
en
conf t
no ip domain-lookup
host R1
int lo0
ip add 2.2.2.2 255.255.255.255
ip ospf 123 area 123
int e0/0
ip add 10.0.23.2 255.255.255.0
ip ospf 123 area 123
ip ospf network point-to-point
no shut
int e0/1
ip add 10.0.12.2 255.255.255.0
ip ospf 123 area 123
ip ospf network point-to-point
no shut
end
```

* R3
```conf
en
conf t
no ip domain-lookup
host R1
int lo0
ip add 3.3.3.3 255.255.255.255
ip ospf 123 area 123
int e0/1
ip add 10.0.23.3 255.255.255.0
ip ospf 123 area 123
ip ospf network point-to-point
no shut
end
```

* Verify

```conf
R1#sh ip route ospf
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

      2.0.0.0/32 is subnetted, 1 subnets
O        2.2.2.2 [110/11] via 10.0.12.2, 00:00:19, Ethernet0/0
      3.0.0.0/32 is subnetted, 1 subnets
O        3.3.3.3 [110/21] via 10.0.12.2, 00:00:09, Ethernet0/0
      10.0.0.0/8 is variably subnetted, 3 subnets, 2 masks
O        10.0.23.0/24 [110/20] via 10.0.12.2, 00:00:19, Ethernet0/0
R1#
```

* R3 (cấu hình Distribute-list + ACL deny 3.3.3.3/32 out)
```conf
en
conf t
access-list 3 deny host 3.3.3.3
access-list 3 permit any
router ospf 123
distribute-list 3 out
end
```

* Verify (kết quả không thay đổi)

```conf
R1#sh ip route ospf
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

      2.0.0.0/32 is subnetted, 1 subnets
O        2.2.2.2 [110/11] via 10.0.12.2, 00:00:19, Ethernet0/0
      3.0.0.0/32 is subnetted, 1 subnets
O        3.3.3.3 [110/21] via 10.0.12.2, 00:00:09, Ethernet0/0
      10.0.0.0/8 is variably subnetted, 3 subnets, 2 masks
O        10.0.23.0/24 [110/20] via 10.0.12.2, 00:00:19, Ethernet0/0
R1#
```

* R1 (cấu hình Distribute-list + ACL deny 3.3.3.3/32 in)
```conf
en
conf t
access-list 3 deny host 3.3.3.3
access-list 3 permit any
router ospf 123
distribute-list 3 in
end
```

* Verify (kết quả có thay đổi)

```conf
R1#sh ip route ospf
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

      2.0.0.0/32 is subnetted, 1 subnets
O        2.2.2.2 [110/11] via 10.0.12.2, 00:00:21, Ethernet0/0
      10.0.0.0/8 is variably subnetted, 3 subnets, 2 masks
O        10.0.23.0/24 [110/20] via 10.0.12.2, 00:00:21, Ethernet0/0
R1#
```

<b><u>Kết luận: OSPF là giao thức định tuyến link state khác với RIP thay vì quảng bá routes thì OSPF chỉ quảng bá trạng thái liên kết. Do đó OSPF trong cùng area chỉ có thể lọc routes chiều in.</u></b>

<br>

### Redistribution using Filter-list
<br>
![Alt text](/docs/CCNP/img/route-redistribution-4.png)

* R1
```conf
en
conf t
no ip domain-lookup
host R1
int lo0
ip add 1.1.1.1 255.255.255.255
ip ospf 1 area 1
int e0/0
ip add 10.0.14.1 255.255.255.0
ip ospf 1 area 1
ip ospf network point-to-point
no shut
end
```

* R2
```conf
en
conf t
no ip domain-lookup
host R2
int lo0
ip add 2.2.2.2 255.255.255.255
ip ospf 2 area 2
int e0/0
ip add 10.0.24.2 255.255.255.0
ip ospf 2 area 2
ip ospf network point-to-point
no shut
end
```

* R3
```conf
en
conf t
no ip domain-lookup
host R3
int lo0
ip add 3.3.3.3 255.255.255.255
ip ospf 3 area 3
int e0/0
ip add 10.0.34.3 255.255.255.0
ip ospf 3 area 3
ip ospf network point-to-point
no shut
end
```

* R4
```conf
en
conf t
no ip domain-lookup
host R4
int lo0
ip add 4.4.4.4 255.255.255.255
ip ospf 1 area 0
int e0/1
ip add 10.0.14.4 255.255.255.0
ip ospf 1 area 1
ip ospf network point-to-point
no shut
int e0/2
ip add 10.0.24.4 255.255.255.0
ip ospf 1 area 2
ip ospf network point-to-point
no shut
int e0/3
ip add 10.0.34.4 255.255.255.0
ip ospf 1 area 3
ip ospf network point-to-point
no shut
end
```

* Verify

```conf
R1#sh ip route ospf
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

      2.0.0.0/32 is subnetted, 1 subnets
O IA     2.2.2.2 [110/21] via 10.0.14.4, 00:00:27, Ethernet0/0
      3.0.0.0/32 is subnetted, 1 subnets
O IA     3.3.3.3 [110/21] via 10.0.14.4, 00:00:27, Ethernet0/0
      4.0.0.0/32 is subnetted, 1 subnets
O IA     4.4.4.4 [110/11] via 10.0.14.4, 00:00:32, Ethernet0/0
      10.0.0.0/8 is variably subnetted, 4 subnets, 2 masks
O IA     10.0.24.0/24 [110/20] via 10.0.14.4, 00:00:27, Ethernet0/0
O IA     10.0.34.0/24 [110/20] via 10.0.14.4, 00:00:27, Ethernet0/0
R1#

R2#sh ip route ospf
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
O IA     1.1.1.1 [110/21] via 10.0.24.4, 00:01:23, Ethernet0/0
      3.0.0.0/32 is subnetted, 1 subnets
O IA     3.3.3.3 [110/21] via 10.0.24.4, 00:01:23, Ethernet0/0
      4.0.0.0/32 is subnetted, 1 subnets
O IA     4.4.4.4 [110/11] via 10.0.24.4, 00:01:27, Ethernet0/0
      10.0.0.0/8 is variably subnetted, 4 subnets, 2 masks
O IA     10.0.14.0/24 [110/20] via 10.0.24.4, 00:01:23, Ethernet0/0
O IA     10.0.34.0/24 [110/20] via 10.0.24.4, 00:01:23, Ethernet0/0
R2#

R3#sh ip route ospf
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
O IA     1.1.1.1 [110/21] via 10.0.34.4, 00:01:08, Ethernet0/0
      2.0.0.0/32 is subnetted, 1 subnets
O IA     2.2.2.2 [110/21] via 10.0.34.4, 00:01:08, Ethernet0/0
      4.0.0.0/32 is subnetted, 1 subnets
O IA     4.4.4.4 [110/11] via 10.0.34.4, 00:01:11, Ethernet0/0
      10.0.0.0/8 is variably subnetted, 4 subnets, 2 masks
O IA     10.0.14.0/24 [110/20] via 10.0.34.4, 00:01:08, Ethernet0/0
O IA     10.0.24.0/24 [110/20] via 10.0.34.4, 00:01:08, Ethernet0/0
R3#

R4#sh ip route ospf
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
O        1.1.1.1 [110/11] via 10.0.14.1, 00:01:17, Ethernet0/1
      2.0.0.0/32 is subnetted, 1 subnets
O        2.2.2.2 [110/11] via 10.0.24.2, 00:01:17, Ethernet0/2
      3.0.0.0/32 is subnetted, 1 subnets
O        3.3.3.3 [110/11] via 10.0.34.3, 00:01:17, Ethernet0/3
R4#
```

* R4 (cấu hình filter-list chặn area 1 quảng bá route 1.1.1.1/32)
```conf
en
conf t
ip prefix-list 1 deny 1.1.1.1/32
ip prefix-list 1 permit 0.0.0.0/0 le 32
router ospf 1
area 1 filter-list prefix 1 out
end
```

_* (Lưu ý: Câu lệnh area filter-list chỉ có thể dùng với prefix-list)_

* Verify

```conf
R2#sh ip route ospf
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

      3.0.0.0/32 is subnetted, 1 subnets
O IA     3.3.3.3 [110/21] via 10.0.24.4, 00:05:45, Ethernet0/0
      4.0.0.0/32 is subnetted, 1 subnets
O IA     4.4.4.4 [110/11] via 10.0.24.4, 00:05:49, Ethernet0/0
      10.0.0.0/8 is variably subnetted, 4 subnets, 2 masks
O IA     10.0.14.0/24 [110/20] via 10.0.24.4, 00:05:45, Ethernet0/0
O IA     10.0.34.0/24 [110/20] via 10.0.24.4, 00:05:45, Ethernet0/0
R2#
```

* R4 (cấu hình filter-list chặn area 2 nhận route 3.3.3.3/32)
```conf
en
conf t
ip prefix-list 3 deny 3.3.3.3/32
ip prefix-list 3 permit 0.0.0.0/0 le 32
router ospf 1
area 2 filter-list prefix 3 in
end
```

* Verify

```conf
R2#sh ip route ospf
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

      4.0.0.0/32 is subnetted, 1 subnets
O IA     4.4.4.4 [110/11] via 10.0.24.4, 00:08:38, Ethernet0/0
      10.0.0.0/8 is variably subnetted, 4 subnets, 2 masks
O IA     10.0.14.0/24 [110/20] via 10.0.24.4, 00:08:34, Ethernet0/0
O IA     10.0.34.0/24 [110/20] via 10.0.24.4, 00:08:34, Ethernet0/0
R2#
```

### PBR - Policy Based Routing
<br>
![Alt text](/docs/CCNP/img/route-pbr.png)

* R1
```conf
en
conf t
no ip domain-lookup
host R1
int e0/0
ip add 192.168.12.1 255.255.255.0
ip ospf 1 area 0
ip ospf network point-to-point
no shut
int lo1
ip add 1.1.1.1 255.255.255.0
ip ospf 1 area 0
ip ospf network point-to-point
int lo2
ip add 2.2.2.2 255.255.255.0
ip ospf 1 area 0
ip ospf network point-to-point
end
```

* R2
```conf
en
conf t
no ip domain-lookup
host R2
int e0/0
ip add 192.168.12.2 255.255.255.0
ip ospf 1 area 0
ip ospf network point-to-point
no shut
int e0/1
ip add 192.168.213.2 255.255.255.0
ip ospf 1 area 0
ip ospf network point-to-point
bandwidth 4000
no shut
int e0/2
ip add 192.168.223.2 255.255.255.0
ip ospf 1 area 0
ip ospf network point-to-point
no shut
end
```

* R3
```conf
en
conf t
no ip domain-lookup
host R3
int e0/1
ip add 192.168.213.3 255.255.255.0
ip ospf 1 area 0
ip ospf network point-to-point
no shut
int e0/2
ip add 192.168.223.3 255.255.255.0
ip ospf 1 area 0
ip ospf network point-to-point
no shut
int lo3
ip add 3.3.3.3 255.255.255.0
ip ospf 1 area 0
ip ospf network point-to-point
end
```

* Verify (traceroute 1.1.1.1 và 2.2.2.2 đều đi đường e0/2 192.168.223.0/24)

```conf
R2#sh ip route ospf
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

      1.0.0.0/24 is subnetted, 1 subnets
O        1.1.1.0 [110/11] via 192.168.12.1, 00:05:15, Ethernet0/0
      2.0.0.0/24 is subnetted, 1 subnets
O        2.2.2.0 [110/11] via 192.168.12.1, 00:05:15, Ethernet0/0
      3.0.0.0/24 is subnetted, 1 subnets
O        3.3.3.0 [110/11] via 192.168.223.3, 00:04:47, Ethernet0/2
R2#

R1#traceroute 3.3.3.3 source 1.1.1.1
Type escape sequence to abort.
Tracing the route to 3.3.3.3
VRF info: (vrf in name/id, vrf out name/id)
  1 192.168.12.2 0 msec 1 msec 0 msec
  2 192.168.223.3 1 msec *  1 msec
R1#traceroute 3.3.3.3 source 2.2.2.2
Type escape sequence to abort.
Tracing the route to 3.3.3.3
VRF info: (vrf in name/id, vrf out name/id)
  1 192.168.12.2 1 msec 0 msec 0 msec
  2 192.168.223.3 0 msec *  1 msec
R1#
```

* R2 (PBR -> Lái lưu lượng 1.1.1.1 đi 3.3.3.3 sẽ đi qua e0/1 192.168.213.0/24)
```conf
en
conf t
access-list 1 permit 1.1.1.1 0.0.0.255
route-map A1 permit 10
match ip address 1
set interface e0/1
exit
int e0/0
set ip next-hop 192.168.213.3
end
```

* Verify (traceroute 1.1.1.1 và 2.2.2.2 đi 2 hướng khác nhau)

```conf
R1#traceroute 3.3.3.3 source 1.1.1.1
Type escape sequence to abort.
Tracing the route to 3.3.3.3
VRF info: (vrf in name/id, vrf out name/id)
  1 192.168.12.2 1 msec 0 msec 1 msec
  2 192.168.213.3 0 msec *  1 msec
R1#traceroute 3.3.3.3 source 2.2.2.2
Type escape sequence to abort.
Tracing the route to 3.3.3.3
VRF info: (vrf in name/id, vrf out name/id)
  1 192.168.12.2 0 msec 1 msec 0 msec
  2 192.168.223.3 1 msec *  2 msec
R1#
```

### Offset-list
<br>
![Alt text](/docs/CCNP/img/route-offset-list.png)

* R1
```conf
en
conf t
no ip domain-lookup
host R1
int e0/0
ip add 10.0.12.1 255.255.255.0
no shut
router rip
version 2
net 0.0.0.0
no auto-summary
end
```

* R2
```conf
en
conf t
no ip domain-lookup
host R2
int e0/1
ip add 10.0.12.2 255.255.255.0
no shut
int lo0
ip add 2.2.2.2 255.255.255.255
router rip
version 2
net 0.0.0.0
no auto-summary
end
```

* Verify (R1 học được 2.2.2.2 với metric 1)

```conf
R1#sh ip route rip
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

      2.0.0.0/32 is subnetted, 1 subnets
R        2.2.2.2 [120/1] via 10.0.12.2, 00:00:12, Ethernet0/0
R1#
```

* R1
```conf
en
conf t
access-list 2 permit host 2.2.2.2
router rip
offset-list 2 in 4
end
```

* Verify (R1 học được 2.2.2.2 với metric 1+4 là 5)

```conf
R1#sh ip route rip
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

      2.0.0.0/32 is subnetted, 1 subnets
R        2.2.2.2 [120/5] via 10.0.12.2, 00:00:02, Ethernet0/0
R1#
```