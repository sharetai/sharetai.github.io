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
___Locator ID Separation Protocol (LISP)___ là cách tiếp cận kiến trúc định tuyến mới cho phép việc mở rộng hệ thống định tuyến hiệu quả hơn so với hiện tại, ứng dụng cho cả môi trường doanh nghiệp và ISP. LISP vừa là _giao thức mặt phẳng điều khiển_ (___control plane___) vừa là _giao thức mặt phẳng dữ liệu_ (___data plane___), tham gia và việc ánh xạ (___mapping___) và đóng gói (___encapsulation___). Cisco đã tạo ra LISP nhưng nó là một tiêu chuẩn mở.

Khái niệm "___Separation Protocol___" có thể được hiểu là sự tách biệt _định danh của host_ (___Endpoint Identifier – EID___) và _vị trí của host_ (___Routing Locator – RLOC___), đây là sự khác biệt với kiến trúc định tuyến hiện tại là không có sự phân biệt giữa hai khái niệm này. Hay nói cách khác với kiến trúc định tuyến hiện tại khi thiết kế mạng, chúng ta sẽ phải xây dựng sơ đồ mạng với nhiều vùng và qui hoạch IP Subnet cho mỗi vùng tương ứng, điều này dẫn đến sự hạn chế khi một host cần thay đổi vùng mạng, địa chỉ IP cũng sẽ phải thay đổi theo, đây chính là _di động_ (___mobility___). Một lợi ích khác đó là LISP không quảng bá thông tin (mô hình ___push___) về mạng mà nó biết như kiến trúc định tuyến hiện tại, mà khi cần gửi gói tin đến vùng mạng bất kỳ nó sẽ gửi yêu cầu (___pull___) đến hệ thống lưu trữ thông tin chứa ánh xạ giữa EID-RLOC cơ chế này tương tự như tiến trình hoạt động của DNS, điều này cho phép bảng định tuyến sẽ gọn hơn rất nhiều, đặt biệt là các router Core khi chỉ cần duy trì thông tin địa chỉ của RLOC mà không cần quan tâm đến địa chỉ của EID.

![alt text](/docs/CCNP/img/lisp-architecture.png)

Có 3 sites trong môi trường LISP environment:

\- __LISP Sites__ – nơi có EID. <br>
\- __Non-LISP Sites__ – nơi không có EID. <br>
\- __LISP Mapping Service__ – chịu trách nhiệm ánh xạ EID-to-RLOC. <br>

Một số vai trò trong môi trường LISP environment:

\- __EID (Endpoint ID):__ Là địa chỉ IP của host, địa chỉ dùng nhận diện host trong hệ thống định tuyến. <br>
\- __RLOC (Routing Locator):__ Là địa chỉ của LISP Router, địa chỉ cho phép xác định vị trí của host trong hệ thống định tuyến. <br>
\- __ITR (Ingress Tunnel Router):__ Vai trò của thiết bị sẽ nhận gói từ host bên trong LISP site và đóng gói (encapsulate) trước khi gửi đến bên ngoài LISP site. <br>
\- __ETR (Egress Tunnel Router):__ Vài trò của thiết bị nhận gói từ bên ngoài LISP site sau đó mở đóng gói (de-encapsulate) trước khi gửi đến host bên trong LISP site. <br>
\- __MS (Map Server):__ Vai trò nhận thông tin đăng ký từ ETR, xây dựng bảng ánh xạ EID-to-RLOC. <br>
\- __MR (Map Resolver):__ Vai trò xử lý yêu cầu (Map-Request) từ ITR, chuyển tiếp các yêu cầu đó đến Map Server. <br>
\- __PITR (Proxy Ingress Tunnel Router):__ Hoạt động tương tự như ITR nhưng dành cho lưu lượng từ Non-LISP site đến EID. <br>
\- __PETR (Proxy Egress Tunnel Router):__ Hoạt động tương tự như ETR nhưng dành cho lưu lượng từ EID đến Non-LISP site. <br>

_Thông thường một thiết bị sẽ đóng cả hai vai trò trong triển khai thực tế, như ITR và ETR là_ ___xTR___ _hoặc vai trò Map-Server và Map Resolver là_ ___MS/MR___.

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
4\. Nếu chỉ có 1 thiết bị làm MS/MR, sẽ chuyển hướng đến chính xác ETR. Nếu có 2 thiết bị độc lập, MR sẽ gửi _Map Request_ đến MS và cũng sẽ chuyển hướng đến chính xác ETR. <br>
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

<h3>Cấu trúc gói tin VXLAN</h3>

<!-- ![alt text](/docs/CCNP/img/VXLAN-Packet-Format.gif) -->

<img src="/docs/CCNP/img/VxLAN-Packet-Format.png" width="1020">

![alt text](/docs/CCNP/img/VXLAN-GPO-Header.png)

<h3>Mạng Overlay và Underlay</h3>

Cơ sở hạ tầng mạng vật lý sẽ là mạng Underlay. Nhờ có các giao thức Lớp 3 trong mạng Underlay, do đó định tuyến động và ECMP sẽ được sử dụng. Mặt khác, mạng Overlay là mạng ảo được xây dựng trên nền mạng vật lý. <br>
Các gói VXLAN sử dụng mã định danh __VXLAN network identifier__ hoặc __VNI__, tương tự như VLAN ID. Đây là mã định danh 24-bit có khả năng tạo ra hơn 16 triệu phân đoạn VXLAN. <br>

<h3>VXLAN Tunnel EndPoint (VTEP)</h3>

VTEP cung cấp kết nối giữa mạng underlay và overlay. Mỗi VTEP có một địa chỉ IP trong mạng underlay và một hoặc nhiều VNI trong mạng overlay. Để chuyển tiếp lưu lượng từ máy chủ này sang máy chủ khác, VTEP nguồn và đích sẽ tạo một đường hầm và chỉ tồn tại để phân phối VXLAN header bên trong một frame. 1 cách hiểu đơn giản là VTEP convert gói tin thường thành gói tin VXLAN và ngược lại.

<h3>VXLAN Control Plane</h3>

VXLAN là data plane protocol và có thể sử dụng với bất kỳ control plane:

\- Multicast Underlay <br>
\- MP-BGP EVPN Control Plane <br>
\- LISP Control Plane <br>
\- Static Unicast VXLAN Tunnels <br>

VXLAN với Multicast Underlay và MP-BGP EVPN Control Plane thường được sử dụng trong các trung tâm dữ liệu và môi trường đám mây riêng. VXLAN với LISP thường được sử dụng trong môi trường campus, ví dụ như Cisco SD-Access.

<br>

## Software-Defined Access (SD-Access)
<br>

<h3>SD-Access Fabric</h3>

![alt text](/docs/CCNP/img/SD-Access-Fabric.webp)
<img src="/docs/CCNP/img/SD-Access-Fabric-Terminology.png" width="620">

1 mạng ___Fabric___, có thể hiểu là 1 mạng trục, là 1 mạng luận lý ___Overlay___ được ảo hóa thiết bị kết nối, xây dựng trên 1 hạ tầng mạng vật lý ___Underlay___.

Mạng Fabric sử dụng đường đi hoàn toàn khác biệt so với mạng vật lý, giúp cung cấp thêm nhiều dịch vụ.

<h3>SD-Access Underlay</h3>

![alt text](/docs/CCNP/img/SD-Access-Underlay.png)

Triển khai giải pháp SD-Access, 2 cách là thủ công hoặc tự động.

<h3>SD-Access Fabric Roles</h3>

<img src="/docs/CCNP/img/SD-Access-Fabric-Roles.png" width="1020">

Vai trò của một số thành phần trong mạng Fabric.

Công nghệ SD-Access của Cisco tự động hóa mạng doanh nghiệp bằng cách sử dụng Cisco DNA Center:

__Network Control Platform (NCP)__ - Cấu hình và quản lý các thiết bị mạng bằng SNMP, SSH/Telnet, NETCONF/YANG, v.v. Cung cấp tự động hóa mạng. <br>
__Network Data Platform (NDP)__ - Thu thập dữ liệu, xu hướng lịch sử, phân tích và liên hệ các sự kiện mạng từ nhiều nguồn khác nhau, chẳng hạn như SPAN và NetFlow. <br>
__Identity Services Engine (ISE)__ - Định nghĩa chính sách (Policy), nhận dạng (Identity), Kiểm soát truy cập mạng (Network Access Control - NAC). <br>

Trong Campus Fabric:

__Fabric Control Plane Node__ - Là LISP MS/MR với các chức năng SDA được tăng cường SDA. Nó quản lý và cung cấp các cài đặt, giao thức và bảng ánh xạ EID-to-RLOC của mạng trục overlay. <br>
__Fabric Border Node__ - Là LISP Proxy Tunnel Router (PxTR) kết nối các mạng Lớp 3 bên ngoài với SD-Access fabric. Nó chuyển đổi thông tin về chính sách và khả năng tiếp cận, chẳng hạn như thông tin SGT và VRF, từ miền này sang miền khác. Có 3 loại: __Internal Border (Rest of Company)__, __Default Border (Outside)__, __Internal + Default Border (Anywhere)__. <br>
__Fabric Edge Node__ - Là router/switch access layer trong fabric overlay kết nối các điểm cuối có dây với SD-Access fabric. Nó cung cấp các giải pháp tích hợp và di động cho người dùng và thiết bị có dây được kết nối qua mạng, bao gồm cả WLC và AP. <br>
__Fabric Wireless Controller (WLC)__ - Kết nối các điểm cuối và AP không dây với SD-Access fabric. Nó cũng cung cấp các tính năng tích hợp và di động cho người dùng không dây và các điểm cuối được kết nối với SD-Access fabric. <br>
__Intermediate Node__ - Là router/switch trung gian trong underlay. <br>

Khác:

__Virtual Network (VN)__ - VRF. <br>
__Host Pool__ - Edge node quản lý các EID thành Host Pool. <br>
__Scalable Group__ - Là 1 nhóm các điểm cuối có chính sách tương tự và có thể được chỉ định tĩnh hoặc động bằng Cisco ISE. <br>
__Anycast Gateway__ - Chỉ có 1 GW kể cả khi người dùng di động sang các edge node khác. <br>

<h3>SD-Access Key</h3>

![alt text](/docs/CCNP/img/SD-Access-Fabric-Key.png)

![alt text](/docs/CCNP/img/SD-Access-Fabric-Key-Differ.png)

Điểm khác biệt vs mô hình truyền thống:

\- Hỗ trợ trung chuyển giữa L2 L3 <br>
\- Hỗ trợ host mobility, host roamming nhờ vào Anycast GW <br>
\- Hỗ trợ VRF ảo + Security Group Tag (SGT) <br>
\- Tự động tạo Tunnel ảo <br>
\- Không bị ràng buộc giới hạn sơ đồ mạng <br>

<br>

## Software-Defined WAN (SD-WAN)
<br>

![alt text](/docs/CCNP/img/SD-WAN-Architecture-1.png)

SD-WAN được tạo ra để đáp ứng nhu cầu chuyển đổi số, bao gồm:

\- Tự động hóa và điều phối mạng WAN với chi phí và rủi ro thấp hơn. <br>
\- Mở rộng mạng doanh nghiệp lên đám mây công cộng. <br>
\- Trải nghiệm người dùng được tối ưu cho các ứng dụng SaaS. <br>
\- Không phụ thuộc vào WAN. <br>
\- Nâng cao hiệu suất và khả năng hiển thị của ứng dụng. <br>
\- Phân đoạn và mã hóa lưu lượng WAN từ điểm đầu đến điểm cuối. <br>

<h3>SD-WAN Architecture</h3>

![alt text](/docs/CCNP/img/SD-WAN-Architecture.png)

<h3>SD-WAN Solution Components</h3>

Có 4 thành phần chính:

<h4>vManage Network Management System (NMS)</h4>

Là 1 hệ thống quản lý mạng GUI định cấu hình và quản lý toàn bộ giải pháp SD-WAN. Nó cho phép cung cấp tập trung và đơn giản hóa các thay đổi mạng.

<h4>vSmart Controller</h4>

Được coi là bộ não của giải pháp SD-WAN. Bộ điều khiển vSmart có thông tin xác thực được cài đặt sẵn để xác thực các Router SD-WAN trực tuyến và cho phép các thiết bị được xác thực truy cập vào SD-WAN fabric.

Sau khi được xác thực, bộ điều khiển vSmart sẽ thiết lập _tunnel_ _Datagram Transport Layer Security (DTLS)_ vĩnh viễn tới các Router SD-WAN trong SD-WAN fabric. Các _tunnel DTLS_ sẽ thiết lập quan hệ neighbor _Overlay Management Protocol (OMP)_ với mỗi Router SD-WAN. OMP là giao thức định tuyến độc quyền của Cisco nhằm quảng bá các _routes_, _nexthop_, _key_ và _policy_ cần thiết để khởi tạo và duy trì SD-WAN fabric. Bộ điều khiển vSmart xử lý các route OMP học được từ các Router SD-WAN hoặc bộ điều khiển vSmart khác để đánh giá cấu trúc liên kết mạng (_network topology_) và tính toán các route ưu tiên đến mạng đích. Sau đó, nó sẽ broadcasts thông tin về khả năng tiếp cận đã học được từ các tuyến đường tới tất cả các Router SD-WAN trong SD-WAN fabric.

<!-- Tất cả các chính sách mặt phẳng điều khiển trên vManager, chẳng hạn như chuỗi dịch vụ (_service chaining_), kỹ thuật lưu lượng (_traffic engineering_) và phân đoạn theo cấu trúc liên kết VPN (_segmentation per VPN_), đều được triển khai bởi bộ điều khiển vSmart. Ví dụ: nếu chính sách được định cấu hình trên vQuản lý cho một ứng dụng yêu cầu mức mất ít hơn 1% và độ trễ 150 ms thì chính sách đó sẽ được tải xuống bộ điều khiển vSmart. -->

<!-- vSmart sẽ huyển chính sách sang định dạng mà tất cả Router SD-WAN trong hệ thống có thể hiểu được và tự động thực thi. -->Bộ điều khiển vSmart làm việc với bộ điều phối vBond để xác thực các thiết bị mới tham gia mạng và điều phối kết nối giữa các bộ định tuyến SD-WAN.

<h4>SD-WAN Routers (vEdge and cEdge)</h4>

Là thiết bị có sẵn dưới dạng bộ định tuyến phần cứng, phần mềm, đám mây và ảo hóa nằm ở khuông viên của site. Cung cấp các tính năng WAN, bảo mật và đa đám mây (multi-cloud) cơ bản của giải pháp Cisco SD-WAN.

cEdge khác với vEdge là do Cisco custom.

vEdge: Phần mềm Viptela chạy trên nền tảng Viptela gốc. <br>
cEdge: Cisco IOS-XE tích hợp phần mềm Viptela. Các nền tảng CSR, ISR, ASR1K, ENCS, CSRv và ISRv hỗ trợ tích hợp Cisco IOS XE SD-WAN.

<h4>vBond Orchestrator</h4>

Bộ điều phối vBond là thiết bị chịu trách nhiệm xác thực và điều phối kết nối giữa bộ điều khiển vSmart và Router SD-WAN. Đây là thiết bị duy nhất trong mạng yêu cầu địa chỉ IP công cộng để tất cả các thiết bị SD-WAN kết nối với nó.

<br>

<h3> Một vài khái niệm khác </h3>

Trong giải pháp Cisco Viptela SDWAN, __OMP (Overlay Management Protocol)__ là một giao thức mới, được giới thiệu như là trái tim của mạng ảo trung chuyển overlay. OMP là một giao thức chạy bên trong các đường hầm TLS hoặc DTLS giữa router vEdge và vSmart controller. OMP là một giao thức điều khiển được dùng để trao đổi các thông tin định tuyến, chính sách và các thông tin quản trị giữa vSmart controller và vEdge router.

Mặc định, giao thức OMP được bật lên, vì vậy bạn không cần cấu hình cho phép giao thức này trên vEdge và vSmart. Khi các thiết bị đã xác thực với nhau xong, các đường hầm DTLS và TLS sẽ được tạo ra, ngay sau đó giao thức OMP sẽ thiết lập các quan hệ láng giềng giữa hai thiết bị và trao đổi các thông tin định tuyến.

OMP quảng bá ba kiểu route sau: OMP Route, TLOC và Service Routes

__OMP routes hay vRoute__: OMP thu thập các thông tin route từ site nội bộ, bao gồm các route dạng connected, static, OSPF và BGP. Các route này sẽ được quảng báo tới vSmart controller cùng với các thuộc tính sau:

__TLOC__: nó chỉ ra giá trị next-hop của vRoute. Thuộc tính này tương tự như BGP next-hop. TLOC là một tập hợp gồm ba giá trị {systemIP, Color, Encapsulation}. Trong đó system IP là địa chỉ của router OMP gửi ra các cập nhật OMP route. Color chỉ ra kiểu kết nối. Encapsulation chỉ ra kiểu đường hầm của lớp transport.

__Service Routes__: các route dạng này tượng trưng cho các dịch vụ kết nối vào vEdge router hay tới các mạng nội bộ mà vEdge có kết nối vào. Các vEdge router sẽ quảng báo các route này tới vSmart controller dùng các họ địa chỉ NLRI.

__Configure VPN__: Đối với các thiết bị SD-WAN Cisco IOS XE Catalyst:

   - __VPN 0—Transport VPN__: control traffic
   - __VPN 512—Management VPN__: out-of-band network management traffic
   - __VPNs 1–511, 513–65530—Service VPNs__: service-side data traffic

<br>


