---
layout: default
title: Network Automation
nav_order: 170
parent: CCNP
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

## EEM Embedded Event Manager

### [\<Cheat sheet\>](/docs/CCNP/img/EEM.png)
<br>
Trình quản lý sự kiện nhúng (EEM) trên thiết bị Cisco IOS là giải pháp tùy chỉnh để phát hiện sự kiện và khôi phục. Khi các sự kiện được giám sát xảy ra hoặc đạt đến ngưỡng, EEM cho phép theo dõi và thực hiện các hành động theo hướng dẫn. EEM mô tả một sự kiện cụ thể và các hành động cần được triển khai để phản hồi lại sự kiện đó.

<h4> DÙNG EEM SCRIPT ĐỂ TỰ ĐỘNG BACKUP FTP KHI SAVE CONFIG </h4>

```
event manager applet backup-config
event cli pattern "wr" sync yes ## để thực hiện xong lệnh wr thì mới chạy script này
action 1.0 cli command "enable"
action 1.1 cli command "conf t"
action 2.0 cli command "file prompt quiet" ##Để không cần user can thiệp khi xác nhận tên file cfg
action 2.1 cli command "end"
action 3.0 cli command "copy running-config ftp://uname:pass@10.1.2.1/R1.cfg"
action 4.0 cli command "end"
```

<h4> thông báo khi người dùng chuyển sang chế độ cấu hình </h4>

```
event manager applet config-alert
event cli pattern "conf t.*" sync yes
action 1.0 snmp-trap strdata "Configuration change alarm"
action 1.1 syslog priority critical msg "Configuration change alarm"
```
