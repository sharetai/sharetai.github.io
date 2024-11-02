---
layout: default
title: QoS
nav_order: 100
parent: CCNP
---

# Quality of Service
{: .no_toc }

Chất lượng của dịch vụ
{: .fs-6 .fw-300 }

---

## Table of contents
{: .no_toc .text-delta }

1. TOC
{:toc}

---

## [\<Cheat sheet\>](/docs/CCNP/img/QOS.png)
<br>

## [CCNA QoS](/docs/CCNA/ccna-qos/)
<br>

## access-list class-map policy-map
<br>

![alt text](/docs/CCNP/img/qos-acl-cm-pm.png)

* R2
```
enable
conf t
!
ip access-list extended PINGTEST
permit icmp any host 10.0.12.1
!
class-map PINGTEST
match access-group name PINGTEST
!
policy-map PINGTEST
class PINGTEST
set ip precedence 6
!
int e0/0
service-policy output PINGTEST
!
end
```

Verify

```
R2#show access-lists PINGTEST
Extended IP access list PINGTEST
    10 permit icmp any host 10.0.12.1 (10 matches)
R2#show policy-map int e0/0
 Ethernet0/0

  Service-policy output: PINGTEST

    Class-map: PINGTEST (match-all)
      10 packets, 1140 bytes
      5 minute offered rate 0000 bps, drop rate 0000 bps
      Match: access-group name PINGTEST
      QoS Set
        precedence 6
          Packets marked 10

    Class-map: class-default (match-any)
      105 packets, 11335 bytes
      5 minute offered rate 0000 bps, drop rate 0000 bps
      Match: any
R2#
```

__before__

![alt text](/docs/CCNP/img/qos-acl-cm-pm (before).png)

__after__

![alt text](/docs/CCNP/img/qos-acl-cm-pm (after).png)


