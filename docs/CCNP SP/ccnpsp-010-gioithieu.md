---
layout: default
title: SPCOR + SPRI Introduction
nav_order: 10
parent: CCNP SP
---

# SPCOR + SPRI Introduction
{: .no_toc }

Giới thiệu
{: .fs-6 .fw-300 }

---

## TABLE OF CONTENTS
{: .no_toc .text-delta }

1. TOC
{:toc}

---

## SPCOR - Implementing and Operating Cisco Service Provider Network Core Technologies

- Network and Software Architectures (Service Provider Network Architect + Cisco IOS Software Architect)
- SP Routing (OSPF, IS-IS, BGP, Route-policy, IPv6, Multicast)
- MPLS and Segment Routing (MPLS LDP, MPLS Traffic-Engineering, Segment Routing)
- L2VPN and L3VPN Service
- QoS Architecture and Implementation (Classifying, Marking, Queuing,…)
- Security Architecture and Implementation (Control Plane, Management Plane, Data Plane Security)
- Automation and Assurance (Network Programmability, Cisco NSO)

## SPRI - Implementing Cisco Service Provider Advanced Routing Solutions

- Implementing and Verifying Dynamic Routing (OSPF Multiarea, IS-IS Multilevel, BGP Security)
- Implementing MPLS and Segment Routing (MPLS LDP, MPLS Traffic Engineering, Segment Routing, Segment Routing Traffic Engineering)
- Service Provider Multicast (PIM-SM, PIM-SSM, Interdomain Multicast)

## Mô tả về kiến trúc Service Provider Network

<img src="/docs/CCNA/img/whvt_1.png" style="max-width: 100%; width: 1500px" />
<h3> W-Why? </h3>
Là 1 SP - Service Provider. Thì cần có quy hoạch và thiết kế ban đầu.

<h3> H-How? </h3>
Ta thường có 1 quy hoạch chung như sau:

| **Service Provider Core Architectures**   | **Modern Service Provider**                           |
| **MPLS Introduction**                     | **MPLS / Unified MPLS / Segment Routing Architect**   |
| **Network Transport Technologies**        | **DWDM & ROADM, Carrier Ethernet**                    |
| **RAN Introduction**                      | **2G/3G/4G/EPC**                                      |

### Modern Service Provider

Service provider là 1 mạng rất là lớn. truyền tải rất nhiều và tất cả loại hình dịch vụ (internet, iptv, voice, mobility..) tại cùng 1 thời điểm. Loại hình dịch vụ có thể chia là **ip** và **non-ip**.

<img src="/docs/CCNP SP/img/Traditional Telephone companies (Telcos) and ISPs.png" style="max-width: 100%; width: 800px" />

Bên trái là mạng **Telco truyền thống**: Gồm nhiều thiết bị để cung cấp dịch vụ: ATM switch → VPN; TDM switch → Thoại; SONET/SDH → Truyền tải ATM và TDM; Router → Internet  
Ưu: QoS tốt, dịch vụ đa dạng (Internet, VPN, Thoại)  
Nhược: Nhiều công nghệ → tốn kém, dịch vụ đắt  

Bên phải là mạng **ISP truyền thống**: Ban đầu chỉ có Internet (chạy IP).  
Ưu: Đơn giản, chi phí thấp, giá cạnh tranh  
Nhược: Chỉ có Internet, không có VPN/dịch vụ khác  

**Kết luận: Cần có mô hình Modern Service Provider:**
- Sử dụng hạ tầng IP-based.  
- Hỗ trợ nhiều dịch vụ: Internet, VPN, Thoại, QoS.  
- Giá cả cạnh tranh.  
- Bổ sung thêm các công nghệ mới: WDM, GPON, Wireless..

**Cisco IP Next-Generation Network (IP NGN)** là kiến trúc thế hệ mới, được thiết kế để cung cấp các dịch vụ thoại, video, di động, và dịch vụ đám mây hoặc dịch vụ quản lý cho người dùng. Ý tưởng của Cisco IP NGN là cung cấp hạ tầng truyền tải **all-IP** cho mọi dịch vụ và ứng dụng, bất kể loại truy nhập nào. **→ Thiết bị phải hỗ trợ MPLS.**

### MPLS

**MPLS** đóng gói 1 header trung gian **giữa L3 và L2**, thường gọi là L2.5. Con đường chuyển mạch bằng nhãn gọi là **Label-Switched Path (LSP)**. **Payload** có thể là bất kỳ giao thức Layer 3, thậm chí cả Layer 2.  

**Đặc điểm:**
- Có thể đóng gói cả payload IP và **non-IP**.
- Chuyển tiếp dựa trên lookup **nhãn (label)** thay vì lookup routing, không phụ thuộc vào payload.
- Mỗi mạng đích sẽ có 1 nhãn tương ứng trên mỗi router được kích hoạt MPLS.
- Chỉ các router ở **rìa miền MPLS (edge routers)** mới thực hiện lookup routing, các router lõi chỉ forward theo nhãn.
- Việc chuyển tiếp bằng nhãn MPLS **không nhanh hơn quá nhiều so với định tuyến IP**, nhưng MPLS có ưu điểm là hỗ trợ chuyển tiếp cả các giao thức **non-IP**, hữu ích trong các mạng nhà cung cấp nhiều dịch vụ.


### Unified MPLS

Thách thức của MPLS: Nhà mạng thường chia nhỏ thành nhiều miền IGP khác nhau (để hạn chế lỗi và tăng tốc độ hội tụ). Dẫn đến khó duy trì LSP xuyên miền vì IGP không đủ khả năng mở rộng.

<img src="/docs/CCNP SP/img/Unified MPLS Multiple IGP Islands.png" style="max-width: 100%; width: 600px" />

**Unified MPLS** là công nghệ tận dụng MPLS hiện có, đồng thời bổ sung khả năng nhận diện lưu lượng chỉ bằng 1 nhãn duy nhất có thể mở rộng qua nhiều miền IGP trong mạng của nhà cung cấp dịch vụ. Bên trong mỗi miền IGP, **LDP** được dùng để phân phối nhãn và xây dựng các **Intra-domain LSPs**. Giữa các miềm IGP, dùng **BGP mang nhãn** hay **BGP-labeled unicast (RFC 3107)** làm giao thức phân phối nhãn liên miền, để xây dựng các **Inter-domain LSPs** xuyên qua nhiều miền IGP.  

→ Quy trình này cho phép cơ sở dữ liệu trạng thái liên kết (link-state database) của mỗi miền độc lập vẫn duy trì ở mức nhỏ nhất, trong khi toàn bộ thông tin kết nối bên ngoài sẽ do **BGP** mang, vốn được thiết kế để mở rộng đến hàng triệu route.

Khi bật RFC 3107 trên cả 2 router BGP, các router sẽ quảng bá cho nhau rằng chúng có thể gửi kèm nhãn MPLS với các route. Nếu 2 router đàm phán thành công khả năng gửi nhãn MPLS, thì chúng sẽ thêm nhãn MPLS vào tất cả các BGP update gửi đi.  

**Nguyên lý hoạt động**:  
- Router trong miền → forward bằng nhãn **LDP**.  
- Đến sát border router → nhãn LDP bị **pop**, để lộ nhãn **BGP**.  
- Border router dựa vào nhãn BGP để định tuyến sang miền kế tiếp, rồi **prepend** nhãn LDP mới của miền đó. 

<img src="/docs/CCNP SP/img/Unified MPLS Inter-domain LSPs.png" style="max-width: 100%; width: 600px" />

### Segment Routing (SR)

Segment Routing là 1 công nghệ **source routing**, trong đó đường đi được nguồn mã hóa trong header gói tin như 1 **danh sách các segment**.  

SR chạy trên hạ tầng MPLS, cho phép xác định đường đi chính xác hơn, không cần LDP/RSVP/BGP-LU.  

**Segment:**  
- **Global Segment**: Có giá trị toàn miền, nhận diện bằng **SID**.  
- **Local Segment**: Chỉ có ý nghĩa trên router gán, thường đại diện cho link hoặc đường thay thế.  

Các nhãn segment (SR labels) được phân phối bởi **IGP**. <br> <br>

<img src="/docs/CCNP SP/img/Segment Routing.png" style="max-width: 100%; width: 600px" />

**Hoạt động**  
- Stack nhãn [R3] → đi đến R3 theo IGP.  
- Stack nhãn [R4 \| R3] → đi qua R4 trước khi tới R3.  
- Stack nhãn [R2 \| link local R2-R4 \| R3] → đi qua R2 và qua link cục bộ R2-R4; khi tới R4, nó tự tìm đường ngắn nhất đến R3.  

### Carrier Ethernet Services

Kết nối CE (Customer Edge) từ khách hàng doanh nghiệp hoặc hộ gia đình sẽ kết thúc tại thiết bị CE (router hoặc switch). CE kết nối đến **user-network interface (UNI)**, thường qua cổng Ethernet chuẩn 10/100/1000 Mbps hoặc 10 Gbps.  

Trong mạng WAN của nhà cung cấp, dịch vụ có thể dựa trên nhiều công nghệ: SONET/SDH, DWDM, Gigabit Ethernet, MPLS,…  

<img src="/docs/CCNP SP/img/Carrier Ethernet Services.png" style="max-width: 100%; width: 400px" />

**Ethernet Virtual Connections (EVCs):** liên kết giữa hai hoặc nhiều UNI.  
- **E-Line**: dựa trên EVC point-to-point.  
- **E-LAN**: dựa trên EVC multipoint-to-multipoint, cho phép service multiplexing (nhiều EVC trên cùng 1 UNI).  
- **E-Tree**: dạng point-to-multipoint, các leaf chỉ giao tiếp với root/hub, không giao tiếp trực tiếp với nhau.  

### DWDM và ROADM

**DWDM**: Ghép nhiều tín hiệu Optical Carrier vào 1 sợi quang bằng các bước sóng laser khác nhau (trong dải 1550 nm).  
Các trạm khuếch đại trung gian có thể **add/drop** một số kênh bước sóng.  
**ROADM**: Phiên bản add/drop quang có khả năng **chuyển mạch từ xa** ở tầng bước sóng. Việc add/drop không ảnh hưởng các kênh pass-through.

<img src="/docs/CCNP SP/img/DWDM and ROADM.png" style="max-width: 100%; width: 500px" />

### IP over DWDM

IP over DWDM (IPoDWDM) là 1 công nghệ tích hợp DWDM trực tiếp trên router, theo chuẩn **ITU-T G.709** để giám sát đường quang.  
Lợi ích: giảm đáng kể chi phí đầu tư (CAPEX), tăng hiệu quả vận hành, bỏ nhu cầu dùng OEO (quang-điện-quang) transponder trong mạng truyền tải.

<img src="/docs/CCNP SP/img/IP over DWDM.png" style="max-width: 100%; width: 400px" />

### Ethernet OAM 

**Operation, Administration, and Maintenance (OAM)** protocols được thiết kế để đáp ứng yêu cầu báo hiệu lỗi (fault indication) và giám sát hiệu năng (performance monitoring) trong các phân đoạn và tầng khác nhau của mạng nhà cung cấp dịch vụ.  

- **IEEE 802.3ah OAM**: Được thiết kế để chạy trên bất kỳ liên kết vật lý nào nhằm giám sát tính toàn vẹn của liên kết. Thường được sử dụng giữa thiết bị CE và PE để xác minh kết nối vật lý Ethernet ở "First Mile" (Ethernet physical connectivity in the First Mile - EFM).  
- **802.1ag Connectivity Fault Management (CFM)**: Quản lý khả năng kết nối end-to-end của 1 dịch vụ Ethernet với nhiều cấp độ miền bảo trì khác nhau.  
- **MPLS OAM**: Được sử dụng trong phần mạng MPLS để giám sát khả năng kết nối của các kênh ảo (virtual circuit).  

### Radio Access Network (RAN)

RAN là phần của mạng di động nằm giữa thiết bị người dùng và mạng lõi, triển khai công nghệ truy nhập vô tuyến. Mạng di động được chia thành các **cell**, mỗi cell có 1 trạm gốc (BTS/NodeB/eNodeB), kết hợp lại để phủ sóng diện rộng, cho phép thiết bị di động liên lạc dù đang di chuyển.  

<img src="/docs/CCNP SP/img/E-UTRAN-4G Mobile Radio Technology.png" style="max-width: 100%; width: 600px" />

**2G – GERAN**
- **BTS**: Truyền/nhận sóng vô tuyến, kết nối với **BSC**.  
- **Tốc độ**: 56–114 Kbps.  

**3G – UTRAN**
- **Node B** và **RNC**: RNC quản lý nhiều Node B.  
- **Tốc độ**: đến 2 Mbps.  

**4G – E-UTRAN (LTE)**
- **eNodeB**: Tích hợp cả truyền dẫn và điều khiển, kiến trúc all-IP.  
- **Tốc độ**: 100 Mbps – 1 Gbps (thường 100–200 Mbps).  

| Feature        | 2G (Early 1990s)        | 3G (Early 2000s)                  | 4G (Late 2000s)                     | 5G (Late 2010s)                                  |
|----------------|-------------------------|-----------------------------------|--------------------------------------|--------------------------------------------------|
| Key Technologies | GSM, CDMA              | UMTS, HSPA, CDMA2000              | LTE, WiMAX                           | NR, mmWave, Massive MIMO, Beamforming            |
| Data Speed     | Up to 64 Kbps           | Up to 2 Mbps                      | Up to 1 Gbps                         | Up to 20 Gbps                                    |
| Voice Quality  | Improved over 1G        | Improved over 2G                  | High quality                         | Very high quality                                |
| Data Services  | Basic SMS, MMS          | Mobile internet, video calls      | HD video streaming, gaming           | Ultra HD streaming, AR/VR applications           |
| Latency        | High                   | Reduced                           | Low                                  | Very low (as low as 1 ms)                        |
| Main Features  | Digital voice, SMS      | Enhanced multimedia, apps         | High-speed internet, VoIP            | Ultra-high speed, ultra-low latency, massive IoT |

