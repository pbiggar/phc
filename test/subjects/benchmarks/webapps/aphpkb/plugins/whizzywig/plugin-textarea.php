<?php //plugin-textarea.php  ?>
<script type="text/javascript" src="whizzywig.js"></script>
<textarea id="edited" name="<?php echo $textareaname; ?>" style="width:100%; height:250px"> 
<?php echo $textareacontent; ?>
</textarea>
<script type="text/javascript">
buttonPath = "plugins/whizzywig/buttons/"; //directory holding button images
makeWhizzyWig("edited", "formatblock fontsize bold italic underline | left center right | number bullet indent outdent | undo redo  table");
</script>

