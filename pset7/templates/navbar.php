<nav class="navbar navbar-default">
    <div class="container-fluid">
        <div class="navbar-header">
            <a class="navbar-brand" href="">$<?= $_SESSION["cash"] ?></a>
        </div>
        <div>
            <ul class="nav navbar-nav">
                <li><a href="index.php"><span class="glyphicon glyphicon-user"></span> Portfolio</a></li>
                <li><a href="history.php"><span class="glyphicon glyphicon-time"></span> History</a></li>
                <li><a href="buy.php"><span class="glyphicon glyphicon-random"></span> Trade</a></li>
                <li><a href="quote.php"><span class="glyphicon glyphicon-usd"></span> Quote</a></li>
            </ul>
            <ul class="nav navbar-nav navbar-right">
                <li><a href="changepass.php"><span class="glyphicon glyphicon-cog"></span> Change Password</a></li>
                <li><a href="logout.php"><span class="glyphicon glyphicon-log-out"></span> Log Out</a></li>
            </ul>
        </div>
    </div>
</nav>
