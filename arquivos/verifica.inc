<?php
// verificação para a inclusão de páginas a partir do index.php
    $sPagina = isset($_GET['pagina']) ? $_GET['pagina'] : 'home';
    
    if($sPagina=='home'){
        echo '<h3>Seja bem vindo, hoje é dia '.date('d/m/Y').'</h3>';
    }
// inclusão da página requerida
    else{
        include_once $sPagina.'.inc';
    }
