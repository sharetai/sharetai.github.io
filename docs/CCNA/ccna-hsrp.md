---
layout: default
title: HSRP
nav_order: 17
parent: CCNA
---

# Hot Standby Router Protocol
{: .no_toc }

Giao thức Bộ định tuyến Dự phòng Nóng
{: .fs-6 .fw-300 }

---

## Table of contents
{: .no_toc .text-delta }

1. TOC
{:toc}

---

## HSRP

__Hot Standby Router Protocol (HSRP)__ cung cấp tính năng dự phòng cho router. Nếu một router gặp sự cố thay vì cấu hình chuyển đổi router cho máy tính người dùng bằng tay, giao thức này sẽ tự động hoá cho hệ thống

![image](/docs/CCNA/img/hsrp.png)

* __R1__

```
R1(config)#int g0/0
R1(config-if)#standby 1 ip 10.0.0.254
R1(config-if)#standby 1 priority 120
R1(config-if)#standby 1 preempt 
```

* __R2__

```
R2(config)#int g0/0
R2(config-if)#standby 1 ip 10.0.0.254
```

## GLBP

__Gateway Load Balancing Protocol (GLBP)__ là một giao thức độc quyền của Cisco cố gắng khắc phục những hạn chế của các giao thức bộ định tuyến dự phòng hiện có bằng cách thêm chức năng cân bằng tải cơ bản .

* __R1__

```
R1(config)#int g0/0
R1(config-if)#glbp 1 ip 10.0.0.254
R1(config-if)#glbp 1 priority 120
R1(config-if)#glbp 1 preempt 
```

* __R2__

```
R2(config)#int g0/0
R2(config-if)#glbp 1 ip 10.0.0.254
```
