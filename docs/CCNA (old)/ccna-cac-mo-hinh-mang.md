---
layout: default
title: Các Mô Hình Mạng
nav_order: 1
parent: CCNA (old)
---

# Open Systems Interconnection Model<br>and<br>Transmission Control Protocol/Internet Protocol Model
{: .no_toc }

Mô hình OSI và mô hình TCP/IP
{: .fs-6 .fw-300 }

---

## TABLE OF CONTENTS
{: .no_toc .text-delta }

1. TOC
{:toc}

---

## Tại sao có các mô hình mạng (why?)
<br>
Cần có một khung tham chiếu chung để các nhà sản xuất thiết bị mạng thiết kế và phát triển các sản phẩm tương thích với nhau.

## MÔ HÌNH OSI (what?)
<br>

<div style="text-align:center">
  <img alt="" alt="" style="max-width: 400px" src="https://upload.wikimedia.org/wikipedia/commons/thumb/8/8d/OSI_Model_v1.svg/800px-OSI_Model_v1.svg.png" />
</div>

**Open Systems Interconnection (OSI)** Model là một sự chuẩn hóa cho những chức năng trong hệ thống mạng. Chức năng của mô hình là giúp cho tính phức tạp của mạng trở nên đơn giản hơn, cho phép các nhà phát triển module hóa việc thiết kế. Phương pháp này cho phép nhiều nhà phát triển làm việc độc lập nhau để tạo ra những chức năng riêng biệt mà vẫn có thể hòa hợp thành một thể thống nhất một cách dễ dàng (plug-and-play). Ngoài ra mô hình còn giúp cho những quản trị viên có thể hình tượng hóa quá trình trao đổi dữ liệu giữa các máy tính để hiểu được hoạt động của hệ thống mạng một cách tường minh hơn.

Mô hình **OSI** bao gồm 7 lớp:

<table>
  <tr>
    <td><b>7.Application</b></td>
    <td>Tầng ứng dụng cấp phương diện cho người dùng truy nhập các thông tin và dữ liệu trên mạng thông qua chương trình ứng dụng. Tầng này là giao diện chính để người dùng tương tác với chương trình ứng dụng, và qua đó với mạng.</td>
    <td>Telnet, HTTP, FTP, SMTP, X.400</td>
  </tr>
  <tr>
    <td><b>6.Presentation</b></td>
    <td>Tầng biên dịch có nhiệm vụ chuẩn hóa dữ liệu. Tầng này dịch dữ liệu được gửi từ tầng Application sang dạng Format chung. Và tại máy tính nhận, lớp này lại chuyển từ Format chung sang định dạng của tầng Application.</td>
    <td>ASCII, JPEG, EBCDIC</td>
  </tr>
  <tr>
    <td><b>5.Session</b></td>
    <td>Tầng phiên kiểm soát các (phiên) hội thoại giữa các máy tính. Mở nhiều ứng dụng đồng thời trên 1 card mạng duy nhất (Chơi game, nghe nhạc, mạng xã hội  )</td>
    <td>OS, Scheduling</td>
  </tr>
  <tr>
    <td><b>4.Transport</b></td>
    <td>Tầng vận chuyển cung cấp dịch vụ chuyển dữ liệu giữa các người dùng tại đầu cuối. Tầng giao vận kiểm soát độ tin cậy của một kết nối được cho trước.</td>
    <td>TCP, UDP, SPX</td>
  </tr>
  <tr>
    <td><b>3.Network</b></td>
    <td>Tầng mạng thực hiện chức năng định tuyến. Tầng này cung cấp việc đánh địa chỉ luận lý (*IP Addressing*) - định tuyến các gói dữ liệu.</td>
    <td>IPv4, IPv6, IPX, AppleTalk, OSPF, RIP, EIGRP</td>
  </tr>
  <tr>
    <td><b>2.Datalink</b></td>
    <td>Tầng liên kết dữ liệu truyền dữ liệu giữa các thực thể mạng, phát hiện và có thể sửa chữa các lỗi trong tầng vật lý nếu có. Đánh địa chỉ vật lý (*MAC Address*) được mã hóa cứng vào trong các card mạng khi chúng được sản xuất.</td>
    <td>ARP, LAN, Ethernet, HDLC, PPP, VLAN, Trunk, STP, 802.2, 802.3</td>
  </tr>
  <tr>
    <td><b>1.Physical</b></td>
    <td>Tầng vật lý định nghĩa các đặc tả về điện và vật lý cho các thiết bị. Bao gồm bố trí các chân cắm (*pin*), hiệu điện thế (*volt*), và các cáp nối (*cable*); hay chuyển đổi giữa các loại tín hiệu điện như xung vuông trong thiết bị, sóng sin trong dây cáp đồng, ánh sáng trong cáp quang, sóng vô tuyến trong thiết bị không dây.</td>
    <td>Cable, EIA/TIA, V.35</td>
  </tr>
</table>

Dữ liệu trên máy tính có nhu cầu truyền sẽ chuyển từ tầng 7 xuống tầng 1. Khi đi qua mỗi tầng, dữ liệu sẽ được gắn thêm định dạng của tầng đó vào. Qua bên máy tính nhận thì dữ liệu sẽ được chuyển từ tầng 1 lên tầng 7. Khi đi qua mỗi tầng, dữ liệu sẽ được gỡ bỏ định dạng mà tầng tương ứng bên kia đã gắn vào.

<div style="text-align:center">
  <img alt="" alt="" src="https://vnpro.vn/upload/user/images/Tin%20T%E1%BB%A9c/1(2).jpg" />
</div>

Đóng gói dữ liệu

![](/docs/CCNA (old)/img/network_encap.png)

Giải đóng gói dữ liệu

![](/docs/CCNA (old)/img/network_decap.png)

## MÔ HÌNH TCP/IP (what?)
<br>

__Mô hình TCP/IP:__ Là một bộ giao thức truyền thông được sử dụng rộng rãi trên Internet. Nó chia quá trình truyền thông thành 4 lớp, đơn giản hơn so với OSI nhưng vẫn đảm bảo chức năng. TCP/IP Được sử dụng rộng rãi trong các mạng máy tính, từ mạng LAN nhỏ đến Internet. Mô hình TCP/IP đơn giản hơn OSI, tập trung vào các giao thức chính như TCP (Transmission Control Protocol) và IP (Internet Protocol). TCP đảm bảo dữ liệu được truyền đi một cách chính xác và đầy đủ, trong khi IP chịu trách nhiệm định tuyến các gói tin.

![image](https://user-images.githubusercontent.com/56266496/165344536-78f1c219-76ea-4ecc-8529-2e24919026f7.png)

Dữ liệu và giao thức qua các tầng:

<div style="text-align:center">
  <img alt="" alt="" style="max-width: 400px" src="https://thietbimangcisco.vn/userfiles/TCP-IP-Model.png" />
</div>
