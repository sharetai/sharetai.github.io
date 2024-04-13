---
layout: default
title: Các loại cáp mạng
nav_order: 3
parent: CCNA
---

# Các loại cáp mạng
{: .no_toc }

Phần này tập trung vào cáp xoắn đôi được phổ biến nhiều hơn cáp quang
{: .fs-6 .fw-300 }

---

## Table of contents
{: .no_toc .text-delta }

1. TOC
{:toc}

---

## Cáp xoắn đôi (Twisted Pair)

<div style="text-align:center">
  <img alt="" style="max-width: 250px" src="https://upload.wikimedia.org/wikipedia/commons/c/cb/UTP_cable.jpg" />
</div>

|  |  | Băng thông | Ứng dụng |  |
| --- | --- | --- | --- | --- |
| * | Cat 5e | 100 MHz | 1 Gb/s, 2.5 Gb/s | 100 m |
|  | Cat 6 | 250 MHz | 10 Gb/s | 55 m |
| * | Cat 6a | 500 MHz | 10 Gb/s | 100 m |

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

## Cáp thẳng hay cáp chéo?

Phân nhóm:

![Alt text](/docs/CCNA/img/cable.png)

* 10/100 Mb/s
  * Cùng nhóm: cáp chéo (MDI - MDI)
  * Khác nhóm: cáp thẳng (MDI - MDIX)
* 1 Gb/s
  * auto MDIX -> cáp thẳng tùy chọn chuẩn (thường là T-568B)
