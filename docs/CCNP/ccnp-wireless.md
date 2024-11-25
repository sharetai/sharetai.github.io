---
layout: default
title: Wireless
nav_order: 150
parent: CCNP
---

# Wireless
{: .no_toc }

Truyền thông không dây
{: .fs-6 .fw-300 }

---

## Table of contents
{: .no_toc .text-delta }

1. TOC
{:toc}

---

## Sóng điện từ
<br>
Truyền dẫn trong hệ thống truyền thông không dây bao gồm một nguồn hoặc máy phát _(transmitter)_ và một điểm đến hoặc máy thu _(receiver)_. Máy phát gửi một dòng điện xoay chiều vào anten, tạo ra điện trường và từ trường chuyển động phân tán khi sóng truyền ra khỏi anten.

Sóng điện từ của mạng không dây không truyền theo đường thẳng. Thay vào đó, chúng lan ra mọi hướng khỏi anten. Sóng điện từ lan ra ngoài theo cả ba chiều trong không gian tự do.

<img style="max-width: 600px" src="/docs/CCNP/img/wireless-wave.png" />

Người gửi truyền tín hiệu không dây. Dịch vụ liên lạc không dây giữa hai thiết bị được thiết lập khi bộ thu nhận được các tín hiệu này. Kết quả là một cầu nối liên lạc không dây được hình thành giữa thiết bị người gửi và người nhận. Quá trình sau đó được đảo ngược ở phía thu của hệ thống truyền thông không dây.

Khi sóng điện từ tới anten của máy thu, chúng sẽ tạo ra tín hiệu điện. Tín hiệu không dây nhận được sẽ là bản sao gần giống của tín hiệu được truyền ban đầu.

Sự khác biệt chính của sóng điện từ là tần số của chúng. Tần số càng cao thì càng có nhiều sóng trong một chu kỳ thời gian cụ thể. Tần số cao hơn cung cấp tốc độ dữ liệu cao hơn. Sóng điện từ tần số thấp có bước sóng dài hơn, đó là khoảng cách giữa các đỉnh sóng. Mặt khác, sóng điện từ tần số cao có bước sóng ngắn.

<h3> Tần số vô tuyến (Radio Frequency - RF) </h3>

Tần số sóng điện từ WiFi là số lần tín hiệu thực hiện một chu kỳ lên xuống hoàn chỉnh trong 1 giây. Một chu kỳ có thể bắt đầu khi tín hiệu tăng lên từ đường trung tâm, đi qua nó và tăng trở lại để gặp nó. Ngoài ra, một chu kỳ có thể được tính từ tâm của đỉnh này đến tâm của đỉnh sau. Bất cứ khi nào bắt đầu đo chu kỳ, tín hiệu phải hoàn thành một chuỗi quay trở lại vị trí ban đầu trước khi lặp lại cùng một mẫu tuần hoàn.

Trong ví dụ bên dưới, 1 giây đã trôi qua. Trong thời gian đó, tín hiệu trải qua bốn chu kỳ hoàn chỉnh mỗi giây (Hertz).

<img style="max-width: 600px" src="/docs/CCNP/img/wireless-frequency.png" />

Băng tần 2.4 GHz được sử dụng cho kết nối WiFi và mạng LAN không dây (WLAN) nằm trong khoảng từ 2.4 GHz đến 2.4835 GHz.

Một phạm vi mạng không dây khác thường được gọi là băng tần 5 GHz vì nó hoạt động trong khoảng 5.150 đến 5.825 GHz. Băng tần 5 GHz có bốn băng tần khác nhau:

5.150 – 5.250 GHz <br>
5.250 – 5.350 GHz <br>
5,470 – 5,725 GHz <br>
5,725 – 5,825 GHz <br>

Gần đây, một băng tần WLAN mới dành cho mạng WiFi đã được giới thiệu, băng tần 6 GHz, có khả năng phủ sóng từ 5.925 GHz đến 7.125 GHz.

<h3> Bước sóng (Wavelength) </h3>

Bước sóng là khoảng cách vật lý mà sóng truyền được trong một chu kỳ đầy đủ.

2.4 GHz – 4.92 inches <br>
5 GHz – 2.36 inches <br>
6 GHz – 1.97 inches <br>

<img style="max-width: 400px" src="/docs/CCNP/img/wireless-wavelength.png" />

Bước sóng giảm khi tần số tăng. Chu kỳ sóng ngắn hơn khi bước sóng nhỏ hơn. Bước sóng dùng cho  việc thiết kế và định vị anten mạng Wi-Fi.

<h3> Suy hao (Net Loss) </h3>

__Suy hao = 10log10(cường độ tín hiệu nhận được/cường độ tín hiệu truyền đi) (dB)__

<img style="max-width: 600px" src="/docs/CCNP/img/wireless-net-loss.png" />

Suy hao = 10log10(0.00123 mW/500 mW) = -56 dB

<h3> Effective Isotropic Radiated Power (EIRP) </h3>

Công suất bức xạ đẳng hướng hiệu dụng (EIRP) là công suất đo được bức xạ theo một hướng bởi một ăng ten đẳng hướng lý tưởng. Đó là công suất đầu ra tối đa của anten theo hướng có mức tăng anten cao nhất. Được tính toán bằng cách sử dụng mức công suất máy phát, chiều dài cáp và độ lợi anten.

__EIRP = Tx Power + Tx Antenna – Tx Cable__

<img style="max-width: 600px" src="/docs/CCNP/img/wireless-eirp-1.png" />

Nếu máy phát có mức công suất đầu vào là 12 dBm và được kết nối với anten có mức tăng 10 dBi sử dụng cáp có mức suy hao 4 dB thì EIRP của hệ thống là 18 dBm.

EIRP = Tx Power + Tx Antenna – Tx Cable <br>
EIRP = 12 dBm + 10 dBi – 4 dB <br>
EIRP = 18 dDm <br>

Giá trị dB tăng và giảm có thể được thêm vào tại các điểm khác nhau dọc theo đường dẫn tín hiệu. Hình ảnh bên dưới mô tả các thành phần tăng hoặc giảm tín hiệu dọc theo đường dẫn từ máy phát đến máy thu.

<img style="max-width: 600px" src="/docs/CCNP/img/wireless-eirp-2.png" />

<img style="max-width: 600px" src="/docs/CCNP/img/wireless-eirp-3.png" />

Rx Signal = Tx Power – Tx Cable + Tx Antenna – Free Space + Rx Antenna – Rx Cable <br>
Rx Signal = 18 dBm – 5 dB + 8 dBi – 25 dB + 8 dBi – 5 dB <br>
Rx Signal = -1 dBm <br>

<h3> Received Signal Strength Indicator (RSSI) </h3>

Cường độ tín hiệu thu hay là chỉ số để đo độ mạnh của tín hiệu tại thiết bị thu (ví dụ anten, sóng wifi..). RSSI càng lớn thì độ mạnh của tín hiệu càng lớn.

<img style="max-width: 600px" src="/docs/CCNP/img/wireless-rssi.png" />

<h4> Signal-to-Noise Ratio (SNR) </h4>

Các giá trị RSSI thể hiện chất lượng tương đối của tín hiệu nhận được so với tín hiệu dự kiến. Các tín hiệu khác nhận được trên cùng tần số thu được coi là nhiễu. Tầng nhiễu là mức nhiễu hoặc cường độ tín hiệu trung bình.

Có thể dễ dàng bỏ qua tiếng ồn miễn là mức nhiễu nền thấp hơn nhiều so với mức mà máy thu đang cố gắng nhận. Để tín hiệu RF được nhận và hiểu chính xác, cường độ tín hiệu phải cao hơn đáng kể so với mức nhiễu nền. Tỷ lệ tín hiệu trên nhiễu (SNR) tính bằng dB là chênh lệch giữa tín hiệu và nhiễu. Khuyến nghị rằng giá trị SNR phải cao hơn.

Hình ảnh bên dưới so sánh cường độ tín hiệu nhận được của tín hiệu RF và mức nhiễu nhận được. Cường độ tín hiệu vào khoảng -40 dBm và mức nhiễu sàn là -80 dBm. SNR sẽ là -40 dBm hoặc 40 dB (-40 dBm – -80 dBm). Ở phía bên phải biểu đồ, mức nhiễu nền tăng lên -55 dBm nên giá trị SNR giảm xuống 15 dB (-40 dBm – -55 dBm). Tín hiệu có thể không sử dụng được vì tín hiệu và mức nhiễu rất gần nhau.

<img style="max-width: 600px" src="/docs/CCNP/img/wireless-snr.png" />

## Anten không dây (Wireless Antenna)
<br>
Anten không dây có thể có nhiều hình dạng và kích cỡ khác nhau, mỗi loại có giá trị khuếch đại cụ thể và chức năng cố định.

<h4> Mẫu bức xạ (radiation patterns) </h4>
Đồ thị biểu thị cường độ tín hiệu tương đối xung quanh anten được gọi là mẫu bức xạ.

<img style="max-width: 600px" src="/docs/CCNP/img/wireless-radiation-patterns.png" />

<h4> Độ lợi (gain) </h4>
Độ lợi của anten đo lường mức độ hiệu quả của nó có thể điều hướng tín hiệu RF theo một hướng cụ thể.

Anten đẳng hướng phát ra năng lượng RF theo mọi hướng như nhau nên nó không thể tập trung năng lượng RF theo một hướng. Độ lợi của anten tính bằng dBi được đo tương ứng với anten đẳng hướng. Độ lợi của anten đẳng hướng là 10log10(1) hoặc 0 dBi.

Độ lợi thấp hơn đối với anten đa hướng, bao phủ một khu vực rộng lớn. Mức tăng cao hơn đối với anten định hướng, được thiết kế để bao phủ các khu vực nhỏ hơn.

<img style="max-width: 600px" src="/docs/CCNP/img/wireless-gain.png" />

<h4> Độ rộng của vùng bức xạ (beamwidth) </h4>
Độ rộng chùm tia được tính bằng cách tìm điểm mạnh nhất của biểu đồ. Sau đó, đồ thị được di chuyển theo một trong hai hướng cho đến khi giá trị giảm đi 3 dB, biểu thị điểm mà tại đó tín hiệu có một nửa công suất cực đại.

Mỗi điểm 3 dB được cắt bởi một đường từ tâm đồ thị. Khi đó góc giữa hai đường thẳng được xác định.

<img style="max-width: 600px" src="/docs/CCNP/img/wireless-beamwidth.png" />

<h4> Sự phân cực (polarization) </h4>
Phân cực của anten là hướng của sóng điện trường so với đường chân trời. Anten phân cực dọc tạo ra dao động dọc và anten phân cực ngang tạo ra dao động ngang. Luôn tồn tại một sóng từ trường lệch 90 độ so với sóng điện trường.

Độ phân cực anten của máy phát và máy thu phải khớp nhau. Tín hiệu thu được có thể bị suy giảm nghiêm trọng nếu phân cực không khớp.

Hình ảnh dưới đây cho thấy sự phân cực của ăng-ten. Ở phía trên, cả máy phát và máy thu đều sử dụng phân cực dọc, giúp tối ưu hóa tín hiệu nhận được. Tuy nhiên, cặp phía dưới có độ phân cực không khớp, dẫn đến khả năng thu tín hiệu kém.

<img style="max-width: 600px" src="/docs/CCNP/img/wireless-polarization.png" />

<br>

## Anten định hướng vs Anten đa hướng (Directional Antenna vs Omnidirectional Antenna)
<br>

<h4> Patch Antenna </h4>

<!-- <img style="max-width: 600px" src="/docs/CCNP/img/wireless-patch-antenna.avif" /> -->
<img style="max-width: 600px" src="/docs/CCNP/img/wireless-patch-antenna.png" />

<h4> Yagi-Uda Antenna </h4>

<img style="max-width: 600px" src="/docs/CCNP/img/wireless-yugia-antenna.avif" />

<h4> Dish Antenna </h4>

<img style="max-width: 600px" src="/docs/CCNP/img/wireless-dish-antenna.avif" />

<h4> Dipole Antenna </h4>

<img style="max-width: 600px" src="/docs/CCNP/img/wireless-dipole-antenna.avif" />

<h4> Integrated Omnidirectional Antennas </h4>

<img style="max-width: 600px" src="/docs/CCNP/img/wireless-integrated-omnidirectional-antennas.avif" />

## Cisco Lightweight Access Point and WLC Pairing
<br>
Cisco Lightweight Access Point (LAP) phải được ghép nối với Wireless LAN Controller (WLC). Các LAP có thể được kết nối với mạng có dây mà không cần bất kỳ cấu hình nào. Tuy nhiên, cổng switch port mà AP kết nối phải được cấu hình đúng VLAN, access mode và cài đặt inline power phù hợp.

<h3> Cisco Lightweight Access Point States </h3>

<img style="max-width: 800px" src="/docs/CCNP/img/wireless-lap-states.png" />

<h3> Cisco Wireless Access Point (AP) Modes </h3>

LAP có thể được cấu hình để hoạt động ở một số chế độ AP. Có thể là _client-serving_ hoặc _network management_.

<h4> Client-Serving Cisco AP Modes </h4>

__Local Mode__ <br>
Là chế độ mặc định của LAP. Cung cấp BSS và cho phép các thiết bị được kết nối đến. Khi AP không truyền được frame, nó sẽ quét các kênh khác để đo ồn và nhiễu, phát hiện các thiết bị giả mạo và đối chiếu với các sự kiện của Hệ thống Phát hiện Xâm nhập (IDS).

__FlexConnect Mode__ <br>
Cho phép chuyển mạch lưu lượng giữa SSID và Vlan trong cục bộ nếu CAPWAP đến WLC bị down, ngay cả khi AP ở một địa điểm rất xa. <!-- Nó cũng có thể được cấu hình để đi ra cổng LAN của điểm truy cập. -->

__Bridge Mode or Mesh Mode__ <br>
Một AP ở chế độ cầu nối sẽ trở thành cầu nối point-to-point hoặc point-to-multipoint chuyên dụng giữa các mạng. Hai điểm truy cập không dây ở chế độ cầu có thể được sử dụng để liên kết hai địa điểm từ xa. Nhiều điểm truy cập chế độ cầu nối được sử dụng để hình thành triển khai mạng không dây dạng lưới trong nhà hoặc ngoài trời.

__Flex+Bridge Mode__ <br>
Kết hợp chế độ điểm truy cập FlexConnect và Bridge. Nó kích hoạt các tính năng FlexConnect trên các điểm truy cập chế độ AP dạng lưới.

<h4> Network Management Cisco AP Modes </h4>

__Monitor Mode__ <br>
Hoàn toàn không truyền tải. Không phát SSID. Tuy nhiên, nó hoạt động như một cảm biến chuyên dụng để giám sát và phát hiện kênh WiFi cho các sự kiện IDS, các điểm truy cập giả mạo và nó cũng xác định vị trí của các trạm không dây thông qua các dịch vụ dựa trên vị trí.

__Rogue Detector Mode__ <br>
Chế độ phát hiện các thiết bị lừa đảo trên mạng có dây và không dây. Nó đối chiếu các địa chỉ MAC trên mạng có dây với các địa chỉ MAC trên mạng không dây và các thiết bị giả mạo xuất hiện trên cả hai mạng. AP có thể phát SSID, do đó, nó vẫn có thể phục vụ khách hàng của mình và khách hàng vẫn có thể có kết nối không dây với điểm truy cập.

__SE-Connect Mode__ <br>
Cho phép điểm truy cập dành riêng kết nối cho công nghệ Cisco CleanAir để phân tích phổ. Điều này được sử dụng bởi phần mềm PC, chẳng hạn như Cisco Spectrum Expert và MetaGeek Chanalyzer, có thể được kết nối từ xa với điểm truy cập. Dữ liệu phân tích phổ được thu thập và phân tích trên tất cả các kênh không dây để phát hiện các nguồn gây nhiễu.

__Sniffer Mode__ <br>
Hoạt động như một bộ thu lưu lượng không dây 802.11 chuyên dụng. Sau đó, lưu lượng được chuyển tiếp đến một máy chạy phần mềm phân tích mạng như Wireshark hoặc OmniPeek để lưu trữ và phân tích thêm. Chế độ Sniffer AP sẽ không phát SSID và máy khách không thể kết nối với nó, nhưng nó rất hữu ích trong việc khắc phục sự cố trên các trang web từ xa.

__Sensor Mode__ <br>
Cho phép AP được hỗ trợ hoạt động giống như máy khách WLAN, liên kết và xác định các sự cố kết nối máy khách
