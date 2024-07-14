---
layout: default
title: Switch Security
nav_order: 24
parent: CCNA
---

# Switch Security
{: .no_toc }

Bảo mật trên Switch
{: .fs-6 .fw-300 }

---

## Table of contents
{: .no_toc .text-delta }

1. TOC
{:toc}

---

## <u>Các bước bảo mật cho Layer 2</u>

1. Bỏ qua VLAN 1, không sử dụng. Tạo VLAN mới làm native VLAN
2. Tắt chế độ thương lượng (negotiate) trên các cổng kết nối với người dùng.
3. Tắt CDP trên các cổng nối với thiết bị không tin cậy.
4. Shutdown các cổng không dùng, đưa các port này vào VLAN dành riêng.
5. Giới hạn MAC trên các cổng.

## <u>Port Security</u>

**Sẽ ra sao nếu có nhiều mac đẩy lên 1 cổng? Do người dùng tự ý cắm vào 1 switch? Do người dùng xấu tạo nhiều mac ảo?**

![image](/docs/CCNA/img/port-security.png)

```
SW1(config)#int range f0/1-24
SW1(config-if-range)#switchport mode access 
SW1(config-if-range)#switchport port-security
SW1(config-if-range)#switchport port-security max 1
SW1(config-if-range)#switchport port-security mac-address sticky 
SW1(config-if-range)#switchport port-security violation <protect/restrict/shutdown>
```

Các mode xử lý vi phạm:
* protect: loại bỏ gói vi phạm
* restrict: loại bỏ gói vi phạm và ghi lại log
* shutdown: loại bỏ gói vi phạm và shutdown port

## <u>AAA and 802.1X</u>

**Sẽ ra sao nếu người dùng tự ý cắm vào 1 access point? Cần 1 cơ chế xác thực, phân quyền, ghi nhận hoạt động?**

*(lab is comming soon)*

## <u>VLAN Access-List (VACL)</u>

**Cần 1 chính sách truy cập cho vlan?**

*(lab is comming soon)*

## <u>Storm Control</u>

**Sẽ ra sao nếu có một lượng lớn yêu cầu liên tục (có thể là unicast, multicast, broadcast)? Là yêu cầu dịch vụ hay tấn công?**

**Cần 1 cơ chế đặt ngưỡng và hành động tương ứng?**

```
Switch(config-if)#storm-control ?
  action     Action to take for storm-control
  broadcast  Broadcast address storm control
  multicast  Multicast address storm control
  unicast    Unicast address storm control
```

*(lab is comming soon)*

## <u>VLAN Hopping</u>

VLAN Hopping là kỹ thuật cho phép nhảy *(hopping)* truy cập từ vlan này sang vlan khác. Có 2 kỹ thuật:

\- Double tags: Kẻ tấn công kết nối vào cổng access vào vlan cùng với native vlan trên trunk. Có thể lợi dụng khi quản trị mạng chưa đổi native vlan mặc định là vlan 1 và các cổng vẫn mặc địng thuộc vlan 1 do chưa được đổi. Gắn thêm vào gói 2 tag vlan, tag trong là vlan muốn tấn công, tag ngoài là vlan native có thể là vlan 1. Switch nhận gói, sẽ tháo tag ngoài và đẩy vào vlan tương ứng tag trong. Kẻ tấn công đã nhảy thành công vào vlan nạn nhân.

\- Switch spoofing: Kẻ tấn công làm giả quá trình thương lượng DTP để thiết lập trunk với switch. Do mặc định switch bật tự động trunk. Lúc này kẻ tấn công muốn nhảy vlan nào thì chỉ cần gắn tag vlan tương ứng.

**Cần thay đổi vlan native mặc định và tắt DTP trên switch**

*(lab is comming soon)*

## <u>DHCP Snooping</u>

![image](/docs/CCNA/img/dhcp-snooping.png)

**Sẽ ra sao nếu 1 máy tính giả danh làm DHCP server?** Làm giả **Gateway**, **DNS**, Web Server? **Sẽ ra sao nếu 1 máy tính tạo ra nhiều mac và yêu cầu cấp nhiều ip?**

**Cần 1 cơ chế chỉ định port tin cậy dành riêng cho DHCP server**

DHCP Snooping: <br>
\- **Trusted** hoặc **Untrusted Port** <br>
\- **Chặn** các gói tin **DHCP OFFER** và **DHCP ACK** trên các port Untrusted <br>
\- Đồng thời lưu 1 databse về **IP-MAC binding** <br>
\- 2 bước cấu hình: <br>
\--\-- Bật DHCP Snooping <br>
\--\-- Cấu hình Trusted Port (mặc định các cổng sẽ là Untrusted Port) <br>

```
Switch(config)#ip dhcp snooping 
Switch(config)#ip dhcp snooping vlan 1
Switch(config)#no ip dhcp snooping information option //Disable DHCP Option-82 data insertion
Switch(config)#int fa0/24
Switch(config-if)#ip dhcp snooping trust 

Switch#show ip dhcp snooping binding
```

## <u>ARP Spoisoning</u>

Có 2 kỹ thuật áp dụng:

\- MITM (Man in the middle): Kẻ tấn công giả ARP reply với mac độc hại, khi máy tính nạn nhân yêu cầu phân giải 1 địa chỉ ip. Máy tính nạn nhân sẽ cập nhật mac độc vào bảng ARP. Kẻ tấn công sẽ có thể nghe được mọi yêu cầu khi máy tính nạn nhân giao tiếp với địa chỉ ip bị đầu độc.

\- DOS (Denial of Service): Kẻ tấn công giả vô số ARP reply, toàn bộ máy tính trong cùng vlan sẽ phải cập nhật liên tục, làm quá tải truy cập.

```
Switch(config)#ip arp inspection vlan 1
Switch(config)#int fa0/24
Switch(config-if)#ip arp inspection trust 
```

