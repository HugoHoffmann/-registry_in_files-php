<!DOCTYPE html>
<html>
    <head>
        <title>Pedidos</title>
        <meta charset="windows-1252">
        <meta name="viewport" content="width=device-width, initial-scale=1.0">
        <link rel="stylesheet" href='../estilo/estiloPedidos.css'>
        <script type="text/javascript" src="../js/pedidos.js"></script>
    </head>
    <section>
        <h1>Pedidos</h1>
        <hr>
        <table id='tabela'>
            <tr>
                <th>Número</th>
                <th>Cliente</th>
                <th>Data</th>
                <th>Pedido</th>
                <th>Ação</th>
            </tr>
            <?php
                function geraTabela($aLinhas){
                    if(!empty($aLinhas)){
                        foreach($aLinhas AS $aPedido){
                            //$aPedido = json_decode($sPedido,true);
                            echo '<tr>
                                    <td>'.$aPedido['numero'].'</td>
                                    <td>'.$aPedido['cliente'].'</td>
                                    <td>'.$aPedido['data'].'</td>
                                    <td><a class="acao" href="index.php?pagina=produtos&pedido='.$aPedido['numero'].'">Ver</a></td> 
                                    <td><a class="acao" href="index.php?pagina=pedidos&remove='.$aPedido['numero'].'">Remover</a></td>    
                                  </tr>';
                        }
                    }
                }
                if(isset($_GET['remove'])){
                    $aRestantes = [];
                    $iCodigo = $_GET['remove'];
                    $aRegistros = getRegistrosArquivo('pedidos');
                    foreach($aRegistros AS $aRegistro){
                        if($iCodigo == $aRegistro['numero']){
                            unset($aRegistro);
                        }
                        else{
                            $aRestantes[] = $aRegistro; 
                            print_r($aRestantes);
                        }

                    }
                    limpaArquivo();

                    foreach($aRestantes AS $aLinha){
                        $sJSON = json_encode($aLinha);
                        file_put_contents('../dados/pedidos.txt', $sJSON.ENTER, FILE_APPEND);
                    }

                }

                function limpaArquivo(){
                    file_put_contents('../dados/pedidos.txt','');
                }


                function getRegistrosArquivo($sArquivo){
                    $aRegistrosArquivo = [];

                    $sConteudo = trim(file_get_contents('../dados/'.$sArquivo.'.txt'));

                    $aRegistros = explode(ENTER, $sConteudo);

                    foreach($aRegistros as $sRegistro){
                        $aRegistro = json_decode($sRegistro, true);

                        $aRegistrosArquivo[] = $aRegistro;
                    }

                    return $aRegistrosArquivo;
                }

                geraTabela(getRegistrosArquivo('pedidos'));

                echo '</table>';
           ?>
        <br>
        <form method="post" action="index.php?pagina=pedidos">
            <label for="numero">Número:<span>*</span></label>
            <input  type="number" name="numero" required="required">
            <br>
            <label for="data">Data:<span>*</span></label>
            <input type="date" name="data" required="required">
            <br>
            <label for="credito">Cliente:<span>*</span></label>
            <select name='cli_selecao' required="required">
                <?php
//                    $sConteudo = trim(file_get_contents('../dados/clientes.txt'));
//                    $aLinhas = explode(ENTER,$sConteudo);
                    $aRegistrosCli = getRegistrosArquivo('clientes');
                    if(!empty($aRegistrosCli)){
                        echo '<option></option>';
                        foreach($aRegistrosCli AS $aRegistroCli){
//                            $aCliente = json_decode($sCliente,true);
                                echo '<option value="'.$aRegistroCli['codigo'].'-'.$aRegistroCli['nome'].'">'.$aRegistroCli['nome'].'</option>';
                                //Validar se o cliente tem crédito, antes de realizar um pedido.
                        }
                    }
                ?>
            </select>
            <label for="pro_selecao">Produto/Qtd:<span>*</span></label>
            <select id='proSelecao' name='pro_selecao' required="required">
                <?php
//                    $sConteudo = trim(file_get_contents('../dados/produtos.txt'));
//                    $aLinhas = explode(ENTER,$sConteudo);
                    $aRegistrosProdu = getRegistrosArquivo('produtos');
                    if(!empty($aRegistrosProdu)){
                        echo '<option></option>';
                        foreach($aRegistrosProdu AS $aRegistroProdu){
//                            $aProduto = json_decode($sProduto,true);
                                echo '<option value="'.$aRegistroProdu['codigo'].'-'.$aRegistroProdu['descricao'].'-'.$aRegistroProdu['valor'].'">'.$aRegistroProdu['descricao'].'   --   R$'.$aRegistroProdu['valor'].' Reais'.'</option>';
                        }
                    }
                ?>
            </select>
            <input id='qtd' type='number' name='qtd' required="required">
            <button id='botao' type="button" name="adiciona" onclick="onClickAdicionarProduto();">+</button>
            <br>
            <label for="credito">Produtos:</label>
            <table id='miniTabela'> <!--realizar a criação da tabela por javascript-->
                <tr>
                    <th>Produto</th>
                    <th>Quantidade</th>
                    <th>Preço</th>
                </tr>
            </table>
            <label for="total">Total:</label>
            <input readonly="true" type="text" name="total" id="total" value="0">
            <input type="text" name="produtos" id="produtos">
            <input type="reset" value='Limpar' onclick="limpaTabela();">
            <input type="submit" value='Gravar' name="gravar" >
        </form>
    </section>
</html>
<?php
    if(isset($_POST['gravar'])){
        if(isset($_POST['cli_selecao'])){
            $iTotal = $_POST['total'];
            $sCliConcatenado = $_POST['cli_selecao'];
            $sCliCodigo = explode("-", $sCliConcatenado);
            $aRegistrosClientes = getRegistrosArquivo('clientes');
            foreach($aRegistrosClientes AS $aRegistroClientes){
                if($aRegistroClientes['codigo'] == $sCliCodigo[0]){
                    if($aRegistroClientes['credito'] < $iTotal){
                        echo '<h4>O Cliente selecionado não possui crédito!</h4>';
                        die();
                    }
                }
            }
        }
        
        $sConteudo = trim(file_get_contents('../dados/pedidos.txt'));
        $aLinhas = explode(ENTER,$sConteudo);

        if(!empty($aLinhas)){
            foreach($aLinhas AS $sPedido){
                $aPedido = json_decode($sPedido,true);
                if($_POST['numero']==$aPedido['numero']){
                   echo '<h4>Número já existe, insira outro.</h4>';
                   die();
                }
            }
            $aConverte = json_decode($_POST['produtos'],true);
            $sClienteConcatenado = $_POST['cli_selecao'];
            $aCliente = explode("-", $sClienteConcatenado);
            $aGravaPedido = [ 'numero'   => $_POST['numero'], 
                              'data'     => $_POST['data'],
                              'cliente'  => $aCliente[1],
                              'produtos' => $aConverte];
            

            $sJSON = json_encode($aGravaPedido); //JSON.stringify();
            //$sJSON = json_decode($aGravaPedido); //JSON.parse();

            file_put_contents('../dados/pedidos.txt', $sJSON.ENTER, FILE_APPEND);
        }
    }

