---
layout: default
title: Lớp ethernet
nav_order: 3.2
parent: CCNA
---

# Ethernet Layer
{: .no_toc }

Lớp ethernet
{: .fs-6 .fw-300 }

---

## Table of contents
{: .no_toc .text-delta }

1. TOC
{:toc}

---

## Ethernet

**Ethernet** là công nghệ mạng được sử dụng nhiều nhất cho mạng LAN hiện nay. Nó định nghĩa hệ thống dây điện *(wire)* và tín hiệu *(signal)* cho lớp Vật lý của mô hình OSI. Đối với lớp Liên kết dữ liệu, nó xác định định dạng khung *(frame)* và giao thức *(protocol)*.

![alt text](/docs/CCNA/img/Ethernet.png)

Là chuẩn **IEEE 802.3**. Sử dụng phương pháp truy cập **Carrier Sense Multiple Access with Collision Detection (CSMA/CD)** và hỗ trợ tốc độ lên đến 100 Gbps. Có thể sử dụng cáp đồng trục, cáp xoắn đôi và cáp quang. Ethernet sử dụng các khung có địa chỉ MAC nguồn và đích để truyền dữ liệu.

**Ethernet Frame**

![alt text](/docs/CCNA/img/Ethernet-Frame.png)

**Ethernet LAN**

![](/docs/CCNA/img/l2-ethernet-lan.gif)

## MAC & IP & ARP

{: .highlight-title }
> Note
>
> __Media Access Control (MAC)__ là địa chỉ dài __48-bit (6 bytes)__, dùng giao tiếp giữa các thiết bị trong môi trường ethernet <br>
> Ví dụ 1 địa chỉ MAC: __D8-D3-85-EB-12-E3__ <br>
> 3 bytes đầu __D8-D3-85__ gọi là __Organizationally Unique Identifier (OUI)__ biểu điễn nhà cung cấp, ở đây là Hewlett Packard (HP) <br>
> 3 bytes cuối là duy nhất trên toàn cầu <br>

![](/docs/CCNA/img/l2-arp.gif)

## Unicast, Broadcast, Multicast

![](/docs/CCNA/img/l2-unicast-broadcast-multicast.png)

## Full duplex vs Half duplex

![](/docs/CCNA/img/l2-fullduplex-halfduplex.png)

## Collision Domain và Broadcast Domain

CSMA/CD

![](/docs/CCNA/img/l2-csma-cd.png)

### Xác định số lượng Collision Domain và Broadcast Domain

03 Collision Domain, 01 Broadcast Domain

![](/docs/CCNA/img/l2-cd-bd_1.png)

09 Collision Domain, 02 Broadcast Domain

![](/docs/CCNA/img/l2-cd-bd_2.png)

08 Collision Domain, 03 Broadcast Domain

![](/docs/CCNA/img/l2-cd-bd_3.png)

07 Collision Domain, 02 Broadcast Domain

![](/docs/CCNA/img/l2-cd-bd_4.png)

09 Collision Domain, 03 Broadcast Domain

![](/docs/CCNA/img/l2-cd-bd_5.png)

