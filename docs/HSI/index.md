---
layout: default
title: HSI
nav_order: 3.5
has_children: false
---

# High Speed Internet
{: .no_toc }

Dịch vụ truy cập internet tốc độ cao cố định
{: .fs-6 .fw-300 }

---

## TABLE OF CONTENTS
{: .no_toc .text-delta }

1. TOC
{:toc}

---

## Sơ đồ

![](/docs/HSI/img/hsi.png)

## Cấu hình

### OSPF

#### # SRT
```
conf t
hostname SRT
interface Loopback0
ip address 1.1.1.1 255.255.255.255
!
interface Ethernet0/0
ip address 10.12.0.1 255.255.255.248
no shutdown
!
router ospf 2
router-id 1.1.1.1
network 1.1.1.1 0.0.0.0 area 0
network 10.12.0.1 0.0.0.0 area 0
!
end
write
```

#### # AGG
```
conf t
hostname AGG
interface Loopback0
ip address 2.2.2.2 255.255.255.255
!
interface Ethernet0/0
ip address 10.23.0.2 255.255.255.248
no shutdown
!
interface Ethernet0/1
ip address 10.12.0.2 255.255.255.248
no shutdown
!
router ospf 2
router-id 2.2.2.2
network 2.2.2.2 0.0.0.0 area 0
network 10.23.0.2 0.0.0.0 area 0
network 10.12.0.2 0.0.0.0 area 0
!
end
write
```

#### # PRT
```
conf t
hostname PRT
interface Loopback0
ip address 3.3.3.3 255.255.255.255
!
interface Ethernet0/1
ip address 10.23.0.3 255.255.255.248
no shutdown
!
interface Ethernet0/2
ip address 8.8.8.1 255.255.255.0
no shutdown
!
router ospf 2
router-id 3.3.3.3
network 3.3.3.3 0.0.0.0 area 0
network 10.23.0.3 0.0.0.0 area 0
!
end
write
```

Kiểm tra
```
SRT#show ip route ospf
...

Gateway of last resort is not set

      2.0.0.0/32 is subnetted, 1 subnets
O        2.2.2.2 [110/11] via 10.12.0.2, 00:00:32, Ethernet0/0
      3.0.0.0/32 is subnetted, 1 subnets
O        3.3.3.3 [110/21] via 10.12.0.2, 00:00:22, Ethernet0/0
      10.0.0.0/8 is variably subnetted, 3 subnets, 2 masks
O        10.23.0.0/29 [110/20] via 10.12.0.2, 00:00:32, Ethernet0/0
```

### MPLS

#### # SRT
```
conf t
mpls ldp explicit-null
!
interface Ethernet0/0
mpls ip
!
end
write
```

#### # AGG
```
conf t
mpls ldp explicit-null
!
interface Ethernet0/0
mpls ip
!
interface Ethernet0/1
mpls ip
!
end
write
```

#### # PRT
```
conf t
mpls ldp explicit-null
!
interface Ethernet0/1
mpls ip
!
end
write
```

Kiểm tra
```
SRT#show mpls forwarding-table
Local      Outgoing   Prefix           Bytes Label   Outgoing   Next Hop
Label      Label      or Tunnel Id     Switched      interface
16         explicit-n 2.2.2.2/32       0             Et0/0      10.12.0.2
17         17         3.3.3.3/32       0             Et0/0      10.12.0.2
18         explicit-n 10.23.0.0/29     0             Et0/0      10.12.0.2
```

### Ethernet Pseudowires

#### # SRT
```
conf t
!
interface Ethernet0/1
no shutdown
xconnect 3.3.3.3 1000 encapsulation mpls
!
end
write
```

#### # PRT
```
conf t
!
interface Ethernet0/0
no shutdown
!
interface Ethernet0/0.11
encapsulation dot1Q 11
xconnect 1.1.1.1 1000 encapsulation mpls
!
end
write
```

Kiểm tra
```
SRT#show xconnect all
...

XC ST  Segment 1                         S1 Segment 2                         S2
------+---------------------------------+--+---------------------------------+--
UP pri   ac Et0/1:4(Ethernet)            UP mpls 3.3.3.3:1000                 UP
```

### PPPoE

#### # Modem
```
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

#### # BRAS Cisco
```
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
!
interface Ethernet0/1.11
 encapsulation dot1Q 11
 pppoe enable group NHATNGHE
!
interface Ethernet0/0
 no shutdown
 ip address 210.245.0.1 255.255.255.0
!
ip local pool NN_DHCP 210.245.0.2 210.245.0.254
!
end
write
```

Kiểm tra
```
Modem1#show ip int brief
Interface                  IP-Address      OK? Method Status                Protocol
...
Dialer0                    210.245.0.2     YES IPCP   up                    up
...
```


### Cấu hình khác

#### # Modem

##### DHCP Server
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

##### NAT
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

##### Default Route
```
conf t
ip route 0.0.0.0 0.0.0.0 210.245.0.1
end
write
```

#### # PRT

##### OSPF 4050 giữa CT-BRAS
```
conf t
!
interface Ethernet0/0.4050
encapsulation dot1Q 4050
ip addr 10.34.0.3 255.255.255.248
!
router ospf 4050
network 10.34.0.3 0.0.0.0 area 4050
!
end
write
```

#### # BRAS Cisco

##### OSPF 4050 giữa CT-BRAS
```
conf t
!
interface Ethernet0/1.4050
 encapsulation dot1Q 4050
 ip address 10.34.0.4 255.255.255.248
!
router ospf 4050
 network 10.34.0.4 0.0.0.0 area 4050
 network 210.245.0.1 0.0.0.0 area 4050
!
end
write
```

##### Default Route
```
conf t
!
ip route 0.0.0.0 0.0.0.0 10.34.0.3
!
end
write
```

