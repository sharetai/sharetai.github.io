---
layout: default
title: Backup và Restore
nav_order: 8
parent: CCNA
---

# Backup và Restore
{: .no_toc }

Sau lưu và Khôi phục
{: .fs-6 .fw-300 }

---

## Table of contents
{: .no_toc .text-delta }

1. TOC
{:toc}

---

Cấu hình xong thiết bị thì ta nên backup để đề phòng khi sự cố xảy ra có thể restore thiết bị về trạng thái ban đầu trong thời gian nhanh nhất. Các thành phần trên thiết bị cisco cần backup:

* File **startup-config** chứa thông tin cấu hình
* Hệ điều hành **IOS**

## Backup

Backup sử dụng lệnh copy file đến TFTP server

Backup file **startup-config**

```
# copy start tftp
```

Backup file **IOS**

```
# copy flash tftp
```

## Restore

Restore ta tiến hành copy theo chiều ngược lại với backup

```
# copy tftp start
# copy tftp flash
```
