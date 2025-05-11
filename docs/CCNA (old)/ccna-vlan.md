---
layout: default
title: VLAN
nav_order: 20
parent: CCNA (old)
---

# Virtual Local Area Network
{: .no_toc }

Mạng LAN ảo
{: .fs-6 .fw-300 }

---

## TABLE OF CONTENTS
{: .no_toc .text-delta }

1. TOC
{:toc}

---

## Mô hình phân cấp ba lớp của Cisco
<br>
Do mạng có thể cực kỳ phức tạp với nhiều giao thức và công nghệ đa dạng nên Cisco đã phát triển mô hình phân cấp nhiều lớp để thiết kế cơ sở hạ tầng mạng đáng tin cậy. Mô hình ba lớp này giúp thiết kế, triển khai và duy trì mạng có thể mở rộng, đáng tin cậy và tiết kiệm chi phí. Mỗi lớp có các tính năng và chức năng riêng, giúp giảm độ phức tạp của mạng.

<img src="/docs/CCNA (old)/img/cisco_hierarchical_model.png" height="540" width="802">

### Three-Tier Network Architecture

{: .highlight-title }
> Note
>
> \- Gồm 3 lớp Core, Distribution, Access <br>
> \- Lớp Access kết nối trực tiếp thiết bị đầu cuối <br>
> \- Lớp Distribution sử dụng như thiết bị tổng hợp lưu lượng từ access và đẩy lên Core. Định tuyến và lọc các lưu lượng đẩy lên core. <br>
> \- Lớp Core là lớp chịu trách nhiệm vận chuyển lượng lớn lưu lượng một cách nhanh chóng, thường có 2 thiết bị trở lên để đảm bảo lưu lượng luôn được tiếp tục <br>
> \- Khi nâng cấp thì phương án sẽ là (scale up) nâng cấp thiết bị <br>

<img src="/docs/CCNA (old)/img/three-tier-architecture.png" height="428" width="547">

### Collapsed Core Architecture

{: .highlight-title }
> Note
>
> \- 2 lớp Core và Distribution gom lại thành 1 lớp <br>
> \- Tiết kiệm chi phí thiết bị <br>

<img src="/docs/CCNA (old)/img/collapsed-core-architecture.png" height="375" width="526">

### Spine and Leaf Network Architecture

{: .highlight-title }
> Note
>
> \- Phù hợp với mạng trung tâm dữ liệu. Khi lưu lượng đông-tây nhiều hơn lưu lượng bắc-nam (lưu lượng giữa các máy trạm nhiều hơn lưu lượng đi internet). <br>
> \- 1 Leaf sẽ kết nối đến tất cả các Spine và ngược lại <br>
> \- Khi nâng cấp thì phương án sẽ là (scale ngang) thêm 1 Leaf hoặc 1 Spine <br>
> \- Chi phí từ 1 host đến 1 host là như nhau, số hop giống nhau <br>

<img src="/docs/CCNA (old)/img/spine-and-leaf-architecture.png" height="272" width="705">

<br>

## Chia vlan
<br>
![image](/docs/CCNA (old)/img/vlan0.png)

![image](/docs/CCNA (old)/img/vlan1.png)

### Bước 1: Tạo Vlan

* __SW1__

```
int g0/1
switchport mode trunk
switchport trunk allowed vlan 101,102,103
switchport trunk native vlan 3999
```

{: .highlight-title }
> Switch port modes:
>
> __- switchport mode access__ - Đưa port vào trạng thái access, nontrunking. <br>
> __- switchport mode trunk__ - Đưa port vào trạng thái trunk và gửi DTP để thương lượng chuyển đổi port đầu xa thành trunk. Kể cả khi thương lượng thất bại port đầu gần vẫn sẽ lên trunk. <br>
> __- switchport mode dynamic desirable__ - Đưa port vào trạng thái chủ động gửi DTP để thương lượng chuyển đổi port đầu xa thành trunk. chỉ khi thương lượng thành công port đầu gần sẽ lên trunk. <br>
> __- switchport mode dynamic auto__ - Đưa port vào trạng thái chờ chuyển đổi trunk khi nhận DTP từ __mode trunk__ hoặc __mode dynamic desirable__. Là trạng thái mặc địch của port switch.<br>
> __- switchport nonegotiate__ - Không gửi DTP và không nhận DTP.<br>

```
vlan 101
name Hanhchanh
vlan 102
name Kinhdoanh
vlan 103
name Ketoan
exit

vtp mode server
vtp domain ABC
vtp pass 123
```

* __SW2__

```
vtp mode client
vtp domain ABC
vtp pass 123
```

*(vtp có 3 mode: server có thể tạo và xoá vlan, gửi đi cập nhật; client không thể thay đổi vlan, nhận cập nhật và chuyển tiếp; transparent không cập nhật, chỉ chuyển tiếp trong suốt)*

### Bước 2: Đưa port vào Vlan

```
int range f0/1-2
switchport mode access 
switchport access vlan 101

... (tương tự cho đưa port vào vlan phù hợp)
```

<br>

## Inter Vlan
<br>
### Cách 1: Sub interface (Giải pháp Router on a Stick)

![image](/docs/CCNA (old)/img/vlan2.png)

* __Router__

```
int g0/0
no shut
ip address 192.168.1.254 255.255.255.0

int g0/0.1
encapsulation dot1Q 101
ip address 192.168.101.254 255.255.255.0
int g0/0.2
encapsulation dot1Q 102
ip address 192.168.102.254 255.255.255.0
int g0/0.3
encapsulation dot1Q 103
ip address 192.168.103.254 255.255.255.0
```

### Cách 2: SW Layer 3 (Giải pháp SVI - Switch Virtual Interface)

![image](/docs/CCNA (old)/img/vlan3.png)

* __Core__

```
conf t
ip routing
int vlan 1
no shut
ip add 192.168.1.254 255.255.255.0
int vlan 101
ip add 192.168.101.254 255.255.255.0
int vlan 102
ip add 192.168.102.254 255.255.255.0
int vlan 103
ip add 192.168.103.254 255.255.255.0
```

<br>

## Dynamic Trunking Protocol (DTP)
<br>
__DTP__, __Dynamic Trunking Protocol__, là giao thức trunking được phát triển và độc quyền của Cisco, được sử dụng để tự động đàm phán thiết lập trunk giữa các thiết bị chuyển mạch của Cisco. DTP chỉ hoạt động nếu cổng được kết nối trực tiếp với nhau.

<h3> Các mode DTP </h3>

__switchport mode access__ - cổng sẽ trở thành port access, không trunk kể cả khi cổng kết nối là trunk, chỉ cho phép 1 vlan đi qua.

__switchport mode trunk__ - cổng sẽ trở thành port trunk kể cả khi cổng kết nối không là trunk, cho phép nhiều vlan đi qua và có gắn tag.

__switchport mode dynamic auto__ - cổng sẽ chờ để có thể trở thành port trunk hay không, là trunk khi cổng kết nối ở mode trunk hoặc dynamic desirable, là chế độ mặc định ban đầu của các dòng switch mới.

__switchport mode dynamic desirable__ - cổng sẽ chủ động đàm phán trunk, là trunk khi cổng kết nối ở mode trunk hoặc dynamic desirable hay dynamic auto, là chế độ mặc định ban đầu của các dòng switch cũ.

__switchport nonegotiate__ - lệnh này sẽ vô hiệu hóa DTP.

<h3> DTP negotiation </h3>

__Trunk Mode__      | Dynamic Auto  | Dynamic Desirable | Trunk                 | Access
Dynamic Auto        | Access        | __Trunk__         | __Trunk__             | Access
Dynamic Desirable   | __Trunk__     | __Trunk__         | __Trunk__             | Access
Trunk               | __Trunk__     | __Trunk__         | __Trunk__             | Limited connectivity
Access              | Access        | Access            | Limited connectivity  | Access

<br>
