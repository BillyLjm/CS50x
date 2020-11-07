<h1 class="page-title">Buy / Sell</h1>
<form method="post">
    <fieldset>
        <div class="form-group">
            <input autofocus class="form-control" name="symbol" placeholder="Stock Symbol" type="text"/>
        </div>
        <div class="form-group">
            <input class="form-control" name="qty" placeholder="Quantity" type="number"/>
        </div>
        <div class="form-group">
            <button formaction="buy.php" type="submit" class="btn btn-success">Buy</button>
            <button formaction="sell.php" type="submit" class="btn btn-danger">Sell</button>
        </div>
    </fieldset>
</form>
