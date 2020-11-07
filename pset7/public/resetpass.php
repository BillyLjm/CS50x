<?php

    // configuration
    require("../includes/config.php"); 

    // if user reached page via GET (as by clicking a link or via redirect)
    if ($_SERVER["REQUEST_METHOD"] == "GET")
    {
        // else render form
        render("resetpass_form.php", []);
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

        // query database for user
        $rows = query("SELECT * FROM users WHERE username = ? AND email = ?", $_POST["username"], $_POST["email"]);

        // if we found user, check password
        if (count($rows) === 1)
        {
            // randomly generate password
            $password = randstr(13);
            
            // update database
            query("UPDATE users SET hash = ? WHERE username = ? AND email = ?", crypt($password), $_POST["username"], $_POST["email"]);

            // send email
            $msg = "Your new password is {$password}.\nYou are advised to change your password right after logging in.";
            mail($_POST["email"], "CS50 Finance Password Reset", $msg, "From: " . EMAIL);
            
            // success page
            success("Your new password has been sent to {$password}{$_POST["email"]}\nYou are advised to change your password right after signing in");
        }

        // else apologize
        else
        {
            apologize("Invalid username and/or email.");
        }
    }

?>
