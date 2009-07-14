<?
/*
 * This software is part of the Tiger php news system
 * http://tpns.sourceforge.net
 * 
 * This software comes with ABSOLUTELY NO WARRANTY. For details, see
 * the enclosed file COPYING for license information (GPL). If you
 * did not receive this file, see http://www.gnu.org/licenses/gpl.txt.
 * 
 */
        require_once( 'Table.php' ); 
class Main
{
    //{{{ Some initialization
    var $page = array();
    var $abbr;
    var $database = "";
    var $newscol = "1";
    var $_convert_path="";
    var $allowanoncomment='false';
    var $allowanonaddcomment='false';
    var $debug='off';
    var $allowanonvote='false';
    var $allowanonaddvote='false';
    var $allowmenunewsaddcomment='false';
    var $allowanonuserhome='false';
    var $showdate='true';
    var $allowanonguestbook='true';
    var $allowanonaddguestbook='true';
    var $showuser='true';
    var $showcategory='true';
    var $maxnrlinks='10';
    var $db;
    var $text;
    var $nr=10;
    var $oldrequestid=0;
    var $showviews="true";
    var $enablebbcode="true";
    var $enableabbr="true";
    var $sqlstatments="";
    var $thumbwidth="150";
    var $thumbheight="300";
    var $thumbquality="80";
    var $newsimgwidth="400";
    var $newsimgheight="800";
    var $newsimgquality="80";
    var $isbot=false;
    var $havecookie="true";
    var $filepath="";
    var $prevnext="";
    var $bbcode="";
    var $mincommentsaccess=0;
    var $usedbsessions=false;
    
    //}}}
    //{{{ Main
    function Main()
    {
        include( 'config.php' );
        $this->database = $database;
        $this->newscol = $newscol;
        $this->_convert_path= $_convert_path;
        $this->debug = $debug;
        $this->allowanoncomment=$allowanoncomment;
        $this->allowanonaddcomment=$allowanonaddcomment;
        $this->allowmenunewsaddcomment=$allowmenunewsaddcomment;
        $this->allowanonvote=$allowanonvote;
        $this->allowanonaddvote=$allowanonaddvote;
        $this->allowanonuserhome=$allowanonuserhome;
        $this->allowanonguestbook=$allowanonguestbook;
        $this->allowanonaddguestbook=$allowanonaddguestbook;
        $this->showuser=$showuser;
        $this->showcategory=$showcategory;
        $this->showviews=$showviews;
        $this->showdate=$showdate;
        $this->maxnrlinks=$maxnrlinks;
        $this->enablebbcode=$enablebbcode;
        $this->enableabbr=$enableabbr;
        $this->nr=$nr;
        $this->filepath=$filepath;
        $this->oldrequestid=0;if ( isset($_SESSION['reqid'])){$this->oldrequestid=$_SESSION['reqid'];}
        $this->db=mysql_connect( $server, $username, $password );
        $this->thumbwidth=$thumbwidth;
        $this->thumbheight=$thumbheight;
        $this->thumbquality=$thumbquality;
        $this->newsimgwidth=$newsimgwidth;
        $this->newsimgheight=$newsimgheight;
        $this->newsimgquality=$newsimgquality;
        $this->abbrcasesensitive=$abbrcasesensitive;
        $this->mincommentsaccess=$mincommentsaccess;
        $this->usedbsessions=$usedbsessions;

        mysql_select_db( $this->database, $this->db);
    }
    //}}}
    //{{{ set bb code
    function setBBcode($bbcode)
    {
        $this->bbcode=$bbcode;
    }
    //}}}
    //{{{ Set text
    function settext( $text )
    {
        $this->text=$text;
    }
    //}}}
    
    //{{{ Print  news
    function printnews( $news,$nrofnews,$role,$userid,$start,$nr,$page,$subpage )
    {
        $requestid=1;if ( isset($_SESSION['reqid']) ){$requestid=$_SESSION['reqid'];}
        $menu=array();
        $name="";
        if ( $subpage == "" and isset($this->text["$page"]) )
        {
            $name=$this->text["$page"];
        }
        elseif ( isset($this->text["$subpage"]))
        {
            $name=$this->text["$subpage"];

        }
        if ( $name == "" and $_SESSION['lastpage'] == "newscat" and isset($_SESSION['catid']))
        {
            $tname=$this->run_query ("select name from category where id = $_SESSION[catid];");
            $name=$tname->records[0]['name'];
            if ( isset($this->text["$name"]) ){$name=$this->text["$name"];}
        }
        if ( "$subpage" != "" ){$subpage="&amp;subpage=$subpage";}
        $counter=0;
        $colwidth=100/$this->newscol;
        $viewnews="false";
        if ( $nrofnews == 1 or $nr == 1  or ($start == -1 and $nr == -1 and $subpage == ""))
        {
            $colwidth=100;
            $this->newscol=1;
            $viewnews="true";
            $this->incresenewsviews($news->records[0]['id']);
        }
        elseif($news->rows == "1")
        {
            $colwidth=100;
            $this->newscol=1;
        }
        if ( $viewnews == "true" and $news->records['0']['type'] > "2" ){$name="";}
        print "<table width='100%' summary='News'>\n";
        if ( $name != "" )
        {
            print "<tr><td colspan='$this->newscol'><span class=\"headline\"><b>$name</b></span></td></tr>\n";
        }
        $newsid="-1";
        $newstype="0";
        $newstart=$start;
        $this->printprevnext( $viewnews, $nr, $start, $nrofnews,$page,$subpage );
        foreach( $news->records as $text )
        {	
            $newsid=$text['id'];
            $newstype=$text['type'];
            if ( $counter % $this->newscol == 0)
            {      
                print "<tr>\n";
            }
            if ( $role >= $text['access'] or $userid == $text['owner'] or ( $this->allowanonuserhome == "true" and $text['access'] <= "2" ) or $role == 4 )
            {
                $date=date("Y-m-d H:i:s",$text['date']);

                print "<td valign='top' class='w$colwidth'><table summary='news cell table' class='newsmain'><tr><td class='titlel'>\n";
                if ( $viewnews == "false" )
                {
                    print "&nbsp;&nbsp;<b><a class='title' href='?page=$page&amp;start=$newstart&amp;nr=1'>$text[headline]</a></b>\n";
                }
                else
                {
                    print "&nbsp;&nbsp;<b class='title'><span class='uline'>$text[headline]</span></b>\n";
                }
                if ( $page == "manageinitpages" )
                {
                    print " ( ".$this->text["access$text[access]"]." )";
                }
                print "<span class=\"smaller\">";
                if ( "$text[order]" == "0" )
                {
                    print $this->text['issticky']."\n";
                }
                $category=$text['category'];
                if ( isset($this->text['$category']) and ( $text['type'] <= "2" or $text['type'] == "5" or $text['type'] >= "8") and $this->showcategory == "true" ){$category=$this->text['$category'];}
                if ( ($text['type'] <= "2" or $text['type'] == "5" or $text['type'] >= "8" ) and $this->showcategory == "true" )
                {
                    if ( $text['type'] <= "2" or $text['type'] >= "8" )
                    {
                        print "&nbsp;&nbsp;<a class='title' href='?page=newscat&amp;catid=$text[catid]'>$category</a>";
                    }
                    else
                    {
                        print "&nbsp;&nbsp;$category";
                    }
                }
                if ( $this->showdate == "true" and $text['type'] != "4"){print "&nbsp;&nbsp;($date)";}
                print "&nbsp;</span>";
                print "</td><td align='right' class='titler'>&nbsp;&nbsp;</td></tr>\n";
                $added="false";
                if (  (   ( $role != "0"  or $this->allowanoncomment == "true") 
                            and ( ($text['type'] <= "2" or $text['type'] >= "5" ) 
                                  or ($text['type'] == "3" and $this->allowmenunewsaddcomment == "true"))   
                          ) or 
                      ( $text['name'] != "" and ($role != "0" or ($this->allowanonuserhome == "true" and $this->showuser == "true" )) or 
                      ( ($text['type'] <= "2"  or $text['type'] == "9" ) and $this->showuser == "true" ) or 
                      ("$role" == "3" or "$text[owner]" == "$userid") and "$role" != "4" ) or 
                      "$role" == "4" )
                {
                    print "<tr><td class='titleb' colspan='2'>&nbsp;&nbsp;<span class=\"smaller\">\n";
                    $added="true";
                }
                if (($role != "0" or $this->allowanoncomment == "true") and (($text['type'] <= "2" or $text['type'] >= "5") or ($text['type'] == "3" and $this->allowmenunewsaddcomment == "true")))
                {
                    if ($viewnews != "true" )
                    {
                        print "<a class='title' href='?page=$page&amp;start=$newstart&amp;nr=1'>".$this->text['nrcomments']."&nbsp;$text[comments]</a>&nbsp;\n";
                    }
                    else
                    {
                        print "<a class='title' href='#comments'>".$this->text['nrcomments']."&nbsp;$text[comments]</a>&nbsp;\n";
                    }
                }
                if (($text['type'] <= "2"  or $text['type'] >= "5") and $text['name'] != "" and ($role != "0" or ($this->allowanonuserhome == "true" and $this->showuser == "true" )))
                {
                    print "<a class='title' href='?page=userhome&amp;id=$text[owner]'>$text[name]</a>\n";
                }
                elseif (( $text['type'] <= "2"  or $text['type'] >= "5") and $this->showuser == "true" )
                {
                    print "$text[name]\n";
                }
                if ( ("$role" == "3" or "$text[owner]" == "$userid") and "$role" != "4" )
                {
                    print "&nbsp;<a class='title' href='?page=editnews&amp;id=$text[id]&amp;rid=$requestid'>".$this->text['edit']."</a>\n"; 
                    if ($text['type'] != "4" or ($page == "manageinitpages" and $text['access'] != 0 )){ print "&nbsp;<a class='title' href='?page=rmnews&amp;id=$text[id]&amp;rid=$requestid'>".$this->text['remove']."</a>\n";}	
                    if (($page == "myhome" or $page == "admhiddennews" ) and $text['type'] == "9" ){print "&nbsp;bbcode: [news=$text[id]]$text[headline][/news]";}
                }
                elseif ( "$role" == "4"  )
                {
                    print "&nbsp;<a class='title' href='?page=editnews&amp;id=$text[id]&amp;rid=$requestid'>".$this->text['edit']."</a>\n";
                    if ($text['type'] != "4" or ($page == "manageinitpages" and $text['access'] != 0 ) ){print "&nbsp;<a class='title' href='?page=rmnews&amp;id=$text[id]&amp;rid=$requestid'>".$this->text['remove']."</a>&nbsp;<a class='title' href='?page=deletenews&amp;id=$text[id]&amp;rid=$requestid'>".$this->text['delete']."</a>\n";}
                    if (($page == "myhome" or $page == "admhiddennews" ) and $text['type'] == "9" ){print "&nbsp;bbcode: [news=$text[id]]$text[headline][/news]";}
                }
                if ( $added == "true" ){print "&nbsp;&nbsp;</span></td></tr>";}
                print "<tr><td valign='top' colspan='3'>\n"; 
                if ( isset($text['img']) and $text['img'] != "" and $viewnews == "false" )
                {
                    print "<a class='title' href='?page=$page&amp;start=$newstart&amp;nr=1'><img src='thumb/news/$text[id]/$text[img]' alt='$text[headline]' class='right'/></a>\n";
                }
                if ( isset($text['img']) and $text['img'] != "" and $viewnews == "true" )
                {
                    print "<a class='title' href='img/news/$text[id]/$text[img]' onclick='window.open(this.href);return false;'><img src='small/news/$text[id]/$text[img]' alt='$text[headline]' class='right'/></a>\n";
                }
                print "$text[data]\n";
                if ( $viewnews == "true" and $text['data2'] != "" )
                {
                    print "<br />$text[data2]\n";
                }
                elseif ( $text['length'] != "0")
                {
                    print "<br /><br /><span class=\"smaller\"><a href='?page=$page&amp;start=$newstart&amp;nr=1'>".$this->text['readmore']." ( $text[length] ".$this->text['chars']." )</a></span>\n";
                }
                print "</td></tr>\n";

                if (( $text['type'] <= "2"  or $text['type'] >= "5") and ("$role" >= "1" or $this->allowanonaddvote == "true" ))
                {
                    print "<tr><td class='title' align='center' colspan='3'><span class=\"smaller\">".$this->text['vote'].":&nbsp;&nbsp;\n";
                    print "<a class='title' href='?page=vote&amp;id=$text[id]&amp;value=1&amp;start=$start&amp;nr=$nr&amp;rid=$requestid' rel='nofollow'>1</a>&nbsp;|&nbsp;\n";	
                    print "<a class='title' href='?page=vote&amp;id=$text[id]&amp;value=2&amp;start=$start&amp;nr=$nr&amp;rid=$requestid' rel='nofollow'>2</a>&nbsp;|&nbsp;\n";	
                    print "<a class='title' href='?page=vote&amp;id=$text[id]&amp;value=3&amp;start=$start&amp;nr=$nr&amp;rid=$requestid' rel='nofollow'>3</a>&nbsp;|&nbsp;\n";	
                    print "<a class='title' href='?page=vote&amp;id=$text[id]&amp;value=4&amp;start=$start&amp;nr=$nr&amp;rid=$requestid' rel='nofollow'>4</a>&nbsp;|&nbsp;\n";	
                    print "<a class='title' href='?page=vote&amp;id=$text[id]&amp;value=5&amp;start=$start&amp;nr=$nr&amp;rid=$requestid' rel='nofollow'>5</a>\n";
                    print "&nbsp;&nbsp;(&nbsp;".$this->text['rating'].":&nbsp;\n"; 
                    printf("%01.2f", round( $text['rating']/$text['votes'], 2 ));
                    print "&nbsp;&nbsp;".$this->text['votes'].":&nbsp;$text[votes]\n";
                    if ( isset($text['views']) and $this->showviews == "true" )
                    {
                        print ", ".$this->text['pageviews']." $text[views] ";
                    }
                    print ")</span></td></tr>";
                }
                elseif ( isset($text['views']) and $this->showviews == "true" )
                {
                    print "<tr><td class='title' align='center' colspan='3'><span class=\"smaller\">( ".$this->text['pageviews']." $text[views] )</span></td></tr>";
                }

                print "</table></td>\n";
                $newstart=$newstart + 1; 
            }
            else
            {
                print "<tr><td>".$this->text['pleaselogin']."</td></tr>\n";
            }
            $counter++;
            if ( $counter % $this->newscol == 0)
            {      
                print "</tr>\n";
            }
        }
        while ($counter % $this->newscol != 0)
        {
            print "<td>&nbsp;</td>\n";
            $counter++;
            if ( $counter % $this->newscol == 0 )
            {
                print "</tr>\n";
            }
        }
        
        $this->printprevnext( $viewnews, $nr, $start, $nrofnews,$page,$subpage );
        print "</table>\n";
        if ($viewnews == "true" and ($role != "0" or $this->allowanoncomment == "true") and (($text['type'] <= "2" or $text['type'] >= "5") or ($text['type'] == "3" and $this->allowmenunewsaddcomment == "true")) ) 
        {
            if ($newstype == "3" and $this->allowmenunewsaddcomment == "false" ){return false;}
            if ( $role < $this->mincommentsaccess ){return false;}
            
            $cstart="";if( isset($_REQUEST['cstart'] )){$cstart=$_REQUEST['cstart'];}
            $cnr=$this->nr;if( isset($_SESSION['nr'] )){$cnr=$_SESSION['nr'];}
            if( isset($_REQUEST['cnr'] )){$cnr=$_REQUEST['cnr'];}
            $this->printcomments( $newsid, $role,$userid,$cstart,$cnr,$page,$start );
        }

    }

//}}}
//{{{ print prev next  
  function printprevnext( $viewnews, $nr, $start, $nrofnews,$page,$subpage )
  {
      if ( $this->prevnext == "" )
      {
        if ( $nrofnews > $nr and (($viewnews == "false" and $nrofnews > 1 )or ($nr == 1 and $viewnews == "true" and $nrofnews > 1 )) )
        {
            $this->prevnext= "<tr>";
            if ( $start != "-1" )
            {	
                $this->prevnext.="<td colspan='$this->newscol' class='title'><span class=\"large\">".$this->text['nrnews']."&nbsp;$nrofnews\n&nbsp;&nbsp;\n";
                if ( $start > 0 )
                {
                    $pstart=$start-$nr;if ($pstart < 0 ){$pstart=0;}
                    $this->prevnext.=" <a class='title' href='?page=$page$subpage&amp;start=$pstart&amp;nr=$nr'>".$this->text['prev']."</a> \n";
                }
                else
                {
                    $this->prevnext.=$this->text['prev'];
                }
                $this->prevnext.="&nbsp;|&nbsp;";

                $nroflinksadded=0;
                $pagenr=0;
                $maxnrofnews=$nrofnews;
                $maxnrlinks=$this->maxnrlinks;
                if ( $nrofnews / $nr > $maxnrlinks )
                {
                    $nroflinksadded=$start - ( $nr * ( $maxnrlinks / 2));
                    if ( $nroflinksadded < 0 ){ $nroflinksadded=0;}
                    $maxnrofnews=$nroflinksadded + ($nr * $maxnrlinks);
                    if ($maxnrofnews > $nrofnews )
                    {
                        $maxnrofnews=$nrofnews;
                        if ( $maxnrofnews % $nr != 0)
                        {
                            $maxnrofnews=$maxnrofnews - ($maxnrofnews % $nr) + $nr;
                        }
                    }
                    $nroflinksadded=$maxnrofnews - ( $nr * ( $maxnrlinks));
                    if ( $nroflinksadded < 0 ){ $nroflinksadded=0;}

                    $pagenr=$nroflinksadded / $nr;
                }
                if ( $nroflinksadded != 0 )
                {
                    $this->prevnext.="<a class='title' href='?page=$page$subpage&amp;start=0&amp;nr=$nr'>&lt;&lt;</a>&nbsp;\n";
                }
                while ( $nroflinksadded < $maxnrofnews )
                {
                    $pagenr=$pagenr+1;
                    if( $start != $nroflinksadded )
                    {
                        $this->prevnext.="<a class='title' href='?page=$page$subpage&amp;start=$nroflinksadded&amp;nr=$nr'>$pagenr</a>&nbsp;";
                    }
                    else
                    {
                        $this->prevnext.="<b class='title'>$pagenr</b>&nbsp;";
                    }
                    $nroflinksadded=$nr+$nroflinksadded;
                }
                if ( $maxnrofnews != ($nrofnews - ($nrofnews % $nr) + $nr) and $maxnrofnews != $nrofnews )
                {
                    $lastnrpagestart=$nrofnews - ($nrofnews % $nr );
                    if ( $lastnrpagestart == $nrofnews )
                    {
                        $lastnrpagestart=$lastnrpagestart - $nr;
                    }
                    $this->prevnext.="<a class='title' href='?page=$page$subpage&amp;start=$lastnrpagestart&amp;nr=$nr'>&gt;&gt;</a>&nbsp;\n";
                }
                $this->prevnext.="|&nbsp;";
                if ( $nrofnews > $nr+$start )
                {
                    $nstart=$start+$nr;
                    $this->prevnext.="<a class='title' href='?page=$page$subpage&amp;start=$nstart&amp;nr=$nr'>".$this->text['next']."</a>&nbsp;\n";
                }
                else
                {
                    $this->prevnext.=$this->text['next'];
                }
                $this->prevnext.="</span></td>\n";
            }
            elseif ( $news->records['0']['type'] < "2" )
            {
                $this->prevnext.="<td colspan='$this->newscol' class='title'><span class=\"smaller\">&nbsp;</span></td>\n";
            }
            else
            {
                $this->prevnext.="<td></td>";
            }
            $this->prevnext.="</tr>\n";
        }
        elseif( $nrofnews == 0 and $viewnews == "false" )
        {
            print "<tr><td colspan='$this->newscol' class='title'><span class=\"large\">".$this->text['nrnews']."&nbsp;$nrofnews</span></td></tr>";
            $this->prevnext=" ";
        }
        elseif( $nrofnews <= $nr and $viewnews == "false" )
        {
            $this->prevnext="<tr><td colspan='$this->newscol' class='title'><span class=\"large\">".$this->text['nrnews']."&nbsp;$nrofnews</span></td></tr>";
        }
        
      }
        print $this->prevnext;
  }
  ///}}}
   //{{{ Print comments
    function printcomments( $newsid, $role,$userid,$cstart,$cnr,$page,$nstart )
    {
        $requestid=1;if ( isset($_SESSION['reqid']) ){$requestid=$_SESSION['reqid'];}
        $_SESSION['lastid']=$newsid;
        if ( "$cnr" == "-1" )
        {
            $cnr=$this->nr;
        }
        if ( "$cstart" == "" or "$cstart" == "-1" )
        {
            #$cstart = $nrofcomments - $cnr;
            $cstart = 0;
        }
        if ( $cstart < 0 )
        {
            $cstart=0;
        }
        if ( $newsid == "-1" )
        {
            $nrofcomments = $this->run_query ( "SELECT count(id) as nr from comment c where c.type = '100'");
            $comments = $this->run_query ( "SELECT c.id, UNIX_TIMESTAMP(c.date) as date, c.from, c.headline, c.data, u.name, c.anonname, c.anonemail, c.anonhomepage, u.role, u.homepage from comment c left join user u on ( c.from = u.id )  where c.type = '100' order by c.id desc limit $cstart,$cnr"); 
        }
        else
        {
            $nrofcomments = $this->run_query ( "SELECT count(id) as nr from comment c where c.toid = '$newsid' and c.type = '1'");
            $comments = $this->run_query ( "SELECT c.id, UNIX_TIMESTAMP(c.date) as date, c.from, c.headline, c.data, u.name, c.anonname, c.anonemail, c.anonhomepage, u.role, u.homepage from comment c left join user u on ( c.from = u.id )  where c.type = '1' and c.toid = $newsid order by c.id desc limit $cstart,$cnr"); 
        }
        $nrofcomments = $nrofcomments->records['0']['nr'];
            $menu=array();
            print "<table width='100%' summary='comments'>\n";
            if ( $newsid != "0")
            {	
                print "<tr><td colspan='3'><span class=\"headline\"><b>";
                print $this->text['comments'];
                print "</b></span><a name=\"comments\" /></td></tr>\n";
            }
            foreach( $comments->records as $text)
            {
                $date=date("Y-m-d H:i:s",$text['date']);
                print "<tr><td class='titlel'>&nbsp;&nbsp;<b class='title'><span class='uline'>$text[headline]</span></b>&nbsp;<span class=\"small\">($date)&nbsp;&nbsp;&nbsp;";
                if ( ($this->allowanonuserhome == "true" or $role != "0") and $text['from'] != '0' )
                {   
                    print "<a class='title' href='?page=userhome&amp;id=$text[from]'>$text[name]</a>\n";
                }
                elseif ( $text['from'] != '0' )
                { 
                    print "$text[name]\n";
                }
                else
                {
                    if ( $text['anonname'] != ""  )
                    {
                        print "$text[anonname]\n";
                    }
                    else
                    {
                        print "$text[name]\n";
                    }
                    if ( $role >= "3" and $text['anonemail'] != "" )
                    {
                        print "&nbsp;<a class='title' href='mailto:$text[anonemail]'>$text[anonemail]</a>\n";
                    }
                }
                if ( $text['homepage'] != "" )
                {
                    $text['homepage'] = str_replace("class=\"title\"", "" ,$text['homepage']);
                    $text['homepage'] = str_replace("target=", "class=\"title\" target=" ,$text['homepage']);
                    print str_replace("onclick=", "class=\"title\" onclick=" ,$text['homepage']);
                }
                elseif ( $text['anonhomepage'] != "" )
                {
                    $text['anonhomepage'] = str_replace("class=\"title\"", "" ,$text['anonhomepage']);
                    $text['anonhomepage'] =  str_replace("target=", "class=\"title\" target=" ,$text['anonhomepage']);
                    print str_replace("onclick=", "class=\"title\" onclick=" ,$text['anonhomepage']);
                }
                
                if ( ("$role" == "3" or ( isset($text['owner']) and "$text[owner]" == "$userid" ) ) and "$role" != "4" )
                {
                    print "&nbsp;<a class='title' href='?page=editcomment&amp;id=$text[id]&amp;rid=$requestid'>".$this->text['edit']."</a>\n";
                    if ($page != "removedcomments" ){print "&nbsp;<a class='title' href='?page=rmcomment&amp;id=$text[id]&amp;rid=$requestid'>".$this->text['remove']."</a>\n";}
                }
                elseif ( "$role" == "4"  )
                {
                    print "&nbsp;<a class='title' href='?page=editcomment&amp;id=$text[id]&amp;rid=$requestid'>".$this->text['edit']."</a>\n";
                    if ($page != "removedcomments" ){print "&nbsp;<a class='title' href='?page=rmcomment&amp;id=$text[id]&amp;rid=$requestid'>".$this->text['remove']."</a>\n";} 
                    print "&nbsp;<a class='title' href='?page=deletecomment&amp;id=$text[id]&amp;rid=$requestid'>".$this->text['delete']."</a>\n";	
                }
                print "</span></td><td colspan='2' align='right' class='titler'>&nbsp;&nbsp;</td></tr><tr><td valign='top' colspan='2'>\n";
                print "$text[data]\n";
                print "</td></tr>\n";
            }
            print "<tr><td colspan='3' class='title'><span class=\"small\">&nbsp;&nbsp;".$this->text['nrcomments']."&nbsp;$nrofcomments&nbsp;&nbsp;\n";
            if ( $cstart > 0 )
            {
                $pstart=$cstart-$cnr;if ($pstart < 0 ){$pstart=0;}
                print "<a class='title' href='?page=$page&amp;cstart=$pstart&amp;cnr=$cnr&amp;start=$nstart&amp;nr=1'>".$this->text['prev']."</a>\n";
            }
            else
            {
                print $this->text['prev'];
            }
            print "&nbsp;|&nbsp;\n";
            if ( $nrofcomments > $cnr+$cstart )
            {
                $cstart=$cstart+$cnr;
                print "<a class='title' href='?page=$page&amp;cstart=$cstart&amp;cnr=$cnr&amp;start=$nstart&amp;nr=1'>".$this->text['next']."</a>\n";
            }
            else
            {
                print $this->text['next'];
            }
            print "</span></td></tr>\n";
            print "</table>\n";
            if ( ( $role >= 1 or $this->allowanonaddcomment == "true" ) and $page != "removedcomments"  )
            {
                print "<script type='text/javascript'>
                    function validate(form)
                    {
                        error=\"\";";
                        if ( $role == 0 )
                        {
                            print "
                                if ( form.name.value == \"\" )
                                {
                                    error=\"".str_replace(":",","," ".$this->edit_array( $this->text['name'])." ")."\";
                                }
                                if ( form.imgkey.value == \"\" )
                                {
                                    error=error+\"".str_replace(":",","," ".$this->edit_array( $this->text['imgkey'])." ")."\";
                                }

                            ";
                        }
                        print "if ( form.header.value == \"\" )
                        {
                            error=error+\"".str_replace(":",","," ".$this->edit_array( $this->text['header'])." ")."\";
                        }

                        if ( form.data.value == \"\" )
                        {
                            error=error+\"".str_replace(":",""," ".$this->edit_array( $this->text['comment'])." ")."\";
                        }
                        if (error != '' )
                        {
                            error=error.replace(\":\", \",\");
                            alert('".$this->edit_array( $this->text['missingfields'])."'+' '+error);
                            return;
                        }
                        else
                        {
                            form.submit();
                        }
                    }
                </script>";
                print "<form enctype='multipart/form-data' action='?page=addnewscomment&amp;start=$nstart&amp;nr=1&amp;cnr=$cnr' method='post'>\n";
                print "<p><input type='hidden' name='rid' value='$requestid' /></p>\n";
                print "<table summary='".$this->text['addcomment']."'>\n";
                print "<tr><td colspan='2'>&nbsp;</td></tr>\n";
                if ( $role == 0 )
                {
                    print "<tr><td>".$this->text['name']."</td><td><input name='name' type='text' id='name' value='$_SESSION[anonname]' /></td></tr>\n";
                    print "<tr><td>".$this->text['email']."</td><td><input name='email' type='text' id='email' value='$_SESSION[anonemail]' /></td></tr>\n";
                    print "<tr><td>".$this->text['homepageheader']."</td><td><input name='homepage' type='text' id='homepage' value='$_SESSION[anonhomepage]' /></td></tr>\n";
                    print "<tr><td>".$this->text['imgkey']."&nbsp;<span class='smaller'>".$this->text['imgkeyhelp']."</span></td><td><input name='imgkey' type='text' id='imgkey' value='' /><img src='randimg.php?rid=$requestid' alt='".$this->text['imgkey']."'/></td></tr>\n";
                }
                print "<tr><td>".$this->text['header']."</td><td><input name='header' type='text' id='header'/></td></tr>\n";
                print "<tr><td colspan='2'>".$this->text['comment']."</td></tr>\n";
                print "<tr><td colspan='2'><textarea name='data' rows='5' cols='70'></textarea></td></tr>\n";
                print "<tr><td colspan='2'><input type='button' value='".$this->text['addcomment']."' id='addcomment' onclick=\"validate(this.form)\" class='button'/>";
                print "<input type='reset' value='".$this->text['reset']."'  class='button'/></td></tr>\n";
                print "</table></form>\n";
                print $this->bbcode;
            }
    }
    //}}}
 
 //{{{ Clean array
    function clean_array( $arr, $checknumeric = true, $bbcodeabbr = true ) 
    {
        if ( is_numeric($arr) )
        {
            return $arr;
        }
        elseif (is_string($arr))
        {
            if ( $bbcodeabbr )
            {
                return $this->addacronym($this->bbcodetohtml($this->encode($arr, array("&","#","[","]",";","=","/","*",":","@",".","-","_","?","~","!") )));
            }
            else
            {
                return $this->encode($arr, array("&","#","[","]",";","=","/","*",":","@",".","-","_","?","~","!"));
            }
        }
        else
        {
            $numeric=array("nr", "id", "rid", "start", "access", "order", "category", "type", "parent","pwdinid", "cstart","cnr","imgkey", "uorder");
            $bbcode=array("news","extnews","data","data2","homepage", "anonhomepage","cookietext");

            $rs = array();
            foreach ($arr as $key => $val)
            {
                if(is_array($val)) 
                {
                    $rs[$key] = $this->clean_array($val, $checknumeric, $bbcodeabbr);
                }
                else 
                {
                    $val = trim($val);
                    if ( is_numeric($val) )
                    {
                        $rs[$key] = $val;
                    }
                    elseif ((!in_array($key, $numeric)) or $checknumeric == false )
                    {
                        if ( $key == "homepage" and $bbcodeabbr )
                        {
                            $val = "[url=".$val."]".$val."[/url]";
                        }
                        if ( $bbcodeabbr and in_array($key, $bbcode))
                        {
                            $rs[$key] = $this->addacronym($this->bbcodetohtml($this->encode($val, array("&","#","[","]",";","=","/","*",":","@",".","-","_","?","~","!"))));
                        }
                        else
                        {
                            $rs[$key] = $this->encode($val, array("&","#","[","]",";","=","/","*",":","@",".","-","_","?","~","!"));
                        }
                    }
                }
            }
            return $rs;
        }
    }
    //}}}
    //{{{ Edit array
    function edit_array($arr) 
    {
        if ( is_numeric($arr) )
        {
            return $arr;
        }
        elseif (is_string($arr))
        {
            $arr=trim($arr);
            if ( is_numeric($arr) )
            {
                return $arr;
            }
            else
            {
                return $this->decode($this->htmltobbcode($this->removeacronym($arr)));
            }

        }
        else
        {
            $rs = array();
            foreach ($arr as $key => $val)
            {
                if(is_array($val)) 
                {
                    $rs[$key] = $this->edit_array($val);
                }
                else 
                {
                    $val=trim($val);
                    if ( $key == "homepage" or $key == "anonhomepage" )
                    {
                        $val = preg_replace("#(\<a)(.*?)(\>)(.*?)(\</a\>)#is","$4",$val);
                    }
                    $rs[$key] = $this->decode($this->htmltobbcode($this->removeacronym($val)));
                }
            }
            return $rs;
        }
    }
    //}}}
    //{{{ Edit str
    function editstr( $key , $string )
    {
        if ( $key == "homepage" or $key == "anonhomepage" )
        {
                    $string = preg_replace("#(\<a)(.*?)(\>)(.*?)(\</a\>)#is","$4",$string);
        }
        return $this->decode($this->htmltobbcode($this->removeacronym($string)));
    }
    //}}}
//{{{Encode
function encode($string, $donttranslate)
{
    $string = stripslashes($string);
    $string = str_replace("&","&amp;"   ,$string);
    $string = str_replace("<", "&lt;"   ,$string);
    $string = str_replace(">", "&gt;"   ,$string);
    $string = str_replace("å", "&aring;",$string);
    $string = str_replace("ä", "&auml;" ,$string);
    $string = str_replace("ö", "&ouml;" ,$string);
    $string = str_replace("Å", "&Aring;" ,$string);
    $string = str_replace("Ä", "&Auml;" ,$string);
    $string = str_replace("Ö", "&Ouml;" ,$string);
    $len = strlen($string);
    $res = "";
    for($i = 0; $i < $len; ++$i) 
    {
        $char=$string{$i};
        $ord = ord($char);
        if ( in_array($char,$donttranslate) )
        {
            $res .= $char;
        }
        elseif( ($ord >= 123 or $ord <= 47 or ( $ord >= 58 and $ord <= 64) or ( $ord >= 91 and $ord <= 96)) and $ord >= 33 )
        {
            $res .= "&#".$ord.";";
        }    
        else
        {
            $res .= $char;
        }
    }
    return preg_replace("/&amp;([#0-9a-z]*);/i" , "&$1;",$res);
}
///}}}
//{{{Decode
function decode($string )
{
    $string = preg_replace("/&#([0-9]*);/e" , "unichr($1)",$string);
    $string = str_replace( "&amp;"  ,"&",$string);
    $string = str_replace("&lt;","<",$string);
    $string = str_replace("&gt;",">",$string);
    $string = str_replace( "&aring;","å",$string);
    $string = str_replace( "&auml;" ,"ä",$string);
    $string = str_replace( "&ouml;" ,"ö",$string);
    $string = str_replace( "&Aring;","Å",$string);
    $string = str_replace( "&Auml;" ,"Ä",$string);
    $string = str_replace( "&Ouml;" ,"Ö",$string);

    return $string;
}
//}}}
//{{{ bbcodetohtml
function bbcodetohtml ($string)
{
    $string = str_replace("[sp]","&nbsp;",$string);
    $string = str_replace("[br]","<br />",$string);

    if ( (substr_count($string, "[table]")) == (substr_count($string, "[/table]")))
    {
        if ( (substr_count($string, "[tr]")) != 0 )
        {
            if ( (substr_count($string, "[td]")) != 0 or (substr_count($string, "[th]")) != 0  )
            {
                $string = preg_replace("#([\n]*\[td\])(.*?)([\n]*\[/td\])#is","<td class=\"newstable\">$2</td>", $string);
                $string = preg_replace("#([\n]*\[th\])(.*?)([\n]*\[/th\])#is","<th class=\"newstable\">$2</th>", $string);
                $string = preg_replace("#([\n]*\[tr\])(.*?)([\n]*\[/tr\])#is","<tr>$2</tr>", $string);
                $string = preg_replace("#([\n]*\[table\])(.*?)([\n]*\[/table\])#is","<table class=\"newstable\" summary=\"table in news\">$2</table>", $string);
            }
        }
    }

    $string = preg_replace("#(\[i\])(.*?)(\[/i\])#is","<i>$2</i>", $string);
    $string = preg_replace("#(\[u\])(.*?)(\[/u\])#is","<span class=\"uline\">$2</span>", $string);
    $string = preg_replace("#(\[b\])(.*?)(\[/b\])#is","<b>$2</b>", $string);
    $string = preg_replace("#(\[s\])(.*?)(\[/s\])#is","<span class=\"small\">$2</span>", $string);
    $string = preg_replace("#(\[strike\])(.*?)(\[/strike\])#is","<span class=\"strike\">$2</span>", $string);
    $string = preg_replace("#([\n]*)(\[bq\])([\n]*)(.*?)([\n]*)(\[/bq\])([\n]*)#is","<blockquote><p>$4</p></blockquote>", $string);
    $string = preg_replace("#(\[big\])(.*?)(\[/big\])#is","<big>$2</big>", $string);
    $string = preg_replace("#(\[sm\])(.*?)(\[/sm\])#is","<small>$2</small>", $string);

    if ( (substr_count($string, "[list")) != 0 and (substr_count($string, "[list")) == (substr_count($string, "[/list]" )))
    {
        $string = preg_replace("#([\n]*)(\[list=1\])([\n]*)(.*?)([\n]*)(\[/list\])([\n]*)#is","<ol class=\"num\">$4[/*]</ol>", $string);
        $string = preg_replace("#([\n]*)(\[list=a\])([\n]*)(.*?)([\n]*)(\[/list\])([\n]*)#s","<ol class=\"la\">$4[/*]</ol>", $string);
        $string = preg_replace("#([\n]*)(\[list=A\])([\n]*)(.*?)([\n]*)(\[/list\])([\n]*)#s","<ol class=\"ua\">$4[/*]</ol>", $string);
        $string = preg_replace("#([\n]*)(\[list=i\])([\n]*)(.*?)([\n]*)(\[/list\])([\n]*)#s","<ol class=\"lr\">$4[/*]</ol>", $string);
        $string = preg_replace("#([\n]*)(\[list=I\])([\n]*)(.*?)([\n]*)(\[/list\])([\n]*)#s","<ol class=\"ur\">$4[/*]</ol>", $string);
        $string = preg_replace("#([\n]*)(\[list\])([\n]*)(.*?)([\n]*)(\[/list\])([\n]*)#is","<ul>$4[/*]</ul>", $string);
        $string = str_replace("[*]","[/*][*]",$string);
        $string = preg_replace("#([\n]*)(\[\*\])([\n]*)(.*?)([\n]*)(\[/\*\])([\n]*)#is","<li>$4</li>", $string);
        $string = preg_replace("#([\n]*)(\[/\*\])#is","",$string);
    }
    $string = preg_replace("#(\[color=\#)([0-9a-f])([0-9a-f])([0-9a-f])(\])(.*?)(\[/color\])#is", "<span style=\"color: #$2$3$4;\">$6</span>", $string);
    $string = preg_replace("#(\[color=\#)([0-9a-f])([0-9a-f])([0-9a-f])([0-9a-f])([0-9a-f])([0-9a-f])(\])(.*?)(\[/color\])#is", "<span style=\"color: #$2$3$4$5$6$7;\">$9</span>", $string);
    $string = preg_replace("#(\[color=)([a-z]*)(\])(.*?)(\[/color\])#is", "<span style=\"color: $2;\">$4</span>", $string);
    $string = preg_replace("#(\[file=)([0-9]*)(\])(.*?)(\[/file\])#is", "<a href=\"?page=dload&amp;id=$2\">$4</a>", $string);
    $string = preg_replace("#(\[news=)([0-9]*)(\])(.*?)(\[/news\])#is", "<a href=\"?page=viewnews&amp;id=$2\">$4</a>", $string);
    $string = preg_replace("#(\[cat=)([0-9]*)(\])(.*?)(\[/cat\])#is", "<a href=\"?page=newscat&amp;catid=$2\">$4</a>", $string);
    $string = preg_replace("#(\[vfile=)([0-9]*)(\])(.*?)(\[/vfile\])#is", "<a href=\"?page=dload&amp;id=$2&amp;view=true\">$4</a>", $string);
    $string = preg_replace("#(\[page=)([0-9a-z]*)(\])(.*?)(\[/page\])#is", "<a href=\"?page=$2\">$4</a>", $string);
    $string = preg_replace("#(\[url=)(http|https|ftp):\/\/([A-Z0-9\_\-\/\.\?\~\=\!\&;:\#]*)(\])(.*?)(\[/url\])#is", "<a href=\"$2://$3\" onclick=\"window.open(this.href);return false;\">$5</a>", $string);
    $string = preg_replace("#(\[url=)mailto:([A-Z0-9\_\-\/\.]*)@([A-Z0-9\_\-\/\.]*)(\])(.*?)(\[/url\])#is", "<a href=\"mailto:$2@$3\">$5</a>", $string);
    $string = preg_replace("#(\[url=)mailto:(.*)(\])(.*?)(\[/url\])#is", "$4", $string);
    $string = preg_replace("#(\[url=)([A-Z0-9\_\-\/\.\?\~\=\!\&;:\#]*)(\])(.*?)(\[/url\])#is", "<a href=\"http://$2\" onclick=\"window.open(this.href);return false;\">$4</a>", $string);
    $string = preg_replace("#(\[url=)(.*?)(\])(.*?)(\[/url\])#is", "$4", $string);
    $string = str_replace("\n","<br />\n",$string);
    return $string;
}
//}}}
//{{{ htmltobbcode
function htmltobbcode ($string)
{
    $string = str_replace("<i>","[i]",$string);
    $string = str_replace("</i>","[/i]",$string);
    $string = str_replace("<b>","[b]",$string);
    $string = str_replace("</b>","[/b]",$string);

    $string = preg_replace("#(\<span class=\"strike\"\>)(.*?)(\</span\>)#is","[strike]$2[/strike]", $string);
    $string = preg_replace("#(\<span class=\"uline\"\>)(.*?)(\</span\>)#is","[u]$2[/u]", $string);
    $string = preg_replace("#(\<span style=\"font-size:80%;\"\>)(.*?)(\</span\>)#is","[s]$2[/s]", $string);
    $string = preg_replace("#(\<span class=\"small\"\>)(.*?)(\</span\>)#is","[s]$2[/s]", $string);

    $string = preg_replace("#(\<span style=\"color: )([\#0-9a-z]*)(;\"\>)(.*?)(\</span\>)#is","[color=$2]$4[/color]", $string);

    $string = str_replace("</strike>","[/strike]",$string);
    $string = str_replace("<table class=\"newstable\" summary=\"table in news\">","\n[table]",$string);
    $string = str_replace("</table>","\n[/table]",$string);
    $string = str_replace("<tr>","\n[tr]",$string);
    $string = str_replace("</tr>","[/tr]",$string);
    $string = str_replace("<td class=\"newstable\">","[td]",$string);
    $string = str_replace("</td>","[/td]",$string);
    $string = str_replace("<th class=\"newstable\">","[th]",$string);
    $string = str_replace("</th>","[/th]",$string);
    $string = str_replace("&amp;","&",$string);

    $string = str_replace("<blockquote><p>","[bq]",$string);
    $string = str_replace("</p></blockquote>","[/bq]",$string);

    $string = str_replace("<li>","\n[*]",$string);
    $string = str_replace("</li>","",$string);
    $string = str_replace("<ol type=\"1\">","\n[list=1]",$string);
    $string = str_replace("<ol type=\"a\">","\n[list=a]",$string);
    $string = str_replace("<ol type=\"A\">","\n[list=A]",$string);
    $string = str_replace("<ol type=\"i\">","\n[list=i]",$string);
    $string = str_replace("<ol type=\"I\">","\n[list=I]",$string);

    $string = str_replace("<ol class=\"num\">","\n[list=1]",$string);
    $string = str_replace("<ol class=\"la\">","\n[list=a]",$string);
    $string = str_replace("<ol class=\"ua\">","\n[list=A]",$string);
    $string = str_replace("<ol class=\"lr\">","\n[list=i]",$string);
    $string = str_replace("<ol class=\"ur\">","\n[list=I]",$string);

    $string = str_replace("</ol>","\n[/list]",$string);
    $string = str_replace("&nbsp;","[sp]",$string);

    $string = str_replace("<big>","[big]",$string);
    $string = str_replace("</big>","[/big]",$string);
    $string = str_replace("<small>","[sm]",$string);
    $string = str_replace("</small>","[/sm]",$string);
    $string = str_replace("<ul>","\n[list]",$string);
    $string = str_replace("</ul>","\n[/list]",$string);
    $string = preg_replace("#(\<a href=\"\?page=dload\&id=)([0-9]*)(\"\>)(.*?)(\</a\>)#is","[file=$2]$4[/file]", $string);
    $string = preg_replace("#(\<a href=\"\?page=dload\&id=)([0-9]*)(&view=true\"\>)(.*?)(\</a\>)#is","[vfile=$2]$4[/vfile]", $string);
    
    $string = preg_replace("#(\<a href=\"\?page=viewnews\&id=)([0-9]*)(\"\>)(.*?)(\</a\>)#is","[news=$2]$4[/news]", $string);
    $string = preg_replace("#(\<a href=\"\?page=newscat\&catid=)([0-9]*)(\"\>)(.*?)(\</a\>)#is","[cat=$2]$4[/cat]", $string);
    $string = preg_replace("#(\<a href=\"\?page=)([0-9a-z]*)(\"\>)(.*?)(\</a\>)#is","[page=$2]$4[/page]", $string);
    
    $string = preg_replace("#(\<a href=\")(http|https|ftp):\/\/(.*?)(\" target=_blank\>)(.*?)(\</a\>)#is", "[url=$2://$3]$5[/url]", $string);
    $string = preg_replace("#(\<a href=\")(http|https|ftp):\/\/(.*?)(\" target=\"_blank\"\>)(.*?)(\</a\>)#is", "[url=$2://$3]$5[/url]", $string);
    $string = preg_replace("#(\<a href=\")(http|https|ftp):\/\/(.*?)(\" onclick=\"window.open\(this.href\);return false;\"\>)(.*?)(\</a\>)#is", "[url=$2://$3]$5[/url]", $string);


    $string = preg_replace("#(\<a href=\"mailto:)(.*?)(\"\>)(.*?)(\</a\>)#is", "[url=mailto:$2]$4[/url]", $string);
    $string = str_replace("<br />\n","\n",$string);
    $string = str_replace("&lt;br /&gt;\n","\n",$string);
    $string = str_replace("<br />","\n",$string);
    $string = str_replace("&lt;br /&gt;","\n",$string);
    return $string;
}
//}}}
//{{{ Add acronym
function addacronym($string)
{
    if ( isset($this->abbr) )
    {
        $abbr=$this->abbr;
    }
    else
    {    
        $abbr = $this->run_query( "select * from `abbr`" );
        $this->abbr=$abbr;
    }
    $string=" $string ";
    foreach ( $abbr->records as $abbrrow ) 
    {
        $string = str_replace("&#44;", ",", $string );
        if ($this->abbrcasesensitive)
        {
            if ( $abbrrow['type'] == 1 )
            {
                $string = preg_replace("#([\!\s\-\_,\,','\.\>\]])($abbrrow[word])([\!\s\-\_,\,','\.:\<\[])#s", "$1<acronym title=\"$abbrrow[title]\">$2</acronym>$3", $string);
            }
            elseif ( $abbrrow['type'] == 2 )
            {
                $string = preg_replace("#([\!\s\-\_,\,','\.\>\]])($abbrrow[word])([\!\s\-\_,\,','\.:\<\[])#s", "$1<acronym title=\"$abbrrow[title]\">$2</acronym>$3", $string);
            }
            elseif ( $abbrrow['type'] == 3 )
            {
                $string = preg_replace("#([\!\s\-\_,\,','\.\>\]])($abbrrow[word])([\!\s\-\_,\,','\.:\<\[])#s", "$1<a onclick=\"window.open(this.href);return false;\" title=\"$abbrrow[title]\" href=\"$abbrrow[data]\">$2</a>$3", $string);
            }
        }
        else
        {
            if ( $abbrrow['type'] == 1 )
            {
                $string = preg_replace("#([\!\s\-\_,\,','\.\>\]])($abbrrow[word])([\!\s\-\_,\,','\.:\<]\[)#is", "$1<acronym title=\"$abbrrow[title]\">$2</acronym>$3", $string);
            }
            elseif ( $abbrrow['type'] == 2 )
            {
                $string = preg_replace("#([\!\s\-\_,\,','\.\>\]])($abbrrow[word])([\!\s\-\_,\,','\.:\<\[])#is", "$1<acronym title=\"$abbrrow[title]\">$2</acronym>$3", $string);
            }
            elseif ( $abbrrow['type'] == 3 )
            {
                $string = preg_replace("#([\!\s\-\_,\,','\.\>\]])($abbrrow[word])([\!\s\-\_,\,','\.:\<\[])#is", "$1<a onclick=\"window.open(this.href);return false;\" title=\"$abbrrow[title]\" href=\"$abbrrow[data]\">$2</a>$3", $string);
            }
        }
        $string = str_replace(",", "&#44;", $string);
    }
    $string=trim($string);
    return $string;
}
//}}}
//{{{ Remove acronym
function removeacronym ( $string )
{
        $string = preg_replace("#(\<acronym title=\")(.*?)(\">)(.*?)(</acronym>)#is", "$4",$string);
        $string = preg_replace("#(\<a target=\"_blank\" title=\")(.*?)(\" href=\")(.*?)(\"\>)(.*?)(\</a\>)#is", "$6", $string);
        $string = preg_replace("#(\<a onclick=\"window.open\(this.href\);return false;\" title=\")(.*?)(\" href=\")(.*?)(\"\>)(.*?)(\</a\>)#is", "$6", $string);
        return $string;
}
///}}}
    //{{{ Rss str
    function rssstr( $string )
    {
        $string = trim($string);
        $string = str_replace( "&aring;","å",$string);
        $string = str_replace( "&auml;" ,"ä",$string);
        $string = str_replace( "&ouml;" ,"ö",$string);
        $string = str_replace( "&Aring;","Å",$string);
        $string = str_replace( "&Auml;" ,"Ä",$string);
        $string = str_replace( "&Ouml;" ,"Ö",$string);
        $string = str_replace( "onclick=\"window.open(this.href);return false;\"" ,"",$string);
        $string = str_replace( "href='?page=" ,"href='http://$_SERVER[HTTP_HOST]/?page=",$string);
        $string = str_replace( "href=\"?page=" ,"href=\"http://$_SERVER[HTTP_HOST]/?page=",$string);
        $string = str_replace( "href='/" ,"href=\"http://$_SERVER[HTTP_HOST]/",$string);
        $string = str_replace( "href=\"/" ,"href=\"http://$_SERVER[HTTP_HOST]/",$string);
        
        return $string;
    }
    //}}}

//{{{ RSS array
    function rss_array($arr) 
    {
        $rs = array();
        foreach ($arr as $key => $val)
        {
            if(is_array($val)) 
            {
					// we removed the recursion here to make the analysis work.
					// Either way, the result would be a string, and we wont get a
					// constant string because of the _SERVER checks in rssstr.
                $rs[$key] = $this->rssstr("some string");
            }
            else 
            {
                $rs[$key] = $this->rssstr($val);
            }
        }
        return $rs;
    }
    //}}}
    // {{{Is public ip
    function isPublicIp($url) {
        $ip = gethostbyname($url);
        $long = ip2long($ip);
        if (($long >= 167772160 AND $long <= 184549375) OR ($long >= -1408237568 AND $long <= -1407188993) OR ($long >= -1062731776 AND $long <= -1062666241) OR ($long >= 2130706432 AND $long <= 2147483647) OR $long == -1) {
            return false;
        }
        return true;
    }
    // }}}
//{{{ Is vallid e-mail
    function isemail($email)
    {
        $rule="/^((([a-zA-Z0-9\._-])*( )*)*( <)?)?([a-zA-Z0-9])+([a-zA-Z0-9\._-])*@(([a-zA-Z0-9_-])+([a-zA-Z0-9\._-]+)*(.))+(>)?$/";
        return preg_match($rule, $email) ? 1 : 0;
    }
    //}}}
    
    //{{{ rmdirr
    function rmdirr($target)
        // removes a directory and everything within it
    {
        $verbose=$this->debug=="on";
        $exceptions=array('.','..');
        if (!$sourcedir=@opendir($target))
        {
            if ($verbose)
                echo '<strong>Couldn&#146;t open '.$target."</strong><br />\n";
            return false;
        }
        while(false!==($sibling=readdir($sourcedir)))
        {
            if(!in_array($sibling,$exceptions))
            {
                $object=str_replace('//','/',$target.'/'.$sibling);
                if($verbose)
                    echo 'Processing: <strong>'.$object."</strong><br />\n";
                if(is_dir($object))
                    rmdirr($object);
                if(is_file($object))
                {
                    $result=@unlink($object);
                    if ($verbose&&$result)
                        echo "File has been removed<br />\n";
                    if ($verbose&&(!$result))
                        echo "<strong>Couldn&#146;t remove file</strong>";
                }
            }
        }
        closedir($sourcedir);
        if($result=@rmdir($target))
        {
            if ($verbose)
                echo "Target directory has been removed<br />\n";
            return true;
        }
        if ($verbose)
            echo "<strong>Couldn&#146;t remove target directory</strong>";
        return false;
    }
        //}}}
    //{{{ Mkdir
    function mkdirr($path)
    {
        if(is_dir($path)) return true;
        return $this->mkdirr(dirname($path)) && @mkdir($path);
    }
    //}}}
    //{{{ Resize
    function resize($src, $dst, $width, $height, $quality, $image_info  )
    {
        //$image_info = getImageSize($src) ; // see EXIF for faster way

        switch ($image_info['mime']) {
            case 'image/gif':
                if (imagetypes() & IMG_GIF)  {
                    $old_im = imagecreatefromgif($src) ;
                } break;
            case 'image/jpeg':
                if (imagetypes() & IMG_JPG)  {
                    $old_im = imagecreatefromjpeg($src) ;
                } break;
            case 'image/png':
                if (imagetypes() & IMG_PNG)  {
                    $old_im = imagecreatefrompng($src) ;
                } break;
            case 'image/wbmp':
                if (imagetypes() & IMG_WBMP)  {
                    $old_im = imagecreatefromwbmp($src) ;
                } break;
        }
        if ( isset($old_im) )
        {
            $old_wd = imagesx($old_im) ;
            $old_ht = imagesy($old_im) ;

            $new_ht = round( $old_ht * ( $width / $old_wd  ));
            $new_wd = $width;
            if ( $new_ht > $height )
            {
                $new_wd = round( $old_wd * ( $height / $old_ht ));
                $new_ht = $height;
            }
            $new_im = imageCreateTrueColor( $new_wd , $new_ht );

            imageCopyResampled( $new_im, $old_im, 0, 0, 0, 0, $new_wd , $new_ht , $old_wd, $old_ht);

            switch ($image_info['mime']) {
                case 'image/gif':
                    if (imagetypes() & IMG_GIF)  {
                        imagegif($new_im,$dst);
                    } break;
                case 'image/jpeg':
                    if (imagetypes() & IMG_JPG)  {
                        imagejpeg($new_im,$dst, $quality);
                    } break;
                case 'image/png':
                    if (imagetypes() & IMG_PNG)  {
                        imagepng($new_im,$dst);
                    } break;
                case 'image/wbmp':
                    if (imagetypes() & IMG_WBMP)  {
                        imagewbmp($new_im,$dst);
                    } break;
            }
            imageDestroy($old_im);
            imageDestroy($new_im);
            if ( $this->debug == "on")
            {
                print "New $image_info[mime] image created using GD old size $old_wd x $old_ht new size $new_wd x $new_ht <br/>\n";
            }
            return;
        }
        $params_line = "-geometry " . $width . "x" . $height . " -quality " . $quality;

        if($dst) 
        {
            exec("$this->_convert_path $params_line \"$src\" \"" . escapeshellcmd($dst) . "\"");
        } 
        else 
        {
            passthru("$this->_convert_path $params_line \"$src\" -");
        }
        if ( $this->debug == "on")
        {
            print "New $image_info[mime] image created using ImageMagick old size $old_wd x $old_ht new size $new_wd x $new_ht <br/>\n";
        }
    }
    //}}}
    //{{{ Upload file
    function uploadfile( $file, $type, $userid )
    {
        $filename=str_replace(" ","_",basename($file['name']));
        $filename=str_replace("å","a",$filename);
        $filename=str_replace("ä","a",$filename);
        $filename=str_replace("ö","o",$filename);
        $filename=str_replace("Å","A",$filename);
        $filename=str_replace("Ä","A",$filename);
        $filename=str_replace("Ö","O",$filename);
        $filename=str_replace("(","_",$filename);
        $filename=str_replace(")","_",$filename);
        $filename=ereg_replace("[^a-z,A-Z,0-9,_,.]","_",$filename);
        $thumbdir="./thumb/$type/$userid/";
        $smalldir="./small/$type/$userid/";
        $uploaddir="./img/$type/$userid/";
        $thumbfile="$thumbdir$filename";
        $uploadfile = "$uploaddir$filename";
        $smallfile="$smalldir$filename";
        $this->mkdirr($thumbdir);
        $this->mkdirr($uploaddir);
        $this->mkdirr($smalldir);
        if (getimagesize($file['tmp_name']))
        {       
            $imagesize=getimagesize($file['tmp_name']);
            if (move_uploaded_file($file['tmp_name'], $uploadfile)) {
                if ( "$imagesize[1]" > $this->newsimgwidth or "$imagesize[0]" > $this->newsimgheight )
                {
                    $this->resize($uploadfile, $smallfile, $this->newsimgwidth,$this->newsimgheight , $this->newsimgquality, $imagesize );
                }
                else
                {
                    exec("cp $uploadfile $smallfile");
                }
                $imagesize=getimagesize($smallfile);
                if ( "$imagesize[1]" > $this->thumbwidth or "$imagesize[0]" > $this->thumbheight )
                {
                    $this->resize($smallfile, $thumbfile, $this->thumbwidth, $this->thumbheight, $this->thumbquality, $imagesize );	
                }
                else
                {
                    exec("cp $smallfile $thumbfile");
                }
            }
        }
        return $filename;
    }
    ///}}}
    //{{{ Upload any file
    function uploadanyfile( $file, $dir )
    {
        $filename=str_replace(" ","_",basename($file['name']));
        $filename=str_replace("å","a",$filename);
        $filename=str_replace("ä","a",$filename);
        $filename=str_replace("ö","o",$filename);
        $filename=str_replace("Å","A",$filename);
        $filename=str_replace("Ä","A",$filename);
        $filename=str_replace("Ö","O",$filename);
        $filename=str_replace("(","_",$filename);
        $filename=str_replace(")","_",$filename);
        $filename=ereg_replace("[^a-z,A-Z,0-9,_,.]","_",$filename);
        $uploadfile = "$dir$filename";
        $this->mkdirr($dir);
        if (move_uploaded_file($file['tmp_name'], $uploadfile)) 
        {
            return $filename;
        }
        return false;
    }
    ///}}}
    //{{{ Add file
    function addfile($filename,$fname,$access,$dir,$parrentdir,$type,$owner,$size)
    {
        $this->run_query( "UPDATE `lastupdate` SET `lastupdate` = NOW( ) WHERE 1;");
        $result=$this->run_query("insert into files ( filename,name,access,dir,parrentdir,type,owner,size,date ) VALUES ('$filename','$fname','$access','$dir','$parrentdir','$type','$owner','$size', now());");
        return $result->lastid;
    }
    //}}}
    //{{{save file
    function savefile($access, $dir, $parrentdir,$fname, $newid)
    {
        $this->run_query("UPDATE files set access='$access', dir='$dir', parrentdir='$parrentdir', name='$fname' where id=$newid");
    }
    //}}}
    //{{{ Delete file
    function deletefile($id)
    {
        $filepath=$this->filepath;
        $this->rmdirr("$filepath/$id");
        $this->run_query("delete from `files` where id = $id");
    }
    //}}}
    
    //{{{ Send mail
    function sendMail($to, $subject, $body, $from)
    {
        $body = str_replace("<br />", "\n",$body);
        $body = str_replace("\n.", "\n..",$body);
        if ( $this->isemail($to) and $this->isemail($from))
        {
            return mail($to,$subject, $body, "From: $from");
        }
        else
        {
            return false;
        }
    }
    //}}}
    //{{{send html mail
    function sendHtmlMail($to, $subject, $from, $body_simple, $body_plain, $body_html )
    {
        $body = str_replace("<br />", "\n",$body);
        $body = str_replace("\n.", "\n..",$body);

        $boundary = md5(uniqid(time()));
        $headers  = 'From: ' . $from . "\n";
        $headers .= 'To: ' . $to . "\n";
        $headers .= 'Return-Path: ' . $from . "\n";
        $headers .= 'MIME-Version: 1.0' ."\n";
        if ( $body_simple != "")
        {
            $headers .= 'Content-Type: multipart/alternative; boundary="' . $boundary . '"' . "\n\n";
            $headers .= $body_simple . "\n";
            $headers .= '--' . $boundary . "\n";
        }
        if ( $body_plain != "")
        {
            $headers .= 'Content-Type: text/plain; charset=ISO-8859-1' ."\n";
            $headers .= 'Content-Transfer-Encoding: 8bit'. "\n\n";
            $headers .= $body_plain . "\n";
            $headers .= '--' . $boundary . "\n";
        }
        if ( $body_html != "")
        {

            $headers .= 'Content-Type: text/HTML; charset=ISO-8859-1' ."\n";
            $headers .= 'Content-Transfer-Encoding: 8bit'. "\n\n";
            $headers .= $body_html . "\n";
            $headers .= '--' . $boundary . "--\n";
        }
        if ( $this->isemail($to) and $this->isemail($from))
        {
            return mail('', $subject,'', $headers);
        }
        else
        {
            return false;
        }
    }
    //}}}

//{{{ Search
    function search( $search, $access, $start, $nr)
    {
        $search = str_replace("*","%",$search);
        return $this->run_query ("select UNIX_TIMESTAMP(n.date) as date, n.owner,n.access, n.id, n.headline, n.views, n.img, n.data, n.data2,length(n.data2) as length, u.name, u.role, n.order, n.type, n.votes, n.rating, c.name as category,c.id as catid, (select count(c.toid)  from comment c where c.toid=n.id and c.type = '1') as comments from news n, user u, category c where  n.type != '6' and  n.type != '8'  and c.id = n.category and n.owner = u.id and (n.headline like '%$search%' or n.data like '%$search%' or n.img like '%$search%' or n.data2 like '%$search%' )  and n.access  <= '$access' order by n.order, n.id desc limit $start,$nr");
    }
    //}}}
    //{{{ Search Search nr
    function searchnr( $search, $access)
    {
        $search = str_replace("*","%",$search);
        return $this->run_query ("select count(id) as nr  from news n where n.type != '6' and n.type != '8'and (n.headline like '%$search%' or n.data like '%$search%' or n.img like '%$search%' or n.data2 like '%$search%' )  and n.access  <= '$access'");
    }
    //}}}
    //{{{ Get menu
    function getmenu( $access, $userid )
    {
        return $this->run_query ( "select * from menu m where m.parent = 0  and ( m.access <= '$access' or ( m.owner = '$userid' and m.owner != '0' )) order by m.access, m.order" );
    }
    //}}}
    //{{{ Get last update
    function getlastupdate()
    {
        $updated = $this->run_query ( "SELECT UNIX_TIMESTAMP(lastupdate) as date FROM `lastupdate` LIMIT 1" );
        if (isset( $updated->records['0']['date']))
        {
            return $updated->records['0']['date'];
        }
        else
        {
            return NULL;
        }
    }
    //}}}
    //{{{ Get all menu items
    function getallmenu( )
    {
        return $this->run_query ( "select * from menu m order by m.parent, m.access, m.order" );
    }
    //}}}
    //{{{ Get categories
    function getCategories($role)
    {
        return $this->run_query ( "select distinct c.* from category c, news n where n.type <= '2' and n.category = c.id and n.access <= '$role' order by c.name");
    }
    //}}}
    //{{{ Get Referer
    function getReferer()
    {
        return $this->run_query ("SELECT * from referer ORDER BY nr DESC ");
    }
    //}}}
    //{{{ Get All Categories
    function getAllCategories()
    {
        return $this->run_query ( "select * from category ");
    }
    //}}}
    //{{{ Add Category
    function addCategory($name)
    {
        return $this->run_query ( "INSERT INTO `category` ( `access` , `name` ) VALUES ('0', '$name');");
    }
    //}}}
    //{{{ Get news
    function getnews( $access, $type, $start, $nr)
    {
        return $this->run_query ( "select UNIX_TIMESTAMP(n.date) as date, n.owner,n.access, n.id, n.headline, n.views, n.img, n.data,n.data2 , length(data2) as length, u.name, u.role, n.order, n.type, n.votes, n.rating, c.name as category,c.id as catid, (select count(c.toid)  from comment c where c.toid=n.id and c.type = '1') as comments from news n, user u, category c where  c.id = n.category and n.type = '$type' and n.owner = u.id and n.access  <= '$access' order by n.order, n.id desc limit $start,$nr");
    }
    //}}}
    //{{{ Get abbr news
    function getabbrnews( $start, $nr)
    {
        return $this->run_query ( "select n.id, n.data, n.data2 from news n where 1 limit $start,$nr");
    }
    //}}}
    //{{{ Get abbr comments
    function getabbrcomments( $start, $nr)
    {
        return $this->run_query ( "select c.id, c.data from comment c where 1 limit $start,$nr");
    }
    //}}}
    //{{{ Get nr abbr news 
    function getnrabbrnews( )
    {
        $news = $this->run_query ( "select count(n.id) as nr from news n where 1");
        return $news->records['0']['nr'];
    }
    //}}}
    //{{{ Get nr abbr comments
    function getnrabbrcomments( )
    {
        $news = $this->run_query ( "select count(n.id) as nr from comment n where 1");
        return $news->records['0']['nr'];
    }
    //}}}
    //{{{ Get top news
    function gettopnews( $access, $start, $nr)
    {
            return $this->run_query ( "select UNIX_TIMESTAMP(n.date) as date, n.rating / n.votes as rate, n.owner,n.access, n.id, n.headline, n.views, n.img, n.data,n.data2, length(data2) as length, u.name, u.role, n.order, n.type, n.votes, n.rating, c.name as category,c.id as catid, (select count(c.toid)  from comment c where c.toid=n.id and c.type = '1') as comments from news n, user u, category c where n.type <= 2 and c.id = n.category and n.owner = u.id and n.access  <= '$access' order by rate desc, n.votes desc, n.views desc, n.id  desc limit $start,$nr");
    }
    //}}}
    //{{{ Get nr top news
    function getnrtopnews( $access )
    {
            return $this->run_query ( "select count(n.id) as nr from news n where n.type <= 2 and n.access  <= '$access'");
    }
    //}}}
    //{{{ Get top view news
    function gettopviewnews( $access, $start, $nr)
    {
        return $this->run_query ( "select UNIX_TIMESTAMP(n.date) as date, n.rating / n.votes as rate, n.owner,n.access, n.id, n.headline, n.views, n.img, n.data2, n.data,length(data2) as length, u.name, u.role, n.order, n.type, n.votes, n.rating, c.name as category,c.id as catid, (select count(c.toid)  from comment c where c.toid=n.id and c.type = '1') as comments from news n, user u, category c where n.type <= 2 and c.id = n.category and n.owner = u.id and n.access  <= '$access'  order by n.views desc, rate desc, n.votes desc limit $start,$nr");
    }
    //}}}
    //{{{ Get top comment news
    function gettopcommentnews( $access, $start, $nr)
    {
        return $this->run_query ( "select UNIX_TIMESTAMP(n.date) as date, n.owner,n.access, n.id, n.headline, n.views, n.img, n.data,n.data2,length(data2) as length, u.name, u.role, n.order, n.type,  n.votes, n.rating, c.name as category,c.id as catid, (select count(c.toid)  from comment c where c.toid=n.id and c.type = '1') as comments from news n, user u, category c where  n.type <= 2 and c.id = n.category and n.owner = u.id and n.access <= '$access' order by comments desc, n.views desc, n.id desc limit $start,$nr");
    }
    //}}}
    //{{{ Get cat news
    function getcatnews( $access, $start, $nr, $cat)
    {
        return $this->run_query ( "select UNIX_TIMESTAMP(n.date) as date, n.owner,n.access, n.id, n.headline, n.views, n.img,n.data,n.data2,length(n.data2) as length, u.name, u.role, n.order, n.type, n.votes, n.rating, c.name as category, c.id as catid, (select count(c.toid)  from comment c where c.toid=n.id and c.type = '1') as comments from news n, user u, category c where n.type <= 2 and c.id='$cat' and c.id = n.category and n.owner = u.id and n.access  <= '$access' order by n.order, n.id desc limit $start,$nr");
    }
    //}}}
    //{{{ Get news rss
    function getnewsrss( $access, $start, $nr)
    {
        return $this->run_query ( "select UNIX_TIMESTAMP(n.date) as date, n.id, n.headline, n.views, n.data , u.name from news n, user u where n.owner = u.id and n.type <= 2 and n.access  <= '$access' order by n.id desc limit $start,$nr");
    }
    //}}}
    //{{{ Get nr news
    function getnrnews( $access, $type )
    {
        return $this->run_query ( "select count(n.id) as nr from news n where n.type = '$type' and n.access  <= '$access'");
    }
    //}}}
    //{{{ Get cat nr news
    function getcatnrnews( $access, $cat )
    {
        return $this->run_query ( "select count(id) as nr from news n where n.type <= '2' and n.category = '$cat' and n.access  <= '$access'");
    }
    //}}}
    //{{{ Get user news
    function getusernews( $id, $access, $type, $start, $nr)
    {
        return $this->run_query ( "select UNIX_TIMESTAMP(n.date) as date, n.owner,n.access, n.id, n.headline, n.views, n.img, n.data,n.data2, length(data2) as length, u.name, u.role, n.order, n.type, n.votes, n.rating, c.name as category, (select count(c.toid) from comment c where c.toid=n.id and c.type = 1) as comments from news n, user u,category c where n.type = '$type' and c.id = n.category and n.owner = u.id and n.access  <= '$access' and owner = '$id' order by n.order, n.id desc limit $start,$nr");
    }
    //}}}
    //{{{ Get nr user news
    function getnrusernews($id, $access, $type )
    {
        return $this->run_query ( "select count(id) as nr from news n where n.type = '$type' and n.access  <= '$access'  and owner = '$id' ");
    }
    //}}}
    //{{{ Login
    function login($user, $passwd, $count )
    {
        $userdata=$this->run_query("select * from user where user = '$user' and passwd = '$passwd'");
        if ( $userdata->rows == 1 )
        {
            if($this->usedbsessions){$this->run_query("update sessions set user ='".$userdata->records['0']['id']."' where session_id = '".session_id()."'");}
            if ($count)
            {
                $this->run_query("update user set lastip=ip, lastlogin=login where user = '$user' and passwd = '$passwd'");
                $this->run_query("update user set ip='$_SERVER[REMOTE_ADDR]', login=NOW(), nrlogins = nrlogins + 1 where user = '$user' and passwd = '$passwd'");
            }
        }

        return $userdata;
    }
    //}}}
    //{{{ Get user list
    function getuserlist( $start , $nr, $sort="name")
    {
        $userdata=$this->run_query("select u.id,u.nr , u.name, u.email, u.data, u.role , u.img, u.nrlogins,  u.login from user u where u.id != '0' order by u.$sort limit $start,$nr");
        return $userdata;
    }
    //}}}
    //{{{ Get nr user list
    function getnruserlist()
    {
        $userdata=$this->run_query("select count(id) as nr from user where id != '0'");
        return $userdata;
    }
    //}}}
    //{{{ Get user
    function getuser($id)
    {
        $userdata=$this->run_query("select * from user u where u.id = '$id' " );
        return $userdata;
    }
    //}}}
    //{{{ Get edit news
    function geteditnews( $id )
    {
        $news = $this->run_query ( "select * from news where `id` = '$id'" );
        return $news;
    }
    //}}}
    //{{{ Get init news
    function getinitnews( $access)
    {
        $news = $this->run_query ( "select UNIX_TIMESTAMP(n.date) as date, n.owner,n.access, n.id, n.headline, n.views, n.img, n.data,n.data2, length(data2) as length, u.name, u.role, n.order, n.type , n.votes, n.rating, c.name as category,c.id as catid, (select count(c.toid)  from comment c where c.toid=n.id and c.type = '1') as comments from news n, user u, category c where  c.id = n.category and n.owner = u.id and n.type = 4 and n.access <= $access order by n.access desc limit 1");
        return $news;
    }
    //}}}
    //{{{ Get menu  news
    function getmenunews($role )
    {
        $news = $this->run_query ( "select UNIX_TIMESTAMP(n.date) as date, n.owner,n.access, n.id, n.headline, n.views, n.img, n.data, length(data2) as length, u.name, u.role, n.order, n.type, n.votes, n.rating, c.name as category,c.id as catid, (select count(c.toid)  from comment c where c.toid=n.id and c.type = '1') as comments from news n, user u, category c where  c.id = n.category and n.owner = u.id and n.type = 3 and n.access <= $role");
        return $news;
    }
    //}}}
    //{{{ Get menu  news list
    function getmenunewslist($role )
    {
        $news = $this->run_query ( "select n.id, n.headline from news n where  n.type = 3 and n.access <= $role order by n.headline");
        return $news;
    }
    //}}}
    //{{{ Del news
    function delnews( $id, $role )
    {
        if ( "$role" == "4" )
        {
            $this->run_query ( "delete from news where `id` = '$id'" );
            $this->run_query ( "delete from comment where `toid` = '$id'" );
            $thumbdir="./thumb/news/$id/";
            $smalldir="./small/news/$id/";
            $uploaddir="./img/news/$id/";
            if(is_dir($thumbdir))
            {
                $this->rmdirr($thumbdir);
            }
            if(is_dir($smalldir))
            {
                $this->rmdirr($smalldir);
            }
            if(is_dir($uploaddir))
            {
                $this->rmdirr($uploaddir);
            }

        }
    }
    //}}}
    //{{{ Rm news
    function rmnews( $id, $role )
    {       
        if ( "$role" >= "1" )
        {
            $this->run_query ( "update news set type = '8' where `id` = '$id'" );
        }

    }
    ///}}}
    //{{{ Vote
    function vote( $id, $value)
    {
        $this->run_query ( "update news set votes=votes + '1', rating = rating + '$value', date =  date  where `id` = '$id'");
    }
    //}}}
    //{{{ Del user
    function deluser( $id )
    {
        $this->run_query ( "delete from user where `id` = '$id'" );
        $thumbdir="./thumb/user/$id/";
        $smalldir="./small/user/$id/";
        $uploaddir="./img/user/$id/";
        if(is_dir($thumbdir))
        {
            $this->rmdirr($thumbdir);
        }
        if(is_dir($smalldir))
        {
            $this->rmdirr($smalldir);
        }
        if(is_dir($uploaddir))
        {
            $this->rmdirr($uploaddir);
        }
    }
    //}}}
    //{{{ Rm user
    function rmuser( $id )
    {       
        $this->run_query ( "update user set role = '0' where `id` = '$id'" );
    }
    //}}}
    //{{{ Add referer
    function addreferer( $referer )
    {
        $r=$this->run_query ( "select * from referer where referer = '$referer'" );
        if ( "" != "$referer" )
        {
            if ( $r->rows != 0)
            {
                $this->run_query ("update referer set nr = nr + 1 where id = '".$r->records[0]['id']."'");
            }
            else
            {
                $this->run_query ("insert into referer ( `id` , `referer` , `nr` ) VALUES ( '', '$referer', '1' )");
            }
        }
        $this->run_query ("delete from referer where referer like '%username%' or  referer like '%uname%'  or referer like '%passwd%' or referer like '%password%';");
    }
    //}}}
    //{{{ Save news
    function savenews( $id, $access, $headline, $img, $data, $data2, $order, $category, $type )
    {
        if ( "$img" == "" )
        {
            $this->run_query( "UPDATE `lastupdate` SET `lastupdate` = NOW( ) WHERE 1;");
            $this->run_query( "update `news` set `access` = '$access' , `category`='$category', `order` = '$order', `type` = '$type' , `headline` = '$headline' , `data` = '$data' , `data2` = '$data2', date = date where `id` = '$id'"  );
        }
        elseif ( "$img" == "del" )
        {
            $this->run_query( "UPDATE `lastupdate` SET `lastupdate` = NOW( ) WHERE 1;");
            $this->run_query( "update `news` set `access` = '$access' , `category`='$category', `order` = '$order' , `type` = '$type' ,`headline` = '$headline' , `img` = '' , `data` = '$data' , `data2` = '$data2' , date = date where `id` = '$id'"  );
        }
        else
        {
            $this->run_query( "UPDATE `lastupdate` SET `lastupdate` = NOW( ) WHERE 1;");
            $this->run_query( "update `news` set `access` = '$access' , `category`='$category', `order` = '$order' , `type` = '$type' ,`headline` = '$headline' , `img` = '$img' , `data` = '$data' , `data2` = '$data2' , date = date where `id` = '$id'"  );
        }
    }
    //}}}
    //{{{ removeoldinit 
    function removeoldinit( $access )
    {
        $this->run_query( "update `news` set `type` = '8' , date = date where `type` = '4' and `access` = '$access'"  );
    }
    //}}}
    //{{{ Save abbr news
    function saveabbrnews( $id, $data, $data2 )
    {
        $this->run_query( "update `news` set `data` = '$data' , `data2` = '$data2', date = date where `id` = '$id'"  );
    }
    //}}}
    //{{{ Save abbr comments
    function saveabbrcomment( $id, $data )
    {
        $this->run_query( "update `comment` set `data` = '$data', date = date where `id` = '$id'"  );
    }
    //}}}
    //{{{ Increase news views
    function incresenewsviews( $id )
    {
        if ($this->isPublicIp($_SERVER['REMOTE_ADDR']))
        {
            if (!isset($_SESSION['views'][$id]))
            {
                if ( isset($_SESSION['role']))
                {
                    if( $_SESSION['role'] > 2 )
                    {
                        return null;
                    }
                
                }
                if ( !$this->isbot and $this->havecookie )
                {
                    $this->run_query( "update `news` set `views` = views + 1 , date = date where `id` = '$id'"  );
                    $_SESSION['views'][$id]=1;
                }
            }
        }
    }
    //}}}
    //{{{ Add news
    function addnews( $access, $owner, $headline, $img, $data,$data2, $order, $category, $type )
    {
        $this->run_query( "UPDATE `lastupdate` SET `lastupdate` = NOW( ) WHERE 1;");
        return $this->run_query( "INSERT INTO `news` ( `id` ,`category`, `access` , `owner` , `order`,`type` , `date` , `headline` , `img` , `data` , `data2` ) VALUES ( '','$category', '$access', '$owner', '$order','$type',  NOW( ) , '$headline', '$img', '$data' , '$data2')" );
    }
    //}}}
    //{{{ Add comment
    function addcomment( $userid, $type, $toid, $headline, $data, $anonname, $anonemail,$anonhomepage )
    {	
        $this->run_query( "INSERT INTO `comment` ( `id` , `from` , `type` , `toid` , `headline` , `data`, `anonname` , `anonemail`, `anonhomepage` ) VALUES ( '', '$userid', '$type', '$toid', '$headline', '$data', '$anonname', '$anonemail', '$anonhomepage')");
    }
    //}}}
    //{{{ save abbr
    function saveabbr( $id, $type, $word , $title, $data )
    {	
        $this->run_query( "update `abbr` set `type`='$type' , `word`='$word' , `title`='$title' , `data`='$data' where id = $id");
    }
    //}}}
    //{{{ save menu
    function savemenu( $id, $access, $order, $parent )
    {	
        $this->run_query( "update `menu` set `access`='$access', `order` = '$order', parent = '$parent' where id = $id");
    }
    //}}}
    //{{{ add abbr
    function addabbr( $type, $word , $title, $data )
    {	
        $this->run_query( "INSERT INTO `abbr` ( `type` , `word` , `title` , `data` ) VALUES ( '$type', '$word', '$title', '$data' )");
    }
    //}}}
    //{{{ del abbr
    function delabbr( $id )
    {	
        $this->run_query( "delete from `abbr` where id = $id");
    }
    //}}}
    //{{{ get abbr
    function getabbr( $order)
    {	
        if ( $order != "id" and $order != "type" and $order != "word" and $order != "title" and $order != "data" )
        {
            $order = "id";
        }
        return $this->run_query( "select * from `abbr` where 1 order by $order");
    }
    //}}}
    //{{{ Save comment
    function savecomment( $userid, $role, $id, $headline, $data, $anonname, $anonemail,$anonhomepage)
    {
        $this->run_query( "update `comment` set headline='$headline', date=date, data='$data', anonname='$anonname', anonemail='$anonemail', anonhomepage='$anonhomepage' where id='$id'");
    } 
    //}}}
    //{{{ Get comment
    function getcomment( $userid, $role, $commentid )
    {
        if ( $role >= 3 )
        {
            return $this->run_query( "select c.*, u.role from comment c left join user u on ( c.from = u.id )  where c.id = '$commentid'" );
        }
        else
        {
            return $this->run_query( "select c.*, u.role from comment c left join user u on ( c.from = u.id )  where c.id = '$commentid' and `from` = '$userid'" );
        }
    }
    //}}}
    //{{{ Rm comment
    function rmcomment( $userid, $role, $commentid )
    {
        if ( $role >= 3 )
        {
            $this->run_query( "update `comment` set `type` = '100' where id = '$commentid'" );
        }
        else
        {
            $this->run_query( "update `comment` set `type` = '100' where id = '$commentid' and `from` = '$userid'" );
        }
    }
    //}}}
    //{{{ Delete comment
    function deletecomment( $commentid)
    {
        $this->run_query( "delete from `comment` where id = $commentid" );
    }
    //}}}
    //{{{ Add user
    function adduser( $role,$nr,$theme, $name,$user,$email,$data, $pwd, $img, $lang ,$homepage)
    {
        $r=$this->run_query("select id from `user` where `user` = '$user'" );
        $result="";
        if ( "$r->rows" == "0" )
        {
            $result=$this->run_query( "INSERT INTO `user` ( `id` , `role`, `nr`, `name` , `passwd` , `user` , `email` , `img` , `data`, `lang`, `theme`,`homepage`  ) VALUES ( '', '$role','$nr' , '$name', '$pwd', '$user', '$email', '$img', '$data', '$lang', '$theme', '$homepage' )" );
        }
        else
        {
            print "Select an other username!";
        }
        return $result;
    }
    //}}}
    //{{{ Get messages
    function getmessages($userid, $start, $nr, $status)
    {
        return $this->run_query( "SELECT *, (select u.name from user u where m.from = u.id) as mfrom , (select u.name from user u where m.to = u.id) as mto FROM messages m WHERE ( m.from = '$userid' OR m.to = '$userid') and status='$status' order by m.threadid, m.date" );
    }
    //}}}
    //{{{ Save user 
    function saveuser($id, $role,$nr,$theme, $name,$email,$data, $pwd, $img, $lang, $homepage )
    {

        if ( "$pwd" != "" )
        {
            if ( "$img" == "" )
            {
                $this->run_query( "update `user` set `role` = '$role' ,`nr` = '$nr',`theme` = '$theme', `name` = '$name', `passwd` = '$pwd' , `email` = '$email' , `data` = '$data' , `lang` = '$lang', `homepage` = '$homepage' where id = '$id'" );
            }
            elseif ( "$img" == "del" )
            {
                $this->run_query( "update `user` set `role` = '$role' ,`nr` = '$nr',`theme` = '$theme', `name` = '$name', `passwd` = '$pwd' , `email` = '$email' , `img` = '', `data` = '$data'  , `lang` = '$lang', `homepage` = '$homepage' where id = '$id'" );
            }
            else
            {
                $this->run_query( "update `user` set `role` = '$role' ,`nr` = '$nr',`theme` = '$theme', `name` = '$name', `passwd` = '$pwd' , `email` = '$email' , `img` = '$img', `data` = '$data'  , `lang` = '$lang', `homepage` = '$homepage' where id = '$id'" );
            }
        }
        else
        {
            if ( "$img" == "" )
            {
                $this->run_query( "update `user` set `role` = '$role' ,`nr` = '$nr',`theme` = '$theme', `name` = '$name', `email` = '$email' , `data` = '$data'  , `lang` = '$lang', `homepage` = '$homepage' where id = '$id'" );
            }
            elseif ( "$img" == "del" )
            {
                $this->run_query( "update `user` set `role` = '$role' ,`nr` = '$nr',`theme` = '$theme', `name` = '$name', `email` = '$email' , `img` = '', `data` = '$data'  , `lang` = '$lang', `homepage` = '$homepage' where id = '$id'" );
            }
            else
            {
                $this->run_query( "update `user` set `role` = '$role' , `name` = '$name', `email` = '$email' , `img` = '$img', `data` = '$data'  , `lang` = '$lang', `homepage` = '$homepage' where id = '$id'" );
            }
        }
    }
    //}}}
    //{{{ Get file info
    function getfileinfo($id)
    {
        $this->run_query( "UPDATE files set hits=hits + '1', date=date where id='$id' ");
        return $this->run_query( "SELECT * FROM files where id='$id'");
    }
    //}}}
    //{{{ Get file edit
    function getfileedit($id)
    {
        return $this->run_query( "SELECT * FROM files where id='$id'");
    }
    //}}}
    //{{{ Get downloads
    function getdownloads($role,$dir)
    {
        return $this->run_query( "SELECT f.*, u.name as uname FROM files f left join user u on ( f.owner = u.id ) where dir = '$dir' and access <= '$role' order by date desc");
    }
    //}}}
    //{{{ Get subdirs
    function getsubdirs($role,$dir)
    {
        return $this->run_query( "SELECT distinct(dir) FROM files where parrentdir = '$dir' and dir != '$dir' and access <= '$role'");
    }
    //}}}
    //{{{ Get latest news
    function getlatestnews($role, $nr)
    {
        return $this->run_query("select n.id, n.headline, UNIX_TIMESTAMP(n.date) as date from news n where  n.access <= $role and n.type < 4 order by n.id desc limit $nr");
    }
    //}}}
    //{{{ Get latest comments
    function getlatestcomments($role, $nr)
    {
        return $this->run_query("select n.id, c.from , c.headline, UNIX_TIMESTAMP(c.date) as date,  u.name, c.anonname, c.anonemail from news n, comment c left join user u on ( c.from = u.id ) where  c.toid != 0 and n.id = c.toid and n.access <= $role and n.type < 4 and c.type < 4 order by c.id desc limit $nr");
    }
    //}}}
    //{{{ Get latest guestbook
    function getlatestguestbook($role, $nr)
    {
        return $this->run_query("select c.headline, c.from,UNIX_TIMESTAMP(c.date) as date, u.name, c.anonname, c.anonemail from comment c left join user u on ( c.from = u.id ) where  c.toid = 0 and c.type < 4 order by c.id desc limit $nr");
    }
    //}}}
//{{{ update browser statistics
function updatebrowserstat($bstatplatform,$bstatbrowser,$bstatversion,$bstatcrawler)
{
    $year=date("Y");
    $month=date("n");
    $found=$this->run_query("select id from browsers where platform = '$bstatplatform' and browser= '$bstatbrowser' and version = '$bstatversion' and crawler = '$bstatcrawler' and year = '$year' and month = '$month'");
    if ($found->rows != 0 )
    {
        $this->run_query("update browsers set hits = hits + 1 where id = '".$found->records['0']['id']."'");
    }
    else
    {
        $this->run_query("insert into browsers ( hits, year, month, platform, browser, version, crawler ) values ('1','$year','$month','$bstatplatform','$bstatbrowser','$bstatversion','$bstatcrawler')");

    }
}
//}}}
//{{{ Get browser statistic
function getbrowserstat($crawler)
{
    if ($crawler == 0 ){
        return $this->run_query("select year, month, sum(hits) as hits, browser, version from browsers where crawler = 0 group by browser,version order by year,month,hits desc");
    }
    elseif ($crawler == 1)
    {
        return $this->run_query("select * from browsers where crawler = 1 order by year,month,hits desc");
    }
    elseif($crawler == 2)
    {
        return $this->run_query("select * from browsers where order by year,month,hits desc");
    }
    elseif($crawler == 3)
    {
        return $this->run_query("select year, month, sum(hits) as hits, platform from browsers where platform != '' group by year,month, hits order by year,month,hits desc");
    }
}
//}}}
//{{{ Optimize table
    function optimizetables( )
    {
        $result=$this->run_query("select * from `category` c where c.id not in (SELECT distinct(c.id) FROM `category` c, news n WHERE c.id = n.category)");
        foreach ($result->records as $cat ) 
        {
            $this->run_query("delete from category where id = $cat[id]");
            print "Not used category <b>$cat[name]</b> deleted <br />";
        }
        $d=dir("img/user");
        while($entry = $d->read())
        {
            if (is_numeric($entry))
            {
                $result=$this->run_query("select id from user where id = $entry");
                if ( !isset($result->records['0']['id']) )
                {
                    print "Userid <b>$entry</b> not found dir deleted<br />";
                    $thumbdir="./thumb/user/$entry/";
                    $smalldir="./small/user/$entry/";
                    $uploaddir="./img/user/$entry/";
                    if(is_dir($thumbdir))
                    {
                        $this->rmdirr($thumbdir);
                    }
                    if(is_dir($smalldir))
                    {
                        $this->rmdirr($smalldir);
                    }
                    if(is_dir($uploaddir))
                    {
                        $this->rmdirr($uploaddir);
                    }
                }
            }
        }
        $d=dir("img/news");
        while($entry = $d->read())
        {
            if (is_numeric($entry))
            {
                $result=$this->run_query("select id from news where id = $entry");
                if ( !isset($result->records['0']['id']))
                {
                    print "Newsid <b>$entry</b> not found dir deleted<br />";
                    $thumbdir="./thumb/news/$entry/";
                    $smalldir="./small/news/$entry/";
                    $uploaddir="./img/news/$entry/";
                    if(is_dir($thumbdir))
                    {
                        $this->rmdirr($thumbdir);
                    }
                    if(is_dir($smalldir))
                    {
                        $this->rmdirr($smalldir);
                    }
                    if(is_dir($uploaddir))
                    {
                        $this->rmdirr($uploaddir);
                    }

                }
            }
        }
        $this->run_query("OPTIMIZE TABLE `abbr` , `category` , `comment` , `menu` , `news` , `referer` , `user`");
        print "Tables optimized<br />";
    }
    //}}}

//{{{ Run query
    function run_query( $sql ) 
    {
        if ( $this->debug == "on")
        {
            $stimer = explode( ' ', microtime() );
            $stimer = $stimer[1] + $stimer[0];
            $this->sqlstatments.="$sql";
        }
        $db = $this->db;
        $t = new Table();
        $rows=0;
        $insertid="0";
        if( $db )
        { 
            $result = mysql_query( $sql, $db );

            if( $result )
            {
                if( preg_match( "/^SELECT|^SHOW/i", $sql ) )
                {
                    $rows = mysql_num_rows( $result ); 
                    for( $r = 0; $r < $rows; $r++ )
                    {
                        $re = mysql_fetch_assoc( $result );
                        $t->add_record(  $re );
                    }
                }
                if (preg_match( "/^INSERT/i", $sql ))
                {
                    $insertid=mysql_insert_id();
                }
            }
            elseif ($this->debug == "on" )
            {
                $this->sqlstatments.="*** Error  ***\n";
                $this->sqlstatments.=mysql_errno($db); 
                $this->sqlstatments.=mysql_error($db) . "\n\n";
            }
        }
        else
        {
            $t = false;
        }
        $t->setnrrows( $rows  );
        $t->setlastid( $insertid );
        if ( $this->debug == "on")
        {
            $etimer = explode( ' ', microtime() );
            $etimer = $etimer[1] + $etimer[0];
            $this->sqlstatments.="\n".($etimer-$stimer)." ".$this->text['seconds']."";
            $this->sqlstatments.=", $rows rows\n";
        }
        return $t;
    }
    //}}}
//{{{ Cloce db
function closedb()
{
    mysql_close($this->db);
}
//}}}
}
//{{{ unichr
function unichr($dec) {
    if ($dec <= 255) {
        $utf = chr($dec);
    } else if ($dec < 2048) {
        $utf = chr(192 + (($dec - ($dec % 64)) / 64));
        $utf .= chr(128 + ($dec % 64));
    } else {
        $utf = chr(224 + (($dec - ($dec % 4096)) / 4096));
        $utf .= chr(128 + ((($dec % 4096) - ($dec % 64)) / 64));
        $utf .= chr(128 + ($dec % 64));
    }
    return $utf;
}
//}}}
?>
