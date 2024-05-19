--TEST--
uuid_v4() Returns a string
--EXTENSIONS--
uuid
--FILE--
<?php
echo gettype(uuid_v4());
?>
--EXPECT--
string
