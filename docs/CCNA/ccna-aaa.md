---
layout: default
title: AAA
nav_order: 25
parent: CCNA
---

# Authentication, Authorization, and Accouting
{: .no_toc }

Xác thực, Ủy quyền và Tính cước
{: .fs-6 .fw-300 }

---

## Table of contents
{: .no_toc .text-delta }

1. TOC
{:toc}

---

## AAA

__AAA__ (**A**uthentication, **A**uthorization, and **A**ccouting) là phương thức cấu hình dùng để xác thực, cấp quyền và ghi thông tin người dùng khi sử dụng thiết bị và dịch vụ trên thiết bị Cisco. 

__Authentication__: xác định người dùng nào được phép kết nối vào thiết bị, tài khoản người dùng có thể tạo local trên thiết bị hoặc trên server dùng giao thức TACACS+ hoặc RADIUS để hỗ trợ chứng thực.

__Authorization__: xác định quyền hạn, cấu hình authorization sẽ cung cấp mức quyền hạn và các lệnh được dùng tương ứng.

__Accouting__: thu thập thông tin người dùng như địa chỉ IP, thời gian kết nối,..

### RADIUS

![image](/docs/CCNA/img/aaa1.png)

![image](/docs/CCNA/img/aaa2.png)

```
Switch(config)#aaa new-model 
Switch(config)#radius-server host 192.168.1.254 key 123
Switch(config)#aaa authentication login ABC group radius 

Switch(config)#line vty 0 4
Switch(config-line)#login authentication ABC

Switch(config)#enable secret 789
```

### TACACS+
```
aaa new-model 

! Set up AAA authentication for login:
! This authorizes privilege level 15 commands using TACACS+, with local as fallback.
aaa authentication login default group tacacs+ local

! Configure TACACS+ server(s):
tacacs server prod
address ipv4 10.10.10.23
key cisco123

! Specify port
ip tacacs source-interface Gig 0/0

! Grant access-level rights to remote users
aaa authorization exec default group tacacs+
```

## RADIUS vs TACACS+

| RADIUS                            | TACACS+                                       |
| :-------------------------------: | :-------------------------------------------: |
| Chuẩn mở                          | Chuẩn của Cisco                               |
| Sử dụng UDP                       | Sử dụng TCP                                   |
| Hỗ trợ 802.1x                     | Không hỗ trợ 802.1x                           |
| Gom 2 phần xác thực và phân quyền | Tách 3 phần xác thực và phân quyền, tính cước |
| Chỉ password được mã hóa          | Toàn bộ payload được mã hóa                   |
