---
layout: default
title: STP
nav_order: 21
parent: CCNA
---

# Spanning Tree Protocol
{: .no_toc }

Giao thức chống loop lớp 2
{: .fs-6 .fw-300 }

---

## Table of contents
{: .no_toc .text-delta }

1. TOC
{:toc}

---

## Giới thiệu

Spanning Tree Protocol (STP) là một giao thức chống loop khi xây dựng các đường dự phòng cho Switch, STP cho phép các Switch /Bridge truyền thông với nhau để phát hiện vòng lặp vật lý trong mạng, sau đó chuyển đổi mô hình sang cấu trúc cây (Tree)

Các bước:

Bước 1: Chọn Root Bridge

- Bridge ID (min) = Priority (default: 32768) + MAC

Bước 2: Chọn Root Port cho mỗi Non-Root Bridge

- Pathcost (min) (1gb/s=4,100mb/s=19,..)
- Port ID (min)

Bước 3: Chọn Designed Port cho mỗi Segment

- Pathcost
- Bridge ID

## Cấu hình

```
// Lệnh hiển thị STP
SW#show spanning-tree

// Lệnh chuyển Root Bridge
SW(config)#spanning-tree vlan 1 root primary
// hoặc 
SW(config)#spanning-tree vlan 1 priority <number>
```

## Giải pháp PVST trên switch cisco

![Alt text](/docs/CCNA/img/stp-pvst-1.png)

![Alt text](/docs/CCNA/img/stp-pvst-2.png)
