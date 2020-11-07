<div class="alert alert-info">
    <h2>
        <?= $stock["name"] ?><br>
        <small>(<?= $stock["symbol"] ?>)</small><br>
    </h2>
    <h1>
        $<?= number_format($stock["price"],4) ?>
    </h1>
</div>
<div>
    or <a href="quote.php">get another quote</a>
</div>
