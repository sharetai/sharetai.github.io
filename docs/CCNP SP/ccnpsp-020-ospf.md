---
layout: default
title: OSPF
nav_order: 20
parent: CCNP SP
---

# Open Shortest Path First
{: .no_toc }

Giao thức định tuyến OSPF
{: .fs-6 .fw-300 }

---

## TABLE OF CONTENTS
{: .no_toc .text-delta }

1. TOC
{:toc}

---

## OSPF Fundamentals

**OSPF** là giao thức định tuyến **IGP (Interior Gateway Protocol)**, chuẩn mở, khắc phục các hạn chế của distance vector.  
- **OSPFv2** (RFC 2328): hỗ trợ IPv4  
- **OSPFv3**: hỗ trợ IPv6  

OSPF trao đổi thông tin định tuyến thông qua **LSA (Link-State Advertisement)** để quảng bá trạng thái liên kết và metric đến router thiết lập láng giềng. Các LSA nhận được được lưu trong **LSDB (link-state database)**, tất cả router trong cùng 1 area duy trì bản sao đồng bộ giống nhau.  

**LSDB** cung cấp bản đồ đầy đủ của mạng. Từ đó, router chạy thuật toán **Dijkstra’s shortest path first (SPF)** để tạo cây đường đi ngắn nhất **SPT (SPF tree)** đảm bảo **loop-free**, với chính nó là gốc (**root**).  

1 router có thể chạy nhiều tiến trình OSPF, mỗi tiến trình có LSDB riêng, không chia sẻ nếu không được **redistribution**. Giá trị process OSPF chỉ có ý nghĩa cục bộ, không cần khớp giữa các router.

<img src="/docs/CCNP SP/img/OSPF SPF tree.png" style="max-width: 100%; width: 800px" />

Ví dụ minh họa 1 topology OSPF đơn giản và cây SPT nhìn từ **R1** và **R4**. Chú ý là từ góc nhìn của mỗi router, **chính nó luôn là gốc (root)** của cây SPT.

## Areas

OSPF tăng khả năng mở rộng bằng cách chia topology thành nhiều **area** trong cùng 1 miền định tuyến.  
Mỗi **interface** chỉ thuộc về **1 area duy nhất**, và **area ID** được gửi trong gói **hello**.  
Tất cả router trong cùng 1 area sẽ có **bản sao LSDB giống hệt nhau**.  

Khi số lượng liên kết và router trong area tăng, **1 area** sẽ gặp các hạn chế:  
- Mỗi khi 1 liên kết thay đổi trạng thái, toàn bộ **SPT** phải được tính lại.  
- **LSDB** trở nên quá lớn và khó quản lý.  
- Việc tính toán **SPF** tiêu tốn nhiều bộ nhớ và thời gian hơn.

Phải cần **thiết kế nhiều area** để giữ cho LSDB nhỏ gọn và dễ quản lý hơn.

Nếu 1 router có các interface thuộc nhiều **area**, nó sẽ duy trì **1 LSDB riêng cho từng area**.  
1 router kết nối nhiều area **không tự động quảng bá route giữa các area**.  
Ví dụ, nếu R1 nối với **Area 1** và **Area 2**, thì **route từ Area 1 không được quảng bá sang Area 2**, và ngược lại.

Area 0 là **area backbone**, mọi area đều phải kết nối với Area 0. Các area khác đưa thông tin định tuyến vào Area 0, và Area 0 sẽ quảng bá các route này sang các area khác.  
Area Backbone ngăn vòng lặp và phân phối route giữa các area.  
**Area ID** dài 32 bit, có thể biểu diễn ở dạng **decimal (0–4294967295)** hoặc **dotted-decimal (0.0.0.0–255.255.255.255)**.  
**ABR (Area Border Router)** là router nối Area 0 với area khác 0, chịu trách nhiệm quảng bá route giữa các area, đồng thời tính SPF riêng cho từng area.

<img src="/docs/CCNP SP/img/Successful Route Advertisement Between Areas.png" style="max-width: 100%; width: 600px" />

Trong hình trên, **R1** kết nối với **Area 0**, **Area 1**, và **Area 2**, nên là **ABR** hợp lệ.  
Route từ **Area 1** và **Area 2** → quảng bá vào **Area 0**.  
Route từ **Area 0** (bao gồm cả route nội bộ và route học được từ **Area 1 & 2**) → quảng bá vào **Area 1** và **Area 2**.  
Cấu trúc này minh họa mô hình **multi-area OSPF**, **Area 0 làm trung tâm** trao đổi định tuyến giữa các area khác.

## Communication

OSPF chạy trực tiếp trên **IPv4**, **protocol 89**.  
OSPF dùng 2 địa chỉ **multicast**:  
- **AllSPFRouters** – IPv4 224.0.0.5 hay MAC 01:00:5E:00:00:05. Tất cả router chạy OSPF đều phải nhận.  
- **AllDRouters** – IPv4 224.0.0.6 hay MAC 01:00:5E:00:00:06. Dùng trao đổi với **Designated Router (DR)**.  

| Type  | Packet Name                           | Functional Overview                                                                                                   |
|:------|:--------------------------------------|:----------------------------------------------------------------------------------------------------------------------|
| **1** | **Hello**                             | Gửi định kỳ trên tất cả giao diện OSPF để phát hiện láng giềng mới và đảm bảo các láng giềng hiện tại vẫn hoạt động.  |
| **2** | **Database Description (DBD/DDP)**    | Trao đổi header của LSDB.                                                                                             |
| **3** | **Link-State Request (LSR)**          | Khi router phát hiện một phần LSDB bị thiếu hoặc cũ, nó sẽ yêu cầu phần dữ liệu đó từ láng giềng.                     |
| **4** | **Link-State Update (LSU)**           | Chứa LSA cụ thể cho một liên kết mạng; thường được gửi để phản hồi trực tiếp LSR.                                     |
| **5** | **Link-State Acknowledgment (LSAck)** | Gửi để xác nhận việc nhận LSA, giúp quá trình truyền bá LSA trở nên tin cậy.                                          |

## Router ID

**Router ID (RID)** là số 32-bit dùng để định danh duy nhất cho mỗi router trong miền OSPF.  
RID được tự động chọn là **địa chỉ IP cao nhất của loopback interface đang up**; nếu không có loopback, dùng **địa chỉ IP cao nhất của interface vật lý đang up**.  
RID được chọn **khi tiến trình OSPF khởi tạo** và **không thay đổi** cho đến khi tiến trình khởi động lại.  
**Cấu hình RID tĩnh** giúp dễ xử lý sự cố và giảm LSAs khi RID thay đổi. RID gồm **4 octet**, cấu hình bằng lệnh: **router-id** *router-id*

## Hello Packet

**Hello packet** chịu trách nhiệm **phát hiện và duy trì mối quan hệ láng giềng (neighbor)** trong OSPF.  
Router sẽ gửi **hello packet** đến địa chỉ multicast **AllSPFRouters (224.0.0.5)**.  
Bảng dưới liệt kê **các thông tin chính** chứa trong 1 OSPF hello packet.  

| Trường Dữ Liệu (Data Field)                       | Mô Tả (Description)                                                                                                   |
|:--------------------------------------------------|:----------------------------------------------------------------------------------------------------------------------|
| **Router ID (RID)**                               | Là 1 ID 32-bit duy nhất trong miền OSPF.                                                                              |
| **Authentication Options**                        | Tùy chọn bảo mật giao tiếp giữa các router OSPF. Các tùy chọn gồm: **none**, **plaintext**, hoặc **MD5**.             |
| **Area ID**                                   | OSPF area mà interface thuộc về. Là số 32-bit, có thể viết dạng **dot-decimal** (**0.0.1.0**) hoặc **decimal** (**256**). |
| **Interface Address Mask**                        | Network mask của địa chỉ IP chính của interface gửi gói hello.                                                        |
| Interface Priority                                | Mức ưu tiên của interface trong quá trình bầu chọn DR.                                                                |
| **Hello Interval**                                | Thời gian (giây) giữa 2 gói hello liên tiếp được gửi trên interface.                                                  |
| **Dead Interval**                                 | Thời gian (giây) mà router chờ gói hello từ neighbor trước khi coi neighbor đó là down.                               |
| Designated Router / Backup Designated Router      | Địa chỉ IP của DR và BDR cho liên kết mạng đó.                                                                        |
| Active Neighbor | Danh sách các OSPF neighbor đã được nhìn thấy trên phân đoạn mạng. Router phải nhận được gói hello từ các neighbor này trong hạn dead interval.         |
| **Area Type**                                     | Loại area như backbone, non-backbone, stub, NSSA..                                                                    |
| **Network Type**                                  | Loại network như broadcast, point-to-point, NBMA..                                                                    |

## Neighbors

**Neighbor**: Là router chia sẻ cùng một liên kết mạng có kích hoạt OSPF.  
**Adjacent**: Là neighbor có **cơ sở dữ liệu OSPF (LSDB)** được **đồng bộ hoàn toàn**.  

| Trạng Thái (State) | Mô Tả (Description)                                                                                                                          |
| :----------------- | :------------------------------------------------------------------------------------------------------------------------------------------- |
| **Down**           | Trạng thái khởi tạo, cho biết router **chưa nhận được** gói tin Hello OSPF nào.                                                              |
| **Init**           | Đã **nhận được gói Hello** từ router khác, nhưng **chưa thiết lập giao tiếp hai chiều**.                                                     |
| **2-Way**          | **Giao tiếp hai chiều** đã được thiết lập. Nếu mạng yêu cầu **bầu chọn DR/BDR**, việc này diễn ra ở đây.                                     |
| **ExStart**        | Bước đầu tiên để **hình thành adjacency**. Các router xác định ai là **master** và ai là **slave** trong quá trình đồng bộ LSDB.             |
| **Exchange**       | Các router **trao đổi thông tin LSDB** bằng các gói **Database Description (DBD)**.                                                          |
| **Loading**        | Router **gửi LSR (Link-State Request)** để yêu cầu các **LSA (Link-State Advertisement)** mới hơn chưa nhận được trong giai đoạn Exchange.   |
| **Full**           | Hai router **đã trở thành adjacent đầy đủ** và **LSDB được đồng bộ hóa hoàn toàn**.                                                          |

## Requirements for Neighbor Adjacency

Để 2 router OSPF có thể trở thành **adjacent neighbor** (quan hệ láng giềng đầy đủ, đồng bộ LSDB), các yêu cầu sau cần được đáp ứng:

- **RID** phải **duy nhất** giữa 2 thiết bị. Để tránh lỗi, tốt nhất nên **duy nhất trong toàn miền OSPF**.
- 2 interface phải nằm trong **cùng subnet**, vì OSPF sử dụng địa chỉ IP chính của interface để gửi gói Hello. Trường netmask trong gói Hello dùng để xác định Network ID.
- **MTU** trên 2 interface phải **bằng nhau**, do OSPF **không hỗ trợ phân mảnh gói tin**.
- 2 interface phải thuộc **cùng Area ID**.
- **Nhu cầu bầu chọn DR/BDR** phải **giống nhau** trên cùng segment mạng. Tức network type phải tương thích.
- **Hello interval** và **Dead interval** phải **giống nhau** để đảm bảo đồng bộ.
- **Kiểu xác thực** và **thông tin xác thực** (nếu có) phải **trùng khớp**.
- **Kiểu area type** như stub, NSSA,... phải **giống nhau** giữa các router.

<img src="/docs/CCNP SP/img/Process for Forming OSPF Neighbor Adjacencies.png" style="max-width: 100%; width: 800px" />

Hình trên minh họa các trạng thái và các gói tin được trao đổi khi hai router (R1 và R2) hình thành 1 quan hệ OSPF adjacency.  
Để quan sát chi tiết quá trình hoặc debug lỗi, có thể sử dụng lệnh: **debug ip ospf adj**

## Lab

<img src="/docs/CCNP SP/img/ospf lab.png" style="max-width: 100%; width: 1500px" />

```
1. Thiet lap IP dau noi va Loopback IP cho cac Router theo hinh ve tren

2. Xay dung OSPF neighbor giua cac Router dap ung cac dieu kien sau:
2.1. vIOS-xRV1: area0, xRV1-xRV2: area 1, xRV1-xRV3: area 2. Cac interface nhan moi truong OSPF = point-to-point
2.2. Cac Router nhan Loopback0 lam Router-ID
2.3. Cac interface cua cac Router xRV1,2,3 MTU = 9000.

3. Tai router vIOS, tao them cac interface Loopback10,11,12 voi IP = 172.16.x.1/32 (x=10,11,12) va dua cac interface nay vao OSPF.
Kiem tra bang route OSPF tai cac router con lai va dua ra nhan xet.

4. Tai router xRV1, thuc hien cau hinh sao cho router xRV2 chi hoc duoc route 1.1.1.1/32 trong area 0.

5. Thuc hien dua area 2 thanh Totally NSSA area, dua ra nhan xet sau khi dieu chinh.
```

**xrv1**
```
conf
!
host xrv1
!
! @@@@@@@@@ 1. Thiet lap IP dau noi va Loopback IP cho cac Router theo hinh ve tren
int lo0
  ipv4 addr 1.1.1.2/32
!
int g0/0/0/0
  no shut
  ipv4 addr 10.1.1.1/30
!
int g0/0/0/1
  no shut
  ipv4 addr 10.1.2.1/30
!
int g0/0/0/2
  no shut
  ipv4 addr 10.1.3.1/30
!
! @@@@@@@@@ 2. Xay dung OSPF neighbor giua cac Router dap ung cac dieu kien sau:
! 2.1. vIOS-xRV1: area0, xRV1-xRV2: area 1, xRV1-xRV3: area 2. Cac interface nhan moi truong OSPF = point-to-point
! 2.2. Cac Router nhan Loopback0 lam Router-ID
! 2.3. Cac interface cua cac Router xRV1,2,3 MTU = 9000.
router ospf 1
  router-id 1.1.1.2
  area 0
    network point-to-point
    interface lo0
      exit
    interface gi0/0/0/0
      exit
  area 1
    network point-to-point
    interface gi0/0/0/1
      exit
  area 2
    network point-to-point
    interface gi0/0/0/2
      exit
root
!
int g0/0/0/0
  mtu 9000
int g0/0/0/1
  mtu 9000
int g0/0/0/2
  mtu 9000
!
! @@@@@@@@@ 4. Tai router xRV1, thuc hien cau hinh sao cho router xRV2 chi hoc duoc route 1.1.1.1/32 trong area 0.
route-policy permit-lo0-vIOS
  if destination in (1.1.1.1/32) then
    pass
  else
    drop
  endif
end-policy
!
router ospf 1
  area 1
    route-policy permit-lo0-vIOS in
root
!
! @@@@@@@@@ 5. Thuc hien dua area 2 thanh Totally NSSA area, dua ra nhan xet sau khi dieu chinh.
router ospf 1
  area 2
    nssa no-summary
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
! @@@@@@@@@ 1. Thiet lap IP dau noi va Loopback IP cho cac Router theo hinh ve tren
int lo0
  ipv4 addr 1.1.1.3/32
!
int g0/0/0/1
  no shut
  ipv4 addr 10.1.2.2/30
!
! @@@@@@@@@ 2. Xay dung OSPF neighbor giua cac Router dap ung cac dieu kien sau:
! 2.1. vIOS-xRV1: area0, xRV1-xRV2: area 1, xRV1-xRV3: area 2. Cac interface nhan moi truong OSPF = point-to-point
! 2.2. Cac Router nhan Loopback0 lam Router-ID
! 2.3. Cac interface cua cac Router xRV1,2,3 MTU = 9000.
router ospf 1
  router-id 1.1.1.3
  area 1
    network point-to-point
    interface lo0
      exit
    interface gi0/0/0/1
      exit
root
!
int g0/0/0/1
  mtu 9000
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
! @@@@@@@@@ 1. Thiet lap IP dau noi va Loopback IP cho cac Router theo hinh ve tren
int lo0
  ipv4 addr 1.1.1.4/32
!
int g0/0/0/2
  no shut
  ipv4 addr 10.1.3.2/30
!
! @@@@@@@@@ 2. Xay dung OSPF neighbor giua cac Router dap ung cac dieu kien sau:
! 2.1. vIOS-xRV1: area0, xRV1-xRV2: area 1, xRV1-xRV3: area 2. Cac interface nhan moi truong OSPF = point-to-point
! 2.2. Cac Router nhan Loopback0 lam Router-ID
! 2.3. Cac interface cua cac Router xRV1,2,3 MTU = 9000.
router ospf 1
  router-id 1.1.1.4
  area 2
    network point-to-point
    interface lo0
      exit
    interface gi0/0/0/2
      exit
root
!
int g0/0/0/2
  mtu 9000
!
! @@@@@@@@@ 5. Thuc hien dua area 2 thanh Totally NSSA area, dua ra nhan xet sau khi dieu chinh.
router ospf 1
  area 2
    nssa no-summary
root
!
commit
end
```

**vIOS**
```
enable
conf t
!
no ip domain-lookup
host vIOS
!
! @@@@@@@@@ 1. Thiet lap IP dau noi va Loopback IP cho cac Router theo hinh ve tren
int Loopback0
  ip addr 1.1.1.1 255.255.255.255
!
int g0/0
  no shut
  ip addr 10.1.1.2 255.255.255.252
!
! @@@@@@@@@ 2. Xay dung OSPF neighbor giua cac Router dap ung cac dieu kien sau:
! @@@ 2.1. vIOS-xRV1: area0, xRV1-xRV2: area 1, xRV1-xRV3: area 2. Cac interface nhan moi truong OSPF = point-to-point
! @@@ 2.2. Cac Router nhan Loopback0 lam Router-ID
! @@@ 2.3. Cac interface cua cac Router xRV1,2,3 MTU = 9000.
int Loopback0
  ip ospf 1 area 0
!
int g0/0
  mtu 8986
  ip ospf 1 area 0
  ip ospf network point-to-point
!
! @@@@@@@@@ 3. Tai router vIOS, tao them cac interface Loopback10,11,12 voi IP = 172.16.x.1/32 (x=10,11,12) va dua cac interface nay vao OSPF.
! @@@ Kiem tra bang route OSPF tai cac router con lai va dua ra nhan xet.
int Loopback10
  ip addr 172.16.10.1 255.255.255.255
  ip ospf 1 area 0
int Loopback20
  ip addr 172.16.20.1 255.255.255.255
  ip ospf 1 area 0
int Loopback30
  ip addr 172.16.30.1 255.255.255.255
  ip ospf 1 area 0
!
end
write
```

