---
layout: default
title: SRE
nav_order: 1
parent: RE
---

# Software Reverse Engineering
{: .no_toc }

Kỹ thuật dịch ngược mã nguồn phần mềm
{: .fs-6 .fw-300 }

---

## Table of contents
{: .no_toc .text-delta }

1. TOC
{:toc}

---

## Software Engineering Review

- Các nhà phát triển viết code bằng các ngôn ngữ bậc cao như C/C++
- Code này sau đó được biên dịch thành mã máy - chuỗi byte mà CPU có thể hiểu được
- Quá trình dịch ngược là quá trình chuyển đổi chuỗi byte này thành các `assembly instructions` - hướng dẫn hợp ngữ
- Với tư cách là các kỹ sư dịch ngược, chuỗi byte này sẽ là điểm khởi đầu của chúng ta

## Compilation Review

- Biên dịch một chương trình là một quá trình đa giai đoạn*
    - Tiền xử lý (Preprocessing)
    - Biên dịch (Compilation)
    - Hợp ngữ (Assembly)
    - Liên kết (Linking)
- Kết quả là mã máy được chạy trên CPU
- Những bước này thường được thực hiện tự động
- Sau khi đi qua những bước này, một tệp thực thi được tạo ra

*Phần cảnh báo: Đây là những lĩnh vực nghiên cứu vô cùng phức tạp, và ta chỉ đang đề cập đến một cái nhìn tổng quan rất cao.

### Tiền xử lý mã nguồn, thực hiện:

- Xóa bỏ các comment
- Mở rộng Macro
- Mở rộng Include
- Biên dịch có điều kiện (IFDEF)

### Biên dịch chuyển đổi kết quả của bước tiền xử lý thành các hướng dẫn hợp ngữ

Compilers – Ví dụ

![](/docs/RE/img/01.png)

### Trình hợp ngữ
- Trình hợp ngữ chuyển đổi mã hợp ngữ thành các mã opcodes nhị phân
- Mỗi hướng dẫn được biểu diễn bằng một mã opcode nhị phân
    - mov rax,1 = 0x48C7C001000000
- Trình hợp ngữ sẽ tạo ra một tệp đối tượng (object file)
    - Tệp đối tượng chứa mã máy
    - Tệp này sẽ chứa các trường để được điền bởi trình liên kết (linker)

Assemblers – Ví dụ

![](/docs/RE/img/02.png)

### Liên kết
- Cần thêm nhiều công việc trước khi mã đối tượng có thể được thực thi
    - Điểm vào (`entry point`), hoặc hướng dẫn khởi đầu (`starting instruction`) phải được xác định
- Được sử dụng để định nghĩa các khu vực bộ nhớ trên các nền tảng nhúng
    - Thường được thực hiện thông qua tập lệnh liên kết (linker scripts)
- Kết quả của quá trình liên kết là chương trình thực thi cuối cùng

Linking – Ví dụ

![](/docs/RE/img/03.png)

## Các Định dạng Đầu ra
- Kết quả của quá trình biên dịch có thể có nhiều định dạng:
    - PE (Windows)
    - ELF (Linux)
    - Mach-O (OSX)
    - COFF/ECOFF
- Tệp đầu ra này thường là điểm khởi đầu của bạn như một kỹ sư dịch ngược

## SE Review: Pixelated Edition

![](/docs/RE/img/04.png)

## Kiến thức Cơ bản về Kiến trúc Máy tính 101
- Khi một chương trình đang chạy, phải xảy ra các bước sau:
1. Một hướng dẫn được đọc vào bộ nhớ.
2. Hướng dẫn được xử lý bởi Đơn vị Logic và Tính toán Số học (Arithmetic Logic Unit).
3. Kết quả của hoạt động được lưu vào các thanh ghi (registers) hoặc bộ nhớ.

![](/docs/RE/img/05.png)

## Kiến trúc x86_64
- Chúng ta sẽ tập trung vào tập lệnh x86-64 của Intel.
    - Đây là phiên bản 64 bit của tập lệnh x86.
    - Bao gồm nhiều chế độ hoạt động để tương thích ngược.
- Phiên bản gốc được tạo ra bởi AMD vào năm 2000.
- Thường được sử dụng trong máy tính để bàn và máy tính xách tay.

## x86_64: Các thanh ghi (Registers)
- Các thanh ghi là các khu vực lưu trữ nhỏ được sử dụng bởi bộ xử lý.
- Hợp ngữ x86_64 sử dụng 16 thanh ghi mục đích chung có độ rộng 64 bit.

![](/docs/RE/img/X86_64-registers.svg)

- RIP: Con trỏ hướng dẫn (Instruction pointer)
   - Chỉ đến hướng dẫn tiếp theo sẽ được thực thi
   - Độ rộng 64 bit
- RFLAGS: Lưu trữ các cờ được sử dụng để điều khiển luồng xử lý của bộ xử lý
- FPR0-FPR7: Các thanh ghi kiểm soát và trạng thái dấu phẩy động
- RBP/RSP: Xử lý và sử dụng ngăn xếp

