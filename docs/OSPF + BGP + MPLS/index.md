---
layout: default
title: OSPF + BGP + MPLS
nav_order: 3.7
has_children: false
---

# OSPF + BGP + MPLS
{: .no_toc }

OSPF + BGP + MPLS
{: .fs-6 .fw-300 }

## Ba giao thức nền tảng trong mạng ISP

<img src="/docs/OSPF + BGP + MPLS/img/OSPF + BGP + MPLS.png" style="max-width: 100%; width: 800px" />

Ba giao thức **OSPF**, **BGP** và **MPLS** là nền tảng trong hạ tầng mạng của các nhà cung cấp dịch vụ (ISP):

- **OSPF (Open Shortest Path First)**  [Đọc ở đây](/docs/CCNP SP/ccnpsp-020-ospf/)  
  Là giao thức định tuyến nội bộ (IGP), giúp các thiết bị trong cùng miền mạng nhận biết lẫn nhau và tìm đường đi ngắn nhất dựa trên chi phí liên kết.

- **BGP (Border Gateway Protocol)**  [Đọc ở đây](/docs/CCNP/ccnp-bgp/)  
  Là giao thức định tuyến biên, xử lý khối lượng lớn bảng định tuyến.  
  **eBGP** dùng để kết nối giữa các ISP khác nhau, còn **iBGP** dùng để trao đổi route giữa các miền IGP trong cùng hệ thống tự trị (AS).

- **MPLS (Multiprotocol Label Switching)**  [Đọc ở đây](/docs/CCNP SP/ccnpsp-030-mpls/)  
  Hoạt động ở lớp giữa Layer 2 và Layer 3, cho phép triển khai các dịch vụ **VPN**, **traffic engineering**, và **QoS** đảm bảo luồng dữ liệu được điều khiển tối ưu qua mạng.




