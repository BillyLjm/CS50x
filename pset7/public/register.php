<?php

    // configuration
    require("../includes/config.php"); 

    // if user reached page via GET (as by clicking a link or via redirect)
    if ($_SERVER["REQUEST_METHOD"] == "GET")
    {
        // else render form
        render("register_form.php", []);
    }

    // else if user reached page via POST (as by submitting a form via POST)
    else if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        // validate submission
        if (empty($_POST["username"]))
        {
            apologize("You must provide your username.");
        }
        else if (empty($_POST["email"]))
        {
            apologize("You must provide your email.");
        }
        else if (empty($_POST["password"]))
        {
            apologize("You must provide your password.");
        }
        else if (empty($_POST["confirmation"]))
        {
            apologize("You must confirm your password.");
        }
        else if($_POST["password"] !== $_POST["confirmation"])
        {
            apologisze("Your passwords do not match");
        }

        // insert user into database
        $rows = query("INSERT INTO users (username, hash, email, cash) VALUES(?, ?, ?, 10000.0000)", $_POST["username"], crypt($_POST["password"]), $_POST["email"]);
        
        // if registration was sucessful, log in
        if ($rows !== false)
        {
            $rows = query("SELECT LAST_INSERT_ID() AS id");
            $_SESSION["id"]  = $rows[0]["id"];
            redirect("/");
        }
        
        // else apologize
        else
        {
            apologize("The username is already taken.");
        }
    }

?>
