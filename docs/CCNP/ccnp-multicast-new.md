---
layout: default
title: Multicast (new)
nav_order: 90.1
parent: CCNP
---

# Multicast (new)
{: .no_toc }

Truyền thông từ một điểm đến một tập hợp các điểm
{: .fs-6 .fw-300 }

---

## Table of contents
{: .no_toc .text-delta }

1. TOC
{:toc}

---

# [\<Cheat sheet\>](/docs/CCNP/img/MULTICAST.png)

# Giới thiệu

## Tại sao là Multicast? (why?)
<br>
Ý tưởng là 1 source chỉ gửi 1 lần, router sao chép và gửi chỉ đến subnet có host cần nhận.

Nếu source gửi unicast đến từng host → tốn tài nguyên server, ảnh hưởng băng thông.

<img style="max-width: 510px" src="/docs/CCNP/img/multicast-Replicated Unicast Example.png" />
<img style="max-width: 580px" src="/docs/CCNP/img/multicast-Multicast Example.png" />

Hình trái: Server tạo luồng unicast đến từng host. Hình phải: Router/Switch sao chép & gửi multicast đến host cần nhận.

## Khó khăn của Multicast
<br>
- Sử dụng __UDP__; vì TCP không hợp lý khi server phải keep trạng thái cho từng receiver và nhận TCP control messages (ví dụ: ACK). UDP dẫn đến lưu lượng multicast là không tin cậy, thường dùng cho audio/video.
- Cần địa chỉ dành riêng cho các nhóm multicast.
- Cần cơ chế tham gia/rời nhóm: dùng __IGMP__. Switch cần hỗ trợ __IGMP snooping__ (thường mặc định); nếu không, mọi host trong VLAN đều nhận multicast.
- Cần giao thức định tuyến để phân phối multicast tới thành viên nhóm: dùng __PIM__.

# IP và MAC

## IP
<br>
Toàn bộ không gian địa chỉ __Class D (224.0.0.0/4)__ là dành cho multicast. 1 IP là 1 multicast group. Dải __239.0.0.0/8__ là __private__.

Chia nhóm Multicast IP:

- **Link-local (224.0.0.0/24):** Dùng cho giao thức chỉ hoạt động trên 1 network segment (như trên 1 link, TTL=1 để không nhảy sang link khác). Ví dụ:  
  - All Hosts: 224.0.0.1  
  - All Multicast Routers: 224.0.0.2  
  - All OSPF Routers: 224.0.0.5  
  - OSPF DR Routers: 224.0.0.6  
  - EIGRP Routers: 224.0.0.10  
  - VRRP: 224.0.0.18  
- **Network protocols/applications (224.0.1.0/24):** Có thể chuyển tiếp ngoài phạm vi link (ví dụ: NTP 224.0.1.1, Cisco-RP-Announce 224.0.1.39, Cisco-RP-Discovery 224.0.1.40).  
- **Source-Specific Multicast (232.0.0.0/8):** Receiver chọn nguồn multicast cần nhận.  
- **GLOP (233.0.0.0/8):** Thử nghiệm, dùng ASN làm phần của địa chỉ, hạn chế do không hỗ trợ 32-bit ASN và chỉ 256 group.  
- **Administratively scoped (239.0.0.0/8):** Tương tự RFC1918 cho unicast (ip private), dùng trong domain riêng.

## MAC
<br>
Multicast IP phải được ánh xạ sang MAC address, do không có 1 host nào "sở hữu" Multicast IP để trả lời ARP. Multicast không phải broadcast nên không thể dùng MAC FFFF.FFFF.FFFF, chỉ host quan tâm mới nhận traffic.

Giải pháp: định nghĩa prefix multicast MAC 25-bit là __0100.5eXX.XXXX__, trong đó hex thứ 7 là 0-7. Do đó, các MAC dùng cho multicast nằm trong khoảng 0100.5E00.0000 đến 0100.5e7f.ffff.

MAC address dài 48 bit, nên có 48 - 25 = 23 bit dùng để ánh xạ multicast IP. Vì multicast IP có 28 bit (32 - 4) là duy nhất (do multicast range là 224.0.0.0/4), nên 5 bit đầu không ánh xạ, dẫn đến 2^5 (32) multicast IP có cùng MAC address.

Ví dụ: multicast IP 239.101.1.23 ánh xạ sang MAC 0100.5e65.0117.

<img style="max-width: 600px" src="/docs/CCNP/img/multicast-Multicast MAC.png" />

<h3>Mapping kiểu này có vấn đề không? (đọc thêm, có thể bỏ qua)</h3>

- Thực tế, nếu host đăng ký nhận multicast từ 239.101.1.23, có thể nhận traffic của 31 multicast IP khác chia sẻ cùng MAC, nhưng host sẽ drop packet nếu IP header không khớp.

<h3>1 Lưu ý về broadcast/multicast bit (đọc thêm, có thể bỏ qua)</h3>
<img style="max-width: 500px" src="/docs/CCNP/img/multicast-broadcast multicast bit.png" />

- MAC address 0100.5exx.xxxx có bit thứ 8 là 1, biểu thị frame là broadcast hoặc multicast.
- Unicast MAC phải có bit này là 0, giúp switch phân biệt unicast và broadcast/multicast.
- Nếu switch không thực hiện multicast snooping, multicast frame sẽ được coi như broadcast và chuyển tiếp ra tất cả port trong VLAN.

# Tree Form và Packet Forwarding

## Source Tree (SPT)
<img style="max-width: 560px" src="/docs/CCNP/img/multicast-Source Tree (SPT).png" />
- Root là __source__ (ví dụ: 10.1.1.1).
- Ký hiệu: __(S, G)__. S là Source, G là Group. Ví dụ (10.1.1.1, 239.1.1.1).
- Được gọi là __Shortest Path Tree__ vì traffic đi theo đường ngắn nhất (theo reverse path).
- __PIM-DM__ sử dụng source tree.

## Shared Tree (RP Tree)
<img style="max-width: 560px" src="/docs/CCNP/img/multicast-Shared Tree (RP Tree).png" />
- Root là __Rendezvous Point (RP)__.
- Ký hiệu: __(\*, G)__; mọi source đều gửi về RP trước. Ví dụ có 2 source 10.1.1.1 và 10.1.2.1, cả 2 multicast flows xem là 1 single tree (\*, 239.1.1.1).
- Mặc dù không phải đường ngắn nhất, nhưng rule bắt buộc traffic phải đi qua RP (__ASM - any source multicast__).
- __PIM-SM__ sử dụng shared tree và source tree.

## Reverse Path Forwarding Check

- Router sử dụng __RPF Check__ để kiểm tra packet multicast có đến từ interface dùng để gửi unicast về source (hoặc RP) hay không.
- Nếu không, packet bị drop, giúp tránh "multicast storm".
- Mỗi router có 1 __upstream__ interface (hướng về __source/RP__) và nhiều __downstream__ interface (hướng về __receiver__), tập hợp này gọi là OIL (Outgoing Interface List). 1 packet nhận từ upstream sẽ được replicate và forward đến nhiều downstream.

## FHR và LHR 

- __FHR (First Hop Router)__: Router nối trực tiếp với __source__.
- __LHR (Last Hop Router)__: Router nối trực tiếp với __receiver__, chịu trách nhiệm theo dõi receiver thông qua IGMP.

# IGMP

Internet Group Management Protocol (IGMP) dùng để host báo với default router rằng chúng muốn nhận multicast traffic cho 1 multicast group. Nếu không có IGMP, router không biết host nào trên LAN muốn nhận multicast và muốn nhận của multicast group nào.

IGMP là giao thức query/response. Router định kỳ gửi query (mặc định mỗi 60 giây): "Có host nào muốn nhận multicast? Cho biết group address bạn cần." Host trả lời: "Yes, hãy gửi multicast cho group 239.1.1.1".  

Các phiên bản IGMP:
  - IGMPv1: Đã lỗi thời.  
  - IGMPv2: Phiên bản mặc định trên Cisco IOS-XE.  
  - IGMPv3: Hỗ trợ source-specific multicast.

## Lab

<img style="max-width: 300px" src="/docs/CCNP/img/multicast-igmp lab.png" />

_(\*) Cấu hình sẽ thay đổi, tất cả thiết bị sẽ dùng IOL. e0/1 là gi1, e0/2 là gi2, e0/3 là gi3, e0/0 là gi4._

__#Source__
```
enable
conf t
!
hostname Source
!
no ip domain-lookup
!
int e0/1
 ip address 10.1.2.1 255.255.255.0
 no shut
!
ip route 0.0.0.0 0.0.0.0 10.1.2.2
!
end
```

__#R1__
```
enable
conf t
!
hostname R1
!
no ip domain-lookup
!
int e0/1
 ip address 10.1.2.2 255.255.255.0
 no shut
!
int e0/2
 ip address 10.10.10.1 255.255.255.0
 no shut
!
end
```

__#Host1__
```
enable
conf t
!
hostname Host1
!
no ip domain-lookup
!
int e0/0
 ip address 10.10.10.10 255.255.255.0
 no shut
!
ip route 0.0.0.0 0.0.0.0 10.10.10.1
!
end
```

__#Host2__
```
enable
conf t
!
hostname Host2
!
no ip domain-lookup
!
int e0/0
 ip address 10.10.10.20 255.255.255.0
 no shut
!
ip route 0.0.0.0 0.0.0.0 10.10.10.1
!
end
```

Bật IGMP trên R1 bằng cách bật PIM trên upstream e0/1 và downstream e0/2. Lưu ý rằng R1 vừa là FHR và LHR trong topo này. Bật PIM đồng nghĩa với việc bật __IGMPv2__ trên giao diện.

__#R1 (bật PIM và IGMPv2 trên upstream e0/1 và downstream e0/2)__
```
enable
conf t
!
ip multicast-routing distributed
!
int e0/1
 ip pim dense-mode
!
int e0/2
 ip pim dense-mode
!
end
```

R1 sẽ gửi IGMP queries mỗi 60 giây trên cả e0/1 và e0/2. Ta quan tâm tới e0/2 vì đó là nơi có các host. Trường Multicast Address là (0.0.0.0).

![alt text](/docs/CCNP/img/multicast-igmp lab (turn on igmp).png)

Join multicast group 239.1.1.1 cho Host1 và Host2

__#Host1/Host2 (Join multicast group 239.1.1.1)__
```
enable
conf t
!
int e0/0
 ip igmp join-group 239.1.1.1
!
end
```

## Membership report supression

Cơ chế __membership report suppression__ chỉ có 1 host trả lời IGMP query dù có nhiều host đăng ký.

Mỗi host khi nhận IGMP query sẽ chạy timer ngẫu nhiên trong khoảng 0 đến max response time (mặc định 10 giây). Nếu host nào khác đã gửi membership report cho group đó trước khi timer hết, host sẽ hủy report của mình. Điều này giúp tránh việc quá nhiều membership report gây quá tải trên LAN.

![alt text](/docs/CCNP/img/multicast-igmp lab (join group).png)

Host1 (10.10.10.10) hoặc Host2 (10.10.10.2) sẽ phản hồi membership query bằng 1 membership report, nhưng không bao giờ là cả 2. R1 không quan tâm có bao nhiêu host mà chỉ quan tâm ít nhất 1 host trong LAN cần nhận multicast.

## Kiểm tra multicast traffic

- Source gửi traffic cho 239.1.1.1 qua default gateway (FHR là R1).
- R1 nhận traffic và chuyển tiếp ra e0/2 tới switch.
- Switch, không có enable IGMP snooping, sẽ replicate traffic ra tất cả port trong VLAN (trừ port nhận vào).

Ví dụ: khi ping từ Source đến 239.1.1.1, Host1 và Host2 đều trả lời.

```
Source#ping 239.1.1.1
Type escape sequence to abort.
Sending 1, 100-byte ICMP Echos to 239.1.1.1, timeout is 2 seconds:

Reply to request 0 from 10.10.10.20, 1 ms
Reply to request 0 from 10.10.10.10, 1 ms
```

Có thể xem các nhóm IGMP hoạt động hiện tại và giao diện gửi trên R1, dùng __show ip igmp groups__.

```
R1#show ip igmp groups
IGMP Connected Group Membership
Group Address    Interface                Uptime    Expires   Last Reporter   Group Accounted
239.1.1.1        Ethernet0/2              00:35:38  00:02:43  10.10.10.10
224.0.1.40       Ethernet0/1              01:09:19  00:02:44  10.1.2.2
```

## Rời nhóm

Khi Host rời multicast group, nó gửi IGMP Leave Group message. Ví dụ, trên Host2:

```
enable
conf t
!
int e0/0
 no ip igmp join-group 239.1.1.1
!
end
```

![alt text](/docs/CCNP/img/multicast-igmp lab (leave group) 1.png)
![alt text](/docs/CCNP/img/multicast-igmp lab (leave group) 2.png)
![alt text](/docs/CCNP/img/multicast-igmp lab (leave group) 3.png)

R1 nhận Leave và gửi targeted membership query (max response time giảm xuống 1 giây) hỏi: "Có host nào khác vẫn cần nhận không? 1s để trả lời nhé." Nếu Host1 trả lời, R1 tiếp tục chuyển tiếp multicast traffic. Nếu không có host nào phản hồi sau 3 lần general query, R1 ngừng gửi traffic cho group đó.

## Querier Election

- Khi có nhiều router trên LAN (ví dụ dùng VRRP/HSRP), chỉ có 1 router làm IGMP Querier.
- Quy tắc: router có IP thấp nhất trên subnet sẽ trở thành IGMP Querier.
- Mỗi router nhận IGMP general query từ các router khác, so sánh IP; router có IP cao sẽ dừng query, chờ router với IP thấp nhất. Nếu querier không gửi query trong 2 khoảng thời gian (2x60 giây), router khác sẽ tiếp quản.

# PIM

__PIM (Protocol Independent Multicast)__ dùng để xây dựng multicast distribution trees. "Protocol independent" nghĩa là PIM không quan tâm giao thức unicast routing protocol nào được dùng để build unicast routing table (dù là static, connected, OSPF, BGP,…). PIM xác định đường đi tốt nhất qua RPF check.

PIM là Router-to-Router Protocol, không trao đổi route, thay vào đó dùng __Join__ và __Prune__ messages để xây dựng tree cho (\*, G) hoặc (S, G). Neighbor discovery diễn ra qua địa chỉ link-local multicast __224.0.0.13__.

__PIM-SM:__ Khi router nhận IGMP Join từ host, nó gửi PIM Join cho neighbor báo "Tôi có host downstream cần nhận multicast từ group này." 

__PIM-DM__: Source gửi multicast traffic, các router sẽ flood traffic ra tất cả các interface kết nối với PIM neighbor hoặc host. Nếu router không có receiver hay neighbor, nó gửi PIM Prune báo "Không có receiver cần nhận multicast."

## PIM-DM (Dense Mode)

Cơ chế của __PIM-DM__ gọi là __"Flood and Prune"__. Traffic ban đầu được flood khắp mạng, sau đó các router prune back trở lại nếu nó không có receiver hay neighbor. Quá trình này tốn tài nguyên và băng thông, chỉ phù hợp khi có nhiều receiver dày đặt trong mạng.

PIM-DM dùng __source-based trees (SPT – shortest path tree)__.

## PIM-DM Lab

<img style="max-width: 700px" src="/docs/CCNP/img/multicast-PIM-DM Lab 0.png" />

_(\*) Cấu hình sẽ thay đổi, tất cả thiết bị sẽ dùng IOL. e0/1 là gi1, e0/2 là gi2, e0/3 là gi3, e0/0 là gi4._

Các router (Source, R1, R2, R3, R4, R5) và các host được cấu hình với IP và OSPF.

__#Source1__
```
enable
conf t
!
hostname Source1
!
no ip domain-lookup
!
int e0/1
 ip address 10.10.10.10 255.255.255.0
 no shut
!
ip route 0.0.0.0 0.0.0.0 10.10.10.1
!
end
write
```

__#R1__
```
enable
conf t
!
hostname R1
!
no ip domain-lookup
!
int e0/1
 ip address 10.10.10.1 255.255.255.0
 no shut
!
int e0/2
 ip address 10.1.2.1 255.255.255.0 
 no shut
!
int e0/3
 ip address 10.1.5.1 255.255.255.0
 no shut
!
int Lo0
 ip address 1.1.1.1 255.255.255.255
!
router ospf 1
 network 0.0.0.0 255.255.255.255 area 0
!
end
write
```

__#R2__
```
enable
conf t
!
hostname R2
!
no ip domain-lookup
!
int e0/1
 ip address 10.1.2.2 255.255.255.0
 no shut
!
int e0/2
 ip address 10.2.3.2 255.255.255.0 
 no shut
!
int e0/3
 ip address 10.2.4.2 255.255.255.0
 no shut
!
int Lo0
 ip address 2.2.2.2 255.255.255.255
!
router ospf 1
 network 0.0.0.0 255.255.255.255 area 0
!
end
write
```

__#R3__
```
enable
conf t
!
hostname R3
!
no ip domain-lookup
!
int e0/1
 ip address 10.2.3.3 255.255.255.0
 no shut
!
int e0/2
 ip address 10.10.0.1 255.255.255.0 
 no shut
!
int Lo0
 ip address 3.3.3.3 255.255.255.255
!
router ospf 1
 network 0.0.0.0 255.255.255.255 area 0
!
end
write
```

__#R4__
```
enable
conf t
!
hostname R4
!
no ip domain-lookup
!
int e0/1
 ip address 10.2.4.4 255.255.255.0
 no shut
!
int e0/2
 ip address 10.10.100.1 255.255.255.0 
 no shut
!
int Lo0
 ip address 4.4.4.4 255.255.255.255
!
router ospf 1
 network 0.0.0.0 255.255.255.255 area 0
!
end
write
```

__#R5__
```
enable
conf t
!
hostname R5
!
no ip domain-lookup
!
int e0/1
 ip address 10.1.5.5 255.255.255.0
 no shut
!
int e0/2
 ip address 10.10.200.1 255.255.255.0 
 no shut
!
int Lo0
 ip address 5.5.5.5 255.255.255.255
!
router ospf 1
 network 0.0.0.0 255.255.255.255 area 0
!
end
write
```

__#Hosts1__
```
enable
conf t
!
hostname Host1
!
no ip domain-lookup
!
int e0/0
 ip address 10.10.0.10 255.255.255.0
 no shut
!
ip route 0.0.0.0 0.0.0.0 10.10.0.1
!
end
write
```

__#Hosts2__
```
enable
conf t
!
hostname Host2
!
no ip domain-lookup
!
int e0/0
 ip address 10.10.100.10 255.255.255.0
 no shut
!
ip route 0.0.0.0 0.0.0.0 10.10.100.1
!
end
write
```

__#Hosts3__
```
enable
conf t
!
hostname Host3
!
no ip domain-lookup
!
int e0/0
 ip address 10.10.100.20 255.255.255.0
 no shut
!
ip route 0.0.0.0 0.0.0.0 10.10.100.1
!
end
write
```

__#Hosts4__
```
enable
conf t
!
hostname Host4
!
no ip domain-lookup
!
int e0/0
 ip address 10.10.200.10 255.255.255.0
 no shut
!
ip route 0.0.0.0 0.0.0.0 10.10.200.1
!
end
write
```

__#Hosts5__
```
enable
conf t
!
hostname Host5
!
no ip domain-lookup
!
int e0/0
 ip address 10.10.200.20 255.255.255.0
 no shut
!
ip route 0.0.0.0 0.0.0.0 10.10.200.1
!
end
write
```

## PIM-DM Neighborship

Enable PIM-DM trên tất cả các router

```
enable
conf t
!
ip multicast-routing
!
int range e0/1-3
  ip pim dense-mode
!
end
write
```

PIM Neighborship được hình thành qua Hello message mỗi 30 giây (dead interval mặc định 105 giây).

![alt text](/docs/CCNP/img/multicast-PIM-DM Neighborship.png)

Xem trạng thái với __show ip pim neighbor__.

```
R1#show ip pim neighbor
PIM Neighbor Table
Mode: B - Bidir Capable, DR - Designated Router, N - Default DR Priority,
      P - Proxy Capable, S - State Refresh Capable, G - GenID Capable,
      L - DR Load-balancing Capable
Neighbor          Interface                Uptime/Expires    Ver   DR
Address                                                            Prio/Mode
10.1.2.2          Ethernet0/2              00:00:50/00:01:23 v2    1 / DR S P G
10.1.5.5          Ethernet0/3              00:00:44/00:01:30 v2    1 / DR S P G

R2#show ip pim neighbor
PIM Neighbor Table
Mode: B - Bidir Capable, DR - Designated Router, N - Default DR Priority,
      P - Proxy Capable, S - State Refresh Capable, G - GenID Capable,
      L - DR Load-balancing Capable
Neighbor          Interface                Uptime/Expires    Ver   DR
Address                                                            Prio/Mode
10.1.2.1          Ethernet0/1              00:04:28/00:01:41 v2    1 / S P G
10.2.3.3          Ethernet0/2              00:04:25/00:01:15 v2    1 / DR S P G
10.2.4.4          Ethernet0/3              00:04:21/00:01:17 v2    1 / DR S P G

R3#show ip pim neighbor
PIM Neighbor Table
Mode: B - Bidir Capable, DR - Designated Router, N - Default DR Priority,
      P - Proxy Capable, S - State Refresh Capable, G - GenID Capable,
      L - DR Load-balancing Capable
Neighbor          Interface                Uptime/Expires    Ver   DR
Address                                                            Prio/Mode
10.2.3.2          Ethernet0/1              00:00:52/00:01:21 v2    1 / S P G

R4#show ip pim neighbor
PIM Neighbor Table
Mode: B - Bidir Capable, DR - Designated Router, N - Default DR Priority,
      P - Proxy Capable, S - State Refresh Capable, G - GenID Capable,
      L - DR Load-balancing Capable
Neighbor          Interface                Uptime/Expires    Ver   DR
Address                                                            Prio/Mode
10.2.4.2          Ethernet0/1              00:00:57/00:01:15 v2    1 / S P G

R5#show ip pim neighbor
PIM Neighbor Table
Mode: B - Bidir Capable, DR - Designated Router, N - Default DR Priority,
      P - Proxy Capable, S - State Refresh Capable, G - GenID Capable,
      L - DR Load-balancing Capable
Neighbor          Interface                Uptime/Expires    Ver   DR
Address                                                            Prio/Mode
10.1.5.1          Ethernet0/1              00:00:58/00:01:15 v2    1 / S P G
```

## PIM-DM Flood and Prune

__#Host2, Host3 join group 239.1.1.1__

```
enable
conf t
!
int e0/0
  ip igmp join-group 239.1.1.1
!
end
```

Kiểm tra igmp group trên R4.

```
R4#show ip igmp groups
IGMP Connected Group Membership
Group Address    Interface                Uptime    Expires   Last Reporter   Group Accounted
239.1.1.1        Ethernet0/2              00:01:42  00:02:11  10.10.100.10
224.0.1.40       Ethernet0/1              00:03:51  00:02:07  10.2.4.4
```

Chỉ mỗi R4 có entry (\*, 239.1.1.1) trong bảng mroute.

```
R1#show ip mroute | sec \(
(*, 224.0.1.40), 00:11:54/00:02:14, RP 0.0.0.0, flags: DCL
  Incoming interface: Null, RPF nbr 0.0.0.0
  Outgoing interface list:
    Ethernet0/3, Forward/Dense, 00:11:45/stopped
    Ethernet0/2, Forward/Dense, 00:11:51/stopped
    Ethernet0/1, Forward/Dense, 00:11:54/stopped

R4#show ip mroute | sec \(
(*, 239.1.1.1), 00:09:16/00:02:35, RP 0.0.0.0, flags: DC
  Incoming interface: Null, RPF nbr 0.0.0.0
  Outgoing interface list:
    Ethernet0/2, Forward/Dense, 00:09:16/stopped
    Ethernet0/1, Forward/Dense, 00:09:16/stopped
(*, 224.0.1.40), 00:11:26/00:02:38, RP 0.0.0.0, flags: DCL
  Incoming interface: Null, RPF nbr 0.0.0.0
  Outgoing interface list:
    Ethernet0/1, Forward/Dense, 00:11:26/stopped

```

Ping từ Source đến 239.1.1.1

```
Source1#ping 239.1.1.1
Type escape sequence to abort.
Sending 1, 100-byte ICMP Echos to 239.1.1.1, timeout is 2 seconds:

Reply to request 0 from 10.10.100.10, 2 ms
Reply to request 0 from 10.10.100.20, 3 ms
```

Khi Source gửi multicast traffic đến 239.1.1.1, R1 tạo (\*, G) và (S, G) entry. Trong PIM-DM, entry (\*, G) không dùng để forwarding, incoming interface là null, (\*, G) chứa tất cả các outgoing interface. Entry (S, G) được tạo dựa trên (\*, G) như "template".

```
R1#show ip mroute | sec 239
(*, 239.1.1.1), 00:00:46/stopped, RP 0.0.0.0, flags: D
  Incoming interface: Null, RPF nbr 0.0.0.0
  Outgoing interface list:
    Ethernet0/3, Forward/Dense, 00:00:46/stopped
    Ethernet0/2, Forward/Dense, 00:00:46/stopped
(10.10.10.10, 239.1.1.1), 00:00:46/00:02:13, flags: T
  Incoming interface: Ethernet0/1, RPF nbr 0.0.0.0
  Outgoing interface list:
    Ethernet0/2, Forward/Dense, 00:00:46/stopped
    Ethernet0/3, Prune/Dense, 00:00:46/00:02:13
```

R1 thực hiện RPF check và thêm các interface có PIM neighbor vào OIL.

Các router không có receiver (vd: R5, R3) sẽ gửi PIM Prune message để loại bỏ interface khỏi tree.

```
R1#show ip mroute | sec 239
(*, 239.1.1.1), 00:00:46/stopped, RP 0.0.0.0, flags: D
  Incoming interface: Null, RPF nbr 0.0.0.0
  Outgoing interface list:
    Ethernet0/3, Forward/Dense, 00:00:46/stopped
    Ethernet0/2, Forward/Dense, 00:00:46/stopped
(10.10.10.10, 239.1.1.1), 00:00:46/00:02:13, flags: T
  Incoming interface: Ethernet0/1, RPF nbr 0.0.0.0
  Outgoing interface list:
    Ethernet0/2, Forward/Dense, 00:00:46/stopped
    Ethernet0/3, Prune/Dense, 00:00:46/00:02:13

R2#show ip mroute | sec 239
(*, 239.1.1.1), 00:00:10/stopped, RP 0.0.0.0, flags: D
  Incoming interface: Null, RPF nbr 0.0.0.0
  Outgoing interface list:
    Ethernet0/3, Forward/Dense, 00:00:10/stopped
    Ethernet0/2, Forward/Dense, 00:00:10/stopped
    Ethernet0/1, Forward/Dense, 00:00:10/stopped
(10.10.10.10, 239.1.1.1), 00:00:10/00:02:49, flags: T
  Incoming interface: Ethernet0/1, RPF nbr 10.1.2.1
  Outgoing interface list:
    Ethernet0/2, Prune/Dense, 00:00:10/00:02:49
    Ethernet0/3, Forward/Dense, 00:00:10/stopped

R3#show ip mroute | sec 239
(*, 239.1.1.1), 00:00:13/stopped, RP 0.0.0.0, flags: D
  Incoming interface: Null, RPF nbr 0.0.0.0
  Outgoing interface list:
    Ethernet0/1, Forward/Dense, 00:00:13/stopped
(10.10.10.10, 239.1.1.1), 00:00:13/00:02:46, flags: PT
  Incoming interface: Ethernet0/1, RPF nbr 10.2.3.2
  Outgoing interface list: Null

R4#show ip mroute | sec 239
(*, 239.1.1.1), 00:16:55/stopped, RP 0.0.0.0, flags: DC
  Incoming interface: Null, RPF nbr 0.0.0.0
  Outgoing interface list:
    Ethernet0/2, Forward/Dense, 00:16:55/stopped
    Ethernet0/1, Forward/Dense, 00:16:55/stopped
(10.10.10.10, 239.1.1.1), 00:00:19/00:02:40, flags: T
  Incoming interface: Ethernet0/1, RPF nbr 10.2.4.2
  Outgoing interface list:
    Ethernet0/2, Forward/Dense, 00:00:19/stopped

R5#show ip mroute | sec 239
(*, 239.1.1.1), 00:00:24/stopped, RP 0.0.0.0, flags: D
  Incoming interface: Null, RPF nbr 0.0.0.0
  Outgoing interface list:
    Ethernet0/1, Forward/Dense, 00:00:24/stopped
(10.10.10.10, 239.1.1.1), 00:00:24/00:02:34, flags: PT
  Incoming interface: Ethernet0/1, RPF nbr 10.1.5.1
  Outgoing interface list: Null
```

![alt text](/docs/CCNP/img/multicast-PIM-DM Flood and Prune.png)

## PIM-DM Prune state refresh

Trong PIM-DM, trạng thái Forward không bao giờ expire. Trong khi đó, trạng thái Prune expire sau 3 phút. Khi hết thời gian, interface sẽ chuyển về trạng thái Forward. Nghĩa là, cứ mỗi 3 phút, interface sẽ chuyển lại sang Forward, traffic được chuyển tới router, và router sẽ lại phải Prune traffic đó.

## PIM-DM Grafting

__#Host1 join group 239.1.1.1__

```
enable
conf t
!
int e0/0
  ip igmp join-group 239.1.1.1
!
end
```

Khi một receiver mới xuất hiện (qua IGMP) trên router vừa bị Prune, router có thể gửi PIM Graft (unicast PIM Join) đến upstream neighbor để nhanh chóng nối lại với tree, bỏ qua thời gian chờ 3 phút của Prune.

![alt text](/docs/CCNP/img/multicast-PIM-DM Grafting.png)


## PIM-SM (Sparse Mode)

Traffic chỉ được chuyển tiếp khi nhận được PIM Join. Khi LHR nhận __IGMP Join__ từ host, nó gửi __PIM Join__ lên hướng __RP__, tạo __shared tree__ từ __RP__ đến __receiver__.  

__PIM-DM__ là mô hình __"push"__ (dùng __(S, G)__ cho __(sourced-based tree)__); PIM-SM là __"pull"__ (dùng __(\*, G)__ cho __(shared tree)__).

Receiver không quan tâm nguồn gửi, chỉ muốn nhận traffic cho group. Nên điều này gọi là __any source multicast (ASM)__, PIM-SM sử dụng (\*, G) entry, nghĩa là "any source".

__RP (Rendezvous Point)__ là __"meeting point"__ giữa __source__ và __receiver__; LHR dùng địa chỉ RP để xác định upstream interface và xây dựng cây từ RP xuống receiver.

Khi source gửi traffic, FHR __encapsulate__ gói tin trong __PIM Register message__ và unicast nó đến RP, gọi là __Source Registration__.

---

## PIM-SM Lab

Sử dụng topology của PIM-DM với bổ sung:  
- Thêm router R6 làm RP.  
- Thêm một Source2 nối với R3.  
- Các kết nối bổ sung.

<img style="max-width: 700px" src="/docs/CCNP/img/multicast-PIM-SM Lab 0.png" />

_(\*) Cấu hình sẽ thay đổi, tất cả thiết bị sẽ dùng IOL. e0/1 là gi1, e0/2 là gi2, e0/3 là gi3, e0/0 là gi4._

__#R6__
```
enable
conf t
!
hostname R6
!
no ip domain-lookup
!
int e0/1
 ip address 10.1.6.6 255.255.255.0
 no shut
!
int e0/2
 ip address 10.2.6.6 255.255.255.0 
 no shut
!
int e0/3
 ip address 10.4.6.6 255.255.255.0
 no shut
!
int Lo0
 ip address 6.6.6.6 255.255.255.255
!
router ospf 1
 network 0.0.0.0 255.255.255.255 area 0
!
end
write
```

__#R1__
```
enable
conf t
!
int e0/0
 ip address 10.1.6.1 255.255.255.0
 no shut
!
end
write
```

__#R2__
```
enable
conf t
!
int e0/0
 ip address 10.2.6.2 255.255.255.0
 no shut
!
end
write
```

__#R3__
```
enable
conf t
!
int e0/3
 ip address 10.10.11.1 255.255.255.0
 no shut
!
end
write
```

__#R4__
```
enable
conf t
!
int e0/3
 ip address 10.4.6.4 255.255.255.0
 no shut
!
int e0/0
 ip address 10.4.5.4 255.255.255.0
 no shut
!
end
write
```

__#R5__
```
enable
conf t
!
int e0/3
 ip address 10.4.5.5 255.255.255.0
 no shut
!
end
write
```

__#Source2__
```
enable
conf t
!
hostname Source2
!
no ip domain lookup
!
int e0/1
 ip address 10.10.11.10 255.255.255.0
 no shut
!
ip route 0.0.0.0 0.0.0.0 10.10.11.1
!
end
write
```

__#R* (Bật PIM-SM trên tất cả router)__
```
enable
conf t
!
ip multicast-routing  ! If not configured already
ip pim rp-address 6.6.6.6  ! Even R6 needs this config so it "knows" it is an RP
ip pim spt-threshold infinity ! Disables SPT switchover so we can focus on basic PIM-SM
!
! Every interface
int range e0/0-3
 ip pim sparse-mode
!
end
write
```

Host1 join group 239.1.1.1, tạo trạng thái (*, 239.1.1.1) trên R3 với e0/2 được thêm vào OIL. RP là 6.6.6.6 và RPF neighbor là 10.2.3.2 (tức R2). R3 gửi PIM Join trên e0/1 hướng về RPF neighbor.

```
R3#show ip mroute | sec 239
(*, 239.1.1.1), 00:07:04/00:02:13, RP 6.6.6.6, flags: SC
  Incoming interface: Ethernet0/1, RPF nbr 10.2.3.2
  Outgoing interface list:
    Ethernet0/2, Forward/Sparse, 00:07:04/00:02:13
```

Bắt gói giữa link R3 và R2.

![alt text](/docs/CCNP/img/multicast-PIM-SM Lab 1.png)

R2 nhận PIM Join, tạo entry (*, 239.1.1.1) và gửi PIM Join về RP (R6).

```
R2#show ip mroute | sec 239
(*, 239.1.1.1), 00:14:50/00:03:19, RP 6.6.6.6, flags: S
  Incoming interface: Ethernet0/0, RPF nbr 10.2.6.6
  Outgoing interface list:
    Ethernet0/2, Forward/Sparse, 00:04:26/00:03:19
```

Đến đây, xem lại thì có 2 tình huống khiến giao diện được thêm vào OIL: 1 là nhận IGMP Join (như R3) và 2 là nhận PIM Join (như R2).

Tiếp theo, do R6 là root, không có incoming interface, nhưng thêm giao diện nối với R2 vào OIL.

```
R6#show ip mroute | sec 239
(*, 239.1.1.1), 00:17:55/00:03:16, RP 6.6.6.6, flags: S
  Incoming interface: Null, RPF nbr 0.0.0.0
  Outgoing interface list:
    Ethernet0/2, Forward/Sparse, 00:07:30/00:03:16
```

## PIM-SM Source Registration

Xem bảng mroute của R1 và R6 trước khi ping.

```
R1#show ip mroute | sec \(
(*, 224.0.1.40), 03:39:30/00:02:48, RP 6.6.6.6, flags: SCL
  Incoming interface: Ethernet0/0, RPF nbr 10.1.6.6
  Outgoing interface list:
    Ethernet0/3, Forward/Sparse, 03:39:28/stopped
    Ethernet0/2, Forward/Sparse, 03:39:29/stopped
    Ethernet0/1, Forward/Sparse, 03:39:30/00:02:32

R6#show ip mroute | sec \(
(*, 239.1.1.1), 01:10:42/00:02:44, RP 6.6.6.6, flags: S
  Incoming interface: Null, RPF nbr 0.0.0.0
  Outgoing interface list:
    Ethernet0/2, Forward/Sparse, 01:00:17/00:02:44
(*, 224.0.1.40), 01:15:17/00:03:06, RP 6.6.6.6, flags: SJCL
  Incoming interface: Null, RPF nbr 0.0.0.0
  Outgoing interface list:
    Ethernet0/2, Forward/Sparse, 01:15:16/00:03:06
    Ethernet0/1, Forward/Sparse, 01:15:16/00:03:00
    Ethernet0/3, Forward/Sparse, 01:15:16/00:02:58
```

Ping từ Source1 đến 239.1.1.1.

```
Source1#ping 239.1.1.1 repeat 8
Type escape sequence to abort.
Sending 8, 100-byte ICMP Echos to 239.1.1.1, timeout is 2 seconds:

Reply to request 0 from 10.10.0.10, 26 ms
Reply to request 1 from 10.10.0.10, 2 ms
Reply to request 1 from 10.10.0.10, 20 ms
Reply to request 2 from 10.10.0.10, 2 ms
Reply to request 3 from 10.10.0.10, 2 ms
Reply to request 4 from 10.10.0.10, 1 ms
Reply to request 5 from 10.10.0.10, 2 ms
Reply to request 6 from 10.10.0.10, 2 ms
Reply to request 7 from 10.10.0.10, 2 ms
```

Khi source gửi traffic (ví dụ, ping tới 239.1.1.1), FHR encapsulates gói tin trong PIM Register và unicast đến RP. 

![alt text](/docs/CCNP/img/multicast-PIM-SM Lab 2.png)

RP trả lời bằng PIM Join cho (S, G) (ví dụ (10.10.10.10, 239.1.1.1)); FHR tạo entry (S, G) với e0/0 trong OIL.

![alt text](/docs/CCNP/img/multicast-PIM-SM Lab 3.png)

```
R1#show ip mroute | sec \(
(*, 239.1.1.1), 00:08:46/stopped, RP 6.6.6.6, flags: SPF
  Incoming interface: Ethernet0/0, RPF nbr 10.1.6.6
  Outgoing interface list: Null
(10.10.10.10, 239.1.1.1), 00:02:30/00:01:02, flags: FT
  Incoming interface: Ethernet0/1, RPF nbr 0.0.0.0
  Outgoing interface list:
    Ethernet0/0, Forward/Sparse, 00:02:30/00:02:58
(*, 224.0.1.40), 03:51:22/00:02:56, RP 6.6.6.6, flags: SCL
  Incoming interface: Ethernet0/0, RPF nbr 10.1.6.6
  Outgoing interface list:
    Ethernet0/3, Forward/Sparse, 03:51:20/stopped
    Ethernet0/2, Forward/Sparse, 03:51:21/stopped
    Ethernet0/1, Forward/Sparse, 03:51:22/00:02:41
```

RP nhận thấy traffic đã đến theo (S, G), bỏ gói encapsulated, forward packet nhận từ (S, G) và gửi PIM Register Stop cho FHR, yêu cầu ngừng encapsulation. RP đã Join thành công vào cây (S, G) có route là Source1. (Trường hợp nếu không có receiver, RP sẽ gửi PIM Register-Stop và không gia nhập (S, G) tree).

![alt text](/docs/CCNP/img/multicast-PIM-SM Lab 4.png)

```
R6#show ip mroute | sec \(
(*, 239.1.1.1), 01:22:59/00:03:14, RP 6.6.6.6, flags: S
  Incoming interface: Null, RPF nbr 0.0.0.0
  Outgoing interface list:
    Ethernet0/2, Forward/Sparse, 01:12:34/00:03:14
(10.10.10.10, 239.1.1.1), 00:04:52/00:03:16, flags: T
  Incoming interface: Ethernet0/1, RPF nbr 10.1.6.1
  Outgoing interface list:
    Ethernet0/2, Forward/Sparse, 00:04:52/00:03:14
(*, 224.0.1.40), 01:27:34/00:02:35, RP 6.6.6.6, flags: SJCL
  Incoming interface: Null, RPF nbr 0.0.0.0
  Outgoing interface list:
    Ethernet0/2, Forward/Sparse, 01:27:33/00:02:35
    Ethernet0/1, Forward/Sparse, 01:27:33/00:02:31
    Ethernet0/3, Forward/Sparse, 01:27:33/00:02:31
```

RP và những router thuộc source-based tree sẽ có (\*, G) và (S, G), những router thuộc shared tree sẽ chỉ có (*, G).

```
R2#show ip mroute | sec 239
(*, 239.1.1.1), 00:04:01/00:03:25, RP 6.6.6.6, flags: S
  Incoming interface: Ethernet0/0, RPF nbr 10.2.6.6
  Outgoing interface list:
    Ethernet0/2, Forward/Sparse, 00:04:01/00:03:25

R3#show ip mroute | sec 239
(*, 239.1.1.1), 00:04:10/00:02:07, RP 6.6.6.6, flags: SC
  Incoming interface: Ethernet0/1, RPF nbr 10.2.3.2
  Outgoing interface list:
    Ethernet0/2, Forward/Sparse, 00:04:10/00:02:07
```

## PIM-SM Multiple sources sending to the same group

Trên host1 hủy join 239.1.1.1. Join 239.1.1.1 trên Host2. Gửi ping đến 239.1.1.1 từ cả Source1 và Source2.

Dù có nhiều source gửi đến 239.1.1.1, LHR (ví dụ R4) vẫn chỉ có 1 entry (*, 239.1.1.1).

```
R4#show ip mroute | sec 239
(*, 239.1.1.1), 00:08:01/00:02:15, RP 6.6.6.6, flags: SC
  Incoming interface: Ethernet0/3, RPF nbr 10.4.6.6
  Outgoing interface list:
    Ethernet0/2, Forward/Sparse, 00:08:01/00:02:15
```

Trạng thái trên R2 có entry (*, G) với OIL trống và entry (S, G) chứa Outgoing interface hướng về RP.

```
R2#show ip mroute | sec 239
(*, 239.1.1.1), 01:57:21/stopped, RP 6.6.6.6, flags: SP
  Incoming interface: Ethernet0/0, RPF nbr 10.2.6.6
  Outgoing interface list: Null
(10.10.11.10, 239.1.1.1), 00:02:30/00:00:29, flags: T
  Incoming interface: Ethernet0/2, RPF nbr 10.2.3.3
  Outgoing interface list:
    Ethernet0/0, Forward/Sparse, 00:02:30/00:02:59
```

Nếu Host1 gửi IGMP Join lại vào 239.1.1.1, R3 thêm e0/2 vào OIL cho (*, 239.1.1.1) và (S, G) cũng được cập nhật. Trong trường hợp này, traffic từ Source2 đến Host1 sẽ không đi qua RP.

```
R3#show ip mroute | sec 239
(*, 239.1.1.1), 00:00:31/stopped, RP 6.6.6.6, flags: SCF
  Incoming interface: Ethernet0/1, RPF nbr 10.2.3.2
  Outgoing interface list:
    Ethernet0/2, Forward/Sparse, 00:00:31/00:02:28
(10.10.11.10, 239.1.1.1), 00:00:25/00:03:08, flags: FT
  Incoming interface: Ethernet0/3, RPF nbr 0.0.0.0
  Outgoing interface list:
    Ethernet0/1, Forward/Sparse, 00:00:25/00:03:04
    Ethernet0/2, Forward/Sparse, 00:00:25/00:02:34
```

(*, G) được tạo khi có IGMP Join, PIM Join hoặc khi router thấy traffic đi từ source. Các interface sẽ được thêm vào OIL do IGMP/PIM Join từ downstream.  

(S, G) được tạo khi RP gia nhập source-based tree; các interface từ (*, G) tự động được thêm vào (S, G).

## PIM-SM Non-optimal routing of (*, G) traffic

Thiết kế PIM-SM yêu cầu traffic chạy qua RP vì LHR join vào cây (*, G) có root là RP, và cây (S, G) được xây dựng từ source tới RP để RP "pull" traffic xuống shared tree.  

Điều này có thể tạo ra đường đi không tối ưu; ví dụ, có thể có đường ngắn hơn trực tiếp từ FHR đến LHR (ví dụ R1 đến R5).  

<img style="max-width: 500px" src="/docs/CCNP/img/multicast-PIM-SM Non-optimal routing.png" />

Để khắc phục, PIM-SM cho phép chuyển sang __SPT switchover__: khi LHR nhận biết source, nó gia nhập cây (S, G) và gửi PIM Join về phía source, bỏ qua RP.

## PIM-SM SPT Switchover

__PIM-SM SPT Switchover__ cho phép LHR chuyển sang cây source-based tree (SPT) thay vì chạy qua RP để có đường đi ngắn nhất.

<h3>Lab</h3>

Sử dụng lại topo cũ. Đảm bảo hủy join group tất cả các host. Join group 239.100.100.100 trên Host4.

```
enable
conf t
!
int e0/0
 ip igmp join-group 239.100.100.100
!
end
```

SPT Switchover là mặc định. Ta đã tắt nó ở lab trước để có thể hiểu hành vi PIM-SM thuần. Bật lại SPT Switchover trên R5.

```
enable
conf t
!
ip pim spt-threshold 0
!
end
```

Ping từ Source1 đến 239.100.100.100.

```
Source1#ping 239.100.100.100 repeat 8
Type escape sequence to abort.
Sending 8, 100-byte ICMP Echos to 239.100.100.100, timeout is 2 seconds:

Reply to request 0 from 10.10.200.10, 39 ms
Reply to request 1 from 10.10.200.10, 3 ms
Reply to request 2 from 10.10.200.10, 3 ms
Reply to request 3 from 10.10.200.10, 1 ms
Reply to request 4 from 10.10.200.10, 1 ms
Reply to request 5 from 10.10.200.10, 2 ms
Reply to request 6 from 10.10.200.10, 4 ms
Reply to request 7 from 10.10.200.10, 1 ms
```

R5 bây giờ có cả 2 entry (\*, G) và (S, G) [Khi tắt SPT Switchover, R5 chỉ có entry (\*, G)]. R5 chuyển sang cây (S, G) dựa vào source, nhận traffic qua giao diện RPF thay vì qua shared tree.

```
R5#show ip mroute | sec 239
(*, 239.100.100.100), 00:23:33/stopped, RP 6.6.6.6, flags: SJC
  Incoming interface: Ethernet0/3, RPF nbr 10.4.5.4
  Outgoing interface list:
    Ethernet0/2, Forward/Sparse, 00:23:33/00:02:06
(10.10.10.10, 239.100.100.100), 00:02:37/00:00:22, flags: JT
  Incoming interface: Ethernet0/1, RPF nbr 10.1.5.1
  Outgoing interface list:
    Ethernet0/2, Forward/Sparse, 00:02:37/00:02:06
```

<h3>Packet Walkthrough</h3>

1. RP chuyển tiếp ping xuống shared tree; R5 nhận gói tin trên e0/3 và học được source.  
2. R5 switch sang source-based tree. R5 gửi PIM Join cho (S, G) (ví dụ: (10.10.10.10, 239.100.100.100)) qua e0/3 (giao diện RPF).
![alt text](/docs/CCNP/img/multicast-PIM-SM SPT Switchover 0.png)
3. Gói tin thứ 2 đến cả trên e0/3 và e0/1; R5 gửi PIM Prune cho nguồn 10.10.10.10, với RP-bit set, để loại bỏ traffic trùng từ shared tree.  
![alt text](/docs/CCNP/img/multicast-PIM-SM SPT Switchover 1.png)
4. Các router dọc đường (ví dụ R4) xóa giao diện không còn cần thiết trong OIL cho (S, G) của nguồn đó. RP loại bỏ các giao diện không cần thiết, và traffic sau đó chỉ đi theo cây SPT.

```
R4#show ip mroute | sec 239
(*, 239.100.100.100), 00:31:51/00:03:04, RP 6.6.6.6, flags: S
  Incoming interface: Ethernet0/3, RPF nbr 10.4.6.6
  Outgoing interface list:
    Ethernet0/0, Forward/Sparse, 00:31:51/00:03:04
(10.10.10.10, 239.100.100.100), 00:03:22/00:03:04, flags: PR
  Incoming interface: Ethernet0/3, RPF nbr 10.4.6.6
  Outgoing interface list: Null

R6#show ip mroute | sec 239
(*, 239.100.100.100), 00:32:02/00:02:57, RP 6.6.6.6, flags: S
  Incoming interface: Null, RPF nbr 0.0.0.0
  Outgoing interface list:
    Ethernet0/3, Forward/Sparse, 00:32:02/00:02:57
(10.10.10.10, 239.100.100.100), 00:03:35/00:02:24, flags: PT
  Incoming interface: Ethernet0/1, RPF nbr 10.1.6.1
  Outgoing interface list: Null

R1#show ip mroute | sec 239
(*, 239.100.100.100), 00:04:59/stopped, RP 6.6.6.6, flags: SPF
  Incoming interface: Ethernet0/0, RPF nbr 10.1.6.6
  Outgoing interface list: Null
(10.10.10.10, 239.100.100.100), 00:04:59/00:02:24, flags: FT
  Incoming interface: Ethernet0/1, RPF nbr 0.0.0.0
  Outgoing interface list:
    Ethernet0/3, Forward/Sparse, 00:02:49/00:02:40
```

<h3>Non-LHR Switchover</h3>

Nếu điểm chuyển (diversion point) nằm ở upstream của LHR (ví dụ tại R2), khi R3 (LHR) chuyển sang SPT (spt-threshold set là 0 trên R3), R2 phải rời khỏi shared tree nếu giao diện nhận của (S, G) khác với của (*, G).  

Nói cách khác, PIM Prune cho (S, G) trên shared tree chỉ xảy ra khi giao diện incoming của (S, G) khác với (*, G).

## PIM-SM Tunnel Interfaces

_(\* Đọc thêm)_

Interface tunnel của PIM dùng để đóng gói (encapsulate) và giải đóng gói (decapsulate) các thông điệp PIM Register.

- **Tunnel FHR:**  
  - Khi cấu hình địa chỉ RP, router tự động tạo Tunnel0 (thông báo bằng log, vd: "%LINEPROTO-5-UPDOWN...").  
  - Tunnel này là tunnel đơn hướng, dùng để đóng gói multicast traffic trong PIM Register message và unicast đến RP.  
  - Nó giúp RP nhận diện nguồn và xây dựng cây (S, G) dựa trên nguồn.  
  - Packet luôn có đích là địa chỉ unicast của RP, và tunnel thêm một header thứ hai (PIM-in-IPv4 encapsulation).

- **Kiểm tra Tunnel:**  
  Sử dụng lệnh `show ip pim tunnel` và `show int tun0` để xem chi tiết (loại, RP, nguồn, trạng thái, MTU, băng thông, …).  
  - Ví dụ: Tunnel0 hiển thị trạng thái UP, nguồn là 10.2.3.3 và đích là 6.6.6.6.  
  - Output packets tăng cho mỗi PIM Register gửi; input packets không tăng vì tunnel đơn hướng.

- **RP Tunnel Interfaces:**  
  RP tự tạo 2 tunnel:  
  1. **Tunnel0:** PIM Register tunnel (đóng gói) – hướng đến chính RP.  
  2. **Tunnel1:** PIM Register decapsulation tunnel – dùng để nhận PIM Register messages, giải đóng gói để trích xuất multicast packet và chuyển tiếp xuống cây chia sẻ.  
  - Kiểm tra với `show ip pim tun` và `show int tun1` để thấy thông tin chi tiết của Tunnel0 và Tunnel1.  
  - Lưu ý: Bộ đếm input trên Tunnel1 không tăng mặc dù RP đã giải đóng gói các gói Register.

## PIM DR và Assert Message

Sử dụng topo sau để mô tả 2 cơ chế này.

<img style="max-width: 300px" src="/docs/CCNP/img/multicast-PIM DR and Assert Message.png" />

<h3>Assert Message</h3>

Trong PIM-DM, khi source gửi multicast, R1 sẽ flood cả Gi2 và Gi3. R2 và R3 đều có entry (\*, 239.1.1.1), vì vậy mỗi router sẽ gửi lưu lượng ra Gi2 của nó. Host1 sẽ nhận được các gói trùng lặp.

```
R2#show ip mroute 239.1.1.1

(*, 239.1.1.1), 00:09:28/00:02:22, RP 0.0.0.0, flags: DC
  Incoming interface: Null, RPF nbr 0.0.0.0
  Outgoing interface list:
    GigabitEthernet2, Forward/Dense, 00:09:28/stopped
    GigabitEthernet1, Forward/Dense, 00:09:28/stopped

R3#show ip mroute 239.1.1.1

(*, 239.1.1.1), 00:09:42/00:02:04, RP 0.0.0.0, flags: DC
  Incoming interface: Null, RPF nbr 0.0.0.0
  Outgoing interface list:
    GigabitEthernet2, Forward/Dense, 00:09:42/stopped
    GigabitEthernet1, Forward/Dense, 00:09:42/stopped
```

Để ngăn điều này, PIM sử dụng Assert message: Khi một router nhận gói multicast trên một interface đã có trong OIL, nó gửi đi thông điệp Assert chứa AD và metric của mình. Nếu nhận được Assert với metric thấp hơn (hoặc cùng metric nhưng IP cao hơn), router đó dừng gửi traffic trên interface đó.

Ví dụ: R2 và R3 đều nhận traffic từ R1, dẫn đến duplicated packets tại Host1. R3 gửi Assert; R2, nhận thấy R3 "win", R2 sẽ gửi Prune trên Gi2 và Gi1.

```
R2#show ip mroute 239.1.1.1

(*, 239.1.1.1), 00:07:04/stopped, RP 0.0.0.0, flags: DC
  Incoming interface: Null, RPF nbr 0.0.0.0
  Outgoing interface list:
    GigabitEthernet1, Forward/Dense, 00:06:39/stopped
    GigabitEthernet2, Forward/Dense, 00:07:04/stopped

(10.10.10.10, 239.1.1.1), 00:04:08/00:01:51, flags: PT
  Incoming interface: GigabitEthernet1, RPF nbr 10.1.2.1
  Outgoing interface list:
    GigabitEthernet2, Prune/Dense, 00:04:08/00:01:48
```

```
R1#show ip mroute 239.1.1.1

(*, 239.1.1.1), 00:05:32/stopped, RP 0.0.0.0, flags: D
  Incoming interface: Null, RPF nbr 0.0.0.0
  Outgoing interface list:
    GigabitEthernet3, Forward/Dense, 00:05:32/stopped
    GigabitEthernet2, Forward/Dense, 00:05:32/stopped

(10.10.10.10, 239.1.1.1), 00:00:43/00:02:16, flags: T
  Incoming interface: GigabitEthernet1, RPF nbr 0.0.0.0
  Outgoing interface list:
    GigabitEthernet2, Prune/Dense, 00:00:31/00:02:28
    GigabitEthernet3, Forward/Dense, 00:00:43/stopped
```

<h3>Designated Router (DR)</h3>

Trong PIM-SM, DR dùng để ngăn duplicated traffic bị pull down từ cả 2 router R2 và R3.

DR được bầu khi các PIM neighborship up, chỉ dùng trong PIM-SM. DR là duy nhất trên một segment, chịu trách nhiệm gửi PIM Join upstream (hoặc PIM Register nếu là FHR) để tránh gửi duplicated traffic.

Ưu tiên dựa trên DR Priority (mặc định là 1). Nếu bằng thì chọn router có IP cao nhất.

Ví dụ: Trên broadcast segment có R2 và R3, nếu R3 có DR flag, thì R2 sẽ không gửi PIM Join mà chỉ gửi Prune. DR cũng chịu trách nhiệm gửi PIM Register nếu có nhiều FHR trên LAN.

```
R2#show ip pim neighbor 
PIM Neighbor Table
Mode: B - Bidir Capable, DR - Designated Router, N - Default DR Priority,
      P - Proxy Capable, S - State Refresh Capable, G - GenID Capable,
      L - DR Load-balancing Capable
Neighbor          Interface                Uptime/Expires    Ver   DR
Address                                                            Prio/Mode
10.1.2.1          GigabitEthernet1         00:20:03/00:01:21 v2    1 / S P G
10.10.100.3       GigabitEthernet2         00:20:02/00:01:21 v2    1 / DR S P G
```

```
*Sep 14 14:44:49.730: PIM(0): Re-check RP 1.1.1.1 into the (*, 239.1.1.1) entry
*Sep 14 14:44:49.731: PIM(0): Building Triggered (*,G) Join / (S,G,RP-bit) Prune message for 239.1.1.1

R2#show ip mroute 239.1.1.1

(*, 239.1.1.1), 00:00:23/00:02:49, RP 1.1.1.1, flags: SP
  Incoming interface: GigabitEthernet1, RPF nbr 10.1.2.1
  Outgoing interface list: Null
```

```
R1#show ip mroute 239.1.1.1

(*, 239.1.1.1), 00:06:04/00:03:02, RP 1.1.1.1, flags: S
  Incoming interface: Null, RPF nbr 0.0.0.0
  Outgoing interface list:
    GigabitEthernet3, Forward/Sparse, 00:02:25/00:03:02
```

<h3>DR Failover</h3>

Nếu DR fail, router không phải DR chỉ takeover sau khi neighborship timeout (thường là 105 giây).

```
#R3
int range Gi1-2
 shutdown

Source1#ping 239.1.1.1 repeat 100
Type escape sequence to abort.
Sending 100, 100-byte ICMP Echos to 239.1.1.1, timeout is 2 seconds:

Reply to request 0 from 10.10.100.10, 37 ms...................................................
Reply to request 52 from 10.10.100.10, 20 ms
```

51 lần ping timeout trước khi R2 take over DR.

## PIM-SM Auto-RP

Auto-RP được tạo ra độc quyền của Cisco, dùng giải quyết cấu hình RP (ip pim rp-address) là thủ công và không hỗ trợ nhiều RP dự phòng.

**Candidate RP:** Cấu hình bằng lệnh __ip pim send-rp-announce__; các router gửi thông báo trạng thái tới Mapping Agent qua multicast __224.0.1.39__ (Cisco-RP-Announce).  

**Mapping Agent:** Cấu hình bằng lệnh __ip pim send-rp-discovery__; lắng nghe các candidate RP trên __224.0.1.39__ và chọn RP tốt nhất (dựa trên IP cao nhất), sau đó quảng bá RP đó cho tất cả các router qua __224.0.1.40__ (Cisco-RP-Discovery).

**Router PIM-SM khác:** Lắng nghe các thông báo RP trên __224.0.1.40__.

_(Sử dụng lại lab trước.)_

__#R* (Xóa cấu hình Static RP trên tất cả router)__
```
enable
conf t
!
no ip pim rp-address 6.6.6.6
!
end
```

__#R2 (Cấu hình làm Mapping Agent)__ 
```
enable
conf t
!
interface Lo0
  ip pim sparse-mode
!
ip pim send-rp-discovery Lo0 scope 255  ! scope value will be used for the TTL of the packet
!
end
```

__#R6 (Cấu hình làm Candidate RP) __ 
```
enable
conf t
!
interface Lo0
  ip pim sparse-mode
!
ip pim send-rp-announce Lo0 scope 255
!
end
```  

Sau đó, các router sẽ nhận thông báo RP (ví dụ, R4 học RP là 6.6.6.6) qua các thông điệp trên 224.0.1.39/224.0.1.40.
  
```
R4#show ip pim rp
Group: 239.1.1.1, RP: 6.6.6.6, uptime 00:10:00, expires 00:02:49
R4#show ip mroute | sec 239
(*, 239.1.1.1), 00:00:42/00:02:27, RP 6.6.6.6, flags: SC
  Incoming interface: Ethernet0/3, RPF nbr 10.4.6.6
  Outgoing interface list:
    Ethernet0/2, Forward/Sparse, 00:00:42/00:02:27
```

Router không trực tiếp kề với Mapping Agent sẽ không học được RP.

```
R5#show ip pim rp
Group: 239.100.100.100, RP: 0.0.0.0
R5#show ip mroute | sec 239
(*, 239.100.100.100), 00:42:08/00:02:53, RP 0.0.0.0, flags: SJC
  Incoming interface: Null, RPF nbr 0.0.0.0
  Outgoing interface list:
    Ethernet0/2, Forward/Sparse, 00:42:08/00:02:53
```

Lệnh __ip pim autorp listener__ buộc router chuyển tiếp thông điệp Auto-RP, giúp các router không trực tiếp kề với Mapping Agent học được RP.

```
R4(config)#do show ip mroute | sec 224
(*, 224.0.1.39), 00:17:29/00:02:06, RP 0.0.0.0, flags: DC
  Incoming interface: Null, RPF nbr 0.0.0.0
  Outgoing interface list:
    Ethernet0/1, Forward/Sparse, 00:17:29/00:02:06
(*, 224.0.1.40), 00:22:21/stopped, RP 0.0.0.0, flags: DCL
  Incoming interface: Null, RPF nbr 0.0.0.0
  Outgoing interface list:
    Ethernet0/1, Forward/Sparse, 00:22:21/00:02:58
(2.2.2.2, 224.0.1.40), 00:16:21/00:02:29, flags: PLTX
  Incoming interface: Ethernet0/1, RPF nbr 10.2.4.2
  Outgoing interface list: Null
R4(config)#ip pim autorp listener
R4(config)#do show ip mroute | sec 224
(*, 224.0.1.39), 00:00:09/stopped, RP 0.0.0.0, flags: DC
  Incoming interface: Null, RPF nbr 0.0.0.0
  Outgoing interface list:
    Ethernet0/0, Forward/Sparse, 00:00:09/stopped
    Ethernet0/3, Forward/Sparse, 00:00:09/stopped
    Ethernet0/1, Forward/Sparse, 00:00:09/stopped
(6.6.6.6, 224.0.1.39), 00:00:09/00:02:50, flags: T
  Incoming interface: Ethernet0/3, RPF nbr 10.4.6.6
  Outgoing interface list:
    Ethernet0/1, Forward/Sparse, 00:00:09/stopped
    Ethernet0/0, Forward/Sparse, 00:00:09/stopped
(*, 224.0.1.40), 00:00:12/00:02:47, RP 0.0.0.0, flags: DCL
  Incoming interface: Null, RPF nbr 0.0.0.0
  Outgoing interface list:
    Ethernet0/0, Forward/Sparse, 00:00:12/stopped
    Ethernet0/3, Forward/Sparse, 00:00:12/stopped
    Ethernet0/1, Forward/Sparse, 00:00:12/stopped

R5#show ip pim rp
Group: 239.100.100.100, RP: 6.6.6.6, uptime 00:02:02, expires 00:02:56
R5#show ip mroute | sec 239
(*, 239.100.100.100), 00:50:21/00:02:38, RP 6.6.6.6, flags: SJC
  Incoming interface: Ethernet0/3, RPF nbr 10.4.5.4
  Outgoing interface list:
    Ethernet0/2, Forward/Sparse, 00:50:21/00:02:38
```

## PIM-SM BSR (Bootstrap Router)

BSR được tích hợp trong PIMv2, thay thế Auto-RP đã cũ.

**Candidate RPs (C-RPs):** Tương tự Auto-RP, thông báo trạng thái được gửi đến BSR.

**Candidate BSR (C-BSR):** Công bố trạng thái qua PIM messages. Một BSR được bầu (dựa trên priority cao nhất hoặc IP cao nhất, mặc định priority = 0) và BSR sẽ phân phối thông tin RP cho tất cả router.

__#R2 (Cấu hình làm Candidate BSR)__

```
enable
conf t
!
interface Lo0
  ip pim sparse-mode
!
no ip pim send-rp-discovery Lo0 scope 
ip pim bsr-candidate lo0
!
end
```

__#R1/R6 (Cấu hình làm Candidate RP)__

```
enable
conf t
!
interface Lo0
  ip pim sparse-mode
!
no ip pim send-rp-discovery Lo0 scope 
ip pim rp-candidate lo0
!
end
```

BSR sẽ quảng bá RP-set cho toàn mạng.

```
R5#show ip pim rp mapping
PIM Group-to-RP Mappings

Group(s) 224.0.0.0/4
  RP 6.6.6.6 (?), v2
    Info source: 2.2.2.2 (?), via bootstrap, priority 0, holdtime 150
         Uptime: 00:00:23, expires: 00:02:02
  RP 1.1.1.1 (?), v2
    Info source: 2.2.2.2 (?), via bootstrap, priority 0, holdtime 150
         Uptime: 00:00:36, expires: 00:02:02
```

## PIM-BiDir

<h3>DF Election</h3>

_(Chưa sẵn sàng)_

Một số ứng dụng sử dụng cách tiếp cận many-to-many. Ví dụ: một ứng dụng trò chuyện video hỗ trợ đa hướng có thể có mỗi người tham gia đều vừa là cả nguồn phát và người nhận. Người tham gia là một nguồn gửi video của riêng mình và là người nhận tất cả các luồng khác của người tham gia.

Để kích hoạt pim-bidir, cần 2 bước:
- Bật BIDIR trên mỗi router: __ip pim bidir-enable__
- Đặt RP thành Bidir:
  - Statically: __ip pim rp-address 1.1.1.1 bidir__
  - BSR: __ip pim rp-candidate Lo0 bidir__
  - Auto-RP: __ip pim send-rp-announce lo0 scope 255 bidir__

<h3>Traffic flow</h3>

_(Chưa sẵn sàng)_

<h3>Phantom RP</h3>

_(Chưa sẵn sàng)_

## PIM-SSM (Source-Specific Multicast)

- **Khái niệm:**  
  - Host chỉ nhận traffic từ 1 nguồn cụ thể.  
  - LHR gia nhập cây (S, G) dựa trên thông tin nguồn từ IGMP Membership Report (ví dụ: (1.1.1.1, 232.1.1.1)).  
  - Cây (S, G) xây dựng giống như PIM-SM sau SPT switchover, nhưng không cần RP vì host đã cung cấp source.

- **Yêu cầu & Giao thức:**  
  - Yêu cầu IGMPv3 trên host để cho phép chỉ định nguồn.  
  - IGMPv3 hỗ trợ tương thích ngược với IGMPv2.
  - PIM-SSM sử dụng dải nhóm 232.0.0.0/8 (có thể thay đổi qua ACL).

- **Ưu điểm:**  
  - Giảm phức tạp: không cần cấu hình RP.
  - Mỗi (source, group) là một flow duy nhất, cho phép tái sử dụng cùng một multicast IP cho các nguồn khác nhau (ví dụ, S1 và S2 cùng sử dụng G cho các kênh TV khác nhau).

- **Cấu hình Lab:**  
  - Loại bỏ các cấu hình PIM-bidir và RP cũ.
  - Cấu hình R6 làm RP bằng BSR (nếu dùng PIM-SM kết hợp).
  - Thiết lập PIM-SSM trên tất cả router:  
    ```
    ip pim ssm default
    ```
  - Trên các interface đối với host (ví dụ R3, R4, R5):  
    ```
    ip igmp version 3
    ```
  - Host tham gia SSM bằng lệnh:  
    ```
    ip igmp join-group 232.1.1.1 source 10.10.10.10
    ```
  - Lưu ý: ban đầu, nếu host vẫn chạy IGMPv2, tham số source sẽ bị bỏ qua.

- **Luồng Traffic & IGMPv3:**  
  - LHR (ví dụ R5) tạo trạng thái cho cả ASM và SSM dựa trên IGMPv3 Membership Report của host.  
  - Ví dụ, trạng thái:  
    - (*, 239.100.100.100) cho ASM, có liên quan đến RP.  
    - (10.10.10.10, 232.1.1.1) cho SSM, được xây dựng trực tiếp từ FHR đến LHR.
  - Khi source gửi traffic tới 232.1.1.1, host nhận phản hồi mà không cần RP can thiệp.

- **Quá trình Leave:**  
  - Khi host rời nhóm ASM, IGMPv3 chuyển sang “Include” với 0 nguồn.
  - Khi host rời nhóm SSM, thông điệp Leave khiến LHR gỡ bỏ entry (vì nguồn duy nhất bị chặn).

- **Kết luận:**  
  - PIM-SSM dùng IGMPv3 để cho host chỉ định nguồn, giúp LHR xây dựng cây (S, G) SPT trực tiếp từ nguồn mà không cần RP.  
  - So với PIM-SM, việc phát hiện nguồn được thực hiện sớm và không cần quá trình đăng ký nguồn (Source Registration), giảm tải cho mạng.


