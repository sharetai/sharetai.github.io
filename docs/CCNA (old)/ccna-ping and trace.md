---
layout: default
title: Ping và Trace
nav_order: 10.5
parent: CCNA (old)
---

# Ping and Trace
{: .no_toc }

Ping và Trace
{: .fs-6 .fw-300 }

---

## TABLE OF CONTENTS
{: .no_toc .text-delta }

1. TOC
{:toc}

---

__Ping và Trace__ là hai công cụ không thể thiếu trong việc kiểm tra và chẩn đoán các vấn đề về kết nối mạng. Giúp xác định xem có sự cố gì xảy ra trong quá trình truyền dữ liệu giữa các thiết bị trên mạng hay không.


## Ping (Packet Internet Grouper)
<br>
__Chức năng:__ <br>
\- Kiểm tra kết nối đến một máy chủ hoặc thiết bị cụ thể. <br>
\- Đo độ trễ (latency) của gói tin đi và về. <br>
\- Kiểm tra tỷ lệ mất gói tin. <br>

__Cách hoạt động:__ <br>
Ping gửi các gói tin ICMP (Internet Control Message Protocol) đến một địa chỉ IP cụ thể và đo thời gian phản hồi. <br>

__Cú pháp:__ <br>

```
ping <địa chỉ IP hoặc tên miền>
```

__Kết quả:__ <br>
Thời gian phản hồi (time)	Thời gian để gói tin đi và về. <br>
TTL (Time to Live)	Số lần gói tin có thể nhảy qua các router. <br>
Mất gói tin (packet loss)	Tỷ lệ gói tin không nhận được phản hồi. <br>

<br>

![Alt text](/docs/CCNA (old)/img/ping.png)

![Alt text](/docs/CCNA (old)/img/ping-ttl-1.png)

![Alt text](/docs/CCNA (old)/img/ping-ttl-2.png)

## Trace (Traceroute)
<br>
__Chức năng:__ <br>
\- Xác định đường đi của một gói tin từ máy tính của bạn đến một máy chủ đích. <br>
\- Hiển thị danh sách các router mà gói tin đi qua. <br>
\- Đo độ trễ tại mỗi hop (router). <br>

__Cách hoạt động:__ <br>
Trace gửi các gói tin ICMP với TTL tăng dần để xác định đường đi của gói tin. <br>

__Cú pháp:__ <br>

```
tracert <địa chỉ IP hoặc tên miền>
```

__Kết quả:__ <br>
Danh sách các hop (router) trên đường đi. <br>
Thời gian phản hồi tại mỗi hop. <br>

<br>

![Alt text](/docs/CCNA (old)/img/trace-1.png)

![Alt text](/docs/CCNA (old)/img/trace-2.png)

![Alt text](/docs/CCNA (old)/img/trace-3.png)