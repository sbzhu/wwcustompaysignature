## 下订单接口

业务系统先调用该接口在服务后台生成预支付交易单，返回正确的交易订单（token_id）和跳转链接（url_params）后，再在客户端里面调起支付。

__请求方式：__POST（HTTPS） 
__请求URL：__https://qyapi.weixin.qq.com/cgi-bin/service/custompay/openorder?suite_access_token=SUITE_ACCESS_TOKEN
__请求包体： __

```json
{
	"out_trade_no": "1458098496971",
    "order_type": 0,
	"buyer_corpid": "ww66302cfadbdd3c64",
    "buyer_name": "达拉斯有限公司",
    "user_nickname": "小甜瓜",
	"product_name": "腾讯乐享",
	"product_detail": "腾讯XX付费服务",
    "appid": 1,
    "unit_name": "天",
    "unit_price": 10000,
    "num": 365,
    "ts": 1541498084,
    "nonce_str": "5K8264ILTKCH16CQ2502SI8ZNMTM67VS",
    "sign": "C380BEC2BFD727A4B6845133519F3AD6"
}
```
__参数说明 ：__

| 参数               | 必须 | 说明                                                         |
| ------------------ | ---- | ------------------------------- |
| suite_access_token | 是   | 调用接口凭证            |
| out_trade_no  | 是   | 商品订单id，全局唯一，最多32字节。仅支持数字、字母、下划线（_）、横杠字符（-）、点（.）的组合 |
| order_type       | 否  | 订单类型，默认为正式订单。<br> order_type=0：正式订单<br> order_type=1: 测试订单 |
| buyer_corpid       | 是   | 购买方企业corpid             |
| buyer_name | 否 | 购买服务的商家的名称。 |
| user_nickname | 否 | 用户昵称，支持回传给购买商品信息页面 |
| product_name       | 是   | 商品名称（仅支持下划线_、横杠字符-，其他特殊字符不支持）, 最多36字节 |
| product_detail     | 是   | 商品详情, 最多255字节      |
| appid              | 否   | 旧的多应用套件中的对应应用id，新开发者请忽略  |
| unit_name | 否 | 购买的商品的单价的名称 |
| unit_price | 是 | 单价，单位分，币种当前只支持默认的CNY。例如：1 |
| num | 是 | 购买的商品的数量，不超过20000000。例如：1 |
| ts | 是 | unix时间戳（中国时区）,精确到秒。<br />注意业务系统的机器时间与腾讯的时间相差不能超过15分钟，否则企业微信基于安全风险考虑，会做主动拦截处理； |
| nonce_str | 是 | 随机字符串，长度要求在32位以内。推荐[随机数生成算法](https://pay.weixin.qq.com/wiki/doc/api/jsapi.php?chapter=4_3) |
| sign | 是 | 通过签名算法计算得出的签名值，详见[签名生成算法](https://pay.weixin.qq.com/wiki/doc/api/jsapi.php?chapter=4_3) |

__返回包体:__

``` json
{
	"errcode" : 0,
	"errmsg" : "ok",
    "transaction_id" : "E-180816160034120067",
	"token_id" : "E-180816160034120067",
	"url_params": "/v1/r/1450005657/qz_goods_info?transaction_id=E-160105190014041272&token_id=E-160105190014041272&pf=midas_group_pay-1000-pc-1000",
	"nonce_str": "5K8264ILTKCH16CQ2502SI8ZNMTM67VS",
    "sign": "C380BEC2BFD727A4B6845133519F3AD6"
}
```

__参数说明 ：__


| 参数               | 说明                                                         |
| ------------------ | -------------------------------------------- |
| errcode | 出错返回码，为0表示成功，非0表示调用失败             |
| errmsg | 返回码提示语 |
| transaction_id | 交易订单 |
| token_id | 交易订单，供不同的调用方使用 |
| url_params | 跳转链接。真正购买商品的url的参数，业务系统需要把该参数传给pc/sdk/H5跳转到相关页面使用户完成真正的购买动作 |
| nonce_str | 随机字符串。推荐[随机数生成算法](https://pay.weixin.qq.com/wiki/doc/api/jsapi.php?chapter=4_3) |
| sign | 通过签名算法计算得出的签名值，详见[签名生成算法](https://pay.weixin.qq.com/wiki/doc/api/jsapi.php?chapter=4_3) |

## 查询订单接口

该接口为订单的查询，商户可以通过该接口主动查询订单状态。需要调用查询接口的情况：
1.当商户后台、网络、服务器等出现异常，商户系统最终未接收到支付通知；
2.调用支付接口后，返回系统错误或未知交易状态情况；
3.调用被扫支付API，返回正在支付中的状态；
4.调用退款接口API之前，需确认支付状态；

__请求方式：__POST（HTTPS） 
__请求URL：__https://qyapi.weixin.qq.com/cgi-bin/service/custompay/queryorder?suite_access_token=SUITE_ACCESS_TOKEN
__请求包体： __

```json
{
    "out_trade_no": "1458098496971",
    "transaction_id": "E-160105190014041272",
    "starttime": "2016-03-20 11:10:10",
    "endtime": "2016-03-26 11:10:10",
    "num": 100,
    "off_set": 1000,
    "ts": 1541498084,
    "nonce_str": "5K8264ILTKCH16CQ2502SI8ZNMTM67VS",
    "sign": "C380BEC2BFD727A4B6845133519F3AD6"
}
```
__参数说明 ：__

| 参数               | 必须 | 说明                                                         |
| ------------------ | ---- | ------------------------------------------------------------ |
| suite_access_token | 是   | 调用接口凭证                                                 |
| out_trade_no       | 否   | 商品订单 |
| transaction_id | 否 | 交易订单<br/>如果out_trade_no、transaction_id均不指定，则根据应用查询 |
| starttime          | 否   | 查询的起始时间，格式：YYYY-MM-DD hh:mm:ss                    |
| endtime            | 否   | 查询的结束时间，格式：YYYY-MM-DD hh:mm:ss                    |
| num                | 否   | 每页返回的记录数。根据用户号码查询订单列表时需要传。用于分页展示。 |
| off_set            | 否   | 记录数偏移量，默认从0开始。根据用户号码查询订单列表时需要传。用于分页展示。 |
| ts | 是 | unix时间戳（中国时区）,精确到秒。<br />注意业务系统的机器时间与腾讯的时间相差不能超过15分钟，否则企业微信基于安全风险考虑，会做主动拦截处理； |
| nonce_str | 是 | 随机字符串，长度要求在32位以内。推荐[随机数生成算法](https://pay.weixin.qq.com/wiki/doc/api/jsapi.php?chapter=4_3) |
| sign | 是 | 通过签名算法计算得出的签名值，详见[签名生成算法](https://pay.weixin.qq.com/wiki/doc/api/jsapi.php?chapter=4_3) |

__返回包体:__

``` json
{
	"errcode": 0,
	"errmsg": "ok",
	"total_num": 1,
	"order_list": [
		{
		  "out_trade_no": "1458098496971",
		  "order_type": 0,
		  "buyer_corpid": "ww66302cfadbdd3c64",
		  "buyer_name": "达拉斯有限公司",
		  "user_nickname": "小甜瓜",
		  "product_name": "腾讯乐享",
		  "appid": 1,
		  "unit_name": "天",
		  "unit_price": 10000,
		  "num": 365,		  
          "amt": 3650000,
		  "order_state": 1,
		  "order_time": "2016-03-24 11:10:20",
		  "pay_time": "2016-03-24 11:10:30"
	  }
	]
   	"ts": 1541498084,
	"nonce_str": "5K8264ILTKCH16CQ2502SI8ZNMTM67VS",
	"sign": "C380BEC2BFD727A4B6845133519F3AD6"
}
```

__参数说明 ：__


| 参数               | 说明                                                         |
| ------------------ | -------------------------------------------- |
| errcode | 出错返回码，为0表示成功，非0表示调用失败             |
| errmsg | 返回码提示语 |
| out_trade_no  | 商品订单id，全局唯一，最多32字节。仅支持数字、字母、下划线（_）、横杠字符（-）、点（.）的组合 |
| order_type       |订单类型，默认为正式订单。<br> order_type=0：正式订单<br> order_type=1: 测试订单 |
| buyer_corpid       | 购买方企业corpid             |
| buyer_name | 购买服务的商家的名称。 |
| user_nickname | 用户昵称，支持回传给购买商品信息页面 |
| product_name       | 商品名称（仅支持下划线_、横杠字符-，其他特殊字符不支持）, 最多36字节 |
| appid              | 旧的多应用套件中的对应应用id，新开发者请忽略  |
| unit_name | 购买的商品的单价的名称 |
| unit_price | 单价，单位分，币种当前只支持默认的CNY。例如：1 |
| num |购买的商品的数量，不超过20000000。例如：1 |
| amt       | 支付金额，单位：分 |
| order_state       | 订单状态。<br>order_state=0：未支付<br>order_state=1：已支付<br>order_state=2：已失效 |
| order_time       |下单时间，格式：YYYY-MM-DD hh:mm:ss |
| pay_time       | 支付时间，格式：YYYY-MM-DD hh:mm:ss |
| ts | 是 | unix时间戳（中国时区）,精确到秒。<br />注意业务系统的机器时间与腾讯的时间相差不能超过15分钟，否则企业微信基于安全风险考虑，会做主动拦截处理； |
| nonce_str | 随机字符串，长度要求在32位以内。推荐[随机数生成算法](https://pay.weixin.qq.com/wiki/doc/api/jsapi.php?chapter=4_3) |
| sign | 通过签名算法计算得出的签名值，详见[签名生成算法](https://pay.weixin.qq.com/wiki/doc/api/jsapi.php?chapter=4_3) |

## 支付成功通知

支付完成后，企业微信会把相关支付结果和用户信息，通过支付成功事件发送给服务商指定的应用的“指令回调URL”，服务商需要接收处理，并返回应答。
对后台通知交互时，如果企业微信收到业务的应答不是成功或超时，认为通知失败，企业微信会通过一定的策略重新发起通知，尽可能提高通知的成功率，但不保证通知最终能成功。

__注意事项：__

1.同样的通知可能会多次发送给业务系统,业务系统必须能够正确处理重复的通知（做好发货防重）!!!
推荐的做法是：当收到通知进行处理时，首先检查对应业务数据的状态，判断该通知是否已经处理过，如果没有处理过再进行处理，如果 处理过直接返回结果成功。在对业务数据进行状态检查和处理之前，要采用数据锁进行并发控制，以避免函数重入造成的数据混乱。
2.业务系统对于支付结果通知的内容一定要做签名验证，防止数据泄漏导致出现“假通知”，造成资金损失。

__返回包体:__

```xml
<xml>
	<SuiteId><![CDATA[ww4asffe99e54c0f4c]]></SuiteId>
	<InfoType><![CDATA[custom_pay_done]]></InfoType>
	<TimeStamp>1403610513</TimeStamp>
	<out_trade_no><![CDATA[1458098496971]]></out_trade_no>
</xml>
```
__参数说明 ：__


| 参数               | 说明                                                         |
| ------------------ | -------------------------------------------- |
| SuiteId | 第三方应用的SuiteId |
| InfoType | 事件类型，此处为“custom_pay_done” |
| TimeStamp | 时间戳|
| out_trade_no | 订单id |

## 签名算法

签名生成的通用步骤如下：

第一步，设所有发送或者接收到的数据为集合M，将集合M内非空参数值的参数按照ASCII码从小到大排序（字典序），使用URL键值对的格式（即key1=value1&key2=value2…）拼接成字符串stringA。

__特别注意__以下重要规则：

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

__第一步：__参数按照key=value的格式构造字符串集合

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

__第二步：__将集合按照字典序排序

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

__第三步：__拼接字符串：

```python
stringA = "errcode=0&errmsg=ok&nonce_str=5K8264ILTKCH16CQ2502SI8ZNMTM67VS&order_type=0&order_type=1&out_trade_no=1458098496971&out_trade_no=1458098496983&total_num=2&ts=1541498084"
```

__第四步：__以secret为key做hash并base64编码得到签名：

```python
sign = base64_encode(hash_hmac("sha256", stringA, secret))
```

最终得到签名： hbeIqbtMijFLvIn86/2GJivyDFE=

参考库下载：[php]()，[python]()，[c++]()

## 生成随机数算法

API接口协议中包含字段nonce_str，主要保证签名不可预测。我们推荐生成随机数算法如下：调用随机数函数生成，将得到的值转换为字符串。
