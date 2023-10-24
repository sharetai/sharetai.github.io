---
layout: default
title: Tạo dialplan đơn giản
nav_order: 3
parent: VoIP
---

# Tạo dialplan đơn giản
{: .no_toc }

Các bước cấu hình tạo user và tạo kịch bản
{: .fs-6 .fw-300 }

---

*Cần biết về Dialplan, Contexts, Extensions, Priorities, Applications: truy cập [link](http://www.asteriskdocs.org/en/3rd_Edition/asterisk-book-html-chunk/asterisk-DP-Basics-SECT-1.html)*

**Cấu hình file sip.conf**

```
$ cd /etc/asterisk/
$ sudo mv sip.conf sip.conf.old
$ sudo cat >> sip.conf
[general]
transport = udp

[friends_internal](!)
type = friend
host = dynamic
context = from-internal
disallow = all
allow = ulaw

[alice](friends_internal)
secret = 1  ; put a strong, unique password here instead

[bob](friends_internal)
secret = 1  ; put a strong, unique password here instead
^D
```

**Cấu hình file extensions.conf**

```
$ cd /etc/asterisk/
$ sudo mv extensions.conf sip.extensions.old
$ sudo cat >> extensions.conf
[from-internal]
exten => 100,1,dial(SIP/alice,20)
exten => 101,1,dial(SIP/bob,20)
exten => 200,1,Answer()
   same => n,Playback(hello-world)
   same => n,Hangup()
^D
```

**Kiểm tra**

Khởi chạy lại dịch vụ.

```
$ sudo systemctl restart asterisk
```

Dùng MicroSip và Zoiper đăng nhập user và gọi thử qua lại.


* *Trường hợp không login được do chưa cấu hình firewalld, cần mở port 5060*

```
$ sudo firewall-cmd --permanent --zone=public --add-port=5060/udp
$ sudo firewall-cmd --reload
```

*(Source: http://www.asteriskdocs.org/en/3rd_Edition/asterisk-book-html-chunk/asterisk-DP-Basics-SECT-2.html)*
