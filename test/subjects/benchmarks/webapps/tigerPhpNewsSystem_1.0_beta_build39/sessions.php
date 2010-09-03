<?php
class session {
   // session-lifetime
   var $lifeTime;
   // mysql-handle
   var $main;

   function setMain($main)
    {
        $this->main = $main;
    }
   function open($savePath, $sessName) {
       // get session-lifetime
       $this->lifeTime = get_cfg_var("session.gc_maxlifetime");
       return true;
   }
   function close() {
       $this->gc(ini_get('session.gc_maxlifetime'));
       $main=$this->main;
       $main->closedb();
   }
   function read($sessID) {
       $this->gc(ini_get('session.gc_maxlifetime'));
       // fetch session-data
       $main=$this->main;
       $res = $main->run_query("SELECT session_data AS d FROM sessions WHERE session_id = '$sessID' AND session_expires > ".time());
       // return data or an empty string at failure
       if( $res->rows == 1 )
       {
           return $res->records['0']['d'];
       }
       return "";
   }
   function write($sessID,$sessData) {
       $main=$this->main;
       // new session-expire-time
       $newExp = time() + $this->lifeTime;
       // is a session with this id in the database?
       $res = $main->run_query("SELECT * FROM sessions WHERE session_id = '$sessID'");
       // if yes,
       if($res->rows == 1 ) {
           // ...update session-data
           $main->run_query("UPDATE sessions SET session_expires = '$newExp', session_data = '$sessData' WHERE session_id = '$sessID'");
           return true;
       }
       // if no session-data was found,
       else {
           // create a new row
           $res = $main->run_query("INSERT INTO sessions ( session_id, session_expires, session_data, ip ) VALUES ( '$sessID', '$newExp', '$sessData', '$_SERVER[REMOTE_ADDR]' )");
           // if row was created, return true
           if( $res->rows == 1 )
               return true;
       }
       // an unknown error occured
       return false;
   }
   function destroy($sessID) {
       $main=$this->main;
       // delete session-data
       $res=$main->run_query("DELETE FROM sessions WHERE session_id = '$sessID'");
       // if session was deleted, return true,
       if( $res->rows == 1 )
           return true;
       // ...else return false
       return false;
   }
   function gc($sessMaxLifeTime) {
       // delete old sessions
       $main=$this->main;
       $res=$main->run_query("DELETE FROM sessions WHERE session_expires < ".time());
       // return affected rows
       return $res->rows;
   }
} 
