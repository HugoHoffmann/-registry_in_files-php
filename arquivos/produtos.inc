<!DOCTYPE html>
<html>
    <head>
        <title>Produtos</title>
        <meta charset="windows-1252">
        <meta name="viewport" content="width=device-width, initial-scale=1.0">
        <link rel="stylesheet" href='../estilo/estiloProdutos.css'>
    </head>
    <section>
        <h1>Produtos</h1>
        <hr>
        <table id="tabela">
            <tr>
                <th>Código</th>
                <th>Descrição</th>
                <th>Valor</th>
                <!--<th>Ação</th>-->
            
        <?php
            function geraTabela($aLinhas, $bPedido){
                if(!empty($aLinhas)){
                    if($bPedido==true){
                        echo '<th>Quantidade</th>
                             </tr>';
                            foreach($aLinhas AS $aPedido){
                                //$aProduto = json_decode($sProduto,true);
                                echo '<tr>
                                            <td>'.$aPedido['codigo'].'</td>
                                            <td>'.$aPedido['descricao'].'</td>
                                            <td>'.$aPedido['valor'].'</td>
                                            <!--<td><a class="acao" href="index.php?pagina=produtos&codigo='.$aPedido['codigo'].'&numero='.$aPedido['numero'].'">Remover</a></td>-->
                                            <td>'.$aPedido['quantidade'].'</td>
                                          </tr>';
                        } 
                    }
                    else{
                        foreach($aLinhas AS $aProduto){
                            echo '  </tr>
                                    <tr>
                                        <td>'.$aProduto['codigo'].'</td>
                                        <td>'.$aProduto['descricao'].'</td>
                                        <td>'.$aProduto['valor'].'</td>
                                        <td><a class="acao" href="index.php?pagina=produtos&remove='.$aProduto['codigo'].'">Remover</a></td>
                                    </tr>';
                        }
                    }
                }
            }
            if(isset($_GET['codigo'])){
                $aRestantes = [];
                $iCodigoItem = $_GET['codigo'];
                $iCodigoPedido = $_GET['numero'];
                $aRegistros = getRegistrosArquivo('pedidos');
                foreach($aRegistros AS $aRe){
                    if($iCodigoPedido == $aRe['numero']){
                        $aRestantes[] = $aRe;
                        foreach($aRe['produtos'] AS $iIndice => $aProduto){
                            if($iCodigoItem == $aProduto['codigo']){
                                unset($aProduto[$iIndice]);
                            }
                            else{
                                $aRestantes[] = $aProduto; 
                            }
                        }
                    }
                        
                }
                limpaArquivo('pedidos');
                
                foreach($aRestantes AS $aLinha){
                    $sJSON = json_encode($aLinha);
                    file_put_contents('../dados/pedidos.txt', $sJSON.ENTER, FILE_APPEND);
                }

            }
            if(isset($_GET['remove'])){
                $aRestantes = [];
                $iCodigo = $_GET['remove'];
                $aRegistros = getRegistrosArquivo('produtos');
                foreach($aRegistros AS $aRegistro){
                    if($iCodigo == $aRegistro['codigo']){
                        unset($aRegistro);
                    }
                    else{
                        $aRestantes[] = $aRegistro; 
                    }
                        
                }
                limpaArquivo('produtos');
                
                foreach($aRestantes AS $aLinha){
                    $sJSON = json_encode($aLinha);
                    file_put_contents('../dados/produtos.txt', $sJSON.ENTER, FILE_APPEND);
                }

            }
            
            function limpaArquivo($sArqui){
                file_put_contents('../dados/'.$sArqui.'.txt','');
            }

            
            $aCodigos = [];
            $aQuantidades = [];
            
            
            if(isset($_GET['pedido'])){
                $aProdutosPedido = [];
                
                $sPedidoTabela = $_GET['pedido'];
                echo'<h2>Pedido número '.$sPedidoTabela.'</h2>';
                $aRegistros = getRegistrosArquivo('pedidos');
                    foreach($aRegistros AS $aReg){
                            //$aPedidos = json_decode($sPedidos,true);
                            if($aReg['numero'] == $sPedidoTabela){
                                foreach($aReg['produtos'] AS $aProduto){
                                    $aRegistro = getRegistroFromCodigo($aProduto['codigo']);
                                    $aRegistro['quantidade'] = $aProduto['qtd'];
                                    $aRegistro['numero'] = $sPedidoTabela;
                                    $aProdutosPedido[] = $aRegistro;
                                }
                            }
                            
                    }
                geraTabela($aProdutosPedido, true);
                echo '</table>';
            }
            else{
                
                geraTabela(getRegistrosArquivo('produtos'), false);

                echo '</table>';
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
            
            function getRegistroFromCodigo($iCodigo){
                $aRegistros = getRegistrosArquivo('produtos');
                
                foreach ($aRegistros as $aRegistro){
                    if($aRegistro['codigo'] == $iCodigo){
                        return $aRegistro;
                    }
                }
                
                return false;
                
            }
            
        ?>
        <hr>
        <br>
        <form action="index.php?pagina=produtos" method="POST">
            <label for="codigo">Código:<span>*</span></label>
            <input type="number" name="codigo" required="required">
            <br>
            <label for="descricao">Descrição:<span>*</span></label>
            <input type="text" name="descricao" required="required">
            <br>
            <label for="valor">Valor:<span>*</span></label>
            <input type="number" name="valor" required="required">
 
            <input type="reset" value='Limpar'>
            <input type="submit" value='Gravar' name="gravar">
        </form>
    </section>
</html>
<?php
    if(isset($_POST['gravar'])){
        $sConteudo = trim(file_get_contents('../dados/produtos.txt'));
        $aLinhas = explode(ENTER,$sConteudo);
        
        if(!empty($aLinhas)){
            foreach($aLinhas AS $sProduto){
                $aProduto = json_decode($sProduto,true);
                if($_POST['codigo']==$aProduto['codigo']){
                   echo '<h2>Código já existe, insira outro.</h2>';
                   die();
                }
            }
            $aGravaProduto = ['codigo'    => $_POST['codigo'], 
                              'descricao' => $_POST['descricao'],
                              'valor'     => $_POST['valor']];

            $sJSON = json_encode($aGravaProduto);

            file_put_contents('../dados/produtos.txt', $sJSON.ENTER, FILE_APPEND);
        }
    }



