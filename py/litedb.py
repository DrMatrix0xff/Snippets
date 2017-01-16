#!/usr/bin/env python
# coding: utf-8

import sqlite3
import uuid
import datetime

def main():
    dbname = "meme.db"
    db = sqlite3.Connection(dbname)
    cursor = db.cursor()
    cursor.execute("CREATE TABLE sessions (sid varchar(64) NOT NULL, atime timestamp NOT NULL DEFAULT current_timestamp)")
    
    l1 = []
    l2 = []
    for i in range(5):
        s = str(uuid.uuid4())
        l1.append(s)
        l2.append(datetime.datetime.today() + datetime.timedelta(i))

    cursor.executemany(
        "INSERT INTO sessions (sid, atime) VALUES (?, ?)",
        zip(l1, l2)
    )
    db.commit()

if __name__ == '__main__':
    main()
