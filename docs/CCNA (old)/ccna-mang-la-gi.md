---
layout: default
title: Mạng là gì?
nav_order: 0
parent: CCNA (old)
---

# What is Network?
{: .no_toc }

Mạng là gì?
{: .fs-6 .fw-300 }

---

## TABLE OF CONTENTS
{: .no_toc .text-delta }

1. TOC
{:toc}

---

## Tại sao có mạng? (why?)
<br>
Nhu cầu chia sẻ thông tin, khoảng cách xa, nhanh chóng, hiệu quả.

## Mạng là gì? (what?)
<br>
2 dấu hiệu nhận biết: <br>
\- 2 hay nhiều thiết bị kết nối với nhau <br>
\- Truyền thông, chia sẻ dữ liệu cho nhau <br>
=> Gọi là 1 hệ thống mạng <br>

![](/docs/CCNA (old)/img/network.png)

![](/docs/CCNA (old)/img/network_1.png)

## Mạng ở đâu? Các loại mạng phổ biến (where?)
<br>
___LAN (Local Area Network)___: Mạng cục bộ <br>
\- Mạng LAN _SOHO (small office/home office)_ điển hình bao gồm PCs, máy in, bộ chuyển mạch, bộ định tuyến và cáp kết nối tất cả các thiết bị này với nhau. <br>
___PAN (Personal Area Network)___: Mạng cá nhân <br>
___MAN (Metropolitan Area Network)___: Mạng đô thị <br>
___WAN (Wide Area Network)___: Mạng diện rộng <br>
___WLAN (Wireless Local Area Network)___: Mạng cục bộ không dây <br>

## Thành phần cơ bản (components? who?)
<br>
\- Máy tính <br>
\- Switch <br>
\- Router <br>
\- Cáp truyền dẫn <br>

![](/docs/CCNA (old)/img/network_2.png)

Khảo sát tình huống 2 máy tính kết nối với nhau, không qua thiết bị trung gian. Ta có 1 hệ thống mạng.

![](/docs/CCNA (old)/img/network_3.png)

Khảo sát tình huống 3 máy tính kết nối với nhau, không qua thiết bị trung gian. Ta có thể cấp thêm mỗi máy tính 1 card mạng để kết nối. Nhưng nhiều máy tính hơn thì không khả thi.

![](/docs/CCNA (old)/img/network_4.png)

Khảo sát tình huống có sự xuất hiện của switch, việc kết nối trở nên dễ dàng hơn. Đặc điểm của switch có thể thấy là có rất nhiều port.

![](/docs/CCNA (old)/img/network_5.png)

Trên thị trường có nhiều loại switch 4, 8, 16, 32, 48.. ports. Trong trường hợp cần dùng nhiều hơn 48 ports, có thể chọn giải pháp nối 2 switch với nhau. Nhưng với cách làm này sẽ đem lại nhiều rủi ro về tài nguyên hay dễ thấy là bảo mật. Khi 1 máy tính tấn công netcut (làm down mạng) sẽ ảnh hưởng toàn bộ.

![](/docs/CCNA (old)/img/network_6.png)

Sự xuất hiện của router. Router chia 1 vùng mạng lớn thành nhiều vùng mạng nhỏ hơn.

![](/docs/CCNA (old)/img/network_7.png)

<h3> Các đặc điểm mạng cơ bản (characteristic) </h3>
<br>
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

## Mạng hoạt động như thế nào? (how?)
<br>
Dữ liệu sẽ được chuyển đổi thành tín hiệu điện truyền qua môi trường truyền dẫn và được chuyển đổi ngược lại để có thể đọc. <br>
Các cơ chế truyền sẽ được tìm hiểu ở các phần sau. <br>