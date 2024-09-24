---
layout: default
title: Lớp vận chuyển
nav_order: 3.4
parent: CCNA
---

# Transport Layer
{: .no_toc }

Lớp vận chuyển
{: .fs-6 .fw-300 }

---

## Table of contents
{: .no_toc .text-delta }

1. TOC
{:toc}

---

![image](https://user-images.githubusercontent.com/56266496/165347318-7a7fe6b7-5b07-4520-9382-413966c3e954.png)

![image](https://user-images.githubusercontent.com/56266496/165347348-6856c549-3497-488f-95e3-e86e81db329a.png)

---

## Tại sao có lớp transport? (why?)
<br>
___- Đảm bảo truyền dữ liệu đáng tin cậy:___ dữ liệu được truyền đúng thứ tự, không bị mất mát hoặc hư hỏng. <br>
___- Kiểm soát luồng:___ điều chỉnh tốc độ truyền dữ liệu để tránh quá tải mạng. <br>
___- Đa luồng:___ cho phép nhiều luồng dữ liệu được truyền cùng lúc trên một kết nối. <br>

## Chức năng của lớp transport? (what?)
<br>
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

## TCP vs UDP (how?)
<br>
![](/docs/CCNA/img/tcp-udp.gif)

___Giao thức TCP:___ Giao thức TCP (Transmission Control Protocol) là giao thức phổ biến nhất ở Transport Layer. Nó cung cấp dịch vụ truyền dữ liệu đáng tin cậy bằng cách kiểm tra lỗi, điều khiển luồng và đa luồng. <br>
___Giao thức UDP:___ Giao thức UDP (User Datagram Protocol) là một giao thức không đáng tin cậy, không đảm bảo truyền dữ liệu đúng thứ tự hoặc không bị mất mát. Nó được sử dụng trong các ứng dụng không yêu cầu độ tin cậy cao, như truyền âm thanh và video trực tuyến. <br>

| TCP                                                 | UDP                                                       |
| :-------------------------------------------------: | :-------------------------------------------------------: |
| 20 bytes header                                     | 8 bytes header                                            |
| tuần tự (sequence), theo luồng (stream)             | không tuần tự, riêng lẻ (individual)                      |
| có ACK                                              | không có ACK                                              |
| window size dùng điều tiết luồng (flow control)     | không có điều tiết luồng (no flow control)                |
| kiểm lỗi nâng cao, bao gồm checksum                 | chỉ có checksum                                           |
| thiết lập phiên trước truyền (connection-oriented)  | truyền luôn không cần phiên (connectionless)              |
| dữ liệu truyền chậm (slow), đảm bảo (guarantee)     | dữ liệu truyền nhanh (fast), không đảm bảo (no guarantee) |
| dữ liệu nhạy cảm trên tính toàn vẹn (reliable)      | dữ liệu nhạy cảm trên thời gian thực (real time)          |

![Alt text](/docs/CCNA/img/tcp-udp.png)

## Một số khái niệm (who?)
<br>
### Session
<br>
![](/docs/CCNA/img/tcp-udp-session.png)

### Flow control
<br>
Điều tiết luồng thông qua trường `window size`

![](/docs/CCNA/img/tcp-udp-flow-control_1.png)

![](/docs/CCNA/img/tcp-udp-flow-control_2.png)

![](/docs/CCNA/img/tcp-udp-flow-control_3.png)

