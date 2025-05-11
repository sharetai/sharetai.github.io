---
layout: default
title: STP RSTP PVST MST
nav_order: 60
parent: CCNP
---

# Spanning Tree Protocol 802.1d
{: .no_toc }

Giao thức Cây Mở Rộng 802.1d
{: .fs-6 .fw-300 }

---

## TABLE OF CONTENTS
{: .no_toc .text-delta }

1. TOC
{:toc}

---

## [\<Cheat sheet\>](/docs/CCNP/img/STP.png)
<br>

## Trạng thái cổng trong STP
<br>
__Disabled:__ Khoá port. <br>
__Blocking:__ Nhận BPDU, không gửi BPDU, không học MAC, không chuyển tiếp frame ___(20 giây)___. <br>
__Listening:__ Nhận BPDU, gửi BPDU, không học MAC, không chuyển tiếp frame ___(15 giây)___. <br>
__Learning:__ Nhận BPDU, gửi BPDU, học MAC, không chuyển tiếp frame ___(15 giây)___. <br>
__Forwarding:__ Nhận BPDU, gửi BPDU, học MAC, chuyển tiếp frame. <br>

## STP Topology Change
<br>
Những thay đổi trong STP Topology có thể được kiểm tra bằng lệnh:
```
show spanning-tree summary
show spanning-tree [vlan vlan-id] [detail]
```

Các sự cố liên quan đến thay đổi cấu trúc STP Topology bao gồm mất nguồn điện, thiết bị khởi động lại và bất kỳ nguyên nhân nào khiến cổng mạng ngừng hoạt động. STP có thể phản ứng theo ba cách khác nhau, tùy thuộc vào tình huống:

<u>Tình huống 1</u>

Có ba switch được kết nối, Switch1 là _Root bridge_. Link giữa Switch2 và Switch3 bị fail. _Designated port_ là Gi1/3 trên Switch2, và _Blocked port_ là Gi1/2 trên Switch3. Sẽ không có ảnh hưởng đến cấu trúc mạng vì cổng Gi1/2 của Switch3 đã bị block. Switch2 và Switch3 sẽ gửi một ___TCN (Topology Change Notification)___ đến root switch, clear bảng địa chỉ MAC của lớp 2.

<u>Tình huống 2</u>

Link giữa Switch1 và Switch3 bị fail. Cổng Gi1/2 của Switch3 bị block, gây cản trở lưu lượng truy cập từ Switch1 và Switch2 sang Switch3.

<image src="/docs/CCNP/img/stp-link-sw1-sw3-fail.png" width="40%"/>

Quá trình hội tụ:

1\. Switch1 và Switch3 phát hiện link fail. <br>
2\. Switch1 do là _root bridge_ nên không tạo _TCN_. Switch1 _flood_ đi ___Configuration BPDU___ với cờ ___TC flag (Topology Change flag)___ đến tất cả cổng _designated port_. <br>
3\. Switch3 ___disable___ port Gi1/1. Chuyển port Gi1/2 sang ___listening___. Tạo _TCN_ gửi đến _root bridge_ thông qua _root port_ (nhưng bị fail do _root port_ down). <br>
4\. Switch2 và Switch3 nhận _Configuration BPDU_ với cờ _TC_ từ _root bridge_. _Clear_ bảng mac. <br>
5\. Switch3 chờ ___15s___ chuyển port Gi1/2 sang ___learning___ và chờ thêm ___15s___ tiếp theo chuyển port Gi1/2 sang ___forwarding___. Tổng ___30s___. <br>

<u>Tình huống 3</u>

Link giữa Switch1 và Switch2 bị fail. Cổng Gi1/2 của Switch3 bị block, gây cản trở lưu lượng truy cập từ Switch1 và Switch3 sang Switch2.

<image src="/docs/CCNP/img/stp-link-sw1-sw2-fail.png" width="40%"/>

Quá trình hội tụ:

1\. Switch1 và Switch2 phát hiện link fail. <br>
2\. Switch1 do là _root bridge_ nên không tạo _TCN_. Switch1 _flood_ đi ___Configuration BPDU___ với cờ ___TC___ đến tất cả cổng _designated port_. <br>
3\. Switch2 ___disable___ port Gi1/1. Switch2 xem như _root bridge_ đã chết, tự xem mình là _root_ và _flood_ đi ___Configuration BPDU___. 
4\. Switch3 nhận _Configuration BPDU_ với cờ _TC_ từ Switch1. Clear bảng mac. Switch3 cũng nhận _Configuration BPDU_ với cờ _TC_ từ Switch2, nhưng do so sánh kém hơn Switch1, loại bỏ. Switch3 muốn chuyển tiếp _Configuration BPDU_ cho Switch2 thông báo Switch1 còn sống, nhưng không thể do cổng Gi1/2 của Switch3 bị _block_. <br>
5\. Switch3 chờ ___20s___ _Max Age_ của Switch2, không nhận được _Configuration BPDU_ của Switch1 từ Switch2, chuyển port Gi1/2 sang ___learning___ và chờ thêm ___15s___ tiếp theo chuyển port Gi1/2 sang ___forwarding___. Tổng ___50s___. <br>

## STP Topology Change (lab)
<br>

![alt text](/docs/CCNP/img/stp-topology-change.png)

__<u>Init</u>__

* __S1__
```
enable
conf t
host S1
no ip domain-lookup
spanning-tree mode pvst
end
wr
debug spanning-tree config
debug spanning-tree events
debug spanning-tree general
```

* __S2__
```
enable
conf t
host S2
no ip domain-lookup
spanning-tree mode pvst
end
wr
debug spanning-tree config
debug spanning-tree events
debug spanning-tree general
```

* __S3__
```
enable
conf t
host S3
no ip domain-lookup
spanning-tree mode pvst
end
wr
debug spanning-tree config
debug spanning-tree events
debug spanning-tree general
```

__<u>Tình huống 2 Link giữa S1 và S3 bị fail</u>__

```
S3#sh spanning-tree summary
Switch is in pvst mode
Root bridge for: none
Extended system ID                      is enabled
Portfast Default                        is disabled
Portfast Edge BPDU Guard Default        is disabled
Portfast Edge BPDU Filter Default       is disabled
Loopguard Default                       is disabled
PVST Simulation Default                 is enabled but inactive in pvst mode
Bridge Assurance                        is enabled but inactive in pvst mode
EtherChannel misconfig guard            is enabled
Configured Pathcost method used is short
UplinkFast                              is disabled
BackboneFast                            is disabled

Name                   Blocking Listening Learning Forwarding STP Active
---------------------- -------- --------- -------- ---------- ----------
VLAN0001                     1         0        0          3          4
---------------------- -------- --------- -------- ---------- ----------
1 vlan                       1         0        0          3          4
S3#sh spanning-tree vlan 1

VLAN0001
  Spanning tree enabled protocol ieee
  Root ID    Priority    32769
             Address     aabb.cc00.1000
             Cost        100
             Port        2 (Ethernet0/1)
             Hello Time   2 sec  Max Age 20 sec  Forward Delay 15 sec

  Bridge ID  Priority    32769  (priority 32768 sys-id-ext 1)
             Address     aabb.cc00.3000
             Hello Time   2 sec  Max Age 20 sec  Forward Delay 15 sec
             Aging Time  15  sec

Interface           Role Sts Cost      Prio.Nbr Type
------------------- ---- --- --------- -------- --------------------------------
Et0/0               Desg FWD 100       128.1    P2p
Et0/1               Root FWD 100       128.2    P2p
Et0/2               Altn BLK 100       128.3    P2p
Et0/3               Desg FWD 100       128.4    P2p


S3#sh mac address-table
          Mac Address Table
-------------------------------------------

Vlan    Mac Address       Type        Ports
----    -----------       --------    -----
   1    aabb.cc00.1030    DYNAMIC     Et0/1
   1    aabb.cc00.2010    DYNAMIC     Et0/1
   1    aabb.cc00.3020    DYNAMIC     Et0/1
Total Mac Addresses for this criterion: 3
S3#en
S3#conf t
Enter configuration commands, one per line.  End with CNTL/Z.
S3(config)#int e0/1
S3(config-if)#shutdown
S3(config-if)#end
S3#
*Sep 22 04:42:14.743: Returning spanning tree stats for VLAN0001 (C0F5FE58)
*Sep 22 04:42:14.743: Returning spanning tree stats for VLAN0001 (C0F5FE58)
*Sep 22 04:42:14.752: Returning spanning tree stats for VLAN0001 (C0F5FE58)
*Sep 22 04:42:14.752: Returning spanning tree port stats: Ethernet0/0 (C102D278)
*Sep 22 04:42:14.752: Returning spanning tree port stats: Ethernet0/1 (C102D410)
*Sep 22 04:42:14.752: Returning spanning tree port stats: Ethernet0/2 (C102D5A8)
*Sep 22 04:42:14.752: Returning spanning tree port stats: Ethernet0/3 (C102D740)
*Sep 22 04:42:14.767: Disabling spanning tree port: Ethernet0/1 (C102D410)
*Sep 22 04:42:14.767: STP: VLAN0001 new root port Et0/2, cost 200
*Sep 22 04:42:14.767: STP: VLAN0001 Et0/2 -> listening
*Sep 22 04:42:14.767: STP[1]: Generating TC trap for port Ethernet0/1
*Sep 22 04:42:14.767: Deleting spanning tree port: Et0/1 (C102D410)
*Sep 22 04:42:14.767: STP PVST: deleted vlan 1 intf C09521F0
S3#
*Sep 22 04:42:14.767: %SYS-5-CONFIG_I: Configured from console by console
S3#
*Sep 22 04:42:16.773: %LINK-5-CHANGED: Interface Ethernet0/1, changed state to administratively down
S3#
*Sep 22 04:42:16.773: STP: VLAN0001 sent Topology Change Notice on Et0/2
*Sep 22 04:42:17.778: %LINEPROTO-5-UPDOWN: Line protocol on Interface Ethernet0/1, changed state to down
S3#sh mac address-table
          Mac Address Table
-------------------------------------------

Vlan    Mac Address       Type        Ports
----    -----------       --------    -----
S3#
*Sep 22 04:42:29.769: STP: VLAN0001 Et0/2 -> learning
S3#
*Sep 22 04:42:44.773: STP[1]: Generating TC trap for port Ethernet0/2
*Sep 22 04:42:44.774: STP: VLAN0001 sent Topology Change Notice on Et0/2
*Sep 22 04:42:44.774: STP: VLAN0001 Et0/2 -> forwarding
S3#sh spanning-tree summary
Switch is in pvst mode
Root bridge for: none
Extended system ID                      is enabled
Portfast Default                        is disabled
Portfast Edge BPDU Guard Default        is disabled
Portfast Edge BPDU Filter Default       is disabled
Loopguard Default                       is disabled
PVST Simulation Default                 is enabled but inactive in pvst mode
Bridge Assurance                        is enabled but inactive in pvst mode
EtherChannel misconfig guard            is enabled
Configured Pathcost method used is short
UplinkFast                              is disabled
BackboneFast                            is disabled

Name                   Blocking Listening Learning Forwarding STP Active
---------------------- -------- --------- -------- ---------- ----------
VLAN0001                     0         0        0          3          3
---------------------- -------- --------- -------- ---------- ----------
1 vlan                       0         0        0          3          3
S3#sh spanning-tree vlan 1

VLAN0001
  Spanning tree enabled protocol ieee
  Root ID    Priority    32769
             Address     aabb.cc00.1000
             Cost        200
             Port        3 (Ethernet0/2)
             Hello Time   2 sec  Max Age 20 sec  Forward Delay 15 sec

  Bridge ID  Priority    32769  (priority 32768 sys-id-ext 1)
             Address     aabb.cc00.3000
             Hello Time   2 sec  Max Age 20 sec  Forward Delay 15 sec
             Aging Time  300 sec

Interface           Role Sts Cost      Prio.Nbr Type
------------------- ---- --- --------- -------- --------------------------------
Et0/0               Desg FWD 100       128.1    P2p
Et0/2               Root FWD 100       128.3    P2p
Et0/3               Desg FWD 100       128.4    P2p


S3#sh mac address-table
          Mac Address Table
-------------------------------------------

Vlan    Mac Address       Type        Ports
----    -----------       --------    -----
   1    aabb.cc00.1020    DYNAMIC     Et0/2
   1    aabb.cc00.2030    DYNAMIC     Et0/2
Total Mac Addresses for this criterion: 2
S3#
```

__<u>Tình huống 3 Link giữa S1 và S2 bị fail</u>__

```
S2#sh spanning-tree summary
Switch is in pvst mode
Root bridge for: none
Extended system ID                      is enabled
Portfast Default                        is disabled
Portfast Edge BPDU Guard Default        is disabled
Portfast Edge BPDU Filter Default       is disabled
Loopguard Default                       is disabled
PVST Simulation Default                 is enabled but inactive in pvst mode
Bridge Assurance                        is enabled but inactive in pvst mode
EtherChannel misconfig guard            is enabled
Configured Pathcost method used is short
UplinkFast                              is disabled
BackboneFast                            is disabled

Name                   Blocking Listening Learning Forwarding STP Active
---------------------- -------- --------- -------- ---------- ----------
VLAN0001                     0         0        0          4          4
---------------------- -------- --------- -------- ---------- ----------
1 vlan                       0         0        0          4          4
S2#sh spanning-tree vlan 1

VLAN0001
  Spanning tree enabled protocol ieee
  Root ID    Priority    32769
             Address     aabb.cc00.1000
             Cost        100
             Port        2 (Ethernet0/1)
             Hello Time   2 sec  Max Age 20 sec  Forward Delay 15 sec

  Bridge ID  Priority    32769  (priority 32768 sys-id-ext 1)
             Address     aabb.cc00.2000
             Hello Time   2 sec  Max Age 20 sec  Forward Delay 15 sec
             Aging Time  15  sec

Interface           Role Sts Cost      Prio.Nbr Type
------------------- ---- --- --------- -------- --------------------------------
Et0/0               Desg FWD 100       128.1    P2p
Et0/1               Root FWD 100       128.2    P2p
Et0/2               Desg FWD 100       128.3    P2p
Et0/3               Desg FWD 100       128.4    P2p


S2#sh mac address-table
          Mac Address Table
-------------------------------------------

Vlan    Mac Address       Type        Ports
----    -----------       --------    -----
   1    aabb.cc00.1020    DYNAMIC     Et0/1
   1    aabb.cc00.3010    DYNAMIC     Et0/1
   1    aabb.cc00.3020    DYNAMIC     Et0/3
Total Mac Addresses for this criterion: 3
S2#
*Sep 22 05:38:04.842: Returning spanning tree stats for VLAN0001 (C0F73E58)
*Sep 22 05:38:04.842: Returning spanning tree stats for VLAN0001 (C0F73E58)
*Sep 22 05:38:04.858: Returning spanning tree stats for VLAN0001 (C0F73E58)
*Sep 22 05:38:04.858: Returning spanning tree port stats: Ethernet0/0 (C1041278)
*Sep 22 05:38:04.858: Returning spanning tree port stats: Ethernet0/1 (C1041410)
*Sep 22 05:38:04.858: Returning spanning tree port stats: Ethernet0/2 (C10415A8)
*Sep 22 05:38:04.858: Returning spanning tree port stats: Ethernet0/3 (C1041740)
S2#en
S2#conf t
Enter configuration commands, one per line.  End with CNTL/Z.
S2(config)#int e0/1
S2(config-if)#shutdown
S2(config-if)#end
S2#
*Sep 22 05:38:21.666: Disabling spanning tree port: Ethernet0/1 (C1041410)
*Sep 22 05:38:21.667: Deleting spanning tree port: Et0/1 (C1041410)
*Sep 22 05:38:21.667: STP PVST: deleted vlan 1 intf C09661F0
S2#
*Sep 22 05:38:21.668: %SYS-5-CONFIG_I: Configured from console by console
S2#
*Sep 22 05:38:23.670: %LINK-5-CHANGED: Interface Ethernet0/1, changed state to administratively down
*Sep 22 05:38:24.670: %LINEPROTO-5-UPDOWN: Line protocol on Interface Ethernet0/1, changed state to down
S2#sh mac address-table
          Mac Address Table
-------------------------------------------

Vlan    Mac Address       Type        Ports
----    -----------       --------    -----
S2#
*Sep 22 05:38:41.551: STP: VLAN0001 heard root 32769-aabb.cc00.1000 on Et0/3
*Sep 22 05:38:41.551:     supersedes 32769-aabb.cc00.2000
*Sep 22 05:38:41.551: STP: VLAN0001 new root is 32769, aabb.cc00.1000 on port Et0/3, cost 200
*Sep 22 05:38:41.551: STP: VLAN0001 sent Topology Change Notice on Et0/3
S2#sh mac address-table
          Mac Address Table
-------------------------------------------

Vlan    Mac Address       Type        Ports
----    -----------       --------    -----
   1    aabb.cc00.1030    DYNAMIC     Et0/3
   1    aabb.cc00.3020    DYNAMIC     Et0/3
Total Mac Addresses for this criterion: 2
S2#


S3#sh spanning-tree summary
Switch is in pvst mode
Root bridge for: none
Extended system ID                      is enabled
Portfast Default                        is disabled
Portfast Edge BPDU Guard Default        is disabled
Portfast Edge BPDU Filter Default       is disabled
Loopguard Default                       is disabled
PVST Simulation Default                 is enabled but inactive in pvst mode
Bridge Assurance                        is enabled but inactive in pvst mode
EtherChannel misconfig guard            is enabled
Configured Pathcost method used is short
UplinkFast                              is disabled
BackboneFast                            is disabled

Name                   Blocking Listening Learning Forwarding STP Active
---------------------- -------- --------- -------- ---------- ----------
VLAN0001                     1         0        0          3          4
---------------------- -------- --------- -------- ---------- ----------
1 vlan                       1         0        0          3          4
S3#sh spanning-tree vlan 1

VLAN0001
  Spanning tree enabled protocol ieee
  Root ID    Priority    32769
             Address     aabb.cc00.1000
             Cost        100
             Port        2 (Ethernet0/1)
             Hello Time   2 sec  Max Age 20 sec  Forward Delay 15 sec

  Bridge ID  Priority    32769  (priority 32768 sys-id-ext 1)
             Address     aabb.cc00.3000
             Hello Time   2 sec  Max Age 20 sec  Forward Delay 15 sec
             Aging Time  15  sec

Interface           Role Sts Cost      Prio.Nbr Type
------------------- ---- --- --------- -------- --------------------------------
Et0/0               Desg FWD 100       128.1    P2p
Et0/1               Root FWD 100       128.2    P2p
Et0/2               Altn BLK 100       128.3    P2p
Et0/3               Desg FWD 100       128.4    P2p


S3#sh mac address-table
          Mac Address Table
-------------------------------------------

Vlan    Mac Address       Type        Ports
----    -----------       --------    -----
   1    aabb.cc00.1030    DYNAMIC     Et0/1
   1    aabb.cc00.2010    DYNAMIC     Et0/1
   1    aabb.cc00.3020    DYNAMIC     Et0/1
Total Mac Addresses for this criterion: 3
S3#
*Sep 22 05:38:08.938: Returning spanning tree stats for VLAN0001 (C1002E58)
*Sep 22 05:38:08.938: Returning spanning tree stats for VLAN0001 (C1002E58)
*Sep 22 05:38:08.948: Returning spanning tree stats for VLAN0001 (C1002E58)
*Sep 22 05:38:08.948: Returning spanning tree port stats: Ethernet0/0 (C10D0278)
*Sep 22 05:38:08.948: Returning spanning tree port stats: Ethernet0/1 (C10D0410)
*Sep 22 05:38:08.948: Returning spanning tree port stats: Ethernet0/2 (C10D05A8)
*Sep 22 05:38:08.948: Returning spanning tree port stats: Ethernet0/3 (C10D0740)
S3#
*Sep 22 05:38:22.520: STP: VLAN0001 heard root 32769-aabb.cc00.2000 on Et0/2
S3#
*Sep 22 05:38:23.670: STP: VLAN0001 heard root 32769-aabb.cc00.2000 on Et0/2
S3#
*Sep 22 05:38:25.676: STP: VLAN0001 heard root 32769-aabb.cc00.2000 on Et0/2
S3#
*Sep 22 05:38:27.684: STP: VLAN0001 heard root 32769-aabb.cc00.2000 on Et0/2
S3#
*Sep 22 05:38:29.689: STP: VLAN0001 heard root 32769-aabb.cc00.2000 on Et0/2
S3#
*Sep 22 05:38:31.694: STP: VLAN0001 heard root 32769-aabb.cc00.2000 on Et0/2
S3#
*Sep 22 05:38:33.698: STP: VLAN0001 heard root 32769-aabb.cc00.2000 on Et0/2
S3#
*Sep 22 05:38:35.707: STP: VLAN0001 heard root 32769-aabb.cc00.2000 on Et0/2
S3#
*Sep 22 05:38:37.711: STP: VLAN0001 heard root 32769-aabb.cc00.2000 on Et0/2
S3#
*Sep 22 05:38:39.717: STP: VLAN0001 heard root 32769-aabb.cc00.2000 on Et0/2
*Sep 22 05:38:40.526: STP: VLAN0001 Et0/2 -> listening
S3#
*Sep 22 05:38:41.551: STP: VLAN0001 Topology Change rcvd on Et0/2
*Sep 22 05:38:41.552: STP: VLAN0001 sent Topology Change Notice on Et0/1
S3#sh mac address-table
          Mac Address Table
-------------------------------------------

Vlan    Mac Address       Type        Ports
----    -----------       --------    -----
   1    aabb.cc00.1030    DYNAMIC     Et0/1
Total Mac Addresses for this criterion: 1
S3#
*Sep 22 05:38:55.527: STP: VLAN0001 Et0/2 -> learning
S3#
*Sep 22 05:39:10.527: STP[1]: Generating TC trap for port Ethernet0/2
*Sep 22 05:39:10.527: STP: VLAN0001 sent Topology Change Notice on Et0/1
*Sep 22 05:39:10.527: STP: VLAN0001 Et0/2 -> forwarding
S3#sh spanning-tree summary
Switch is in pvst mode
Root bridge for: none
Extended system ID                      is enabled
Portfast Default                        is disabled
Portfast Edge BPDU Guard Default        is disabled
Portfast Edge BPDU Filter Default       is disabled
Loopguard Default                       is disabled
PVST Simulation Default                 is enabled but inactive in pvst mode
Bridge Assurance                        is enabled but inactive in pvst mode
EtherChannel misconfig guard            is enabled
Configured Pathcost method used is short
UplinkFast                              is disabled
BackboneFast                            is disabled

Name                   Blocking Listening Learning Forwarding STP Active
---------------------- -------- --------- -------- ---------- ----------
VLAN0001                     0         0        0          4          4
---------------------- -------- --------- -------- ---------- ----------
1 vlan                       0         0        0          4          4
S3#sh spanning-tree vlan 1

VLAN0001
  Spanning tree enabled protocol ieee
  Root ID    Priority    32769
             Address     aabb.cc00.1000
             Cost        100
             Port        2 (Ethernet0/1)
             Hello Time   2 sec  Max Age 20 sec  Forward Delay 15 sec

  Bridge ID  Priority    32769  (priority 32768 sys-id-ext 1)
             Address     aabb.cc00.3000
             Hello Time   2 sec  Max Age 20 sec  Forward Delay 15 sec
             Aging Time  15  sec

Interface           Role Sts Cost      Prio.Nbr Type
------------------- ---- --- --------- -------- --------------------------------
Et0/0               Desg FWD 100       128.1    P2p
Et0/1               Root FWD 100       128.2    P2p
Et0/2               Desg FWD 100       128.3    P2p
Et0/3               Desg FWD 100       128.4    P2p


S3#sh mac address-table
          Mac Address Table
-------------------------------------------

Vlan    Mac Address       Type        Ports
----    -----------       --------    -----
   1    aabb.cc00.1030    DYNAMIC     Et0/1
   1    aabb.cc00.2030    DYNAMIC     Et0/2
Total Mac Addresses for this criterion: 2
S3#
```

## Những cải tiến của STP
<br>
![alt text](/docs/CCNP/img/stp-evolution.png)

### STP Portfast, Uplinkfast, Backbonefast (lab)
<br>
STP có thể gây ra độ trễ đáng kể trong quá trình hội tụ mạng, đặc biệt khi có sự thay đổi trong topology. Để giải quyết vấn đề này, ở những giai đoạn đầu, Cisco đã giới thiệu các tính năng mở rộng của STP như Portfast, Uplinkfast và Backbonefast.

__Portfast__

___- Mục đích:___ Giảm thời gian hội tụ khi kết nối các thiết bị cuối (end-devices) như máy tính, máy in vào switch. <br>
___- Hoạt động:___ Khi một cổng được cấu hình Portfast, cổng đó sẽ lập tức chuyển sang trạng thái forwarding ngay khi được kết nối, bỏ qua các trạng thái listening và learning. Điều này giúp rút ngắn đáng kể thời gian chờ đợi. <br>
___- Lưu ý:___ Chỉ sử dụng Portfast trên các cổng kết nối với các thiết bị cuối. Nếu sử dụng Portfast trên các cổng kết nối giữa các switch, có thể gây ra loop. <br>

__Uplinkfast__

___- Mục đích:___ Giảm thời gian hội tụ khi đường uplink bị lỗi. <br>
___- Hoạt động:___ UplinkFast được định nghĩa 1 nhóm các đường iplink, gọi là uplink group. Với mỗi 1 switch, uplink group bao gồm root port và tất cả các cổng cung cấp kết nối thay thế đến root bridge. Nếu root port bị lỗi, cổng có chi phí thấp nhất tiếp theo trong uplink group sẽ được chọn để thay thế ngay lập tức, bỏ qua các trạng thái listening và learning, qua đó giảm thời gian hội tụ của STP xuống còn khoảng 1 giây. Giảm được 30 giây _(xem STP Topology Change Tình huống 2)_.<br>
___- Lưu ý:___ Uplinkfast thường được sử dụng trên các access switch (switch đấu nối với các thiết bị cuối). <br>

__Backbonefast__

___- Mục đích:___ Giảm thời gian hội tụ trong trường hợp liên kết gián tiếp bị lỗi, nghĩa là liên kết trên 1 switch khác, không phải các link kết nối trực tiếp với switch đó. <br>
___- Hoạt động:___ Backbonefast sẽ bỏ qua 20 giây max age, block port sẽ chuyển lần lượt sang trạng thái listening, learning và forwarding. Tổng là 30 giây thay vì 50 giây _(xem STP Topology Change Tình huống 3)_. <br>
___- Lưu ý:___ Backbonefast nên được sử dụng trên tất cả các switch. <br>

__Portfast (lab)__

```
S3>show clock
*08:09:56.367 UTC Sun Sep 22 2024
S3>show spanning-tree vlan 1

VLAN0001
  Spanning tree enabled protocol ieee
  Root ID    Priority    32769
             Address     aabb.cc00.1000
             Cost        100
             Port        2 (Ethernet0/1)
             Hello Time   2 sec  Max Age 20 sec  Forward Delay 15 sec

  Bridge ID  Priority    32769  (priority 32768 sys-id-ext 1)
             Address     aabb.cc00.3000
             Hello Time   2 sec  Max Age 20 sec  Forward Delay 15 sec
             Aging Time  15  sec

Interface           Role Sts Cost      Prio.Nbr Type
------------------- ---- --- --------- -------- --------------------------------
Et0/0               Desg FWD 100       128.1    P2p
Et0/1               Root FWD 100       128.2    P2p
Et0/2               Altn BLK 100       128.3    P2p
Et0/3               Desg FWD 100       128.4    P2p


S3>en
S3#conf t
Enter configuration commands, one per line.  End with CNTL/Z.
S3(config)#int e0/3
S3(config-if)#spanning-tree portfast
%Warning: portfast should only be enabled on ports connected to a single
 host. Connecting hubs, concentrators, switches, bridges, etc... to this
 interface  when portfast is enabled, can cause temporary bridging loops.
 Use with CAUTION

%Portfast has been configured on Ethernet0/3 but will only
 have effect when the interface is in a non-trunking mode.
S3(config-if)#shut
S3(config-if)#no shut
S3(config-if)#end
S3#
*Sep 22 08:09:56.390: %SYS-5-CONFIG_I: Configured from console by console
S3#show clock
*08:09:57.944 UTC Sun Sep 22 2024
S3#show spanning-tree vlan 1

VLAN0001
  Spanning tree enabled protocol ieee
  Root ID    Priority    32769
             Address     aabb.cc00.1000
             Cost        100
             Port        2 (Ethernet0/1)
             Hello Time   2 sec  Max Age 20 sec  Forward Delay 15 sec

  Bridge ID  Priority    32769  (priority 32768 sys-id-ext 1)
             Address     aabb.cc00.3000
             Hello Time   2 sec  Max Age 20 sec  Forward Delay 15 sec
             Aging Time  15  sec

Interface           Role Sts Cost      Prio.Nbr Type
------------------- ---- --- --------- -------- --------------------------------
Et0/0               Desg FWD 100       128.1    P2p
Et0/1               Root FWD 100       128.2    P2p
Et0/2               Altn BLK 100       128.3    P2p
Et0/3               Desg FWD 100       128.4    P2p Edge


S3#
```

__Uplinkfast (lab)__

```
S3#conf t
Enter configuration commands, one per line.  End with CNTL/Z.
S3(config)#spanning-tree uplinkfast
S3(config)#end
S3#sh spanning-tree summary | sec abled
Extended system ID                      is enabled
Portfast Default                        is disabled
Portfast Edge BPDU Guard Default        is disabled
Portfast Edge BPDU Filter Default       is disabled
Loopguard Default                       is disabled
PVST Simulation Default                 is enabled but inactive in pvst mode
Bridge Assurance                        is enabled but inactive in pvst mode
EtherChannel misconfig guard            is enabled
UplinkFast                              is enabled
BackboneFast                            is disabled
S3#sh clock
*08:17:33.800 UTC Sun Sep 22 2024
S3#sh spanning-tree vlan 1

VLAN0001
  Spanning tree enabled protocol ieee
  Root ID    Priority    32769
             Address     aabb.cc00.1000
             Cost        3100
             Port        2 (Ethernet0/1)
             Hello Time   2 sec  Max Age 20 sec  Forward Delay 15 sec

  Bridge ID  Priority    49153  (priority 49152 sys-id-ext 1)
             Address     aabb.cc00.3000
             Hello Time   2 sec  Max Age 20 sec  Forward Delay 15 sec
             Aging Time  300 sec
  Uplinkfast enabled

Interface           Role Sts Cost      Prio.Nbr Type
------------------- ---- --- --------- -------- --------------------------------
Et0/0               Desg FWD 3100      128.1    P2p
Et0/1               Root FWD 3100      128.2    P2p
Et0/2               Altn BLK 3100      128.3    P2p
Et0/3               Desg FWD 3100      128.4    P2p Edge


S3#conf t
Enter configuration commands, one per line.  End with CNTL/Z.
S3(config)#int e0/1
S3(config-if)#shut
S3(config-if)#end
S3#
*Sep 22 08:17:33.811: %SPANTREE_FAST-7-PORT_FWD_UPLINK: VLAN0001 Ethernet0/2 moved to Forwarding (UplinkFast).
S3#sh clock
*08:17:35.519 UTC Sun Sep 22 2024
S3#sh spanning-tree vlan 1
*Sep 22 08:17:33.811: %SYS-5-CONFIG_I: Configured from console by console

VLAN0001
  Spanning tree enabled protocol ieee
  Root ID    Priority    32769
             Address     aabb.cc00.1000
             Cost        3200
             Port        3 (Ethernet0/2)
             Hello Time   2 sec  Max Age 20 sec  Forward Delay 15 sec

  Bridge ID  Priority    49153  (priority 49152 sys-id-ext 1)
             Address     aabb.cc00.3000
             Hello Time   2 sec  Max Age 20 sec  Forward Delay 15 sec
             Aging Time  300 sec
  Uplinkfast enabled

Interface           Role Sts Cost      Prio.Nbr Type
------------------- ---- --- --------- -------- --------------------------------
Et0/0               Desg FWD 3100      128.1    P2p
Et0/2               Root FWD 3100      128.3    P2p
Et0/3               Desg FWD 3100      128.4    P2p Edge


S3#
*Sep 22 08:17:35.815: %LINK-5-CHANGED: Interface Ethernet0/1, changed state to administratively down
*Sep 22 08:17:36.816: %LINEPROTO-5-UPDOWN: Line protocol on Interface Ethernet0/1, changed state to down
S3#
```

__Backbonefast (lab)__

```
S3#en
S3#conf t
Enter configuration commands, one per line.  End with CNTL/Z.
S3(config)#! CAU HINH CHO 3 SWITCH S1,S2,S3
S3(config)#spanning-tree backbonefast
S3(config)#end
S3#sh spanning-tree summary | sec abled
Extended system ID                      is enabled
Portfast Default                        is disabled
Portfast Edge BPDU Guard Default        is disabled
Portfast Edge BPDU Filter Default       is disabled
Loopguard Default                       is disabled
PVST Simulation Default                 is enabled but inactive in pvst mode
Bridge Assurance                        is enabled but inactive in pvst mode
EtherChannel misconfig guard            is enabled
UplinkFast                              is enabled
BackboneFast                            is enabled
S3#


S2#conf t
Enter configuration commands, one per line.  End with CNTL/Z.
S2(config)#int e0/1
S2(config-if)#shut
S2(config-if)#
*Sep 22 08:31:50.387: %LINK-5-CHANGED: Interface Ethernet0/1, changed state to administratively down
*Sep 22 08:31:51.392: %LINEPROTO-5-UPDOWN: Line protocol on Interface Ethernet0/1, changed state to down
S2(config-if)#


S3#sh clock
*08:31:47.885 UTC Sun Sep 22 2024
S3#sh spanning-tree vlan 1

VLAN0001
  Spanning tree enabled protocol ieee
  Root ID    Priority    32769
             Address     aabb.cc00.1000
             Cost        3100
             Port        2 (Ethernet0/1)
             Hello Time   2 sec  Max Age 20 sec  Forward Delay 15 sec

  Bridge ID  Priority    49153  (priority 49152 sys-id-ext 1)
             Address     aabb.cc00.3000
             Hello Time   2 sec  Max Age 20 sec  Forward Delay 15 sec
             Aging Time  15  sec
  Uplinkfast enabled

Interface           Role Sts Cost      Prio.Nbr Type
------------------- ---- --- --------- -------- --------------------------------
Et0/0               Desg FWD 3100      128.1    P2p
Et0/1               Root FWD 3100      128.2    P2p
Et0/2               Altn BLK 3100      128.3    P2p
Et0/3               Desg FWD 3100      128.4    P2p Edge


S3#sh clock
*08:31:49.050 UTC Sun Sep 22 2024
S3#sh spanning-tree vlan 1

VLAN0001
  Spanning tree enabled protocol ieee
  Root ID    Priority    32769
             Address     aabb.cc00.1000
             Cost        3100
             Port        2 (Ethernet0/1)
             Hello Time   2 sec  Max Age 20 sec  Forward Delay 15 sec

  Bridge ID  Priority    49153  (priority 49152 sys-id-ext 1)
             Address     aabb.cc00.3000
             Hello Time   2 sec  Max Age 20 sec  Forward Delay 15 sec
             Aging Time  15  sec
  Uplinkfast enabled

Interface           Role Sts Cost      Prio.Nbr Type
------------------- ---- --- --------- -------- --------------------------------
Et0/0               Desg FWD 3100      128.1    P2p
Et0/1               Root FWD 3100      128.2    P2p
Et0/2               Desg LIS 3100      128.3    P2p
Et0/3               Desg FWD 3100      128.4    P2p Edge


S3#
```

### STP BPDU guard, Root guard, Loop Guard, BPUD filter (lab)
<br>
Để tăng cường bảo mật và ổn định của mạng, STP cung cấp các tính năng bổ sung như BPDU Guard, Root Guard, Loop Guard, và BPDU Filter.

__BPDU Guard__

___- Mục đích:___ Ngăn chặn các thiết bị không được phép tham gia vào việc xây dựng cây cấu trúc. <br>
___- Hoạt động:___ Khi một cổng nhận được một BPDU không hợp lệ hoặc không mong muốn, BPDU Guard sẽ chuyển cổng đó sang trạng thái disabled, ngăn chặn việc truyền dữ liệu qua cổng. <br>
___- Ứng dụng:___ Thường được sử dụng trên các cổng kết nối với các thiết bị cuối như máy tính, máy in để ngăn chặn các cuộc tấn công. <br>

__Root Guard__

___- Mục đích:___ Ngăn chặn các thiết bị không được phép trở thành root bridge. <br>
___- Hoạt động:___ Khi một cổng nhận được một Superior BPDU, Root Guard sẽ chuyển cổng đó sang trạng thái root-inconsistent. <br>
___- Ứng dụng:___ Thường được sử dụng trên các cổng downlink xuống access switch. <br>

__Loop Guard__

___- Mục đích:___ Phát hiện và ngăn chặn các vòng lặp trong trường hợp STP chuyển nhầm từ trạng thái blocking sang forwarding. <br>
___- Hoạt động:___ Nếu cổng không nhận được BPDU thì nó sẽ chặn thay vì chuyển trạng thái. <br>
___- Ứng dụng:___ Thưởng sử dụng cho cổng bị block, tuy nhiên được sử dụng trên tất cả các cổng trên mạng để tăng cường tính ổn định và ngăn chặn các sự cố. Không sử dụng lên các cổng đang cấu hình root guard, vì loop guard sẽ vô hiệu hóa root guard<br>

__BPDU Filter__

___- Mục đích:___ Lọc các BPDU giữa 2 site. <br>
___- Hoạt động:___ BPDU Filter cấu hình bộ lọc ngăn chặn gửi, nhận và xử lý các BPDU. <br>
___- Ứng dụng:___ Sử dụng trong tình huống muốn ngăn bpdu truyền đi trong môi trường là L2 giữa 2 site. <br>

<br>
![Alt text](/docs/CCNA (old)/img/stp-Portfast-BPDU-Guard-Root-Guard.png)

![alt text](/docs/CCNP/img/stp-Portfast-BPDU-Guard-Root-Guard-lab.png)

__BPDU Guard (lab)__

```
S2#en
S2#conf t
Enter configuration commands, one per line.  End with CNTL/Z.
S2(config)#int e0/1
S2(config-if)#spanning-tree bpduguard enable
S2(config-if)#exit
S2(config)#errdisable recovery cause bpduguard
S2(config)#errdisable recovery interval 30
S2(config)#end
S2#
*Sep 22 11:40:37.278: %SYS-5-CONFIG_I: Configured from console by console
*Sep 22 11:40:38.513: %SPANTREE-2-BLOCK_BPDUGUARD: Received BPDU on port Et0/1 with BPDU Guard enabled. Disabling port.
S2#
*Sep 22 11:40:38.513: %PM-4-ERR_DISABLE: bpduguard error detected on Et0/1, putting Et0/1 in err-disable state
*Sep 22 11:40:39.514: %LINEPROTO-5-UPDOWN: Line protocol on Interface Ethernet0/1, changed state to down
S2#
*Sep 22 11:40:40.518: %LINK-3-UPDOWN: Interface Ethernet0/1, changed state to down
S2#sh int e0/1 | i line pro
Ethernet0/1 is down, line protocol is down (err-disabled)
S2#sh errdisable recovery
ErrDisable Reason            Timer Status
-----------------            --------------
arp-inspection               Disabled
bpduguard                    Enabled
channel-misconfig (STP)      Disabled
dhcp-rate-limit              Disabled
dtp-flap                     Disabled
gbic-invalid                 Disabled
inline-power                 Disabled
l2ptguard                    Disabled
link-flap                    Disabled
mac-limit                    Disabled
link-monitor-failure         Disabled
loopback                     Disabled
oam-remote-failure           Disabled
pagp-flap                    Disabled
port-mode-failure            Disabled
pppoe-ia-rate-limit          Disabled
psecure-violation            Disabled
security-violation           Disabled
sfp-config-mismatch          Disabled
storm-control                Disabled
udld                         Disabled

Interface       Errdisable reason       Time left(sec)
---------       -----------------       --------------
unicast-flood                Disabled
vmps                         Disabled
psp                          Disabled
dual-active-recovery         Disabled
evc-lite input mapping fa    Disabled
Recovery command: "clear     Disabled

Timer interval: 30 seconds

Interfaces that will be enabled at the next timeout:

Interface       Errdisable reason       Time left(sec)
---------       -----------------       --------------
Et0/1                  bpduguard           16

S2#
```

__Root Guard (lab)__

```
S1#en
S1#conf t
Enter configuration commands, one per line.  End with CNTL/Z.
S1(config)#int e0/2
S1(config-if)#spanning-tree guard root
S1(config-if)#end
S1#
*Sep 22 11:45:22.515: %SPANTREE-2-ROOTGUARD_CONFIG_CHANGE: Root guard enabled on port Ethernet0/2.
S1#


S2(config)#spanning-tree vlan 1 root primary


S1#
*Sep 22 11:46:07.050: %SPANTREE-2-ROOTGUARD_BLOCK: Root guard blocking port Ethernet0/2 on VLAN0001.
S1#sh spanning-tree vlan 1

VLAN0001
  Spanning tree enabled protocol ieee
  Root ID    Priority    32769
             Address     aabb.cc00.4000
             This bridge is the root
             Hello Time   2 sec  Max Age 20 sec  Forward Delay 15 sec

  Bridge ID  Priority    32769  (priority 32768 sys-id-ext 1)
             Address     aabb.cc00.4000
             Hello Time   2 sec  Max Age 20 sec  Forward Delay 15 sec
             Aging Time  15  sec

Interface           Role Sts Cost      Prio.Nbr Type
------------------- ---- --- --------- -------- --------------------------------
Et0/0               Desg FWD 100       128.1    P2p
Et0/1               Desg FWD 100       128.2    P2p
Et0/2               Desg BKN*100       128.3    P2p *ROOT_Inc
Et0/3               Desg FWD 100       128.4    P2p


S1#


S2(config)#no spanning-tree vlan 1 root primary


S1#
*Sep 22 11:47:21.194: %SPANTREE-2-ROOTGUARD_UNBLOCK: Root guard unblocking port Ethernet0/2 on VLAN0001.
S1#sh spanning-tree vlan 1

VLAN0001
  Spanning tree enabled protocol ieee
  Root ID    Priority    32769
             Address     aabb.cc00.4000
             This bridge is the root
             Hello Time   2 sec  Max Age 20 sec  Forward Delay 15 sec

  Bridge ID  Priority    32769  (priority 32768 sys-id-ext 1)
             Address     aabb.cc00.4000
             Hello Time   2 sec  Max Age 20 sec  Forward Delay 15 sec
             Aging Time  300 sec

Interface           Role Sts Cost      Prio.Nbr Type
------------------- ---- --- --------- -------- --------------------------------
Et0/0               Desg FWD 100       128.1    P2p
Et0/1               Desg FWD 100       128.2    P2p
Et0/2               Desg LRN 100       128.3    P2p
Et0/3               Desg FWD 100       128.4    P2p


S1#
```

__Loop Guard (lab)__

```
S1(config)#int e0/2
S1(config-if)#no spanning-tree guard root
S1(config-if)#spanning-tree guard loop
```

__BPDU Filter (lab)__

```
S1(config)#int e0/2
S1(config-if)#spanning-tree bpdufilter enable

S2(config)#int e0/1
S2(config-if)#spanning-tree bpdufilter enable
```

<br>

## RSTP 802.1w
<br>
STP có thể gây ra độ trễ đáng kể trong quá trình hội tụ mạng, đặc biệt khi có sự thay đổi trong topology. RSTP giúp giảm thiểu thời gian hội tụ, đảm bảo mạng hoạt động ổn định và liên tục.

__Port States__

| STP (802.1D) Port State | RSTP (802.1w) Port State | Is Port Included in Active Topology? | Is Port Learning MAC Addresses? |
| :---------------------- | :----------------------- | :----------------------------------- | :------------------------------ |
| Disabled                | Discarding               | No                                   | No                              |
| Blocking                | Discarding               | No                                   | No                              |
| Listening               | Discarding               | Yes                                  | No                              |
| Learning                | Learning                 | Yes                                  | Yes                             |
| Forwarding              | Forwarding               | Yes                                  | Yes                             |

__Port Roles__

![alt text](/docs/CCNP/img/rstp-root-port.png)
![alt text](/docs/CCNP/img/rstp-designed-port.png)
![alt text](/docs/CCNP/img/rstp-alternate-port.png)
![alt text](/docs/CCNP/img/rstp-backup-port.png)

__Sync process__

![alt text](/docs/CCNP/img/rstp-sync-process.png)

<br>

## Giải pháp PVST trên switch cisco
<br>
![Alt text](/docs/CCNA (old)/img/stp-pvst-1.png)

![Alt text](/docs/CCNA (old)/img/stp-pvst-2.png)

### IEEE Open Standard Spanning Tree Modes <br>
__Spanning Tree Protocol (STP) IEEE 802.1D –__ 1 instance <br>
__Rapid Spanning Tree Protocol (RSTP) IEEE 802.1w –__ 1 instance <br>
__Multiple Spanning Tree Protocol (MSTP) IEEE 802.1s –__ nhiều instance và cho phép phân bổ vlan vào các instance <br>

### Cisco Spanning Tree Modes <br>
__Per VLAN Spanning Tree Plus (PVST+) –__ 1 instance per vlan <br>
__Rapid Per VLAN Spanning Tree Plus (RPVST+) –__ 1 instance per vlan <br>
__Multiple Spanning Tree (MST) –__ nhiều instance và cho phép phân bổ vlan vào các instance <br>

```conf
Switch(config)#spanning-tree mode ?
  mst         Multiple spanning tree mode
  pvst        Per-Vlan spanning tree mode
  rapid-pvst  Per-Vlan rapid spanning tree mode
```

## MST (xem thêm)

```
Switch(config)# spanning-tree mode mst
Switch(config)# spanning-tree mst 0-1 root primary
Switch(config)# spanning-tree mst 2 root secondary
Switch(config)# spanning-tree mst configuration
Switch(config-mst)# name STUDY_CCNP
Switch(config-mst)# revision 2
Switch(config-mst)# instance 1 vlan 15,25
Switch(config-mst)# instance 2 vlan 99
```
