---
layout: default
title: SD-Access và SD-WAN
nav_order: 125
parent: CCNP
---

# SD-Access và SD-WAN
{: .no_toc }

Software-Defined Access và Software-Defined WAN
{: .fs-6 .fw-300 }

---

## Table of contents
{: .no_toc .text-delta }

1. TOC
{:toc}

---

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

<img src="/docs/CCNP/img/SD-WAN-Architecture-1.png" width="800">

SD-WAN được tạo ra để đáp ứng nhu cầu chuyển đổi số, bao gồm:

\- Tự động hóa và điều phối mạng WAN với chi phí và rủi ro thấp hơn. <br>
\- Mở rộng mạng doanh nghiệp lên đám mây công cộng. <br>
\- Trải nghiệm người dùng được tối ưu cho các ứng dụng SaaS. <br>
\- Không phụ thuộc vào WAN. <br>
\- Nâng cao hiệu suất và khả năng hiển thị của ứng dụng. <br>
\- Phân đoạn và mã hóa lưu lượng WAN từ điểm đầu đến điểm cuối. <br>

<h3>SD-WAN Architecture</h3>

<img src="/docs/CCNP/img/SD-WAN-Architecture.png" width="800">

<h3>SD-WAN Solution Components</h3>

Có 4 thành phần chính:

__1\. vBond__

\- Điều phối kết nối giữa management plane, control plane và data plane. <br>
\- Điểm đầu xác thực của tất cả vEdge. <br>
\- Yêu cầu địa chỉ IP public. <br>
\- Hỗ trợ NAT Traversal. <br>
\- Tất cả các thành phần khác đều biết địa chỉ của vBond. <br>
\- Phân phối danh sách các vSmart cho các vEdge để đồng bộ các chính sách. <br>

__2\. vManage__

\- Single pane of glass. Thông suốt từ quá trình lên kế hoạch, triển khai và vận hành. <br>
\- Cảnh báo theo thời gian thực. <br>
\- Tích hợp các thành phần khác một cách tập trung. <br>
\- Chuẩn hóa cấu hình. <br>
\- Đơn giản hóa quá trình triển khai. <br>
\- Đơn giản hóa quá trình thay đổi. <br>
\- Hỗ trợ: REST API, CLI, Syslog, SNMP, NETCONF. <br>

__3\. vSmart__

\- Là bộ não trung tâm của giải pháp. <br>
\- Toàn bộ route sẽ được vEdge quảng bá lên vSmart và sau đó vSmart sẽ phân phối lại. <br>
\- Thiết lập OMP peering đến tất cả vEdge. <br>
\- Thực hiện các chính sách được tạo từ vManage và đẩy xuống vEdge bằng OMP. <br>
\- Phân phối thông tin kết nối giữa các vEdge. Quan trọng là thông tin key để xây dựng IPSec tunnel. <br>

__4\. vEdge__

\- Cung cấp kết nối bảo mật (IPSec tunnel) giữa các vEdge với nhau. <br>
\- Thiết lập bảo mật điều khiển với vSmart bằng OMP. <br>
\- Thực thi các chính sách liên quan đến data plane như qos, permit hay deny.. <br>
\- Xuất ra hiệu suất và thông báo trạng thái lên vManage. <br>
\- Tận dụng và sử dụng các giao thức truyền thống OSPF, BGP, VRRP. <br>
\- Hỗ trợ Zero Touch Deployment. <br>
\- Hỗ trợ kết nối 100Mb, 1Gb, 10Gb. <br>

<h3> Một vài khái niệm khác </h3>

Trong giải pháp Cisco Viptela SDWAN, __OMP (Overlay Management Protocol)__ là một giao thức mới, được giới thiệu như là trái tim của mạng ảo trung chuyển overlay. OMP là một giao thức chạy bên trong các đường hầm TLS hoặc DTLS giữa router vEdge và vSmart controller. OMP là một giao thức điều khiển được dùng để trao đổi các thông tin định tuyến, chính sách và các thông tin quản trị giữa vSmart controller và vEdge router.

Mặc định, giao thức OMP được bật lên, vì vậy bạn không cần cấu hình cho phép giao thức này trên vEdge và vSmart. Khi các thiết bị đã xác thực với nhau xong, các đường hầm DTLS và TLS sẽ được tạo ra, ngay sau đó giao thức OMP sẽ thiết lập các quan hệ láng giềng giữa hai thiết bị và trao đổi các thông tin định tuyến.

<img src="/docs/CCNP/img/SD-WAN-OMP.png" width="700">

OMP quảng bá ba kiểu route sau: OMP Route, TLOC và Service Routes

__OMP routes hay vRoute__: OMP thu thập các thông tin route từ site nội bộ, bao gồm các route dạng connected, static, OSPF và BGP. Các route này sẽ được quảng báo tới vSmart controller cùng với các thuộc tính sau:

__TLOC__: nó chỉ ra giá trị next-hop của vRoute. Thuộc tính này tương tự như BGP next-hop. TLOC là một tập hợp gồm ba giá trị {systemIP, Color, Encapsulation}. Trong đó system IP là địa chỉ của router OMP gửi ra các cập nhật OMP route. Color chỉ ra kiểu kết nối. Encapsulation chỉ ra kiểu đường hầm của lớp transport.

__Service Routes__: các route dạng này tượng trưng cho các dịch vụ kết nối vào vEdge router hay tới các mạng nội bộ mà vEdge có kết nối vào. Các vEdge router sẽ quảng bá các route này tới vSmart controller dùng các họ địa chỉ NLRI.

__Configure VPN__: Đối với các thiết bị SD-WAN Cisco IOS XE Catalyst:

   - __VPN 0—Transport VPN__: control traffic
   - __VPN 512—Management VPN__: out-of-band network management traffic
   - __VPNs 1–511, 513–65530—Service VPNs__: service-side data traffic

<br>


