<?


class smallobject {

    var $avar = 'hello';

    function smallobject() {
        echo "some hairy constructor\n";
    }
    
    function afunc() {
        echo $avar;
    }
    
}

class largeobject {

    var $var1 = 'some string';
    var $var2 = 'some string';
    var $var3 = 'some string';
    var $var4 = 'some string';
    var $var5 = 'some string';
    var $var6 = 'some string';
    var $var7 = 'some string';
    var $var8 = 'some string';
    var $var9 = 'some string';
    var $var10 = 'some string';
    var $var11 = 'some string';
    var $var12 = 'some string';
    var $var13 = 'some string';
    var $var14 = 'some string';
    var $var15 = 'some string';
    var $var16 = 'some string';
    var $var17 = 'some string';
    var $var18 = 'some string';
    var $var19 = 'some string';
    var $var20 = 'some string';
    var $var21 = 'some string';
    var $var22 = 'some string';
    var $var23 = 'some string';
    var $var24 = 'some string';
    var $var25 = 'some string';
    var $var26 = 'some string';
    var $var27 = 'some string';
    var $var28 = 'some string';
    var $var29 = 'some string';
    var $var30 = 'some string';
    var $var31 = 'some string';
    var $var32 = 'some string';
    var $var33 = 'some string';
    var $var34 = 'some string';
    var $var35 = 'some string';
    var $var36 = 'some string';
    var $var37 = 'some string';
    var $var38 = 'some string';
    var $var39 = 'some string';
    var $var40 = 'some string';

    function largeobject() {
        echo "some hairy constructor\n";
    }
    
    function afunc11($a) {        
        echo "a function\n";
    }

    function afunc12($a) {        
                echo "a function\n";
    }

    function afunc13($a) {        
                echo "a function\n";
    }

    function afunc14($a) {        
                echo "a function\n";
    }

    function afunc15($a) {        
                echo "a function\n";
    }

    function afunc16($a) {        
                echo "a function\n";
    }

    function afunc17($a) {        
                echo "a function\n";
    }

    function afunc18($a) {        
                echo "a function\n";
    }

    function afunc19($a) {        
                echo "a function\n";
    }

    function afunc20($a) {        
                echo "a function\n";
    }

    function afunc21($a) {        
                echo "a function\n";
    }
    
}

$numObjs=50000;

// creation of objects
for ($i=0; $i<$numObjs; $i++) {
    $large[$i] =& new largeobject();
    $large[$i]->small[$i] =& new smallobject(); 
}
     
// calling methods
for ($i=0; $i<$numObjs; $i++) {

        $large[$i]->afunc11('hi');
        $large[$i]->afunc12('hi');
        $large[$i]->afunc13('hi');
        $large[$i]->afunc14('hi');
        $large[$i]->afunc15('hi');
        $large[$i]->afunc16('hi');
        $large[$i]->afunc17('hi');
        $large[$i]->afunc18('hi');
        $large[$i]->afunc19('hi');
        $large[$i]->afunc20('hi');
        $large[$i]->afunc21('hi');
}

// property access
for ($i=0; $i<$numObjs; $i++) {
    for ($t=0; $t<=40; $t++) {
        $somevar = 'var'.$t;
        $a = $large[$i]->$somevar;
        $b = $large[$i]->small[$i]->avar;
    }
}

?>