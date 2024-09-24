---
layout: default
title: OSPF Route - Single Area
nav_order: 12
parent: CCNA
---

# Open Shortest Path First - Single Area
{: .no_toc }

Cấu hình định tuyến động sử dụng giao thức OSPF cho Router cho single area
{: .fs-6 .fw-300 }

---

## Table of contents
{: .no_toc .text-delta }

1. TOC
{:toc}

---

Giao thức điển hình của giải thuật Link State hay còn được gọi là Shortest Path First (SPF). Mỗi router khi chạy giao thức sẽ gửi các trạng thái đường link của nó cho tất cả các router trong vùng (area). Sau một thời gian trao đổi, các router sẽ đồng nhất được bảng cơ sở dữ liệu trạng thái đường link (Link State Database - LSDB) với nhau, mỗi router đều có được "bản đồ mạng" của cả vùng. Từ đó mỗi router sẽ chạy giải thuật Dijkstra tính toán ra một cây đường đi ngắn nhất (Shortest Path Tree) và dựa vào cây này để xây dựng nên bảng định tuyến.

Quy trình hoạt động cơ bản:

* Gửi gói tin hello quảng bá về bản thân với chu kì 10s với mạng quảng bá đa truy cập (broadcast multi-access) và 30s cho dead.
* Bên cạnh đó quảng bá và thu các gói tin về trạng thái đường đi đến các router láng giềng - gói Link State Advertisement (LSA).
* Dùng thuật toán Dijkstra xây dựng sơ đồ Shortest Path Tree (SPT) - bản đồ thống nhất về các router trong vùng và khoảng cách, băng thông giữa chúng theo router tính toán.
* Tính toán đường đi tối ưu.
* Bản đồ được lưu vào Link State Database (LSD).

![image](/docs/CCNA/img/ospf_route_single_area.png)

## Cách 1

{: .note-title }
> Syntax
>
> Router(config)# __router ospf__ _{process-id}_ <br/>
> Router(config-router)# exit <br/>
> Router(config)# __interface__ _{direct-interface}_ <br/>
> Router(config-if)# __ip ospf__ _{process-id}_ __area__ _{area-id}_

* **R1**

```
R1(config)#router ospf 1
R1(config-router)#exit

R1(config)#int Gi0/0
R1(config-if)#ip ospf 1 area 0

R1(config)#int Gi0/1
R1(config-if)#ip ospf 1 area 0
```

* **R2**

```
R2(config)#router ospf 1
R2(config-router)#exit

R2(config)#int Gi0/0
R2(config-if)#ip ospf 1 area 0

R2(config)#int Gi0/1
R2(config-if)#ip ospf 1 area 0

R2(config)#int Gi0/2
R2(config-if)#ip ospf 1 area 0
```

* **R3**

```
R3(config)#router ospf 1
R3(config-router)#exit

R3(config)#int Gi0/0
R3(config-if)#ip ospf 1 area 0

R3(config)#int Gi0/1
R3(config-if)#ip ospf 1 area 0
```

## Cách 2

{: .note-title }
> Syntax
>
> Router(config)# __router ospf__ _{process-id}_ <br/>
> Router(config-router)# __network__ _{direct-hop}_ __0.0.0.0 area__ _{area-id}_

* **R1**

```
R1(config)#router ospf 1
R1(config-router)#network 172.16.0.1 0.0.0.0 area 0
R1(config-router)#network 192.168.1.254 0.0.0.0 area 0
```

* **R2**

```
R2(config)#router ospf 1
R2(config-router)#network 172.16.0.2 0.0.0.0 area 0
R2(config-router)#network 223.17.0.1 0.0.0.0 area 0
R2(config-router)#network 192.168.2.254 0.0.0.0 area 0
```

* **R3**

```
R3(config)#router ospf 1
R3(config-router)#network 223.17.0.1 0.0.0.0 area 0
R3(config-router)#network 192.168.3.254 0.0.0.0 area 0
```

## Cách 3

{: .note-title }
> Syntax
>
> Router(config)# __router ospf__ _{process-id}_ <br/>
> Router(config-router)# __network__ _{direct-hop}_ _{wildcard-mask}_ __area__ _{area-id}_

* **R1**

```
R1(config)#router ospf 1
R1(config-router)#network 172.16.0.0 0.0.255.255 area 0
R1(config-router)#network 192.168.1.0 0.0.0.255 area 0
```

* **R2**

```
R2(config)#router ospf 1
R2(config-router)#network 172.16.0.0 0.0.255.255 area 0
R2(config-router)#network 223.17.0.0 0.0.255.255 area 0
R2(config-router)#network 192.168.2.0 0.0.0.255 area 0
```

* **R3**

```
R3(config)#router ospf 1
R3(config-router)#network 223.17.0.0 0.0.255.255 area 0
R3(config-router)#network 192.168.3.0 0.0.0.255 area 0
```

## Các lệnh debug

```
R# show ip int bri
R# show ip route ospf
R# show ip ospf
R# show ip ospf interface
R# show ip ospf neighbor
R# show ip ospf database
```

