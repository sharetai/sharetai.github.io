---
layout: default
title: OSPF Route
nav_order: 5
parent: JN0
---

# Open Shortest Path First Route
{: .no_toc }

Cấu hình OSPF
{: .fs-6 .fw-300 }

---

__Cấu hình__

![](/docs/JN0/img/2.png)

{: .note-title }
> Syntax
>
> __# set protocols ospf area__ _area-id_ __interface__ _interface-name_

```
# vMX1
set protocols ospf area 0.0.0.0 interface lo0.0
set protocols ospf area 0.0.0.0 interface ge-0/0/0.0

# vMX2
set protocols ospf area 0.0.0.0 interface lo0.0
set protocols ospf area 0.0.0.0 interface ge-0/0/0.0
set protocols ospf area 0.0.0.0 interface ge-0/0/1.0

# vMX3
set protocols ospf area 0.0.0.0 interface lo0.0
set protocols ospf area 0.0.0.0 interface ge-0/0/1.0
```

__Kiểm tra__

```
root@vMX1> show route

inet.0: 7 destinations, 7 routes (7 active, 0 holddown, 0 hidden)
+ = Active Route, - = Last Active, * = Both

1.1.1.1/32         *[Direct/0] 02:20:23
                    > via lo0.0
2.2.2.2/32         *[OSPF/10] 00:09:08, metric 1
                    > to 172.0.12.2 via ge-0/0/0.0
3.3.3.3/32         *[OSPF/10] 00:08:14, metric 2
                    > to 172.0.12.2 via ge-0/0/0.0
172.0.12.0/29      *[Direct/0] 02:19:27
                    > via ge-0/0/0.0
172.0.12.1/32      *[Local/0] 02:19:28
                      Local via ge-0/0/0.0
172.0.23.0/29      *[OSPF/10] 00:09:08, metric 2
                    > to 172.0.12.2 via ge-0/0/0.0
224.0.0.5/32       *[OSPF/10] 00:10:25, metric 1
                      MultiRecv

root@vMX1> ping 2.2.2.2 rapid
PING 2.2.2.2 (2.2.2.2): 56 data bytes
!!!!!
--- 2.2.2.2 ping statistics ---
5 packets transmitted, 5 packets received, 0% packet loss
round-trip min/avg/max/stddev = 1.421/1.980/2.970/0.538 ms

root@vMX1> ping 3.3.3.3 rapid
PING 3.3.3.3 (3.3.3.3): 56 data bytes
!!!!!
--- 3.3.3.3 ping statistics ---
5 packets transmitted, 5 packets received, 0% packet loss
round-trip min/avg/max/stddev = 2.561/3.059/3.594/0.439 ms
```

