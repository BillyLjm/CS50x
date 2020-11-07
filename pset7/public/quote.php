<?php

    // configuration
    require("../includes/config.php"); 

    // if user reached page via GET (as by clicking a link or via redirect)
    if ($_SERVER["REQUEST_METHOD"] == "GET")
    {
        // else trade form
        render("quote_form.php", []);
    }

    // else if user reached page via POST (as by submitting a form via POST)
    else if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        // validate submission
        if (empty($_POST["symbol"]))
        {
            apologize("You must provide a stock symbol.");
        }

        // lookup stock
        $stock = lookup($_POST["symbol"]);
        
        // if lookup was sucessful, display info
        if ($stock !== false)
        {
            render("quote_display.php", ["stock" => $stock]);
        }
        
        // else apologize
        else
        {
            apologize("We could not find the stock symbol.");
        }
    }

?>
