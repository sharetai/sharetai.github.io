---
layout: default
title: DHCP
nav_order: 15
parent: CCNA (old)
---

# Dynamic Host Configuration Protocol
{: .no_toc }

Giao thức cấp phát địa chỉ IP động
{: .fs-6 .fw-300 }

---

## TABLE OF CONTENTS
{: .no_toc .text-delta }

1. TOC
{:toc}

---

<h2>what?</h2>
 <br>
__DHCP__ là một giao thức mạng được sử dụng để cung cấp địa chỉ IP và các thông tin cấu hình khác cho các thiết bị trên một mạng. Nó giúp tự động hóa quá trình cấu hình, giảm bớt công việc thủ công và tăng tính linh hoạt của mạng.

__Cách hoạt động__ <br>
___- DHCP Discover:___ Một thiết bị mới kết nối với mạng sẽ gửi một gói tin DHCP Discover để yêu cầu địa chỉ IP và thông tin cấu hình khác. <br>
___- DHCP Offer:___ Một máy chủ DHCP sẽ trả lời với một gói tin DHCP Offer chứa địa chỉ IP, subnet mask, gateway và các thông tin khác. <br>
___- DHCP Request:___ Thiết bị mới sẽ gửi một gói tin DHCP Request để chấp nhận địa chỉ IP được cung cấp. <br>
___- DHCP Ack:___ Máy chủ DHCP sẽ trả lời với một gói tin DHCP Ack để xác nhận việc cấp phát địa chỉ IP. <br>

__Thông tin được cấp bởi DHCP__ <br>
___- Địa chỉ IP:___ Địa chỉ IP duy nhất cho thiết bị. <br>
___- Subnet mask:___ Xác định mạng con mà thiết bị thuộc về. <br>
___- Gateway:___ Địa chỉ IP của router mặc định. <br>
___- DNS server:___ Địa chỉ IP của máy chủ DNS. <br>
___- Lease time:___ Thời gian thuê địa chỉ IP. <br>

![Alt text](/docs/CCNA (old)/img/dhcp-process.png)

![image](/docs/CCNA (old)/img/dhcp-lap.png)

## Routing
 <br>

```
R1(config)#ip route 192.168.2.0 255.255.255.0 10.0.0.2
R2(config)#ip route 192.168.1.0 255.255.255.0 10.0.0.1
```

## DHCP Server
 <br>
___DHCP Server___ Cấp phát địa chỉ IP và thông tin cấu hình cho các thiết bị trên mạng. Quản lý pool địa chỉ IP. Giải phóng và gia hạn địa chỉ IP.

{: .note-title }
> Syntax
>
> R(config)# __ip dhcp pool__ _{name}_ <br/>
> R(dhcp-config)# __network__ _{network-number}_ _{mask}_ <br/>
> R(dhcp-config)# __default-router__ _{address}_ <br/>
> _(Optional)_ R(config)# __ip dhcp excluded-address__ _{low-address}_ _{high-address}_ <br/>
> R(config)# __service dhcp__

| Syntax | Function |
|:---|:---|
| R(config)# **ip dhcp pool** < name > | Khai báo tên pool |
| R(dhcp-config)# **network** < net-id > < subnet-mask > | Khai báo network sẽ cấp địa chỉ IP |
| R(dhcp-config)# **default-router** < ip-address > | Default gateway của các client |
| _(Optional)_ R(config)# **ip dhcp excluded-address** < ip-address > < ip-address > | Địa chỉ IP loại trừ không cấp |
| R(config)# **service dhcp** | Mở dịch vụ DHCP |

* **R1**

```
R1(config)#ip dhcp pool 1
R1(dhcp-config)#network 192.168.1.0 255.255.255.0
R1(dhcp-config)#default-router 192.168.1.254
R1(dhcp-config)#exit
R1(config)#ip dhcp excluded-address 192.168.1.1 192.168.1.10
R1(config)#service dhcp 
```

## DHCP Relay
<br>
___DHCP Relay___ Chuyển tiếp các yêu cầu DHCP từ các thiết bị không thể giao tiếp trực tiếp với DHCP Server đến DHCP Server. Giúp mở rộng phạm vi hoạt động của DHCP Server.

* **R1**

```
R1(config)#ip dhcp pool 2
R1(dhcp-config)#network 192.168.2.0 255.255.255.0
R1(dhcp-config)#default-router 192.168.2.254
```

* **R2**

```
R2(config)#int g0/1
R2(config-if)#ip helper-address 10.0.0.1

R2#show ip int g0/1
```

## APIPA (Automatic Private IP Addressing)

Là tính năng trong hệ điều hành (chẳng hạn như Windows) cho phép máy tính tự động định cấu hình địa chỉ IP và subnet mask khi máy chủ DHCP không thể truy cập được. Phạm vi địa chỉ IP cho APIPA là __169.254.0.1-169.254.255.254__, subnet mask là __255.255.0.0__.

__Cách hoạt động__ <br>
___- Kiểm tra DHCP:___ Khi máy tính khởi động, nó sẽ cố gắng nhận địa chỉ IP từ một máy chủ DHCP trên mạng. <br>
___- Không tìm thấy DHCP:___ Nếu không tìm thấy máy chủ DHCP, máy tính sẽ chuyển sang chế độ APIPA. <br>
___- Cấp phát địa chỉ IP:___ APIPA sẽ tự động cấp phát một địa chỉ IP riêng tư cho máy tính từ phạm vi 169.254.0.1 đến 169.254.255.255. <br>
___- Sử dụng địa chỉ IP:___ Máy tính có thể sử dụng địa chỉ IP này để giao tiếp với các thiết bị khác trên cùng một mạng. <br>
