---
layout: default
title: _
nav_order: 0
parent: CCNP
---

https://stucknactive.com/

### 1.2 Enterprise Network Infrastructure (Kiến trúc mạng doanh nghiệp) <br>
\- _The enterprise campus_: Thường được thiết kế sử dụng mô hình phân cấp: _core, distribution, access_ <br>
\- _The enterprise edge_: Cơ bản là mở rộng truy cập đến chi nhánh, nhân viên làm việc từ xa <br>

### 1.3 Role of Dynamic Routing Protocols (Vai trò của giao thức định tuyến động) <br>
\- Y/c quan trọng đối vs giao thức định tuyến là tự động _thích nghi nhanh vs sự thay đổi_ và _chọn đường đi tốt nhất_ <br>
\- Thiết bị chạy giao thức định tuyến động sẽ thoả hiệp lẫn nhau và trao đổi thông tin tiếp cận được <br>
\- Lý tưởng nhất là chạy một IGP duy nhất -> Giảm thiểu sự phức tạp vận hành, cấu hình sai, đường đi không tối ưu, vòng lặp, lỗ đen <br>

### 1.4 Choosing the Optimal Routing Protocol (Chọn ra giao thức định tuyến tối ưu) <br>
\+ Theo yêu cầu: <br>
\-- Kích thước của mạng <br>
\-- Số lượng vendor <br>
\-- Trình độ chuyên môn <br>
\-- Dễ vận hành <br>
\-- Dễ sửa chửa <br>
\+ Theo đặc điểm giao thức: <br>
\-- Thuật toán <br>
\-- Tốc độ hội tụ <br>
\-- Khả năng mở rộng <br>
\-- Tính sẵn sàng <br>
\-- Bảo mật <br>
\-- Tài nguyên và chi phí tiêu tốn <br>

### 1.5 IGP vs. EGP <br>
\- Autonomous System Numbers (ASN or AS): BGP Public AS range = 1 – 64,511 (đăng ký bởi IANA); Private AS range = 64,512 – 65,535 <br>
\- IGP hoạt động bên trong 1 AS, EGP hoạt động giữa các AS

### 1.6 Types of Routing Protocols (Các loại giao thức định tuyến)<br>
\- Distance Vector: RIPv2, EIGRP <br>
\- Link State: OSPF, IS-IS <br>
\- Path Vector: BGP <br>

### 1.7 Convergence (Hội tụ) <br>
Hội tụ là quá trình các bộ định tuyến nhận ra thay đổi, liên lạc thông báo, tính toán lại, ổn định mạng <br>
\+ Giảm thời gian hội tụ: <br>
\-- Giảm thời gian hello <br>
\-- Summary route <br>
\-- Route Flap Dampening <br>
\-- Bi-Directional Forwarding Detection (BFD), Stateful Switch Over (SSO), Graceful Restart (NSF), BGP Fast Re-Route (FRR), and BGP Prefix Independent Convergence (PIC) <br>

### 1.10 Traffic Types (các loại lưu lượng) <br>
\- Unicast (IPv4 and IPv6) 1:1 <br>
\- Broadcast (IPv4 only) 1:many Local Broadcast -> 255.255.255.255, Directed Broadcast -> 192.168.1.255 <br>
\- Multicast (IPv4 and IPv6) 1:group <br>
\- Anycast (IPv6 only) 1:many <br>

### 1.12 Network Types (các loại mạng) <br>
\- Point-to-Point 1:1 <br>
\- Broadcast  <br>
\- NBMA: Non-broadcast, Multiple Access <br>

### 1.12 Network Types (các loại mạng) <br>
\- Point-to-Point 1:1 <br>
\- Broadcast  <br>
\- NBMA: Non-broadcast, Multiple Access <br>
\-- Hub and Spoke <br>
\-- Full Mesh <br>
\-- Partial Mesh <br>

### 1.14 Routing over the Internet (Định tuyến qua mạng) <br>
\+ Nhu cầu: <br>
\-- Dự phòng cao <br>
\-- Băng thông lớn (phụ thuộc) <br>
\-- Rẻ <br>
\+ Thách thức: <br>
\-- Router không được kết nối trực tiếp <br>
\-- Y/c Public IP <br>
\-- Khả năng mở rộng <br>
\-- Không an toàn <br>
\-- Không có qos đảm bảo chất lượng dịch vụ <br>
\+ Giải pháp: tunnel, vpn<br>

### 1.15 Routing Across MPLS VPNs (Định tuyến qua MPLS VPNs) <br>
\+ Nhu cầu: <br>
\-- Dự phòng cao <br>
\-- Băng thông lớn (phụ thuộc) <br>
\-- Rẻ <br>
\+ Thách thức: <br>
\-- Router không được kết nối trực tiếp <br>
\-- Y/c Public IP <br>
\-- Khả năng mở rộng <br>
\-- Không an toàn <br>
\-- Không có qos đảm bảo chất lượng dịch vụ <br>
\+ Giải pháp: tunnel, vpn <br>

### 1.16 VPN <br>
\+ MPLS VPNs _ ISP sử dụng nhãn để phân phối trong core <br>
\-- L3 MPLS _ Sử dụng MP-BGP để truyền <br>
\-- L2 MPLS _ Sử dụng pseudowire <br>
\--\-- VPWS (Virtual Private Wire Service) _ point-to-point L2 MPLS tương tự leased line <br>
\--\-- VPLS (Virtual Private LAN Service) _ point-to-multipoint L2 MPLS tương tự môi trường ethernet (tương tự switch) <br>
\+ Tunneling VPNs _ Đóng gói lưu lượng trong một giao thức mang <br>
\-- GRE <br>
\-- IPsec <br>
\-- DMVPN (Dynamic Multipoint VPN) <br>
\+ Hybrid VPNs <br>









