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

## Các thành phần bên trong thiết bị cisco

Các thành phần bên trong thiết bị cisco cơ bản gồm có:

* __CPU - Central Processing Unit__: trung tâm xử lý
* __RAM - Random Access Memory__: bộ nhớ đệm
* __Flash__: bên trong lưu trữ hệ điều hành IOS (Internetwork Operating System), cấu hình configuration
* __NVRAM - Nonvolatile RAM__ (có ở router): lưu trữ cấu hình khởi động ban đầu (starup-config)
* __ROM - Read-only memory__: lưu trữ chương trình POST (Power On Self Test) dùng để test phần cứng trước khi khởi động, ngoài ra còn có ROMMON, Bootstrap

Quy trình khởi động cơ bản: POST (ROM) -> Bootstrap (ROM) -> IOS (Flash) -> config (Flash/NVRAM)

## Các phím tắt và thông báo lỗi

```
> help
HELP:
Special keys:
DEL, BS... delete previous character
Ctrl-A .... go to beginning of line
Ctrl-E .... go to end of line
Ctrl-F .... go forward one character
Ctrl-B .... go backward one character
Ctrl-D .... delete current character
Ctrl-U, X. delete to beginning of line
Ctrl-K .... delete to end of line
Ctrl-W .... delete previous word
Ctrl-T .... transpose previous character
Ctrl-P .... go to previous line in history buffer
Ctrl-N .... go to next line in history buffer
Ctrl-Z .... return to root command prompt
Tab, <SPACE> command-line completion
Exit .... go to next lower command prompt
? .... list choices```
```

```
! Ambigous command    từ gõ vào trùng nhiều lệnh 
! Incomplete command  lệnh chưa hoàn tất 
! Invalid command     giá trị nhập sai
! Unknown command     lệnh không có hay không hỗ trợ trong mode này
```

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
# copy run start
# write
# erase start
# write erase
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
