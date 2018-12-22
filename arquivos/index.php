<?php
    include_once './constantes.inc';
//Arquivo para uso de menu estático
?>

<!DOCTYPE html>
<html>
    <head>
        <title>Sistema</title>
        <meta charset="UTF-8">
        <meta name="viewport" content="width=device-width, initial-scale=1.0">
        <link rel="stylesheet" href='../estilo/estiloHome.css'>
        <script type="text/javascript" src="../js/validaCampo.js"></script>
        <script src="https://ajax.googleapis.com/ajax/libs/jquery/3.3.1/jquery.min.js"></script>
    </head>
    <header>
        <h2>Projeto Manipulação de arquivos</h2>
        <img src="../imagens/logo.png" >
    </header>
    <nav>
        <ul>
            <li><a href="index.php?pagina=home">Início</a></li>
            <li><a href="index.php?pagina=clientes">Clientes</a></li>
            <li><a href="index.php?pagina=produtos">Produtos</a></li>
            <li><a href="index.php?pagina=pedidos">Pedidos</a></li>
        </ul>
    </nav>

<?php
    //incorporação das páginas de acordo com a url requisitada no item de menu selecionado
    include_once './verifica.inc';
?>
    <footer><hr>Todos os direitos reservados</footer>
</html>
