---
layout: default
title: TCP vs UDP
nav_order: 2.1
parent: CCNA
---

# TCP vs UDP
{: .no_toc }

Transmission Control Protocol vs User Datagram Protocol
{: .fs-6 .fw-300 }

_Nguồn tham khảo đầy đủ: [Tự học CCNA](https://www.youtube.com/playlist?list=PLhchcQ1p5Tc9_LOTMsjK_Mk2xZZR1VChu)_

---

## Table of contents
{: .no_toc .text-delta }

1. TOC
{:toc}

---

![image](https://user-images.githubusercontent.com/56266496/165347318-7a7fe6b7-5b07-4520-9382-413966c3e954.png)

![image](https://user-images.githubusercontent.com/56266496/165347348-6856c549-3497-488f-95e3-e86e81db329a.png)

---

## Chức năng của lớp transport

- Ghép phiên kết nối
- Phân mảnh dữ liệu
- 3 bước bắt tay
- Đảm bảo truyền thông tin cậy
- Điều tiết luồng

![](/docs/CCNA/img/tcp-udp-encap.png)

Mặc dù máy tính chỉ có 1 card mạng, nhưng tại một thời điểm có thể mở rất nhiều ứng dụng mạng khác nhau thông qua việc mở nhiều phiên ứng dụng đồng thời.

Xét trường hợp server gửi dữ liệu có kích thước 10M đến máy trạm. Thì 10M này sẽ được phân mảnh thành các gói tin có kích thước tối đa 1480 bytes (+20 bytes ip header = 1500 bytes (MTU - Maxium Transmission Unit)).

Nhưng trước khi quá trình truyền thông thực sự diễn ra. 2 thiết bị đầu cuối cần trải qua quá trình bắt ta 3 bước để thoả thuận xem kích thức segment tối đa sử dụng là bao nhiêu do MTU server là 9000 bytes và MTU client là 1500 bytes.

TCP đảm bảo truyền thông tin cậy. UDP đảm bảo truyền dữ liệu thời gian thực.

TCP có thể cải thiện tốc độ nhờ vào việc điều chỉnh trường `window size` để điều tiết lưu lượng.

## TCP vs UDP

![](/docs/CCNA/img/tcp-udp.gif)

![Alt text](/docs/CCNA/img/tcp-udp.png)

## Session

![](/docs/CCNA/img/tcp-udp-session.png)

## Flow control

Điều tiết luồng thông qua trường `window size`

![](/docs/CCNA/img/tcp-udp-flow-control_1.png)

![](/docs/CCNA/img/tcp-udp-flow-control_2.png)

![](/docs/CCNA/img/tcp-udp-flow-control_3.png)

