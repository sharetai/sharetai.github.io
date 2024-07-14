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
router eigrp 1234
network 1.0.0.0
network 10.0.0.0
network 10.0.13.1
end
```

* __R2__
```
en
conf t
router eigrp 1234
network 0.0.0.0
end
```

* __R3__
```
en
conf t
router eigrp 1234
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
router eigrp 1234
network 4.4.4.4 0.0.0.0
network 10.0.34.4 0.0.0.0
end
```

__Verify__

```conf
R1#sh run | sec router eigrp
router eigrp 1234
 network 1.0.0.0
 network 10.0.0.0

R2#sh run | sec router eigrp
router eigrp 1234
 network 0.0.0.0
R2#

R3#sh run | sec router eigrp
router eigrp 1234
 network 3.3.3.3 0.0.0.0
 network 10.0.13.0 0.0.0.255
 network 10.0.23.0 0.0.0.255
 network 10.0.34.0 0.0.0.255
R3#

R4#sh run | sec router eigrp
router eigrp 1234
 network 4.4.4.4 0.0.0.0
 network 10.0.34.4 0.0.0.0
R4#
```

```conf
R1#sh ip eigrp neighbors
EIGRP-IPv4 Neighbors for AS(1234)
H   Address                 Interface              Hold Uptime   SRTT   RTO  Q  Seq
                                                   (sec)         (ms)       Cnt Num
1   10.0.13.3               Et0/1                    10 00:01:22    8   100  0  11
0   10.0.12.2               Et0/0                    14 00:01:26    4   100  0  10
R1#sh ip eigrp topology
EIGRP-IPv4 Topology Table for AS(1234)/ID(1.1.1.1)
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
D        2.2.2.2 [90/409600] via 10.0.12.2, 00:01:29, Ethernet0/0
      3.0.0.0/32 is subnetted, 1 subnets
D        3.3.3.3 [90/409600] via 10.0.13.3, 00:01:27, Ethernet0/1
      4.0.0.0/32 is subnetted, 1 subnets
D        4.4.4.4 [90/435200] via 10.0.13.3, 00:01:25, Ethernet0/1
      10.0.0.0/8 is variably subnetted, 6 subnets, 2 masks
D        10.0.23.0/24 [90/307200] via 10.0.13.3, 00:01:29, Ethernet0/1
                      [90/307200] via 10.0.12.2, 00:01:29, Ethernet0/0
D        10.0.34.0/24 [90/307200] via 10.0.13.3, 00:01:27, Ethernet0/1
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
- __Successor__ - best loop free path
- __Feasible Successor__ - loop free backup path
- __Feasible Condition__ - điều kiện để 1 route được xem là backup path và cài vào bảng _eigrp topology_. __RD < FD__. Đây cũng là điều kiện chống loop của EIGRP.

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
EIGRP-IPv4 Topology Table for AS(1234)/ID(1.1.1.1)
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
EIGRP-IPv4 Topology Table for AS(1234)/ID(1.1.1.1)
Codes: P - Passive, A - Active, U - Update, Q - Query, R - Reply,
       r - reply Status, s - sia Status

P 10.0.34.0/24, 1 successors, FD is 307200, serno 5
        via 10.0.13.3 (307200/281600), Ethernet0/1
        via 10.0.12.2 (332800/307200), Ethernet0/0
P 4.4.4.4/32, 1 successors, FD is 435200, serno 7
        via 10.0.13.3 (435200/409600), Ethernet0/1
        via 10.0.12.2 (460800/435200), Ethernet0/0
P 10.0.13.0/24, 1 successors, FD is 281600, serno 3
        via Connected, Ethernet0/1
P 2.2.2.2/32, 1 successors, FD is 409600, serno 9
        via 10.0.12.2 (409600/128256), Ethernet0/0
        via 10.0.13.3 (435200/409600), Ethernet0/1
P 10.0.23.0/24, 2 successors, FD is 307200, serno 10
        via 10.0.12.2 (307200/281600), Ethernet0/0
        via 10.0.13.3 (307200/281600), Ethernet0/1
P 3.3.3.3/32, 1 successors, FD is 409600, serno 4
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
Enter configuration commands, one per line.  End with CNTL/Z.
R2(config)#int e0/0
R2(config-if)#delay 80
R2(config-if)#end
R2#
*Jul 13 12:28:10.076: %SYS-5-CONFIG_I: Configured from console by console
R2#sh int e0/0 | sec DLY
  MTU 1500 bytes, BW 10000 Kbit/sec, DLY 800 usec,
     reliability 255/255, txload 1/255, rxload 1/255

R2#

R1#sh ip eigrp topology
EIGRP-IPv4 Topology Table for AS(1234)/ID(1.1.1.1)
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

DUAL có các đặc điểm sau:
- Khám phá 1 tuyến đường dự phòng nếu có
- Tự động khôi phục tuyến đường
- Hỗ trợ VLSM
- Truy vấn _(query)_ neighbors cho tuyến đường thay thế chưa biết

```
R1#debug eigrp packets query
    (QUERY)
EIGRP Packet debugging is on
R1#sh ip eigrp topology
EIGRP-IPv4 Topology Table for AS(1234)/ID(1.1.1.1)
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
P 10.0.23.0/24, 2 successors, FD is 302080
        via 10.0.12.2 (307200/281600), Ethernet0/0
        via 10.0.13.3 (307200/281600), Ethernet0/1
P 3.3.3.3/32, 1 successors, FD is 409600
        via 10.0.13.3 (409600/128256), Ethernet0/1
P 1.1.1.1/32, 1 successors, FD is 128256
        via Connected, Loopback0
P 10.0.12.0/24, 1 successors, FD is 281600
        via Connected, Ethernet0/0

R1#conf t
Enter configuration commands, one per line.  End with CNTL/Z.
R1(config)#int e0/1
R1(config-if)#shutdown
R1(config-if)#end
R1#
*Jul 13 13:37:17.188: %SYS-5-CONFIG_I: Configured from console by console
*Jul 13 13:37:17.192: %DUAL-5-NBRCHANGE: EIGRP-IPv4 1234: Neighbor 10.0.13.3 (Ethernet0/1) is down: interface down
R1#
*Jul 13 13:37:17.206: EIGRP: Enqueueing QUERY on Et0/0 - paklen 0 tid 0 iidbQ un/rely 0/1 serno 73-76
*Jul 13 13:37:17.215: EIGRP: Sending QUERY on Et0/0 - paklen 178 tid 0
*Jul 13 13:37:17.215:   AS 1234, Flags 0x0:(NULL), Seq 51/0 interfaceQ 0/0 iidbQ un/rely 0/0 serno 73-76
R1#
*Jul 13 13:37:19.189: %LINK-5-CHANGED: Interface Ethernet0/1, changed state to administratively down
*Jul 13 13:37:20.193: %LINEPROTO-5-UPDOWN: Line protocol on Interface Ethernet0/1, changed state to down
R1#sh ip eigrp topology
EIGRP-IPv4 Topology Table for AS(1234)/ID(1.1.1.1)
Codes: P - Passive, A - Active, U - Update, Q - Query, R - Reply,
       r - reply Status, s - sia Status

P 10.0.34.0/24, 1 successors, FD is 332800
        via 10.0.12.2 (332800/307200), Ethernet0/0
P 4.4.4.4/32, 1 successors, FD is 460800
        via 10.0.12.2 (460800/435200), Ethernet0/0
P 10.0.13.0/24, 1 successors, FD is 332800
        via 10.0.12.2 (332800/307200), Ethernet0/0
P 2.2.2.2/32, 1 successors, FD is 409600
        via 10.0.12.2 (409600/128256), Ethernet0/0
P 10.0.23.0/24, 1 successors, FD is 302080
        via 10.0.12.2 (307200/281600), Ethernet0/0
P 3.3.3.3/32, 1 successors, FD is 435200
        via 10.0.12.2 (435200/409600), Ethernet0/0
P 1.1.1.1/32, 1 successors, FD is 128256
        via Connected, Loopback0
P 10.0.12.0/24, 1 successors, FD is 281600
        via Connected, Ethernet0/0

R1#
```

![alt text](/docs/CCNP/img/eigrp-query-1.png)

![alt text](/docs/CCNP/img/eigrp-query-2.png)

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
R1(config)#router eigrp 1234
R1(config-router)#passive-interface lo0
R1(config-router)#passive-interface e0/3
```

## Auto Summary và Manual Summary
<br>
__<u>Auto Summary</u>__

* __R4__
```
en
conf t
int lo1
ip addr 4.4.1.4 255.255.255.255
int lo2
ip addr 4.4.2.4 255.255.255.255
int lo3
ip addr 4.4.3.4 255.255.255.255
end
```

* __R4__
```
en
conf t
router eigrp 1234
net 4.4.1.4 0.0.0.0
net 4.4.2.4 0.0.0.0
net 4.4.3.4 0.0.0.0
end
```

* __R4__
```
en
conf t
router eigrp 1234
auto-summary
end
```

{: .highlight-title }
> Note
>
> Khi bật summary, sẽ sinh ra route summary trỏ tới Null0, các gói tin đến các mạng dư thừa từ kết quả summary sẽ drop để tránh loop.

__Verify__

```conf
R4#sh ip route
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
D        1.1.1.1 [90/435200] via 10.0.34.3, 00:10:52, Ethernet0/1
      2.0.0.0/32 is subnetted, 1 subnets
D        2.2.2.2 [90/435200] via 10.0.34.3, 01:31:48, Ethernet0/1
      3.0.0.0/32 is subnetted, 1 subnets
D        3.3.3.3 [90/409600] via 10.0.34.3, 01:32:02, Ethernet0/1
      4.0.0.0/8 is variably subnetted, 5 subnets, 2 masks
D        4.0.0.0/8 is a summary, 00:00:17, Null0
C        4.4.1.4/32 is directly connected, Loopback1
C        4.4.2.4/32 is directly connected, Loopback2
C        4.4.3.4/32 is directly connected, Loopback3
C        4.4.4.4/32 is directly connected, Loopback0
      10.0.0.0/8 is variably subnetted, 6 subnets, 3 masks
D        10.0.0.0/8 is a summary, 00:00:17, Null0
D        10.0.12.0/24 [90/332800] via 10.0.34.3, 00:10:52, Ethernet0/1
D        10.0.13.0/24 [90/307200] via 10.0.34.3, 01:32:02, Ethernet0/1
D        10.0.23.0/24 [90/307200] via 10.0.34.3, 01:32:02, Ethernet0/1
C        10.0.34.0/24 is directly connected, Ethernet0/1
L        10.0.34.4/32 is directly connected, Ethernet0/1
R4#

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
D        2.2.2.2 [90/409600] via 10.0.12.2, 00:10:59, Ethernet0/0
      3.0.0.0/32 is subnetted, 1 subnets
D        3.3.3.3 [90/409600] via 10.0.13.3, 00:10:59, Ethernet0/1
      4.0.0.0/8 is subnetted, 1 subnets
D        4.0.0.0 [90/435200] via 10.0.13.3, 00:00:27, Ethernet0/1
      10.0.0.0/8 is variably subnetted, 6 subnets, 2 masks
D        10.0.23.0/24 [90/307200] via 10.0.13.3, 00:10:59, Ethernet0/1
                      [90/307200] via 10.0.12.2, 00:10:59, Ethernet0/0
D        10.0.34.0/24 [90/307200] via 10.0.13.3, 00:10:59, Ethernet0/1
R1#
```

__<u>Manual Summary</u>__

* __R4__
```
en
conf t
int e0/1
ip summary-address eigrp 1234 4.4.0.4 255.255.248.0
end
```

__Verify__

```conf
R4#sh ip route
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
D        1.1.1.1 [90/435200] via 10.0.34.3, 00:22:57, Ethernet0/1
      2.0.0.0/32 is subnetted, 1 subnets
D        2.2.2.2 [90/435200] via 10.0.34.3, 01:43:53, Ethernet0/1
      3.0.0.0/32 is subnetted, 1 subnets
D        3.3.3.3 [90/409600] via 10.0.34.3, 01:44:07, Ethernet0/1
      4.0.0.0/8 is variably subnetted, 5 subnets, 2 masks
D        4.4.0.0/21 is a summary, 00:00:48, Null0
C        4.4.1.4/32 is directly connected, Loopback1
C        4.4.2.4/32 is directly connected, Loopback2
C        4.4.3.4/32 is directly connected, Loopback3
C        4.4.4.4/32 is directly connected, Loopback0
      10.0.0.0/8 is variably subnetted, 5 subnets, 2 masks
D        10.0.12.0/24 [90/332800] via 10.0.34.3, 00:22:57, Ethernet0/1
D        10.0.13.0/24 [90/307200] via 10.0.34.3, 01:44:07, Ethernet0/1
D        10.0.23.0/24 [90/307200] via 10.0.34.3, 01:44:07, Ethernet0/1
C        10.0.34.0/24 is directly connected, Ethernet0/1
L        10.0.34.4/32 is directly connected, Ethernet0/1
R4#

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
D        2.2.2.2 [90/409600] via 10.0.12.2, 00:24:01, Ethernet0/0
      3.0.0.0/32 is subnetted, 1 subnets
D        3.3.3.3 [90/409600] via 10.0.13.3, 00:24:01, Ethernet0/1
      4.0.0.0/21 is subnetted, 1 subnets
D        4.4.0.0 [90/435200] via 10.0.13.3, 00:01:55, Ethernet0/1
      10.0.0.0/8 is variably subnetted, 6 subnets, 2 masks
D        10.0.23.0/24 [90/307200] via 10.0.13.3, 00:24:01, Ethernet0/1
                      [90/307200] via 10.0.12.2, 00:24:01, Ethernet0/0
D        10.0.34.0/24 [90/307200] via 10.0.13.3, 00:24:01, Ethernet0/1
R1#
```

## STUCK IN ACTIVE
<br>
Sẽ ra sao nếu _query_ nhưng không nhận được _reply_?

![alt text](/docs/CCNP/img/eigrp-STUCK-IN-ACTIVE.png)

Tối ưu EIGRP
- Giảm query:
  > - EIGRP summary
  > - EIGRP Stub Routing
- Giảm ảnh hưởng của SIA:
  > - EIGRP Active Process Enhancement

EIGRP Stub Router sẽ thông báo rằng, các router neighbor không gửi _query_ đến nó khi xảy ra _active_.

```
R4(config)#router eigrp 1234
R4(config-router)#eigrp stub
```

Mặc định không nhận reply trong 3 phút, router sẽ huỷ bỏ trạng thái neighbor. __Active Process Enhancement__ giảm ảnh hưởng bẳng cách bổ sung thêm 2 thông điệp SIA-Query và SIA-Reply, SIA-Query sẽ gửi sau khi không nhận reply trong 1.5 phút.

<img src="/docs/CCNP/img/eigrp-Active-Process-Enhancement.png" width="50%"/>

## Load Balancing
<br>
EIGRP hỗ trợ cả __equal-cost load balancing__ và __unequal-cost load balancing__.

```
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
D        2.2.2.2 [90/409600] via 10.0.12.2, 00:01:17, Ethernet0/0
      3.0.0.0/32 is subnetted, 1 subnets
D        3.3.3.3 [90/409600] via 10.0.13.3, 00:01:17, Ethernet0/1
      4.0.0.0/32 is subnetted, 1 subnets
D        4.4.4.4 [90/435200] via 10.0.13.3, 00:01:17, Ethernet0/1
      10.0.0.0/8 is variably subnetted, 6 subnets, 2 masks
D        10.0.23.0/24 [90/302080] via 10.0.12.2, 00:01:17, Ethernet0/0
D        10.0.34.0/24 [90/307200] via 10.0.13.3, 00:01:17, Ethernet0/1
R1#sh ip eigrp topology
EIGRP-IPv4 Topology Table for AS(1234)/ID(1.1.1.1)
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

R1#conf t
R1(config)#router eigrp 1234
R1(config-router)#variance 2
R1(config-router)#end

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
D        2.2.2.2 [90/409600] via 10.0.12.2, 00:00:44, Ethernet0/0
      3.0.0.0/32 is subnetted, 1 subnets
D        3.3.3.3 [90/409600] via 10.0.13.3, 00:00:44, Ethernet0/1
                 [90/430080] via 10.0.12.2, 00:00:44, Ethernet0/0
      4.0.0.0/32 is subnetted, 1 subnets
D        4.4.4.4 [90/435200] via 10.0.13.3, 00:00:44, Ethernet0/1
                 [90/455680] via 10.0.12.2, 00:00:44, Ethernet0/0
      10.0.0.0/8 is variably subnetted, 6 subnets, 2 masks
D        10.0.23.0/24 [90/307200] via 10.0.13.3, 00:00:44, Ethernet0/1
                      [90/302080] via 10.0.12.2, 00:00:44, Ethernet0/0
D        10.0.34.0/24 [90/307200] via 10.0.13.3, 00:00:44, Ethernet0/1
                      [90/327680] via 10.0.12.2, 00:00:44, Ethernet0/0
R1#
```

Số `2` trong `variance 2` sẽ lấy các route FS có FD < 2*FDmin.