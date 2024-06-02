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

## Spanning Tree Modes: MSTP, PVST+, and RPVST+

### IEEE Open Standard Spanning Tree Modes <br>
__Spanning Tree Protocol (STP) IEEE 802.1D –__ 1 instance <br>
__Rapid Spanning Tree Protocol (RSTP) IEEE 802.1w –__ 1 instance <br>
__Multiple Spanning Tree Protocol (MSTP) IEEE 802.1s –__ nhiều instance và cho phép phân bổ vlan vào các instance <br>

### Cisco Spanning Tree Modes <br>
__Per VLAN Spanning Tree Plus (PVST+) Protocol –__ 1 instance per vlan <br>
__Rapid Per VLAN Spanning Tree Plus (RPVST+) Protocol –__ 1 instance per vlan <br>

```conf
Switch(config)#spanning-tree mode ?
  mst         Multiple spanning tree mode
  pvst        Per-Vlan spanning tree mode
  rapid-pvst  Per-Vlan rapid spanning tree mode
```

## Giải pháp PVST trên switch cisco

![Alt text](/docs/CCNA/img/stp-pvst-1.png)

![Alt text](/docs/CCNA/img/stp-pvst-2.png)



## Portfast, BPDU Guard, Root Guard, Loop Guard

\- PortFast cho phép chuyển đổi tức thời từ trạng thái _blocking_ sang _forwarding_ ngay lập tức, bỏ qua trạng thái _listening_ và _learning_. PortFast chỉ được khuyến nghị sử dụng trên các cổng _non-trunking access ports_, như cổng biên _edge ports_, vì các cổng này thường không gửi cũng như không nhận BPDU. <br>
\- Do PortFast vẫn có thể truyền và nhận BPDU, nên loop vẫn có thể xảy ra. BPDU guard được bật cho phép đưa port vào trạng thái _errdisable_ và shut down cổng PortFast khi cổng đó nhận BPDU. BPDU Guard được sử dụng để bảo vệ mạng khỏi các cuộc tấn công STP. <br>
\- Root Guard được sử dụng để ngăn chặn các cổng trở thành root bridge. <br>
\- Loop Guard được sử dụng để ngăn chặn loop. <br>

![Alt text](/docs/CCNA/img/stp-Portfast-BPDU-Guard-Root-Guard.png)

```conf
# int conf
int e0/1
spanning-tree portfast edge
spanning-tree bpduguard enable

# global conf
spanning-tree portfast edge bpduguard default
int e0/1
spanning-tree portfast edge

# recovery
errdisable recovery cause bpduguard
errdisable recovery interval 30
```

```conf
int e0/2
spanning-tree guard root
```

```conf
int e0/3
spanning-tree guard loop
```

