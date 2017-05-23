========================
ShoppingSystem项目概述
========================
    该项目是一个用MFC框架编写的C/S项目，主要功能包括用户登录、商品增删查改、购物结算、当日卖出商品查询及售货员管理等。

========================
ShoppingSystem文件目录
========================
    该项目运用三层架构的思想编写软件。
    1、Framework目录是mfc框架生成的文件，包括：
        resource.h
        ShoppingSystem.h  //框架主程序，包含theApp
        stdafx.h

    2、Tools目录是整个项目用到的数据转换工具，包括：
        Tools.h  //整型和浮点型转换为CString

    3、DAL目录是数据库访问类，包括：
        Ado.h  //成真版ADO
        AdoCommand.h  //成真版ADO
        AdoRecordSet.h  //成真版ADO
        DBAccess.h  封装了使用Sql语句进行返回数据集的查询及非数据集的增删改

    4、BLL目录是整个项目的业务逻辑层，包括：
        AdminManager.h  //管理员管理类
        GoodsManager.h  //商品管理类
        GSalesManager.h  //购物结算、当日卖出商品的业务逻辑类
        LoginManager.h  //管理员或售货员登录管理的基类，派生出AdminManager和SalesmanManager两个类
        SalesmanManager.h  //售货员管理类

    5、Entity目录是对应数据库各个表的实体类
        Admin.h
        Goods.h
        GSales.h
        Salesman.h

========================
数据库设计和功能设计文档
========================
    详见files文件夹下的需求说明书部分