
CREATE PROCEDURE fatura_pedido_venda(in_cod_pedido_venda INT,
                                     in_cod_empresa CHAR(02),
                                     in_natureza_operacao SMALLINT,
                                     in_usuario_inclusao VARCHAR(16),
                                     in_data_hora_emissao DATETIME)
BEGIN
   DECLARE not_found INT DEFAULT 0;
   DECLARE l_cod_cliente CHAR(15);
   DECLARE l_cod_forma_pagto SMALLINT;
   DECLARE l_cod_cfop_padrao       SMALLINT;
   DECLARE l_cod_cst_icms_padrao   VARCHAR(4);
   DECLARE l_cod_cst_ipi_padrao    VARCHAR(4);
   DECLARE l_cod_cst_pis_padrao    VARCHAR(4);
   DECLARE l_cod_cst_cofins_padrao VARCHAR(4);
   DECLARE l_percentual_icms       DECIMAL(5,2);
   DECLARE l_info_complementar     VARCHAR(4000);
   DECLARE l_num_nota_fiscal INT;
   DECLARE l_serie_nota_fiscal SMALLINT;
   DECLARE l_cod_nota_fiscal INT;
   DECLARE l_seq_produto SMALLINT;
   DECLARE l_cod_produto VARCHAR(15);
   DECLARE l_den_produto VARCHAR(75);
   DECLARE l_cod_ncm VARCHAR(8);
   DECLARE l_origem_mercadoria SMALLINT;
   DECLARE l_cod_unid_medida VARCHAR(3);
   DECLARE l_qtd_produto DECIMAL(15,3);
   DECLARE l_valor_unitario DECIMAL(15,3);
   DECLARE l_valor_desconto DECIMAL(15,2);
   DECLARE l_valor_frete DECIMAL(15,2);
   DECLARE l_valor_seguro DECIMAL(15,2);
   DECLARE l_valor_total DECIMAL(15,2);
   DECLARE l_cod_extipi VARCHAR(3); 
   DECLARE l_classe_enq_ipi VARCHAR(5); 
   DECLARE l_cod_enq_ipi VARCHAR(3);
   DECLARE l_valor_icms DECIMAL(15,2);

   DECLARE cq_pedido_venda_item CURSOR FOR
   SELECT pv.seq_produto, pv.cod_produto, p.den_produto, 
          p.cod_ncm, p.origem_mercadoria,
          p.cod_unid_medida, pv.qtd_produto, pv.preco_venda,
          (pv.qtd_produto * pv.val_desconto) valor_desconto,
          (pv.qtd_produto * pv.preco_venda) valor_total,
          p.cod_extipi, p.classe_enq_ipi, p.cod_enq_ipi
     FROM tbl_pedido_venda_item pv, tbl_produto p
    WHERE p.cod_produto = pv.cod_produto
      AND pv.cod_pedido_venda = in_cod_pedido_venda 
    ORDER BY pv.seq_produto;
   DECLARE CONTINUE HANDLER FOR NOT FOUND SET not_found=1;

   SELECT cod_cliente, cod_forma_pagto 
     INTO l_cod_cliente, l_cod_forma_pagto
     FROM tbl_pedido_venda
    WHERE cod_pedido_venda = in_cod_pedido_venda;
    
   SELECT cod_cfop_padrao,       
          cod_cst_icms_padrao,   
          cod_cst_ipi_padrao,    
          cod_cst_pis_padrao,    
          cod_cst_cofins_padrao, 
          percentual_icms,
          info_complementar
     INTO l_cod_cfop_padrao,       
          l_cod_cst_icms_padrao,   
          l_cod_cst_ipi_padrao,    
          l_cod_cst_pis_padrao,    
          l_cod_cst_cofins_padrao, 
          l_percentual_icms,
          l_info_complementar
     FROM tbl_natureza_operacao
    WHERE cod_natureza_operacao = in_natureza_operacao;
    
    IF l_percentual_icms IS NULL THEN 
       SET l_percentual_icms = 0;
    END IF;
    
   -- Verifica se a forma de pagamento é parcelada ou a vista
   SELECT cod_forma_pagto
     INTO l_cod_forma_pagto
     FROM tbl_forma_pagto
    WHERE cod_forma_pagto = l_cod_forma_pagto
      AND ies_parcelado = 'S';
   IF not_found THEN
      SET l_cod_forma_pagto = 1; -- Pagamento a prazo
   ELSE
      SET l_cod_forma_pagto = 0; -- Pagamento a vista 
   END IF;
   
   -- Este UPDATE é só pra travar a tabela caso tenha acesso simultâneo
   UPDATE tbl_parametro_sistema
      SET valor_texto = in_cod_empresa
    WHERE nome_parametro = 'prox_num_nf_venda'
      AND valor_texto = in_cod_empresa;

   SET not_found = 0;
   SELECT valor_decimal
     INTO l_num_nota_fiscal
     FROM tbl_parametro_sistema
    WHERE nome_parametro = 'prox_num_nf_venda'
      AND valor_texto = in_cod_empresa;
   -- Se nunca gerou uma nota para esta série
   IF not_found THEN
      SET l_num_nota_fiscal = 1;
      -- Insere o registro na tabela de parâmetros
      INSERT INTO tbl_parametro_sistema (nome_parametro, valor_texto, valor_decimal, data_atualizacao, user_atualizacao)
      VALUES ('prox_num_nf_venda',in_cod_empresa,l_num_nota_fiscal,in_data_hora_emissao,in_usuario_inclusao);
   END IF;
   -- Buscando a série das notas fiscais
   SELECT valor_decimal
     INTO l_serie_nota_fiscal
     FROM tbl_parametro_sistema
    WHERE nome_parametro = 'serie_nf_venda'
      AND valor_texto = in_cod_empresa;
   -- Inserindo cabeçalho da nota fiscal de venda
   INSERT INTO tbl_nota_fiscal 
          (cod_empresa,tipo_nota_fiscal,num_nota_fiscal,serie_nota_fiscal,
           modelo_nota_fiscal,ies_situacao,cod_natureza_operacao,cod_forma_pagto,cod_cliente,
           valor_mercadoria,valor_desconto,valor_duplicata,valor_frete,valor_seguro,
           outras_despesas,valor_nota_fiscal,usuario_inclusao,data_hora_emissao,tipo_frete,info_complementar)
   VALUES (in_cod_empresa,1,l_num_nota_fiscal,l_serie_nota_fiscal,'55','A',in_natureza_operacao,l_cod_forma_pagto,
           l_cod_cliente, 0, 0, 0, 0, 0, 0, 0, in_usuario_inclusao, in_data_hora_emissao,9,l_info_complementar);

   SET l_cod_nota_fiscal = LAST_INSERT_ID();
   
   SET not_found = 0;
   SET l_valor_frete = 0;
   SET l_valor_seguro = 0;
   OPEN cq_pedido_venda_item;
   read_loop: LOOP
      FETCH cq_pedido_venda_item INTO l_seq_produto, l_cod_produto, l_den_produto, l_cod_ncm,
                                      l_origem_mercadoria, l_cod_unid_medida, l_qtd_produto, 
                                      l_valor_unitario, l_valor_desconto, l_valor_total,
                                      l_cod_extipi, l_classe_enq_ipi, l_cod_enq_ipi;
      IF not_found THEN
          LEAVE read_loop;
      END IF;
      
      -- Inserindo os itens da nota fiscal
      INSERT INTO tbl_nota_fiscal_item 
             (cod_empresa,cod_nota_fiscal,seq_produto,cod_produto,den_produto,    
              cod_ncm,cod_ean,cod_cfop,cod_unid_medida,qtd_produto,
              valor_unitario,valor_desconto,valor_frete,valor_seguro,  
              valor_total,cod_pedido,seq_pedido,
              cod_extipi, classe_enq_ipi, cod_enq_ipi)
      VALUES (in_cod_empresa,l_cod_nota_fiscal,l_seq_produto,l_cod_produto,l_den_produto,    
              l_cod_ncm,NULL,l_cod_cfop_padrao,l_cod_unid_medida,l_qtd_produto,
              l_valor_unitario,l_valor_desconto,l_valor_frete,l_valor_seguro,
              l_valor_total,in_cod_pedido_venda,l_seq_produto,
              l_cod_extipi, l_classe_enq_ipi, l_cod_enq_ipi);
      
      -- Inserindo os impostos da nota fiscal - Por ora vai ser feito desta forma
      SET l_valor_icms = (l_valor_total - l_valor_desconto + l_valor_frete + l_valor_seguro) * (l_percentual_icms / 100);
      INSERT INTO tbl_nota_fiscal_item_tributo  
             (cod_empresa,cod_nota_fiscal,seq_produto,cod_tributo,cod_cst,perc_tributo,base_calculo,valor_tributo)
      VALUES (in_cod_empresa,l_cod_nota_fiscal,l_seq_produto,'ICMS',l_cod_cst_icms_padrao,l_percentual_icms,0,l_valor_icms);
      INSERT INTO tbl_nota_fiscal_item_tributo  
             (cod_empresa,cod_nota_fiscal,seq_produto,cod_tributo,cod_cst,perc_tributo,base_calculo,valor_tributo)
      VALUES (in_cod_empresa,l_cod_nota_fiscal,l_seq_produto,'IPI',l_cod_cst_ipi_padrao,NULL,NULL,0);
      INSERT INTO tbl_nota_fiscal_item_tributo  
             (cod_empresa,cod_nota_fiscal,seq_produto,cod_tributo,cod_cst,perc_tributo,base_calculo,valor_tributo)
      VALUES (in_cod_empresa,l_cod_nota_fiscal,l_seq_produto,'PIS',l_cod_cst_pis_padrao,NULL,NULL,0);
      INSERT INTO tbl_nota_fiscal_item_tributo  
             (cod_empresa,cod_nota_fiscal,seq_produto,cod_tributo,cod_cst,perc_tributo,base_calculo,valor_tributo)
      VALUES (in_cod_empresa,l_cod_nota_fiscal,l_seq_produto,'COFINS',l_cod_cst_cofins_padrao,NULL,NULL,0);
 
   END LOOP;
   CLOSE cq_pedido_venda_item;
   
   -- Deve atualizar o total da nota fiscal agora
   SELECT SUM(valor_desconto),
          SUM(valor_frete),
          SUM(valor_seguro),
          SUM(valor_total)
     INTO l_valor_desconto, 
          l_valor_frete,    
          l_valor_seguro,   
          l_valor_total
     FROM tbl_nota_fiscal_item
    WHERE cod_empresa = in_cod_empresa
      AND cod_nota_fiscal = l_cod_nota_fiscal;
    
   UPDATE tbl_nota_fiscal
      SET valor_mercadoria = l_valor_total,
          valor_desconto = l_valor_desconto, 
          valor_frete = l_valor_frete,    
          valor_seguro = l_valor_seguro,   
          valor_nota_fiscal = (l_valor_total - l_valor_desconto + l_valor_frete + l_valor_seguro)
    WHERE cod_empresa = in_cod_empresa
      AND cod_nota_fiscal = l_cod_nota_fiscal;  
   
   -- Inserindo os impostos na nota fiscal
   INSERT INTO tbl_nota_fiscal_tributo  
         (cod_empresa,cod_nota_fiscal,cod_tributo,base_calculo,valor_tributo)
   SELECT cod_empresa,cod_nota_fiscal,cod_tributo,0,0 -- SUM(base_calculo),SUM(valor_tributo)
     FROM tbl_nota_fiscal_item_tributo
    WHERE cod_empresa = in_cod_empresa
      AND cod_nota_fiscal = l_cod_nota_fiscal
    GROUP BY cod_empresa,cod_nota_fiscal,cod_tributo;
   -- Marcando o pedido de venda como faturado
   UPDATE tbl_pedido_venda
      SET ies_situacao = 'T'
    WHERE cod_pedido_venda = in_cod_pedido_venda;
        
   -- Atualizando o próximo de número de nota fiscal        
   UPDATE tbl_parametro_sistema
      SET valor_decimal = valor_decimal + 1
    WHERE nome_parametro = 'prox_num_nf_venda'
      AND valor_texto = in_cod_empresa;
      
END

CREATE PROCEDURE atualiza_imposto_item(
      in_cod_empresa CHAR(2),
      in_cod_nota_fiscal INTEGER,
      in_seq_produto SMALLINT,
      in_cod_tributo VARCHAR(10),
      in_cod_cst VARCHAR(4),
      in_perc_tributo DECIMAL(5, 2),
      in_valor_tributo DECIMAL(15, 2),
      in_mod_def_base_calc SMALLINT,
      in_base_calculo DECIMAL(15, 2),
      in_perc_red_base_calc DECIMAL(5, 2),
      in_perc_marg_valor_add DECIMAL(5, 2),
      in_valor_unit_tributo DECIMAL(15, 3),
      in_qtd_total_tributo DECIMAL(15, 3))
BEGIN
   DECLARE l_cod_tributo VARCHAR(10);
   DECLARE not_found INT DEFAULT 0;
   DECLARE CONTINUE HANDLER FOR NOT FOUND SET not_found=1;

   SELECT cod_tributo
     INTO l_cod_tributo
     FROM tbl_nota_fiscal_item_tributo
    WHERE cod_empresa = in_cod_empresa
      AND cod_nota_fiscal = in_cod_nota_fiscal
      AND seq_produto = in_seq_produto
      AND cod_tributo = in_cod_tributo;
   IF not_found = 1 THEN
      INSERT INTO tbl_nota_fiscal_item_tributo 
             (cod_empresa, cod_nota_fiscal, seq_produto, cod_tributo, cod_cst, 
              mod_def_base_calc, perc_tributo, base_calculo, valor_tributo, 
              perc_red_base_calc, perc_marg_valor_add, valor_unit_tributo, qtd_total_tributo)
      VALUES (in_cod_empresa, in_cod_nota_fiscal, in_seq_produto, in_cod_tributo, in_cod_cst, 
              in_mod_def_base_calc, in_perc_tributo, in_base_calculo, in_valor_tributo, 
              in_perc_red_base_calc, in_perc_marg_valor_add, in_valor_unit_tributo, in_qtd_total_tributo);
   ELSE
       UPDATE tbl_nota_fiscal_item_tributo
          SET cod_cst = in_cod_cst, 
              mod_def_base_calc = in_mod_def_base_calc, 
              perc_tributo = in_perc_tributo, 
              base_calculo = in_base_calculo, 
              valor_tributo = in_valor_tributo, 
              perc_red_base_calc = in_perc_red_base_calc, 
              perc_marg_valor_add = in_perc_marg_valor_add, 
              valor_unit_tributo = in_valor_unit_tributo, 
              qtd_total_tributo = in_qtd_total_tributo
       WHERE cod_empresa = in_cod_empresa
         AND cod_nota_fiscal = in_cod_nota_fiscal
         AND seq_produto = in_seq_produto
         AND cod_tributo = in_cod_tributo;
    END IF;

END;

CREATE PROCEDURE exclui_imposto_item(
      in_cod_empresa CHAR(2),
      in_cod_nota_fiscal INTEGER,
      in_seq_produto SMALLINT,
      in_cod_tributo VARCHAR(10))
BEGIN
   DELETE FROM tbl_nota_fiscal_item_tributo
    WHERE cod_empresa = in_cod_empresa
      AND cod_nota_fiscal = in_cod_nota_fiscal
      AND seq_produto = in_seq_produto
      AND cod_tributo = in_cod_tributo;
END;


CREATE PROCEDURE reabre_nota_fiscal_venda(in_cod_empresa CHAR(02),
                                          in_cod_nota_fiscal INTEGER)
BEGIN
   -- Excluindo o registro da nota fiscal de venda
   DELETE FROM tbl_nota_fiscal_nfe
    WHERE cod_empresa = in_cod_empresa
      AND cod_nota_fiscal = in_cod_nota_fiscal;
   -- Alterando a nota fiscal para aberta
   UPDATE tbl_nota_fiscal SET ies_situacao = 'A'
    WHERE cod_empresa = in_cod_empresa
      AND cod_nota_fiscal = in_cod_nota_fiscal;
END;

CREATE PROCEDURE fecha_nota_fiscal_venda(in_cod_empresa CHAR(02),
                                         in_cod_nota_fiscal INTEGER,
                                         in_chave_acesso_nfe VARCHAR(44))
BEGIN
   DECLARE l_chave_acesso_nfe VARCHAR(44);
   DECLARE not_found INTEGER DEFAULT 0;
   DECLARE CONTINUE HANDLER FOR NOT FOUND SET not_found=1;

   -- Verifica se já existe um registro
   SELECT chave_acesso
     INTO l_chave_acesso_nfe
     FROM tbl_nota_fiscal_nfe
    WHERE cod_empresa = in_cod_empresa
      AND cod_nota_fiscal = in_cod_nota_fiscal;
   IF not_found = 1 THEN
      INSERT INTO tbl_nota_fiscal_nfe 
             (cod_empresa, cod_nota_fiscal, chave_acesso)
      VALUES (in_cod_empresa, in_cod_nota_fiscal, in_chave_acesso_nfe);
   ELSE
       UPDATE tbl_nota_fiscal_nfe
          SET chave_acesso = in_chave_acesso_nfe
       WHERE cod_empresa = in_cod_empresa
         AND cod_nota_fiscal = in_cod_nota_fiscal;
    END IF;
   -- Alterando a nota fiscal para faturada
   UPDATE tbl_nota_fiscal SET ies_situacao = 'F'
    WHERE cod_empresa = in_cod_empresa
      AND cod_nota_fiscal = in_cod_nota_fiscal;
END;
