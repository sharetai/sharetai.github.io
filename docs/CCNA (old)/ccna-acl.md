---
layout: default
title: ACL
nav_order: 14
parent: CCNA (old)
---

# Access Control List
{: .no_toc }

Danh sách điều khiển truy cập
{: .fs-6 .fw-300 }

---

## TABLE OF CONTENTS
{: .no_toc .text-delta }

1. TOC
{:toc}

---

**Chức năng**
* Quản lý gói qua cổng : áp vào interface
* Quản lý telnet : áp vào vty
* Quản lý dịch vụ : áp vào dịch vụ tương ứng

**Phân loại**
* Standard (id 1-99)
* Extended (id 100-199)

{: .warning-title }
> Warning
>
> Lưu ý: ACL là một danh sách các phát biểu, nếu gói tin không thuộc phát biểu nào sẽ bị **deny**.

## Standard access list

{: .note-title }
> Syntax
>
> __access-list__ _{acl-id(1-99)}_ _{permit \| deny}_ _{source wildcard \| host source \| any}_

**Cách 1**

```
R(config)#access-list 1 deny 192.168.1.1 0.0.0.0
(hoặc) R(config)#access-list 1 deny host 192.168.1.1
R(config)#access-list 1 permit any
```

**Cách 2**

```
R(config)#ip access-list standard 1
R(config-std-nacl)#deny 192.168.1.1 0.0.0.0
(hoặc) R(config-std-nacl)#deny host 192.168.1.1
R(config-std-nacl)#permit any
```

## Extended access list

{: .note-title }
> Syntax
>
> __access-list__ _{acl-id(100-199)}_ _{permit \| deny}_ _{protocol}_ _{source wildcard \| host source \| any}_ _{destination wildcard \| host destination \| any}_ [operator [port]]

**Cách 1**

```
R(config)#access-list 100 deny icmp host 192.168.1.1 host 192.168.2.1
R(config)#access-list 100 deny tcp host 192.168.1.1 host 192.168.2.1 eq 80
R(config)#access-list 100 deny tcp host 192.168.1.1 host 192.168.2.1 eq 443
R(config)#access-list 100 permit ip any any
```


**Cách 2**

```
R(config)#ip access-list extended 100
R(config-ext-nacl)#deny icmp host 192.168.1.1 host 192.168.2.1
R(config-ext-nacl)#deny tcp host 192.168.1.1 host 192.168.2.1 eq 80
R(config-ext-nacl)#deny tcp host 192.168.1.1 host 192.168.2.1 eq 443
R(config-ext-nacl)#permit ip any any
```

## Áp cổng

{: .note-title }
> Syntax
>
> __interface__ _{interface}_ <br/>
> __ip access-group__ _{acl-id}_ _{in \| out}_
>
> __line vty 0 4__ <br/>
> __ip access-class__ _{acl-id}_ _{in \| out}_

```
int g0/0
ip access-group 1 out
```
