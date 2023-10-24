---
layout: default
title: Cài đặt Asterisk GUI
nav_order: 2
parent: VoIP
---

# Cài đặt Asterisk GUI
{: .no_toc }

Các bước cài đặt giao diện web cho Asterisk
{: .fs-6 .fw-300 }

---

**Cài đặt Asterisk GUI**

```
$ cd /usr/src   # or wherever you prefer to download source code to
$ sudo svn co http://svn.digium.com/svn/asterisk-gui/trunk asterisk-gui
$ cd asterisk-gui
$ sudo ./configure
$ sudo make
$ sudo make install
$ sudo make samples
```

**Cấu hình file httpd.conf**

```
$ cd /etc/asterisk/
$ sudo mv httpd.conf httpd.conf.old
$ sudo cat >> httpd.conf
[general]
enabled=yes
enablestatic=yes      ; without this, you can only send AMI commands, not display 
                      ; html content

bindaddr=0.0.0.0          ; address you want the Asterisk HTTP server to respond on
bindport=8088             ; port you want the Asterisk HTTP server to respond on
prefix=asterisk           ; will form part of the URI, similar to a directory name
^D
```

**Cấu hình file manager.conf**

```
$ cd /etc/asterisk/
$ sudo mv manager.conf manager.conf.old
$ sudo cat >> manager.conf
[general]
enabled=yes      ; you may already have AMI enabled if you are using it for other things
webenabled=yes   ; this enables the interaction between the Asterisk web server and AMI

[asterisk] ; you can name the user whatever you want
secret = asterisk
read = system,call,log,verbose,command,agent,user,config
write = system,call,log,verbose,command,agent,user,config
^D
```

**Kiểm tra**

```
$ sudo systemctl restart asterisk
```

Truy cập URL sau để kiểm tra gui đã được cấu hình

```
http://localhost:8088/asterisk/static/config/index.html
```

*(Source: http://www.asteriskdocs.org/en/2nd_Edition/asterisk-book-html-chunk/I_sect111_tt1363.html)*
