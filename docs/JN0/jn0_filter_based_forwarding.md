---
layout: default
title: Filter-Based Forwarding
nav_order: 10
parent: JN0
---

# Filter-Based Forwarding
{: .no_toc }

Chuyển tiếp dựa vào bộ lọc
{: .fs-6 .fw-300 }

---

## Table of contents
{: .no_toc .text-delta }

1. TOC
{:toc}

---

## Chuẩn bị

![](/docs/JN0/img/8.png)

* Cấu hình interface

```
# vMX1

set interfaces ge-0/0/0 unit 0 family inet address 172.0.1.1/24
set interfaces ge-0/0/0 unit 0 family inet address 172.0.2.1/24
set interfaces ge-0/0/1 unit 0 family inet address 10.0.12.1/29
set interfaces ge-0/0/2 unit 0 family inet address 10.0.13.1/29

# ISP-A

set interfaces ge-0/0/0 unit 0 family inet address 10.0.12.2/29
set interfaces ge-0/0/1 unit 0 family inet address 10.0.24.2/29

# ISP-B

set interfaces ge-0/0/0 unit 0 family inet address 10.0.13.3/29
set interfaces ge-0/0/1 unit 0 family inet address 10.0.34.3/29

# vMX4

set interfaces ge-0/0/1 unit 0 family inet address 10.0.24.4/29
set interfaces ge-0/0/2 unit 0 family inet address 10.0.34.4/29
set interfaces lo0 unit 0 family inet address 8.8.8.8/24
```

* Cấu hình định tuyến OSPF từ ISP đi lên

```
# ISP-A

set protocols ospf area 0.0.0.0 interface ge-0/0/1.0

# ISP-B

set protocols ospf area 0.0.0.0 interface ge-0/0/1.0

# vMX4

set protocols ospf area 0.0.0.0 interface lo0.0
set protocols ospf area 0.0.0.0 interface ge-0/0/1.0
set protocols ospf area 0.0.0.0 interface ge-0/0/2.0
```

* Cấu hình default route để mạng bên dưới đẩy gói tin ra internet lên các ISP

```
# vMX1

set routing-options static route 0.0.0.0/0 next-hop 10.0.12.2
set routing-options static route 0.0.0.0/0 next-hop 10.0.13.3
```

* Cấu hình static route và quảng bá vào miền OSPF để mạng bên trên có thể phản hồi gói tin xuống mạng bên dưới

```
# ISP-A

set routing-options static route 172.0.1.0/24 next-hop 10.0.12.1
set policy-options policy-statement static-to-ospf term static-accept from protocol static
set policy-options policy-statement static-to-ospf term static-accept then accept
set protocols ospf export static-to-ospf

# ISP-B

set routing-options static route 172.0.2.0/24 next-hop 10.0.13.1
set policy-options policy-statement static-to-ospf term static-accept from protocol static
set policy-options policy-statement static-to-ospf term static-accept then accept
set protocols ospf export static-to-ospf
```

* Kiểm tra trước khi cấu hình `FBF`, toàn bộ gói tin bị đẩy về 1 hướng. Lý do bảng định tuyến chỉ chọn 1 next-hop cho 1 destination.

```
root@vMX1# run show route

inet.0: 9 destinations, 9 routes (9 active, 0 holddown, 0 hidden)
+ = Active Route, - = Last Active, * = Both

0.0.0.0/0          *[Static/5] 00:03:02
                    > to 10.0.12.2 via ge-0/0/1.0
                      to 10.0.13.3 via ge-0/0/2.0
...

VPC6> trace 8.8.8.8
trace to 8.8.8.8, 8 hops max, press Ctrl+C to stop
 1   172.0.1.1   1.977 ms  1.124 ms  1.687 ms
 2   10.0.12.2   4.039 ms  2.035 ms  3.549 ms

VPC7> trace 8.8.8.8
trace to 8.8.8.8, 8 hops max, press Ctrl+C to stop
 1   172.0.1.1   13.557 ms  1.291 ms  1.003 ms
 2   10.0.12.2   11.352 ms  2.968 ms  4.289 ms
```


## Bước 1: Cấu hình và áp Match Filter

Nếu src `172.0.1.0/24` đẩy về bảng `routing-instance ISP-A`. Nếu src `172.0.2.0/24` đẩy về bảng `routing-instance ISP-B`.

```
# vMX1

set firewall family inet filter my-match-filter term match-1 from source-address 172.0.1.0/24
set firewall family inet filter my-match-filter term match-1 then routing-instance ISP-A
set firewall family inet filter my-match-filter term match-2 from source-address 172.0.2.0/24
set firewall family inet filter my-match-filter term match-2 then routing-instance ISP-B

set interfaces ge-0/0/0 unit 0 family inet filter input my-match-filter
```

## Bước 2: Cấu hình Routing Instances

Cấu hình `default route` cho 2 bảng routing-instances ISP-A và ISP-B.

```
# vMX1

set routing-instances ISP-A instance-type forwarding
set routing-instances ISP-A routing-options static route 0.0.0.0/0 next-hop 10.0.12.2
set routing-instances ISP-B instance-type forwarding
set routing-instances ISP-B routing-options static route 0.0.0.0/0 next-hop 10.0.13.3
```

## Bước 3: Cấu hình RIB Group

Cấu hình rib group giữa 2 bảng ISP-A và ISP-B với bảng inet.0 để chia sẻ các giao diện định tuyến. Mục đích để đưa các giao diện định tuyến từ inet.0 vào các instances.

```
# vMX1

set routing-options rib-groups my-rib-group import-rib inet.0
set routing-options rib-groups my-rib-group import-rib ISP-A.inet.0
set routing-options rib-groups my-rib-group import-rib ISP-B.inet.0

set routing-options interface-routes rib-group inet my-rib-group
```

## Kiểm tra

Các gói tin đã được đẩy về 2 hướng khác nhau.

```
root@vMX1# run show route table ISP-A.inet.0

ISP-A.inet.0: 9 destinations, 9 routes (9 active, 0 holddown, 0 hidden)
+ = Active Route, - = Last Active, * = Both

0.0.0.0/0          *[Static/5] 00:00:45
                    > to 10.0.12.2 via ge-0/0/1.0
...

root@vMX1# run show route table ISP-B.inet.0

ISP-B.inet.0: 9 destinations, 9 routes (9 active, 0 holddown, 0 hidden)
+ = Active Route, - = Last Active, * = Both

0.0.0.0/0          *[Static/5] 00:00:51
                    > to 10.0.13.3 via ge-0/0/2.0
...

VPC6> trace 8.8.8.8
trace to 8.8.8.8, 8 hops max, press Ctrl+C to stop
 1   172.0.1.1   2.184 ms  2.463 ms  1.180 ms
 2   10.0.12.2   3.424 ms  2.211 ms  2.024 ms

VPC7> trace 8.8.8.8
trace to 8.8.8.8, 8 hops max, press Ctrl+C to stop
 1   172.0.1.1   1.253 ms  1.213 ms  2.203 ms
 2   10.0.13.3   8.871 ms  2.231 ms  2.250 ms
```
