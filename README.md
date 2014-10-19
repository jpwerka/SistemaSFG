SistemaSFG
==========

Este é um sistema que inicialmente foi desenvolvido com propósito comercial, porém o projeto foi abortado.
Como foram investidas muitas horas e o sistema é bem funcional, estou abrindo o código para quem tiver interesse em dar continuidade a este projeto, com a condição de que toda melhoria seja repassada e implementada nesta versão do projeto.
Este é um projeto totalmente feito na IDE de desenvolvimento da Borland C++Builder6, primo do Delphi, utilizando a VCL como sua biblioteca de interface gráfica e conexão ZEOS com MySQL.

Até tentei portar este projeto para versão mais recente da atual ferramenta de desenvolvimento da Embarcadero, o C++Builder XE, porém como esta nova IDE exige muitos recursos de máquina e não tinha no momento, mantive na versão anterior mesmo.

Este projeto é dependente de algumas customizações e componentes de terceiros que podem ser adquiridos entrando em contato pelo e-mail jpwerka@gmail.com. Estes componentes são instalados em conjunto na IDE de desenvolvimento para o projeto então poder ser aberto e compilado. Com exceção dos componentes customizados

Os componentes em questão são:
- Zeos Database Component -  Version 6.6.6-stable - http://sourceforge.net/projects/zeoslib/
- Fast  Report Component -  Version 4.6.8 - http://www.fast-report.com/pt/
- Indy Components – Version 10.5.8 - http://www.indyproject.org/index.en.aspx
- Windows XP Theme Manager - http://www.soft-gems.net/index.php/controls/windows-xp-theme-manager
- Sfg Customizado – Contém o StringAlignGrid e outros components customizados.

Estou abrindo o projeto para desenvolvimento comunitário onde o objetivo não é vender um produto, mas serviços de customização, portanto as melhorias incorporadas ao produto devem ser desenvolvidas de forma livre. Visto que o produto foi pensado em ser modularizado de forma a poder ser customizado para estender suas funcionalidades.

O Software é composto dos seguintes módulos:
- FrameWork
- Estoque
- Compras
- Vendas
- Finaceiro
- Fiscal

O módulo de framework comporta toda a base do sistema e contém todas as funcionalidades básicas para implementar novos cadastros/relatórios.

O módulo de estoque é composto pelo cadastro de produtos e gerenciamento básico de estoque.

O Módulo de compras contém o cadastro de fornecedores e pedidos de compra.

O módulo de vendas contém o cadastro de clientes e geração de orçamento e pedidos de venda.

O módulo financeiro contém o controle de fluxo de caixa com entradas e saídas além de controle de contas a pagar a receber.

O módulo fiscal permite a geração de dados para notas fiscais que podem ser envidas ao Sefax utilizando o programa oficial disponibilizado pela receita federal para pequenas empresas lançarem notas manuais. Atualmente ele exporta os dados em formato txt para importação no programa da receita federal. Foi neste ponto que o desenvolvimento do sistema parou.
