---
layout: default
title: Cloud Computing
nav_order: 96
parent: CCNA
---

# Cloud Computing
{: .no_toc }

Điện toán đám mây
{: .fs-6 .fw-300 }

---

## Table of contents
{: .no_toc .text-delta }

1. TOC
{:toc}

---

## <u>Server Virtualization</u>

Ảo hoá máy chủ là xây dựng nhiều máy chủ ảo trên một máy chủ vật lý. Tiết kiệm chi phí, tài nguyên, điện, diện tích, không gian làm mát.

![Alt text](/docs/CCNA/img/Server-Virtualization.png)

## <u>Hypervisor</u>

Hypervisor phần mềm cho phép chia một máy tính vật lý (CPU, memory, storage) thành nhiều máy tính ảo riêng biệt, mỗi máy ảo có hệ điều hành và ứng dụng riêng.

Có hai loại hypervisor chính: <br>
\- Hypervisor loại 1 (Hypervisor Bare-metal): Cài đặt trực tiếp trên phần cứng máy tính, không cần hệ điều hành trung gian. Loại này thường được sử dụng cho các ứng dụng đòi hỏi hiệu suất cao và tính ổn định cao, ví dụ như ảo hóa máy chủ. VMware ESXi, Microsoft Hyper-V <br>
\- Hypervisor loại 2 (Hypervisor Hosted): Cài đặt trên hệ điều hành hiện có, như Windows hoặc Linux. Loại này phổ biến hơn cho người dùng cá nhân và doanh nghiệp nhỏ vì dễ cài đặt và sử dụng hơn. VMware Workstation Player, Oracle VirtualBox <br>

![Alt text](/docs/CCNA/img/Types-of-Hypervisors.png)

## <u>Virtual Routing and Forwarding (VRF)</u>

Chia 1 router vật lý thành nhiều router ảo.

<img src="/docs/CCNA/img/Virtual-Routing-and-Forwarding.png" height="355" width="518" />

## <u>On-Premise vs. IaaS vs. PaaS vs. SaaS</u>

![Alt text](/docs/CCNA/img/IaaS-PaaS-SaaS.png)
