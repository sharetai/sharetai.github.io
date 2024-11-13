---
layout: default
title: Virtualization
nav_order: 120
parent: CCNP
---

# Virtualization
{: .no_toc }

Ảo hóa
{: .fs-6 .fw-300 }

---

## Table of contents
{: .no_toc .text-delta }

1. TOC
{:toc}

---

## Virtual Routing and Forwarding (VRF)
<br>
Với Switch ta có kỹ thuật VLAN chia switch thành nhiều switch nhỏ. Với Router ta có kỹ thuật VRF chia router thành nhiều router nhỏ với các bảng định tuyến khác nhau.

![alt text](/docs/CCNP/img/vrf.avif)

Configuration

```
enable
conf t
!
! Create a VRF instance for our Customer A. Remember that the VRF name is case-sensitive.
vrf definition Cust-A
! Initialize the address family.
address-family ipv4
!
! Associate interfaces with VRF instance.
interface e0/1
no shut
vrf forwarding Cust-A
! Configure the IPv4 address on the interface.
ip address 192.168.1.1 255.255.255.0
!
! Repeat the same process for Customer B
vrf definition Cust-B
address-family ipv4
!
interface e0/2
no shut
vrf forwarding Cust-B
ip address 192.168.1.1 255.255.255.0
!
end
```

Verify

```
Router#sh ip route
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

Router#sh ip route vrf Cust-A

Routing Table: Cust-A
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

  192.168.1.0/24 is variably subnetted, 2 subnets, 2 masks
C192.168.1.0/24 is directly connected, Ethernet0/1
L192.168.1.1/32 is directly connected, Ethernet0/1
Router#sh ip route vrf Cust-B

Routing Table: Cust-B
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

  192.168.1.0/24 is variably subnetted, 2 subnets, 2 masks
C192.168.1.0/24 is directly connected, Ethernet0/2
L192.168.1.1/32 is directly connected, Ethernet0/2
Router#
```

<br>

## Locator ID Separation Protocol (LISP)
<br>
___Locator ID Separation Protocol (LISP)___ là cách tiếp cận kiến trúc định tuyến mới cho phép việc mở rộng hệ thống định tuyến hiệu quả hơn so với hiện tại, ứng dụng cho cả môi trường doanh nghiệp và ISP.

Khái niệm "___Separation Protocol___" có thể được hiểu là sự tách biệt _định danh của host_ (___Endpoint Identifier – EID___) và _vị trí của host_ (___Routing Locator – RLOC___), đây là sự khác biệt với kiến trúc định tuyến hiện tại là không có sự phân biệt giữa hai khái niệm này. Hay nói cách khác với kiến trúc định tuyến hiện tại khi thiết kế mạng, chúng ta sẽ phải xây dựng sơ đồ mạng với nhiều vùng và qui hoạch IP Subnet cho mỗi vùng tương ứng, điều này dẫn đến sự hạn chế khi một host cần thay đổi vùng mạng, địa chỉ IP cũng sẽ phải thay đổi theo, đây chính là _di động_ (___mobility___). Một lợi ích khác đó là LISP không quảng bá thông tin (mô hình ___push___) về mạng mà nó biết như kiến trúc định tuyến hiện tại, mà khi cần gửi gói tin đến vùng mạng bất kỳ nó sẽ gửi yêu cầu (___pull___) đến hệ thống lưu trữ thông tin chứa ánh xạ giữa EID-RLOC cơ chế này tương tự như tiến trình hoạt động của DNS, điều này cho phép bảng định tuyến sẽ gọn hơn rất nhiều, đặt biệt là các router Core khi chỉ cần duy trì thông tin địa chỉ của RLOC mà không cần quan tâm đến địa chỉ của EID.

![alt text](/docs/CCNP/img/lisp-architecture.png)

\- __EID (Endpoint ID):__ Là địa chỉ IP của host, địa chỉ dùng nhận diện host trong hệ thống định tuyến. <br>
\- __RLOC ( Routing Locator):__ Là địa chỉ của LISP Router, địa chỉ cho phép xác định vị trí của host trong hệ thống định tuyến. <br>
\- __ITR (Ingress Tunnel Router):__ Vai trò của thiết bị sẽ nhận gói từ host bên trong và đóng gói (encapsulate) trước khi gửi đến remote site. <br>
\- __ETR (Egress Tunnel Router):__ Vài trò của thiết bị nhận gói từ remote site sau đó mở đóng gói (de-encapsulate) trước khi gửi đến host bên trong. <br>
\- __MS (Map Server):__ Vai trò nhận thông tin đăng ký từ ETR, xây dựng bảng ánh xạ giữa EID-RLOC. <br>
\- __MR (Map Resolver):__ Vai trò xử lý yêu cầu (Map-Request) từ ITR, chuyển tiếp các yêu cầu đó đến Map Server. <br>

Thông thường một thiết bị sẽ đóng cả hai vai trò trong triển khai thực tế, như ITR và ETR là xTR hoặc vai trò Map-Server và Map Resolver là MS/MR.

Có 3 sites trong môi trường LISP environment:

\- __LISP Sites__ – nơi có EID. <br>
\- __Non-LISP Sites__ – nơi có RLOC. <br>
\- __LISP Mapping Service__ – chịu trách nhiệm ánh xạ EID-to-RLOC. <br>

Hoạt động của LISP:

\- __Map Registration and Notification__ <br>
\- __Map Request and Map Reply__ <br>
\- __LISP Protocol Data Path__ <br>

<h3>Map Registration and Notification</h3>

![alt text](/docs/CCNP/img/lisp-Map-Registration-and-Notification.png)

1\. Router ETR gửi _"Map Register Message"_ đến Router MS để đăng ký EID mới, 10.1.2.0/24. Message cũng sẽ chứa RLOC của router, 100.64.2.2. <br>
2\. Router MS gửi lại _"Map Notify Message"_ qua cổng UDP 4342, xác nhận rằng EID đã được thêm vào database. <br>

<h3>Map Request and Map Reply</h3>

![alt text](/docs/CCNP/img/lisp-Map-Request-and-Map-Reply.png)

1\. Host ở Site 1, host1, gửi DNS query để lấy địa chỉ IP của host2.cisco.com. Máy chủ DNS phản hồi bằng địa chỉ IP EID 10.1.2.2. Sau đó, host1 gửi lưu lượng đến 10.1.2.2, nhưng nó sẽ được chuyển tiếp đến default gateway (ITR). <br>
2\. Router ITR nhận gói tin được gửi đến địa chỉ 10.1.2.2 sẽ thực hiện kiểm tra: <br>
Liệu gói tin có khớp với default route vì không có route nào khác cho nó không? <br>
\- CÓ – Bộ định tuyến sẽ chuyển sang bước tiếp theo. <br>
\- KHÔNG – Bộ định tuyến đi theo tuyến đường định tuyến phù hợp. <br>
3\. Router ITR gửi _"Map Request"_ đến Router MR liên quan đến địa chỉ 10.1.2.2. <!-- Router ITR chọn cổng nguồn và cổng đích là cổng UDP 4342. --> <br>
4\. Router MR nhận _Map Request_ và chuyển hướng đến chính xác ETR.<br>
5\. Router ETR phản hồi _"Map Reply"_ đến ITR, chứa ánh xạ EID-to-RLOC (10.1.2.2 -> 100.64.2.2). <br>
6\. Router ITR lưu trữ ánh xạ EID-to-RLOC trong database, thay đổi lại nội dung của bảng FIB. <br>

<h3>LISP Protocol Data Path</h3>

Sau khi nhận được ánh xạ EID-to-RLOC từ Router ETR (hoặc Router MS), Router ITR sẽ sẵn sàng trao đổi dữ liệu giữa các thiết bị đầu cuối.

![alt text](/docs/CCNP/img/lisp-LISP-Protocol-Data-Path.png)

<br>

## Virtual Extensible LAN (VXLAN)
<br>
VLAN thì đã biết, chức năng của VLAN là phân chia và hiểu một cách đơn giản là mỗi frame dán thêm 1 nhãn (VLAN ID) vào để phân tách lưu lượng.

Vậy tại sao là VXLAN?

VXLAN - Virtual Extensible LAN, dựa vào tên nói lên đặc điểm quan trọng nhất của VXLAN chính là mở rộng VLAN.

Vậy VXLAN ra đời với mục đích gì?

Với xu thế phát triển mạnh mẽ của Cloud Computing, hạ tầng Data Center (DC). VLAN gặp nhiều vấn đề bất cập bao gồm:

\- Số lượng VLAN hạn chế (chỉ có 12-bit ~4096 VLAN ID). VXLAN sử dụng 24-bit cho VXLAN ID (hơn 16 triệu VXLAN ID). <br>
\- Với hạ tầng overlay phức tạp và số lượng lớn VM thì lưu lượng mạng cũng cực lớn. STP (Spanning Tree Protocol) sẽ có độ trễ là khá lớn. <br>
\- ECMP hay load balancing không hỗ trợ. <br>
\- Hạ tầng ảo hóa với số lượng VM (Virtual Machine) cực lớn, yêu cầu số lượng MAC entry cũng cực lớn trên switch. <br>

<h3>Cấu trúc gói tin VxLAN</h3>

![alt text](/docs/CCNP/img/VxLAN-Packet-Format.gif)

<h3>Mạng Overlay và Underlay</h3>

Cơ sở hạ tầng mạng vật lý sẽ là mạng Underlay. Nhờ có các giao thức Lớp 3 trong mạng Underlay, do đó định tuyến động và ECMP sẽ được sử dụng. Mặt khác, mạng Overlay là mạng ảo được xây dựng trên nền mạng vật lý. <br>
Các gói VXLAN sử dụng mã định danh __VXLAN network identifier__ hoặc __VNI__, tương tự như VLAN ID. Đây là mã định danh 24-bit có khả năng tạo ra hơn 16 triệu phân đoạn VXLAN. <br>

<h3>VXLAN Tunnel EndPoint (VTEP)</h3>

VTEP cung cấp kết nối giữa mạng underlay và overlay. Mỗi VTEP có một địa chỉ IP trong mạng underlay và một hoặc nhiều VNI trong mạng overlay. Để chuyển tiếp lưu lượng từ máy chủ này sang máy chủ khác, VTEP nguồn và đích sẽ tạo một đường hầm và chỉ tồn tại để phân phối VXLAN header bên trong một frame. 1 cách hiểu đơn giản là VTEP convert gói tin thường thành gói tin VxLAN và ngược lại.

<h3>VXLAN Control Plane</h3>

VXLAN là data plane protocol và có thể sử dụng với bất kỳ control plane:

Multicast Underlay <br>
MP-BGP EVPN Control Plane <br>
LISP Control Plane <br>
Static Unicast VXLAN Tunnels <br>

VXLAN với Multicast Underla và MP-BGP EVPN Control Plane thường được sử dụng trong các trung tâm dữ liệu và môi trường đám mây riêng. VXLAN với LISP thường được sử dụng trong môi trường campus, ví dụ như Cisco SD-Access.
