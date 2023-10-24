---
layout: default
title: "Asterisk security: run as non-root"
nav_order: 6
parent: VoIP
---

# Asterisk security: run as non-root
{: .no_toc }

Các bước thêm user non-root cho Asterisk
{: .fs-6 .fw-300 }

---

## Thêm user và group

```
$ sudo useradd asterisk
$ sudo passwd asterisk
```

## Thay đổi permissions

```
$ sudo chown -R asterisk:asterisk /var/{lib,log,run,spool}/asterisk
$ sudo chown -R asterisk:asterisk /etc/asterisk
$ sudo chown asterisk:asterisk /usr/sbin/asterisk

# for 32-bit system
$ sudo chown -R asterisk:asterisk /usr/lib/asterisk

# for 64-bit system
$ sudo chown -R asterisk:asterisk /usr/lib64/asterisk
```

## Cấu hình file asterisk.conf

```
$ sudo vim /etc/asterisk/asterisk.conf
...
[options]
runuser = asterisk
rungroup = asterisk
...
$ sudo systemctl restart asterisk
```

*(Source: https://hotkey404.com/asterisk-security-run-as-non-root-user/)*
