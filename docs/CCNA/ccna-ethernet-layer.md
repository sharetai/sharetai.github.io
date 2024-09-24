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

## Tại sao có Ethernet? (why?)
<br>
___- Truyền khung dữ liệu:___ Lớp Ethernet chia dữ liệu thành các khung nhỏ, mỗi khung chứa địa chỉ nguồn, địa chỉ đích và dữ liệu. Việc chia nhỏ dữ liệu giúp dễ dàng quản lý và truyền đi. <br>
___- Kiểm soát truy cập:___ Lớp Ethernet cung cấp các cơ chế để kiểm soát việc truy cập vào môi trường truyền dẫn, tránh xung đột khi nhiều thiết bị muốn truyền dữ liệu cùng một lúc. <br>
___- Phát hiện và sửa lỗi:___ Lớp Ethernet có các cơ chế để phát hiện và sửa các lỗi có thể xảy ra trong quá trình truyền dữ liệu. <br>

## Ethernet là gì? (what?)
<br>
Là chuẩn **IEEE 802.3**. **Ethernet** là công nghệ mạng được sử dụng nhiều nhất cho mạng LAN hiện nay. Nó định nghĩa hệ thống dây điện *(wire)* và tín hiệu *(signal)* cho lớp Vật lý của mô hình OSI, cụ thể là lớp liên kết dữ liệu _Data Link Layer_. Ethernet xác định định dạng khung *(frame)* và giao thức *(protocol)* được truyền đi qua một mạng cục bộ (LAN). Ethernet đảm bảo rằng dữ liệu được truyền đi một cách chính xác và không bị xung đột với các khung dữ liệu khác trên cùng một mạng.

![alt text](/docs/CCNA/img/Ethernet.png)

## Ethernet hoạt động như thế nào? (how?)
<br>
![alt text](/docs/CCNA/img/Ethernet-Frame.png)

__Khung Ethernet:__ Mỗi khung Ethernet có cấu trúc bao gồm: <br>
___- Địa chỉ nguồn:___ Địa chỉ MAC của thiết bị gửi dữ liệu. <br>
___- Địa chỉ đích:___ Địa chỉ MAC của thiết bị nhận dữ liệu. <br>
___- Type:___ Chỉ ra loại dữ liệu được truyền đi. <br>
___- Data:___ Dữ liệu cần truyền. <br>
___- FCS:___ Kiểm tra lỗi khung. <br>

__Truyền dữ liệu:__ Khi một thiết bị muốn gửi dữ liệu, nó sẽ tạo một khung Ethernet và truyền đi trên mạng. Các thiết bị khác trên mạng sẽ kiểm tra địa chỉ đích trong khung. Nếu địa chỉ đích trùng với địa chỉ của mình, thiết bị đó sẽ nhận khung dữ liệu và xử lý.

__Kiểm soát truy cập:__ Ethernet sử dụng các phương pháp như _CSMA/CD (Carrier Sense Multiple Access with Collision Detection)_ để kiểm soát việc truy cập vào môi trường truyền dẫn.

![](/docs/CCNA/img/l2-ethernet-lan.gif)

## Một số khái niệm? (who?)
<br>
### MAC, IP, ARP
<br>
___MAC (Media Access Control):___ Là địa chỉ dài ___48-bit (6 bytes)___, dùng giao tiếp giữa các thiết bị trong môi trường ethernet <br>
Ví dụ 1 địa chỉ MAC: ___D8-D3-85-EB-12-E3___ <br>
3 bytes đầu ___D8-D3-85___ gọi là ___Organizationally Unique Identifier (OUI)___ biểu điễn nhà cung cấp, ở đây là Hewlett Packard (HP) <br>
3 bytes cuối là duy nhất trên toàn cầu <br>

___IP (Internet Protocol):___ Là một địa chỉ logic được gán cho một thiết bị trên mạng. Không giống như MAC, địa chỉ IP có thể thay đổi và được cấu hình thủ công hoặc tự động qua DHCP.

___ARP (Address Resolution Protocol):___ Là một giao thức mạng được sử dụng để chuyển đổi giữa địa chỉ IP và địa chỉ MAC. Khi một thiết bị muốn gửi dữ liệu đến một thiết bị khác, nó sẽ sử dụng ARP để tìm ra địa chỉ MAC tương ứng với địa chỉ IP đích.

![](/docs/CCNA/img/l2-arp.gif)

### Unicast, Broadcast, Multicast
<br>
___Unicast___ là việc gửi dữ liệu từ một nguồn đến một đích duy nhất.	Gửi email, truy cập web, FTP. <br>
___Broadcast___ là việc gửi dữ liệu từ một nguồn đến tất cả các thiết bị trên một mạng. Tìm kiếm thiết bị, gửi thông báo. <br>
___Multicast___ là việc gửi dữ liệu từ một nguồn đến một nhóm thiết bị đặc biệt. Truyền video trực tiếp, trò chơi trực tuyến. <br>

![](/docs/CCNA/img/l2-unicast-broadcast-multicast.png)

### Full duplex, Half duplex
<br>
___Full Duplex___ cho phép truyền dữ liệu theo cả hai hướng cùng một lúc. Điều này có nghĩa là cả hai thiết bị có thể gửi và nhận dữ liệu đồng thời. <br>
___Half Duplex___ chỉ cho phép truyền dữ liệu theo một hướng tại một thời điểm. Điều này có nghĩa là chỉ có một thiết bị có thể gửi dữ liệu trong khi thiết bị kia chỉ có thể nhận dữ liệu. <br>

![](/docs/CCNA/img/l2-fullduplex-halfduplex.png)

### Collision Domain, Broadcast Domain
<br>
___Collision Domain___ là một khu vực trên mạng nơi các thiết bị có thể xung đột khi truyền dữ liệu cùng một lúc. Nếu hai thiết bị trong cùng một Collision Domain cố gắng truyền dữ liệu cùng một lúc, sẽ xảy ra xung đột và cả hai gói dữ liệu đều bị mất. Một mạng Ethernet Hub tạo ra một Collision Domain duy nhất. Tất cả các thiết bị kết nối với Hub đều nằm trong cùng một Collision Domain. <br>
___Broadcast Domain___ là một khu vực trên mạng nơi các gói tin broadcast có thể được truyền đi đến tất cả các thiết bị trong khu vực đó. Một mạng Ethernet Switch có thể chia một mạng thành nhiều Broadcast Domain, tùy thuộc vào cấu hình của Switch. <br>

<h3> Xác định số lượng Collision Domain và Broadcast Domain </h3> 
<br>
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

### CSMA/CD
<br>

CSMA/CD (Carrier Sense Multiple Access with Collision Detection) là một phương thức truy cập đa truy nhập được sử dụng trong các mạng Ethernet để kiểm soát việc truy cập vào môi trường truyền dẫn. Nó giúp tránh xung đột khi nhiều thiết bị muốn truyền dữ liệu cùng một lúc.

__Nguyên lý hoạt động:__

___- Carrier Sense:___ Trước khi truyền dữ liệu, một thiết bị sẽ kiểm tra xem môi trường truyền dẫn có đang được sử dụng hay không. Nếu môi trường đang bận, thiết bị sẽ chờ cho đến khi môi trường trống. <br>
___- Multiple Access:___ Nếu môi trường trống, nhiều thiết bị có thể truyền dữ liệu cùng một lúc. <br>
___- Collision Detection:___ Trong quá trình truyền dữ liệu, nếu một thiết bị phát hiện xung đột với một thiết bị khác, nó sẽ ngừng truyền dữ liệu và chờ một thời gian ngẫu nhiên trước khi thử lại. <br>

__Ưu điểm:__

___- Dễ triển khai:___ CSMA/CD là một phương thức đơn giản và dễ triển khai. <br>
___- Hiệu quả:___ CSMA/CD có thể hoạt động hiệu quả trong các mạng nhỏ. <br>

__Nhược điểm:__

___- Xung đột:___ CSMA/CD có thể dẫn đến xung đột khi nhiều thiết bị truyền dữ liệu cùng một lúc, làm giảm hiệu suất mạng. <br>
___- Không phù hợp cho mạng lớn:___ CSMA/CD không phù hợp cho các mạng lớn với nhiều thiết bị, vì khả năng xảy ra xung đột sẽ tăng lên. <br>

__Ứng dụng:__

___- Mạng Ethernet:___ CSMA/CD là phương thức truy cập chính được sử dụng trong các mạng Ethernet. <br>
___- Mạng không dây:___ Một số tiêu chuẩn mạng không dây cũng sử dụng CSMA/CD, như 802.11. <br>

![](/docs/CCNA/img/l2-csma-cd.png)

__Tóm lại:__

CSMA/CD là một phương thức truy cập đa truy nhập được sử dụng trong các mạng Ethernet để kiểm soát việc truy cập vào môi trường truyền dẫn. Nó giúp tránh xung đột và đảm bảo hiệu suất mạng. Tuy nhiên, CSMA/CD có thể không phù hợp cho các mạng lớn với nhiều thiết bị.
