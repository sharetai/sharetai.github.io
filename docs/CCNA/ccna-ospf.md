---
layout: default
title: OSPF Route
nav_order: 12
parent: CCNA
---

# Open Shortest Path First
{: .no_toc }

Giao thức định tuyến đường đi ngắn nhất chuẩn mở
{: .fs-6 .fw-300 }

---

## Table of contents
{: .no_toc .text-delta }

1. TOC
{:toc}

---

__OSPF (Open Shortest Path First)__ là giao thức định tuyến nội IGP và là giao thức Link State. Mỗi router khi chạy giao thức sẽ gửi các trạng thái đường link của nó cho tất cả các router trong vùng (area). Sau một thời gian trao đổi, các router sẽ đồng nhất được bảng cơ sở dữ liệu trạng thái đường link (Link State Database - LSDB) với nhau, mỗi router đều có được "bản đồ mạng" của cả vùng. Từ đó mỗi router sẽ chạy giải thuật Dijkstra tính toán ra một cây đường đi ngắn nhất (Shortest Path Tree) và dựa vào cây này để xây dựng nên bảng định tuyến.

Quy trình hoạt động cơ bản:

* Gửi gói tin hello quảng bá về bản thân với chu kì 10s với mạng quảng bá đa truy cập (broadcast multi-access) và 30s cho dead.
* Bên cạnh đó quảng bá và thu các gói tin về trạng thái đường đi đến các router láng giềng - gói Link State Advertisement (LSA).
* Dùng thuật toán Dijkstra xây dựng sơ đồ Shortest Path Tree (SPT) - bản đồ thống nhất về các router trong vùng và khoảng cách, băng thông giữa chúng theo router tính toán.
* Tính toán đường đi tối ưu.
* Bản đồ được lưu vào Link State Database (LSD).

<br>

## OSPF Single Area
<br>
![image](/docs/CCNA/img/ospf_route_single_area.png)

<h3> Cách làm 1 </h3>

{: .note-title }
> Syntax
>
> Router(config)# __router ospf__ _process-id_ <br/>
> Router(config-router)# exit <br/>
> Router(config)# __interface__ _direct-interface_ <br/>
> Router(config-if)# __ip ospf__ _process-id_ __area__ _area-id_

* __R1__
```
router ospf 1
exit
int Gi0/0
ip ospf 1 area 0
int Gi0/1
ip ospf 1 area 0
```

* __R2__
```
router ospf 1
exit
int Gi0/0
ip ospf 1 area 0
int Gi0/1
ip ospf 1 area 0
int Gi0/2
ip ospf 1 area 0
```

* __R3__
```
router ospf 1
exit
int Gi0/0
ip ospf 1 area 0
int Gi0/1
ip ospf 1 area 0
```

<h3> Cách làm 2 </h3>

{: .note-title }
> Syntax
>
> Router(config)# __router ospf__ _process-id_ <br/>
> Router(config-router)# __network__ _direct-hop_ __0.0.0.0 area__ _area-id_

* __R1__
```
router ospf 1
network 172.16.0.1 0.0.0.0 area 0
network 192.168.1.254 0.0.0.0 area 0
```

* __R2__
```
router ospf 1
network 172.16.0.2 0.0.0.0 area 0
network 223.17.0.1 0.0.0.0 area 0
network 192.168.2.254 0.0.0.0 area 0
```

* __R2__
```
router ospf 1
network 223.17.0.1 0.0.0.0 area 0
network 192.168.3.254 0.0.0.0 area 0
```

<h3> Cách làm 3 </h3>

{: .note-title }
> Syntax
>
> Router(config)# __router ospf__ _{process-id}_ <br/>
> Router(config-router)# __network__ _{direct-hop}_ _{wildcard-mask}_ __area__ _{area-id}_

* __R1__
```
router ospf 1
network 172.16.0.0 0.0.255.255 area 0
network 192.168.1.0 0.0.0.255 area 0
```

* __R2__
```
router ospf 1
network 172.16.0.0 0.0.255.255 area 0
network 223.17.0.0 0.0.255.255 area 0
network 192.168.2.0 0.0.0.255 area 0
```

* __R2__
```
router ospf 1
network 223.17.0.0 0.0.255.255 area 0
network 192.168.3.0 0.0.0.255 area 0
```

<br>

## OSPF Multi Area
<br>
![image](/docs/CCNA/img/ospf_route_multi_area.png)

* __R0__
```
router ospf 1
network 10.0.0.2 0.0.0.0 area 0
network 20.0.0.1 0.0.0.0 area 0
```

* __R1__
```
router ospf 1
network 10.0.0.1 0.0.0.0 area 0
network 192.168.1.126 0.0.0.0 area 1
network 192.168.1.254 0.0.0.0 area 1
```

* __R2__
```
router ospf 1
network 20.0.0.2 0.0.0.0 area 0
network 192.168.2.126 0.0.0.0 area 2
network 192.168.2.254 0.0.0.0 area 2
```

<br>

## OSPF Summarization
<br>

```
router ospf 1
area 2 range 192.168.2.0 255.255.255.0
```

<br>

## OSPF Debug
<br>
```
show ip int bri
show ip route ospf
show ip ospf
show ip ospf interface
show ip ospf neighbor
show ip ospf database
```

