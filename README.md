
## 签名算法

签名生成的通用步骤如下：

第一步，设所有发送或者接收到的数据为集合M，将集合M内非空参数值的参数按照ASCII码从小到大排序（字典序），使用URL键值对的格式（即key1=value1&key2=value2…）拼接成字符串stringA。

__特别注意__ 以下重要规则：

1.  参数名ASCII码从小到大排序（字典序）；
2.  如果参数的值为空不参与签名；
3.  传送的sign参数不参与签名，将生成的签名与该sign值作校验；
4. 可能有数组类型的数据（如“查询订单接口”返回包里的order_list），这种类型参数不直接参与签名，而是递归地把数组中的元素取出构造字符串）；
5.  参数名区分大小写；
6.  接口可能增加字段，验证签名时必须支持增加的扩展字段；

第二步，对stringA进行HMAC-SHA256运算，再将得到的字符串进行base64编码，得到sign。

__举例：__ 

假设第三方应用secret为：

```python
secret = "gHqphoZuLCqHsSWbnojEKPLsWPE10G8UyKEE1B4uV64"
```

接收到的json参数如下：

```json
{
	"errcode": 0,
	"errmsg": "ok",
	"total_num": 2,
	"order_list": [
	    	{
			"out_trade_no": "1458098496971",
			"order_type": 1
		},
		{
			"out_trade_no": "1458098496983",
			"order_type": 0
		}
	],
	"ts": 1541498084,
	"nonce_str": "5K8264ILTKCH16CQ2502SI8ZNMTM67VS",
	"sign": "C380BEC2BFD727A4B6845133519F3AD6"
}
```

__第一步：__ 参数按照key=value的格式构造字符串集合

```bash
errcode=0
errmsg=ok
total_num=2
out_trade_no=1458098496971
order_type=1
out_trade_no=1458098496983
order_type=0
ts=1541498084
nonce_str=5K8264ILTKCH16CQ2502SI8ZNMTM67VS
```

```注意：```1. sign并不参与签名；2. order_list是数组类型，不直接参与签名，而是用它的元素来参与签名。

__第二步：__ 将集合按照字典序排序

```bash
errcode=0
errmsg=ok
nonce_str=5K8264ILTKCH16CQ2502SI8ZNMTM67VS
order_type=0
order_type=1
out_trade_no=1458098496971
out_trade_no=1458098496983
total_num=2
ts=1541498084
```

__第三步：__ 拼接字符串：

```python
stringA = "errcode=0&errmsg=ok&nonce_str=5K8264ILTKCH16CQ2502SI8ZNMTM67VS&order_type=0&order_type=1&out_trade_no=1458098496971&out_trade_no=1458098496983&total_num=2&ts=1541498084"
```

__第四步：__ 以secret为key做hash并base64编码得到签名：

```python
sign = base64_encode(hash_hmac("sha256", stringA, secret))
```

最终得到签名： hbeIqbtMijFLvIn86/2GJivyDFE=

参考库下载：[php]()，[python]()，[c++]()

## 生成随机数算法

API接口协议中包含字段nonce_str，主要保证签名不可预测。我们推荐生成随机数算法如下：调用随机数函数生成，将得到的值转换为字符串。
