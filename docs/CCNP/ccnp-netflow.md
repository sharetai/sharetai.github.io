---
layout: default
title: NetFlow SPAN RSPAN ERSPAN
nav_order: 130
parent: CCNP
---

# NetFlow SPAN RSPAN ERSPAN
{: .no_toc }

Network traffic analyzer
{: .fs-6 .fw-300 }

---

## TABLE OF CONTENTS
{: .no_toc .text-delta }

1. TOC
{:toc}

---

## NetFlow

<h3> Overview </h3>

NetFlow là một hệ thống giao thức mạng do Cisco tạo ra để thu thập lưu lượng truy cập mạng IP. Sau đó, dữ liệu NetFlow được phân tích để tạo ra bức tranh về lưu lượng cập mạng.

<h3> Traditional NetFlow (TNF) </h3>

Cisco IOS NetFlow cho phép các thiết bị mạng được chuyển tiếp lưu lượng truy cập để tổng hợp dữ liệu về lưu lượng giao thông cá nhân. NetFlow truyền thống (TNF) đề cập đến việc thực hiện ban đầu của NetFlow, trong đó xác định cụ thể một dòng chảy là sự kết hợp độc đáo trong bảy lĩnh vực chính sau đây:

\- Source IP address <br>
\- Destination IP address <br>
\- Source port number <br>
\- Destination port number <br>
\- Layer 3 protocol type <br>
\- Type of service (ToS) byte <br>
\- Input logical interface <br>

    Netflow versions

    v1
        initial version
    v5
        adds support for ASN and flow sequence numbers
    v7
        special version for old C6k releases
    v8
        adds support for aggregation caches
    v9
        adds support for new fields and record types using templates
        adds support for IPv6, multicast, MPLS and BGP next hop
    v10
        aka IPFIX

    
    v1, v5, v9 are the most common ones.

    IPFIX (an IETF standard) is based on netflow v9.
    
<h4> Configuration </h4>

![alt text](/docs/CCNP/img/netflow.png)

```
Router1>enable
Router1#conf t
Router1(config)# ! Specify the NTOP server
Router1(config)# ! The router will export all flows to 192.168.1.1 with destination UDP port 2055.
Router1(config)# ip flow-export destination 192.168.10.1 2055
Router1(config)#
Router1(config)# ! Configure the router to use version 9
Router1(config)# ip flow-export version 9
Router1(config)#
Router1(config)# ! Configure what interface the router should use to source the updates from
Router1(config)# ip flow-export source Gi 0/0
Router1(config)#
Router1(config)# ! Tell the router on what interfaces to track the flows
Router1(config)# interface Gi 0/1
Router1(config-if)# ip route-cache flow
Router1(config-if)#
Router1(config-if)#end
```

Sử dụng lệnh `ip router-cache flow`, sẽ theo dõi tất cả các luồng đi vào trên physical interface tất cả các sub-interface. Có thể sử dụng lệnh `ip flow egress` hoặc `ip flow ingress` nếu chỉ muốn kích hoạt trên 1 sub-interface hoặc theo 1 hướng.

<h4> Verification </h4>

```
Router1#show ip flow export
Flow export v9 is enabled for main cache
Export source and destination details :
VRF ID : Default
Source(1) 192.168.10.254 (FastEthernet0/0)
Destination(1) 192.168.10.1 (2055)
Version 9 flow records
433 flows exported in 28 udp datagrams
0 flows failed due to lack of export packet
0 export packets were sent up to process level
0 export packets were dropped due to no fib
0 export packets were dropped due to adjacency issues
0 export packets were dropped due to fragmentation failures
0 export packets were dropped due to encapsulation fixup failures
```

<h3> Flexible NetFlow (FNF) </h3>

__Flexible NetFlow (FNF)__, không giống như TNF, cho phép tùy chỉnh và tập trung vào thông tin cụ thể. Có thể sử dụng một tập hợp con hoặc nhỏ hơn trong bảy lĩnh vực trọng điểm truyền thống để xác định một dòng chảy. FNF cũng có nhiều lĩnh vực khác. Điều này cho phép một tổ chức xác định mục tiêu thông tin cụ thể hơn, giảm thiểu luồng trafic không cần thiết, cho phép khả năng mở rộng và truyền thông hội nhóm.

__Flexible NetFlow (FNF)__ giúp tối ưu hóa cơ sở hạ tầng mạng bằng cách cung cấp đặc tính chi tiết về lưu lượng IP và xác định nguồn, đích lưu lượng cũng như các giao thức ứng dụng. Với điều này, nó làm giảm nguy cơ xảy ra các mối đe dọa bảo mật tiềm ẩn do khả năng lập kế hoạch năng lực được cải thiện với tính linh hoạt và khả năng mở rộng tăng lên.

<h4> Flexible NetFlow Components </h4>

| Component Name | Description                                                                              |
| :------------: | :--------------------------------------------------------------------------------------: |
| Flow Records   | Thu thập bản ghi.                                                                        |
| Flow Monitors  | Áp vào cổng để giám sát lưu lượng mạng.                                                  |
| Flow Exporters | Xuất dữ liệu NetFlow Version 9 từ Flow Monitor cache đến 1 host hoặc NetFlow collector.  |
| Flow Samplers  | Lấy mẫu một phần dữ liệu NetFlow thay vì phân tích tất cả dữ liệu NetFlow.               |

<h4> Configuring and Verifying the Custom Flow Record </h4>

```
Router# configure terminal
Router(config)# flow record CUSTOM
Router(config-flow-record)# description Custom Flow Record for IPv4 Traffic
Router(config-flow-record)# match ipv4 destination address
Router(config-flow-record)# collect counter bytes
Router(config-flow-record)# collect counter packets
Router(config-flow-record)# exit
Router(config)# do show flow record CUSTOM
```

<h4> Configuring and Verifying the Custom Flow Exporter </h4>

```
Router# configure terminal
Router(config)# flow exporter CUSTOM
Router(config-flow-exporter)# description EXPORT-TO-NETFLOW-COLLECTOR
Router(config-flow-exporter)# destination 192.168.10.10
Router(config-flow-exporter)# export-protocol netflow-v9
Router(config-flow-exporter)# transport UDP 999
Router(config-flow-exporter)# exit
Router(config)# exit
Router# sh run flow exporter
```

<h4> Configuring and Verifying the Custom Flow Monitor </h4>

```
Router(config)# flow monitor CUSTOM
Router(config-flow-monitor)# description Uses Custom Flow Record CUSTOM for IPv4 Traffic
Router(config-flow-monitor)# record CUSTOM
Router(config-flow-monitor)# cache timeout active 60
Router(config-flow-monitor)# end
Router# show run flow monitor CUSTOM
```

<h4> Configuring and Verifying the Flow Exporter Mapping to the Flow Monitor </h4>

```
Router# configure terminal
Router(config)# flow monitor CUSTOM
Router(config-flow-monitor)# exporter CUSTOM
Router(config-flow-monitor)# end
```

<h4> Configuring and Verifying the Flow Monitor Interface Commands </h4>

```
Router(config)# interface ethernet1/1
Router(config-if)# ip flow monitor CUSTOM input
Router(config-if)# interface ethernet1/2
Router(config-if)# ip flow monitor CUSTOM input
Router(config-if)# end
```

<br>

## SPAN

<h3> Overview </h3>

__SPAN (Switch Port Analyzer or Local Switched Port Analyzer)__ - Ghi lại lưu lượng truy cập mạng cục bộ trên một bộ chuyển mạch và gửi một bản sao đến một cổng cục bộ được kết nối với bộ phân tích lưu lượng.

<h3> Configuration </h3>

![alt text](/docs/CCNP/img/span.png)

```
Switch1(config)#monitor session 1 source interface gig0/0/0
Switch1(config)#monitor session 1 destination interface gig0/0/1
```

<h3> Verification </h3>

```
Switch1#show monitor session 1
Session 1
---------
Type: Local Session
Source Ports :
Both: gig0/0/0
Destination Ports: gig0/0/1
Encapsulation: Native
Ingress: Disabled
```

## RSPAN

<h3> Overview </h3>

__RSPAN (Remote Switch Port Analyzer)__ - Tương tự SPAN, tuy nhiên đích đến là một giao diện đầu xa trên một switch khác.

<h3> Configuration </h3>

![alt text](/docs/CCNP/img/rspan.png)

```
Switch1(config)#vlan 50
Switch1(config-vlan)#remote-span

Switch1(config)#interface gig0/0/0
Switch1(config-if)#switchport trunk encapsulation dot1q
Switch1(config-if)#switchport mode trunk

Switch1(config)#monitor session 1 source interface gig0/0/1
Switch1(config)#monitor session 1 destination remote vlan 50
```

```
Switch2(config)#vlan 50
Switch2(config-vlan)#remote-span

Switch2(config)#interface gig0/0/0
Switch2(config-if)#switchport trunk encapsulation dot1q
Switch2(config-if)#switchport mode trunk

Switch2(config)#monitor session 1 source remote vlan 50
Switch2(config)#monitor session 1 destination interface gig0/0/1
```

<h3> Verification </h3>

```
Switch1#show monitor session remote
Session 1
---------
Type: Remote Source Session
Source Ports :
Both: gig0/0/1
Dest RSPAN VLAN: 50
```

```
Switch2#show monitor session 1
Session 1
---------
Type: Remote Destination Session
Source RSPAN VLAN: 50
Destination Ports: gig0/0/1
Encapsulation: Native
Ingress: Disabled
```

## ERSPAN

<h3> Overview </h3>

__ERSPAN (Encapsulated Remote SPAN)__ - Tương tự SPAN, tuy nhiên có sử dụng đóng gói GRE, cho phép định tuyến lưu lượng truy cập SPAN từ nguồn đến đích.

<h3> Configuration </h3>

![alt text](/docs/CCNP/img/erspan.png)

```
Router1(config)#monitor session 1 type erspan-source
Router1(config-mon-erspan-src)#description SOURCE
Router1(config-mon-erspan-src)#no shutdown
Router1(config-mon-erspan-src)#source interface GigabitEthernet0/0/1 rx
Router1(config-mon-erspan-src)#
Router1(config-mon-erspan-src)#destination
Router1(config-mon-erspan-src-dst)#erspan-id 10
Router1(config-mon-erspan-src-dst)#ip address 172.16.30.254
Router1(config-mon-erspan-src-dst)#origin ip address 172.16.20.10
```

```
Router2(config)#monitor session 1 type erspan-destination
Router2(config-mon-erspan-dst)#description DESTINATION
Router2(config-mon-erspan-dst)#no shutdown
Router2(config-mon-erspan-dst)#destination interface GigabitEthernet0/0/1
Router2(config-mon-erspan-dst)#
Router2(config-mon-erspan-dst)#source
Router2(config-mon-erspan-dst-src)#erspan-id 10
Router2(config-mon-erspan-dst-src)#ip address 172.16.30.254
```

<h3> Verification </h3>

```
Router1#show monitor session erspan-source session
Type: ERSPAN Source Session
Status: Admin Enabled
Source Ports :
RX Only: Gig0/0/1
Destination IP Address: 172.16.30.254
Destination ERSPAN ID: 10
Origin IP Address: 172.16.10.10
```

```
Router2#show monitor session 1
Session 1
---------
Type: ERSPAN Destination Session
Status: Admin Enabled
Destination Ports: Gig0/0/1
Source IP Address: 172.16.30.254
Source ERSPAN ID: 10
```
