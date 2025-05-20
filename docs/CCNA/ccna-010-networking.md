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

<h3> why? </h3>
Do nhu cầu chia sẻ thông tin, khoảng cách xa, nhanh chóng, hiệu quả.

<h3> what? </h3>
2 hay nhiều thiết bị __kết nối__ với nhau + __chia sẻ__ dữ liệu cho nhau. => Gọi là 1 hệ thống mạng.

Tên gọi 1 số mạng phổ biến: <br>
\- __LAN (Local Area Network)__: Mạng cục bộ <br>
\- __SOHO (small office/home office) LAN__ điển hình bao gồm PCs, máy in, bộ chuyển mạch, bộ định tuyến và cáp kết nối tất cả các thiết bị này với nhau. <br>
\- __PAN (Personal Area Network)__: Mạng cá nhân <br>
\- __MAN (Metropolitan Area Network)__: Mạng đô thị <br>
\- __WAN (Wide Area Network)__: Mạng diện rộng <br>
\- __WLAN (Wireless Local Area Network)__: Mạng cục bộ không dây

<h3> how? </h3>
Hiện tại mạng sẽ hoạt động đúng chính xác vì các thiết bị và phần mềm tuân thủ theo các nguyên tắc. Những nguyên tắc là các __chuẩn__, __giao thức__ và __mô hình__; được thỏa thuận cách mà mạng sẽ hoạt động.

## Các thành phần mạng

Cơ bản sẽ có:
- máy tính + cáp + switch + router.

| <img src="/docs/CCNA/img/networking-pc-pc.png" style="max-width: 100%; width: 600px" /> | 1 máy tính kết nối 1 máy tính. Ta có 1 mạng. |
| <img src="/docs/CCNA/img/networking-3pc.png" style="max-width: 100%; width: 600px" /> | 3 máy tính kết nối với nhau. Cần gắn mỗi máy tính thêm 1 card mạng. Nhiều máy tính hơn sẽ không khả thi. |
| <img src="/docs/CCNA/img/networking-3pc-1switch.png" style="max-width: 100%; width: 600px" /> | Kết nối thông qua switch. Switch có nhiều port. |
| <img src="/docs/CCNA/img/networking-more-pc-more-switch.png" style="max-width: 100%; width: 600px" /> | Mạng nhiều máy tính và nhiều switch. Tiêu tốn tài nguyên (băng thông) và rủi ro bảo mật (1 máy tính tấn công netcut sẽ làm down toàn bộ mạng). |
| <img src="/docs/CCNA/img/networking-more-pc-more-switch-1router.png" style="max-width: 100%; width: 600px" /> | Router chia 1 vùng mạng lớn thành nhiều vùng mạng nhỏ hơn. |

## Các đặc điểm mạng cơ bản

__Tốc độ (speed)__ <br>
Đảm bảo các thành phần đều hỗ trợ tốc độ mong muốn (ví dụ hình là 1 Gbps) <br>
\- Cáp 1000BASE‑T <br>
\- Card mạng trên máy tính hỗ trợ tốc độ 1 Gbps <br>
\- Modem và thiết bị di động hỗ trợ chuẩn 802.11 ac <br>

__Chi phí (cost)__ <br>
Chia thành 3 nhóm <br>
\- Chi phí triển khai ban đầu <br>
\- Chi phí duy trì hạ tầng mạng <br>
\- Chi phí bảo trì, bảo dưỡng, nâng cấp hệ thống mạng <br>

__Bảo mật (security)__ <br>
\- Tính năng bảo mật trên switch (port security, dhcp snooping..) <br>
\- Firewall (Chặn lọc nội dung, chống chọi trước tấn công dos/ddos..) <br>
\- Sử dụng giao thức truyền thông tin cậy (SSH, SFTP, HTTPS..) <br>
\- Confidentiality (Tính bảo mật của thông tin), Integrity (Tính toàn vẹn thông tin), Availability (Tính sẵn sàng của hệ thống) <br>

__Tính sẵn sàng (availability)__ <br>
Đảm bảo kết nối internet. Thuê ít nhất 2 kết nối mạng từ 2 nhà cung cấp dịch vụ mạng khác nhau. <br>

__Khả năng mở rộng (scalability)__ <br>
Đầu tư những dòng thiết bị hiệu năng cao, khả năng phục vụ nhiều người dùng. Không cần tính toán lại hay loại bỏ thiết bị cũ để thay thiết bị mới. <br>

## Các mô hình mạng

<h3> why? </h3>
Do cần có 1 khung tham chiếu chung để các nhà sản xuất thiết bị mạng thiết kế và phát triển các sản phẩm tương thích với nhau.

<h3> what? </h3>

Có 2 mô hình:
- __TCP/IP - Transmission Control Protocol/Internet Protocol Model__
- __OSI - Open Standard Interconnection Model__

TCP/IP được phát triển ở Mỹ bởi Cerf và Kahn, để xây dựng 1 bộ giao thức truyền thông có khả năng kết nối các mạng khác nhau. Song song, OSI được phát triển ở châu âu bởi Tổ chức Tiêu chuẩn hóa Quốc tế ISO, nhằm tạo ra 1 khung chuẩn hoá toàn diện để giúp các hệ thống với công nghệ khác nhau có thể giao tiếp được, cung cấp 1 khung lý thuyết rõ ràng nhằm phân chia chức năng và tăng tính tương tác giữa các thành phần hệ thống.

TCP/IP có lợi thế về thực nghiệm khi đã chứng minh hiệu quả qua việc triển khai thực tế. OSI là 1 mô hình lý thuyết, chuẩn hóa theo từng tầng, mặc dù chi tiết và hữu ích trong giảng dạy và tư duy về cấu trúc mạng, nhưng khó và chậm triển khai. Kết quả TCP/IP đã giành chiến thắng về mặt ứng dụng và được áp dụng rộng rãi.

### Mô hình TCP/IP

TCP/IP định nghĩa các giao thức bằng cách sử dụng các tài liệu RFC (Requests For Comments) hoặc tránh các giao thức có sẵn như tham chiếu đến IEEE (Institute of Electrical and Electronic Engineers ).

| <img src="/docs/CCNA/img/networking-tcp-ip-model.png" style="max-width: 100%; width: 200px" /> | Tầng Physical truyền các bit qua các liên kết. Tầng Data Link chỉ rõ cách gửi dữ liệu qua từng loại liên kết vật lý (ví dụ: Ethernet LAN hay Wireless LAN). Tầng Network truyền dữ liệu toàn trình từ máy tính gửi đến máy tính đích. 2 tầng trên cùng làm việc với các ứng dụng cần gửi và nhận dữ liệu. |

1 số giao thức TCP/IP tương ứng các tầng của mô hình như bảng dưới.<br>
<img src="/docs/CCNA/img/networking-tcp-ip-model-and-example-protocols.png" style="max-width: 100%; width: 600px" />

Hoạt động của giao thức HTTP:

| <img src="/docs/CCNA/img/networking-tcp-ip-application-layer.png" style="max-width: 100%; width: 280px" /> | __TCP/IP application layer__<br>Tầng ứng dụng không định nghĩa ứng dụng, mà định nghĩa dịch vụ mà ứng dụng cần. Như ví dụ, HTTP định nghĩa cách mà trình duyệt web lấy nội dung trang web từ web server.<br><br>(1) PC gửi yêu cầu "GET http://larry.com/home.htm".<br>(2) Server gửi phản hồi "200 OK home.htm".<br>(3) Các phần còn lại của nội dung file "home.htm" được chia nhỏ gửi tiếp theo sau. |
| <img src="/docs/CCNA/img/networking-tcp-ip-transport-layer.png" style="max-width: 100%; width: 345px" /> | __TCP/IP transport layer__<br>Tầng vận chuyển sử dụng 2 giao thức phổ biến là TCP (Transmission Control Protocol) và UDP (User Datagram Protocol). TCP cung cấp cơ chế truyền thông tin cậy, nhờ tính năng phục hồi lỗi bằng cách gửi lại.<br><br>(1)->(3) TCP header có trường thứ tự SEQ mỗi message.<br> (4) PC không nhận được message số 2 sẽ yêu cầu server gửi lại. |
| <img src="/docs/CCNA/img/networking-tcp-ip-network-layer.png" style="max-width: 100%; width: 1000px" /> | __TCP/IP network layer__<br>Tầng mạng có 1 giao thức lớn là IP. IP cung cấp tính năng định địa chỉ và định tuyến (có thể hiểu tương đương với dịch vụ bưu chính).<br><br>(1) Server gửi gói đến R1 là router gần nhất (tương đương gửi gói hàng đến bưu cục gần nhất). Server không biết topo của các router.<br>(2) R1 nhận được gói, R1 nhìn vào ip đích là 2.2.2.2, đưa ra quyết định chuyển tiếp dựa vào định tuyến ip. Kết quả là gửi đến R2.<br>(3) R2 làm công việc tương tự R1, R2 gửi gói đến PC do trong cùng mạng LAN. |
| <img src="/docs/CCNA/img/networking-tcp-ip-datalink-and-physical-layer.png" style="max-width: 100%; width: 1000px" /> | __TCP/IP data-link and physical layer__<br>Tầng liên kết dữ liệu và tầng vật lý định nghĩa các giao thức và phần cứng cần thiết để truyền dữ liệu qua 1 mạng vật lý. 2 tầng này hoạt động chặt chẽ cùng nhau. Tầng vật lý quy định về hệ thống cáp, năng lượng và các tín hiệu điện. Có một số quy tắc và chuẩn khi gửi dữ liệu qua cáp, các quy tắc đó thuộc về tầng liên kết dữ liệu.<br><br>(1) IP packet được đóng gói vào giữa Ethernet header và Ethernet trailer, gọi là 1 Ethernet frame.<br>(2) Frame được chuyển thành các bits và sử dụng tín hiệu điện để chuyền trên cáp ethernet.<br>(3) R1 nhận được tín hiệu điện trên cáp và tái tạo lại thành các bits giống máy gửi.<br>(4) R1 mở gói IP bằng cách bỏ đi Ethernet header và Ethernet trailer. |

Hình dưới là tóm tắt quá trình encapsulation. Các từ __Segment__, __Packet__, và __Frame__ thường dùng để chỉ các thông điệp tương ứng các tầng.

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
