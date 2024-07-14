---
layout: default
title: DHCP
nav_order: 15
parent: CCNA
---

# Dynamic Host Configuration Protocol
{: .no_toc }

Giao thức cấp phát địa chỉ IP động
{: .fs-6 .fw-300 }

---

## Table of contents
{: .no_toc .text-delta }

1. TOC
{:toc}

---

![Alt text](/docs/CCNA/img/dhcp-process.png)

![image](/docs/CCNA/img/dhcp-lap.png)

## Routing

```
R1(config)#ip route 192.168.2.0 255.255.255.0 10.0.0.2
R2(config)#ip route 192.168.1.0 255.255.255.0 10.0.0.1
```

## DHCP Server

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

