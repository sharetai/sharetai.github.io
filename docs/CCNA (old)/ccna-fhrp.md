---
layout: default
title: FHRP
nav_order: 17
parent: CCNA (old)
---

# First Hop Redundancy Protocol
{: .no_toc }

Giao thức dự phòng bước nhảy đầu tiên
{: .fs-6 .fw-300 }

---

## TABLE OF CONTENTS
{: .no_toc .text-delta }

1. TOC
{:toc}

---

<h2 style="display:inline-block">why?</h2><p style="display:inline-block">
Khi gateway duy nhất gặp sự cố, cần có 1 gateway dự phòng sẵn sàng thay thế, tự động chuyển tiếp các gói tin, đảm bảo lưu lượng mạng không bị gián đoạn.</p>

## HSRP

__Hot Standby Router Protocol (HSRP)__ cung cấp tính năng dự phòng cho router. Nếu một router gặp sự cố thay vì cấu hình chuyển đổi router cho máy tính người dùng bằng tay, giao thức này sẽ tự động hoá cho hệ thống

__HSRP state__ <br>
Active – Trạng thái chủ động chuyển tiếp lưu lượng. <br>
Init or Disabled – Trạng thái khởi động, chưa sẵn sàng hoặc chưa thể tham gia HSRP. <br>
Learn – Trạng thái chưa xác định địa chỉ IP ảo và chờ tin nhắn hello. <br>
Listen – Trạng thái đã xác định địa chỉ IP ảo và đang nhận tin nhắn hello. <br>
Speak – Trạng thái đang gửi và nhận tin nhắn hello. <br>
Standby – Trạng thái sẵn sàng tiếp quản nhiệm vụ chuyển tiếp lưu lượng từ thiết bị đang Active. <br>

![image](/docs/CCNA (old)/img/hsrp.png)

* __R1__

```
R1(config)#int g0/0
R1(config-if)#standby 1 ip 10.0.0.254
R1(config-if)#standby 1 priority 120
R1(config-if)#standby 1 preempt 
```

* __R2__

```
R2(config)#int g0/0
R2(config-if)#standby 1 ip 10.0.0.254
```

*(Nhược điểm: Lưu lượng dồn về 1 mặt router ưu tiên)*

## HSRP - Cân bằng tải bằng cách tạo 2 Default Gateway

* __R1__

```
R1(config)#int g0/0
R1(config-if)#standby 1 ip 10.0.0.254
R1(config-if)#standby 1 priority 120
R1(config-if)#standby 1 preempt
R1(config-if)#standby 2 ip 10.0.0.253
```

* __R2__

```
R2(config)#int g0/0
R2(config-if)#standby 1 ip 10.0.0.254
R2(config-if)#standby 2 ip 10.0.0.253
R2(config-if)#standby 2 priority 120
R2(config-if)#standby 2 preempt
```

*(Nhược điểm: Không thể cấp ip dhcp được do chỉ có thể cấp 1 default gateway, nên phải cấu hình default gateway thủ công từng máy)*

## HSRP - Cân bằng tải bằng cách tạo 2 vlan

* __R1__

```
R1(config)#int g0/0.10
R1(config-if)#encapsulation dot1q 10
R1(config-if)#standby 1 ip 10.0.0.254
R1(config-if)#standby 1 priority 120
R1(config-if)#standby 1 preempt
R1(config)#int g0/0.20
R1(config-if)#encapsulation dot1q 20
R1(config-if)#standby 2 ip 10.0.0.254
R1(config-if)#standby 2 priority 100
R1(config-if)#standby 2 preempt
```

* __R2__

```
R2(config)#int g0/0.10
R2(config-if)#encapsulation dot1q 10
R2(config-if)#standby 1 ip 10.0.0.254
R2(config-if)#standby 1 priority 100
R2(config-if)#standby 1 preempt
R2(config)#int g0/0.20
R2(config-if)#encapsulation dot1q 20
R2(config-if)#standby 2 ip 10.0.0.254
R2(config-if)#standby 2 priority 120
R2(config-if)#standby 2 preempt
```

*(Nhược điểm: Phải chia thủ công vlan người dùng)*

## HSRP - Track giám sát trạng thái port

* __R1__

```
R1(config)#track 9 int g0/1 line-protocol
R1(config)#int g0/0
R1(config-if)#standby 1 ip 10.0.0.254
R1(config-if)#standby 1 priority 120 -> 90 (trường hợp g0/1 down)
R1(config-if)#standby 1 preempt
R1(config-if)#standby 1 track 9 decrement 30
```

* __R2__

```
R2(config)#int g0/0
R2(config-if)#standby 1 ip 10.0.0.254
R2(config-if)#standby 1 priority 100
R2(config-if)#standby 1 preempt
```

## GLBP

__Gateway Load Balancing Protocol (GLBP)__ là một giao thức độc quyền của Cisco cố gắng khắc phục những hạn chế của các giao thức bộ định tuyến dự phòng hiện có bằng cách thêm chức năng cân bằng tải cơ bản .

* __R1__

```
R1(config)#int g0/0
R1(config-if)#glbp 1 ip 10.0.0.254
R1(config-if)#glbp 1 priority 120
R1(config-if)#glbp 1 preempt 
```

* __R2__

```
R2(config)#int g0/0
R2(config-if)#glbp 1 ip 10.0.0.254
```

## HSRP & VRRP & GLBP

| FHRP           | HSRP                                                   | VRRP                         | GLBP                                                                     |
| :------------- | :----------------------------------------------------- | :--------------------------- | :----------------------------------------------------------------------- |
| Term           | 1 Active<br>1 Standby<br>1 or more listening           | 1 Master<br>1 or more Backup | 1 AVG (Active Virtual Gateway)<br>Up to 4 AVF (Active Virtual Forwarder) |
| Scope          | Cisco Proprietary                                      | IEEE Standard                | Cisco Proprietary                                                        |
| Virtual MAC    | v1: 0000.0c07.ac<u>XX</u><br>v2: 0000.0c9f.f<u>XXX</u> | 0000.5e00.01<u>XX</u>        | 0007.b400.<u>XXYY</u>                                                    |
| Multicast IP   | v1: 224.0.0.2 - UDP 1985<br>v2: 224.0.0.102 - UDP 1985 | 224.0.0.18 - UDP 112         | 224.0.0.102 - UDP 3222                                                   |
| Timers         | Hello - 3s<br>Hold - 10s                               | Advertisement - 1s<br>Down Interval = 3*Advertisement         | Hello - 3s<br>Hold - 10s                |
| Group Range    | 0 to 255                                               | 0 to 255                     | 0 to 1023                                                                |
| Priority Range | 1 to 255, Default 100                                  | 1 to 255, Default 100        | 1 to 255, Default 100                                                    |
| Support IPv6   | HSRPv2                                                 | VRRPv3                       | GLBP                                                                     |
| Preempt        | disabled by defaul                                     | enabled by defaul            | disabled by defaul                                                       |
| Authentication | MD5                                                    | No                           | MD5                                                                      |

