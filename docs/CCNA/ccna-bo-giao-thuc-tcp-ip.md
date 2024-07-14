---
layout: default
title: Bộ giao thức TCP/IP
nav_order: 2
parent: CCNA
---

# TCP/IP suite of protocols
{: .no_toc }

Bộ giao thức TCP/IP
{: .fs-6 .fw-300 }

---

## Table of contents
{: .no_toc .text-delta }

1. TOC
{:toc}

---
## ARP Header

![Alt text](/docs/CCNA/img/tcp-ip-arp-header.png)

* Chức năng: Được sử dụng để liên kết địa chỉ IP với địa chỉ MAC.

## IP Header

![Alt text](/docs/CCNA/img/tcp-ip-ipv4-header.png)

* Chức năng: Định tuyến
* Giải thích các field cần nhớ:
  * Source address: Địa chỉ nguồn
  * Destination address: Địa chỉ đích
  * Protocol: Thông tin giao thức lớp trên (Vd: 1 - ICMP, 6 - TCP, ...)
  * TTL: Dùng để tránh lặp gói tin vô hạn trong hệ thống (khi qua Router TTL sẽ giảm 1, gói tin sẽ bị hủy khi TTL=0)

## ICMP Header

![Alt text](/docs/CCNA/img/tcp-ip-icmp-header.png)

* Chức năng: Kiểm tra kết nối giữa các thiết bị và truyền thông điệp lỗi.
* Giải thích các field cần nhớ:
  * Type: Loại gói ICMP (Vd: 8 - Echo request, 0 - Echo reply, ...)
  * Code: Chi tiết gói ICMP khi có Type: 3, 5, 11, 12

## TCP Header

![Alt text](/docs/CCNA/img/tcp-ip-tcp-header.png)

* Chức năng: Kiểm soát việc gửi dữ liệu giữa các thiết bị đầu cuối được chính xác đầy đủ
* Giải thích các field cần nhớ:
  * Port number: Thông tin giao thức lớp trên (Loại ứng dụng trao đổi. Vd: 80 - HTTP, 25 - SMTP, ...)
  * Sequence number: Thông tin đoạn dữ liệu được tiếp nhận
  * Acknowledgment number: Phản hồi lượng dữ liệu nhận được trước đó của máy gửi

## UDP Header

![Alt text](/docs/CCNA/img/tcp-ip-udp-header.png)

* Chức năng: Là giao thức cùng lớp với TCP, nhưng được rút gọn. UDP không được thiết kế để kiểm soát chính xác và đầy đủ việc truyền dữ liệu nhưng hoạt động nhanh hơn.
* Giao thức UDP chỉ được sử dụng khi:
  * Môi trường tin cậy (mạng lan)
  * Môi trường không tin cậy:
    * dữ liệu nhỏ (chat)
    * dữ liệu không quan trọng (phim)
