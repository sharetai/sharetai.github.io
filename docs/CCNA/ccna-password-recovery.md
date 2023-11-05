---
layout: default
title: Password recovery
nav_order: 7
parent: CCNA
---

# Password recovery
{: .no_toc }

Các bước crack password một thiết bị mạng
{: .fs-6 .fw-300 }

---

## Table of contents
{: .no_toc .text-delta }

1. TOC
{:toc}

---

## Thao tác trên Router

**Bước 1:** Tắt-bật router, nhấn nhanh tổ hợp phím **Ctrl+Break** để khởi động router vào chế độ **ROM MONITOR**

**Bước 2:** Cấu hình thanh ghi config-register là **0x2142** để lần khởi động kế sẽ không load cấu hình trong NVRAM, do đó sẽ không bị hỏi password

```
Rommon 1>confreg 0x2142
Rommon 2>reset
```

**Bước 3:** Copy cấu hình start vào run, sau đó ghi đè hoặc loại bỏ password cũ, cuối cùng cấu hình confreg về **0x2102** và lưu lại cấu hình vào start

```
Router#copy start run
Router#conf t
Router(config)#no enable password
Router(config)#no enable secret
Router(config)#line console 0
Router(config-line)#no login
Router(config-line)#no password
Router(config-line)#exit
Router(config)#conf 0x2102
Router(config)#end
Router#write
Router#reload
```

## Thao tác trên Switch

**Bước 1:** Tắt-bật switch, nhấn giữ phím **Mode** ở mặt trước cho đến khi đèn **SYST LED** trên switch chuyển từ màu vàng sang màu xanh lá cây. Khi ta nhả phím **Mode** thì đèn **SYST LED** phải ở trạng thái xanh lá cây để vào chế độ **ROM MONITOR**

**Bước 2:** Khi vào được chế độ **ROM MONITOR**, đổi tên file config.text để lần khởi động kế không load cấu hình cũ

```
Switch: flash_init
Switch: dir_flash
Switch: rename flash:config.text flash:config.old
Switch: reboot
```

**Bước 3:** Load vào run để loại bỏ password

```
Switch#copy flash: run
Source filename []? config.old
Destination filename [running-config]? 
```

**Bước 4:** Ghi đè hoặc loại bỏ password cũ, cuối cùng lưu lại cấu hình vào start

```
Switch#conf t
Switch(config)#no enable password
Switch(config)#no enable secret
Switch(config)#line console 0
Switch(config-line)#no login
Switch(config-line)#no password
Switch(config-line)#exit
Switch(config)#end
Switch#write
Switch#reload
```
