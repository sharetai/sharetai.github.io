---
layout: default
title: OSPF
nav_order: 20
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

## Tổng quan về OSPF
<br>
\- Giao thức ___Open Shortest Path First (OSPF)___, được phát triển bởi tổ chức ___Internet Engineering Task Force (IETF)___, là giao thức ___link-state Interior Gateway Protocol (IGP)___. <br>
\- Hiện tại, ___OSPF Version 2___ được định nghĩa trong ___RFC 2328___ cho ___IPv4___ và ___OSPF Version 3___ được định nghĩa trong ___RFC 2740___ cho ___IPv6___. <br>

![alt text](/docs/CCNP/img/ospf-types-of-routing-protocols.png)
<br>

## Chức năng của OSPF
<br>
\- Chia Hệ thống tự trị (AS - Autonomous System) thành một hoặc nhiều vùng logic (gọi là ___area___). <br>
\- Quảng bá các tuyến đường bằng cách gửi các ___LSAs___ - Link State Advertisements. <br>
\- Trao đổi các gói OSPF giữa các thiết bị trong vùng OSPF để đồng bộ hóa thông tin định tuyến ___LSDB___. <br>
\- Đóng gói các gói OSPF thành các gói IP và gửi các gói ở chế độ ___unicast___ hoặc ___multicast___. <br><br>

## Cấu hình OSPF cơ bản

### Router ID (có lab)
<br>
___Yêu cầu 1 Router ID___ để chạy OSPF. 1 Router ID ___dài 32 bit dạng thập phân___, là duy nhất trong 1 miền AS. <br>
___Router ID có thể được cấu hình thủ công hoặc router chọn tự động___, thứ tự chọn Router ID như sau: <br> <br>
1\. ___Sử dụng Router ID được cấu hình thủ công___ bằng câu lệnh `router-id` mode `router ospf`. <br>
2\. ___Sử dụng địa chỉ IP cao nhất trên cổng loopback___ đang trong tình trạng hoạt động tốt cả vật lý và giao thức (up/up). <br>
3\. ___Sử dụng địa chỉ IP cao nhất trên cổng vật lý___ không phải là loopback và trong tình trạng hoạt động tốt cả vật lý và giao thức (up/up). <br>
<br>
Thứ tự đơn giản, nhưng một vài chi tiết bị che dấu bên dưới thứ tự được nêu ra ở trên. Các chi tiết đó như sau: <br> <br>
\- Cổng mà từ đó Router ID được chọn ra không nhất thiết phải so trùng với một câu lệnh `network`. Nói cách khác, cổng đó không bắt buộc phải chạy OSPF. <br>
\- OSPF không phải quảng bá một tuyến đi đến địa chỉ mạng của Router ID. <br>
\- Router ID không cần thiết phải đến được trong từng bảng định tuyến. <br>
<br>
Sau khi router chạy OSPF và chọn Router ID, nó vẫn sử dụng Router ID này kể cả khi cổng có IP bị hỏng hoặc biến mất hoặc tồn tại một địa chỉ IP lớn hơn. Router chỉ chọn Router ID mới sau khi Router ID được cấu hình lại hoặc quá trình OSPF được khởi động lại.


```
R1>en
R1#conf t
Enter configuration commands, one per line.  End with CNTL/Z.
R1(config)#int e0/0
R1(config-if)#ip addr 10.0.12.1 255.255.255.0
R1(config-if)#no shut
R1(config-if)#
*Mar 16 15:34:19.178: %LINK-3-UPDOWN: Interface Ethernet0/0, changed state to up
*Mar 16 15:34:20.186: %LINEPROTO-5-UPDOWN: Line protocol on Interface Ethernet0/0, changed state to up
R1(config-if)#int e0/1
R1(config-if)#ip addr 10.0.13.1 255.255.255.0
R1(config-if)#no shut
R1(config-if)#
*Mar 16 15:34:37.585: %LINK-3-UPDOWN: Interface Ethernet0/1, changed state to up
*Mar 16 15:34:38.591: %LINEPROTO-5-UPDOWN: Line protocol on Interface Ethernet0/1, changed state to up
R1(config-if)#int e0/2
R1(config-if)#ip addr 10.0.14.1 255.255.255.0
R1(config-if)#exit
R1(config)#router ospf 1
R1(config-router)#exit
R1(config)#do sh ip int bri
Interface                  IP-Address      OK? Method Status                Protocol
Ethernet0/0                10.0.12.1       YES manual up                    up
Ethernet0/1                10.0.13.1       YES manual up                    up
Ethernet0/2                10.0.14.1       YES manual administratively down down
Ethernet0/3                unassigned      YES unset  administratively down down
R1(config)#do sh ip ospf database

            OSPF Router with ID (10.0.13.1) (Process ID 1)
R1(config)#int lo0
R1(config-if)#
*Mar 16 15:36:15.173: %LINEPROTO-5-UPDOWN: Line protocol on Interface Loopback0, changed state to up
R1(config-if)#ip addr 2.2.2.2 255.255.255.255
R1(config-if)#exit
R1(config)#do sh ip int bri
Interface                  IP-Address      OK? Method Status                Protocol
Ethernet0/0                10.0.12.1       YES manual up                    up
Ethernet0/1                10.0.13.1       YES manual up                    up
Ethernet0/2                10.0.14.1       YES manual administratively down down
Ethernet0/3                unassigned      YES unset  administratively down down
Loopback0                  2.2.2.2         YES manual up                    up
R1(config)#do sh ip ospf database

            OSPF Router with ID (10.0.13.1) (Process ID 1)
R1(config)#do clear ip ospf process
Reset ALL OSPF processes? [no]: yes
R1(config)#do sh ip ospf database

            OSPF Router with ID (10.0.13.1) (Process ID 1)
R1(config)#int e0/1
R1(config-if)#shut
R1(config-if)#
*Mar 16 15:37:59.636: %LINK-5-CHANGED: Interface Ethernet0/1, changed state to administratively down
*Mar 16 15:38:00.640: %LINEPROTO-5-UPDOWN: Line protocol on Interface Ethernet0/1, changed state to down
R1(config-if)#do clear ip ospf process
Reset ALL OSPF processes? [no]: yes
R1(config-if)#do sh ip ospf database

            OSPF Router with ID (10.0.13.1) (Process ID 1)
R1(config-if)#no ip addr
R1(config-if)#do sh ip ospf database

            OSPF Router with ID (10.0.13.1) (Process ID 1)
R1(config-if)#do clear ip ospf process
Reset ALL OSPF processes? [no]: yes
R1(config-if)#do sh ip ospf database

            OSPF Router with ID (2.2.2.2) (Process ID 1)
R1(config-if)#exit
R1(config)#router ospf 1
R1(config-router)#router-id 1.1.1.1
R1(config-router)#exit
R1(config)#do sh ip ospf database

            OSPF Router with ID (1.1.1.1) (Process ID 1)
R1(config)#router ospf 2
R1(config-router)#router ospf 3
R1(config-router)#router ospf 4
R1(config-router)#
*Mar 16 15:41:24.074: %OSPF-4-NORTRID: OSPF process 4 failed to allocate unique router-id and cannot start
R1(config-router)#exit
R1(config)#do sh ip ospf database
%OSPF: Router process 4 is not running, please configure a router-id

            OSPF Router with ID (10.0.12.1) (Process ID 3)

            OSPF Router with ID (2.2.2.2) (Process ID 2)

            OSPF Router with ID (1.1.1.1) (Process ID 1)
R1(config)#
```

```
R2>en
R2#conf t
Enter configuration commands, one per line.  End with CNTL/Z.
R2(config)#int e0/1
R2(config-if)#ip addr 10.0.12.2 255.255.255.0
R2(config-if)#no shut
R2(config-if)#
*Mar 16 15:51:14.752: %LINK-3-UPDOWN: Interface Ethernet0/1, changed state to up
*Mar 16 15:51:15.756: %LINEPROTO-5-UPDOWN: Line protocol on Interface Ethernet0/1, changed state to up
R2(config-if)#router ospf 1
R2(config-router)#network 10.0.12.2 0.0.0.0 area 0
R2(config-router)#
*Mar 16 15:52:32.787: %OSPF-5-ADJCHG: Process 1, Nbr 1.1.1.1 on Ethernet0/1 from LOADING to FULL, Loading Done
R2(config-router)#end
R2#
*Mar 16 15:52:50.754: %SYS-5-CONFIG_I: Configured from console by console
R2#sh ip ospf database

            OSPF Router with ID (10.0.12.2) (Process ID 1)

                Router Link States (Area 0)

Link ID         ADV Router      Age         Seq#       Checksum Link count
1.1.1.1         1.1.1.1         36          0x80000002 0x0016DC 1
10.0.12.2       10.0.12.2       35          0x80000002 0x009A2F 1

                Net Link States (Area 0)

Link ID         ADV Router      Age         Seq#       Checksum
10.0.12.1       1.1.1.1         36          0x80000001 0x00B949
R2#show ip route
Codes: L - local, C - connected, S - static, R - RIP, M - mobile, B - BGP
       D - EIGRP, EX - EIGRP external, O - OSPF, IA - OSPF inter area
       N1 - OSPF NSSA external type 1, N2 - OSPF NSSA external type 2
       E1 - OSPF external type 1, E2 - OSPF external type 2
       i - IS-IS, su - IS-IS summary, L1 - IS-IS level-1, L2 - IS-IS level-2
       ia - IS-IS inter area, * - candidate default, U - per-user static route
       o - ODR, P - periodic downloaded static route, H - NHRP, l - LISP
       a - application route
       + - replicated route, % - next hop override

Gateway of last resort is not set

      10.0.0.0/8 is variably subnetted, 2 subnets, 2 masks
C        10.0.12.0/24 is directly connected, Ethernet0/1
L        10.0.12.2/32 is directly connected, Ethernet0/1
R2#
```
<br>

### Link State
<br>
___Link State___ - Là thông tin trạng thái kết nối của router. Bao gồm: <br>
\- ___IP Address/mask___ <br>
\- ___Network Type___ - Môi trường Ethernet là broadcast hay môi trường Serial là point-to-point <br>
\- ___Cost___ <br>
\- ___Neighbor routers___ của link <br>
<br>

### Cost (có lab)
<br>
\- ___OSPF sử dụng cost làm metric.___ <br>
\- Công thức tính: ___cost = 100M / Interface bandwidth___. 100 Mbit/s là OSPF reference bandwidth. _(Note: Đối với các giao diện trên 100M, chi phí sẽ làm tròn là 1, không chính xác. Do đó sử dụng lệnh `auto-cost reference-bandwidth` trong mode `router ospf` để thay đổi reference bandwidth)_ <br>
\- ___Cost của tuyến đường là tổng giá trị cost của tất cả các interface từ router nguồn đến router đích.___ <br>
<br>

![alt text](/docs/CCNP/img/ospf-cost.png)

* R1
```
enable
conf t
host R1
int lo0
ip addr 1.1.1.1 255.255.255.255
int e0/0
ip addr 10.0.12.1 255.255.255.0
no shut
router ospf 1
router-id 1.1.1.1
network 0.0.0.0 0.0.0.0 area 0
end
```

* R2
```
enable
conf t
host R2
int lo0
ip addr 2.2.2.2 255.255.255.255
int e0/0
ip addr 10.0.23.2 255.255.255.0
ip ospf cost 1000
no shut
int e0/1
ip addr 10.0.12.2 255.255.255.0
ip ospf cost 100
no shut
router ospf 1
router-id 2.2.2.2
network 0.0.0.0 0.0.0.0 area 0
end
```

* R3
```
enable
conf t
host R3
int lo0
ip addr 3.3.3.3 255.255.255.255
int e0/1
ip addr 10.0.23.3 255.255.255.0
ip ospf cost 10000
no shut
router ospf 1
router-id 3.3.3.3
network 0.0.0.0 0.0.0.0 area 0
end
```

Verify

```
R1#show ip route | e subnets|-
C        1.1.1.1 is directly connected, Loopback0
O        2.2.2.2 [110/11] via 10.0.12.2, 00:04:32, Ethernet0/0
O        3.3.3.3 [110/1011] via 10.0.12.2, 00:04:22, Ethernet0/0
C        10.0.12.0/24 is directly connected, Ethernet0/0
L        10.0.12.1/32 is directly connected, Ethernet0/0
O        10.0.23.0/24 [110/1010] via 10.0.12.2, 00:04:32, Ethernet0/0

R2#show ip route | e subnets|-
O        1.1.1.1 [110/101] via 10.0.12.1, 00:04:44, Ethernet0/1
C        2.2.2.2 is directly connected, Loopback0
O        3.3.3.3 [110/1001] via 10.0.23.3, 00:04:34, Ethernet0/0
C        10.0.12.0/24 is directly connected, Ethernet0/1
L        10.0.12.2/32 is directly connected, Ethernet0/1
C        10.0.23.0/24 is directly connected, Ethernet0/0
L        10.0.23.2/32 is directly connected, Ethernet0/0

R3#show ip route | e subnets|-
O        1.1.1.1 [110/10101] via 10.0.23.2, 00:04:41, Ethernet0/1
O        2.2.2.2 [110/10001] via 10.0.23.2, 00:04:41, Ethernet0/1
C        3.3.3.3 is directly connected, Loopback0
O        10.0.12.0/24 [110/10100] via 10.0.23.2, 00:04:41, Ethernet0/1
C        10.0.23.0/24 is directly connected, Ethernet0/1
L        10.0.23.3/32 is directly connected, Ethernet0/1
```

### Packet Types + Adjacency establishment (có lab)
<br>
<h4> Packet Types </h4>
<br>
OSPF đóng gói trực tiếp ___5___ kiểu thông điệp OSPF khác nhau bên trong gói tin IP, dùng giao thức ___IP 89___

| Loại gói                             | Chức năng                                                                                                          |
| :----------------------------------- | :----------------------------------------------------------------------------------------------------------------- |
| Hello                                | Được gửi định kỳ để khám phá, thoả hiệp và duy trì các mối quan hệ neighbor.                                       |
| Database Description (DD)            | Chứa thông tin ngắn gọn về cơ sở dữ liệu trạng thái liên kết cục bộ (LSDB) và đồng bộ hóa LSDB trên hai thiết bị.  |
| Link State Request (LSR)             | Yêu cầu LSA cần thiết từ hàng xóm. Các gói LSR chỉ được gửi sau khi các gói DD được trao đổi thành công.           |
| Link State Update (LSU)              | Gửi LSA cần thiết cho hàng xóm.                                                                                    |
| Link State Acknowledgement (LSAck)   | Xác nhận việc nhận LSA.                                                                                            |

<br>

<h4> Adjacency establishment </h4>
<br>
![Alt text](/docs/CCNP/img/ospf-state.png)

OSPF lắng nghe những thông điệp Hello được gửi đến 224.0.0.5. Đây là địa chỉ multicast cho tất cả các router chạy OSPF, trên bất cứ cổng nào đã bật OSPF. Các gói Hello sẽ lấy nguồn từ địa chỉ chính trên cổng.
Khi hai router tìm ra nhau thông qua các gói Hello, các router thực hiện các phép kiểm tra các thông số như sau:

- Các router phải vượt qua tiến trình xác thực.
- Các router phải trong cùng địa chỉ mạng chính, phải có cùng mặt nạ mạng con.
- Phải trong cùng vùng OSPF _(area)_.
- Phải có cùng kiểu vùng OSPF _(area type)_.
- Phải có cùng kiểu môi trường OSPF _(network type)_.
- Không trùng Router ID.
- Thời gian gửi gói tin Hello _(hello interval)_ và thời gian hết hạn _(dead interval)_ phải bằng nhau. Thời gian *dead interval* mặc định bằng bốn lần thời gian *hello interval*.

Nếu bất kỳ điều kiện nào nêu trên không thỏa mãn, hai router đơn giản sẽ không hình thành quan hệ láng giềng. Cũng lưu ý rằng một trong những điều kiện quan trọng nhất mà hai bên không cần giống là chỉ số Proces ID của tiến trình OSPF, như được cấu hình trong câu lệnh `router ospf process-id`. Cũng nên lưu ý rằng giá trị MTU phải bằng nhau để các gói tin DD được gửi thành công giữa những láng giềng nhưng thông số này không được kiểm tra trong tiến trình Hello.

Phân biệt _neighbor_ và _adjacency_:

- _Neighbor_: Khi giao diện OSPF của _local router_ gửi gói _Hello_ đến _remote router_. _Remote router_ nhận được gói, nó sẽ kiểm tra xem các tham số được mang trong gói có phù hợp với các tham số riêng của nó hay không. Nếu các tham số là phù hợp, thì _local router_ và _remote router_ thiết lập quan hệ _neighbor_.
- _Adjacency_: Sau khi _local router_ và _remote router_ thiết lập quan hệ _neighbor_, trao đổi tiếp các gói DD và LSA để thiết lập _adjacency_.

OSPF có 7 trạng thái state machines:

- _Down_: khi router không nhận được _Hello_ khi _dead interval_ hết hạn.
- _Init_: khi router nhận được _Hello_.
- _2-way_: khi gói _Hello_ nhận được có chứa _router ID local_.
- _Exstart_: khi 2 _neighbor_ bắt đầu thương lượng _master/slave_ và xác định _sequence numbers_ của các gói DD.
- _Exchange_: khi bắt đầu trao đổi các gói DD.
- _Loading_: khi đã hoàn tất việc trao đổi các gói DD.
- _Full_: khi danh sách LSA cần truyền lại là trống.

<br>

<h4> LAB </h4>
<br>
![Alt text](/docs/CCNA/img/ospf-topo.png)

* R1
```
enable
conf t
host R1
int lo0
ip addr 1.1.1.1 255.255.255.255
int e0/0
ip addr 10.0.12.1 255.255.255.0
no shut
router ospf 1
router-id 1.1.1.1
network 0.0.0.0 0.0.0.0 area 0
end
```

* R2
```
enable
conf t
host R2
int lo0
ip addr 2.2.2.2 255.255.255.255
int e0/1
ip addr 10.0.12.2 255.255.255.0
no shut
router ospf 1
router-id 2.2.2.2
network 0.0.0.0 0.0.0.0 area 0
end
```

![Alt text](/docs/CCNA/img/ospf-process-1.png)

![Alt text](/docs/CCNA/img/ospf-process-2.png)

![Alt text](/docs/CCNA/img/ospf-process-3.png)

![Alt text](/docs/CCNA/img/ospf-process-4.png)

![Alt text](/docs/CCNA/img/ospf-process-5.png)

![Alt text](/docs/CCNA/img/ospf-process-6.png)

![Alt text](/docs/CCNA/img/ospf-process-7.png)

![Alt text](/docs/CCNA/img/ospf-process-8.png)

![Alt text](/docs/CCNA/img/ospf-process-9.png)

![Alt text](/docs/CCNA/img/ospf-process-10.png)

![Alt text](/docs/CCNA/img/ospf-process-11.png)

![Alt text](/docs/CCNA/img/ospf-process-12.png)

![Alt text](/docs/CCNA/img/ospf-process-13.png)

<br>

### LSA Types (có lab)
<br>

| Loại LSA                     | Chức năng                                                                                                |
| :------------------------    | :------------------------------------------------------------------------------------------------------- |
| Router-LSA (Type 1)          | Các router cùng area trao đổi trạng thái liên kết cho nhau để xây dựng routes nội vùng (intra area routes) |
| Network-LSA (Type 2)         | Thông báo vị trí của DR trong 1 area                                                                     |
| Network-summary-LSA (Type 3) | Quảng bá routes giữa các area trong cùng miền OSPF (inter area routes)                                   |
| ASBR-summary-LSA (Type 4)    | Thông báo vị trí của ASBR trong 1 miền OSPF                                                              |
| AS-external-LSA (Type 5)     | Quảng bá routes bên ngoài vào trong miền OSPF (external routes)                                          |
| NSSA-LSA (Type 7)            | Quảng bá routes bên ngoài vào trong miền OSPF nhưng để đi qua vùng NSSA (nssa external routes)           |

<br>

![Alt text](/docs/CCNP/img/ospf-lsa-area.png)

* R1
```conf
enable
conf t
host R1
no ip domain-lookup
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
enable
conf t
host R2
no ip domain-lookup
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
enable
conf t
host R3
no ip domain-lookup
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

* R1
```conf
enable
conf t
int lo10
ip add 10.10.10.10 255.255.255.0
router ospf 1
redistribute connected subnets      <== Có subnets để quảng bá /24 classless, không có sẽ quảng bá /8 classful
end
```

* R2
```conf
enable
conf t
int lo20
ip add 20.20.20.20 255.255.255.0
ip ospf network point-to-point      <== Add thêm network type để quảng bá /24 do mặc định OSPF quảng bá loopback với /32
ip ospf 1 area 0
end
```

* R3
```conf
enable
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
```

<br>

#### LSA Type 1: OSPF Router LSA
<br>
<img src="/docs/CCNP/img/ospf-lsa-01.png" width="25%">

Các Router trong cùng một khu vực sẽ Flooding các LSA Type 1 cho chính nó và cho các Router khác trong cùng khu vực. LSA Type 1 chứa các thông tin về các kết nối trực tiếp (Directly Link) của Router và danh sách các Router hàng xóm. LSA Type 1 chỉ chạy nội bộ trong một Area và không gửi được sang các Area khác.

![Alt text](/docs/CCNP/img/ospf-lsa-1.png)

```
R1#show ip ospf database router

            OSPF Router with ID (1.1.1.1) (Process ID 1)

                Router Link States (Area 0)

  LS age: 421
  Options: (No TOS-capability, DC)
  LS Type: Router Links
  Link State ID: 1.1.1.1
  Advertising Router: 1.1.1.1
  LS Seq Number: 80000006
  Checksum: 0x1ECD
  Length: 36
  AS Boundary Router
  Number of Links: 1

    Link connected to: a Transit Network
     (Link ID) Designated Router address: 10.0.12.2
     (Link Data) Router Interface address: 10.0.12.1
      Number of MTID metrics: 0
       TOS 0 Metrics: 10


  LS age: 418
  Options: (No TOS-capability, DC)
  LS Type: Router Links
  Link State ID: 2.2.2.2
  Advertising Router: 2.2.2.2
  LS Seq Number: 80000007
  Checksum: 0xECA8
  Length: 48
  Area Border Router
  Number of Links: 2

    Link connected to: a Stub Network
     (Link ID) Network/subnet number: 20.20.20.0
     (Link Data) Network Mask: 255.255.255.0
      Number of MTID metrics: 0
       TOS 0 Metrics: 1

    Link connected to: a Transit Network
     (Link ID) Designated Router address: 10.0.12.2
     (Link Data) Router Interface address: 10.0.12.2
      Number of MTID metrics: 0
       TOS 0 Metrics: 10
```

<br>

#### LSA Type 2: OSPF Network LSA
<br>
<img src="/docs/CCNP/img/ospf-lsa-02.png" width="25%">

LSA Type 2 được sử dụng trên môi trường Multi-Access và do Router DR tạo ra để gửi đi tới các Router khác kết nối trực tiếp. Môi trường Broadcast và Multicast đều đòi hỏi phải có DR/BDR, LSA Type 2 sẽ chứa thông tin về tất cả các Router được kết nối trong môi trường Multi-Access. LSA Type 2 cũng chỉ hoạt động nội bộ trong một khu vực và không gửi sang các khu vực khác.

![Alt text](/docs/CCNP/img/ospf-lsa-2.png)

```
R1#show ip ospf database network

            OSPF Router with ID (1.1.1.1) (Process ID 1)

                Net Link States (Area 0)

  LS age: 678
  Options: (No TOS-capability, DC)
  LS Type: Network Links
  Link State ID: 10.0.12.2 (address of Designated Router)
  Advertising Router: 2.2.2.2
  LS Seq Number: 80000001
  Checksum: 0xBE4F
  Length: 32
  Network Mask: /24
        Attached Router: 2.2.2.2
        Attached Router: 1.1.1.1
```

<br>

#### LSA Type 3: OSPF Summary LSA
<br>
<img src="/docs/CCNP/img/ospf-lsa-03.png" width="50%">

LSA Type 3 được tạo ra bởi các Router ABR để gửi thông tin giao tiếp giữa 2 khu vực khác nhau, đây cũng là Router cầu nối định tuyến dữ liệu giữa 2 khu vực. Dựa vào hình minh họa ta có thể thấy Router R1 sẽ gửi LSA của mình qua cho R2 và R2 sẽ đưa LSA đó vào trong LSDB của mình, Router R3 và R4 cần biết được mạng trong Area 2 và R2 sẽ làm cầu nối bằng cách nó tự tạo ra LSA Type 3 và Flood tới Area 0. LSA Type 3 này cũng sẽ Flood ra tất cả Router thuộc các Area OSPF khác, bằng cách này mà các Area OSPF khác sẽ biết được mạng của nhau.

Các routes có ký hiệu "O IA" (OSPF Inter Area), là các routes từ các khu vực khác được học thông qua LSA loại 3.

![Alt text](/docs/CCNP/img/ospf-lsa-3.png)

```
R1#show ip ospf database summary

            OSPF Router with ID (1.1.1.1) (Process ID 1)

                Summary Net Link States (Area 0)

  LS age: 797
  Options: (No TOS-capability, DC, Upward)
  LS Type: Summary Links(Network)
  Link State ID: 10.0.23.0 (summary Network Number)
  Advertising Router: 2.2.2.2
  LS Seq Number: 80000001
  Checksum: 0x31D8
  Length: 28
  Network Mask: /24
        MTID: 0         Metric: 10
```

<br>

#### LSA Type 4: OSPF ASBR Summary LSA
<br>
<img src="/docs/CCNP/img/ospf-lsa-04.png" width="50%">

LSA Type 4 được tạo ra bởi các Router ABR để gửi thông tin giữa các khu vực khác nhau nhằm báo hiệu Router nào đang là ASBR. Trong trường hợp này R1 sẽ phải Redistribute giao thức định tuyến RIP vào trong OSPF và nó cũng trở thành Router ASBR. Router R1 sẽ bật một Bit trong gói LSA được gọi là Bit External nhằm thông báo rằng chính nó là ASBR  sau đó nó sẽ tạo ra LSA Type 1 để gửi đi tới các Router biên tiếp giáp vùng Backbone (Area 0). Khi Router R2 nhận được thì bản thân nó sẽ tạo ra LSA Type 4 chỉ để chứa thông tin về ai là Router ASBR và không chứa bất kỳ thông tin định tuyến nào khác. Router R2 sẽ tiến hành Flood LSA Type 4 ấy vào Area 0 và dần sang tới tất cả Area khác, khi ấy mọi Router trong hệ thống mạng sẽ biết đâu là Router ASBR.

```
R1#show ip ospf database asbr-summary

            OSPF Router with ID (1.1.1.1) (Process ID 1)

                Summary ASB Link States (Area 0)

  LS age: 679
  Options: (No TOS-capability, DC, Upward)
  LS Type: Summary Links(AS Boundary Router)
  Link State ID: 3.3.3.3 (AS Boundary Router address)
  Advertising Router: 2.2.2.2
  LS Seq Number: 80000001
  Checksum: 0x1905
  Length: 28
  Network Mask: /0
        MTID: 0         Metric: 10
```

<br>

#### LSA Type 5: OSPF ASBR External LSA
<br>

<img src="/docs/CCNP/img/ospf-lsa-05.png" width="50%">

LSA Type 5 được tạo ra bởi Router ASBR để gửi thông tin định tuyến từ một giao thức định tuyến khác với giao thức định tuyến của các khu vực còn lại. Như trên hình ta thấy Router dùng RIP được gán thêm một mạng trên Interface của mình (5.5.5.0 /24), mạng này sẽ được Redistribute vào các khu vực đang dùng OSPF. R1 chính là Router ASBR và nó sẽ tạo ra LSA Type 5 để Flood đi tới các Area khác. Tuy nhiên quan trọng là phải đảm bảo các LSA Type 4 đã được quảng bá tới các Router trong các Area khác.

Các routes có ký hiệu "O E1" (OSPF External type 1) và "O E2" (OSPF External type 2), là các routes từ các mạng bên ngoài miền ospf được học thông qua LSA loại 5.

![Alt text](/docs/CCNP/img/ospf-lsa-45.png)

```
R1#show ip ospf database external

            OSPF Router with ID (1.1.1.1) (Process ID 1)

                Type-5 AS External Link States

  LS age: 772
  Options: (No TOS-capability, DC, Upward)
  LS Type: AS External Link
  Link State ID: 10.10.10.0 (External Network Number )
  Advertising Router: 1.1.1.1
  LS Seq Number: 80000001
  Checksum: 0x601E
  Length: 36
  Network Mask: /24
        Metric Type: 2 (Larger than any link state path)
        MTID: 0
        Metric: 20
        Forward Address: 0.0.0.0
        External Route Tag: 0

  LS age: 707
  Options: (No TOS-capability, DC, Upward)
  LS Type: AS External Link
  Link State ID: 30.30.30.0 (External Network Number )
  Advertising Router: 3.3.3.3
  LS Seq Number: 80000001
  Checksum: 0x51E8
  Length: 36
  Network Mask: /24
        Metric Type: 2 (Larger than any link state path)
        MTID: 0
        Metric: 20
        Forward Address: 0.0.0.0
        External Route Tag: 0
```

<br>

#### LSA Type 7: OSPF Not So Stubby Area (NSSA) External LSA
<br>
<img src="/docs/CCNP/img/ospf-lsa-07.png" width="50%">

LSA Type 7 cũng giống như LSA Type 5 nhưng được phép chạy trong vùng NSSA (Not So Stubby Area) bởi vì trong vùng NSSA không tồn tại các gói LSA Type 5 được. Do đó LSA Type 7 có thể xem là  bổ sung cho LSA Type 5 để thực hiện công việc gửi thông tin định tuyến sang vùng NSSA. Router biên giữa vùng NSSA và các vùng khác sẽ tự động chuyển đổi giữa 2 loại LSA này như trên hình ta thấy Router R2 khi nhận LSA Type 7 thì nó sẽ tiến hành biên dịch và chuyển đổi sang LSA Type 5 để Flood được đi tới Area khác.

Các routes sẽ có ký hiệu "O N1" (OSPF NSSA External type 1) và "O N2" (OSPF NSSA External type 2).

![Alt text](/docs/CCNP/img/ospf-lsa-7.png)

<br>

```
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

<h4> Stub area </h4>

* R2/3
```conf
enable
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

<h4> Totally stub area </h4>

* R2 or R2/3
```conf
enable
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
0.0.0.0         2.2.2.2         31          0x80000003 0x0071C2   <== Totally stub area lọc các LSA type 3+4+5, ABR quảng bá defaul route cho các routes bên ngoài miền OSPF và các routes khác area
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

O*IA  0.0.0.0/0 [110/11] via 10.0.23.2, 00:00:38, Ethernet0/1  <== Totally stub area lọc các LSA type 3+4+5, ABR quảng bá defaul route cho các routes bên ngoài miền OSPF và các routes khác area
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

<h4> NSSA </h4>

* R2/3
```conf
enable
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

<h4> Totally NSSA </h4>

* R2 or R2/3
```conf
enable
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
0.0.0.0         2.2.2.2         33          0x80000001 0x00FC31      <== NSSA area lọc các LSA type 3+4+5, ABR dùng LSA type 7 quảng bá defaul route cho các routes bên ngoài miền OSPF và các routes khác area

                Type-7 AS External Link States (Area 1)

Link ID         ADV Router      Age         Seq#       Checksum Tag
0.0.0.0         2.2.2.2         989         0x80000001 0x00D0D8 0    <== NSSA area lọc các LSA type 3+4+5, ABR dùng LSA type 7 quảng bá defaul route cho các routes bên ngoài miền OSPF và các routes khác area
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

O*IA  0.0.0.0/0 [110/11] via 10.0.23.2, 00:00:35, Ethernet0/1        <== NSSA area lọc các LSA type 3+4+5, ABR dùng LSA type 7 quảng bá defaul route cho các routes bên ngoài miền OSPF và các routes khác area
R3#ping 10.10.10.10 source 30.30.30.30
Type escape sequence to abort.
Sending 5, 100-byte ICMP Echos to 10.10.10.10, timeout is 2 seconds:
Packet sent with a source address of 30.30.30.30
!!!!!
Success rate is 100 percent (5/5), round-trip min/avg/max = 1/1/1 ms
R3#
```

<u>LSA Type 6,8,9,10,11</u>

Loại 6 không còn hỗ trợ.<br>
Loại 8,9,10,11 đọc thêm.<br>
<br>

### Area types and accepted LSAs
<br>

<table class="wikitable mw-collapsible mw-made-collapsible" style="text-align:center;">
<tbody><tr style="text-align:left;">
<th>
</th>
<th colspan="3" style="text-align:center;">Within a single area
</th>
<th colspan="3" style="text-align:center;">Inter area
</th></tr>
<tr>
<td style="text-align:left;">Area type
</td>
<td><b>LSA 1 - router</b>
</td>
<td><b>LSA 2 - network</b>
</td>
<td><b>LSA 7 - NSSA external</b>
</td>
<td><b>LSA 3 - network summary</b>
</td>
<td><b>LSA 4 - ASBR Summary</b>
</td>
<td><b>LSA 5 - AS external</b>
</td></tr>
<tr>
<td style="text-align:right;">Backbone
</td>
<td style="background:#9EFF9E;color:black;vertical-align:middle;text-align:center;" class="table-yes">Yes
</td>
<td style="background:#9EFF9E;color:black;vertical-align:middle;text-align:center;" class="table-yes">Yes
</td>
<td style="background:#FFC7C7;color:black;vertical-align:middle;text-align:center;" class="table-no">No, converted into a Type 5 by the ABR
</td>
<td style="background:#9EFF9E;color:black;vertical-align:middle;text-align:center;" class="table-yes">Yes
</td>
<td style="background:#9EFF9E;color:black;vertical-align:middle;text-align:center;" class="table-yes">Yes
</td>
<td style="background:#9EFF9E;color:black;vertical-align:middle;text-align:center;" class="table-yes">Yes
</td></tr>
<tr>
<td style="text-align:right;">Non-backbone
</td>
<td style="background:#9EFF9E;color:black;vertical-align:middle;text-align:center;" class="table-yes">Yes
</td>
<td style="background:#9EFF9E;color:black;vertical-align:middle;text-align:center;" class="table-yes">Yes
</td>
<td style="background:#FFC7C7;color:black;vertical-align:middle;text-align:center;" class="table-no">No, converted into a Type 5 by the ABR
</td>
<td style="background:#9EFF9E;color:black;vertical-align:middle;text-align:center;" class="table-yes">Yes
</td>
<td style="background:#9EFF9E;color:black;vertical-align:middle;text-align:center;" class="table-yes">Yes
</td>
<td style="background:#9EFF9E;color:black;vertical-align:middle;text-align:center;" class="table-yes">Yes
</td></tr>
<tr>
<td style="text-align:right;">Stub
</td>
<td style="background:#9EFF9E;color:black;vertical-align:middle;text-align:center;" class="table-yes">Yes
</td>
<td style="background:#9EFF9E;color:black;vertical-align:middle;text-align:center;" class="table-yes">Yes
</td>
<td style="background:#FFC7C7;color:black;vertical-align:middle;text-align:center;" class="table-no">No, Default route
</td>
<td style="background:#9EFF9E;color:black;vertical-align:middle;text-align:center;" class="table-yes">Yes
</td>
<td style="background:#FFC7C7;color:black;vertical-align:middle;text-align:center;" class="table-no">No, Default route
</td>
<td style="background:#FFC7C7;color:black;vertical-align:middle;text-align:center;" class="table-no">No, Default route
</td></tr>
<tr>
<td style="text-align:right;">Totally stubby
</td>
<td style="background:#9EFF9E;color:black;vertical-align:middle;text-align:center;" class="table-yes">Yes
</td>
<td style="background:#9EFF9E;color:black;vertical-align:middle;text-align:center;" class="table-yes">Yes
</td>
<td style="background:#FFC7C7;color:black;vertical-align:middle;text-align:center;" class="table-no">No, Default route
</td>
<td style="background:#FFC7C7;color:black;vertical-align:middle;text-align:center;" class="table-no">No, Default route
</td>
<td style="background:#FFC7C7;color:black;vertical-align:middle;text-align:center;" class="table-no">No, Default route
</td>
<td style="background:#FFC7C7;color:black;vertical-align:middle;text-align:center;" class="table-no">No, Default route
</td></tr>
<tr>
<td style="text-align:right;">Not-so-stubby
</td>
<td style="background:#9EFF9E;color:black;vertical-align:middle;text-align:center;" class="table-yes">Yes
</td>
<td style="background:#9EFF9E;color:black;vertical-align:middle;text-align:center;" class="table-yes">Yes
</td>
<td style="background:#9EFF9E;color:black;vertical-align:middle;text-align:center;" class="table-yes">Yes
</td>
<td style="background:#9EFF9E;color:black;vertical-align:middle;text-align:center;" class="table-yes">Yes
</td>
<td style="background:#FFC7C7;color:black;vertical-align:middle;text-align:center;" class="table-no">No, Default route
</td>
<td style="background:#FFC7C7;color:black;vertical-align:middle;text-align:center;" class="table-no">No, Default route
</td></tr>
<tr>
<td style="text-align:right;">Totally not-so-stubby
</td>
<td style="background:#9EFF9E;color:black;vertical-align:middle;text-align:center;" class="table-yes">Yes
</td>
<td style="background:#9EFF9E;color:black;vertical-align:middle;text-align:center;" class="table-yes">Yes
</td>
<td style="background:#9EFF9E;color:black;vertical-align:middle;text-align:center;" class="table-yes">Yes
</td>
<td style="background:#FFC7C7;color:black;vertical-align:middle;text-align:center;" class="table-no">No, Default route
</td>
<td style="background:#FFC7C7;color:black;vertical-align:middle;text-align:center;" class="table-no">No, Default route
</td>
<td style="background:#FFC7C7;color:black;vertical-align:middle;text-align:center;" class="table-no">No, Default route
</td></tr></tbody></table>
<br>

### Router Types
<br>
![alt text](/docs/CCNP/img/ospf-router-types.png)

| Loại Router               | Mô tả                                                     |
| :------------------------ | :-------------------------------------------------------- |
| Internal router           | Tất cả các interface trên router thuộc cùng area          |
| Area Border Router (ABR)  | 1 ABR thuộc về 2 area hay nhiều hơn, 1 trong đó là area 0 |
| Backbone router           | Ít nhất 1 interface thuộc area 0                          |
| AS Boundary Router (ASBR) | ASBR trao đổi thông tin định tuyến giữa các AS khác       |

<br>

### Route Types
<br>

| Loại Route            | Mô tả                |
| :-------------------- | :------------------- |
| Intra-area route      | Routes trong 1 area  |
| Inter-area route      | Routes giữa các area |
| Type 1 external route | ..                   |
| Type 2 external route | ..                   |

<br>

### Network Types
<br>

| Network Type                         | When                        | Timers                   | DR/BDR | Multicast/Unicast                     | Nexthop            |
| :----------------------------------- | :-------------------------- | :----------------------- | :----- | :------------------------------------ | :----------------- |
| Broadcast                            | Ethernet                    | Hello: 10s<br>Dead: 40s  | Yes    | Multicast (.5, .6)<br>(auto neighbor) | unchanged          |
| Non-Broadcast                        | FR Multipoint               | Hello: 30s<br>Dead: 120s | Yes    | Unicast<br>(manual neighbor)          | unchanged          |
| Point to Point                       | FR P2P, PPP, HDLC           | Hello: 10s<br>Dead: 40s  | No     | Multicast (.5)<br>(auto neighbor)     | changed (neighbor) |
| Point to Multipoint<br>Broadcast     | FR Multipoint, Partial mesh | Hello: 30s<br>Dead: 120s | No     | Multicast (.5)<br>(auto neighbor)     | changed (neighbor) |
| Point to Multipoint<br>Non-Broadcast | FR Multipoint               | Hello: 30s<br>Dead: 120s | No     | Unicast<br>(manual neighbor)          | changed (neighbor) |

__Compatible Network types:__

_Broadcast_ -- to --  _Broadcast_ <br>
_Non-broadcast_ -- to -- _Non-broadcast_ <br>
_Point-to-Point_ -- to -- _Point-to-Point_ <br>
_Broadcast_ -- to -- _Non-broadcast_ (điều chỉnh lại _hello/dead timers_) <br>
_Point-to-Point_ -- to -- _Point-to-Multipoint_ (điều chỉnh lại _hello/dead timers_)

<br>

## Cấu hình Virtual-Link OSPF

![Alt text](/docs/CCNP/img/ospf-virtual-link.png)

* R1
```conf
enable
conf t
host R1
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
enable
conf t
host R2
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
enable
conf t
host R3
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
enable
conf t
host R4
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
enable
conf t
host R5
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

## Cấu hình Route Summary OSPF

![Alt text](/docs/CCNP/img/ospf-route-summary.png)

* R1
```conf
enable
conf t
host R1
int e0/0
ip add 10.0.12.1 255.255.255.0
ip ospf 1 area 0
no shut
int lo1
ip add 100.0.1.1 255.255.255.0
int lo2
ip add 100.0.2.1 255.255.255.0
router ospf 1
router-id 1.1.1.1
redistribute connected subnets
end
```

* R2
```conf
enable
conf t
host R2
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
enable
conf t
host R3
int e0/1
ip add 10.0.23.3 255.255.255.0
ip ospf 1 area 1
no shut
int lo1
ip add 172.16.1.1 255.255.255.0
ip ospf 1 area 1
ip ospf network point-to-point
int lo2
ip add 172.16.2.1 255.255.255.0
ip ospf 1 area 1
ip ospf network point-to-point
router ospf 1
router-id 3.3.3.3
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

      10.0.0.0/8 is variably subnetted, 3 subnets, 2 masks
O IA     10.0.23.0/24 [110/20] via 10.0.12.2, 00:09:09, Ethernet0/0
      172.16.0.0/24 is subnetted, 2 subnets
O IA     172.16.1.0 [110/21] via 10.0.12.2, 00:02:46, Ethernet0/0
O IA     172.16.2.0 [110/21] via 10.0.12.2, 00:02:46, Ethernet0/0
R1#

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

      10.0.0.0/8 is variably subnetted, 3 subnets, 2 masks
O IA     10.0.12.0/24 [110/20] via 10.0.23.2, 00:09:18, Ethernet0/1
      100.0.0.0/24 is subnetted, 2 subnets
O E2     100.0.1.0 [110/20] via 10.0.23.2, 00:03:06, Ethernet0/1
O E2     100.0.2.0 [110/20] via 10.0.23.2, 00:03:06, Ethernet0/1
R3#
```

* R1 (ASBR)
```conf
conf t
router ospf 1
summary-address 100.0.0.0 255.255.252.0
end
```

* R2 (ABR)
```conf
conf t
router ospf 1
area 1 range 172.16.0.0 255.255.252.0
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

      10.0.0.0/8 is variably subnetted, 3 subnets, 2 masks
O IA     10.0.23.0/24 [110/20] via 10.0.12.2, 00:17:21, Ethernet0/0
      100.0.0.0/8 is variably subnetted, 5 subnets, 3 masks
O        100.0.0.0/22 is a summary, 00:00:38, Null0
      172.16.0.0/22 is subnetted, 1 subnets
O IA     172.16.0.0 [110/21] via 10.0.12.2, 00:03:02, Ethernet0/0
R1#

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

      10.0.0.0/8 is variably subnetted, 3 subnets, 2 masks
O IA     10.0.12.0/24 [110/20] via 10.0.23.2, 00:17:31, Ethernet0/1
      100.0.0.0/22 is subnetted, 1 subnets
O E2     100.0.0.0 [110/20] via 10.0.23.2, 00:00:49, Ethernet0/1
R3#
```