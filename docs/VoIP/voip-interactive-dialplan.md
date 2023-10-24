---
layout: default
title: Tạo dialplan tương tác
nav_order: 4
parent: VoIP
---

# Tạo dialplan tương tác
{: .no_toc }

Các bước cấu hình tạo kịch bản có thể tương tác
{: .fs-6 .fw-300 }

---

**extensions.conf**

VD1

```
[from-internal]
exten => 100,1,dial(SIP/alice,20)
exten => 101,1,dial(SIP/bob,20)
exten => 200,1,Answer()
   same => n,Playback(hello-world)
   same => n,Hangup()
exten => 201,1,Goto(TestMenu,start,1)


[TestMenu]
exten => start,1,Answer()
   same => n,Background(main-menu)
   same => n,WaitExten(5)

exten => 1,1,Playback(digits/1)
   same => n,Goto(TestMenu,start,1)

exten => 2,1,Playback(digits/2)
   same => n,Goto(TestMenu,start,1)

exten => i,1,Playback(pbx-invalid)
   same => n,Goto(TestMenu,start,1)

exten => t,1,Playback(vm-goodbye)
   same => n,Hangup()
```

VD2

```
[from-internal]
exten => 100,1,dial(SIP/alice,20)
exten => 101,1,dial(SIP/bob,20)
exten => 200,1,Answer()
   same => n,Playback(hello-world)
   same => n,Hangup()
exten => 201,1,Goto(TestMenu,start,1)


[TestMenu]
exten => start,1,Answer()
   same => n,Background(main-menu&press-1&or&press-2)
   same => n,WaitExten(5)

exten => 1,1,Dial(SIP/alice,20)
   same => n,Playback(vm-nobodyavail)
   same => n,Hangup()

exten => 2,1,Dial(SIP/bob,20)
   same => n,Playback(vm-nobodyavail)
   same => n,Hangup()

exten => i,1,Playback(pbx-invalid)
   same => n,Goto(TestMenu,start,1)

exten => t,1,Playback(vm-goodbye)
   same => n,Hangup()
```

*(Source: http://www.asteriskdocs.org/en/3rd_Edition/asterisk-book-html-chunk/asterisk-DP-Basics-SECT-3.html)*

