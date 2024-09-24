---
layout: default
title: Lớp vật lý
nav_order: 3.1
parent: CCNA
---

# Physical Layer
{: .no_toc }

Lớp vật lý
{: .fs-6 .fw-300 }

---

## Table of contents
{: .no_toc .text-delta }

1. TOC
{:toc}

---

<h2 style="display:inline-block">why?</h2><p style="display:inline-block">&nbsp;&nbsp;Là môi trường truyền dẫn giữa các thiết bị mạng.</p>

## Cáp xoắn đôi (Twisted Pair)
<br>
![alt text](/docs/CCNA/img/cable-Twisted-Pair.png)

|  |  | Băng thông | Ứng dụng |  |
| --- | --- | --- | --- | --- |
| * | Cat 5e | 100 MHz | 1 Gb/s, 2.5 Gb/s | 100 m |
|  | Cat 6 | 250 MHz | 5 Gb/s, 10 Gb/s | 55 m |
| * | Cat 6a | 500 MHz | 5 Gb/s, 10 Gb/s | 100 m |

<div style="text-align:center">
  <img alt="" style="max-width: 800px" src="https://differencecamp.com/wp-content/uploads/2021/03/T568A-and-T568B.jpg?ezimgfmt=ng:webp/ngcb7" />
</div>

| STT | Đôi | Màu sắc | Chức năng | STT | Đôi | Màu sắc | Chức năng |
| --- | --- | --- | --- | --- | --- | --- | --- |
| 1 | 3 | Trắng Lá | Phát | 1 | 2 | Trắng Cam | Phát |
| 2 | 3 | Lá | Phát | 2 | 2 | Cam | Phát |
| 3 | 2 | Trắng Cam | Thu | 3 | 3 | Trắng Lá | Thu |
| 4 | 1 | Dương | Chưa dùng | 4 | 1 | Dương | Chưa dùng |
| 5 | 1 | Trắng Dương | Chưa dùng | 5 | 1 | Trắng Dương | Chưa dùng |
| 6 | 2 | Cam | Thu | 6 | 3 | Lá | Thu |
| 7 | 4 | Trắng Nâu | Phát | 7 | 4 | Trắng Nâu | Chưa dùng |
| 8 | 4 | Nâu | Chưa dùng | 8 | 4 | Nâu | Chưa dùng |

<h3> Cáp thẳng hay cáp chéo? </h3>

Cáp chéo được sử dụng để kết nối hai thiết bị mạng cùng loại với nhau. Lý do cần dùng cáp chéo là vì nó đảo ngược thứ tự các chân truyền và nhận dữ liệu giữa hai thiết bị. Điều này đảm bảo rằng dữ liệu được gửi từ chân truyền của thiết bị này sẽ được kết nối với chân nhận của thiết bị kia, và ngược lại.

![Alt text](/docs/CCNA/img/cable-crossover.png)

Phân nhóm:

![Alt text](/docs/CCNA/img/cable.png)

* 10/100 Mb/s
  * Cùng nhóm: cáp chéo (MDI - MDI)
  * Khác nhóm: cáp thẳng (MDI - MDIX)
* 1 Gb/s
  * auto MDIX -> cáp thẳng tùy chọn chuẩn (thường là T-568B)

## Cáp quang (Fiber-optic)
<br>
<image src="/docs/CCNA/img/cable-Fiber-optic-working.png" width="50%"/>

![alt text](/docs/CCNA/img/cable-Fiber-optic.png)

## Sóng vô tuyến (Wireless)
<br>
\- Bluetooth<br>
\- Cellular networks: 2G, 3G, 4G, 5G, 6G<br>
\- Wireless networks: Wireless LAN (WLAN), Wi-Fi (IEEE 802.11)<br>
\- Viba<br>

## Power over Ethernet (PoE)
<br>
Là công nghệ cho phép cấp nguồn điện một chiều (DC) cho các thiết bị mạng qua cáp Ethernet. Ví dụ: Camera IP, điện thoại VoIP.

![alt text](/docs/CCNA/img/PoE.png)

Có 3 mode: <br>
! auto - Tự động phát hiện nếu thiết bị kết nối yêu cầu cấp nguồn, switch kiểm tra nguồn đảm bảo sẽ cấp cho thiết bị. Nếu thiết bị yêu cầu nguồn vượt quá ngưỡng thiết lập, sẽ tắt port.<br>
! static - Switch phân bổ nguồn sẵn cho port kể cả không có thiết bị kết nối. Tự động phát hiện nếu thiết bị kết nối yêu cầu cấp nguồn. Nếu thiết bị yêu cầu nguồn vượt quá ngưỡng thiết lập, sẽ tắt port.<br>
! never - Vô hiệu cấp nguồn trên port.<br>

