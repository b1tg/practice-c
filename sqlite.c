/**
 * @file sqlite.c
 * @author b1tg (https://b1tg.github.io)
 * @brief play with sqlite
 * @version 0.1
 * @date 2022-02-28
 * 
 */

// https://zetcode.com/db/sqlitec/

#include <sqlite3.h>
#include <stdio.h>

int callback(void *a, int b, char**c, char**d) {
        printf("===========\n");
        for(int i=0;i<b;i++) {
                printf("%s: %s\n", d[i], c[i]);
        }
        return 0;
}

int main() {
        printf("sqlite version: %s\n", sqlite3_libversion());
        sqlite3 *db;
        int rc = sqlite3_open("test.db", &db);
        if (rc != SQLITE_OK) {
                sqlite3_close(db);
                return -1;
        }

        char* sqls = "DROP TABLE IF EXISTS Tweet;"
                "CREATE TABLE Tweet(Id INT, Text TEXT);"
                "INSERT INTO Tweet Values(0, 'look');"
                "INSERT INTO Tweet Values(1, 'at');"
                "INSERT INTO Tweet Values(2, 'you');";
        char *err = 0;
        rc = sqlite3_exec(db, sqls, 0, 0, &err);
        if (rc != SQLITE_OK) {
                sqlite3_free(err);
                sqlite3_close(db);
                return -2;
        }

        //// get data from sqlite3
        char *sql = "select * from Tweet";
        rc = sqlite3_exec(db, sql, callback, 0, &err);
        if (rc != SQLITE_OK) {
                sqlite3_free(err);
                sqlite3_close(db);
                return -3;
        }

        sqlite3_close(db);
        printf("end\n");
        return 0;
}

// ===========
// Id: 0
// Text: look
// ===========
// Id: 1
// Text: at
// ===========
// Id: 2
// Text: you

// sqlite> .mode column
// sqlite> .headers on
// sqlite> select * from Tweet;
// Id          Text      
// ----------  ----------
// 0           look      
// 1           at        
// 2           you       
// sqlite> 
