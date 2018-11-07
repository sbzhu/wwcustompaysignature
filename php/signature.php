<?php

class SignatureGetter { 

	public function __construct($secret) 
	{ 
		$this->secret = $secret;
	}

	public function GetSha1HmacSign(string $key, string $data)
	{
		return base64_encode(hash_hmac("sha256", $data, $key, $raw_output = true));
	}

	private $secret = null;
} // class
