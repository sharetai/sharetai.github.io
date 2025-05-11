---
layout: default
title: BGP
nav_order: 40
parent: CCNP
---

# Border Gateway Protocol
{: .no_toc }

Giao thức cổng đường biên
{: .fs-6 .fw-300 }

---

## TABLE OF CONTENTS
{: .no_toc .text-delta }

1. TOC
{:toc}

---

## [\<Cheat sheet\>](/docs/CCNP/img/BGP-1.png)
<br>

## Tổng quan
<br>
___BGP___ hiện tại là ___BGP-4___ định nghĩa [RFC 4271](http://tools.ietf.org/html/rfc4271) năm 2006. <br>
BGP là giao thức định tuyến ___path vector___ và là giao thức ___EGP___ duy nhất hiện tại. <br>
BGP là giao thức định tuyến ___classless___ (có gửi kèm subnet mask), hỗ trợ VLSM (subnets) và CIDR (summary route). <br>
BGP là giao thức định tuyến ___PBR___ (Policy-based routing) xử lý số lượng routes lớn _(100k routes yêu cầu 70MB RAM, hiện tại đã gần 1tr routes)_ và BGP tập trung vào sự ổn định. <br>

<h3>Autonomous System (AS)</h3>
___Hệ thống tự trị AS___ là tập hợp các router của 1 tổ chức. ___Số ASN là đại diện AS___, do tổ chức ___Internet Assigned Numbers Authority (IANA)___ cấp phát và quản lý. <br>
ASN ban đầu là ___16 bit___, có ___65.535 ASN___, đã cạn kiệt. RFC 4893 đã mở rộng ASN 32 bit, cho phép 4.294.967.295 ASN. <br>
ASN private cho phép sử dụng cục bộ bên trong tổ chức, không được công khai trên internet: <br>
\- Private 16-bit ASN Range: 64,512–65,535 <br>
\- Private 32-bit ASN Range: 4,200,000,000–4,294,967,294 <br>

<h3>Mục đích</h3>
Mạng toàn cầu được chia thành các AS khác nhau để dễ quản lý. BGP được thiết kế để: <br>
\- Lựa chọn các optimal routes <br>
\- Ngăn chặn routing loops <br>
\- Truyền thông tin định tuyến hiệu quả <br>
\- Duy trì một số lượng lớn các routes <br>

<h3>Lợi ích</h3>
BGP đảm bảo an toàn mạng, linh hoạt, ổn định, tin cậy và hiệu quả: <br>
\- BGP có xác thực và sử dụng _Generalized TTL Security Mechanism (GTSM)_ cho bảo mật mạng. <br>
\- BGP cung cấp các chính sách định tuyến để cho phép lựa chọn tuyến đường linh hoạt. <br>
\- BGP cung cấp _Route Summarization_ và _Route Dampening_ để ngăn chặn route _flapping_ và cải thiện sự ổn định của mạng. <br>
\- BGP sử dụng _TCP port 179_ làm giao thức lớp vận chuyển, có hỗ trợ _BFD_, có _BGP Tracking_ và _BGP GR_. <br>

<h3>BGP Messages</h3>
\- _Open message_: dùng thiết lập peer <br>
\- _Update message_: dùng trao đổi routes <br>
\- _Notification message_: dùng kết thúc peer <br>
\- _Keepalive message_: dùng duy trì peer <br>
\- _Route-refresh message_: dùng gửi lại routes nếu chính sách định tuyến có thay đổi <br>

<h3>BGP State Machine</h3>
![alt text](/docs/CCNP/img/BGP-State-Machine.png) <br>

<h3>Attributes</h3>
1 route BGP có thể xem là 1 thực thể bao gồm các thuộc tính:

___1. Well-Known Mandatory___ \- Bắt buộc phải hỗ trợ và bắt buộc chuyển tiếp <br>
\- Origin <br>
\- AS Path ___(*) BGP chống loop dựa vào thuộc tính AS Path___ <br>
\- Next Hop <br>

___2. Well-Known Discretionary___ \- Bắt buộc phải hỗ trợ nhưng không bắt buộc chuyển tiếp <br>
\- Local Preference <br>

___3. Optional Transitive___ \- Tuỳ chọn, có hay không hỗ trợ vẫn sẽ chuyển tiếp <br>
\- Community <br>

___4. Optional Non-Transitive___ \- Tuỳ chọn, không hỗ trợ thì không chuyển tiếp <br>
\- MED <br>
\- Weight <br>

<h3>eBGP vs iBGP (external BGP vs internal BGP)</h3>
_(*) Tại sao có eBGP rồi, lại có thêm iBGP? Vì, ta có thể redistribute routes vào IGP (EIGRP, OSPF), tuy nhiên số lượng routes rất lớn, hạn chế của IGP ko đáp ứng được. iBGP cho phép tuỳ chọn đường đi tối ưu dựa vào các thuộc tính (đường mà BGP chọn là tối ưu có thể dài hơn và IGP lại xem là chưa tối ưu)_ <br>
- ___eBGP là peer khác AS___ trong câu lệnh `neighbor <ip> remote-as <asn>`, ngược lại ___iBGP là peer cùng AS___. <br>
- ___eBGP___ có AD là ___20___ và ___iBGP___ là ___200___. Để ưu tiên hạ tầng của bên khác hay vì là của mình. <br>
- ___eBGP___ có TTL là ___1___ và ___iBGP___ là ___255___. iBGP cho phép peer xuyên qua nhiều hop, eBGP thì không. <br>
- ___eBGP___ chống loop bằng thuộc tính ___AS Path___ _(eBGP không nhận routes nếu AS Path chứa ASN của chính nó)_ và ___iBGP___ chống loop bằng luật ___Split Horizon___ _(routes nhận từ iBGP sẽ không quảng bá cho iBGP khác)_ <br>

<br>

## Cấu hình eBGP neighbor, iBGP neighbor, quảng bá bgp, Next-Hop-Self, Route Reflector, Peer Group
<br>

![alt text](/docs/CCNP/img/bgp-ebgp-ibgp-nhs-rr.png)

__<u>Init</u>__

* __R1__
```
enable
conf t
no ip domain-lookup
host R1
int lo1
ip addr 1.1.1.1 255.255.255.255
int lo10
ip addr 10.10.10.10 255.255.255.255
int e0/0
ip addr 117.0.12.1 255.255.255.0
no shut
end
```

* __R2__
```
enable
conf t
no ip domain-lookup
host R2
int lo2
ip addr 2.2.2.2 255.255.255.255
ip ospf 1 area 0
ip ospf network point-to-point
int e0/0
ip addr 10.0.23.2 255.255.255.0
no shut
ip ospf 1 area 0
ip ospf network point-to-point
int e0/1
ip addr 117.0.12.2 255.255.255.0
no shut
router ospf 1
end
```

* __R3__
```
enable
conf t
no ip domain-lookup
host R3
int lo3
ip addr 3.3.3.3 255.255.255.255
ip ospf 1 area 0
ip ospf network point-to-point
int e0/0
ip addr 10.0.34.3 255.255.255.0
no shut
ip ospf 1 area 0
ip ospf network point-to-point
int e0/1
ip addr 10.0.23.3 255.255.255.0
no shut
ip ospf 1 area 0
ip ospf network point-to-point
end
```

* __R4__
```
enable
conf t
no ip domain-lookup
host R4
int lo4
ip addr 4.4.4.4 255.255.255.255
ip ospf 1 area 0
ip ospf network point-to-point
int e0/0
ip addr 204.0.45.4 255.255.255.0
no shut
int e0/1
ip addr 10.0.34.4 255.255.255.0
no shut
ip ospf 1 area 0
ip ospf network point-to-point
ip route 5.5.5.5 255.255.255.255 204.0.45.5
end
```

* __R5__
```
enable
conf t
no ip domain-lookup
host R5
int lo5
ip addr 5.5.5.5 255.255.255.255
int lo50
ip addr 50.50.50.50 255.255.255.255
int e0/1
ip addr 204.0.45.5 255.255.255.0
no shut
ip route 4.4.4.4 255.255.255.255 204.0.45.4
end
```

__<u>eBGP</u>__

* __R1 (eBGP dùng ip đấu nối)__
```
enable
conf t
router bgp 1
neighbor 117.0.12.2 remote-as 234
end
```

* __R2 (eBGP dùng ip đấu nối)__
```
enable
conf t
router bgp 234
neighbor 117.0.12.1 remote-as 1
end
```

* __R4 (eBGP dùng loopback)__
```
enable
conf t
router bgp 234
neighbor 5.5.5.5 remote-as 5
neighbor 5.5.5.5 update-source lo4
neighbor 5.5.5.5 ebgp-multihop 2
end
```

* __R5 (eBGP dùng loopback)__
```
enable
conf t
router bgp 5
neighbor 4.4.4.4 remote-as 234
neighbor 4.4.4.4 update-source lo5
neighbor 4.4.4.4 ebgp-multihop 2
end
```

__Verify__

```conf
R1#sh ip bgp summary
BGP router identifier 10.10.10.10, local AS number 1
BGP table version is 1, main routing table version 1

Neighbor        V           AS MsgRcvd MsgSent   TblVer  InQ OutQ Up/Down  State/PfxRcd
117.0.12.2      4          234      17      17        1    0    0 00:13:29        0
R1#

R2#sh bgp summary
BGP router identifier 2.2.2.2, local AS number 234
BGP table version is 1, main routing table version 1

Neighbor        V           AS MsgRcvd MsgSent   TblVer  InQ OutQ Up/Down  State/PfxRcd
117.0.12.1      4            1      19      19        1    0    0 00:14:35        0
R2#

R5#sh bgp ipv4 unicast summary
BGP router identifier 50.50.50.50, local AS number 5
BGP table version is 1, main routing table version 1

Neighbor        V           AS MsgRcvd MsgSent   TblVer  InQ OutQ Up/Down  State/PfxRcd
4.4.4.4         4          234       5       5        1    0    0 00:01:32        0
R5#
```

__<u>iBGP full-mesh</u>__

* __R2__
```
enable
conf t
router bgp 234
neighbor 3.3.3.3 remote-as 234
neighbor 3.3.3.3 update-source lo2
neighbor 4.4.4.4 remote-as 234
neighbor 4.4.4.4 update-source lo2
end
```

* __R3__
```
enable
conf t
router bgp 234
neighbor 2.2.2.2 remote-as 234
neighbor 2.2.2.2 update-source lo3
neighbor 4.4.4.4 remote-as 234
neighbor 4.4.4.4 update-source lo3
end
```

* __R4__
```
enable
conf t
router bgp 234
neighbor 2.2.2.2 remote-as 234
neighbor 2.2.2.2 update-source lo4
neighbor 3.3.3.3 remote-as 234
neighbor 3.3.3.3 update-source lo4
end
```

__Verify__

```conf
R2#sh bgp sum
BGP router identifier 2.2.2.2, local AS number 234
BGP table version is 1, main routing table version 1

Neighbor        V           AS MsgRcvd MsgSent   TblVer  InQ OutQ Up/Down  State/PfxRcd
3.3.3.3         4          234       5       7        1    0    0 00:02:51        0
4.4.4.4         4          234       7       4        1    0    0 00:02:46        0
117.0.12.1      4            1      32      32        1    0    0 00:27:02        0
R2#
```

__<u>Quảng bá BGP</u>__

* __R1 (quảng bá 1.1.1.1 và 10.10.10.10 vào BGP)__
```
enable
conf t
router bgp 1
network 1.1.1.1 mask 255.255.255.255
network 10.10.10.10 mask 255.255.255.255
end
```

* __R5 (quảng bá 5.5.5.5 và 50.50.50.50 vào BGP)__
```
enable
conf t
router bgp 5
network 5.5.5.5 mask 255.255.255.255
network 50.50.50.50 mask 255.255.255.255
end
```

* __R2 (next-hop-self)__
```
enable
conf t
router bgp 234
neighbor 3.3.3.3 next-hop-self
neighbor 4.4.4.4 next-hop-self
end
clear ip bgp * soft out
```

* __R4 (next-hop-self)__
```
enable
conf t
router bgp 234
neighbor 2.2.2.2 next-hop-self
neighbor 3.3.3.3 next-hop-self
end
clear ip bgp * soft out
```

__Verify__

```conf
R1#sh bgp
BGP table version is 5, local router ID is 10.10.10.10
Status codes: s suppressed, d damped, h history, * valid, > best, i - internal,
              r RIB-failure, S Stale, m multipath, b backup-path, f RT-Filter,
              x best-external, a additional-path, c RIB-compressed,
              t secondary path,
Origin codes: i - IGP, e - EGP, ? - incomplete
RPKI validation codes: V valid, I invalid, N Not found

     Network          Next Hop            Metric LocPrf Weight Path
 *>   1.1.1.1/32       0.0.0.0                  0         32768 i
 *>   5.5.5.5/32       117.0.12.2                             0 234 5 i
 *>   10.10.10.10/32   0.0.0.0                  0         32768 i
 *>   50.50.50.50/32   117.0.12.2                             0 234 5 i
R1#

R2#sh bgp
BGP table version is 5, local router ID is 2.2.2.2
Status codes: s suppressed, d damped, h history, * valid, > best, i - internal,
              r RIB-failure, S Stale, m multipath, b backup-path, f RT-Filter,
              x best-external, a additional-path, c RIB-compressed,
              t secondary path,
Origin codes: i - IGP, e - EGP, ? - incomplete
RPKI validation codes: V valid, I invalid, N Not found

     Network          Next Hop            Metric LocPrf Weight Path
 *>   1.1.1.1/32       117.0.12.1               0             0 1 i
 *>i  5.5.5.5/32       4.4.4.4                  0    100      0 5 i
 *>   10.10.10.10/32   117.0.12.1               0             0 1 i
 *>i  50.50.50.50/32   4.4.4.4                  0    100      0 5 i
R2#

R3#sh bgp
BGP table version is 5, local router ID is 3.3.3.3
Status codes: s suppressed, d damped, h history, * valid, > best, i - internal,
              r RIB-failure, S Stale, m multipath, b backup-path, f RT-Filter,
              x best-external, a additional-path, c RIB-compressed,
              t secondary path,
Origin codes: i - IGP, e - EGP, ? - incomplete
RPKI validation codes: V valid, I invalid, N Not found

     Network          Next Hop            Metric LocPrf Weight Path
 *>i  1.1.1.1/32       2.2.2.2                  0    100      0 1 i
 *>i  5.5.5.5/32       4.4.4.4                  0    100      0 5 i
 *>i  10.10.10.10/32   2.2.2.2                  0    100      0 1 i
 *>i  50.50.50.50/32   4.4.4.4                  0    100      0 5 i
R3#

R4#sh bgp
BGP table version is 5, local router ID is 4.4.4.4
Status codes: s suppressed, d damped, h history, * valid, > best, i - internal,
              r RIB-failure, S Stale, m multipath, b backup-path, f RT-Filter,
              x best-external, a additional-path, c RIB-compressed,
              t secondary path,
Origin codes: i - IGP, e - EGP, ? - incomplete
RPKI validation codes: V valid, I invalid, N Not found

     Network          Next Hop            Metric LocPrf Weight Path
 *>i  1.1.1.1/32       2.2.2.2                  0    100      0 1 i
 r>   5.5.5.5/32       5.5.5.5                  0             0 5 i
 *>i  10.10.10.10/32   2.2.2.2                  0    100      0 1 i
 *>   50.50.50.50/32   5.5.5.5                  0             0 5 i
R4#sh ip bgp rib-failure
  Network            Next Hop                      RIB-failure   RIB-NH Matches
5.5.5.5/32         5.5.5.5             Higher admin distance              n/a
R4#

R5#sh bgp
BGP table version is 5, local router ID is 50.50.50.50
Status codes: s suppressed, d damped, h history, * valid, > best, i - internal,
              r RIB-failure, S Stale, m multipath, b backup-path, f RT-Filter,
              x best-external, a additional-path, c RIB-compressed,
              t secondary path,
Origin codes: i - IGP, e - EGP, ? - incomplete
RPKI validation codes: V valid, I invalid, N Not found

     Network          Next Hop            Metric LocPrf Weight Path
 *>   1.1.1.1/32       4.4.4.4                                0 234 1 i
 *>   5.5.5.5/32       0.0.0.0                  0         32768 i
 *>   10.10.10.10/32   4.4.4.4                                0 234 1 i
 *>   50.50.50.50/32   0.0.0.0                  0         32768 i
R5#

R1#ping 50.50.50.50 source 10.10.10.10
Type escape sequence to abort.
Sending 5, 100-byte ICMP Echos to 50.50.50.50, timeout is 2 seconds:
Packet sent with a source address of 10.10.10.10
!!!!!
Success rate is 100 percent (5/5), round-trip min/avg/max = 1/1/1 ms
R1#
```

__<u>Route Reflector</u>__

* __R3 (cấu hình R3 làm route reflector)__
```
enable
conf t
router bgp 234
no neighbor 2.2.2.2
no neighbor 4.4.4.4
neighbor 2.2.2.2 remote-as 234
neighbor 2.2.2.2 route-reflector-client
neighbor 4.4.4.4 remote-as 234
neighbor 4.4.4.4 route-reflector-client
end
```

* __R2 (bỏ peer R4)__
```
enable
conf t
router bgp 234
no neighbor 4.4.4.4
end
```

* __R4 (bỏ peer R2)__
```
enable
conf t
router bgp 234
no neighbor 2.2.2.2
end
```

__Verify__

```conf
R2#sh bgp sum
BGP router identifier 2.2.2.2, local AS number 234
BGP table version is 5, main routing table version 5
2 network entries using 288 bytes of memory
2 path entries using 168 bytes of memory
2/2 BGP path/bestpath attribute entries using 320 bytes of memory
1 BGP rrinfo entries using 24 bytes of memory
2 BGP AS-PATH entries using 48 bytes of memory
0 BGP route-map cache entries using 0 bytes of memory
0 BGP filter-list cache entries using 0 bytes of memory
BGP using 848 total bytes of memory
BGP activity 3/1 prefixes, 3/1 paths, scan interval 60 secs

Neighbor        V           AS MsgRcvd MsgSent   TblVer  InQ OutQ Up/Down  State/PfxRcd
3.3.3.3         4          234       8       5        5    0    0 00:00:15        1
117.0.12.1      4            1      56      60        5    0    0 00:48:19        1
R2#

R3#sh bgp sum
BGP router identifier 3.3.3.3, local AS number 234
BGP table version is 9, main routing table version 9
2 network entries using 288 bytes of memory
2 path entries using 168 bytes of memory
2/2 BGP path/bestpath attribute entries using 320 bytes of memory
2 BGP AS-PATH entries using 48 bytes of memory
0 BGP route-map cache entries using 0 bytes of memory
0 BGP filter-list cache entries using 0 bytes of memory
BGP using 824 total bytes of memory
BGP activity 4/2 prefixes, 5/3 paths, scan interval 60 secs

Neighbor        V           AS MsgRcvd MsgSent   TblVer  InQ OutQ Up/Down  State/PfxRcd
2.2.2.2         4          234       5       8        9    0    0 00:00:00        1
4.4.4.4         4          234       5       5        9    0    0 00:00:08        1
R3#

R4#sh bgp sum
BGP router identifier 4.4.4.4, local AS number 234
BGP table version is 5, main routing table version 5
2 network entries using 288 bytes of memory
2 path entries using 168 bytes of memory
2/2 BGP path/bestpath attribute entries using 320 bytes of memory
1 BGP rrinfo entries using 24 bytes of memory
2 BGP AS-PATH entries using 48 bytes of memory
0 BGP route-map cache entries using 0 bytes of memory
0 BGP filter-list cache entries using 0 bytes of memory
BGP using 848 total bytes of memory
BGP activity 3/1 prefixes, 3/1 paths, scan interval 60 secs

Neighbor        V           AS MsgRcvd MsgSent   TblVer  InQ OutQ Up/Down  State/PfxRcd
3.3.3.3         4          234       5       5        5    0    0 00:00:32        1
5.5.5.5         4            5      44      47        5    0    0 00:36:05        1
R4#

R1#sh bgp
BGP table version is 9, local router ID is 10.10.10.10
Status codes: s suppressed, d damped, h history, * valid, > best, i - internal,
              r RIB-failure, S Stale, m multipath, b backup-path, f RT-Filter,
              x best-external, a additional-path, c RIB-compressed,
              t secondary path,
Origin codes: i - IGP, e - EGP, ? - incomplete
RPKI validation codes: V valid, I invalid, N Not found

     Network          Next Hop            Metric LocPrf Weight Path
 *>   1.1.1.1/32       0.0.0.0                  0         32768 i
 *>   5.5.5.5/32       117.0.12.2                             0 234 5 i
 *>   10.10.10.10/32   0.0.0.0                  0         32768 i
 *>   50.50.50.50/32   117.0.12.2                             0 234 5 i
R1#

R5#sh bgp
BGP table version is 9, local router ID is 50.50.50.50
Status codes: s suppressed, d damped, h history, * valid, > best, i - internal,
              r RIB-failure, S Stale, m multipath, b backup-path, f RT-Filter,
              x best-external, a additional-path, c RIB-compressed,
              t secondary path,
Origin codes: i - IGP, e - EGP, ? - incomplete
RPKI validation codes: V valid, I invalid, N Not found

     Network          Next Hop            Metric LocPrf Weight Path
 *>   1.1.1.1/32       4.4.4.4                                0 234 1 i
 *>   5.5.5.5/32       0.0.0.0                  0         32768 i
 *>   10.10.10.10/32   4.4.4.4                                0 234 1 i
 *>   50.50.50.50/32   0.0.0.0                  0         32768 i
R5#

R1#ping 50.50.50.50 source 10.10.10.10
Type escape sequence to abort.
Sending 5, 100-byte ICMP Echos to 50.50.50.50, timeout is 2 seconds:
Packet sent with a source address of 10.10.10.10
!!!!!
Success rate is 100 percent (5/5), round-trip min/avg/max = 1/1/3 ms
R1#
```

__<u>Peer Group</u>__

* __R3__
```
enable
conf t
router bgp 234
no neighbor 2.2.2.2
no neighbor 4.4.4.4
neighbor rr-client peer-group
neighbor rr-client remote-as 234
neighbor rr-client route-reflector-client
neighbor 2.2.2.2 peer-group rr-client
neighbor 4.4.4.4 peer-group rr-client
end
```

__Verify__

```conf
R3#sh bgp sum
BGP router identifier 3.3.3.3, local AS number 234
BGP table version is 9, main routing table version 9
2 network entries using 288 bytes of memory
2 path entries using 168 bytes of memory
2/2 BGP path/bestpath attribute entries using 320 bytes of memory
2 BGP AS-PATH entries using 48 bytes of memory
0 BGP route-map cache entries using 0 bytes of memory
0 BGP filter-list cache entries using 0 bytes of memory
BGP using 824 total bytes of memory
BGP activity 4/2 prefixes, 5/3 paths, scan interval 60 secs

Neighbor        V           AS MsgRcvd MsgSent   TblVer  InQ OutQ Up/Down  State/PfxRcd
2.2.2.2         4          234       5       8        9    0    0 00:00:00        1
4.4.4.4         4          234       5       5        9    0    0 00:00:08        1
R3#
```

<br>

## Cấu hình lựa chọn đường đi với Weight - Local Preference
<br>

![alt text](/docs/CCNP/img/bgp-wei-lp-aspath-orin-med.png)

__<u>Init</u>__

* __R1__
```
enable
conf t
no ip domain-lookup
host R1
int lo0
ip addr 1.1.1.1 255.255.255.255
ip ospf 1 area 0
ip ospf network point-to-point
int e0/2
ip addr 10.0.12.1 255.255.255.0
no shut
ip ospf 1 area 0
ip ospf network point-to-point
int e0/3
ip addr 10.0.13.1 255.255.255.0
no shut
ip ospf 1 area 0
ip ospf network point-to-point
router ospf 1
router-id 1.1.1.1
end
```

* __R2__
```
enable
conf t
no ip domain-lookup
host R2
int lo0
ip addr 2.2.2.2 255.255.255.255
ip ospf 1 area 0
ip ospf network point-to-point
int e0/2
ip addr 10.0.12.2 255.255.255.0
no shut
ip ospf 1 area 0
ip ospf network point-to-point
int e0/0
ip addr 117.0.24.2 255.255.255.0
no shut
router ospf 1
router-id 2.2.2.2
end
```

* __R3__
```
enable
conf t
no ip domain-lookup
host R3
int lo0
ip addr 3.3.3.3 255.255.255.255
ip ospf 1 area 0
ip ospf network point-to-point
int e0/1
ip addr 204.0.34.3 255.255.255.0
no shut
int e0/3
ip addr 10.0.13.3 255.255.255.0
no shut
ip ospf 1 area 0
ip ospf network point-to-point
router ospf 1
router-id 3.3.3.3
end
```

* __R4__
```
enable
conf t
no ip domain-lookup
host R4
int lo4
ip addr 4.4.4.4 255.255.255.255
int lo40
ip addr 40.40.40.40 255.255.255.255
int e0/0
ip addr 117.0.24.4 255.255.255.0
no shut
int e0/1
ip addr 204.0.34.4 255.255.255.0
no shut
end
```

__<u>iBGP</u>__

* __R1__
```
enable
conf t
router bgp 123
neighbor 2.2.2.2 remote-as 123
neighbor 2.2.2.2 update-source lo0
neighbor 3.3.3.3 remote-as 123
neighbor 3.3.3.3 update-source lo0
end
```

* __R2__
```
enable
conf t
router bgp 123
neighbor 1.1.1.1 remote-as 123
neighbor 1.1.1.1 update-source lo0
neighbor 1.1.1.1 next-hop-self
neighbor 3.3.3.3 remote-as 123
neighbor 3.3.3.3 update-source lo0
neighbor 3.3.3.3 next-hop-self
end
```

* __R3__
```
enable
conf t
router bgp 123
neighbor 1.1.1.1 remote-as 123
neighbor 1.1.1.1 update-source lo0
neighbor 1.1.1.1 next-hop-self
neighbor 2.2.2.2 remote-as 123
neighbor 2.2.2.2 update-source lo0
neighbor 2.2.2.2 next-hop-self
end
```

__<u>eBGP</u>__

* __R2__
```
enable
conf t
router bgp 123
neighbor 117.0.24.4 remote-as 4
end
```

* __R3__
```
enable
conf t
router bgp 123
neighbor 204.0.34.4 remote-as 4
end
```

* __R4__
```
enable
conf t
router bgp 4
neighbor 117.0.24.2 remote-as 123
neighbor 204.0.34.3 remote-as 123
network 4.4.4.4 mask 255.255.255.255
network 40.40.40.40 mask 255.255.255.255
end
```

__Verify__

```conf
R1#sh bgp
BGP table version is 3, local router ID is 1.1.1.1
Status codes: s suppressed, d damped, h history, * valid, > best, i - internal,
              r RIB-failure, S Stale, m multipath, b backup-path, f RT-Filter,
              x best-external, a additional-path, c RIB-compressed,
              t secondary path,
Origin codes: i - IGP, e - EGP, ? - incomplete
RPKI validation codes: V valid, I invalid, N Not found

     Network          Next Hop            Metric LocPrf Weight Path
 * i  4.4.4.4/32       3.3.3.3                  0    100      0 4 i
 *>i                   2.2.2.2                  0    100      0 4 i
 * i  40.40.40.40/32   3.3.3.3                  0    100      0 4 i
 *>i                   2.2.2.2                  0    100      0 4 i
R1#
```

__<u>Local Preference</u>__

* __R1__
```
enable
conf t
route-map R2-in permit 10
set local-preference 200
route-map R2-in permit 20
route-map R3-in permit 10
set local-preference 300
route-map R3-in permit 20
router bgp 123
neighbor 2.2.2.2 route-map R2-in in
neighbor 3.3.3.3 route-map R3-in in
end
clear ip bgp * soft in
```

__Verify__

```conf
R1#sh bgp
BGP table version is 7, local router ID is 1.1.1.1
Status codes: s suppressed, d damped, h history, * valid, > best, i - internal,
              r RIB-failure, S Stale, m multipath, b backup-path, f RT-Filter,
              x best-external, a additional-path, c RIB-compressed,
              t secondary path,
Origin codes: i - IGP, e - EGP, ? - incomplete
RPKI validation codes: V valid, I invalid, N Not found

     Network          Next Hop            Metric LocPrf Weight Path
 *>i  4.4.4.4/32       3.3.3.3                  0    300      0 4 i
 * i                   2.2.2.2                  0    200      0 4 i
 *>i  40.40.40.40/32   3.3.3.3                  0    300      0 4 i
 * i                   2.2.2.2                  0    200      0 4 i
R1#
```

__<u>Weight</u>__

* __R1__
```
enable
conf t
access-list 4 permit 4.4.4.4
route-map R2-in permit 5
match ip address 4
set weight 2
end
clear ip bgp * in
```

__Verify__

```conf
R1#sh bgp
BGP table version is 3, local router ID is 1.1.1.1
Status codes: s suppressed, d damped, h history, * valid, > best, i - internal,
              r RIB-failure, S Stale, m multipath, b backup-path, f RT-Filter,
              x best-external, a additional-path, c RIB-compressed,
              t secondary path,
Origin codes: i - IGP, e - EGP, ? - incomplete
RPKI validation codes: V valid, I invalid, N Not found

     Network          Next Hop            Metric LocPrf Weight Path
 * i  4.4.4.4/32       3.3.3.3                  0    300      0 4 i
 *>i                   2.2.2.2                  0    100      2 4 i
 *>i  40.40.40.40/32   3.3.3.3                  0    300      0 4 i
 * i                   2.2.2.2                  0    200      0 4 i
R1#
```

<br>

## Cấu hình lựa chọn đường đi với ASpath Prepend - Origin Code - MED
<br>

![alt text](/docs/CCNP/img/bgp-wei-lp-aspath-orin-med.png)

_(Sử dụng lại lab trước)_

__<u>Init</u>__

* __R1__
```
enable
conf t
int lo10
ip addr 10.10.10.10 255.255.255.255
ip ospf 1 area 0
ip ospf network point-to-point
router bgp 123
network 1.1.1.1 mask 255.255.255.255
network 10.10.10.10 mask 255.255.255.255
end
```

__Verify__

```conf
R4#sh bgp | e 0.0.0.0
BGP table version is 5, local router ID is 40.40.40.40
Status codes: s suppressed, d damped, h history, * valid, > best, i - internal,
              r RIB-failure, S Stale, m multipath, b backup-path, f RT-Filter,
              x best-external, a additional-path, c RIB-compressed,
              t secondary path,
Origin codes: i - IGP, e - EGP, ? - incomplete
RPKI validation codes: V valid, I invalid, N Not found

     Network          Next Hop            Metric LocPrf Weight Path
 *    1.1.1.1/32       204.0.34.3                             0 123 i
 *>                    117.0.24.2                             0 123 i
 *    10.10.10.10/32   204.0.34.3                             0 123 i
 *>                    117.0.24.2                             0 123 i

R4#
```

__<u>ASpath Prepend</u>__

* __R2__
```
enable
conf t
route-map R4-out permit 10
set as-path prepend 123 123
route-map R4-out permit 20
router bgp 123
neighbor 117.0.24.4 route-map R4-out out
end
clear ip bgp * soft out
```

__Verify__

```conf
R4#sh bgp | e 0.0.0.0
BGP table version is 7, local router ID is 40.40.40.40
Status codes: s suppressed, d damped, h history, * valid, > best, i - internal,
              r RIB-failure, S Stale, m multipath, b backup-path, f RT-Filter,
              x best-external, a additional-path, c RIB-compressed,
              t secondary path,
Origin codes: i - IGP, e - EGP, ? - incomplete
RPKI validation codes: V valid, I invalid, N Not found

     Network          Next Hop            Metric LocPrf Weight Path
 *>   1.1.1.1/32       204.0.34.3                             0 123 i
 *                     117.0.24.2                             0 123 123 123 i
 *>   10.10.10.10/32   204.0.34.3                             0 123 i
 *                     117.0.24.2                             0 123 123 123 i

R4#
```

__<u>Origin Code</u>__

* __R2__
```
enable
conf t
access-list 1 permit 1.1.1.1
route-map R4-out permit 10
no set as-path prepend 123 123
match ip address 1
set origin incomplete
end
clear ip bgp * soft out
```

__Verify__

```conf
R4#sh bgp | e 0.0.0.0
BGP table version is 3, local router ID is 40.40.40.40
Status codes: s suppressed, d damped, h history, * valid, > best, i - internal,
              r RIB-failure, S Stale, m multipath, b backup-path, f RT-Filter,
              x best-external, a additional-path, c RIB-compressed,
              t secondary path,
Origin codes: i - IGP, e - EGP, ? - incomplete
RPKI validation codes: V valid, I invalid, N Not found

     Network          Next Hop            Metric LocPrf Weight Path
 *    1.1.1.1/32       117.0.24.2                             0 123 ?
 *>                    204.0.34.3                             0 123 i
 *>   10.10.10.10/32   117.0.24.2                             0 123 i
 *                     204.0.34.3                             0 123 i

R4#
```

__<u>MED (metric)</u>__

* __R2__
```
enable
conf t
access-list 10 permit 10.10.10.10
route-map R4-out permit 15
match ip address 10
set metric 10
end
clear ip bgp * soft out
```

__Verify__

```conf
R4#sh bgp | e 0.0.0.0
BGP table version is 6, local router ID is 40.40.40.40
Status codes: s suppressed, d damped, h history, * valid, > best, i - internal,
              r RIB-failure, S Stale, m multipath, b backup-path, f RT-Filter,
              x best-external, a additional-path, c RIB-compressed,
              t secondary path,
Origin codes: i - IGP, e - EGP, ? - incomplete
RPKI validation codes: V valid, I invalid, N Not found

     Network          Next Hop            Metric LocPrf Weight Path
 *    1.1.1.1/32       117.0.24.2                             0 123 ?
 *>                    204.0.34.3                             0 123 i
 *    10.10.10.10/32   117.0.24.2              10             0 123 i
 *>                    204.0.34.3                             0 123 i

R4#
```

<br>

## BGP Regular Expression (Regex)
<br>
`show ip bgp regexp <regex>`

```
ip as-path access-list <as-path acl number> permit <regex>
route-map <route-map name> permit 10
match as-path <as-path acl number>
route-map abc deny 100
```

<br>

## Cấu hình BGP Confederation - Allowas in - AS override - Community
<br>

![alt text](/docs/CCNP/img/bgp-confederation-allowasin-asoveride-community.png)

__<u>Init</u>__

* __R1__
```
enable
conf t
no ip domain-lookup
host R1
int e0/0
ip addr 10.0.12.1 255.255.255.0
no shut
end
```

* __R2__
```
enable
conf t
no ip domain-lookup
host R2
int e0/1
ip addr 10.0.12.2 255.255.255.0
no shut
int e0/0
ip addr 10.0.23.2 255.255.255.0
no shut
router ospf 1
net 0.0.0.0 255.255.255.255 area 0
end
```

* __R3__
```
enable
conf t
no ip domain-lookup
host R3
int e0/1
ip addr 10.0.23.3 255.255.255.0
no shut
int e0/0
ip addr 10.0.34.3 255.255.255.0
no shut
router ospf 1
net 0.0.0.0 255.255.255.255 area 0
end
```

* __R4__
```
enable
conf t
no ip domain-lookup
host R4
int e0/1
ip addr 10.0.34.4 255.255.255.0
no shut
int e0/0
ip addr 10.0.45.4 255.255.255.0
no shut
router ospf 1
net 0.0.0.0 255.255.255.255 area 0
end
```

* __R5__
```
enable
conf t
no ip domain-lookup
host R5
int e0/1
ip addr 10.0.45.5 255.255.255.0
no shut
int lo5
ip addr 5.5.5.5 255.255.255.255
int lo50
ip addr 50.50.50.50 255.255.255.255
int lo55
ip addr 55.55.55.55 255.255.255.255
end
```

__<u>BGP Confederation</u>__

* __R1__
```
enable
conf t
router bgp 15
neighbor 10.0.12.2 remote-as 234
end
```

* __R2 (cấu hình bgp confederation)__
```
enable
conf t
router bgp 2
bgp confederation identifier 234
bgp confederation peers 34
neighbor 10.0.12.1 remote-as 15
neighbor 10.0.23.3 remote-as 34
end
```

* __R3 (cấu hình bgp confederation)__
```
enable
conf t
router bgp 34
bgp confederation identifier 234
bgp confederation peers 2
neighbor 10.0.23.2 remote-as 2
neighbor 10.0.34.4 remote-as 34
end
```

* __R4 (cấu hình bgp confederation)__
```
enable
conf t
router bgp 34
bgp confederation identifier 234
neighbor 10.0.45.5 remote-as 15
neighbor 10.0.34.3 remote-as 34
neighbor 10.0.34.3 next-hop-self
end
```

* __R5__
```
enable
conf t
router bgp 15
neighbor 10.0.45.4 remote-as 234
network 5.5.5.5 mask 255.255.255.255
network 50.50.50.50 mask 255.255.255.255
network 55.55.55.55 mask 255.255.255.255
end
```

* __Verify__

```conf
R2#sh bgp
BGP table version is 4, local router ID is 10.0.23.2
Status codes: s suppressed, d damped, h history, * valid, > best, i - internal,
              r RIB-failure, S Stale, m multipath, b backup-path, f RT-Filter,
              x best-external, a additional-path, c RIB-compressed,
              t secondary path,
Origin codes: i - IGP, e - EGP, ? - incomplete
RPKI validation codes: V valid, I invalid, N Not found

     Network          Next Hop            Metric LocPrf Weight Path
 *>i  5.5.5.5/32       10.0.34.4                0    100      0 (4) 15 i
 *>i  50.50.50.50/32   10.0.34.4                0    100      0 (4) 15 i
 *>i  55.55.55.55/32   10.0.34.4                0    100      0 (4) 15 i
R2#
```

__<u>Allowas in</u>__

* __R1__
```
enable
conf t
router bgp 15
neighbor 10.0.12.2 allowas-in
end
```

* __Verify__

```conf
R1#sh bgp
BGP table version is 4, local router ID is 10.0.12.1
Status codes: s suppressed, d damped, h history, * valid, > best, i - internal,
              r RIB-failure, S Stale, m multipath, b backup-path, f RT-Filter,
              x best-external, a additional-path, c RIB-compressed,
              t secondary path,
Origin codes: i - IGP, e - EGP, ? - incomplete
RPKI validation codes: V valid, I invalid, N Not found

     Network          Next Hop            Metric LocPrf Weight Path
 *>   5.5.5.5/32       10.0.12.2                              0 234 15 i
 *>   50.50.50.50/32   10.0.12.2                              0 234 15 i
 *>   55.55.55.55/32   10.0.12.2                              0 234 15 i
R1#
```

__<u>AS override</u>__

* __R1__
```
enable
conf t
router bgp 15
no neighbor 10.0.12.2 allowas-in
end
```

* __R2__
```
enable
conf t
router bgp 2
neighbor 10.0.12.1 as-override
end
```

* __Verify__

```conf
R1#sh bgp
BGP table version is 10, local router ID is 10.0.12.1
Status codes: s suppressed, d damped, h history, * valid, > best, i - internal,
              r RIB-failure, S Stale, m multipath, b backup-path, f RT-Filter,
              x best-external, a additional-path, c RIB-compressed,
              t secondary path,
Origin codes: i - IGP, e - EGP, ? - incomplete
RPKI validation codes: V valid, I invalid, N Not found

     Network          Next Hop            Metric LocPrf Weight Path
 *>   5.5.5.5/32       10.0.12.2                              0 234 234 i
 *>   50.50.50.50/32   10.0.12.2                              0 234 234 i
 *>   55.55.55.55/32   10.0.12.2                              0 234 234 i
R1#
```

__<u>Community</u>__

* __R2__
```
enable
conf t
router bgp 2
neighbor 10.0.12.1 send-community both
end
```

* __R3__
```
enable
conf t
router bgp 34
neighbor 10.0.23.2 send-community both
end
```

* __R4__
```
enable
conf t
router bgp 34
neighbor 10.0.34.3 send-community both
end
```

* __R5__
```
enable
conf t
access-list 5 permit 5.5.5.5
access-list 50 permit 50.50.50.50
access-list 55 permit 55.55.55.55
route-map R4 permit 5
match ip address 5
set community no-export
route-map R4 permit 50
match ip address 50
set community no-advertise
route-map R4 permit 55
match ip address 55
set community local-AS
route-map R4 permit 1000
router bgp 15
neighbor 10.0.45.4 route-map R4 out
neighbor 10.0.45.4 send-community both
end
```

```
no-export <== Nhận route nhưng không quảng bá sang as khác
no-advertise <== Nhận route nhưng không quảng bá
local-AS <== Nhận route và chỉ quảng bá trong cùng as
```

* __Verify__

```conf
R4#sh bgp 5.5.5.5
BGP routing table entry for 5.5.5.5/32, version 7
Paths: (1 available, best #1, table default, not advertised to EBGP peer)
  Advertised to update-groups:
     8
  Refresh Epoch 2
  15
    10.0.45.5 from 10.0.45.5 (55.55.55.55)
      Origin IGP, metric 0, localpref 100, valid, external, best
      Community: no-export
      rx pathid: 0, tx pathid: 0x0
R4#sh bgp 50.50.50.50
BGP routing table entry for 50.50.50.50/32, version 6
Paths: (1 available, best #1, table default, not advertised to any peer)
  Not advertised to any peer
  Refresh Epoch 2
  15
    10.0.45.5 from 10.0.45.5 (55.55.55.55)
      Origin IGP, metric 0, localpref 100, valid, external, best
      Community: no-advertise
      rx pathid: 0, tx pathid: 0x0
R4#sh bgp 55.55.55.55
BGP routing table entry for 55.55.55.55/32, version 5
Paths: (1 available, best #1, table default, not advertised outside local AS)
  Not advertised to any peer
  Refresh Epoch 2
  15
    10.0.45.5 from 10.0.45.5 (55.55.55.55)
      Origin IGP, metric 0, localpref 100, valid, external, best
      Community: local-AS
      rx pathid: 0, tx pathid: 0x0
R4#

R4#sh bgp
BGP table version is 4, local router ID is 10.0.45.4
Status codes: s suppressed, d damped, h history, * valid, > best, i - internal,
              r RIB-failure, S Stale, m multipath, b backup-path, f RT-Filter,
              x best-external, a additional-path, c RIB-compressed,
              t secondary path,
Origin codes: i - IGP, e - EGP, ? - incomplete
RPKI validation codes: V valid, I invalid, N Not found

     Network          Next Hop            Metric LocPrf Weight Path
 *>   5.5.5.5/32       10.0.45.5                0             0 15 i
 *>   50.50.50.50/32   10.0.45.5                0             0 15 i
 *>   55.55.55.55/32   10.0.45.5                0             0 15 i
R4#

R3#sh bgp
BGP table version is 5, local router ID is 10.0.34.3
Status codes: s suppressed, d damped, h history, * valid, > best, i - internal,
              r RIB-failure, S Stale, m multipath, b backup-path, f RT-Filter,
              x best-external, a additional-path, c RIB-compressed,
              t secondary path,
Origin codes: i - IGP, e - EGP, ? - incomplete
RPKI validation codes: V valid, I invalid, N Not found

     Network          Next Hop            Metric LocPrf Weight Path
 *>i  5.5.5.5/32       10.0.34.4                0    100      0 15 i
 *>i  55.55.55.55/32   10.0.34.4                0    100      0 15 i
R3#

R2#sh bgp
BGP table version is 5, local router ID is 10.0.23.2
Status codes: s suppressed, d damped, h history, * valid, > best, i - internal,
              r RIB-failure, S Stale, m multipath, b backup-path, f RT-Filter,
              x best-external, a additional-path, c RIB-compressed,
              t secondary path,
Origin codes: i - IGP, e - EGP, ? - incomplete
RPKI validation codes: V valid, I invalid, N Not found

     Network          Next Hop            Metric LocPrf Weight Path
 *>   5.5.5.5/32       10.0.34.4                0    100      0 (34) 15 i
R2#

R1#sh bgp
R1#
```

<br>

