<?

// Security
$htmlsafe                     = "no";               // disable & enable html posting
$commenthtmlsafe              = "yes";              // Disable all HTML Tags for comment section prevent exploit
$searchstriptagsenable        = "yes";              // Strip all HTML Tags before search to prevent exploit
$searchhtmlsafe               = "yes";              // Disable all HTML Tags before search to prevent exploit

// Blog Configuration
$recentlimit                  = 10;                 // No of Recent Post to be displayed
$archivelimit                 = 12;                 // No of Archive Post to be displayed
$bloglimit                    = 5;                  // No of post per page
$display_chop_text            = "no";
$editlimit                    = 15;                 // No of post per page - Post Editing page
$style                        = "aura";             // select template theme used
$language                     = "lang_eng.php";     // select language used
$blogbgcolor                  = "#ffffff";



// Switch between left of right side     menu
$right_menu                   = true;

//Email Notification
$sender_email                 = "noreply@mywebland.com";       //Email address of comment sender
$receive_email                = "";     //Email address of to receive comment notification
$emailnotification            = true;                          //Use true or false


// Trackback

$enable_trackback             = 1;
$tb_title_len                 = 75;
$tb_excerpt_len               = 255;
$tb_blogname_len              = 75;

$myblogURL                    = 'http://yourweblog.com/';
$myblogname                   = "Your Weblog Name";

//File upload
$enable_user_upload           = true;
$max_size                     = 2000000;
$file_mimes                   = array('image/jpeg','image/jpg','image/gif'
                                ,'image/png','application/msword');
$file_exts                    = array('.zip','.jpg','.png','.gif');
$allow_delete                 = true;

//thumbnail size
$max_width    = 200; // maximum x aperture  in pixels
$max_height   = 150; // maximum y aperture in pixels

// Flood Control - time allowed between comments ( same commentor )
$floodcontrol  = 300 ; // in seconds


/// Dont change anything below here !!

$html_entities_match         = array('#&(?!(\#[0-9]+;))#', '#<#', '#>#');
$html_entities_replace       = array('&amp;', '&lt;', '&gt;');

if ($timezone > -1) { $sign = "+" ;}

$mb_version                   = "2.1.3 Beta";
$blog_desc                    ="myBloggie - Open Source Weblog";

?>