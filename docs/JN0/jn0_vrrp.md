---
layout: default
title: VRRP
nav_order: 13
parent: JN0
---

# Virtual Router Redundancy Protocol
{: .no_toc }

Giao thức Dự phòng Bộ định tuyến Ảo
{: .fs-6 .fw-300 }

---

## Table of contents
{: .no_toc .text-delta }

1. TOC
{:toc}

---

## Cấu hình

![](/docs/JN0/img/11.png)

```
# vMX1
set interfaces ge-0/0/0 unit 0 family inet address 192.168.1.1/24 vrrp-group 10 virtual-address 192.168.1.3
set interfaces ge-0/0/0 unit 0 family inet address 192.168.1.1/24 vrrp-group 10 priority 200
set interfaces ge-0/0/1 unit 0 family inet address 8.8.8.1/24 vrrp-group 80 virtual-address 8.8.8.3
set interfaces ge-0/0/1 unit 0 family inet address 8.8.8.1/24 vrrp-group 80 priority 100

# vMX2
set interfaces ge-0/0/0 unit 0 family inet address 192.168.1.2/24 vrrp-group 10 virtual-address 192.168.1.3
set interfaces ge-0/0/0 unit 0 family inet address 192.168.1.2/24 vrrp-group 10 priority 100
set interfaces ge-0/0/1 unit 0 family inet address 8.8.8.2/24 vrrp-group 80 virtual-address 8.8.8.3
set interfaces ge-0/0/1 unit 0 family inet address 8.8.8.2/24 vrrp-group 80 priority 200
```

## Kiểm tra

```
root@vMX1> show vrrp
Interface     State       Group   VR state VR Mode   Timer    Type   Address
ge-0/0/0.0    up             10   master   Active      A  0.719 lcl    192.168.1.1
                                                                vip    192.168.1.3
ge-0/0/1.0    up             80   backup   Active      D  3.190 lcl    8.8.8.1
                                                                vip    8.8.8.3
                                                                mas    8.8.8.2

root@vMX2> show vrrp
Interface     State       Group   VR state VR Mode   Timer    Type   Address
ge-0/0/0.0    up             10   backup   Active      D  3.021 lcl    192.168.1.2
                                                                vip    192.168.1.3
                                                                mas    192.168.1.1
ge-0/0/1.0    up             80   master   Active      A  0.795 lcl    8.8.8.2
                                                                vip    8.8.8.3
```