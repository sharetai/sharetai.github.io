---
layout: default
title: Deploy programming challenge
nav_order: 6
parent: CTFd
---

# Deploy programming challenge
{: .no_toc }

Bài viết này dùng để ghi lại các bước cơ bản để dễ dàng deploy một thử thách programming cho team nghiên cứu.
{: .fs-6 .fw-300 }

---

## TABLE OF CONTENTS
{: .no_toc .text-delta }

1. TOC
{:toc}

---

## File Python

Chương trình chính cho thử thách

Dưới đây là chương trình mẫu cho thử thách tính cộng

**sum.py**

```
#!/usr/bin/python3
import random

def main():

    print("Xin chào người chơi.")
    print("Bạn học phép cộng ➕ rồi đúng chứ. Lấy máy tính ra đi nào.")

    for i in range(2, 1000):
        ints = []
        sum = 0
        for j in range(i):
            rd = random.randint(100, 999)
            ints.append(rd)
            sum += rd
        print(f"[+] Cho các số sau: {' '.join([str(int) for int in ints])}")
        ans = input("[+] Tìm tổng: ")
        if str(ans) == str(sum):
            print("Đúng rồi. Thử lại nào.")
        else :
            print("Sai rồi, Tiếc quá.")
            exit()
            
    print("Cộng tốt đấy. Phần thưởng cho bạn đây: Flag{programming}")

if __name__ == '__main__':
    main()
```

## File script timeout

File script dùng tạo timeout cho kết nối, khi hết thời gian mà người chơi chưa giải được sẽ đóng kết nối.

**timeout.sh**

```
#!/bin/bash
# $1: timeout (5,10,12,..)
# $2: python file name (pro1.py, pro2.py,..)

timeout --signal=SIGKILL $1 stdbuf -i 0 -o 0 -e 0 /usr/bin/python3 $2
echo -e '\nTimeout!'
```

## Tạo file service cho challenge

Tạo file service để chạy challenge như một dịch vụ trên linux

```
$ sudo cat >> /etc/systemd/system/pro.service
[Unit]
Description=Pro

[Service]
Type=simple

ExecStart=socat -v -dd TCP-LISTEN:28061,fork EXEC:"bash /home/debian/timeout.sh 30 /home/debian/sum.py"
Restart=always

[Install]
WantedBy=multi-user.target
^D

$ sudo systemctl daemon-reload
$ sudo systemctl restart pro.service
```

## Kết quả

Dùng máy khác làm client để kiểm tra kết nối

```
$ nc <IP_ADDRESS> 28061
Xin chào người chơi.
Bạn học phép cộng ➕ rồi đúng chứ. Lấy máy tính ra đi nào.
[+] Cho các số sau: 670 821
[+] Tìm tổng:
```
