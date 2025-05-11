---
layout: default
title: Hosting hệ thống CTFd
nav_order: 1
parent: CTFd
---

# Hosting hệ thống CTFd
{: .no_toc }

Bài viết này dùng để ghi lại các bước cơ bản để dễ dàng hosting một hệ thống CTFd cho team nghiên cứu.
{: .fs-6 .fw-300 }

---

## TABLE OF CONTENTS
{: .no_toc .text-delta }

1. TOC
{:toc}

---

**[ Cài đặt ]**

Trang này hướng dẫn cài đặt CTFd lên server, các chỉ dẫn này có thể dễ dàng tìm được ở [CTFd Docs](https://docs.ctfd.io/) trang [Installation](https://docs.ctfd.io/docs/deployment/installation).

Nếu lười đọc có thể thực hiện theo các bước dưới đây (tuy nhiên chỉ phù hợp tại thời điểm mình viết trang này, [CTFd Docs](https://docs.ctfd.io/) có thể cập nhật thêm về sau).

**Server mình dùng để host cấu hình CPU 4GB ram, ổ cứng đâu đó 20GB, hệ điều hành Ubuntu.**

*(Một lần nữa, mình khuyến khích nên đọc hướng dẫn [CTFd Docs](https://docs.ctfd.io/) để hiểu rõ chi tiết).*

## Install [Docker](https://docs.docker.com/engine/install/)

```
$ sudo apt-get remove docker docker-engine docker.io containerd runc
$ sudo apt-get update
$ sudo apt-get install \
    ca-certificates \
    curl \
    gnupg \
    lsb-release
$ curl -fsSL https://download.docker.com/linux/ubuntu/gpg | sudo gpg --dearmor -o /usr/share/keyrings/docker-archive-keyring.gpg
$ echo \
  "deb [arch=$(dpkg --print-architecture) signed-by=/usr/share/keyrings/docker-archive-keyring.gpg] https://download.docker.com/linux/ubuntu \
  $(lsb_release -cs) stable" | sudo tee /etc/apt/sources.list.d/docker.list > /dev/null
$ sudo apt-get update
$ sudo apt-get install docker-ce docker-ce-cli containerd.io
```

Test cài đặt thành công.

```
$ sudo docker run hello-world
```

## Install [Docker Compose](https://docs.docker.com/compose/install/)

```
$ sudo curl -L "https://github.com/docker/compose/releases/download/1.29.2/docker-compose-$(uname -s)-$(uname -m)" -o /usr/local/bin/docker-compose
$ sudo chmod +x /usr/local/bin/docker-compose
$ sudo ln -s /usr/local/bin/docker-compose /usr/bin/docker-compose
```

Test cài đặt thành công.

```
$ docker-compose --version
docker-compose version 1.29.2, build 1110ad01
```

## Clone CTFd

`git clone https://github.com/CTFd/CTFd.git`

## Run docker-compose

`docker-compose up`

*(truy cập folder CTFd trước khi chạy câu lệnh trên)*

```
$ cd CTFd_HCMUTE/CTFd/
```

Đến đây có thể mở browser trình duyệt quét truy cập `localhost` để xem kết quả *(như hình bên dưới là thành công).*

![image](https://user-images.githubusercontent.com/56266496/163779758-c46ee17d-9a83-406a-97b3-511095818d5e.png)
