---
layout: default
title: Junos CLI
nav_order: 1
parent: JN0
---

# Junos OS command-line
{: .no_toc }

Các dòng lệnh hệ điều hành Junos
{: .fs-6 .fw-300 }

---

## TABLE OF CONTENTS
{: .no_toc .text-delta }

1. TOC
{:toc}

---

## CLI basics

```
Amnesiac (ttyu0)

login: root
Password:

--- JUNOS 12.1X47-D30.4 built 2015-11-13 14:47:35 UTC
root@router% cli
root@router> configure
Entering configuration mode

[edit]
root@router#
```

## Phím Điều Khiển Theo Kiểu Emacs

Giao diện dòng lệnh (CLI) hỗ trợ các chuỗi phím theo kiểu Emacs cho phép di chuyển con trỏ trên dòng lệnh và xóa các ký tự hoặc từ cụ thể.

* Ctrl+b: Di chuyển con trỏ sang trái một ký tự;
* Ctrl+a: Di chuyển con trỏ đến đầu dòng lệnh;
* Ctrl+f: Di chuyển con trỏ sang phải một ký tự;
* Ctrl+e: Di chuyển con trỏ đến cuối dòng lệnh;
* Delete và Backspace: Xóa ký tự trước con trỏ;
* Ctrl+d: Xóa ký tự tại con trỏ;
* Ctrl+k: Xóa từ con trỏ đến cuối dòng;
* Ctrl+u: Xóa tất cả các ký tự và huỷ lệnh hiện tại;
* Ctrl+w: Xóa toàn bộ từ bên trái của con trỏ;
* Ctrl+l: Vẽ lại dòng lệnh hiện tại;
* Ctrl+p, Ctrl+n: Lặp lại lệnh trước và lệnh tiếp theo trong lịch sử lệnh tương ứng;

-------------------------

* Esc+d: Xóa từ bên phải;
* Esc+b: Di chuyển con trỏ lùi lại một từ mà không xóa;
* Esc+f: Di chuyển con trỏ tới phía trước một từ mà không xóa.

Vui lòng lưu ý rằng khi sử dụng phím Esc, bạn phải nhả phím và nhấn lại cho mỗi lần xuất hiện. Hành động này khác với phím Ctrl, mà bạn có thể giữ xuống cho nhiều lần xuất hiện.

## Loading a Factory-Default Configuration

```
[edit]
root@router# load factory-default
warning: activating factory configuration

[edit]
root@router# set system root-authentication plain-text-password
New password:
Retype new password:

[edit]
root@router# commit
commit complete
```

## Khác

```
# Show cấu hình ở dạng lệnh set
root@router> show configuration | display set | no-more
root@router# run show configuration | display set | no-more

# Show compare cấu hình thay đổi khi chưa commit
root@router# show | compare | no-more

# Xoá toàn bộ cấu hình thay đổi khi chưa commit
root@router# rollback 0

# Nếu đã commit rồi mà muốn quay lại cấu hình trước
root@router# rollback 1
root@router# commit

# Commit
root@router# commit
root@router# commit check
root@router# commit and-quit

# Thêm comment
[edit]
root@router# edit interfaces

[edit interfaces]
root@router# annotate ge-0/0/0 "SRT-to-AGG"

[edit interfaces]
root@router# commit
commit complete

[edit interfaces]
root@router# run show configuration interfaces
/* SRT-to-AGG */
ge-0/0/0 {
    apply-groups vlan_tag;
    unit 10 {
        vlan-id 10;
        family inet {
            address 192.168.1.1/24;
        }
    }
}
```