---
layout: default
title: MPLS
nav_order: 30
parent: CCIE
---

# Multiprotocol Label Switching
{: .no_toc }

Chuyển mạch nhãn đa giao thức
{: .fs-6 .fw-300 }

_Nguồn tham khảo: [http://ccie-in-2-months.blogspot.com/](http://ccie-in-2-months.blogspot.com/p/the-hints-series.html)_

---

## Table of contents
{: .no_toc .text-delta }

1. TOC
{:toc}

---

LDP (Label Distribution Protocol) is defined in [RFC 5036](http://tools.ietf.org/html/rfc5036).<br>
MPLS (Multi-Protocol Label Switching) architecture is defined in [RFC 3031](http://tools.ietf.org/html/rfc3031).<br>
MPLS Label Stack Encoding is defined in [RFC 3032](http://tools.ietf.org/html/rfc3032).

---

<u>Topo</u>

\[ PPPoE client \] e0/0 ------------ e0/1 \[ Switch \] e0/0 ------------ e0/1 \[ PPPoE server \]

---

## <u>PPPoE</u>

IOS
{: .label .label-blue }

<u>PPPoE server</u>

