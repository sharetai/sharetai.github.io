---
layout: default
title: QoS
nav_order: 96
parent: CCNA (old)
---

# Quality of Service
{: .no_toc }

Chất lượng của dịch vụ
{: .fs-6 .fw-300 }

---

## TABLE OF CONTENTS
{: .no_toc .text-delta }

1. TOC
{:toc}

---

Khi số lượng lớn người dùng, máy chủ, thiết bị mạng, dịch vụ mạng tăng sẽ ảnh hưởng đến trải nghiệm người dùng. Thoả thuận dịch vụ (**Service Level Agreement - SLA**) có thể không đạt được như kỳ vọng của khách hàng, vì tất cả các loại lưu lượng mạng đều được xử lý là ngang hàng.

Nếu tất cả người dùng truy cập cùng một lúc. Sẽ tiêu tốn rất nhiều tài nguyên của router, router sẽ phải sắp hàng đợi và buộc phải loại bỏ phần lưu lượng hay gói tin gây ra tắc nghẽn.

## QoS là gì?
<br>
Để giải quyết vấn đề tắc nghẽn do nhiều người dùng sử dụng chung tài nguyên mạng. QoS cần được triển khai. QoS là kỹ thuật phân loại (**classify**) và ưu tiên (**priority**) loại lưu lượng, như dữ liệu nhạy cảm hay không nhảy cảm.

Dữ liệu nhạy cảm, voice hay video, thường dùng UDP, cần đảm bảo băng thông trên thời gian thực. Không như TCP, dữ liệu ít nhạy cảm hơn, web hay mail, có thể không yêu cầu đảm bảo băng thông do có thể xử lý gửi lại cái gói tin lỗi bị loại bỏ khi tắt nghẽn. Với QoS, hiệu suất mạng và trải nghiệm người dùng có thể được tối ưu tốt hơn.

<br>

## 4 đặc điểm của lưu lượng mạng
<br>
1\. **Bandwidth** - Băng thông là khả năng truyền dữ liệu trên link. Có thể hiểu càng rộng càng tốt.

2\. **Delay** - Độ trễ thời gian cần thiết để gói tin đi từ nguồn đến đích.

3\. **Jitter** - Độ biến động thời gian truyền. Có thể hiểu mong muốn gửi đi 10ms nhưng lại đến sớm 9ms (jitter là -1ms) hay trễ 11ms (jitter là +1ms).

4\. **Loss** - Độ rớt gói.

{: .highlight-title }
> Note
>
> __QoS needs of video__ conferencing traffic are __similar to those for voice__: <br>
> \- __Loss__ should be no more than 1% <br>
> \- __One-way latency__ should be no more than 150-200ms <br>
> \- __Average Jitter__ should be no more than 30ms <br>

<br>

## QoS tools
<br>
![Alt text](/docs/CCNA (old)/img/QoS-tools.png)

1\. **Classification** - Áp vào chân router để phân loại gói.

2\. **Policing** - Thực hiện loại bỏ hay đánh dấu gói.

3\. **Marking** - Đánh dấu vào header gói dựa trên phân loại.

4\. **Congestion Management** - Sắp ưu tiên truyền theo hàng đợi.

5\. **Congestion Avoidance** - Drop gói trước khi tắc nghẽn.

6\. **Queuing** - Sắp gói tin vào bộ đệm và chờ đến lượt truyền.

7\. **Shaping** - Giới hạn băng thông. Đưa các gói vào bộ đệm chờ 1 lúc.

<br>

## QoS models
<br>
Có ba mô hình triển khai khác nhau:

__Best Effort__

Nỗ lực chuyển tiếp khi có thể. Xem các dự liệu là ngang hàng. Không cần cấu hình.

__Integrated Services (IntServ)__

IntServ sử dụng giao thức đặt trước tài nguyên __Resource Reservation Protocol (RSVP)__ để báo hiệu và dành riêng các tài nguyên mạng cần thiết cho một ứng dụng cụ thể.

__Differentiated Services (DiffServ)__

DiffServ phân loại lưu lượng IP và đánh dấu chúng bằng cách sử dụng các byte __Type-of-Service (ToS)__ của _IP header_. Theo cách này, mỗi lớp lưu lượng có thể được chỉ định một mức dịch vụ khác nhau. Các thiết bị mạng nhận dạng 1 _IP packet class_ thông qua việc đánh dấu của nó, triển khai hàng đợi thông minh, điều hòa lưu lượng, định hình và kiểm soát lưu lượng.

<br>

## Classification and Marking
<br>
Phân loại dựa trên mô tả chuẩn.

Layer 1 – Physical interface <br>
Layer 2 – 802.1Q/p Class of Service (**CoS**) bits and MAC addresses <br>
Layer 2.5 – MPLS Experimental (**EXP**) bits <br>
Layer 3 – Differentiated Services Code Point (**DSCP**) value, IP Precedence value (IPP), and source and destination IP addresses <br>
Layer 4 – TCP and UDP ports <br>
Layer 7 – Next Generation Network-Based Application Recognition (NBAR2) <br>

<br>

__Layer 2 QoS Marking__
<br>
Tiêu chuẩn IEEE 802.1Q định nghĩa 2 trường được đưa vào khung Ethernet:

1. Tag Protocol Identifier (TPID)
2. Tag Control Information (TCI)

![alt text](/docs/CCNA (old)/img/qos-cos.png)

TPID là trường 2-byte hoặc 16-bit có giá trị 0x8100, biểu thị đây là khung được gắn thẻ 802.1Q. TCI cũng là trường 2-byte hoặc 16-bit và bao gồm ba trường:

- Priority Code Point (PCP)
- Drop Eligible Indicator (DEI)
- VLAN Identifier (VLAN ID)

<u>Priority Code Point (PCP)</u>

0 (lowest) | Background (BK) <br>
1 (default) | Best effort (BE) <br>
2 | Excellent effort (EE) <br>
3 | Critical applications (CA) <br>
4 | Video with < 100 ms latency and jitter (VI) <br>
5 | Voice with < 10 ms latency and jitter (VO) <br>
6 | Internetwork control (IC) <br>
7 (highest) | Network control (NC) <br>

<br>

__Layer 3 QoS Marking__
<br>
![alt text](/docs/CCNA (old)/img/qos-tos.png)

<table>
  <thead>
    <tr>
      <th style="text-align: left">Binary</th>
      <th style="text-align: left">DSCP Name</th>
      <th style="text-align: left">DS Field Value (Dec)</th>
      <th style="text-align: left">IP Precedence (Description)</th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <td style="text-align: left"><span style="color:red;">111</span>000</td>
      <td style="text-align: left">CS<span style="color:red;">7</span></td>
      <td style="text-align: left">56</td>
      <td style="text-align: left"><span style="color:red;">7</span>: Network Control</td>
    </tr>
    <tr>
      <td style="text-align: left"><span style="color:red;">110</span>000</td>
      <td style="text-align: left">CS<span style="color:red;">6</span></td>
      <td style="text-align: left">48</td>
      <td style="text-align: left"><span style="color:red;">6</span>: Internetwork Control</td>
    </tr>
    <tr>
      <td style="text-align: left"><span style="color:red;">101</span>110</td>
      <td style="text-align: left">CS<span style="color:red;">5</span>, EF</td>
      <td style="text-align: left">40,46</td>
      <td style="text-align: left"><span style="color:red;">5</span>: Critical - mainly used for voice RTP, Expedited Forwarding</td>
    </tr>
    <tr>
      <td style="text-align: left"><span style="color:red;">100</span><span style="color:blue;">xx</span>0</td>
      <td style="text-align: left">CS<span style="color:red;">4</span>, AF<span style="color:red;">4</span><span style="color:blue;">1</span>-<span style="color:red;">4</span><span style="color:blue;">3</span></td>
      <td style="text-align: left">32,34,36,38</td>
      <td style="text-align: left"><span style="color:red;">4</span>: Flash Override, Class-Selector, Assured Forwarding</td>
    </tr>
    <tr>
      <td style="text-align: left"><span style="color:red;">011</span><span style="color:blue;">xx</span>0</td>
      <td style="text-align: left">CS<span style="color:red;">3</span>, AF<span style="color:red;">3</span><span style="color:blue;">1</span>-<span style="color:red;">3</span><span style="color:blue;">3</span></td>
      <td style="text-align: left">24,26,28,30</td>
      <td style="text-align: left"><span style="color:red;">3</span>: Flash - mainly used for voice signaling, Class-Selector, Assured Forwarding</td>
    </tr>
    <tr>
      <td style="text-align: left"><span style="color:red;">010</span><span style="color:blue;">xx</span>0</td>
      <td style="text-align: left">CS<span style="color:red;">2</span>, AF<span style="color:red;">2</span><span style="color:blue;">1</span>-<span style="color:red;">2</span><span style="color:blue;">3</span></td>
      <td style="text-align: left">16,18,20,22</td>
      <td style="text-align: left"><span style="color:red;">2</span>: Immediate, Class-Selector, Assured Forwarding</td>
    </tr>
    <tr>
      <td style="text-align: left"><span style="color:red;">001</span><span style="color:blue;">xx</span>0</td>
      <td style="text-align: left">CS<span style="color:red;">1</span>, AF<span style="color:red;">1</span><span style="color:blue;">1</span>-<span style="color:red;">1</span><span style="color:blue;">3</span></td>
      <td style="text-align: left">8,10,12,14</td>
      <td style="text-align: left"><span style="color:red;">1</span>: Priority, Class-Selector, Assured Forwarding</td>
    </tr>
    <tr>
      <td style="text-align: left">000001</td>
      <td style="text-align: left">LE</td>
      <td style="text-align: left">1</td>
      <td style="text-align: left">n/a: Low Effort</td>
    </tr>
    <tr>
      <td style="text-align: left">000000</td>
      <td style="text-align: left">CS0, BE</td>
      <td style="text-align: left">0</td>
      <td style="text-align: left">0: Best Effort</td>
    </tr>
  </tbody>
</table>

![alt text](/docs/CCNA (old)/img/qos-dscp.png)

<br>

## Queues and Queuing
<br>
Hàng đợi là bộ đệm trên thiết bị mạng được sử dụng để lưu trữ các gói dựa trên lớp khi cổng bận hoặc hết băng thông. Lưu lượng ở hàng đợi có thể được xử lý sau khi cổng hoặc băng thông khả dụng trở lại.

<u>Cisco QoS Queues</u>

**Priority Queues (PQs)** <br>
**Class-Based Weighted Fair Queuing (CBWFQ)** <br>

<u>Other Queuing Methods</u>

First In – First Out (FIFO) <br>
Weighted Fair Queueing (WFQ) <br>
Custom Queuing (CQ) <br>
Weighted Round Robin (WRR) <br>
Priority Queueing (PQ) <br>
Low Latency Queuing (LLQ) <br>
IP RTP Priority <br>
Class-Based WFQ (CBWFQ) <br>

<br>

## Network Congestion Management
<br>
Có 2 kiểu drop gói khi tắt nghẽn: <br>
\- Tail Drop. Drop gói đến sau. <br>
\- Random Early Detection (RED) and Weighted Random Early Detection (WRED). Drop gói ngẫu nhiên trong hàng đợi. <br>

<br>

