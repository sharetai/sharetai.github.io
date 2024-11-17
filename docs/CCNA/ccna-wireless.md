---
layout: default
title: Wireless
nav_order: 97
parent: CCNA
---

# Wireless Network
{: .no_toc }

Mạng không dây
{: .fs-6 .fw-300 }

---

## Table of contents
{: .no_toc .text-delta }

1. TOC
{:toc}

---

{: .highlight-title }
> Note
>
> Bản chất điểm truy cập không dây (access points) là kết nối các thiết bị không dây (wireless devices) vào mạng có dây (wired network)

## 802.11

{: .highlight-title }
> Note
>
> __- 802.11r__ hay __fast BSS transition (FT)__ - hỗ trợ chuyển vùng nhanh <br>
> __- 802.11w__ - tăng cường bảo mật cho các frame quản lý được bảo vệ <br>

<h3> Một vài điểm khác biệt giữa mạng WLAN và mạng LAN: </h3>
\- Mạng LAN không dây (WLAN) sử dụng ___sóng vô tuyến (radio wave)___ ở tầng vật lý: <br>
\- WLAN sử dụng cơ chế ___CSMA/CA (Carrier Sense Multiple Access/Collision Avoidance)___ thay vì _CSMA/CD (Carrier Sense Multiple Access/Collision Detect)_ cho môi trường truy nhập (_media access_). CSMA/CD sử dụng trong môi trường hub để phát hiện và giảm thiểu xung đột, nhưng ở môi trường access point không thể dò được xung đột nên chỉ có thể sử dụng CSMA/CA để tránh xung đột.<br>
\- Là kiểu truyền ___half-duplex___. <br>
\- Một số vấn đề khi truyền dẫn bằng sóng vô tuyến: vùng phủ (_coverage_), nhiễu (_interference, noise_) và bảo mật (_privacy_) cho môi trường khó khăn hơn rất nhiều. <br>
\- Access points là các thiết bị chia sẻ tương tự Ethernet hub trong việc chia sẻ băng thông. Càng nhiều thiết bị truy nhập thì tốc độ dành riêng cho mỗi thiết bị càng giảm. <br>

<h3> Truyền dẫn bằng sóng vô tuyến: </h3>
\- Sóng radio sẽ được bức xạ ra ngoài môi trường thông qua anten để tạo ra sóng lan truyền. <br>
\- Các vấn đề ảnh hưởng đến sóng: Phản xạ (_Reflection_) khi sóng đập vào bề mặt vật thể. Tán xạ (_Scattering_) khi gặp vật nhọn hay gồ ghề. Hấp thụ (_Absorption_). <br>
\- Tần số càng cao cho phép tốc độ truyền dữ liệu càng cao, tuy nhiên khoảng cách truyền càng ngắn. <br>

<h3> Có 3 mô hình WLAN: </h3>
\- __AD HOC: Independent Basic Service sets (IBSS)__: Không có AP. Máy tính kết nối không dây với máy tính. <br>
\- __Basic service sets (BSS)__: 1 AP. <br>
\- __Extended Service Set (ESS)__: 2 hay nhiều AP. <br>

<img src="/docs/CCNA/img/802.11-BSS.webp" style="max-width: 500px"/>

BSS có thể xem là vùng phủ của 1 AP.

<h3> Có 2 cách cấu hình cho 1 access point: </h3>
\- __Autonomous AP Configuration__: AP tự chủ, hoạt động độc lập, phù hợp với mạng nhỏ. <br>
\- __Lightweight AP Configuration__: Nhiều LAP được quản lý bởi __Wireless LAN Controller (WLC)__, sử dụng cho mạng lớn. Có 2 mode: local và flexconnect (với flexconnect sẽ chuyển autonomous khi mất kết nối với WLC). <br>

<h3> Có 2 kiến trúc mạng không dây (_Wireless Architecture)_: </h3>
\- Autonomous AP Architecture <br>
\- Split-MAC Architectures <br>

<h4> Autonomous AP Architecture </h4>
1 AP phải làm mọi thứ: Phê duyệt yêu cầu liên kết, Quản lý power, Quản lý tần số vô tuyến, Quản lý BSS. Với thiết lập này, có thể cần phải đăng nhập vào mọi AP để cấu hình khi triển khai mới hay mỗi lần cần cập nhật cấu hình.

<img src="/docs/CCNA/img/802.11-Autonomous-AP-Architecture.webp" style="max-width: 500px"/>

<h4> Cloud-Based AP Architecture </h4>
Đối với kiến ​​trúc Autonomous AP, khả năng mở rộng là có thể, mặc dù phức tạp hơn. Cisco đã giới thiệu một kiến ​​trúc không dây dựa trên đám mây có tên là Cisco Meraki, đặc điểm chính là: <br>
\- Phần mềm không nằm tại cơ sở mà nằm trên máy chủ của nhà cung cấp. <br>
\- Nhiệm vụ quản lý AP được chuyển lên Đám mây. <br>
\- Chỉ có các tác vụ chuyển tiếp dữ liệu thời gian thực được thực hiện bởi AP. <br>

<img src="/docs/CCNA/img/802.11-Cloud-Based-AP-Architecture.webp" style="max-width: 500px"/>

<h4> Split-MAC Architectures </h4>
Kiến trúc mạng không dây dựa trên đám mây chỉ tập trung cải thiện quản lý hệ thống. Tuy nhiên, khả năng di động của máy khách vẫn là không thể. Với kiến ​​trúc Split-MAC, sẽ có 1 __Wireless LAN Controller (WLC)__ quản lý tập trung, cho phép người dùng chuyển vùng tự do từ điểm truy cập này sang điểm truy cập khác mà không cần ngắt kết nối. Kiến trúc này cung cấp Extended Service Set (ESS).

<img src="/docs/CCNA/img/802.11-Unified-WLC.webp" style="max-width: 425px"/>

Đường hầm ___CAPWAP (Control and Provisioning of Wireless Access Points Tunnels)___ sẽ được tạo có số lượng là 2 giữa WLC và LAP: 1 là CAPWAP Control Tunnel và 2 là CAPWAP Data Tunnel.

<img src="/docs/CCNA/img/802.11-WLC-CAPWAP.webp" style="max-width: 800px"/>

<h3> Phổ tần số WiFi 2.4 GHz so với 5 GHz </h3>
2.4 GHz và 5 GHz là các dải tần số thường được sử dụng trong kết nối WiFi. Sự khác biệt chính giữa 2.4 GHz và 5 GHz là tốc độ và phạm vi phủ sóng. Tần số càng cao thì tốc độ càng nhanh nhưng phạm vi phủ sóng càng ngắn.

__2.4 GHz__

\- 2.4 GHz có phạm vi xa hơn nhưng tốc độ chậm hơn. <br>
\- 2.4 GHz có tốc độ tối đa là 150 Mbps. <br>
\- Khả năng nhiễu cao hơn ở tần số 2.4 GHz. <br>
\- Chỉ có 11 kênh khác nhau (trong đó có 3 kênh không chồng chéo là kênh 1, 6, 11) – điều này khiến nó dễ bị hết tài nguyên. <br>
\- Hầu hết các bộ định tuyến và điểm truy cập không dây sử dụng 2.4 GHz, đặc biệt là các bộ định tuyến và điểm truy cập cũ. <br>
\- Tương đối rẻ hơn so với các thiết bị không dây băng tần kép. <br>
\- Hiệu suất cao hơn trong việc xuyên thủng các vật thể rắn. <br>

__5 GHz__

\- 5 GHz có phạm vi ngắn hơn nhưng tốc độ cao hơn. <br>
\- 5 GHz có tốc độ truyền dữ liệu tối đa là 1 Gbps. <br>
\- Hiệu suất kém khi xuyên qua các vật thể rắn. <br>
\- Ít nhiễu hơn vì nó có thể sử dụng 23 kênh. <br>
\- Bộ định tuyến băng tần kép đắt hơn. <br>

<table class="wikitable floatright mw-datatable">
<caption>Wi-Fi generations</caption>
<tbody><tr>
<th>Generation
</th>
<th>IEEE<br>standard
</th>
<th>Adopted
</th>
<th>Maximum<br>link rate<br>(Mbit/s)
</th>
<th>Radio<br>frequency<br>(GHz)
</th></tr>
<tr>
<th><a class="mw-redirect" title="IEEE 802.11bn">Wi-Fi 8</a>
</th>
<td><a class="mw-redirect" title="IEEE 802.11bn">802.11bn</a>
</td>
<td align="center">2028
</td>
<td align="right">100,000
</td>
<td align="right">2.4, 5, 6, 7,<br>42.5, 71
</td></tr>
<tr>
<th><a class="mw-redirect" title="Wi-Fi 7">Wi-Fi 7</a>
</th>
<td><a class="mw-redirect" title="IEEE 802.11be">802.11be</a>
</td>
<td align="center">2024
</td>
<td align="right">1376–46,120
</td>
<td align="right">2.4, 5, 6
</td></tr>
<tr>
<th><a class="mw-redirect" title="Wi-Fi 6E">Wi-Fi 6E</a>
</th>
<td rowspan="2"><a class="mw-redirect" title="IEEE 802.11ax">802.11ax</a>
</td>
<td align="center">2020
</td>
<td rowspan="2" align="right">574–9608
</td>
<td align="right">6
</td></tr>
<tr>
<th><a title="Wi-Fi 6">Wi-Fi 6</a>
</th>
<td align="center">2019
</td>
<td align="right">2.4, 5
</td></tr>
<tr>
<th><a class="mw-redirect" title="Wi-Fi 5">Wi-Fi 5</a>
</th>
<td><a class="mw-redirect" title="IEEE 802.11ac-2013">802.11ac</a>
</td>
<td align="center">2014
</td>
<td align="right">433–6933
</td>
<td align="right">5
</td></tr>
<tr>
<th><a class="mw-redirect" title="Wi-Fi 4">Wi-Fi 4</a>
</th>
<td><a class="mw-redirect" title="IEEE 802.11n-2009">802.11n</a>
</td>
<td align="center">2008
</td>
<td align="right">72–600
</td>
<td align="right">2.4, 5
</td></tr>
<tr>
<th><i>(Wi-Fi&nbsp;3)*</i>
</th>
<td><a class="mw-redirect" title="IEEE 802.11g-2003">802.11g</a>
</td>
<td align="center">2003
</td>
<td rowspan="2" align="right">6–54
</td>
<td align="right">2.4
</td></tr>
<tr>
<th><i>(Wi-Fi&nbsp;2)*</i>
</th>
<td><a class="mw-redirect" title="IEEE 802.11a-1999">802.11a</a>
</td>
<td align="center">1999
</td>
<td align="right">5
</td></tr>
<tr>
<th><i>(Wi-Fi&nbsp;1)*</i>
</th>
<td><a class="mw-redirect" title="IEEE 802.11b-1999">802.11b</a>
</td>
<td align="center">1999
</td>
<td align="right">1–11
</td>
<td align="right">2.4
</td></tr>
<tr>
<th><i>(Wi-Fi&nbsp;0)*</i>
</th>
<td><a class="mw-redirect" title="IEEE 802.11 (legacy mode)">802.11</a>
</td>
<td align="center">1997
</td>
<td align="right">1–2
</td>
<td align="right">2.4
</td></tr>
<tr>
<td colspan="5"><b>*</b><i>Wi‑Fi 0</i>, <i>1</i>, <i>2</i>, and <i>3</i> are named by retroactive inference.<br>They do not exist in the official nomenclature.
</td></tr></tbody></table>

<h3> Frame Types: </h3>
\- Association | Management <br>
\- Authentication | Management <br>
\- Beacon | Management <br>
\- Probe | Management <br>
\- Request to Send (RTS) | Control <br>
\- Clear to Send (CTS) | Control <br>
\- Acknowledgment (ACK) | Control <br>
\- Data | Data <br>

<h3> WiFi security protocols: </h3>
\- __WEP__ - __RC4 40-bit__, __PWE__<br>
\- __WPA__ - __TKIP 128-bit with RC4__, __PSK & 802.1x__<br>
\- __WPA2__ - __AES 128-bit__, CCMP encryption, __PSK & 802.1x__ <br>
\- __WPA3__ - __AES 128-bit (personal) 192-bit (enterprise)__-GCMP encryption, Simultaneous Authentication of Equals (__SAE__) & __802.1x__ <br>

<h3> Wireless LAN Controller Deployment </h3>

__Unified or Centralized WLAN Controller Deployment__ support up to 6000 Wireless Access Points

<img src="/docs/CCNA/img/802.11-Unified-WLC.webp" style="max-width: 400px"/>

__Cloud-Based Wireless LAN Controller Deployment__ support up to 3000 Wireless Access Points

<img src="/docs/CCNA/img/802.11-Cloud-Based-WLC.webp" style="max-width: 400px"/>

__Embedded Wireless LAN Controller Deployment__ support up to 200 Wireless Access Points

<img src="/docs/CCNA/img/802.11-Embedded-WLC.webp" style="max-width: 375px"/>

__Mobility Express Wireless LAN Controller Deployment__ support up to 100 Wireless Access Points

<img src="/docs/CCNA/img/802.11-Mobility-Express-WLC.webp" style="max-width: 425px"/>


## Cisco WLC Interfaces, Ports

__<u>WLC Ports (Physical Interfaces)</u>__

![Alt text](/docs/CCNA/img/wlc-phy-int.png)

__Redundancy Port__ - Cổng sử dụng cho __High-Availability (HA)__ khi có 2 WLC. 2 port redun của 2 WLC sẽ đấu nhau.

__Service Port__ - Cổng sử dụng cho __out-of-band management__ bảo trì khi mạng lỗi. Là __access port__, không hỗ trợ trunk.

__SFP Distribution Port__ - Kết nối với cổng logic bên trong và chứa lưu lượng không dây của máy khách.

__<u>WLC INTERFACES (LOGICAL INTERFACES)</u>__

![Alt text](/docs/CCNA/img/wlc-logic-int.png)

__Service Interface__ - Giao diện quản trị, tách biệt với lưu lượng máy khách.

__Management Interface__ - Giao diện quản trị, chung với lưu lượng máy khách.

__AP-Manager Interface__ - Giao diện giao tiếp giữa controller và lightweight access points. AP-Manager IP address sử dụng như tunnel source cho các gói CAPWAP/LWAPP.

__Virtual Interface__ - Giao diện cung cấp DHCP relay, authentication.

__Dynamic Interface__ - Giao diện máy khách.

## 802.1x

Khi truy cập vào wifi, thường chỉ cần mật khẩu. Người quản trị chỉ xác định được số lượng truy cập, ip hay mac. Thiếu định danh, nhận dạng thiết bị an toàn hay được cho phép.

802.1x cung cấp đăng nhập yêu cầu username và password hay yêu cầu chứng chỉ CA được phép.

![Alt text](/docs/CCNA/img/802.1x_wired_protocols.png)

![Alt text](/docs/CCNA/img/802.1x.png)

## (lab is comming soon)
