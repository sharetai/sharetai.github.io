<!-- ---
layout: default
title: LDP & RSVP
nav_order: 1
parent: JN0
--- -->

# Label Distribution Protocol and Resource Reservation Protocol
{: .no_toc }

Giao thức phân phối nhãn
{: .fs-6 .fw-300 }

---

## Table of contents
{: .no_toc .text-delta }

1. TOC
{:toc}

---

## Chuẩn bị

* Cấu hình interfaces

```
set interfaces ge-0/0/0 unit 0 family inet address 10.0.12.1/29
set interfaces lo0 unit 0 family inet address 1.1.1.1/32

set interfaces ge-0/0/0 unit 0 family inet address 10.0.23.2/29
set interfaces ge-0/0/1 unit 0 family inet address 10.0.12.2/29
set interfaces ge-0/0/2 unit 0 family inet address 10.0.25.2/29
set interfaces lo0 unit 0 family inet address 2.2.2.2/32

set interfaces ge-0/0/0 unit 0 family inet address 10.0.34.3/29
set interfaces ge-0/0/1 unit 0 family inet address 10.0.23.3/29
set interfaces ge-0/0/3 unit 0 family inet address 10.0.35.3/29
set interfaces lo0 unit 0 family inet address 3.3.3.3/32

set interfaces ge-0/0/1 unit 0 family inet address 10.0.34.4/29
set interfaces lo0 unit 0 family inet address 4.4.4.4/32

set interfaces ge-0/0/2 unit 0 family inet address 10.0.35.5/29
set interfaces ge-0/0/3 unit 0 family inet address 10.0.25.5/29
set interfaces lo0 unit 0 family inet address 5.5.5.5/32
```

* Cấu hình OSPF

```
set protocols ospf area 0.0.0.0 interface lo0.0
set protocols ospf area 0.0.0.0 interface ge-0/0/0.0

set protocols ospf area 0.0.0.0 interface lo0.0
set protocols ospf area 0.0.0.0 interface ge-0/0/0.0
set protocols ospf area 0.0.0.0 interface ge-0/0/1.0
set protocols ospf area 0.0.0.0 interface ge-0/0/2.0

set protocols ospf area 0.0.0.0 interface lo0.0
set protocols ospf area 0.0.0.0 interface ge-0/0/0.0
set protocols ospf area 0.0.0.0 interface ge-0/0/1.0
set protocols ospf area 0.0.0.0 interface ge-0/0/3.0

set protocols ospf area 0.0.0.0 interface lo0.0
set protocols ospf area 0.0.0.0 interface ge-0/0/1.0

set protocols ospf area 0.0.0.0 interface lo0.0
set protocols ospf area 0.0.0.0 interface ge-0/0/2.0
set protocols ospf area 0.0.0.0 interface ge-0/0/3.0
```

## Cấu hình MPLS interfaces

```
set interfaces ge-0/0/0 unit 0 family mpls
set interfaces lo0 unit 0 family mpls
set protocols mpls interface ge-0/0/0.0
set protocols mpls interface lo0.0

set interfaces ge-0/0/0 unit 0 family mpls
set interfaces ge-0/0/1 unit 0 family mpls
set interfaces ge-0/0/2 unit 0 family mpls
set interfaces lo0 unit 0 family mpls
set protocols mpls interface ge-0/0/0.0
set protocols mpls interface ge-0/0/1.0
set protocols mpls interface ge-0/0/2.0
set protocols mpls interface lo0.0

set interfaces ge-0/0/0 unit 0 family mpls
set interfaces ge-0/0/1 unit 0 family mpls
set interfaces ge-0/0/3 unit 0 family mpls
set interfaces lo0 unit 0 family mpls
set protocols mpls interface ge-0/0/0.0
set protocols mpls interface ge-0/0/1.0
set protocols mpls interface ge-0/0/3.0
set protocols mpls interface lo0.0

set interfaces ge-0/0/1 unit 0 family mpls
set interfaces lo0 unit 0 family mpls
set protocols mpls interface ge-0/0/1.0
set protocols mpls interface lo0.0

set interfaces ge-0/0/2 unit 0 family mpls
set interfaces ge-0/0/3 unit 0 family mpls
set interfaces lo0 unit 0 family mpls
set protocols mpls interface ge-0/0/2.0
set protocols mpls interface ge-0/0/3.0
set protocols mpls interface lo0.0
```

## Cấu hình LDP

```
set protocols ldp interface ge-0/0/0.0
set protocols ldp interface lo0.0

set protocols ldp interface ge-0/0/0.0
set protocols ldp interface ge-0/0/1.0
set protocols ldp interface ge-0/0/2.0
set protocols ldp interface lo0.0

set protocols ldp interface ge-0/0/0.0
set protocols ldp interface ge-0/0/1.0
set protocols ldp interface ge-0/0/3.0
set protocols ldp interface lo0.0

set protocols ldp interface ge-0/0/1.0
set protocols ldp interface lo0.0

set protocols ldp interface ge-0/0/2.0
set protocols ldp interface ge-0/0/3.0
set protocols ldp interface lo0.0
```