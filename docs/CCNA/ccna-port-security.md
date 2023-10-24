---
layout: default
title: Port Security
nav_order: 19
parent: CCNA
---

# Port Security
{: .no_toc }

Các bước bảo mật cho Layer 2
{: .fs-6 .fw-300 }

---

## Table of contents
{: .no_toc .text-delta }

1. TOC
{:toc}

---

## Các bước bảo mật cho Layer 2

1. Bỏ qua VLAN 1, không sử dụng. Tạo VLAN mới làm native VLAN
2. Tắt chế độ thương lượng (negotiate) trên các cổng kết nối với người dùng.
3. Tắt CDP trên các cổng nối với thiết bị không tin cậy.
4. Shutdown các cổng không dùng, đưa các port này vào VLAN dành riêng.
5. Giới hạn MAC trên các cổng.

## Cấu hình port-security

![image](/docs/CCNA/img/port-security.png)

```
SW1(config)#int range f0/1-24
SW1(config-if-range)#switchport mode access 
SW1(config-if-range)#switchport port-security
SW1(config-if-range)#switchport port-security max 1
SW1(config-if-range)#switchport port-security mac-address sticky 
SW1(config-if-range)#switchport port-security violation <protect/restrict/shutdown>
```

Các mode xử lý vi phạm:
* protect: loại bỏ gói vi phạm
* restrict: loại bỏ gói vi phạm và ghi lại log
* shutdown: loại bỏ gói vi phạm và shutdown port
