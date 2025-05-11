---
layout: default
title: Chạy Docker với non-root user
nav_order: 5
parent: CTFd
---

# Chạy Docker với non-root user
{: .no_toc }

Bài viết này dùng để ghi lại các bước cơ bản để chayj Docker với người dùng không phải root.
{: .fs-6 .fw-300 }

---

## TABLE OF CONTENTS
{: .no_toc .text-delta }

1. TOC
{:toc}

---

Sẽ rất nguy hiểm nếu chạy Docker với quyền root. Khi hackers tấn công các ứng dụng đang chạy bên trong các containers và giành được quyền truy cập root vào máy chủ, kẻ tấn công sẽ có được hệ thống server. Có rất nhiều thành phần cần phải bảo mật khi chạy Docker:

* Nên sử dụng các phần mềm quét Docker.
* Một container chỉ nên chứa một phần mềm hoặc chương trình.
* Không sử dụng các image không rõ nguồn gốc.
* Xây dựng lại Dockerfile.
* ...

Trong các phương pháp để tăng tính bảo mật cho Docker, không sử dụng root để chạy image docker bằng cách tạo user để chạy image docker là cách dễ dàng thực hiện.

## Bước 1: Tạo và thêm user vào nhóm Docker

```
$ sudo adduser zeri
$ sudo usermod -aG docker zeri
```

Sau khi tạo xong, chỉ truy cập vào non-root user để chạy Docker

```
$ su - zeri
```

## Bước 2: Chỉnh sửa Dockerfile

Thêm vào

```
RUN useradd -u 8833 zeri
USER zeri
```
