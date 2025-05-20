---
layout: default
title: Ethernet LANs
nav_order: 20
parent: CCNA
---

# Ethernet LANs
{: .no_toc }

Cơ bản về Ethernet LAN
{: .fs-6 .fw-300 }

---

## TABLE OF CONTENTS
{: .no_toc .text-delta }

1. TOC
{:toc}

---

## Ethernet LANs

<h3> why? </h3>
Cần 1 chuẩn kết nối vật lý hay 1 nguyên tắc giao thức giữa các thiết bị đầu cuối.

<h3> what? </h3>
Cụm từ __Ethernet__ dùng để chỉ 1 họ các chuẩn mạng LAN quy định lớp vật lý và lớp liên kết dữ liệu của công nghệ mạng LAN có dây. __Ethernet LAN là chuẩn của Wired LAN__. Do Viện Kỹ sư Điện và Điện tử (IEEE) ban hành, bao gồm quy định về loại cáp (cabling), đầu nối (connector), quy tắc truyền thông (protocol rules) và mọi yếu tố cần thiết để xây dựng 1 mạng Ethernet.

__Ethernet__ là họ chuẩn __IEEE 802.3__ quy định cách truyền dữ liệu qua cáp đồng hoặc quang với nhiều tốc độ.<br>
Cáp đồng rẻ, truyền điện, khoảng cách ngắn.<br>
Cáp quang đắt, truyền ánh sáng, đi xa.<br>
Tên chuẩn cho biết tốc độ và loại cáp: __T__ là đồng, __X__ là quang.

Ví dụ về các loại Ethernet:<br>
<img src="/docs/CCNA/img/ethernet-lan-Examples of Types of Ethernet.png" style="max-width: 100%; width: 600px" />

{: .new-title }
> NOTE
>
> Có thể truy cập trang (www.EthernetAlliance.org) để xem roadmap mới nhất về Ethernet.<br>
> Hoặc [đây](/docs/CCNA/img/2025-Ethernet-Roadmap-2-Sided-Web-03-17-2025.pdf) để xem 2025 Ethernet Roadmap.

## Cáp xoắn đôi (Twisted Pair)

<img src="/docs/CCNA/img/ethernet-lan-cable-Twisted-Pair.png" style="max-width: 100%; width: 600px" />

Thông thường, NIC phát ở chân 1,2 và nhận ở 3,6; switch làm ngược lại.<br>
<img src="/docs/CCNA/img/ethernet-lan-Using One Pair for Each Transmission Direction with 10- and 100-Mbps Ethernet.png" style="max-width: 100%; width: 600px" />

Để NIC trên PC giao tiếp với switch, cáp UTP cần là cáp thẳng hay "straight-through cable". Cáp thẳng nối cùng chân ở 2 đầu (1–1, 2–2, 3–3, 6-6…), phù hợp nối PC với switch.<br>
<img src="/docs/CCNA/img/ethernet-lan-Ethernet Straight-Through Cable Concept.png" style="max-width: 100%; width: 600px" />

Cáp thẳng hoạt động đúng khi 2 thiết bị dùng cặp chân phát khác nhau. Nếu 2 thiết bị giống nhau (như switch–switch) cùng phát ở cùng chân, cần dùng cáp chéo hay "crossover cable". Cáp chéo sẽ nối chân phát của thiết bị này đến chân thu của thiết bị kia.

<img src="/docs/CCNA/img/ethernet-lan-Crossover Ethernet Cable.png" style="max-width: 100%; width: 350px" />

Quy tắc chọn cáp phù hợp: <br>
\- Cáp chéo: nếu 2 đầu phát trên cùng cặp chân. <br>
\- Cáp thẳng: nếu 2 đầu phát trên cặp chân khác nhau. <br>
<img src="/docs/CCNA/img/ethernet-lan-10BASE-T and 100BASE-T Pin Pairs Used.png" style="max-width: 100%; width: 650px" />

{: .new-title }
> NOTE
>
> Nếu sai loại cáp mà mạng vẫn hoạt động, đó là nhờ tính năng __auto-mdix__ của switch Cisco, tự động điều chỉnh để phù hợp.

Cáp 1000BASE-T (Gigabit Ethernet) khác với 10/100 Mbps: dùng 4 cặp dây, giữ nguyên như chuẩn cũ, thêm cặp chân 4–5 và 7–8.

## Cáp quang (Fiber optic)

<img src="/docs/CCNA/img/ethernet-lan-cable-Fiber-optic.png" style="max-width: 100%; width: 450px" />

Cáp quang dùng sợi thủy tinh để truyền ánh sáng mã hóa dữ liệu. Sợi quang linh hoạt, nằm giữa lõi cáp. Ánh sáng từ nguồn phát (optical transmitter) đi vào lõi (core), phản xạ trên lớp cladding giúp truyền đi xa. 3 lớp ngoài có tác dụng bảo vệ bên trong của cáp.<br>
<img src="/docs/CCNA/img/ethernet-lan-Components of a Fiber-Optic Cable.png" style="max-width: 100%; width: 450px" />

Multimode fiber (sợi quang đa mode): <br>
\- Dùng lõi (core) có đường kính lớn hơn, cho phép ánh sáng truyền theo nhiều góc (nhiều "mode"). <br>
\- Sử dụng đèn __LED__ làm nguồn phát sáng. <br>
\- Do nhiều mode ánh sáng truyền qua cùng lúc, chúng đến đích không đồng thời, gây hiện tượng suy hao và tán sắc, giới hạn khoảng cách truyền. <br>
\- Khoảng cách tối đa thường từ 300–400 mét (ví dụ: chuẩn 10GBASE-S). <br>
\- Ưu điểm: Chi phí thấp hơn do dùng thiết bị phát rẻ hơn. <br>
\- Ứng dụng: Thường dùng trong nội bộ tòa nhà, khuôn viên văn phòng gần nhau.

<img src="/docs/CCNA/img/ethernet-lan-Transmission on Multimode Fiber with Internal Reflection.png" style="max-width: 100%; width: 450px" />

Single-mode fiber (sợi quang đơn mode): <br>
\- Có lõi nhỏ hơn nhiều (khoảng 1/5 đường kính lõi multimode). <br>
\- Chỉ cho phép ánh sáng truyền theo một góc duy nhất, giảm tối đa sự suy hao và tán sắc. <br>
\- Dùng nguồn phát __LASER__ chính xác và mạnh. <br>
\- Khoảng cách tối đa có thể lên tới 10–30 km (ví dụ: chuẩn 10GBASE-LR hoặc 10GBASE-E). <br>
\- Chi phí cao hơn: Do dùng module SFP/SFP+ đắt hơn. <br>
\- Ứng dụng: Kết nối giữa các tòa nhà cách xa, giữa các văn phòng trong khu công nghiệp, mạng diện rộng (WAN).

<img src="/docs/CCNA/img/ethernet-lan-Transmission on Single-Mode Fiber with Laser Transmitter.png" style="max-width: 100%; width: 450px" />

Cáp quang dùng 2 sợi – 1 sợi phát (__TX__), 1 sợi thu (__RX__). <br>
<img src="/docs/CCNA/img/ethernet-lan-Two Fiber Cables with Tx Connected to Rx on Each Cable.png" style="max-width: 100%; width: 450px" />

Để sử dụng cáp quang với switch Ethernet, cần dùng loại switch có cổng tích hợp hỗ trợ chuẩn Ethernet quang cụ thể, hoặc loại switch có cổng dạng module, cho phép thay đổi chuẩn Ethernet bằng cách thay module. Ví dụ: SFP là module nhỏ dùng cho cổng GE, SFP+ cùng size với SFP nhưng dùng cho cổng 10GE..

Một số chuẩn Ethernet quang 10G: <br>
<img src="/docs/CCNA/img/ethernet-lan-A Sampling of IEEE 802.3 10-Gbps Fiber Standards.png" style="max-width: 100%; width: 600px" />

## Truyền dữ liệu trong mạng ethernet

<h3> how? </h3>

Ethernet sử dụng chung một tiêu chuẩn tầng liên kết dữ liệu (data-link) cho dù chuẩn tầng vật lý có thể khác nhau. Giao thức tầng liên kết định nghĩa __frame ethernet, gồm: header ở đầu, dữ liệu ở giữa và trailer ở cuối__. Cấu trúc phổ biến của frame gồm các trường: <br>
<img src="/docs/CCNA/img/ethernet-lan-Commonly Used Ethernet Frame Format.png" style="max-width: 100%; width: 600px" />

| Trường           | Độ dài (bytes) | Mô tả                                                                |
|:-----------------|:---------------|:---------------------------------------------------------------------|
| Preamble         | 7              | Đồng bộ hóa tín hiệu.                                                |
| SFD              | 1              | Báo hiệu byte tiếp theo là MAC đích.                                 |
| MAC đích         | 6              | Địa chỉ thiết bị nhận.                                               |
| MAC nguồn        | 6              | Địa chỉ thiết bị gửi.                                                |
| Type             | 2              | Loại giao thức tầng mạng bên trong (thường là IPv4 hoặc IPv6).       |
| Data & Pad       | 46–1500        | Dữ liệu thực tế, thêm pad nếu thiếu để đủ tối thiểu 46 byte.         |
| FCS              | 4              | Kiểm tra lỗi (sử dụng CRC - Cyclic Redundancy Check).                |

__Địa chỉ MAC (Media Access Control)__ là địa chỉ __48-bit (6 byte)__, thường viết dạng thập lục phân. Ví dụ: D8-D3-85-EB-12-E3. Địa chỉ MAC được chia thành: <br>
\- __OUI (3 byte đầu)__: Do IEEE cấp cho nhà sản xuất. (D8-D3-85 như ví dụ là HP - Hewlett Packard) <br>
\- __Phần còn lại (3 byte sau)__: Nhà sản xuất tự gán, đảm bảo không trùng lặp.

<img src="/docs/CCNA/img/ethernet-lan-layer2-encapsulation.gif" style="max-width: 100%; width: 750px" />

__IP (Internet Protocol)__: Là một địa chỉ logic được gán cho một thiết bị trên mạng. Không giống như MAC, địa chỉ IP có thể thay đổi và được cấu hình thủ công hoặc tự động qua DHCP.

__ARP (Address Resolution Protocol)__: Là một giao thức mạng được sử dụng để chuyển đổi giữa địa chỉ IP và địa chỉ MAC. Khi một thiết bị muốn gửi dữ liệu đến một thiết bị khác, nó sẽ sử dụng ARP để tìm ra địa chỉ MAC tương ứng với địa chỉ IP đích.

<img src="/docs/CCNA/img/ethernet-lan-arp.gif" style="max-width: 100%; width: 750px" />

3 loại địa chỉ: <br>
\- __Unicast__: Một thiết bị cụ thể. <br>
\- __Broadcast__: Tất cả thiết bị trên LAN (__FFFF.FFFF.FFFF__). <br>
\- __Multicast__: Một nhóm thiết bị cụ thể trên LAN (__0100.5EXX.XXXX__).

Trường Type cho biết loại gói tin tầng 3 chứa trong phần dữ liệu của frame. Trường này giúp thiết bị đích biết cách xử lý phần dữ liệu. Ví dụ: <br>
\- __0800__ cho __IPv4__. <br>
\- __86DD__ cho __IPv6__.

Trường __Frame Check Sequence (FCS)__ dùng để phát hiện lỗi truyền. Sender tính toán __CRC__ và gán vào FCS; receiver cũng tính CRC và so sánh. Nếu không khớp → frame bị lỗi và bị loại bỏ. Ethernet không phục hồi lỗi, chỉ phát hiện và loại bỏ. __TCP__ ở tầng trên sẽ xử lý phục hồi bằng việc phát hiện bị mất gói và gửi lại.

<h3> Truyền Frame Ethernet qua Switch và Hub </h3>
<br>
__Gửi qua Switch (Full-Duplex)__ <br>
Switch hiện đại cho phép full-duplex: gửi và nhận đồng thời, không xảy ra va chạm.

<img src="/docs/CCNA/img/ethernet-lan-Example of Sending Data in a Modern Ethernet LAN.png" style="max-width: 100%; width: 650px" />

Ví dụ truyền giữa PC1 và PC2 qua 2 switch: <br>
(1) PC1 gửi frame → địa chỉ nguồn là MAC PC1, đích là MAC PC2 <br>
(2) SW1 nhận → gửi qua G0/1 đến SW2 <br>
(3) SW2 nhận → gửi qua F0/2 đến PC2 <br>
(4) PC2 nhận và xử lý frame

__Gửi qua Hub (Half-Duplex)__ <br>
Hub chỉ lặp lại tín hiệu điện, không đọc địa chỉ. Nếu 2 thiết bị gửi cùng lúc → collision. Vì thế phải dùng half-duplex: nếu đang nhận thì chờ trước khi gửi. Cơ chế điều phối dùng thuật toán __carrier sense multiple access with collision detection (CSMA/CD)__: <br>
\- Nghe đường truyền → nếu rảnh thì gửi. <br>
\- Nếu đang gửi mà phát hiện collision: Gửi jamming signal. Chờ ngẫu nhiên rồi thử lại.

<img src="/docs/CCNA/img/ethernet-lan-Collision Occurring Because of LAN Hub Behavior.png" style="max-width: 100%; width: 500px" />

Ví dụ, nếu Archie bắt đầu gửi frame đủ sớm để Bob nhận được những bit đầu tiên của frame đó trước khi Bob cố gắng gửi frame của mình. Tại Bước 1B, Bob sẽ phát hiện rằng mình đang nhận một frame từ thiết bị khác, và theo logic half-duplex, Bob sẽ đơn giản chờ để gửi lại frame ở Bước 1B.