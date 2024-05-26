---
layout: default
title: IPv6
nav_order: 23
parent: CCNA
---

# Internet Protocol Version 6
{: .no_toc }

Giao thức Internet phiên bản 6
{: .fs-6 .fw-300 }

---

## Table of contents
{: .no_toc .text-delta }

1. TOC
{:toc}

---

## Giới thiệu

2001:0000:0000:000A:0000:0000:0000:0001

2001::A:0000:0000:0000:1

![alt text](/docs/CCNA/img/ipv6-type.png)

## IPv6 Routing

![image](/docs/CCNA/img/ipv6-routing.png)

### IPv6 Static Route

```
R1(config)#ipv6 unicast-routing 
R1(config)#ipv6 route FC00:2::/64 2001::2

R2(config)#ipv6 unicast-routing 
R2(config)#ipv6 route FC00:1::/64 2001::1
```

### IPv6 OSPF Route

* __R1__

```
R1(config)#ipv6 unicast-routing 
R1(config)#ipv6 router ospf 1
R1(config-rtr)#router-id 1.1.1.1

R1(config)#int g0/0
R1(config-if)#ipv6 ospf 1 area 0
R1(config-if)#int g0/1
R1(config-if)#ipv6 ospf 1 area 0
```

* __R1__

```
R2(config)#ipv6 unicast-routing 
R2(config)#ipv6 router ospf 1
R2(config-rtr)#router-id 2.2.2.2

R2(config)#int g0/0
R2(config-if)#ipv6 ospf 1 area 0
R2(config-if)#int g0/1
R2(config-if)#ipv6 ospf 1 area 0
```
