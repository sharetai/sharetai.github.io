---
layout: default
title: OSPF
nav_order: 100
parent: CCNP
---

# Open Shortest Path First
{: .no_toc }

Giao thức định tuyến OSPF
{: .fs-6 .fw-300 }

---

## Table of contents
{: .no_toc .text-delta }

1. TOC
{:toc}

---

## Cấu hình OSPF cơ bản

OSPF có các chức năng sau:

- Chia Hệ thống tự trị (AS - Autonomous System) thành một hoặc nhiều vùng logic (gọi là area).

- Quảng bá các tuyến đường bằng cách gửi các LSAs - Link State Advertisements.

- Trao đổi các gói OSPF giữa các thiết bị trong vùng OSPF để đồng bộ hóa thông tin định tuyến.

- Đóng gói các gói OSPF thành các gói IP và gửi các gói ở chế độ unicast hoặc multicast.

*** Các loại gói**

| Loại gói                             | Chức năng                                                                                                          |
| :----------------------------------- | :----------------------------------------------------------------------------------------------------------------- |
| Hello packet                         | Được gửi định kỳ để khám phá và duy trì các mối quan hệ lân cận OSPF.                                              |
| Database Description (DD)            | Chứa thông tin ngắn gọn về cơ sở dữ liệu trạng thái liên kết cục bộ (LSDB) và đồng bộ hóa LSDB trên hai thiết bị.  |
| Link State Request (LSR)             | Yêu cầu LSA cần thiết từ hàng xóm. Các gói LSR chỉ được gửi sau khi các gói DD được trao đổi thành công.           |
| Link State Update (LSU)              | Gửi LSA cần thiết cho hàng xóm.                                                                                    |
| Link State Acknowledgement (LSAck)   | Xác nhận việc nhận LSA.                                                                                            |

![Alt text](/docs/CCNP/img/ospf-state.png)

* __<u>Topology</u>__

![Alt text](/docs/CCNP/img/ospf-lsa-area.png)

* R1
```conf
en
conf t
int e0/0
ip add 10.0.12.1 255.255.255.0
ip ospf 1 area 0
no shut
router ospf 1
router-id 1.1.1.1
end
```

* R2
```conf
en
conf t
int e0/0
ip add 10.0.23.2 255.255.255.0
ip ospf 1 area 1
no shut
int e0/1
ip add 10.0.12.2 255.255.255.0
ip ospf 1 area 0
no shut
router ospf 1
router-id 2.2.2.2
end
```

* R3
```conf
en
conf t
int e0/1
ip add 10.0.23.3 255.255.255.0
ip ospf 1 area 1
no shut
router ospf 1
router-id 3.3.3.3
end
```

* Verify

```conf
R1#show ip ospf neighbor

Neighbor ID     Pri   State           Dead Time   Address         Interface
2.2.2.2           1   FULL/DR         00:00:38    10.0.12.2       Ethernet0/0
R1#show ip ospf database

            OSPF Router with ID (1.1.1.1) (Process ID 1)

                Router Link States (Area 0)

Link ID         ADV Router      Age         Seq#       Checksum Link count
1.1.1.1         1.1.1.1         39          0x80000003 0x001ED2 1
2.2.2.2         2.2.2.2         38          0x80000005 0x00DE06 1

                Net Link States (Area 0)

Link ID         ADV Router      Age         Seq#       Checksum
10.0.12.2       2.2.2.2         45          0x80000001 0x00BE4F

                Summary Net Link States (Area 0)

Link ID         ADV Router      Age         Seq#       Checksum
10.0.23.0       2.2.2.2         87          0x80000001 0x0031D8
R1#show ip route ospf
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

      10.0.0.0/8 is variably subnetted, 3 subnets, 2 masks
O IA     10.0.23.0/24 [110/20] via 10.0.12.2, 00:00:44, Ethernet0/0
R1#

R2#show ip ospf neighbor

Neighbor ID     Pri   State           Dead Time   Address         Interface
1.1.1.1           1   FULL/BDR        00:00:36    10.0.12.1       Ethernet0/1
3.3.3.3           1   FULL/DR         00:00:36    10.0.23.3       Ethernet0/0
R2#show ip ospf database

            OSPF Router with ID (2.2.2.2) (Process ID 1)

                Router Link States (Area 0)

Link ID         ADV Router      Age         Seq#       Checksum Link count
1.1.1.1         1.1.1.1         125         0x80000003 0x001ED2 1
2.2.2.2         2.2.2.2         122         0x80000005 0x00DE06 1

                Net Link States (Area 0)

Link ID         ADV Router      Age         Seq#       Checksum
10.0.12.2       2.2.2.2         129         0x80000001 0x00BE4F

                Summary Net Link States (Area 0)

Link ID         ADV Router      Age         Seq#       Checksum
10.0.23.0       2.2.2.2         171         0x80000001 0x0031D8

                Router Link States (Area 1)

Link ID         ADV Router      Age         Seq#       Checksum Link count
2.2.2.2         2.2.2.2         128         0x80000003 0x00DFEF 1
3.3.3.3         3.3.3.3         127         0x80000004 0x009C2A 1

                Net Link States (Area 1)

Link ID         ADV Router      Age         Seq#       Checksum
10.0.23.3       3.3.3.3         134         0x80000001 0x007184

                Summary Net Link States (Area 1)

Link ID         ADV Router      Age         Seq#       Checksum
10.0.12.0       2.2.2.2         161         0x80000001 0x00AA6A
R2#show ip route ospf
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

R2#

R3#show ip ospf neighbor

Neighbor ID     Pri   State           Dead Time   Address         Interface
2.2.2.2           1   FULL/BDR        00:00:33    10.0.23.2       Ethernet0/1
R3#show ip ospf database

            OSPF Router with ID (3.3.3.3) (Process ID 1)

                Router Link States (Area 1)

Link ID         ADV Router      Age         Seq#       Checksum Link count
2.2.2.2         2.2.2.2         114         0x80000003 0x00DFEF 1
3.3.3.3         3.3.3.3         111         0x80000004 0x009C2A 1

                Net Link States (Area 1)

Link ID         ADV Router      Age         Seq#       Checksum
10.0.23.3       3.3.3.3         118         0x80000001 0x007184

                Summary Net Link States (Area 1)

Link ID         ADV Router      Age         Seq#       Checksum
10.0.12.0       2.2.2.2         147         0x80000001 0x00AA6A
R3#show ip route ospf
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

      10.0.0.0/8 is variably subnetted, 3 subnets, 2 masks
O IA     10.0.12.0/24 [110/20] via 10.0.23.2, 00:01:58, Ethernet0/1
R3#
```

## Các loại LSA và Area trong OSPF

<u>LSA Type 1: OSPF Router LSA</u>

<img src="/docs/CCNP/img/ospf-lsa-01.png" width="25%">

Các Router trong cùng một khu vực sẽ Flooding các LSA Type 1 cho chính nó và cho các Router khác trong cùng khu vực. LSA Type 1 chứa các thông tin về các kết nối trực tiếp (Directly Link) của Router và danh sách các Router hàng xóm. LSA Type 1 chỉ chạy nội bộ trong một Area và không gửi được sang các Area khác.

![Alt text](/docs/CCNP/img/ospf-lsa-1.png)

<u>LSA Type 2: OSPF Network LSA</u>

<img src="/docs/CCNP/img/ospf-lsa-02.png" width="25%">

LSA Type 2 được sử dụng trên môi trường Multi-Access và do Router DR tạo ra để gửi đi tới các Router khác kết nối trực tiếp. Môi trường Broadcast và Multicast đều đòi hỏi phải có DR/BDR, LSA Type 2 sẽ chứa thông tin về tất cả các Router được kết nối trong môi trường Multi-Access. LSA Type 2 cũng chỉ hoạt động nội bộ trong một khu vực và không gửi sang các khu vực khác.

![Alt text](/docs/CCNP/img/ospf-lsa-2.png)

<u>LSA Type 3: OSPF Summary LSA</u>

<img src="/docs/CCNP/img/ospf-lsa-03.png" width="50%">

LSA Type 3 được tạo ra bởi các Router ABR để gửi thông tin giao tiếp giữa 2 khu vực khác nhau, đây cũng là Router cầu nối định tuyến dữ liệu giữa 2 khu vực. Dựa vào hình minh họa ta có thể thấy Router R1 sẽ gửi LSA của mình qua cho R2 và R2 sẽ đưa LSA đó vào trong LSDB của mình, Router R3 và R4 cần biết được mạng trong Area 2 và R2 sẽ làm cầu nối bằng cách nó tự tạo ra LSA Type 3 và Flood tới Area 0. LSA Type 3 này cũng sẽ Flood ra tất cả Router thuộc các Area OSPF khác, bằng cách này mà các Area OSPF khác sẽ biết được mạng của nhau.

Các routes có ký hiệu "O IA" (OSPF Inter Area), là các routes từ các khu vực khác được học thông qua LSA loại 3.

![Alt text](/docs/CCNP/img/ospf-lsa-3.png)

<u>LSA Type 4: OSPF ASBR Summary LSA and LSA Type 5: OSPF ASBR External LSA</u>

<img src="/docs/CCNP/img/ospf-lsa-04.png" width="50%">

LSA Type 4 cũng được tạo ra bởi các Router ABR để gửi thông tin giữa các khu vực khác nhau nhằm báo hiệu Router nào đang là ASBR. Trong trường hợp này R1 sẽ phải Redistribute giao thức định tuyến RIP vào trong OSPF và nó cũng trở thành Router ASBR. Router R1 sẽ bật một Bit trong gói LSA được gọi là Bit External nhằm thông báo rằng chính nó là ASBR  sau đó nó sẽ tạo ra LSA Type 1 để gửi đi tới các Router biên tiếp giáp vùng Backbone (Area 0). Khi Router R2 nhận được thì bản thân nó sẽ tạo ra LSA Type 4 chỉ để chứa thông tin về ai là Router ASBR và không chứa bất kỳ thông tin định tuyến nào khác. Router R2 sẽ tiến hành Flood LSA Type 4 ấy vào Area 0 và dần sang tới tất cả Area khác, khi ấy mọi Router trong hệ thống mạng sẽ biết đâu là Router ASBR.

<img src="/docs/CCNP/img/ospf-lsa-05.png" width="50%">

LSA Type 5 được tạo ra bởi Router ASBR để gửi thông tin định tuyến từ một giao thức định tuyến khác với giao thức định tuyến của các khu vực còn lại. Như trên hình ta thấy Router dùng RIP được gán thêm một mạng trên Interface của mình (5.5.5.0 /24), mạng này sẽ được Redistribute vào các khu vực đang dùng OSPF. R1 chính là Router ASBR và nó sẽ tạo ra LSA Type 5 để Flood đi tới các Area khác. Tuy nhiên quan trọng là phải đảm bảo các LSA Type 4 đã được quảng bá tới các Router trong các Area khác.

Các routes có ký hiệu "O E1" (OSPF External type 1) và "O E2" (OSPF External type 2), là các routes từ các mạng bên ngoài miền ospf được học thông qua LSA loại 5.

![Alt text](/docs/CCNP/img/ospf-lsa-45.png)

<u>LSA Type 7: OSPF Not So Stubby Area (NSSA) External LSA</u>

<img src="/docs/CCNP/img/ospf-lsa-07.png" width="50%">

LSA Type 7 cũng giống như LSA Type 5 nhưng được phép chạy trong vùng NSSA (Not So Stubby Area) bởi vì trong vùng NSSA không tồn tại các gói LSA Type 5 được. Do đó LSA Type 7 có thể xem là  bổ sung cho LSA Type 5 để thực hiện công việc gửi thông tin định tuyến sang vùng NSSA. Router biên giữa vùng NSSA và các vùng khác sẽ tự động chuyển đổi giữa 2 loại LSA này như trên hình ta thấy Router R2 khi nhận LSA Type 7 thì nó sẽ tiến hành biên dịch và chuyển đổi sang LSA Type 5 để Flood được đi tới Area khác.

Các routes sẽ có ký hiệu "O N1" (OSPF NSSA External type 1) và "O N2" (OSPF NSSA External type 2).

![Alt text](/docs/CCNP/img/ospf-lsa-7.png)

<u>LSA Type 6,8,9,10,11</u>

Loại 6 không còn hỗ trợ.<br>
Loại 8,9,10,11 đọc thêm.

### Lab Common area



* R1
```conf
en
conf t
int lo10
ip add 10.10.10.10 255.255.255.0
router ospf 1
redistribute connected subnets
end
```

* R2
```conf
en
conf t
int lo20
ip add 20.20.20.20 255.255.255.0
ip ospf network point-to-point      <== Add thêm network type để quảng bá /24 do mặc định OSPF quảng bá loopback với /32
ip ospf 1 area 0
end
```

* R3
```conf
en
conf t
int lo30
ip add 30.30.30.30 255.255.255.0
router ospf 1
redistribute connected subnets
end
```

* Verify

```conf
R1#show ip ospf database

            OSPF Router with ID (1.1.1.1) (Process ID 1)

                Router Link States (Area 0)

Link ID         ADV Router      Age         Seq#       Checksum Link count
1.1.1.1         1.1.1.1         183         0x80000007 0x001CCE 1
2.2.2.2         2.2.2.2         17          0x8000000B 0x00E4AC 2

                Net Link States (Area 0)

Link ID         ADV Router      Age         Seq#       Checksum
10.0.12.2       2.2.2.2         226         0x80000004 0x00B852

                Summary Net Link States (Area 0)

Link ID         ADV Router      Age         Seq#       Checksum
10.0.23.0       2.2.2.2         226         0x80000004 0x002BDB

                Summary ASB Link States (Area 0)

Link ID         ADV Router      Age         Seq#       Checksum
3.3.3.3         2.2.2.2         156         0x80000001 0x001905

                Type-5 AS External Link States

Link ID         ADV Router      Age         Seq#       Checksum Tag
10.10.10.0      1.1.1.1         619         0x80000001 0x00601E 0
30.30.30.0      3.3.3.3         164         0x80000001 0x0051E8 0
R1#show ip route ospf
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

      10.0.0.0/8 is variably subnetted, 5 subnets, 2 masks
O IA     10.0.23.0/24 [110/20] via 10.0.12.2, 01:42:59, Ethernet0/0
      20.0.0.0/24 is subnetted, 1 subnets
O        20.20.20.0 [110/11] via 10.0.12.2, 00:00:19, Ethernet0/0
      30.0.0.0/24 is subnetted, 1 subnets
O E2     30.30.30.0 [110/20] via 10.0.12.2, 00:02:38, Ethernet0/0
R1#

R3#show ip ospf database

            OSPF Router with ID (3.3.3.3) (Process ID 1)

                Router Link States (Area 1)

Link ID         ADV Router      Age         Seq#       Checksum Link count
2.2.2.2         2.2.2.2         185         0x8000000C 0x00CDF8 1
3.3.3.3         3.3.3.3         190         0x8000000E 0x008E2C 1

                Net Link States (Area 1)

Link ID         ADV Router      Age         Seq#       Checksum
10.0.23.3       3.3.3.3         195         0x80000008 0x00638B

                Summary Net Link States (Area 1)

Link ID         ADV Router      Age         Seq#       Checksum
10.0.12.0       2.2.2.2         203         0x80000006 0x00A06F
20.20.20.0      2.2.2.2         50          0x80000001 0x008473

                Summary ASB Link States (Area 1)

Link ID         ADV Router      Age         Seq#       Checksum
1.1.1.1         2.2.2.2         203         0x80000001 0x0075B0

                Type-5 AS External Link States

Link ID         ADV Router      Age         Seq#       Checksum Tag
10.10.10.0      1.1.1.1         658         0x80000001 0x00601E 0
30.30.30.0      3.3.3.3         200         0x80000001 0x0051E8 0
R3#show ip route ospf
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

      10.0.0.0/8 is variably subnetted, 4 subnets, 2 masks
O IA     10.0.12.0/24 [110/20] via 10.0.23.2, 00:03:24, Ethernet0/1
O E2     10.10.10.0/24 [110/20] via 10.0.23.2, 00:03:14, Ethernet0/1
      20.0.0.0/24 is subnetted, 1 subnets
O IA     20.20.20.0 [110/11] via 10.0.23.2, 00:00:52, Ethernet0/1
R3#ping 10.10.10.10 source 30.30.30.30
Type escape sequence to abort.
Sending 5, 100-byte ICMP Echos to 10.10.10.10, timeout is 2 seconds:
Packet sent with a source address of 30.30.30.30
!!!!!
Success rate is 100 percent (5/5), round-trip min/avg/max = 1/1/1 ms
R3#
```

### Lab Stub area

* R2/3
```conf
en
conf t
router ospf 1
area 1 stub
end
```

* Verify

```conf
R3#show ip ospf database

            OSPF Router with ID (3.3.3.3) (Process ID 1)

                Router Link States (Area 1)

Link ID         ADV Router      Age         Seq#       Checksum Link count
2.2.2.2         2.2.2.2         32          0x8000000F 0x00E5DF 1
3.3.3.3         3.3.3.3         36          0x80000010 0x00A21A 1

                Net Link States (Area 1)

Link ID         ADV Router      Age         Seq#       Checksum
10.0.23.3       3.3.3.3         41          0x80000009 0x007F70

                Summary Net Link States (Area 1)

Link ID         ADV Router      Age         Seq#       Checksum
0.0.0.0         2.2.2.2         43          0x80000001 0x0075C0   <== Stub area lọc các LSA type 4+5, ABR quảng bá defaul route cho các routes bên ngoài miền OSPF
10.0.12.0       2.2.2.2         43          0x80000007 0x00BC54
20.20.20.0      2.2.2.2         43          0x80000002 0x00A058
R3#show ip route ospf
Codes: L - local, C - connected, S - static, R - RIP, M - mobile, B - BGP
       D - EIGRP, EX - EIGRP external, O - OSPF, IA - OSPF inter area
       N1 - OSPF NSSA external type 1, N2 - OSPF NSSA external type 2
       E1 - OSPF external type 1, E2 - OSPF external type 2
       i - IS-IS, su - IS-IS summary, L1 - IS-IS level-1, L2 - IS-IS level-2
       ia - IS-IS inter area, * - candidate default, U - per-user static route
       o - ODR, P - periodic downloaded static route, H - NHRP, l - LISP
       a - application route
       + - replicated route, % - next hop override, p - overrides from PfR

Gateway of last resort is 10.0.23.2 to network 0.0.0.0

O*IA  0.0.0.0/0 [110/11] via 10.0.23.2, 00:00:50, Ethernet0/1  <== Stub area lọc các LSA type 4+5, ABR quảng bá defaul route cho các routes bên ngoài miền OSPF
      10.0.0.0/8 is variably subnetted, 3 subnets, 2 masks
O IA     10.0.12.0/24 [110/20] via 10.0.23.2, 00:01:00, Ethernet0/1
      20.0.0.0/24 is subnetted, 1 subnets
O IA     20.20.20.0 [110/11] via 10.0.23.2, 00:01:00, Ethernet0/1
R3#
```

### Lab Totally stub area

* R2 or R2/3
```conf
en
conf t
router ospf 1
area 1 stub no-summary
end
```

* Verify

```conf
R3#show ip ospf database

            OSPF Router with ID (3.3.3.3) (Process ID 1)

                Router Link States (Area 1)

Link ID         ADV Router      Age         Seq#       Checksum Link count
2.2.2.2         2.2.2.2         600         0x8000000F 0x00E5DF 1
3.3.3.3         3.3.3.3         604         0x80000010 0x00A21A 1

                Net Link States (Area 1)

Link ID         ADV Router      Age         Seq#       Checksum
10.0.23.3       3.3.3.3         609         0x80000009 0x007F70

                Summary Net Link States (Area 1)

Link ID         ADV Router      Age         Seq#       Checksum
0.0.0.0         2.2.2.2         31          0x80000003 0x0071C2   <== Totally stub area lọc các LSA type 3+4+5, ABR quảng bá defaul route cho các routes bên ngoài miền OSPF và các routes khác khu vực
R3#show ip route ospf
Codes: L - local, C - connected, S - static, R - RIP, M - mobile, B - BGP
       D - EIGRP, EX - EIGRP external, O - OSPF, IA - OSPF inter area
       N1 - OSPF NSSA external type 1, N2 - OSPF NSSA external type 2
       E1 - OSPF external type 1, E2 - OSPF external type 2
       i - IS-IS, su - IS-IS summary, L1 - IS-IS level-1, L2 - IS-IS level-2
       ia - IS-IS inter area, * - candidate default, U - per-user static route
       o - ODR, P - periodic downloaded static route, H - NHRP, l - LISP
       a - application route
       + - replicated route, % - next hop override, p - overrides from PfR

Gateway of last resort is 10.0.23.2 to network 0.0.0.0

O*IA  0.0.0.0/0 [110/11] via 10.0.23.2, 00:00:38, Ethernet0/1  <== Totally stub area lọc các LSA type 3+4+5, ABR quảng bá defaul route cho các routes bên ngoài miền OSPF và các routes khác khu vực
R3#ping 10.10.10.10 source 30.30.30.30
Type escape sequence to abort.
Sending 5, 100-byte ICMP Echos to 10.10.10.10, timeout is 2 seconds:
Packet sent with a source address of 30.30.30.30
.....
Success rate is 0 percent (0/5)
R3#

<== Stub area + Totally stub area lọc các LSA type 5 nên ABR R3 không quảng bá route external (30.30.30.30/24) cho R1 ==>
R1#show ip route ospf
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

      10.0.0.0/8 is variably subnetted, 5 subnets, 2 masks
O IA     10.0.23.0/24 [110/20] via 10.0.12.2, 01:57:54, Ethernet0/0
      20.0.0.0/24 is subnetted, 1 subnets
O        20.20.20.0 [110/11] via 10.0.12.2, 00:15:14, Ethernet0/0
R1#
```

### Lab NSSA

* R2/3
```conf
en
conf t
router ospf 1
no area 1 stub
area 1 nssa default-information-originate
end
```

* Verify

```conf
R1#show ip ospf database

            OSPF Router with ID (1.1.1.1) (Process ID 1)

                Router Link States (Area 0)

Link ID         ADV Router      Age         Seq#       Checksum Link count
1.1.1.1         1.1.1.1         129         0x80000008 0x001ACF 1
2.2.2.2         2.2.2.2         520         0x8000000F 0x00E2A8 2

                Net Link States (Area 0)

Link ID         ADV Router      Age         Seq#       Checksum
10.0.12.2       2.2.2.2         158         0x80000005 0x00B653

                Summary Net Link States (Area 0)

Link ID         ADV Router      Age         Seq#       Checksum
10.0.23.0       2.2.2.2         158         0x80000005 0x0029DC

                Type-5 AS External Link States

Link ID         ADV Router      Age         Seq#       Checksum Tag
10.10.10.0      1.1.1.1         628         0x80000002 0x005E1F 0
30.30.30.0      2.2.2.2         648         0x80000001 0x0034E5 0
R1#show ip route ospf
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

      10.0.0.0/8 is variably subnetted, 5 subnets, 2 masks
O IA     10.0.23.0/24 [110/20] via 10.0.12.2, 02:15:38, Ethernet0/0
      20.0.0.0/24 is subnetted, 1 subnets
O        20.20.20.0 [110/11] via 10.0.12.2, 00:32:58, Ethernet0/0
      30.0.0.0/24 is subnetted, 1 subnets
O E2     30.30.30.0 [110/20] via 10.0.12.2, 00:10:55, Ethernet0/0    <== NSSA area lọc các LSA type 4+5, ABR chuyển đổi LSA type 7 thành LSA Type 5 và flood đi tới area khác.
R1#

R3#show ip ospf database

            OSPF Router with ID (3.3.3.3) (Process ID 1)

                Router Link States (Area 1)

Link ID         ADV Router      Age         Seq#       Checksum Link count
2.2.2.2         2.2.2.2         69          0x80000019 0x005F52 1
3.3.3.3         3.3.3.3         79          0x80000018 0x00208A 1

                Net Link States (Area 1)

Link ID         ADV Router      Age         Seq#       Checksum
10.0.23.3       3.3.3.3         200         0x8000000E 0x00FCE5

                Summary Net Link States (Area 1)

Link ID         ADV Router      Age         Seq#       Checksum
10.0.12.0       2.2.2.2         208         0x80000001 0x0050BE
20.20.20.0      2.2.2.2         208         0x80000001 0x002AC7

                Type-7 AS External Link States (Area 1)

Link ID         ADV Router      Age         Seq#       Checksum Tag
0.0.0.0         2.2.2.2         70          0x80000001 0x00D0D8 0    <== NSSA area lọc các LSA type 4+5, ABR dùng LSA type 7 quảng bá defaul route cho các routes bên ngoài miền OSPF
30.30.30.0      3.3.3.3         205         0x80000001 0x00818A 0
R3#show ip route ospf
Codes: L - local, C - connected, S - static, R - RIP, M - mobile, B - BGP
       D - EIGRP, EX - EIGRP external, O - OSPF, IA - OSPF inter area
       N1 - OSPF NSSA external type 1, N2 - OSPF NSSA external type 2
       E1 - OSPF external type 1, E2 - OSPF external type 2
       i - IS-IS, su - IS-IS summary, L1 - IS-IS level-1, L2 - IS-IS level-2
       ia - IS-IS inter area, * - candidate default, U - per-user static route
       o - ODR, P - periodic downloaded static route, H - NHRP, l - LISP
       a - application route
       + - replicated route, % - next hop override, p - overrides from PfR

Gateway of last resort is 10.0.23.2 to network 0.0.0.0

O*N2  0.0.0.0/0 [110/1] via 10.0.23.2, 00:01:18, Ethernet0/1   <== NSSA area lọc các LSA type 4+5, ABR dùng LSA type 7 quảng bá defaul route cho các routes bên ngoài miền OSPF
      10.0.0.0/8 is variably subnetted, 3 subnets, 2 masks
O IA     10.0.12.0/24 [110/20] via 10.0.23.2, 00:01:29, Ethernet0/1
      20.0.0.0/24 is subnetted, 1 subnets
O IA     20.20.20.0 [110/11] via 10.0.23.2, 00:01:29, Ethernet0/1
R3#ping 10.10.10.10 source 30.30.30.30
Type escape sequence to abort.
Sending 5, 100-byte ICMP Echos to 10.10.10.10, timeout is 2 seconds:
Packet sent with a source address of 30.30.30.30
!!!!!
Success rate is 100 percent (5/5), round-trip min/avg/max = 1/1/1 ms
R3#
```

### Lab Totally NSSA

* R2 or R2/3
```conf
en
conf t
router ospf 1
no area 1 stub
area 1 nssa default-information-originate no-summary
end
```

* Verify

```conf
R3#show ip ospf database

            OSPF Router with ID (3.3.3.3) (Process ID 1)

                Router Link States (Area 1)

Link ID         ADV Router      Age         Seq#       Checksum Link count
2.2.2.2         2.2.2.2         33          0x8000001A 0x005D53 1
3.3.3.3         3.3.3.3         998         0x80000018 0x00208A 1

                Net Link States (Area 1)

Link ID         ADV Router      Age         Seq#       Checksum
10.0.23.3       3.3.3.3         1119        0x8000000E 0x00FCE5

                Summary Net Link States (Area 1)

Link ID         ADV Router      Age         Seq#       Checksum
0.0.0.0         2.2.2.2         33          0x80000001 0x00FC31      <== NSSA area lọc các LSA type 3+4+5, ABR dùng LSA type 7 quảng bá defaul route cho các routes bên ngoài miền OSPF

                Type-7 AS External Link States (Area 1)

Link ID         ADV Router      Age         Seq#       Checksum Tag
0.0.0.0         2.2.2.2         989         0x80000001 0x00D0D8 0    <== NSSA area lọc các LSA type 3+4+5, ABR dùng LSA type 7 quảng bá defaul route cho các routes bên ngoài miền OSPF
30.30.30.0      3.3.3.3         1124        0x80000001 0x00818A 0
R3#show ip route ospf
Codes: L - local, C - connected, S - static, R - RIP, M - mobile, B - BGP
       D - EIGRP, EX - EIGRP external, O - OSPF, IA - OSPF inter area
       N1 - OSPF NSSA external type 1, N2 - OSPF NSSA external type 2
       E1 - OSPF external type 1, E2 - OSPF external type 2
       i - IS-IS, su - IS-IS summary, L1 - IS-IS level-1, L2 - IS-IS level-2
       ia - IS-IS inter area, * - candidate default, U - per-user static route
       o - ODR, P - periodic downloaded static route, H - NHRP, l - LISP
       a - application route
       + - replicated route, % - next hop override, p - overrides from PfR

Gateway of last resort is 10.0.23.2 to network 0.0.0.0

O*IA  0.0.0.0/0 [110/11] via 10.0.23.2, 00:00:35, Ethernet0/1        <== NSSA area lọc các LSA type 3+4+5, ABR dùng LSA type 7 quảng bá defaul route cho các routes bên ngoài miền OSPF
R3#ping 10.10.10.10 source 30.30.30.30
Type escape sequence to abort.
Sending 5, 100-byte ICMP Echos to 10.10.10.10, timeout is 2 seconds:
Packet sent with a source address of 30.30.30.30
!!!!!
Success rate is 100 percent (5/5), round-trip min/avg/max = 1/1/1 ms
R3#
```

## Các loại Network Types trong OSPF

| Network Type                         | When                        | Timers                   | DR/BDR | Multicast/Unicast                     | Nexthop            |
| :----------------------------------- | :-------------------------- | :----------------------- | :----- | :------------------------------------ | :----------------- |
| Broadcast                            | Ethernet                    | Hello: 10s<br>Dead: 40s  | Yes    | Multicast (.5, .6)<br>(auto neighbor) | unchanged          |
| Non-Broadcast                        | FR Multipoint               | Hello: 30s<br>Dead: 120s | Yes    | Unicast<br>(manual neighbor)          | unchanged          |
| Point to Point                       | FR P2P, PPP, HDLC           | Hello: 10s<br>Dead: 40s  | No     | Multicast (.5)<br>(auto neighbor)     | changed (neighbor) |
| Point to Multipoint<br>Broadcast     | FR Multipoint, Partial mesh | Hello: 30s<br>Dead: 120s | No     | Multicast (.5)<br>(auto neighbor)     | changed (neighbor) |
| Point to Multipoint<br>Non-Broadcast | FR Multipoint               | Hello: 30s<br>Dead: 120s | No     | Unicast<br>(manual neighbor)          | changed (neighbor) |

## Cấu hình Virtual-Link OSPF

![Alt text](/docs/CCNP/img/ospf-virtual-link.png)

* R1
```conf
en
conf t
int e0/0
ip add 10.0.12.1 255.255.255.0
ip ospf 1 area 0
no shut
router ospf 1
router-id 1.1.1.1
end
```

* R2
```conf
en
conf t
int e0/0
ip add 10.0.23.2 255.255.255.0
ip ospf 1 area 1
no shut
int e0/1
ip add 10.0.12.2 255.255.255.0
ip ospf 1 area 0
no shut
router ospf 1
router-id 2.2.2.2
area 1 virtual-link 3.3.3.3
end
```

* R3
```conf
en
conf t
int e0/0
ip add 10.0.34.3 255.255.255.0
ip ospf 1 area 2
no shut
int e0/1
ip add 10.0.23.3 255.255.255.0
ip ospf 1 area 1
no shut
router ospf 1
router-id 3.3.3.3
area 1 virtual-link 2.2.2.2
area 2 virtual-link 4.4.4.4
end
```

* R4
```conf
en
conf t
int e0/0
ip add 10.0.45.4 255.255.255.0
ip ospf 1 area 3
no shut
int e0/1
ip add 10.0.34.4 255.255.255.0
ip ospf 1 area 2
no shut
router ospf 1
router-id 4.4.4.4
area 2 virtual-link 3.3.3.3
end
```

* R5
```conf
en
conf t
int e0/1
ip add 10.0.45.5 255.255.255.0
ip ospf 1 area 3
no shut
router ospf 1
router-id 5.5.5.5
end
```

* Verify

```conf
R1#show ip ospf neighbor

Neighbor ID     Pri   State           Dead Time   Address         Interface
2.2.2.2           1   FULL/DR         00:00:32    10.0.12.2       Ethernet0/0
R1#show ip route ospf
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

      10.0.0.0/8 is variably subnetted, 5 subnets, 2 masks
O IA     10.0.23.0/24 [110/20] via 10.0.12.2, 00:57:51, Ethernet0/0
O IA     10.0.34.0/24 [110/30] via 10.0.12.2, 00:57:41, Ethernet0/0
O IA     10.0.45.0/24 [110/40] via 10.0.12.2, 00:19:32, Ethernet0/0
R1#

R2#show ip ospf neighbor

Neighbor ID     Pri   State           Dead Time   Address         Interface
3.3.3.3           0   FULL/  -           -        10.0.23.3       OSPF_VL0
1.1.1.1           1   FULL/BDR        00:00:38    10.0.12.1       Ethernet0/1
3.3.3.3           1   FULL/DR         00:00:35    10.0.23.3       Ethernet0/0
R2#show ip route ospf
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

      10.0.0.0/8 is variably subnetted, 6 subnets, 2 masks
O IA     10.0.34.0/24 [110/20] via 10.0.23.3, 00:58:57, Ethernet0/0
O IA     10.0.45.0/24 [110/30] via 10.0.23.3, 00:20:53, Ethernet0/0
R2#

R3#show ip ospf neighbor

Neighbor ID     Pri   State           Dead Time   Address         Interface
4.4.4.4           0   FULL/  -           -        10.0.34.4       OSPF_VL1
2.2.2.2           0   FULL/  -           -        10.0.23.2       OSPF_VL0
2.2.2.2           1   FULL/BDR        00:00:38    10.0.23.2       Ethernet0/1
4.4.4.4           1   FULL/DR         00:00:32    10.0.34.4       Ethernet0/0
R3#show ip route ospf
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

      10.0.0.0/8 is variably subnetted, 6 subnets, 2 masks
O        10.0.12.0/24 [110/20] via 10.0.23.2, 00:58:42, Ethernet0/1
O IA     10.0.45.0/24 [110/20] via 10.0.34.4, 00:20:30, Ethernet0/0
R3#

R4#show ip ospf neighbor

Neighbor ID     Pri   State           Dead Time   Address         Interface
3.3.3.3           0   FULL/  -           -        10.0.34.3       OSPF_VL1
3.3.3.3           1   FULL/BDR        00:00:32    10.0.34.3       Ethernet0/1
5.5.5.5           1   FULL/DR         00:00:39    10.0.45.5       Ethernet0/0
R4#show ip route ospf
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

      10.0.0.0/8 is variably subnetted, 6 subnets, 2 masks
O        10.0.12.0/24 [110/30] via 10.0.34.3, 00:20:36, Ethernet0/1
O IA     10.0.23.0/24 [110/20] via 10.0.34.3, 00:20:36, Ethernet0/1
R4#

R5#show ip ospf neighbor

Neighbor ID     Pri   State           Dead Time   Address         Interface
4.4.4.4           1   FULL/BDR        00:00:35    10.0.45.4       Ethernet0/1
R5#show ip route ospf
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

      10.0.0.0/8 is variably subnetted, 5 subnets, 2 masks
O IA     10.0.12.0/24 [110/40] via 10.0.45.4, 00:21:28, Ethernet0/1
O IA     10.0.23.0/24 [110/30] via 10.0.45.4, 00:21:28, Ethernet0/1
O IA     10.0.34.0/24 [110/20] via 10.0.45.4, 00:21:32, Ethernet0/1
R5#
```