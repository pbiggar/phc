<?php

error_reporting(E_ALL | E_STRICT);

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */

/**
 * Written and contributed by
 * Alex Stapleton,
 * Andy Doctorow,
 * Tarakan,
 * Bill Zeller,
 * Vijay "Cyberax" Bhatter
 * traB
 * This code is released into the public domain
 * http://www.tapouillo.com/firefox_extension/sourcecode.txt
 */

function zeroFill($a, $b)
{
	$z = hexdec(80000000);
	if ($z & $a)
	{
		$a = ($a>>1);
		$a &= (~$z);
		$a |= 0x40000000;
		$a = ($a>>($b-1));
	}
	else
	{
		$a = ($a>>$b);
	}

	return $a;
}

/**
 * setLength function by Alexander Hjalmarsson
 */
function setLength(&$array,$length)
{
    for ($i = 0; $i < $length; $i++)
    {
        $array[] = "";
    }
}

/*
 * AES Cipher function: encrypt 'input' with Rijndael algorithm
 *
 *   takes   byte-array 'input' (16 bytes)
 *           2D byte-array key schedule 'w' (Nr+1 x Nb bytes)
 *
 *   applies Nr rounds (10/12/14) using key schedule w for 'add round key' stage
 *
 *   returns byte-array encrypted value (16 bytes)
 */
// main Cipher function [§5.1]
function Cipher($input, $w)
{
	$Nb = 4;               // block size (in words): no of columns in state (fixed at 4 for AES)
	$Nr = count($w) / $Nb - 1; // no of rounds: 10/12/14 for 128/192/256-bit keys

	$state = array(array(), array(), array(), array());  // initialise 4xNb byte-array 'state' with input [§3.4]
	for($i = 0; $i < 4 * $Nb; $i++)
	{
		$state[$i % 4][floor($i / 4)] = $input[$i];
	}

	$state = AddRoundKey($state, $w, 0, $Nb);

	for($round = 1; $round < $Nr; $round++)
	{
		$state = SubBytes($state, $Nb);
		$state = ShiftRows($state, $Nb);
		$state = MixColumns($state, $Nb);
		$state = AddRoundKey($state, $w, $round, $Nb);
	}

	$state = SubBytes($state, $Nb);
	$state = ShiftRows($state, $Nb);
	$state = AddRoundKey($state, $w, $Nr, $Nb);

	$output = array(4 * $Nb);  // convert state to 1-d array before returning [§3.4]

	for($i = 0; $i < 4 * $Nb; $i++)
	{
		$output[$i] = $state[$i % 4][floor($i / 4)];
	}

	return $output;
}

// apply SBox to state S [§5.1.1]
function SubBytes($s, $Nb)
{
	global $Sbox;

	for($r = 0; $r < 4; $r++)
	{
		for($c = 0; $c < $Nb; $c++)
		{
			$s[$r][$c] = $Sbox[$s[$r][$c]];
		}
	}

	return $s;
}

// shift row r of state S left by r bytes [§5.1.2]
function ShiftRows($s, $Nb)
{
	// shift row r of state S left by r bytes [§5.1.2]
	$t = array();

	for($r = 1; $r < 4; $r++)
	{
		for($c = 0; $c < 4; $c++)
		{
			$t[$c] = $s[$r][($c + $r) % $Nb];  // shift into temp copy
		}

		for($c = 0; $c < 4; $c++)
		{
			$s[$r][$c] = $t[$c];         // and copy back
		}
	}// note that this will work for Nb=4,5,6, but not 7,8 (always 4 for AES):

	return $s;  // see fp.gladman.plus.com/cryptography_technology/rijndael/aes.spec.311.pdf
}

// combine bytes of each col of state S [§5.1.3]
function MixColumns($s, $Nb)
{
	for($c = 0; $c < 4; $c++)
	{
		$a = array();  // 'a' is a copy of the current column from 's'
		$b = array();  // 'b' is a•{02} in GF(2^8)

		for($i = 0; $i < 4; $i++)
		{
			$a[$i] = $s[$i][$c];
			$b[$i] = $s[$i][$c] & 0x80 ? $s[$i][$c] << 1 ^ 0x011b : $s[$i][$c] << 1;
		}

		// a[n] ^ b[n] is a•{03} in GF(2^8)
		$s[0][$c] = $b[0] ^ $a[1] ^ $b[1] ^ $a[2] ^ $a[3]; // 2*a0 + 3*a1 + a2 + a3
		$s[1][$c] = $a[0] ^ $b[1] ^ $a[2] ^ $b[2] ^ $a[3]; // a0 * 2*a1 + 3*a2 + a3
		$s[2][$c] = $a[0] ^ $a[1] ^ $b[2] ^ $a[3] ^ $b[3]; // a0 + a1 + 2*a2 + 3*a3
		$s[3][$c] = $a[0] ^ $b[0] ^ $a[1] ^ $a[2] ^ $b[3]; // 3*a0 + a1 + a2 + 2*a3
	}

	return $s;
}

// xor Round Key into state S [§5.1.4]
function AddRoundKey($state, $w, $rnd, $Nb)
{
	for($r = 0; $r < 4; $r++)
	{
		for($c = 0; $c < $Nb; $c++)
		{
			$state[$r][$c] ^= $w[$rnd * 4 + $c][$r];
		}
	}

	return $state;
}

// generate Key Schedule (byte-array Nr+1 x Nb) from Key [§5.2]
function KeyExpansion($key)
{
	global $Rcon;

	$Nb = 4;            // block size (in words): no of columns in state (fixed at 4 for AES)
	$Nk = count($key) / 4;  // key length (in words): 4/6/8 for 128/192/256-bit keys
	$Nr = $Nk + 6;       // no of rounds: 10/12/14 for 128/192/256-bit keys

	$w = array($Nb * ($Nr + 1));
	setLength($temp, 4);

	for($i = 0; $i < $Nk; $i++)
	{
		$r = array($key[4 * $i], $key[4 * $i + 1], $key[4 * $i + 2], $key[4 * $i + 3]);
		$w[$i] = $r;
	}

	for($i = $Nk; $i < ($Nb * ($Nr + 1)); $i++)
	{
		$w[$i] = array();

		for($t = 0; $t < 4; $t++)
		{
			$temp[$t] = $w[$i - 1][$t];
		}

		if($i % $Nk == 0)
		{
			$temp = SubWord(RotWord($temp));

			for($t = 0; $t < 4; $t++)
			{
				$temp[$t] ^= $Rcon[$i / $Nk][$t];
			}
		}
		elseif($Nk > 6 && $i % $Nk == 4)
		{
			$temp = SubWord($temp);
		}

		for($t = 0; $t < 4; $t++)
		{
			$w[$i][$t] = $w[$i - $Nk][$t] ^ $temp[$t];
		}
	}

	return $w;
}

// apply SBox to 4-byte word w
function SubWord($w)
{
	global $Sbox;

	for($i = 0; $i < 4; $i++)
	{
		$w[$i] = $Sbox[$w[$i]];
	}

	return $w;
}

// rotate 4-byte word w left by one byte
function RotWord($w)
{
	$w[4] = $w[0];

	for($i = 0; $i < 4; $i++)
	{
		$w[$i] = $w[$i + 1];
	}

	return $w;
}

// Sbox is pre-computed multiplicative inverse in GF(2^8) used in SubBytes and KeyExpansion [§5.1.1]
$Sbox =  array(0x63,0x7c,0x77,0x7b,0xf2,0x6b,0x6f,0xc5,0x30,0x01,0x67,0x2b,0xfe,0xd7,0xab,0x76,
               0xca,0x82,0xc9,0x7d,0xfa,0x59,0x47,0xf0,0xad,0xd4,0xa2,0xaf,0x9c,0xa4,0x72,0xc0,
               0xb7,0xfd,0x93,0x26,0x36,0x3f,0xf7,0xcc,0x34,0xa5,0xe5,0xf1,0x71,0xd8,0x31,0x15,
               0x04,0xc7,0x23,0xc3,0x18,0x96,0x05,0x9a,0x07,0x12,0x80,0xe2,0xeb,0x27,0xb2,0x75,
               0x09,0x83,0x2c,0x1a,0x1b,0x6e,0x5a,0xa0,0x52,0x3b,0xd6,0xb3,0x29,0xe3,0x2f,0x84,
               0x53,0xd1,0x00,0xed,0x20,0xfc,0xb1,0x5b,0x6a,0xcb,0xbe,0x39,0x4a,0x4c,0x58,0xcf,
               0xd0,0xef,0xaa,0xfb,0x43,0x4d,0x33,0x85,0x45,0xf9,0x02,0x7f,0x50,0x3c,0x9f,0xa8,
               0x51,0xa3,0x40,0x8f,0x92,0x9d,0x38,0xf5,0xbc,0xb6,0xda,0x21,0x10,0xff,0xf3,0xd2,
               0xcd,0x0c,0x13,0xec,0x5f,0x97,0x44,0x17,0xc4,0xa7,0x7e,0x3d,0x64,0x5d,0x19,0x73,
               0x60,0x81,0x4f,0xdc,0x22,0x2a,0x90,0x88,0x46,0xee,0xb8,0x14,0xde,0x5e,0x0b,0xdb,
               0xe0,0x32,0x3a,0x0a,0x49,0x06,0x24,0x5c,0xc2,0xd3,0xac,0x62,0x91,0x95,0xe4,0x79,
               0xe7,0xc8,0x37,0x6d,0x8d,0xd5,0x4e,0xa9,0x6c,0x56,0xf4,0xea,0x65,0x7a,0xae,0x08,
               0xba,0x78,0x25,0x2e,0x1c,0xa6,0xb4,0xc6,0xe8,0xdd,0x74,0x1f,0x4b,0xbd,0x8b,0x8a,
               0x70,0x3e,0xb5,0x66,0x48,0x03,0xf6,0x0e,0x61,0x35,0x57,0xb9,0x86,0xc1,0x1d,0x9e,
               0xe1,0xf8,0x98,0x11,0x69,0xd9,0x8e,0x94,0x9b,0x1e,0x87,0xe9,0xce,0x55,0x28,0xdf,
               0x8c,0xa1,0x89,0x0d,0xbf,0xe6,0x42,0x68,0x41,0x99,0x2d,0x0f,0xb0,0x54,0xbb,0x16);

// Rcon is Round Constant used for the Key Expansion [1st col is 2^(r-1) in GF(2^8)] [§5.2]
$Rcon = array( array(0x00, 0x00, 0x00, 0x00),
	           array(0x01, 0x00, 0x00, 0x00),
	           array(0x02, 0x00, 0x00, 0x00),
	           array(0x04, 0x00, 0x00, 0x00),
	           array(0x08, 0x00, 0x00, 0x00),
	           array(0x10, 0x00, 0x00, 0x00),
	           array(0x20, 0x00, 0x00, 0x00),
	           array(0x40, 0x00, 0x00, 0x00),
	           array(0x80, 0x00, 0x00, 0x00),
	           array(0x1b, 0x00, 0x00, 0x00),
	           array(0x36, 0x00, 0x00, 0x00));


/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */

/*
 * Use AES to encrypt 'plaintext' with 'password' using 'nBits' key, in 'Counter' mode of operation
 *                           - see http://csrc.nist.gov/publications/nistpubs/800-38a/sp800-38a.pdf
 *   for each block
 *   - outputblock = cipher(counter, key)
 *   - cipherblock = plaintext xor outputblock
 */
function AESEncryptCtr($plaintext, $password, $nBits)
{
	if(!($nBits == 128 || $nBits == 192 || $nBits == 256))
	{
		return '';  // standard allows 128/192/256 bit keys
	}

	// for this example script, generate the key by applying Cipher to 1st 16/24/32 chars of password;
	// for real-world applications, a more secure approach would be to hash the password e.g. with SHA-1
	$nBytes = $nBits / 8;  // no bytes in key

	$pwBytes = array();

	for($i = 0; $i < $nBytes; $i++)
	{
		$pwBytes[$i] = ord($password[$i]) & 0xff;
	}

	$key = Cipher($pwBytes, KeyExpansion($pwBytes));
	$key = array_merge($key, array_slice($key , 0, $nBytes-16)); // key is now 16/24/32 bytes long

	// initialise counter block (NIST SP800-38A §B.2): millisecond time-stamp for nonce in 1st 8 bytes,
	// block counter in 2nd 8 bytes
	$blockSize = 16;  // block size fixed at 16 bytes / 128 bits (Nb=4) for AES
    setLength($counterBlock, $blockSize); // block size fixed at 16 bytes / 128 bits (Nb=4) for AES
	$nonce = 1262304001;//floatval(time().substr(microtime(), 2, 3));  // milliseconds since 1-Jan-1970

	// encode nonce in two stages to cater for JavaScript 32-bit limit on bitwise ops
	for($i = 0; $i < 4; $i++)
	{
		$counterBlock[$i] = zeroFill($nonce, $i * 8) & 0xff;
	}
	for($i = 0; $i < 4; $i++)
	{
		$counterBlock[$i + 4] = zeroFill($nonce / 0x100000000, $i * 8) & 0xff;
	}

	// generate key schedule - an expansion of the key into distinct Key Rounds for each round
	$keySchedule = KeyExpansion($key);
	$blockCount = ceil(strlen($plaintext) / $blockSize);
	$ciphertext = array($blockCount);  // ciphertext as array of strings

	for($b = 0; $b < $blockCount; $b++)
	{
		// set counter (block #) in last 8 bytes of counter block (leaving nonce in 1st 8 bytes)
		// again done in two stages for 32-bit ops
		for($c = 0; $c < 4; $c++)
		{
			$counterBlock[15 - $c] = zeroFill($b, $c * 8) & 0xff;
		}

		for($c = 0; $c < 4; $c++)
		{
			$counterBlock[15 - $c -4] = zeroFill($b / 0x100000000, $c * 8);
		}

		$cipherCntr = Cipher($counterBlock, $keySchedule);  // -- encrypt counter block --

		// calculate length of final block:
		$blockLength = $b < $blockCount - 1 ? $blockSize : (strlen($plaintext) - 1) % $blockSize + 1;

		$ct = '';

		// -- xor plaintext with ciphered counter byte-by-byte --
		for($i = 0; $i < $blockLength; $i++)
		{
			$plaintextByte = ord($plaintext[$b * $blockSize + $i]);
			$cipherByte = $plaintextByte ^ $cipherCntr[$i];
			$ct .= chr($cipherByte);
		}
		// ct is now ciphertext for this block

		$ciphertext[$b] = escCtrlChars($ct);  // escape troublesome characters in ciphertext
	}

	// convert the nonce to a string to go on the front of the ciphertext
	$ctrTxt = '';
	for($i = 0; $i < 8; $i++)
	{
		$ctrTxt .= chr($counterBlock[$i]);
	}

	$ctrTxt = escCtrlChars($ctrTxt);

	// use '-' to separate blocks, use Array.join to concatenate arrays of strings for efficiency
	return $ctrTxt.'-'.implode('-', $ciphertext);
}

/*
 * Use AES to decrypt 'ciphertext' with 'password' using 'nBits' key, in Counter mode of operation
 *
 *   for each block
 *   - outputblock = cipher(counter, key)
 *   - cipherblock = plaintext xor outputblock
 */
function AESDecryptCtr($ciphertext, $password, $nBits)
{
	if(!($nBits == 128 || $nBits == 192 || $nBits == 256))
	{
		return '';  // standard allows 128/192/256 bit keys
	}

	$nBytes = $nBits / 8;  // no bytes in key
    setLength($pwBytes, $nBytes);

	for($i = 0; $i < $nBytes; $i++)
	{
		$pwBytes[$i] = ord($password[$i]) & 0xff;
	}

	$pwKeySchedule = KeyExpansion($pwBytes);
	$key = Cipher($pwBytes, $pwKeySchedule);

	$key = array_merge($key, array_slice($key, 0, $nBytes - 16)); // key is now 16/24/32 bytes long

	$keySchedule = KeyExpansion($key);

	$ciphertext = explode('-', $ciphertext);  // split ciphertext into array of block-length strings

	// recover nonce from 1st element of ciphertext
	$blockSize = 16;  // block size fixed at 16 bytes / 128 bits (Nb=4) for AES
    setLength($counterBlock, $blockSize);

	$ctrTxt = unescCtrlChars($ciphertext[0]);

	for($i = 0; $i < 8; $i++)
	{
		$counterBlock[$i] = ord($ctrTxt[$i]);
	}

    setLength($plaintext, count($ciphertext) - 1);

	for($b = 1; $b < count($ciphertext); $b++)
	{
		// set counter (block #) in last 8 bytes of counter block (leaving nonce in 1st 8 bytes)
		for($c = 0; $c < 4; $c++)
		{
			$counterBlock[ 15 - $c] = zeroFill(($b - 1), $c * 8) & 0xff;
		}

		for($c = 0; $c < 4; $c++)
		{
			$counterBlock[15 - $c - 4] = zeroFill(($b / 0x100000000 - 1), $c * 8) & 0xff;
		}

		$cipherCntr = Cipher($counterBlock, $keySchedule);  // encrypt counter block

		$ciphertext[$b] = unescCtrlChars($ciphertext[$b]);

		$pt = '';
		for($i = 0; $i < strlen($ciphertext[$b]); $i++)
		{
			// -- xor plaintext with ciphered counter byte-by-byte --
			$ciphertextByte = ord($ciphertext[$b][$i]);
			$plaintextByte = $ciphertextByte ^ $cipherCntr[$i];
			$pt .= chr($plaintextByte);
		}
		// pt is now plaintext for this block

		$plaintext[$b - 1] = $pt;  // b-1 'cos no initial nonce block in plaintext
	}

	return implode('', $plaintext);
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */

// escape control chars which might cause problems handling ciphertext
function escCtrlChars($str)
{
    return preg_replace('/([\0\t\n\v\f\r\xa0\'"!-])/ie', '"!".ord(substr("$1",0,1))."!"', $str);
    // \xa0 to cater for bug in Firefox; include '-' to leave it free for use as a block marker
}

// unescape potentially problematic control characters
function unescCtrlChars($str)
{
	return preg_replace("/(!\d\d?\d?!)/ie", 'chr(substr("$1", 1, -1))', $str);
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */

/*
 * if escCtrlChars()/unescCtrlChars() still gives problems, use encodeBase64()/decodeBase64() instead
 */
$b64 = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/=";

// http://tools.ietf.org/html/rfc4648
function encodeBase64($str)
{
	$i = 0;
	$enc = '';

	$str = encodeUTF8($str);  // encode multi-byte chars into UTF-8 for byte-array

	do {  // pack three octets into four hexets
		$o1 = ord($str[$i++]);
		$o2 = ord($str[$i++]);
		$o3 = ord($str[$i++]);

		$bits = $o1 << 16 | $o2 << 8 | $o3;

		$h1 = $bits >> 18 & 0x3f;
		$h2 = $bits >> 12 & 0x3f;
		$h3 = $bits >> 6 & 0x3f;
		$h4 = $bits & 0x3f;

		// end of string? index to '=' in b64
		if (is_nan($o3)) $h4 = 64;
		if (is_nan($o2)) $h3 = 64;

		// use hexets to index into b64, and append result to encoded string
		$enc += $b64[$h1] + $b64[$h2] + $b64[$h3] + $b64[$h4];
	} while ($i < strlen($str));

	return $enc;
}

function decodeBase64($str)
{
	$i = 0;
	$enc = '';

	do {  // unpack four hexets into three octets using index points in b64
		$h1 = strpos($b64, $str[$i++]);
		$h2 = strpos($b64, $str[$i++]);
		$h3 = strpos($b64, $str[$i++]);
		$h4 = strpos($b64, $str[$i++]);

		$bits = $h1 << 18 | $h2 << 12 | $h3 << 6 | $h4;

		$o1 = $bits >> 16 & 0xff;
		$o2 = $bits >> 8 & 0xff;
		$o3 = $bits & 0xff;

		if ($h3 == 64)
		{
			$enc += chr($o1);
		}
		elseif($h4 == 64)
		{
			$enc += chr($o1.$o2);
		}
		else
		{
			$enc += chr($o1.$o2.$o3);
		}
	} while ($i < strlen($str));

	return decodeUTF8($enc);  // decode UTF-8 byte-array back to Unicode
}

// encode multi-byte string into utf-8 multiple single-byte characters
function encodeUTF8($str)
{
	$str = preg_replace("/[\u0080-\u07ff]/g", chr(0xc0 | ord($str[0]) >> 6 . 0x80 | ord($str[0]) & 0x3f), $str);
	$str = preg_replace("/[\u0800-\uffff]/g", chr(0xe0 | ord($str[0]) >> 12 . 0x80 | ord($str[0]) >> 6 & 0x3F . 0x80 | ord($str[0]) & 0x3f), $str);

	return $str;
}

// decode utf-8 encoded string back into multi-byte characters
function decodeUTF8($str)
{
	$str = preg_replace("/[\u00c0-\u00df][\u0080-\u00bf]/g", chr((ord($str[0]) & 0x1f) << 6 | ord($str[1]) & 0x3f), $str);
	$str = preg_replace("/[\u00e0-\u00ef][\u0080-\u00bf][\u0080-\u00bf]/g", chr((ord($str[0]) & 0x0f) << 12 | (ord($str[1]) & 0x3f << 6) | ord($str[0]) & 0x3f), $str);

	return $str;
}

// convert byte array to hex string for displaying test vectors
function byteArrayToHexStr($b)
{
	$s = '';
	for($i = 0; $i < strlen($b); $i++)
	{
		$s += strval($b[$i]).' ';
	}

	return $s;
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */

$plainText = <<<EOF
abcdefghijklmnopqrstuvwxyz,-ABCDEFGHIJKLMNOPQRSTUVWXYZ,-1234567890.
abcdefghijklmnopqrstuvwxyz,-ABCDEFGHIJKLMNOPQRSTUVWXYZ,-1234567890.
abcdefghijklmnopqrstuvwxyz,-ABCDEFGHIJKLMNOPQRSTUVWXYZ,-1234567890.
abcdefghijklmnopqrstuvwxyz,-ABCDEFGHIJKLMNOPQRSTUVWXYZ,-1234567890.
abcdefghijklmnopqrstuvwxyz,-ABCDEFGHIJKLMNOPQRSTUVWXYZ,-1234567890.
abcdefghijklmnopqrstuvwxyz,-ABCDEFGHIJKLMNOPQRSTUVWXYZ,-1234567890.
abcdefghijklmnopqrstuvwxyz,-ABCDEFGHIJKLMNOPQRSTUVWXYZ,-1234567890.
abcdefghijklmnopqrstuvwxyz,-ABCDEFGHIJKLMNOPQRSTUVWXYZ,-1234567890.
abcdefghijklmnopqrstuvwxyz,-ABCDEFGHIJKLMNOPQRSTUVWXYZ,-1234567890.
abcdefghijklmnopqrstuvwxyz,-ABCDEFGHIJKLMNOPQRSTUVWXYZ,-1234567890.
abcdefghijklmnopqrstuvwxyz,-ABCDEFGHIJKLMNOPQRSTUVWXYZ,-1234567890.
abcdefghijklmnopqrstuvwxyz,-ABCDEFGHIJKLMNOPQRSTUVWXYZ,-1234567890.
abcdefghijklmnopqrstuvwxyz,-ABCDEFGHIJKLMNOPQRSTUVWXYZ,-1234567890.
abcdefghijklmnopqrstuvwxyz,-ABCDEFGHIJKLMNOPQRSTUVWXYZ,-1234567890.
abcdefghijklmnopqrstuvwxyz,-ABCDEFGHIJKLMNOPQRSTUVWXYZ,-1234567890.
abcdefghijklmnopqrstuvwxyz,-ABCDEFGHIJKLMNOPQRSTUVWXYZ,-1234567890.
abcdefghijklmnopqrstuvwxyz,-ABCDEFGHIJKLMNOPQRSTUVWXYZ,-1234567890.
abcdefghijklmnopqrstuvwxyz,-ABCDEFGHIJKLMNOPQRSTUVWXYZ,-1234567890.
abcdefghijklmnopqrstuvwxyz,-ABCDEFGHIJKLMNOPQRSTUVWXYZ,-1234567890.
abcdefghijklmnopqrstuvwxyz,-ABCDEFGHIJKLMNOPQRSTUVWXYZ,-1234567890.
abcdefghijklmnopqrstuvwxyz,-ABCDEFGHIJKLMNOPQRSTUVWXYZ,-1234567890.
abcdefghijklmnopqrstuvwxyz,-ABCDEFGHIJKLMNOPQRSTUVWXYZ,-1234567890.
abcdefghijklmnopqrstuvwxyz,-ABCDEFGHIJKLMNOPQRSTUVWXYZ,-1234567890.
abcdefghijklmnopqrstuvwxyz,-ABCDEFGHIJKLMNOPQRSTUVWXYZ,-1234567890.
abcdefghijklmnopqrstuvwxyz,-ABCDEFGHIJKLMNOPQRSTUVWXYZ,-1234567890.
abcdefghijklmnopqrstuvwxyz,-ABCDEFGHIJKLMNOPQRSTUVWXYZ,-1234567890.
abcdefghijklmnopqrstuvwxyz,-ABCDEFGHIJKLMNOPQRSTUVWXYZ,-1234567890.
abcdefghijklmnopqrstuvwxyz,-ABCDEFGHIJKLMNOPQRSTUVWXYZ,-1234567890.
abcdefghijklmnopqrstuvwxyz,-ABCDEFGHIJKLMNOPQRSTUVWXYZ,-1234567890.
abcdefghijklmnopqrstuvwxyz,-ABCDEFGHIJKLMNOPQRSTUVWXYZ,-1234567890.
abcdefghijklmnopqrstuvwxyz,-ABCDEFGHIJKLMNOPQRSTUVWXYZ,-1234567890.
abcdefghijklmnopqrstuvwxyz,-ABCDEFGHIJKLMNOPQRSTUVWXYZ,-1234567890.
abcdefghijklmnopqrstuvwxyz,-ABCDEFGHIJKLMNOPQRSTUVWXYZ,-1234567890.
abcdefghijklmnopqrstuvwxyz,-ABCDEFGHIJKLMNOPQRSTUVWXYZ,-1234567890.
abcdefghijklmnopqrstuvwxyz,-ABCDEFGHIJKLMNOPQRSTUVWXYZ,-1234567890.
abcdefghijklmnopqrstuvwxyz,-ABCDEFGHIJKLMNOPQRSTUVWXYZ,-1234567890.
abcdefghijklmnopqrstuvwxyz,-ABCDEFGHIJKLMNOPQRSTUVWXYZ,-1234567890.
abcdefghijklmnopqrstuvwxyz,-ABCDEFGHIJKLMNOPQRSTUVWXYZ,-1234567890.
abcdefghijklmnopqrstuvwxyz,-ABCDEFGHIJKLMNOPQRSTUVWXYZ,-1234567890.
abcdefghijklmnopqrstuvwxyz,-ABCDEFGHIJKLMNOPQRSTUVWXYZ,-1234567890.
EOF;

$password = "SuperSecretThatIsVeryVeryVeryLong";

for($i = 0; $i >= 5; $i++)
{
    $plainText .= $plainText;
}

$cipherText = AESEncryptCtr($plainText, $password, 256);
$decryptedText = AESDecryptCtr($cipherText, $password, 256);