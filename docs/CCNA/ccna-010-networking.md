---
layout: default
title: Networking
nav_order: 10
parent: CCNA
---

# Networking
{: .no_toc }

Kết nối truyền thông
{: .fs-6 .fw-300 }

---

## TABLE OF CONTENTS
{: .no_toc .text-delta }

1. TOC
{:toc}

---

## Mạng là gì?

<h3> W-Why? </h3>
<img src="/docs/CCNA/img/whvt_1.png" style="max-width: 100%; width: 1500px" />
Tại sao tạo ra mạng? Là **do nhu cầu chia sẻ thông tin, đi được xa, nhanh chóng, hiệu quả**.

Nhưng mạng hoạt động như thế nào?

<h3> H-How? </h3>
<img src="/docs/CCNA/img/voice of the world.png" style="max-width: 100%; width: 1500px" />
Mạng hoạt động đơn giản là **di chuyển dữ liệu từ thiết bị này sang thiết bị khác**. Bản chất của mạng: **Networking = Forwarding**. Đưa dữ liệu **đi đúng nơi cần đến**.

Có **từ 2 thiết bị trở lên**, có **kết nối** và **chia sẻ dữ liệu cho nhau** => Là 1 **hệ thống mạng**.

Tên gọi 1 số loại mạng phổ biến: <br>
\- **LAN (Local Area Network)** – Mạng cục bộ. <br>
\- **SOHO (Small Office/Home Office)** – LAN nhỏ gồm PC, máy in, switch, router, cáp. <br>
\- **PAN (Personal Area Network)** – Mạng cá nhân gồm Bluetooth, USB. <br>
\- **MAN (Metropolitan Area Network)** – Mạng đô thị. <br>
\- **WAN (Wide Area Network)** – Mạng diện rộng. <br>
\- **WLAN (Wireless LAN)** – Mạng cục bộ không dây (Wi-Fi).

Hiện tại mạng sẽ hoạt động đúng chính xác vì các thiết bị và phần mềm tuân thủ theo các quy tắc. Các quy tắc là các **chuẩn (standard)** và **giao thức (protocol)**, là những thỏa thuận cách mà mạng sẽ hoạt động. Tuy nhiên, do số lượng các chuẩn và giao thức là lớn, nên đã tạo ra 1 số mô hình mạng (**OSI**, **TCP/IP**). Các mô hình định nghĩa 1 cấu trúc gồm các lớp chuẩn và giao thức khác nhau, các nhà sản xuất thiết bị mạng sẽ dựa vào và tạo ra các sản phẩm tương thích hoạt động chính xác với nhau.

## Các thành phần mạng cơ bản

<img src="/docs/CCNA/img/whvt_1.png" style="max-width: 100%; width: 1500px" />
Các thành phần mạng cơ bản cơ bản sẽ có:
- **máy tính** + **cáp** + **switch** + **router**.

| <img src="/docs/CCNA/img/networking-pc-pc.png" style="max-width: 100%; width: 600px" /> | 1 máy tính kết nối 1 máy tính. Ta có 1 mạng. |
| <img src="/docs/CCNA/img/networking-3pc.png" style="max-width: 100%; width: 600px" /> | 3 máy tính kết nối với nhau. Cần gắn mỗi máy tính thêm 1 card mạng. Nhiều máy tính hơn sẽ không khả thi. |
| <img src="/docs/CCNA/img/networking-3pc-1switch.png" style="max-width: 100%; width: 600px" /> | Kết nối thông qua switch. Switch có nhiều port. |
| <img src="/docs/CCNA/img/networking-more-pc-more-switch.png" style="max-width: 100%; width: 600px" /> | Mạng nhiều máy tính và nhiều switch. Tiêu tốn tài nguyên (băng thông) và rủi ro bảo mật (1 máy tính tấn công netcut sẽ làm down toàn bộ mạng). |
| <img src="/docs/CCNA/img/networking-more-pc-more-switch-1router.png" style="max-width: 100%; width: 600px" /> | Router chia 1 vùng mạng lớn thành nhiều vùng mạng nhỏ hơn. |

## Các đặc điểm mạng cơ bản

<img src="/docs/CCNA/img/whvt_1.png" style="max-width: 100%; width: 1500px" />
Các đặc điểm mạng cơ bản:

**Tốc độ (Speed)**
- Đảm bảo tất cả thành phần trong mạng hỗ trợ tốc độ mong muốn (ví dụ 1 Gbps).  
  - Cáp: 1000BASE‑T  
  - Card mạng trên máy tính: hỗ trợ 1 Gbps  
  - Modem/router và thiết bị di động: chuẩn Wi‑Fi 802.11ac hoặc cao hơn  

**Chi phí (Cost)**
- Chia thành 3 nhóm:  
  - Triển khai ban đầu: thiết bị, cáp, cấu hình…  
  - Duy trì hạ tầng mạng: điện, thuê dịch vụ, quản lý mạng  
  - Bảo trì, bảo dưỡng, nâng cấp: hệ thống mạng  

**Bảo mật (Security)**
- Switch: port security, DHCP snooping…  
- Firewall: chặn/lọc nội dung, chống DoS/DDoS  
- Giao thức an toàn: SSH, SFTP, HTTPS…  
- Nguyên tắc CIA:  
  - Confidentiality: bảo mật thông tin  
  - Integrity: toàn vẹn dữ liệu  
  - Availability: sẵn sàng dịch vụ  

**Tính sẵn sàng (Availability)**
- Đảm bảo kết nối liên tục; ví dụ thuê ít nhất 2 đường kết nối từ 2 nhà cung cấp khác nhau.  
- Dùng thiết bị có khả năng dự phòng (redundancy); ví dụ thiết bị có 2 card điều khiển hay nhiều module nguồn.

**Khả năng mở rộng (Scalability)**
- Đầu tư thiết bị hiệu năng cao, phục vụ nhiều người dùng.  
- Không cần thay toàn bộ thiết bị khi mở rộng mạng, dễ nâng cấp.


## Các mô hình mạng

<h3> W-Why? </h3>
<img src="/docs/CCNA/img/whvt_1.png" style="max-width: 100%; width: 1500px" />
Như đã nói ở trên. Do cần có 1 khung tham chiếu chung để các nhà sản xuất thiết bị mạng thiết kế và phát triển các sản phẩm tương thích với nhau.

Các mô hình mạng hoạt động như thế nào?

<h3> H-How? </h3>
<img src="/docs/CCNA/img/voice of the world.png" style="max-width: 100%; width: 1500px" />
Có 2 mô hình:
- **OSI - Open Standard Interconnection Model**
- **TCP/IP - Transmission Control Protocol/Internet Protocol Model**

Mặc dù các mô hình mạng độc quyền của nhà cung cấp thường hoạt động tốt, nhưng mong muốn nỗ lực có 1 mô hình mạng mở và trung lập sẽ làm giảm độ phức tạp của mạng. Ở châu âu, Tổ chức Tiêu chuẩn hóa Quốc tế The International Organization for Standardization **ISO đã nhận nhiệm vụ tạo ra mô hình OSI: chuẩn hóa các giao thức mạng dữ liệu để cho phép giao tiếp được giữa tất cả các máy tính trên toàn hành tinh**. ISO có sự tham gia của hầu hết các quốc gia phát triển công nghệ trên trái đất.

Ít chính thức hơn, **xuất phát từ 1 hợp động của Bộ quốc phòng Mỹ**, 1 nỗ lực thứ 2 tạo ra mô hình mạng công cộng và trung lập, **các nhà nghiên cứu tình nguyện của nhiều trường đại học đã phát triển và cho ra đời TCP/IP**.

TCP/IP có lợi thế về thực nghiệm khi đã chứng minh hiệu quả qua việc triển khai thực tế. OSI là 1 mô hình lý thuyết, chuẩn hóa theo từng tầng (7 tầng), mặc dù chi tiết và hữu ích trong giảng dạy và tư duy về cấu trúc mạng, nhưng khó và chậm triển khai. **Kết quả TCP/IP được áp dụng rộng rãi và đã giành chiến thắng về mặt ứng dụng.**

### Mô hình TCP/IP

**TCP/IP vừa định nghĩa** các giao thức bằng cách sử dụng các tài liệu **RFC (Requests For Comments)** **vừa tránh lặp lại** các giao thức có sẵn bằng việc tham chiếu đến **IEEE (Institute of Electrical and Electronic Engineers)**.

| <img src="/docs/CCNA/img/networking-tcp-ip-model.png" style="max-width: 100%; width: 200px" /> | Tầng **Physical** truyền các bit qua các liên kết.<br>Tầng **Data Link** chỉ rõ cách gửi dữ liệu qua từng loại liên kết vật lý (ví dụ: Ethernet LAN hay Wireless LAN).<br>Tầng **Network** truyền dữ liệu toàn trình từ máy tính gửi đến máy tính nhận.<br>2 tầng **Application** và **Transport** làm việc với các ứng dụng cần gửi và nhận dữ liệu. |

1 số giao thức TCP/IP tương ứng các tầng của mô hình như bảng dưới.<br>
<img src="/docs/CCNA/img/networking-tcp-ip-model-and-example-protocols.png" style="max-width: 100%; width: 600px" />

Hoạt động của giao thức HTTP:

| <img src="/docs/CCNA/img/networking-tcp-ip-application-layer.png" style="max-width: 100%; width: 320px" /> | **5. TCP/IP application layer**<br>Tầng ứng dụng cung cấp các dịch vụ cho phần mềm ứng dụng chạy trên máy tính. Như ví dụ, HTTP cung cấp cách mà trình duyệt web lấy nội dung trang web từ web server.<br><br>(1) PC gửi yêu cầu "GET http://larry.com/home.htm".<br>(2) Server gửi phản hồi "200 OK home.htm".<br>(3) Các phần còn lại của nội dung file "home.htm" được chia nhỏ gửi tiếp theo sau. |
| <img src="/docs/CCNA/img/networking-tcp-ip-transport-layer.png" style="max-width: 100%; width: 385px" /> | **4. TCP/IP transport layer**<br>Tầng vận chuyển sử dụng 2 giao thức phổ biến là TCP (Transmission Control Protocol) và UDP (User Datagram Protocol). TCP cung cấp cơ chế truyền thông tin cậy, nhờ tính năng phục hồi lỗi bằng cách gửi lại.<br><br>(1)->(3) TCP header có trường thứ tự SEQ mỗi message.<br> (4) PC không nhận được message có số thứ tự 2 sẽ yêu cầu server gửi lại. |
| <img src="/docs/CCNA/img/networking-tcp-ip-network-layer.png" style="max-width: 100%; width: 1000px" /> | **3. TCP/IP network layer**<br>Tầng mạng có 1 giao thức lớn là IP. IP cung cấp tính năng định địa chỉ và định tuyến (có thể hiểu tương đương với dịch vụ bưu chính). IP là địa chỉ duy nhất để nhận dạng 1 thiết bị TCP/IP trong mạng. Định tuyến IP là chuyển tiếp gói tin IP từ thiết bị này sang thiết bị khác.<br><br>(1) Server gửi gói đến R1 là router gần nhất (tương đương gửi gói hàng đến bưu cục gần nhất). Server không biết topo của các router.<br>(2) R1 nhận được gói, R1 nhìn vào ip đích là 2.2.2.2, đưa ra quyết định chuyển tiếp dựa vào định tuyến ip. Kết quả là gửi đến R2.<br>(3) R2 làm công việc tương tự R1, R2 gửi gói đến PC do trong cùng mạng LAN. |
| <img src="/docs/CCNA/img/networking-tcp-ip-datalink-and-physical-layer.png" style="max-width: 100%; width: 1000px" /> | **1&2. TCP/IP data-link and physical layer**<br>Tầng liên kết dữ liệu và tầng vật lý định nghĩa các giao thức và phần cứng cần thiết để truyền dữ liệu qua 1 mạng vật lý. 2 tầng này hoạt động chặt chẽ cùng nhau. Tầng vật lý quy định về hệ thống cáp, năng lượng và các tín hiệu điện. Có một số quy tắc và chuẩn khi gửi dữ liệu qua cáp, các quy tắc đó thuộc về tầng liên kết dữ liệu.<br><br>(1) IP packet được đóng gói vào giữa Ethernet header và Ethernet trailer, gọi là 1 Ethernet frame.<br>(2) Frame được chuyển thành các bits và sử dụng tín hiệu điện để truyền trên cáp Ethernet.<br>(3) R1 nhận được tín hiệu điện trên cáp và tái tạo lại thành các bits giống máy gửi.<br>(4) R1 mở gói IP bằng cách bỏ đi Ethernet header và Ethernet trailer. |

**Thuật ngữ đóng gói (encapsulation) đề cập đến quá trình đặt phần tiêu đề (header) thường là lên đầu dữ liệu.** Hình dưới là tóm tắt quá trình encapsulation. Các từ **Segment**, **Packet**, và **Frame** thường dùng để chỉ các thông điệp tương ứng các tầng.

<img src="/docs/CCNA/img/networking-tcp-ip-encapsulation.png" style="max-width: 100%; width: 500px" />

### Mô hình OSI

Open Standard Interconnection (OSI) Model là một sự chuẩn hóa cho những chức năng trong hệ thống mạng. Chức năng của mô hình là giúp cho tính phức tạp của mạng trở nên đơn giản hơn, cho phép các nhà phát triển module hóa việc thiết kế. Phương pháp này cho phép nhiều nhà phát triển làm việc độc lập nhau để tạo ra những chức năng riêng biệt mà vẫn có thể hòa hợp thành một thể thống nhất một cách dễ dàng (plug-and-play). Ngoài ra mô hình còn giúp cho những quản trị viên có thể hình tượng hóa quá trình trao đổi dữ liệu giữa các máy tính để hiểu được hoạt động của hệ thống mạng một cách tường minh hơn.

Mô hình OSI tương đồng với mô hình TCP/IP, có các tầng và mỗi tầng định nghĩa một tập hợp các chức năng mạng điển hình. Giống như TCP/IP, mỗi tầng trong mô hình OSI cũng liên quan đến nhiều giao thức và tiêu chuẩn được sử dụng để thực hiện các chức năng mà tầng đó quy định.

<img src="/docs/CCNA/img/networking-osi-model-compare-to-tcp-ip-model.png" style="max-width: 100%; width: 350px" />

Mô hình OSI bao gồm 7 lớp:

| **7. Application** | Giao diện giữa người dùng và mạng. Cung cấp dịch vụ mạng cho ứng dụng. | HTTP, FTP, SMTP, Telnet |
| **6. Presentation** | Xử lý định dạng dữ liệu: mã hóa, giải mã, nén, chuyển đổi ký tự. | ASCII, JPEG, MPEG |
| **5. Session** | Thiết lập, duy trì, đồng bộ và kết thúc phiên giao tiếp. | NetBIOS, RPC |
| **4. Transport** | Đảm bảo truyền dữ liệu đáng tin cậy, phân mảnh và tái tổ hợp dữ liệu. | TCP, UDP |
| **3. Network** | Định tuyến, gán địa chỉ IP, gửi gói qua các mạng trung gian. | IPv4, IPv6, OSPF, RIP |
| **2. Data Link** | Truyền dữ liệu qua liên kết vật lý, kiểm soát lỗi và địa chỉ MAC. | Ethernet, PPP, VLAN, ARP |
| **1. Physical** | Truyền bit qua phương tiện vật lý: cáp, tín hiệu, điện áp. | RJ45, Fiber, DSL, V.35 |
