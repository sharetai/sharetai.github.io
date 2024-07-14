---
layout: default
title: Mạng là gì?
nav_order: 0
parent: CCNA
---

# What is Network?
{: .no_toc }

Mạng là gì?
{: .fs-6 .fw-300 }

---

## Table of contents
{: .no_toc .text-delta }

1. TOC
{:toc}

---

## <u>Mạng là gì? (what?)</u>

2 dấu hiệu nhận biết:

- 2 hay nhiều thiết bị kết nối với nhau
- Truyền thông, chia sẻ dữ liệu cho nhau

=> Gọi là 1 hệ thống mạng

![](/docs/CCNA/img/network.png)

Hệ thống mạng gia đình

![](/docs/CCNA/img/network_1.png)

## <u>Thành phần cơ bản (components)</u>

- Máy tính
- Switch
- Router
- Cáp truyền dẫn

![](/docs/CCNA/img/network_2.png)

Khảo sát tình huống 2 máy tính kết nối với nhau, không qua thiết bị trung gian. Ta có 1 hệ thống mạng.

![](/docs/CCNA/img/network_3.png)

Khảo sát tình huống 3 máy tính kết nối với nhau, không qua thiết bị trung gian. Ta có thể cấp thêm mỗi máy tính 1 card mạng để kết nối. Nhưng nhiều máy tính hơn thì không khả thi.

![](/docs/CCNA/img/network_4.png)

Khảo sát tình huống có sự xuất hiện của switch, việc kết nối trở nên dễ dàng hơn. Đặc điểm của switch có thể thấy là có rất nhiều port.

![](/docs/CCNA/img/network_5.png)

Trên thị trường có nhiều loại switch 4, 8, 16, 32, 48.. ports. Trong trường hợp cần dùng nhiều hơn 48 ports, có thể chọn giải pháp nối 2 switch với nhau. Nhưng với cách làm này sẽ đem lại nhiều rủi ro về tài nguyên hay dễ thấy là bảo mật. Khi 1 máy tính tấn công netcut (làm down mạng) sẽ ảnh hưởng toàn bộ.

![](/docs/CCNA/img/network_6.png)

Sự xuất hiện của router. Router chia 1 vùng mạng lớn thành nhiều vùng mạng nhỏ hơn.

![](/docs/CCNA/img/network_7.png)

## <u>Các loại mạng phổ biến (type)</u>

__LAN (Local Area Network)__: Mạng cục bộ <br>
\- Mạng LAN SOHO (small office/home office) điển hình bao gồm PCs, máy in, bộ chuyển mạch, bộ định tuyến và cáp kết nối tất cả các thiết bị này với nhau. <br>
__PAN (Personal Area Network)__: Mạng cá nhân <br>
__MAN (Metropolitan Area Network)__: Mạng đô thị <br>
__WAN (Wide Area Network)__: Mạng diện rộng <br>
__WLAN (Wireless Local Area Network)__: Mạng cục bộ không dây <br>

## <u>Các đặc điểm mạng cơ bản (characteristic)</u>

<h3> Tốc độ (speed) </h3>

Đảm bảo các thành phần đều hỗ trợ tốc độ mong muốn (ví dụ hình là 1 Gbps)
- Cáp 1000BASE‑T
- Card mạng trên máy tính hỗ trợ tốc độ 1 Gbps
- Modem và thiết bị di động hỗ trợ chuẩn 802.11 ac

<h3> Chi phí (cost) </h3>

Chia thành 3 nhóm
- Chi phí triển khai ban đầu
- Chi phí duy trì hạ tầng mạng
- Chi phí bảo trì, bảo dưỡng, nâng cấp hệ thống mạng

<h3> Bảo mật (security) </h3>

- Tính năng bảo mật trên switch (port security, dhcp snooping..)
- Firewall (Chặn lọc nội dung, chống chọi trước tấn công dos/ddos..)

<h3> Tính sẵn sàng (availability) </h3>

Đảm bảo kết nối internet. Thuê ít nhất 2 kết nối mạng từ 2 nhà cung cấp dich vụ mạng khác nhau.

<h3> Khả năng mở rộng (scalability) </h3>

Đầu tư những dòng thiết bị hiệu năng cao, khả năng phục vụ nhiều người dùng. Không cần tính toán lại hay loại bỏ thiết bị cũ để thay thiết bị mới.

<h3> Độ tin cậy (reliability) </h3>

Sử dụng giao thức truyền thông tin cậy (SSH, SFTP, HTTPS..)
