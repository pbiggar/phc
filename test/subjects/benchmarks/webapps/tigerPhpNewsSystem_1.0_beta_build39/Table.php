<?
/*
 * This software is part of the Tiger php news system
 * 
 * This software comes with ABSOLUTELY NO WARRANTY. For details, see
 * the enclosed file COPYING for license information (GPL). If you
 * did not receive this file, see http://www.gnu.org/licenses/gpl.txt.
 * 
 */

class Table
{
    //{{{ Init
    var $records;
    var $rows;
    var $lastid;
    //}}}
    //{{{  Table
    function Table()
    {
        $this->records = array();
    }
    //}}}
    //{{{ add_record
    function add_record( $record )
    {    
        array_push( $this->records, $record );
    }
    //}}}
    //{{{count
    function count()
    {
        return count( $this->records );
    }
    //}}}
    //{{{ rox
    function row( $record_number )
    {
        return $this->records[$record_number];
    }
    //}}}
    //{{{ column
    function column( $field_name )
    {
        $c = array();

        foreach( $this->records as $r )
        {
            array_push( $c, $r[$field_name] );
        }

        return $c;
    }
    //}}}
    //{{{ setnrrows
    function setnrrows( $rows )
    {
        $this->rows=$rows;
    }
    //}}}
    //{{{ setlastid
    function setlastid( $id )
    {
        $this->lastid=$id;
    }
    //}}}
    //{{{ cell
    function cell( $field_name, $record_number )
    {
        if( ! $record_number )
        {
            $record_number = 0;
        }

        return $this->records[$record_number][$field_name];
    }
    //}}}
}
?>
