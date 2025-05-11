---
layout: default
title: Router Security Features 
nav_order: 140
parent: CCNP
---

# Router Security Features 
{: .no_toc }

Tính năng bảo mật của bộ định tuyến
{: .fs-6 .fw-300 }

---

## TABLE OF CONTENTS
{: .no_toc .text-delta }

1. TOC
{:toc}

---

## Zone-Based Firewall

<h3> Overview </h3>

Zone xác định lưu lượng truy cập có thể chấp nhận được phép đi qua giữa các zone thông qua các hạn chế về chính sách.

<h3> Configuration and Verification </h3>

![alt text](/docs/CCNP/img/Cisco-Zone-Based-Firewall-1.avif)

Tạo zone trên ZBFirewall

```
ZBFirewall(config)#zone security OUTSIDE
ZBFirewall(config-sec-zone)#exit
ZBFirewall(config)#zone security INSIDE
ZBFirewall(config-sec-zone)#
```

Gán port cho zone

```
ZBFirewall(config)#interface G0/0/0
ZBFirewall(config-if)#zone-member security OUTSIDE
ZBFirewall(config-if)#exit
ZBFirewall(config)#interface G0/0/1
ZBFirewall(config-if)#zone-member security INSIDE
```

Cấu hình zone pair

```
ZBFirewall(config)#zone-pair security IN-to-OUT source INSIDE destination OUTSIDE
ZBFirewall(config-sec-zone-pair)#description INSIDE TO OUTSIDE TRAFFIC
ZBFirewall(config-sec-zone-pair)#exit
ZBFirewall(config)#zone-pair security OUT-to-IN source OUTSIDE destination INSIDE
ZBFirewall(config-sec-zone-pair)#description OUTSIDE TO INSIDE TRAFFIC
```

Kiểm tra cấu hình zone

```
ZBFirewall#show zone security
zone self
Description: System defined zone

zone OUTSIDE
Member Interfaces:
GigabitEthernet0/0/0

zone INSIDE
Member Interfaces:
GigabitEthernet0/0/1
```

Kiểm tra cấu hình zone pair

```
ZBFirewall#show zone-pair security
Zone-pair name IN-to-OUT
Description: INSIDE TO OUTSIDE TRAFFIC
Source-Zone INSIDE Destination-Zone OUTSIDE
service-policy not configured

Zone-pair name OUT-to-IN
Description: OUTSIDE TO INSIDE TRAFFIC
Source-Zone OUTSIDE Destination-Zone INSIDE
service-policy not configured
```

Nếu thử gửi lưu lượng giữa các zone, theo mặc định, nó sẽ không thành công. Đó là bởi vì cần phải cấu hình các chính sách bảo mật để quyết định điều gì sẽ xảy ra với lưu lượng truy cập.

```
ISP#ping 10.10.1.2
Type escape sequence to abort.
Sending 5, 100-byte ICMP Echos to 10.10.1.2, timeout is 2 seconds:
.....
Success rate is 0 percent (0/5)
```

Tạo một chính sách bảo mật cho phép lưu lượng ICMP có thể đi từ zone INSIDE đến zone OUTSIDE

```
ZBFirewall(config)#class-map type inspect ?
WORD class-map name
match-all Logical-AND all matching statements under this classmap
match-any Logical-OR all matching statements under this classmap

ZBFirewall(config)#class-map type inspect ICMP
ZBFirewall(config-cmap)#match protocol icmp
ZBFirewall(config-cmap)#exit
ZBFirewall(config)#policy-map type inspect IN-OUT-ICMP
ZBFirewall(config-pmap)#class type inspect ICMP
ZBFirewall(config-pmap-c)#inspect
```

Áp chính sách IN-OUT-ICMP cho zone pair IN-to-OUT

```
ZBFirewall(config)#zone-pair security IN-to-OUT source INSIDE destination OUTSIDE
ZBFirewall(config-sec-zone-pair)#service-policy type inspect IN-OUT-ICMP
```

Ping lại sẽ thành công.

```
ISP#ping 10.10.1.2
Type escape sequence to abort.
Sending 5, 100-byte ICMP Echos to 10.10.1.2, timeout is 2 seconds:
!!!!!
Success rate is 100 percent (5/5), round-trip min/avg/max = 1/1/1 ms
```

Kiểm tra lại chính sách

```
ZBFirewall#show policy-map type inspect zone-pair sessions

policy exists on zp IN-to-OUT
Zone-pair: IN-to-OUT

Service-policy inspect : IN-OUT-ICMP

Class-map: ICMP (match-all)
Match: protocol icmp
Inspect

Class-map: class-default (match-any)
Match: any
Drop (default action)
0 packets, 0 bytes
```

## Control Plane Policing (CoPP)

<h3> Overview </h3>

__Control Plane Policing (CoPP)__ là bộ lọc QoS được áp dụng cho lưu lượng truy cập được hướng đến hoặc tạo bởi __CPU Control Plane (CP)__ của bộ định tuyến. Chính sách CoPP hạn chế lưu lượng truy cập đã biết ở một tốc độ cụ thể đồng thời bảo vệ CPU khỏi tốc độ lưu lượng truy cập cao bất ngờ có thể gây nguy hiểm cho tính ổn định của bộ định tuyến. Kết quả là CP vẫn có thể điều chỉnh trạng thái chuyển tiếp gói và giao thức ngay cả khi phải đối mặt với tình trạng quá tải lưu lượng.

<h3> Configuration </h3>

![alt text](/docs/CCNP/img/Cisco-CoPP.png)

```
Router1(config)#ip access-list extended ACL-EIGRP
Router1(config-ext-nacl)#permit eigrp any any
Router1(config)#ip access-list extended ACL-ICMP
Router1(config-ext-nacl)#permit icmp any any
Router1(config)#ip access-list extended ACL-TELNET
Router1(config-ext-nacl)#permit tcp any any eq 23

Router1(config)#class-map CLASS-EIGRP
Router1(config-cmap)#match access-group name ACL-EIGRP
Router1(config)#class-map CLASS-ICMP
Router1(config-cmap)#match access-group name ACL-ICMP
Router1(config)#class-map CLASS-TELNET
Router1(config-cmap)#match access-group name ACL-TELNET

Router1(config)#policy-map CoPP
Router1(config-pmap)#class CLASS-EIGRP
Router1(config-pmap-c)#police 64000 conform-action transmit exceed-action transmit violate-action transmit
Router(config-pmap-c)#exit
Router1(config-pmap)#class CLASS-ICMP
Router1(config-pmap-c)#police 8000 conform-action transmit exceed-action transmit violate-action drop
Router1(config-pmap-c)#exit
Router1(config-pmap)#class CLASS-TELNET
Router1(config-pmap-c)#police 8000 conform-action transmit exceed-action transmit violate-action drop
Router1(config-pmap-c)#exit

Router1(config)#control-plane
Router1(config-cp)#service-policy input CoPP
```

<h3> Verification </h3>

```
Router1#show policy-map control-plane input
Control Plane
Service-policy input: CoPP

Class-map: CLASS-ICMP (match-all)
5 packets, 490 bytes
5 minute offered rate 0000 bps, drop rate 0000 bps
Match: access-group name ACL-ICMP
police:
cir 8000 bps, bc 1500 bytes, be 1500 bytes
conformed 5 packets, 490 bytes; actions:
transmit
exceeded 0 packets, 0 bytes; actions:
transmit
violated 0 packets, 0 bytes; actions:
drop
conformed 0000 bps, exceeded 0000 bps, violated 0000 bps

Class-map: CLASS-TELNET (match-all)
15 packets, 1026 bytes
5 minute offered rate 0000 bps, drop rate 0000 bps
Match: access-group name ACL-TELNET
police:
cir 8000 bps, bc 1500 bytes, be 1500 bytes
conformed 15 packets, 1026 bytes; actions:
transmit
exceeded 0 packets, 0 bytes; actions:
transmit
violated 0 packets, 0 bytes; actions:
drop
conformed 0000 bps, exceeded 0000 bps, violated 0000 bps

Class-map: CLASS-EIGRP (match-all)
25 packets, 2318 bytes
5 minute offered rate 0000 bps, drop rate 0000 bps
Match: access-group name ACL-EIGRP
police:
cir 64000 bps, bc 2000 bytes, be 2000 bytes
conformed 206 packets, 19360 bytes; actions:
transmit
exceeded 0 packets, 0 bytes; actions:
transmit
violated 0 packets, 0 bytes; actions:
transmit
conformed 0000 bps, exceeded 0000 bps, violated 0000 bps

Class-map: class-default (match-any)
53 packets, 13479 bytes
5 minute offered rate 0000 bps, drop rate 0000 bps
Match: any
```