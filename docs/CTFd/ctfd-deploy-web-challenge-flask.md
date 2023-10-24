---
layout: default
title: Deploy web challenge Flask
nav_order: 4
parent: CTFd
---

# Deploy web challenge Flask
{: .no_toc }

Bài viết này dùng để ghi lại các bước cơ bản để dễ dàng deploy một thử thách web Flask cho team nghiên cứu.
{: .fs-6 .fw-300 }

---

## Table of contents
{: .no_toc .text-delta }

1. TOC
{:toc}

---

Chuẩn bị folder với cấu trúc sau:

```
web-flask
  ├── templates/
  │   └── vuln.html
  ├── docker-compose.yml
  ├── Dockerfile
  ├── app.py
  └── requirements.txt
```

## vuln.html

```
<html>
     <body>
   
      <h1>This site is vulnerable</h1>
      
   </body>
</html>
```

## app.py

```
from flask import Flask, render_template
app = Flask(__name__)

@app.route('/')
def vuln():
   return render_template('vuln.html')

if __name__ == '__main__':
   app.run()
```

## requirements.txt

```
Flask
```

## Dockerfile

```
FROM python:3.7-alpine

WORKDIR /usr/src/app

COPY requirements.txt ./
RUN pip install --no-cache-dir -r requirements.txt

COPY . .

CMD [ "python", "./app.py" ]
```

Giải thích thì:

|        | ý nghĩa 
| ------ | ------ 
| FROM python:3.7-alpine | Lấy image từ docker hub làm môi trường chạy web. |
| WORKDIR | Trỏ vào thư mục làm việc. |
| COPY | Copy file từ source vào destination (source là thư mục hiện tại, destination là thư mục bên trong docker) |
| RUN | Chạy lệnh khi build image. |
| CMD | Chỉ cho Docker biết lệnh nào sẽ được chạy khi container bắt đầu được chạy. |

## docker-compose.yml

```
version: "3.9"
services:
    web-flask:
        build: .
        ports:
            - "19062:5000"
        volumes:
            - .:/usr/src/app
```

Giải thích thì:

|        | ý nghĩa 
| ------ | ------ 
| version: "3.9" | Version của file docker-compose (cái này giữ nguyên).  |
| services | Chứa các container. Với mỗi service là tên của một container (tên container chọn tùy ý). |
| build | Chỉ ra vị trí đường dẫn đặt Dockerfile (như trên là trỏ về thư mục hiện tại). |
| ports | Kết nối port của máy host đến port của container (như trên thì 19062 là port của máy chủ, 5000 là port mặc định của dịch vụ flask). |
| volumes | Gắn đường dẫn trên host machine được sử dụng trên container. |

## Run docker-composer

`sudo docker-composer up`

Test lại bằng cách truy cập `localhost:19062`.
