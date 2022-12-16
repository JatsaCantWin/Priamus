#include <iostream>
#include <cassandra.h>
#include "SQLiteConnector.h"

void testSQL()
{
    SQLiteConnector sqliteConnector("test.db");

    const std::string sqlStatement = "PRAGMA TABLE_INFO(tracks);";
    //const std::string sqlStatement = "SELECT * FROM sqlite_master";
    Table sqlData;

    sqliteConnector.executeSQL(sqlStatement, sqlData);

    sqlData.print();
    std::cout << std::endl;
    sqliteConnector.constructTable("tracks").print();
}

void testCassandra()
{
    CassFuture* connect_future = nullptr;
    CassCluster* cluster = cass_cluster_new();
    CassSession* session = cass_session_new();

    /* Add contact points */
    cass_cluster_set_contact_points(cluster, "127.0.0.1");

    /* Provide the cluster object as configuration to connect the session */
    connect_future = cass_session_connect(session, cluster);

    /* This operation will block until the result is ready */
    CassError rc = cass_future_error_code(connect_future);

    if (rc != CASS_OK) {
        /* Display connection error message */
        const char* message;
        size_t message_length;
        cass_future_error_message(connect_future, &message, &message_length);
        fprintf(stderr, "Connect error: '%.*s'\n", (int)message_length, message);
    }

    /* Run queries... */

    cass_future_free(connect_future);
    cass_session_free(session);
    cass_cluster_free(cluster);
}

int main(int argc, char** argv)
{
    testCassandra();
    return 0;
}