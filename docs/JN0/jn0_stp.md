---
layout: default
title: STP
nav_order: 15
parent: JN0
---

# Spanning Tree Protocol
{: .no_toc }

Giao thức chống loop lớp 2
{: .fs-6 .fw-300 }

---

## TABLE OF CONTENTS
{: .no_toc .text-delta }

1. TOC
{:toc}

---

![](/docs/JN0/img/15.png)

## Cấu hình

```
# vMX1 + vMX2 + vMX3

set bridge-domains vlan_100 vlan-id 100

set interfaces ge-0/0/0 vlan-tagging
set interfaces ge-0/0/0 unit 0 family bridge interface-mode trunk
set interfaces ge-0/0/0 unit 0 family bridge vlan-id-list 100
set interfaces ge-0/0/1 vlan-tagging
set interfaces ge-0/0/1 unit 0 family bridge interface-mode trunk
set interfaces ge-0/0/1 unit 0 family bridge vlan-id-list 100

set protocols rstp interface ge-0/0/0
set protocols rstp interface ge-0/0/1
```

## Kiểm tra

Kiểm tra bằng lệnh `show spanning-tree bridge`

```
root@vMX1> show spanning-tree bridge
STP bridge parameters
Routing instance name               : GLOBAL
Context ID                          : 0
Enabled protocol                    : RSTP
  Root ID                           : 32768.00:05:86:71:50:d0
  Hello time                        : 2 seconds
  Maximum age                       : 20 seconds
  Forward delay                     : 15 seconds
  Message age                       : 0
  Number of topology changes        : 3
  Time since last topology change   : 236 seconds
  Local parameters
    Bridge ID                       : 32768.00:05:86:71:50:d0
    Extended system ID              : 0

root@vMX2> show spanning-tree bridge
STP bridge parameters
Routing instance name               : GLOBAL
Context ID                          : 0
Enabled protocol                    : RSTP
  Root ID                           : 32768.00:05:86:71:50:d0
  Root cost                         : 20000
  Root port                         : ge-0/0/1
  Hello time                        : 2 seconds
  Maximum age                       : 20 seconds
  Forward delay                     : 15 seconds
  Message age                       : 1
  Number of topology changes        : 5
  Time since last topology change   : 220 seconds
  Local parameters
    Bridge ID                       : 32768.00:05:86:71:8e:d0
    Extended system ID              : 0

root@vMX3> show spanning-tree bridge
STP bridge parameters
Routing instance name               : GLOBAL
Context ID                          : 0
Enabled protocol                    : RSTP
  Root ID                           : 32768.00:05:86:71:50:d0
  Root cost                         : 20000
  Root port                         : ge-0/0/0
  Hello time                        : 2 seconds
  Maximum age                       : 20 seconds
  Forward delay                     : 15 seconds
  Message age                       : 1
  Number of topology changes        : 3
  Time since last topology change   : 226 seconds
  Local parameters
    Bridge ID                       : 32768.00:05:86:71:f0:d0
    Extended system ID              : 0
```

Kiểm tra bằng lệnh `show spanning-tree interface`

```
root@vMX1> show spanning-tree interface

Spanning tree interface parameters for instance 0

Interface    Port ID    Designated      Designated         Port    State  Role
                         port ID        bridge ID          Cost
ge-0/0/0         128:1        128:1  32768.0005867150d0     20000  FWD    DESG
ge-0/0/1         128:2        128:2  32768.0005867150d0     20000  FWD    DESG

root@vMX2> show spanning-tree interface

Spanning tree interface parameters for instance 0

Interface    Port ID    Designated      Designated         Port    State  Role
                         port ID        bridge ID          Cost
ge-0/0/0         128:1        128:1  32768.000586718ed0     20000  FWD    DESG
ge-0/0/1         128:2        128:1  32768.0005867150d0     20000  FWD    ROOT

root@vMX3> show spanning-tree interface

Spanning tree interface parameters for instance 0

Interface    Port ID    Designated      Designated         Port    State  Role
                         port ID        bridge ID          Cost
ge-0/0/0         128:1        128:2  32768.0005867150d0     20000  FWD    ROOT
ge-0/0/1         128:2        128:1  32768.000586718ed0     20000  BLK    ALT
```

Bổ sung cấu hình vlan access + Thêm PC và dùng wirehark test ping, bắt gói tin.

```
# vMX2 + vMX3
set interfaces ge-0/0/3 unit 0 family bridge interface-mode access
set interfaces ge-0/0/3 unit 0 family bridge vlan-id 100
```