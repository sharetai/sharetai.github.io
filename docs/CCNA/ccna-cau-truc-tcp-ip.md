---
layout: default
title: Cấu trúc bộ giao thức TCP/IP
nav_order: 2
parent: CCNA
---

# Cấu trúc bộ giao thức TCP/IP
{: .no_toc }

Cấu trúc header một số giao thức cơ bản
{: .fs-6 .fw-300 }

---

## Table of contents
{: .no_toc .text-delta }

1. TOC
{:toc}

---

## ICMP Header

![image](https://user-images.githubusercontent.com/56266496/165346980-739b5c06-6856-468b-9d0e-446dc1ccc5fc.png)

* Chức năng: Kiểm tra kết nối giữa các thiết bị và truyền thông điệp lỗi.
* Giải thích các field cần nhớ:
  * Type: Loại gói ICMP (Vd: 8 - Echo request, 0 - Echo reply, ...)
  * Code: Chi tiết gói ICMP khi có Type: 3, 5, 11, 12

## IP Header

![image](https://user-images.githubusercontent.com/56266496/165347257-95cb23ca-f323-40c9-9e37-0e4fa4731cf5.png)

* Chức năng: Định tuyến
* Giải thích các field cần nhớ:
  * Source address: Địa chỉ nguồn
  * Destination address: Địa chỉ đích
  * Protocol: Thông tin giao thức lớp trên (Vd: 1 - ICMP, 6 - TCP, ...)
  * TTL: Dùng để tránh lặp gói tin vô hạn trong hệ thống (khi qua Router TTL sẽ giảm 1, gói tin sẽ bị hủy khi TTL=0)

## TCP Header

![image](https://user-images.githubusercontent.com/56266496/165347318-7a7fe6b7-5b07-4520-9382-413966c3e954.png)

* Chức năng: Kiểm soát việc gửi dữ liệu giữa các thiết bị đầu cuối được chính xác đầy đủ
* Giải thích các field cần nhớ:
  * Port number: Thông tin giao thức lớp trên (Loại ứng dụng trao đổi. Vd: 80 - HTTP, 25 - SMTP, ...)
  * Sequence number: Thông tin đoạn dữ liệu được tiếp nhận
  * Acknowledgment number: Phản hồi lượng dữ liệu nhận được trước đó của máy gửi

## UDP Header

![image](https://user-images.githubusercontent.com/56266496/165347348-6856c549-3497-488f-95e3-e86e81db329a.png)

* Chức năng: Là giao thức cùng lớp với TCP, nhưng được rút gọn. UDP không được thiết kế để kiểm soát chính xác và đầy đủ việc truyền dữ liệu nhưng hoạt động nhanh hơn.
* Giao thức UDP chỉ được sử dụng khi:
  * Môi trường tin cậy (mạng lan)
  * Môi trường không tin cậy:
    * dữ liệu nhỏ (chat)
    * dữ liệu không quan trọng (phim)
