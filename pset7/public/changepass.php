<?php

    // configuration
    require("../includes/config.php"); 

    // if user reached page via GET (as by clicking a link or via redirect)
    if ($_SERVER["REQUEST_METHOD"] == "GET")
    {
        // else render form
        render("changepass_form.php", []);
    }

    // else if user reached page via POST (as by submitting a form via POST)
    else if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        // validate submission
        if (empty($_POST["currpass"]))
        {
            apologize("You must provide your current password.");
        }
        else if (empty($_POST["newpass"]))
        {
            apologize("You must provide a new password.");
        }
        else if (empty($_POST["confirmation"]))
        {
            apologize("You must confirm your new password.");
        }
        else if($_POST["newpass"] !== $_POST["confirmation"])
        {
            apologisze("Your passwords do not match");
        }

        // query database for user
        $rows = query("SELECT * FROM users WHERE id = ?", $_SESSION["id"]);
        
        // if we found user, check password
        if (count($rows) == 1)
        {
            // first (and only) row
            $row = $rows[0];

            // compare hash of user's input against hash that's in database
            if (crypt($_POST["currpass"], $row["hash"]) == $row["hash"])
            {
                query("UPDATE users SET hash = ? WHERE id = ?", crypt($_POST["newpass"]), $_SESSION["id"]);
                success("Your password has been change successfully.");
            }
        }
        // else apologize
        else
        {
            apologize("Invalid username and/or email.");
        }
    }

?>
