---
layout: default
title: PPPoE
nav_order: 26
parent: CCNA
---

# Point-to-Point Protocol over Ethernet
{: .no_toc }

Giao thức điểm-điểm qua Ethernet
{: .fs-6 .fw-300 }

---

	Modem1 (e0/0)------------(e0/1) SW (e0/0)------------(e0/1) BRAS
	Modem2 (e0/0)------------(e0/2) -┘

* __BRAS__

```
en
conf t
hostname BRAS
!
username ftth_u1 password 123
!
bba-group pppoe NHATNGHE
 virtual-template 1
!
interface Virtual-Template1
 mtu 1492
 ip unnumbered Ethernet0/0
 peer default ip address pool NN_DHCP
 ppp authentication chap callin
!
interface Ethernet0/1
 no shutdown
 no ip address
 pppoe enable group NHATNGHE
!
interface Ethernet0/0
 no shutdown
 no ip address
 ip address 210.245.0.1 255.255.255.0
!
ip local pool NN_DHCP 210.245.0.2 210.245.0.254
!
end
write

```

* __Modem1__

PAP authen

```
en
conf t
hostname Modem1
!
interface Ethernet0/0
 no shutdown
 no ip address
 pppoe enable
 pppoe-client dial-pool-number 1
!
interface Dialer0
 mtu 1492
 ip address negotiated
 encapsulation ppp
 dialer pool 1
 ppp authentication pap callin
 ppp pap sent-username ftth_u1 password 123
!
end
write

```

CHAP authen

```
en
conf t
hostname Modem1
!
interface Ethernet0/0
 no shutdown
 no ip address
 pppoe enable
 pppoe-client dial-pool-number 1
!
interface Dialer0
 mtu 1492
 ip address negotiated
 encapsulation ppp
 dialer pool 1
 ppp chap hostname ftth_u1
 ppp chap password 123
!
end
write

```

DHCP

```
conf t
int e0/1
no shut
ip addr 192.168.1.1 255.255.255.0
!
service dhcp
!
ip dhcp pool 1
network 192.168.1.0 255.255.255.0
default-router 192.168.1.1
!
end
write

```

NAT

```
conf t
access-list 1 permit any
ip nat inside source list 1 int Dialer0 overload
int Dialer0
ip nat outside
int e0/1
ip nat inside
end
write

```

Default route

```
conf t
ip route 0.0.0.0 0.0.0.0 210.245.0.1
end
write

```

* __Test__

```
show pppoe session
show ip int brief
ping 210.245.0.1
```

```
GHI CHÚ:

Nếu có PPPoE thì phải sửa cấu hình: NAT, VPN thành cổng Dialer thay cho cổng Vật lý

	LAN ----(e0/1) Modem1 (e0/0 - Dialer0: pppoe)  ------- Internet

vd: Modem1 cấu hình NAT

	conf t
	access-list 1 permit any
	(ip nat inside source list 1 int e0/0 overload)
	ip nat inside source list 1 int dialer 0 overload
	int DIALER 0
	ip nat outside
	int e0/1
	ip nat inside
	
VPN theo sơ đồ trong bài học, phải thay cổng f0/1 bằng Dialer 0
	int f0/1 ---> int dialer 0
	crypto map MAP1
```
