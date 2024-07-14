---
layout: default
title: VLAN
nav_order: 14
parent: JN0
---

# Virtual Local Area Network
{: .no_toc }

Mạng nội bộ ảo
{: .fs-6 .fw-300 }

---

## Table of contents
{: .no_toc .text-delta }

1. TOC
{:toc}

---

## VLAN

![](/docs/JN0/img/12.png)

* Tạo VLAN

```
# vMX1
set bridge-domains vlan_100 vlan-id 100
set bridge-domains vlan_200 vlan-id 200

# vMX2 (Tương tụ)
```

* Cấu hình interface mode access

```
# vMX1
set interfaces ge-0/0/1 unit 0 family bridge interface-mode access
set interfaces ge-0/0/1 unit 0 family bridge vlan-id 100
set interfaces ge-0/0/2 unit 0 family bridge interface-mode access
set interfaces ge-0/0/2 unit 0 family bridge vlan-id 200

# vMX2 (Tương tụ)
```

* Cấu hình interface mode trunk

```
# vMX1
set interfaces ge-0/0/0 vlan-tagging
set interfaces ge-0/0/0 unit 0 family bridge interface-mode trunk
set interfaces ge-0/0/0 unit 0 family bridge vlan-id-list [100 200]

# vMX2 (Tương tụ)
```

* Kiểm tra

```
root@vMX1> show bridge domain

Routing instance        Bridge domain            VLAN ID     Interfaces
default-switch          vlan_100                 100
                                                     ge-0/0/0.0
                                                     ge-0/0/1.0
default-switch          vlan_200                 200
                                                     ge-0/0/0.0
                                                     ge-0/0/2.0
```

## IRB interface

![](/docs/JN0/img/13.png)

Integrated Routing and Bridging, cho phép giao tiếp giữa 2 vlan thông qua ip gateway trên IRB interface.

```
# vMX1

set interfaces irb unit 100 family inet address 10.0.100.1/24
set interfaces irb unit 200 family inet address 10.0.200.1/24

set bridge-domains vlan_100 routing-interface irb.100

set bridge-domains vlan_200 routing-interface irb.200
```

Kiểm tra

```
root@vMX1> show interfaces terse irb
Interface               Admin Link Proto    Local                 Remote
irb                     up    up
irb.100                 up    up   inet     10.0.100.1/24
                                   multiservice
irb.200                 up    up   inet     10.0.200.1/24
                                   multiservice

root@vMX1> show route

inet.0: 4 destinations, 4 routes (4 active, 0 holddown, 0 hidden)
+ = Active Route, - = Last Active, * = Both

10.0.100.0/24      *[Direct/0] 00:16:46
                    > via irb.100
10.0.100.1/32      *[Local/0] 00:17:19
                      Local via irb.100
10.0.200.0/24      *[Direct/0] 00:16:46
                    > via irb.200
10.0.200.1/32      *[Local/0] 00:17:19
                      Local via irb.200
```