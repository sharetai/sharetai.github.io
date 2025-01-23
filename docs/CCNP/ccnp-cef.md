---
layout: default
title: Packet Forwarding Mechanisms
nav_order: 110
parent: CCNP
---

# Packet Forwarding Mechanisms
{: .no_toc }

Cơ chế chuyển tiếp gói
{: .fs-6 .fw-300 }

---

## Table of contents
{: .no_toc .text-delta }

1. TOC
{:toc}

---

## Cisco Express Forwarding (CEF)
<br>
CEF là 1 kỹ thuật chuyển mạch IP ở lớp 3 do Cisco phát triển cho các sản phẩm Multilayer Switch (Switch Layer 3) và Router của mình. CEF được đánh giá là kỹ thuật chuyển mạch lớp 3 có tốc độ xử lý khá cao, giúp tối ưu hóa hiệu suất và sự linh động của mạng. CEF được tạo ra để khắc phục những khuyết điểm của các công nghệ chuyển mạch cũ khi nhận thấy những công nghệ chuyển mạch cũ làm tiêu tốn quá nhiều tài nguyên CPU để xử lý quá trình chuyển mạch nhưng không mang lại hiệu quả cao.
 
Trước khi tìm hiểu về CEF, ta sẽ xem qua cách thức hoạt động của các công nghệ chuyển mạch cũ trước khi CEF ra đời. Ở đây mình sẽ đưa ra 2 công nghệ chuyển mạch phổ biến đó là Process Switching và Fast Switching. 
 
___Process Switching___: là 1 kỹ thuật chuyển mạch chậm chạp, trước khi gói tin được gửi ra ngoài phải trải qua nhiều bước. Switch nhận gói tin từ interface đầu vào sau đó mở gói tin và so sánh địa chỉ IP đích với thông tin trong bảng định tuyến của mình. Nếu thông tin về đường đi đến mạng đích đã được lưu trong bảng định tuyến thì switch sẽ tìm địa chỉ MAC của next-hop tương ứng với mạng đích của gói tin.
 
Nếu chưa có địa chỉ MAC, switch sử dụng giao thức ARP để xác định địa chỉ MAC tương ứng với next-hop. Sau khi có được địa chỉ MAC, switch sẽ rewrite lại thông tin lớp 2 (địa chỉ MAC nguồn và MAC đích) của gói tin và chuyển gói tin sang interface đầu ra. Tiến trình sẽ hoạt động lặp đi lặp lại như vậy với mỗi gói tin switch nhận được. Toàn bộ quá trình trên đều được thực hiển bởi CPU do đó sẽ làm hao tốn 1 lượng lớn tài nguyên và gây độ trễ trong quá trình định tuyến.
 
___Fast Switching___: còn gọi là Route Caching, là phương pháp chuyển mạch cải tiến của process switching. So với cơ chế chuyển mạch sử dụng tài nguyên CPU để xử lý tất cả các gói tin đến thì Fast Switching sẽ chỉ xử lý gói tin đầu tiên qua các bước tương tự như Process Switching nhưng sau đó lưu cache lại các thông tin đã được xử lý. Các gói tin đi sau sẽ dựa trên thông tin đã được cache sẵn để đi đến mạng đích. Như vậy nếu như có 100 gói tin đi đến thì switch chỉ cần xử lý 1 gói tin đầu tiên, còn 99 gói tin còn lại sẽ được chuyển mạch dựa trên thông tin đã lưu lại của gói tin trước đó.
 
___CEF (Cisco Express Forwarding)___: hay còn gọi là Topology-base Switching, là phương thức chuyển mạch cho Cisco phát triển để áp dụng cho các dòng Multilayer Switch và Router của hãng. Các thiết bị này được trang bị thêm 1 bộ chip hardware đặc biệt gọi là Application-Specific Intergrated Circuits (ASICs) được lập trình sẵn và thiết kế để định tuyến giữa các Ethernet port với tốc độ cao. 
 
Mô hình chuyển mạch sử dụng CEF gồm 2 thành phần chính là Control Plane và Data Plane.

- __Control Plan__: có nhiệm vụ xây dựng và duy trì thông tin định tuyến bao gồm routing table và ARP table. Các thông tin từ các giao thức định tuyến sẽ được tập trung lưu trữ tại đây. Với mỗi gói tin ip đi đến sẽ được xác định chuyển ra interface nào với địa chỉ đích là bao nhiêu. Cơ chế Layer 3 routing của router đề cập ở trên hoạt động tương tự với cơ chế của control plane.
- __Data Plane__: làm nhiệm vụ định tuyến các gói tin dựa trên những thông tin học được từ control plane. Trong khi ở control plane mọi thứ đều được xử lý bởi CPU thì tại data plane quá trình xử lý định tuyến sẽ được thực hiện bằng phần cứng nhờ vào ASICs. Quá trình xử lý này còn được gọi là layer 3 switching.

![alt text](/docs/CCNP/img/CEF-1.png)

Với CEF, khi gói tin đi vào sẽ được xử lý trực tiếp tại data plane mà không cần phải di chuyển lên control plan. Do đó, quá trình xử lý không tiêu tốn tài nguyên CPU. Mặt khác, data plane hoạt động dựa trên phần cứng ASICs nên sẽ giúp cho CEF đạt được hiệu suất cao hơn rất nhiều so với các phương pháp định tuyến thông thường.
 
Tại data plane, CEF sẽ tạo ra 2 bảng là Forwarding Information Base (FIB table) và Adjacency Table.

- __FIB table__: được hình thành từ việc trích lọc các thông tin trong routing table. Nó cũng tương tự như 1 bảng định tuyến, và chỉ bao gồm các thôn tin tối thiểu đủ để forward gói tin mà không chứa thông tin về các giao thức định tuyến.
- __Adjacency table__: được hình thành từ việc trích lọc thông tin trong ARP table. Nó chứa thông tin về địa chỉ MAC của các node mạng liền kề (các node mạng được xem là liền kề khi chúng có thể liên lạc với nhau qua 1 thiết bị layer 2). Các thông tin trong Adjacency table được sử dụng trong quá trình rewrite thông tin lớp 2 của gói tin.

![alt text](/docs/CCNP/img/CEF-2.png)

_Quá trình trích lọc thông tin để xây dựng bảng FIB và bảng Adjacency_

![alt text](/docs/CCNP/img/CEF-3.png)

_Quá trình chuyển mạch gói tin của CEF_
 
Mặc định, CEF đã được enable tự động trên hầu hết các thiết bị sử dụng hệ điều hành Cisco IOS phiên bản 12.0 trở lên. Để kiểm tra hoạt động của CEF trên thiết bị ta gõ lệnh như sau: 

<img style="max-width: 600px" src="/docs/CCNP/img/CEF-4.png" />

Nếu như cef chưa được bật thì hệ thống sẽ trả về kết quả như hình bên dưới:

<img style="max-width: 600px" src="/docs/CCNP/img/CEF-5.png" />

Để bật chức năng CEF, ta gõ lệnh: 

<img style="max-width: 250px" src="/docs/CCNP/img/CEF-6.png" />

Để kiểm tra thông tin bảng Adjacency, ta gõ lệnh:

<img style="max-width: 300px" src="/docs/CCNP/img/CEF-7.png" />

<br>

{: .highlight-title }
> Note
>
> __CEF can be enabled in one of two modes:__ <br>
>
> __Central CEF mode__ - When CEF mode is enabled, the CEF FIB and adjacency tables reside on the route processor, and the route processor performs the express forwarding. You can use CEF mode when __line cards are not available for CEF switching__, or when you need to use features not compatible with distributed CEF switching. <br>
>
> __Distributed CEF (dCEF) mode__ - When dCEF is enabled, line cards maintain identical copies of the FIB and adjacency tables. __The line cards can perform the express forwarding by themselves__, and this relieves the main processor - Gigabit Route Processor (GRP) - of involvement in the switching operation. This is the only switching method available on the Cisco 12000 Series Router.

## RIB vs FIB
<br>
___RIB (Routing Information Base)___ có nguồn gốc từ control plane, không dùng cho forwarding. Mọi giao thức như OSPF, EIGRP, BGP đều có bảng RIB riêng và chọn ra những route tốt nhất để cố gắng cài đặt vào bảng RIB global để sau đó có thể chọn nó để chuyển tiếp.

___FIB (Forwarding Information Base)___ có nguồn gốc từ RIB, dùng cho forwarding, đưa ra quyết định chuyển tiếp dựa vào IP destination prefix.

<br>

## CAM vs TCAM
<br>

1 tiến trình đơn giản hóa được hiển thị trong hình bên dưới. Dữ liệu đi vào, tra cứu bảng _data table_ để tìm địa chỉ lưu trữ _action_ và 1 _action_ được chọn từ bảng _action table_. _Data table_ thường nằm trong CAM, _action table_ thường nằm trong RAM.

<img style="max-width: 800px" src="/docs/CCNP/img/ufispace_tcam_lookup_table_process.JPG" />

1 bảng thường được đặt trong _RAM (Random Access Memory)_ để thao tác tốc độ cao. Phần mềm cung cấp 1 địa chỉ và lấy dữ liệu từ bảng khớp với địa chỉ đó. Tuy nhiên, việc sử dụng RAM để tra cứu có thể mất nhiều chu kỳ để hoàn thành và điều đó không lý tưởng khi mục tiêu là tốc độ.

<img style="max-width: 800px" src="/docs/CCNP/img/ufispace_ram_vs_cam_lookup_table_ram.JPG" />

Đó là lúc _CAM (Content-Addressable Memory)_ xuất hiện. Nó thực hiện mọi việc theo cách ngược lại, trong khi dữ liệu được sử dụng làm chìa khóa để tìm kiếm địa chỉ nơi nó được đặt. Và theo bản chất thiết kế của CAM, việc tìm kiếm diễn ra song song, có nghĩa là việc tra cứu có thể được thực hiện trong một chu kỳ. Điều này làm cho CAM phù hợp hơn nhiều cho việc tra cứu bảng dữ liệu.

2 loại CAM khác nhau thường được sử dụng gọi là _BCAM (Binary CAM)_ và _TCAM (Ternary CAM)_.

BCAM, như tên của nó, là nơi dữ liệu ở trạng thái nhị phân, 0 hoặc 1. Việc tìm kiếm dữ liệu phải được khớp hoàn hảo. Nó phù hợp để tra cứu dữ liệu với các mục duy nhất như tra cứu địa chỉ MAC.

<img style="max-width: 800px" src="/docs/CCNP/img/ufispace_bcam_lookup_table.JPG" />

TCAM bổ sung thêm 1 trạng thái thứ ba,ở đây là X, có nghĩa là "DON'T CARE" hoặc "wildcard", do đó ngoài việc khớp 0 hoặc 1, một bit cụ thể có thể bị bỏ qua khi nó được đặt là "X". Trong ví dụ bên dưới, cả 1110X và 111XX đều khớp với dữ liệu 11101.

<img style="max-width: 800px" src="/docs/CCNP/img/ufispace_tcam_lookup_table.JPG" />

Khái niệm "DON'T CARE" có thể hữu ích trong định tuyến.

Ví dụ: khi viết 1.1.1.0/24, nó mô tả một dải địa chỉ IP từ 1.1.1.0 ~ 1.1.1.255. Số 24 cho biết 24 bit đầu tiên của địa chỉ IP phải khớp nhau và 8 bit cuối cùng là gì không quan trọng.

<img style="max-width: 800px" src="/docs/CCNP/img/ufispace_tcam_wildcard_beneft.JPG" />

Khi xử lý chính sách điều khiển lưu lượng, đôi khi bộ định tuyến chỉ nên quan tâm đến các phần của mẫu lưu lượng và bỏ qua các tham số khác. Trong cấu hình ACL bên dưới, "ANY" trong mục nhập đầu tiên có nghĩa là dữ liệu được gửi đến bất kỳ cổng nào ở đích sẽ khớp với quy tắc.

<img style="max-width: 800px" src="/docs/CCNP/img/ufispace_tcam_example.JPG" />

<br>

## Stateful Switchover (SSO)
<br>
Bộ định tuyến có dự phòng phần cứng có thể có nguồn điện kép và bộ xử lý tuyến đường _route processors (RPs)_.

![alt text](/docs/CCNP/img/sso.avif)

Tuy nhiên, nếu không có cấu hình bổ sung, việc chuyển tiếp gói tin Lớp 3 có thể bị gián đoạn. Khi quá trình chuyển đổi RP xảy ra, giao thức thiết lập láng giềng sẽ nháy, thao tác này sẽ xóa bảng định tuyến. Các mục CEF sẽ bị xóa khi bảng định tuyến bị xóa và lưu lượng không được định tuyến cho đến khi cấu trúc liên kết mạng được học lại và bảng chuyển tiếp được lập trình lại.

Việc kích hoạt các tính năng ___NonStop Forwarding (NSF)___ hoặc ___NonStop Routing (NSR)___ sẽ hướng dẫn bộ định tuyến giữ các mục CEF trong 1 thời gian giới hạn và tiếp tục chuyển tiếp các gói trong trường hợp RP bị lỗi cho đến khi mặt phẳng điều khiển phục hồi.

NSF với SSO giúp giảm khoảng thời gian người dùng không thể truy cập mạng sau khi chuyển đổi. Các thiết bị nhận biết NSF của Cisco giúp giảm thiểu các lỗi định tuyến trong các thiết bị hỗ trợ SSO, giảm thiểu tính không ổn định của mạng.

SSO Cisco Configuration

```
Router> enable
Router# configure terminal
Router(config)# redundancy
Router(config)# mode sso
Router(config-red)# end
Router# copy running-config startup-config
```

SSO Cisco Verification

```
show redundancy
crashdump-timeout
debug redundancy
show diag
show version
```

<br>

## Switching Database Manager (SDM) Template
<br>
Các Switch Cisco sử dụng _Ternary Content Addressable Memory (TCAM)_ để lưu trữ thông tin Lớp 2 và 3 nhằm tra cứu nhanh hơn, sử dụng _Switching Database Manager (SDM)_ để quản lý việc sử dụng bộ nhớ TCAM. Mẫu Cisco SDM Template liên quan đến các mẫu cấu hình giúp nâng cao việc sử dụng tài nguyên vật lý của bộ chuyển mạch Cisco.

Các mẫu SDM có thể được sử dụng để định cấu hình tài nguyên hệ thống dựa trên cách bộ chuyển mạch được vận hành trong mạng nhằm hỗ trợ các chức năng cụ thể hoặc để cân bằng việc sử dụng tài nguyên hệ thống.

<br>
