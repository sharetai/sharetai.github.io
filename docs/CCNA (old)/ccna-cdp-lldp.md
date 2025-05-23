---
layout: default
title: CDP/LLDP
nav_order: 5
parent: CCNA (old)
---

# Cisco Discovery Protocol / Link Layer Discovery Protocol
{: .no_toc }

Giao thức thu thập thông tin các thiết bị láng giềng
{: .fs-6 .fw-300 }

---

## TABLE OF CONTENTS
{: .no_toc .text-delta }

1. TOC
{:toc}

---

## CDP

__CDP__ là giao thức riêng của Cisco dùng để thu thập thông tin về neighbor (láng giềng). Sử dụng CDP, ta có thể biết được thông tin phần cứng của các thiết bị gần kề, thông tin này hữu ích trong xử lý sự cố hay kiểm soả thiết bị trong mạng.

```
# show cdp
# show cdp neighbors
# show cdp neighbors detail
# show cdp entry *
# show cdp interface
```

```
(config)# no cdp run
(config)# cdp run
(config)# interface e0/0
(config-if)# no cdp enable
```

## LLDP

Tương tự CDP. Khác, __LLDP__ là chuẩn mở.

```
# show lldp neighbors
```

```
(config)# lldp run
(config)# interface e0/0
(config-if)# no lldp receive
(config-if)# no lldp transmit
```
