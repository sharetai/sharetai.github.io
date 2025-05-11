---
layout: default
title: Switch Security
nav_order: 70
parent: CCNP
---

# Switch Security
{: .no_toc }

Bảo mật trên Switch
{: .fs-6 .fw-300 }

---

## TABLE OF CONTENTS
{: .no_toc .text-delta }

1. TOC
{:toc}

---

## Protected Port
<br>
Nếu muốn ngăn chặn giao tiếp giữa các thiết bị trong cùng 1 vlan, hay ngăn chặn các loại các tấn công trong cùng 1 phân đoạn mạng.

Mặc định các cổng là ___unprotected port___. Cổng cùng là ___protected port___ không giao tiếp được với nhau nhưng có thể giao tiếp với cổng ___unprotected port___.

![alt text](/docs/CCNP/img/switch-security-protected-port-1.png)
![alt text](/docs/CCNP/img/switch-security-protected-port-2.png)

```
conf t
int range e0/2-3
switchport protected
end
```

```
show interfaces switchport
```

<br>

## Private VLAN (PVLAN)
<br>
___Private VLAN___ sẽ chia nhỏ vlan này thành nhiều sub vlan riêng biệt.

Trong Private VLAN có các loại port sau:

\+ ___Promiscuous (P):___ thường kết nối tới router, là port cho phép gửi và nhận frame với bất kỳ port loại khác (gửi/nhận với P, I, C) <br>
\+ ___Isolated (I):___ thường được kết nối đến host, là port chỉ cho phép giao tiếp với port P (gửi/nhận với P) <br>
\+ ___Community (C):___ là port có thể giao tiếp với các port C cùng nhóm (community), có thể giao tiếp với port P (gửi/nhận với C, P).

Có các loại PVLAN sau: primary VLAN và secondary VLAN (isolated VLAN và community VLAN). <br>

\+ ___Primary VLAN:___ là VLAN ban đầu, VLAN này sẽ chuyển các frame downstream từ port P tới tất cả các kiểu port khác (port I và C). <br>
\+ ___Isolated VLAN:___ chuyển các frame từ port I tới port P. Do các port I không trao đổi frame với nhau, nên ta có thể chỉ dùng 1 isolated VLAN để kết nối tất cả các port I tới port P. <br>
\+ ___Community VLAN:___ chuyển đổi các frame giữa các port C thuộc cùng nhóm (community) và chuyển đổi các frame upstream tới port P của primary VLAN. <br>

![alt text](/docs/CCNP/img/switch-security-pvlan.png)

```
!
!
! Enter config mode
enable
conf t
!
!
! Set device to VTP TRANSPARENT mode
vtp mode transparent
!
!
! Create Primary VLANs: Primary, subject to subdivision
vlan 500
private-vlan primary
!
!
! Create Community VLAN: allows a subVLAN within a Primary VLAN
vlan 501
private-vlan community
!
!
! Create Isolated VLAN: Connects all stub hosts to router
vlan 502
private-vlan isolated
!
!
! Add Association
vlan 500
private-vlan association add 501,502
!
!
! Assign promiscuous port
int fa0/24
switchport mode private-vlan promiscuous
switchport private-vlan mapping 500 501,502
!
!
! Assign community port
int range fa0/1-2
switchport mode private-vlan host
switchport private-vlan host-association 500 501
!
!
! Assign isolated port
int range fa0/3-4
switchport mode private-vlan host
switchport private-vlan host-association 500 502
!
!
end
!
!
```

```
show interfaces [interface] switchport
show vlan private-vlan
show vlan private-vlan type
```

