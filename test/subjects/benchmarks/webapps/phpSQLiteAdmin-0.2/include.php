<?php

session_start();

require_once('config.php');
require_once('SPSQLite.class.php');


if($_SESSION['phpSQLiteAdmin_currentdb'] == '') {
	$_SESSION['phpSQLiteAdmin_currentdb'] = 'phpsla.sqlite';
} elseif(isset($_POST['sessionname'])) {
	$_SESSION['phpSQLiteAdmin_currentdb'] = $_POST['sessionvalue'];
}


function check_db() {
	global $current_db;
	//clearstatcache(); // should not be necessary
	if (!is_writable($current_db)) {
		//print "db is ro";
		return false;
	} else {
		return true;
	}
}


// connect to the system database
if (!is_writable('phpsla.sqlite')) die("<br>System database 'phpsla.sqlite' is not writeable by webserver account.");
$sysdbh =& new SPSQLite('phpsla.sqlite');
$current_db = $_SESSION['phpSQLiteAdmin_currentdb'];
$current_user = 1;


if (check_db()) {
	$userdbh =& new SPSQLite($current_db);
	// I know this is ugly... time should cure it
	$userdbh2 =& new SPSQLite($current_db);
	$sqliteversion = $userdbh->libVersion();
}


function i18n($defaultstring,$stringid) {
	include('i18n_langs.php');
	global $langid;
	$string = ${'t'.$stringid}[$langid];

	if ( (isset($langid)) && (isset($string)) ) {
		return $string;
	} else {
		return $defaultstring;
	}
}


function print_top_links($current_table) {
global $sqliteversion;
echo<<<EOT
<div id="currentdb">Database: {$_SESSION['phpSQLiteAdmin_currentdb']}</div>
<p class="sqliteversion">SQLite version: $sqliteversion</p>
<br>
<a href="mainframe.php" target="mainframe">Back</a> |
<a href="table_structure.php?object=$current_table" target="mainframe">Structure</a> |
<a href="table_browse.php?object=$current_table" target="mainframe">Browse</a> |
<a href="query.php?object=$current_table" target="mainframe">Query</a> |
<!--<a href="export.php?object=$current_table" target="mainframe">Export</a> |-->
<a href="dbaction.php?action=empty_table&object=$current_table" target="_top" onclick="return confirm_empty_table();">Empty</a> |
<a href="dbaction.php?action=drop_table&object=$current_table" target="_top" onclick="return confirm_drop_table();">Drop</a>
EOT;
}


function print_table_action_links($current_table) {
echo<<<EOT
<a href="table_structure.php?object=$current_table" target="mainframe">Structure</a> |
<a href="table_browse.php?object=$current_table" target="mainframe">Browse</a> |
<a href="query.php?object=$current_table" target="mainframe">Query</a> |
<a href="dbaction.php?action=empty_table&object=$current_table" target="_top" onclick="return confirm_empty_table();">Empty</a> |
<a href="dbaction.php?action=drop_table&object=$current_table" target="_top" onclick="return confirm_drop_table();">Drop</a>

EOT;
}


function print_index_action_links($current_index) {
echo<<<EOT
<a href="dbaction.php?action=drop_index&object=$current_index" target="_top" onclick="return confirm_drop_index();">Drop</a>
EOT;
}


function print_db_selector($current_db) {
	global $db_dir,$database,$sysdbh;
	print "<form name=choosedb action=\"set_session.php\" method=post target=\"_top\">\n";
	print "<input type=hidden name=sessionname value=phpSQLiteAdmin_currentdb>\n";
	print "<select name=sessionvalue onchange=\"this.form.submit();\">\n";

	$sysdbh->query("select alias,path from databases order by alias");
	while($row = $sysdbh->fetchArray()) {
		//print $row[0].'-'.$current_db."<br>\n";
		if ($row[1] != $current_db) {
			print '<option value="'.$row[1].'">'.$row[0]."</option>\n";
		} else {
			print '<option value="'.$row[1].'" selected>'.$row[0]."</option>\n";
		}
		// dunno what this is for... remove it later
		$available_dbs[] = $row[0];
	}
	print "</select>\n";
	print "</form>\n";
}


function print_column_types() {
echo<<<EOT
<option value="">typeless</option>
<option value="integer">integer</option>
<option value="float">float</option>
<option value="varchar">varchar</option>
<option value="nvarchar">nvarchar</option>
<option value="text">text</option>
<option value="boolean">boolean</option>
<option value="clob">clob</option>
<option value="blob">blob</option>
<option value="timestamp">timestamp</option>
<option value="numeric">numeric</option>
<option value="varying character">varying character</option>
<option value="national varying character">national varying character</option>
EOT;
}


class dbfile {
	var $name;
	var $device;
	var $inode;
	var $inode_protection_mode;
	var $number_of_links;
	var $uid;
	var $gid;
	var $user;
	var $group;
	var $device_type;
	var $size;
	var $last_access;
	var $last_modification;
	var $last_change;
	var $blocksize;
	var $number_of_blocks;

	function dbfile($name) {
		$this->name = $name;
		$info = stat($this->name);
		$this->device = $info[0];
		$this->inode = $info[1];
		$this->inode_protection_mode = $info[2];
		$this->number_of_links = $info[3];
		$this->uid = $info[4];
		$this->gid = $info[5];
		$this->device_type = $info[6];
		$this->size = $info[7];
		$this->last_access = $info[8];
		$this->last_modification = $info[9];
		$this->last_change = $info[10];
		$this->blocksize = $info[11];
		$this->number_of_blocks = $info[12];

  		// not on windoze
		//$userdata = posix_getpwuid($this->uid);
		//$groupdata = posix_getgrgid($this->gid);
		//$this->user = $userdata['name'];
		//$this->group = $groupdata['name'];

	}
}


class dbalias {
	var $user;
	var $alias;
	var $path;
	var $description;
	
	function get($user,$alias) {
		// select here and return object
		return 0;
	}

	function insert($user,$alias) {
	}

	function update($this) {
	}
}


// hoster mode init stuff starts here
$dirs = explode('/',$_SERVER['SCRIPT_FILENAME']);

foreach($dirs as $value) {
	$hm_dbpath[] = $value;
	if ($value == $dirs[$hm_userdirposition]) break;
}

$hm_dbpath[] = $hm_dbdir;
$hm_dbpath = implode('/',$hm_dbpath);
// hoster mode stuff ends here
?>
