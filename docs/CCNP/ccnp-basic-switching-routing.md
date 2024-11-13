---
layout: default
title: Basic Switching and Routing
nav_order: 5
parent: CCNP
---

# Basic Switching and Routing
{: .no_toc }

Chuyển mạch và Định tuyến căn bản
{: .fs-6 .fw-300 }

---

## Table of contents
{: .no_toc .text-delta }

1. TOC
{:toc}

---

## Configure Static MAC Address
<br>
Thiết bị Switch của Cisco tự động xây dựng bảng địa chỉ MAC bằng cách sử dụng địa chỉ MAC nguồn của các _frame_ nhận, nhưng cũng có thể thêm được thủ công địa chỉ MAC vào bảng địa chỉ MAC của thiết bị Switch. Các mục ___Static MAC Entries___ sẽ được giữ lại ngay cả sau khi khởi động lại Switch.

Lệnh cấu hình địa chỉ MAC tĩnh:

```
SW1(config)#mac-address-table static 1111.1111.1111 vlan 1 interface fa0/2
```

Lệnh kiểm tra:

```
SW1(config)#do show mac-address-table
```

<br>

## Configure Static Null Route
<br>
___Null interface___, hay ___Null0___, là giao diện ___black hole interface___ thường được sử dụng để ngăn chặn các vòng lặp định tuyến. Là giao diện ảo nên sẽ luôn up. Giao diện Null0 không chuyển tiếp hoặc nhận lưu lượng truy cập mạng. Mọi lưu lượng truy cập được gửi đến giao diện này đều bị loại bỏ. _Access list (ACL)_ có thể được sử dụng để lọc lưu lượng không mong muốn, nhưng việc sử dụng _null route_ không yêu cầu thêm chi phí CPU. Đây là một phương pháp hiệu quả khi cần yêu cầu lọc lưu lượng truy cập đơn giản.

<h3> Xem xét ngữ cảnh </h3>
<br>
![alt text](/docs/CCNP/img/Null-Route-Example-Scenario.png)

ISP có định tuyến tĩnh cho mạng 192.168.0.0/20 trỏ về phía MainRouter tại 172.16.1.2

```
ISP(config)#ip route 192.168.0.0 255.255.240.0 172.16.1.2
```

MainRouter có định tuyến tĩnh _default static route_ hướng tới ISP tại 172.16.1.1. Nó cũng có các định tuyến tĩnh đến Sales 192.168.1.0/24 đi qua SalesRouter (192.168.0.250) và đến Management 192.168.2.0/24 đi qua MgmtRouter (192.168.0.250).

```
MainRouter(config)#ip route 0.0.0.0 0.0.0.0 172.16.1.1
MainRouter(config)#ip route 192.168.1.0 255.255.255.0 192.168.0.250
MainRouter(config)#ip route 192.168.2.0 255.255.255.0 192.168.0.254
```

Nếu cố gắng gửi lưu lượng truy cập đến các địa chỉ IP chưa sử dụng, nó sẽ tạo ra một vòng lặp. Ví dụ: gửi truy cập đến IP không được sử dụng 192.168.10.1 từ ISP, gói tin bị kẹt trong một vòng lặp và nó sẽ tiêu thụ băng thông cho đến khi TTL hết hạn.

Vòng lặp được tạo vì từ ISP gửi đến MainRouter thông qua cấu hình route tĩnh của ISP đến MainRouter (`ip route 192.168.0.0 255.255.240.0 172.16.1.2`), sau đó trên MainRouter, 0.0.0.0 là prefix khớp dài nhất cho 192.158.10.1 (`ip route 0.0.0.0 0.0.0.0 172.16.1.1`). Sau đó, gói sẽ được gửi trở lại ISP và gửi lại cho MainRouter, v.v. Vì vậy, gây _routing loop_.

```
ISP#trace 192.168.10.1
Type escape sequence to abort.
Tracing the route to 192.168.10.1

1 172.16.1.2 0 msec 0 msec 0 msec
2 172.16.1.1 0 msec 0 msec 0 msec
3 172.16.1.2 0 msec 0 msec 0 msec
4 172.16.1.1 0 msec 0 msec 0 msec
...etc.
```

<br>

<h3> Cấu hình </h3>
<br>
Để ngăn _routing loop_, cấu hình cho thiết bị _null route_. Tương tự như _static route_, nhưng thay vào đó là trỏ đến giao diện _Null0_.

```
MainRouter(config)#ip route 192.168.0.0 255.255.240.0 Null0
```

Bây giờ, ngoại trừ các mạng 192.168.1.0/24 và 192.168.2.0/24, tất cả lưu lượng truy cập khác đến phạm vi 192.168.0.0/20 đều bị loại bỏ.

Nếu cố gắng truy cấp từ ISP một lần nữa, sẽ thấy lưu lượng bị drop bởi _null route_.

```
ISP#trace 192.168.10.1
Type escape sequence to abort.
Tracing the route to 192.168.10.1

1 172.16.1.2 * * *
2 172.16.1.2 * * *
```

<br>

## RIP loop prevention
<br>
Các giao thức định tuyến distance vector (như RIP và EIGRP) sử dụng một số cơ chế khác nhau để ngăn chặn các vòng lặp định tuyến.

<h3> Split Horizon </h3>
<br>
Router không gửi quảng bá tuyến đường trở lại giao diện mà nó học.

![alt text](/docs/CCNP/img/RIP-loop-prevention-Split-Horizon.jpg)

<h3> Route poisoning </h3>
<br>
Khi router phát hiện rằng một tuyến đường kết nối trực tiếp của nó bị lỗi, nó sẽ gửi quảng bá cho tuyến đường đó với _metric_ là vô hạn (_metric_ sẽ là 16 do _max hop count_ của RIP là 15), gọi là _poisoning the route_. Router nhận được cập nhật tuyến đường bị lỗi và không sử dụng nó nữa.

![alt text](/docs/CCNP/img/RIP-loop-prevention-Route-poisoning.jpg)

<!-- <h3> Holddown timer </h3>
<br>
Holddown là một cơ chế ngăn chặn vòng lặp khác được sử dụng bởi giao thức định tuyến vectơ khoảng cách. Tính năng này ngăn bộ định tuyến tìm hiểu thông tin mới về tuyến đường bị lỗi. Khi bộ định tuyến nhận được thông tin về tuyến đường không thể truy cập, bộ đếm thời gian giữ lại sẽ bắt đầu. Bộ định tuyến bỏ qua tất cả các cập nhật định tuyến cho tuyến đó cho đến khi hết giờ (theo mặc định là 180 giây trong RIP). Chỉ các bản cập nhật được phép trong khoảng thời gian đó là các bản cập nhật được gửi từ bộ định tuyến đã quảng cáo tuyến đường ban đầu. Nếu bộ định tuyến đó quảng cáo bản cập nhật, bộ đếm thời gian chờ sẽ dừng và thông tin định tuyến được xử lý.

<br> -->


