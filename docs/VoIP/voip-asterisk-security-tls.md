---
layout: default
title: "Asterisk security: TLS"
nav_order: 7
parent: VoIP
---

# Asterisk security: TLS
{: .no_toc }

Các bước cấu hình Asterisk dùng TLS
{: .fs-6 .fw-300 }

---

Các bước sau đây được thực thi với quyền user `asterisk`

```
$ su asterisk
```

## Tạo chứng chỉ

```
$ cd /usr/src/
$ cd asterisk-*/
$ bash contrib/scripts/ast_tls_cert -C pbx1.mycompany.local -O "My Company" -d /etc/asterisk/keys -b 2048
```

## Cấu hình file sip.conf

```
$ vim /etc/asterisk/sip.conf
...
[general]
bindaddr=0.0.0.0
port=5061
transport=tls
encryption=yes
tlsprivatekey=/etc/asterisk/keys/asterisk.key
tlscertfile=/etc/asterisk/keys/asterisk.crt
tlsbindaddr=[::]:5061
tlsdontverifyserver=no
tlsclientmethod=tlsv1
tlsenable=yes
...

$ systemctl restart asterisk
```

*(Source: https://hotkey404.com/asterisk-security-using-self-signed-ssl-certificate-for-tls-registration/)*
