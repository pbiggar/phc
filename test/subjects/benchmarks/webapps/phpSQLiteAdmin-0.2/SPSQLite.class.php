<?php
/* vim: set expandtab tabstop=4 shiftwidth=4 foldmethod=marker: */
// +------------------------------------------------------------------------+
// | Simple Power SQLite class v 0.6                                        |
// +------------------------------------------------------------------------+
// | Copyright (c) 2003 Alan D'Angelo                                       |
// | Email         info@php-power.it, alan_dangelo@php.net                  |
// | Web           http://www.php-power.it/SPSQLiteClass.php                |
// +------------------------------------------------------------------------+
// | This source file is subject to version 3.00 of the PHP License,        |
// | that is available at http://www.php.net/license/3_0.txt.               |
// | If you did not receive a copy of the PHP license and are unable to     |
// | obtain it through the world-wide-web, please send a note to            |
// | license@php.net so we can mail you a copy immediately.                 |
// +------------------------------------------------------------------------+
// | Author: Alan D'Angelo <alan_dangelo@php.net>                           |
// +------------------------------------------------------------------------+
//
// $Id: SPSQLite.class.php, v 0.6 2003/07/15 20:30:00 alan_dangelo Exp $
//
/* ADD-ON:
// +------------------------------------------------------------------------+
// | Copyright (c) 2004 Felipe Lopes                                        |
// | Email         php4@ibest.com.br                                        |
// +------------------------------------------------------------------------+
// | ADD-ON Author: Felipe Lopes  <php4@ibest.com.br>                       |
// +------------------------------------------------------------------------+
/**
 * Simple Power SQLite class: Class in PHP for easy SQLite operation.
 * Tested on PHP 4.3.3 (Win XP) - PHP5.0.0b2dev (Win XP).
 *
 * @package Php-Power
 * @author Alan D'Angelo <info@php-power.it>
 * @since PHP 4.3.3 (SQLite PECL extension)
 * @version v 0.6 - 2003/07/15
 * @copyright Copyright 2003 Alan D'Angelo
 * @link http://www.php-power.it/SPSQLite.class.php
 * @license http://www.php.net/license/3_0.txt
 */

class SPSQLite
{
    // {{{ properties

    /**
     * The class version
     *
     * @var     string
     * @access  private
     * @see		classVersion()
     */

	var $_version = 'SPSQLite Class v 0.6';

    /**
     * The name of database
     *
     * @var     string
     * @access  private
     * @see		SPQSLite()
     */

	var $_file = '';

    /**
     * Resouce of SQLite connection
     *
     * @var     resource
     * @access  private
     * @see		SPSQLite()
     */

	var $_conn = null;

	/**
	 * Show or not show the error message?
	 *
     * @var     bool
     * @access  private
     * @see		SPSQLite(), _showError()
	 */

	var $_showError = false;

    /**
     * The SQL query
     *
     * @var     string
     * @access  private
     * @see		query()
     */

	var $_command = '';

    /**
     * The result resource
     *
     * @var     resource
     * @access  private
     * @see		query()
     */

	var $_result = null;

    /**
     * Use or not use buffer/unbeffered result?
     *
     * @var     bool
     * @access  private
     * @see		query()
     */

	var $_buffer = true;

    /**
     * Set behaviour: reset or not reset the type setting?
     * If $_rememberType is true, it comes remembered between one call and the
     * other of returnRow() and selectRow(), if it is false, $_type always comes
     * set on 'both'
     *
     * @var     string
     * @access  private
     * @see		SPSQLite(), returnRows(), selectRows()
     */

	var $_rememberType = true;

    /**
     * Type of array index (row)
     *
     * @var     string	$_type
     * @access  private
     * @see		_setType(), returnRows(), selectRows()
     */
	
	var $_type = SQLITE_BOTH;

    /**
     * Array of queries
     *
     * @var     array of strings (query)
     * @access  private
     * @see		beginTransaction(), commitTransaction()
     */

	var $_transaction = array();

    /**
     * The state of transaction
     *
     * @var     bool
     * @access  private
     * @see		beginTransaction(), commitTransaction()
     */

	var $_openTransaction = false;

    /**
     * Milliseconds of waiting time 
     *
     * @var     int
     * @access  private
     * @see		setWaitingTime()
     */

    var $_busyTimeout = 30000;

    /**
     * Array with table informations
     *
     * @var     array
     * @access  private
     * @see		
     */

    var $_tableInfo = '';

    /**
     * Array with columns names and columns types
     *
     * @var     array
     * @access  private
     * @see		
     */

    var $_colsType = '';

    // }}}
	
    // {{{ constructor SPSQLite()

    /**
    * Set the properties $file, $persistent and $showMessage.
    * Connect to database.
    *
    * @param    string  $file			filename (the SQLite database)
    * @param    bool	$persistent		true or false
    * @param    bool	$showError		true or false
    * @param	bool	$rememberType	true or false
    * @access	public
    * @return	void
    */

	function SPSQLite($file, $persistent = false, $showError = true, $rememberType = true)
	{
    	$this->_file = $file;
    	$this->_showError = $showError;
    	$this->_rememberType = $rememberType;

    	if (!$persistent) {
    		$this->_conn = @sqlite_open($this->_file, 0666, $error);
    	} else {
    		$this->_conn = @sqlite_popen($this->_file, 0666, $error);
    	}
		if (!is_resource($this->_conn)) {
			die('Impossible to open or create database ' . $this->_file);
		}
	}

    // }}}

    // {{{ setWaitingTime()
    
    /**
    * Set the waiting time to busy
    *
    * @param    int		$milliseconds	number of missiseconds
    * @access	public
    * @return	void
    */

	function setWaitingTime($milliseconds)
	{
		$this->_busyTimeout = $milliseconds;
		sqlite_busy_timeout($this->conn, $this->_busyTimeout);
	}

    // }}}

    // {{{ turboMode()
    
    /**
    * Increase the performance of SQLite
    *
    * @access	public
    * @return	void
    */

	function turboMode()
	{
		$this->query("PRAGMA default_synchronous = OFF");
	}

    // }}}

    // {{{ alterTable()
    
    /**
    * Alter the structure of table
    *
    * @param	string		$tablename		name of table
    * @param	array		$newDefinition	array that it define a columns name and type.
    *										Es: array('name1'=>'type1','name1'=>'type1',...);
    * @param	array		$sourceCols		array that define a columns name of table source
    *										Es: array('name1','name1',...);
    * @param	array		$targetCols		array that define destination columns
    * @access	public
    * @return	void
    */
	
	function alterTable($tableName, $newDefinition, $sourceCols = null, $targetCols = null)
	{
		$this->getTableInfo($tableName);
		$this->getColsType();
		
		$colsQueryType = $this->_createColsQuery($this->_colsType);
		$colsQueryName = $this->_createColsQuery($this->_colsType, true);
		$newColsQueryType = $this->_createColsQuery($newDefinition);
		$newColsQueryName = $this->_createColsQuery($newDefinition, true);

		if (empty($sourceCols)) {
			$sourceColsName = $colsQueryName;
		} else {
			$sourceColsName = $this->_createColsQuery($sourceCols, true);
		}

		if(empty($targetCols)){
			$targetColsName = $newColsQueryName;
		} else {
			$targetColsName = $this->_createColsQuery($targetCols, true);
		}

		$this->beginTransaction();
		$this->addQuery("CREATE TEMPORARY TABLE backup(" . $colsQueryType . ")");
		$this->addQuery("INSERT INTO backup SELECT " . $colsQueryName . " FROM " . $tableName);
		$this->addQuery("DROP TABLE " . $tableName);
		$this->addQuery("CREATE TABLE " . $tableName . "(" . $newColsQueryType . ")");
		$this->addQuery("INSERT INTO " . $tableName . " (" . $targetColsName . ") SELECT " . $sourceColsName . " FROM backup");
		$this->addQuery("DROP TABLE backup");
		$this->commitTransaction();
	}

    // }}}

    // {{{ _createColsQuery()
    
    /**
    * This method create a fragment of query (process the array whith columns definition)
    *
    * @param	array		$colsfinition	array that it define a columns name or columns name and type
    * @access	private
    * @return	string
    */
	
	function _createColsQuery($colsDefinition, $onlyName = false)
	{
		if($onlyName){
			if(is_int(key($colsDefinition))){
				$colsQuery = $colsDefinition;
			} else {
				$colsQuery = array_keys($colsDefinition);
			}
		} else {
			foreach ($colsDefinition as $name => $type) {
				$colsQuery[] = $name . ' ' . $type;
			}
		}
		
		return implode(', ' , $colsQuery);
	}

    // }}}

    // {{{ _setTableInfo()
    
    /**
    * This method set _tableInfo
    *
    * @param	string		$tablename	the name of table
    * @access	private
    * @return	void
    */
	
	function _setTableInfo($tablename)
	{
		$query = "SELECT type, name, tbl_name, rootpage, sql FROM sqlite_master where tbl_name = '" . $tablename . "'";
		$this->query($query);
		$this->_tableInfo = $this->selectRows(0);
	}

    // }}}

    // {{{ getTableInfo()
    
    /**
    * This method return an array of table info or a specific info
    *
    * @param	string		$tablename	the name of table
    * @param	string		$type		specific the typo of information to obtain
    *									valid values are: 'type','name','tbl_name','rootpage','sql'
    * @access	public
    * @return	array or string
    */
	
	function getTableInfo($tablename, $type = '')
	{
		$this->_setTableInfo($tablename);
		
		if(empty($type)){
			return $this->_tableInfo;
		} else {
			return $this->_tableInfo[$type];
		}
	}

    // }}}

    // {{{ _setColsType()
    
    /**
    * Set the array _colsType with columns information
    *
    * @access	private
    * @return	void
    */
	
	function _setColsType()
	{
		$SQLCreateTable = preg_replace("/\s+/", ' ', $this->_tableInfo['sql']);
		$n = strpos($SQLCreateTable, '(');
		$cols = substr($SQLCreateTable, $n + 1, -1) ;
		$cols = split(',[^0-9]', $cols);	// preserve the integrity in NUM(XX,XX)
        foreach ($cols as &$col)
        {
            $col = $this->_filterTrim ($col);
            $col = $this->_filterName ($col);
            $col = $this->_filterType ($col);
        }
		$this->_colsType = $this->_colsTypeCombine($name, $type);
	}
	
    // }}}

    // {{{ getColsType()
    
    /**
    * This method return an array with columns name and type of the current table
    *
    * @param	string		$colname	a specific column name
    * @access	public
    * @return	array or string
    */
	
	function getColsType($colname = '')
	{
		$this->_setColsType();
		
		if(empty($colname)){
			return $this->_colsType;
		} else {
			return $this->_colsType[$colname];
		}
	}

    // }}}

    // {{{ encodeBinary()
    
    /**
    * This method return encoded binary data
    *
    * @param	string		$file	name/path of file
    * @access	public
    * @return	string
    */
	
	function encodeBinary($file)
	{
		if (file_exists($file) && is_readable($file)) {
			$fr = fopen($file, 'rb');

			do {
				$data = fread($fr, 1024);
				if (strlen($data) == '') {
        			break;
    			}
    			$content .= $data;
			} while(true);
			
			return sqlite_udf_encode_binary($content);
			
		} else {
			$this->_showError('Impossible find file');;
		}
	}
	
    // }}}

    // {{{ decodeBinary()
    
    /**
    * This method return decoded binary data
    *
    * @param	string		$content	binary data
    * @access	public
    * @return	string
    */
	
	function decodeBinary($content)
	{
		return sqlite_udf_decode_binary($content);
	}

    // }}}

    // {{{ otimizeDatabase()
    
    /**
    * Optimize dimension of database with the SQLite statemant VACUUM
    *
    * @param	string		$indexOrTable	an index of a name of table
    * @access	public
    * @return	void
    */
	
	function optimizeDatabase($indexOrTable)
	{
		$this->query("VACUUM " . $indexOrTable);
	}

    // }}}

    // {{{ addFunction()
    
    /**
    * This method expand the SQLite ability
    *
    * The functions added with this method, can be used in the sql query.
    * The functgion of PHP, they can be called with the sintax:
    * php('functionName', param, param, ...)
    *
    * @param	string		$name				name of SQLite function
    * @param	string		$originalFunction	name of the original funtion to call
    * @param	int			$args				number of aguments
    * @access	public
    * @return	void
    */
	
	function addFunction($name, $originalFunction, $args)
	{
		sqlite_create_function($this->_conn, $name, $originalFunction, $args);
	}
	
    // }}}

    // {{{ query()
    
    /**
    * Submit a SQL query to database
    *
    * @param	string	$query		query SQL SQLite compatible		
    * @param	bool	$buffer		true or false (If you only need sequential access to
    								the data, it is recommended false)
    								If you use false, some function do not work.
    * @access	public
    * @return	bool
    */

	function query($query, $buffer = true)
	{
		$this->_command = $query;
		$this->_buffer = $buffer;
		
		if ($buffer) {
			$this->_result = @sqlite_query($query, $this->_conn);
		} else {
			$this->_result = @sqlite_unbuffered_query($query, $this->_conn);
		}
		
		if (!$this->_result) {
			$this->_showError();
			return false;
		} else {
			//echo $query . '<p>';
			return true;
		}
	}

    // }}}

    // {{{ returnRows()
    
    /**
    * Get rows !!
    *
    * @param	string	$type		'both', 'assoc' or 'num'
    * @access	public
    * @return	mixed
    */
	
	function returnRows($type = null, $return_one_row = false)
	{
		if (isset($type)) {
			$this->_setType($type);
		}

		while ($row = @sqlite_fetch_array($this->_result, $this->_type, true)) {
			$rows[] = $row;
		}

		if($return_one_row == true) {
			
			return $rows;

		} else {
			if (count($rows) == 1) {
				return $rows[0];
			} else {
				return $rows;
			}
		}
	}
	
    // }}}

    // {{{ selectRows()
    
    /**
    * Select a portion of rowset
    *
    * @param	int		$index01		first row number
    * @param	int		$index02		last row number
    * @param	string	$type			type of index
    *									'both', 'num' or 'assoc'
    * @access	public
    * @return	mixed
    */
	
	function selectRows($index01, $index02 = null, $type = null)
	{
		if (isset($type)) {
			$this->_setType($type);
		}
		
		if ($this->_buffer) {
			if (isset($index01) && (empty($index02) || ($index02 < $index01))) {
				if (@sqlite_seek($this->_result, $index01)) {
					return sqlite_current($this->_result, $this->_type, true);
				}
			} else {
				while (@sqlite_seek($this->_result, $index01) && ($index01 <= $index02)) {
					$rows[] = sqlite_current($this->_result, $this->_type, true);
					$index01++;
				}
				return $rows;
			}
			
		} else {
			$this->_showError('Query unbuffered: selectRows() is unavailable');
			return false;
		}
	}
	
    // }}}

    // {{{ _setType()
    
    /**
    * This method set a type-index of the array rows
    *
    * @param	string		$type	'both', 'num' or 'assoc'
    * @access	private
    * @return	void
    */
    
    function _setType($type)
    {
		if ($type == 'both' || (empty($type) && !$this->_rememberType)) {
			$this->_type = SQLITE_BOTH;
		}
		if ($type == 'assoc') {
			$this->_type = SQLITE_ASSOC;
		}
		if ($type == 'num') {
			$this->_type = SQLITE_NUM;
		}
    }

    // {{{ lastInsertId()
    
    /**
    * Return the last insert id (column declared INTEGER PRIMARY KEY )
    *
    * @access public
    * @return int
    */
	
	function lastInsertId()
	{
		return sqlite_last_insert_rowid($this->_conn);
	}
	
    // }}}

    // {{{ affectedRows()
    
    /**
    * Return how many lines are changed
    *
    * @access public
    * @return int
    */
	
	function affectedRows()
	{
		return sqlite_changes($this->_conn);
	}
	
    // }}}

    // {{{ numRows()
    
    /**
    * Return the number of rows
    *
    * @access public
    * @return int
    */
	
	function numRows($table = "")
	{
		if (($this->_buffer) && (empty($table))) {
			return sqlite_num_rows($this->_result);
		} elseif (($this->_buffer) && (!empty($table))) {
			$this->query("SELECT * FROM " . $table);
			return sqlite_num_rows($this->_result);
		} else {
			$this->_showError('Query unbuffered: numRows() is unavailable');
			return false;
		}
	}
	
    // }}}

    // {{{ beginTransaction()
    
    /**
    * Start transaction process
    *
    * @access public
    * @return void
    */
	
	function beginTransaction()
	{
		$this->_openTransaction = true;
		$this->_transaction = array();
		$this->_transaction[] = "BEGIN TRANSACTION;";
	}

    // }}}

    // {{{ commitTransaction()
    
    /**
    * Finish the transaction process
    *
    * @param  bool $stop		true or false, if $stop is true 
    * @access public
    * @return void
    */
	
	function commitTransaction($stop = false)
	{
		$this->_transaction[] = "COMMIT TRANSACTION;";
		foreach ($this->_transaction as $query) {
			if (!$this->query($query)) {
				$this->_rollbackTransaction();
				if (!$stop) {
					return false;
				} else {
					$this->close();
					die('A query as failed - Rollback go !!');
				}
			}
		}
		$this->_openTransaction = false;
	}

    // }}}

    // {{{ _rollbackTransaction()

    /**
    * If a query fails in a transaction, this method it takes part
    *
    * @access private
    * @return void
    */

	function _rollbackTransaction()
	{
		$this->query('ROLLBACK TRANSACTION');
	}
	
    // }}}

    // {{{ addQuery()
    
    /**
    * Add a query to transaction
    *
    * @param  string $query
    * @access public
    * @return void
    */
	
	function addQuery($query)
	{
		if ($this->_openTransaction) {
			$this->_transaction[] = $query;
		} else {
			$this->_showError('No one transaction is open');
		}
	}
	
    // }}}

    // {{{ escapeString()
    
    /**
    * Prepare a string with special characters
    *
    * @param  string $string
    * @access public
    * @return string
    */
	
	function escapeString($string)
	{
		return sqlite_escape_string($string);
	}
	
    // }}}

    // {{{ libEncoding()
    
    /**
    * The encoding of library
    *
    * @access public
    * @return string
    */
	
	function libEncoding()
	{
		return sqlite_libencoding();
	}
	
    // }}}

    // {{{ libVersion()
    
    /**
    * The version of library
    *
    * @access public
    * @return string
    */
	
	function libVersion()
	{
		return sqlite_libversion();
	}
	
    // }}}

    // {{{ classVersion()
    
    /**
    * The version of class
    *
    * @access public
    * @return string
    */
	
	function classVersion()
	{
		return $this->_version;
	}
	
    // }}}

    // {{{ _showError()
    
    /**
    * Print the last error
    *
    * @param  string $message		the error message
    * @access private
    * @return void
    */
	
	function _showError($message = '')
	{
		if (!empty($message)) {
			$istruzione = $message;
		} else {
			$istruzione = $this->_command;
		}
		if ($this->_showError) {
			$msg_errore = "<p>ERROR: <ul><li>Error n°: " . sqlite_last_error($this->_conn) . 
							"</li><li>Description: " . sqlite_error_string(sqlite_last_error($this->_conn)) . 
							"</li><li>Possibile cause: " . htmlentities($istruzione) . "</li></ul></p>";
		}
		echo $msg_errore;
	}

    // }}}

    // {{{ close()
    
    /**
    * Close a connection to database
    *
    * @access public
    * @return void
    */
	
	function close()
	{
		unset($this->_conn);
	}

    // }}}

    // {{{ _filterName()
    
    /**
    * Accessory method
    *
    * @access private
    * @return string
    */
	
	function _filterName($col)
	{
		$pos = strpos($col, ' ');
		/* see str_split() in PHP 5 */
		$name = substr($col, 0, $pos);

		return trim($name);
	}

    // }}}

    // {{{ _filterType()

    /**
    * Accessory method
    *
    * @access private
    * @return string
    */

	function _filterType($col)
	{
		$n = strpos($col, ' ');
		/* see str_split() in PHP 5 */
		$type = substr($col, $n + 1, strlen($col));

		return trim($type);
	}

    // }}}

    // {{{ _filterTrim()

    /**
    * Accessory method
    *
    * @access private
    * @return string
    */

	function _filterTrim($col)
	{
		return trim($col);
	}

    // }}}

    // {{{ _filterName()

    /**
    * Accessory method
    *
    * @access private
    * @return array
    */

	/* see array_combine in PHP 5 */
	function _colsTypeCombine($name, $type)
	{
		for ($i = 0; $i < count($name); $i++) {
			$cols[$name[$i]] = $type[$i];
		}
		return $cols;
	}

	/*
	HERE STARTS ADD-ON TO SPSQLITE CLASS TO FIT PHPSLA NEEDS
	*/

	function listTables() {

		$query = "SELECT name FROM sqlite_master WHERE type='table' ORDER BY name";
		$this->query($query);

	}

	function getIndexesInfo($tbl_name = "") {

		if (empty($tbl_name)) {
			
			$query = "SELECT * FROM sqlite_master WHERE type='index' ORDER BY name";
			$this->query($query);

		} else {

			$query = "SELECT * FROM sqlite_master WHERE type='index' AND tbl_name='$tbl_name' ORDER BY name";
			$this->query($query);

		}

	}

	function dbInfo() {

		$dbInfo['size'] = filesize($this->_file);
		$dbInfo['last_mod'] = date("Y-m-d H:i", filemtime($this->_file));
		$dbInfo['last_acc'] = date("Y-m-d H:i", fileatime($this->_file));
		$dbInfo['owner'] = fileowner($this->_file);

		clearstatcache();

		return $dbInfo;

	}

	function fetchArray($type = 'num') {

		if (isset($type)) {

			$this->_setType($type);

		}

		return @sqlite_fetch_array($this->_result, $this->_type);

	}

	function vacuum() {

		$this->query("VACUUM");

	}

}

    // }}}

/*
	This product includes PHP, freely available from
	<http://www.php.net/>.
*/

?>
