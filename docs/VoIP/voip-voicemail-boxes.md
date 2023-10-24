---
layout: default
title: Tạo hộp thư thoại voicemail boxes
nav_order: 5
parent: VoIP
---

# Tạo hộp thư thoại voicemail boxes
{: .no_toc }

Các bước cấu hình hộp thư thoại dùng để ghi âm thoại khi cuộc gọi bận
{: .fs-6 .fw-300 }

---

**Cấu hình file voicemail.conf**

```
$ sudo mv voicemail.conf voicemail.conf.old
$ sudo cat >> voicemail.conf
[vm-demo]
100 => 1234,Alice Jones,alice@example.com,alice2@example.com,attach=no|tz=central|maxmsg=10
101 => 1234,Bob Smith,bob@example.com,bob2@example.com,attach=yes|tz=eastern
^D
```

**Cấu hình file extensions.conf**

```
[from-internal]
exten => 100,1,dial(SIP/alice,20)
   same => n,VoiceMail(100@vm-demo,u)
exten => 101,1,dial(SIP/bob,20)
   same => n,VoiceMail(101@vm-demo,u)
exten => 500,1,Answer()
   same => n,VoiceMailMain(@vm-demo)
```

**Kiểm tra**

Gọi đến số bận, sẽ nghe được thoại voicemail và bắt đầu ghi âm. Muốn nghe lại voicemail, theo như cấu hình thì ấn **500** sẽ nghe được các options.

*(Source: https://wiki.asterisk.org/wiki/display/AST/Configuring+Voice+Mail+Boxes)*
