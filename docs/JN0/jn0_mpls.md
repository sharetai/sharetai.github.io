---
layout: default
title: MPLS
nav_order: 18
parent: JN0
---

# Multiprotocol Label Switching
{: .no_toc }

Chuyển mạch nhãn đa giao thức
{: .fs-6 .fw-300 }

---

## TABLE OF CONTENTS
{: .no_toc .text-delta }

1. TOC
{:toc}

---

![](/docs/JN0/img/14.png)

## Chuẩn bị

* Cấu hình interfaces

```
# vMX1
set interfaces ge-0/0/0 unit 0 family inet address 10.0.12.1/29
set interfaces lo0 unit 0 family inet address 1.1.1.1/32

# vMX2
set interfaces ge-0/0/0 unit 0 family inet address 10.0.23.2/29
set interfaces ge-0/0/1 unit 0 family inet address 10.0.12.2/29
set interfaces lo0 unit 0 family inet address 2.2.2.2/32

# vMX3
set interfaces ge-0/0/0 unit 0 family inet address 10.0.34.3/29
set interfaces ge-0/0/1 unit 0 family inet address 10.0.23.3/29
set interfaces lo0 unit 0 family inet address 3.3.3.3/32

# vMX4
set interfaces ge-0/0/1 unit 0 family inet address 10.0.34.4/29
set interfaces lo0 unit 0 family inet address 4.4.4.4/32
```

* (Optional) Cấu hình OSPF -> để ping thông. Nếu ko cấu hình OSPF có thể dùng bắt gói để kiểm tra.

```
# vMX1
set protocols ospf area 0.0.0.0 interface lo0.0
set protocols ospf area 0.0.0.0 interface ge-0/0/0.0

# vMX2 + vMX3
set protocols ospf area 0.0.0.0 interface lo0.0
set protocols ospf area 0.0.0.0 interface ge-0/0/0.0
set protocols ospf area 0.0.0.0 interface ge-0/0/1.0

# vMX4
set protocols ospf area 0.0.0.0 interface lo0.0
set protocols ospf area 0.0.0.0 interface ge-0/0/1.0
```

## Cấu hình MPLS interfaces

```
# vMX1
set interfaces ge-0/0/0 unit 0 family mpls
set protocols mpls interface ge-0/0/0.0

# vMX2 + vMX3
set interfaces ge-0/0/0 unit 0 family mpls
set interfaces ge-0/0/1 unit 0 family mpls
set protocols mpls interface ge-0/0/0.0
set protocols mpls interface ge-0/0/1.0

# vMX4
set interfaces ge-0/0/1 unit 0 family mpls
set protocols mpls interface ge-0/0/1.0
```

## Cấu hình Static LSP

```
# vMX1 (Ingress Router)
set routing-options static route 4.4.4.4/32 static-lsp-next-hop R1-to-R4
set protocols mpls static-label-switched-path R1-to-R4 ingress next-hop 10.0.12.2
set protocols mpls static-label-switched-path R1-to-R4 ingress to 4.4.4.4
set protocols mpls static-label-switched-path R1-to-R4 ingress push 1000822

# vMX2 (Transit Router)
set protocols mpls static-label-switched-path R1-to-R4 transit 1000822 next-hop 10.0.23.3
set protocols mpls static-label-switched-path R1-to-R4 transit 1000822 swap 1000675

# vMX3 (Penultimate Router)
set protocols mpls static-label-switched-path R1-to-R4 transit 1000675 next-hop 10.0.34.4
set protocols mpls static-label-switched-path R1-to-R4 transit 1000675 pop

# vMX4 (Egress Router)
// no configuration needed
```

## Kiểm tra

```
root@vMX1> show route table inet.3

inet.3: 1 destinations, 1 routes (1 active, 0 holddown, 0 hidden)
+ = Active Route, - = Last Active, * = Both

4.4.4.4/32         *[MPLS/6/1] 00:39:58, metric 0
                    > to 10.0.12.2 via ge-0/0/0.0, Push 1000822

root@vMX2> show route table mpls.0 | find 1000822
1000822            *[MPLS/6] 00:44:07, metric 1
                    > to 10.0.23.3 via ge-0/0/0.0, Swap 1000675

root@vMX3> show route table mpls.0 | find 1000675
1000675            *[MPLS/6] 00:38:49, metric 1
                    > to 10.0.34.4 via ge-0/0/0.0, Pop
1000675(S=0)       *[MPLS/6] 00:38:49, metric 1
                    > to 10.0.34.4 via ge-0/0/0.0, Pop
```