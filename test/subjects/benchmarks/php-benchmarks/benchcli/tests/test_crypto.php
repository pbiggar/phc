<?php
error_reporting(E_ALL ^ E_STRICT);

$BigIntegerZero = nbv(0);
$BigIntegerOne = nbv(1);

define("BI_DB", 28);
define("BI_DM", ((1<<28)-1));
define("BI_DV", (1<<28));

define("BI_FP", 52);
define("BI_FV", pow(2,BI_FP));
define("BI_F1", BI_FP-28);
define("BI_F2", 2*28-BI_FP);

// Digit conversions
$BI_RM = "0123456789abcdefghijklmnopqrstuvwxyz";
$BI_RC = array();
$rr    = ord("0");
$vv    = "";
for($vv = 0; $vv <= 9; ++$vv) {
    $BI_RC[$rr++] = $vv;
}
$rr = ord("a");
for ($vv = 10; $vv < 36; ++$vv) {
    $BI_RC[$rr++] = $vv;
}
$rr = ord("A");
for($vv = 10; $vv < 36; ++$vv) {
    $BI_RC[$rr++] = $vv;
}
$rngc = new rng();
$rngc->init();

/*
 * Unsigned right shift function, since PHP has neither >>> operator nor unsigned ints
 * This function is from http://www.movable-type.co.uk/scripts/aes-php.html .
 *
 * @param a  number to be shifted (32-bit integer)
 * @param b  number of bits to shift a to the right (0..31)
 *
 * @return   a right-shifted and zero-filled by b bits
 */
function urs($a, $b) {
    $a &= 0xffffffff;
    $b &= 0x1f;  // (bounds check)
    if ($a&0x80000000 && $b>0) {   // if left-most bit set
        $a = ($a>>1) & 0x7fffffff;   //   right-shift one bit & clear left-most bit
        $a = $a >> ($b-1);           //   remaining right-shifts
    } else {                       // otherwise
        $a = ($a>>$b);               //   use normal right-shift
    }
    return $a;
}

function nbi() {
    return new BigInteger(null,null,null);
}

// return bigint initialized to value
function nbv($i) {
    $r = nbi();
    $r->fromInt($i);
    return $r;
}

function int2char($n) {
    return $GLOBALS['BI_RM'][$n];
}

function intAt($s,$i)
{
    $c = $GLOBALS['BI_RC'][ord($s[$i])];
    return (is_null($c))?-1:$c;
}

function nbits($x)
{   
    $r = 1;
    if (($t=urs($x,16)) != 0) {
        $x = $t;
        $r += 16;
    }
    if (($t=$x>>8) != 0) {
        $x = $t;
        $r += 8;
    }
    if (($t=$x>>4) != 0) {
        $x = $t;
        $r += 4;
    }
    if (($t=$x>>2) != 0) {
        $x = $t;
        $r += 2;
    }
    if (($t=$x>>1) != 0) {
        $x = $t;
        $r += 1;
    }
    return $r;
}

// return number of 1 bits in x
function cbit($x)
{
    $r = 0;
    while($x != 0) {
        $x &= $x-1;
        ++$r;
    }
    return $r;
}

// return index of lowest 1-bit in x, x < 2^31
function lbit($x)
{
    if($x == 0) {
        return -1;
    }
    $r = 0;
    if(($x&0xffff) == 0)
    {
        $x >>= 16;
        $r += 16;
    }
    if(($x&0xff) == 0)
    {
        $x >>= 8;
        $r  += 8;
    }
    if(($x&0xf) == 0)
    {
        $x >>= 4;
        $r  += 4;
    }
    if(($x&3) == 0) {
        $x >>= 2;
        $r  += 2;
    }
    if(($x&1) == 0) {
        ++$r;
    }
    return $r;
}

function setLength(&$array,$length) {
    for ($i = 0; $i < $length; $i++) {
        $array[] = "";
    }
}

// convert a (hex) string to a bignum object
function parseBigInt($str,$r) {
    return new BigInteger($str,$r);
}


class BigInteger
{
    var $array;
    var $t,$s;
    var $lowprimes = array(2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67,71,73,79,83,89,97,101,103,107,109,113,127,131,137,139,149,151,157,163,167,173,179,181,191,193,197,199,211,223,227,229,233,239,241,251,257,263,269,271,277,281,283,293,307,311,313,317,331,337,347,349,353,359,367,373,379,383,389,397,401,409,419,421,431,433,439,443,449,457,461,463,467,479,487,491,499,503,509);
    var $lplim;


    function BigInteger($a,$b=null,$c=null)
    {
        $this->array = array();
        if (!is_null($a)) {
            if ("integer" == gettype($a)) {
                $this->fromNumber($a,$b,$c);
            } else if (is_null($b) && "string" != gettype($a)) {
                $this->fromString($a,256);
            } else {
                $this->fromString($a,$b);
            }

        }
        $this->lplim = (1<<26)/$this->lowprimes[count($this->lowprimes)-1];
    }
    function am($i,$x,$w,$j,$c,$n)
    {
        $this_array = &$this->array;
        $w_array    = &$w->array;
        $xl         = $x&0x3fff;
        $xh         = $x>>14;
        while (--$n >= 0) {
            $l = $this_array[$i]&0x3fff;
            $h = $this_array[$i++]>>14;
            $m = $xh*$l+$h*$xl;
            $l = $xl*$l+(($m&0x3fff)<<14)+$w_array[$j]+$c;
            $c = ($l>>28)+($m>>14)+$xh*$h;
            $w_array[$j++] = $l&0xfffffff;
        }
        return $c;
    }
    function copyTo($r)
    {
        $this_array = &$this->array;
        $r_array    = &$r->array;
        for ($i = $this->t-1; $i >= 0; --$i) {
            $r_array[$i] = $this_array[$i];
        }
        $r->t = $this->t;
        $r->s = $this->s;
        
    }
    function fromInt($x)
    {
        $this_array = &$this->array;
        $this->t    = 1;
        $this->s    = ($x<0) ? -1 : 0;
        if ($x > 0) {
            $this_array[0] = $x;
        } else if($x < -1) {
            $this_array[0] = $x + BI_DV;
        } else {
        $this->t = 0;
        }
    }
    function fromString($s, $b)
    {
        $this_array = &$this->array;
        if ($b == 16) {
            $k = 4;
        } else if ($b == 8) {
            $k = 3;
        } else if ($b == 256) {
            $k = 8;
        } else if ($b == 2) {
            $k = 1;
        } else if ($b == 32) {
            $k = 5;
        } else if ($b == 4) {
            $k = 2;
        } else {
            $this->fromRadix($s,$b);
            return;
        }
        $this->t = 0;
        $this->s = 0;
        if (is_array($s)) {
        	$i = count($s);
        } else {
        	$i = strlen($s);
        }
        $mi = false;
        $sh = 0;
        while (--$i >= 0) {
            $x = ($k==8) ? $s[$i]&0xFF:intAt($s,$i);
            if ($x < 0) {
                if ($s[$i] == "-") {
                    $mi = true;
                    continue;
                }
                $mi = false;
            }
            if ($sh == 0) {
                $this_array[$this->t++] = $x;
            } else if($sh + $k > BI_DB) {
                $this_array[$this->t-1] |= ($x&((1<<(BI_DB-$sh))-1)) << $sh;
                $this_array[$this->t++]  = ($x >> (BI_DB-$sh));
            } else {
                $this_array[$this->t-1] |= $x << $sh;
            }
            $sh += $k;
            if ($sh >= BI_DB) {
                $sh -= BI_DB;
            }
        }
        if ($k == 8 && ($s[0]&0x80) != 0) {
            $this->s = -1;
            if ($sh > 0) {
                $this_array[$this->t-1] |= ((1<<(BI_DB - $sh))-1) << $sh;
            }
        }
        $this->clamp();
        if ($mi) {
            $GLOBALS['BigIntegerZero']->subTo($this,$this);
        }
    }
    function clamp()
    {
        $this_array = &$this->array;
        $c          = $this->s & BI_DM;
        while ($this->t > 0 && $this_array[$this->t-1] == $c) {
            --$this->t;
        }
    }
    function toString($b)
    {
        $this_array = &$this->array;
        if ($this->s < 0) {
            return "-"+$this->negate()->toString($b);
        }
        if ($b == 16) {
            $k = 4;
        } else if ($b == 8) {
            $k = 3;
        } else if ($b == 2) {
            $k = 1;
        } else if ($b == 32) {
            $k = 5;
        } else if ($b == 4) {
            $k = 2;
        } else {
            return $this->toRadix($b);
        }
        $km = (1<<$k)-1;
        $m  = false;
        $r  = "";
        $i  = $this->t;
        $p  = BI_DB - ($i * BI_DB) % $k;
        if ($i-- > 0) {
            if ($p < BI_DB && ($d = $this_array[$i] >> p) > 0) {
                $m = true;
                $r = int2char($d);
            }
            while ($i >= 0) {
                if ($p < $k) {
                    $d  = ($this_array[$i] & ((1<<$p)-1)) << ($k-$p);
                    $d |= $this_array[--$i] >> ($p+=BI_DB-$k);
                } else {
                    $d = ($this_array[$i] >> ($p-=$k)) & $km;
                    if ($p <= 0) {
                        $p += BI_DB;
                        --$i;
                    }
                }
                if ($d > 0) {
                    $m = true;
                }
                if ($m) {
                    $r .= int2char($d);
                }
            }
        }
        return $m ? $r : "0";

    }
    function negate()
    {
        $r = nbi();
        $GLOBALS['BigIntegerZero']->subTo($this,$r);
        return $r;
    }
    function abs()
    {
        return ($this->s < 0) ? $this->negate() : $this;
    }
    function compareTo($a)
    {
        $this_array = &$this->array;
        $a_array    = &$a->array;
        $r          = $this->s - $a->s;
        if ($r != 0) {
            return $r;
        }
        $i = $this->t;
        $r = $i - $a->t;
        if ($r != 0) {
            return $r;
        }
        while (--$i >= 0) {
            if (($r = $this_array[$i] - $a_array[$i]) != 0) {
                return $r;
            }
        }
        return 0;
    }
    function bitLength()
    {
        $this_array = &$this->array;
        if ($this->t <= 0) {
            return 0;
        }
        return BI_DB * ($this->t - 1) + nbits($this_array[$this->t-1] ^ ($this->s&BI_DM));
    }

    // (protected) r = this << n*DB
    function dlShiftTo($n,$r)
    {
        
    	$this_array = &$this->array;
        $r_array    = &$r->array;
       
        for ($i = $this->t-1; $i >= 0; --$i) {
        
            $r_array[$i+$n] = $this_array[$i];
        }
        for ($i = $n-1; $i >= 0; --$i) {
            $r_array[$i] = 0;
        }
        $r->t = $this->t+$n;
        $r->s = $this->s;
    }

    // (protected) r = this >> n*DB
    function drShiftTo($n,$r)
    {
        $this_array = &$this->array;
        $r_array    = &$r->array;
        for ($i = $n; $i < $this->t; ++$i) {
            $r_array[$i-$n] = $this_array[$i];
        }
        $r->t = max($this->t -$n,0);
        $r->s = $this->s;
    }
    function lShiftTo($n,$r)
    {
        $this_array = &$this->array;
        $r_array    = &$r->array;
        $bs         = $n % BI_DB;
        $cbs        = BI_DB - $bs;
        $bm         = (1<<$cbs) - 1;
        $ds         = floor($n/BI_DB);
        $c          = ($this->s << $bs) & BI_DM;

        for ($i = $this->t - 1; $i >= 0; --$i) {
            $r_array[$i+$ds+1] = ($this_array[$i] >> $cbs) | $c;
            $c = ($this_array[$i] & $bm) << $bs;
        }
       
        for ($i = $ds - 1; $i >= 0; --$i) {
            $r_array[$i] = 0;
        }
        $r_array[$ds] = $c;
        $r->t         = $this->t + $ds + 1;
        $r->s         = $this->s;
        $r->clamp();
    }
    function rShiftTo($n,$r)
    {
        $this_array = &$this->array;
        $r_array    = &$r->array;
        $r->s       = $this->s;
        $ds         = floor($n / BI_DB);
        if ($ds >= $this->t) {
            $r->t = 0;
            return;
        }
        $bs         = $n % BI_DB;
        $cbs        = BI_DB - $bs;
        $bm         = (1<<$bs) - 1;
        $r_array[0] = $this_array[$ds] >> $bs;
        for ($i = $ds + 1; $i < $this->t; ++$i) {
            $r_array[$i-$ds-1] |= ($this_array[$i]&$bm) << $cbs;
            $r_array[$i-$ds] = $this->array[$i] >> $bs;
        }
        if ($bs > 0) {
            $r_array[$this->t-$ds-1] |= ($this->s & $bm) << $cbs;
        }
        $r->t = $this->t - $ds;
        $r->clamp();

    }
    function subTo($a,$r)
    {
        $this_array = &$this->array;
        $r_array    = &$r->array;
        $a_array    = &$a->array;
        $i          = 0;
        $c          = 0;
        $m          = min($a->t,$this->t);
        while ($i < $m) {
            $c            += $this_array[$i] - $a_array[$i];
            $r_array[$i++] = $c&BI_DM;
            $c           >>= BI_DB;
        }
        if ($a->t < $this->t) {
            $c -= $a->s;
            while ($i < $this->t) {
                $c            += $this_array[$i];
                $r_array[$i++] = $c & BI_DM;
                $c           >>= BI_DM;
            }
            $c += $this->s;
        } else {
            $c += $this->s;
            while ($i < $a->t) {
                $c            -= $a_array[$i];
                $r_array[$i++] = $c&BI_DM;
                $c           >>= BI_DM;
            }
            $c -= $a->s;
        }
        $r->s = ($c < 0) ? -1 : 0;
        if ($c < -1) {
            $r_array[$i++] = BI_DV + $c;
        } else if ($c > 0) {
            $r_array[$i++] = $c;
        }
        $r->t = $i;
        $r->clamp();
    }   
    function multiplyTo($a,$r)
    {
        $this_array = &$this->array;
        $r_array    = &$r->array;
        $x          = $this->abs();
        $y          = $a->abs();
        $y_array    = &$y->array;
        $i          = $x->t;
    
        $r->t = $i + $y->t;
        while (--$i >= 0) {
            $r_array[$i] = 0;
        }
        for ($i = 0; $i < $y->t; ++$i) {
            $r_array[$i+$x->t] = $x->am(0,$y_array[$i],$r,$i,0,$x->t);
        }
        $r->s = 0;
        $r->clamp();
        if ($this->s != $a->s) {
            $GLOBALS['BigIntegerZero']->subTo($r,$r);
        }
    }
    // (protected) r = this^2, r != this (HAC 14.16)
    function squareTo($r)
    {
        $x         = $this->abs();
        $x_array   = &$x->array;
        $r_array   = &$r->array;
        $i = $r->t = 2*$x->t;

        while (--$i >= 0) {
            $r_array[$i] = 0;
        }
        for ($i = 0; $i < $x->t-1; ++$i) {
        
            $c = $x->am($i,$x_array[$i],$r,2*$i,0,1);
            
            if (($r_array[$i+$x->t]+=$x->am($i+1,2*$x_array[$i],$r,2*$i+1,$c,$x->t-$i-1)) >= BI_DV) {
                $r_array[$i+$x->t]  -= BI_DV;
                $r_array[$i+$x->t+1] = 1;
            }
        }
        if ($r->t > 0) {
            $r_array[$r->t-1] += $x->am($i,$x_array[$i],$r,2*$i,0,1);
        }
        $r->s = 0;
        $r->clamp();
    }
    // (protected) divide this by m, quotient and remainder to q, r (HAC 14.20)
    // r != q, this != m.  q or r may be null.
    function divRemTo($m,$q,$r)
    {
        $pm = $m->abs();
        if ($pm->t <= 0) {
            return;
        }
          
        $pt = $this->abs(); 
        if ($pt->t < $pm->t) {
            if(!is_null($q)) {
                $q->fromInt(0);
            }
            if(!is_null($r)) {
                $this->copyTo($r);
            }
            return;
        } 
        if (is_null($r))  {
            $r = nbi();
        }
        $y        = nbi();
        $ts       = $this->s;
        $ms       = $m->s;
        $pm_array = &$pm->array;
        $nsh      = BI_DB - nbits($pm_array[$pm->t-1]);	// normalize modulus
      
        if ($nsh > 0) {
            $pm->lShiftTo($nsh,$y);
            $pt->lShiftTo($nsh,$r);
        
        } else {
            $pm->copyTo($y);
            $pt->copyTo($r);
        }
        $ys = $y->t;
        
        $y_array = &$y->array;
        $y0      = $y_array[$ys-1];
        if ($y0 == 0) {
            return;
        }
        
        $yt = $y0*(1<<BI_F1)+(($ys>1)?$y_array[$ys-2]>>BI_F2:0);
        $d1 = BI_FV/$yt;
        $d2 = (1<<BI_F1)/$yt;
        $e  = 1<<BI_F2;
        $i  = $r->t;
        $j  = $i-$ys;
        $t  = (is_null($q))?nbi():$q;
        $y->dlShiftTo($j,$t);
        $r_array = &$r->array;
        
        if ($r->compareTo($t) >= 0) {
            $r_array[$r->t++] = 1;
            $r->subTo($t,$r);
        }
        $GLOBALS['BigIntegerOne']->dlShiftTo($ys,$t);
        
        
        $t->subTo($y,$y);	// "negative" y so we can replace sub with am later
        while($y->t < $ys) {
        	$y_array[$y->t++] = 0;
        }
        
        while(--$j >= 0) {
        
            // Estimate quotient digit
            $qd = ($r_array[--$i]==$y0)?BI_DM:floor($r_array[$i]*$d1+($r_array[$i-1]+$e)*$d2);
            if(($r_array[$i]+=$y->am(0,$qd,$r,$j,0,$ys)) < $qd) {	// Try it out
            
                $y->dlShiftTo($j,$t);
                $r->subTo($t,$r);
                while ($r_array[$i] < --$qd) {
                    $r->subTo($t,$r);
                }
                
            }
        }
        if(!is_null($q)) {
            $r->drShiftTo($ys,$q);
            if($ts != $ms){
                $GLOBALS['BigIntegerZero']->subTo($q,$q);
            }
        }
        $r->t = $ys;
        $r->clamp();
        if($nsh > 0) {
            $r->rShiftTo($nsh,$r);	// Denormalize remainder
        }
        if($ts < 0) {
            $GLOBALS['BigIntegerZero']->subTo($r,$r);
        } 
        
    }
    // (public) this mod a
    function mod($a)
    {
        $r = nbi();
        
        $this->abs()->divRemTo($a,null,$r);
        if ($this->s < 0 && $r->compareTo($GLOBALS['BigIntegerZero']) > 0) {
        
            $a->subTo($r,$r);
        }
        return $r;
    }




    // (protected) return "-1/this % 2^DB"; useful for Mont. reduction
    // justification:
    //         xy == 1 (mod m)
    //         xy =  1+km
    //   xy(2-xy) = (1+km)(1-km)
    // x[y(2-xy)] = 1-k^2m^2
    // x[y(2-xy)] == 1 (mod m^2)
    // if y is 1/x mod m, then y(2-xy) is 1/x mod m^2
    // should reduce x and y(2-xy) by m^2 at each step to keep size bounded.
    // JS multiply "overflows" differently from C/C++, so care is needed here.
    function invDigit() {
        $this_array = &$this->array;
        if ($this->t < 1) {
            return 0;
        }
        $x = $this_array[0];
        if (($x&1) == 0) {
            return 0;
        }
        $y = $x&3;		// y == 1/x mod 2^2
        $y = ($y*(2-($x&0xf)*$y))&0xf;	// y == 1/x mod 2^4
        $y = ($y*(2-($x&0xff)*$y))&0xff;	// y == 1/x mod 2^8
        $y = ($y*(2-((($x&0xffff)*$y)&0xffff)))&0xffff;	// y == 1/x mod 2^16
        // last step - calculate inverse mod DV directly;
        // assumes 16 < DB <= 32 and assumes ability to handle 48-bit ints
        $y = ($y*(2-$x*$y%BI_DV))%BI_DV;		// y == 1/x mod 2^dbits
        // we really want the negative inverse, and -DV < y < DV
        return ($y>0)?BI_DV-$y:-$y;
    }

    //(protected) true if this is even
    function isEven()
    {
        $this_array = &$this->array;
        return (($this->t>0)?($this_array[0]&1):$this->s) == 0;
    }

    // (protected) this^e, e < 2^32, doing sqr and mul with "r" (HAC 14.79)
    function exp($e,$z) {
    
        if ($e > 0xffffffff || $e < 1) {
        	return $GLOBALS['BigIntegerOne'];
        }
        $r  = nbi();
        $r2 = nbi();
        $g  = $z->convert($this);
        $i  = nbits($e)-1;
        $g->copyTo($r);
        while(--$i >= 0) {
            $z->sqrTo($r,$r2);
            if (($e&(1<<$i)) > 0) {
                $z->mulTo($r2,$g,$r);
            } else {
                $t  = $r;
                $r  = $r2;
                $r2 = $t;
            }
        }
        return $z->revert($r);
    }

    // (public) this^e % m, 0 <= e < 2^32
    function modPowInt($e,$m)
    {
        if($e < 256 || $m->isEven()) {
            $z = new Classic($m);
        } else {
            $z = new Montgomery($m);
        }
        return $this->exp($e,$z);
    }

    function bnpClone()
    {
        $r = nbi();
        $this->copyTo($r);
        return $r;
    }
    // (public) return value as integer
    function intValue()
    {
        $this_array = &$this->array;
        if ($this->s < 0) {
            if ($this->t == 1) {
                return $this_array[0]-BI_DV;
            } else if ($this->t == 0) {
                return -1;
            }
        } else if ($this->t == 1) {
            return $this_array[0];
        } else if ($this->t == 0) {
            return 0;
        }
        // assumes 16 < DB < 32
        return (($this_array[1]&((1<<(32-BI_DB))-1))<<BI_DB)|$this_array[0];
    }

    // (public) return value as byte
    function byteValue()
    {
        $this_array = &$this->array;
        return ($this->t==0)?$this->s:($this_array[0]<<24)>>24;
    }

    // (public) return value as short (assumes DB>=16)
    function shortValue()
    {
        $this_array = &$this->array;
        return ($this->t==0)?$this->s:($this_array[0]<<16)>>16;
    }

    // (protected) return x s.t. r^x < DV
    function chunkSize($r)
    {
        return floor(log(2)*BI_DB/log($r));
    }

    // (public) 0 if this == 0, 1 if this > 0
    function signum()
    {
        $this_array = &$this->array;
        if ($this->s < 0) {
            return -1;
        } else if ($this->t <= 0 || ($this->t == 1 && $this_array[0] <= 0)) {
            return 0;
        } else {
            return 1;
        }
    }

    // (protected) convert to radix string
    function toRadix($b)
    {
        if (is_null($b)) {
            $b = 10;
        }
        if ($this->signum() == 0 || $b < 2 || $b > 36) {
            return "0";
        }
        $cs = $this->chunkSize($b);
        $a  = pow($b,$cs);
        $d  = nbv($a);
        $y  = nbi();
        $z  = nbi();
        $r  = "";
        $this->divRemTo($d,$y,$z);
        while ($y->signum() > 0) {
            //$r = ($a+$z->intValue())->toString($b)->substr(1) + $r;
            $r = substr(base_convert(($a+$z->intValue()),10,$b),1) . $r;
            $y->divRemTo($d,$y,$z);
        }
        return base_convert($z->intValue(),10,$b) . $r;
    }

    // (protected) convert from radix string
    function fromRadix($s,$b) {
        $this->fromInt(0);
        if (is_null($b)) {
            $b = 10;
        }
        $cs = $this->chunkSize($b);
        $d  = pow($b,$cs);
        $mi = false;
        for($i = 0; $i < $s->length; ++$i) {
            $x = intAt($s,$i);
            if ($x < 0) {
                if ($s[$i] == "-" && $this->signum() == 0) {
                    $mi = true;
                }
                continue;
            }
            $w = $b*$w+$x;
            if (++$j >= $cs) {
                $this->dMultiply($d);
                $this->dAddOffset($w,0);
                $j = 0;
                $w = 0;
            }
        }
        if ($j > 0) {
            $this->dMultiply(pow($b,$j));
            $this->dAddOffset($w,0);
        }
        if ($mi) {
            $GLOBALS['BigIntegerZero'].subTo($this,$this);
        }
    }

    // (protected) alternate constructor
    function fromNumber($a,$b,$c) {
        if ("number" == gettype($b)) {
            // new BigInteger(int,int,RNG)
            if ($a < 2) {
                $this->fromInt(1);
            } else {
                $this->fromNumber($a,$c);
                if (!$this->testBit($a-1)) {	// force MSB set
                    $this->bitwiseTo($GLOBALS['BigIntegerOne']->shiftLeft($a-1),op_or,$this);
                }
                if ($this->isEven()) {
                    $this->dAddOffset(1,0); // force odd
                }
                while (!$this->isProbablePrime($b)) {
                    $this->dAddOffset(2,0);
                    if ($this->bitLength() > $a) {
                        $this->subTo($GLOBALS['BigIntegerOne']->shiftLeft($a-1),$this);
                    }
                }
            }
        } else {
            // new BigInteger(int,RNG)
            $x = array();
            $t = $a&7;
            //$x.length = ($a>>3)+1;
            setLength($x,(($a>>3)+1));
            $b->nextBytes($x);
            if ($t > 0) {
                $x[0] &= ((1<<$t)-1);
            } else {
                $x[0] = 0;
            }
            $this->fromString($x,256);
        }
    }
    // (public) convert to bigendian byte array
    function toByteArray()
    {
        $this_array = &$this->array;
        $i = $this->t;
        $r = array();
        $r[0] = $this->s;
        $p = BI_DB-($i*BI_DB)%8;
        $k = 0;
        $d = "";
        if ($i-- > 0) {
            if ($p < BI_DB && ($d = $this_array[$i]>>$p) != ($this->s&BI_DM)>>$p) {
            	$r[$k++] = $d|($this->s<<(BI_DB-$p));
            }
            while ($i >= 0) {
                if($p < 8) {
                    $d  = ($this_array[$i]&((1<<$p)-1))<<(8-$p);
                    $d |= $this_array[--$i]>>($p+=BI_DB-8);
                } else {
                    $d = ($this_array[$i]>>($p-=8))&0xff;
                    if($p <= 0) {
                        $p += BI_DB; 
                        --$i;
                    }
                }
                if (($d&0x80) != 0) {
                    $d |= -256;
                }
                if ($k == 0 && ($this->s&0x80) != ($d&0x80)) {
                    ++$k;
                }
                if ($k > 0 || $d != $this->s) {
                    $r[$k++] = $d;
                }
            }
        }
        return $r;
    }

    function equals($a)
    {
        return ($this->compareTo($a)==0);
    }
    function min($a)
    {
        return ($this->compareTo($a)<0)?$this:$a;
    }
    function max($a)
    {
        return ($this->compareTo($a)>0)?$this:$a;
    }
    // (protected) r = this op a (bitwise)
    function bitwiseTo($a,$op,$r) {
        $this_array = &$this->array;
        $a_array    = &$a->array;
        $r_array    = &$r->array;
        $m          = min($a->t,$this->t);
        for ($i = 0; $i < $m; ++$i) {
            $r_array[$i] = $op($this_array[$i],$a_array[$i]);
        }
        if ($a->t < $this->t) {
            $f = $a->s&BI_DM;
            for($i = $m; $i < $this->t; ++$i) {
                $r_array[$i] = $op($this_array[$i],$f);
            }
            $r->t = $this->t;
        } else {
            $f = $this->s&BI_DM;
            for($i = $m; $i < $a->t; ++$i) {
                $r_array[$i] = $op($f,$a_array[$i]);
            }
            $r->t = $a->t;
        }
        $r->s = $op($this->s,$a->s);
        $r->clamp();
    }

    // (public) this & a
    function op_and($x,$y)
    {
        return $x&$y;
    }
    function band($a)
    {
        $r = nbi();
        $this->bitwiseTo($a,op_and,$r);
        return r;
    }

    // (public) this | a
    function op_or($x,$y)
    {
        return $x|$y;
    }
    function bor($a)
    {
        $r = nbi();
        $this->bitwiseTo($a,op_or,$r);
        return r;
    }

    // (public) this ^ a
    function op_xor($x,$y)
    {
        return $x^$y;
    }
    function bxor($a)
    {
        $r = nbi();
        $this->bitwiseTo($a,op_xor,$r);
        return $r;
    }

    // (public) this & ~a
    function op_andnot($x,$y)
    {
        return $x&~$y;
    }
    function andNot($a)
    {
        $r = nbi();
        $this->bitwiseTo($a,op_andnot,$r);
        return r;
    }

    // (public) ~this
    function not()
    {
        $this_array = &$this->array;
        $r          = nbi();
        $r_array    = &$r->array;

        for ($i = 0; $i < $this->t; ++$i) {
            $r_array[$i] = BI_DM&~$this_array[$i];
        }
        $r->t = $this->t;
        $r->s = ~$this->s;
        return $r;
    }

    // (public) this << n
    function shiftLeft($n)
    {
        $r = nbi();
        if($n < 0) {
            $this->rShiftTo(-$n,$r);
        } else {
            $this->lShiftTo($n,$r);
        }
        return $r;
    }

    // (public) this >> n
    function shiftRight($n)
    {
        $r = nbi();
        if($n < 0) {
            $this->lShiftTo(-$n,$r);
        } else {
            $this->rShiftTo($n,$r);
        }
        return $r;
    }

    // (public) returns index of lowest 1-bit (or -1 if none)
    function getLowestSetBit()
    {
        $this_array = &$this->array;
        for($i = 0; $i < $this->t; ++$i)
        {
            if($this_array[$i] != 0) {
                return $i*BI_DB+lbit($this_array[$i]);
            }
        }
        if($this->s < 0) {
            return $this->t*BI_DB;
        }
        return -1;
    }

    // (public) return number of set bits
    function bitCount()
    {
        $r = 0;
        $x = $this->$s&BI_DM;
        for ($i = 0; $i < $this->t; ++$i) {
            $r += cbit($this_array[$i]^$x);
        }
        return $r;
    }

    // (public) true iff nth bit is set
    function testBit($n)
    {
        $this_array = &$this->array;
        $j = floor($n/BI_DB);
        if ($j >= $this->t) {
            return($this->s!=0);
        }
        return (($this_array[$j]&(1<<($n%BI_DB)))!=0);
    }

    // (protected) this op (1<<n)
    function changeBit($n,$op)
    {
        $r = $GLOBALS['BigIntegerOne']->shiftLeft($n);
        $this->bitwiseTo($r,$op,$r);
        return $r;
    }

    // (public) this | (1<<n)
    function setBit($n)
    {
        return $this->changeBit($n,op_or);
    }

    // (public) this & ~(1<<n)
    function clearBit($n)
    {
        return $this->changeBit($n,op_andnot);
    }

    // (public) this ^ (1<<n)
    function flipBit($n)
    {
        return $this->changeBit($n,$op_xor);
    }

    // (protected) r = this + a
    function addTo($a,$r)
    {
        $this_array = &$this->array;
        $a_array    = &$a->array;
        $r_array    = &$r->array;
        $i          = 0;
        $c          = 0;
        $m          = min($a->t,$this->t);
        while ($i < $m) {
            $c            += $this_array[$i]+$a_array[$i];
            $r_array[$i++] = $c&BI_DM;
            $c           >>= BI_DB;
        }
        if ($a->t < $this->t) {
            $c += $a->s;
            while ($i < $this->t) {
                $c            += $this_array[$i];
                $r_array[$i++] = $c&BI_DM;
                $c           >>= BI_DB;
            }
            $c += $this->s;
        } else {
            $c += $this->s;
            while($i < $a->t) {
                $c            += $a_array[$i];
                $r_array[$i++] = $c&BI_DM;
                $c           >>= BI_DB;
            }
            $c += $a->s;
        }
        $r->s = ($c<0)?-1:0;
        if($c > 0) {
            $r_array[$i++] = $c;
        } else if($c < -1) {
            $r_array[$i++] = BI_DV+$c;
        }
        $r->t = $i;
        $r->clamp();
    }

    // (public) this + a
    function add($a)
    {
        $r = nbi();
        $this->addTo($a,$r);
        return $r;
    }

    // (public) this - a
    function subtract($a)
    {
        $r = nbi();
        $this->subTo($a,$r);
        return $r;
    }

    // (public) this * a
    function multiply($a)
    {
        $r = nbi();
        $this->multiplyTo($a,$r);
        return $r;
    }

    // (public) this / a
    function divide($a)
    {
        $r = nbi();
        $this->divRemTo($a,$r,null);
        return $r;
    }

    // (public) this % a
    function remainder($a)
    {
        $r = nbi();
        $this->divRemTo($a,null,$r);
        return $r;
    }

    // (public) [this/a,this%a]
    function divideAndRemainder($a)
    {
        $q = nbi();
        $r = nbi();
        $this->divRemTo($a,$q,$r);
        return array($q,$r);
    }

    // (protected) this *= n, this >= 0, 1 < n < DV
    function dMultiply($n)
    {
        $this_array           = &$this->array;
        $this_array[$this->t] = $this->am(0,$n-1,$this,0,0,$this->t);
        ++$this->t;
        $this->clamp();
    }

    // (protected) this += n << w words, this >= 0
    function dAddOffset($n,$w)
    {
        $this_array = &$this->array;
        while ($this->t <= $w) {
            $this_array[$this->t++] = 0;
        }
        $this_array[$w] += $n;
        while ($this_array[$w] >= BI_DV) {
            $this_array[$w] -= BI_DV;
            if (++$w >= $this->t) {
                $this_array[$this->t++] = 0;
            }
            ++$this_array[$w];
        }
    }
    // (public) this^e
    function pow($e)
    {
        return $this->exp($e, new NullExp());
    }

    // (protected) r = lower n words of "this * a", a.t <= n
    // "this" should be the larger one if appropriate.
    function multiplyLowerTo($a,$n,$r)
    {
        $r_array = &$r->array;
        $a_array = &$a->array;
        $i       = min($this->t+$a->t,$n);
        $r->s    = 0; // assumes a,this >= 0
        $r->t    = $i;
        while ($i > 0) {
            $r_array[--$i] = 0;
        }
        for ($j = $r->t-$this->t; $i < $j; ++$i) {
            $r_array[$i+$this->t] = $this->am(0,$a_array[$i],$r,$i,0,$this->t);
        }
        for($j = min($a->t,$n); $i < $j; ++$i) {
            $this->am(0,$a_array[$i],$r,$i,0,$n-$i);
        }
        $r->clamp();
    }

    // (protected) r = "this * a" without lower n words, n > 0
    // "this" should be the larger one if appropriate.
    function multiplyUpperTo($a,$n,$r)
    {
        $r_array = &$r->array;
        $a_array = &$a->array;
        --$n;
        $i = $r->t = $this->t + $a->t - $n;
        $r->s    = 0; // assumes a,this >= 0
        while(--$i >= 0) {
            $r_array[$i] = 0;
        }
        for ($i = max($n-$this->t,0); $i < $a->t; ++$i)
        {
            $r_array[$this->t+$i-$n] = $this->am($n-$i,$a_array[$i],$r,0,0,$this->t+$i-$n);
        }
        $r->clamp();
        $r->drShiftTo(1,$r);
    }

    // (public) this^e % m (HAC 14.85)
    function modPow($e,$m)
    {
        $e_array = &$e->array;
        $i       = $e->bitLength();
        $r       = nbv(1);
        if($i <= 0) {
            return $r;
        } else if($i < 18) {
            $k = 1;
        } else if($i < 48) {
            $k = 3;
        } else if($i < 144) {
            $k = 4;
        } else if($i < 768) {
            $k = 5;
        } else {
            $k = 6;
        }
        if($i < 8) {
            $z = new Classic($m);
        } else if ($m->isEven()) {
            $z = new Barret($m);
        } else {
            $z = new Montgomery($m);
        }
        // precomputation
        $g  = array();
        $n  = 3;
        $k1 = $k-1;
        $km = (1<<$k)-1;
        $g[1] = $z->convert($this);
        if($k > 1) {
            $g2 = nbi();
            $z->sqrTo($g[1],$g2);
            while ($n <= $km) {
                $g[$n] = nbi();
                $z->mulTo($g2,$g[$n-2],$g[$n]);
                $n += 2;
            }
        }
        $j   = $e->t-1;
        $is1 = true;
        $r2  = nbi();
        $i   = nbits($e_array[$j])-1;
        
        while($j >= 0) {
            if($i >= $k1) {
                $w = ($e_array[$j]>>($i-$k1))&$km;
            } else {
                $w = ($e_array[$j]&((1<<($i+1))-1))<<($k1-$i);
                if($j > 0) {
                    $w |= $e_array[$j-1]>>(BI_DB+$i-$k1);
                }
            }

            $n = $k;
            while (($w&1) == 0) {
                $w >>= 1;
                --$n;
            }
            if (($i -= $n) < 0) {
                $i += BI_DB;
                --$j;
            }
            if ($is1) {	// ret == 1, don't bother squaring or multiplying it
                $g[$w]->copyTo($r);
                $is1 = false;
            } else {
                while ($n > 1) {
                    
                    $z->sqrTo($r,$r2);
                    $z->sqrTo($r2,$r);
                    $n -= 2;
                } if($n > 0) {
                    $z->sqrTo($r,$r2);
                } else {
                    $t  = $r;
                    $r  = $r2;
                    $r2 = $t;
                }
                $z->mulTo($r2,$g[$w],$r);
            }

            while($j >= 0 && ($e_array[$j]&(1<<$i)) == 0) {
                $z->sqrTo($r,$r2);
                $t  = $r;
                $r  = $r2;
                $r2 = $t;
                if(--$i < 0){
                    $i = BI_DB-1; --$j;
                }
            }
        }
        return $z->revert($r);
    }

    // (public) gcd(this,a) (HAC 14.54)
    function gcd($a)
    {
        $x = ($this->s<0)?$this->negate():$this->clone();
        $y = ($a->s<0)?$a->negate():$a->clone();
        if ($x->compareTo($y) < 0){
            $t = $x;
            $x = $y;
            $y = $t;
        }
        $i = $x->getLowestSetBit();
        $g = $y->getLowestSetBit();
        if ($g < 0) {
            return $x;
        }
        if ($i < $g) {
            $g = $i;
        }
        if($g > 0) {
            $x->rShiftTo($g,$x);
            $y->rShiftTo($g,$y);
        }
        while ($x->signum() > 0) {
            if (($i = $x->getLowestSetBit()) > 0) {
                $x->rShiftTo($i,$x);
            }
            if (($i = $y->getLowestSetBit()) > 0) {
                $y->rShiftTo($i,$y);
            }
            if($x->compareTo($y) >= 0) {
                $x->subTo($y,$x);
                $x->rShiftTo(1,$x);
            } else {
                $y->subTo($x,$y);
                $y->rShiftTo(1,$y);
            }
        }
        if($g > 0) {
            $y->lShiftTo($g,$y);
        }
        return $y;
    }

    // (protected) this % n, n < 2^26
    function modInt($n)
    {
        $this_array = &$this->array;
        if($n <= 0) {
            return 0;
        }
        $d = BI_DV%$n;
        $r = ($this->s<0)?$n-1:0;
        if ($this->t > 0) {
            if($d == 0) {
                $r = $this_array[0]%$n;
            } else {
                for($i = $this->t-1; $i >= 0; --$i) {
                    $r = ($d*$r+$this_array[$i])%$n;
                }
            }
        }


        return $r;
    }

    // (public) 1/this % m (HAC 14.61)
    function ModInverse($m) {
        $ac = $m->isEven();
        if (($this->isEven() && $ac) || $m->signum() == 0) {
            return $GLOBALS['BigIntegerZero'];
        }
        $u = $m->clone();
        $v = $this->clone();
        $a = nbv(1);
        $b = nbv(0);
        $c = nbv(0);
        $d = nbv(1);
        while($u->signum() != 0) {
            while($u->isEven()) {
                $u->rShiftTo(1,$u);
                if($ac) {
                    if(!$a->isEven() || !$b->isEven()) {
                        $a->addTo($this,$a);
                        $b->subTo($m,$b);
                    }
                    $a->rShiftTo(1,$a);
                } else if(!$b->isEven()) {
                    $b->subTo($m,$b);
                }
                $b->rShiftTo(1,$b);
            }
            while ($v->isEven()) {
                $v->rShiftTo(1,$v);
                if($ac) {
                    if (!$c->isEven() || !$d->isEven()) {
                        $c->addTo($this,$c);
                        $d->subTo($m,$d);
                    }
                    $c->rShiftTo(1,$c);
                } else if(!$d->isEven()) {
                    $d->subTo($m,$d);
                }
                $d->rShiftTo(1,$d);
            }
            if ($u->compareTo($v) >= 0) {
                $u->subTo($v,$u);
                if($ac) {
                    $a->subTo($c,$a);
                }
                $b->subTo($d,$b);
            } else {
                $v->subTo($u,$v);
                if($ac) {
                    $c->subTo($a,$c);
                }
                $d->subTo($b,$d);
            }
        }
        if ($v->compareTo($GLOBALS['BigIntegerOne']) != 0) {
            return $GLOBALS['BigIntegerZero'];
        }
        if ($d->compareTo($m) >= 0) {
            return $d->subtract($m);
        }
        if ($d->signum() < 0) {
            $d->addTo($m,$d);
        } else {
            return $d;
        }
        if ($d->signum() < 0) {
            return $d->add($m);
        } else {
            return $d;
        }
    }

    // (public) test primality with certainty >= 1-.5^t
    function IsProbablePrime($t) {
        $x       = $this->abs();
        $x_array = &$x->array;
        if($x->t == 1 && $x_array[0] <= $this->lowprimes[count($this->lowprimes)-1]) {
            for ($i = 0; $i < count($this->lowprimes); ++$i) {
                if ($x_array[0] == $this->lowprimes[$i]) {
                    return true;
                }
            }
            return false;
        }
        if($x->isEven()) {
            return false;
        }
        $i = 1;
        while ($i < count($this->lowprimes)) {
            $m = $this->lowprimes[$i];
            $j = $i+1;
            while ($j < count($this->lowprimes) && $m < $this->lplim) {
                $m *= $this->lowprimes[$j++];
            }
            $m = $x->modInt($m);
            while ($i < $j) {
                if($m%$this->lowprimes[$i++] == 0) {
                    return false;
                }
            }
        }
        return $x->millerRabin($t);
    }

    // (protected) true if probably prime (HAC 4.24, Miller-Rabin)
    function MillerRabin($t)
    {
        $n1 = $this->subtract($GLOBALS['BigIntegerOne']);
        $k  = $n1->getLowestSetBit();
        if ($k <= 0) {
            return false;
        }
        $r = $n1->shiftRight($k);
        $t = ($t+1)>>1;
        if($t > count($this->lowprimes)) {
            $t = count($this->lowprimes);
        }
        $a = nbi();
        for($i = 0; $i < $t; ++$i) {
            $a->fromInt($this->lowprimes[$i]);
            $y = $a->modPow($r,$this);
            if($y->compareTo($GLOBALS['BigIntegerOne']) != 0 && $y->compareTo($n1) != 0) {
                $j = 1;
                while($j++ < $k && $y->compareTo($n1) != 0) {
                    $y = $y->modPowInt(2,$this);
                    if($y->compareTo($GLOBALS['BigIntegerOne']) == 0) {
                        return false;
                    }
                }
                if($y->compareTo($n1) != 0) {
                    return false;
                }
            }
        }
        return true;
    }


}

class Arcfour
{
    var $i;
    var $j;
    var $S = array();
    // Initialize arcfour context from key, an array of ints, each from [0..255]
    function init($key) {
        for ($i = 0; $i < 256; ++$i) {
            $this->S[$i] = $i;
        }
        $j = 0;
        for ($i = 0; $i < 256; ++$i) {
            $j           = ($j + $this->S[$i] + $key[$i % count($key)]) & 255;
            $t           = $this->S[$i];
            $this->S[$i] = $this->S[$j];
            $this->S[$j] = $t;
        }
        $this->i = 0;
        $this->j = 0;
    }
    function next() {
        $this->i           = ($this->i + 1) & 255;
        $this->j           = ($this->j + $this->S[$this->i]) & 255;
        $t                 = $this->S[$this->i];
        $this->S[$this->i] = $this->S[$this->j];
        $this->S[$this->j] = $t;
        return $this->S[($t + $this->S[$this->i]) & 255];
    }

}


class Classic
{
    var $m;
    // Modular reduction using "classic" algorithm
    function Classic($m)
    {
        $this->m = $m;
    }
    function convert($x)
    {
        if ($x->s < 0 || $x->compareTo($this->m) >= 0) {
            return $x->mod($this->m);
        } else {
            return $x;
        }
    }
    function revert($x)
    {
        return $x;
    }
    function reduce($x)
    {
        $x->divRemTo($this->m,null,$x);
    }
    function mulTo($x,$y,$r)
    {
        $x->multiplyTo($y,$r);
        $this->reduce($r);
    }
    function sqrTo($x,$r)
    {
        $x->squareTo($r);
        $this->reduce($r);
    }
}
class Montgomery
{
    var $m;
    var $mp;
    var $mp1;
    var $mph;
    var $um;
    var $mt2;
    // Montgomery reduction
    function Montgomery($m)
    {
        $this->m   = $m;
        $this->mp  = $m->invDigit();
        $this->mpl = $this->mp&0x7fff;
        $this->mph = $this->mp>>15;
        $this->um  = (1<<(BI_DB-15))-1;
        $this->mt2 = 2*$m->t;
    }

    // xR mod m
    function convert($x)
    {
        $r = nbi();
        $x->abs()->dlShiftTo($this->m->t,$r);
      
        $r->divRemTo($this->m,null,$r);
        if($x->s < 0 && $r->compareTo($GLOBALS['BigIntegerZero']) > 0) {
            $this->m->subTo($r,$r);
        }
        return $r;
    }

    // x/R mod m
    function revert($x)
    {
        $r = nbi();
        $x->copyTo($r);
        
        $this->reduce($r);
        return $r;
    }

    // x = x/R mod m (HAC 14.32)
    function reduce($x)
    {
        $x_array = &$x->array;
        while ($x->t <= $this->mt2)	{
            // pad x so am has enough room later
            $x_array[$x->t++] = 0;
        }
        for ($i = 0; $i < $this->m->t; ++$i) {
            // faster way of calculating u0 = x[i]*mp mod DV
            $j  = $x_array[$i]&0x7fff;
            $u0 = ($j*$this->mpl+((($j*$this->mph+($x_array[$i]>>15)*$this->mpl)&$this->um)<<15))&BI_DM;
            // use am to combine the multiply-shift-add into one call
            $j            = $i+$this->m->t;
            $x_array[$j] += $this->m->am(0,$u0,$x,$i,0,$this->m->t);
            // propagate carry
            while ($x_array[$j] >= BI_DV) {
                $x_array[$j] -= BI_DV;
                $x_array[++$j]++;
            }
        }
        $x->clamp();
        $x->drShiftTo($this->m->t,$x);
        if($x->compareTo($this->m) >= 0) {
            $x->subTo($this->m,$x);
        }
    }

    // r = "x^2/R mod m"; x != r
    function sqrTo($x,$r) {
        $x->squareTo($r);
        $this->reduce($r);
    }

    // r = "xy/R mod m"; x,y != r
    function mulTo($x,$y,$r)
    {
        $x->multiplyTo($y,$r);
        $this->reduce($r);
    }

}
class NullExp extends BigInteger
{
    function revert($x)
    {
        return $x;
    }
    function convert($x)
    {
        return $x;
    }
    function mulTo($x,$y,$r)
    {
        $x->multiplyTo($y,$r);
    }
    function sqrTo($x,$r)
    {
        $x->squareTo($r);
    }
}
// Barrett modular reduction
class Barrett
{
    var $q3;
    var $r2;
    var $m;
    var $mu;
    function Barrett($m)
    {
        // setup Barrett
        $this->r2 = nbi();
        $this->q3 = nbi();
        $GLOBALS['BigIntegerOne']->dlShiftTo(2*$m->t,$this->r2);
        $this->mu = $this->r2->divide($m);
        $this->m  = $m;
    }
    function convert($x)
    {
        if($x->s < 0 || $x->t > 2*$this->m->t) {
            return $x->mod($this->m);
        } else if($x->compareTo($this->m) < 0) {
            return x;
        } else {
            $r = nbi();
            $x->copyTo($r);
            $this->reduce($r);
            return $r;
        }
    }

    function revert($x)
    {
        return $x;
    }

    // x = x mod m (HAC 14.42)
    function reduce($x) {
        $x->drShiftTo($this->m->t-1,$this->r2);
        if($x->t > $this->m->t+1)
        {
            $x->t = $this->m->t+1;
            $x->clamp();
        }
        $this->mu->multiplyUpperTo($this->r2,$this->m->t+1,$this->q3);
        $this->m->multiplyLowerTo($this->q3,$this->m->t+1,$this->r2);
        while ($x->compareTo($this->r2) < 0) {
            $x->dAddOffset(1,$this->m->t+1);
        }
        $x->subTo($this->r2,$x);
        while ($x->compareTo($this->m) >= 0) {
            $x->subTo($this->m,$x);
        }
    }

    // r = x^2 mod m; x != r
    function sqrTo($x,$r)
    {
        $x->squareTo($r);
        $this->reduce($r);
    }

    // r = x*y mod m; x,y != r
    function mulTo($x,$y,$r)
    {
        $x->multiplyTo($y,$r);
        $this->reduce($r);
    }

}

// Plug in your RNG constructor here
function prng_newstate() {
    return new Arcfour();
}



class rng
{
    var $state;
    var $pool;
    var $pptr;
    var $psize = 256;
    function init()
    {
        if(is_null($this->pool)) {
            $this->pool = array();
            $this->pptr = 0;
            while($this->pptr < $this->psize) {  // extract some randomness from Math.random()
                $t = floor(rand(0,65536));
                $this->pool[$this->pptr++] = urs($t,8);
                $this->pool[$this->pptr++] = $t & 255;
                
            }
            $this->pptr = 0;
            $this->seed_time();
        }
    }
    function seed_int($x)
    {
        $this->pool[$this->pptr++] ^= $x & 255;
        $this->pool[$this->pptr++] ^= ($x >> 8) & 255;
        $this->pool[$this->pptr++] ^= ($x >> 16) & 255;
        $this->pool[$this->pptr++] ^= ($x >> 24) & 255;
        if ($this->pptr >= $this->psize) {
            $this->pptr -= $this->psize;
        }
    }
    function seed_time()
    {
        $this->seed_int(1122926989487);
    }

    // Initialize the pool with junk if needed.
    function get_byte() {
        
        if(is_null($this->state)) {
            
            $this->seed_time();
            $this->state = prng_newstate();
            $this->state->init($this->pool);
           
            for ($this->pptr = 0; $this->pptr < count($this->pool); ++$this->pptr)
            {
                $this->pool[$this->pptr] = 0;
            } 
            $this->pptr = 0;
            //rng_pool = null;
        }
        // TODO: allow reseeding after first request
        return $this->state->next();
    }


}
class SecureRandom
{
    var $rng;
    function SecureRandom($rng)
    {
        $this->rng = $rng;
    }
    function nextBytes(&$ba) {
        for($i = 0; $i < count($ba); ++$i) {
            $ba[$i] = $this->rng->get_byte();
        }
    }
}

function linebrk($s,$n) {
    $ret = "";
    $i = 0;
    while ($i + $n < count($s)) {
        $ret .= substr($s,$i,$i+$n) . "\n";
        $i += $n;
    }
    return $ret . substr($s,$i,count($s));
}
function byte2Hex($b) {
    if($b < 0x10) {
        return "0" . base_convert($b,2,16);
    }
    else
    {
        return base_convert($b,2,16);
    }
}

// PKCS#1 (type 2, random) pad input string s to n bytes, and return a bigint
function pkcs1pad2($s,$n) {
    if($n < strlen($s) + 11) {
        echo ("Message too long for RSA");
        return null;
    }
    $ba = array();
    $i = strlen($s) - 1;
    
    while($i >= 0 && $n > 0) {
        $ba[--$n] = ord($s[$i--]);
    }
    $ba[--$n] = 0;
    $rng = new SecureRandom($GLOBALS['rngc']);
    $x = array();
    while ($n > 2) { // random non-zero pad
        $x[0] = 0;
        while ($x[0] == 0) {
            $rng->nextBytes($x);
        }
        $ba[--$n] = $x[0];
    }
    $ba[--$n] = 2;
    $ba[--$n] = 0;
    return new BigInteger($ba);
}
// Undo PKCS#1 (type 2, random) padding and, if valid, return the plaintext
function pkcs1unpad2($d,$n) {
    $b = $d->toByteArray();
    $i = 0;
    while ($i < count($b) && $b[$i] == 0) {
        ++$i;
    }
    
    if (count($b)-$i != $n-1 || $b[$i] != 2) {
        return null;
    }
    ++$i;
    while ($b[$i] != 0) {
        if (++$i >= count($b)) {
            return null;
        }
    }
    $ret = "";
    while (++$i < count($b)) {
        $ret .= chr($b[$i]);
    }
    return $ret;
}
class RSAKey
{
    var $n     = null;
    var $e     = 0;
    var $d     = null;
    var $p     = null;
    var $q     = null;
    var $dmp1  = null;
    var $dmq1  = null;
    var $coeff = null;
    // Set the public key fields N and e from hex strings
    function setPublic($N,$E) {
        if (!is_null($N) && !is_null($E) && count($N) > 0 && count($E) > 0) {
            $this->n = parseBigInt($N,16);
            $this->e = intval($E,16);
        } else {
            echo ("Invalid RSA public key");
        }
    }

    // Perform raw public operation on "x": return x^e (mod n)
    function doPublic($x) {
        return $x->modPowInt($this->e, $this->n);
    }

    // Return the PKCS#1 RSA encryption of "text" as an even-length hex string
    function encrypt($text) {
        $m = pkcs1pad2($text,($this->n->bitLength()+7)>>3);
        if (is_null($m)) {
            return null;
        }
        $c = $this->doPublic($m);
        if (is_null($c)) {
            return null;
        }
        
    
        $h = $c->toString(16);
        
        if ((strlen($h) & 1) == 0) {
            return $h;
        } else {
            return "0" . $h;
        }
    }

    // Set the private key fields N, e, and d from hex strings
    function setPrivate($N,$E,$D) {
        if(!is_null($N) && is_null($E) && count($N) > 0 && count($E) > 0) {
            $this->n = parseBigInt($N,16);
            $this->e = intval($E,16);
            $this->d = parseBigInt($D,16);
        } else {
            echo ("Invalid RSA private key");
        }
    }

    // Set the private key fields N, e, d and CRT params from hex strings
    function setPrivateEx($N,$E,$D,$P,$Q,$DP,$DQ,$C) {
        if(!is_null($N) && !is_null($E) && count($N) > 0 && count($E) > 0) {
            $this->n = parseBigInt($N,16);
            $this->e = intval($E,16);
            $this->d = parseBigInt($D,16);
            $this->p = parseBigInt($P,16);
            $this->q = parseBigInt($Q,16);
            $this->dmp1 = parseBigInt($DP,16);
            $this->dmq1 = parseBigInt($DQ,16);
            $this->coeff = parseBigInt($C,16);
        } else {
            alert("Invalid RSA private key");
        }
    }
    // Generate a new random private key B bits long, using public expt E
    function generate($B,$E) {
        $rng     = new SecureRandom($GLOBALS['rngc']);
        $qs      = $B>>1;
        $this->e = intval($E,16);
        $ee      = new BigInteger($E,16);
        for(;;) {
            for(;;) {
                $this->p = new BigInteger($B-$qs,1,$rng);
                if($this->p->subtract($GLOBALS['BigIntegerOne'])->gcd($ee)->compareTo($GLOBALS['BigIntegerOne']) == 0 && $this->p->isProbablePrime(10)) break;
            }
            for(;;) {
                $this->q = new BigInteger($qs,1,$rng);
                if($this->q->subtract($GLOBALS['BigIntegerOne'])->gcd($ee)->compareTo($GLOBALS['BigIntegerOne']) == 0 && $this->q->isProbablePrime(10)) break;
            }
            if($this->p->compareTo($this->q) <= 0) {
                $t = $this->p;
                $this->p = $this->q;
                $this->q = $t;
            }
            $p1 = $this->p->subtract($GLOBALS['BigIntegerOne']);
            $q1 = $this->q->subtract($GLOBALS['BigIntegerOne']);
            $phi = $p1->multiply($q1);
            if ($phi->gcd($ee)->compareTo($GLOBALS['BigIntegerOne']) == 0) {
                $this->n = $this->p->multiply($this->q);
                $this->d = $ee->modInverse($phi);
                $this->dmp1 = $this->d->mod($p1);
                $this->dmq1 = $this->d->mod($q1);
                $this->coeff = $this->q->modInverse($this->p);
                break;
            }
        }
    }

    // Perform raw private operation on "x": return x^d (mod n)
    function doPrivate($x) {
        if(is_null($this->p) || is_null($this->q)) {
            return $x->modPow($this->d, $this->n);
        }

        // TODO: re-calculate any missing CRT params
        $xp = $x->mod($this->p)->modPow($this->dmp1, $this->p);
        $xq = $x->mod($this->q)->modPow($this->dmq1, $this->q);
        
        while ($xp->compareTo($xq) < 0) {
            $xp = $xp->add($this->p);
        }
        
        return $xp->subtract($xq)->multiply($this->coeff)->mod($this->p)->multiply($this->q)->add($xq);
    }
    // Return the PKCS#1 RSA decryption of "ctext".
    // "ctext" is an even-length hex string and the output is a plain string.
    function decrypt($ctext) {
        $c = parseBigInt($ctext, 16);
        $m = $this->doPrivate($c);
        if(is_null($m)) {
            return null;
        }
        return pkcs1unpad2($m, ($this->n->bitLength()+7)>>3);
    }

}

$nValue     ="a5261939975948bb7a58dffe5ff54e65f0498f9175f5a09288810b8975871e99af3b5dd94057b0fc07535f5f97444504fa35169d461d0d30cf0192e307727c065168c788771c561a9400fb49175e9e6aa4e23fe11af69e9412dd23b0cb6684c4c2429bce139e848ab26d0829073351f4acd36074eafd036a5eb83359d2a698d3";
$eValue     ="10001";
$dValue     ="8e9912f6d3645894e8d38cb58c0db81ff516cf4c7e5a14c7f1eddb1459d2cded4d8d293fc97aee6aefb861859c8b6a3d1dfe710463e1f9ddc72048c09751971c4a580aa51eb523357a3cc48d31cfad1d4a165066ed92d4748fb6571211da5cb14bc11b6e2df7c1a559e6d5ac1cd5c94703a22891464fba23d0d965086277a161";
$pValue     ="d090ce58a92c75233a6486cb0a9209bf3583b64f540c76f5294bb97d285eed33aec220bde14b2417951178ac152ceab6da7090905b478195498b352048f15e7d";
$qValue     ="cab575dc652bb66df15a0359609d51d1db184750c00c6698b90ef3465c99655103edbf0d54c56aec0ce3c4d22592338092a126a0cc49f65a4a30d222b411e58f";
$dmp1Value  ="1a24bca8e273df2f0e47c199bbf678604e7df7215480c77c8db39f49b000ce2cf7500038acfff5433b7d582a01f1826e6f4d42e1c57f5e1fef7b12aabc59fd25";
$dmq1Value  ="3d06982efbbe47339e1f6d36b1216b8a741d410b0c662f54f7118b27b9a4ec9d914337eb39841d8666f3034408cf94f5b62f11c402fc994fe15a05493150d9fd";
$coeffValue ="3a3e731acd8960b7ff9eb81a7ff93bd1cfa74cbd56987db58b4594fb09c09084db1734c8143f98b602b981aaa9243ca28deb69b5b280ee8dcee0fd2625e53250";
$TEXT       = "Brothers what we do in life echoes in eternity";
$encrypted  = "";
function encrypt() {
    global $nValue, $eValue, $dValue, $pValue, $qValue, $dmp1Value, $dmq1Value, $coeffValue,$TEXT,$encrypted;
    $RSA = new RSAKey();
    $RSA->setPublic($nValue,$eValue);
    $RSA->setPrivateEx($nValue, $eValue, $dValue, $pValue, $qValue, $dmp1Value, $dmq1Value, $coeffValue);
    $encrypted = $RSA->encrypt($TEXT);
}
function decrypt() {
    global $nValue, $eValue, $dValue, $pValue, $qValue, $dmp1Value, $dmq1Value, $coeffValue,$TEXT,$encrypted;
    $RSA = new RSAKey();
    $RSA->setPublic($nValue, $eValue);
    $RSA->setPrivateEx($nValue, $eValue, $dValue, $pValue, $qValue, $dmp1Value, $dmq1Value, $coeffValue);
    $decrypted = $RSA->decrypt($encrypted);
    
    if ($decrypted != $TEXT) {
        echo ("Crypto operation failed");
    }
}

for($i = 0; $i < 7; $i++) {
	encrypt();
	decrypt();
}



?>