---
layout: default
title: Deploy web challenge Php Apache Mysql
nav_order: 3
parent: CTFd
---

# Deploy web challenge Php Apache Mysql
{: .no_toc }

Bài viết này dùng để ghi lại các bước cơ bản để dễ dàng deploy một thử thách web Php Apache Mysql cho team nghiên cứu.
{: .fs-6 .fw-300 }

---

## Table of contents
{: .no_toc .text-delta }

1. TOC
{:toc}

---

Chuẩn bị folder với cấu trúc sau:

```
web-php-apache-mysql
   ├── db
   │   └── mydb.sql         // File db dùng để import
   ├── src
   │   └── index.php        // Src web
   ├── Dockerfile
   └── docker-compose.yml
```

## Dockerfile

```
FROM php:7.2-apache

RUN docker-php-ext-install mysqli pdo pdo_mysql
```

Giải thích thì:

|        | ý nghĩa 
| ------ | ------ 
| FROM | Lấy image từ docker hub làm môi trường chạy web. |
| RUN | Chạy lệnh khi build image. |

## docker-compose.yml

```
version: "3.9"
services:
    web-php-apache-mysql:
        container_name: web-php-apache-mysql
        build:
            context: .
            dockerfile: Dockerfile
        depends_on:
            - web-php-apache-mysql-db
        volumes:
            - ./src:/var/www/html
        ports:
            - 19064:80
    web-php-apache-mysql-db:
        container_name: web-php-apache-mysql-db
        image: mysql:5.7
        restart: always
        environment:
            MYSQL_ROOT_PASSWORD: YOURSECUREPASSWORD
            MYSQL_DATABASE: YOURDB
        volumes:
            - ./db:/docker-entrypoint-initdb.d
```

## Run docker-composer

`sudo docker-composer up`

Test lại bằng cách truy cập `localhost:19064`.
