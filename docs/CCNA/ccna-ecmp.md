---
layout: default
title: ECMP
nav_order: 13.7
parent: CCNA
---

# Equal Cost Multi-Path
{: .no_toc }

Định tuyến đa đường chi phí ngang nhau
{: .fs-6 .fw-300 }

---

## Table of contents
{: .no_toc .text-delta }

1. TOC
{:toc}

---

__Equal Cost Multi-Path__ hay __ECMP__ là chiến lược định tuyến trong đó các gói hướng tới một địa chỉ IP đích duy nhất được cân bằng tải trên nhiều đường đi tốt nhất với metric bằng nhau.

## Khái niệm định tuyến của Cisco

{: .important-title }
> Thiết bị Cisco Lớp 3, ví dụ router, quyết định sử dụng tuyến đường dựa trên:
>
> 1\. __Longest Prefix length__ <br>
> 2\. __Lowest Administrative Distance (AD)__ <br>
> 3\. __Lowest Metric__ <br>

Ví dụ lấy từ câu 2 trong bộ đề CCNA 200-301:

![alt text](/docs/CCNA/img/ecmp.png)

<u>Bảng giá trị AD mặc định của Cisco</u>

<table class="wikitable" style="text-align:center">
<tbody><tr>
<th>Routing protocol</th>
<th>Administrative distance
</th></tr>
<tr>
<td>Directly connected interface</td>
<td>0
</td></tr>
<tr>
<td>Static route</td>
<td>1
</td></tr>
<tr>
<td>Dynamic Mobile Network Routing (DMNR)</td>
<td>3
</td></tr>
<tr>
<td><a href="/wiki/EIGRP" class="mw-redirect" title="EIGRP">EIGRP</a> summary route</td>
<td>5
</td></tr>
<tr>
<td>External <a href="/wiki/BGP" class="mw-redirect" title="BGP">BGP</a></td>
<td>20
</td></tr>
<tr>
<td><a href="/wiki/EIGRP" class="mw-redirect" title="EIGRP">EIGRP</a> internal route</td>
<td>90
</td></tr>
<tr>
<td><a href="/wiki/IGRP" class="mw-redirect" title="IGRP">IGRP</a></td>
<td>100
</td></tr>
<tr>
<td><a href="/wiki/OSPF" class="mw-redirect" title="OSPF">Open Shortest Path First</a> (OSPF)</td>
<td>110
</td></tr>
<tr>
<td><a href="/wiki/IS-IS" title="IS-IS">Intermediate System to Intermediate System</a> (IS-IS)</td>
<td>115
</td></tr>
<tr>
<td><a href="/wiki/Routing_Information_Protocol" title="Routing Information Protocol">Routing Information Protocol</a> (RIP)</td>
<td>120
</td></tr>
<tr>
<td><a href="/wiki/Exterior_Gateway_Protocol" title="Exterior Gateway Protocol">Exterior Gateway Protocol</a> (EGP)</td>
<td>140
</td></tr>
<tr>
<td><a href="/wiki/On_Demand_Routing" title="On Demand Routing">ODR</a></td>
<td>160
</td></tr>
<tr>
<td><a href="/wiki/EIGRP" class="mw-redirect" title="EIGRP">EIGRP</a> external route</td>
<td>170
</td></tr>
<tr>
<td>Internal <a href="/wiki/BGP" class="mw-redirect" title="BGP">BGP</a></td>
<td>200
</td></tr>
<tr>
<td><a href="/wiki/Next_Hop_Resolution_Protocol" title="Next Hop Resolution Protocol">Next Hop Resolution Protocol</a> (NHRP)</td>
<td>250
</td></tr>
<tr>
<td>Default static route learned via DHCP</td>
<td>254
</td></tr>
<tr>
<td>Unknown and unused</td>
<td>255
</td></tr></tbody></table>

## Load Balancing Methods

__Per-Destination Load Balancing –__ _(default)_ Các gói tin cho một cặp máy chủ nguồn và đích nhất định được đảm bảo đi theo cùng một đường dẫn, ngay cả khi có nhiều đường dẫn ECMP khả dụng. (Per-flow load balancing)

__Per-Packet Load Balancing –__ Sử dụng phương pháp round-robin để xác định đường dẫn mà mỗi gói tin sẽ đi đến IP đích. Điều này không phù hợp với một số loại lưu lượng truy cập nhất định, chẳng hạn như Voice over IP (VoIP), vốn phụ thuộc vào việc các gói tin đến đích theo trình tự.

