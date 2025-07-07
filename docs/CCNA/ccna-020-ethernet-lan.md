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

Ethernet định ngĩa cách để truyền dữ liệu qua 1 loại cáp cụ thể và ở 1 tốc độ cụ thể. Ethernet định nghĩa giao thức hay nguyên tắc mà các Ethernet node phải tuân theo để trở thành 1 phần của Ethernet Lan.

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

__Hành vi đồng nhất trên mọi liên kết nhờ tầng liên kết dữ liệu Ethernet__

Dù Ethernet có nhiều chuẩn vật lý khác nhau, nó vẫn hoạt động như một công nghệ LAN duy nhất vì dùng chung chuẩn tầng liên kết dữ liệu. Chuẩn này quy định 1 header và trailer Ethernet thống nhất (là các byte dữ liệu phụ giúp Ethernet gửi dữ liệu trên LAN). __Dù dữ liệu truyền qua UTP, cáp quang hay ở tốc độ nào, header và trailer vẫn giữ nguyên định dạng__.

Các chuẩn vật lý tập trung vào việc truyền bit trên cáp, còn giao thức tầng liên kết dữ liệu của Ethernet tập trung vào việc gửi khung (frame) từ nút nguồn đến nút đích. __1 frame gồm header, trailer và dữ liệu được gói bên trong__. Các nút chỉ cần chuyển tiếp khung qua các liên kết cần thiết để đến đúng đích.

Hình minh họa: PC1 gửi khung Ethernet đến PC3, đi qua UTP đến SW1, qua cáp quang đến SW2 và SW3, rồi qua UTP đến PC3. Các liên kết này chạy ở 4 tốc độ khác nhau: 10 Mbps, 1 Gbps, 10 Gbps và 100 Mbps.

<img src="/docs/CCNA/img/ethernet-lan-Ethernet LAN Forwards a Data-Link Frame over Many Types of Links.png" style="max-width: 100%; width: 600px" />

## Cáp xoắn đôi (Twisted Pair)

Ethernet truyền dữ liệu qua cáp UTP bằng cách dùng dòng điện chạy trong các sợi dây. Có 2 phần: tạo mạch điện và truyền tín hiệu 0, 1.<br>
Trước hết, Ethernet định nghĩa cách dùng 2 dây trong 1 cặp xoắn để tạo thành 1 mạch kín, cho phép dòng điện chạy qua (như hình). Các cổng Ethernet của 2 thiết bị nối hai dây này thành vòng kín để dòng điện lưu thông.

<img src="/docs/CCNA/img/ethernet-lan-Creating One Electrical Circuit over One Pair to Send in One Direction.png" style="max-width: 100%; width: 600px" />

Để truyền dữ liệu, 2 thiết bị tuân theo một quy tắc mã hóa: thiết bị gửi thay đổi tín hiệu điện theo thời gian, còn thiết bị nhận giải mã các thay đổi đó thành các bit 0, 1. Ví dụ, 10BASE-T mã hóa bit 0 bằng cách chuyển từ điện áp cao sang thấp giữa khoảng thời gian 1/10.000.000 giây.<br>
Trong thực tế, các dây trong cáp UTP được xoắn lại (không song song như hình) để giảm nhiễu điện từ. Việc xoắn giúp triệt tiêu phần lớn nhiễu.

<img src="/docs/CCNA/img/ethernet-lan-cable-Twisted-Pair.png" style="max-width: 100%; width: 600px" />
<img src="/docs/CCNA/img/ethernet-lan-cable-Twisted-Pair-t568a-t568b.png" style="max-width: 100%; width: 400px" />

Liên kết Ethernet gồm: cáp UTP, đầu nối RJ-45 và cổng RJ-45 trên thiết bị. Cáp chứa các cặp dây đồng xoắn, chuẩn 10/100BASE-T dùng 2 cặp, chuẩn 1000BASE-T dùng 4 cặp. Đầu RJ-45 với 8 chân nối dây đồng với thiết bị, cho phép dòng điện truyền dữ liệu.<br>
Các thiết bị cần cổng RJ-45 để kết nối với đầu cáp RJ-45. Trên PC, cổng này thường nằm trên card mạng (NIC). Switch thường có nhiều cổng RJ-45 để nối nhiều thiết bị vào mạng.<br>
Ngoài RJ-45, switch Cisco còn hỗ trợ các loại cổng khác, với phần cứng (transceiver) có thể thay đổi sau khi mua. Ví dụ:
- __SFP__: Cho Gigabit.
- __SFP+__: Cùng kích thước SFP nhưng hỗ trợ tốc độ 10 Gbps.

<img src="/docs/CCNA/img/ethernet-lan-RJ-45 Connectors and Ports.png" style="max-width: 100%; width: 600px" />
<img src="/docs/CCNA/img/ethernet-lan-10-Gbps SFP+ with Cable Sitting Just Outside a Catalyst 3560CX Switch.png" style="max-width: 100%; width: 400px" />

Chuẩn 10BASE-T và 100BASE-T dùng 2 cặp dây UTP, mỗi cặp truyền dữ liệu theo 1 chiều. NIC phát ở cặp chân trên 1,2 và nhận ở cặp dưới 3,6; switch làm ngược lại.<br>
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

Cáp quang dùng lõi thủy tinh để truyền ánh sáng, thay đổi ánh sáng theo thời gian để mã hóa 0 và 1. Thủy tinh trong cáp là sợi thủy tinh mỏng, mềm, đặt giữa các lớp bảo vệ: cladding, buffer, strengthener và vỏ ngoài. Ánh sáng từ nguồn phát (optical transmitter) đi vào lõi (core), phản xạ trên lớp cladding giúp truyền đi xa. 3 lớp ngoài có tác dụng bảo vệ bên trong của cáp.<br>
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

{: .new-title }
> NOTE
>
> Nếu cần xem thêm về quang ethernet và SFP/SFP+, hãy xem (tmgmatrix.cisco.com).

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
Hub chỉ lặp lại tín hiệu điện ra tất cả các cổng (trừ cổng nhận vào), không đọc địa chỉ. Nếu 2 thiết bị gửi cùng lúc → collision. 

Nếu thay hub bằng switch, va chạm sẽ được tránh. Switch hoạt động ở tầng 2, đọc header và trailer của khung, xem địa chỉ MAC. Nếu phải gửi hai khung đến cùng đích, switch sẽ gửi từng khung một, khung còn lại được xếp hàng chờ.

Để tránh va chạm các thiết bị kết nối với hub phải dùng half-duplex: nếu đang nhận thì chờ trước khi gửi. Cơ chế điều phối dùng thuật toán __carrier sense multiple access with collision detection (CSMA/CD)__: nghe kênh → gửi → nếu va chạm thì phát tín hiệu nhiễu, đợi ngẫu nhiên rồi thử lại.

<img src="/docs/CCNA/img/ethernet-lan-Collision Occurring Because of LAN Hub Behavior.png" style="max-width: 100%; width: 500px" />

Ví dụ, nếu Archie bắt đầu gửi frame đủ sớm để Bob nhận được những bit đầu tiên của frame đó trước khi Bob cố gắng gửi frame của mình. Tại Bước 1B, Bob sẽ phát hiện rằng mình đang nhận một frame từ thiết bị khác, và theo logic half-duplex, Bob sẽ đơn giản chờ để gửi lại frame ở Bước 1B.