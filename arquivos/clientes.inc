<?php
// Uso da constante ENTER para inserção de dados em arquivos
    include_once './constantes.inc';
?>
<!DOCTYPE html>
<html>
    <head>
        <title>Clientes</title>
        <meta charset="UTF-8">
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
            // funcao para geracao da tabela, recebendo como parametro as linhas de dados a serem inseridas na tabela
            function geraTabela($aLinhas){
                // caso exista linhas, execucao de foreach para leitura das linhas recebidas por parametro
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
            // codicao para remoção de registro de acordo com o código do mesmo
            if(isset($_GET['remove'])){
                $aRestantes = [];
                $iCodigo = $_GET['remove'];
                // getRegistrosArquivo, funcao para recebimento de registros no arquivo
                $aRegistros = getRegistrosArquivo();
                foreach($aRegistros AS $aRegistro){
                    // verificao do codigo do registro a ser removido do arquivo
                    if($iCodigo == $aRegistro['codigo']){
                        unset($aRegistro);
                    }
                    // armazenamento dos arquivos restantes sem o arquivo removido
                    else{
                        $aRestantes[] = $aRegistro; 
                    }
                        
                }
                limpaArquivo();
                // armazenamento dos arquivos restantes
                foreach($aRestantes AS $aLinha){
                    // cada linha de registro e armazenada na variavel codificando o valor para json
                    $sJSON = json_encode($aLinha);
                    // armazenamento no arquivo txt utilizando a constante de enter e 
                    //a funcao file_append para que não seja sobreescrito nenhum dado
                    file_put_contents('../dados/clientes.txt', $sJSON.ENTER, FILE_APPEND);
                }

            }
            // funcao para a limpeza do arquivo inteiro
            function limpaArquivo(){
                file_put_contents('../dados/clientes.txt','');
            }

        // funcao para obtencao de todos os registro do arquivo
        function getRegistrosArquivo(){
            // inicializacao do vetor
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
