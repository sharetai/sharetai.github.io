---
layout: default
title: Syslog vs SNMP
nav_order: 95
parent: CCNA (old)
---

# System Logging Protocol vs Simple Network Management Protocol
{: .no_toc }

Nhật ký hệ thống và Giao thức quản lý mạng đơn giản
{: .fs-6 .fw-300 }

---

## TABLE OF CONTENTS
{: .no_toc .text-delta }

1. TOC
{:toc}

---

## Syslog explained

**Syslog** là một tiêu chuẩn để ghi nhật ký tin nhắn

## Syslog message format

```
*Jan 18 03:02:42: %LINEPROTO-5-UPDOWN: Line protocol on Interface GigabitEthernet0/0, changed state to down
```

\- **Jan 18 03:02:42** – thời gian timestamp <br>
\- **%LINEPROTO** – nguồn tạo ra log. Nó có thể là một thiết bị phần cứng (ví dụ: bộ định tuyến), giao thức hoặc mô-đun của phần mềm hệ thống. <br>
\- **5** – mức độ nghiêm trọng, từ 0 đến 7, với số càng thấp càng nghiêm trọng. <br>
\- **UPDOWN** – cách ghi nhớ duy nhất cho tin nhắn. <br>
\- **Line protocol on Interface GigabitEthernet0/0, changed state to down** – mô tả sự kiện <br>

<u>* Mức độ nghiêm trọng được đánh số từ 0 đến 7:</u>

**0 – emergency** (Hệ thống không sử dụng được) <br>
**1 – alert** (Cần hành động ngay lập tức) <br>
**2 – critical** events (Điều kiện nguy cấp) <br>
**3 – error** events (Điều kiện lỗi) <br>
**4 – warning** events (Điều kiện cảnh báo) <br>
**5 – notice** events (Điều kiện bình thường nhưng quan trọng) <br>
**6 – informational** events (Chỉ tin nhắn thông tin) <br>
**7 – debug** messages (Chỉ xuất hiện trong quá trình gỡ lỗi) <br>

## Cisco IOS Syslog Logging Locations

\- Logging Buffer - các sự kiện sẽ được lưu trong bộ nhớ RAM <br>
\- Console Line - các sự kiện sẽ được hiển thị trong CLI khi truy cập qua console <br>
\- Terminal Lines - các sự kiện sẽ được hiển thị trong CLI khi truy cập qua telnet/sssh <br>
\- Syslog Server - các sự kiện sẽ được lưu trên server syslog <br>

<u>Logging Buffer Configuration</u>

```
R1(config)#logging buffered
R1(config)#logging buffered 100000
R1(config)#logging buffered debugging
```

<u>Console Line Configuration</u>

```
R1(config)#logging console
R1(config)#no logging console
```

<u>Terminal Line Configuration</u>

```
R1#terminal monitor
R1#terminal no monitor
```

<u>Syslog Server Configuration</u>

logging trap <0-7>. Số điền vào sẽ bao gồm cả số nhỏ hơn.

```
R1(config)#logging 10.0.0.100
R1(config)#logging trap debugging
R1(config)#logging trap ?
  <0-7>          Logging severity level
  alerts         Immediate action needed           (severity=1)
  critical       Critical conditions               (severity=2)
  debugging      Debugging messages                (severity=7)
  emergencies    System is unusable                (severity=0)
  errors         Error conditions                  (severity=3)
  informational  Informational messages            (severity=6)
  notifications  Normal but significant conditions (severity=5)
  warnings       Warning conditions                (severity=4)
  <cr>
```

Mặc định không gửi timestamp, nên cần bổ sung:

```
R1(config)#service timestamps log datetime msec
```

## The logging synchronous Cisco Command

```
logging synchronous [level [severity-level | all] | limit number-of-buffers]
```

khi không có `logging synchronous`, khi phun log, con trỏ sẽ vẫn ghi tiếp lên log, không ảnh hưởng, chỉ khó chịu cho người quản trị 
```
R1(config-if)#ip add 10.0.13
*Jun  9 10:25:01.336: %LINK-3-UPDOWN: Interface Ethernet0/1, changed state to up
*Jun  9 10:25:02.341: %LINEPROTO-5-UPDOWN: Line protocol on Interface Ethernet0/1, changed state to up.1 255.255.255.0
R1(config-if)#ip add 10.0.13.1 255.255.255.0
```

khi có `logging synchronous`, sau phun log sẽ tự động xuống nhảy xuống 

```
R1(config-if)#ip add 10.0.13
*Jun  9 10:29:40.763: %LINK-5-CHANGED: Interface Ethernet0/1, changed state to administratively down
*Jun  9 10:29:41.771: %LINEPROTO-5-UPDOWN: Line protocol on Interface Ethernet0/1, changed state to down
R1(config-if)#ip add 10.0.13.1 255.255.255.0
```

disable synchronization

```
no logging synchronous
```

## SNMP (Simple Network Management Protocol)

SNMP là chương trình giám sát tài nguyên mạng, server-client, udp, port 25.

**Network management station (NMS)** - snmp server <br>
**Agent** - snmp client <br>

<img src="/docs/CCNA (old)/img/SNMP_communication_principles_diagram.png" width="500" height="231" />

*Trap* là một thông báo được gửi tự động từ *SNMP agent* (đại lý SNMP) đến *SNMP manager* (trình quản lý SNMP) để báo cáo về một sự kiện quan trọng hoặc bất thường xảy ra trên thiết bị mạng.

*MIB* là viết tắt của *Management Information Base* (Cơ sở dữ liệu thông tin quản lý) trong SNMP. MIB đóng vai trò quan trọng trong việc thu thập và quản lý thông tin thiết bị mạng.

