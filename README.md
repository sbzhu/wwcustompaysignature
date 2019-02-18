
## 签名算法

签名生成的通用步骤如下：

第一步，将所有非空参数构造成键值对（即key=value）集合，按照ASCII码从小到大排序（字典序），最后拼接成字符串stringA。

__特别注意__ 以下重要规则：

1.  将“键值对”整体按照ASCII码从小到大排序（字典序）；
2.  如果参数的值为空不参与签名；
3.  传送的sig参数不参与签名，将生成的签名与该sig值作校验；
5.  区分大小写；
6.  接口可能增加字段，验证签名时必须支持增加的扩展字段；

第二步，对stringA以服务商的ProviderSecret为key进行HMAC-SHA256运算，并进行base64编码，得到sig。
第三步，将计算得到的sig与请求中的sig对比，如果不相同，表示该请求可能被篡改。

__举例：__ 

假设服务商的ProviderSecret为：

```python
secret = "vt23pxnPBNQY3JiA8N5U1g__iQqxZwqH_Gih07a_wrULmlOPVP-HiRjv9JWYPrDJ"
```

接收到的json参数如下：

```json
{
    	"orderid" : "ord7",
        "buyer_corpid": "ww66302cfadbdd3c64",
    	"buyer_userid" : "invitetest",
        "product_id": "product_id_xxx",
        "product_name": "product_name_xxx",
        "product_detail": "product_detail_xxx",
        "unit_name": "台",
        "unit_price": 1,
        "num": 3,
        "ts": 1548302135,
        "sig": "mPOwVW/vQ74xN+b+Yu1KMa9RrmhKJaJjAtXHTof+EpU="
}

```

__第一步：__ 参数按照key=value的格式构造"键值对"集合

```bash
orderid=ord7
buyer_corpid=ww66302cfadbdd3c64
buyer_userid=invitetest
product_id=product_id_xxx
product_name=product_name_xxx
product_detail=product_detail_xxx
unit_name=台
unit_price=1
num=3
ts=1548302135
```

```注意：```sig并不参与签名。

__第二步：__ 将集合按照字典序排序

```bash
buyer_corpid=ww66302cfadbdd3c64
buyer_userid=invitetest
num=3
orderid=ord7
product_detail=product_detail_xxx
product_id=product_id_xxx
product_name=product_name_xxx
ts=1548302135
unit_name=台
unit_price=1
```

__第三步：__ 拼接字符串：

```python
stringA = "buyer_corpid=ww66302cfadbdd3c64&buyer_userid=invitetest&num=3&orderid=ord7&product_detail=product_detail_xxx&product_id=product_id_xxx&product_name=product_name_xxx&ts=1548302135&unit_name=台&unit_price=1"
```

__第四步：__ 以secret为key做hash并base64编码得到签名：

```python
sign = base64_encode(hash_hmac("sha256", stringA, secret))
```

最终得到签名： mnyEtahO9S19z+7fmETni3Wcv6fzHQtAW6bjb6vlNAM=

而接收到的签名为 "sign": "mPOwVW/vQ74xN+b+Yu1KMa9RrmhKJaJjAtXHTof+EpU="，两者不一致，那么很有可能是被第三者篡改数据了 ！

## 生成随机数算法

部分API接口协议中包含字段nonce_str，主要保证签名不可预测。我们推荐生成随机数算法如下：调用随机数函数生成，将得到的值转换为字符串。
