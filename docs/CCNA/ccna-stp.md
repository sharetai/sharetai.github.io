---
layout: default
title: STP
nav_order: 21
parent: CCNA
---

# Spanning Tree Protocol
{: .no_toc }

Giao thức chống loop lớp 2
{: .fs-6 .fw-300 }

---

## Table of contents
{: .no_toc .text-delta }

1. TOC
{:toc}

---

## Tại sao có STP? (why?)
<br>
___Ngăn chặn loop:___ STP giúp tránh tình trạng lặp vòng dữ liệu, gây ra hiện tượng broadcast storm và làm giảm hiệu suất mạng.

___Nguyên nhân loop:___ Có nhiều nguyên nhân gây ra các vòng lặp không cần thiết trong mạng, điển hình do việc thiết kế thiết bị và kết nối mang tính dự phòng. Khi vòng lặp xảy ra sẽ xuất hiện các hiện tượng sau: <br>

\- Broadcast storm: việc này diễn ra khi một host trong mạng gửi một frame dưới dạng Broadcast (Destination MAC: FFFF.FFFF.FFFF) ví dụ như gói ARP. <br>
\- Thay đổi thông tin bảng MAC Address liên tục trên thiết bị chuyển mạch. <br>
\- Tạo ra nhiều bản sao của gói frame. <br>

![alt text](/docs/CCNA/img/stp-broadcast-storm.png)

## STP là gì? (what?)
<br>
Spanning Tree Protocol (STP) là một giao thức chống loop khi xây dựng các đường dự phòng cho Switch, STP cho phép các Switch/Bridge truyền thông với nhau để phát hiện vòng lặp vật lý trong mạng, sau đó chuyển đổi mô hình sang cấu trúc cây (Tree)

![alt text](/docs/CCNA/img/stp-loop-free.png)

## BPDU: Bridge Protocol Data Unit (who?)
<br>
BPDU là một loại gói tin được sử dụng trong giao thức STP (Spanning Tree Protocol) để truyền thông tin giữa các thiết bị mạng chuyển mạch (switch). Nó đóng vai trò quan trọng trong việc xây dựng và duy trì cây cấu trúc mạng, ngăn chặn vòng lặp và đảm bảo tính ổn định của mạng Ethernet.

__Cấu trúc BPDU__ <br>

![alt text](/docs/CCNA/img/stp-bpdu-frame.png)

Một BPDU thường bao gồm các trường thông tin sau: <br>

___- Root Bridge ID:___ BID (Root Priority + Root MAC) của switch được chọn làm root bridge. <br>
___- Root Path Cost:___ Chi phí đường dẫn từ root bridge đến switch hiện tại. <br>
___- Bridge ID:___ BID (Bridge Priority + Bridge MAC) của switch gửi : trường này gồm 8 byte, 2 byte cho Priority (0 - 65.535 mặc định là 32.768 _[Trong TH sử dụng thiết bị của Cisco thì Priority phải là bộ số của 4096 do mặc định Switch Cisco chạy cơ chế Per Vlan Spanning Tree]_) và 6 byte cho MAC <br>
___- Message Age:___ Thời gian sống của BPDU. <br>
___- Max Age:___ Thời gian tối đa mà một BPDU có thể tồn tại trên mạng. <br>
___- Forward Delay:___ Thời gian chờ trước khi một cổng chuyển sang chế độ forwarding. <br>
___- Hello Time:___ Khoảng thời gian giữa hai BPDU được gửi. <br>

IEEE 802.1D and IEEE 802.1aq BPDUs have the following format:

```
1. Protocol ID:    2 bytes (0x0000 IEEE 802.1D)
 2. Version ID:     1 byte (0x00 Config & TCN / 0x02 RST / 0x03 MST / 0x04 SPT  BPDU) 
 3. BPDU Type:      1 byte (0x00 STP Config BPDU, 0x80 TCN BPDU, 0x02 RST/MST Config BPDU)
 4. Flags:          1 byte
   bits  : usage
       1 : 0 or 1 for Topology Change
       2 : 0 (unused) or 1 for Proposal in RST/MST/SPT BPDU
     3–4 : 00 (unused) or
           01 for Port Role Alternate/Backup in RST/MST/SPT BPDU
           10 for Port Role Root in RST/MST/SPT BPDU
           11 for Port Role Designated in RST/MST/SPT BPDU
       5 : 0 (unused) or 1 for Learning in RST/MST/SPT BPDU
       6 : 0 (unused) or 1 for Forwarding in RST/MST/SPT BPDU
       7 : 0 (unused) or 1 for Agreement in RST/MST/SPT BPDU
       8 : 0 or 1 for Topology Change Acknowledgement
 5. Root ID:        8 bytes (CIST Root ID in MST/SPT BPDU)
   bits  : usage
     1–4 : Root Bridge Priority
    5–16 : Root Bridge System ID Extension
   17–64 : Root Bridge MAC Address
 6. Root Path Cost: 4 bytes (CIST External Path Cost in MST/SPT BPDU)
 7. Bridge ID:      8 bytes (CIST Regional Root ID in MST/SPT BPDU)
   bits  : usage
     1–4 : Bridge Priority
    5–16 : Bridge System ID Extension
   17–64 : Bridge MAC Address
  8. Port ID:       2 bytes
  9. Message Age:   2 bytes in 1/256 secs
 10. Max Age:       2 bytes in 1/256 secs
 11. Hello Time:    2 bytes in 1/256 secs
 12. Forward Delay: 2 bytes in 1/256 secs
 13. Version 1 Length: 1 byte (0x00 no ver 1 protocol info present. RST, MST, SPT BPDU only)
 14. Version 3 Length: 2 bytes (MST, SPT BPDU only)
 
 The TCN BPDU includes fields 1–3 only.
```

## STP hoạt động như thế nào? (how?)
<br>

___4 bước hoạt động:___

Bước 1: Chọn Root Bridge <br>
\- Bridge ID (min) = Priority (default: 32768) + MAC

Bước 2: Chọn Root Port cho mỗi Non-Root Bridge <br>
\- Pathcost (min) (1gb/s=4,100mb/s=19,..)

Bước 3: Chọn Designed Port cho mỗi Segment <br>
\- Pathcost

Bước 4: Các port còn lại sẽ là Block Port

___3 nguyên tắc so sánh:___

- Pathcost
- Sender Bridge ID
- SenderPort ID

<image src="/docs/CCNA/img/stp-select-root-bridge.png" width="50%"/>
<image src="/docs/CCNA/img/stp-select-root-port.png" width="100%"/>
<image src="/docs/CCNA/img/stp-select-designed-port.png" width="100%"/>

<table class="wikitable floatright" style="text-align: right">
<caption>Path cost for different port speed and STP variation
</caption>
<tbody><tr>
<th>Data rate<br>(link bandwidth)
</th>
<th>Original STP cost<br>(802.1D-1998)
</th>
<th>RSTP/MSTP cost<br>(recommended value)<sup id="cite_ref-802.1Q_3-1" class="reference"><a href="#cite_note-802.1Q-3"><span class="cite-bracket">[</span>3<span class="cite-bracket">]</span></a></sup><sup class="reference nowrap"><span title="Page / location: 503">:&hairsp;503&hairsp;</span></sup>
</th></tr>
<tr>
<td>4&nbsp;Mbit/s
</td>
<td>250
</td>
<td>5,000,000
</td></tr>
<tr>
<td>10&nbsp;Mbit/s
</td>
<td>100
</td>
<td>2,000,000
</td></tr>
<tr>
<td>16&nbsp;Mbit/s
</td>
<td>62
</td>
<td>1,250,000
</td></tr>
<tr>
<td>100&nbsp;Mbit/s
</td>
<td>19
</td>
<td>200,000
</td></tr>
<tr>
<td>1&nbsp;Gbit/s
</td>
<td>4
</td>
<td>20,000
</td></tr>
<tr>
<td>2&nbsp;Gbit/s
</td>
<td>3
</td>
<td>10,000
</td></tr>
<tr>
<td>10&nbsp;Gbit/s
</td>
<td>2
</td>
<td>2,000
</td></tr>
<tr>
<td>100&nbsp;Gbit/s
</td>
<td>N/A
</td>
<td>200
</td></tr>
<tr>
<td>1&nbsp;Tbit/s
</td>
<td>N/A
</td>
<td>20
</td></tr></tbody></table>

## Cấu hình thay đổi root bridge
<br>

```
// Lệnh hiển thị STP
SW#show spanning-tree

// Lệnh chuyển Root Bridge
SW(config)#spanning-tree vlan 1 root primary
// hoặc 
SW(config)#spanning-tree vlan 1 priority <number>
```

