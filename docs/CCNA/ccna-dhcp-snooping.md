---
layout: default
title: DHCP Snooping
nav_order: 24
parent: CCNA
---

# DHCP Snooping
{: .no_toc }

Cấu hình chống dhcp snooping và arp poisoning
{: .fs-6 .fw-300 }

---

## Table of contents
{: .no_toc .text-delta }

1. TOC
{:toc}

---

![image](/docs/CCNA/img/dhcp-snooping.png)

## DHCP Snooping

```
Switch(config)#ip dhcp snooping 
Switch(config)#ip dhcp snooping vlan 1
Switch(config)#no ip dhcp snooping information option 
Switch(config)#int fa0/24
Switch(config-if)#ip dhcp snooping trust 
```

## ARP Spoisoning

```
Switch(config)#ip arp inspection vlan 1
Switch(config)#ip dhcp snooping 
Switch(config)#ip dhcp snooping vlan 1
Switch(config)#no ip dhcp snooping information option 
Switch(config)#int fa0/24
Switch(config-if)#ip dhcp snooping trust 
Switch(config-if)#ip arp inspection trust 
```

