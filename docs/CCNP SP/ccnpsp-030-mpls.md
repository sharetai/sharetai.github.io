---
layout: default
title: MPLS
nav_order: 30
parent: CCNP SP
---

# Multiprotocol Label Switching
{: .no_toc }

Chuyển mạch nhãn đa giao thức
{: .fs-6 .fw-300 }

---

## TABLE OF CONTENTS
{: .no_toc .text-delta }

1. TOC
{:toc}

---

## Kiến trúc MPLS

MPLS sử dụng **nhãn (Label)** để chuyển tiếp lưu lượng.

Mặt phẳng điều khiển (**control plane**) xây dựng **bảng định tuyến RIB (routing information base)** dựa trên các giao thức như **OSPF**, **EIGRP**, **IS-IS**, **RIP**, hoặc **BGP**.

Mặt phẳng điều khiển (**control plane**) sử dụng **giao thức trao đổi nhãn (label exchange protocol)** để tạo, duy trì và trao đổi nhãn với các thiết bị hỗ trợ MPLS khác.  
Giao thức này ánh xạ nhãn (**binds labels to prefixes**) với các mạng học được từ giao thức định tuyến.  

Các giao thức trao đổi nhãn:
- **LDP (Label Distribution Protocol)**
- **BGP** – dùng bởi **MPLS VPN**
- **RSVP** – dùng bởi **MPLS Traffic Engineering (MPLS TE)**

Control plane cũng xây dựng 2 bảng chuyển tiếp:
- **FIB (Forwarding Information Base)** – dựa trên thông tin từ RIB  
- **LFIB (Label Forwarding Information Base)** – dựa trên giao thức trao đổi nhãn và RIB  

<img src="/docs/CCNP SP/img/mpls forwarding plane.png" style="max-width: 100%; width: 800px" />

**Data plane** (còn gọi là **forwarding plane**) đảm nhận việc chuyển tiếp gói tin dựa trên **địa chỉ đích hoặc nhãn**, dùng thông tin trong **FIB hoặc LFIB** để xác định cổng ra phù hợp.

## Nhãn MPLS

MPLS chèn một **header 32-bit** giữa lớp 2 và lớp 3, gồm:  
- **20-bit Label:** giá trị nhãn dùng để chuyển tiếp (giá trị 0–15 là reserved)  
- **3-bit EXP:** dùng cho phân loại dịch vụ (CoS)  
- **1-bit Bottom-of-Stack:** xác định nhãn cuối cùng trong ngăn xếp (1 = nhãn cuối)  
- **8-bit TTL:** tương tự TTL trong IP header (chống loop L3)

<img src="/docs/CCNP SP/img/mpls label.png" style="max-width: 100%; width: 600px" />

**Hoạt động chèn nhãn tại Edge LSR:**  
1. Thực hiện **routing lookup** để chọn **outgoing interface**.  
2. **Chèn label** giữa header lớp 2 và lớp 3 nếu interface hỗ trợ MPLS và có nhãn next-hop.  
3. Thay đổi Layer 2 process ID (PID) hoặc **EtherType** thành **0x8847** (MPLS unicast). Báo hiệu đây là labeled packet.
4. **Gửi đi** gói tin đã gắn nhãn ra interface.

## Ứng dụnh MPLS

MPLS là công nghệ dùng để truyền tải dịch vụ IP, với nhiều ứng dụng khác nhau:  
- **Unicast IP routing:** ứng dụng phổ biến nhất.  
- **Multicast IP routing:** xử lý riêng vì yêu cầu chuyển tiếp khác.  
- **MPLS TE (Traffic Engineering):** mở rộng của MPLS giúp tối ưu sử dụng liên kết.  
- **Differentiated QoS:** cung cấp chất lượng dịch vụ phân biệt.  
- **MPLS VPN:** dùng nhãn để cho phép các VPN có không gian địa chỉ trùng lặp.  
- **AToM (Any Transport over MPLS):** cho phép truyền tải gói tin lớp 2 qua mạng IP hoặc MPLS.  

<img src="/docs/CCNP SP/img/mpls stack.png" style="max-width: 100%; width: 600px" />

**Cấu trúc nhãn trong MPLS nhiều lớp:**  
- **Outer label:** dùng để chuyển gói MPLS qua mạng, thường là **nhãn TE** trỏ đến điểm cuối tunnel.  
- **Inner label:** dùng để trỏ đến router đích (egress) và để xác định dịch vụ VPN.  
- **Bottom-of-Stack bit = 1:** chỉ ra nhãn cuối cùng trong gói tin.

## Giao thức phân phối nhãn LDP

**LDP (Label Distribution Protocol)** là giao thức tiêu chuẩn dùng để trao đổi nhãn giữa các router liền kề trong mạng MPLS, giữa các thiết bị của nhiều hãng khác nhau.

Trước khi trao đổi nhãn, các router MPLS phải thiết lập quan hệ láng giềng qua hai bước:
- **LDP Discovery:** gửi gói *Hello* để phát hiện neighbor.  
- **LDP Adjacency:** router nhận *Hello* sẽ mở kết nối TCP (port 646) để thiết lập phiên LDP qua unicast TCP.  

LDP gửi gói *Hello* định kỳ mỗi **5 giây** qua UDP multicast địa chỉ **224.0.0.2**, port **646**.
 
<img src="/docs/CCNP SP/img/mpls LDP Discovery.png" style="max-width: 100%; width: 600px" />

Quá trình thương lượng phiên LDP gồm ba bước chính:
1. **Thiết lập kết nối TCP.**  
2. **Trao đổi gói initialization:** chứa thông tin về phương thức phân phối nhãn, thời gian keepalive, và TLV chống lỗi. Nếu hợp lệ, neighbor phản hồi; nếu không, gửi *error notification*.  
3. **Trao đổi keepalive:** gửi định kỳ mỗi **60 giây** để duy trì phiên.

Sau đó, hai router bắt đầu trao đổi nhãn cho các mạng có trong bảng định tuyến.

MPLS sử dụng **liberal label retention mode**, nghĩa là mỗi router (**LSR**) giữ lại tất cả nhãn nhận được từ neighbor, dù neighbor đó không phải là next-hop đến mạng đích.

## Tạo và phân phối nhãn

- Thông tin định tuyến được trao đổi bằng các giao thức định tuyến IP (OSPF, IS-IS, EIGRP, v.v.).
- 1 nhãn cục bộ duy nhất (**local unique label**) được tạo cho mỗi **prefix IP** được tìm thấy trong bảng định tuyến chính và được lưu trong bảng LIB.
- Các nhãn cục bộ được **truyền** đến các router liền kề.
- Mỗi LSR xây dựng các cấu trúc dữ liệu LIB, LFIB và FIB của riêng nó dựa trên các **nhãn đã nhận**.

<img src="/docs/CCNP SP/img/mpls Label Allocation and Distribution 1.png" style="max-width: 100%; width: 600px" />
<img src="/docs/CCNP SP/img/mpls Label Allocation and Distribution 2.png" style="max-width: 100%; width: 600px" />
<img src="/docs/CCNP SP/img/mpls Label Allocation and Distribution 3.png" style="max-width: 100%; width: 600px" />
<img src="/docs/CCNP SP/img/mpls Label Allocation and Distribution 4.png" style="max-width: 100%; width: 600px" />

## Truyền gói tin trên miền MPLS

- Router A **gán nhãn 25** cho một gói tin có đích đến mạng X (Cisco Express Forwarding CEF, chuyển mạch bằng bảng FIB).  
- Router B **swap nhãn 25 với nhãn 34** và chuyển tiếp gói tin đến router C (chuyển mạch nhãn bằng bảng LFIB).  
- Router C **pop nhãn** và chuyển tiếp gói tin đến router D (chuyển mạch nhãn bằng bảng LFIB).  
- Router D thực hiện tra cứu IP trong bảng FIB. Mạng X được kết nối trực tiếp.

<img src="/docs/CCNP SP/img/mpls Packet Propagation Across an MPLS Domain.png" style="max-width: 100%; width: 600px" />

## Quá trình hội tụ MPLS bị lỗi liên kết

- Quá trình hội tụ tổng thể hoàn toàn **phụ thuộc vào sự hội tụ của IGP** được sử dụng trong miền MPLS.  
- Liên kết giữa router B và router C bị **down**.  
- Các mục liên quan đến router C bị xóa khỏi các bảng LIB, LFIB, FIB và RIB.  
- Khi router B xác định rằng router E nên được sử dụng để đến mạng X, **nhãn được học từ router E** có thể được sử dụng để chuyển mạch nhãn cho các gói tin.

<img src="/docs/CCNP SP/img/mpls Link Failure MPLS Convergence Process.png" style="max-width: 100%; width: 600px" />

## MPLS L3VPN

Dịch vụ MPLS L3VPN được sử dụng để đảm bảo tách biệt mặt phẳng dữ liệu giữa các gói tin của các khách hàng khác nhau, ngay cả khi có thể dùng cùng địa chỉ IP.  
Các bộ định tuyến ảo **VRF (Virtual Routing and Forwarding)** được sử dụng trên router của nhà cung cấp dịch vụ để tách biệt thông tin định tuyến của từng khách hàng.

Internet, thoại IP, IPTV hoặc mạng quản trị NMS đều có thể được tách riêng và cung cấp qua các MPLS L3VPN riêng.

<img src="/docs/CCNP SP/img/mpls MPLS L3VPN 1.png" style="max-width: 100%; width: 600px" />
<img src="/docs/CCNP SP/img/mpls MPLS L3VPN 2.png" style="max-width: 100%; width: 600px" />

## MPLS L2VPN

Dịch vụ MPLS L2VPN cho phép nhà cung cấp dịch vụ cung cấp kết nối lớp 2 dạng point-to-point hoặc multipoint giữa các site khách hàng ở xa.  
Loại VPN này thường được dùng để gom lưu lượng Ethernet lớp 2 qua mạng IP hoặc MPLS. 

<img src="/docs/CCNP SP/img/mpls MPLS L2VPN 1.png" style="max-width: 100%; width: 600px" />
<img src="/docs/CCNP SP/img/mpls MPLS L2VPN 2.png" style="max-width: 100%; width: 600px" />

## LDP Advanced

### LDP Session Protection

**LDP Session Protection** cho phép LDP **tự động bảo vệ các phiên** thiết lập. Mặc định, tính năng này **tắt**. Khi cấu hình, LDP sẽ tự động khởi tạo các gói **backup targeted hello** cho những neighbor backup cho liên kết chính. Các gói này **duy trì phiên LDP** khi liên kết chính bị mất.  

<img src="/docs/CCNP SP/img/mpls LDP Session Protection.png" style="max-width: 100%; width: 600px" />

### LDP Graceful Restart and NSR

**LDP Graceful Restart** cung cấp cơ chế khôi phục khỏi lỗi của mặt phẳng điều khiển mà không ảnh hưởng đến chuyển tiếp gói tin.  
Khi một router có **LDP Graceful Restart** kết nối với router hỗ trợ **NSF**, router NSF có thể giữ nguyên trạng thái chuyển tiếp khi phiên LDP bị gián đoạn. Nếu peer khởi động lại trong thời gian quy định, nó sẽ được phép đồng bộ lại. Nếu không, trạng thái cũ sẽ bị xóa sau hold timer.

**LDP NSR (Nonstop Routing)** giúp quá trình failover (RP hoặc DRP) diễn ra mà không ảnh hưởng đến quá trình hội tụ. 

<img src="/docs/CCNP SP/img/mpls LDP Graceful Restart and NSR 1.png" style="max-width: 100%; width: 600px" />
<img src="/docs/CCNP SP/img/mpls LDP Graceful Restart and NSR 2.png" style="max-width: 100%; width: 600px" />

### LDP IGP Synchronization

**LDP IGP Synchronization** giúp tránh mất **lưu lượng MPLS** do mất đồng bộ giữa LDP và IGP.  
Ví dụ: khi một liên kết vừa up, IGP có thể quảng bá và sử dụng liên kết đó **trước khi LDP hội tụ**.  

Khi được bật, **IGP chỉ quảng bá liên kết với metric bình thường khi LDP đã hội tụ trên liên kết đó.**  
LDP coi liên kết đã hội tụ khi:
- Có ít nhất một phiên LDP hoạt động trên liên kết.  
- Đã gửi và nhận được ít nhất một *label binding* từ peer.  

LDP thông báo trạng thái này cho IGP khi liên kết nháy up/down.  
Ngoài ra, có thể cấu hình **delay timer** để trì hoãn đồng bộ lên đến **60 giây**, trong trường hợp cần thời gian ổn định thêm.

<img src="/docs/CCNP SP/img/mpls LDP IGP Synchronization.png" style="max-width: 100%; width: 600px" />

### Lab

<img src="/docs/CCNP SP/img/mpls lab LDP Advanced.png" style="max-width: 100%; width: 400px" />

**xrv1**
```
conf
!
host xrv1
!
! @@@@@@@@@ 1. Thiet lap IP dau noi va Loopback IP
int lo0
  ipv4 addr 1.1.1.1/32
!
int g0/0/0/0
  no shut
  ipv4 addr 10.0.12.1/24
!
int g0/0/0/1
  no shut
  ipv4 addr 10.0.13.1/24
!
! @@@@@@@@@ 2. Xay dung OSPF neighbor giua cac Router
router ospf 1
  router-id 1.1.1.1
  area 0
    network point-to-point
    interface lo0
      exit
    interface gi0/0/0/0
      exit
    interface gi0/0/0/1
      exit
root
!
! @@@@@@@@@ 3. Cau hinh LDP Advanced
mpls ldp
  router-id 1.1.1.1
  !
  interface gi0/0/0/0
  interface gi0/0/0/1
  !
  ! @@@ 3.1. Cau hinh LDP Session Protection
  session protection
  !
  address-family ipv4
  !
    ! @@@ 3.2. Cau hinh LDP host-routes
    label local allocate for host-routes
    !
    ! @@@ 3.3. Cau hinh LDP explicit-null
    label local advertise explicit-null
  !
root
router ospf 1
  ! @@@ 3.4. Cau hinh LDP IGP Sync
  mpls ldp sync
root
!
commit
end
```

**xrv2**
```
conf
!
host xrv2
!
! @@@@@@@@@ 1. Thiet lap IP dau noi va Loopback IP
int lo0
  ipv4 addr 2.2.2.2/32
!
int g0/0/0/0
  no shut
  ipv4 addr 10.0.23.2/24
!
int g0/0/0/1
  no shut
  ipv4 addr 10.0.12.2/24
!
! @@@@@@@@@ 2. Xay dung OSPF neighbor giua cac Router
router ospf 1
  router-id 2.2.2.2
  area 0
    network point-to-point
    interface lo0
      exit
    interface gi0/0/0/0
      exit
    interface gi0/0/0/1
      exit
root
!
! @@@@@@@@@ 3. Cau hinh LDP Advanced
mpls ldp
  router-id 2.2.2.2
  !
  interface gi0/0/0/0
  interface gi0/0/0/1
  !
  ! @@@ 3.1. Cau hinh LDP Session Protection
  session protection
  !
  address-family ipv4
  !
    ! @@@ 3.2. Cau hinh LDP host-routes
    label local allocate for host-routes
    !
    ! @@@ 3.3. Cau hinh LDP explicit-null
    label local advertise explicit-null
  !
root
router ospf 1
  ! @@@ 3.4. Cau hinh LDP IGP Sync
  mpls ldp sync
root
!
commit
end
```

**xrv3**
```
conf
!
host xrv3
!
! @@@@@@@@@ 1. Thiet lap IP dau noi va Loopback IP
int lo0
  ipv4 addr 3.3.3.3/32
!
int g0/0/0/0
  no shut
  ipv4 addr 10.0.13.3/24
!
int g0/0/0/1
  no shut
  ipv4 addr 10.0.23.3/24
!
! @@@@@@@@@ 2. Xay dung OSPF neighbor giua cac Router
router ospf 1
  router-id 3.3.3.3
  area 0
    network point-to-point
    interface lo0
      exit
    interface gi0/0/0/0
      exit
    interface gi0/0/0/1
      exit
root
!
! @@@@@@@@@ 3. Cau hinh LDP Advanced
mpls ldp
  router-id 3.3.3.3
  !
  interface gi0/0/0/0
  interface gi0/0/0/1
  !
root
!
commit
end
```

```
RP/0/0/CPU0:xrv1#show mpls ldp neighbor
Sun Oct 12 14:29:55.181 UTC

Peer LDP Identifier: 2.2.2.2:0
  TCP connection: 2.2.2.2:54657 - 1.1.1.1:646
  Graceful Restart: No
  Session Holdtime: 180 sec
  State: Oper; Msgs sent/rcvd: 32/31; Downstream-Unsolicited
  Up time: 00:22:57
  LDP Discovery Sources:
    IPv4: (2)
      GigabitEthernet0/0/0/0                        <= xrv1 có 1 phiên peer xrv2 qua cổng 0/0/0/0
      Targeted Hello (1.1.1.1 -> 2.2.2.2, active)   <= ngoài ra xrv1 còn có 1 phiên backup peer xrv2 (vì xrv1 và xrv2 có cấu hình `mpls ldp session protection`,
                                                       định kì loopback của 2 router gửi Targeted Hello cho nhau)
    IPv6: (0)
  Addresses bound to this peer:
    IPv4: (3)
      2.2.2.2        10.0.12.2      10.0.23.2
    IPv6: (0)

Peer LDP Identifier: 3.3.3.3:0
  TCP connection: 3.3.3.3:36434 - 1.1.1.1:646
  Graceful Restart: No
  Session Holdtime: 180 sec
  State: Oper; Msgs sent/rcvd: 25/29; Downstream-Unsolicited
  Up time: 00:17:32
  LDP Discovery Sources:
    IPv4: (1)
      GigabitEthernet0/0/0/1                        <= xrv1 chỉ có 1 phiên peer xrv3 qua cổng 0/0/0/1
    IPv6: (0)
  Addresses bound to this peer:
    IPv4: (3)
      3.3.3.3        10.0.13.3      10.0.23.3
    IPv6: (0)

RP/0/0/CPU0:xrv1#show cef 2.2.2.2
Sun Oct 12 14:43:43.335 UTC
2.2.2.2/32, version 23, internal 0x1000001 0x0 (ptr 0xa13ffb74) [1], 0x0 (0xa13cb3b0), 0xa28 (0xa157b0f0)
 Updated Oct 12 14:40:19.579
 local adjacency 10.0.12.2
 Prefix Len 32, traffic index 0, precedence n/a, priority 3
   via 10.0.12.2/32, GigabitEthernet0/0/0/0, 3 dependencies, weight 0, class 0 [flags 0x0]
    path-idx 0 NHID 0x0 [0xa10f634c 0x0]
    next hop 10.0.12.2/32
    local adjacency
     local label 24000      labels imposed {0}          <= Bảng FIB nói xrv1 trước khi gửi gói tin đến 2.2.2.2 sẽ gắn nhãn {0} tức {explicit-null},
                                                           vì xrv2 có cấu hình `advertise explicit-null`
RP/0/0/CPU0:xrv1#show cef 3.3.3.3
Sun Oct 12 14:43:47.824 UTC
3.3.3.3/32, version 32, internal 0x1000001 0x0 (ptr 0xa13ffcf4) [1], 0x0 (0xa13cb320), 0xa20 (0xa157b168)
 Updated Oct 12 14:41:58.851
 local adjacency 10.0.13.3
 Prefix Len 32, traffic index 0, precedence n/a, priority 3
   via 10.0.13.3/32, GigabitEthernet0/0/0/1, 7 dependencies, weight 0, class 0 [flags 0x0]
    path-idx 0 NHID 0x0 [0xa10f6154 0xa10f61a8]
    next hop 10.0.13.3/32
    local adjacency
     local label 24001      labels imposed {ImplNull}   <= Bảng FIB nói xrv1 trước khi gửi gói tin đến 3.3.3.3 sẽ pop nhãn,
                                                           vì xrv3 ko cấu hình `advertise explicit-null`
RP/0/0/CPU0:xrv1#
RP/0/0/CPU0:xrv1#show mpls ldp bindings
Sun Oct 12 14:30:44.858 UTC

1.1.1.1/32, rev 2
        Local binding: label: ImpNull
        Remote bindings: (2 peers)
            Peer                Label
            -----------------   ---------
            2.2.2.2:0           24000
            3.3.3.3:0           24000
2.2.2.2/32, rev 5
        Local binding: label: 24000
        Remote bindings: (2 peers)
            Peer                Label
            -----------------   ---------
            2.2.2.2:0           ExpNullv4         <= Bảng LIB nói xrv2 quảng bá prefix 2.2.2.2/32 cho xrv1: nhớ gắn nhãn {0} nhá
            3.3.3.3:0           24001
3.3.3.3/32, rev 6
        Local binding: label: 24001
        Remote bindings: (2 peers)
            Peer                Label
            -----------------   ---------
            2.2.2.2:0           24001
            3.3.3.3:0           ImpNull           <= Bảng LIB nói xrv3 quảng bá prefix 3.3.3.3/32 cho xrv1: pop nhãn rồi gửi nhá
10.0.12.0/24, rev 0
        No local binding
        Remote bindings: (1 peers)
            Peer                Label
            -----------------   ---------
            3.3.3.3:0           24002
10.0.13.0/24, rev 0
        No local binding
        Remote bindings: (1 peers)
            Peer                Label
            -----------------   ---------
            3.3.3.3:0           ImpNull
10.0.23.0/24, rev 0
        No local binding
        Remote bindings: (1 peers)
            Peer                Label
            -----------------   ---------
            3.3.3.3:0           ImpNull

RP/0/0/CPU0:xrv1#show mpls ldp forwarding
Sun Oct 12 14:31:28.515 UTC

Codes:
  - = GR label recovering, (!) = LFA FRR pure backup path
  {} = Label stack with multi-line output for a routing path
  G = GR, S = Stale, R = Remote LFA FRR backup

Prefix          Label   Label(s)       Outgoing     Next Hop            Flags
                In      Out            Interface                        G S R
--------------- ------- -------------- ------------ ------------------- -----
2.2.2.2/32      24000   ExpNullv4      Gi0/0/0/0    10.0.12.2                 <= Bảng LFIB nói xrv1 trước khi gửi gói tin đến 2.2.2.2 sẽ gắn nhãn {0}
3.3.3.3/32      24001   ImpNull        Gi0/0/0/1    10.0.13.3                 <= Bảng LFIB nói xrv1 trước khi gửi gói tin đến 3.3.3.3 sẽ pop nhãn

RP/0/0/CPU0:xrv1#configure
Sun Oct 12 14:32:40.540 UTC
RP/0/0/CPU0:xrv1(config)#interface g0/0/0/0
RP/0/0/CPU0:xrv1(config-if)#shutdown
RP/0/0/CPU0:xrv1(config-if)#commit
Sun Oct 12 14:33:02.928 UTC
RP/0/0/CPU0:xrv1(config-if)#end
RP/0/0/CPU0:xrv1#show mpls ldp neighbor
Sun Oct 12 14:33:11.998 UTC

Peer LDP Identifier: 2.2.2.2:0
  TCP connection: 2.2.2.2:54657 - 1.1.1.1:646
  Graceful Restart: No
  Session Holdtime: 180 sec
  State: Oper; Msgs sent/rcvd: 37/35; Downstream-Unsolicited
  Up time: 00:26:14
  LDP Discovery Sources:
    IPv4: (1)
      Targeted Hello (1.1.1.1 -> 2.2.2.2, active)       <= Shut link xrv1-xrv2, tuy nhiên phiên LDP giữa xrv1 và xrv2 vẫn up, nhờ backup target LDP
    IPv6: (0)
  Addresses bound to this peer:
    IPv4: (3)
      2.2.2.2        10.0.12.2      10.0.23.2
    IPv6: (0)

Peer LDP Identifier: 3.3.3.3:0
  TCP connection: 3.3.3.3:36434 - 1.1.1.1:646
  Graceful Restart: No
  Session Holdtime: 180 sec
  State: Oper; Msgs sent/rcvd: 30/33; Downstream-Unsolicited
  Up time: 00:20:49
  LDP Discovery Sources:
    IPv4: (1)
      GigabitEthernet0/0/0/1
    IPv6: (0)
  Addresses bound to this peer:
    IPv4: (3)
      3.3.3.3        10.0.13.3      10.0.23.3
    IPv6: (0)

RP/0/0/CPU0:xrv1#show mpls ldp bindings
Sun Oct 12 14:33:21.977 UTC

1.1.1.1/32, rev 2
        Local binding: label: ImpNull
        Remote bindings: (2 peers)
            Peer                Label
            -----------------   ---------
            2.2.2.2:0           24000
            3.3.3.3:0           24000
2.2.2.2/32, rev 5
        Local binding: label: 24000
        Remote bindings: (2 peers)
            Peer                Label
            -----------------   ---------
            2.2.2.2:0           ExpNullv4
            3.3.3.3:0           24001
3.3.3.3/32, rev 6
        Local binding: label: 24001
        Remote bindings: (2 peers)
            Peer                Label
            -----------------   ---------
            2.2.2.2:0           24001
            3.3.3.3:0           ImpNull
10.0.12.0/24, rev 0
        No local binding
        Remote bindings: (1 peers)
            Peer                Label
            -----------------   ---------
            3.3.3.3:0           24002
10.0.13.0/24, rev 0
        No local binding
        Remote bindings: (1 peers)
            Peer                Label
            -----------------   ---------
            3.3.3.3:0           ImpNull
10.0.23.0/24, rev 0
        No local binding
        Remote bindings: (1 peers)
            Peer                Label
            -----------------   ---------
            3.3.3.3:0           ImpNull

RP/0/0/CPU0:xrv1#show mpls ldp forwarding
Sun Oct 12 14:33:37.756 UTC

Codes:
  - = GR label recovering, (!) = LFA FRR pure backup path
  {} = Label stack with multi-line output for a routing path
  G = GR, S = Stale, R = Remote LFA FRR backup

Prefix          Label   Label(s)       Outgoing     Next Hop            Flags
                In      Out            Interface                        G S R
--------------- ------- -------------- ------------ ------------------- -----
2.2.2.2/32      24000   24001          Gi0/0/0/1    10.0.13.3
3.3.3.3/32      24001   ImpNull        Gi0/0/0/1    10.0.13.3

RP/0/0/CPU0:xrv1#configure
Sun Oct 12 14:35:06.290 UTC
RP/0/0/CPU0:xrv1(config)#interface g0/0/0/0
RP/0/0/CPU0:xrv1(config-if)#no shutdown
RP/0/0/CPU0:xrv1(config-if)#commit
Sun Oct 12 14:35:15.729 UTC
RP/0/0/CPU0:Oct 12 14:35:15.749 : ifmgr[228]: %PKT_INFRA-LINK-3-UPDOWN : Interface GigabitEthernet0/0/0/0, changed state to Down
RP/0/0/CPU0:xrv1(config-if)#RP/0/0/CPU0:Oct 12 14:35:15.779 : ifmgr[228]: %PKT_INFRA-LINK-3-UPDOWN : Interface GigabitEthernet0/0/0/0, changed state to Up

RP/0/0/CPU0:xrv1(config-if)#end
RP/0/0/CPU0:xrv1#
RP/0/0/CPU0:xrv1#show route | i 2.2.2.2
Sun Oct 12 14:37:11.781 UTC
O    2.2.2.2/32 [110/2] via 10.0.12.2, 00:01:49, GigabitEthernet0/0/0/0
RP/0/0/CPU0:xrv1#configure
Sun Oct 12 14:37:15.891 UTC
RP/0/0/CPU0:xrv1(config)#interface g0/0/0/1
RP/0/0/CPU0:xrv1(config-if)#shutdown
RP/0/0/CPU0:xrv1(config-if)#mpls ldp
RP/0/0/CPU0:xrv1(config-ldp)#no interface g0/0/0/0
RP/0/0/CPU0:xrv1(config-ldp)#commit
Sun Oct 12 14:37:37.570 UTC
RP/0/0/CPU0:xrv1(config-ldp)#end
RP/0/0/CPU0:xrv1#show route | i 2.2.2.2
Sun Oct 12 14:38:15.027 UTC
O    2.2.2.2/32 [110/65536] via 10.0.12.2, 00:00:04, GigabitEthernet0/0/0/0   <= Shut link xrv1-xrv3 và xóa ldp peer xrv1-xrv2,
                                                                                 thì cost metric ospf xrv1 đi 2.2.2.2 tăng 65536,
                                                                                 là do cấu hình `router ospf 1 mpls ldp sync` sẽ
                                                                                 tăng max metric ospf đối với link ospf up nhưng
                                                                                 ldp down. Nếu no shut link xrv1-xrv3, sẽ thấy
                                                                                 ospf học ưu tiên sang link xrv1-xrv3.
RP/0/0/CPU0:xrv1#
```

```
RP/0/0/CPU0:xrv3#show mpls ldp forwarding
Sun Oct 12 14:42:40.139 UTC

Codes:
  - = GR label recovering, (!) = LFA FRR pure backup path
  {} = Label stack with multi-line output for a routing path
  G = GR, S = Stale, R = Remote LFA FRR backup

Prefix          Label   Label(s)       Outgoing     Next Hop            Flags
                In      Out            Interface                        G S R
--------------- ------- -------------- ------------ ------------------- -----
1.1.1.1/32      24000   ExpNullv4      Gi0/0/0/0    10.0.13.1
2.2.2.2/32      24001   ExpNullv4      Gi0/0/0/1    10.0.23.2
10.0.12.0/24    24002   Unlabelled     Gi0/0/0/0    10.0.13.1                 <= So sánh với bảng LFIB của xrv1 sẽ thấy, xrv1 chỉ học /32 trong khi xrv3 học cả /24,
                        Unlabelled     Gi0/0/0/1    10.0.23.2                    là vì xrv1 có cấu hình `allocate for host-routes` còn xrv3 thì không

RP/0/0/CPU0:xrv3#
```

## MPLS Traffic Engineering

**Mục tiêu:**  
**Điều khiển luồng lưu lượng mạng**, giảm nghẽn mạng, tận dụng tối đa tài nguyên mạng.
 
<img src="/docs/CCNP SP/img/mpls Tunnel Path with Most Available Resources.png" style="max-width: 100%; width: 350px" />

**Yêu cầu chính:**  
- Mọi LSR phải thấy **toàn bộ topology** mạng (qua OSPF/IS-IS).  
- Phải biết **thông tin thêm** về tài nguyên (băng thông, ràng buộc).  
- Cần **OSPF hoặc IS-IS** có mở rộng TE và RSVP để thiết lập tunnel, phân phối nhãn.

**Cơ chế hoạt động:**  
- MPLS TE tạo **Label-Switched Path (LSP)** – đường hầm dẫn lưu lượng qua các router được chỉ định.  
- **CSPF (Constrained SPF)** chọn đường ngắn nhất thỏa mãn ràng buộc tài nguyên.  
- **RSVP** gửi thông điệp **Path** từ router đầu (headend) đến cuối (tail-end), rồi nhận lại **Resv** để gán nhãn và thiết lập LSP.

<img src="/docs/CCNP SP/img/mpls RSVP Path.png" style="max-width: 100%; width: 600px" />
<img src="/docs/CCNP SP/img/mpls RSVP Resv.png" style="max-width: 100%; width: 600px" />

**Chuyển lưu lượng vào tunnel:**  
- **static route**
- **autoroute announce** (tự quảng bá tunnel vào IGP)  
- Hoặc **policy-based routing (PBR)**.

**End to End Protection:**  
Khi **LSP chính (protected LSP)** gặp sự cố, **router nguồn** sẽ ngay lập tức kích hoạt **LSP dự phòng (secondary LSP)** để tạm thời chuyển lưu lượng của tunnel.  
Nếu **LSP dự phòng** cũng bị lỗi, tunnel sẽ mất khả năng bảo vệ đường đi cho đến khi lỗi được khắc phục.  
Cơ chế bảo vệ đường đi (path protection) có thể được áp dụng trong cùng một vùng IGP.

<img src="/docs/CCNP SP/img/mpls te End to End Protection.png" style="max-width: 100%; width: 800px" />

### Lab

<img src="/docs/CCNP SP/img/mpls lab tunnel-te.png" style="max-width: 100%; width: 420px" />

**xrv4**
```
conf
!
host xrv4
!
! @@@@@@@@@ 1. Thiet lap IP dau noi va Loopback IP
int lo0
  ipv4 addr 4.4.4.4/32
!
int g0/0/0/0
  no shut
  ipv4 addr 10.0.24.4/24
!
! @@@@@@@@@ 2. Xay dung OSPF neighbor giua cac Router
router ospf 1
  router-id 4.4.4.4
  area 0
    network point-to-point
    interface lo0
      exit
    interface gi0/0/0/0
      exit
root
!
commit
end
```

**xrv2**
```
conf
!
int g0/0/0/2
  no shut
  ipv4 addr 10.0.24.2/24
!
router ospf 1
  area 0
    interface gi0/0/0/2
      exit
root
!
commit
end
```

**xrv1/2/3/4**
```
conf
!
router ospf 1
  mpls traffic-eng router-id loopback 0
  mpls traffic-eng multicast-intact
  area 0
    mpls traffic-eng
root
!
mpls traffic-eng
  interface gi0/0/0/0
  !
  interface gi0/0/0/1
  !
  interface gi0/0/0/2
  !
  signalling advertise explicit-null
root
!
rsvp
  interface gi0/0/0/0
    bandwidth percentage 85
  !
  interface gi0/0/0/1
    bandwidth percentage 85
  !
  interface gi0/0/0/2
    bandwidth percentage 85
  !
root
!
commit
end
```
```
RP/0/0/CPU0:xrv1#show rsvp interface
Wed Oct 22 17:28:00.849 UTC

*: RDM: Default I/F B/W % : 75% [default] (max resv/bc0), 0% [default] (bc1)

Interface                 MaxBW (bps)  MaxFlow (bps) Allocated (bps)      MaxSub (bps)
------------------------- ------------ ------------- -------------------- -------------
GigabitEthernet0/0/0/0           850M           850M             0 (  0%)            0
GigabitEthernet0/0/0/1           850M           850M             0 (  0%)            0
GigabitEthernet0/0/0/2           850M           850M             0 (  0%)            0
RP/0/0/CPU0:xrv1#
```

**xrv1**
```
conf
!
interface tunnel-te4
  description xrv1-to-xrv4-dynamicpath
  ipv4 unnumbered Loopback0
  signalled-name xrv1-to-xrv4-dynamicpath
  destination 4.4.4.4
  path-option 1 dynamic
!
commit
end
```
```
RP/0/0/CPU0:xrv1#show mpls traffic-eng tunnels 4
Mon Oct 13 18:29:37.519 UTC


Name: tunnel-te4  Destination: 4.4.4.4  Ifhandle:0xd0
  Signalled-Name: xrv1-to-xrv4-dynamicpath
  Status:
    Admin:    up Oper:   up   Path:  valid   Signalling: connected

    path option 1,  type dynamic  (Basis for Setup, path weight 2)
    G-PID: 0x0800 (derived from egress interface properties)
    Bandwidth Requested: 0 kbps  CT0
    Creation Time: Mon Oct 13 18:28:05 2025 (00:01:32 ago)
  Config Parameters:
    Bandwidth:        0 kbps (CT0) Priority:  7  7 Affinity: 0x0/0xffff
    Metric Type: TE (global)
    Path Selection:
      Tiebreaker: Min-fill (default)
    Hop-limit: disabled
    Cost-limit: disabled
    Path-invalidation timeout: 10000 msec (default), Action: Tear (default)
    AutoRoute: disabled  LockDown: disabled   Policy class: not set
    Forward class: 0 (default)
    Forwarding-Adjacency: disabled
    Autoroute Destinations: 0
    Loadshare:          0 equal loadshares
    Auto-bw: disabled
    Fast Reroute: Disabled, Protection Desired: None
    Path Protection: Not Enabled
    BFD Fast Detection: Disabled
    Reoptimization after affinity failure: Enabled
    Soft Preemption: Disabled
  History:
    Tunnel has been up for: 00:01:31 (since Mon Oct 13 18:28:06 UTC 2025)
    Current LSP:
      Uptime: 00:01:31 (since Mon Oct 13 18:28:06 UTC 2025)

  Path info (OSPF 1 area 0):
  Node hop count: 2
  Hop0: 10.0.12.2
  Hop1: 10.0.24.4
  Hop2: 4.4.4.4
Displayed 1 (of 2) heads, 0 (of 0) midpoints, 0 (of 0) tails
Displayed 1 up, 0 down, 0 recovering, 0 recovered heads
```
```
conf
!
explicit-path name xrv1-to-xrv4
 index 1 next-address strict ipv4 unicast 10.0.13.3
 index 2 next-address strict ipv4 unicast 10.0.23.2
 index 3 next-address strict ipv4 unicast 10.0.24.4
!
explicit-path name xrv1-to-xrv4-bk
 index 1 next-address strict ipv4 unicast 10.0.12.2
 index 2 next-address strict ipv4 unicast 10.0.24.4
!
interface tunnel-te40
  description xrv1-to-xrv4-explicitpath
  ipv4 unnumbered Loopback0
  signalled-name xrv1-to-xrv4-explicitpath
  autoroute announce
  !
  destination 4.4.4.4
  path-protection
  path-option 1 explicit name xrv1-to-xrv4 protected-by 2
  path-option 2 explicit name xrv1-to-xrv4-bk
!
commit
end
```
```
RP/0/0/CPU0:xrv1#show mpls traffic-eng tunnels 40
Mon Oct 13 18:54:52.165 UTC


Name: tunnel-te40  Destination: 4.4.4.4  Ifhandle:0xf0
  Signalled-Name: xrv1-to-xrv4-explicitpath
  Status:
    Admin:    up Oper:   up   Path:  valid   Signalling: connected

    path option 1,  type explicit xrv1-to-xrv4 (Basis for Setup, path weight 3)
      Protected-by PO index: 2
    path option 2,  type explicit xrv1-to-xrv4-bk (Basis for Standby, path weight 2)
    G-PID: 0x0800 (derived from egress interface properties)
    Bandwidth Requested: 0 kbps  CT0
    Creation Time: Mon Oct 13 18:36:26 2025 (00:18:26 ago)
  Config Parameters:
    Bandwidth:        0 kbps (CT0) Priority:  7  7 Affinity: 0x0/0xffff
    Metric Type: TE (global)
    Path Selection:
      Tiebreaker: Min-fill (default)
    Hop-limit: disabled
    Cost-limit: disabled
    Path-invalidation timeout: 10000 msec (default), Action: Tear (default)
    AutoRoute:  enabled  LockDown: disabled   Policy class: not set
    Forward class: 0 (default)
    Forwarding-Adjacency: disabled
    Autoroute Destinations: 0
    Loadshare:          0 equal loadshares
    Auto-bw: disabled
    Fast Reroute: Disabled, Protection Desired: None
    Path Protection: Enabled
    BFD Fast Detection: Disabled
    Reoptimization after affinity failure: Enabled
    Soft Preemption: Disabled
  History:
    Tunnel has been up for: 00:10:38 (since Mon Oct 13 18:44:14 UTC 2025)
    Current LSP:
      Uptime: 00:07:42 (since Mon Oct 13 18:47:10 UTC 2025)
    Reopt. LSP:
      Last Failure:
        LSP not signalled, identical to the [CURRENT] LSP
        Date/Time: Mon Oct 13 18:47:45 UTC 2025 [00:07:07 ago]
    Prior LSP:
      ID: 5 Path Option: 2
      Removal Trigger: reoptimization completed
    Standby LSP:
      Uptime: 00:01:08 (since Mon Oct 13 18:53:44 UTC 2025)

  Path info (OSPF 1 area 0):
  Node hop count: 3
  Hop0: 10.0.13.3
  Hop1: 10.0.23.2
  Hop2: 10.0.24.4
  Hop3: 4.4.4.4

  Standby LSP Path info (OSPF 1 area 0), Oper State: Up :
  Node hop count: 2
  Hop0: 10.0.12.2
  Hop1: 10.0.24.4
  Hop2: 4.4.4.4
Displayed 1 (of 3) heads, 0 (of 0) midpoints, 0 (of 0) tails
Displayed 1 up, 0 down, 0 recovering, 0 recovered heads
RP/0/0/CPU0:xrv1#
RP/0/0/CPU0:xrv1#traceroute mpls traffic-eng tunnel-te 40 lsp active
Mon Oct 13 18:55:24.133 UTC

Tracing MPLS TE Label Switched Path on tunnel-te40, timeout is 2 seconds

Codes: '!' - success, 'Q' - request not sent, '.' - timeout,
  'L' - labeled output interface, 'B' - unlabeled output interface,
  'D' - DS Map mismatch, 'F' - no FEC mapping, 'f' - FEC mismatch,
  'M' - malformed request, 'm' - unsupported tlvs, 'N' - no rx label,
  'P' - no rx intf label prot, 'p' - premature termination of LSP,
  'R' - transit router, 'I' - unknown upstream index,
  'X' - unknown return code, 'x' - return code 0

Type escape sequence to abort.

  0 10.0.13.1 MRU 1500 [Labels: 24005 Exp: 0]
L 1 10.0.13.3 MRU 1500 [Labels: 24005 Exp: 0] 30 ms
L 2 10.0.23.2 MRU 1500 [Labels: implicit-null Exp: 0] 0 ms
! 3 10.0.24.4 10 ms
RP/0/0/CPU0:xrv1#traceroute mpls traffic-eng tunnel-te 40 lsp path-protect
Mon Oct 13 18:55:33.012 UTC

Tracing MPLS TE Label Switched Path on tunnel-te40, timeout is 2 seconds

Codes: '!' - success, 'Q' - request not sent, '.' - timeout,
  'L' - labeled output interface, 'B' - unlabeled output interface,
  'D' - DS Map mismatch, 'F' - no FEC mapping, 'f' - FEC mismatch,
  'M' - malformed request, 'm' - unsupported tlvs, 'N' - no rx label,
  'P' - no rx intf label prot, 'p' - premature termination of LSP,
  'R' - transit router, 'I' - unknown upstream index,
  'X' - unknown return code, 'x' - return code 0

Type escape sequence to abort.

  0 10.0.12.1 MRU 1500 [Labels: 24004 Exp: 0]
L 1 10.0.12.2 MRU 1500 [Labels: implicit-null Exp: 0] 10 ms
! 2 10.0.24.4 1 ms
RP/0/0/CPU0:xrv1#
RP/0/0/CPU0:xrv1#show route 4.4.4.4/32
Mon Oct 13 18:56:24.239 UTC

Routing entry for 4.4.4.4/32
  Known via "ospf 1", distance 110, metric 65537, type intra area
  Installed Oct 13 18:53:44.830 for 00:02:39
  Routing Descriptor Blocks
    4.4.4.4, from 4.4.4.4, via tunnel-te40
      Route metric is 65537
  No advertising protos.
RP/0/0/CPU0:xrv1#
```