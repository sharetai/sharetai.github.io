---
layout: default
title: Syslog
nav_order: 160
parent: CCNP
---

# Syslog
{: .no_toc }

Nhật ký hệ thống
{: .fs-6 .fw-300 }

---

## TABLE OF CONTENTS
{: .no_toc .text-delta }

1. TOC
{:toc}

---

## Reliable Delivery and Filtering for Syslog

<h3> Creating a Message Discriminator </h3>

<h4> SUMMARY STEPS </h4>

1. __enable__
2. __configure terminal__
3. __logging discriminator__ _discr-name_ [[__facility__ ] [__mnemonics__ ] [__msg-body__ ] {__drops__ _string_ \| __includes__ _string_ }] [__severity__ {__drops__ _sev-num_ \| __includes__ _sev-num_ }] [__rate-limit__ _msglimit_ ]
4. __end__

<h3> Associating a Message Discriminator with a Logging Buffer </h3>

<h4> SUMMARY STEPS </h4>

1. __enable__
2. __configure terminal__
3. __logging discriminator__ _discr-name_ [[__facility__ ] [__mnemonics__ ] [__msg-body__ ] {__drops__ _string_ \| __includes__ _string_ }] [__severity__ {__drops__ _sev-num_ \| __includes__ _sev-num_ }] [__rate-limit__ _msglimit_ ]
4. __logging buffered__ [__discriminator__ _discr-name_ \| __xml__ ] [_buffer-size_ ] [_severity-level_ ]
5. __end__

<h3> Associating a Message Discriminator with a Console Terminal </h3>

<h4> SUMMARY STEPS </h4>

1. __enable__
2. __configure terminal__
3. __logging discriminator__ _discr-name_ [[__facility__ ] [__mnemonics__ ] [__msg-body__ ] {__drops__ _string_ \| __includes__ _string_ }] [__severity__ {__drops__ _sev-num_ \| __includes__ _sev-num_ }] [__rate-limit__ _msglimit_ ]
4. __logging console__ [__discriminator__ _discr-name_ \| __xml__ ] [_buffer-size_ ] [_severity-level_ ]
5. __end__

<h3> Associating a Message Discriminator with Terminal Lines </h3>

<h4> SUMMARY STEPS </h4>

1. __enable__
2. __configure terminal__
3. __logging discriminator__ _discr-name_ [[__facility__ ] [__mnemonics__ ] [__msg-body__ ] {__drops__ _string_ \| __includes__ _string_ }] [__severity__ {__drops__ _sev-num_ \| __includes__ _sev-num_ }] [__rate-limit__ _msglimit_ ]
4. __logging monitor__ [__discriminator__ _discr-name_ \| __xml__ ] [_buffer-size_ ] [_severity-level_ ]
5. __end__

<h3> Enabling Message Counters </h3>

<h4> SUMMARY STEPS </h4>

1. __enable__
2. __configure terminal__
3. __logging message-counter__ {__debug__ \| __log__ \| __syslog__ } 
5. __end__

<h3> Examble </h3>

Enabling logging to a local buffer, to the terminal, and to a syslog server for all debugging level logs filtered by facility code 7

```
logging buffered discriminator Disc1
logging monitor discriminator Disc1
logging host 10.1.55.237 discriminator Disc1
logging discriminator Disc1 severity includes 7 facility includes fac7
```