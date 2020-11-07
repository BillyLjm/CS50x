<?php

    // configuration
    require("../includes/config.php");

    // query shares for user
    $rows = query("SELECT symbol, shares FROM shares WHERE id = ? ORDER BY symbol", $_SESSION["id"]);

    $stocks = [];
    foreach ($rows as $row)
    {
        $stock = lookup($row["symbol"]);
        if ($stock !== false)
        {
            $stocks[] = ["name" => $stock["name"],
                         "symbol" => $stock["symbol"],
                         "shares" => $row["shares"],
                         "price" => number_format($stock["price"],4)];
        }
    }

    // render portfolio information
    render("portfolio_display.php", ["stocks" => $stocks]);

?>
