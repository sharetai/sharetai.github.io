---
layout: default
title: Multicast
nav_order: 90
parent: CCNP
---

# Multicast
{: .no_toc }

Truyền thông từ một điểm đến một tập hợp các điểm
{: .fs-6 .fw-300 }

---

## Table of contents
{: .no_toc .text-delta }

1. TOC
{:toc}

---

## [\<Cheat sheet\>](/docs/CCNP/img/MULTICAST.png)
<br>

## Tại sao là Multicast? (why?)
<br>
Sẽ thế nào nếu gửi dữ liệu từ 1 nguồn đến nhiều đích?

<image src="/docs/CCNP/img/multicast-send-by-unicast.png" width="70%"/>

Gửi bằng __Unicast__. Bao nhiêu phiên là đủ? Bao nhiêu băng thông là đủ? <br>
1 router hoặc 1 thiết bị L3 sẽ chuyển các gói tin bằng cách tìm địa chỉ đích trong bảng định tuyến. Nếu 1 thiết bị là L2, nó chỉ cần dựa vào địa chỉ MAC.

<image src="/docs/CCNP/img/multicast-send-by-broadcast.png" width="70%"/>

Gửi bằng __Broadcast__. Hiệu quả kém. Lãng phí. <br>
Địa chỉ đích có thể là địa chỉ tất cả các máy trạm (255.255.255.255) hoặc là 1 phần của địa chỉ mạng con. 1 router hoặc 1 switch L3 sẽ không cho phép chuyển các dữ liệu Broadcast này _(cần cấu hình `ip directed-broadcast`)_. 1 thiết bị switch L2 sẽ cho phép phát tán lưu lượng Broadcast ra tất cả các cổng của nó.

Gửi bằng __Multicast__. 1 nguồn chỉ gửi dữ liệu đến 1 nhóm các máy tính có nhu cầu.

__Có 3 yêu cầu cho Multicast:__ <br>
__\- Phải có một tập hợp các địa chỉ dành cho các nhóm Multicast.__ <br>
__\- Phải có một cơ chế để các máy tính có thể tham gia hay rời khỏi nhóm.__ <br>
__\- Phải có một giao thức định tuyến cho phép các router phân phối các lưu lượng Multicast tới các thành viên của nhóm.__ <br>

<br>

## Một số khái niệm của Multicast? (what?)
<br>

### Địa chỉ Multicast
<br>
Địa chỉ ___Multicast___ là 1 loại địa chỉ IP đặc biệt được sử dụng để truyền dữ liệu đến 1 nhóm các máy tính cùng 1 lúc trên mạng. Thay vì gửi từng gói tin đến từng máy tính riêng lẻ (như trong giao tiếp Unicast), gói tin Multicast chỉ được gửi 1 lần đến địa chỉ nhóm, và tất cả các máy tính thuộc nhóm đó sẽ nhận được gói tin này.

1 gói tin mang lưu lượng cho 1 ứng dụng Multicast sẽ có địa chỉ ___ip nguồn là Unicast___ và địa chỉ ___ip đích là Multicast___. 1 địa chỉ Multicast sẽ không bao giờ được gán đến 1 thiết bị mạng. Địa chỉ Multicast là địa chỉ ___lớp D 224.0.0.0 - 239.255.255.255___, 4 bit bên trái luôn là ___1110___.

Địa chỉ mac cho gói tin Multicast thường sẽ được tạo tự động. Không có cơ chế ARP, địa chỉ mac multicast sẽ được chuyển đổi từ địa chỉ ip multicast. ___24 bit đầu luôn là 01-00-5e, bit 25 sẽ là 0 và 23 bit cuối sẽ là 23 bit cuối của địa chỉ ip___. _Do sẽ có 5 bit của địa chỉ ip bị bỏ qua, nên sẽ có 2^5 là 32 địa chỉ ip multicast chuyển đổi sang cùng 1 địa chỉ mac multicast._

Multicast là ___UDP___.

![alt text](/docs/CCNP/img/multicast-mac.png)

__Một số không gian địa chỉ được dành riêng:__ <br>
__\- Local Network Control Block (224.0.0.0/24)__ được dùng bởi các giao thức định tuyến. <br>
__\- Internetwork Control Block (224.0.1.0/24)__ có thể được định tuyến trên Internet, vì yêu cầu phải là duy nhất. <br>
__\- Source Specific Multicast (SSM) Block (232.0.0.0/8)__. <br>
__\- GLOP Block (233.0.0.0/8)__. <br>
__\- Administratively Scoped Block (239.0.0.0/8)__ được tự do dùng trong vùng mạng nội bộ riêng. <br>

| Description                                                                        | Multicast Addresses |
| :--------------------------------------------------------------------------------: | :-----------------: |
| All Hosts in This Subnet (All-Hosts Group)                                         | 224.0.0.1           |
| All Routers in This Subnet                                                         | 224.0.0.2           |
| All OSPF Routers (AllSPFRouters)                                                   | 224.0.0.5           |
| All OSPF DRs (AllDRouters)                                                         | 224.0.0.6           |
| All RIPv2 Routers                                                                  | 224.0.0.9           |
| All EIGRP Routers                                                                  | 224.0.0.10          |
| All PIM Routers                                                                    | 224.0.0.13          |
| Virtual Router Redundancy Protocol (VRRP)                                          | 224.0.0.18          |
| Internet Group Management Protocol v3 (IGMPv3)                                     | 224.0.0.22          |
| Hot Standby Router Protocol v2 (HSRPv2) and Gateway Load Balancing Protocol (GLBP) | 224.0.0.102         |
| Network Time Protocol (NTP)                                                        | 224.0.0.102         |
| Cisco-RP-Announce (Auto-RP)                                                        | 224.0.1.39          |
| Cisco-RP-Discovery (Auto-RP)                                                       | 224.0.1.40          |

### IGMP (Internet Group Management Protocol)
<br>
___IGMP___ (Internet Group Management Protocol) là 1 giao thức mạng được sử dụng để quản lý việc tham gia và rời khỏi các nhóm Multicast. Nó cho phép các máy tính trên 1 mạng LAN thông báo cho router về việc chúng muốn tham gia hoặc rời khỏi 1 nhóm Multicast cụ thể.

IGMP phát triển đến hiện tại có 3 phiên bản ___IGMPv1 IGMPv2 IGMPv3___. Điểm chung là các thông điệp IGMP sẽ có trường ___TTL là 1___, các gói IGMP chỉ được truyền trong LAN và không được phép chuyển tiếp sang vùng mạng khác. 1 máy tính muốn tham gia 1 nhóm Multicast sẽ gửi 1 thông điệp IGMP "Join" đến router, thông điệp này chứa địa chỉ nhóm Multicast mà máy tính muốn tham gia. ___Mỗi 60 giây___, router Multicast sẽ gửi truy vấn (___query___) đến tất cả các port cấu hình Multicast để kiểm tra mỗi phân đoạn mạng có còn quan tâm nhận lưu lượng của các nhóm Multicast nữa không, nếu không sẽ huỷ cho từng nhóm. Router sẽ truy vấn 3 lần trước khi huỷ, thời gian huỷ nhóm sẽ là ___3 phút___. Router gửi truy vấn gọi là ___Querier___.

__* IGMPv1__ <br>
Sử dụng 2 thông điệp:

\- __Membership report:__ sử dụng để máy tính thông báo sẽ tham gia 1 nhóm Multicast đến router gần nhất. <br>
\- __Membership query:__ sử dụng để router gửi truy vấn huỷ nhóm nếu máy tính không phản hồi sau 3 lần truy vấn mỗi 60 giây. Mỗi khi router nhận được report sẽ gửi ra 1 lần query. <br>

__* IGMPv2__ <br>
Có sự cải tiến hơn phiên bản 1, nổi bật là cơ chế mới cho phép máy tính chủ động gửi "leave":

\- __Leave group message:__ sử dụng để máy tính chủ động gửi thông báo rời nhóm. Router nhận được leave sẽ ngay lập tức gửi ra query. <br>
\- __Group specific Query:__ cho phép router gửi truy vấn cho 1 nhóm cụ thể thay vì cho tất cả các nhóm. <br>
\- __Maximum response Time:__ 1 trường mới trong gói tin truy vấn, cho phép hiệu chỉnh khoảng thời gian cho thông điệp báo cáo. <br>
\- __Querier election process:__ nếu có 2 router Multicast trên cùng phân đoạn mạng, sẽ bầu chọn router có ip thấp hơn làm Querier. <br>

__* IGMPv3__ <br>
Bổ sung thêm cơ chế "source filtering" để kiểm tra nguồn gửi Multicast. Lợi ích khi có thể ngăn chặn tấn công từ 1 nguồn Multicast xấu muốn gửi ra thông điệp không mong muốn. 

<br>

### PIM (Protocol Independent Multicast)
<br>
___PIM___ (Protocol-Independent Multicast) được sử dụng bởi các router mà nó chuyển các dữ liệu multicast. PIM hoạt động độc lập với các giao thức định tuyến khác (EIGRP hoặc OSPF) chạy trong mạng. PIM sử dụng bảng định tuyến bình thường, được thêm vào bởi giao thức định tuyến unicast (EIGRP, OSPF, RIPv2…), trong các giao thức định tuyến multicast của nó. Không giống như các giao thức định tuyến khác, không có các cập nhật định tuyến giữa các router. Khi router chuyển dữ liệu unicast nó sẽ nhìn vào địa chỉ đích trong bảng định tuyến để chuyển gói tin ra ngoài cổng phù hợp.

Tuy nhiên, khi router gửi các dữ liệu multicast, router có lẽ phải chuyển các gói tin ra nhiều cổng, hướng về tất cả các host nhận. Các router cho phép multicast sử dụng PIM tạo tự động các cây phân phối mà nó điều khiển đường đi của lưu lượng IP multicast thông qua mạng để cung cấp lưu lượng truy cập cho tất cả thiết bị nhận. Có hai loại cây phân phối:

o __Source tree__ (cây nguồn): 1 source tree được tạo ra cho mỗi nhóm multicast, source tree có 1 gốc tại nơi gửi và các nhánh xuyên qua mạng đến các thiết bị nhận.

o __Shared tree__ (cây chia sẻ): là 1 cây duy nhất mà nó được chia sẽ giữa các source tree. Shared tree có 1 gốc chung duy nhất được gọi là Rendezvous Point (RP).

PIM hoạt động 1 trong 2 chế độ sau:

o __Dense mode__: mô hình này nó sẽ tràn lưu lượng multicast đến toàn bộ mạng. Mô hình sử dụng các Source tree, các router không cần thiết cho các dữ liệu yêu cầu mà các cây được tỉa bớt bớt vì vậy router không còn nhận dữ liệu nữa.

o __Sparse mode__: sử dụng Shared tree, do đó phải xác định được RP. Các nguồn đăng ký với RP, các router dọc đường đi đến các thiết bị đã đăng ký nhận gói tín tham gia vào nhóm multicast. Router sẽ tính toán, sử dụng giao thức định tuyến unicast, các router có metric tốt hơn đến RP hoặc đến các nguồn của nó, các router sẽ chuyển thông điệp tham gia đến thiết bị với metric tốt hơn. (metric số router mà gói tin phải đi qua).

Bổ sung thêm __Reverse Path Forwarding (RPF)__ là một cơ chế bảo mật mạng được sử dụng để ngăn chặn các cuộc tấn công giả mạo địa chỉ IP (IP spoofing). Nó hoạt động bằng cách kiểm tra xem đường đi ngược lại của một gói tin có khớp với đường đi mà router đã học được hay không. Nếu không khớp, gói tin sẽ bị loại bỏ.

<br>

### IGMP snooping và CGMP
<br>
Không chỉ router cần phải biết cổng LAN nào để chuyển lưu lượng Multicast mà switch cũng cần phải biết những cổng nào cần nó chuyển lưu lượng đi. Mặc định, nếu một switch nhận được khung tin Multicast trên một cổng, switch sẽ phát tán khung tin trên toàn Vlan giống như Broadcast. Lý do là các switch sẽ không bao giờ tìm ra địa chỉ MAC Multicast như là một địa chỉ nguồn. Quyết định của một switch phát tán các khung tin Multicast có nghĩa là nếu có bất kỳ máy trạm nào trong cùng Vlan, cho dù máy trạm đó có yêu cầu nhận khung tin Multicast hay không, cũng sẽ nhận được lưu lượng Multicast.

Yêu cầu 1 cơ chế để Switch biết được cổng nào cần chuyển lưu lượng Multicast.

#### IGMP snooping <br>
Switch sẽ lắng nghe các thông điệp IGMP giao tiếp giữa máy tính và router để xác định cổng tham gia nhóm hay huỷ nhóm. Nhược điểm là tốn tài nguyên CPU.

#### CGMP (Cisco Group Management Protocol) <br>
Switch sẽ hỏi trực tiếp Router những máy tính nào đã gửi tham gia nhóm hay huỷ nhóm. Yêu cầu Switch và Router phải cùng là vendor Cisco.

<br>

## LAB
<br>
![Alt text](/docs/CCNP/img/multicast-0.png)

<h3> OSPF </h3>

* R1
```conf
enable
conf t
!
host R1
!
interface Loopback0
 ip address 1.1.1.1 255.255.255.255
!
interface Ethernet0/0
 no shut
 ip address 10.0.12.1 255.255.255.0
!
interface Ethernet0/1
 no shut
 ip address 10.0.13.1 255.255.255.0
!
router ospf 1
 router-id 1.1.1.1
 network 0.0.0.0 255.255.255.255 area 0
!
end
```

* R2
```conf
enable
conf t
!
host R2
!
interface Loopback0
 ip address 2.2.2.2 255.255.255.255
!
interface Ethernet0/0
 no shut
 ip address 10.0.23.2 255.255.255.0
!
interface Ethernet0/1
 no shut
 ip address 10.0.12.2 255.255.255.0
!
router ospf 1
 router-id 2.2.2.2
 network 0.0.0.0 255.255.255.255 area 0
!
end
```

* R3
```conf
enable
conf t
!
host R3
!
interface Loopback0
 ip address 3.3.3.3 255.255.255.255
!
interface Ethernet0/0
 no shut
 ip address 10.0.13.3 255.255.255.0
!
interface Ethernet0/1
 no shut
 ip address 10.0.23.3 255.255.255.0
!
interface Ethernet0/2
 no shut
 ip address 10.0.34.3 255.255.255.0
!
router ospf 1
 router-id 3.3.3.3
 network 0.0.0.0 255.255.255.255 area 0
!
end
```

* R4
```conf
enable
conf t
!
host R4
!
interface Loopback0
 ip address 4.4.4.4 255.255.255.255
!
interface Ethernet0/0
 no shut
 ip address 10.0.34.4 255.255.255.0
!
interface Ethernet0/1
 no shut
 ip address 10.0.40.1 255.255.255.0
!
router ospf 1
 router-id 4.4.4.4
 network 4.4.4.4 0.0.0.0 area 0
 network 10.0.34.4 0.0.0.0 area 0
!
end
```

Verify

```conf
R1#ping 4.4.4.4
Type escape sequence to abort.
Sending 5, 100-byte ICMP Echos to 4.4.4.4, timeout is 2 seconds:
!!!!!
Success rate is 100 percent (5/5), round-trip min/avg/max = 1/1/1 ms
R1#
```

### IGMP join-group

* R4
```conf
enable
conf t
!
interface Ethernet0/1
 ip igmp join-group 224.6.6.6
!
end
```

### PIM Dense-mode

* R1/2/3/4
```conf
enable
conf t
!
ip multicast-routing
!
int range e0/0-2
ip pim dense-mode
!
end
```

Verify

```
R1#ping 224.6.6.6
Type escape sequence to abort.
Sending 1, 100-byte ICMP Echos to 224.6.6.6, timeout is 2 seconds:

Reply to request 0 from 10.0.40.1, 32 ms
Reply to request 0 from 10.0.40.1, 33 ms
R1#show ip mroute
IP Multicast Routing Table
Flags: D - Dense, S - Sparse, B - Bidir Group, s - SSM Group, C - Connected,
       L - Local, P - Pruned, R - RP-bit set, F - Register flag,
       T - SPT-bit set, J - Join SPT, M - MSDP created entry, E - Extranet,
       X - Proxy Join Timer Running, A - Candidate for MSDP Advertisement,
       U - URD, I - Received Source Specific Host Report,
       Z - Multicast Tunnel, z - MDT-data group sender,
       Y - Joined MDT-data group, y - Sending to MDT-data group,
       G - Received BGP C-Mroute, g - Sent BGP C-Mroute,
       N - Received BGP Shared-Tree Prune, n - BGP C-Mroute suppressed,
       Q - Received BGP S-A Route, q - Sent BGP S-A Route,
       V - RD & Vector, v - Vector, p - PIM Joins on route,
       x - VxLAN group
Outgoing interface flags: H - Hardware switched, A - Assert winner, p - PIM Join
 Timers: Uptime/Expires
 Interface state: Interface, Next-Hop or VCD, State/Mode

(*, 224.6.6.6), 00:00:39/stopped, RP 0.0.0.0, flags: D
  Incoming interface: Null, RPF nbr 0.0.0.0
  Outgoing interface list:
    Ethernet0/1, Forward/Dense, 00:00:39/stopped
    Ethernet0/0, Forward/Dense, 00:00:39/stopped

(10.0.13.1, 224.6.6.6), 00:00:39/00:02:20, flags: PT
  Incoming interface: Ethernet0/1, RPF nbr 0.0.0.0
  Outgoing interface list:
    Ethernet0/0, Prune/Dense, 00:00:39/00:02:20, A

(10.0.12.1, 224.6.6.6), 00:00:39/00:02:20, flags: PT
  Incoming interface: Ethernet0/0, RPF nbr 0.0.0.0
  Outgoing interface list:
    Ethernet0/1, Prune/Dense, 00:00:39/00:02:20, A

(*, 224.0.1.40), 00:12:37/00:02:46, RP 0.0.0.0, flags: DCL
  Incoming interface: Null, RPF nbr 0.0.0.0
  Outgoing interface list:
    Ethernet0/1, Forward/Dense, 00:12:37/stopped
    Ethernet0/0, Forward/Dense, 00:12:37/stopped

R1#
```

### PIM Sparse-mode

* R1/2/3/4
```conf
enable
conf t
!
ip multicast-routing
!
int range lo0
ip pim sparse-mode
!
int range e0/0-2
ip pim sparse-mode
!
end
```

Verify (Ping sẽ không thông do sparse-mode yêu cầu phải có RP)

```
R1#ping 224.6.6.6
Type escape sequence to abort.
Sending 1, 100-byte ICMP Echos to 224.6.6.6, timeout is 2 seconds:
.
R1#
```

#### PIM Static RP

* R1/2/3/4
```conf
enable
conf t
!
ip pim rp-address 2.2.2.2
!
end
```

Verify

```
R1#ping 224.6.6.6
Type escape sequence to abort.
Sending 1, 100-byte ICMP Echos to 224.6.6.6, timeout is 2 seconds:

Reply to request 0 from 10.0.40.1, 1 ms
Reply to request 0 from 10.0.40.1, 1 ms
R1#show ip mroute
IP Multicast Routing Table
Flags: D - Dense, S - Sparse, B - Bidir Group, s - SSM Group, C - Connected,
       L - Local, P - Pruned, R - RP-bit set, F - Register flag,
       T - SPT-bit set, J - Join SPT, M - MSDP created entry, E - Extranet,
       X - Proxy Join Timer Running, A - Candidate for MSDP Advertisement,
       U - URD, I - Received Source Specific Host Report,
       Z - Multicast Tunnel, z - MDT-data group sender,
       Y - Joined MDT-data group, y - Sending to MDT-data group,
       G - Received BGP C-Mroute, g - Sent BGP C-Mroute,
       N - Received BGP Shared-Tree Prune, n - BGP C-Mroute suppressed,
       Q - Received BGP S-A Route, q - Sent BGP S-A Route,
       V - RD & Vector, v - Vector, p - PIM Joins on route,
       x - VxLAN group
Outgoing interface flags: H - Hardware switched, A - Assert winner, p - PIM Join
 Timers: Uptime/Expires
 Interface state: Interface, Next-Hop or VCD, State/Mode

(*, 224.6.6.6), 00:01:20/stopped, RP 2.2.2.2, flags: SP
  Incoming interface: Ethernet0/0, RPF nbr 10.0.12.2
  Outgoing interface list: Null

(10.0.12.1, 224.6.6.6), 00:01:18/00:01:58, flags: PT
  Incoming interface: Ethernet0/0, RPF nbr 0.0.0.0
  Outgoing interface list: Null

(10.0.13.1, 224.6.6.6), 00:01:20/00:01:58, flags: PT
  Incoming interface: Ethernet0/1, RPF nbr 0.0.0.0
  Outgoing interface list: Null

(*, 224.0.1.40), 00:05:28/00:02:36, RP 2.2.2.2, flags: SJPL
  Incoming interface: Ethernet0/0, RPF nbr 10.0.12.2
  Outgoing interface list: Null

R1#show ip pim rp mapping
PIM Group-to-RP Mappings

Group(s): 224.0.0.0/4, Static
    RP: 2.2.2.2 (?)
R1#
```

#### PIM Auto RP

![Alt text](/docs/CCNP/img/multicast-2.png)

* R1 (RP candidate - Ứng viên sẽ làm RP)
```conf
enable
conf t
!
ip pim send-rp-announce lo0 scope 5
!
end
```

* R2 (Mapping Agent)
```conf
enable
conf t
!
ip pim send-rp-discovery lo0 scope 5
!
end
```

* R3 (RP candidate - Ứng viên sẽ làm RP)
```conf
enable
conf t
!
ip pim send-rp-announce lo0 scope 5
ip pim autorp listener
!
end
```

Verify

```
R1#ping 224.6.6.6
Type escape sequence to abort.
Sending 1, 100-byte ICMP Echos to 224.6.6.6, timeout is 2 seconds:

Reply to request 0 from 10.0.40.1, 15 ms
Reply to request 0 from 10.0.40.1, 35 ms
Reply to request 0 from 10.0.40.1, 35 ms
R1#show ip pim rp mapping
PIM Group-to-RP Mappings
This system is an RP (Auto-RP)

Group(s) 224.0.0.0/4
  RP 3.3.3.3 (?), v2v1
    Info source: 2.2.2.2 (?), elected via Auto-RP
         Uptime: 00:04:45, expires: 00:02:12
R1#

R2#show ip pim rp mapping
PIM Group-to-RP Mappings
This system is an RP-mapping agent (Loopback0)

Group(s) 224.0.0.0/4
  RP 3.3.3.3 (?), v2v1
    Info source: 3.3.3.3 (?), elected via Auto-RP
         Uptime: 00:02:40, expires: 00:02:15
  RP 1.1.1.1 (?), v2v1
    Info source: 1.1.1.1 (?), via Auto-RP
         Uptime: 00:03:15, expires: 00:02:43
R2#
```

#### PIM BSR

![Alt text](/docs/CCNP/img/multicast-3.png)

* R1 (RP candidate - Ứng viên sẽ làm RP)
```conf
enable
conf t
!
ip pim rp-candidate lo0
!
end
```

* R2 (BSR - Thiết bị sẽ chọn RP)
```conf
enable
conf t
!
ip pim bsr-candidate lo0
!
end
```

* R3 (RP candidate - Ứng viên sẽ làm RP)
```conf
enable
conf t
!
ip pim rp-candidate lo0
!
end
```

Verify

```
R1#show ip pim bsr-router
PIMv2 Bootstrap information
  BSR address: 2.2.2.2 (?)
  Uptime:      00:01:00, BSR Priority: 0, Hash mask length: 0
  Expires:     00:01:13
  Candidate RP: 1.1.1.1(Loopback0)
    Holdtime 150 seconds
    Advertisement interval 60 seconds
    Next advertisement in 00:00:50
R1#show ip pim rp-hash 224.6.6.6
  RP 3.3.3.3 (?), v2
    Info source: 2.2.2.2 (?), via bootstrap, priority 0, holdtime 150
         Uptime: 00:01:07, expires: 00:02:17
  PIMv2 Hash Value (mask 0.0.0.0)
    RP 3.3.3.3, via bootstrap, priority 0, hash value 450145259
    RP 1.1.1.1, via bootstrap, priority 0, hash value 332477713
R1#show ip pim rp mapping
PIM Group-to-RP Mappings
This system is a candidate RP (v2)

Group(s) 224.0.0.0/4
  RP 3.3.3.3 (?), v2
    Info source: 2.2.2.2 (?), via bootstrap, priority 0, holdtime 150
         Uptime: 00:01:27, expires: 00:01:58
  RP 1.1.1.1 (?), v2
    Info source: 2.2.2.2 (?), via bootstrap, priority 0, holdtime 150
         Uptime: 00:01:49, expires: 00:01:38
R1#ping 224.6.6.6
Type escape sequence to abort.
Sending 1, 100-byte ICMP Echos to 224.6.6.6, timeout is 2 seconds:

Reply to request 0 from 10.0.40.1, 21 ms
Reply to request 0 from 10.0.40.1, 47 ms
Reply to request 0 from 10.0.40.1, 47 ms
R1#
R1#show ip pim bsr-router
PIMv2 Bootstrap information
  BSR address: 2.2.2.2 (?)
  Uptime:      00:01:00, BSR Priority: 0, Hash mask length: 0
  Expires:     00:01:13
  Candidate RP: 1.1.1.1(Loopback0)
    Holdtime 150 seconds
    Advertisement interval 60 seconds
    Next advertisement in 00:00:50
R1#show ip pim rp-hash 224.6.6.6
  RP 3.3.3.3 (?), v2
    Info source: 2.2.2.2 (?), via bootstrap, priority 0, holdtime 150
         Uptime: 00:01:07, expires: 00:02:17
  PIMv2 Hash Value (mask 0.0.0.0)
    RP 3.3.3.3, via bootstrap, priority 0, hash value 450145259
    RP 1.1.1.1, via bootstrap, priority 0, hash value 332477713
R1#show ip pim rp mapping
PIM Group-to-RP Mappings
This system is a candidate RP (v2)

Group(s) 224.0.0.0/4
  RP 3.3.3.3 (?), v2
    Info source: 2.2.2.2 (?), via bootstrap, priority 0, holdtime 150
         Uptime: 00:01:27, expires: 00:01:58
  RP 1.1.1.1 (?), v2
    Info source: 2.2.2.2 (?), via bootstrap, priority 0, holdtime 150
         Uptime: 00:01:49, expires: 00:01:38
R1#ping 224.6.6.6
Type escape sequence to abort.
Sending 1, 100-byte ICMP Echos to 224.6.6.6, timeout is 2 seconds:

Reply to request 0 from 10.0.40.1, 21 ms
Reply to request 0 from 10.0.40.1, 47 ms
Reply to request 0 from 10.0.40.1, 47 ms
R1#
```

<br>

