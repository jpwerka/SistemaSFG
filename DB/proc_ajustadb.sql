DROP PROCEDURE ajusta_schema_db;

DELIMITER $$
CREATE PROCEDURE ajusta_schema_db( in_schema_name varchar(100))
BEGIN
   DECLARE not_found INT DEFAULT 0;
   DECLARE l_table_name VARCHAR(64);
   DECLARE l_constraint_name VARCHAR(64);
   DECLARE l_index_name VARCHAR(64);
   DECLARE l_column_name VARCHAR(64);
   DECLARE l_data_type VARCHAR(64);
   DECLARE l_is_nullable VARCHAR(10);
   declare l_extra varchar(30);

   DECLARE cq_tb CURSOR FOR
    SELECT table_name 
      FROM information_schema.tables
     WHERE table_schema = in_schema_name
       AND table_type = 'BASE TABLE'
     ORDER BY table_name;

   DECLARE cq_tbfk CURSOR FOR
    SELECT table_name, constraint_name 
      FROM information_schema.table_constraints
     WHERE table_schema = in_schema_name
       AND constraint_type = 'FOREIGN KEY'
     ORDER BY table_name, constraint_name;

   DECLARE cq_tbidx CURSOR FOR
    SELECT DISTINCT table_name, index_name
      FROM information_schema.statistics
     WHERE table_schema = in_schema_name
       AND index_name != 'PRIMARY'
     ORDER BY table_name, index_name;  

   DECLARE cq_colnr CURSOR FOR
   SELECT c.table_name, c.column_name, c.data_type, c.is_nullable, c.extra
     FROM information_schema.columns c
    INNER JOIN information_schema.tables t
       ON t.table_schema = c.table_schema 
      AND t.table_name = c.table_name
    WHERE c.table_schema = in_schema_name
      AND data_type in ('int', 'smallint')
      AND t.table_type = 'BASE TABLE'
      AND column_type like '%unsigned%';

   DECLARE CONTINUE HANDLER FOR NOT FOUND SET not_found=1;

   SET not_found = 0;
   OPEN cq_tbfk;
   read_loop: LOOP
      FETCH cq_tbfk INTO l_table_name,
                         l_constraint_name;
      IF not_found THEN
         LEAVE read_loop;
      END IF;
         
      SET @sql_stmt = CONCAT('ALTER TABLE `',in_schema_name,'`.`',l_table_name, '` DROP FOREIGN KEY ',l_constraint_name,';');
      PREPARE ce_tbfk FROM @sql_stmt;
      EXECUTE ce_tbfk;
      DEALLOCATE PREPARE ce_tbfk;

   END LOOP;
   CLOSE cq_tbfk;

   SET not_found = 0;
   OPEN cq_tbidx;
   read_loop: LOOP
      FETCH cq_tbidx INTO l_table_name,
                          l_index_name;
      IF not_found THEN
         LEAVE read_loop;
      END IF;
         
      SET @sql_stmt = CONCAT('ALTER TABLE `',in_schema_name,'`.`',l_table_name, '` DROP INDEX ',l_index_name,';');
      PREPARE ce_tbidx FROM @sql_stmt;
      EXECUTE ce_tbidx;
      DEALLOCATE PREPARE ce_tbidx;

   END LOOP;
   CLOSE cq_tbidx;

   SET not_found = 0;
   OPEN cq_tb;
   read_loop: LOOP
      FETCH cq_tb INTO l_table_name;
      IF not_found THEN
         LEAVE read_loop;
      END IF;
      
      SET @sql_stmt = CONCAT('ALTER TABLE `',in_schema_name,'`.`',l_table_name, '` CONVERT TO CHARACTER SET ''utf8'' COLLATE ''utf8_general_ci'';');
      PREPARE ca_tbutf8 FROM @sql_stmt;
      EXECUTE ca_tbutf8;
      DEALLOCATE PREPARE ca_tbutf8;

   END LOOP;
   CLOSE cq_tb;

   SET not_found = 0;
   OPEN cq_colnr;
   read_loop: LOOP
      FETCH cq_colnr INTO l_table_name,
                          l_column_name,
                          l_data_type,
                          l_is_nullable,
                          l_extra;
      IF not_found THEN
         LEAVE read_loop;
      END IF;
      
      IF l_is_nullable = 'YES' THEN
         SET l_is_nullable = 'NULL';
      ELSE
         SET l_is_nullable = 'NOT NULL';
      END IF;
      IF l_extra = 'auto_increment' THEN
         SET l_extra = 'AUTO_INCREMENT';
      ELSE
         SET l_extra = '';
      END IF;
      
      SET @sql_stmt = CONCAT('ALTER TABLE `',in_schema_name,'`.`',l_table_name, '` MODIFY COLUMN ',l_column_name,' ',l_data_type,' ',l_is_nullable,' ',l_extra,';');
      PREPARE ca_colnr FROM @sql_stmt;
      EXECUTE ca_colnr;
      DEALLOCATE PREPARE ca_colnr;

   END LOOP;
   CLOSE cq_colnr;  
   
END $$

DROP TRIGGER IF EXISTS [dbname].tr_conta_pagar_update
DROP TRIGGER IF EXISTS [dbname].tr_conta_receber_update
DROP TRIGGER IF EXISTS [dbname].pedido_venda_after_delete

ALTER DATABASE [dbname] DEFAULT CHARACTER SET 'utf8' COLLATE 'utf8_general_ci';

call ajusta_schema_db('sistemasfg');


DROP TRIGGER IF EXISTS dbcafeteria.tr_pedido_venda_after_delete
DROP TRIGGER IF EXISTS dbcafeteria.tr_cta_rec_pagto_after_update
DROP TRIGGER IF EXISTS dbcafeteria.tr_cta_pag_pagto_after_update


