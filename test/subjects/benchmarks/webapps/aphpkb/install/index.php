<?php // index.php - Installation Guide and Wizard

include('../config/config.php');
include('../functions.php');
include"../html/header.html";

if($_REQUEST['submit']){
// registering the admin user

echo <<<_REG
<div id="navAlpha">
<div class="title">
<p>
<img src="../imgs/logo.png" width="45" alt="Andy Grayndler">
<br /></div><b>Andy's PHP Knowledgebase</b></p>
<p><u>Registration</u><br />
<a href="../index.php">Knowledgebase Index</a><br />

<br /></p>
</div>
<div class="content">
_REG;

if(KBINSTALL==1) {

  include_once "../classes/mysql.class.php";
  
   $mysqldb = new mysql();
 $mysqldb->connect();
 $mysqldb->select(); 

$mysqldb->query("SELECT FirstName FROM authors WHERE UserName='Admin'");

 $row = $mysqldb->fetchObject();
$firstname = $row->Firstname;

if($firstname){ // don't have to worry about setting up a new admin, 'cause it looks like we've already got one.


$page_title = 'Aphpkb : Installation';
$title = 'Install';


?>
<div id="navAlpha">
<div class="title">
<p>
<img src="../imgs/logo.png" width="45" alt="Andy Grayndler">
<br /></div><b>Andy's PHP Knowledgebase</b></p>
<p><u>Release Notes</u><br />
<a href="step1.php">Step 1 - Database</a><br />
<i>Step 2 - KB Details</i><br />
<i>Step 3 - Plugins</i><br />
<i>Step 4 - Admin Auth</i><br />
<i>Step 5 - Write Config</i><br />
<br /></p>
</div>
<div class="content">
<h2>Installation Successful</h2>
<a href="../index.php">Knowledgebase Index</a><br />
</div>
<?php install_foot_page();}


} // end of admin user check

	// Check for a first name.
	if ($_REQUEST['install_first_name']) {
		$fn = $_REQUEST['install_first_name'];
		$firstname = TRUE;
	} else {
		$firstname = FALSE;
		echo '<p>First name not entered!</p>';
	}
	
	// Check for a last name.
	if ($_REQUEST['install_last_name']) {
		$ln = $_REQUEST['install_last_name'];
		$lastname = TRUE;
	} else {
		$lastname = FALSE;
		echo '<p>Last name not entered!</p>';
	}
	
	// Check for an email address.
	if ($_REQUEST['install_email']) {
		$e = $_REQUEST['install_email'];
		$email = TRUE;
	} else {
		$email = FALSE;
		echo '<p>Email Address not entered!</p>';
	}
	
	// Check for a password and match against the confirmed password.
	if ($_REQUEST['install_password1']) {
		if ($_REQUEST['install_password1'] == $_REQUEST['install_password2']) {
			$p = $_REQUEST['install_password1'];
			$password = TRUE;
		} else {
			$password = FALSE;
			echo '<p>Your password did not match the confirmed password!</p>';
		}
	} else {
		$password = FALSE;
		echo '<p>Invalid password!</p>';
	}
	
	if ($firstname && $lastname && $email && $password) { // If everything's OK.
include_once"../config/config.php";
 $mysqldb = new mysql();
 $mysqldb->connect();
 $mysqldb->select(); 

$mysqldb->query("INSERT INTO authors (UserName, FirstName, LastName, Email, Approved, Passwd, RegistrationDate) VALUES ('Admin', '$fn', '$ln', '$e', 'Y', PASSWORD('$p'), NOW())");
echo '<h2>Congratulations, your Aphpkb Install and Setup was successful - please proceed to the </h2><a href="../index.php">Knowledgebase Index</a><br />';
install_foot_page();
exit();

} else {
echo '<p>Registration of the Knowledgebase was not successfull</p>';
echo '<p><a href="step4.php">Return to Install Step 4</a></p>';
install_foot_page();
exit();
}
} else {
?>
<div id="navAlpha">
<div class="title">
<p>
<img src="../imgs/logo.png" width="45" alt="Andy Grayndler">
<br /></div><b>Andy's PHP Knowledgebase</b></p>
<p><u>Release Notes</u><br />
<a href="step1.php">Step 1 - Database</a><br />
<i>Step 2 - KB Details</i><br />
<i>Step 3 - Plugins</i><br />
<i>Step 4 - Admin Auth</i><br />
<i>Step 5 - Write Config</i><br />
<br /></p>
</div>
<div class="content">
<pre>
<?php include"../docs/README";?>
</pre>
</div>
<?php install_foot_page();}
?>