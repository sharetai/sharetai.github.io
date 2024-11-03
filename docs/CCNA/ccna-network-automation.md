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
<br>
Ở mạng truyền thống, chỉ có thể quản lý từng thiết bị mạng một bằng cách sử dụng SSH. Tốn nhiều thời gian, công sức và dễ xảy ra lỗi của con người. Không hiệu quả trong một doanh nghiệp lớn và cũng không mở rộng quy mô tốt.

Thách thức: <br>
\- Vấn đề về khả năng mở rộng <br>
\- Sự phức tạp trong quản lý <br>
\- Xử lý lỗi chậm hơn <br>

<br>

## Controller-Based Networks
<br>
Cho phép quản lý tập trung cấu hình thiết bị mạng và tự động cấu hình, vận hành mạng thông qua Giao diện lập trình ứng dụng _(API - Application Programming Interfaces)_.

SD-Access là giải pháp tự động hóa mạng của Cisco thay thế quản lý mạng truyền thống. Nó cung cấp một điểm duy nhất để tự động hóa, điều phối và quản lý mạng thông qua bộ điều khiển trung tâm Cisco DNA Center. SD-Access có hai thành phần chính: <br>
\- Cisco Campus Fabric Solution - đó là lớp phủ ảo hóa mạng _overlay_ được xây dựng dựa trên lớp nền mạng _underlay_. <br>
\- Cisco DNA Center – Bộ điều khiển SDN để quản lý tập trung và NMS. <br>

<br>

## Configuration Management Tools – Ansible, Chef, Puppet
<br>
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

<br>

## Cisco SDN – Software Defined Networking
<br>
Tương lai của mạng là tự động hóa. Trong mạng truyền thống, hiện tại quản lý bằng các phương pháp ___box-by-box___ sử dụng CLI, GUI, SNMP, SSH hoặc telnet. Gặp các vấn đề khi triển khai các thiết bị mới hay nâng cấp thiết bị mới, cấu hình thủ công, quản lý sai sót, không tối ưu hóa được tài nguyên mạng.

___Software Defined Networking (SDN)___ là công nghệ kiểm soát và quản lý mạng cho phép các phương pháp tiếp cận linh hoạt và có lập trình để giám sát và cấu hình mạng. Với SDN, các nhà khai thác mạng hoặc kỹ sư có thể sửa đổi và kiểm soát lưu lượng từ bộ điều khiển tập trung mà không cần thủ công vào từng thiết bị. Có thể tự động cập nhật các thay đổi về cấu hình hay các chính sách.

<br>

__3 mặt phẳng:__

__1. Data Plane__ Là mặt phẳng chuyển tiếp dữ liệu. So khớp địa chỉ đích với bảng định tuyến để chuyển tiếp dữ liệu. <br>
__2. Control Plane__ Quyết định các chuyển tiếp dữ liệu. Xây dựng bảng định tuyến, mac, arp, stp. <br>
__3. Management Plane__ Quản lý các thiết bị mạng bằng CLI sử dụng SSH/telnet hay GUI sử dụng HTTP/HTTPS. <br>

Khác với mạng truyền thống, mặt phẳng điều khiển trong SDN được tách biệt và được triển khai trong phần mềm được lưu trữ trên máy chủ, cho phép quản lý các thiết bị mạng một cách linh hoạt và có lập trình.

<br>

__3 lớp kiến trúc:__

__1. Infrastructure Layer__ <br>
__2. Control Layer__ <br>
__3. Application Layer__ <br>

Liên kết giữa lớp cơ sở hạ tầng và lớp điều khiển sử dụng API hướng Nam và liên kết giữa lớp điều khiển và lớp ứng dụng  sử dụng API hướng Bắc. API hướng Nam cho phép bộ điều khiển lập trình các bảng chuyển tiếp của mặt phẳng dữ liệu.

API southbound sử dụng **SSH**, **NETCONF**, **OpenFlow**, SNMP. API Northbound sử dụng API **REST**, **SOAP**, TLS.

![Alt text](/docs/CCNA/img/software-defined-networking.png)

<br>

## Cisco DNA – Digital Network Architecture
<br>
___Cisco DNA Center (còn gọi là Cisco Digital Network Architecture)___ là bộ điều khiển và quản lý SDN mạnh mẽ cho phép kiểm soát mạng, tối ưu hóa, bảo mật các kết nối từ xa và giảm chi phí.

Cisco DNA Center tận dụng sử dụng mạng dựa trên mục đích ___Intent-Based Networking (IBN)___. IBN là công nghệ SDN chuyển các nhu cầu kinh doanh thành các chính sách có thể được tự động hóa và thực thi nhất quán trên toàn mạng. Với nền tảng trung tâm Cisco DNA, không cần phải lo lắng quá nhiều về cấu hình CLI. Kỹ sư mạng sẽ chỉ tạo chính sách hoặc cấu hình dựa trên mục đích kinh doanh hoặc yêu cầu trên Cisco DNA center và điều đó sẽ thực hiện được. Cisco DNA center sẽ tự động triển khai cấu hình cho tất cả các thiết bị dựa trên cách ta muốn mạng hoạt động.

<br>

## Cisco SD-Access Architecture
<br>
![alt text](/docs/CCNA/img/sdn-sd-access.png)

## Cisco SD-WAN Architecture
<br>
![alt text](/docs/CCNA/img/sdn-sd-wan.png)

