---
layout: default
title: TELNET
nav_order: 2
parent: JN0
---

# Teletype Network
{: .no_toc }

Giao thức đăng nhập thiết bị mạng
{: .fs-6 .fw-300 }

---

Đặt hostname
```
root> configure
Entering configuration mode

root# set system host-name vMX1

[edit]
root# commit
commit complete

[edit]
root@vMX1#
```

* Cài đặt telnet

{: .note-title }
> Syntax
>
> __# set system services telnet__ <br/>
> __# set system login user__ _user-name_ __class__ _operator|read-only|super-user|unauthorized_ __authentication__ __plain-text-password__

```
[edit]
root@vMX1# set system services telnet

[edit]
root@vMX1# set system login user lab class super-user authentication plain-text-password
New password:
Retype new password:

[edit]
root@vMX1# commit
commit complete
```
