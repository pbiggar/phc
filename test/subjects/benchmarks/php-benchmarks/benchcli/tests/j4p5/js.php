<?php
/* 
  J4P5: EcmaScript interpreter for php
  ¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯
  (also known as JavaScript over PHP5)
  
  This is a true EcmaScript/JavaScript interpreter, as defined by Ecma-262 3d edition.
  You get:
  - functions, objects, closures, exceptions, regular expressions, that kind of stuff.
  You don't get:
  - a browser DOM. However, you can plug whatever objects you want for your scripts to use.
  
  Speed?
  - parsing is faster than it used to be, but still sluggish.
  - execution is done by running generated php code. It is strongly recommended to use a PHP 
    opcode cache when available.
    
  Safety?
  - Yes. That was the idea. scripts are sand-boxed and won't have access to anything 
    you don't expose them to explicitely.
    
  Fully compliant Ecma-262 3d edition?
  - No. We're missing unicode support, magic semi-colons, and regexp literals.
    You might bump into other minor quirks that may get fixed eventually.
    
  Any Weird Extensions?
  - Yes. We support <? | <?= | <?js ... ?>.
*/
//error_reporting(4095);

define("JS_CACHE_DIR", (getenv("TMP")?getenv("TMP"):"/tmp")."/es4php");
define("JS_DEBUG", 1);
function enum() {
  static $index = 1;
  foreach (func_get_args() as $c) {
    define ($c, JS_DEBUG?$index++:$c);
  }
}
enum("JS_INLINE", "JS_DIRECT");

class js {

  #-- auto-magic function that should work out of the box without being too inefficient.
  static function run($src, $mode=JS_DIRECT, $id=NULL) {
    

    #-- attempt to setup our cache directory
    if (!file_exists(JS_CACHE_DIR)) {
      mkdir(JS_CACHE_DIR, 0777, true);
    }
    #-- we need a unique ID for this script. passing $id makes this faster, but whatever.
    if ($id==NULL) $id = md5($src);
    $path = JS_CACHE_DIR."/".$id.".php";
    /**
     * Modification to always compile the script.
     */  
    if (true) {
      #-- ok. we need to compile the darn thing.
      require_once(dirname(__FILE__)."/jsc.php");

      if ($mode==JS_INLINE) $src = "?>".$src;
      $t1 = microtime(1);
      $php = jsc::compile($src);
      $t2 = microtime(2);
      //echo "Compilation done in ".($t2-$t1). " seconds<hr>";
      file_put_contents($path, "<?php\n".$php."\n?>");
      #-- then we run it.
    }
    #echo highlight_linenum($path);
    include $path;
  }
  
  #-- normally called by generated code. Your code doesn't need to call it.
  static function init() {
    require_once(dirname(__FILE__)."/jsrt.php");
    jsrt::start_once();
  }

  #-- easy-to-use crud to define functions, variables and all that good stuff  
  /**
   * sample use:
   *
   *  define("external", 
   *         array("include"=>"my_js_include", "require"=>"my_js_require"),
   *         array("PI"=>3.1415926535, "ZERO"=>0) );
   *
   * A few notes:
   *  - this function create a new Object() and assign it as $objname on the global object.
   *  - every function and variable is placed as a direct property of $objname
   *  - those functions will have a length of 0. I'd be surprised if someone cares.
   *  - those functions won't have a prototype. Again, not likely to matter much.
   *  - variables cannot contain arrays or objects. use the real jsrt:: API for that stuff.
   *
   */
  static function define($objname, $funcarray, $vararray=null) {
    #-- start by covering our basics
    js::init();
    #-- define the main object
    $obj = new js_object();
    jsrt::define_variable($objname, $obj);
    #-- start linking our functions
    jsrt::push_context($obj);
    foreach ($funcarray as $js=>$php) {
      jsrt::define_function($php, $js);
    }
    jsrt::pop_context();
    #-- put variables in place
    foreach ((array)$vararray as $js=>$php) {
      #-- odd, but php.net discourages the use of gettype, so watch me comply.
      switch(true) {
        case is_bool($php):    $v = new js_val(js_val::BOOLEAN, $php); break;
        case is_string($php):  $v = js_str($php); break;
        case is_numeric($php): $v = js_int($php); break;
        case is_null($php):    $v = jsrt::$null;  break;
        case is_array($php):  /* we could do something smarter here. maybe later. */
        default:               $v = jsrt::$undefined; break;
      }
      $obj->put($js, $v);
    }
  }
}

/**
 * Debug function. ignore and stuff.
 */
function highlight_linenum($path)
{
    // Init
    $data = explode ('<br />', highlight_file($path,1));
    $start = '<span style="color: black;">';
    $end   = '</span>';
    $i = 1;
    $text = '';
 
    // Loop
    foreach ($data as $line) {
        $text .= $start . $i . ' ' . $end .
            str_replace("\n", '', $line) . "\n";
        ++$i;
    }
 
    return "<pre style='border:1px dotted #aaa;'>".$text."</pre>";
}