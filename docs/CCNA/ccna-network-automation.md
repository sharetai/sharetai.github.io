---
layout: default
title: Network Automation
nav_order: 98
parent: CCNA
---

# Network Automation
{: .no_toc }

Tự động hóa mạng
{: .fs-6 .fw-300 }

---

## Table of contents
{: .no_toc .text-delta }

1. TOC
{:toc}

---

## Traditional Network Management

Ở mạng truyền thống, chỉ có thể quản lý từng thiết bị mạng một bằng cách sử dụng SSH. Tốn nhiều thời gian, công sức và dễ xảy ra lỗi của con người. Không hiệu quả trong một doanh nghiệp lớn và cũng không mở rộng quy mô tốt.

Thách thức: <br>
\- Vấn đề về khả năng mở rộng <br>
\- Sự phức tạp trong quản lý <br>
\- Xử lý lỗi chậm hơn <br>

## Controller-Based Networks

Cho phép quản lý tập trung cấu hình thiết bị mạng và tự động cấu hình, vận hành mạng thông qua Giao diện lập trình ứng dụng _(API - Application Programming Interfaces)_.

SD-Access là giải pháp tự động hóa mạng của Cisco thay thế quản lý mạng truyền thống. Nó cung cấp một điểm duy nhất để tự động hóa, điều phối và quản lý mạng thông qua bộ điều khiển trung tâm Cisco DNA Center. SD-Access có hai thành phần chính: <br>
\- Cisco Campus Fabric Solution - đó là lớp phủ ảo hóa mạng _overlay_ được xây dựng dựa trên lớp nền mạng _underlay_. <br>
\- Cisco DNA Center – Bộ điều khiển SDN để quản lý tập trung và NMS. <br>

## Configuration Management Tools – Ansible, Chef, Puppet

**<u>Ansible</u>** <br>
\- Ngôn ngữ **python**, định dạng **yaml** <br>
\- Mô hình **agentless** (only master) <br>
\- Agent **push** cấu hình cho node mạng <br>
\- Sử dụng **SSH** NETCONF <br>
\- File cấu hình gọi là **playbook** với các **task** <br>

**<u>Chef</u>** <br>
\- Ngôn ngữ **ruby** <br>
\- Mô hình **master-agent** <br>
\- Agent **pull** cấu hình từ master <br>
\- Sử dụng REST <br>
\- File cấu hình gọi là **cookbook** <br>
\- **Recipe** là mã được triển khai <br>

**<u>Puppet</u>** <br>
\- Ngôn ngữ **ruby** <br>
\- Mô hình **master-agent** <br>
\- Agent **pull** cấu hình từ master <br>
\- Sử dụng REST <br>
\- Các mẫu trong file cấu hình gọi là **module** <br>
\- **Manifest** là mã được triển khai <br>

## Cisco SDN – Software Defined Networking

Kiến trúc SDN được chia thành ba lớp – Lớp cơ sở hạ tầng, Lớp điều khiển và Lớp ứng dụng. Sử dụng API kết nối các lớp trong kiến ​​trúc SDN. Các lớp có tính phân cấp. Lớp cơ sở hạ tầng được đặt ở dưới cùng của kiến ​​trúc SDN, và lớp điều khiển được đặt ở giữa trong khi lớp ứng dụng được đặt ở trên cùng.

Do đó, liên kết giữa lớp cơ sở hạ tầng và lớp điều khiển đang sử dụng API hướng Nam và liên kết giữa lớp điều khiển và lớp ứng dụng đang sử dụng API hướng Bắc. API hướng Nam cho phép bộ điều khiển lập trình các bảng chuyển tiếp mặt phẳng dữ liệu của thiết bị mạng.

API southbound sử dụng **SSH**, **NETCONF**, **OpenFlow**, SNMP. API Northbound sử dụng API **REST**, **SOAP**, TLS.

![Alt text](/docs/CCNA/img/software-defined-networking.png)
