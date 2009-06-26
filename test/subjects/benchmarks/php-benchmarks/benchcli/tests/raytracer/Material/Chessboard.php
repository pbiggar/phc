<?php 
class RayTracer_Material_Chessboard extends RayTracer_Material_BaseMaterial {
	public $colorEven = null;
	public $colorOdd = null;
	public $density = 0.5;
                	
	public function __construct($colorEven, $colorOdd, $reflection, $transparency, $gloss, $density)
	{
    	$this->colorEven = $colorEven;
        $this->colorOdd = $colorOdd;
        $this->reflection = $reflection;
        $this->transparency = $transparency;
        $this->gloss = $gloss;
        $this->density = $density;
        $this->hasTexture = true;
    }

    public function getColor($u, $v)
    {
    	$t = $this->wrapUp($u * $this->density) * $this->wrapUp($v * $this->density);
    	
    	if($t < 0.0)
            return $this->colorEven;
        else
            return $this->colorOdd;
    }
    
    public function __toString()
    {
 		return 'ChessMaterial [gloss=' . $this->gloss . ', transparency=' . $this->transparency . ', hasTexture=' . $this->hasTexture .']';
    }
}