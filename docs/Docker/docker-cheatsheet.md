---
layout: default
title: Docker Cheatsheet
nav_order: 1
parent: Docker
---

# Docker Cheatsheet
{: .no_toc }

Một số lệnh làm quen với Docker
{: .fs-6 .fw-300 }

---



## Để tải về một image nào đó
{: .no_toc }

```shell
docker pull ubuntu
```

## Kiểm tra các images đang có
{: .no_toc }

```shell
docker images
docker images -a
```

## Để tạo và chạy một container
{: .no_toc }

```shell
docker run -it ubuntu
```

Chú ý có tham số `-it` để khi container chạy, làm việc ngay với terminal của Ubuntu. Tham số này có nghĩa là

- `-t` nó có nghĩa là tty, cho phép kết nối với terminal để tương tác
- `-i` có nghĩa duy trì mở stdin để nhập lệnh.

## Tạo và chạy container, muốn container tự xóa khi kết thúc thì thêm vào tham số `--rm`
{: .no_toc }

```shell
docker run -it --rm ubuntu
```

## Tạo và chạy container, khi container vừa chạy thì thực hiện ngay một lệnh nào đó
{: .no_toc }

```shell
docker run -it --rm ubuntu whoami
docker run -it --rm ubuntu ls -la
docker run -it --rm ubuntu /bin/bash
```

## Tạo và chạy container ở dưới nền kể cả khi đã thoát ra thì thêm vào tham số `-d`
{: .no_toc }

```shell
docker run -itd --rm ubuntu
```

## Kiểm tra các containers đang có
{: .no_toc }

```shell
docker ps
docker ps -a
```

## Chạy một lệnh trên container đang chạy nền
{: .no_toc }

```shell
docker exec -it <container_id> whoami
docker exec -it <container_id> /bin/bash
```

## Deploy web php
{: .no_toc }

Dockerfile
```
FROM php:7.2-apache
COPY src /var/www/html
```

build-docker.sh -> `bash build-docker.sh`
```
#!/bin/bash
name="sample-web"
docker rm -f $name
docker build --tag=$name .
docker run -p 2023:80 --name $name -itd $name
```

docker-compose.yml -> `docker-compose up -d`
```
version: "1.0"
services:
  sample-web:
    build: .
    ports:
      - "2023:80"
    volumes:
      - ./src:/var/www/html
```

## Docker clean all
{: .no_toc }

```shell
docker kill $(docker ps -aq)
docker rm $(docker ps -aq) --force
docker rmi $(docker images -aq) --force
```