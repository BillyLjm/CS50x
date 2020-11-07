<?php

    // configuration
    require("../includes/config.php");

    // if user reached page via GET (as by clicking a link or via redirect)
    if ($_SERVER["REQUEST_METHOD"] == "GET")
    {
        // else trade form
        render("trade_form.php", []);
    }

    // else if user reached page via POST (as by submitting a form via POST)
    else if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        // validate submission
        if (empty($_POST["symbol"]))
        {
            apologize("You must provide a stock symbol.");
        }
        else if (empty($_POST["qty"]) or $_POST["qty"] < 1)
        {
            apologize("You must provide a valid quantity.");
        }

        // lookup stock
        $stock = lookup(strtoupper($_POST["symbol"]));
        if ($stock === false)
        {
            apologize("We could not find the stock symbol");
        }

        // check user's cash
        $rows = query("SELECT cash FROM users WHERE id = ?", $_SESSION["id"]);
        if (count($rows) !== 1 or $rows[0]["cash"] < $stock["price"] * $_POST["qty"])
        {
            apologize("You do not have sufficient cash to buy the shares.");
        }

        // do sql transaction
        query("INSERT INTO history (id, type, symbol, shares, unit_price) VALUES(?, ?, ?, ?, ?)",
               $_SESSION["id"], BUY, $stock["symbol"], $_POST["qty"], $stock["price"]);
        query("UPDATE users SET cash = cash - ? WHERE id =?", $stock["price"] * $_POST["qty"], $_SESSION["id"]);
        query("INSERT INTO shares (id, symbol, shares) VALUES(?, ?, ?) ON DUPLICATE KEY UPDATE shares = shares + VALUES(shares)",
               $_SESSION["id"], $stock["symbol"], $_POST["qty"]);

        // update cash
        $rows = query("SELECT cash FROM users WHERE id = ?", $_SESSION["id"]);
        $_SESSION["cash"] =  $rows[0]["cash"];

        // send email
        $msg = "You just bought {$_POST["qty"]} stocks of {$stock["symbol"]} at $" . number_format($stock["price"],4) . " each";
        mail($_SESSION["email"], "CS50 Finance Shares Bought", $msg, "From: " . EMAIL);
        
        // render success page
        success($msg);
    }

?>
