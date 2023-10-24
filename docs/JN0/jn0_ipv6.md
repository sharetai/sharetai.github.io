---
layout: default
title: IPv6
nav_order: 6
parent: JN0
---

# IPv6
{: .no_toc }

Mô hình OSI và mô hình TCP/IP
{: .fs-6 .fw-300 }

---

## Table of contents
{: .no_toc .text-delta }

1. TOC
{:toc}

---

![](/docs/JN0/img/4.png)

## Interface

{: .note-title }
> Syntax
>
> __# set interfaces__ _interface-name_ __unit__ _unit-number_ __family inet6 address__ _source_

```
# vMX1
set interfaces lo0 unit 0 family inet6 address 1::1/128
set interfaces ge-0/0/0 unit 0 family inet6 address 1002::1/64

# vMX2
set interfaces lo0 unit 0 family inet6 address 2::2/128
set interfaces ge-0/0/1 unit 0 family inet6 address 1002::2/64
set interfaces ge-0/0/0 unit 0 family inet6 address 2003::2/64

# vMX3
set interfaces lo0 unit 0 family inet6 address 3::3/128
set interfaces ge-0/0/1 unit 0 family inet6 address 2003::3/64
```

## Static Route

{: .note-title }
> Syntax
>
> __# set routing-options rib inet6.0 static route__ _destination_ __next-hop__ _next-hop_

```
# vMX1
set routing-options rib inet6.0 static route 2::2/128 next-hop 1002::2
set routing-options rib inet6.0 static route 3::3/128 next-hop 1002::2

# vMX2
set routing-options rib inet6.0 static route 1::1/128 next-hop 1002::1
set routing-options rib inet6.0 static route 3::3/128 next-hop 2003::3

# vMX3
set routing-options rib inet6.0 static route 1::1/128 next-hop 2003::2
set routing-options rib inet6.0 static route 2::2/128 next-hop 2003::2
```

## OSPF Route

{: .note-title }
> Syntax
>
> __# set protocols ospf3 area__ _area-id_ __interface__ _interface-name_

```
# vMX1
set protocols ospf3 area 0.0.0.0 interface lo0.0
set protocols ospf3 area 0.0.0.0 interface ge-0/0/0.0

# vMX2
set protocols ospf3 area 0.0.0.0 interface lo0.0
set protocols ospf3 area 0.0.0.0 interface ge-0/0/0.0
set protocols ospf3 area 0.0.0.0 interface ge-0/0/1.0

# vMX3
set protocols ospf3 area 0.0.0.0 interface lo0.0
set protocols ospf3 area 0.0.0.0 interface ge-0/0/1.0
```