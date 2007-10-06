<? /* The Great Computer Language Shootout 
   http://shootout.alioth.debian.org/
   
   contributed by Isaac Gouy (PHP novice)
   
   php -q binarytrees.php 12
*/

// range 12-14


function newTreeNode(&$left, &$right, $item){ 
   return array($left,$right,$item);      
}    

function itemCheck(&$treeNode){ 
   if (!isset($treeNode[0])){ return $treeNode[2]; }
   else {return 
      $treeNode[2] + 
         itemCheck($treeNode[0]) - itemCheck($treeNode[1]); 
   }
} 

function bottomUpTree($item,$depth){ 
   if ($depth>0){
      $left = bottomUpTree(2*$item-1,$depth-1);
      $right = bottomUpTree(2*$item,$depth-1);
      return newTreeNode($left,$right,$item);
      }
   else {
      $treeNode = NULL;
      return newTreeNode($treeNode, $treeNode, $item);
   }
}  


$minDepth = 4;

$n = ($argc == 2) ? $argv[1] : 1;
$maxDepth = max($minDepth + 2, $n);
$stretchDepth = $maxDepth + 1;

$stretchTree = bottomUpTree(0,$stretchDepth);
printf("stretch tree of depth %d\t check: %d\n", 
   $stretchDepth, itemCheck($stretchTree));
unset($stretchTree);

$longLivedTree = bottomUpTree(0,$maxDepth);

for ($depth=$minDepth; $depth<=$maxDepth; $depth+=2){
   $iterations = 1 << ($maxDepth - $depth + $minDepth);

   $check = 0;
   for ($i=1; $i<=$iterations; $i++){
      $t = bottomUpTree($i,$depth);
      $check += itemCheck($t);
      $t = NULL;       
      
      $t = bottomUpTree(-$i,$depth);
      $check += itemCheck($t);
      $t = NULL;           
   }
   
   printf("%d\t trees of depth %d\t check: %d\n",
      2*$iterations, $depth, $check);
}

printf("long lived tree of depth %d\t check: %d\n", 
   $maxDepth, itemCheck($longLivedTree));

?>
