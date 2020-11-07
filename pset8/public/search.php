<?php
    /**
     * Auto-completes US address based on partial address
     * Only auto-completes trailing parts of words
     *
     * @author: Billy.Ljm
     * @date: 18 July 2015
     */
    require(__DIR__ . "/../includes/config.php");

    // numerically indexed array of places
    $places = [];

    // format geo & split by spaces or commas
    $geo = preg_replace('/[^a-zA-Z0-9, ]/', '', $_GET["geo"]);
    $geo = preg_split('/[ ,]+/', $geo);

    // construct SQL query
    $querystr = "SELECT * FROM places WHERE"; // SQL query string
    $queryarg = []; // arguments to pass to query, in order
    foreach ($geo as $geoinfo)
    {
        // country code, discarded
        if($geoinfo == "US")
        {
            continue;
        }

        // postal code
        else if (is_numeric($geoinfo))
        {
            $querystr .= " postal_code LIKE ? AND";
            array_push($queryarg, $geoinfo.'%');
        }

        // city name, state name or state code
        else if (strlen($geoinfo) < 3)
        {
            $querystr .= " (place_name LIKE ? OR admin_name1 LIKE ? OR admin_code1 LIKE ?) AND";
            array_push($queryarg, $geoinfo.'%', $geoinfo.'%', $geoinfo.'%');
        }

        // city or state name
        else
        {
            $querystr .= " (place_name LIKE ? OR admin_name1 LIKE ?) AND";
            array_push($queryarg, $geoinfo.'%', $geoinfo.'%');
        }
    }
    $querystr = substr($querystr, 0, -4); // remove trailing " AND"

    // execute sql query
    array_unshift($queryarg, $querystr);
    $places = call_user_func_array("query", $queryarg);

    // output places as JSON (pretty-printed for debugging convenience)
    header("Content-type: application/json");
    print(json_encode($places, JSON_PRETTY_PRINT));

?>
