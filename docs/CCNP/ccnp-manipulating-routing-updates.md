---
layout: default
title: Manipulating Routing Updates
nav_order: 3
parent: CCNP
---

# Manipulating Routing Updates
{: .no_toc }

Thao túng cập nhật định tuyến
{: .fs-6 .fw-300 }

---

## Table of contents
{: .no_toc .text-delta }

1. TOC
{:toc}

---

## Route Redistribution (Phân phối lại tuyến đường)

### <u>Default Seed Metrics</u>

![Alt text](/docs/CCNP/img/default-seed-metric.png)

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

### <u>Redistribution OSPF into RIP</u>

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

### <u>Redistribution OSPF into RIP using Route-map + ACL</u>

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

### <u>Redistribution OSPF into RIP using Route-map + Prefix-list</u>

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

### <u>Redistribution OSPF into RIP using Route-map + Prefix-list (set tag)</u>

nháp
```
# R1
en
conf t
int e0/3
ip add 192.168.14.1 255.255.255.0
no shut
end

# R2/4
en
conf t
router ospf 1
redistribute rip subnets
end

# R3
en
conf t
int e0/0
ip add 192.168.35.3 255.255.255.0
ip ospf 1 area 0
ip ospf network point-to-point
no shut
int e0/3
ip add 192.168.34.3 255.255.255.0
ip ospf 1 area 0
ip ospf network point-to-point
no shut
end

# R4
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
redistribute ospf 1 metric 8
end

# R5
en
conf t
no ip domain-lookup
host R5
int lo0
ip add 5.5.5.5 255.255.255.255
ip ospf 1 area 0
ip ospf network point-to-point
int e0/0
ip add 192.168.35.5 255.255.255.0
ip ospf 1 area 0
ip ospf network point-to-point
no shut
end


en
conf t
route-map OSPF-into-RIP deny 5
 match tag 200
route-map OSPF-into-RIP permit 7
 set tag 200
end

```