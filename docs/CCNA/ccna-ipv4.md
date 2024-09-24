---
layout: default
title: IPv4
nav_order: 3.3
parent: CCNA
---

# Internet Protocol Version 4
{: .no_toc }

Giao thức Internet phiên bản 4
{: .fs-6 .fw-300 }

---

## Table of contents
{: .no_toc .text-delta }

1. TOC
{:toc}

---

<h2 style="display:inline-block">why?</h2><p style="display:inline-block">&nbsp;&nbsp;Địa chỉ IPv4 giúp các máy tính trên mạng xác định chính xác thiết bị mà chúng muốn giao tiếp. Các gói tin dữ liệu được chuyển qua mạng Internet dựa trên địa chỉ IPv4 của đích đến. Để truy cập Internet, mỗi thiết bị cần có một địa chỉ IPv4 hợp lệ.</p>

## Phân lớp địa chỉ

Toàn bộ địa chỉ IP được chia thành 5 nhóm gọi là Class IP. 5 nhóm này phân biệt dựa vào giá trị nhóm octet đầu tiên như sau:

|                 | Class | First octet | Default Subnet Mask | Function                                     |
| :-------------- | :---- | :---------- | :------------------ | :------------------------------------------- |
| 0 _ _ _ _ _ _ _ | A     | 1 - 126     | 255.0.0.0           | Unicast (IP riêng) / Broadcast (IP quảng bá) |
| 1 0 _ _ _ _ _ _ | B     | 128 - 191   | 255.255.0.0         | Unicast (IP riêng) / Broadcast (IP quảng bá) |
| 1 1 0 _ _ _ _ _ | C     | 192 - 223   | 255.255.255.0       | Unicast (IP riêng) / Broadcast (IP quảng bá) |
| 1 1 1 0 _ _ _ _ | D     | 224 - 239   |                     | Multicast (IP nhóm)                          |
| 1 1 1 1 _ _ _ _ | E     | 240 - 255   |                     | Experimental                                 |

### Địa chỉ đặc biệt:

| Phạm vi địa chỉ IP | Mô tả                        |
| :----------------- | :--------------------------- |
| 0.0.0.0/8          | local network                |
| 127.0.0.0/8        | loopback addresses           |
| 169.254.0.0/16     | link-local addresses (APIPA) |

### Địa chỉ mạng riêng:

| Phạm vi địa chỉ IP            | Số lượng địa chỉ | Khối CIDR lớn nhất (mặt nạ mạng con) | Kích thước ID máy chủ | Mặt nạ bit | 
| :---------------------------- | :--------------- | :----------------------------------- | :-------------------- | :--------- |
| 10.0.0.0 - 10.255.255.255     | 16777216         | 10.0.0.0/8 (255.0.0.0)               | 24 bit                | 8 bit      |
| 172.16.0.0 - 172.31.255.255   | 1048576          | 172.16.0.0/12 (255.240.0.0)          | 20 bit                | 12 bit     |
| 192.168.0.0 - 192.168.255.255 | 65536            | 192.168.0.0/16 (255.255.0.0)         | 16 bit                | 16 bit     |

### Địa chỉ mạng Carrier-Grade NAT:

| Phạm vi địa chỉ IP            | Số lượng địa chỉ | Khối CIDR lớn nhất (mặt nạ mạng con) | Kích thước ID máy chủ | Mặt nạ bit | 
| :---------------------------- | :--------------- | :----------------------------------- | :-------------------- | :--------- |
| 100.64.0.0 – 100.127.255.255  | 4194304          | 100.64.0.0/10 (255.192.0.0)          | 22 bit                | 10 bit     |


### Bảng phân hoạch IP:

| Số bit mượn (n) | Số subnet (2^n) | Bước nhảy 2^(8-n) | Subnet mask |
| --- | --- | --- | --- |
| 1 | 2 | 128 | 128 |
| 2 | 4 | 64 | 192 |
| 3 | 8 | 32 | 224 |
| 4 | 16 | 16 | 240 |
| 5 | 32 | 8 | 248 |
| 6 | 64 | 4 | 252 |
| 7 | 128 | 2 | 254 |
| 8 | 256 | 1 | 255 |

## Chia subnet

Dạng 1: 10.0.0.0/8 chia 4

```
* Số bit mượn (n): 2
* Bước nhảy 2^(8-n): 64
* Subnet mask: 255.192.0.0
* 4 mạng con:
  - 10.0.0.0/10       10.0.0.1 -> 10.63.255.254
  - 10.64.0.0/10      10.64.0.1 -> 10.127.255.254
  - 10.128.0.0/10     10.128.0.1 -> 10.191.255.254
  - 10.192.0.0/10     10.192.0.1 -> 10.255.255.254
```

Dạng 2: 10.0.0.0/8 chia 1024

```
* 1024 = 2^8 x 2^2
* chia 256:
  - 10.0.0.0/16
  - 10.1.0.0/16
  - ...
  - 10.255.0.0/16
* chia 4:
  - 10.0.0.0/16
    -- 10.0.0.0/18
    -- 10.0.64.0/18
    -- 10.0.128.0/18
    -- 10.0.192.0/18
  - 10.1.0.0/16
    -- 10.1.0.0/18
    -- 10.1.64.0/18
    -- 10.1.128.0/18
    -- 10.1.192.0/18
  - ...
```

Dạng 3: 200.0.0.64/26 chia 4

```
* Bước nhảy gốc: 64 (do mượn 2 bit)
* Bước nhảy mới: 16 (mượn thêm 2 bit)
* Subnet mask gốc: 255.255.255.192
* Subnet mask mới: 255.255.255.240
* 4 mạng con:
  - 200.0.0.64/28
  - 200.0.0.80/28
  - 200.0.0.96/28
  - 200.0.0.112/28
```

## Summary

VD1: Gộp 2 mạng

* 200.0.0.64/28
* 200.0.0.80/28

```
B1: Đổi nhị
64: 010|0 0000
80: 010|1 0000

B2: Giữ phần bit giống nhau
=> 200.0.0.64/27
```

VD2: Gộp 4 mạng

* 200.0.0.128/28
* 200.0.0.144/28
* 200.0.0.160/28
* 200.0.0.176/28

```
128: 10|00 0000
144: 10|01 0000
160: 10|10 0000
176: 10|11 0000

=> 200.0.0.128/26
```

