CREATE TABLE tbl_empresa (
	cod_empresa   CHAR(02),
	cnpj          VARCHAR(15),
	razao_social  VARCHAR(60),
	nome_fantasia VARCHAR(60),
	logradouro    VARCHAR(50),
	numero        INTEGER,
	complemento   VARCHAR(10),
	bairro        VARCHAR(30),
	cod_cidade    VARCHAR(05),
	cod_uf        VARCHAR(02),
	cep           VARCHAR(12),
	inscricao_estadual  VARCHAR(15),
	inscricao_municipal VARCHAR(15),
	telefone      VARCHAR(15),
	fax           VARCHAR(15),
	regime_tributario SMALLINT,
	PRIMARY KEY (cod_empresa)
);

ALTER TABLE tbl_empresa 
  ADD CONSTRAINT fk1_tbl_empresa FOREIGN KEY (cod_cidade) 
  REFERENCES tbl_cidade (cod_cidade);

CREATE TABLE tbl_natureza_operacao (
   cod_natureza_operacao SMALLINT NOT NULL,
   den_natureza_operacao VARCHAR(30),
   cod_cfop_padrao       SMALLINT,
   cod_cst_icms_padrao   VARCHAR(4),
   cod_cst_ipi_padrao    VARCHAR(4),
   cod_cst_pis_padrao    VARCHAR(4),
   cod_cst_cofins_padrao VARCHAR(4),
   percentual_icms       DECIMAL(5,2),
   info_complementar     VARCHAR(4000)
   PRIMARY KEY (cod_natureza_operacao)
);

CREATE TABLE tbl_nota_fiscal (
   cod_empresa            CHAR(02) NOT NULL,
   cod_nota_fiscal        INTEGER NOT NULL AUTO_INCREMENT,
   tipo_nota_fiscal       SMALLINT NOT NULL,
   num_nota_fiscal        INTEGER NOT NULL,
   serie_nota_fiscal      SMALLINT,
   modelo_nota_fiscal     VARCHAR(2),
   ies_situacao           CHAR(1) NOT NULL, 
   cod_natureza_operacao  SMALLINT, 
   cod_forma_pagto        SMALLINT,  
   cod_cliente            VARCHAR(15),
   cod_fornecedor         VARCHAR(15),
   tipo_frete             SMALLINT,
   cod_transportador      VARCHAR(15),
   placa_veiculo          VARCHAR(10),
   estado_placa_veiculo   VARCHAR(2),
   placa_reboque          VARCHAR(10),
   estado_placa_reboque   VARCHAR(2),
   qtd_volume             INTEGER,
   especie_volume         VARCHAR(30),
   marca_volume           VARCHAR(30),
   numeracao_volume       VARCHAR(30),
   peso_liquido           DECIMAL(15,3),
   peso_bruto             DECIMAL(15,3),
   volume_cubico          DECIMAL(15,3),
   valor_mercadoria       DECIMAL(15,2),
   valor_desconto         DECIMAL(15,2),
   valor_duplicata        DECIMAL(15,2),
   valor_frete            DECIMAL(15,2),
   valor_seguro           DECIMAL(15,2),
   outras_despesas        DECIMAL(15,2),
   valor_nota_fiscal      DECIMAL(15,2) NOT NULL,      
   usuario_inclusao       VARCHAR(16) NOT NULL,
   data_hora_emissao      DATETIME NOT NULL,
   data_hora_saida        DATETIME,
   data_hora_entrega      DATETIME,   
   data_hora_cancelamento DATETIME,
   motivo_cancelamento    SMALLINT,
   usuario_cancelamento   VARCHAR(16),
   info_complementar      VARCHAR(4000),
   info_adicional_fisco   VARCHAR(2000),
   PRIMARY KEY (cod_nota_fiscal,cod_empresa)
);

ALTER TABLE tbl_nota_fiscal  
  ADD CONSTRAINT fk1_tbl_nota_fiscal FOREIGN KEY (cod_empresa)
    REFERENCES tbl_empresa (cod_empresa);

ALTER TABLE tbl_nota_fiscal  
  ADD CONSTRAINT fk2_tbl_nota_fiscal FOREIGN KEY (cod_natureza_operacao)
    REFERENCES tbl_natureza_operacao (cod_natureza_operacao);

ALTER TABLE tbl_nota_fiscal  
  ADD CONSTRAINT fk3_tbl_nota_fiscal FOREIGN KEY (cod_cliente)
    REFERENCES tbl_cliente (cod_cliente);

ALTER TABLE tbl_nota_fiscal  
  ADD CONSTRAINT fk4_tbl_nota_fiscal FOREIGN KEY (cod_fornecedor)
    REFERENCES tbl_fornecedor (cod_fornecedor);

CREATE TABLE tbl_nota_fiscal_tributo (
   cod_empresa        CHAR(02) NOT NULL,
   cod_nota_fiscal    INTEGER NOT NULL,
   cod_tributo        VARCHAR(10) NOT NULL,
   base_calculo       DECIMAL(15,2),
   valor_tributo      DECIMAL(15,2),
   PRIMARY KEY (cod_empresa,cod_nota_fiscal,cod_tributo)
);

ALTER TABLE tbl_nota_fiscal_tributo 
  ADD CONSTRAINT fk1_tbl_nota_fiscal_tributo FOREIGN KEY (cod_nota_fiscal,cod_empresa)
    REFERENCES tbl_nota_fiscal (cod_nota_fiscal,cod_empresa) ON DELETE CASCADE;

CREATE TABLE tbl_nota_fiscal_nfe (
   cod_empresa         CHAR(02) NOT NULL,
   cod_nota_fiscal     INTEGER NOT NULL,
   chave_acesso        VARCHAR(44),
   ult_forma_emissao   SMALLINT,
	protoc_envio_normal VARCHAR(15),
	data_rec_protoc_1   DATETIME,
	protoc_envio_cancel VARCHAR(15),
	data_rec_protoc_2   DATETIME,
	registro_dpec       VARCHAR(15),
	data_rec_protoc_3   DATETIME,
	status_envio_nfe    CHAR(1),   
   PRIMARY KEY (cod_empresa, cod_nota_fiscal)
);

ALTER TABLE tbl_nota_fiscal_nfe 
  ADD CONSTRAINT fk1_tbl_nota_fiscal_nfe FOREIGN KEY (cod_nota_fiscal,cod_empresa)
    REFERENCES tbl_nota_fiscal (cod_nota_fiscal,cod_empresa);


CREATE TABLE tbl_nota_fiscal_item (
   cod_empresa        CHAR(02) NOT NULL,
   cod_nota_fiscal    INTEGER NOT NULL,
   seq_produto        SMALLINT NOT NULL,
   cod_produto        VARCHAR(15) NOT NULL,
   den_produto        VARCHAR(75),
   cod_ncm            VARCHAR(08),
   cod_ean            VARCHAR(14),
   cod_cfop           SMALLINT,
   cod_extipi         VARCHAR(3),
   origem_mercadoria  SMALLINT,
   cod_unid_medida    VARCHAR(3),
   qtd_produto        DECIMAL(15,3),
   valor_unitario     DECIMAL(15,3),
   valor_desconto     DECIMAL(15,2),
   valor_frete        DECIMAL(15,2),
   valor_seguro       DECIMAL(15,2),
   valor_total        DECIMAL(15,2),
   cod_pedido         INTEGER,
   seq_pedido         SMALLINT,
   classe_enq_ipi     VARCHAR(5),
   cod_enq_ipi        VARCHAR(3)
   PRIMARY KEY (cod_empresa, cod_nota_fiscal, seq_produto)
);

ALTER TABLE tbl_nota_fiscal_item 
  ADD CONSTRAINT fk1_tbl_nota_fiscal_item FOREIGN KEY (cod_nota_fiscal,cod_empresa)
    REFERENCES tbl_nota_fiscal (cod_nota_fiscal,cod_empresa);

ALTER TABLE tbl_nota_fiscal_item 
  ADD CONSTRAINT fk2_tbl_nota_fiscal_item FOREIGN KEY (cod_produto)
    REFERENCES tbl_produto (cod_produto);
    
CREATE TABLE tbl_nota_fiscal_item_tributo (
   cod_empresa         CHAR(02) NOT NULL,
   cod_nota_fiscal     INTEGER NOT NULL,
   seq_produto         SMALLINT NOT NULL,
   cod_tributo         VARCHAR(10) NOT NULL,
   cod_cst             VARCHAR(4),
   mod_def_base_calc   SMALLINT,
   perc_tributo        DECIMAL(5,2),
   base_calculo        DECIMAL(15,2),
   valor_tributo       DECIMAL(15,2),
   perc_red_base_calc  DECIMAL(5,2),
   perc_marg_valor_add DECIMAL(5,2),
   valor_unit_tributo  DECIMAL(15,3),
   qtd_total_tributo   DECIMAL(15,3),
   PRIMARY KEY (cod_empresa, cod_nota_fiscal, seq_produto, cod_tributo)
);

ALTER TABLE tbl_nota_fiscal_item_tributo 
  ADD CONSTRAINT fk1_tbl_nota_fiscal_item_trib FOREIGN KEY (cod_empresa, cod_nota_fiscal, seq_produto)
    REFERENCES tbl_nota_fiscal_item (cod_empresa, cod_nota_fiscal, seq_produto) ON DELETE CASCADE;
    
ALTER TABLE tbl_usuario ADD COLUMN empresa_padrao CHAR(2);

ALTER TABLE tbl_produto ADD cod_extipi VARCHAR(3)

ALTER TABLE tbl_produto ADD classe_enq_ipi VARCHAR(5)
ALTER TABLE tbl_produto ADD cod_enq_ipi VARCHAR(3)

DELETE FROM tbl_pre_meta_fiedls 

INSERT INTO tbl_pre_meta_fiedls
SELECT col.table_name, col.COLUMN_NAME, col.ordinal_position column_order,
       col.data_type column_datatype, 
       col.COLUMN_TYPE column_typename, 
       CASE col.data_type 
       WHEN 'char' THEN col.CHARACTER_MAXIMUM_LENGTH
       WHEN 'varchar' THEN col.CHARACTER_MAXIMUM_LENGTH
       WHEN 'smallint' THEN col.NUMERIC_PRECISION
       WHEN 'int' THEN col.NUMERIC_PRECISION
       WHEN 'integer' THEN col.NUMERIC_PRECISION
       WHEN 'decimal' THEN col.NUMERIC_PRECISION
       WHEN 'date' THEN 10
       WHEN 'datetime' THEN 18
       ELSE 0 END column_size,
       CASE WHEN col.numeric_precision IS NULL THEN 0 ELSE col.numeric_precision END column_precision,
       CASE WHEN col.column_key = 'PRI' THEN 'S' ELSE 'N' END column_ispkkey,
       CASE WHEN col.is_nullable = 'NO' THEN 'N' ELSE 'S' END column_isnull,
       CASE WHEN idx.index_name IS NOT NULL THEN 'S' ELSE 'N' END column_isindex,
       CASE WHEN fk.CONSTRAINT_NAME IS NOT NULL THEN 'S' ELSE 'N' END column_isfkkey,
       'N','N','N','N','N',32768,
       fk.REFERENCED_TABLE_NAME fk_table_name, fk.REFERENCED_COLUMN_NAME fk_column_name
  FROM information_schema.columns col
  LEFT JOIN information_schema.statistics idx
    ON idx.table_schema = col.table_schema
   AND idx.table_name = col.table_name
   AND idx.column_name = col.column_name
   AND idx.index_name != 'PRIMARY' 

  LEFT JOIN information_schema.KEY_COLUMN_USAGE fk
    ON fk.table_schema = col.table_schema
   AND fk.table_name = col.table_name
   AND fk.column_name = col.column_name
   AND fk.CONSTRAINT_name != 'PRIMARY' 

 WHERE col.table_schema = 'sistemasfg'
 AND col.table_name = 'tbl_usuario'


   FD_NONE    = 0x00000000,
   FD_PKKEY   = 0x00000001,
   FD_BROWSE  = 0x00000002,
   FD_SEARCH  = 0x00000004,
   FD_ORDERB  = 0x00000008,
   FD_ORDERS  = 0x00000010,
   FD_INDEX   = 0x00000020,
   FD_NOTNULL = 0x00000040,
   FD_FKKEY   = 0x00000080,
   FD_MONEY   = 0x00000100,
   FD_EDIT    = 0x00008000,
   FD_COMBO   = 0x00004000,
   FD_CHECK   = 0x00002000
   
   8192  - FD_CHECK
   16384 - FD_COMBO
   32768 - FD_EDIT
   
CREATE TABLE tbl_pre_meta_fiedls (
table_name VARCHAR (64)
, column_name VARCHAR (64)
, column_order INTEGER
, column_datatype VARCHAR (64)
, column_typename VARCHAR (64)
, column_size INTEGER
, column_precision INTEGER
, column_ispkkey CHAR (1)
, column_isnull CHAR (1)
, column_isindex CHAR (1)
, column_isfkkey CHAR (1)
, column_isbrowse CHAR (1)
, column_issearch CHAR(1)
, column_orderb CHAR(1)
, column_orders CHAR(1)
, column_ismoney CHAR(1)
, column_editcmp INTEGER
, fk_table_name VARCHAR (64)
, fk_column_name VARCHAR (64)
)
   
SELECT * FROM tbl_pre_meta_fiedls
   
CREATE TABLE tbl_meta_fiedls (
table_name VARCHAR (64)
, column_name VARCHAR (64)
, column_order INTEGER
, column_datatype VARCHAR (64)
, column_typename VARCHAR (64)
, column_size INTEGER
, column_precision INTEGER
, column_properties INTEGER
, fk_table_name VARCHAR (64)
, fk_column_name VARCHAR (64)
, PRIMARY KEY (table_name, column_name)
)

ALTER TABLE tbl_pre_meta_fiedls ADD PRIMARY KEY (table_name, column_name)

INSERT INTO tbl_meta_fiedls
SELECT table_name, column_name, column_order, column_datatype, column_typename, 
      column_size, column_pecision, 
      CASE WHEN column_ispkkey = 'S' THEN 1 ELSE 0 END +
      CASE WHEN column_isnull = 'N' THEN 64 ELSE 0 END +
      CASE WHEN column_isindex = 'S' THEN 32 ELSE 0 END +
      CASE WHEN column_isfkkey = 'S' THEN 128 ELSE 0 END +
      CASE WHEN column_isbrowse = 'S' THEN 2 ELSE 0 END + 
      CASE WHEN column_issearch = 'S' THEN 4 ELSE 0 END +
      CASE WHEN column_orderb = 'S' THEN 8 ELSE 0 END +
      CASE WHEN column_orders = 'S' THEN 16 ELSE 0 END +
      CASE WHEN column_ismoney = 'S' THEN 256 ELSE 0 END  + 
      column_editcmp column_properties, fk_table_name, fk_column_name
 FROM tbl_pre_meta_fiedls 
 
SELECT * from tbl_meta_fiedls



ALTER TABLE tbl_meta_fiedls ADD column_label VARCHAR(100)
ALTER TABLE tbl_meta_fiedls ADD column_editmask VARCHAR(64)
, 
tbl_representante

ALTER TABLE tbl_representante ADD nome_fantasia VARCHAR(50) after den_representante;
ALTER TABLE tbl_representante ADD observacao VARCHAR(4000);

cod_cli_for_rep_aut
prox_cod_cliente
prox_cod_fornecedor
prox_cod_representa
rep_alt_cli_for_rep

ALTER TABLE tbl_cliente ADD COLUMN cod_representante VARCHAR(15);

ALTER TABLE tbl_cliente ADD cod_classificacao INTEGER;


CREATE TABLE tbl_class_cliente (
    cod_classificacao INTEGER NOT NULL AUTO_INCREMENT,
    den_classificacao VARCHAR(30) NOT NULL,
    PRIMARY KEY (cod_classificacao)
);

ALTER TABLE tbl_cliente
  ADD CONSTRAINT fk2_tbl_cliente FOREIGN KEY (cod_representante) 
  REFERENCES tbl_representante (cod_representante);

ALTER TABLE tbl_cliente
  ADD CONSTRAINT fk3_tbl_cliente FOREIGN KEY (cod_classificacao) 
  REFERENCES tbl_class_cliente (cod_classificacao);