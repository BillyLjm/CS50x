<?php

    // configuration
    require("../includes/config.php");

    // query for transaction historu
    $rows = query("SELECT * FROM history WHERE id = ? ORDER BY time DESC LIMIT 100", $_SESSION["id"]);

    // render information
    render("history_display.php", ["txns" => $rows]);

?>
