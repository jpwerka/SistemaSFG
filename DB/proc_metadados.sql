CREATE PROCEDURE carrega_metadados()
BEGIN
   DECLARE not_found INT DEFAULT 0;
   DECLARE l_table_name VARCHAR(64);
   DECLARE l_column_name VARCHAR(64);
   DECLARE l_fktable_name VARCHAR(64);
   DECLARE l_fkcolumn_name VARCHAR(64);
   DECLARE cq_foreignkey CURSOR FOR
   SELECT table_name, column_name, 
          referenced_table_name, referenced_column_name
     FROM information_schema.key_column_usage fk
    WHERE fk.table_schema = DATABASE()
      AND fk.constraint_name != 'PRIMARY'
    ORDER BY fk.constraint_name;  
   DECLARE CONTINUE HANDLER FOR NOT FOUND SET not_found=1;
   
   -- Cria a tabela temporária, caso não exista
   CREATE TEMPORARY TABLE IF NOT EXISTS tt_meta_fields (
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
   , column_isbrowse CHAR(1)
   , column_orderb CHAR(1)
   , column_issearch CHAR(1)
   , column_orders CHAR(1)
   , column_fklist CHAR(1)
   , column_ismoney CHAR(1)
   , fk_table_name VARCHAR (64)
   , fk_column_name VARCHAR (64)
   , column_label VARCHAR (100)
   , column_editmask VARCHAR (64)
   , column_checkvalues VARCHAR (64)
   , more_fkkey CHAR(1)
   , column_editcmp VARCHAR(16),
    PRIMARY KEY (table_name, column_name));

   -- Limpa a temporária caso existam informações
   DELETE FROM tt_meta_fields;
  
   INSERT INTO tt_meta_fields
      (table_name, column_name, column_order,
       column_datatype, column_typename, column_size, column_precision,
       column_ispkkey, column_isnull, column_isbrowse, column_orderb, 
       column_issearch, column_orders, column_ismoney, column_fklist, 
       fk_table_name, fk_column_name, column_label, column_editmask, 
       column_checkvalues, column_editcmp)
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
          ELSE col.CHARACTER_MAXIMUM_LENGTH END column_size,
          CASE WHEN col.numeric_precision IS NULL THEN 0 ELSE col.numeric_precision END column_precision,
          CASE WHEN col.column_key = 'PRI' THEN 'S' ELSE 'N' END column_ispkkey,
          CASE WHEN col.is_nullable = 'NO' THEN 'N' ELSE 'S' END column_isnull,
          CASE WHEN (mtd.column_properties & 0x00000002) > 0 THEN 'S' ELSE 'N' END column_isbrowse,
          CASE WHEN (mtd.column_properties & 0x00000008) > 0 THEN 'S' ELSE 'N' END column_orderb,
          CASE WHEN (mtd.column_properties & 0x00000004) > 0 THEN 'S' ELSE 'N' END column_issearch,
          CASE WHEN (mtd.column_properties & 0x00000010) > 0 THEN 'S' ELSE 'N' END column_orders,
          CASE WHEN (mtd.column_properties & 0x00000100) > 0 THEN 'S' ELSE 'N' END column_ismoney,
          CASE WHEN (mtd.column_properties & 0x00000200) > 0 THEN 'S' ELSE 'N' END column_fklist,
          mtd.fk_table_name, mtd.fk_column_name, 
          mtd.column_label, mtd.column_editmask, mtd.column_checkvalues,
          CASE mtd.column_editcmp
          WHEN 3 THEN 'CheckBox'
          WHEN 2 THEN 'ComboBox'
         ELSE 'TextBox' END column_editcmp
     FROM information_schema.columns col
     LEFT JOIN tbl_meta_fiedls mtd
       ON mtd.table_name = col.table_name
      AND mtd.column_name = col.column_name
    WHERE col.table_schema = DATABASE();
     
   UPDATE tt_meta_fields
      SET column_isindex = ( 
       SELECT 'S'
         FROM information_schema.statistics idx
        WHERE idx.table_schema = DATABASE()
          AND idx.table_name = tt_meta_fields.table_name
          AND idx.column_name = tt_meta_fields.column_name); 
   
   UPDATE tt_meta_fields
      SET column_isindex = 'N'
    WHERE column_isindex IS NULL;
    
   -- Atualiza as FKs das tabelas
   SET not_found = 0;
   OPEN cq_foreignkey;
   read_loop: LOOP
       FETCH cq_foreignkey INTO l_table_name,
                                l_column_name,
                                l_fktable_name,
                                l_fkcolumn_name;
      IF not_found THEN
         LEAVE read_loop;
      END IF;
       
      UPDATE tt_meta_fields
         SET more_fkkey = 'S'
       WHERE table_name = l_table_name 
         AND column_name = l_column_name
         AND fk_table_name IS NOT NULL
         AND fk_table_name != l_fktable_name
         AND fk_column_name != l_fkcolumn_name;

      UPDATE tt_meta_fields
         SET column_isfkkey = 'S',
             fk_table_name = l_fktable_name,
             fk_column_name = l_fkcolumn_name
       WHERE table_name = l_table_name 
         AND column_name = l_column_name
         AND fk_table_name IS NULL;
         
   END LOOP;
   CLOSE cq_foreignkey;

   UPDATE tt_meta_fields
      SET column_isfkkey = 'N'
    WHERE column_isfkkey IS NULL;

   UPDATE tt_meta_fields
      SET more_fkkey = 'N'
    WHERE more_fkkey IS NULL;
    
END
