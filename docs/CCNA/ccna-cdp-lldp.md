---
layout: default
title: CDP/LLDP
nav_order: 5
parent: CCNA
---

# Cisco Discovery Protocol / Link Layer Discovery Protocol
{: .no_toc }

Giao thức thu thập thông tin các thiết bị láng giềng
{: .fs-6 .fw-300 }

---

## Table of contents
{: .no_toc .text-delta }

1. TOC
{:toc}

---

## CDP

**Cisco Discovery Protocol (CDP)** là giao thức riêng của Cisco dùng để thu thập thông tin về neighbor (láng giềng). Sử dụng CDP, ta có thể biết được thông tin phần cứng của các thiết bị gần kề, thông tin này hữu ích trong xử lý sự cố hay kiểm soả thiết bị trong mạng.

```
# show cdp
# show cdp neighbors
# show cdp neighbors detail
# show cdp entry *
# show cdp interface
```

Bật tắt CDP:

```
(config)# no cdp run
(config)# cdp run
(config)# interface e0/0
(config-if)# no cdp enable
```

## LLDP

Tương tự CDP. Khác, LLDP là chuẩn mở.

```
# show lldp neighbors
```

```
(config)# lldp run
(config)# interface e0/0
(config-if)# no cdp receive
(config-if)# no cdp transmit
```
