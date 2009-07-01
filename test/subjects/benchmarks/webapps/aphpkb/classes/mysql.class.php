<?php // mysql.php mysql class
class mysql {
	   private $linkid;
	   private $host;
	   private $user;
	   private $pswd;
	   private $db;
	   private $result;
	   private $querycount;
	   
	   /* class constructor.  Initialises the $host, $user, $pawd and $db fields. */
	   
	  /* function __construct($host, $user, $pswd, $db) {
			 $this->host = $host;
			 $this->user = $user;
			 $this->pswd = $pswd;
			 $this->db = $db;
	   }*/
	   
	   function __construct() {
			 $this->host = DB_HOST;
			 $this->user = DB_USER;
			 $this->pswd = DB_PASSWORD;
			 $this->db = DB_NAME;
	   }
	   
	   
	   
	   
	   
/* Connects to the MySQL database server. */
	   
function connect() {
	   try {
			 $this->linkid = @mysql_connect($this->host, $this->user, $this->pswd);
			 if (! $this->linkid)
				    throw new Exception("Could not connect to the MySQL Server.");
			 }
			 catch (Exception $e) {
				    die($e->getMessage());
			 }
	   }
	   /* selects the Mysql Database */
	   
	   function select() {
			 try {
				    if (! @mysql_select_db($this->db, $this->linkid))
						  throw new Exception("Could not connect to the MySQL database");
			 }
			 catch (Exception $e) {
				    die($e->getMessage());
			 }
	   }
	   
	   /* Execute database query */
	   function query($query) {
			 try {
				    $this->result = @mysql_query($query, $this->linkid);
				    if (! $this->result)
						  throw new Exception("The Database query failed");
			 }
			 catch (Exception $e) {
				    echo ($e->getMessage());
			 }
			 $this->querycount++;
			 return $this->result;
	   }
	   /* Determine total rows affected by query. */
	   function affectedRows() {
			 $count = @mysql_affected_rows($this->linkid);
			 return $count;
	   }
	   
	   /* Determine total rows returned by query. */
	   function numRows() {
			 $count = @mysql_num_rows($this->result);
			 return $count;
	   }
	   
	   /* Return query result row as an object */
	   function fetchObject() {
			 $row = @mysql_fetch_object($this->result);
			 return $row;
	   }
	   
	   /* Return query result row as an indexed array. */
	   function fetchRow() {
			 $row = @mysql_fetch_row($this->result);
			 return $row;
	   }
	   
	   /* Return query result row as an associative array. */
	   function fetchArray(){
			 $row = @mysql_fetch_array($this->result);
			 return $row;
	   }
	   
	   /* Return total number queries excecuted during lifetime of this object.  Not required, but interesting nonetheless. */
	   function numQueries(){
			 return $this->querycount;
	   }
	   
	   /* Return the number of feilds in a result set. */
	   function numberFields(){
			 return @mysql_num_fields($this->result);
			 }
	   
	   /* Return a field name given an integer offset. */
	   function fieldName($offset) {
			 return @mysql_field_name($this->result, $offset);
	   }
	   
	   function getResultAsTable($action){
			 if ($this->numrows() > 0) {
				    // Start the table
				    $resultHTML = "<table border='1'>\n<tr>\n";
				    //Output the table header
				    $fieldCount = $this->numberFields();
				    for ($i=1; $i < $fieldCount; $i++) {
						  $rowName = $this->fieldName($i);
						  $resultHTML .= "<th>$rowName</th>";
				    } # end for
			 // Close the row
			 $resultHTML .= "</tr>\n";
			 
			 //Output the table data
			 while ($row = $this->fetchRow()) {
				    $resultHTML .= "<tr>\n";
				    for ($i = 1; $i < $fieldCount; $i++)
						$resultHTML .= "<td>" .htmlentities($row[$i])."</td>";
				    // Replace VALUE with the correct Primary Key
				    $action = str_replace("VALUE", $row[0], $actions);
				    // Add the action cell to end of the row
				    $resultHTML .= "<td nowrap>&nbsp;$action</td>\n</tr>\n";
				    
				    } # end while
				    
				    // Close the table
				    $resultHTML .="</table>";
			 } else {
				    $resultHTML .= "No results found";
			 }
			 return $resultHTML;
	   }
}
?>