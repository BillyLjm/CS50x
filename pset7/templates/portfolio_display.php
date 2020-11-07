<h1 class="page-title">Portfolio</h1>
<table class="table table-hover">
    <tr>
        <th>Symbol</th>
        <th>Name</th>
        <th>Num of Shares</th>
        <th>Current Price</th>
    </tr>
<?php foreach ($stocks as $stock): ?>
    <tr>
        <td><?= $stock["symbol"] ?></td>
        <td><?= $stock["name"] ?></td>
        <td><?= $stock["shares"] ?></td>
        <td><?= $stock["price"] ?></td>
    </tr>
<?php endforeach ?>
</table>
