<?php


function xmlfile($num) {
    return $_ENV["PCC_HOME"] . "/benchmarks/data/xml-data-{$num}.xml";
}


class xmlparser {

    function readfile($num) {
        $this->currentFile = xmlfile($num);
            
        if (!($fp = fopen($this->currentFile, "r"))) {
            die("could not open XML input");
        }
    
        $this->contentBuffer = NULL;
        while ($data = fread($fp, 4096)) {
                $this->contentBuffer .= $data;
        }

        fclose($fp);
    }

    function runtest($num, $i) {

        $this->readfile($num);
        echo "parsing xml data file $this->currentFile iteration $i\n";
        
        $xml_parser = xml_parser_create();
        xml_parser_set_option($xml_parser, XML_OPTION_CASE_FOLDING, 1);
    
        xml_set_object($xml_parser, $this);
        xml_set_element_handler($xml_parser, 'startElement', 'endElement');
        xml_set_character_data_handler($xml_parser, 'cDataHandler');
    
        xml_set_external_entity_ref_handler($xml_parser, 'externalEntityRefHandler');
        xml_set_processing_instruction_handler($xml_parser, 'piHandler');
        xml_set_unparsed_entity_decl_handler($xml_parser, 'unparsedEntityDeclHandler');
        xml_set_notation_decl_handler($xml_parser, 'entityDeclHandler');
        xml_set_default_handler($xml_parser, 'defaultHandler');
    
        if (!xml_parse($xml_parser, $this->contentBuffer, true)) {
            ($this->currentFile != '') ? $inFile = "in file $this->currentFile" : $inFile = '';
            $this->fatalErrorPage(sprintf(get_class($this).": XML error: %s at line %d $inFile",
                                          xml_error_string(xml_get_error_code($xml_parser)),
                                          xml_get_current_line_number($xml_parser)));
        }
    
        xml_parser_free($xml_parser);
        
    }


    function startElement($parser, $name, $attrs) {
        print "start: $name\n";
    }
    
    function endElement($parser, $name) {
        print "end: $name\n";
    }


    function cDataHandler($parser, $data) {
        // virtual
        //print "cdatahandler\n";
    }

    function externalEntityRefHandler($parser, $openEntityNames, $base, $systemID, $publicID) {
        // virtual
        echo "externalentity\n";
    }

    function unparsedEntityDeclHandler($parser, $entityName, $base, $systemID, $publicID, $notationName) {
        // virtual
        echo "unparsedentity\n";
    }

    function entityDeclHandler($parser, $notationName, $base, $systemID, $publicID) {
        // virtual
        echo "entitydecl\n";
    }

    function piHandler($parser, $target, $data) {
        // virtual
        echo "pihandler\n";
    }

    function defaultHandler($parser, $data) {
        // virtual
        //echo "defaulthandler\n";
    }
    
}


$pObj =& new xmlparser();

$numTests = 2; // number of data files in ../data/
$numIterations = 20;

for ($i=0; $i<$numTests; $i++) {
    for ($t=0; $t<$numIterations; $t++) {
        $pObj->runtest($i, $t);
    }
}

?>