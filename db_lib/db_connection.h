#pragma once

#include "QtSql"

QSqlQuery connection_to_db();

QSqlQuery connection_to_db_with_measure();

QSqlQuery connection_to_db_with_lib();

QSqlQuery connection_to_db_with_signal();

QSqlQuery connection_to_db_with_control();

QSqlQuery connection_to_cp_db();

void update_table_lib(QString str, int int1, int int2, int int3, int int4, int id);

void update_table_mes(QString str, int int1, double double1, double double2, double double3, int id);

void update_table_control(QString str, int int1, int id);

void update_table_sign(QString str, int int1, int id);