--TEST--
test1() Basic test
--EXTENSIONS--
uuid
--FILE--
<?php
$ret = test1();

var_dump($ret);
?>
--EXPECT--
The extension uuid is loaded and working!
NULL
