---
layout: default
title: NTP
nav_order: 25.5
parent: CCNA
---

# Network Time Protocol
{: .no_toc }

Giao thức đồng bộ thời gian mạng
{: .fs-6 .fw-300 }

---

## Network Time Protocol (NTP)
<br>
**NTP (Network Time Protocol)** là giao thức lớp ứng dụng được sử dụng để đồng bộ hóa thời gian. Mục tiêu của NTP là đảm bảo rằng tất cả các thiết bị trên mạng đều đồng nhất về thời gian, thuận lợi cho việc chẩn đoán thời điểm lỗi trên mạng. NTP sử dụng kiến ​​trúc server-client.

	R1 10.0.12.1 (e0/0)-----(e0/0) 10.0.12.2 R2

## NTP Server
<br>
* __R1__

```
R1#clock set 00:00:00 24 aug 2024
R1#conf t
R1(config)#ntp master 1
```

```
R1#sh clock
0:0:7.835 UTC Sat Aug 24 2024
```

* __R2__

```
R2#sh clock
*0:5:15.308 UTC Mon Mar 1 1993
```

```
R2#conf t
R2(config)#ntp server 10.0.12.1
```

```
R2#sh ntp status
Clock is synchronized, stratum 16, reference is 10.0.12.1
nominal freq is 250.0000 Hz, actual freq is 249.9990 Hz, precision is 2**24
reference time is 25780725.0000035A (0:0:37.858 UTC Thu Feb 17 2056)
clock offset is 1.00 msec, root delay is 0.00  msec
root dispersion is 10.33 msec, peer dispersion is 0.12 msec.
loopfilter state is 'CTRL' (Normal Controlled Loop), drift is - 0.000001193 s/s system poll interval is 4, last update was 16 sec ago.
R2#sh ntp associations 

address         ref clock       st   when     poll    reach  delay          offset            disp
*~10.0.12.1     127.127.1.1     1    5        16      37     0.00           1.00              0.12
 * sys.peer, # selected, + candidate, - outlyer, x falseticker, ~ configured
R2#sh clock
0:5:5.764 UTC Sat Aug 24 2024
```

## NTP Peer
<br>
Trong trường hợp máy khách NTP không đồng bộ thời gian với máy chủ NTP, 2 thiết bị ngang hàng cục bộ và khác nhau nguồn đồng bộ NTP có thể đồng bộ lẫn nhau.

```
ntp peer <ip-address>
```