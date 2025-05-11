---
layout: default
title: ERP
nav_order: 16
parent: JN0
---

# Ethernet Ring Protection
{: .no_toc }

Giao thức bảo vệ vòng ring layer 2
{: .fs-6 .fw-300 }

---

## TABLE OF CONTENTS
{: .no_toc .text-delta }

1. TOC
{:toc}

---

![](/docs/JN0/img/16.png)

## Bước 1: Tạo Bridge Domains

```
# vMX1 + vMX2 + vMX3 + vMX4 + vMX5 + vMX6

set bridge-domains bd100 vlan-id 100
set bridge-domains bd101 vlan-id 101
set bridge-domains bd200 vlan-id 200
set bridge-domains bd201 vlan-id 201
```

## Bước 2: Cấu hình giao diện trunk

```
# vMX1 + vMX2 + vMX3 + vMX4 + vMX5 + vMX6

set interfaces ge-0/0/0 vlan-tagging
set interfaces ge-0/0/0 unit 0 family bridge interface-mode trunk
set interfaces ge-0/0/0 unit 0 family bridge vlan-id-list 100-1000
set interfaces ge-0/0/1 vlan-tagging
set interfaces ge-0/0/1 unit 0 family bridge interface-mode trunk
set interfaces ge-0/0/1 unit 0 family bridge vlan-id-list 100-1000
```

## Bước 3: Cấu hình RPL Owner Node (Master Node)

```
# vMX3 (RPL Owner Node của erp100)

set protocols protection-group ethernet-ring erp100 ring-protection-link-owner
set protocols protection-group ethernet-ring erp100 west-interface ring-protection-link-end

# vMX6 (RPL Owner Node của erp200)

set protocols protection-group ethernet-ring erp200 ring-protection-link-owner
set protocols protection-group ethernet-ring erp200 east-interface ring-protection-link-end
```

## Bước 4: Cấu hình Normal Node (Transit Node)

```
# vMX1 + vMX2 + vMX3 + vMX4 + vMX5 + vMX6

set protocols protection-group ethernet-ring erp100 east-interface control-channel vlan 101
set protocols protection-group ethernet-ring erp100 east-interface control-channel ge-0/0/0.0
set protocols protection-group ethernet-ring erp100 west-interface control-channel vlan 101
set protocols protection-group ethernet-ring erp100 west-interface control-channel ge-0/0/1.0
set protocols protection-group ethernet-ring erp100 data-channel vlan 100-199

set protocols protection-group ethernet-ring erp200 east-interface control-channel vlan 201
set protocols protection-group ethernet-ring erp200 east-interface control-channel ge-0/0/0.0
set protocols protection-group ethernet-ring erp200 west-interface control-channel vlan 201
set protocols protection-group ethernet-ring erp200 west-interface control-channel ge-0/0/1.0
set protocols protection-group ethernet-ring erp200 data-channel vlan 200-299
```

## Kiểm tra

* Trên 2 RPL Owner node

```
root@vMX3> show protection-group ethernet-ring interface

Ethernet ring port parameters for protection group erp100

Interface    Control Channel  Forward State  Ring Protection Link End  Signal Failure  Admin State
ge-0/0/0     ge-0/0/0.0       forwarding     No                        Clear          IFF ready
ge-0/0/1     ge-0/0/1.0       discarding     Yes                       Clear          IFF ready

Ethernet ring port parameters for protection group erp200

Interface    Control Channel  Forward State  Ring Protection Link End  Signal Failure  Admin State
ge-0/0/0     ge-0/0/0.0       forwarding     No                        Clear          IFF ready
ge-0/0/1     ge-0/0/1.0       forwarding     No                        Clear          IFF ready


root@vMX6> show protection-group ethernet-ring interface

Ethernet ring port parameters for protection group erp100

Interface    Control Channel  Forward State  Ring Protection Link End  Signal Failure  Admin State
ge-0/0/0     ge-0/0/0.0       forwarding     No                        Clear          IFF ready
ge-0/0/1     ge-0/0/1.0       forwarding     No                        Clear          IFF ready

Ethernet ring port parameters for protection group erp200

Interface    Control Channel  Forward State  Ring Protection Link End  Signal Failure  Admin State
ge-0/0/0     ge-0/0/0.0       discarding     Yes                       Clear          IFF ready
ge-0/0/1     ge-0/0/1.0       forwarding     No                        Clear          IFF ready
```

* Trên bất kỳ Normal Node

```
root@vMX5> show protection-group ethernet-ring interface

Ethernet ring port parameters for protection group erp100

Interface    Control Channel  Forward State  Ring Protection Link End  Signal Failure  Admin State
ge-0/0/0     ge-0/0/0.0       forwarding     No                        Clear          IFF ready
ge-0/0/1     ge-0/0/1.0       forwarding     No                        Clear          IFF ready

Ethernet ring port parameters for protection group erp200

Interface    Control Channel  Forward State  Ring Protection Link End  Signal Failure  Admin State
ge-0/0/0     ge-0/0/0.0       forwarding     No                        Clear          IFF ready
ge-0/0/1     ge-0/0/1.0       forwarding     No                        Clear          IFF ready

root@vMX5> show protection-group ethernet-ring vlan

Ethernet ring IFBD parameters for protection group erp100

Interface    Vlan    STP Index   Bridge Domain
ge-0/0/0     100     16          default-switch/bd100
ge-0/0/1     100     17          default-switch/bd100
ge-0/0/0     101     16          default-switch/bd101
ge-0/0/1     101     17          default-switch/bd101

Ethernet ring IFBD parameters for protection group erp200

Interface    Vlan    STP Index   Bridge Domain
ge-0/0/0     200     18          default-switch/bd200
ge-0/0/1     200     19          default-switch/bd200
ge-0/0/0     201     18          default-switch/bd201
ge-0/0/1     201     19          default-switch/bd201
```

## Bổ sung cấu hình vlan access để test ping

```
# vMX1 + vMX5
set interfaces ge-0/0/3 unit 0 family bridge interface-mode access
set interfaces ge-0/0/3 unit 0 family bridge vlan-id 100

# vMX2 + vMX4
set interfaces ge-0/0/3 unit 0 family bridge interface-mode access
set interfaces ge-0/0/3 unit 0 family bridge vlan-id 200
```