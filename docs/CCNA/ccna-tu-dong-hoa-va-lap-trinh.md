---
layout: default
title: Tự động hóa và lập trình
nav_order: 98
parent: CCNA
---

# Network Automation and Programmability
{: .no_toc }

Tự động hóa mạng và khả năng lập trình
{: .fs-6 .fw-300 }

---

## Table of contents
{: .no_toc .text-delta }

1. TOC
{:toc}

---

## WHY?
<br>
__Tự động hóa mạng__ là quá trình tự động hóa việc cung cấp, sắp xếp, quản lý, cấu hình, xử lý lỗi. Giảm tương tác giữa người với máy, giảm lỗi của con người. Tiết kiệm thời gian và công sức lao động thủ công của con người. Đảm bảo tính nhất quán trong cấu hình, đảm bảo sự quen thuộc với cấu hình của từng thiết bị, giảm lỗi cấu hình tối thiểu, giúp ích trong việc khắc phục sự cố và tạo báo cáo.

<h3> Traditional Network Management </h3>
Ở mạng truyền thống, chỉ có thể quản lý từng thiết bị mạng một bằng cách sử dụng SSH. Tốn nhiều thời gian, công sức và dễ xảy ra lỗi của con người. Không hiệu quả trong một doanh nghiệp lớn và cũng không mở rộng quy mô tốt. Thách thức: <br>
\- Vấn đề về khả năng mở rộng <br>
\- Sự phức tạp trong quản lý <br>
\- Xử lý lỗi chậm hơn <br>

<h3> Controller-Based Networks </h3>
Mạng dựa trên Bộ điều khiển sử dụng phần mềm hoặc thiết bị điều khiển để tự động hóa các hoạt động mạng. Cho phép quản lý tập trung cấu hình thiết bị mạng và tự động cấu hình, vận hành mạng thông qua Giao diện lập trình ứng dụng _(API - Application Programming Interfaces)_. Tự động hóa mạng thông minh giúp quản lý mạng dễ dàng hơn so với mạng truyền thống vì mọi cài đặt cấu hình đều có thể dễ dàng được quản lý trong GUI của bộ điều khiển.

<br>

## Network Programmability – Python, Git, GitHub, and CI/CD

<h3> Python </h3>
Python là một trong những ngôn ngữ lập trình sử dụng phổ biến để lập trình mạng.

<h3> Git </h3>
Git là một hệ thống kiểm soát phiên bản, theo dõi các thay đổi trong mã nguồn và tệp, lưu trữ mã, cộng tác với người khác, phân nhánh.

<h3> GitHub </h3>
Tương tự Git nhưng có thêm giao diện web.

<h3> CI/CD </h3>
CI/CD là tên viết tắt của 3 mô hình luồng tự động: Tích hợp liên tục (_Continuous Integration_), Phân phối liên tục (_Continuous Delivery_) vầ Triển khai liên tục (_Continuous Deployment_). Là một tập hợp các nguyên tắc và quy trình vận hành cho phép các nhóm phát triển ứng dụng cung cấp các thay đổi mã để lập trình mạng thường xuyên và đáng tin cậy hơn. Đây là một trong những phương pháp hay nhất mà các nhóm DevOps áp dụng. CI/CD là một phương pháp linh hoạt và cho phép các nhóm phát triển phần mềm tập trung vào các yêu cầu kinh doanh, chất lượng mã và bảo mật vì các bước triển khai được tự động hóa.

<br>

## Data Serialization Formats – JSON, YAML, and XML
<br>
Data serialization là kỹ thuật chuyển đổi dữ liệu có cấu trúc thành định dạng cho phép lưu trữ hoặc chia sẻ. Các hệ thống khác nhau có kiến ​​trúc hoặc cơ khác nhau, là thách thức, là lý do tại sao cần chuẩn hóa dữ liệu cho phép chia sẻ trên nhiều ứng dụng khác nhau.

JSON – JavaScript Object Notation <br>
XML – Extensible Markup Language <br>
YAML: YAML Ain’t Markup Language <br>

<br>

## Web API Services – SOAP vs REST
<br>
Giao diện lập trình ứng dụng (Application Programming Interface - API) là giao diện cho phép các ứng dụng hoặc chương trình máy tính giao tiếp trực tiếp với nhau, biểu diễn các chức năng và quy trình thông qua đường dẫn dịch vụ hoặc URL. Web Services là loại API thường chạy qua HTTP/HTTPS. Hai loại API chính được sử dụng cho dịch vụ web chạy trên Internet và thường sử dụng HTTP/HTTPS là SOAP và REST.

SOAP - Simple Object Access Protocol <br>
REST - Representational State Transfer <br>

<br>

## Model-Driven Programmability: NETCONF & RESTCONF
<br>
Thách thức trong việc cấu hình các thiết bị mạng bằng CLI truyền thống gia tăng, các giao thức quản lý mạng (SNMP, NETCONF, RESTCONF) ra đời.

NETCONF - Network Configuration Protocol. Là giao thức cấu hình mạng và quản lý mạng. Hoạt động theo mô hình máy khách-máy chủ trong đó máy khách NETCONF giao tiếp với máy chủ NETCONF trên thiết bị mạng. Thường sử dụng các giao thức truyền tải an toàn như SSH (Secure Shell) hoặc TLS (Transport Layer Security). Lợi ích từ các tính năng bảo mật được cung cấp bởi các giao thức truyền tải an toàn cơ bản (SSH, TLS).

RESTCONF - RESTful Network Configuration Protocol. Là phương pháp tiếp cận dựa trên RESTful API để cập nhật và thay đổi cấu hình mạng. Tuân thủ các nguyên tắc RESTful, coi tài nguyên mạng là tài nguyên web. Giao tiếp dựa trên các phương thức HTTP chuẩn (GET, POST, PUT, DELETE) để cấu hình và truy xuất. Hoạt động trên các giao thức HTTP hoặc HTTPS chuẩn, giúp nó thân thiện với tường lửa. Dựa trên HTTPS để giao tiếp an toàn, kế thừa các tính năng bảo mật từ chuẩn HTTP Secure.

<br>

## Configuration Management Tools – Ansible, Chef, Puppet
<br>
__<u>Ansible</u>__ <br>
\- Ngôn ngữ __python__, định dạng __yaml__ <br>
\- Mô hình __agentless__ (only master) <br>
\- Agent __push__ cấu hình cho node mạng <br>
\- Sử dụng __SSH__ NETCONF <br>
\- File cấu hình gọi là __playbook__ với các __task__ <br>

__<u>Chef</u>__ <br>
\- Ngôn ngữ __ruby__ <br>
\- Mô hình __master-agent__ <br>
\- Agent __pull__ cấu hình từ master <br>
\- Sử dụng REST <br>
\- File cấu hình gọi là __cookbook__ <br>
\- __Recipe__ là mã được triển khai <br>

__<u>Puppet</u>__ <br>
\- Ngôn ngữ __ruby__ <br>
\- Mô hình __master-agent__ <br>
\- Agent __pull__ cấu hình từ master <br>
\- Sử dụng REST <br>
\- Các mẫu trong file cấu hình gọi là __module__ <br>
\- __Manifest__ là mã được triển khai <br>

<br>

## SDN – Software Defined Networking
<br>
Tương lai của mạng là tự động hóa. Trong mạng truyền thống, hiện tại quản lý bằng các phương pháp ___box-by-box___ sử dụng CLI, GUI, SNMP, SSH hoặc telnet. Gặp các vấn đề khi triển khai các thiết bị mới hay nâng cấp thiết bị mới, cấu hình thủ công, quản lý sai sót, không tối ưu hóa được tài nguyên mạng.

___Software Defined Networking (SDN)___ là công nghệ kiểm soát và quản lý mạng cho phép các phương pháp tiếp cận linh hoạt và có lập trình để giám sát và cấu hình mạng. Với SDN, các nhà khai thác mạng hoặc kỹ sư có thể sửa đổi và kiểm soát lưu lượng từ bộ điều khiển tập trung mà không cần thủ công vào từng thiết bị. Có thể tự động cập nhật các thay đổi về cấu hình hay các chính sách.

<br>

__3 mặt phẳng:__

__1. Data Plane__ Là mặt phẳng chuyển tiếp dữ liệu. So khớp địa chỉ đích với bảng định tuyến để chuyển tiếp dữ liệu. <br>
__2. Control Plane__ Quyết định các chuyển tiếp dữ liệu. Xây dựng bảng định tuyến, mac, arp, stp. <br>
__3. Management Plane__ Quản lý các thiết bị mạng bằng CLI sử dụng SSH/telnet hay GUI sử dụng HTTP/HTTPS. <br>

Khác với mạng truyền thống, mặt phẳng điều khiển trong SDN được tách biệt và được triển khai trong phần mềm được lưu trữ trên máy chủ, cho phép quản lý các thiết bị mạng một cách linh hoạt và có lập trình.

<br>

__3 lớp kiến trúc:__

__1. Infrastructure Layer__ <br>
__2. Control Layer__ <br>
__3. Application Layer__ <br>

Liên kết giữa lớp cơ sở hạ tầng và lớp điều khiển sử dụng API hướng Nam và liên kết giữa lớp điều khiển và lớp ứng dụng  sử dụng API hướng Bắc. API hướng Nam cho phép bộ điều khiển lập trình các bảng chuyển tiếp của mặt phẳng dữ liệu.

API southbound sử dụng __SSH__, __NETCONF__, __OpenFlow__, SNMP. API Northbound sử dụng API __REST__, __SOAP__, TLS.

![Alt text](/docs/CCNA/img/software-defined-networking.png)

<br>

## DNA – Digital Network Architecture
<br>
___Cisco DNA Center (còn gọi là Cisco Digital Network Architecture)___ là bộ điều khiển và quản lý SDN mạnh mẽ cho phép kiểm soát mạng, tối ưu hóa, bảo mật các kết nối từ xa và giảm chi phí.

Cisco DNA Center tận dụng sử dụng mạng dựa trên mục đích ___Intent-Based Networking (IBN)___. IBN là công nghệ SDN chuyển các nhu cầu kinh doanh thành các chính sách có thể được tự động hóa và thực thi nhất quán trên toàn mạng. Với nền tảng trung tâm Cisco DNA, không cần phải lo lắng quá nhiều về cấu hình CLI. Kỹ sư mạng sẽ chỉ tạo chính sách hoặc cấu hình dựa trên mục đích kinh doanh hoặc yêu cầu trên Cisco DNA center và điều đó sẽ thực hiện được. Cisco DNA center sẽ tự động triển khai cấu hình cho tất cả các thiết bị dựa trên cách ta muốn mạng hoạt động.

<br>

## SD-Access
<br>
![alt text](/docs/CCNA/img/sdn-sd-access.png)

## SD-WAN
<br>
__SD-WAN (Software-Defined Wide Area Network)__, mạng WAN được xác định bằng phần mềm, được giới thiệu để cung cấp kết nối an toàn và đáng tin cậy hơn với chi phí thấp hơn. SD-WAN là sự kết hợp giữa Internet và private WAN. SD-WAN tối ưu hóa và tự động hóa sử dụng các kết nối như MPLS, DSL, 5G/LTE và Internet để kết nối với các chi nhánh, trung tâm dữ liệu và hội sở. SD-WAN có bộ điều khiển tập trung chịu trách nhiệm tự động hóa, điều khiển cũng như quản lý và cấu hình tập trung.

![alt text](/docs/CCNA/img/sdn-sd-wan.png)

Kiến trúc SD-WAN có 4 thành phần chính:

__1\. vEdge__

vEdge có vai trò là data plane và có thể là router vật lý hoặc ảo. vEdge chịu trách nhiệm định tuyến và chuyển tiếp trong kiến ​​trúc SD-WAN. Mỗi router sử dụng mã hóa IPSec để cung cấp kết nối an toàn. Các router vEdge phổ biến cho phần cứng là Viptela OS Router hay IOS XE SD-WAN Router và cho ảo hóa là vEdge Cloud hay Cisco Cloud Services Router (CSR).

__2\. vSmart__

vSmart có vai trò là control plane và có sẵn dưới dạng máy ảo. vSmart quảng cáo các policy, routes và security. vSmart chịu trách nhiệm quản lý tất cả các dữ liệu và chính sách điều khiển bằng giao thức Overlay Management Protocol (OMP).

__3\. vManage__

vManage có vai trò là management plane và có thể được xem trong GUI. Là 1 cổng tập trung để quản lý, tạo chính sách và định cấu hình phần mềm và phần cứng trong kiến ​​trúc SD-WAN.

__4\. vBond__

vBond là bộ điều phối, xác thực vSmart controller, vEdge router, vManage trong mạng SD-WAN. Có thể có sẵn dưới dạng phần cứng hoặc thiết bị ảo. vBond chịu trách nhiệm tích hợp tất cả vEdge router. Nó tạo một đường hầm an toàn với vEdge, sau đó thông báo cho vSmart và vManage về cấu hình và thông số của nó, chẳng hạn như địa chỉ IP.

__Zero Touch Provisioning (ZTP)__ là dịch vụ cung cấp tự động dựa trên đám mây cho các thiết bị mạng ở một địa điểm từ xa mà không cần gửi kỹ sư mạng đến các địa điểm đó. ZTP hạn chế lỗi của con người, tích hợp, nâng cấp và cài đặt cấu hình một cách hiệu quả cho các thiết bị trong toàn bộ mạng.

