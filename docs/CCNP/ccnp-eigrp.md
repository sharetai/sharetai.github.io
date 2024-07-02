---
layout: default
title: EIGRP
nav_order: 10
parent: CCNP
---

# Enhanced Interior Gateway Routing Protocol
{: .no_toc }

Giao thức định tuyến vectơ khoảng cách tiên tiến
{: .fs-6 .fw-300 }

---

## Table of contents
{: .no_toc .text-delta }

1. TOC
{:toc}

---

## Tổng quan
<br>
__EIGRP (Enhanced Interior Gateway Routing Protocol)__ là giao thức __độc quyền của Cisco__. EIGRP hỗ trợ _classless routing_ và _VLSM_, route _summarization_, _incremental updates_, _load balacing_ và nhiều tính năng hữu ích khác.

EIGRP xem như sự kết hợp giữa distance vector và link state. Vì có các đặc điểm:
- Các router chạy EIGRP phải trở thành __neighbor__ rồi mới trao đổi thông tin định tuyến.
- EIGRP router tự động tìm neighbor sử dụng __Hello__ và địa chỉ multicast là __224.0.0.10__.
- Mỗi EIGRP router lưu trữ thông tin gồm 3 bảng:
     > __Neighbor table__ – lưu các EIGRP neighbors <br>
     > __Topology table__ – lưu thông tin định tuyến học từ các EIGRP neighbors <br>
     > __Routing table__ –  lưu best routes <br>

## Cấu hình
<br>
![alt text](/docs/CCNP/img/eigrp-lab.png)

__<u>Init</u>__

* __R1__
```
en
conf t
no ip domain-lookup
host R1
int lo0
ip addr 1.1.1.1 255.255.255.255
int e0/0
ip addr 10.0.12.1 255.255.255.0
no shut
int e0/1
ip addr 10.0.13.1 255.255.255.0
no shut
end
```

* __R2__
```
en
conf t
no ip domain-lookup
host R2
int lo0
ip addr 2.2.2.2 255.255.255.255
int e0/0
ip addr 10.0.23.2 255.255.255.0
no shut
int e0/1
ip addr 10.0.12.2 255.255.255.0
no shut
end
```

* __R3__
```
en
conf t
no ip domain-lookup
host R3
int lo0
ip addr 3.3.3.3 255.255.255.255
int e0/0
ip addr 10.0.34.3 255.255.255.0
no shut
int e0/1
ip addr 10.0.23.3 255.255.255.0
no shut
int e0/2
ip addr 10.0.13.3 255.255.255.0
no shut
end
```

* __R4__
```
en
conf t
no ip domain-lookup
host R4
int lo0
ip addr 4.4.4.4 255.255.255.255
int e0/1
ip addr 10.0.34.4 255.255.255.0
no shut
end
```

__<u>EIGRP</u>__

* __R1__
```
en
conf t
router eigrp 123
network 1.0.0.0
network 10.0.0.0
network 10.0.13.1
end
```

* __R2__
```
en
conf t
router eigrp 123
network 0.0.0.0
end
```

* __R3__
```
en
conf t
router eigrp 123
network 3.3.3.3 0.0.0.0
network 10.0.13.0 0.0.0.255
network 10.0.23.0 0.0.0.255
network 10.0.34.3 0.0.0.255
end
```

* __R4__
```
en
conf t
router eigrp 123
network 4.4.4.4 0.0.0.0
network 10.0.34.4 0.0.0.0
end
```

__Verify__

```conf
R1#sh run | sec router eigrp
router eigrp 123
 network 1.0.0.0
 network 10.0.0.0

R2#sh run | sec router eigrp
router eigrp 123
 network 0.0.0.0
R2#

R3#sh run | sec router eigrp
router eigrp 123
 network 3.3.3.3 0.0.0.0
 network 10.0.13.0 0.0.0.255
 network 10.0.23.0 0.0.0.255
 network 10.0.34.0 0.0.0.255
R3#

R4#sh run | sec router eigrp
router eigrp 123
 network 4.4.4.4 0.0.0.0
 network 10.0.34.4 0.0.0.0
R4#
```

```conf
R1#sh ip eigrp neighbors
EIGRP-IPv4 Neighbors for AS(123)
H   Address                 Interface              Hold Uptime   SRTT   RTO  Q  Seq
                                                   (sec)         (ms)       Cnt Num
1   10.0.13.3               Et0/1                    10 00:02:06    9   100  0  16
0   10.0.12.2               Et0/0                    10 00:08:21    6   100  0  17
R1#sh ip eigrp topology
EIGRP-IPv4 Topology Table for AS(123)/ID(1.1.1.1)
Codes: P - Passive, A - Active, U - Update, Q - Query, R - Reply,
       r - reply Status, s - sia Status

P 10.0.34.0/24, 1 successors, FD is 307200
        via 10.0.13.3 (307200/281600), Ethernet0/1
P 4.4.4.4/32, 1 successors, FD is 435200
        via 10.0.13.3 (435200/409600), Ethernet0/1
P 10.0.13.0/24, 1 successors, FD is 281600
        via Connected, Ethernet0/1
P 2.2.2.2/32, 1 successors, FD is 409600
        via 10.0.12.2 (409600/128256), Ethernet0/0
P 10.0.23.0/24, 2 successors, FD is 307200
        via 10.0.12.2 (307200/281600), Ethernet0/0
        via 10.0.13.3 (307200/281600), Ethernet0/1
P 3.3.3.3/32, 1 successors, FD is 409600
        via 10.0.13.3 (409600/128256), Ethernet0/1
P 1.1.1.1/32, 1 successors, FD is 128256
        via Connected, Loopback0
P 10.0.12.0/24, 1 successors, FD is 281600
        via Connected, Ethernet0/0

R1#sh ip route eigrp
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
D        2.2.2.2 [90/409600] via 10.0.12.2, 00:02:30, Ethernet0/0
      3.0.0.0/32 is subnetted, 1 subnets
D        3.3.3.3 [90/409600] via 10.0.13.3, 00:02:30, Ethernet0/1
      4.0.0.0/32 is subnetted, 1 subnets
D        4.4.4.4 [90/435200] via 10.0.13.3, 00:00:39, Ethernet0/1
      10.0.0.0/8 is variably subnetted, 6 subnets, 2 masks
D        10.0.23.0/24 [90/307200] via 10.0.13.3, 00:02:30, Ethernet0/1
                      [90/307200] via 10.0.12.2, 00:02:30, Ethernet0/0
D        10.0.34.0/24 [90/307200] via 10.0.13.3, 00:02:30, Ethernet0/1
R1#
```

## EIGRP Protocol
<br>
![alt text](/docs/CCNP/img/eigrp-rtp.png)

EIGRP có __5__ loại bản tin:
- __Hello__ thiết lập neighbor và duy trì
- __Update__ chứa thông tin định tuyến
- __Acknowledgment (ACK)__ phản hồi Update
- __Query (ít thấy)__ yêu cầu bổ sung nếu thiếu thông tin định tuyến
- __Reply (ít thấy)__ phản hồi Query

EIGRP có __3__ yêu cầu bắt buộc trong bản tin hello phải giống nhau để thiết lập neighbor:
- __ASN__ (autonomous system number)
- __subnet__
- __Tham số K__ (K1, K2, K3, K4, K5, K6)

_(*) Khác với OSPF, kể cả khi time interval hay mtu là khác nhau thì neighbor vẫn up_

## EIGRP Metric
<br>
EIGRP tính toán metric dựa vào băng thông _(bandwidth)_, độ trễ _(delay)_, độ tin cậy _(reliability)_ và tải _(load)_ .Theo mặc định, chỉ băng thông và độ trễ được sử dụng khi tính toán, trong khi độ tin cậy và tải thường là 0.

![alt text](/docs/CCNP/img/eigrp-metric-1.png)

![alt text](/docs/CCNP/img/eigrp-metric-2.png)

![alt text](/docs/CCNP/img/eigrp-metric-3.png)

## Diffusing Update Algorithm (DUAL)
<br>
EIGRP sử dụng thuật toán __Diffusing Update Algorithm (DUAL)__ chọn đường đi tốt nhất, đồng thời tìm ra một đường dự phòng khả thi.

DUAL có một số khái niệm sau:
- __Feasible Distance__ - metric của best route đến đích
- __Reported Distance/Advertised Distance__ - cũng là metric của best route đến đích nhưng là của neighbor và quảng bá vào router
- __Successor__ - best loop-free path
- __Feasible Successor__ loop-free backup path
- __Feasible Condition__ điều kiện để 1 route được xem là backup path và cài vào bảng _eigrp topology_. __RD < FD__. Đây cũng là điều kiện chống loop của EIGRP.

```
Xem kết quả lệnh `sh ip eigrp topology`
- Successor là path được chọn để đến đích.
- Feasible Distance (FD) thể hiện qua `FD is ..` là metric tốt nhất hay nhỏ nhất.
- Mỗi path có 2 giá trị trong dấu "()", biểu diễn "(FD/RD)". Giá trị 2 là Reported Distance (RD).
- Feasible Successor là backup path. Theo lab thì R1 có 2 path có thể đến R4, 1 là best path R1->R3->R4
và 2 là backup path R1->R2->R3->R4. Nhưng ở đây chỉ thấy best path trỏ next hop đến R3 (10.0.13.3), 
không thấy backup path. Xem lệnh `sh ip eigrp topology all-links` sẽ hiện các path không thoả điều kiện 
Feasible Condition, có thể thấy path đến R2 có RD = FD (435200 = 435200) nên không thoả và không xem là 
backup path. Đây là sự không hoàn hảo của Feasible Condition. Có thể thay đổi kết quả từ công thức tính 
metric để sửa cho path đến R2 có thể được chọn làm Feasible Successor, bên dưới là thay đổi delay trên 
link.

R1#sh ip eigrp topology
EIGRP-IPv4 Topology Table for AS(123)/ID(1.1.1.1)
Codes: P - Passive, A - Active, U - Update, Q - Query, R - Reply,
       r - reply Status, s - sia Status

P 10.0.34.0/24, 1 successors, FD is 307200
        via 10.0.13.3 (307200/281600), Ethernet0/1
P 4.4.4.4/32, 1 successors, FD is 435200
        via 10.0.13.3 (435200/409600), Ethernet0/1
P 10.0.13.0/24, 1 successors, FD is 281600
        via Connected, Ethernet0/1
P 2.2.2.2/32, 1 successors, FD is 409600
        via 10.0.12.2 (409600/128256), Ethernet0/0
P 10.0.23.0/24, 2 successors, FD is 307200
        via 10.0.12.2 (307200/281600), Ethernet0/0
        via 10.0.13.3 (307200/281600), Ethernet0/1
P 3.3.3.3/32, 1 successors, FD is 409600
        via 10.0.13.3 (409600/128256), Ethernet0/1
P 1.1.1.1/32, 1 successors, FD is 128256
        via Connected, Loopback0
P 10.0.12.0/24, 1 successors, FD is 281600
        via Connected, Ethernet0/0

R1#sh ip eigrp topology all-links
EIGRP-IPv4 Topology Table for AS(123)/ID(1.1.1.1)
Codes: P - Passive, A - Active, U - Update, Q - Query, R - Reply,
       r - reply Status, s - sia Status

P 10.0.34.0/24, 1 successors, FD is 307200, serno 12
        via 10.0.13.3 (307200/281600), Ethernet0/1
        via 10.0.12.2 (332800/307200), Ethernet0/0
P 4.4.4.4/32, 1 successors, FD is 435200, serno 13
        via 10.0.13.3 (435200/409600), Ethernet0/1
        via 10.0.12.2 (460800/435200), Ethernet0/0
P 10.0.13.0/24, 1 successors, FD is 281600, serno 3
        via Connected, Ethernet0/1
P 2.2.2.2/32, 1 successors, FD is 409600, serno 4
        via 10.0.12.2 (409600/128256), Ethernet0/0
        via 10.0.13.3 (435200/409600), Ethernet0/1
P 10.0.23.0/24, 2 successors, FD is 307200, serno 11
        via 10.0.12.2 (307200/281600), Ethernet0/0
        via 10.0.13.3 (307200/281600), Ethernet0/1
P 3.3.3.3/32, 1 successors, FD is 409600, serno 10
        via 10.0.13.3 (409600/128256), Ethernet0/1
        via 10.0.12.2 (435200/409600), Ethernet0/0
P 1.1.1.1/32, 1 successors, FD is 128256, serno 1
        via Connected, Loopback0
P 10.0.12.0/24, 1 successors, FD is 281600, serno 2
        via Connected, Ethernet0/0

R1#

R2#sh int e0/0 | sec DLY
  MTU 1500 bytes, BW 10000 Kbit/sec, DLY 1000 usec,
     reliability 255/255, txload 1/255, rxload 1/255

R2#conf t
R2(config)#int e0/0
R2(config-if)#delay 80
R2(config-if)#end
R2#sh int e0/0 | sec DLY
  MTU 1500 bytes, BW 10000 Kbit/sec, DLY 800 usec,
     reliability 255/255, txload 1/255, rxload 1/255

R2#

R1#sh ip eigrp topology
EIGRP-IPv4 Topology Table for AS(123)/ID(1.1.1.1)
Codes: P - Passive, A - Active, U - Update, Q - Query, R - Reply,
       r - reply Status, s - sia Status

P 10.0.34.0/24, 1 successors, FD is 307200
        via 10.0.13.3 (307200/281600), Ethernet0/1
        via 10.0.12.2 (327680/302080), Ethernet0/0
P 4.4.4.4/32, 1 successors, FD is 435200
        via 10.0.13.3 (435200/409600), Ethernet0/1
        via 10.0.12.2 (455680/430080), Ethernet0/0
P 10.0.13.0/24, 1 successors, FD is 281600
        via Connected, Ethernet0/1
P 2.2.2.2/32, 1 successors, FD is 409600
        via 10.0.12.2 (409600/128256), Ethernet0/0
P 10.0.23.0/24, 1 successors, FD is 302080
        via 10.0.12.2 (302080/276480), Ethernet0/0
        via 10.0.13.3 (307200/281600), Ethernet0/1
P 3.3.3.3/32, 1 successors, FD is 409600
        via 10.0.13.3 (409600/128256), Ethernet0/1
        via 10.0.12.2 (430080/404480), Ethernet0/0
P 1.1.1.1/32, 1 successors, FD is 128256
        via Connected, Loopback0
P 10.0.12.0/24, 1 successors, FD is 281600
        via Connected, Ethernet0/0

R1#
```

Một vài minh hoạ khác:

Feasibility Condition (Sẽ ra sao nếu R3 cài vào bảng route các path có RD > FD?)

![alt text](/docs/CCNP/img/eigrp-Feasibility-Condition.png)

Feasible Successor thoả mãn điều kiện Feasibility Condition (RD < FD)

![alt text](/docs/CCNP/img/eigrp-Feasible-Successor.png)

Feasibility Condition Is Not Perfect (Là backup path nhưng RD > FD)

![alt text](/docs/CCNP/img/eigrp-Feasibility-Condition-Is-Not-Perfect.png)

## Passive Interface
<br>
Về nguyên tắc là không gửi eigrp ra các cổng kết nối đến host hay loopback, tối ưu khi không cần gửi hello tìm kiếm neighbor đến các host hay loopback.

Bật passive interface trên cổng là:
- Tiếp tục quảng bá thông tin định tuyến của mạng kết nối đến cổng.
- Không gửi, nhận hay xử lý bản tin Hello.

```
R1(config)#router eigrp 123
R1(config-router)#passive-interface lo0
R1(config-router)#passive-interface e0/3
```
