<? /* The Computer Language Shootout 
   http://shootout.alioth.debian.org/
   
   contributed by Isaac Gouy (PHP novice)
	  --range 0
*/

define("NW", 0);
define("NE", 1);
define("W", 2);
define("E", 3);
define("SW", 4);
define("SE", 5);
define("SIDES", 6);

class Cell {
   var $marked = false;
   var $next;
   function Cell() { for ($i=0; $i<SIDES; $i++) $this->next[$i] = null; }
   function mark(){ $this->marked = true; }
   function unmark(){ $this->marked = false; }
}

class BoardCell extends Cell {
   var $number;
   var $piece;

   function BoardCell($i) { 
      Cell::Cell();
      $this->number = $i; 
   }

   function isEmpty() { return $this->piece == null; }
   function setEmpty() { $this->piece = null; }

   function contiguousEmptyCells() { 
      if ((!$this->marked) && ($this->isEmpty())){
         $this->mark();
         $count = 1;
         for ($i = 0 ; $i < SIDES ; $i++){
            $neighbour = $this->next[$i];
            if ($neighbour != null && $neighbour->isEmpty())
               $count += $neighbour->contiguousEmptyCells();
         }
      } else {
         $count = 0;
      }
      return $count;
   }
}


define("BOARD_COLS", 5);
define("BOARD_ROWS", 10);
define("BOARD_SIZE", BOARD_COLS * BOARD_ROWS);

define("PIECES", 10);
define("PIECE_SIZE", 5);
define("PIECE_ROTATIONS", SIDES);
define("PIECE_FLIPS", 2);
define("PIECE_ORIENTATIONS", PIECE_ROTATIONS * PIECE_FLIPS); 

class Board {
   var $cells;
   var $cellsPieceWillFill;
   var $cellCount = 0;
   var $cache;
   var $noFit = array();

   function Board(){
      for ($i=0; $i<BOARD_SIZE; $i++) $this->cells[$i] = new BoardCell($i);
      $m = floor(BOARD_SIZE / BOARD_COLS) - 1;

      for ($i=0; $i<BOARD_SIZE; $i++){ 
         $row = floor($i / BOARD_COLS);
         $isFirst = $i % BOARD_COLS == 0;
         $isLast = ($i + 1) % BOARD_COLS == 0;
         $c = $this->cells[$i];

         if ($row % 2 == 1) {
            if (!$isLast) $c->next[NE] = $this->cells[$i-(BOARD_COLS-1)];
            $c->next[NW] = $this->cells[$i-BOARD_COLS]; 
            if ($row != $m) {
               if (!$isLast) $c->next[SE] = $this->cells[$i+(BOARD_COLS+1)];
               $c->next[SW] = $this->cells[$i+BOARD_COLS]; 
            }
         } else {
            if ($row != 0) {
               if (!$isFirst) $c->next[NW] = $this->cells[$i-(BOARD_COLS+1)];
               $c->next[NE] = $this->cells[$i-BOARD_COLS];
            }
            if ($row != $m) {
               if (!$isFirst) $c->next[SW] = $this->cells[$i+(BOARD_COLS-1)];
               $c->next[SE] = $this->cells[$i+BOARD_COLS];
            }
         }
         if (!$isFirst) $c->next[W] = $this->cells[$i-1];
         if (!$isLast) $c->next[E] = $this->cells[$i+1]; 
      }
      $this->initializeCache();
   }

   function initializeCache(){
      for ($i=0; $i<PIECES; $i++) 
         for ($j=0; $j<PIECE_ORIENTATIONS; $j++) 
            for ($k=0; $k<PIECE_SIZE; $k++) 
               for ($m=0; $m<BOARD_SIZE; $m++) 
                  $this->cache[$i][$j][$k][$m] = null;
   }

   function unmark(){
      for ($i=0; $i<BOARD_SIZE; $i++) $this->cells[$i]->unmark();
   }

   function firstEmptyCellIndex(){
      for ($i=0; $i<BOARD_SIZE; $i++) 
         if ($this->cells[$i]->isEmpty()) return $i;
      return -1;
   }

   function remove(&$p){
      for ($i=0; $i<BOARD_SIZE; $i++) 
         if ($this->cells[$i]->piece == $p) $this->cells[$i]->piece = null;
   }

   function find(&$p,&$c){
      if (($p != null) && ((!$p->marked) && ($c != null))){
         $this->cellsPieceWillFill[$this->cellCount] = $c;
         $this->cellCount++;
         $p->mark();  
         for ($i=0; $i<SIDES; $i++){ $this->find($p->next[$i],$c->next[$i]); } 
      }
   }

   function add($pieceIndex,$boardIndex,&$p){
      $a = $this->cache[$p->number][$p->orientation][$pieceIndex][$boardIndex];
      $this->cellCount = 0;
      $p->unmark();

      if ($a == null){
         $this->find($p->cell($pieceIndex), $this->cells[$boardIndex]);
         if ($this->cellCount != PIECE_SIZE){ 
            $this->cache[$p->number][$p->orientation]
               [$pieceIndex][$boardIndex] = $this->noFit;
            return false;
         }
         $a = array_slice($this->cellsPieceWillFill,0);
         $this->cache[$p->number][$p->orientation][$pieceIndex][$boardIndex] = $a;  
      } else { 
         if ($a == $this->noFit) return false;
      }
      for ($i=0; $i<PIECE_SIZE; $i++){ if (!$a[$i]->isEmpty()) return false; }
      for ($i=0; $i<PIECE_SIZE; $i++){ $a[$i]->piece = $p; }
      return true;
   }

   function asString(){
      $a = array();
      for ($i=0; $i<BOARD_SIZE; $i++) $a[] = $this->cells[$i]->piece->number;
      return implode("",$a);
   }

/*
   function printBoard(){
      print("cell\tNW NE W  E  SW SE\n");
      for ($i=0; $i<BOARD_SIZE; $i++){
         printf("%d \t", $i);
         for ($j=0; $j<SIDES; $j++){
            $c = $this->cells[$i]->next[$j];
            if ($c == null) print("-- "); else printf("%2d ", $c->number);
         }
         print("\n");
      }
      print("\n");
   }
*/
}


class PieceCell extends Cell {
   function PieceCell() { Cell::Cell(); }

   function flip() { 
      $swap = $this->next[NE];
      $this->next[NE] = $this->next[NW];
      $this->next[NW] = $swap;

      $swap = $this->next[E];
      $this->next[E] = $this->next[W];
      $this->next[W] = $swap;

      $swap = $this->next[SE];
      $this->next[SE] = $this->next[SW];
      $this->next[SW] = $swap;
   }

   function rotate() { 
      $swap = $this->next[E];
      $this->next[E] = $this->next[NE];
      $this->next[NE] = $this->next[NW];
      $this->next[NW] = $this->next[W];
      $this->next[W] = $this->next[SW];
      $this->next[SW] = $this->next[SE];
      $this->next[SE] = $swap;
   }
}


class Piece {
   var $number;
   var $orientation = 0;
   var $cache;

   function Piece($n) { 
      $this->number = $n;
      for ($k=0; $k<PIECE_ORIENTATIONS; $k++){

         for ($i=0; $i<PIECE_SIZE; $i++) 
            $this->cache[$k][$i] = new PieceCell();

         switch ($n){
            case 0: $this->make0( $this->cache[$k] ); break;
            case 1: $this->make1( $this->cache[$k] ); break;
            case 2: $this->make2( $this->cache[$k] ); break;
            case 3: $this->make3( $this->cache[$k] ); break;
            case 4: $this->make4( $this->cache[$k] ); break;
            case 5: $this->make5( $this->cache[$k] ); break;
            case 6: $this->make6( $this->cache[$k] ); break;
            case 7: $this->make7( $this->cache[$k] ); break;
            case 8: $this->make8( $this->cache[$k] ); break;
            case 9: $this->make9( $this->cache[$k] ); break;
         }

         for ($i=0; $i<$k; $i++)
            if ($i % PIECE_ROTATIONS == 0) 
               for ($j=0; $j<PIECE_SIZE; $j++) $this->cache[$k][$j]->flip();
            else
               for ($j=0; $j<PIECE_SIZE; $j++) $this->cache[$k][$j]->rotate();
      }
   }

   function unmark(){
      for ($i=0; $i<PIECE_SIZE; $i++) $this->cache[$this->orientation][$i]->unmark();
   }

   function nextOrientation(){
      $this->orientation = ($this->orientation + 1) % PIECE_ORIENTATIONS;
      return $this;
   }

   function cell($i){ return $this->cache[$this->orientation][$i]; }

   function make0(&$a) {
      $a[0]->next[E] = $a[1];
      $a[1]->next[W] = $a[0];
      $a[1]->next[E] = $a[2];
      $a[2]->next[W] = $a[1];
      $a[2]->next[E] = $a[3];
      $a[3]->next[W] = $a[2];
      $a[3]->next[SE] = $a[4];
      $a[4]->next[NW] = $a[3];
   }

   function make1(&$a) {
      $a[0]->next[SE] = $a[1];
      $a[1]->next[NW] = $a[0];
      $a[1]->next[SW] = $a[2];
      $a[2]->next[NE] = $a[1];
      $a[2]->next[W] = $a[3];
      $a[3]->next[E] = $a[2];
      $a[3]->next[SW] = $a[4];
      $a[4]->next[NE] = $a[3];
   }

   function make2(&$a) {
      $a[0]->next[W] = $a[1];
      $a[1]->next[E] = $a[0];
      $a[1]->next[SW] = $a[2];
      $a[2]->next[NE] = $a[1];
      $a[2]->next[SE] = $a[3];
      $a[3]->next[NW] = $a[2];
      $a[3]->next[SE] = $a[4];
      $a[4]->next[NW] = $a[3];
   }

   function make3(&$a) {
      $a[0]->next[SW] = $a[1];
      $a[1]->next[NE] = $a[0];
      $a[1]->next[W] = $a[2];
      $a[2]->next[E] = $a[1];
      $a[1]->next[SW] = $a[3];
      $a[3]->next[NE] = $a[1];
      $a[2]->next[SE] = $a[3];
      $a[3]->next[NW] = $a[2];
      $a[3]->next[SE] = $a[4];
      $a[4]->next[NW] = $a[3];
   }

   function make4(&$a) {
      $a[0]->next[SE] = $a[1];
      $a[1]->next[NW] = $a[0];
      $a[1]->next[SW] = $a[2];
      $a[2]->next[NE] = $a[1];
      $a[1]->next[E] = $a[3];
      $a[3]->next[W] = $a[1];
      $a[3]->next[SE] = $a[4];
      $a[4]->next[NW] = $a[3];
   }

   function make5(&$a) {
      $a[0]->next[SW] = $a[1];
      $a[1]->next[NE] = $a[0];
      $a[0]->next[SE] = $a[2];
      $a[2]->next[NW] = $a[0];
      $a[1]->next[SE] = $a[3];
      $a[3]->next[NW] = $a[1];
      $a[2]->next[SW] = $a[3];
      $a[3]->next[NE] = $a[2];
      $a[3]->next[SW] = $a[4];
      $a[4]->next[NE] = $a[3];
   }

   function make6(&$a) {
      $a[0]->next[SW] = $a[1];
      $a[1]->next[NE] = $a[0];
      $a[2]->next[SE] = $a[1];
      $a[1]->next[NW] = $a[2];
      $a[1]->next[SE] = $a[3];
      $a[3]->next[NW] = $a[1];
      $a[3]->next[SW] = $a[4];
      $a[4]->next[NE] = $a[3];
   }

   function make7(&$a) {
      $a[0]->next[SE] = $a[1];
      $a[1]->next[NW] = $a[0];
      $a[0]->next[SW] = $a[2];
      $a[2]->next[NE] = $a[0];
      $a[2]->next[SW] = $a[3];
      $a[3]->next[NE] = $a[2];
      $a[3]->next[SE] = $a[4];
      $a[4]->next[NW] = $a[3];
   }

   function make8(&$a) {
      $a[0]->next[E] = $a[1];
      $a[1]->next[W] = $a[0];
      $a[1]->next[E] = $a[2];
      $a[2]->next[W] = $a[1];
      $a[2]->next[NE] = $a[3];
      $a[3]->next[SW] = $a[2];
      $a[3]->next[E] = $a[4];
      $a[4]->next[W] = $a[3];
   }

   function make9(&$a) {
      $a[0]->next[E] = $a[1];
      $a[1]->next[W] = $a[0];
      $a[1]->next[E] = $a[2];
      $a[2]->next[W] = $a[1];
      $a[2]->next[NE] = $a[3];
      $a[3]->next[SW] = $a[2];
      $a[2]->next[E] = $a[4];
      $a[4]->next[W] = $a[2];
      $a[4]->next[NW] = $a[3];
      $a[3]->next[SE] = $a[4];
   }

/*
   function printPiece(){
      printf("Piece # %d\n", $this->number);
      print("cell\tNW NE W  E  SW SE\n");
      for ($i=0; $i<PIECE_SIZE; $i++){
         printf("%d \t", $i);
         for ($j=0; $j<SIDES; $j++){
            $neighbour = $this->cell($i)->next[$j];
            if ($neighbour == null){ 
               print("-- "); 
            } else {
               for ($k=0; $k<PIECE_SIZE; $k++)
                  if (($this->cell($k)) == $neighbour) printf("%2d ", $k);
            }
         }
         print("\n");
      }
      print("\n");
   }
*/
}


class Solver {
   var $countdown, $n, $board, $pieces, $unplaced, $unplacedSize, $once,
       $first, $last, $current;

   function Solver($arg) { 
      $this->n = $arg;
      $this->countdown = $this->n;
      $this->board = new Board();

      for ($i=0; $i<PIECES; $i++){ 
         $this->pieces[$i] = new Piece($i);
         $this->unplaced[$i] = true;
      }
      $this->unplacedSize = PIECES;

      $this->once = true;
   }

   function shouldPrune() { 
      $this->board->unmark();
      for ($i=0; $i<BOARD_SIZE; $i++) {
         $forall = ($this->board->cells[$i]->contiguousEmptyCells() % PIECE_SIZE) == 0;
         if (!$forall) return !$forall;
      }
      return !$forall;
   }

   function puzzleSolved() { 
      $a = $this->board->asString();
      if ($this->first == null){
         $this->first = $a; 
         $this->last = $a;
      } else {
         if ($a < $this->first){ 
            $this->first = $a; 
         } else { 
            if ($a > $this->last){ $this->last = $a; } 
         }
      }
      $this->countdown--; 
   }

   function findSolutions() { 
      if ($this->countdown > 0){
         if ($this->unplacedSize > 0){
            $emptyCellIndex = $this->board->firstEmptyCellIndex();

            for ($k=0; $k<PIECES; $k++){
               if ($this->unplaced[$k]){
                  $this->unplaced[$k] = false; $this->unplacedSize--;

                  for ($i=0; $i<PIECE_ORIENTATIONS; $i++){
                     $piece = $this->pieces[$k]->nextOrientation();
                     for ($j=0; $j<PIECE_SIZE; $j++){
                        if ($this->board->add($j,$emptyCellIndex,$piece)){
                           if (!$this->shouldPrune()) $this->findSolutions();
                           $this->board->remove($piece);
                        }
                     }
                  }
                  $this->unplaced[$k] = true; $this->unplacedSize++;
               }
            }
         } else {
            $this->puzzleSolved();
         }
      }
   }

   function printBoard(&$s) { 
      $indent = false;
      $i = 0;
      while ($i < strlen($s)){
         if ($indent) print(" ");
         $j = 0;
         while ($j < BOARD_COLS){
            print($s[$i]); print(" ");
            $j++;
            $i++;
         }
         print("\n");
         $indent = !$indent;
      }
      print("\n");
   }

   function printSolutions() { 
      printf("%d solutions found\n\n",$this->n);
      $this->printBoard($this->first);
      $this->printBoard($this->last);
   }
}


$s = new Solver($argv[1]);
$s->findSolutions();
$s->printSolutions();

?>
