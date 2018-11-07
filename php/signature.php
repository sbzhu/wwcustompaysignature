<?php

class SignatureGetter { 

	public function __construct($secret) 
	{ 
		$this->secret = $secret;
	}

	public function Get(string $json)
	{ 
		$jsonArray = json_decode($json, true);

		$paramArray = array();
		$this->Json2Array($jsonArray, $paramArray);

		$string = $this->ParamArray2String($paramArray);

		return $this->HmacSha256($this->secret, $string);
	}

	private function ParamArray2String(array $array)
	{
		asort($array); // sort

		//
		$str = "";
		foreach($array as $k => $v) { 
			if (0 === strpos($v, 'sign=')) { // note: do not use ==, fuck !
				continue; // escape sign self
			}

			$str = ($str . $v . '&');
		} 
		return substr($str, 0, strlen($str)-1);
	}

	private function Json2Array(array $jsonArray, array &$paramArray)
	{ 
		foreach($jsonArray as $k => $v) { 
			if (is_array($v)) { 
				$this->Json2Array($v, $paramArray);
			} else { 
				array_push($paramArray, $k . '=' . $v);
			}
		}
	}

	private function HmacSha256(string $key, string $data)
	{
		return base64_encode(hash_hmac("sha256", $data, $key, $raw_output = true));
	}

	private $secret = null;
} // class
