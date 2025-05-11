---
layout: default
title: Bộ giao thức TCP/IP
nav_order: 2
parent: CCNA (old)
---

# Transmission Control Protocol / Internet Protocol suite of protocols
{: .no_toc }

Bộ giao thức TCP/IP
{: .fs-6 .fw-300 }

---

## TABLE OF CONTENTS
{: .no_toc .text-delta }

1. TOC
{:toc}

---

## Tại sao cần có bộ giao thức TCP/IP (why?)
<br>

___\- Đảm bảo giao tiếp:___ TCP/IP cung cấp một bộ quy tắc chung, giúp các thiết bị khác nhau (máy tính, điện thoại, máy chủ,...) có thể hiểu và giao tiếp với nhau, dù chúng có cấu trúc phần cứng và hệ điều hành khác nhau. <br>
___\- Định tuyến:___ TCP/IP giúp định tuyến gói tin dữ liệu từ nguồn đến đích một cách hiệu quả, qua nhiều mạng khác nhau. <br>
___\- Kiểm soát lỗi:___ TCP/IP có các cơ chế để phát hiện và sửa lỗi trong quá trình truyền dữ liệu, đảm bảo tính chính xác của thông tin. <br>
___\- Quản lý lưu lượng:___ TCP/IP giúp điều khiển lưu lượng dữ liệu trên mạng, tránh tình trạng quá tải. <br>

## ARP Header
<br>
![Alt text](/docs/CCNA (old)/img/tcp-ip-arp-header.png)

* Chức năng: Được sử dụng để liên kết địa chỉ IP với địa chỉ MAC.

## IP Header
<br>
![Alt text](/docs/CCNA (old)/img/tcp-ip-ipv4-header.png)

* Chức năng: Định tuyến
* Giải thích các field cần nhớ:
  * Source address: Địa chỉ nguồn
  * Destination address: Địa chỉ đích
  * Protocol: Thông tin giao thức lớp trên (Vd: 1 - ICMP, 6 - TCP, ...)
  * TTL: Dùng để tránh lặp gói tin vô hạn trong hệ thống (khi qua Router TTL sẽ giảm 1, gói tin sẽ bị hủy khi TTL=0)

## ICMP Header
<br>
![Alt text](/docs/CCNA (old)/img/tcp-ip-icmp-header.png)

* Chức năng: Kiểm tra kết nối giữa các thiết bị và truyền thông điệp lỗi.
* Giải thích các field cần nhớ:
  * Type: Loại gói ICMP (Vd: 8 - Echo request, 0 - Echo reply, ...)
  * Code: Chi tiết gói ICMP khi có Type: 3, 5, 11, 12

## TCP Header
<br>
![Alt text](/docs/CCNA (old)/img/tcp-ip-tcp-header.png)

* Chức năng: Kiểm soát việc gửi dữ liệu giữa các thiết bị đầu cuối được chính xác đầy đủ
* Giải thích các field cần nhớ:
  * Port number: Thông tin giao thức lớp trên (Loại ứng dụng trao đổi. Vd: 80 - HTTP, 25 - SMTP, ...)
  * Sequence number: Thông tin đoạn dữ liệu được tiếp nhận
  * Acknowledgment number: Phản hồi lượng dữ liệu nhận được trước đó của máy gửi

## UDP Header
<br>
![Alt text](/docs/CCNA (old)/img/tcp-ip-udp-header.png)

* Chức năng: Là giao thức cùng lớp với TCP, nhưng được rút gọn. UDP không được thiết kế để kiểm soát chính xác và đầy đủ việc truyền dữ liệu nhưng hoạt động nhanh hơn.
* Giao thức UDP chỉ được sử dụng khi:
  * Môi trường tin cậy (mạng lan)
  * Môi trường không tin cậy:
    * dữ liệu nhỏ (chat)
    * dữ liệu không quan trọng (phim)
