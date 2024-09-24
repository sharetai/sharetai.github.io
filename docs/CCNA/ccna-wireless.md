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

\! Chuẩn **IEEE 802.11** mô tả một giao tiếp "truyền qua không khí" _(over-the-air)_ sử dụng sóng vô tuyến để truyền nhận tín hiệu <br>

\! Là **half-duplex** <br>

\! Vùng tập trung các pc truy cập không dây gọi là **Basic Service Set (BSS)** và trung tâm là **Wireless Access Point (WAP)** <br>

\! **2.4GHz vs 2.5GHz**:  <br>
\-- 2.4GHz có 3 kênh không chồng chéo là kênh 1, 6, 11<br>
\-- 2.5GHz có 23 kênh không chồng chéo <br>

\! **Frame Types**:  <br>
\-- Association | Management <br>
\-- Authentication | Management <br>
\-- Beacon | Management <br>
\-- Probe | Management <br>
\-- Request to Send (RTS) | Control <br>
\-- Clear to Send (CTS) | Control <br>
\-- Acknowledgment (ACK) | Control <br>
\-- Data | Data <br>

\! 2 Modes:  <br>
\-- **Autonomous Access Point (AP)** <br>
\--\-- độc lập <br>
\-- **Lightweight Access Point (LAP)** <br>
\--\-- nhiều *LAP* được quản lý bởi **Wireless LAN Controller (WLC)** <br>
\--\-- có 2 mode: local và flexconnect (với flexconnect sẽ chuyển autonomous khi mất kết nối với WLC)

\! WiFi security protocols: <br>
\-- **WEP** - **RC4 40-bit**, **PWE**<br>
\-- **WPA** - **TKIP 128-bit with RC4**, **PSK & 802.1x**<br>
\-- **WPA2** - **AES 128-bit**, CCMP encryption, **PSK & 802.1x** <br>
\-- **WPA3** - **AES 128-bit (personal) 192-bit (enterprise)**-GCMP encryption, Simultaneous Authentication of Equals (**SAE**) & **802.1x** <br>

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

{: .highlight-title }
> Note
>
> __- 802.11r__ hay __fast BSS transition (FT)__ - hỗ trợ chuyển vùng nhanh <br>
> __- 802.11w__ - tăng cường bảo mật cho các frame quản lý được bảo vệ <br>

## Cisco WLC Interfaces, Ports

**<u>WLC Ports (Physical Interfaces)</u>**

![Alt text](/docs/CCNA/img/wlc-phy-int.png)

**Redundancy Port** - Cổng sử dụng cho **High-Availability (HA)** khi có 2 WLC. 2 port redun của 2 WLC sẽ đấu nhau.

**Service Port** - Cổng sử dụng cho **out-of-band management** bảo trì khi mạng lỗi. Là **access port**, không hỗ trợ trunk.

**SFP Distribution Port** - Kết nối với cổng logic bên trong và chứa lưu lượng không dây của máy khách.

**<u>WLC INTERFACES (LOGICAL INTERFACES)</u>**

![Alt text](/docs/CCNA/img/wlc-logic-int.png)

**Service Interface** - Giao diện quản trị, tách biệt với lưu lượng máy khách.

**Management Interface** - Giao diện quản trị, chung với lưu lượng máy khách.

**AP-Manager Interface** - Giao diện giao tiếp giữa controller và lightweight access points. AP-Manager IP address sử dụng như tunnel source cho các gói CAPWAP/LWAPP.

**Virtual Interface** - Giao diện cung cấp DHCP relay, authentication.

**Dynamic Interface** - Giao diện máy khách.

## 802.1x

Khi truy cập vào wifi, thường chỉ cần mật khẩu. Người quản trị chỉ xác định được số lượng truy cập, ip hay mac. Thiếu định danh, nhận dạng thiết bị an toàn hay được cho phép.

802.1x cung cấp đăng nhập yêu cầu username và password hay yêu cầu chứng chỉ CA được phép.

![Alt text](/docs/CCNA/img/802.1x_wired_protocols.png)

![Alt text](/docs/CCNA/img/802.1x.png)

## (lab is comming soon)
