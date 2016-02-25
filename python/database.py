import sqlite3

class Database(object):
    def __init__(self, path):
        self.conn = sqlite3.connect(path)
        self.c = self.conn.cursor()

    def __del__(self):
        self.conn.close()

    def create_table(self, name, columns):
        command = 'CREATE TABLE {0} ({1})'.format(name, ",".join(columns))
        self.c.execute(command)
        self.conn.commit()

    def get_id(self, table, column, value):
        command = "SELECT {0}Id FROM {0} WHERE {1}=? LIMIT 1".format(table, column)
        self.c.execute(command, (value,))
        assembly_id = self.c.fetchone()[0]
        return assembly_id

    def insert(self, table, rows):
        nb_vals = len(rows[0])
        wild_cards = ','.join(['?']*nb_vals)
        sql_insert = 'INSERT OR REPLACE INTO {0} VALUES ({1})'.format(table, wild_cards)
        self.c.executemany(sql_insert, rows)
        self.conn.commit()