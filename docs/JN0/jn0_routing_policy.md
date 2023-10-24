---
layout: default
title: Routing Policy
nav_order: 7
parent: JN0
---

# Routing Policy
{: .no_toc }

Chính sách định tuyến
{: .fs-6 .fw-300 }

---

## Table of contents
{: .no_toc .text-delta }

1. TOC
{:toc}

---

## Chuẩn bị

![](/docs/JN0/img/5.png)

* Interfaces

```
# vMX1
set interfaces ge-0/0/0 unit 0 family inet address 10.0.12.1/29
set interfaces ge-0/0/1 unit 0 family inet address 10.0.13.1/29
set interfaces ge-0/0/3 unit 0 family inet address 172.30.15.2/30
set interfaces lo0 unit 0 family inet address 1.1.1.1/32

# vMX2
set interfaces ge-0/0/0 unit 0 family inet address 10.0.23.2/29
set interfaces ge-0/0/1 unit 0 family inet address 10.0.12.2/29
set interfaces lo0 unit 0 family inet address 2.2.2.2/32

# vMX3
set interfaces ge-0/0/0 unit 0 family inet address 10.0.13.3/29
set interfaces ge-0/0/1 unit 0 family inet address 10.0.23.3/29
set interfaces lo0 unit 0 family inet address 3.3.3.3/32

# ISP
set interfaces ge-0/0/3 unit 0 family inet address 172.30.15.1/30
set interfaces lo0 unit 0 family inet address 8.8.8.8/32
```

* Static Route

```
# vMX1
set routing-options static route 0.0.0.0/0 next-hop 172.30.15.1

# ISP
set routing-options static route 10.0.0.0/8 next-hop 172.30.15.2
```

* OSPF Route

```
# vMX1 + vMX2 + vMX3
set protocols ospf area 0.0.0.0 interface lo0.0
set protocols ospf area 0.0.0.0 interface ge-0/0/0.0
set protocols ospf area 0.0.0.0 interface ge-0/0/1.0
```

## Định nghĩa Policy

```
# vMX1
set policy-options policy-statement static-to-ospf term static-accept from protocol static
set policy-options policy-statement static-to-ospf term static-accept from route-filter 0.0.0.0/0 exact
set policy-options policy-statement static-to-ospf term static-accept then accept
```

## Áp Policy

```
# vMX1
set protocols ospf export static-to-ospf
```

## Kiểm tra

```
[edit]
root@vMX2# run show route protocol ospf exact 0.0.0.0/0

inet.0: 11 destinations, 11 routes (11 active, 0 holddown, 0 hidden)
+ = Active Route, - = Last Active, * = Both

0.0.0.0/0          *[OSPF/150] 00:00:02, metric 0, tag 0
                    > to 10.0.12.1 via ge-0/0/1.0

```

