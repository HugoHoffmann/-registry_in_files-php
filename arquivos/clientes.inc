<?php
    include_once './constantes.inc';
?>
<!DOCTYPE html>
<html>
    <head>
        <title>Clientes</title>
        <meta charset="windows-1252">
        <meta name="viewport" content="width=device-width, initial-scale=1.0">
        <link rel="stylesheet" href='../estilo/estiloClientes.css'>
    </head>
    <section>
        <h1>Clientes</h1>
        <hr>
        <table id='tabela' border="1px">
            <tr>
                <th>Código</th>
                <th>Nome</th>
                <th>Crédito</th>
                <th>Ação</th>
            </tr>
        <?php
            function geraTabela($aLinhas){
                if(!empty($aLinhas)){
                    foreach($aLinhas AS $aCliente){
                        echo '  <tr>
                                    <td>'.$aCliente['codigo'].'</td>
                                    <td>'.$aCliente['nome'].'</td>
                                    <td>'.$aCliente['credito'].'</td>
                                    <td><a class="acao" href="index.php?pagina=clientes&remove='.$aCliente['codigo'].'">Remover</a></td>
                                </tr>';
                    }
                }
            }
            if(isset($_GET['remove'])){
                $aRestantes = [];
                $iCodigo = $_GET['remove'];
                $aRegistros = getRegistrosArquivo();
                foreach($aRegistros AS $aRegistro){
                    if($iCodigo == $aRegistro['codigo']){
                        unset($aRegistro);
                    }
                    else{
                        $aRestantes[] = $aRegistro; 
                    }
                        
                }
                limpaArquivo();
                
                foreach($aRestantes AS $aLinha){
                    $sJSON = json_encode($aLinha);
                    file_put_contents('../dados/clientes.txt', $sJSON.ENTER, FILE_APPEND);
                }

            }
            
            function limpaArquivo(){
                file_put_contents('../dados/clientes.txt','');
            }


        function getRegistrosArquivo(){
            $aRegistrosArquivo = [];

            $sConteudo = trim(file_get_contents('../dados/clientes.txt'));

                $aRegistros = explode(ENTER, $sConteudo);
                
                foreach($aRegistros as $sRegistro){
                    $aRegistro = json_decode($sRegistro, true);
                    
                    $aRegistrosArquivo[] = $aRegistro;
                }
                
                return $aRegistrosArquivo;
            }

            geraTabela(getRegistrosArquivo('clientes'));
    
            echo '</table>';
        ?>
        <hr>
        <br>
        <form action="index.php?pagina=clientes" method="post">
            <label for="codigo">Código:<span>*</span></label>
            <input  type="number" name="codigo" required="required">
            <br>
            <label for="nome">Nome:<span>*</span></label>
            <input type="text" name="nome" required="required">
            <br>
            <label for="credito">Valor do crédito:<span>*</span></label>
            <input type="number" name="credito" required="required">
            <hr>
            <input type="reset" value='Limpar'name='limpar' >
            <input type="submit" value='Gravar' name='gravar' onclick="verificaCamposCli();">
        </form>
    </section>
</html>
<?php
    if(isset($_POST['gravar'])){
        $sConte = trim(file_get_contents('../dados/clientes.txt'));
        $aLin = explode(ENTER,$sConte);
        
        if(!empty($aLin)){
            foreach($aLin AS $sCliente){
                $aCliente = json_decode($sCliente,true);
                if($_POST['codigo'] == $aCliente['codigo']){
                   echo '<h1>Código já existe, insira outro.</h1>';
                   die();
                }
            }
            $aGrava = ['codigo'  => $_POST['codigo'], 
                       'nome'    => $_POST['nome'],
                       'credito' => $_POST['credito']];

            $sJSON = json_encode($aGrava);

            file_put_contents('../dados/clientes.txt', $sJSON.ENTER, FILE_APPEND);
        }
    }

?>