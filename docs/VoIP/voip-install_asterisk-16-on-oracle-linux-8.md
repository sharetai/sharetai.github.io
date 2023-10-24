---
layout: default
title: Cài đặt Asterisk 16 trên Oracle linux 8
nav_order: 1
parent: VoIP
---

# Cài đặt Asterisk 16 trên Oracle linux 8
{: .no_toc }

Các bước cài đặt Asterisk 16.26.1 stable trên hệ điều hành Oracle linux 8.6
{: .fs-6 .fw-300 }

---

**Disable SELINUX**

```
$ sudo sed -i 's/\(^SELINUX=\).*/\SELINUX=disabled/' /etc/selinux/config
$ sudo reboot
```

**Cài đặt các package cần thiết**

```
$ sudo yum -y install epel-release
$ sudo yum -y install git wget net-tools sqlite-devel psmisc libtermcap-devel newt-devel libxml2-devel libtiff-devel gtk2-devel libtool subversion kernel-devel crontabs cronie-anacron make openssl-devel gcc gcc-c++ ncurses-devel libuuid-devel libedit
```

* Nếu không cài đặt được libedit-devel thì dùng rpm để cài đặt

```
Unable to find a match: libedit-devel
$ sudo rpm -i https://vault.centos.org/centos/8/PowerTools/x86_64/os/Packages/libedit-devel-3.1-23.20170329cvs.el8.x86_64.rpm
```

**Cài đặt Asterisk**

```
$ cd /usr/src/
$ sudo wget http://downloads.asterisk.org/pub/telephony/asterisk/asterisk-16-current.tar.gz
$ sudo tar xvfz asterisk-16-current.tar.gz
$ sudo rm -rf asterisk-16-current.tar.gz
$ cd asterisk-16*/
$ sudo ./contrib/scripts/install_prereq install
$ sudo ./configure --libdir=/usr/lib64 --with-pjproject-bundled --with-jansson-bundled
$ sudo make menuselect
$ sudo contrib/scripts/get_mp3_source.sh
$ sudo make
$ sudo make install
$ sudo make samples
$ sudo make config
```

**Khởi động asterisk service**

```
$ sudo systemctl enable asterisk
$ sudo systemctl restart asterisk
```

**Kết quả, chạy asterisk**

```
$ sudo asterisk -rvvv
*CLI>
```

*(Source: https://hotkey404.com/asterisk-16-install-from-source/)*
