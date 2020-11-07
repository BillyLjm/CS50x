<h1 class="page-title">Transaction History</h1>
<table class="table table-hover">
    <tr>
        <th>Symbol</th>
        <th>Buy/Sell</th>
        <th>Num of Shares</th>
        <th>Unit Price</th>
        <th>Time</th>
    </tr>
    <?php foreach ($txns as $txn): ?>
        <tr>
            <td><?= $txn["symbol"] ?></td>
            <?php if ($txn["type"] == BUY): ?>
                <td>BUY</td>
            <?php else: ?>
                <td>SELL</td>
            <?php endif; ?>
            <td><?= $txn["shares"] ?></td>
            <td>$<?= number_format($txn["unit_price"], 4) ?></td>
            <td><?= $txn["time"] ?></td>
        </tr>
    <?php endforeach ?>
</table>
