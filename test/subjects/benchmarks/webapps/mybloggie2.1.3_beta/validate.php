<?php

define('IN_MYBLOGGIE', true);

session_start();

$mybloggie_root_path = './';

include_once('./config.php');
include_once('./includes/db.php');
include_once('./includes/template.php');
include_once('./includes/function.php');
include_once('./language/lang_eng.php');

   $confirm_image = '';
    if (!empty($board_config['enable_confirm']) && $mode == 'register')
    {
        $sql = 'SELECT session_id 
            FROM ' . SESSIONS_TABLE; 
        if (!($result = $db->sql_query($sql)))
        {
            die(GENERAL_ERROR, 'Could not select session data', '', __LINE__, __FILE__, $sql);
        }

        if ($row = $db->sql_fetchrow($result))
        {
            $confirm_sql = '';
            do
            {
                $confirm_sql .= (($confirm_sql != '') ? ', ' : '') . "'" . $row['session_id'] . "'";
            }
            while ($row = $db->sql_fetchrow($result));
        
            $sql = 'DELETE FROM ' .  CONFIRM_TABLE . " 
                WHERE session_id NOT IN ($confirm_sql)";
            if (!$db->sql_query($sql))
            {
                die(GENERAL_ERROR, 'Could not delete stale confirm data', '', __LINE__, __FILE__, $sql);
            }
        }
        $db->sql_freeresult($result);

        $sql = 'SELECT COUNT(session_id) AS attempts 
            FROM ' . CONFIRM_TABLE . " 
            WHERE session_id = '" . $userdata['session_id'] . "'";
        if (!($result = $db->sql_query($sql)))
        {
            die(GENERAL_ERROR, 'Could not obtain confirm code count', '', __LINE__, __FILE__, $sql);
        }

        if ($row = $db->sql_fetchrow($result))
        {
            if ($row['attempts'] > 3)
            {
                die(GENERAL_MESSAGE, $lang['Too_many_registers']);
            }
        }
        $db->sql_freeresult($result);
        
        $confirm_chars = array('A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J',  'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T',  'U', 'V', 'W', 'X', 'Y', 'Z', '1', '2', '3', '4', '5', '6', '7', '8', '9');

        list($usec, $sec) = explode(' ', microtime()); 
        mt_srand($sec * $usec); 

        $max_chars = count($confirm_chars) - 1;
        $code = '';
        for ($i = 0; $i < 6; $i++)
        {
            $code .= $confirm_chars[mt_rand(0, $max_chars)];
        }

        $confirm_id = md5(uniqid($user_ip));

        $sql = 'INSERT INTO ' . CONFIRM_TABLE . " (confirm_id, session_id, code) 
            VALUES ('$confirm_id', '". $userdata['session_id'] . "', '$code')";
        if (!$db->sql_query($sql))
        {
            die(GENERAL_ERROR, 'Could not insert new confirm code information', '', __LINE__, __FILE__, $sql);
        }

        unset($code);
        
        $confirm_image = (@extension_loaded('zlib')) ? '<img src="' . append_sid("profile.$phpEx?mode=confirm&amp;id=$confirm_id") . '" alt="" title="" />' : '<img src="' . append_sid("profile.$phpEx?mode=confirm&amp;id=$confirm_id&amp;c=1") . '" alt="" title="" /><img src="' . append_sid("profile.$phpEx?mode=confirm&amp;id=$confirm_id&amp;c=2") . '" alt="" title="" /><img src="' . append_sid("profile.$phpEx?mode=confirm&amp;id=$confirm_id&amp;c=3") . '" alt="" title="" /><img src="' . append_sid("profile.$phpEx?mode=confirm&amp;id=$confirm_id&amp;c=4") . '" alt="" title="" /><img src="' . append_sid("profile.$phpEx?mode=confirm&amp;id=$confirm_id&amp;c=5") . '" alt="" title="" /><img src="' . append_sid("profile.$phpEx?mode=confirm&amp;id=$confirm_id&amp;c=6") . '" alt="" title="" />';
        $s_hidden_fields .= '<input type="hidden" name="confirm_id" value="' . $confirm_id . '" />';

        $template->assign_block_vars('switch_confirm', array());
    }
?>
