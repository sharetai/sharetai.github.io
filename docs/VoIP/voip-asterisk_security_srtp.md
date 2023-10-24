---
layout: default
title: "Asterisk security: SRTP"
nav_order: 8
parent: VoIP
---

# Asterisk security: SRTP
{: .no_toc }

Các bước cấu hình Asterisk dùng SRTP
{: .fs-6 .fw-300 }

---

Các bước sau đây được thực thi với quyền user `asterisk`

```
$ su asterisk
```

```
$ sudo yum -y install openssl*
$ sudo yum -y install libsrtp

$ cd /usr/src/
$ cd asterisk-*/
$ sudo ./configure --libdir=/usr/lib64 --with-pjproject-bundled --with-jansson-bundled
$ sudo make
$ sudo make install

$ sudo systemctl restart asterisk
```
