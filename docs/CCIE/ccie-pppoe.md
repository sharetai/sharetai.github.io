---
layout: default
title: PPPoE
nav_order: 10
parent: CCIE
---

# PPP over Ethernet
{: .no_toc }

Point-to-Point Protocol over Ethernet
{: .fs-6 .fw-300 }

_Nguồn tham khảo: [http://ccie-in-2-months.blogspot.com/](http://ccie-in-2-months.blogspot.com/p/the-hints-series.html)_

---

## TABLE OF CONTENTS
{: .no_toc .text-delta }

1. TOC
{:toc}

---

PPP (Point-to-Point Protocol) is defined in [RFC 1661](http://tools.ietf.org/html/rfc1661).<br>
PPPoE (PPP over Ethernet) is described in [RFC 2516](http://tools.ietf.org/html/rfc2516).

---

<u>Topo</u>

\[ PPPoE client \] e0/0 ------------ e0/1 \[ Switch \] e0/0 ------------ e0/1 \[ PPPoE server \]

---

## <u>PPPoE</u>

IOS
{: .label .label-blue }

<u>PPPoE server</u>
```
conf t

hostname PPPoE-server
!
bba-group pppoe ccie
 virtual-template 1
!
interface Virtual-Template1
 mtu 1492
 ip address 10.10.10.1 255.255.255.0
!
interface e0/1
 no shut
 pppoe enable group ccie

end
write
```

<u>PPPoE client</u>
```
conf t

hostname PPPoE-client
!
interface e0/0
 no shut
 pppoe enable
 pppoe-client dial-pool-number 1
!
interface Dialer1
 mtu 1492
 ip address 10.10.10.2 255.255.255.0
 encapsulation ppp
 dialer pool 1

end
write
```

test
```
PPPoE-client#ping 10.10.10.1
Type escape sequence to abort.
Sending 5, 100-byte ICMP Echos to 10.10.10.1, timeout is 2 seconds:
!!!!!
Success rate is 100 percent (5/5), round-trip min/avg/max = 1/1/1 ms
```

## <u>PPP Authentication</u>

IOS
{: .label .label-blue }

<u>PPPoE server</u>
```
conf t

username u1 password 123
!
interface Virtual-Template1
 encapsulation ppp
 ppp authentication chap

end
write
```

<u>PPPoE client</u>
```
conf t

interface Dialer1
 encapsulation ppp
 ppp chap hostname u1
 ppp chap password 123

end
write
```

test
```
PPPoE-client#ping 10.10.10.1
Type escape sequence to abort.
Sending 5, 100-byte ICMP Echos to 10.10.10.1, timeout is 2 seconds:
!!!!!
Success rate is 100 percent (5/5), round-trip min/avg/max = 1/1/1 ms
```

## <u>FTTH</u>

IOS
{: .label .label-blue }

<u>BRAS</u>
```
conf t

hostname BRAS
!
username ftth_u1 password 123
!
bba-group pppoe ccie_group
 virtual-template 1
!
interface Virtual-Template1
 mtu 1492
 ip unnumbered e0/0
 peer default ip address pool ccie_pool
 ppp authentication chap
!
interface e0/1
 no shutdown
 pppoe enable group ccie_group
!
interface e0/0
 no shutdown
 ip address 210.245.0.1 255.255.255.0
!
ip local pool ccie_pool 210.245.0.2 210.245.0.254

end
write
```

<u>Modem</u>
```
conf t

hostname Modem
!
interface e0/0
 no shut
 pppoe enable
 pppoe-client dial-pool-number 1
!
interface Dialer1
 mtu 1492
 ip address negotiated
 encapsulation ppp
 dialer pool 1
 ppp chap hostname ftth_u1
 ppp chap password 123

end
write
```

test
```
Modem#show ip int bri
Interface                  IP-Address      OK? Method Status                Protocol
Ethernet0/0                unassigned      YES unset  up                    up
Ethernet0/1                unassigned      YES unset  administratively down down
Ethernet0/2                unassigned      YES unset  administratively down down
Ethernet0/3                unassigned      YES unset  administratively down down
Dialer1                    210.245.0.2     YES IPCP   up                    up
Virtual-Access1            unassigned      YES unset  up                    up
Virtual-Access2            unassigned      YES unset  up                    up
Modem#ping 210.245.0.1
Type escape sequence to abort.
Sending 5, 100-byte ICMP Echos to 210.245.0.1, timeout is 2 seconds:
!!!!!
Success rate is 100 percent (5/5), round-trip min/avg/max = 1/1/2 ms
```



