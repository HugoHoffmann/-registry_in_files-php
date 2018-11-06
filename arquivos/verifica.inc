<?php

    $sPagina = isset($_GET['pagina']) ? $_GET['pagina'] : 'home';
    
    if($sPagina=='home'){
        echo '<h3>Seja bem vindo, hoje é dia '.date('d/m/Y').'</h3>';
    }
    else{
        include_once $sPagina.'.inc';
    }
