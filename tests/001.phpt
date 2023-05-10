--TEST--
Check if includemonitor is loaded
--EXTENSIONS--
includemonitor
--FILE--
<?php
echo 'The extension "includemonitor" is available';
?>
--EXPECT--
The extension "includemonitor" is available
