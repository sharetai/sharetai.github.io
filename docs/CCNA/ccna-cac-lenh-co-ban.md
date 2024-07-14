---
layout: default
title: Các lệnh cơ bản
nav_order: 4
parent: CCNA
---

# Các lệnh cơ bản
{: .no_toc }

Một số lệnh cơ bản ở các mode
{: .fs-6 .fw-300 }

---

## Table of contents
{: .no_toc .text-delta }

1. TOC
{:toc}

---

Các thành phần bên trong thiết bị cisco cơ bản gồm có:

* __CPU - Central Processing Unit__: trung tâm xử lý
* __RAM - Random Access Memory__: bộ nhớ đệm
* __Flash__: bên trong lưu trữ hệ điều hành IOS (Internetwork Operating System), cấu hình configuration
* __NVRAM - Nonvolatile RAM__ (có ở router): lưu trữ cấu hình khởi động ban đầu (starup-config)
* __ROM - Read-only memory__: lưu trữ chương trình POST (Power On Self Test) dùng để test phần cứng trước khi khởi động, ngoài ra còn có ROMMON, Bootstrap

Quy trình khởi động cơ bản: POST (ROM) -> Bootstrap (ROM) -> IOS (Flash) -> config (Flash/NVRAM)

## Các phím tắt và thông báo lỗi

<table>
  <tr>
    <td>Ctrl A</td>
    <td>ahead</td>
    <td>về đầu dòng lệnh</td>
  </tr>
  <tr>
    <td>Ctrl E</td>
    <td>end</td>
    <td>về cuối dòng lệnh</td>
  </tr>
  <tr>
    <td>Ctrl D</td>
    <td>delete a character</td>
    <td>xoá 1 ký tự phía sau</td>
  </tr>
  <tr>
    <td>Ctrl U</td>
    <td>delete all characters</td>
    <td>xoá toàn bộ hàng</td>
  </tr>
</table>

<table>
  <tr>
    <td>! Ambigous command</td>
    <td>từ gõ vào trùng nhiều lệnh</td>
  </tr>
  <tr>
    <td>! Incomplete command</td>
    <td>lệnh chưa hoàn tất</td>
  </tr>
  <tr>
    <td>! Invalid command</td>
    <td>giá trị nhập sai</td>
  </tr>
  <tr>
    <td>! Unknown command</td>
    <td>lệnh không có hay không hỗ trợ trong mode này</td>
  </tr>
</table>

## Các lệnh cơ bản

Mode User

```
> enable
```

Mode Priviledge hay mode Enable

```
> enable
# exit
# show run
# show start
# copy run start || write
# erase start || write erase
# reload
# show ip int brief
```

Mode Global Configuration

```
# conf t
(config) # enable password 456
(config) # enable secret 789
(config) # no ip domain-lookup
(config) # no logging console
(config) # logging synchronous
```

Mode Sub Configuration

```
(config) # line console 0
(config-line) # pass 123
(config-line) # login
```

Ngoài ra còn nhiều lệnh khác nữa, trên đây là những lệnh thường gặp nhưng chưa đi sâu vào từng lệnh.
